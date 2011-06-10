/* 
 * File:   ProjectLoader.h
 * Author: Serg Alexeev sealeks@mail.ru Alexeev sealeks@mail.ru
 *
 * Created on 20 Март 2010 г., 20:15
 */

#ifndef _PROJECTLOADER_H
#define	_PROJECTLOADER_H


#include "winregwork.h"
#include "kernel/memfile.h"

namespace dvnci{
    tagsbase* loadMainBase(int& error);
};

#endif	/* _PROJECTLOADER_H */

