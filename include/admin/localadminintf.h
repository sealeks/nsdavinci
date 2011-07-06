/* 
 * File:   kernel_nsLocalIntrface.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 21 Декабрь 2009 г., 17:02
 */

#ifndef _ADMININTF_NSADMINLOCALINTRFACE_H
#define	_ADMININTF_NSADMINLOCALINTRFACE_H


#include <admin/adminintf.h>
#include <kernel/memfile.h>

namespace dvnci {
    namespace admin {


        class localadminintf;

        class localtagintf : public tagintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localtagintf(localadminintf* rot) : tagintf(),
            intf(0), key_(npos), root(rot) {
                ;};

            virtual ~localtagintf() {}

            bool exists() const {
                return ((intf) && (key_ < intf->count()) && (intf->exists(key_)));}

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            virtual ptagstruct _struct()      {
                return exists() ? intf->operator[](key_) : 0;};

            virtual void   value(const std::string& val) {
                if (exists()) intf->value(key_, val);};

            virtual std::string value()  const {
                return exists() ? intf->value_frmt (key_) : "";};

            virtual std::string value_log() const  {
                return exists() ? intf->value_log_frmt (key_) : "";};

            virtual void   mineu(const std::string& val) {
                if (exists()) intf->mineu(key_, val);};

            virtual std::string mineu()  const  {
                return exists() ? intf->mineu (key_) : "";};

            virtual void   maxeu(const std::string& val) {
                if (exists()) intf->maxeu(key_, val);};

            virtual std::string maxeu()  const    {
                return exists() ? intf->maxeu(key_) : "";};

            virtual void   minraw(const std::string& val) {
                if (exists()) intf->minraw(key_, val);};

            virtual std::string minraw()  const  {
                return exists() ? intf->minraw (key_) : "";};

            virtual void   maxraw(const std::string& val) {
                if (exists()) intf->maxraw(key_, val);};

            virtual std::string maxraw() const  {
                return exists() ? intf->maxraw(key_) : "";};

            virtual void   logdb(const std::string& val) {
                if (exists()) { 
                    double tmp=0;
                    if (str_to(trim_copy(val), tmp))
                         intf->logdb(key_, tmp);}};

            virtual std::string logdb() const {
                return exists() ? to_str( intf->logdb(key_), "%8.3f") : "";};

            virtual void   devdb(const std::string& val) {
                if (exists()) { 
                    double tmp=0;
                    if (str_to(trim_copy(val), tmp))
                         intf->devdb(key_, tmp);}};

            virtual std::string devdb() const  {
                return exists() ? to_str(intf->devdb(key_), "%8.3f") : "";};

            virtual void   alarmconst(const std::string& val) {
                if (exists()) intf->alarmconst(key_, val);};

            virtual std::string alarmconst()  const   {
                return exists() ? intf->alarmconst(key_) : "";};


            virtual void   name(const std::string& val);

            virtual std::string name()  const    {
                return exists() ? intf->name(key_) : "";};

            virtual void   comment(const std::string& val)   {
                if (exists()) intf->comment(key_, val);};

            virtual std::string comment() const  {
                return exists() ? intf->comment(key_) : "";};

            virtual void   binding(const std::string& val)   {
                if (exists()) intf->binding(key_, val);};

            virtual std::string binding() const  {
                return exists() ? intf->binding(key_) : "";};

            virtual void   eu(const std::string& val)   {
                if (exists()) intf->eu(key_, val);};

            virtual std::string eu()  const    {
                return exists() ? intf->eu(key_) : "";};

            virtual void   onmsg(const std::string& val)     {
                if (exists()) intf->onmsg(key_, val);};

            virtual std::string onmsg()  const {
                return exists() ? intf->onmsg(key_) : "";};

            virtual void   offmsg(const std::string& val)    {
                if (exists()) intf->offmsg(key_, val);};

            virtual std::string offmsg() const {
                return exists() ? intf->offmsg(key_) : "";};

            virtual void   alarmmsg(const std::string& val)  {
                if (exists()) intf->alarmmsg(key_, val);};

            virtual std::string alarmmsg() const  {
                return exists() ? intf->alarmmsg(key_) : "";};

            virtual void   logged(bool val)      {
                if (exists()) intf->logged(key_, val);};

            virtual bool   logged()   const  {
                return exists() ? intf->logged(key_) : false;};

            virtual void   onmsged(bool val)     {
                if (exists()) intf->onmsged(key_, val);};

            virtual bool   onmsged()  const   {
                return exists() ? intf->onmsged(key_) : false;};

            virtual void   offmsged(bool val)    {
                if (exists()) intf->offmsged(key_, val);};

            virtual bool   offmsged()  const    {
                return exists() ? intf->offmsged(key_) : false;};

            virtual bool   alarmed()  const  {
                return exists() ? intf->alarmed(key_) : false;};

            virtual bool   alarmon()  const  {
                return exists() ? intf->alarmon(key_) : false;};

            virtual bool   alarmkvit()  const  {
                return exists() ? intf->alarmkvit(key_) : false;};

            virtual acclevtype   accesslevel() const {
                return exists() ? intf->accesslevel(key_) : false;}

            virtual void accesslevel(acclevtype val)  {
                if (exists()) intf->accesslevel(key_, val);}

            virtual std::string  time()   const  {
                return exists() ? intf->time_str(key_) : "";};

            virtual std::string  time_log()   const  {
                return exists() ? intf->time_log_str(key_) : "";};

            virtual vlvtype valid()   const  {
                return exists() ? intf->valid(key_) : 0;};

            virtual onum   refcnt()  const  {
                return exists() ? intf->refcnt(key_) : 0;};

            virtual void   type(tagtype val)       {
                if (exists()) intf->type(key_, val);};

            virtual tagtype   type() const {
                return exists() ? intf->type(key_) : 0;};

            virtual void   alarmlevel(altype val) {
                if (exists()) intf->alarmlevel(key_, val);};

            virtual altype   alarmlevel()  const  {
                return exists() ? intf->alarmlevel(key_) : 0;};

            virtual void   alwactive(bool val)   {
                if (exists()) intf->alwactive(key_, val);};

            virtual bool   alwactive() const {
                return exists() ? intf->alwactive(key_) : false;};
                
            virtual void   rangable(bool val) {
                if (exists()) intf->rangable(key_, val);};
                
            virtual bool   rangable() const {
                return exists() ? intf->rangable(key_) : false;};

            virtual ns_error  error() const {
                return exists() ? intf->error(key_) : 0;};

            virtual void  group(indx val);

            virtual indx  group() const {
                return exists() ? intf->group(key_) : 0;};

            virtual void  agroup(indx val);

            virtual indx  agroup() const  {
                return exists() ? intf->agroup(key_) : 0;};

            virtual void   alarmcase(alcstype val)  {
                if (exists()) intf->alarmcase(key_, val);};

            virtual alcstype  alarmcase() const {
                return exists() ? intf->alarmcase(key_) : 0;};

            virtual void   rwtype(acstgtype val)         {
                if (exists()) intf->rwtype(key_, val);};

            virtual acstgtype  rwtype() const {
                return exists() ? intf->rwtype(key_) : 0;};

            virtual void   reporthistory(reporthisttype val)  {
                if (exists()) intf->reporthistory(key_, val);}

            virtual reporthisttype  reporthistory() const {
                return exists() ? intf->reporthistory(key_) : 0;};

            virtual void   reportsubdelt(reporthistdelt val)  {
                if (exists()) intf->reportsubdelt(key_, val);}

            virtual reporthistdelt  reportsubdelt() const {
                return exists() ? intf->reportsubdelt(key_) : 0;};

            virtual void   reportstatistic(repstattype val) {
                if (exists()) intf->reportstatistic(key_, val);}

            virtual repstattype  reportstatistic() const    {
                return exists() ? intf->reportstatistic(key_) : 0;};

        private:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            tagsbase* intf;
            indx key_;
            localadminintf* root;} ;

        class localgroupintf : public groupintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localgroupintf(localadminintf* rot) : groupintf() ,
            intf(0), key_(npos), root(rot) {
                ;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            bool exists() const {
                return ((intf) && (key_ < intf->groups()->count()) && (intf->groups()->exists(key_)));}

            virtual pgroupstruct _struct()      {
                return exists() ? (*(intf->groups()))[key_] : 0;};

            virtual void   name(const std::string& val);

            virtual std::string name() const {
                return exists() ? intf->groups()->name(key_) : "";};

            virtual void   host(const std::string& val);

            virtual std::string host() const {
                return exists() ? intf->groups()->host(key_) : "";};

            virtual void   user(const std::string& val);

            virtual std::string user() const {
                return exists() ? intf->groups()->user(key_) : "";};

            virtual void   password(const std::string& val);

            virtual std::string password() const {
                return exists() ? intf->groups()->password(key_) : "";};

            virtual void   server(const std::string& val);

            virtual std::string server() const {
                return exists() ? intf->groups()->server(key_) : "";};

            virtual void   group(const std::string& val);

            virtual std::string group() const {
                return exists() ? intf->groups()->group(key_) : "";};

            virtual void   port(const std::string& val);

            virtual std::string port() const {
                return exists() ? intf->groups()->port(key_) : "";};

            virtual void   topic(const std::string& val);

            virtual std::string topic() const {
                return exists() ? intf->groups()->topic(key_) : "";};

            virtual void   ether(const std::string& val);

            virtual std::string ether() const {
                return exists() ? intf->groups()->ether(key_) : "";};

            virtual void   appid(appidtype val);

            virtual appidtype appid() const {
                return exists() ? intf->groups()->appid(key_) : 0;};

            virtual void   chanaltype(chnltype val) {
                if (exists()) intf->groups()->chanaltype(key_, val);};

            virtual chnltype chanaltype() const {
                return exists() ? intf->groups()->chanaltype(key_) : 0;};

            virtual void   chanalnum(chnlnumtype val)  {
                if (exists()) intf->groups()->chanalnum(key_, val);};

            virtual chnlnumtype  chanalnum()  const  {
                return exists() ? intf->groups()->chanalnum(key_) : 0;};

            virtual void   devnum(devnumtype val) {
                if (exists()) intf->groups()->devnum(key_, val);};

            virtual devnumtype  devnum() const {
                return exists() ? intf->groups()->devnum(key_) : 0;};

            virtual void   protocol(protocoltype val)  {
                if (exists()) intf->groups()->protocol(key_, val);};

            virtual protocoltype  protocol()const {
                return exists() ? intf->groups()->protocol(key_) : 0;};

            virtual void   config(void* val) {
                if (exists()) intf->groups()->config(key_, val);};

            virtual const void*  config() const {
                return exists() ? intf->groups()->config(key_) : 0;};

            virtual bool   active() const {
                return (exists()) ? intf->groups()->active(key_) : false;};

            virtual ns_error   error() const {
                return exists() ? intf->groups()->error(key_) : 0;};

            virtual void   timeout(timeouttype val)    {
                if (exists()) intf->groups()->timeout(key_, val);};

            virtual timeouttype   timeout() const {
                return exists() ? intf->groups()->timeout(key_) : 0;};

            virtual void   deadbound(double val)  {
                if (exists()) intf->groups()->deadbound(key_, val);};

            virtual double deadbound() const {
                return exists() ? intf->groups()->deadbound(key_) : 0;};

            virtual void   grouprate(gratetype val) {
                if (exists()) intf->groups()->grouprate(key_, val);};

            virtual gratetype  grouprate() const {
                return exists() ? intf->groups()->grouprate(key_) : 0;};

            virtual void   trycount(size_t val)   {
                if (exists()) intf->groups()->trycount(key_, val);};

            virtual size_t  trycount() const {
                return exists() ? intf->groups()->trycount(key_) : 0;};

            virtual void   blocksize(blksizetype val)  {
                if (exists()) intf->groups()->blocksize(key_, val);};

            virtual blksizetype  blocksize() const {
                return exists() ? intf->groups()->blocksize(key_) : 0;};

            virtual void   archblocksize(blksizetype val) {
                if (exists()) intf->groups()->archblocksize(key_, val);};

            virtual blksizetype  archblocksize() const {
                return exists() ? intf->groups()->archblocksize(key_) : 0;};

            virtual void   utiloperation(bool val) {
                if (exists()) intf->groups()->utiloperation(key_, val);};

            virtual bool   utiloperation() const {
                return exists() ? intf->groups()->utiloperation(key_) : false;};

            virtual void   indicateto(timeouttype val)  {
                if (exists()) intf->groups()->indicateto(key_, val);};

            virtual timeouttype  indicateto() const {
                return exists() ? intf->groups()->indicateto(key_) : 0;};

            virtual lcltype local() const {
                return exists() ? intf->groups()->local(key_) : 0;};

            virtual void local(lcltype val ) {
                if (exists()) intf->groups()->local(key_, val);};

            virtual subcripttype synctype() const  {
                return exists() ? intf->groups()->synctype(key_) : 0;};

            virtual void synctype(subcripttype val ) {
                if (exists()) intf->groups()->synctype(key_, val);};

            virtual intfvertype ver() const {
                return exists() ? intf->groups()->ver(key_) : 0;};

            virtual void ver(intfvertype val ) {
                if (exists()) intf->groups()->ver(key_, val);};

            virtual bool supporttype() const {
                return exists() ? intf->groups()->supporttype(key_) : 0;};

            virtual void supporttype(bool val ) {
                if (exists()) intf->groups()->supporttype(key_, val);};

            virtual vlvtype valid() const {
                return exists() ? intf->groups()->valid(key_) : 0;};

            virtual ~localgroupintf() {}

        private:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            tagsbase* intf;
            indx key_;
            localadminintf* root;} ;

        class localagroupintf : public agroupintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localagroupintf(localadminintf* rot) : agroupintf() ,
            intf(0), key_(npos), root(rot) {};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            bool exists() const {
                return ((intf) && (key_ < intf->agroups()->count()) && (intf->agroups()->exists(key_)));}

            virtual pagroupstruct _struct() {
                return exists() ? (*(intf->agroups()))[key_] : 0;};

            virtual void   name(const std::string& val) {
                if (exists()) intf->rename_agroup(key_, val);};

            virtual std::string name() const {
                return exists() ? intf->agroups()->name(key_) : "";};

            virtual void   headername(const std::string& val) {
                if (exists()) intf->agroups()->headername(key_, val);};

            virtual std::string headername() const {
                return exists() ? intf->agroups()->headername(key_) : "";};


        private:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            tagsbase* intf;
            indx key_;
            localadminintf* root;} ;

        class localuserintf : public userintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localuserintf(localadminintf* rot) : userintf() ,
            intf(0), key_(npos), root(rot) {
                ;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            bool exists() const {
                return (intf) ;}

            virtual void   name(const std::string& val);

            virtual std::string name() const {
                return exists() ? intf->users()->name(key_) : "";};

            virtual void   password(const std::string& val) {
                if (exists()) intf->users()->password(key_, val);};

            virtual std::string password() const {
                return exists() ? intf->users()->password(key_) : "";};
                
            virtual void   filter(const std::string& val) {
                if (exists()){
                  ipfilter tst;
                  if (ipfilter::ipfilter_from_str(tst,val)){
                     intf->users()->filter(key_, tst);}}}

            virtual std::string  filter() const {
                return exists() ? intf->users()->filter(key_).to_string() : "";}                

            virtual void   accesslevel(acclevtype val) {
                if (exists()) intf->users()->accesslevel(key_, val);};

            virtual acclevtype accesslevel() const {
                return exists() ? intf->users()->accesslevel(key_) : 0;};
                
            virtual void   role(rolesettype val) {
                if (exists()) intf->users()->role(key_, val);}
            
            virtual rolesettype role() const {
                return exists() ? intf->users()->role(key_) : 0;}
          
        private:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            tagsbase* intf;
            indx key_;
            localadminintf* root;} ;

        class localaccessruleintf : public accessruleintf {
            

            friend class localadminintf;
            friend class adminintf;

        public:

            localaccessruleintf(localadminintf* rot) : accessruleintf(),
            intf(0), key_(npos), root(rot) {
                ;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            bool exists() const {
                return (intf) ;}

            virtual void   name(const std::string& val) ;

            virtual std::string name() const {
                return exists() ? intf->accessrules()->name(key_) : "";};
                
            virtual void   user(const std::string& val) {
                if (exists()) intf->accessrules()->user(key_, val);}

            virtual std::string  user() const {
                return exists() ? intf->accessrules()->user(key_) : "";}                

            virtual void   host(const std::string& val) {
                if (exists()) intf->accessrules()->host(key_, val);}

            virtual std::string  host() const {
                return exists() ? intf->accessrules()->host(key_) : "";}

            virtual void   filter(const std::string& val) {
                if (exists()){
                  ipfilter tst;
                  if (ipfilter::ipfilter_from_str(tst,val)){
                     intf->accessrules()->filter(key_, tst);}}}

            virtual std::string  filter() const {
                return exists() ? intf->accessrules()->filter(key_).to_string() : "";}

            virtual void   appid(appidtype val) {
                if (exists()) intf->accessrules()->appid(key_, val);}

            virtual appidtype appid() const {
                return exists() ? intf->accessrules()->appid(key_) : 0;}
            
             virtual void   protocol(protocoltype val) {
                if (exists()) intf->accessrules()->protocol(key_, val);}
            
            virtual protocoltype protocol() const {
                return exists() ? intf->accessrules()->protocol(key_) : 0;}            

            virtual void   accessrule(accessruletype val) {
                if (exists()) intf->accessrules()->accessrule(key_, val);}

            virtual accessruletype accessrule() const {
                return exists() ? intf->accessrules()->accessrule(key_) : 0;}

            virtual void   accesslevel(acclevtype val) {
                if (exists()) intf->accessrules()->accesslevel(key_, val);}

            virtual acclevtype accesslevel() const {
                return exists() ? intf->accessrules()->accesslevel(key_) : 0;}
            
             virtual void   role(rolesettype val) {
                if (exists()) intf->accessrules()->role(key_, val);}
            
            virtual rolesettype role() const {
                return exists() ? intf->accessrules()->role(key_) : 0;}
       


        private:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            tagsbase* intf;
            indx key_;
            localadminintf* root;} ;

        class localmetaintf : public metaintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localmetaintf(localadminintf* rot) : metaintf(), intf(0), _id(npos), root(rot) {
                ;};

            bool exists() const {
                return (intf);}

            virtual void  key(nodetype type_, indx val) {
                _type = type_;
                _id = val;};

            virtual std::string property(const std::string& prop) const {
                return exists() ? intf->getItemProperty(_type, _id, prop) : "";};

            virtual void  property(const std::string& prop, const std::string& val) {
                if (exists()) intf->property(_type, _id, prop, val);};


        private:

            void setintf(meta* intf_) {
                intf = intf_;};

            meta* intf;
            nodetype _type;
            indx _id;
            localadminintf* root;} ;

        class localalarmsintf : public alarmsintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localalarmsintf(adminintf* rot) : alarmsintf(), intf(0), root(rot) {};

        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t load(const std::string& agroup = "", const std::string& group = "") {
                intf->select_alarms<alarms_data, num64 > (vect, version_, agroup, group);
                return count();}

            tagsbase* intf;
            adminintf* root;} ;

        class localcommandintf : public commandintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localcommandintf(adminintf* rot) : commandintf() , intf(0), root(rot) {};

        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t load(const std::string& group = "") {
                intf->select_commands<commands_data, num64 > (vect, version_, group);
                return count();}

            tagsbase* intf;
            adminintf* root;} ;

        class localregistryintf : public registryintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localregistryintf(adminintf* rot) : registryintf() , intf(0), root(rot) {};

        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t load() {
                intf->select_registry<registry_data, num64 > (vect, version_);
                return count();}

            tagsbase* intf;
            adminintf* root;} ;

        class localclientsintf : public clientsintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localclientsintf(adminintf* rot) : clientsintf(), intf(0), root(rot) {};

        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t load() {
                intf->select_clients<clients_data, num64 > (vect, version_);
                return count();}

            tagsbase* intf;
            adminintf* root;} ;

        class localjournalintf : public journalintf {
            friend class localadminintf;
            friend class adminintf;

        public:

            localjournalintf(adminintf* rot) : journalintf(), intf(0), root(rot) {};

        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t assign_data(vect_journal_data& vct)  {
                intf->select_journal<journal_data, num64 > (vct, guid_, cursor_, count_);
                return count_;}

            virtual size_t load(const std::string& agroup = "") {
                vect_journal_data vct;
                assign_data(vct);
                filldata(vct);
                return count_;}

            tagsbase* intf;
            adminintf* root;} ;

        class localdebugintf : public debugintf {

            friend class localadminintf;
            friend class adminintf;

        public:

            localdebugintf(adminintf* rot) : debugintf() , intf(0), root(rot) {};


        protected:

            void setintf(tagsbase* intf_) {
                intf = intf_;};

            virtual size_t assign_data(vect_debug_data& vct) {
                intf->select_debug<debug_data, num64 > (vct, guid_, cursor_, count_);
                return count_;}

            virtual size_t load(debuglvtype lev = 0) {
                vect_debug_data vct;
                assign_data(vct);
                filldata(vct);
                return count_;}

            tagsbase* intf;
            adminintf* root;} ;

        class localserviceintf : public serviceintf {

            friend class localadminintf;
            friend class adminintf;

        public:

            localserviceintf() : serviceintf() {
                   svm_=demon_entry_factory::build(FULL_EXEC_DIR()); };

            bool                  exists() const {
                return ((svm_) && (svm_->exists(number_)));}

            virtual void          number(indx val) {
                number_ = val;};

            virtual indx          number() const {
                return number_;};

            virtual std::string   displayname() const {
                if (exists()) {
                    return svm_->name(number_);};
                return "";}

            virtual std::string   path() const {
                if (exists()) {
                    return svm_->fullpath(number_);};
                return "";}

            virtual num64         starttype() const {
                if (exists()) {
                    return svm_->starttype(number_);};
                return SERVICE_RUNSTATE_NODEF;}

            virtual void          starttype(num64 val)  {
                if (exists()) {
                    return svm_->starttype(number_, static_cast<int>(val));};}

            virtual num64         status() const   {
                if (exists()) {
                    return svm_->status(number_);};
                return SERVICE_STATUS_NODEF;}

            virtual void          status(num64 val) {;}

        protected:

            mutable  servicemanager_ptr svm_;
            indx                        number_;} ;
            
            
            
            
            

        class localadminintf : public adminintf {
            
            
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


            friend class adminsession;
            //friend class intrusive_sync_share_ptr_tmpl<adminintf>;


        public:

            localadminintf(const fspath& pth, appidtype app = 0, eventtypeset evnts = 0);
            
            localadminintf(tagsbase_ptr inf);

            virtual ~localadminintf () {
                disconnect();};
                
            virtual void setaddress(const boost::asio::ip::address& adr){
                    address=adr;}
                
            virtual bool connect(const std::string& user = "", const std::string& password = "");

            virtual bool disconnect();
            

            virtual void operation_mapprj(std::string path_);

            virtual void operation_unmapprj();

            virtual void operation_newprj(std::string path_);
            

            virtual ns_error select_entities(nodetype parenttp, iteminfo_map& mappack, indx parentid,
                    const std::string& strcriteria = "" ,  bool clearer = true);
            
            

            virtual  ns_error load_entities(nodetype ittp,  indx_set& set_) {
                clearerrors();
                return NS_ERROR_SUCCESS;};
                
                

            virtual ns_error insert_entity(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
                    std::string newnm = "" );

            virtual ns_error insert_entities(nodetype ittp, indx parentid, str_indx_map& mpnew);
            
            

            virtual ns_error delete_entities(nodetype ittp, const indx_set& idset);
            
            

            virtual ns_error change_parent_entities(nodetype ittp, indx_set& idset, indx parentid);
            
            

            virtual ns_error duplicate_entity(nodetype ittp,  indx id, const std::string& newname, iteminfo_pair& pairpack);
            
            
            virtual  ns_error merge_entities(nodetype ittp,  indx_set& set_, iteminfo_map& mappack);

            virtual ns_error merge_entities(nodetype ittp,  const indx_set&  idset);

            bool merge_entities(nodetype ittp, indx id);
            
            

            virtual std::string conf_property(const confproptype& name) const;

            virtual int conf_numproperty(const confproptype& name);

            virtual void conf_property(const confproptype& name, const std::string& val);

            virtual void conf_property(const confproptype& name, int val);

            virtual bool operation_setvalue(indx id, const std::string& val, vlvtype valid);

            virtual bool operation_setvalid(indx id, vlvtype valid);

            virtual bool operation_setallvalid(vlvtype valid);

            virtual bool operation_setcounter(indx id, bool inc = true);

            virtual bool operation_setallcounter(bool inc = true);

            virtual bool operation_kvit();

            virtual bool operation_kvitgroup(indx id);

            virtual bool operation_kvitagroup(indx id);

            virtual bool operation_send_command(indx id, std::string val, bool setqueue = true);

            virtual ns_error operation_autorizate(const std::string& user = "", const std::string& password = "");

            virtual bool operation_startservice(appidtype val);

            virtual bool operation_stopservice(appidtype val);

        protected:
            
            servicemanager_ptr svm() const;

            virtual ns_error entities_internal_signature(nodetype ittp, indx_set& set_, iteminfo_map& mappack,
                    const std::string& strcriteria = "" );

            bool changeparenttag( indx_set& idset, indx parentid);

            bool changeparentatag( indx_set& idset, indx parentid);


            
            void createtags( str_indx_map& mpnew, std::string group);

            void createtags( str_indx_map& mpnew, indx group);


            bool duplicategroup(indx id, const std::string& newname, iteminfo_pair& pairpack);



        private:
            
            tagsbase_ptr              intf;
            iteminfo_map              key_name_map;
            fspath                    path;
            appidtype                 appid;
            eventtypeset              events;
            dvnci::meta               metaintf_;
            boost::asio::ip::address  address;
            guidtype                  regclid;

            void setintf(tagsbase* intf_);} ;}}

#endif	/* _KERNEL_NSLOCALINTRFACE_H */
