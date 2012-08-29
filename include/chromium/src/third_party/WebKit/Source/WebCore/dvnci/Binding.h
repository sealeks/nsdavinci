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


#include "TableObserver.h"
#include "ValueObserver.h"




namespace WebCore {

    class Attr;
    class CSSStyleDeclaration;
    class Element;
    class NamedNodeMap;
    class Text;
    class Attribute;
    class DOMWindow;
    class Event;

    class ClientRect;
    class ClientRectList;
    class DOMStringMap;
    class DOMTokenList;
    class ElementRareData;
    class IntSize;
    class ShadowRoot;
    class WebKitAnimationList;



    namespace DVNCI {


        //////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////         

        class DVNDOMValueObserver : public RefCounted<DVNDOMValueObserver> {
        public:

            static WTF::RefPtr<DVNDOMValueObserver> create(Attribute * const el, const AtomicString& val);
            static WTF::RefPtr<DVNDOMValueObserver> create(Text * const txt, const String& val);

            virtual ~DVNDOMValueObserver() {
            }

            virtual void setvalue(const String& val) {
            }

            virtual bool valid() const {
                return false;
            }


        protected:

            DVNDOMValueObserver() {
            }

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

            virtual ~Observer() {
            };

        private:

            impl_reftype impl;

        };
    }


	const int DVNCI_EXECUTE_EXPRESSION = 0;
	const int DVNCI_EXECUTE_CHECK = 1;
	const int DVNCI_EXECUTE_ERROR = 2;
	const int DVNCI_EXECUTE_USERLIST =3;
	const int DVNCI_EXECUTE_REGIST =4;
	const int DVNCI_EXECUTE_UNREGIST = 5;

    v8::Handle<v8::Value> dvnciExecute(int code, const v8::Arguments& args);

    v8::Handle<v8::Value> dvnciEntety(const v8::Arguments& args);
    
    v8::Handle<v8::Value> dvnciSCDBConnection(const v8::Arguments& args);


}

#endif