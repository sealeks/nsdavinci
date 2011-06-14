/*
 * Automatically generated from netstruct.rpc
 */

#ifndef _NETSTRUCT_RPC_
#define _NETSTRUCT_RPC_

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

struct error_info;
struct error_ex_info;
struct error_outside;
struct req_auth;
struct resp_auth;
struct cid_key;
struct sid_key;
struct req_add_items;
struct resp_add_items;
struct cid_key_ex;
struct sid_key_ex;
struct req_add_items_ex;
struct resp_add_items_ex;
struct req_remove_items;
struct resp_remove_items;
struct data_item;
struct data_item_str;
struct req_data_item;
struct req_data_item1;
struct resp_data_item;
struct req_data_item_ex;
struct req_data_item_ex1;
struct resp_data_item_ex;
struct command_data;
struct req_send_commands;
struct resp_send_commands;
struct reporttask;
struct report_value_item;
struct report_value_data;
struct req_reporttask;
struct resp_reporttask;
struct event_value_item;
struct eventtask;
struct req_eventtask;
struct resp_eventtask;
struct trendtask;
struct trend_value_item;
struct trend_value_data;
struct req_trendtask;
struct resp_trendtask;
struct alarms_data;
struct req_alarms;
struct resp_alarms;
struct journal_data;
struct req_journal;
struct resp_journal;

const short RPC_OPERATION_ERROR_INFO=0x10;
const short RPC_OPERATION_ERROR_EX_INFO=0x11;
const short RPC_OPERATION_ERROR_OUTSIDE=0x12;
const short RPC_OPERATION_REQ_AUTH=0x13;
const short RPC_OPERATION_RESP_AUTH=0x14;
const short RPC_OPERATION_CID_KEY=0x15;
const short RPC_OPERATION_SID_KEY=0x16;
const short RPC_OPERATION_REQ_ADD_ITEMS=0x17;
const short RPC_OPERATION_RESP_ADD_ITEMS=0x18;
const short RPC_OPERATION_CID_KEY_EX=0x19;
const short RPC_OPERATION_SID_KEY_EX=0x1A;
const short RPC_OPERATION_REQ_ADD_ITEMS_EX=0x1B;
const short RPC_OPERATION_RESP_ADD_ITEMS_EX=0x1C;
const short RPC_OPERATION_REQ_REMOVE_ITEMS=0x1D;
const short RPC_OPERATION_RESP_REMOVE_ITEMS=0x1E;
const short RPC_OPERATION_DATA_ITEM=0x1F;
const short RPC_OPERATION_DATA_ITEM_STR=0x20;
const short RPC_OPERATION_REQ_DATA_ITEM=0x21;
const short RPC_OPERATION_REQ_DATA_ITEM1=0x22;
const short RPC_OPERATION_RESP_DATA_ITEM=0x23;
const short RPC_OPERATION_REQ_DATA_ITEM_EX=0x24;
const short RPC_OPERATION_REQ_DATA_ITEM_EX1=0x25;
const short RPC_OPERATION_RESP_DATA_ITEM_EX=0x26;
const short RPC_OPERATION_COMMAND_DATA=0x27;
const short RPC_OPERATION_REQ_SEND_COMMANDS=0x28;
const short RPC_OPERATION_RESP_SEND_COMMANDS=0x29;
const short RPC_OPERATION_REPORTTASK=0x2A;
const short RPC_OPERATION_REPORT_VALUE_ITEM=0x2B;
const short RPC_OPERATION_REPORT_VALUE_DATA=0x2C;
const short RPC_OPERATION_REQ_REPORTTASK=0x2D;
const short RPC_OPERATION_RESP_REPORTTASK=0x2E;
const short RPC_OPERATION_EVENT_VALUE_ITEM=0x2F;
const short RPC_OPERATION_EVENTTASK=0x30;
const short RPC_OPERATION_REQ_EVENTTASK=0x31;
const short RPC_OPERATION_RESP_EVENTTASK=0x32;
const short RPC_OPERATION_TRENDTASK=0x33;
const short RPC_OPERATION_TREND_VALUE_ITEM=0x34;
const short RPC_OPERATION_TREND_VALUE_DATA=0x35;
const short RPC_OPERATION_REQ_TRENDTASK=0x36;
const short RPC_OPERATION_RESP_TRENDTASK=0x37;
const short RPC_OPERATION_ALARMS_DATA=0x38;
const short RPC_OPERATION_REQ_ALARMS=0x39;
const short RPC_OPERATION_RESP_ALARMS=0x3A;
const short RPC_OPERATION_JOURNAL_DATA=0x3B;
const short RPC_OPERATION_REQ_JOURNAL=0x3C;
const short RPC_OPERATION_RESP_JOURNAL=0x3D;

typedef std::vector<error_info > vect_error_info;
typedef std::vector<error_ex_info > vect_error_ex_info;
typedef std::vector<error_outside > vect_error_outside;
typedef std::vector<req_auth > vect_req_auth;
typedef std::vector<resp_auth > vect_resp_auth;
typedef std::vector<cid_key > vect_cid_key;
typedef std::vector<sid_key > vect_sid_key;
typedef std::vector<req_add_items > vect_req_add_items;
typedef std::vector<resp_add_items > vect_resp_add_items;
typedef std::vector<cid_key_ex > vect_cid_key_ex;
typedef std::vector<sid_key_ex > vect_sid_key_ex;
typedef std::vector<req_add_items_ex > vect_req_add_items_ex;
typedef std::vector<resp_add_items_ex > vect_resp_add_items_ex;
typedef std::vector<req_remove_items > vect_req_remove_items;
typedef std::vector<resp_remove_items > vect_resp_remove_items;
typedef std::vector<data_item > vect_data_item;
typedef std::vector<data_item_str > vect_data_item_str;
typedef std::vector<req_data_item > vect_req_data_item;
typedef std::vector<req_data_item1 > vect_req_data_item1;
typedef std::vector<resp_data_item > vect_resp_data_item;
typedef std::vector<req_data_item_ex > vect_req_data_item_ex;
typedef std::vector<req_data_item_ex1 > vect_req_data_item_ex1;
typedef std::vector<resp_data_item_ex > vect_resp_data_item_ex;
typedef std::vector<command_data > vect_command_data;
typedef std::vector<req_send_commands > vect_req_send_commands;
typedef std::vector<resp_send_commands > vect_resp_send_commands;
typedef std::vector<reporttask > vect_reporttask;
typedef std::vector<report_value_item > vect_report_value_item;
typedef std::vector<report_value_data > vect_report_value_data;
typedef std::vector<req_reporttask > vect_req_reporttask;
typedef std::vector<resp_reporttask > vect_resp_reporttask;
typedef std::vector<event_value_item > vect_event_value_item;
typedef std::vector<eventtask > vect_eventtask;
typedef std::vector<req_eventtask > vect_req_eventtask;
typedef std::vector<resp_eventtask > vect_resp_eventtask;
typedef std::vector<trendtask > vect_trendtask;
typedef std::vector<trend_value_item > vect_trend_value_item;
typedef std::vector<trend_value_data > vect_trend_value_data;
typedef std::vector<req_trendtask > vect_req_trendtask;
typedef std::vector<resp_trendtask > vect_resp_trendtask;
typedef std::vector<alarms_data > vect_alarms_data;
typedef std::vector<req_alarms > vect_req_alarms;
typedef std::vector<resp_alarms > vect_resp_alarms;
typedef std::vector<journal_data > vect_journal_data;
typedef std::vector<req_journal > vect_req_journal;
typedef std::vector<resp_journal > vect_resp_journal;

struct error_info {
num64  id;
num64  code;
};

struct error_ex_info {
std::string  cid;
num64  code;
};

struct error_outside {
num64  error;
};

struct req_auth {
std::string  user;
std::string  pass;
};

struct resp_auth {
error_info  error;
};

struct cid_key {
num64  cid;
std::string  name;
num64  type;
num64  dbound;
};

struct sid_key {
num64  cid;
num64  sid;
};

struct req_add_items {
vect_cid_key  cids;
};

struct resp_add_items {
vect_sid_key  sids;
vect_error_info  errors;
};

struct cid_key_ex {
std::string  cid;
num64  dbound;
};

struct sid_key_ex {
std::string  cid;
num64  sid;
num64  val;
num64  time;
num64  pack;
num64  mineu;
num64  maxeu;
std::string  valstr;
std::string  comment;
std::string  eu;
};

struct req_add_items_ex {
vect_cid_key_ex  cids;
};

struct resp_add_items_ex {
vect_cid_key_ex  sids;
vect_error_ex_info  errors;
};

struct req_remove_items {
vect_num64  cids;
};

struct resp_remove_items {
vect_num64  cids;
vect_error_info  errors;
};

struct data_item {
num64  sid;
num64  val;
num64  time;
num64  pack;
};

struct data_item_str {
num64  sid;
std::string  val;
num64  vld;
num64  time;
};

struct req_data_item {
num64  stub;
};

struct req_data_item1 {
vect_num64  sids;
};

struct resp_data_item {
vect_data_item  lines;
vect_data_item_str  linesstr;
vect_error_info  errors;
};

struct req_data_item_ex {
num64  stub;
};

struct req_data_item_ex1 {
vect_num64  sids;
};

struct resp_data_item_ex {
vect_data_item  lines;
vect_data_item  strlines;
vect_sid_key_ex  fulllines;
vect_error_info  errors;
};

struct command_data {
num64  sid;
num64  val;
num64  type;
num64  queue;
std::string  valstr;
};

struct req_send_commands {
vect_command_data  cmds;
};

struct resp_send_commands {
vect_error_info  errors;
};

struct reporttask {
num64  sid;
num64  start;
num64  stop;
};

struct report_value_item {
num64  val;
num64  time;
};

struct report_value_data {
num64  sid;
vect_report_value_item  data;
};

struct req_reporttask {
vect_reporttask  tasks;
};

struct resp_reporttask {
vect_report_value_data  datas;
vect_error_info  errors;
};

struct event_value_item {
num64  sid;
num64  val;
num64  time;
};

struct eventtask {
num64  sid;
num64  start;
};

struct req_eventtask {
vect_eventtask  tasks;
};

struct resp_eventtask {
vect_event_value_item  data;
vect_error_info  errors;
};

struct trendtask {
num64  sid;
num64  start;
num64  stop;
};

struct trend_value_item {
num64  val;
num64  time;
};

struct trend_value_data {
num64  sid;
vect_trend_value_item  data;
};

struct req_trendtask {
vect_trendtask  tasks;
};

struct resp_trendtask {
vect_trend_value_data  datas;
vect_error_info  errors;
};

struct alarms_data {
num64  time;
std::string  tag;
std::string  text;
num64  kvit;
num64  level;
num64  type;
std::string  value;
};

struct req_alarms {
unum64  vers;
};

struct resp_alarms {
num64  err;
unum64  vers;
vect_alarms_data  lines;
};

struct journal_data {
num64  index;
unum64  guid;
num64  time;
std::string  tag;
std::string  text;
std::string  agroup;
num64  type;
num64  level;
std::string  value;
std::string  user;
};

struct req_journal {
unum64  guid;
unum64  cursor;
unum64  cnt;
};

struct resp_journal {
unum64  guid;
unum64  cursor;
unum64  cnt;
vect_journal_data  lines;
};


namespace boost {
namespace serialization {


   template<class Archive>
   void serialize(Archive& ar, error_info& g, const unsigned int version) {
        ar & g.id;
        ar & g.code;
   };

   template<class Archive>
   void serialize(Archive& ar, error_ex_info& g, const unsigned int version) {
        ar & g.cid;
        ar & g.code;
   };

   template<class Archive>
   void serialize(Archive& ar, error_outside& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, req_auth& g, const unsigned int version) {
        ar & g.user;
        ar & g.pass;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_auth& g, const unsigned int version) {
        ar & g.error;
   };

   template<class Archive>
   void serialize(Archive& ar, cid_key& g, const unsigned int version) {
        ar & g.cid;
        ar & g.name;
        ar & g.type;
        ar & g.dbound;
   };

   template<class Archive>
   void serialize(Archive& ar, sid_key& g, const unsigned int version) {
        ar & g.cid;
        ar & g.sid;
   };

   template<class Archive>
   void serialize(Archive& ar, req_add_items& g, const unsigned int version) {
        ar & g.cids;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_add_items& g, const unsigned int version) {
        ar & g.sids;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, cid_key_ex& g, const unsigned int version) {
        ar & g.cid;
        ar & g.dbound;
   };

   template<class Archive>
   void serialize(Archive& ar, sid_key_ex& g, const unsigned int version) {
        ar & g.cid;
        ar & g.sid;
        ar & g.val;
        ar & g.time;
        ar & g.pack;
        ar & g.mineu;
        ar & g.maxeu;
        ar & g.valstr;
        ar & g.comment;
        ar & g.eu;
   };

   template<class Archive>
   void serialize(Archive& ar, req_add_items_ex& g, const unsigned int version) {
        ar & g.cids;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_add_items_ex& g, const unsigned int version) {
        ar & g.sids;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, req_remove_items& g, const unsigned int version) {
        ar & g.cids;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_remove_items& g, const unsigned int version) {
        ar & g.cids;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, data_item& g, const unsigned int version) {
        ar & g.sid;
        ar & g.val;
        ar & g.time;
        ar & g.pack;
   };

   template<class Archive>
   void serialize(Archive& ar, data_item_str& g, const unsigned int version) {
        ar & g.sid;
        ar & g.val;
        ar & g.vld;
        ar & g.time;
   };

   template<class Archive>
   void serialize(Archive& ar, req_data_item& g, const unsigned int version) {
        ar & g.stub;
   };

   template<class Archive>
   void serialize(Archive& ar, req_data_item1& g, const unsigned int version) {
        ar & g.sids;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_data_item& g, const unsigned int version) {
        ar & g.lines;
        ar & g.linesstr;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, req_data_item_ex& g, const unsigned int version) {
        ar & g.stub;
   };

   template<class Archive>
   void serialize(Archive& ar, req_data_item_ex1& g, const unsigned int version) {
        ar & g.sids;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_data_item_ex& g, const unsigned int version) {
        ar & g.lines;
        ar & g.strlines;
        ar & g.fulllines;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, command_data& g, const unsigned int version) {
        ar & g.sid;
        ar & g.val;
        ar & g.type;
        ar & g.queue;
        ar & g.valstr;
   };

   template<class Archive>
   void serialize(Archive& ar, req_send_commands& g, const unsigned int version) {
        ar & g.cmds;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_send_commands& g, const unsigned int version) {
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, reporttask& g, const unsigned int version) {
        ar & g.sid;
        ar & g.start;
        ar & g.stop;
   };

   template<class Archive>
   void serialize(Archive& ar, report_value_item& g, const unsigned int version) {
        ar & g.val;
        ar & g.time;
   };

   template<class Archive>
   void serialize(Archive& ar, report_value_data& g, const unsigned int version) {
        ar & g.sid;
        ar & g.data;
   };

   template<class Archive>
   void serialize(Archive& ar, req_reporttask& g, const unsigned int version) {
        ar & g.tasks;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_reporttask& g, const unsigned int version) {
        ar & g.datas;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, event_value_item& g, const unsigned int version) {
        ar & g.sid;
        ar & g.val;
        ar & g.time;
   };

   template<class Archive>
   void serialize(Archive& ar, eventtask& g, const unsigned int version) {
        ar & g.sid;
        ar & g.start;
   };

   template<class Archive>
   void serialize(Archive& ar, req_eventtask& g, const unsigned int version) {
        ar & g.tasks;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_eventtask& g, const unsigned int version) {
        ar & g.data;
        ar & g.errors;
   };

   template<class Archive>
   void serialize(Archive& ar, trendtask& g, const unsigned int version) {
        ar & g.sid;
        ar & g.start;
        ar & g.stop;
   };

   template<class Archive>
   void serialize(Archive& ar, trend_value_item& g, const unsigned int version) {
        ar & g.val;
        ar & g.time;
   };

   template<class Archive>
   void serialize(Archive& ar, trend_value_data& g, const unsigned int version) {
        ar & g.sid;
        ar & g.data;
   };

   template<class Archive>
   void serialize(Archive& ar, req_trendtask& g, const unsigned int version) {
        ar & g.tasks;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_trendtask& g, const unsigned int version) {
        ar & g.datas;
        ar & g.errors;
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
   void serialize(Archive& ar, req_alarms& g, const unsigned int version) {
        ar & g.vers;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_alarms& g, const unsigned int version) {
        ar & g.err;
        ar & g.vers;
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
   void serialize(Archive& ar, req_journal& g, const unsigned int version) {
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
   };

   template<class Archive>
   void serialize(Archive& ar, resp_journal& g, const unsigned int version) {
        ar & g.guid;
        ar & g.cursor;
        ar & g.cnt;
        ar & g.lines;
   };

}
}


#endif  /* _NETSTRUCT_RPC_ */
