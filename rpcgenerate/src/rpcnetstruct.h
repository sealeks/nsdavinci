/*
 * Automatically generated from rpcnetstruct.rpc
 */

#ifndef _RPCNETSTRUCT_RPC_
#define _RPCNETSTRUCT_RPC_

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
struct req_items;
struct resp_items;
struct client_item;
struct server_item;
struct error_item;
struct req_reporttask;
struct resp_reporttask;
struct req_values;
struct req_values_ex;
struct resp_values;
struct resp_values_ex;
struct value_item;
struct report_value_item;
struct report_value_items;
struct req_remitems;
struct resp_remitems;
struct req_commands;
struct resp_commands;
struct command_item;

const short RPC_OPERATION_ERROR_OUTSIDE=0x10;
const short RPC_OPERATION_REQ_ITEMS=0x11;
const short RPC_OPERATION_RESP_ITEMS=0x12;
const short RPC_OPERATION_CLIENT_ITEM=0x13;
const short RPC_OPERATION_SERVER_ITEM=0x14;
const short RPC_OPERATION_ERROR_ITEM=0x15;
const short RPC_OPERATION_REQ_REPORTTASK=0x16;
const short RPC_OPERATION_RESP_REPORTTASK=0x17;
const short RPC_OPERATION_REQ_VALUES=0x18;
const short RPC_OPERATION_REQ_VALUES_EX=0x19;
const short RPC_OPERATION_RESP_VALUES=0x1A;
const short RPC_OPERATION_RESP_VALUES_EX=0x1B;
const short RPC_OPERATION_VALUE_ITEM=0x1C;
const short RPC_OPERATION_REPORT_VALUE_ITEM=0x1D;
const short RPC_OPERATION_REPORT_VALUE_ITEMS=0x1E;
const short RPC_OPERATION_REQ_REMITEMS=0x1F;
const short RPC_OPERATION_RESP_REMITEMS=0x20;
const short RPC_OPERATION_REQ_COMMANDS=0x21;
const short RPC_OPERATION_RESP_COMMANDS=0x22;
const short RPC_OPERATION_COMMAND_ITEM=0x23;

typedef std::vector<error_outside > vect_error_outside;
typedef std::vector<req_items > vect_req_items;
typedef std::vector<resp_items > vect_resp_items;
typedef std::vector<client_item > vect_client_item;
typedef std::vector<server_item > vect_server_item;
typedef std::vector<error_item > vect_error_item;
typedef std::vector<req_reporttask > vect_req_reporttask;
typedef std::vector<resp_reporttask > vect_resp_reporttask;
typedef std::vector<req_values > vect_req_values;
typedef std::vector<req_values_ex > vect_req_values_ex;
typedef std::vector<resp_values > vect_resp_values;
typedef std::vector<resp_values_ex > vect_resp_values_ex;
typedef std::vector<value_item > vect_value_item;
typedef std::vector<report_value_item > vect_report_value_item;
typedef std::vector<report_value_items > vect_report_value_items;
typedef std::vector<req_remitems > vect_req_remitems;
typedef std::vector<resp_remitems > vect_resp_remitems;
typedef std::vector<req_commands > vect_req_commands;
typedef std::vector<resp_commands > vect_resp_commands;
typedef std::vector<command_item > vect_command_item;

struct error_outside {
_num64  error;
};

struct req_items {
_num64  ver;
vect_client_item  cl_items;
};

struct resp_items {
vect_server_item  srv_items;
vect_error_item  errors;
};

struct client_item {
_num64  key;
std::string  name;
_num64  tpitem;
_num64  dbound;
};

struct server_item {
_num64  key;
_num64  outkey;
_num64  tpitem;
};

struct error_item {
_num64  code;
_num64  key;
};

struct req_reporttask {
_num64  ver;
_num64  key;
_num64  start;
_num64  stop;
};

struct resp_reporttask {
_num64  error;
};

struct req_values {
_num64  ver;
std::vector<_num64 >  srv_ids;
};

struct req_values_ex {
_num64  ver;
};

struct resp_values {
vect_value_item  items;
vect_report_value_items  repitems;
vect_error_item  errors;
};

struct resp_values_ex {
vect_value_item  items;
vect_report_value_items  repitems;
};

struct value_item {
_num64  outkey;
_num64  val;
_num64  valid;
_num64  time;
_num64  type;
};

struct report_value_item {
_num64  val;
_num64  valid;
_num64  time;
_num64  type;
};

struct report_value_items {
_num64  outkey;
vect_report_value_item  values;
};

struct req_remitems {
_num64  ver;
std::vector<_num64 >  outkey;
};

struct resp_remitems {
vect_error_item  errors;
};

struct req_commands {
_num64  ver;
vect_command_item  commands;
};

struct resp_commands {
vect_error_item  errors;
};

struct command_item {
_num64  outkey;
_num64  val;
_num64  type;
_num64  queue;
std::string  user;
std::string  pass;
};


namespace boost {
namespace serialization {


   template<class Archive>
   void serialize(Archive& ar, error_outside& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_items& g, const unsigned int version) {
        ar & g.ver;
        ar & g.cl_items;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_items& g, const unsigned int version) {
        ar & g.srv_items;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, client_item& g, const unsigned int version) {
        ar & g.key;
        ar & g.name;
        ar & g.tpitem;
        ar & g.dbound;
   };

   template<class Archive>
   void serialize(Archive& ar, server_item& g, const unsigned int version) {
        ar & g.key;
        ar & g.outkey;
        ar & g.tpitem;
   };

   template<class Archive>
   void serialize(Archive& ar, error_item& g, const unsigned int version) {
        ar & g.code;
        ar & g.key;
   };

   template<class Archive>
   void serialize(Archive& ar, req_reporttask& g, const unsigned int version) {
        ar & g.ver;
        ar & g.key;
        ar & g.start;
        ar & g.stop;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_reporttask& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_values& g, const unsigned int version) {
        ar & g.ver;
        ar & g.srv_ids;
   };

   template<class Archive>
   void serialize(Archive& ar, req_values_ex& g, const unsigned int version) {
        ar & g.ver;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_values& g, const unsigned int version) {
        ar & g.items;
        ar & g.repitems;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_values_ex& g, const unsigned int version) {
        ar & g.items;
        ar & g.repitems;
   };

   template<class Archive>
   void serialize(Archive& ar, value_item& g, const unsigned int version) {
        ar & g.outkey;
        ar & g.val;
        ar & g.valid;
        ar & g.time;
        ar & g.type;
   };

   template<class Archive>
   void serialize(Archive& ar, report_value_item& g, const unsigned int version) {
        ar & g.val;
        ar & g.valid;
        ar & g.time;
        ar & g.type;
   };

   template<class Archive>
   void serialize(Archive& ar, report_value_items& g, const unsigned int version) {
        ar & g.outkey;
        ar & g.values;
   };

   template<class Archive>
   void serialize(Archive& ar, req_remitems& g, const unsigned int version) {
        ar & g.ver;
        ar & g.outkey;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_remitems& g, const unsigned int version) {
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, req_commands& g, const unsigned int version) {
        ar & g.ver;
        ar & g.commands;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_commands& g, const unsigned int version) {
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, command_item& g, const unsigned int version) {
        ar & g.outkey;
        ar & g.val;
        ar & g.type;
        ar & g.queue;
        ar & g.user;
        ar & g.pass;
   };

}
}


#endif  /* _RPCNETSTRUCT_RPC_ */
