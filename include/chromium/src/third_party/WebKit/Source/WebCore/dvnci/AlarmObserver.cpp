/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "TrendObserver.h"


#include "DOMWindow.h"

#include <wtf/HashMap.h>
#include <wtf/UnusedParam.h>
#include <wtf/Threading.h>








namespace WebCore {

    v8::Handle<v8::Value> toV8(WebCore::DVNCI::alarmrow* impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(5);

        if (array.IsEmpty())
            return v8::Handle<v8::Array > ();

        if (impl) {
            array->Set(0, v8::Date::New(impl->time));
            array->Set(1, v8::Integer::New(impl->level));
            array->Set(2, v8::Integer::New(impl->kvit));
            array->Set(3, impl->tag.data() ? v8::String::New(impl->tag.data()) : v8::Null());
            array->Set(4, impl->text.data() ? v8::String::New(impl->text.data()) : v8::Null());
            array->Set(5, impl->value.data() ? v8::String::New(impl->value.data()) : v8::Null());
        } else {
            array->Set(0, v8::Null());
            array->Set(1, v8::Null());
            array->Set(2, v8::Null());
            array->Set(3, v8::Null());
            array->Set(4, v8::Null());
            array->Set(5, v8::Null());
        }

        // Return the value through Close.
        return handle_scope.Close(array);
    }

    v8::Handle<v8::Value> toV8(DVNAlarmEvent* impl) {
        if (!impl)
            return v8::Null();

        if (!impl->table())
            return v8::Null();

        if (impl->table()->size() == 0)
            return v8::Null();

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(impl->table()->size());

        // Return an empty result if there was an error creating the array.
        if (array.IsEmpty())
            return v8::Handle<v8::Array > ();

        // Fill out the values
        for (int i = 0; i < impl->table()->size(); ++i) {
            array->Set(i, toV8(impl->table()->get(i)));
        }


        // Return the value through Close.
        return handle_scope.Close(array);
    }



}

