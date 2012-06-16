/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCIVALUEOBSERVER_H
#define	DVNCIVALUEOBSERVER_H


#include "QualifiedName.h"
#include <wtf/RefPtr.h>


#include "Event.h"
#include <v8.h>

namespace dvnci {
    struct short_value;
    class trends_table;
}

namespace WebCore {
    
    

    class DVNTrendsEvent : public Event {
    public:

        static PassRefPtr<DVNTrendsEvent> create(const AtomicString& eventType, const dvnci::trends_table& value, PassRefPtr<EventTarget> target);

        virtual ~DVNTrendsEvent() {
        }

        virtual bool isDVNTrendsEvent() const {
            return true;
        }

        virtual const dvnci::trends_table& table() = 0;

    protected:

        DVNTrendsEvent(const AtomicString& eventType, const dvnci::trends_table& value, PassRefPtr<EventTarget> target) ;
    } ;


    v8::Handle<v8::Value> toV8(DVNTrendsEvent* impl);



    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class DVNExpressionEvent : public Event {
    public:

        static PassRefPtr<DVNExpressionEvent> create(const AtomicString& eventType, const dvnci::short_value& val, const String& expr, PassRefPtr<EventTarget> target);

        virtual ~DVNExpressionEvent() {
        }

        virtual bool isDVNExpressionEvent() const {
            return true;
        }

        virtual dvnci::short_value value() = 0;
        
        String expression() const {
            return expression_;            
        }       

    protected:

        DVNExpressionEvent(const AtomicString& eventType, const dvnci::short_value& val, const String& expr, PassRefPtr<EventTarget> target);
        

    private: 
        
        String expression_;        

    } ;


    v8::Handle<v8::Value> toV8(DVNExpressionEvent* impl);


}

#endif