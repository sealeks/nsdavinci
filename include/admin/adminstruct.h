/*
 * Automatically generated from adminstruct.rpc
 */

#ifndef _ADMINSTRUCT_RPC_
#define _ADMINSTRUCT_RPC_

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

namespace dvnci {
namespace admin {

struct error_outside;
struct req_entitysigs;
struct resp_entitysigs;
struct entitysig_data;
struct error_entity;
struct req_removeentity;
struct resp_removeentity;
struct req_addentity;
struct resp_addentity;
struct req_dupentity;
struct resp_dupentity;
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
struct req_accessrules;
struct req_sendaccessrules;
struct resp_accessrules;
struct resp_sendaccessrules;
struct accessrule_data;
struct req_users;
struct req_sendusers;
struct resp_users;
struct resp_sendusers;
struct user_data;
struct req_journal;
struct resp_journal;
struct journal_data;
struct req_debug;
struct resp_debug;
struct debug_data;
struct req_alarms;
struct resp_alarms;
struct alarms_data;
struct req_commands;
struct resp_commands;
struct commands_data;
struct req_registry;
struct resp_registry;
struct registry_data;
struct req_clients;
struct resp_clients;
struct clients_data;
struct req_metas;
struct req_sendmetas;
struct resp_metas;
struct resp_sendmetas;
struct meta_data;
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
const short RPC_OPERATION_REQ_DUPENTITY=0x19;
const short RPC_OPERATION_RESP_DUPENTITY=0x1A;
const short RPC_OPERATION_REQ_TAGS=0x1B;
const short RPC_OPERATION_REQ_SENDTAGS=0x1C;
const short RPC_OPERATION_RESP_TAGS=0x1D;
const short RPC_OPERATION_RESP_SENDTAGS=0x1E;
const short RPC_OPERATION_TAG_DATA=0x1F;
const short RPC_OPERATION_REQ_GROUPS=0x20;
const short RPC_OPERATION_REQ_SENDGROUPS=0x21;
const short RPC_OPERATION_RESP_GROUPS=0x22;
const short RPC_OPERATION_RESP_SENDGROUPS=0x23;
const short RPC_OPERATION_GROUP_DATA=0x24;
const short RPC_OPERATION_REQ_AGROUPS=0x25;
const short RPC_OPERATION_REQ_SENDAGROUPS=0x26;
const short RPC_OPERATION_RESP_AGROUPS=0x27;
const short RPC_OPERATION_RESP_SENDAGROUPS=0x28;
const short RPC_OPERATION_AGROUP_DATA=0x29;
const short RPC_OPERATION_REQ_ACCESSRULES=0x2A;
const short RPC_OPERATION_REQ_SENDACCESSRULES=0x2B;
const short RPC_OPERATION_RESP_ACCESSRULES=0x2C;
const short RPC_OPERATION_RESP_SENDACCESSRULES=0x2D;
const short RPC_OPERATION_ACCESSRULE_DATA=0x2E;
const short RPC_OPERATION_REQ_USERS=0x2F;
const short RPC_OPERATION_REQ_SENDUSERS=0x30;
const short RPC_OPERATION_RESP_USERS=0x31;
const short RPC_OPERATION_RESP_SENDUSERS=0x32;
const short RPC_OPERATION_USER_DATA=0x33;
const short RPC_OPERATION_REQ_JOURNAL=0x34;
const short RPC_OPERATION_RESP_JOURNAL=0x35;
const short RPC_OPERATION_JOURNAL_DATA=0x36;
const short RPC_OPERATION_REQ_DEBUG=0x37;
const short RPC_OPERATION_RESP_DEBUG=0x38;
const short RPC_OPERATION_DEBUG_DATA=0x39;
const short RPC_OPERATION_REQ_ALARMS=0x3A;
const short RPC_OPERATION_RESP_ALARMS=0x3B;
const short RPC_OPERATION_ALARMS_DATA=0x3C;
const short RPC_OPERATION_REQ_COMMANDS=0x3D;
const short RPC_OPERATION_RESP_COMMANDS=0x3E;
const short RPC_OPERATION_COMMANDS_DATA=0x3F;
const short RPC_OPERATION_REQ_REGISTRY=0x40;
const short RPC_OPERATION_RESP_REGISTRY=0x41;
const short RPC_OPERATION_REGISTRY_DATA=0x42;
const short RPC_OPERATION_REQ_CLIENTS=0x43;
const short RPC_OPERATION_RESP_CLIENTS=0x44;
const short RPC_OPERATION_CLIENTS_DATA=0x45;
const short RPC_OPERATION_REQ_METAS=0x46;
const short RPC_OPERATION_REQ_SENDMETAS=0x47;
const short RPC_OPERATION_RESP_METAS=0x48;
const short RPC_OPERATION_RESP_SENDMETAS=0x49;
const short RPC_OPERATION_META_DATA=0x4A;
const short RPC_OPERATION_CONFIG_DATA=0x4B;
const short RPC_OPERATION_REQ_CONFIG=0x4C;
const short RPC_OPERATION_REQ_SENDCONFIG=0x4D;
const short RPC_OPERATION_RESP_CONFIG=0x4E;
const short RPC_OPERATION_RESP_SENDCONFIG=0x4F;
const short RPC_OPERATION_REQ_BASEDATA=0x50;
const short RPC_OPERATION_RESP_BASEDATA=0x51;
const short RPC_OPERATION_REQ_SETBASEDATA=0x52;
const short RPC_OPERATION_RESP_SETBASEDATA=0x53;
const short RPC_OPERATION_BASE_DATA=0x54;
const short RPC_OPERATION_REQ_ADMINOPERATION=0x55;
const short RPC_OPERATION_RESP_ADMINOPERATION=0x56;
const short RPC_OPERATION_REQ_AUTORIZATION=0x57;
const short RPC_OPERATION_RESP_AUTORIZATION=0x58;
const short RPC_OPERATION_REQ_SERVICES=0x59;
const short RPC_OPERATION_REQ_SENDSERVICES=0x5A;
const short RPC_OPERATION_RESP_SERVICES=0x5B;
const short RPC_OPERATION_RESP_SENDSERVICES=0x5C;
const short RPC_OPERATION_SERVICE_DATA=0x5D;

typedef std::vector<error_outside > vect_error_outside;
typedef std::vector<req_entitysigs > vect_req_entitysigs;
typedef std::vector<resp_entitysigs > vect_resp_entitysigs;
typedef std::vector<entitysig_data > vect_entitysig_data;
typedef std::vector<error_entity > vect_error_entity;
typedef std::vector<req_removeentity > vect_req_removeentity;
typedef std::vector<resp_removeentity > vect_resp_removeentity;
typedef std::vector<req_addentity > vect_req_addentity;
typedef std::vector<resp_addentity > vect_resp_addentity;
typedef std::vector<req_dupentity > vect_req_dupentity;
typedef std::vector<resp_dupentity > vect_resp_dupentity;
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
typedef std::vector<req_accessrules > vect_req_accessrules;
typedef std::vector<req_sendaccessrules > vect_req_sendaccessrules;
typedef std::vector<resp_accessrules > vect_resp_accessrules;
typedef std::vector<resp_sendaccessrules > vect_resp_sendaccessrules;
typedef std::vector<accessrule_data > vect_accessrule_data;
typedef std::vector<req_users > vect_req_users;
typedef std::vector<req_sendusers > vect_req_sendusers;
typedef std::vector<resp_users > vect_resp_users;
typedef std::vector<resp_sendusers > vect_resp_sendusers;
typedef std::vector<user_data > vect_user_data;
typedef std::vector<req_journal > vect_req_journal;
typedef std::vector<resp_journal > vect_resp_journal;
typedef std::vector<journal_data > vect_journal_data;
typedef std::vector<req_debug > vect_req_debug;
typedef std::vector<resp_debug > vect_resp_debug;
typedef std::vector<debug_data > vect_debug_data;
typedef std::vector<req_alarms > vect_req_alarms;
typedef std::vector<resp_alarms > vect_resp_alarms;
typedef std::vector<alarms_data > vect_alarms_data;
typedef std::vector<req_commands > vect_req_commands;
typedef std::vector<resp_commands > vect_resp_commands;
typedef std::vector<commands_data > vect_commands_data;
typedef std::vector<req_registry > vect_req_registry;
typedef std::vector<resp_registry > vect_resp_registry;
typedef std::vector<registry_data > vect_registry_data;
typedef std::vector<req_clients > vect_req_clients;
typedef std::vector<resp_clients > vect_resp_clients;
typedef std::vector<clients_data > vect_clients_data;
typedef std::vector<req_metas > vect_req_metas;
typedef std::vector<req_sendmetas > vect_req_sendmetas;
typedef std::vector<resp_metas > vect_resp_metas;
typedef std::vector<resp_sendmetas > vect_resp_sendmetas;
typedef std::vector<meta_data > vect_meta_data;
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
num64  error;
};

struct req_entitysigs {
num64  tpitem;
num64  parentid;
std::string  strcriteria;
num64  numcriteria;
};

struct resp_entitysigs {
num64  tpreq;
num64  err;
vect_entitysig_data  sigs;
};

struct entitysig_data {
num64  key;
std::string  name;
num64  tpitem;
};

struct error_entity {
num64  code;
num64  key;
std::string  str;
};

struct req_removeentity {
num64  tpitem;
vect_num64  keys;
};

struct resp_removeentity {
num64  err;
vect_error_entity  error;
};

struct req_addentity {
num64  tpitem;
num64  parentkey;
std::string  newname;
num64  numcriteria;
};

struct resp_addentity {
num64  err;
entitysig_data  sig;
vect_error_entity  error;
};

struct req_dupentity {
num64  tpitem;
num64  soursekey;
std::string  newname;
};

struct resp_dupentity {
num64  err;
entitysig_data  sig;
vect_error_entity  error;
};

struct req_tags {
vect_num64  keys;
};

struct req_sendtags {
vect_tag_data  tags;
};

struct resp_tags {
num64  err;
vect_tag_data  tags;
};

struct resp_sendtags {
num64  err;
vect_tag_data  tags;
vect_error_entity  error;
};

struct tag_data {
num64  key;
char  tginfo[360];
std::string  name;
std::string  comment;
std::string  bind;
std::string  ue;
std::string  onmsg;
std::string  offmsg;
std::string  almsg;
std::string  group;
num64  changeset;
};

struct req_groups {
vect_num64  keys;
};

struct req_sendgroups {
vect_group_data  groups;
};

struct resp_groups {
num64  err;
vect_group_data  groups;
};

struct resp_sendgroups {
num64  err;
vect_group_data  groups;
vect_error_entity  error;
};

struct group_data {
num64  key;
char  groupinfo[512];
std::string  name;
std::string  host;
std::string  user;
std::string  password;
std::string  server;
std::string  group;
std::string  port;
std::string  topic;
std::string  ether;
std::string  unuse1;
std::string  unuse2;
std::string  unuse3;
std::string  unuse4;
num64  changeset;
};

struct req_agroups {
vect_num64  keys;
};

struct req_sendagroups {
vect_agroup_data  agroups;
};

struct resp_agroups {
num64  err;
vect_agroup_data  agroups;
};

struct resp_sendagroups {
num64  err;
vect_agroup_data  agroups;
vect_error_entity  error;
};

struct agroup_data {
num64  key;
char  agroupinfo[64];
std::string  name;
std::string  headername;
num64  changeset;
};

struct req_accessrules {
vect_num64  keys;
};

struct req_sendaccessrules {
vect_accessrule_data  accessrules;
};

struct resp_accessrules {
num64  err;
vect_accessrule_data  accessrules;
};

struct resp_sendaccessrules {
num64  err;
vect_accessrule_data  accessrules;
vect_error_entity  error;
};

struct accessrule_data {
num64  key;
std::string  name;
std::string  user;
std::string  host;
std::string  filter;
num64  appid;
num64  protocol;
num64  accessrule;
num64  accesslevel;
num64  role;
num64  changeset;
};

struct req_users {
vect_num64  keys;
};

struct req_sendusers {
vect_user_data  users;
};

struct resp_users {
num64  err;
vect_user_data  users;
};

struct resp_sendusers {
num64  err;
vect_user_data  users;
vect_error_entity  error;
};

struct user_data {
num64  key;
std::string  name;
std::string  password;
std::string  filter;
num64  accesslevel;
num64  role;
num64  changeset;
};

struct req_journal {
unum64  guid;
unum64  cursor;
unum64  cnt;
};

struct resp_journal {
num64  err;
unum64  guid;
unum64  cursor;
unum64  cnt;
vect_journal_data  lines;
};

struct journal_data {
num64  index;
unum64  guid;
datetime  time;
std::string  tag;
std::string  text;
std::string  agroup;
num64  type;
num64  level;
std::string  value;
std::string  user;
};

struct req_debug {
unum64  guid;
unum64  cursor;
unum64  cnt;
};

struct resp_debug {
num64  err;
unum64  guid;
unum64  cursor;
unum64  cnt;
vect_debug_data  lines;
};

struct debug_data {
num64  index;
unum64  guid;
datetime  time;
std::string  message;
num64  level;
num64  appid;
};

struct req_alarms {
unum64  vers;
std::string  agroup;
std::string  group;
};

struct resp_alarms {
num64  err;
unum64  vers;
vect_alarms_data  lines;
};

struct alarms_data {
datetime  time;
std::string  tag;
std::string  text;
num64  kvit;
num64  level;
num64  type;
std::string  value;
};

struct req_commands {
unum64  vers;
std::string  group;
};

struct resp_commands {
num64  err;
unum64  vers;
vect_commands_data  lines;
};

struct commands_data {
datetime  time;
std::string  tag;
std::string  group;
std::string  valuebefore;
std::string  value;
std::string  user;
std::string  host;
};

struct req_registry {
unum64  vers;
};

struct resp_registry {
num64  err;
unum64  vers;
vect_registry_data  lines;
};

struct registry_data {
num64  handle;
num64  appid;
num64  eventset;
num64  queuehandle;
};

struct req_clients {
unum64  vers;
};

struct resp_clients {
num64  err;
unum64  vers;
vect_clients_data  lines;
};

struct clients_data {
std::string  name;
std::string  host;
std::string  ip;
std::string  user;
num64  appid;
num64  accesslevel;
num64  ruleid;
};

struct req_metas {
num64  meta_type;
vect_num64  keys;
};

struct req_sendmetas {
vect_meta_data  metas;
};

struct resp_metas {
num64  err;
vect_meta_data  metas;
};

struct resp_sendmetas {
num64  err;
vect_meta_data  metas;
vect_error_entity  error;
};

struct meta_data {
num64  key;
num64  meta_type;
std::string  str_data[19];
num64  changeset;
};

struct config_data {
std::string  str_data[19];
num64  changeset;
};

struct req_config {
num64  ver;
};

struct req_sendconfig {
config_data  config;
};

struct resp_config {
num64  err;
config_data  config;
};

struct resp_sendconfig {
num64  err;
config_data  config;
vect_error_entity  error;
};

struct req_basedata {
std::string  strcriteria;
num64  numcriteria;
};

struct resp_basedata {
num64  err;
vect_base_data  base;
vect_error_entity  error;
};

struct req_setbasedata {
vect_base_data  base;
};

struct resp_setbasedata {
num64  err;
vect_error_entity  error;
};

struct base_data {
vect_group_data  groups;
vect_tag_data  tags;
vect_agroup_data  agroups;
vect_user_data  users;
num64  options;
};

struct req_adminoperation {
num64  ver;
num64  numpar1;
num64  numpar2;
num64  numpar3;
std::string  strpar1;
std::string  strpar2;
std::string  strpar3;
};

struct resp_adminoperation {
num64  err;
vect_error_entity  error;
};

struct req_autorization {
num64  ver;
std::string  name;
std::string  password;
};

struct resp_autorization {
num64  err;
num64  platform;
num64  ver;
num64  local;
};

struct req_services {
vect_num64  keys;
};

struct req_sendservices {
vect_service_data  services;
};

struct resp_services {
num64  err;
vect_service_data  services;
};

struct resp_sendservices {
num64  err;
vect_service_data  services;
vect_error_entity  error;
};

struct service_data {
num64  key;
std::string  name;
std::string  path;
std::string  depend;
std::string  user;
std::string  pass;
std::string  unuse;
num64  starttype;
num64  status;
num64  unusenum1;
num64  unusenum2;
num64  changeset;
};

}}

namespace boost {
namespace serialization {


   using namespace dvnci::admin;
   
   template<class Archive>
   void serialize(Archive& ar, error_outside& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_entitysigs& g, const unsigned int version) {
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
        ar & g.tpitem;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_removeentity& g, const unsigned int version) {
        ar & g.err;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_addentity& g, const unsigned int version) {
        ar & g.tpitem;
        ar & g.parentkey;
        ar & g.newname;
        ar & g.numcriteria;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_addentity& g, const unsigned int version) {
        ar & g.err;
        ar & g.sig;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_dupentity& g, const unsigned int version) {
        ar & g.tpitem;
        ar & g.soursekey;
        ar & g.newname;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_dupentity& g, const unsigned int version) {
        ar & g.err;
        ar & g.sig;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_tags& g, const unsigned int version) {
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendtags& g, const unsigned int version) {
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
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendgroups& g, const unsigned int version) {
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
        ar & g.host;
        ar & g.user;
        ar & g.password;
        ar & g.server;
        ar & g.group;
        ar & g.port;
        ar & g.topic;
        ar & g.ether;
        ar & g.unuse1;
        ar & g.unuse2;
        ar & g.unuse3;
        ar & g.unuse4;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_agroups& g, const unsigned int version) {
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendagroups& g, const unsigned int version) {
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
        ar & g.headername;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_accessrules& g, const unsigned int version) {
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendaccessrules& g, const unsigned int version) {
        ar & g.accessrules;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_accessrules& g, const unsigned int version) {
        ar & g.err;
        ar & g.accessrules;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_sendaccessrules& g, const unsigned int version) {
        ar & g.err;
        ar & g.accessrules;
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, accessrule_data& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.user;
        ar & g.host;
        ar & g.filter;
        ar & g.appid;
        ar & g.protocol;
        ar & g.accessrule;
        ar & g.accesslevel;
        ar & g.role;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_users& g, const unsigned int version) {
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendusers& g, const unsigned int version) {
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
        ar & g.filter;
        ar & g.accesslevel;
        ar & g.role;
        ar & g.changeset;
   };

   template<class Archive>
   void serialize(Archive& ar, req_journal& g, const unsigned int version) {
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_journal& g, const unsigned int version) {
        ar & g.err;
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, journal_data& g, const unsigned int version) {
        ar & g.index;
        ar & g.guid;
        ar & g.time;
        ar & g.tag;
        ar & g.text;
        ar & g.agroup;
        ar & g.type;
        ar & g.level;
        ar & g.value;
        ar & g.user;
   };

   template<class Archive>
   void serialize(Archive& ar, req_debug& g, const unsigned int version) {
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_debug& g, const unsigned int version) {
        ar & g.err;
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, debug_data& g, const unsigned int version) {
        ar & g.index;
        ar & g.guid;
        ar & g.time;
        ar & g.message;
        ar & g.level;
        ar & g.appid;
   };

   template<class Archive>
   void serialize(Archive& ar, req_alarms& g, const unsigned int version) {
        ar & g.vers;
        ar & g.agroup;
        ar & g.group;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_alarms& g, const unsigned int version) {
        ar & g.err;
        ar & g.vers;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, alarms_data& g, const unsigned int version) {
        ar & g.time;
        ar & g.tag;
        ar & g.text;
        ar & g.kvit;
        ar & g.level;
        ar & g.type;
        ar & g.value;
   };

   template<class Archive>
   void serialize(Archive& ar, req_commands& g, const unsigned int version) {
        ar & g.vers;
        ar & g.group;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_commands& g, const unsigned int version) {
        ar & g.err;
        ar & g.vers;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, commands_data& g, const unsigned int version) {
        ar & g.time;
        ar & g.tag;
        ar & g.group;
        ar & g.valuebefore;
        ar & g.value;
        ar & g.user;
        ar & g.host;
   };

   template<class Archive>
   void serialize(Archive& ar, req_registry& g, const unsigned int version) {
        ar & g.vers;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_registry& g, const unsigned int version) {
        ar & g.err;
        ar & g.vers;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, registry_data& g, const unsigned int version) {
        ar & g.handle;
        ar & g.appid;
        ar & g.eventset;
        ar & g.queuehandle;
   };

   template<class Archive>
   void serialize(Archive& ar, req_clients& g, const unsigned int version) {
        ar & g.vers;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_clients& g, const unsigned int version) {
        ar & g.err;
        ar & g.vers;
        ar & g.lines;
   };

   template<class Archive>
   void serialize(Archive& ar, clients_data& g, const unsigned int version) {
        ar & g.name;
        ar & g.host;
        ar & g.ip;
        ar & g.user;
        ar & g.appid;
        ar & g.accesslevel;
        ar & g.ruleid;
   };

   template<class Archive>
   void serialize(Archive& ar, req_metas& g, const unsigned int version) {
        ar & g.meta_type;
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendmetas& g, const unsigned int version) {
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
        ar & g.keys;
   };

   template<class Archive>
   void serialize(Archive& ar, req_sendservices& g, const unsigned int version) {
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


#endif  /* _ADMINSTRUCT_RPC_ */
