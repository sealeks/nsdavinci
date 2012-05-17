/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCITABLEOBSERVER_H
#define	DVNCITABLEOBSERVER_H


#include "QualifiedName.h"
#include <wtf/RefPtr.h>


#include "Event.h"
#include <v8.h>

namespace dvnci {
    class  alarms_table;
    class  journal_table;
    class  debug_table;
    }



namespace WebCore {
    
    
    ///////////////////////////////////////////
    ///////////////////////////////////////////    
    

    class DVNAlarmEvent : public Event {
    public:

        static PassRefPtr<DVNAlarmEvent> create(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target);

        virtual ~DVNAlarmEvent() {
        }

        virtual bool isDVNAlarmEvent() const {
            return true;
        }

        virtual const dvnci::alarms_table& table()  = 0;

    protected:

        DVNAlarmEvent(const AtomicString& eventType, const dvnci::alarms_table& value, PassRefPtr<EventTarget> target) ;

    } ;


    v8::Handle<v8::Value> toV8(DVNAlarmEvent* impl);
    
    
    
    
    
    ///////////////////////////////////////////
    ///////////////////////////////////////////

    class DVNJournalEvent : public Event {
    public:

        static PassRefPtr<DVNJournalEvent> create(const AtomicString& eventType, const dvnci::journal_table& value, PassRefPtr<EventTarget> target);

        virtual ~DVNJournalEvent() {
        }

        virtual bool isDVNJournalEvent() const {
            return true;
        }

        virtual const dvnci::journal_table& table()  = 0;

    protected:

        DVNJournalEvent(const AtomicString& eventType, const dvnci::journal_table& value, PassRefPtr<EventTarget> target) ;


    } ;


    v8::Handle<v8::Value> toV8(DVNJournalEvent* impl);   
    
    
    
    
    
    ///////////////////////////////////////////
    ///////////////////////////////////////////

    class DVNDebugEvent : public Event {
    public:

        static PassRefPtr<DVNDebugEvent> create(const AtomicString& eventType, const dvnci::debug_table& value, PassRefPtr<EventTarget> target);

        virtual ~DVNDebugEvent() {
        }

        virtual bool isDVNDebugEvent() const {
            return true;
        }

        virtual const dvnci::journal_table& table()  = 0;

    protected:

        DVNDebugEvent(const AtomicString& eventType, const dvnci::debug_table& value, PassRefPtr<EventTarget> target) ;


    } ;


    v8::Handle<v8::Value> toV8(DVNDebugEvent* impl);       


}

#endif