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
        

        class AbstractObserver : public RefCounted<AbstractObserver> {
        public:

            AbstractObserver(Attribute * const el, const AtomicString& val) {
            };

            AbstractObserver(Text * const txt, const String& val) {
            }

            virtual void setvalue(const String& val) {
            }

            virtual bool valid() const {
                return false;
            }

            virtual ~AbstractObserver() {
            };
            
        };





        // AttributeObserver        

        class AttributeObserver : public AbstractObserver {
        public:
            AttributeObserver(Attribute * const el, const AtomicString& val);
            
            virtual void setvalue(const String& val);

            virtual bool valid() const {
                return false;
            }
            
            virtual ~AttributeObserver();

        protected:
            
            Attribute * const attribute;
            Element * const elem;
            String value;
            
        };



        // TextNodeObserver         

        class TextNodeObserver : public AbstractObserver {
        public:
            TextNodeObserver(Text * const txt, const String& val);
            
            virtual void setvalue(const String& val);

            virtual bool valid() const {
                return false;
            }
            
            virtual ~TextNodeObserver();

        protected:
            
            Text * const text;
            String value;
            
        };




        // Observer        

        class Observer {
            typedef WTF::RefPtr<AbstractObserver> impl_reftype;

        public:
            
            Observer(Attribute * const attr, const AtomicString& val);
            
            Observer(Text * const txt, const String& val);

            Observer() : impl() {
            };
            
            bool valid() const;
            
            virtual ~Observer();
            
        private:
            
            impl_reftype impl;
            
        };




    }

	//////////////////////////////////////////////////////////////////////////////////////////







}

#endif