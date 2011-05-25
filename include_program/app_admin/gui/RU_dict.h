/* 
 * File:   RU_dict.h
 * Author: Serg
 *
 * Created on 20 Июнь 2010 г., 3:46
 */

#ifndef _RU_DICT_H
#define	_RU_DICT_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <QString>

namespace dvnci {
    namespace admin {

        typedef std::pair<QString, QString> wstringtranslate_pair;
        typedef std::map<QString, QString, std::less<QString>, std::allocator<wstringtranslate_pair > > wstringtranslate_map;

        void load_dictionary(wstringtranslate_map& map_);

    }}
#endif	/* _RU_DICT_H */

