/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCIBINDING_H
#define	DVNCIBINDING_H

#include "CSSMappedAttributeDeclaration.h"
#include "QualifiedName.h"
#include <wtf/RefPtr.h>
#include <v8.h>

#include "Observer.h"
#include "TableObserver.h"
#include "ValueObserver.h"




namespace WebCore {


    namespace DVNCI {
        
    
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////         
        
      
        class DVNDOMValueObserver : public RefCounted<DVNDOMValueObserver> {
        public:

            static WTF::RefPtr<DVNDOMValueObserver> DVNDOMValueObserver(Attribute * const el, const AtomicString& val);
            static WTF::RefPtr<DVNDOMValueObserver> DVNDOMValueObserver(Text * const txt, const String& val);
            
            virtual ~DVNDOMValueObserver() {
            };

            virtual void setvalue(const String& val) {
            }

            virtual bool valid() const {
                return false;
            }

            
        protected:
            
            DVNDOMValueObserver() {};
            
        };


        
        typedef WTF::RefPtr<DVNDOMValueObserver> impl_reftype;       

        // Observer        

        class Observer {

        public:
            
            Observer(Attribute * const attr, const AtomicString& val);
            
            Observer(Text * const txt, const String& val);

            Observer() : impl() {
            };
            
            bool valid() const;
            
            virtual ~Observer(){};
            
        private:
            
            impl_reftype impl;
            
        };


    }








}

#endif