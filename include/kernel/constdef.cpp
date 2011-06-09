/* 
 * File:   constdef.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 25 Р¤РµРІСЂР°Р»СЊ 2010 Рі., 20:13
 */

#include <kernel/constdef.h>

/*
 * 
 */

namespace dvnci {

    std::string messagestrin_test(qumsgtype val) {
        switch (val) {

            case MSG_DVNCLOG: return "mLOG";
            case MSG_DVNCICOMMAND: return "mCommand";
            case MSG_DVNCIKVIT: return "mKvit";
            case MSG_DVNCINEWREF: return "mNewRef";
            case MSG_DVNCIREMREF: return "mRemRef";
            case MSG_DVNCIVALID: return "mValid";
            case MSG_DVNCDEBUG: return "mDEBUG";
            case MSG_DVNCTAGDELETE: return "mTag_remove";
            case MSG_DVNCTAGNEW: return "mTag_add";
            case MSG_DVNCTAGDELFROMGR: return "mTag_remove_to_Group";
            case MSG_DVNCTAGADDTOGR: return "mTag_add_to_Group";
            case MSG_DVNCTAGREPNAME: return "mTag_replace_name";
            case MSG_DVNCIGROUPDELETE: return "mGroup_remove";
            case MSG_DVNCIGROUPNEW: return "mGroup_add";
            case MSG_DVNCITAGREPORT: return "mTag_report";
            case MSG_DVNCIGROUPCHAPP: return "mGroup_replace_appid";
            case MSG_DVNCICONNSTRCH: return "mDataBase_replace_cs";
            case MSG_DVNCDBCONNECT: return "mDataBase_connect";
            case MSG_DVNCDBDISCONNECT: return "mDataBase_disconnect";}
        return "UndefMess";}



    tagtype oldtypetonew(tagtype val) {
        switch (val) {
            case  OLD_EVENT_TYPE_WITH_TIME_VAL: return EVENT_TYPE_WITHTIME;
            case  OLD_EVENT_TYPE_WITHTIME: return EVENT_TYPE_WITHTIME;
            case  OLD_EVENT_TYPE_ALARM: return EVENT_TYPE_WITHTIME;
            case  OLD_EVENT_TYPE_OSC: return EVENT_TYPE_OSC;
            case  OLD_TYPE_DISCRET: return TYPE_DISCRET;
            case  OLD_TYPE_NUM32: return TYPE_NUM32;
            case  OLD_TYPE_DOUBLE: return TYPE_DOUBLE;
            case  OLD_TYPE_UNUM32: return TYPE_UNUM32;
            case  OLD_TYPE_SMALL_INT: return TYPE_NUM8;
            case  OLD_TYPE_UNUM16: return TYPE_UNUM16;
            case  OLD_TYPE_NUM16: return TYPE_NUM16;
            case  OLD_TYPE_UNUM8: return TYPE_UNUM8;
            case  OLD_TYPE_SINGLE: return TYPE_FLOAT;
            case  OLD_TYPE_REAL48: return TYPE_FLOAT;
            case  OLD_TYPE_NUM8: return TYPE_NUM8;
            case  OLD_TYPE_TEXT: return TYPE_TEXT;
            case  OLD_TYPE_DT: return TYPE_TM;

            case  OLD_REPORTTYPE_YEAR: return REPORTTYPE_YEAR;
            case  OLD_REPORTTYPE_MIN: return REPORTTYPE_MIN;
            case  OLD_REPORTTYPE_HOUR: return REPORTTYPE_HOUR;
            case  OLD_REPORTTYPE_DEC: return REPORTTYPE_DEC;
            case  OLD_REPORTTYPE_DAY: return REPORTTYPE_DAY;
            case  OLD_REPORTTYPE_MONTH: return REPORTTYPE_MONTH;
            case  OLD_REPORTTYPE_10MIN: return REPORTTYPE_10MIN;
            case  OLD_REPORTTYPE_30MIN: return REPORTTYPE_30MIN;
            case  OLD_REPORTTYPE_QVART: return REPORTTYPE_QVART;
            case  OLD_REPORTTYPE_CUSTOM: return REPORTTYPE_CUSTOM;}
        return 0;}

    bool nodetp_canchild(nodetype tp) {
        if ((tp == NT_TAG) || (tp == NT_ATAG)) return false;
        switch (tp) {
            case NT_ROOT: return true;
            case NT_ROOT_SERVERS_NOTAVAIL: return true;
            case NT_ROOT_SERVERS_NOTAVAIL_R: return true;
            case NT_ROOT_SERVERS_AVAIL_R: return true;
            case NT_GROUP: return true;
            case NT_ROOT_SERVERS_AVAIL: return true;
            case NT_ROOT_GROUPS: return true;
            case NT_ROOT_AGROUPS: return true;
            case NT_ROOT_USERS: return true;
            case NT_ROOT_ACCESSRULES: return true;
            case NT_AGROUP: return true;
            case NT_MF_ROOT: return true;
            case NT_MF_HOME: return true;
            case NT_MF_REPLIST: return true;
            case NT_MF_TRENDLIST: return true;
            case NT_MF_MESSLIST: return true;
            case NT_MF_REPHEADER: return true;
            case NT_MF_TRENDHEADER: return true;
            case NT_MF_MESSHEADER: return true;
            case NT_MF_REPARR: return true;
            case NT_MF_TRENDARR:return true;
            case NT_MF_MESSARR: return true;
            case NT_UTIL_FINDER: return true;
            case NT_ROOT_SERVICES: return true;
            default: return false;}
        return false;}

    nodetype nodetp_child_by_parent(nodetype tp) {
        switch (tp) {
            case NT_ROOT: return 0;
            case NT_ROOT_SERVERS_NOTAVAIL: return 0;
            case NT_ROOT_SERVERS_AVAIL: return 0;
            case NT_ROOT_GROUPS: return NT_GROUP;
            case NT_ROOT_AGROUPS: return NT_AGROUP;
            case NT_ROOT_USERS: return NT_USER;
            case NT_ROOT_ACCESSRULES: return NT_ACCESSRULE;
            case NT_GROUP: return NT_TAG;
            case NT_AGROUP: return NT_ATAG;
            case NT_TAG: return 0;
            case NT_ROOT_SERVICES: return NT_SERVICE;
            case NT_UTILGROUP: return 0;
            case NT_UTIL_MAINTABLE: return 0;
            case NT_UTIL_ACCESSRULES: return 0;
            case NT_UTIL_CLIENTS: return 0;
            case NT_UTIL_GROUPTABLE: return 0;
            case NT_UTIL_DEBUG: return 0;
            case NT_UTIL_REGISTRY: return 0;
            case NT_UTIL_VALCH: return 0;
            case NT_UTIL_COMMAND: return 0;
            case NT_UTIL_JOURNAL: return 0;
            case NT_UTIL_ALARM: return 0;
            case NT_MF_ROOT: return 0;
            case NT_MF_HOME: return 0;
            case NT_MF_REPLIST: return NT_MF_REPHEADER;
            case NT_MF_TRENDLIST: return NT_MF_TRENDHEADER;
            case NT_MF_MESSLIST: return NT_MF_MESSHEADER;
            case NT_MF_REPHEADER: return NT_MF_REPARR;
            case NT_MF_TRENDHEADER: return NT_MF_TRENDARR;
            case NT_MF_MESSHEADER: return NT_MF_MESSARR;
            case NT_MF_REPARR: return NT_MF_UNIT;
            case NT_MF_UNIT: return 0;
            case NT_MF_TRENDARR: return NT_MF_TREND;
            case NT_MF_TREND: return 0;
            case NT_MF_MESSARR: return NT_MF_MESSAGE;
            case NT_MF_MESSAGE: return 0;
            default: return 0;}
        return 0;}

    nodetype nodetp_paren_by_child(nodetype tp) {
        switch (tp) {
            case NT_ROOT: return 0;
            case NT_ROOT_SERVERS_NOTAVAIL: return NT_ROOT;
            case NT_ROOT_SERVERS_AVAIL: return NT_ROOT;
            case NT_ROOT_GROUPS: return NT_ROOT;
            case NT_ROOT_AGROUPS: return NT_AGROUP;
            case NT_ROOT_USERS: return NT_ROOT;
            case NT_ROOT_ACCESSRULES: return NT_ROOT;
            case NT_GROUP: return NT_ROOT_GROUPS;
            case NT_AGROUP: return NT_ROOT_AGROUPS;
            case NT_TAG: return NT_GROUP;
            case NT_ATAG: return NT_AGROUP;
            case NT_USER: return NT_ROOT_USERS;
            case NT_ACCESSRULE: return NT_ROOT_ACCESSRULES;
            case NT_SERVICE: return NT_ROOT_SERVICES;
            case NT_UTILGROUP: return NT_ROOT;
            case NT_UTIL_MAINTABLE: return NT_UTILGROUP;
            case NT_UTIL_ACCESSRULES: return NT_UTILGROUP;
            case NT_UTIL_CLIENTS: return NT_UTILGROUP;
            case NT_UTIL_GROUPTABLE: return NT_UTILGROUP;
            case NT_UTIL_DEBUG: return NT_UTILGROUP;
            case NT_UTIL_REGISTRY: return NT_UTIL_REGISTRY;
            case NT_UTIL_VALCH: return NT_UTILGROUP;
            case NT_UTIL_COMMAND: return NT_UTILGROUP;
            case NT_UTIL_JOURNAL: return NT_UTILGROUP;
            case NT_UTIL_ALARM: return NT_UTILGROUP;
            case NT_REGISTRY: return NT_REGISTRY;

            case NT_MF_ROOT: return NT_ROOT;
            case NT_MF_HOME: return NT_MF_ROOT;
            case NT_MF_REPLIST: return NT_MF_ROOT;
            case NT_MF_TRENDLIST: return NT_MF_ROOT;
            case NT_MF_MESSLIST: return NT_MF_ROOT;
            case NT_MF_REPHEADER: return NT_MF_REPLIST;
            case NT_MF_TRENDHEADER: return NT_MF_TRENDLIST;
            case NT_MF_MESSHEADER: return NT_MF_MESSLIST;
            case NT_MF_REPARR: return NT_MF_REPHEADER;
            case NT_MF_UNIT: return NT_MF_REPARR;
            case NT_MF_TRENDARR: return NT_MF_TRENDHEADER;
            case NT_MF_TREND: return NT_MF_TRENDARR;
            case NT_MF_MESSARR: return NT_MF_MESSHEADER;
            case NT_MF_MESSAGE: return NT_MF_MESSARR;
            default: return 0;}
        return 0;}

    bool nodetp_is_meta(nodetype tp) {
        return ((tp >= NT_MF_ROOT) && (tp <= NT_MF_MESSAGE));}

    indx_set& operator>>(const num64_vect rs,  indx_set& ls){
        for (num64_vect::const_iterator it = rs.begin();it != rs.end();++it) {
			ls.insert(static_cast<indx>(*it));}
		return ls;}


    num64_vect& operator>>(const indx_set rs, num64_vect & ls){
        for (indx_set::const_iterator it = rs.begin();it != rs.end();++it) {
			ls.push_back(static_cast<num64>(*it));}
		return ls;}

	boost::mutex& global_out_mutex(){
		static boost::mutex mtx;
		return mtx;}

}







