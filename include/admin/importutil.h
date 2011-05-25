/* 
 * File:   importutil.h
 * Author: Serg
 *
 * Created on 2 Апрель 2010 г., 13:28
 */

#ifndef _ADMININTF_ADMIN_IMPORTUTIL_H
#define	_ADMININTF_ADMIN_IMPORTUTIL_H


#include <pugixml/pugixml.hpp>

#include <admin/adminintf.h>

namespace dvnci{
namespace admin{

const num8 esd_type_all=0; //result := 'X';
const num8 esd_type_x=8; //result := 'X';
const num8 esd_type_y=9; // result := 'Y';
const num8 esd_type_c=10; //result := 'C';
const num8 esd_type_s=12; //result := 'S';
const num8 esd_type_t=13; //result := 'T';
const num8 esd_type_gx=15; //result := 'GX';
const num8 esd_type_gy=16; //result := 'GX';
const num8 esd_type_v=17; //result := 'V';
const num8 esd_type_sp=22; //result := 'SP';
const num8 esd_type_b=27; //result := 'B';

const int TIPE_NS_IMPORT_XML=1;
const int TIPE_NS_IMPORT_CSV=2;
const int TIPE_NS_IMPORT_ESD=3;


num64 setesdnumcriteria(num16 min, num16 max, num8 type);

int gettipeimport(std::string filepath);


const std::string NS_XML_ROOT_IMPORT="root";
const std::string NS_XML_GROUPS_IMPORT="groups";
const std::string NS_XML_AGROUPS_IMPORT="agroups";
const std::string NS_XML_USERS_IMPORT="users";
const std::string NS_XML_TAGS_IMPORT_OLD="rtitems";
const std::string NS_XML_TAGS_IMPORT="tags";

const std::string NS_XML_GROUP_IMPORT="group";
const std::string NS_XML_AGROUP_IMPORT="agroup";
const std::string NS_XML_USER_IMPORT="user";
const std::string NS_XML_TAG_IMPORT_OLD="rtitem";
const std::string NS_XML_TAG_IMPORT="tag";


bool getimportdata(std::string filepath, base_data& base,int& loc, std::string group="", num64 mumcriteria=060000);
bool setexportdata(std::string filepath, base_data& base);

}
}

#endif	/* _IMPORTUTIL_H */

