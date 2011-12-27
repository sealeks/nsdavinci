/* 
 * File:   DVNCIExternal.h
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#ifndef DVNCIOBSERVER_H
#define	DVNCIOBSERVER_H

#include "CSSMappedAttributeDeclaration.h"
#include "QualifiedName.h"
#include <wtf/RefPtr.h>


#include "Event.h"
#include <v8.h>



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


   namespace DVNCI{


       bool isexpression(const AtomicString&);
       AtomicString expression(const AtomicString&);
       AtomicString defaultexpression(const AtomicString&);
       
        // AbstractObserver

   }



   
    
    
    

}

#endif