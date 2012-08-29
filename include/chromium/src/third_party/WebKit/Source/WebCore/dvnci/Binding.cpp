/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "Binding.h"
#include "Element.h"
#include "Text.h"
#include "EventTarget.h"

#include "DOMWindow.h"
#include "V8BindingState.h"
#include "V8DOMWindow.h"
#include "V8HiddenPropertyName.h"
#include "ExceptionCode.h"
#include "ContentSecurityPolicy.h"
#include "ScheduledAction.h"

#include <wtf/HashMap.h>
#include <wtf/UnusedParam.h>
#include <wtf/Threading.h>



#include <winsock2.h>
#include <custom/gui_executor.h>
#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/constdef.h>
#include <kernel/factory.h>

//#if defined(DEBUG)
namespace boost {

    void throw_exception(std::exception const & e) {
        throw e;
    }
}

bool BrowserDVNCI_isEditable();

//#endif

const int TICK_DVNCI_DURATION = 500;

struct guichrome_terminated_thread {

    guichrome_terminated_thread(dvnci::chrome_executor_ptr inf_) : inf(inf_), th(inf_) {
    }

    ~guichrome_terminated_thread() {
        if (inf && (!inf->terminated())) {
            inf->detachall();
            inf.terminate();
        }
        th.join();
    }

private:
    dvnci::chrome_executor_ptr inf;
    boost::thread th;
} ;

dvnci::chrome_executor_ptr getexecutordvnci() {
    static dvnci::fspath basepath = dvnci::getlocalbasepath();
    static dvnci::tagsbase_ptr kintf = dvnci::krnl::factory::build(basepath, 0);
    static dvnci::chrome_executor_ptr DVNCI_INTERFACE = dvnci::chrome_executor_ptr(new dvnci::chrome_gui_executor(kintf));
    static guichrome_terminated_thread dvnth(DVNCI_INTERFACE);
    return /*BrowserDVNCI_isEditable() ? dvnci::chrome_executor_ptr() :*/ DVNCI_INTERFACE;
}

void shutdown_dvnci_interface() {
    dvnci::chrome_executor_ptr intf = getexecutordvnci();
    if (intf) {
        if (!intf->terminated()) {
            intf->detachall();
            intf.terminate();
        }
    }
}

void dvnciMain(void* cntxt) {
    typedef boost::shared_ptr<dvnci::datetime> time_ptr;
    static time_ptr tick = time_ptr(new dvnci::datetime());
    static dvnci::chrome_executor_ptr intf = getexecutordvnci();

    if (intf && ((tick->is_special()) ||
            (dvnci::abs(dvnci::millisecondsbetween(*tick, dvnci::now())) > TICK_DVNCI_DURATION))) {
        tick.swap(time_ptr(new dvnci::datetime(dvnci::now())));
        intf->call();
    }
    WTF::callOnMainThread(dvnciMain, 0, TICK_DVNCI_DURATION);

}

void (*dvnciMainVar)(void*) = 0;

void initdvnciMain() {
    if (!dvnciMainVar) {
        dvnciMainVar = dvnciMain;
        WTF::callOnMainThread(dvnciMain, 0);
    }
}



namespace WebCore {



    namespace DVNCI {




        const String NULLDEFAULTSTRING = " ";



        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        class AttributeObserverImpl : public DVNDOMValueObserver {

            class attribute_expression_listener : public dvnci::expression_listener {
            public:

                attribute_expression_listener(AttributeObserverImpl * const lsnr, const std::wstring& deflt = L"") : dvnci::expression_listener(), listener(lsnr), stdvl(), dfltvl(deflt) {
                }

                virtual ~attribute_expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    stdvl = (val.valid() && !val.error()) ? dvnci::utf8_to_wstr(val.value<std::string > ()) : dfltvl;
                    vl = String(stdvl.c_str(), stdvl.size());
                    listener->setvalue(vl);
                }

                void setdefault() {
                    stdvl = dfltvl;
                    vl = String(stdvl.c_str(), stdvl.size());
                    listener->setvalue(vl);
                }

            private:
                AttributeObserverImpl * const listener;
                std::wstring stdvl;
                std::wstring dfltvl;
                String vl;
            } ;

        public:

            AttributeObserverImpl(Attribute * const attr, const AtomicString& val) :
            attribute(attr), elem(attr ? attr->element_ext() : 0), value(val), defaultvalue("") {
                registrate(elem, val);
            }

            virtual void setvalue(const String& val) {

                if (elem && attribute) {
                    ExceptionCode ec;
                    attribute->setValue(val);
                    elem->setAttribute(attribute->name(), attribute->value(), ec);
                }
            }

            virtual ~AttributeObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return exrptr;
            }

            const AtomicString& deflt() const {
                return defaultvalue;
            }


        private:

            dvnci::expression_listener_ptr registrate(Element * const el, const AtomicString& val) {
                std::wstring tmpw = std::wstring(val.characters(), val.length());
                std::wstring tmpdef = dvnci::attribute_default_expression(tmpw);
                tmpw = dvnci::attribute_expression(tmpw);
                defaultvalue = String(tmpdef.c_str(), tmpdef.size());

                if (tmpw.empty()) {
                    setvalue(defaultvalue);
                    return dvnci::expression_listener_ptr();
                }
                intf = getexecutordvnci();
                if (intf) {
                    exprstr = dvnci::wstr_to_utf8(tmpw);
                    exrptr = dvnci::expression_listener_ptr(new attribute_expression_listener(this, tmpdef));
                    /*if (exrptr.get())
                         static_cast<attribute_expression_listener*>(exrptr.get())->setdefault();*/
                    intf->regist_expr_listener(exprstr, exrptr);
                    return exrptr;
                }
                else
                    setvalue(defaultvalue);
                return dvnci::expression_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (exrptr)) {
                    intf->unregist_expr_listener(exrptr);
                }
            }

            Attribute * const attribute;
            Element * const elem;
            String value;
            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr intf;
            std::string exprstr;
            AtomicString defaultvalue;

        } ;




        //////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////

        class TextNodeObserverImpl : public DVNDOMValueObserver {

            class text_expression_listener : public dvnci::expression_listener {
            public:

                text_expression_listener(TextNodeObserverImpl * const lsnr, const std::wstring& deflt = L"") : dvnci::expression_listener(), listener(lsnr), stdvl(), vl() {
                }

                virtual ~text_expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    stdvl = dvnci::utf8_to_wstr(val.value<std::string > ());
                    vl =  String(stdvl.c_str(), stdvl.size());
                    listener->setvalue((val.valid() && !val.error())  ? vl : listener->deflt());
                }

            private:
                TextNodeObserverImpl * const listener;
                std::wstring stdvl;
                String vl;
            } ;

        public:

            TextNodeObserverImpl(Text * const txt, const String& val) :  text(txt), value(val), defaultvalue("") , spacevalue(" ") {
                registrate(txt, val);
            }

            virtual void setvalue(const String& val) {
                if (text) {
                    ExceptionCode ec;
                    text->replaceWholeText(val.isEmpty() ? spacevalue : val, ec);
                    ;
                }
            }

            virtual ~TextNodeObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return exrptr;
            }

            const String& deflt() const {
                return defaultvalue.length() ? defaultvalue : NULLDEFAULTSTRING;
            }



        private:

            dvnci::expression_listener_ptr registrate(Text * const txt, const String& val) {
                std::wstring tmpw = std::wstring(val.characters(), val.length());
                std::wstring tmpdef = dvnci::attribute_default_expression(tmpw);
                tmpw = dvnci::attribute_expression(tmpw);
                defaultvalue =  String(tmpdef.c_str(), tmpdef.size());
                setvalue(deflt());
                if (tmpw.empty()) {
                    return dvnci::expression_listener_ptr();
                }
                intf = getexecutordvnci();
                if (intf) {
                    exprstr = dvnci::wstr_to_utf8(tmpw);
                    exrptr = dvnci::expression_listener_ptr(new text_expression_listener(this, tmpdef));
                    if (exrptr) {
                        intf->regist_expr_listener(exprstr, exrptr);
                    }
                    return exrptr;
                }
                return dvnci::expression_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (exrptr)) {
                    intf->unregist_expr_listener(exrptr);
                }
            }

            Text * const text;
            String value;
            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr intf;
            std::string exprstr;
            String defaultvalue;
            String spacevalue;
        } ;






        ////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////

        impl_reftype DVNDOMValueObserver::create(Attribute * const el, const AtomicString& val) {
            return adoptRef(new AttributeObserverImpl(el, val));
        }

        impl_reftype DVNDOMValueObserver::create(Text * const txt, const String& val) {
            return adoptRef(new TextNodeObserverImpl(txt, val));

        }




        ////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////

        Observer::Observer(Attribute * const attr, const AtomicString& val) {
            if ((attr) && (val.find("#{") != WTF::notFound) && (val.find("}") != WTF::notFound)) {
                initdvnciMain();
                if (!valid()) {
                    impl = impl_reftype();
                    impl = DVNDOMValueObserver::create(attr, val);
                }
            }
        }

        Observer::Observer(Text * const txt, const String& val) {
            if (!val.isEmpty()) {
                if ((txt) && (val.find("#{") != WTF::notFound) && (val.find("}") != WTF::notFound)) {
                    initdvnciMain();
                    if (!valid()) {
                        if (impl)
                            impl = impl_reftype();
                        impl = DVNDOMValueObserver::create(txt, val);
                    }
                }
            }
        }

        bool Observer::valid() const {
            return impl ? impl->valid() : false;
        }










        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        class AlarmsObserverImpl : public AbstractEventObserver {

            class alarm_listener : public dvnci::alarms_listener {
                friend class AlarmsObserverImpl;
            public:

                alarm_listener(AlarmsObserverImpl * const lsnr, const std::string& grp = "", const std::string& agrp = "") : dvnci::alarms_listener(grp, agrp) , listener(lsnr) {
                }

                virtual ~alarm_listener() {
                }

                virtual void event(const dvnci::vect_alarms_row& val) {
                    listener->notyfy(val);
                }

            private:
                AlarmsObserverImpl * const listener;
            } ;

        public:

            AlarmsObserverImpl(EventTarget * const evtarget, const String& group_, const String& agroup_) : AbstractEventObserver(evtarget), group(group_), agroup(agroup_) {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::vect_alarms_row& val) {
                if (alarmlsnrptr && (target())) {
                    target()->dispatchAlarmsEvent(dvnci::alarms_table(val));
                }
            }

            virtual ~AlarmsObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return alarmlsnrptr;
            }




        private:

            dvnci::alarms_listener_ptr registrate() {
                intf = getexecutordvnci();
                if (intf) {
                    alarmlsnrptr = dvnci::alarms_listener_ptr(
                            new alarm_listener(this, std::string(group.utf8().data()), std::string(agroup.utf8().data())));
                    intf->regist_alarm_listener(alarmlsnrptr);
                    return alarmlsnrptr;
                }
                return dvnci::alarms_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (alarmlsnrptr)) {
                    intf->unregist_alarm_listener(alarmlsnrptr);
                }

            }

            String group;
            String agroup;
            dvnci::alarms_listener_ptr alarmlsnrptr;
            dvnci::chrome_executor_ptr intf;
            dvnci::vect_alarms_row value;
        } ;


        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        class JournalObserverImpl : public AbstractEventObserver {

            class journal_listener : public dvnci::journal_listener {
                friend class JournalObserverImpl;
            public:

                journal_listener(JournalObserverImpl * const lsnr) : dvnci::journal_listener() , listener(lsnr) {
                }

                virtual ~journal_listener() {
                }

                virtual void event(const dvnci::vect_journal_row& val) {
                    listener->notyfy(val);
                }

            private:
                JournalObserverImpl * const listener;
            } ;

        public:

            JournalObserverImpl(EventTarget * const evtarget, const String& filter_) : AbstractEventObserver(evtarget), filter(filter_)  {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::vect_journal_row& val) {
                if (journallsnrptr && (target())) {
                    target()->dispatchJournalEvent(dvnci::journal_table(val));
                }
            }

            virtual ~JournalObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return journallsnrptr;
            }




        private:

            dvnci::journal_listener_ptr registrate() {
                intf = getexecutordvnci();
                if (intf) {
                    journallsnrptr = dvnci::journal_listener_ptr(
                            new journal_listener(this));
                    intf->regist_journal_listener(journallsnrptr);
                    return journallsnrptr;
                }
                return dvnci::journal_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (journallsnrptr)) {
                    intf->unregist_journal_listener(journallsnrptr);
                }

            }

            String filter;
            dvnci::journal_listener_ptr journallsnrptr;
            dvnci::chrome_executor_ptr intf;
            dvnci::vect_journal_row value;
        } ;



        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        class DebugObserverImpl : public AbstractEventObserver {

            class debug_listener : public dvnci::debug_listener {
                friend class DebugObserverImpl;
            public:

                debug_listener(DebugObserverImpl * const lsnr) : dvnci::debug_listener() , listener(lsnr) {
                }

                virtual ~debug_listener() {
                }

                virtual void event(const dvnci::vect_debug_row& val) {
                    listener->notyfy(val);
                }

            private:
                DebugObserverImpl * const listener;
            } ;

        public:

            DebugObserverImpl(EventTarget * const evtarget, const String& filter_) : AbstractEventObserver(evtarget), filter(filter_)  {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::vect_debug_row& val) {
                if (debuglsnrptr && (target())) {
                    target()->dispatchDebugEvent(dvnci::debug_table(val));
                }
            }

            virtual ~DebugObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return debuglsnrptr;
            }


        private:

            dvnci::debug_listener_ptr registrate() {
                intf = getexecutordvnci();
                if (intf) {
                    debuglsnrptr = dvnci::debug_listener_ptr(
                            new debug_listener(this));
                    intf->regist_debug_listener(debuglsnrptr);
                    return debuglsnrptr;
                }
                return dvnci::debug_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (debuglsnrptr)) {
                    intf->unregist_debug_listener(debuglsnrptr);
                }

            }

            String filter;
            dvnci::debug_listener_ptr debuglsnrptr;
            dvnci::chrome_executor_ptr intf;
            dvnci::vect_debug_row value;
        } ;



        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////      

        class TrendsObserverImpl : public AbstractEventObserver {

            class trend_listener : public dvnci::trend_listener {
                friend class TrendsObserverImpl;
            public:

                trend_listener(TrendsObserverImpl * const lsnr, const dvnci::str_vect& tgs, dvnci::num64 histmilisec) : dvnci::trend_listener(tgs, histmilisec), listener(lsnr) {
                }

                virtual ~trend_listener() {
                }

                virtual void event(const dvnci::short_values_table& val) {
                    listener->notyfy(val);
                }

            private:
                TrendsObserverImpl * const listener;
            } ;

        public:

            TrendsObserverImpl(EventTarget * const evtarget, const Vector<String>& tags_, int period_ = 0) : AbstractEventObserver(evtarget), tags(tags_), period(period_) {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::short_values_table& val) {
                if (trendlsnrptr && target()) {
                    target()->dispatchTrendsEvent(dvnci::trends_table(val));
                }
            }

            virtual ~TrendsObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return trendlsnrptr;
            }




        private:

            dvnci::trend_listener_ptr registrate() {
                intf = getexecutordvnci();
                dvnci::str_vect tgs;
                for (Vector<String>::const_iterator it = tags.begin(); it != tags.end(); ++it)
                    if (!it->isEmpty())
                        tgs.push_back(std::string(it->utf8().data()));
                if (target() && intf && tgs.size()) {
                    trendlsnrptr = dvnci::trend_listener_ptr(new trend_listener(this, tgs, period));
                    intf->regist_trend_listener(trendlsnrptr);
                }
                return trendlsnrptr;
            }

            void unregistrate() {
                if ((intf) && (trendlsnrptr)) {
                    intf->unregist_trend_listener(trendlsnrptr);
                }
            }

            Vector<String> tags;
            int period;
            dvnci::trend_listener_ptr trendlsnrptr;
            dvnci::chrome_executor_ptr intf;
            std::vector<dvnci::short_value> value;
        } ;



        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////      

        class ExpressionObserverImpl : public AbstractEventObserver {

            class expression_listener : public dvnci::expression_listener {
            public:

                expression_listener(ExpressionObserverImpl * const lsnr) : listener(lsnr) {
                }

                virtual ~expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    listener->notyfy(val);
                }


            private:
                ExpressionObserverImpl * const listener;
            } ;

        public:

            ExpressionObserverImpl(EventTarget * const evtarget, const String& tag_) : AbstractEventObserver(evtarget), tag(tag_) {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::short_value& val) {
                if (expressionptr && target()) {
                    value = val;
                    target()->dispatchExpressionEvent(value, tag);
                }
            }

            virtual ~ExpressionObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return expressionptr;
            }




        private:

            dvnci::expression_listener_ptr registrate() {

                std::string tmp = dvnci::wstr_to_utf8(std::wstring(tag.characters(), tag.length()));
                intf = getexecutordvnci();
                if (intf) {
                    expressionptr = dvnci::expression_listener_ptr(new expression_listener(this));
                    if (expressionptr)
                        intf->regist_expr_listener(tmp, expressionptr);
                }
                return expressionptr;
            }

            void unregistrate() {
                if ((intf) && (expressionptr)) {
                    intf->unregist_expr_listener(expressionptr);
                }
            }

            dvnci::expression_listener_ptr expressionptr;
            dvnci::chrome_executor_ptr intf;
            String tag;
            dvnci::short_value value;
        } ;






        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createAlarmsObserver(EventTarget * const evtarget, const String& group, const String& agroup) {
            return adoptRef(new AlarmsObserverImpl(evtarget, group, agroup));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createJournalObserver(EventTarget * const evtarget, const String& filter) {
            return adoptRef(new JournalObserverImpl(evtarget, filter));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createDebugObserver(EventTarget * const evtarget, const String& filter) {
            return adoptRef(new DebugObserverImpl(evtarget , filter));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createTrendsObserver(EventTarget * const evtarget, const Vector<String>& tags, int period) {
            return adoptRef(new TrendsObserverImpl(evtarget, tags, period));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createExpressionObserver(EventTarget * const evtarget, const String& tag) {
            return adoptRef(new ExpressionObserverImpl(evtarget, tag));
        }

        static v8::Handle<v8::Value> dvnci_shortvalue_conv_exec(const dvnci::short_value& val) {
            if (val.nan()) return v8::Undefined();
            if (val.valid() < 100) return v8::Null();
            if (val.type() <= dvnci::TYPE_FLOAT) return v8::Number::New(val.type() != dvnci::TYPE_FLOAT ?
                    val.value<double>() : static_cast<double> (val.value<float>()));
            if (val.type() < dvnci::TYPE_DISCRET) return v8::Integer::New(static_cast<int32_t> (val.value<dvnci::num64 > ()));
            if (val.type() == dvnci::TYPE_DISCRET) return v8::Boolean::New(val.value<bool>());
            if (val.type() == dvnci::TYPE_TM) return v8::Date::New(dvnci::datetime_to_epoch_msc_utc(val.value<dvnci::datetime > ()));
            if (val.type() == dvnci::TYPE_TEXT) return v8::String::New(val.value<std::string > ().c_str());
            return v8::Number::New(val.value<double>());
        }

        class execute_expression_listener : public dvnci::expression_listener {
        public:

            execute_expression_listener(String expr, int type, v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::expression_listener(true), m_expression(expr), m_type(type),  m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            execute_expression_listener(String expr, int type) :
            dvnci::expression_listener(true), m_expression(expr), m_type(type), m_scriptcontext(0) {
            }

            virtual ~execute_expression_listener() {

                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::short_value& val) {


                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, m_type));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }


        protected:

            v8::Handle<v8::Value> conv(const dvnci::short_value& val, int code) {

                switch (code) {
                    case DVNCI_EXECUTE_EXPRESSION:
                    case DVNCI_EXECUTE_CHECK:
                    {

                        v8::HandleScope handle_scope;

                        v8::Handle<v8::Object> evnt = v8::Object::New();

                        evnt->Set(v8::String::New("expression"), v8::String::New(m_expression.utf8().data(), m_expression.length()));
                        evnt->Set(v8::String::New("value"), dvnci_shortvalue_conv_exec(val));
                        evnt->Set(v8::String::New("valid"), v8::Integer::New(val.valid()));
                        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc_utc(val.time())));
                        evnt->Set(v8::String::New("error"), v8::Integer::New(val.error()));


                        return handle_scope.Close(evnt);

                    }

                    case DVNCI_EXECUTE_ERROR:
                    {

                        v8::HandleScope handle_scope;

                        v8::Handle<v8::Object> evnt = v8::Object::New();
                        evnt->Set(v8::String::New("error"), v8::Integer::New(val.error()));
                        return handle_scope.Close(evnt);
                    }
                }

                return v8::Undefined();
            }

        private:
            String m_expression;
            int m_type;
            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;
        } ;

        class entety_expression_listener : public dvnci::entety_listener {
        public:

            entety_expression_listener(dvnci::nodetype enttp, dvnci::indx parentid, const std::string& filter , v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::entety_listener(enttp, parentid,  filter) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~entety_expression_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::iteminfo_map& val) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {
                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val, type()));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::iteminfo_map& val, dvnci::nodetype type) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                evnt->Set(v8::String::New("type"), v8::Integer::New(type));

                v8::Handle<v8::Array> array = v8::Array::New(val.size());

                int i = 0;

                for (dvnci::iteminfo_map::const_iterator it = val.begin(); it != val.end(); ++it) {

                    v8::HandleScope tmphandle_scope;

                    v8::Handle<v8::Object> tmp = v8::Object::New();

                    tmp->Set(v8::String::New("name"), v8::String::New(it->second.name().c_str(), it->second.name().size() ));
                    tmp->Set(v8::String::New("type"), v8::Integer::New(it->second.typeex()));
                    tmp->Set(v8::String::New("id"), v8::Integer::New(it->first));

                    array->Set(i++, tmphandle_scope.Close(tmp));
                }

                evnt->Set(v8::String::New("list"), array);


                return handle_scope.Close(evnt);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;

        class regitrate_expression_listener : public dvnci::registrate_listener {
        public:

            regitrate_expression_listener(const std::string& user, const std::string& password, v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::registrate_listener(dvnci::registrate_listener::REGIST, user,  password) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            regitrate_expression_listener(v8::Handle<v8::Context> context, ScriptExecutionContext* scriptcontext, v8::Handle<v8::Function> func) :
            dvnci::registrate_listener(dvnci::registrate_listener::UNREGIST) , m_context(context) ,  m_scriptcontext(scriptcontext) {
                m_function = v8::Persistent<v8::Function>::New(func);
            }

            virtual ~regitrate_expression_listener() {
                if (m_function.IsEmpty())
                    return;
                m_function.Dispose();
            }

            virtual void event(const dvnci::ns_error& val) {

                if (m_scriptcontext && !m_function.IsEmpty() && m_function->IsFunction()) {
                    V8Proxy* proxy = V8Proxy::retrieve(m_scriptcontext);
                    if (proxy) {

                        v8::HandleScope handleScope;
                        v8::Handle<v8::Context> v8Context = v8::Local<v8::Context>::New(m_context.get());
                        if (v8Context.IsEmpty())
                            return; // JS may not be enabled.
                        v8::Context::Scope scope(v8Context);

                        v8::Handle<v8::String> eventSymbol = V8HiddenPropertyName::event();
                        v8::Local<v8::Value> savedEvent = v8Context->Global()->GetHiddenValue(eventSymbol);

                        v8Context->Global()->SetHiddenValue(eventSymbol, conv(val));

                        proxy->callFunction(v8::Persistent<v8::Function>::Cast(m_function), v8Context->Global(), 0, 0);
                        if (savedEvent.IsEmpty())
                            v8Context->Global()->SetHiddenValue(eventSymbol, v8::Undefined());
                        else
                            v8Context->Global()->SetHiddenValue(eventSymbol, savedEvent);
                    }
                }
            }

        protected:

            v8::Handle<v8::Value> conv(const dvnci::ns_error& val) {


                v8::HandleScope handle_scope;

                v8::Handle<v8::Object> evnt = v8::Object::New();

                evnt->Set(v8::String::New("type"), v8::Integer::New(type()));

                evnt->Set(v8::String::New("error"), v8::Integer::New(val));

                evnt->Set(v8::String::New("success"), v8::Boolean::New(val == 0));

                evnt->Set(v8::String::New("user"), v8::String::New(user().c_str(), user().size()));

                return handle_scope.Close(evnt);
            }


        private:

            v8::Persistent<v8::Value> m_function;
            OwnHandle<v8::Context> m_context;
            ScriptExecutionContext* m_scriptcontext;

        } ;



    }

    v8::Handle<v8::Value> dvnciExecute(int code, const v8::Arguments& args) {

        int argumentCount = args.Length();

        int callbackid = 100000;

        initdvnciMain();

        String stringarg1 = "";
        String stringarg2 = "";


        switch (code) {
            case DVNCI_EXECUTE_EXPRESSION:
            {
                if (!argumentCount) return v8::Undefined();
                callbackid = 1;
                stringarg1 = toWebCoreString(args[0]) ;
                break;
            }
            case DVNCI_EXECUTE_CHECK:
            case DVNCI_EXECUTE_ERROR:
            {
                if (argumentCount < 2) return v8::Undefined();
                callbackid = 1;
                stringarg1 = toWebCoreString(args[0]) ;
                break;
            }
            case DVNCI_EXECUTE_USERLIST:
            {
                if (!argumentCount) return v8::Undefined();
                callbackid = 0;
                break;
            }
            case DVNCI_EXECUTE_REGIST:
            {
                if (argumentCount < 3) return v8::Undefined();
                callbackid = 0;
                stringarg1 = toWebCoreString(args[1]) ;
                stringarg2 = toWebCoreString(args[2]);
                break;
            }
            case DVNCI_EXECUTE_UNREGIST:
            {
                if (!argumentCount) return v8::Undefined();
                callbackid = 0;
                break;
            }
        };


        ScriptExecutionContext* scriptContext = 0;
        DOMWindow* imp = V8DOMWindow::toNative(args.Holder());
        v8::Handle<v8::Value> function = callbackid < argumentCount ? args[callbackid] : v8::Handle<v8::Value > ();

        bool hascallback = false;

        if ( imp  &&  (imp->frame()) && (callbackid < argumentCount) && (scriptContext = static_cast<ScriptExecutionContext*> (imp->document()))) {

            WTF::String functionString;
            if (!function->IsFunction()) {
                if (function->IsString())
                    functionString = toWebCoreString(function);
                else {
                    v8::Handle<v8::Value> v8String = function->ToString();
                    functionString = v8String.IsEmpty() ? "" : toWebCoreString(v8String);
                }
                hascallback = functionString.length();
            }
            else {
                hascallback = true;
            }
        }


        switch (code) {
            case DVNCI_EXECUTE_EXPRESSION:
            case DVNCI_EXECUTE_CHECK:
            case DVNCI_EXECUTE_ERROR:
            {
                dvnci::chrome_executor_ptr intf = getexecutordvnci();
                if (intf) {
                    std::string exprstr = dvnci::wstr_to_utf8(std::wstring(stringarg1.characters(), stringarg1.length()));
                    dvnci::expression_listener_ptr exrptr = hascallback ?
                            dvnci::expression_listener_ptr(new WebCore::DVNCI::execute_expression_listener (stringarg1, code, V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function))) :
                            dvnci::expression_listener_ptr(new WebCore::DVNCI::execute_expression_listener (stringarg1, code));
                    bool rslt = intf->regist_expr_listener(exprstr, exrptr, code != DVNCI_EXECUTE_EXPRESSION);
                    return v8::Boolean::New(rslt);
                }
            }

            case DVNCI_EXECUTE_USERLIST:
            {
                dvnci::chrome_executor_ptr intf = getexecutordvnci();
                if (intf && hascallback) {
                    dvnci::entety_listener_ptr  exrptr = dvnci::entety_listener_ptr(
                            new WebCore::DVNCI::entety_expression_listener (dvnci::NT_USER, dvnci::npos, "", V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));
                    bool rslt = intf->regist_entety_listener(exrptr);
                    return v8::Boolean::New(rslt);
                }
            }

            case DVNCI_EXECUTE_REGIST:
            {
                dvnci::chrome_executor_ptr intf = getexecutordvnci();
                if (intf && hascallback) {
                    dvnci::registrate_listener_ptr  exrptr = dvnci::registrate_listener_ptr(
                            new WebCore::DVNCI::regitrate_expression_listener(stringarg1.utf8().data(), stringarg2.utf8().data(), V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));
                    bool rslt = intf->regist_registrate_listener(exrptr);
                    return v8::Boolean::New(rslt);
                }
            }

            case DVNCI_EXECUTE_UNREGIST:
            {
                dvnci::chrome_executor_ptr intf = getexecutordvnci();
                if (intf && hascallback) {
                    dvnci::registrate_listener_ptr  exrptr = dvnci::registrate_listener_ptr(
                            new WebCore::DVNCI::regitrate_expression_listener (V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));
                    bool rslt = intf->regist_registrate_listener(exrptr);
                    return v8::Boolean::New(rslt);
                }
            }

        }



        return v8::Boolean::New(false);

    }

    v8::Handle<v8::Value> dvnciEntety(const v8::Arguments& args) {

        int argumentCount = args.Length();

        int callbackid = 0;

        initdvnciMain();

        dvnci::nodetype enttp = 0;

        dvnci::indx parentid = dvnci::npos;

        std::string filter = "";

        int type = 0;

        bool hascallback = false;

        if (argumentCount > 1) {

            enttp = static_cast<dvnci::nodetype> (toInt64(args[1]));

            if (argumentCount > 2)
                parentid = static_cast<dvnci::indx> (toInt64(args[2]));

            if (argumentCount > 3) {
                String fltr = toWebCoreString(args[3]);
                filter  = std::string(fltr.utf8().data());
            }

            ScriptExecutionContext* scriptContext = 0;
            DOMWindow* imp = V8DOMWindow::toNative(args.Holder());
            v8::Handle<v8::Value> function = callbackid < argumentCount ? args[callbackid] : v8::Handle<v8::Value > ();



            if ( imp  &&  (imp->frame()) && (callbackid < argumentCount) && (scriptContext = static_cast<ScriptExecutionContext*> (imp->document()))) {

                WTF::String functionString;
                if (!function->IsFunction()) {
                    if (function->IsString())
                        functionString = toWebCoreString(function);
                    else {
                        v8::Handle<v8::Value> v8String = function->ToString();
                        functionString = v8String.IsEmpty() ? "" : toWebCoreString(v8String);
                    }
                    hascallback = functionString.length();
                }
                else {
                    hascallback = true;
                }
            }

            if (enttp) {
                dvnci::chrome_executor_ptr intf = getexecutordvnci();
                if (intf && hascallback) {
                    dvnci::entety_listener_ptr  exrptr = dvnci::entety_listener_ptr(
                            new WebCore::DVNCI::entety_expression_listener (enttp, parentid, filter , V8Proxy::context(imp->frame()), scriptContext, v8::Handle<v8::Function>::Cast(function)));
                    bool rslt = intf->regist_entety_listener(exrptr);
                    return v8::Boolean::New(rslt);
                }
            }
        }

        return v8::Boolean::New(false);

    }





}

