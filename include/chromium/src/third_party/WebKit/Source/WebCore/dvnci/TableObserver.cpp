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


#include <winsock2.h>
#include <custom/gui_executor.h>





namespace WebCore {
    
    
    
    
    //////////////////////////////////////////
    //////////////////////////////////////////
    

    v8::Handle<v8::Value> toV8(const dvnci::alarms_row& impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Object> evnt = v8::Object::New();
        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(impl.time)));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("kvit"), v8::Boolean::New(impl.kvit));
        evnt->Set(v8::String::New("tag"), v8::String::New(impl.tag.c_str(), impl.tag.size()));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.text.c_str(), impl.text.size()));
        evnt->Set(v8::String::New("value"), v8::String::New(impl.value.c_str(), impl.value.size()));

        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNAlarmEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_alarms_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::vect_alarms_row::const_iterator it = vect.begin(); it != vect.end(); ++it)
            array->Set(i++, toV8(*it));

        return handle_scope.Close(array);

    }
    
    

    class DVNAlarmEventImpl : public DVNAlarmEvent {
    public:

        DVNAlarmEventImpl(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) :
        DVNAlarmEvent(eventType, value, target), tabl(value) {
        }

        virtual ~DVNAlarmEventImpl() {
        }

        virtual const dvnci::alarms_table& table() {
            return tabl;
        }

    protected:

        dvnci::alarms_table tabl;

    } ;
    
    
    

    PassRefPtr<DVNAlarmEvent> DVNAlarmEvent::create(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNAlarmEventImpl(eventType, value, target));
    }

    DVNAlarmEvent::DVNAlarmEvent(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) : Event(eventType, false, false) {
        setTarget(target);
    }

    
    
    //////////////////////////////////////////
    //////////////////////////////////////////
    

    v8::Handle<v8::Value> toV8(const dvnci::journal_row& impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Object> evnt = v8::Object::New();
        /*evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(impl.time)));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("kvit"), v8::Boolean::New(impl.kvit));
        evnt->Set(v8::String::New("tag"), v8::String::New(impl.tag.c_str(), impl.tag.size()));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.text.c_str(), impl.text.size()));
        evnt->Set(v8::String::New("value"), v8::String::New(impl.value.c_str(), impl.value.size()));*/

        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNJournalEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_alarms_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::vect_journal_row::const_iterator it = vect.begin(); it != vect.end(); ++it)
            array->Set(i++, toV8(*it));

        return handle_scope.Close(array);

    }
    
    

    class DVNJournalEventImpl : public DVNJournalEvent {
    public:

        DVNJournalEventImpl(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) :
        DVNJournalEvent(eventType, value, target), tabl(value) {
        }

        virtual ~DVNJournalEventImpl() {
        }

        virtual const dvnci::journal_table& table() {
            return tabl;
        }

    protected:

        dvnci::journal_table tabl;

    } ;
    
    
    

    PassRefPtr<DVNJournalEvent> DVNJournalEvent::create(const AtomicString& eventType, const dvnci::journal_table& value, PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNJournalEventImpl(eventType, value, target));
    }

    DVNJournalEvent::DVNJournalEvent(const AtomicString& eventType, const dvnci::journal_table& value, PassRefPtr<EventTarget> target) : Event(eventType, false, false) {
        setTarget(target);
    }    
    
    
    
    
    //////////////////////////////////////////
    //////////////////////////////////////////
    

    v8::Handle<v8::Value> toV8(const dvnci::debug_row& impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Object> evnt = v8::Object::New();
        /*evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc(impl.time)));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("kvit"), v8::Boolean::New(impl.kvit));
        evnt->Set(v8::String::New("tag"), v8::String::New(impl.tag.c_str(), impl.tag.size()));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.text.c_str(), impl.text.size()));
        evnt->Set(v8::String::New("value"), v8::String::New(impl.value.c_str(), impl.value.size()));*/

        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNDebugEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_alarms_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::vect_debug_row::const_iterator it = vect.begin(); it != vect.end(); ++it)
            array->Set(i++, toV8(*it));

        return handle_scope.Close(array);

    }
    
    

    class DVNDebugEventImpl : public DVNDebugEvent {
    public:

        DVNDebugEventImpl(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) :
        DVNDebugEvent(eventType, value, target), tabl(value) {
        }

        virtual ~DVNDebugEventImpl() {
        }

        virtual const dvnci::debug_table& table() {
            return tabl;
        }

    protected:

        dvnci::debug_table tabl;

    } ;
    
    
    

    PassRefPtr<DVNDebugEvent> DVNDebugEvent::create(const AtomicString& eventType, const dvnci::debug_table& value, PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNDebugEventImpl(eventType, value, target));
    }

    DVNDebugEvent::DVNDebugEvent(const AtomicString& eventType, const dvnci::debug_table& value, PassRefPtr<EventTarget> target) : Event(eventType, false, false) {
        setTarget(target);
    }    
    

}

