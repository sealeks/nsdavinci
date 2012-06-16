/* 
 * File:   V8DVNCIBinding.h
 * Author: sealeks@mail.ru
 *
 * Created on 25 Декабрь 2011 г., 14:36
 */

#ifndef V8DVNCIBINDING_H
#define	V8DVNCIBINDING_H

#include "DOMWindow.h"
#include "V8BindingState.h"

#include "Page.h"
#include "Chrome.h"
#include "EventTarget.h"

#include <winsock2.h>
#include <custom/gui_executor.h>
#include <kernel/utils.h>
#include <kernel/constdef.h>
#include <kernel/systemutil.h>

/*
 
 $$(expr [,handler])   ?!
 $$check(expr [,handler])  ?!
 $$error(expr [,handler])   ?!
 $$exit()
 $$writefile()
 $$filelist([ext]) !!!!
 $$fileexists((file|dir))  !!!!
 $$kill()
 $$editable()
 $$runtime()
 $$global()
 element.onalarm = handler  - delete
 element.ontrend = handler - delete
 addExpressionListener(handler, expr)
 removeExpressionListener(handler)
 addAlarmsListener(handler[, agroup, group])
 removeAlarmsListener(handler)
 addTrendsListener(handler, taglist, period)
 removTrendsListener(handler)
 
 
 */

dvnci::chrome_executor_ptr getexecutordvnci();
void shutdown_dvnci_interface();
bool BrowserDVNCI_isEditable();
bool BrowserDVNCI_isRuntime();

namespace WebCore {

    static v8::Handle<v8::Value> dvnci_value_conv(const dvnci::short_value& val) {
        if (val.nan()) return v8::Undefined();
        if (val.valid() < 100) return v8::Null();
        if (val.type() <= dvnci::TYPE_FLOAT) return v8::Number::New(val.type() != dvnci::TYPE_FLOAT ?
                val.value<double>() : static_cast<double> (val.value<float>()));
        if (val.type() < dvnci::TYPE_DISCRET) return v8::Integer::New(static_cast<int32_t> (val.value<dvnci::num64 > ()));
        if (val.type() == dvnci::TYPE_DISCRET) return v8::Boolean::New(val.value<bool>());
        if (val.type() == dvnci::TYPE_TM) return v8::Date::New(dvnci::datetime_to_epoch_msc(val.value<dvnci::datetime > ()));
        if (val.type() == dvnci::TYPE_TEXT) return v8::String::New(val.value<std::string > ().c_str());
        return v8::Number::New(val.value<double>());
    }

    
    static v8::Handle<v8::Value> dvnci_execCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_exec");
        if (args.Length() > 0) {
            dvnci::chrome_executor_ptr exec = getexecutordvnci();
            if (exec) {
                v8::Handle<v8::Value> arg = args[0];
                v8::String::Utf8Value value(arg);
                return dvnci_value_conv(exec->execute(std::string(*value, value.length())));
            }
        }
        return v8::Undefined();
    }

    
    static v8::Handle<v8::Value> dvnci_exprtestCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_test");
        if (args.Length() > 0) {
            dvnci::chrome_executor_ptr exec = getexecutordvnci();
            if (exec) {
                v8::Handle<v8::Value> arg = args[0];
                v8::String::Utf8Value value(arg);
                return dvnci_value_conv(exec->execute(std::string(*value, value.length()), true));
            }
        }
        return v8::Undefined();
    }

    
    static v8::Handle<v8::Value> dvnci_exprerrorCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_error");
        if (args.Length() > 0) {
            dvnci::chrome_executor_ptr exec = getexecutordvnci();
            if (exec) {
                v8::Handle<v8::Value> arg = args[0];
                v8::String::Utf8Value value(arg);
                dvnci::short_value val = exec->execute(std::string(*value, value.length()), true);
                return v8::Integer::New(val.error());
            }
        }
        return v8::Undefined();
    }

    
    static v8::Handle<v8::Value> dvnci_writefileCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_writefile");
        bool rslt = 0;
        if (args.Length() > 1) {
            v8::Handle<v8::Value> arg1 = args[0];
            v8::String::Utf8Value file(arg1);
            v8::Handle<v8::Value> arg2 = args[1];
            v8::String::Utf8Value data(arg2);
            rslt = dvnci::filestream::write(std::string(*file, file.length()), std::string(*data, data.length()));
        }

        return v8::Boolean::New(rslt);
    }

    
    static v8::Handle<v8::Value> dvnci_exitCallback(const v8::Arguments& args) {

        INC_STATS("DOM.DOMWindow.dvnci_exit");
        V8BindingState* state = V8BindingState::Only();

        DOMWindow* activeWindow = state->activeWindow();
        shutdown_dvnci_interface();
        if (activeWindow && activeWindow->frame() && activeWindow->frame()->page() && activeWindow->frame()->page()->chrome())
            activeWindow->frame()->page()->chrome()->exitBrowser();
        return v8::Undefined();
    }

    
    static v8::Handle<v8::Value> dvnci_shutdownCallback(const v8::Arguments& args) {

        INC_STATS("DOM.DOMWindow.dvnci_shutdown");

        shutdown_dvnci_interface();

        return v8::Undefined();
    }

    
    static v8::Handle<v8::Value> dvnci_isEditableCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_isEditable");
        return v8::Boolean::New(BrowserDVNCI_isEditable());
    }

    
    static v8::Handle<v8::Value> dvnci_isRuntimeCallback(const v8::Arguments& args) {

        INC_STATS("DOM.DOMWindow.dvnci_isRuntime");
        return v8::Boolean::New(BrowserDVNCI_isRuntime());
    }

    
    static v8::Handle<v8::Value> dvnci_GlobalObject(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.dvnci_globalobject");
        v8::HandleScope handle_scope;
        static v8::Persistent<v8::Object> global = v8::Persistent<v8::Object>::New(v8::Object::New());
        static v8::Handle<v8::Value> value = global->ToObject();
        return handle_scope.Close(value);
    }

    static v8::Handle<v8::Value> addExpressionEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.addExpressionEventListener()");
        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if ((impl) && (args.Length() > 1)) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener && (args[1]->IsString())) {
                String tag = toWebCoreString(args[1]);
                rslt = impl->addExpressionEventListener(tag, listener);
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> removeExpressionEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.removeExpressionEventListener()");
        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if (args.Length() > 0) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->removeExpressionEventListener(listener.get ());
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> addAlarmsEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.addAlarmsEventListener()");

        String agroup = args.Length() > 1 ? toWebCoreString(args[1]) : "";
        String group = args.Length() > 2 ? toWebCoreString(args[2]) : "";

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if ((impl) && (args.Length() > 0)) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->addAlarmsEventListener(listener, group, agroup);
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> removeAlarmsEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.removeAlarmsEventListener()");

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if (args.Length() > 0) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->removeAlarmsEventListener(listener.get ());
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> addJournalEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.addJournalEventListener()");
        String filter = args.Length() > 1 ? toWebCoreString(args[1]) : "";

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if ((impl) && (args.Length() > 0)) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->addJournalEventListener(listener, filter);
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> removeJournalEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.removeJournalEventListener()");

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if (args.Length() > 0) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->removeJournalEventListener(listener.get ());
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }
    
    static v8::Handle<v8::Value> addDebugEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.addDebugEventListener()");
        
        String filter = args.Length() > 1 ? toWebCoreString(args[1]) : "";

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if ((impl) && (args.Length() > 0)) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->addDebugEventListener(listener, filter);
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> removeDebugEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.removeDebugEventListener()");
        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if (args.Length() > 0) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->removeDebugEventListener(listener.get ());
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }    

    static v8::Handle<v8::Value> addTrendsEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.addTrendsEventListener()");

        bool rslt = false;

        int period = 0;
        if (args.Length() > 2) {
            bool ok = true;
            period = toInt32(args[2], ok);
            if (!ok)
                period = 0;
        }


        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));

        if ((impl) && (args.Length() > 1) && (args[1]->IsArray() || args[1]->IsString())) {
            Vector<String> tags;
            if (args[1]->IsString()) {
                tags.append(toWebCoreString(args[1]->ToString()));
            }
            else {
                v8::Handle<v8::Array> array = v8::Handle<v8::Array>::Cast(args[1]);
                for (uint32_t i = 0; i < array->Length(); i++) {
                    if (array->Get(i)->IsString())
                        tags.append(toWebCoreString(array->Get(i)->ToString()));
                }
            }

            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);

            if (listener && (!tags.isEmpty())) {
                rslt = impl->addTrendsEventListener(listener, tags, period);
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }

    static v8::Handle<v8::Value> removeTrendsEventListenerCallback(const v8::Arguments& args) {
        INC_STATS("DOM.DOMWindow.removeTrendsEventListener()");

        bool rslt = false;
        EventTarget* impl = reinterpret_cast<EventTarget*> (args.Holder()->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
        if (args.Length() > 0) {
            RefPtr<EventListener> listener = V8DOMWrapper::getEventListener(args[0], false, ListenerFindOrCreate);
            if (listener) {
                rslt = impl->removeTrendsEventListener(listener.get ());
                //createHiddenDependency(args.Holder(), args[1], eventListenerCacheIndex);
            }
        }
        return v8::Boolean::New(rslt);
    }



    static const BatchedCallback ext_DOMWindowCallbacks[] = {
        {"$$", dvnci_execCallback},
        {"$$writefile", dvnci_writefileCallback},
        {"$$check", dvnci_exprtestCallback},
        {"$$error", dvnci_exprerrorCallback},
        {"$$exit", dvnci_exitCallback},
        {"$$kill", dvnci_shutdownCallback},
        {"$$editable", dvnci_isEditableCallback},
        {"$$runtime", dvnci_isRuntimeCallback},
        {"$$global", dvnci_GlobalObject},
        {"addExpressionListener", addExpressionEventListenerCallback},
        {"removeExpressionListener", removeExpressionEventListenerCallback},
        {"addAlarmsListener", addAlarmsEventListenerCallback},
        {"removeAlarmsListener", removeAlarmsEventListenerCallback},
        {"addTrendsListener", addTrendsEventListenerCallback},
        {"removeTrendsListener", removeTrendsEventListenerCallback},
        {"addJournalListener", addJournalEventListenerCallback},
        {"removeJournalListener", removeJournalEventListenerCallback},
        {"addDebugListener", addDebugEventListenerCallback},
        {"removeDebugListener", removeDebugEventListenerCallback},        
        {"$$global", dvnci_GlobalObject},
    };


    static const BatchedCallback ext_ElementCallbacks[] = {
        {"addExpressionListener", addExpressionEventListenerCallback},
        {"removeExpressionListener", removeExpressionEventListenerCallback},
        {"addAlarmsListener", addAlarmsEventListenerCallback},
        {"removeAlarmsListener", removeAlarmsEventListenerCallback},
        {"addTrendsListener", addTrendsEventListenerCallback},
        {"removeTrendsListener", removeTrendsEventListenerCallback},
        {"addJournalListener", addJournalEventListenerCallback},
        {"removeJournalListener", removeJournalEventListenerCallback},
        {"addDebugListener", addDebugEventListenerCallback},
        {"removeDebugListener", removeDebugEventListenerCallback},
    };

    void dvnci_external_registrate(v8::Persistent<v8::FunctionTemplate> desc, const char *interfaceName, v8::Local<v8::ObjectTemplate> instance) {
        if (WTF::CString(interfaceName) == WTF::CString("DOMWindow")) {
            v8::Local<v8::Signature> defaultSignature = v8::Signature::New(desc);
            batchConfigureCallbacks(desc->PrototypeTemplate(),
                    defaultSignature,
                    static_cast<v8::PropertyAttribute> (v8::DontDelete),
                    ext_DOMWindowCallbacks, WTF_ARRAY_LENGTH(ext_DOMWindowCallbacks));
        }

        if (WTF::CString(interfaceName) == WTF::CString("Element")) {
            v8::Local<v8::Signature> defaultSignature = v8::Signature::New(desc);
            batchConfigureCallbacks(desc->PrototypeTemplate(),
                    defaultSignature,
                    static_cast<v8::PropertyAttribute> (v8::DontDelete),
                    ext_ElementCallbacks, WTF_ARRAY_LENGTH(ext_ElementCallbacks));
        }

    }


}

#endif	/* V8DVNCIBINDING_H */

