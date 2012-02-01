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

#include <winsock2.h>
#include <custom/gui_executor.h>
#include <kernel/utils.h>
#include <kernel/constdef.h>
#include <kernel/systemutil.h>

dvnci::chrome_executor_ptr getexecutordvnci();
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
                dvnci::short_value val = exec->execute(std::string(*value, value.length()));
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
        if (activeWindow && activeWindow->frame() && activeWindow->frame()->page() && activeWindow->frame()->page()->chrome())
            activeWindow->frame()->page()->chrome()->exitBrowser();
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
        static v8::Persistent<v8::Object> global = v8::Persistent<v8::Object>::New(v8::Object::New());
        return global->ToObject();
    }

    namespace DVNCI {

        static v8::Handle<v8::Value> onalarmeventAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info) {
            INC_STATS("DOM.DOMWindow.onalarm._get");
            v8::Handle<v8::Object> holder = info.Holder();
            DOMWindow* imp = reinterpret_cast<DOMWindow*> (holder->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
            if (!imp->document())
                return v8::Handle<v8::Value > ();
            return imp->onalarm() ? v8::Handle<v8::Value > (static_cast<V8AbstractEventListener*> (imp->onalarm())->getListenerObject(imp->scriptExecutionContext())) : v8::Handle<v8::Value > (v8::Null());
        }

        static void onalarmeventAttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info) {
            INC_STATS("DOM.DOMWindow.onalarm._set");
            v8::Handle<v8::Object> holder = info.Holder();
            DOMWindow* imp = reinterpret_cast<DOMWindow*> (holder->GetPointerFromInternalField(v8DOMWrapperObjectIndex));
            if (!imp->document())
                return;
            //return;
            transferHiddenDependency(info.Holder(), imp->onalarm(), value, v8DefaultWrapperInternalFieldCount + 0);
            imp->setOnalarm(V8DOMWrapper::getEventListener(value, true, ListenerFindOrCreate));
            imp->setalarmlistener(imp->onalarm());
            return;

        }

        static v8::Handle<v8::Value> ontrendAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info) {
            INC_STATS("DOM.Element.ontrend._get");
            Element* imp = V8Element::toNative(info.Holder());
            return imp->ontrend() ? v8::Handle<v8::Value > (static_cast<V8AbstractEventListener*> (imp->ontrend())->getListenerObject(imp->scriptExecutionContext())) : v8::Handle<v8::Value > (v8::Null());
        }

        static void ontrendAttrSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info) {
            INC_STATS("DOM.Element.ontrend._set");
            Element* imp = V8Element::toNative(info.Holder());
            imp->setOntrend(V8DOMWrapper::getEventListener(value, true, ListenerFindOrCreate));
            imp->settrendlistener(imp->ontrend());
            return;
        }
    }

    static const BatchedCallback ext_DOMWindowCallbacks[] = {
        {"dvnci_exec", dvnci_execCallback},
        {"dvnci_value", dvnci_execCallback},
        {"dvnci_writefile", dvnci_writefileCallback},
        {"dvnci_test", dvnci_exprtestCallback},
        {"dvnci_exit", dvnci_exitCallback},
        {"dvnci_iseditable", dvnci_isEditableCallback},
        {"dvnci_isruntime", dvnci_isRuntimeCallback},
		{"dvnci_globalobject", dvnci_GlobalObject},
    };

    static const BatchedAttribute ext_DOMWindowAttrs[] = {
        {"onalarm", DVNCI::onalarmeventAttrGetter, DVNCI::onalarmeventAttrSetter, 0, static_cast<v8::AccessControl> (v8::DEFAULT), static_cast<v8::PropertyAttribute> (v8::None), 1},

    };

    static const BatchedAttribute ext_ElementAttrs[] = {
        {"ontrend", DVNCI::ontrendAttrGetter, DVNCI::ontrendAttrSetter, 0, static_cast<v8::AccessControl> (v8::DEFAULT), static_cast<v8::PropertyAttribute> (v8::None | v8::DontEnum), 0 /* on instance */},
    };

    void dvnci_external_registrate(v8::Persistent<v8::FunctionTemplate> desc, const char *interfaceName, v8::Local<v8::ObjectTemplate> instance) {
        if (WTF::CString(interfaceName) == WTF::CString("DOMWindow")) {
            v8::Local<v8::Signature> defaultSignature = v8::Signature::New(desc);
            batchConfigureCallbacks(desc->PrototypeTemplate(),
                    defaultSignature,
                    static_cast<v8::PropertyAttribute> (v8::DontDelete),
                    ext_DOMWindowCallbacks, WTF_ARRAY_LENGTH(ext_DOMWindowCallbacks));
        }

        if (WTF::CString(interfaceName) == WTF::CString("DOMWindow")) {
            batchConfigureAttributes(instance, desc->PrototypeTemplate(),
                    ext_DOMWindowAttrs, WTF_ARRAY_LENGTH(ext_DOMWindowAttrs));
        }

        if (WTF::CString(interfaceName) == WTF::CString("Element")) {
            batchConfigureAttributes(instance, desc->PrototypeTemplate(),
                    ext_ElementAttrs, WTF_ARRAY_LENGTH(ext_ElementAttrs));
        }

    }


}

#endif	/* V8DVNCIBINDING_H */

