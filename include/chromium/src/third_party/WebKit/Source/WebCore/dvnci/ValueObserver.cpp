/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "ValueObserver.h"


#include "DOMWindow.h"

#include <wtf/HashMap.h>
#include <wtf/UnusedParam.h>
#include <wtf/Threading.h>

#undef pow

#include <winsock2.h>
#include <custom/gui_executor.h>
#include <kernel/utils.h>
#include <kernel/constdef.h>
#include <kernel/systemutil.h>



namespace WebCore {


    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////

    static v8::Handle<v8::Value> dvnci_shortvalue_conv(const dvnci::short_value& val) {
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

    v8::Handle<v8::Value> toV8(const dvnci::short_value_vect& vect) {

        v8::HandleScope handle_scope;
        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::short_value_vect::const_iterator it = vect.begin(); it != vect.end(); ++it) {
            v8::Handle<v8::Array> point = v8::Array::New(2);
            point->Set(0, v8::Date::New(dvnci::datetime_to_epoch_msc(it->time())));
            point->Set(1, dvnci_shortvalue_conv(*it));
            array->Set(i++, point);
        }

        return handle_scope.Close(array);
    }

    v8::Handle<v8::Value> toV8(const dvnci::short_values_table& vect) {

        v8::HandleScope handle_scope;
        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::short_values_table::const_iterator it = vect.begin(); it != vect.end(); ++it) {
            v8::Handle<v8::Object> evnt = v8::Object::New();
            evnt->Set(v8::String::New("start"), v8::Boolean::New(it->first.second == 1));
            evnt->Set(v8::String::New("tag"), v8::String::New(it->first.first.c_str(), it->first.first.size()));
            evnt->Set(v8::String::New("id"), v8::Integer::New(i));
            if (it->first.second > 1)
                evnt->Set(v8::String::New("error"), v8::Boolean::New(true));
            else
                evnt->Set(v8::String::New("data"), toV8(it->second));
            array->Set(i++, evnt);
        }

        return handle_scope.Close(array);
    }

    v8::Handle<v8::Value> toV8(DVNTrendsEvent* impl) {

        if (!impl)
            return v8::Null();

        const dvnci::short_values_table& vect = impl->table().val;
        v8::HandleScope handle_scope;
        v8::Handle<v8::Value> array = toV8(vect);

        return handle_scope.Close(array);

    }

    class DVNTrendsEventImpl : public DVNTrendsEvent {
    public:

        DVNTrendsEventImpl(const AtomicString& eventType, const dvnci::trends_table& value, PassRefPtr<EventTarget> target) : DVNTrendsEvent(eventType, value,  target), tabl(value) {

        }

        virtual ~DVNTrendsEventImpl() {
        }

        virtual const dvnci::trends_table& table() {
            return tabl;
        }

    private:
        dvnci::trends_table tabl;
    } ;

    PassRefPtr<DVNTrendsEvent> DVNTrendsEvent::create(const AtomicString& eventType, const dvnci::trends_table& value, PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNTrendsEventImpl(eventType, value, target));
    }

    DVNTrendsEvent::DVNTrendsEvent(const AtomicString& eventType, const dvnci::trends_table& value, PassRefPtr<EventTarget> target) :
    Event(eventType, false, false) {
        setTarget(target);
    }



    ////////////////////////////////////////////////////
    ////////////////////////////////////////////////////
    
    v8::Handle<v8::Value> toV8(DVNExpressionEvent* impl) {
        if (!impl)
            return v8::Null();


        v8::HandleScope handle_scope;

        v8::Handle<v8::Object> evnt = v8::Object::New();
        
        evnt->Set(v8::String::New("expression"), v8::String::New(impl->expression().utf8().data(),impl->expression().length()));        
        evnt->Set(v8::String::New("value"), dvnci_shortvalue_conv(impl->value()));
        evnt->Set(v8::String::New("valid"), v8::Integer::New(impl->value().valid()));
        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(impl->value().time())));
        evnt->Set(v8::String::New("error"), v8::Integer::New(impl->value().error()));


        return handle_scope.Close(evnt);

    }    
    

    class DVNExpressionEventImpl : public DVNExpressionEvent {
    public:

        DVNExpressionEventImpl(const AtomicString& eventType, const dvnci::short_value& val, const String& expr, PassRefPtr<EventTarget> target) :
        DVNExpressionEvent(eventType, val, expr, target), value_(val) {
        }

        virtual ~DVNExpressionEventImpl() {
        }

        virtual dvnci::short_value value()  {
            return value_;
        }

    private:

        dvnci::short_value  value_;

    } ;

    PassRefPtr<DVNExpressionEvent> DVNExpressionEvent::create(const AtomicString& eventType, const dvnci::short_value& val, const String& expr,PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNExpressionEventImpl(eventType, val, expr, target));
    }

    DVNExpressionEvent::DVNExpressionEvent(const AtomicString& eventType, const dvnci::short_value& val, const String& expr, PassRefPtr<EventTarget> target) :
    Event(eventType, false, false), expression_(expr) {
        setTarget(target);
    }






}

