/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCIALARMOBSERVER_H
#define	DVNCIALARMOBSERVER_H


#include "QualifiedName.h"
#include <wtf/RefPtr.h>


#include "Event.h"
#include <v8.h>



namespace WebCore {


    namespace DVNCI {


        // AlarmEvent

        struct alarmrow {
            double time;
            int level;
            int kvit;
            WTF::CString tag;
            WTF::CString text;
            WTF::CString value;
            int type;
        };

        class alarmtable : public RefCounted<alarmtable> {
        public:

            alarmtable(int sz) : size_(sz) {
                table = new alarmrow[size_];
            };

            virtual ~alarmtable() {
                delete[] table;
            };

            int size() const {
                return size_;
            }

            alarmrow* get(int i) {
                if ((i < 0) || (i >= size_)) {
                    return 0;
                }
                return &table[i];
            }
        protected:
            int size_;
            alarmrow* table;
        };

        
        

    }
    
    
    

    class DVNAlarmEvent : public Event {
    public:

        static PassRefPtr<DVNAlarmEvent> create(const AtomicString& eventType, PassRefPtr<WebCore::DVNCI::alarmtable> value, PassRefPtr<EventTarget> target) {
            return adoptRef(new DVNAlarmEvent(eventType, value, target));
        }

        virtual ~DVNAlarmEvent() {
        }

        virtual bool isDVNAlarmEvent() const {
            return true;
        }

        WebCore::DVNCI::alarmtable* table() {
            return tabl.get();
        }

    protected:

        DVNAlarmEvent(const AtomicString& eventType, PassRefPtr<WebCore::DVNCI::alarmtable> value, PassRefPtr<EventTarget> target) : Event(eventType, false, false), tabl(value) {
            setTarget(target);
        }

    private:

        PassRefPtr<WebCore::DVNCI::alarmtable> tabl;
    };



    v8::Handle<v8::Value> toV8(WebCore::DVNCI::alarmrow* impl);


    v8::Handle<v8::Value> toV8(DVNAlarmEvent* impl);


}

#endif