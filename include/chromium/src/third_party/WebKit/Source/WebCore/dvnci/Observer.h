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



   namespace DVNCI{


       bool isexpression(const AtomicString&);
       AtomicString expression(const AtomicString&);
       AtomicString defaultexpression(const AtomicString&);
       
        // DVNDOMValueObserver

   }



   
    
    
    

}

#endif