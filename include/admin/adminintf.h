/* 
 * File:   kernelInterface.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 21 Р”РµРєР°Р±СЂСЊ 2009 Рі., 11:46
 */

#ifndef _ADMININTF_NSADMININTERFACE_H
#define	_ADMININTF_NSADMININTERFACE_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/memfile.h>
#include <kernel/utils.h>
#include <kernel/serviceapp.h>

#include <meta/meta.h>

#include <admin/properties.h>
#include <admin/adminstruct.h>


namespace dvnci {
    namespace admin {

        class adminintf;
        typedef intrusive_sync_share_ptr_tmpl<adminintf> adminintf_ptr;

        typedef std::pair<confproptype, int> confinfo_pair;
        typedef std::map<confproptype, int, std::less<confproptype>, std::allocator<confinfo_pair > > confinfo_map;

        const num64 intrf_ver = 1;

        const num64 MASK_RT_CHANGE_NAME =     0x1;
        const num64 MASK_RT_CHANGE_COMMENT =  0x2;
        const num64 MASK_RT_CHANGE_BINDING =  0x4;
        const num64 MASK_RT_CHANGE_EU =       0x8;
        const num64 MASK_RT_CHANGE_ONMSGTXT = 0x10;
        const num64 MASK_RT_CHANGE_OFFMSGTXT = 0x20;
        const num64 MASK_RT_CHANGE_ALMSGTXT = 0x40;
        const num64 MASK_RT_CHANGE_VALUE =    0x80;
        const num64 MASK_RT_CHANGE_VALUELOG = 0x100;
        const num64 MASK_RT_CHANGE_MINEU =    0x200;
        const num64 MASK_RT_CHANGE_MAXEU =    0x400;
        const num64 MASK_RT_CHANGE_MINRAW =   0x800;
        const num64 MASK_RT_CHANGE_MAXRAW =   0x1000;
        const num64 MASK_RT_CHANGE_LOGDB =    0x2000;
        const num64 MASK_RT_CHANGE_DEVDB =    0x4000;
        const num64 MASK_RT_CHANGE_ALARMCONST = 0x8000;
        const num64 MASK_RT_CHANGE_TIME =     0x10000;
        const num64 MASK_RT_CHANGE_LOGGED =   0x20000;
        const num64 MASK_RT_CHANGE_ONMSG =    0x40000;
        const num64 MASK_RT_CHANGE_OFFMSG =   0x80000;
        const num64 MASK_RT_CHANGE_ALMSG =    0x100000;
        const num64 MASK_RT_CHANGE_REFCNT =   0x200000;
        const num64 MASK_RT_CHANGE_RW =       0x400000;
        const num64 MASK_RT_CHANGE_TYPE =     0x800000;
        const num64 MASK_RT_CHANGE_TIMELOG =  0x1000000;
        const num64 MASK_RT_CHANGE_LOCALMSG = 0x2000000;
        const num64 MASK_RT_CHANGE_ALLEVEL =  0x4000000;
        const num64 MASK_RT_CHANGE_ALWACTIVE =  0x8000000;
        const num64 MASK_RT_CHANGE_ERROR =    0x10000000;
        const num64 MASK_RT_CHANGE_GROUP =    0x20000000;
        const num64 MASK_RT_CHANGE_AGROUP =   0x40000000;
        const num64 MASK_RT_CHANGE_ALCASE =   0x80000000;
        const num64 MASK_RT_CHANGE_REPPER =   0x100000000LL;
        const num64 MASK_RT_CHANGE_DELT =     0x200000000LL;
        const num64 MASK_RT_CHANGE_STAT =     0x400000000LL;
        const num64 MASK_RT_CHANGE_ACCESSL =  0x800000000LL;
        const num64 MASK_RT_CHANGE_RANG =    0x1000000000LL;

        const num64 MASK_RT_EXPORT1 =   0x86DEFE7F;


        const num64 MASK_GR_CHANGE_NAME =     0x1;
        const num64 MASK_GR_CHANGE_APPID =    0x2;
        const num64 MASK_GR_CHANGE_CHTYPE =   0x4;
        const num64 MASK_GR_CHANGE_CHNUM =    0x8;
        const num64 MASK_GR_CHANGE_CHDEVNUM = 0x10;
        const num64 MASK_GR_CHANGE_DEVNUM =   0x20;
        const num64 MASK_GR_CHANGE_CONFIG =   0x40;
        const num64 MASK_GR_CHANGE_TO =       0x80;
        const num64 MASK_GR_CHANGE_DB =       0x100;
        const num64 MASK_GR_CHANGE_GR =       0x200;
        const num64 MASK_GR_CHANGE_SYNCT =    0x400;
        const num64 MASK_GR_CHANGE_BS =       0x800;
        const num64 MASK_GR_CHANGE_ABS =      0x1000;
        const num64 MASK_GR_CHANGE_TCNT =     0x2000;
        const num64 MASK_GR_CHANGE_INDTO =    0x4000;
        const num64 MASK_GR_CHANGE_HOST  =    0x8000;
        const num64 MASK_GR_CHANGE_USER  =    0x10000;
        const num64 MASK_GR_CHANGE_PASS  =    0x20000;
        const num64 MASK_GR_CHANGE_SERVER  =    0x40000;
        const num64 MASK_GR_CHANGE_GROUP   =    0x80000;
        const num64 MASK_GR_CHANGE_PORT    =    0x100000;
        const num64 MASK_GR_CHANGE_TOPIC    =   0x200000;
        const num64 MASK_GR_CHANGE_ETHER    =   0x400000;
        const num64 MASK_GR_CHANGE_LOCAL   =    0x800000;
        const num64 MASK_GR_CHANGE_SYNCTYPE =   0x1000000;
        const num64 MASK_GR_CHANGE_VER      =   0x2000000;
        const num64 MASK_GR_CHANGE_SUPTP    =   0x4000000;

        const num64 MASK_GR_EXPORT1 =   0x7F;

        const num64 MASK_AGR_CHANGE_NAME =       0x1;
        const num64 MASK_AGR_CHANGE_HEADNAME =       0x2;

        const num64 MASK_AGR_EXPORT1 =   0x1;

        const num64 MASK_USER_CHANGE_NAME =      0x1;
        const num64 MASK_USER_CHANGE_PASSWORD =  0x4;
        const num64 MASK_USER_CHANGE_LEVEL =     0x8;
        const num64 MASK_USER_CHANGE_FILTER =    0x10;
        const num64 MASK_USER_CHANGE_ROLE   =    0x20;

        const num64 MASK_USER_EXPORT1 =   0xF;

        const num64 MASK_SV_CHANGE_NAME =     0x1;
        const num64 MASK_SV_CHANGE_PATH =    0x2;
        const num64 MASK_GR_CHANGE_DEPEND =   0x4;
        const num64 MASK_GR_CHANGE_STARTTP =   0x20;
        const num64 MASK_GR_CHANGE_STATUS =   0x40;


        const num64 MASK_AR_CHANGE_NAME =     0x1;
        const num64 MASK_AR_CHANGE_USER =    0x2;
        const num64 MASK_AR_CHANGE_HOST =   0x4;
        const num64 MASK_AR_CHANGE_APPID =    0x8;
        const num64 MASK_AR_CHANGE_RULE =   0x10;
        const num64 MASK_AR_CHANGE_AL =   0x20;
        const num64 MASK_AR_CHANGE_FILTER =    0x40;
        const num64 MASK_AR_CHANGE_ROLE =    0x80;
        const num64 MASK_AR_CHANGE_PROT =    0x100;


        const num64 OPERATION_INCCOUNTALL = 0x32;
        const num64 OPERATION_DECCOUNTALL = 0x33;
        const num64 OPERATION_SETALL_VALID = 0x34;
        const num64 OPERATION_SETALL_INVALID = 0x35;
        const num64 OPERATION_ACTION_KVIT = 0x36;
        const num64 OPERATION_KVIT_GROUP = 0x37;
        const num64 OPERATION_KVIT_AGROUP = 0x38;
        const num64 OPERATION_INCCOUNT = 0x39;
        const num64 OPERATION_DECCOUNT = 0x3A;
        const num64 OPERATION_SET_VALID = 0x3B;
        const num64 OPERATION_SET_INVALID = 0x3C;
        const num64 OPERATION_SET_VALUE = 0x3D;
        const num64 OPERATION_SET_COMMAND = 0x3E;
        const num64 OPERATION_SERVICE_START = 0x40;
        const num64 OPERATION_SERVICE_STOP = 0x41;


        iteminfo_map & operator<<(iteminfo_map& ls, const resp_entitysigs& rs) ;

        typedef std::pair<indx, tag_data > indx_tags_pair;
        typedef std::map<indx, tag_data , std::less<indx>, std::allocator<indx_tags_pair > > indx_tags_map;
        req_tags & operator<<(req_tags& rs, const indx_set& ls);
        indx_tags_map & operator<<(indx_tags_map& ls, const resp_tags& rs);
        indx_tags_map & operator<<(indx_tags_map& ls, const resp_sendtags& rs);


        typedef std::pair<indx, group_data > indx_groups_pair;
        typedef std::map<indx, group_data, std::less<indx>, std::allocator<indx_groups_pair > > indx_groups_map;
        req_groups & operator<<(req_groups& rs, const indx_set& ls);
        indx_groups_map & operator<<(indx_groups_map& ls, const resp_groups& rs);
        indx_groups_map & operator<<(indx_groups_map& ls, const resp_sendgroups& rs);


        typedef std::pair<indx, agroup_data > indx_agroups_pair;
        typedef std::map<indx, agroup_data, std::less<indx>, std::allocator<indx_agroups_pair > > indx_agroups_map;
        req_agroups & operator<<(req_agroups& rs, const indx_set& ls);
        indx_agroups_map & operator<<(indx_agroups_map& ls, const resp_agroups& rs);
        indx_agroups_map & operator<<(indx_agroups_map& ls, const resp_sendagroups& rs);


        typedef std::pair<indx, accessrule_data > indx_accessrules_pair;
        typedef std::map<indx, accessrule_data, std::less<indx>, std::allocator<indx_accessrules_pair > > indx_accessrules_map;
        req_accessrules & operator<<(req_accessrules& rs, const indx_set& ls);
        indx_accessrules_map & operator<<(indx_accessrules_map& ls, const resp_accessrules& rs);
        indx_accessrules_map & operator<<(indx_accessrules_map& ls, const resp_sendaccessrules& rs);

        typedef std::pair<indx, user_data > indx_users_pair;
        typedef std::map<indx, user_data, std::less<indx>, std::allocator<indx_users_pair > > indx_users_map;
        req_users & operator<<(req_users& rs, const indx_set& ls);
        indx_users_map & operator<<(indx_users_map& ls, const resp_users& rs);
        indx_users_map & operator<<(indx_users_map& ls, const resp_sendusers& rs);

        typedef std::pair<indx, meta_data > indx_metaitem_pair;
        typedef std::map<indx, meta_data, std::less<indx>, std::allocator<indx_metaitem_pair > > indx_metaitem_map;

        typedef std::pair<nodetype, indx_metaitem_map > nodetype_metamap_pair;
        typedef std::map<nodetype, indx_metaitem_map, std::less<nodetype>, std::allocator<nodetype_metamap_pair > > entitytype_metamaps_maps;

        typedef std::pair<std::string, int > propertymeta_ids_pair;
        typedef std::map<std::string, int , std::less<std::string>, std::allocator<propertymeta_ids_pair > > propertymeta_ids_map;

        typedef std::pair<nodetype, propertymeta_ids_map > nodetype_metaidsmap_pair;
        typedef std::map<nodetype, propertymeta_ids_map , std::less<nodetype>, std::allocator<nodetype_metaidsmap_pair > > nodetype_metaidsmap_map;
        req_metas & operator<<(req_metas& rs, const indx_set& ls);

        typedef std::pair<indx, service_data > indx_services_pair;
        typedef std::map<indx, service_data, std::less<indx>, std::allocator<indx_services_pair > > indx_services_map;
        req_services & operator<<(req_services& rs, const indx_set& ls);
        indx_services_map & operator<<(indx_services_map& ls, const resp_services& rs);
        indx_services_map & operator<<(indx_services_map& ls, const resp_sendservices& rs);

        req_config & operator<<(req_config& rs, const indx_set& ls);
        confinfo_map & operator<<(confinfo_map& rs, const resp_config& ls);

        class tagintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            tagintf() {};

            virtual ~tagintf() {}
            virtual void   key(indx val) = 0;
            virtual indx key() const = 0;
            virtual ptagstruct _struct() = 0;
            virtual void   value(const std::string& val) = 0;
            virtual std::string value() const = 0;
            virtual std::string value_log() const = 0;
            virtual void   mineu(const std::string& val) = 0;
            virtual std::string mineu() const = 0;
            virtual void   maxeu(const std::string& val) = 0;
            virtual std::string maxeu() const = 0;
            virtual void   minraw(const std::string& val) = 0;
            virtual std::string minraw() const  = 0;
            virtual void   maxraw(const std::string& val) = 0;
            virtual std::string maxraw() const = 0;
            virtual void   logdb(const std::string& val) = 0;
            virtual std::string logdb() const = 0;
            virtual void   devdb(const std::string& val) = 0;
            virtual std::string devdb() const = 0;
            virtual void   alarmconst(const std::string& val) = 0;
            virtual std::string alarmconst() const = 0;
            virtual void   name(const std::string& val) = 0;
            virtual std::string  name() const = 0;
            virtual void   comment(const std::string& val) = 0;
            virtual std::string  comment() const = 0;
            virtual void   binding(const std::string& val) = 0;
            virtual std::string  binding() const = 0;
            virtual void   eu(const std::string& val) = 0;
            virtual std::string  eu() const = 0;
            virtual void   onmsg(const std::string& val) = 0;
            virtual std::string  onmsg() const = 0;
            virtual void   offmsg(const std::string& val) = 0;
            virtual std::string  offmsg() const = 0;
            virtual void   alarmmsg(const std::string& val) = 0;
            virtual std::string  alarmmsg() const = 0;
            virtual void   logged(bool val) = 0;
            virtual bool   logged() const = 0;
            virtual void   onmsged(bool val) = 0;
            virtual bool   onmsged() const = 0;
            virtual void   offmsged(bool val) = 0;
            virtual bool   offmsged() const = 0;
            virtual bool   alarmed() const = 0;
            virtual bool   alarmon() const = 0;
            virtual bool   alarmkvit() const = 0;
            virtual acclevtype   accesslevel() const = 0;
            virtual void accesslevel(acclevtype val) = 0;
            virtual std::string   time() const = 0;
            virtual std::string   time_log() const = 0;
            virtual vlvtype valid() const = 0;
            virtual onum   refcnt() const = 0;
            virtual void   type(tagtype val) = 0;
            virtual tagtype type() const = 0;
            virtual void   alarmlevel(altype val) = 0;
            virtual altype   alarmlevel() const = 0;
            virtual void   alwactive(bool val) = 0;
            virtual bool   alwactive() const = 0;
            virtual void   rangable(bool val) = 0;
            virtual bool   rangable() const = 0;
            virtual ns_error  error() const = 0;
            virtual indx  group() const = 0;
            virtual void  group(indx val) = 0;
            virtual indx  agroup() const = 0;
            virtual void  agroup(indx val) = 0;
            virtual void  alarmcase(alcstype val) = 0;
            virtual alcstype  alarmcase() const = 0;
            virtual void   rwtype(acstgtype val) = 0;
            virtual acstgtype  rwtype() const = 0;
            virtual void   reporthistory(reporthisttype val) = 0;
            virtual reporthisttype  reporthistory() const = 0;
            virtual void   reportsubdelt(reporthistdelt val) = 0;
            virtual reporthistdelt  reportsubdelt() const = 0;
            virtual void   reportstatistic(repstattype val) = 0;
            virtual repstattype  reportstatistic() const = 0;} ;

        class groupintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            groupintf() {};

            virtual ~groupintf() {}
            virtual void  key(indx val) = 0;
            virtual indx key() const = 0;
            virtual pgroupstruct _struct() = 0 ;
            virtual void   name(const std::string& val) = 0;
            virtual std::string  name() const = 0;
            virtual void   host(const std::string& val) = 0;
            virtual std::string  host() const = 0;
            virtual void   user(const std::string& val) = 0;
            virtual std::string  user() const = 0;
            virtual void   password(const std::string& val) = 0;
            virtual std::string  password() const = 0;
            virtual void   server(const std::string& val) = 0;
            virtual std::string  server() const = 0;
            virtual void   group(const std::string& val) = 0;
            virtual std::string  group() const = 0;
            virtual void   port(const std::string& val) = 0;
            virtual std::string  port() const = 0;
            virtual void   topic(const std::string& val) = 0;
            virtual std::string  topic() const = 0;
            virtual void   ether(const std::string& val) = 0;
            virtual std::string  ether() const = 0;
            virtual void   appid(appidtype val) = 0;
            virtual appidtype appid() const = 0;
            virtual void   chanaltype(chnltype val) = 0;
            virtual chnltype chanaltype() const = 0;
            virtual void   chanalnum(chnlnumtype val) = 0;
            virtual chnlnumtype chanalnum() const = 0;
            virtual void   devnum(devnumtype val) = 0;
            virtual devnumtype devnum() const = 0;
            virtual void   protocol(protocoltype val) = 0;
            virtual protocoltype protocol() const = 0;
            virtual void   timeout(timeouttype val) = 0;
            virtual timeouttype timeout() const = 0;
            virtual void   deadbound(double val) = 0;
            virtual double deadbound() const = 0;
            virtual void   grouprate(gratetype val) = 0;
            virtual gratetype grouprate() const = 0;
            virtual void   trycount(size_t val) = 0;
            virtual size_t trycount() const = 0;
            virtual void   blocksize(blksizetype val) = 0;
            virtual blksizetype blocksize() const = 0;
            virtual void   archblocksize(blksizetype val) = 0;
            virtual blksizetype archblocksize() const = 0;
            virtual void   utiloperation(bool val) = 0;
            virtual bool utiloperation() const = 0;
            virtual void   indicateto(timeouttype val) = 0;
            virtual timeouttype indicateto() const = 0;
            virtual lcltype local() const = 0;
            virtual void local(lcltype val ) = 0;
            virtual subcripttype synctype() const = 0;
            virtual void synctype(subcripttype val ) = 0;
            virtual intfvertype ver() const = 0;
            virtual void ver(intfvertype val ) = 0;
            virtual bool supporttype() const = 0;
            virtual void supporttype(bool val ) = 0;
            virtual void   config(void* val) = 0;
            virtual const void*  config() const = 0;
            virtual bool   active() const = 0;
            virtual vlvtype valid() const = 0;
            virtual ns_error error() const = 0;} ;

        class agroupintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            agroupintf() {};

            virtual ~agroupintf() {};
            virtual void  key(indx val) = 0;
            virtual indx key() const = 0;
            virtual pagroupstruct _struct() = 0;
            virtual void   name(const std::string& val) = 0;
            virtual std::string  name() const = 0;
            virtual void   headername(const std::string& val) = 0;
            virtual std::string  headername() const = 0;} ;

        class userintf {
            
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            userintf() {};

            virtual ~userintf() {};
            virtual void  key(indx val) = 0;
            virtual indx key() const = 0;
            virtual void   name(const std::string& val)  = 0;
            virtual std::string  name() const = 0;
            virtual void   password(const std::string& val) = 0;
            virtual std::string  password() const = 0;
            virtual void   filter(const std::string& val) = 0;
            virtual std::string filter() const = 0; 
            virtual void   accesslevel(acclevtype val) = 0;
            virtual acclevtype accesslevel() const = 0;
            virtual void   role(rolesettype val) = 0;
            virtual rolesettype role() const = 0;};


        class accessruleintf {
            
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            accessruleintf() {};

            virtual ~accessruleintf() {};
            virtual void  key(indx val) = 0;
            virtual indx key() const = 0;
            virtual void   name(const std::string& val) = 0;
            virtual std::string  name() const = 0;
            virtual void   user(const std::string& val) = 0;
            virtual std::string  user() const = 0;
            virtual void   host(const std::string& val) = 0;
            virtual std::string host() const = 0;
            virtual void   filter(const std::string& val) = 0;
            virtual std::string filter() const = 0;
            virtual void   appid(appidtype val) = 0;
            virtual appidtype appid() const = 0;
            virtual void   protocol(protocoltype val) = 0;
            virtual protocoltype protocol() const = 0;
            virtual void   accessrule(accessruletype val) = 0;
            virtual accessruletype accessrule() const = 0;
            virtual void   accesslevel(acclevtype val) = 0;
            virtual acclevtype accesslevel() const = 0;
            virtual void   role(rolesettype val) = 0;
            virtual rolesettype role() const = 0;};
            
            
            

        class metaintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:
            metaintf();

            virtual ~metaintf() {}

            virtual void  key(nodetype tp, indx val) {};

            virtual std::string  property( const std::string&  prop) const {
                return "";};

            virtual void  property(const std::string& prop, std::string  val) {};

            int propertyid(const std::string& val) const {
                propertymeta_ids_map::const_iterator it = propertymeta_ids.find(val);
                if (it == propertymeta_ids.end()) return -1;
                return it->second;}

            propertymeta_ids_map* propertymap(nodetype val) {
                nodetype_metaidsmap_map::iterator it = metaidsmap_map.find(val);
                if (it == metaidsmap_map.end()) return 0;
                return &it->second;}

        protected:
            propertymeta_ids_map propertymeta_ids;
            nodetype_metaidsmap_map metaidsmap_map;} ;

        template<typename T>
        class liveviewintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        protected:

            typedef std::vector< T , std::allocator<T > >                                 type_vect;
            typedef typename type_vect::iterator                                          type_vect_iterator;
            typedef typename type_vect::const_iterator                                    type_vect_const_iterator;

        public:

            liveviewintf() : version_(0), number_(npos) {};

            virtual ~liveviewintf() {};

            size_t count() const {
                return vect.size();}

            guidtype version() const {
                return version_;};

            void  number(indx val) {
                number_ = val;};

            indx number() const {
                return number_;};

            bool exists() const {
                return (viewindex() < vect.size());}

        protected:

            indx viewindex() const {
                return (number_);}

            guidtype        version_;
            indx            number_;
            type_vect       vect;

            void assign_data(type_vect&  vct) const {
                vct = vect;}} ;

        class alarmsintf : public liveviewintf<alarms_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            alarmsintf() : liveviewintf<alarms_data>() {};

            virtual ~alarmsintf() {};

            std::string time() const {
                return exists() ? datetime_to_string(vect[viewindex()].time) : "";}

            num64 time_num64() const {
                return exists() ? num64_cast<datetime>(vect[viewindex()].time) : 0;}

            std::string tag() const {
                return exists() ? vect[viewindex()].tag : "";}

            std::string text() const {
                return exists() ? vect[viewindex()].text : "";}

            bool  kvit() const {
                return exists() ? static_cast<bool> (vect[viewindex()].kvit) : false;}

            bool   off() const {
                return false;}

            altype level() const {
                return exists() ? static_cast<altype> (vect[viewindex()].level) : 0;}

            msgtype type() const {
                return exists() ? static_cast<msgtype> (vect[viewindex()].type) : 0;}

            std::string value() const {
                return exists() ? vect[viewindex()].value : "";};

        protected:

            virtual size_t load(const std::string& agroup = "", const std::string& group = "") = 0;} ;

        class commandintf : public liveviewintf<commands_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            commandintf()  : liveviewintf<commands_data>() {};

            virtual ~commandintf() {}

            std::string time() const {
                return exists() ? datetime_to_string(vect[viewindex()].time) : "";}

            num64 time_num64() const {
                return exists() ? num64_cast<datetime>(vect[viewindex()].time) : 0;}

            std::string tag() const {
                return exists() ? vect[viewindex()].tag : "";}

            std::string group() const {
                return exists() ? vect[viewindex()].group : "";}

            std::string value() const {
                return exists() ? vect[viewindex()].value : "";}

            std::string valuebefore() const {
                return exists() ? vect[viewindex()].valuebefore : "";}

            std::string user() const {
                return exists() ? vect[viewindex()].user : "";}

            std::string host() const {
                return exists() ? vect[viewindex()].host : "";}

            bool   executed()  const {
                return false;}

        protected:

            virtual size_t load(const std::string& group = "") = 0;} ;

        class registryintf : public liveviewintf<registry_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            registryintf()  : liveviewintf<registry_data>() {};

            virtual ~registryintf() {}

            guidtype handle() const {
                return exists() ? static_cast<guidtype> (vect[viewindex()].handle) : 0;}

            guidtype queuehandle() const {
                return exists() ? static_cast<guidtype> (vect[viewindex()].queuehandle) : 0;}

            appidtype appid() const {
                return exists() ? static_cast<appidtype> (vect[viewindex()].appid) : 0;}

            eventtypeset evset() const {
                return exists() ? static_cast<eventtypeset> (vect[viewindex()].eventset) : 0;}

            std::string  name() const {
                return exists() ? ("application." + to_str(static_cast<appidtype> (vect[viewindex()].appid))) : "";}

        protected:

            virtual size_t load() = 0;} ;

        class clientsintf  : public liveviewintf<clients_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            clientsintf()  : liveviewintf<clients_data>() {};

            virtual ~clientsintf() {}

            std::string  name() const {
                return exists() ? vect[viewindex()].name : "";}

            std::string  host() const {
                return exists() ? vect[viewindex()].host : "";}

            std::string  ip() const {
                return exists() ? vect[viewindex()].ip : "";}

            std::string  user() const {
                return exists() ? vect[viewindex()].user : "";}

            indx ruleid() const {
                return exists() ? static_cast<indx> (vect[viewindex()].ruleid) : 0;}

            acclevtype accesslevel() const {
                return exists() ? static_cast<acclevtype> (vect[viewindex()].accesslevel) : 0;
                ;}

            appidtype appid() const {
                return exists() ? static_cast<appidtype> (vect[viewindex()].appid) : 0;}


        protected:

            virtual size_t load() = 0;} ;

        template<typename T>
        class cyclicviewintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        protected:

            typedef const T*                                                              const_type_ptr;

            typedef std::pair<indx, T >                                                   indx_type_pair;
            typedef std::map<indx, T , std::less<indx>, std::allocator<indx_type_pair > > indx_type_map;
            typedef typename indx_type_map::iterator                                      indx_type_map_iterator;
            typedef typename indx_type_map::const_iterator                                indx_type_map_const_iterator;

            typedef std::vector< T , std::allocator<T > >                                 type_vect;
            typedef typename type_vect::iterator                                          type_vect_iterator;
            typedef typename type_vect::const_iterator                                    type_vect_const_iterator;

        public:

            cyclicviewintf() : number_(npos), cursor_(0), count_(0) , guid_(0) {}

            virtual ~cyclicviewintf() {}

            size_t mapcount() const {
                return mapdata.size();}

            size_t count() const {
                return count_;}

            guidtype guid() const {
                return guid_;}

            size_t viewtop() const {
                return viewtop_;}

            void viewtop(size_t val) {
                viewtop_ = val;}

            size_t cursor() const {
                return cursor_;}

            void  number(indx val) {
                number_ = val;};

            indx number() const {
                return number_;};

            bool exists() const {
                return mapdata.find(viewindex()) != mapdata.end();}


        protected:

            indx viewindex() const {
                if (!(number_<count_)) return npos;
                return (cursor_ > number_) ? cursor_ - 1 - number_ : count_ + cursor_ - 1 - number_;}

            const_type_ptr item() const {
                indx_type_map_const_iterator it = mapdata.find(viewindex());
                return (it != mapdata.end()) ? &it->second : 0;}

            void filldata(const type_vect& src) {
                for (type_vect_const_iterator it = src.begin(); it != src.end(); ++ it) {
                    indx_type_map_iterator itdata=mapdata.find(static_cast<indx> (it->index));
                    if (itdata != mapdata.end())
                        itdata->second=*it;
                    else
                        mapdata.insert(indx_type_pair(static_cast<indx> (it->index), *it));}}

            indx             number_;
            size_t           cursor_;
            size_t           count_;
            size_t           viewtop_;
            guidtype         guid_;
            indx_type_map    mapdata;

        protected:

            virtual size_t assign_data(type_vect& vct) {
                return 0;}} ;

        class journalintf : public cyclicviewintf<journal_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            journalintf() : cyclicviewintf<journal_data>() {}

            virtual ~journalintf() {}

            std::string time() const {
                return exists() ? datetime_to_string(item()->time) : "";}

            num64 time_num64() const {
                return exists() ? num64_cast<datetime>(item()->time) : 0;}

            std::string tag() const {
                return exists() ? item()->tag : "";}

            std::string agroup() const {
                return exists() ? item()->agroup : "";}

            std::string text() const {
                return exists() ? item()->text : "";}

            altype level() const {
                return exists() ? static_cast<altype> (item()->level) : 0;}

            msgtype type() const {
                return exists() ? static_cast<msgtype> (item()->type) : 0;}

            std::string value() const {
                return exists() ? item()->value : "";};

            std::string user() const {
                return exists() ? item()->user : "";};

        protected:

            virtual size_t load(const std::string& agroup = "") = 0;} ;

        class debugintf : public cyclicviewintf<debug_data> {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            debugintf() : cyclicviewintf<debug_data>() {};

            virtual ~debugintf() {}

            std::string time() const {
                return exists() ? datetime_to_string(item()->time) : "";}

            num64 time_num64() const {
                return exists() ? num64_cast<datetime>(item()->time) : 0;}

            std::string  message() const {
                return exists() ? item()->message : "";}

            appidtype  appid() const {
                return exists() ? static_cast<appidtype> (item()->appid) : 0;}

            debuglvtype   level()  const {
                return exists() ? static_cast<debuglvtype> (item()->level) : 0;}

        protected:

            virtual size_t load(debuglvtype lev = 0) = 0;} ;

        class serviceintf {
            friend class adminintf;
            friend class remoteadminintf;
            friend class localadminintf;

        public:

            serviceintf() {};

            virtual ~serviceintf() {};

            virtual void  number(indx val) = 0;
            virtual indx number()  const = 0;
            virtual std::string displayname()   const = 0;
            virtual std::string path() const = 0;
            virtual num64 starttype() const = 0;
            virtual void starttype(num64 val)  = 0;
            virtual num64 status()    const = 0;
            virtual void status(num64 val)    = 0;} ;

        class adminintf {
            friend class tagintf;
            friend class groupintf;
            friend class agroupintf;
            friend class userintf;
            friend class metaintf;
            friend class accessruleintf;
            friend class journalintf;
            friend class debugintf;
            friend class registryintf;
            friend class alarmsintf;
            friend class clientsintf;
            friend class commandintf;
            friend class serviceintf;

            friend class localtagintf;
            friend class localgroupintf;
            friend class localagroupintf;
            friend class localuserintf;
            friend class localmetaintf;
            friend class localaccessruleintf;
            friend class localjournalintf;
            friend class localdebugintf;
            friend class localregistryintf;
            friend class localalarmsintf;
            friend class localclientsintf;
            friend class localcommandintf;
            friend class localserviceintf;

            friend class romotetagintf;
            friend class remotegroupintf;
            friend class remoteagroupintf;
            friend class remoteuserintf;
            friend class remotemetaintf;
            friend class remoteaccessruleintf;
            friend class remotejournalintf;
            friend class remotedebugintf;
            friend class remoteregistryintf;
            friend class remotealarmsintf;
            friend class remoteclientsintf;
            friend class remotecommandintf;
            friend class remoteserviceintf;

            friend class adminsession;
            //friend class intrusive_sync_share_ptr_tmpl<adminintf>;

            typedef          boost::mutex                 &mutex_ref;

        public:

            typedef boost::shared_ptr<tagintf> tagintf_ptr;
            typedef boost::shared_ptr<groupintf> groupintf_ptr;
            typedef boost::shared_ptr<agroupintf> agroupintf_ptr;
            typedef boost::shared_ptr<userintf> userintf_ptr;
            typedef boost::shared_ptr<accessruleintf> accessruleintf_ptr;
            typedef boost::shared_ptr<journalintf> journalintf_ptr;
            typedef boost::shared_ptr<alarmsintf> alarmsintf_ptr;
            typedef boost::shared_ptr<registryintf> registryintf_ptr;
            typedef boost::shared_ptr<clientsintf> clientsintf_ptr;
            typedef boost::shared_ptr<commandintf> commandintf_ptr;
            typedef boost::shared_ptr<debugintf> debugintf_ptr;
            typedef boost::shared_ptr<metaintf> metaintf_ptr;
            typedef boost::shared_ptr<serviceintf> serviceintf_ptr;

            enum interfacestate {
                disconnected , connected} ;

            adminintf();

            virtual ~adminintf() {};
            
            virtual void setaddress(const boost::asio::ip::address& adr){}

            bool isautorizated() const {
                return isautorizated_;}

            virtual bool islocal() const {
                return true;}

            virtual std::string named() const {
                return "maintree.local";}

            virtual void fullnamed(const std::string& val) {
                split_2str(val, ":", adminname, adminpassword);}

            virtual std::string fullnamed() const {
                return (adminname + ":" + adminpassword);}

            virtual bool connect(const std::string& user = "", const std::string& password = "") = 0;

            virtual bool disconnect() = 0;

            interfacestate state() {
                return _state;}

            ns_error error() const {
                return _error;}

            virtual lcltype locale() const {
                return locale_;}

            /**
             * Запрашивает сигнатуры дочерних объектов для некоторой родительской сущности
             * @param parenttp тип родителя для дочерних объектов см. kernel/constdef.h,
             * -1 !!! все дочерние для данного типа (предпологаетя 0, при переходе на недействительный
             * нулевой индекс)
             * @param parentid уникальный индекс родителя
             * @param mappack карта в которой возвращаются сигнатуры
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации
             * @return  успешность выполнения / не используется
             * @see kernel/constdef.h nodetype
             */
            virtual ns_error select_entities(nodetype parenttp,  iteminfo_map& mappack,  indx parentid,
                    const std::string&  strcriteria = "" , bool clearer = true) {
                if ((parenttp == NT_ROOT_NODEF) || (parenttp == NT_ROOT_SERVERS_AVAIL) || (parenttp == NT_ROOT_SERVERS_AVAIL_R) ||
                        (parenttp == NT_UTIL_MAINTABLE) ||  (parenttp == NT_UTIL_GROUPTABLE)
                        || (parenttp == NT_UTIL_FINDER)) {
                    getgroupdata();
                    getagroupdata();}
                return NS_ERROR_SUCCESS;}

            /**
             * Поиск сигнатур сущностей по некоторым критериям
             * @param ittp тип  айтемсов см. kernel/constdef.h
             * @param map_ карта в которой возвращаются сигнатуры
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации
             * @return  успешность выполнения
             * @see
             */
            virtual ns_error find_entities(nodetype ittp, iteminfo_map& mappack,  std::string  strcriteria = "" ) {
                //THD_EXCLUSIVE_LOCK(mutex);

                mappack.clear();
                if (nodetp_paren_by_child(ittp) != 0) {
                    select_entities(nodetp_paren_by_child(ittp),  mappack, npos,
                            strcriteria );}
                return NS_ERROR_SUCCESS;}
            
            /**
             * Метод entity_create добавляет новый айтемс в базу конфигурацмм
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param parentid уникальный индекс родителя нового айтемса
             * @param pairpack добавленный айтемс
             * @param newnm  имя новой сущьности
             * @param numcriteria передается критерий перезаись/ запрет перезаписи
             * CRITERIA_REWRITE / CRITERIA_NO_REWRITE
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */
            virtual ns_error insert_entity(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
                    std::string  newnm = "" ) {
                if (ittp == NT_GROUP) getgroupdata();
                if (ittp == NT_AGROUP) getagroupdata();
                return NS_ERROR_SUCCESS;}

            /**
             * Метод entity_create добавляет новый айтемс в базу конфигурацмм
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param parentid уникальный индекс родителя нового айтемса
             * @param pairpack добавленный айтемс
             * @param newnm  имя новой сущьности
             * @param numcriteria передается критерий перезаись/ запрет перезаписи
             * CRITERIA_REWRITE / CRITERIA_NO_REWRITE
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */
            virtual ns_error insert_entities(nodetype ittp, indx parentid, str_indx_map& mpnew) {
                return NS_ERROR_SUCCESS;}            

            /**
             * Метод entities_load загружает в буфер полную информацию о айтемсах
             * Реализуется только в удаленном интерфейсе, локальный работает с базой напрямую
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации
             * @param idset_ множество уникальных индексов  айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */
            virtual ns_error load_entities(nodetype ittp,  indx_set& idset) = 0;

            ns_error load_entities(nodetype ittp,  iteminfo_map& mappack);

            ns_error load_entity(nodetype ittp,  indx id);

            /**
             * Метод entities_merge отправляет из буфер полную информацию о айтемсах
             * Реализуется только в удаленном интерфейсе, локальный работает с базой напрямую
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param idset множество уникальных индексов  айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */

            virtual ns_error merge_entities(nodetype ittp,  const indx_set& idset , iteminfo_map& mappack) {
                if (ittp == NT_GROUP) getgroupdata();
                if (ittp == NT_AGROUP) getagroupdata();
                return NS_ERROR_SUCCESS;}

            virtual ns_error merge_entities(nodetype ittp,  const indx_set& idset) = 0;

            ns_error merge_entities(nodetype ittp, indx id) {
                indx_set tmp;
                tmp.insert(id);
                return merge_entities(ittp, tmp);}



            /**
             * Метод entities_merge закрепляет изменения айтемсов в базе конфигурацмм
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param idsetмножество ключей, закрепляемых айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */

            /**
             * Метод entities_erase удаляет айтемсы из базы конфигурацмм
             * @param ittp тип  айтемсов см. kernel/constdef.h
             * @param idsetмножество ключей, удаляемых айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */

            virtual ns_error delete_entities(nodetype ittp, const indx_set& idset) {
                if (ittp == NT_GROUP) getgroupdata();
                if (ittp == NT_AGROUP) getagroupdata();
                return NS_ERROR_SUCCESS;}

            /**
             * Метод entities_erase удаляет айтемсы из базы конфигурацмм
             * @param ittp тип  айтемсов см. kernel/constdef.h
             * @param idsetмножество ключей, удаляемых айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */

            virtual ns_error change_parent_entities(nodetype ittp, indx_set& idset, indx parentid) = 0;


            /**
             * Метод duplicate_entity( 
             * @see kernel/constdef.h nodetype
             */

            virtual ns_error duplicate_entity(nodetype ittp,  indx id,  const std::string& newname, iteminfo_pair& pairpack) = 0;
            
            

            virtual void operation_mapprj(std::string path_) {}

            virtual void operation_unmapprj() {}

            virtual void operation_newprj(std::string path_) {};

            /**
             * Метод возвращает интерфейс tagintf доступа к тегу
             *
             * @param   id ключ тега
             * @return  интефейс tagintf
             * @see tagintf
             */
            virtual tagintf& tag(indx id) const {
                tag_->key(id);
                return *tag_;};

            virtual tagintf& tag() const {
                return *tag_;};

            /**
             * Метод возвращает интерфейс groupintf доступа к группе
             *
             * @param  id ключ группы
             * @return  интефейс groupintf
             * @see groupintf
             */
            virtual  groupintf& group(indx id) const {
                group_->key(id);
                return *group_;}

            virtual  groupintf& group() const {
                return *group_;}

            /**
             * Метод возвращает интерфейс agroupintf доступа к группе алармов
             *
             * @param   id ключ группы алармов
             * @return  интефейс agroupintf
             * @see agroupintf
             */
            virtual  agroupintf& agroup(indx id) const {
                agroup_->key(id);
                return *agroup_;}

            virtual  agroupintf& agroup() const {
                return *agroup_;}

            /**
             * Метод возвращает интерфейс userintf доступа к пользователю
             *
             * @param   id ключ пользователя
             * @return  интефейс userintf
             * @see userintf
             */
            virtual  userintf& user(indx id) const {
                users_->key(id);
                return *users_;}

            virtual  userintf& user() const {
                return *users_;}

            /**
             * Метод возвращает интерфейс accessruleintf правил доступа
             *
             * @param   id ключ правила
             * @return  интефейс accessruleintf
             * @see accessruleintf
             */
            virtual  accessruleintf& accessrule(indx id) const {
                accessrules_->key(id);
                return *accessrules_;}

            virtual  accessruleintf& accessrule() const {
                return *accessrules_;}

            /**
             * Метод возвращает интерфейс metaintf доступа к метаинформации
             *
             * @param   tp тип сущности [NT_MF_ROOT....NT_MF_MESSAGE]
             * @param   id ключ сущности
             * @return  интефейс metaintf
             * @see metaintf
             */

            virtual metaintf& meta(nodetype tp, indx id) const {
                clientmeta_->key(tp, id);
                return *clientmeta_;};

            virtual metaintf& meta() const {
                return *clientmeta_;};

            /**
             * Метод возвращает интерфейс к журналу зарегестрированных приложений registryintf
             *
             * @param   id ключ сущности
             * @return  интефейс metaintf
             * @see registryintf
             */

            virtual registryintf& registry(indx id) const  {
                reg_->number(id);
                return *reg_;};

            virtual registryintf& registry() const {
                return *reg_;};

            virtual clientsintf& client(indx id) const  {
                clients_->number(id);
                return *clients_;};

            virtual clientsintf& client() const {
                return *clients_;};

            virtual debugintf& debug(indx id)  const {
                debug_->number(static_cast<indx> (id));
                return *debug_;};

            virtual debugintf& debug() const {
                return *debug_;};

            virtual commandintf& command(indx id) const  {
                command_->number(static_cast<indx> (id));
                return *command_;};

            virtual commandintf& command() const {
                return *command_;};

            virtual journalintf& journal(indx id) const  {
                journal_->number(static_cast<indx> (id));
                return *journal_;};

            virtual journalintf& journal() const  {
                return *journal_;};

            virtual alarmsintf& alarm(indx id)  const {
                alarms_->number(static_cast<indx> (id));
                return *alarms_;};

            virtual alarmsintf& alarm()  const {
                return *alarms_;};

            virtual serviceintf& service(num64 id) const {
                serviceintf_->number(static_cast<indx> (id));
                return *serviceintf_;};

            virtual serviceintf& service() const {
                return *serviceintf_;};

            const iteminfo_map& groupsmap() const {
                return groupsmap_;}

            const iteminfo_map& agroupsmap() const {
                return agroupsmap_;}


            /**
             * Метод loadview загружает в буфер полную информацию для айтемсов журналов
             * Реализуется только в удаленном интерфейсе, локальный работает с базой напрямую
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param set_ множество уникальных индексов  айтемсов
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */


            ns_error read_view(nodetype ittp, const std::string& = "" );

            bool iserror() const {
                return (errmap.size() > 0);}

            virtual std::string  conf_property(const confproptype&  name) const = 0;

            virtual int conf_numproperty(const confproptype&  name) = 0;

            virtual void conf_property(const confproptype&  name, const std::string&  val) = 0;

            virtual void conf_property(const confproptype&  name, int val) = 0;

            /**
             * Метод getexportbase загружает в переменную base полную информацию по базе или инфрмацию для некоторого объекта
             * @param base структура для извлечения информации
             * @param ittp тип  айтемса см. kernel/constdef.h
             * @param idset множество уникальных индексов  айтемсов
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации (передается индекс порождающего объекта)
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */
            bool getexportbase(base_data& base, nodetype itemtype,
                    const std::string&  strcriteria,  indx partid );
            /**
             * Метод setimportbase импортирует в базу  информацию из переменной bаse
             * @param base структура для извлечения информации
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации
             * @return  успешность выполнения
             * @see kernel/constdef.h nodetype
             */
            bool setimportbase(base_data& base, const std::string&  strcriteria = "");

            /**
             * Метод operation_setvalue устанавливает значение тега с индексом id
             * @param id индекс тега
             * @param val новое значение тега
             * @param valid валидность
             * @return  тег существует
             */
            virtual bool operation_setvalue(indx id, const std::string& val, vlvtype valid) = 0;

            /**
             * Метод operation_setvalid устанавливает валидность тега с индексом id
             * @param id индекс тега
             * @param valid валидность
             * @return  тег существует
             */
            virtual bool operation_setvalid(indx id, vlvtype valid) = 0;

            /**
             * Метод operation_setallvalid устанавливает валидность всех тегов базы
             * @param valid валидность
             * @return  всегда истина
             */
            virtual bool operation_setallvalid(vlvtype valid) = 0;


            /**
             * Метод operation_setcounter уменьшает или увеличивает количество ссылок на тег
             * @param id индекс тега
             * @param inc истина - увеличение, ложь - уменьшение
             * @return  тег существует
             */
            virtual bool operation_setcounter(indx id, bool inc = true) = 0;

            /**
             * Метод operation_setcounter уменьшает или увеличивает количество ссылок на теги всей базы
             * @param inc истина - увеличение, ложь - уменьшение
             * @return  всегда истина
             */
            virtual bool operation_setallcounter(bool inc = true) = 0;

            /**
             * Метод kvit общее квитирование
             * @return  всегда истина
             */
            virtual bool operation_kvit() = 0;

            /**
             * Метод kvit квитирование группы
             * @param id индекс группы
             * @return  всегда истина
             */
            virtual bool operation_kvitgroup(indx id) = 0;


            /**
             * Метод kvit квитирование алармовой группы
             * @param id индекс алармовой группы
             * @return  всегда истина
             */
            virtual bool operation_kvitagroup(indx id) = 0;

            /**
             * Метод kvit квитирование алармовой группы
             * @param id индекс тега
             * @param val новое значение тега
             * @param setqueue поставить в очередь команд
             * @return  тег существует
             */
            virtual bool     operation_send_command(indx id, std::string val, bool setqueue = true) {
                return true;}

            virtual bool     operation_startservice(appidtype val) = 0;

            virtual bool     operation_stopservice(appidtype val) = 0;

            virtual ns_error operation_autorizate(const std::string& user = "", const std::string& password = "") = 0;

            virtual void     host(std::string host_, std::string port_, unsigned int timout = DEFAULT_DVNCI_TIMOUT) {}


            int_dvncierror_map errors(bool clear = true) {
                if (!clear) return errmap;
                int_dvncierror_map tmp = errmap;
                clearerrors();
                return tmp;}

            boost::mutex* mtx_internal() {
                return &mutex;}

        protected:

            boost::mutex mutex;

            void clearerrors() {
                errmap.clear();}

            virtual void adderror(const dvncierror& val) {
                if (errmap.size() > 1000) clearerrors();
                errmap.insert(int_dvncierror_pair(errmap.size(), val));}
             /**
             * Запрашивает сигнатуры  сущностей для множесва ключей idset. Используется в удаленном интерфейсе
             * для чтения данных из буфера без запроса к серверу.
             * @param ittp тип сущности см. kernel/constdef.h,
             * @param idset множество уникальных индексов  сущности
             * @param mappack карта в которой возвращаются сигнатуры
             * @param strcriteria произвольный критерий фильтрации
             * @param numcriteria произвольный критерий фильтрации
             * @return  успешность выполнения / не используется
             * @see kernel/constdef.h nodetype
              *
             */
            virtual ns_error entities_internal_signature(nodetype ittp, indx_set& idset, iteminfo_map& mappack,
                    const std::string&  strcriteria = "" ) = 0;


            bool alarms_mf(const std::string& strcriteria = "" ) {
                return alarms_->load();}

            bool commands_mf(const std::string& strcriteria = "") {
                return command_->load();}

            bool regs_mf(const std::string& strcriteria = "" ) {
                return reg_->load();}

            bool clients_mf(const std::string& strcriteria = "" ) {
                return clients_->load();}

            bool debug_mf(const std::string& strcriteria = "") {
                return this->debug_->load();}

            bool journal_mf(const std::string& strcriteria = "") {
                return journal_->load();}

            void printerr() {}


            num16 generate_impl(req_entitysigs& req, resp_entitysigs& resp);
            num16 generate_impl(req_tags& req,       resp_tags& resp);
            num16 generate_impl(req_sendtags& req,   resp_sendtags& resp);
            num16 generate_impl(req_groups& req,     resp_groups& resp);
            num16 generate_impl(req_sendgroups& req, resp_sendgroups& resp);
            num16 generate_impl(req_agroups& req,    resp_agroups& resp);
            num16 generate_impl(req_sendagroups& req, resp_sendagroups& resp);
            num16 generate_impl(req_accessrules& req, resp_accessrules& resp);
            num16 generate_impl(req_sendaccessrules& req, resp_sendaccessrules& resp);
            num16 generate_impl(req_users& req, resp_users& resp);
            num16 generate_impl(req_sendusers& req, resp_sendusers& resp);
            num16 generate_impl(req_metas& req, resp_metas& resp);
            num16 generate_impl(req_sendmetas& req, resp_sendmetas& resp);
            num16 generate_impl(req_addentity& req, resp_addentity& resp);
            num16 generate_impl(req_dupentity& req, resp_dupentity& resp);
            num16 generate_impl(req_removeentity& req, resp_removeentity& resp);
            num16 generate_impl(req_config& req, resp_config& resp);
            num16 generate_impl(req_sendconfig& req, resp_sendconfig& resp);
            num16 generate_impl(req_adminoperation& req, resp_adminoperation& resp);
            num16 generate_impl(req_autorization& req, resp_autorization& resp);
            num16 generate_impl(req_services& req, resp_services& resp);
            num16 generate_impl(req_sendservices& req, resp_sendservices& resp);

            num16 generate_impl(req_alarms& req, resp_alarms& resp);
            num16 generate_impl(req_registry& req, resp_registry& resp);
            num16 generate_impl(req_commands& req, resp_commands& resp);
            num16 generate_impl(req_clients& req, resp_clients& resp);
            num16 generate_impl(req_journal& req, resp_journal& resp);
            num16 generate_impl(req_debug& req, resp_debug& resp);


            void assign_sig(const iteminfo_map& mappack, vect_entitysig_data& val) const;

            void assign_vect_error_entity(vect_error_entity& val) const;
            void set_vect_error_entity(const vect_error_entity& val);

            void assign_tag_data(const indx_set& idset, vect_tag_data& val) const;
            void assign_tag_data(const num64_vect& keys, vect_tag_data& val) const;
            void set_tag_data(const vect_tag_data& val, indx_set& idset);

            void assign_group_data(const indx_set& idset, vect_group_data& val) const;
            void assign_group_data(const num64_vect& keys, vect_group_data& val) const;
            void set_group_data(const vect_group_data& val, indx_set& idset);

            void assign_agroup_data(const indx_set& idset, vect_agroup_data& val) const;
            void assign_agroup_data(const num64_vect& keys, vect_agroup_data& val) const;
            void set_agroup_data(const vect_agroup_data& val, indx_set& idset);

            void assign_user_data(const indx_set& idset, vect_user_data& val) const;
            void assign_user_data(const num64_vect& keys, vect_user_data& val) const;
            void set_user_data(const vect_user_data& val, indx_set& idset);

            void assign_accessrule_data(const indx_set& idset, vect_accessrule_data& val) const;
            void assign_accessrule_data(const num64_vect& keys, vect_accessrule_data& val) const;
            void set_accessrule_data(const vect_accessrule_data& val, indx_set& idset);

            void assign_service_data(const indx_set& idset, vect_service_data& val) const;
            void assign_service_data(const num64_vect& keys, vect_service_data& val) const;
            void set_service_data(const vect_service_data& val, indx_set& idset);

            void assign_meta_data(const indx_set& idset, nodetype metatp, vect_meta_data& val) const;
            void assign_meta_data(const num64_vect& keys, nodetype metatp, vect_meta_data& val) const;
            void set_meta_data(const vect_meta_data& val,  indx_set& keys);


            void assign_config_data(const indx_set& idset, config_data& val) const;
            void assign_config_data(const num64_vect& keys, config_data& val) const;
            void set_config_data(const config_data& val, indx_set& idset);

            void getgroupdata() {
                if (state() == disconnected) return;
                select_entities(NT_ROOT_GROUPS,  groupsmap_, npos, "",  false);}

            void getagroupdata() {
                if (state() == disconnected) return;
                select_entities(NT_ROOT_AGROUPS, agroupsmap_, npos,  "",  false);}



            tagintf_ptr               tag_;
            groupintf_ptr             group_;
            agroupintf_ptr            agroup_;
            userintf_ptr              users_;
            accessruleintf_ptr        accessrules_;
            journalintf_ptr           journal_;
            alarmsintf_ptr            alarms_;
            registryintf_ptr          reg_;
            clientsintf_ptr           clients_;
            commandintf_ptr           command_;
            debugintf_ptr             debug_;
            metaintf_ptr              clientmeta_;
            serviceintf_ptr           serviceintf_;

            iteminfo_map              groupsmap_;
            iteminfo_map              agroupsmap_;
            iteminfo_map              alarmmap_;
            iteminfo_map              activealarmmap_;
            iteminfo_map              debugmap_;
            iteminfo_map              commandmap_;
            int_dvncierror_map        errmap;
            confinfo_map              config_map;

            interfacestate            _state;
            ns_error                  _error;

            lcltype                   locale_;
            std::string               adminname;
            std::string               adminpassword;
            bool                      isautorizated_;
            unsigned int              timeout;} ;}}

#endif	/* _KERNELINTERFACE_H */

