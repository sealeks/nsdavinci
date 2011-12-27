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


    v8::Handle<v8::Value> toV8(WebCore::DVNCI::trendrow* impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(2);

        if (array.IsEmpty())
            return v8::Handle<v8::Array > ();

        if (impl) {
            array->Set(0, v8::Date::New(impl->time));
            array->Set(1, v8::Number::New(impl->value));
        } else {
            array->Set(0, v8::Null());
            array->Set(1, v8::Null());
        }
        return handle_scope.Close(array);
    }
    
    
    
    
    

    v8::Handle<v8::Value> toV8(DVNTrendEvent* impl, v8::Handle<v8::Value> vl) {
        if (!impl)
            return v8::Null();

        if (!impl->table())
            return v8::Null();

        if (impl->table()->size() == 0)
            return v8::Null();

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(2);


        if (array.IsEmpty())
            return v8::Handle<v8::Array > ();

        v8::Handle<v8::Array> array2 = v8::Array::New(impl->table()->size());

        if (array2.IsEmpty())
            return v8::Handle<v8::Array > ();


        // Fill out the values
        for (int i = 0; i < impl->table()->size(); ++i) {
            array2->Set(i, toV8(impl->table()->get(i)));
        }

        array->Set(0, impl->target() ? vl : v8::Null());
        array->Set(1, array2);


        return handle_scope.Close(array);
    }


}

