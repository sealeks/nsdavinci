/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "TableObserver.h"


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
        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc_utc(impl.time)));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("kvit"), v8::Boolean::New(impl.kvit));
        evnt->Set(v8::String::New("tag"), v8::String::New(impl.tag.c_str(), impl.tag.size()));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.text.c_str(), impl.text.size()));
        evnt->Set(v8::String::New("value"), v8::String::New(impl.value.c_str(), impl.value.size()));

        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNAlarmsEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_alarms_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());
        
        int maxlevel = 0;
        int actuallevel = 0;
        bool allkvit = false;

        int i = 0;

        v8::Handle<v8::Object> evnt = v8::Object::New();

        for (dvnci::vect_alarms_row::const_iterator it = vect.begin(); it != vect.end(); ++it) {
            if (it->level > maxlevel)
                maxlevel = it->level;
            if (!it->kvit) {
                allkvit = true;
                if (it->level > actuallevel)
                    actuallevel = it->level;
            }
            array->Set(i++, toV8(*it));
        }

        evnt->Set(v8::String::New("table"), array);
        evnt->Set(v8::String::New("maxlevel"), v8::Integer::New(maxlevel));
        evnt->Set(v8::String::New("actuallevel"), v8::Integer::New(actuallevel));
        evnt->Set(v8::String::New("allkvit"), v8::Boolean::New(allkvit));

        return handle_scope.Close(array);

    }
    
    

    class DVNAlarmsEventImpl : public DVNAlarmsEvent {
    public:

        DVNAlarmsEventImpl(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) :
        DVNAlarmsEvent(eventType, value, target), tabl(value) {
        }

        virtual ~DVNAlarmsEventImpl() {
        }

        virtual const dvnci::alarms_table& table() {
            return tabl;
        }

    protected:

        dvnci::alarms_table tabl;

    } ;
    
    
    

    PassRefPtr<DVNAlarmsEvent> DVNAlarmsEvent::create(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) {
        return adoptRef(new DVNAlarmsEventImpl(eventType, value, target));
    }

    DVNAlarmsEvent::DVNAlarmsEvent(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) : Event(eventType, false, false) {
        setTarget(target);
    }

    
    
    //////////////////////////////////////////
    //////////////////////////////////////////
    

    v8::Handle<v8::Value> toV8(const dvnci::journal_row& impl) {

        v8::HandleScope handle_scope;

        v8::Handle<v8::Object> evnt = v8::Object::New();
        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc_utc(impl.time)));
        evnt->Set(v8::String::New("guid"), v8::Integer::New(impl.guid));
        evnt->Set(v8::String::New("type"), v8::Integer::New(impl.type));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("tag"), v8::String::New(impl.tag.c_str(), impl.tag.size()));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.text.c_str(), impl.text.size()));
        evnt->Set(v8::String::New("agroup"), v8::String::New(impl.agroup.c_str(), impl.agroup.size()));
        evnt->Set(v8::String::New("user"), v8::String::New(impl.user.c_str(), impl.user.size()));
        evnt->Set(v8::String::New("value"), v8::String::New(impl.value.c_str(), impl.value.size()));

        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNJournalEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_journal_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::vect_journal_row::const_iterator it = vect.begin(); it != vect.end(); ++it)
            array->Set(i++, toV8(*it));

        return handle_scope.Close(array);

    }
    
    

    class DVNJournalEventImpl : public DVNJournalEvent {
    public:

        DVNJournalEventImpl(const AtomicString& eventType, const dvnci::journal_table& value, PassRefPtr<EventTarget> target) :
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
        evnt->Set(v8::String::New("time"), v8::Date::New(dvnci::datetime_to_epoch_msc_utc(impl.time)));
        evnt->Set(v8::String::New("level"), v8::Integer::New(impl.level));
        evnt->Set(v8::String::New("app"), v8::Integer::New(impl.appid));
        evnt->Set(v8::String::New("message"), v8::String::New(impl.message.c_str(), impl.message.size()));


        return handle_scope.Close(evnt);
    }
    
    

    v8::Handle<v8::Value> toV8(DVNDebugEvent* impl) {
        
        if (!impl)
            return v8::Null();

        const dvnci::vect_debug_row& vect = impl->table().val;

        v8::HandleScope handle_scope;

        v8::Handle<v8::Array> array = v8::Array::New(vect.size());

        int i = 0;
        for (dvnci::vect_debug_row::const_iterator it = vect.begin(); it != vect.end(); ++it)
            array->Set(i++, toV8(*it));

        return handle_scope.Close(array);

    }
    
    

    class DVNDebugEventImpl : public DVNDebugEvent {
    public:

        DVNDebugEventImpl(const AtomicString& eventType, const dvnci::debug_table& value, PassRefPtr<EventTarget> target) :
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

