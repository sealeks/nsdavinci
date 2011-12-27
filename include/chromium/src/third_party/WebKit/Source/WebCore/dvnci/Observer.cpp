/* 
 * File:   DVNCIExternal.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 24 Декабрь 2011 г., 18:49
 */

#include "config.h"
#include "Attribute.h"
#include "Observer.h"
#include "Element.h"
#include "Text.h"

#include "DOMWindow.h"

#include <wtf/HashMap.h>
#include <wtf/UnusedParam.h>
#include <wtf/Threading.h>






namespace WebCore {
    namespace DVNCI {

       bool isexpression(const AtomicString&){ return true;}
       AtomicString expression(const AtomicString&) { return "";};
       AtomicString defaultexpression(const AtomicString&) { return "";};

    }

}

