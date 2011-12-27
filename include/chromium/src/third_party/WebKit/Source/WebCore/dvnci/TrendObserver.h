/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCITRENDOBSERVER_H
#define	DVNCITRENDOBSERVER_H


#include "QualifiedName.h"
#include <wtf/RefPtr.h>


#include "Event.h"
#include <v8.h>



namespace WebCore {


    namespace DVNCI {



        struct trendrow {
            double value;
            double time;
        };

        class trendtable : public RefCounted<trendtable> {
        public:

            trendtable(int sz) : size_(sz) {
                table = new trendrow[size_];
            };

            virtual ~trendtable() {
                delete[] table;
            };

            int size() const {
                return size_;
            }

            trendrow* get(int i) {
                if ((i < 0) || (i >= size_)) {
                    return 0;
                }
                return &table[i];
            }
        protected:
            int size_;
            trendrow* table;
        };
        
        

    }
    
    

    class DVNTrendEvent : public Event {
    public:

        static PassRefPtr<DVNTrendEvent> create(const AtomicString& eventType, PassRefPtr<WebCore::DVNCI::trendtable> value, PassRefPtr<EventTarget> target) {
            return adoptRef(new DVNTrendEvent(eventType, value, target));
        }

        virtual ~DVNTrendEvent() {
        }

        virtual bool isDVNTrendEvent() const {
            return true;
        }

        WebCore::DVNCI::trendtable* table() {
            return tabl.get();
        }

    protected:

        DVNTrendEvent(const AtomicString& eventType, PassRefPtr<WebCore::DVNCI::trendtable> value, PassRefPtr<EventTarget> target) :
        Event(eventType, false, false), tabl(value) {
            setTarget(target);
        }

    private:

        PassRefPtr<WebCore::DVNCI::trendtable> tabl;
    };


    v8::Handle<v8::Value> toV8(WebCore::DVNCI::trendrow* impl);


    v8::Handle<v8::Value> toV8(DVNTrendEvent* impl, v8::Handle<v8::Value> vl);




}

#endif