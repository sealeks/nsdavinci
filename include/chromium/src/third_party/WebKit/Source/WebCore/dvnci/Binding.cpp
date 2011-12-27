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
//#endif

dvnci::chrome_executor_ptr getexecutordvnci() {
    static dvnci::fspath basepath = dvnci::getlocalbasepath();
    static dvnci::tagsbase_ptr kintf = dvnci::krnl::factory::build(basepath, 0);
    static dvnci::chrome_executor_ptr DVNCI_INTERFACE = dvnci::chrome_executor_ptr(new dvnci::chrome_gui_executor(kintf));
    static boost::thread dvnth = boost::thread(DVNCI_INTERFACE);
    return DVNCI_INTERFACE;
}


void dvnciMain(void* cntxt){
    static dvnci::chrome_executor_ptr intf = getexecutordvnci();
    if (intf)
        intf->call();
    WTF::callOnMainThread(dvnciMain, 0);
    
}

void (*dvnciMainVar)(void*) = 0;

void initdvnciMain(){
	if (!dvnciMainVar){
	    dvnciMainVar = dvnciMain;
	    dvnciMainVar(0);}
}



namespace WebCore {
    namespace DVNCI {



        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 
        
        

        AttributeObserver::AttributeObserver
        (Attribute * const attr, const AtomicString& val) :
        AbstractObserver(attr, val), attribute(attr), elem(attr ? attr->element_ext() : 0), value(val) {
        }

        void AttributeObserver::setvalue(const String& val) {
        }

        AttributeObserver::~AttributeObserver() {
        }



        // 

        TextNodeObserver::TextNodeObserver
        (Text * const txt, const String& val) : AbstractObserver(txt, val), text(txt), value() {
        }

        void TextNodeObserver::setvalue(const String& val) {
        }

        TextNodeObserver::~TextNodeObserver() {
        }

        class AttributeObserverImpl : public AttributeObserver {

            class attribute_expression_listener : public dvnci::expression_listener {
            public:

                attribute_expression_listener(AttributeObserverImpl * const lsnr, const std::wstring& deflt = L"") : listener(lsnr), stdvl() {
                }

                virtual ~attribute_expression_listener() {
                }

                virtual void event(const dvnci::short_value& val) {
                    stdvl = dvnci::utf8_to_wstr(val.value<std::string > ());
                    vl = String( stdvl.c_str(), stdvl.size());
                    listener->setvalue( val.valid() ? vl : listener->deflt());
                }

            private:
                AttributeObserverImpl * const listener;
                std::wstring stdvl;
                String vl;
            };

        public:

            AttributeObserverImpl(Attribute * const attr, const AtomicString& val, const std::wstring& deflt = L"") : AttributeObserver(attr, val), defaultvalue("") {
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
            
            const String& deflt() const{
                return defaultvalue;
            }


        private:

            dvnci::expression_listener_ptr registrate(Element * const el, const AtomicString& val) {
                std::wstring tmpw = std::wstring(val.characters(), val.length());
                std::wstring tmpdef = dvnci::attribute_default_expression(tmpw);
                tmpw = dvnci::attribute_expression(tmpw);              
                defaultvalue = String(tmpdef.c_str(),tmpdef.size());
                setvalue(defaultvalue);
                if (tmpw.empty()) {
                    return dvnci::expression_listener_ptr();
                }
                intf = getexecutordvnci();
                if (intf) {
                    exprstr = dvnci::wstr_to_utf8(tmpw);
                    exrptr = dvnci::expression_listener_ptr(new attribute_expression_listener(this, tmpdef));
                    if (exrptr) {
                            intf->regist_expr_listener(exprstr, exrptr);}
                    return exrptr;
                }
                return dvnci::expression_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (exrptr)) {
                    intf->unregist_expr_listener(exrptr);
                }
            }

            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr intf;
            std::string exprstr;
            String defaultvalue;
        };
        
        

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
            };

        public:

            TextNodeObserverImpl(Text * const txt, const String& val) : TextNodeObserver(txt, val) , defaultvalue("") {
                registrate(txt, val);
            }

            virtual void setvalue(const String& val) {
                if (text) {
                    ExceptionCode ec;
                    text->replaceWholeText(val, ec);;
                }
            }

            virtual ~TextNodeObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return exrptr;
            }
            
                        
            const String& deflt() const{
                return defaultvalue;
            }



        private:

            dvnci::expression_listener_ptr registrate(Text * const txt, const String& val) {
                std::wstring tmpw = std::wstring(val.characters(), val.length());
                std::wstring tmpdef = dvnci::attribute_default_expression(tmpw);
                tmpw = dvnci::attribute_expression(tmpw);
                defaultvalue = String(tmpdef.c_str(),tmpdef.size());
                setvalue(defaultvalue);
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

            dvnci::expression_listener_ptr exrptr;
            dvnci::chrome_executor_ptr intf;
            std::string exprstr;
            String defaultvalue;
        };

        Observer::Observer(Attribute * const attr, const AtomicString& val) {
            if ((attr) && (val.find("#{") != WTF::notFound) && (val.find("}") != WTF::notFound)) {
                initdvnciMain();
                if (!valid()) {
                    impl = impl_reftype();
                    impl = adoptRef(new AttributeObserverImpl(attr, val));
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
                        impl = adoptRef(new TextNodeObserverImpl(txt, val));
                    }
                }
            }
        }

        bool Observer::valid() const {
            return impl ? impl->valid() : false;
        }

        Observer::~Observer() {
        }





        //////////////////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////////////////// 

        class AlarmObserverImpl : public AbstractAlarmObserver {

            class alarmtable_impl : public alarmtable {
            public:

                alarmtable_impl(const dvnci::vect_alarms_row& row) : alarmtable(row.size()) {
                    size_t i = 0;
                    for (dvnci::vect_alarms_row::const_iterator it = row.begin(); it != row.end(); ++it) {
                        alarmrow tmp = {dvnci::datetime_to_epoch_msc(it->time), it->level, it->kvit, it->tag.c_str(), it->text.c_str(), it->value.c_str(), it->type};
                        table[i++] = tmp;
                    }
                }
            };

            class alarm_listener : public dvnci::alarms_listener {
                friend class AlarmObserverImpl;
            public:

                alarm_listener(AlarmObserverImpl * const lsnr) : listener(lsnr) {
                }

                virtual ~alarm_listener() {
                }

                virtual void event(const dvnci::vect_alarms_row& val) {
                    listener->notyfy(val);
                }

            private:
                AlarmObserverImpl * const listener;
            };

        public:

            AlarmObserverImpl(DOMWindow * const domwin) : AbstractAlarmObserver(), win(domwin) {
                registrate();
            }

            virtual void notyfy(const dvnci::vect_alarms_row& val) {
                if (alarmlsnrptr  && win) {
                    win->dispatchAlarmEvent(adoptRef(new alarmtable_impl(value)));
                }
            }


            virtual ~AlarmObserverImpl() {
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

            dvnci::alarms_listener_ptr alarmlsnrptr;
            dvnci::chrome_executor_ptr intf;
            dvnci::vect_alarms_row value;
            WebCore::DOMWindow * const win;
        };
        
        

        AlarmObserver::AlarmObserver(DOMWindow * const domwin) {
            if (domwin){
                initdvnciMain();
                impl = adoptRef(new AlarmObserverImpl(domwin));}
            else
                impl = impl_reftype();
        }





        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////      

        class TrendObserverImpl : public AbstractTrendObserver {

            class trendtable_impl : public trendtable {
            public:

                trendtable_impl(const std::vector<dvnci::short_value>& val) : trendtable(val.size()) {
                    size_t i = 0;
                    for (std::vector<dvnci::short_value>::const_iterator it = val.begin(); it != val.end(); ++it) {
                        trendrow tmp = {it->value<double>(), dvnci::datetime_to_epoch_msc(it->time())};
                        table[i++] = tmp;
                    }
                }
            };

            class trend_listener : public dvnci::trend_listener {
                friend class TrendObserverImpl;
            public:

                trend_listener(TrendObserverImpl * const lsnr) : listener(lsnr) {
                }

                virtual ~trend_listener() {
                }

                virtual bool event(const std::vector<dvnci::short_value>& val) {
                    listener->notyfy(val);
                    return true;
                }

            private:
                TrendObserverImpl * const listener;
            };

        public:

            TrendObserverImpl(Element * const domelem) : AbstractTrendObserver(), elem(domelem) {
                registrate();
            }

            virtual void notyfy(const std::vector<dvnci::short_value>& val) {
                if (trendlsnrptr && elem) {
                    elem->dispatchTrendEvent(adoptRef(new trendtable_impl(val)));
                }
            }


            virtual ~TrendObserverImpl() {
                unregistrate();
            };

            virtual bool valid() const {
                return trendlsnrptr;
            }




        private:

            dvnci::trend_listener_ptr registrate() {
                intf = getexecutordvnci();
                if (elem && intf && (elem->hasAttribute(L"desc"))) {
                    const AtomicString& attr = elem->getAttribute(L"desc");
                    std::wstring tmpw = std::wstring(attr.characters(), attr.length());
                    trendlsnrptr = dvnci::trend_listener_ptr(new trend_listener(this));
                    return intf->regist_trend_listener(
                            dvnci::wstr_to_utf8(tmpw), trendlsnrptr) ? trendlsnrptr : dvnci::trend_listener_ptr();
                }
                return dvnci::trend_listener_ptr();
            }

            void unregistrate() {
                if ((intf) && (trendlsnrptr)) {
                    intf->unregist_trend_listener(trendlsnrptr);
                }
            }

            dvnci::trend_listener_ptr trendlsnrptr;
            dvnci::chrome_executor_ptr intf;
            std::vector<dvnci::short_value> value;
            WebCore::Element * const elem;
        };
        
        
        
        

        TrendObserver::TrendObserver(Element * const domelm) {
            if (domelm){
                initdvnciMain();
                impl = adoptRef(new TrendObserverImpl(domelm));}
            else
                impl = impl_reftype();
        }

    }
}

