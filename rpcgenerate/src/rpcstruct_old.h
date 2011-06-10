/*
 * Automatically generated from rpcstruct.rpc
 */

#ifndef _RPCSTRUCT_RPC_
#define _RPCSTRUCT_RPC_

#include <string>
#include <vector>
#include "kernel/constdef.h"
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/basic_binary_oprimitive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>

struct error_outside;
struct req_entitysigs;
struct resp_entitysigs;
struct entitysig_data;
struct error_entity;
struct req_removeentity;
struct resp_removeentity;
struct req_addentity;
struct resp_addentity;
struct req_tags;
struct req_sendtags;
struct resp_tags;
struct resp_sendtags;
struct tag_data;
struct req_groups;
struct req_sendgroups;
struct resp_groups;
struct resp_sendgroups;
struct group_data;
struct req_agroups;
struct req_sendagroups;
struct resp_agroups;
struct resp_sendagroups;
struct agroup_data;
struct req_users;
struct req_sendusers;
struct resp_users;
struct resp_sendusers;
struct user_data;
struct req_metas;
struct req_sendmetas;
struct resp_metas;
struct resp_sendmetas;
struct meta_data;
struct req_regs;
struct resp_regs;
struct reg_data;
struct req_viewcount;
struct resp_viewcount;
struct req_views;
struct resp_views;
struct view_data;
struct config_data;
struct req_config;
struct req_sendconfig;
struct resp_config;
struct resp_sendconfig;
struct req_basedata;
struct resp_basedata;
struct req_setbasedata;
struct resp_setbasedata;
struct base_data;
struct req_adminoperation;
struct resp_adminoperation;
struct req_autorization;
struct resp_autorization;
struct req_services;
struct req_sendservices;
struct resp_services;
struct resp_sendservices;
struct service_data;

const short RPC_OPERATION_ERROR_OUTSIDE=0x10;
const short RPC_OPERATION_REQ_ENTITYSIGS=0x11;
const short RPC_OPERATION_RESP_ENTITYSIGS=0x12;
const short RPC_OPERATION_ENTITYSIG_DATA=0x13;
const short RPC_OPERATION_ERROR_ENTITY=0x14;
const short RPC_OPERATION_REQ_REMOVEENTITY=0x15;
const short RPC_OPERATION_RESP_REMOVEENTITY=0x16;
const short RPC_OPERATION_REQ_ADDENTITY=0x17;
const short RPC_OPERATION_RESP_ADDENTITY=0x18;
const short RPC_OPERATION_REQ_TAGS=0x19;
const short RPC_OPERATION_REQ_SENDTAGS=0x1A;
const short RPC_OPERATION_RESP_TAGS=0x1B;
const short RPC_OPERATION_RESP_SENDTAGS=0x1C;
const short RPC_OPERATION_TAG_DATA=0x1D;
const short RPC_OPERATION_REQ_GROUPS=0x1E;
const short RPC_OPERATION_REQ_SENDGROUPS=0x1F;
const short RPC_OPERATION_RESP_GROUPS=0x20;
const short RPC_OPERATION_RESP_SENDGROUPS=0x21;
const short RPC_OPERATION_GROUP_DATA=0x22;
const short RPC_OPERATION_REQ_AGROUPS=0x23;
const short RPC_OPERATION_REQ_SENDAGROUPS=0x24;
const short RPC_OPERATION_RESP_AGROUPS=0x25;
const short RPC_OPERATION_RESP_SENDAGROUPS=0x26;
const short RPC_OPERATION_AGROUP_DATA=0x27;
const short RPC_OPERATION_REQ_USERS=0x28;
const short RPC_OPERATION_REQ_SENDUSERS=0x29;
const short RPC_OPERATION_RESP_USERS=0x2A;
const short RPC_OPERATION_RESP_SENDUSERS=0x2B;
const short RPC_OPERATION_USER_DATA=0x2C;
const short RPC_OPERATION_REQ_METAS=0x2D;
const short RPC_OPERATION_REQ_SENDMETAS=0x2E;
const short RPC_OPERATION_RESP_METAS=0x2F;
const short RPC_OPERATION_RESP_SENDMETAS=0x30;
const short RPC_OPERATION_META_DATA=0x31;
const short RPC_OPERATION_REQ_REGS=0x32;
const short RPC_OPERATION_RESP_REGS=0x33;
const short RPC_OPERATION_REG_DATA=0x34;
const short RPC_OPERATION_REQ_VIEWCOUNT=0x35;
const short RPC_OPERATION_RESP_VIEWCOUNT=0x36;
const short RPC_OPERATION_REQ_VIEWS=0x37;
const short RPC_OPERATION_RESP_VIEWS=0x38;
const short RPC_OPERATION_VIEW_DATA=0x39;
const short RPC_OPERATION_CONFIG_DATA=0x3A;
const short RPC_OPERATION_REQ_CONFIG=0x3B;
const short RPC_OPERATION_REQ_SENDCONFIG=0x3C;
const short RPC_OPERATION_RESP_CONFIG=0x3D;
const short RPC_OPERATION_RESP_SENDCONFIG=0x3E;
const short RPC_OPERATION_REQ_BASEDATA=0x3F;
const short RPC_OPERATION_RESP_BASEDATA=0x40;
const short RPC_OPERATION_REQ_SETBASEDATA=0x41;
const short RPC_OPERATION_RESP_SETBASEDATA=0x42;
const short RPC_OPERATION_BASE_DATA=0x43;
const short RPC_OPERATION_REQ_ADMINOPERATION=0x44;
const short RPC_OPERATION_RESP_ADMINOPERATION=0x45;
const short RPC_OPERATION_REQ_AUTORIZATION=0x46;
const short RPC_OPERATION_RESP_AUTORIZATION=0x47;
const short RPC_OPERATION_REQ_SERVICES=0x48;
const short RPC_OPERATION_REQ_SENDSERVICES=0x49;
const short RPC_OPERATION_RESP_SERVICES=0x4A;
const short RPC_OPERATION_RESP_SENDSERVICES=0x4B;
const short RPC_OPERATION_SERVICE_DATA=0x4C;

typedef std::vector<error_outside > vect_error_outside;
typedef std::vector<req_entitysigs > vect_req_entitysigs;
typedef std::vector<resp_entitysigs > vect_resp_entitysigs;
typedef std::vector<entitysig_data > vect_entitysig_data;
typedef std::vector<error_entity > vect_error_entity;
typedef std::vector<req_removeentity > vect_req_removeentity;
typedef std::vector<resp_removeentity > vect_resp_removeentity;
typedef std::vector<req_addentity > vect_req_addentity;
typedef std::vector<resp_addentity > vect_resp_addentity;
typedef std::vector<req_tags > vect_req_tags;
typedef std::vector<req_sendtags > vect_req_sendtags;
typedef std::vector<resp_tags > vect_resp_tags;
typedef std::vector<resp_sendtags > vect_resp_sendtags;
typedef std::vector<tag_data > vect_tag_data;
typedef std::vector<req_groups > vect_req_groups;
typedef std::vector<req_sendgroups > vect_req_sendgroups;
typedef std::vector<resp_groups > vect_resp_groups;
typedef std::vector<resp_sendgroups > vect_resp_sendgroups;
typedef std::vector<group_data > vect_group_data;
typedef std::vector<req_agroups > vect_req_agroups;
typedef std::vector<req_sendagroups > vect_req_sendagroups;
typedef std::vector<resp_agroups > vect_resp_agroups;
typedef std::vector<resp_sendagroups > vect_resp_sendagroups;
typedef std::vector<agroup_data > vect_agroup_data;
typedef std::vector<req_users > vect_req_users;
typedef std::vector<req_sendusers > vect_req_sendusers;
typedef std::vector<resp_users > vect_resp_users;
typedef std::vector<resp_sendusers > vect_resp_sendusers;
typedef std::vector<user_data > vect_user_data;
typedef std::vector<req_metas > vect_req_metas;
typedef std::vector<req_sendmetas > vect_req_sendmetas;
typedef std::vector<resp_metas > vect_resp_metas;
typedef std::vector<resp_sendmetas > vect_resp_sendmetas;
typedef std::vector<meta_data > vect_meta_data;
typedef std::vector<req_regs > vect_req_regs;
typedef std::vector<resp_regs > vect_resp_regs;
typedef std::vector<reg_data > vect_reg_data;
typedef std::vector<req_viewcount > vect_req_viewcount;
typedef std::vector<resp_viewcount > vect_resp_viewcount;
typedef std::vector<req_views > vect_req_views;
typedef std::vector<resp_views > vect_resp_views;
typedef std::vector<view_data > vect_view_data;
typedef std::vector<config_data > vect_config_data;
typedef std::vector<req_config > vect_req_config;
typedef std::vector<req_sendconfig > vect_req_sendconfig;
typedef std::vector<resp_config > vect_resp_config;
typedef std::vector<resp_sendconfig > vect_resp_sendconfig;
typedef std::vector<req_basedata > vect_req_basedata;
typedef std::vector<resp_basedata > vect_resp_basedata;
typedef std::vector<req_setbasedata > vect_req_setbasedata;
typedef std::vector<resp_setbasedata > vect_resp_setbasedata;
typedef std::vector<base_data > vect_base_data;
typedef std::vector<req_adminoperation > vect_req_adminoperation;
typedef std::vector<resp_adminoperation > vect_resp_adminoperation;
typedef std::vector<req_autorization > vect_req_autorization;
typedef std::vector<resp_autorization > vect_resp_autorization;
typedef std::vector<req_services > vect_req_services;
typedef std::vector<req_sendservices > vect_req_sendservices;
typedef std::vector<resp_services > vect_resp_services;
typedef std::vector<resp_sendservices > vect_resp_sendservices;
typedef std::vector<service_data > vect_service_data;

struct error_outside {
_num64  error;
};

struct req_entitysigs {
_num64  ver;
_num64  tpitem;
_num64  parentid;
std::string  strcriteria;
_num64  numcriteria;
};

struct resp_entitysigs {
_num64  tpreq;
_num64  err;
vect_entitysig_data  sigs;
};

struct entitysig_data {
_num64  key;
std::string  name;
_num64  tpitem;
};

struct error_entity {
_num64  code;
_num64  key;
std::string  str;
};

struct req_removeentity {
_num64  ver;
_num64  tpitem;
std::vector<_num64 >  keys;
};

struct resp_removeentity {
_num64  err;
_num64  ver;
vect_error_entity  error;
};

struct req_addentity {
_num64  ver;
_num64  tpitem;
_num64  parentkey;
std::string  newname;
_num64  numcriteria;
};

struct resp_addentity {
_num64  err;
_num64  ver;
entitysig_data  sig;
vect_error_entity  error;
};

struct req_tags {
_num64  ver;
std::vector<_num64 >  keys;
};

struct req_sendtags {
_num64  ver;
vect_tag_data  tags;
};

struct resp_tags {
_num64  err;
vect_tag_data  tags;
};

struct resp_sendtags {
_num64  err;
vect_tag_data  tags;
vect_error_entity  error;
};

struct tag_data {
_num64  key;
char  tginfo[360];
std::string  name;
std::string  comment;
std::string  bind;
std::string  ue;
std::string  onmsg;
std::string  offmsg;
std::string  almsg;
std::string  group;
_num64  changeset;
};

struct req_groups {
_num64  ver;
std::vector<_num64 >  keys;
};

struct req_sendgroups {
_num64  ver;
vect_group_data  groups;
};

struct resp_groups {
_num64  err;
vect_group_data  groups;
};

struct resp_sendgroups {
_num64  err;
vect_group_data  groups;
vect_error_entity  error;
};

struct group_data {
_num64  key;
char  groupinfo[708];
std::string  name;
_num64  changeset;
};

struct req_agroups {
_num64  ver;
std::vector<_num64 >  keys;
};

struct req_sendagroups {
_num64  ver;
vect_agroup_data  agroups;
};

struct resp_agroups {
_num64  err;
vect_agroup_data  agroups;
};

struct resp_sendagroups {
_num64  err;
vect_agroup_data  agroups;
vect_error_entity  error;
};

struct agroup_data {
_num64  key;
char  agroupinfo[276];
std::string  name;
_num64  changeset;
};

struct req_users {
_num64  ver;
std::vector<_num64 >  keys;
};

struct req_sendusers {
_num64  ver;
vect_user_data  users;
};

struct resp_users {
_num64  err;
vect_user_data  users;
};

struct resp_sendusers {
_num64  err;
vect_user_data  users;
vect_error_entity  error;
};

struct user_data {
_num64  key;
std::string  name;
std::string  password;
_num64  level;
_num64  changeset;
};

struct req_metas {
_num64  ver;
_num64  meta_type;
std::vector<_num64 >  keys;
};

struct req_sendmetas {
_num64  ver;
vect_meta_data  metas;
};

struct resp_metas {
_num64  err;
vect_meta_data  metas;
};

struct resp_sendmetas {
_num64  err;
vect_meta_data  metas;
vect_error_entity  error;
};

struct meta_data {
_num64  key;
_num64  meta_type;
std::string  str_data[19];
_num64  changeset;
};

struct req_regs {
_num64  ver;
std::vector<_num64 >  keys;
};

struct resp_regs {
_num64  err;
vect_reg_data  regs;
};

struct reg_data {
_num64  key;
std::string  name;
_num64  appid;
_num64  hndl;
_num64  evst;
};

struct req_viewcount {
_num64  ver;
_num64  type;
_num64  numcriteria;
std::string  strcriteria;
};

struct resp_viewcount {
_num64  err;
_num64  type;
_num64  globalnum;
_num64  count;
};

struct req_views {
_num64  ver;
_num64  type;
std::vector<_num64 >  nums;
};

struct resp_views {
_num64  err;
_num64  type;
vect_view_data  views;
};

struct view_data {
_num64  num;
_num64  time;
_num64  tgid;
_num64  lev_type;
_num64  exec_iskvit;
_num64  isoff;
_num64  val_before;
_num64  val_set;
_num64  unu1;
_num64  unu2;
std::string  mess_host;
std::string  app_user;
std::string  unu3;
};

struct config_data {
std::string  str_data[19];
_num64  changeset;
};

struct req_config {
_num64  ver;
};

struct req_sendconfig {
_num64  ver;
config_data  config;
};

struct resp_config {
_num64  err;
config_data  config;
};

struct resp_sendconfig {
_num64  err;
config_data  config;
vect_error_entity  error;
};

struct req_basedata {
_num64  ver;
std::string  strcriteria;
_num64  numcriteria;
};

struct resp_basedata {
_num64  err;
vect_base_data  base;
vect_error_entity  error;
};

struct req_setbasedata {
_num64  ver;
vect_base_data  base;
};

struct resp_setbasedata {
_num64  err;
vect_error_entity  error;
};

struct base_data {
vect_group_data  groups;
vect_tag_data  tags;
vect_agroup_data  agroups;
vect_user_data  users;
_num64  options;
};

struct req_adminoperation {
_num64  ver;
_num64  numpar1;
_num64  numpar2;
_num64  numpar3;
std::string  strpar1;
std::string  strpar2;
std::string  strpar3;
};

struct resp_adminoperation {
_num64  err;
vect_error_entity  error;
};

struct req_autorization {
_num64  ver;
std::string  name;
std::string  password;
};

struct resp_autorization {
_num64  err;
_num64  platform;
_num64  ver;
_num64  local;
};

struct req_services {
_num64  ver;
std::vector<_num64 >  keys;
};

struct req_sendservices {
_num64  ver;
vect_service_data  services;
};

struct resp_services {
_num64  err;
vect_service_data  services;
};

struct resp_sendservices {
_num64  err;
vect_service_data  services;
vect_error_entity  error;
};

struct service_data {
_num64  key;
std::string  name;
std::string  path;
std::string  depend;
std::string  user;
std::string  pass;
std::string  unuse;
_num64  starttype;
_num64  status;
_num64  unusenum1;
_num64  unusenum2;
_num64  changeset;
};


namespace boost {
namespace serialization {


   template<class Archive>
   void serialize(Archive& ar, error_outside& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_entitysigs& g, const unsigned int version) {
        ar & g.ver;
        ar & g.tpitem;
        ar & g.parentid;
        ar & g.strcriteria;
        ar & g.numcriteria;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_entitysigs& g, const unsigned int version) {
        ar & g.tpreq;
        ar & g.err;
        ar & g.sigs;
   };

   template<class Archive>
   void serialize(Archive& ar, entitysig_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.tpitem;
   };

   template<class Archive>
   void serialize(Archive& ar, error_entity& g, const unsigned int version) {
        ar & g.code;
        ar & g.key;
        ar & g.str;
   };

   template<class Archive>
   void serialize(Archive& ar, req_removeentity& g, const unsigned int version) {
        ar & g.ver;
        ar & g.tpitem;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_removeentity& g, const unsigned int version) {
        ar & g.err;
        ar & g.ver;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_addentity& g, const unsigned int version) {
        ar & g.ver;
        ar & g.tpitem;
        ar & g.parentkey;
        ar & g.newname;
        ar & g.numcriteria;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_addentity& g, const unsigned int version) {
        ar & g.err;
        ar & g.ver;
        ar & g.sig;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_tags& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendtags& g, const unsigned int version) {
        ar & g.ver;
        ar & g.tags;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_tags& g, const unsigned int version) {
        ar & g.err;
        ar & g.tags;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendtags& g, const unsigned int version) {
        ar & g.err;
        ar & g.tags;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, tag_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.tginfo;
        ar & g.name;
        ar & g.comment;
        ar & g.bind;
        ar & g.ue;
        ar & g.onmsg;
        ar & g.offmsg;
        ar & g.almsg;
        ar & g.group;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_groups& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendgroups& g, const unsigned int version) {
        ar & g.ver;
        ar & g.groups;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_groups& g, const unsigned int version) {
        ar & g.err;
        ar & g.groups;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendgroups& g, const unsigned int version) {
        ar & g.err;
        ar & g.groups;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, group_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.groupinfo;
        ar & g.name;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_agroups& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendagroups& g, const unsigned int version) {
        ar & g.ver;
        ar & g.agroups;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_agroups& g, const unsigned int version) {
        ar & g.err;
        ar & g.agroups;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendagroups& g, const unsigned int version) {
        ar & g.err;
        ar & g.agroups;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, agroup_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.agroupinfo;
        ar & g.name;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_users& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendusers& g, const unsigned int version) {
        ar & g.ver;
        ar & g.users;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_users& g, const unsigned int version) {
        ar & g.err;
        ar & g.users;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendusers& g, const unsigned int version) {
        ar & g.err;
        ar & g.users;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, user_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.password;
        ar & g.level;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_metas& g, const unsigned int version) {
        ar & g.ver;
        ar & g.meta_type;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendmetas& g, const unsigned int version) {
        ar & g.ver;
        ar & g.metas;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_metas& g, const unsigned int version) {
        ar & g.err;
        ar & g.metas;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendmetas& g, const unsigned int version) {
        ar & g.err;
        ar & g.metas;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, meta_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.meta_type;
        ar & g.str_data;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_regs& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_regs& g, const unsigned int version) {
        ar & g.err;
        ar & g.regs;
   };

   template<class Archive>
   void serialize(Archive& ar, reg_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.appid;
        ar & g.hndl;
        ar & g.evst;
   };

   template<class Archive>
   void serialize(Archive& ar, req_viewcount& g, const unsigned int version) {
        ar & g.ver;
        ar & g.type;
        ar & g.numcriteria;
        ar & g.strcriteria;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_viewcount& g, const unsigned int version) {
        ar & g.err;
        ar & g.type;
        ar & g.globalnum;
        ar & g.count;
   };

   template<class Archive>
   void serialize(Archive& ar, req_views& g, const unsigned int version) {
        ar & g.ver;
        ar & g.type;
        ar & g.nums;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_views& g, const unsigned int version) {
        ar & g.err;
        ar & g.type;
        ar & g.views;
   };

   template<class Archive>
   void serialize(Archive& ar, view_data& g, const unsigned int version) {
        ar & g.num;
        ar & g.time;
        ar & g.tgid;
        ar & g.lev_type;
        ar & g.exec_iskvit;
        ar & g.isoff;
        ar & g.val_before;
        ar & g.val_set;
        ar & g.unu1;
        ar & g.unu2;
        ar & g.mess_host;
        ar & g.app_user;
        ar & g.unu3;
   };

   template<class Archive>
   void serialize(Archive& ar, config_data& g, const unsigned int version) {
        ar & g.str_data;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_config& g, const unsigned int version) {
        ar & g.ver;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendconfig& g, const unsigned int version) {
        ar & g.ver;
        ar & g.config;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_config& g, const unsigned int version) {
        ar & g.err;
        ar & g.config;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendconfig& g, const unsigned int version) {
        ar & g.err;
        ar & g.config;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_basedata& g, const unsigned int version) {
        ar & g.ver;
        ar & g.strcriteria;
        ar & g.numcriteria;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_basedata& g, const unsigned int version) {
        ar & g.err;
        ar & g.base;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_setbasedata& g, const unsigned int version) {
        ar & g.ver;
        ar & g.base;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_setbasedata& g, const unsigned int version) {
        ar & g.err;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, base_data& g, const unsigned int version) {
        ar & g.groups;
        ar & g.tags;
        ar & g.agroups;
        ar & g.users;
        ar & g.options;
   };

   template<class Archive>
   void serialize(Archive& ar, req_adminoperation& g, const unsigned int version) {
        ar & g.ver;
        ar & g.numpar1;
        ar & g.numpar2;
        ar & g.numpar3;
        ar & g.strpar1;
        ar & g.strpar2;
        ar & g.strpar3;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_adminoperation& g, const unsigned int version) {
        ar & g.err;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_autorization& g, const unsigned int version) {
        ar & g.ver;
        ar & g.name;
        ar & g.password;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_autorization& g, const unsigned int version) {
        ar & g.err;
        ar & g.platform;
        ar & g.ver;
        ar & g.local;
   };

   template<class Archive>
   void serialize(Archive& ar, req_services& g, const unsigned int version) {
        ar & g.ver;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendservices& g, const unsigned int version) {
        ar & g.ver;
        ar & g.services;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_services& g, const unsigned int version) {
        ar & g.err;
        ar & g.services;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendservices& g, const unsigned int version) {
        ar & g.err;
        ar & g.services;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, service_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.path;
        ar & g.depend;
        ar & g.user;
        ar & g.pass;
        ar & g.unuse;
        ar & g.starttype;
        ar & g.status;
        ar & g.unusenum1;
        ar & g.unusenum2;
        ar & g.changeset;
   };

}
}


#endif  /* _RPCSTRUCT_RPC_ */
