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
    static time_ptr tick = time_ptr( new dvnci::datetime());
    static dvnci::chrome_executor_ptr intf = getexecutordvnci();

    if (intf && ((tick->is_special()) ||
            (dvnci::abs(dvnci::millisecondsbetween(*tick, dvnci::now())) > TICK_DVNCI_DURATION))) {
        tick.swap(time_ptr( new dvnci::datetime(dvnci::now())));
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

                attribute_expression_listener(AttributeObserverImpl * const lsnr, const std::wstring& deflt = L"") : listener(lsnr), stdvl(), dfltvl(deflt) {
                }

                virtual ~attribute_expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    stdvl = val.valid() ? dvnci::utf8_to_wstr( val.value<std::string > ()) : dfltvl;
                    vl = String( stdvl.c_str(), stdvl.size());
                    listener->setvalue( vl );
                }

                void setdefault() {
                    stdvl =  dfltvl;
                    vl = String( stdvl.c_str(), stdvl.size());
                    listener->setvalue( vl );
                }

            private:
                AttributeObserverImpl * const listener;
                std::wstring stdvl;
                std::wstring dfltvl;
                String vl;
            } ;

        public:

            AttributeObserverImpl(Attribute * const attr, const AtomicString& val, const std::wstring& deflt = L"") : 
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

            Attribute * const              attribute;
            Element * const                elem;
            String                         value;
            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr     intf;
            std::string                    exprstr;
            AtomicString                   defaultvalue;
            
        } ;
        
        //////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////
        
        

        class TextNodeObserverImpl : public TextNodeObserver {

            class text_expression_listener : public dvnci::expression_listener {
            public:

                text_expression_listener(TextNodeObserverImpl * const lsnr, const std::wstring& deflt = L"") : listener(lsnr), stdvl(), vl() {
                }

                virtual ~text_expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    stdvl = dvnci::utf8_to_wstr(val.value<std::string > ());
                    vl = String( stdvl.c_str(), stdvl.size());
                    listener->setvalue( val.valid() ? vl : listener->deflt());
                }

            private:
                TextNodeObserverImpl * const listener;
                std::wstring stdvl;
                String vl;
            } ;

        public:

            TextNodeObserverImpl(Text * const txt, const String& val) : text(txt), value(val) , defaultvalue("") {
                registrate(txt, val);
            }

            virtual void setvalue(const String& val) {
                if (text) {
                    ExceptionCode ec;
                    text->replaceWholeText(val, ec);
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
                defaultvalue = String(tmpdef.c_str(), tmpdef.size());
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
            
            Text * const                   text;
            String                         value;
            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr     intf;
            std::string                    exprstr;
            String                         defaultvalue;
        } ;
        
        
        
        
                
        
        ////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////
        
        
        
        impl_reftype DVNDOMValueObserver::DVNDOMValueObserver(Attribute * const el, const AtomicString& val){
            return adoptRef(new AttributeObserverImpl(attr, val));
        }
        
        
        impl_reftype DVNDOMValueObserver::DVNDOMValueObserver(Text * const txt, const String& val){
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
                friend class AlarmsObserverImpl ;
            public:

                alarm_listener(AlarmsObserverImpl  * const lsnr) : listener(lsnr) {
                }

                virtual ~alarm_listener() {
                }

                virtual void event(const dvnci::vect_alarms_row& val) {
                    listener->notyfy(val);
                }

            private:
                AlarmsObserverImpl  * const listener;
            } ;

        public:

            AlarmsObserverImpl(EventTarget * const evtarget , const String& group_,  const String& agroup_) : AbstractEventObserver(evtarget), group(group_), agroup(agroup_)  {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::vect_alarms_row& val) {
                if (alarmlsnrptr  && (target())) {
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
                    alarmlsnrptr = dvnci::alarms_listener_ptr(new alarm_listener(this));
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

        class TrendsObserverImpl : public AbstractEventObserver {

            class trend_listener : public dvnci::trend_listener {
                friend class TrendsObserverImpl;
            public:

                trend_listener(TrendsObserverImpl * const lsnr, const dvnci::str_vect& tgs, dvnci::num64 histmilisec) : dvnci::trend_listener(tgs, histmilisec),  listener(lsnr) {
                }

                virtual ~trend_listener() {
                }

                virtual bool event(const dvnci::short_values_table& val) {
                    listener->notyfy(val);
                    return true;
                }

            private:
                TrendsObserverImpl * const listener;
            } ;

        public:

            TrendsObserverImpl(EventTarget * const evtarget , const Vector<String>& tags_, int period_ = 0) : AbstractEventObserver(evtarget), tags(tags_), period(period_) {
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
                    intf->regist_trend_listener( trendlsnrptr);
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
                    listener->notyfy( val);
                }


            private:
                ExpressionObserverImpl * const listener;
            } ;

        public:

            ExpressionObserverImpl(EventTarget * const evtarget , const String& tag_) : AbstractEventObserver(evtarget), tag(tag_) {
                initdvnciMain();
                registrate();
            }

            virtual void notyfy(const dvnci::short_value& val) {
                if (expressionptr && target()) {
                    value = val;
                    target()->dispatchExpressionEvent(value);
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

            dvnci::expression_listener_ptr   expressionptr;
            dvnci::chrome_executor_ptr      intf;
            String                                     tag;
            dvnci::short_value           value;
        } ;






        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createAlarmsObserver(EventTarget * const evtarget , const String& group, const String& agroup) {
            return adoptRef( new AlarmsObserverImpl(evtarget, group, agroup));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createJournalObserver(EventTarget * const evtarget ,  const String& filter) {
            return adoptRef( new AbstractEventObserver(evtarget));
        }
        
        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createDebugObserver(EventTarget * const evtarget ,  const String& filter) {
            return adoptRef( new ExpressionObserverImpl (evtarget, tag));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createTrendsObserver(EventTarget * const evtarget , const Vector<String>& tags, int period) {
            return adoptRef( new TrendsObserverImpl(evtarget, tags, period));
        }

        WTF::RefPtr<AbstractEventObserver> AbstractEventObserver::createExpressionObserver(EventTarget * const evtarget ,  const String& tag) {
            return adoptRef( new ExpressionObserverImpl (evtarget, tag));
        }

    }
}

