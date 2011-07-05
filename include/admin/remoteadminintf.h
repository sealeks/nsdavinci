/* 
 * File:   kernel_nsRemoteInterface.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 8 Январь 2010 г., 23:00
 */

#ifndef _ADMININTF_NSADMINREMOTEINTERFACE_H
#define	_ADMININTF_NSADMINREMOTEINTERFACE_H



#include <kernel/rpcioclient.h>

#include <meta/meta.h>

#include <admin/adminintf.h>

#include <sstream>

namespace dvnci {
    namespace admin {

        class remoteadminintf;

        class remotetagintf : public tagintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotetagintf(indx_tags_map* mappack) : tagintf() {
                map = mappack;};

            bool exists() const {
                return ((map) && (get(key_)));};

            virtual ptagstruct _struct() {
                return exists() ? gets() : 0;};

            virtual void         key(indx val)  {
                key_ = val;};

            virtual indx         key()   const  {
                return key_;};

            virtual void         value(const std::string& val) {
                if (exists()) gets()->value(val);
                in_cangeset(MASK_RT_CHANGE_VALUE);};

            virtual std::string  value() const          {
                return exists() ? gets()->value_frmt() : "";};

            virtual std::string  value_log()  const     {
                return exists() ? gets()->value_log_frmt() : "";};

            virtual void         mineu(const std::string& val) {
                if (exists()) gets()->mineu(val);
                in_cangeset(MASK_RT_CHANGE_MINEU);};

            virtual std::string  mineu()  const         {
                return exists() ? gets()->mineu_str() : "";};

            virtual void         maxeu(const std::string& val) {
                if (exists()) gets()->maxeu(val);
                in_cangeset(MASK_RT_CHANGE_MAXEU);};

            virtual std::string  maxeu() const      {
                return exists() ? gets()->maxeu_str() : "";};

            virtual void         minraw(const std::string& val) {
                if (exists()) gets()->minraw(val);
                in_cangeset(MASK_RT_CHANGE_MINRAW);};

            virtual std::string  minraw()   const      {
                return exists() ? gets()->minraw_str() : "";};

            virtual void         maxraw(const std::string& val) {
                if (exists()) gets()->maxraw(val);
                in_cangeset(MASK_RT_CHANGE_MAXRAW);};

            virtual std::string  maxraw()   const      {
                return exists() ? gets()->maxraw_str() : "";};

            virtual void         logdb(const std::string& val) {
                if (exists()) { 
                    double tmp=0;
                    if (str_to(trim_copy(val), tmp))
                         gets()->logdb(tmp);
                         in_cangeset(MASK_RT_CHANGE_LOGDB);}};

            virtual std::string  logdb()  const        {
                return exists() ? to_str(gets()->logdb(), "%8.3f") : "";};

            virtual void         devdb(const std::string& val) {
                if (exists()) { 
                    double tmp=0;
                    if (str_to(trim_copy(val), tmp))
                         gets()->devdb(tmp);
                         in_cangeset(MASK_RT_CHANGE_DEVDB);}};

            virtual std::string  devdb() const          {
                return exists() ? to_str(gets()->devdb(), "%8.3f") : "";};

            virtual void         alarmconst(const std::string& val) {
                if (exists()) gets()->alarmconstr(val);
                in_cangeset(MASK_RT_CHANGE_ALARMCONST);};

            virtual std::string  alarmconst()  const     {
                return exists() ? gets()->alarmconst_str() : "";};


            virtual void         name(const std::string& val)   {
                if (exists()) gets_()->name = val;
                in_cangeset(MASK_RT_CHANGE_NAME);};

            virtual std::string  name()  const           {
                return exists() ?    gets_()->name : "";};

            virtual void         comment(const std::string& val) {
                if (exists()) gets_()->comment = val;
                in_cangeset(MASK_RT_CHANGE_COMMENT);};

            virtual std::string  comment()  const        {
                return exists() ? gets_()->comment : "";};

            virtual void         binding(const std::string& val) {
                if (exists()) gets_()->bind = val;
                in_cangeset(MASK_RT_CHANGE_BINDING);};

            virtual std::string  binding() const         {
                return exists() ? gets_()->bind : "";};

            virtual void         eu(const std::string& val)     {
                if (exists()) gets_()->ue = val;
                in_cangeset(MASK_RT_CHANGE_EU);};

            virtual std::string  eu()   const            {
                return exists() ? gets_()->ue : "";};

            virtual void         onmsg(const std::string& val)  {
                if (exists()) gets_()->onmsg = val;
                in_cangeset(MASK_RT_CHANGE_ONMSGTXT);};

            virtual std::string  onmsg()  const          {
                return exists() ? gets_()->onmsg : "";};

            virtual void         offmsg(const std::string& val) {
                if (exists()) gets_()->offmsg = val;
                in_cangeset(MASK_RT_CHANGE_OFFMSGTXT);};

            virtual std::string  offmsg() const          {
                return exists() ? gets_()->offmsg : "";};

            virtual void         alarmmsg(const std::string& val)  {
                if (exists()) gets_()->almsg = val;
                in_cangeset(MASK_RT_CHANGE_ALMSGTXT);};

            virtual std::string  alarmmsg() const        {
                return exists() ? gets_()->almsg : "";};

            virtual void         logged(bool val)        {
                if (exists()) gets()->logged(val);
                in_cangeset(MASK_RT_CHANGE_LOGGED);};

            virtual bool         logged()  const         {
                return exists() ? gets()->logged() : false;};

            virtual void         onmsged(bool val)       {
                if (exists()) gets()->onmsged(val);
                in_cangeset(MASK_RT_CHANGE_ONMSG);};

            virtual bool         onmsged() const         {
                return exists() ? gets()->onmsged() : false;};

            virtual void         offmsged(bool val)      {
                if (exists()) gets()->offmsged(val);
                in_cangeset(MASK_RT_CHANGE_OFFMSG);};

            virtual bool         offmsged()  const       {
                return exists() ? gets()->offmsged() : false;};

            virtual bool         alarmed()  const        {
                return exists() ? (gets()->alarmlevel() != 0) : false;};

            virtual bool         alarmon() const         {
                return exists() ? gets()->alarmon() : false;};

            virtual bool         alarmkvit() const       {
                return exists() ? gets()->alarmkvit() : false;};

            virtual altype        accesslevel() const        {
                return exists() ? gets()->accesslevel() : false;};

            virtual void         accesslevel(altype val)       {
                if (exists()) gets()->accesslevel(val);
                in_cangeset(MASK_RT_CHANGE_ACCESSL);};

            virtual std::string  time() const            {
                return exists() ? gets()->time_str() : "";};

            virtual std::string  time_log() const        {
                return exists() ? gets()->time_log_str() : "";};

            virtual vlvtype      valid()  const          {
                return exists() ? gets()->valid() : 0;};

            virtual onum         refcnt() const          {
                return exists() ? gets()->refcnt() : 0;};

            virtual void         type(tagtype val)       {
                if (exists()) gets()->type(val);
                in_cangeset(MASK_RT_CHANGE_TYPE);};

            virtual tagtype      type() const            {
                return exists() ? gets()->type() : 0;};

            virtual void         alarmlevel(altype val)  {
                if (exists()) gets()->alarmlevel(val);
                in_cangeset(MASK_RT_CHANGE_ALLEVEL);};

            virtual altype       alarmlevel()  const     {
                return exists() ? gets()->alarmlevel() : 0;};

            virtual void         alwactive(bool val)      {
                if (exists()) gets()->alwactive(val);
                in_cangeset(MASK_RT_CHANGE_ALWACTIVE);};

            virtual bool         alwactive()  const        {
                return exists() ? gets()->alwactive() : false;};
                
            virtual void         rangable(bool val)      {
                //if (exists()) gets()->rangable(val);
                in_cangeset(MASK_RT_CHANGE_MINRAW);
                in_cangeset(MASK_RT_CHANGE_MAXRAW);};

            virtual bool         rangable()  const        {
                return exists() ? gets()->rangable() : false;};                

            virtual ns_error     error() const           {
                return exists() ? gets()->error() : 0;};

            virtual void         group(indx val)         {
                if (exists()) gets()->group(val);
                in_cangeset(MASK_RT_CHANGE_GROUP);};

            virtual indx         group() const           {
                return exists() ? gets()->group() : 0;};

            virtual void         agroup(indx val)        {
                if (exists()) gets()->agroup(val);
                in_cangeset(MASK_RT_CHANGE_AGROUP);};

            virtual indx         agroup()   const        {
                return exists() ? gets()->agroup() : 0;};

            virtual void         alarmcase(alcstype val) {
                if (exists()) gets()->alarmcase(val);
                in_cangeset(MASK_RT_CHANGE_ALCASE);};

            virtual alcstype     alarmcase() const       {
                return exists() ? gets()->alarmcase() : 0;};

            virtual void         rwtype(acstgtype val)        {
                if (exists()) gets()->rwtype(val);
                in_cangeset(MASK_RT_CHANGE_RW);};

            virtual acstgtype    rwtype() const          {
                return exists() ? gets()->rwtype() : 0;};

            virtual void         reporthistory(reporthisttype val) {
                if (exists()) gets()->reporthistory(val);
                in_cangeset(MASK_RT_CHANGE_REPPER);}

            virtual reporthisttype    reporthistory() const   {
                return exists() ? gets()->reporthistory() : 0;};

            virtual void         reportsubdelt(reporthistdelt val)  {
                if (exists()) gets()->reportsubdelt(val);
                in_cangeset(MASK_RT_CHANGE_DELT);}

            virtual reporthistdelt        reportsubdelt()  const  {
                return exists() ? gets()->reportsubdelt() : 0;};

            virtual void         reportstatistic(repstattype val) {
                if (exists()) gets()->reportstatistic(val);
                in_cangeset(MASK_RT_CHANGE_STAT);}

            virtual repstattype  reportstatistic() const  {
                return exists() ? gets()->reportstatistic() : 0;};

        private:

            tag_data* get(indx val) const {
                indx_tags_map::iterator it = map->find(val);
                return (it != map->end()) ?  &it->second : 0;}

            ptagstruct getstruct(tag_data* val) const {
                return (ptagstruct) (&val->tginfo);}

            ptagstruct gets() const {
                return getstruct(get(key_));}

            tag_data* gets_() const {
                return get(key_);}

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            indx_tags_map* map;
            indx key_;} ;

        class remotegroupintf : public groupintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotegroupintf(indx_groups_map* mappack) : groupintf() {
                map = mappack;};

            virtual pgroupstruct _struct() {
                return exists() ? gets() : 0;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx key() const {
                return key_;};

            bool exists() const {
                return ((map) && (get(key_)) && (gets_()));}

            virtual void   name(const std::string& val)           {
                gets_()->name = val;
                in_cangeset(MASK_GR_CHANGE_NAME);};

            virtual std::string  name() const              {
                return exists() ? gets_()->name : "";};

            virtual void   host(const std::string& val)           {
                gets_()->host = val;
                in_cangeset(MASK_GR_CHANGE_HOST);};

            virtual std::string  host() const              {
                return exists() ? gets_()->host : "";};

            virtual void   user(const std::string& val)           {
                gets_()->user = val;
                in_cangeset(MASK_GR_CHANGE_USER);};

            virtual std::string  user() const              {
                return exists() ? gets_()->user : "";};

            virtual void   password(const std::string& val)           {
                gets_()->password = val;
                in_cangeset(MASK_GR_CHANGE_PASS);};

            virtual std::string  password() const              {
                return exists() ? gets_()->password : "";};

            virtual void   server(const std::string& val)           {
                gets_()->server = val;
                in_cangeset(MASK_GR_CHANGE_SERVER);};

            virtual std::string  server() const              {
                return exists() ? gets_()->server : "";};

            virtual void   group(const std::string& val)           {
                gets_()->group = val;
                in_cangeset(MASK_GR_CHANGE_GROUP);};

            virtual std::string  group() const              {
                return exists() ? gets_()->group : "";};

            virtual void   port(const std::string& val)           {
                gets_()->port = val;
                in_cangeset(MASK_GR_CHANGE_PORT);};

            virtual std::string  port() const              {
                return exists() ? gets_()->port : "";};

            virtual void   topic(const std::string& val)           {
                gets_()->topic = val;
                in_cangeset(MASK_GR_CHANGE_TOPIC);};

            virtual std::string  topic() const              {
                return exists() ? gets_()->topic : "";};

            virtual void   ether(const std::string& val)           {
                gets_()->ether = val;
                in_cangeset(MASK_GR_CHANGE_ETHER);};

            virtual std::string  ether() const              {
                return exists() ? gets_()->ether : "";};

            virtual void   appid(appidtype val)            {
                gets()->appid(val);
                in_cangeset(MASK_GR_CHANGE_APPID);};

            virtual appidtype   appid() const              {
                return exists() ? gets()->appid() : 0;};

            virtual void   chanaltype(chnltype val)        {
                gets()->chanaltype(val);
                in_cangeset(MASK_GR_CHANGE_CHTYPE);};

            virtual chnltype chanaltype()  const           {
                return exists() ? gets()->chanaltype() : 0;};

            virtual void   chanalnum(chnlnumtype val)            {
                gets()->chanalnum(val);
                in_cangeset(MASK_GR_CHANGE_CHNUM);};

            virtual chnlnumtype  chanalnum()   const             {
                return exists() ? gets()->chanalnum() : 0;};

            virtual void   devnum(devnumtype val)            {
                gets()->devnum(val);
                in_cangeset(MASK_GR_CHANGE_CHDEVNUM);};

            virtual devnumtype  devnum()    const           {
                return exists() ? gets()->devnum() : 0;};

            virtual void   protocol(protocoltype val)            {
                gets()->protocol(val);
                in_cangeset(MASK_GR_CHANGE_DEVNUM);};

            virtual protocoltype  protocol()   const             {
                return exists() ? gets()->protocol() : 0;};

            virtual void   config(void* val)               {
                memcpy(gets()->config(), val, GROP_CONFIG_SIZE/*384*/);
                in_cangeset(MASK_GR_CHANGE_CONFIG);};

            virtual const void*  config() const                  {
                return exists() ? gets()->config() : 0;};

            virtual bool   active() const                  {
                return exists() ? gets()->active() : false;};

            virtual ns_error error()  const                {
                return exists() ? gets()->error() : 0;};

            virtual void   timeout(timeouttype val)              {
                gets()->timeout(val);
                in_cangeset(MASK_GR_CHANGE_TO);};

            virtual timeouttype  timeout() const                 {
                return exists() ? gets()->timeout() : 0;};

            virtual void   deadbound(double val)           {
                gets()->deadbound(val);
                in_cangeset(MASK_GR_CHANGE_DB);};

            virtual double deadbound()  const              {
                return exists() ? gets()->deadbound() : 0;};

            virtual void   grouprate(gratetype val)            {
                gets()->grouprate(val);
                in_cangeset(MASK_GR_CHANGE_GR);};

            virtual gratetype  grouprate() const               {
                return exists() ? gets()->grouprate() : 0;};

            virtual void   trycount(size_t val)              {
                gets()->trycount(val);
                in_cangeset(MASK_GR_CHANGE_TCNT);};

            virtual size_t  trycount() const                {
                return exists() ? gets()->trycount() : 0;};

            virtual void   blocksize(blksizetype val)            {
                gets()->blocksize(val);
                in_cangeset(MASK_GR_CHANGE_BS);};

            virtual blksizetype  blocksize() const               {
                return exists() ? gets()->blocksize() : 0;};

            virtual void   archblocksize(blksizetype val)        {
                gets()->archblocksize(val);
                in_cangeset(MASK_GR_CHANGE_ABS);};

            virtual blksizetype  archblocksize()  const          {
                return exists() ? gets()->archblocksize() : 0;};

            virtual void   utiloperation(bool val)              {
                gets()->utiloperation(val);
                in_cangeset(MASK_GR_CHANGE_SYNCT);};

            virtual bool   utiloperation()  const               {
                return exists() ? gets()->utiloperation() : 0;};

            virtual void   indicateto(timeouttype val)           {
                gets()->indicateto(val);
                in_cangeset(MASK_GR_CHANGE_INDTO);};

            virtual timeouttype  indicateto()   const            {
                return exists() ? gets()->indicateto() : 0;};

            virtual lcltype local() const {
                return exists() ? gets()->local() : 0;};

            virtual void local(lcltype val )  {
                gets()->local(val);
                in_cangeset(MASK_GR_CHANGE_LOCAL);};

            virtual subcripttype synctype() const  {
                return exists() ? gets()->synctype() : 0;};

            virtual void synctype(subcripttype val ) {
                gets()->synctype(val);
                in_cangeset(MASK_GR_CHANGE_SYNCTYPE);};

            virtual intfvertype ver() const {
                return exists() ? gets()->ver() : 0;};

            virtual void ver(intfvertype val ) {
                gets()->ver(val);
                in_cangeset(MASK_GR_CHANGE_VER);};

            virtual bool supporttype() const {
                return exists() ? gets()->supporttype() : 0;};

            virtual void supporttype(bool val ) {
                gets()->supporttype(val);
                in_cangeset(MASK_GR_CHANGE_SUPTP);};

            virtual vlvtype valid()  const                 {
                return exists() ? gets()->valid() : 0;};

        private:

            group_data* get(indx val) const {
                indx_groups_map::iterator it = map->find(val);
                return (it != map->end()) ? &it->second : NULL;}

            pgroupstruct getstruct(group_data* val) const {
                return (groupstruct*) (&val->groupinfo);}

            pgroupstruct gets() const {
                return getstruct(get(key_));}

            group_data* gets_() const {
                return get(key_);}

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            indx_groups_map* map;
            indx key_;} ;

        class remoteagroupintf : public agroupintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remoteagroupintf(indx_agroups_map* mappack) : agroupintf() {
                map = mappack;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx  key() const {
                return key_;};

            bool exists() const {
                return ((map) && (get(key_)));}

            virtual pagroupstruct _struct() {
                return exists() ? gets() : 0;};

            agroup_data* get(indx val) const {
                indx_agroups_map::iterator it = map->find(val);
                return (it != map->end()) ? &it->second : 0;}

            virtual void         name(const std::string& val) {
                gets_()->name = val;
                in_cangeset(MASK_AGR_CHANGE_NAME);};

            virtual std::string  name()  const         {
                return exists() ? gets_()->name : "";};

            virtual void         headername(const std::string& val) {
                gets_()->headername = val;
                in_cangeset(MASK_AGR_CHANGE_HEADNAME);};

            virtual std::string  headername()  const         {
                return exists() ? gets_()->headername : "";};

        private:

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            pagroupstruct getstruct(agroup_data* val) const {
                return (pagroupstruct) (&val->agroupinfo);}

            pagroupstruct gets() const {
                return getstruct(get(key_));}

            agroup_data* gets_() const {
                return get(key_);}

            indx_agroups_map* map;
            indx key_;} ;

        class remoteuserintf : public userintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remoteuserintf(indx_users_map* mappack) : userintf() {
                map = mappack;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx  key() const {
                return key_;};

            bool exists() const {
                return ((map) && (get(key_)));}

            virtual void         name(const std::string& val) {
                if (exists()) {
                    gets_()->name = val;
                    in_cangeset(MASK_USER_CHANGE_NAME);}};

            virtual std::string  name()  const {
                return exists() ? gets_()->name : "";};

            virtual void         password(const std::string& val) {
                if (exists()) {
                    gets_()->password = val;
                    in_cangeset(MASK_USER_CHANGE_PASSWORD);}};

            virtual std::string  password() const           {
                return exists() ? gets_()->password : "";};
                
            virtual void         filter(const std::string& val) {
                if (exists()) {
                    gets_()->filter = val;
                    in_cangeset(MASK_USER_CHANGE_PASSWORD);}};

            virtual std::string  filter() const           {
                return exists() ? gets_()->filter : "";};
             
                    
            virtual void         accesslevel(acclevtype val) {
                if (exists()) {
                    gets_()->accesslevel = static_cast<num64> (val);
                    in_cangeset(MASK_USER_CHANGE_LEVEL);}};

            virtual acclevtype   accesslevel() const        {
                return exists() ? static_cast<acclevtype> (gets_()->accesslevel) : 0;};                    
                
                

            virtual void         role(rolesettype val) {
                if (exists()) {
                    gets_()->role = static_cast<num64> (val);
                    in_cangeset(MASK_USER_CHANGE_ROLE);}};

            virtual acclevtype   role() const        {
                return exists() ? static_cast<rolesettype> (gets_()->role) : 0;};

        private:

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            user_data* get(indx val) const {
                indx_users_map::iterator it = map->find(val);
                return (it != map->end()) ? &it->second : 0;}

            user_data* gets_() const {
                return get(key_);}

            indx_users_map* map;
            indx key_;} ;



        class remoteaccessruleintf : public accessruleintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remoteaccessruleintf(indx_accessrules_map* mappack) : accessruleintf() {
                map = mappack;};

            virtual void  key(indx val) {
                key_ = val;};

            virtual indx  key() const {
                return key_;};

            bool exists() const {
                return ((map) && (get(key_)));}

            virtual void   name(const std::string& val) {
                if (exists()) {
                    gets_()->name = val;
                    in_cangeset(MASK_AR_CHANGE_NAME);}};

            virtual std::string  name() const {
                return exists() ? gets_()->name : "";};

            virtual void   user(const std::string& val) {
                if (exists()) {
                    gets_()->user = val;
                    in_cangeset(MASK_AR_CHANGE_USER);}};

            virtual std::string  user() const {
               return exists() ? gets_()->user : "";};

            virtual void   host(const std::string& val) {
                if (exists()) {
                    gets_()->host = val;
                    in_cangeset(MASK_AR_CHANGE_HOST);}};

            virtual std::string  host() const {
               return exists() ? gets_()->host : "";};
               
            virtual void   filter(const std::string& val) {
                if (exists()) {
                    gets_()->filter = val;
                    in_cangeset(MASK_AR_CHANGE_FILTER);}};

            virtual std::string  filter() const {
               return exists() ? gets_()->filter : "";};
               

            virtual void   appid(appidtype val){
                if (exists()) {
                    gets_()->appid = static_cast<num64>(val);
                    in_cangeset(MASK_AR_CHANGE_APPID);}};

            virtual appidtype appid()  const {
               return exists() ? static_cast<appidtype>(gets_()->appid) : 0;};
               
            virtual void   protocol(protocoltype val){
                if (exists()) {
                    gets_()->protocol = static_cast<num64>(val);
                    in_cangeset(MASK_AR_CHANGE_PROT);}};

            virtual protocoltype protocol() const {
               return exists() ? static_cast<protocoltype>(gets_()->protocol) : 0;};                
               

            virtual void   accessrule(accessruletype val){
                if (exists()) {
                    gets_()->accessrule = static_cast<num64>(val);
                    in_cangeset(MASK_AR_CHANGE_RULE);}};

            virtual accessruletype accessrule() const {
               return exists() ? static_cast<accessruletype>(gets_()->accessrule) : 0;};

            virtual void   accesslevel(acclevtype val){
                if (exists()) {
                    gets_()->accesslevel = static_cast<num64>(val);
                    in_cangeset(MASK_AR_CHANGE_AL);}};

            virtual acclevtype accesslevel() const {
               return exists() ? static_cast<acclevtype>(gets_()->accesslevel) : 0;};
               
            virtual void   role(rolesettype val){
                if (exists()) {
                    gets_()->role = static_cast<num64>(val);
                    in_cangeset(MASK_AR_CHANGE_ROLE);}};

            virtual rolesettype role() const {
               return exists() ? static_cast<rolesettype>(gets_()->role) : 0;};               

        private:

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            accessrule_data* get(indx val) const {
                indx_accessrules_map::iterator it = map->find(val);
                return (it != map->end()) ? &it->second : 0;}

            accessrule_data* gets_() const {
                return get(key_);}

            indx_accessrules_map* map;
            indx key_;} ;

        class remotemetaintf : public metaintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:
            remotemetaintf(entitytype_metamaps_maps* maps_);

            bool exists() const {
                return ((maps) && (get(_type, _id)));}

            meta_data* get(nodetype type_, indx val) const {
                entitytype_metamaps_maps::iterator it = maps->find(type_);
                if (it != maps->end()) {
                    indx_metaitem_map* metasmap_tmp = &it->second;
                    indx_metaitem_map::iterator it1 = metasmap_tmp->find(val);
                    return (it1 != metasmap_tmp->end()) ? &it1->second : 0;}
                else
                    return 0;}

            void set(nodetype type_, indx val, meta_data& mf_) {
                entitytype_metamaps_maps::iterator it = maps->find(type_);
                if (it != maps->end()) {
                    indx_metaitem_map* metasmap_tmp = &it->second;
                    if (metasmap_tmp) {
                        if (metasmap_tmp->find(val) != metasmap_tmp->end())
                            metasmap_tmp->operator [](val) = mf_;
                        metasmap_tmp->insert(indx_metaitem_pair(val, mf_));};}}

            void in_cangeset(int num) {
                if (num > 31) return;
                get(_type, _id)->changeset = (get(_type, _id)->changeset | (0x1LL << num));}

            virtual void  key(nodetype type_, indx val) {
                _type = type_;
                _id = val;
                curitem = 0;};

            virtual std::string  property(const std::string&  prop) const {
                if (!exists()) return "";
                int pr_id = propertyid(prop);
                return ((pr_id >= 0) && (pr_id < 20)) ? get(_type, _id)->str_data[pr_id] : "";}

            virtual void  property(const std::string& prop, const std::string&  val) {
                if (!exists()) return;
                int pr_id = propertyid(prop);
                if (pr_id < 0) return;
                if ((pr_id >= 0) && (pr_id < 20)) {
                    get(_type, _id)->str_data[pr_id] = val;
                    in_cangeset(pr_id);}}


        private:
            nodetype _type;
            indx _id;
            entitytype_metamaps_maps* maps;
            meta_data* curitem;} ;

        class remoteregistryintf : public registryintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remoteregistryintf( remoteadminintf& intf_) : registryintf() , rintf(intf_) {};

        protected:

            virtual size_t load();

            remoteadminintf& rintf;} ;

        class remoteclientsintf  : public clientsintf  {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remoteclientsintf ( remoteadminintf& intf_) : clientsintf() , rintf(intf_) {};


        protected:

            virtual size_t load();

            remoteadminintf& rintf;} ;

        class remotealarmsintf : public alarmsintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotealarmsintf(remoteadminintf& intf_) : alarmsintf() , rintf(intf_) {};

        protected:

            virtual size_t load(const std::string& grp = "", const std::string& agrp = "");

            remoteadminintf& rintf;} ;

        class remotecommandintf : public commandintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotecommandintf(remoteadminintf& intf_) : commandintf() , rintf(intf_) {};

        protected:

            virtual size_t load(const std::string& grp = "");

            remoteadminintf& rintf;} ;

        class remotejournalintf : public journalintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotejournalintf(remoteadminintf& intf_) : journalintf() , rintf(intf_) {};


        protected:

            virtual size_t load(const std::string& agroup = "");

            remoteadminintf& rintf;} ;

        class remotedebugintf : public debugintf {
            friend class remoteadminintf;
            friend class adminintf;

        public:

            remotedebugintf(remoteadminintf& intf_) : debugintf() , rintf(intf_) {};


        protected:

            virtual size_t load(debuglvtype lev = 0);

            remoteadminintf& rintf;} ;

        class remoteserviceintf : public serviceintf {
        public:

            remoteserviceintf(indx_services_map* mappack) : serviceintf() {
                map = mappack;};

            virtual void  number(indx val) {
                number_ = val;}

            virtual indx number() const {
                return number_;}

            service_data* get(indx val) const {
                indx_services_map::iterator it = map->find(val);
                return (it != map->end()) ? &it->second : 0;}

            service_data* gets_() const {
                return get(number_);}

            bool exists() const {
                return ((map) && (get(number_)));}

            void in_cangeset(num64 mask) {
                gets_()->changeset = ((gets_()->changeset) | mask);}

            virtual std::string displayname() const {
                return exists() ? gets_()->name : "";}

            virtual std::string path() const {
                return exists() ? gets_()->path : "";}

            virtual num64 starttype() const {
                return exists() ? gets_()->starttype : 0;}

            virtual void starttype(num64 val) {
                if (exists()) {
                    gets_()->starttype = val;
                    in_cangeset(MASK_GR_CHANGE_STARTTP);};}

            virtual num64 status() const   {
                return 0;}

            virtual void status(num64 val) {
                ;}
        private:
            indx_services_map* map;
            indx number_;} ;

        class remoteadminintf : public adminintf {
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

            remoteadminintf(std::string host_, std::string port_, unsigned int timout = DEFAULT_DVNCI_TIMOUT);

            virtual ~remoteadminintf () {};

            virtual bool islocal() const {
                return false;}

            virtual std::string named() const{
                return (host_ + ":" + port);}

            virtual void fullnamed(std::string val) {
                parse_servinfo( val, host_, port , timeout, adminname, adminpassword);}

            virtual std::string fullnamed() const {
                return generate_servinfo(host_, port, timeout, adminname, adminpassword);}

            virtual bool connect(const std::string& user = "", const std::string& password = "") {
                clearerrors();
                if (_state == adminintf::connected) {
                    return true;}
                connect_(user, password);
                return (_state == adminintf::connected);};

            virtual bool disconnect() {
                clearerrors();
                if (_state == adminintf::disconnected) {
                    return true;}
                disconnect_();
                return (_state == adminintf::disconnected);};

            virtual ns_error select_entities(nodetype parenttp, iteminfo_map& mappack, indx parentid,
                    const std::string&  strcriteria = "" ,  bool clearer = true);

            virtual ns_error load_entities(nodetype ittp,  indx_set& idset);

            virtual ns_error merge_entities(nodetype ittp,  indx_set& idset, iteminfo_map& mappack);

            virtual ns_error insert_entity(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
                    std::string  newname_ = "" );

            virtual ns_error delete_entities(nodetype ittp, const indx_set& idset);

            virtual ns_error duplicate_entity(nodetype ittp,  indx id,  const std::string& newname, iteminfo_pair& pairpack);

            virtual ns_error merge_entities(nodetype ittp,  const indx_set&  idset) {
                return true;}

            virtual ns_error change_parent_entities(nodetype ittp, indx_set& idset, indx parentid);

            virtual std::string  conf_property(const confproptype&  name) const ;

            virtual int conf_numproperty(const confproptype&  name);

            virtual void conf_property(const confproptype&  name, const std::string&  val);

            virtual void conf_property(const confproptype&  name, int val);

            virtual bool operation_setvalue(indx id, const std::string& val, vlvtype valid);

            virtual bool operation_setvalid(indx id, vlvtype valid);

            virtual bool operation_setallvalid(vlvtype valid);

            virtual bool operation_setcounter(indx id, bool inc = true);

            virtual bool operation_setallcounter(bool inc = true);

            virtual bool operation_kvit();

            virtual bool operation_kvitgroup(indx id);

            virtual bool operation_kvitagroup(indx id);

            virtual bool operation_startservice(appidtype val);

            virtual bool operation_stopservice(appidtype val);

            virtual ns_error operation_autorizate(const std::string& user = "", const std::string& password = "",
                                                  const std::string& hst = "localhost", const std::string& ipadr = "localhost");

            virtual void host(std::string hst, std::string prt, unsigned int timout = DEFAULT_DVNCI_TIMOUT) {
                host_ = hst;
                port = prt;
                timeout = timout;}



        protected:


            virtual ns_error entities_internal_signature(nodetype ittp, indx_set& idset, iteminfo_map& mappack,
                    const std::string&  strcriteria = "");

            ns_error readtags(indx_set& idset);

            ns_error readgroups(indx_set& idset);

            ns_error readagroups(indx_set& idset);

            ns_error readusers(indx_set& idset);

            ns_error readaccessrules(indx_set& idset);

            ns_error readservices(indx_set& idset);

            ns_error readmetas(nodetype ittp, indx_set& idset);

            ns_error readconfig(indx_set& idset);


            bool tags(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria = "" );

            bool groups(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria = "" );

            bool agroups(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria = "") ;

            bool users(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria = "");

            bool metas(nodetype ittp, iteminfo_map& mappack, indx_set& idset, std::string  strcriteria = "");



            ns_error sendtags(indx_set& idset);

            ns_error sendgroups(indx_set& idset);

            ns_error sendagroups(indx_set& idset);

            ns_error sendusers(indx_set& idset);

            ns_error sendaccessrules(indx_set& idset);

            ns_error sendservices(indx_set& idset);

            ns_error sendmetas(nodetype ittp, indx_set& idset);

            ns_error sendconfig(indx_set& idset);


            bool changeparenttag( indx_set& idset, indx parentid);

            bool changeparentatag( indx_set& idset, indx parentid);


            ns_error executeoperation(req_adminoperation& operat);

            void releaseconnection();

            size_t alarms_net_req(vect_alarms_data& vect, guidtype& vers, const std::string& agroup = "", const std::string& group = "");

            size_t commands_net_req(vect_commands_data& vect, guidtype& vers, const std::string& grp = "");

            size_t regs_net_req(vect_registry_data& vect, guidtype& vers);

            size_t clients_net_req(vect_clients_data& vect, guidtype& vers);

            size_t debug_net_req(vect_debug_data& vect, guidtype& guid, size_t& curs, size_t& cnt );

            size_t journal_net_req(vect_journal_data& vect, guidtype& guid, size_t& curs, size_t& cnt);


            bool connect_(std::string user = "", std::string password = "");

            bool disconnect_();

            template<class _REQSTRUCT, class _RESPSTRUCT, num16 _reqtp, num16 _resptp>
            bool querytmpl(_REQSTRUCT& reqstruct_, _RESPSTRUCT& respstruct_) {


                std::ostringstream out_archive_stream(std::ostringstream::binary);
                std::istringstream in_archive_stream(std::istringstream::binary);
                prb_binary_oarchive out_archive(out_archive_stream);

                out_archive << reqstruct_;
                dvnci::rpc::rpcmessage out_mess(out_archive_stream.str(), _reqtp);
                dvnci::rpc::rpcmessage in_mess;
                client_io->req(out_mess, in_mess);

                if (in_mess.type() == _resptp) {

                    in_archive_stream.str(in_mess.message());

                    prb_binary_iarchive in_archive(in_archive_stream);
                    in_archive >> respstruct_;}
                else {
                    if (in_mess.type() == RPC_OPERATION_ERROR_OUTSIDE) {
                        error_outside tmperr;
                        in_archive_stream.str(in_mess.message());
                        prb_binary_iarchive in_archive(in_archive_stream);
                        in_archive >> tmperr;
                        dvncierror err(static_cast<ns_error> (tmperr.error));
                        adderror(err);}}

                return true;};


        private:

            indx_groups_map groups_map;
            indx_tags_map     tags_map;
            indx_agroups_map agroups_map;
            indx_users_map users_map;
            indx_accessrules_map accessrules_map;
            entitytype_metamaps_maps meta_maps;
            iteminfo_map key_name_map;
            indx_services_map services_map;
            indx  globalnum_journalmap_;
            indx  globalnum_alarmsmap_;
            indx  globalnum_logmap_;
            indx  globalnum_commandmap_;
            indx  count_journalmap_;
            indx  count_alarmsmap_;
            indx  count_logmap_;
            indx  count_commandmap_;

            std::string host_;
            std::string port;
            config_data config_;
            dvnci::rpc::rpcioclient_ptr client_io;

            void parseerror(dvncierror& err);
            void parseundeferror();} ;}}

#endif	/* _KERNEL_NSREMOTEINTERFACE_H */

