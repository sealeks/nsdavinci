/* 
 * File:   memfile.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 29 ??????? 2009 ?., 15:25
 */

#ifndef _DVNCI_KRNL_MEMFILE_H
#define	_DVNCI_KRNL_MEMFILE_H


#include <kernel/constdef.h>
#include <kernel/mainstruct.h>
#include <kernel/templ.h>
#include <kernel/cyclic_table_templ.h>
#include <kernel/static_table_templ.h>
#include <kernel/index_base.h>
#include <kernel/bufferbase_templ.h>
#include <kernel/stringvalue_base.h>
#include <kernel/filebase_templ.h>


namespace dvnci {

    const size_t EXTEND_MEMSHARE_TAG_SIZE = EXTEND_MEMSHARE_TAGCNT * sizeof (tagstruct);
    const size_t EXTEND_MEMSHARE_GRP_SIZE = EXTEND_MEMSHARE_GRPCNT * sizeof (groupstruct);
    const size_t EXTEND_MEMSHARE_AGRP_SIZE = EXTEND_MEMSHARE_AGRPCNT * sizeof (agroupstruct);
    const size_t EXTEND_MEMSHARE_USER_SIZE = EXTEND_MEMSHARE_USERCNT * sizeof (userstruct);
    const size_t EXTEND_MEMSHARE_ACCESSRUL_SIZE = EXTEND_MEMSHARE_ACCESSRULCNT * sizeof (accessrulestruct);
    const size_t EXTEND_MEMSHARE_STR_SIZE = EXTEND_MEMSHARE_STRCNT * EXTEND_MEMSHARE_STRMDL;
    const size_t EXTEND_MEMSHARE_STRSTATIC_SIZE = EXTEND_MEMSHARE_STRSTATICCNT * EXTEND_MEMSHARE_STRSTATIC;

    class tagsbase;
    class groupsbase;
    class agroupsbase;
    class accessrulesbase;
    class usersbase;
    class staticmemorymap;
    class filememorymap;

    void test_immi_struct();

    typedef membase_sync_ptr_tmpl<tagsbase>                     tagsbase_ptr;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Ciclyc Structure
    /////////////////////////////////////////////////////////////////////////////////////////////

    class journalbase : public cyclicbasemem<journalsstruct> {
        friend class tagsbase;

    public:

        journalbase(ptagsbase intf_ptr, const std::string& mapname, size_t maxcnt = MAX_NUM32_SIGNED) :
        cyclicbasemem<journalsstruct>(mapname, maxcnt) {
            tgbs_ptr = intf_ptr;}

        datetime time(size_type id) const {
            return operator[](id)->time();};

        datetime time_retrosp(size_type id) const {
            return  operator()(id)->time();};

        msgtype type(size_type id) const {
            return operator[](id)->type();};

        msgtype type_retrosp(size_type id) const {
            return operator()(id)->type();};

        altype level(size_type id) const {
            return operator[](id)->level();};

        altype level_retrosp(size_type id) const {
            return operator()(id)->level();};

        size_type tagid(size_type id) const {
            return operator[](id)->tagid();};

        altype tagid_retrosp(size_type id) const {
            return operator()(id)->tagid();};

        std::string text(size_type id) const ;

        std::string text_retrosp(size_type id) const ;

        std::string tag(size_type id) const;

        std::string tag_retrosp(size_type id) const ;

        size_type agroup(const std::string& nm) const;

    protected:

        void add(const datetime& tm, size_type tgid, msgtype tp, altype lev = altNone, const double& val = NULL_DOUBLE, size_type userid = npos);

    private:

        std::string  agroupname(size_type id) const;

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& gid, size_t& curs, size_t& cnt) const {

            INP_EXCLUSIVE_LOCK(memlock());
            vect.clear();
            curs = (cursor() != npos) ? static_cast<size_t> (cursor()) : 0;
            cnt  = (count()  != npos)  ? static_cast<size_t> (count()) : 0;

            guidtype maxgid = gid;
            size_type strt1 = find_guid_morethen(gid, 0, cursor());
            size_type strt2 = find_guid_morethen(gid, cursor(), count());

            if (strt1 != npos)
                fillvect<T, B > (vect, maxgid, strt1, cursor());
            if (strt2 != npos)
                fillvect<T, B > (vect, maxgid, strt2, count());

            gid = maxgid;
            return vect.size();}

        template<typename T, typename B>
        void fillvect(std::vector<T>& vect, guidtype& maxgid, size_type b, size_type e) const {
            if ((b != npos) && (e <= count())) {
                for (size_type i = b; i < e; ++i) {
                    guidtype tmpgid = guid(i);
                    maxgid = (maxgid < tmpgid) ? tmpgid : maxgid;
                    vect.push_back(rowline<T, B > (i, tmpgid));}}};

        template<typename T, typename B>
        T rowline(size_type i, guidtype gid) const {
            datetime tm = time(i);
            T tmp  = {static_cast<B> (i), gid, tm, tag (i) , text(i), agroupname(i),
                static_cast<B> (type(i)), static_cast<B> (level(i)), std::string(""), std::string("")};
            return tmp;}

        ptagsbase tgbs_ptr;} ;

    ////////////////////////////////////////////////////////////////////////////

    class debugbase : public cyclicbasemem<debugsstruct> {
        friend class tagsbase;

    public:

        debugbase(const std::string& mapname, size_t maxcnt = MAX_NUM32_SIGNED) :
        cyclicbasemem<debugsstruct>(mapname, maxcnt) {}

        datetime time(size_type id) const {
            return operator[](id)->time();};

        datetime time_retrosp(size_type id) const {
            return operator()(id)->time();};

        std::string message(size_type id) const {
            return operator[](id)->message();};

        std::string message_retrosp(size_type id) const {
            return operator()(id)->message();};

        debuglvtype level(size_type id) const {
            return operator[](id)->level();};

        debuglvtype level_retrosp(size_type id) const {
            return operator()(id)->level();};

        appidtype appid(size_type id) const {
            return operator[](id)->appid();};

        appidtype appid_retrosp(size_type id) const {
            return operator()(id)->appid();};

    protected:

        void add(const datetime& tm, const std::string& mess, debuglvtype lev, appidtype app = 0) {
            INP_EXCLUSIVE_LOCK(memlock());
            size_type newind = inc();
            new (operator[](newind)) debugstruct(gloubnum(), tm, mess, lev, app);}

    private:

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& gid, size_t& curs, size_t& cnt) const {

            INP_EXCLUSIVE_LOCK(memlock());
            vect.clear();
            curs = (cursor() != npos) ? static_cast<size_t> (cursor()) : 0;
            cnt  = (count() != npos)  ? static_cast<size_t> (count()) : 0;

            guidtype maxgid = gid;
            size_type strt1 = find_guid_morethen(gid, 0, cursor());
            size_type strt2 = find_guid_morethen(gid, cursor(), count());

            if (strt1 != npos)
                fillvect<T, B > (vect, maxgid, strt1, cursor());
            if (strt2 != npos)
                fillvect<T, B > (vect, maxgid, strt2, count());

            gid = maxgid;
            return vect.size();}

        template<typename T, typename B>
        void fillvect(std::vector<T>& vect, guidtype& maxgid, size_type b, size_type e) const {
            if ((b != npos) && (e <= count())) {
                for (size_type i = b; i < e; ++i) {
                    guidtype tmpgid = guid(i);
                    maxgid = (maxgid < tmpgid) ? tmpgid : maxgid;
                    vect.push_back(rowline<T, B > (i, tmpgid));}}};

        template<typename T, typename B>
        T rowline(size_type i, guidtype gid) const {
            datetime tm = time(i);
            T tmp = {static_cast<B> (i), gid, tm , message (i) ,
                static_cast<B> (level(i)), static_cast<B> (appid(i))};
            return tmp;}} ;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Deletable line Table Structure
    /////////////////////////////////////////////////////////////////////////////////////////////

    class alarmsbase : public livebasemem< alarmssstruct> {
        friend class tagsbase;

    public:

        alarmsbase(ptagsbase intf_ptr, const std::string& mapnm, size_t maxcnt = MAX_NUM32_SIGNED) :
        livebasemem< alarmssstruct>(mapnm, maxcnt), tgbs_ptr(intf_ptr) {
            ;}

        size_type tagid(size_type id) const {
            return operator[](id)->tagid();};

        datetime time(size_type id) const {
            return operator[](id)->time();};

        bool kvit(size_type id) const {
            return operator[](id)->kvit();};

        bool off(size_type id) const {
            return operator[](id)->off();};

        altype level(size_type id) const {
            return operator[](id)->level();};

        msgtype type(size_type id) const {
            return operator[](id)->type();}

        std::string text(size_type id) const ;

        std::string tag(size_type id) const;

        std::string value(size_type id) const {
            return operator[](id)->value();}

        size_type group(size_type id) const {
            return operator[](id)->group();};

        size_type agroup(size_type id) const {
            return operator[](id)->agroup();};

    private:

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& vers, size_type agrpindx = npos, size_type grpindx = npos) const {

            INP_EXCLUSIVE_LOCK(memlock());

            if (vers == version()) return vect.size();

            vect.clear();

            bool filtereda =  (agrpindx != npos);
            bool filteredg =  (grpindx != npos);
            bool filtered = filtereda || filteredg;


            size_type i = npos;
            for (size_type j = 0; j < count(); ++j) {
                i = reverse_index(j);
                if ((!filtered) || ((filtered) && (filtereda && (agrpindx == agroup(i))) || (filteredg && (grpindx == group(i))))) {
                    datetime tm = time(i);
                    T tmp = {tm , tag (i) , text(i),
                        static_cast<B> (kvit(i)), static_cast<B> (level(i)), static_cast<B> (type(i)), value(i)};
                    vect.push_back(tmp);}}
            vers = version();
            return vect.size();}

        void kvit(size_type id, bool val) {
            if (exists(id)) operator[](id)->kvit(val);};

        void time(size_type id, const datetime& tm) {
            if (exists(id)) operator[](id)->time(tm);};

        void add(const datetime& tm, size_type id, msgtype msgtp = msNew, const double& val = NULL_DOUBLE);

        void remove(size_type id);

        void kvitall();

        void kvit_agroup(size_type agrnum);

        void kvit_group(size_type grnum);

        void kvit_tag(size_type id);

        void checkout();

        size_type find_by_tagid(size_type id);

        ptagsbase tgbs_ptr;} ;

    ////////////////////////////////////////////////////////////////////////////

    class commandsbase : public livebasemem< commandsstruct>  {
        friend class tagsbase;

    public:

        commandsbase(ptagsbase intf_ptr, const std::string& mapnm, size_t maxcnt = MAX_NUM32_SIGNED) :
        livebasemem< commandsstruct>(mapnm, maxcnt), tgbs_ptr(intf_ptr) {}

        size_type tagid(size_type id) const {
            return (exists(id)) ? operator[](id)->tagid() : npos;};

        std::string tag(size_type id) const ;

        std::string groupname(size_type id) const ;

        std::string user(size_type id) const ;

        std::string host(size_type id) const;

        datetime time(size_type id) const {
            return operator[](id)->time();};

        bool executed(size_type id) const {
            return operator[](id)->executed();};

        std::string value_before_str(size_type id) const {
            return operator[](id)->value_before_str() ;};

        std::string value_str_set(size_type id) const {
            return operator[](id)->value_str_set() ;};

        num64 value_before(size_type id) const {
            return operator[](id)->value_before<num64 > ();};

        num64 value_set(size_type id) const {
            return operator[](id)->value_set<num64 > ();};

        size_type group(size_type id) const {
            return operator[](id)->group();};

    protected:

        addcmdtype add(size_type id, num64 preval, num64 val, tagtype tp, addcmdtype queue = acQueuedCommand, guidtype clid = 0);

        addcmdtype add(size_type id, const std::string& val,  addcmdtype queue = acQueuedCommand, guidtype clid = 0);

        bool select_commands(command_vector& vect_, size_type group = npos);

        bool select_commands(command_vector& vect_, indx_set groups);

        bool clear_commands(size_type group = npos);

        void checkout();

        size_type find_by_tagid(size_type id);

    private:

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& vers, size_type grpindx = npos) const {

            INP_EXCLUSIVE_LOCK(memlock());

            if (vers == version()) return vect.size();

            vect.clear();

            bool filtered = (grpindx != npos);

            size_type i = npos;
            for (size_type j = 0; j < count(); ++j) {
                i = reverse_index(j);
                if ((!filtered) || (grpindx == npos) || (grpindx = group(i))) {
                    datetime tm = time(i);
                    T tmp = {tm , tag (i) , groupname(i), value_before_str(i),
                        value_str_set(i), user(i), host(i)};
                    vect.push_back(tmp);}}

            vers = version();
            return vect.size();}

        ptagsbase tgbs_ptr;} ;

    ////////////////////////////////////////////////////////////////////////////

    class registrybase : public livebasemem< registrysstruct> {
        friend class tagsbase;
        typedef boost::shared_ptr<boost::mutex> mutex_ptr;

    public:

        registrybase(ptagsbase intf_ptr, const std::string& mapnm, size_t maxcnt = 0x400) :
        livebasemem< registrysstruct>(mapnm, maxcnt), tgbs_ptr(intf_ptr) {
            mutex_ = mutex_ptr( new boost::mutex());
            selfhadle_ = 0;
            lastguid_ = 0;}

        std::string name(size_type id) const {
            return ((exists(id)) && (queuehandle(id))) ? ("queue" + to_str(queuehandle(id))) : "";};

        appidtype appid(size_type id) const {
            return operator[](id)->appid();};

        guidtype handle(size_type id) const {
            return operator[](id)->guid();};

        eventtypeset evset(size_type id) const {
            return operator[](id)->eventsset();};

        guidtype queuehandle(size_type id) const {
            return operator[](id)->handle();};

        guidtype selfhadle() const {
            return selfhadle_;};



    protected:

        guidtype reghandle(appidtype app, eventtypeset evts);

        guidtype unreghandle(guidtype id);

        void notify_valid(size_type id) {
            notify(MSG_DVNCIVALID, id, 0, sIMMIValid);}

        void notify_log(size_type id, bool vl) {
            notify(MSG_DVNCLOG, id, vl ? 1 : 0, sIMMILog);}

        void notify_journal(size_type line) {
            notify(MSG_DVNCJOURNAL, line, 0, sIMMIJournal);}

        void notify_commands(size_type id) {
            notify(MSG_DVNCICOMMAND, id, 0, sIMMICommand);}

        void notify_newref(size_type id, size_type pid) {
            notify(MSG_DVNCINEWREF, id, static_cast<num32> (pid), sIMMITagManage);}

        void notify_remref(size_type id, size_type pid) {
            notify(MSG_DVNCIREMREF, id, static_cast<num32> (pid), sIMMITagManage);}

        void notify_debug() {
            notify(MSG_DVNCDEBUG, 0, 0, sIMMIDebug);}

        void notify_tagmanage(qumsgtype mess, size_type id, size_type group) {
            notify(mess, id, static_cast<num32> (group), sIMMITagManage);}

        void notify_groupmanage(qumsgtype mess, size_type id, num32 some) {
            notify(mess, id, some, sIMMIGroupManage);}

        void notify_dbmanage(qumsgtype mess) {
            notify(mess, 0, 0, sIMMIDBManage);}


    private:

        boost::mutex&  mtx() const {
            return (*mutex_);}

        guidtype              selfhadle_;
        mq_class_ptr          self_mq;
        evst_indxmqmap_map    ev_mqs_map;
        guid_mq_map           guid_mqs_mp;
        guidtype              lastguid_;
        mutex_ptr             mutex_;

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& vers) const {

            INP_EXCLUSIVE_LOCK(memlock());

            if (vers == version()) return vect.size();

            vect.clear();

            size_type i = npos;
            for (size_type j = 0; j < count(); ++j) {
                i = reverse_index(j);
                T tmp = {static_cast<B> (handle(i)), static_cast<B> (appid(i)) , static_cast<B> (evset(i)), static_cast<B> (queuehandle(i))};
                vect.push_back(tmp);}

            vers = version();
            return vect.size();}

        void notify(qumsgtype mess, size_type id, num32 some, eventtypeset event);

        mq_class_ptr getproccessqueue(guidtype val);

        void rebuild_messageset();

        void removeproccessqueue(const guidtype_set& mset);

        ptagsbase tgbs_ptr;} ;

    ////////////////////////////////////////////////////////////////////////////

    class clientbase : public livebasemem< clientsstruct> {
        class client_registrator;

        friend class client_registrator;
        friend class tagsbase;

        typedef boost::shared_ptr<boost::mutex> mutex_ptr;

        class client_registrator {
        public:

            client_registrator(clientbase& prnt) : parent(prnt) {}

            ~client_registrator() {
                erase();}

            void insert(guidtype vl) {
                sets.insert(vl);}

            void eraise(guidtype vl) {
                if (sets.find(vl) != sets.end())
                    sets.erase(vl);}

        private:

            void erase() {
                for (guidtype_set::const_iterator it = sets.begin(); it != sets.end(); ++it) {
                    parent.unregclient_from_set(*it);}
                sets.clear();}
            clientbase&   parent;
            guidtype_set  sets;} ;

        typedef boost::shared_ptr<client_registrator>  client_registrator_ptr;

    public:

        clientbase(ptagsbase intf_ptr, const std::string& mapnm, size_t maxcnt = 0x400) :
        livebasemem< clientsstruct>(mapnm, maxcnt), tgbs_ptr(intf_ptr) {
            mutex_ = mutex_ptr( new boost::mutex());
            clientscls = client_registrator_ptr(new client_registrator(*this));}

        std::string name(size_type id) const {
            return exists(id) ? ("client" + to_str(id)) : "";};

        std::string host(size_type id) const {
            return operator[](id)->host();};

        std::string ip(size_type id) const {
            return operator[](id)->ip();};

        std::string user(size_type id) const {
            return operator[](id)->username();};

        appidtype appid(size_type id) const {
            return operator[](id)->appid();};

        size_type ruleid(size_type id) const {
            return operator[](id)->ruleid();};

        acclevtype accesslevel(size_type id) const {
            return operator[](id)->accesslevel();};

    protected:

        guidtype regclient(appidtype app, const std::string& hst = "", const std::string& ipp = "", const std::string& usr = "",  const std::string& password = "");

        guidtype unregclient(guidtype gid);


    private:

        boost::mutex&  mtx() const {
            return (*mutex_);}

        guidtype unregclient_from_set(guidtype gid);

        template<typename T, typename B>
        size_t get(std::vector<T>& vect, guidtype& vers) const {

            INP_EXCLUSIVE_LOCK(memlock());

            if (vers == version()) return vect.size();

            vect.clear();

            size_type i = npos;
            for (size_type j = 0; j < count(); ++j) {
                i = reverse_index(j);
                T tmp = {name(i), host(i), ip(i) , user(i), static_cast<B> (appid(i)),
                    static_cast<B> (accesslevel(i)), static_cast<B> (ruleid(i))};
                vect.push_back(tmp);}

            vers = version();
            return vect.size();}

        ptagsbase                tgbs_ptr;
        mutex_ptr                mutex_;
        client_registrator_ptr   clientscls;} ;

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Filepersistence Table Structure
    /////////////////////////////////////////////////////////////////////////////////////////////

    class groupsbase : public templatebase<groupsstruct> {
        friend class tagsbase;

    public:

        groupsbase(stringbase_ptr strbs, ptagsbase intf_ptr_, const fspath& basepatht) :
        templatebase<groupsstruct>(intf_ptr_, strbs, basepatht / GROUPS_FILE_NAME, GROUPS_MAP_NAME, EXTEND_MEMSHARE_GRP_SIZE) {}

        virtual ~groupsbase() {};



        // active property

        bool active(size_type id) const {
            return operator[](id)->active();}

        void active(size_type id, bool val);


        // valid property

        vlvtype valid(size_type id) const {
            return operator[](id)->valid();}

        void valid(size_type id, vlvtype val);


        // valid property  

        ns_error error(size_type id) const {
            return operator[](id)->error();}

        void error(size_type id, ns_error val) {
            if (exists(id))
                operator[](id)->error(val);}


        // valid property

        datetime time(size_type id) const {
            return operator[](id)->time();}

        std::string time_str(size_type id) const {
            return operator[](id)->time_str();}

        void time(size_type id, datetime value) {
            if (exists(id)) operator[](id)->time(value);}


        // host property

        std::string host(size_type id) const {
            return stringbase_src(operator[](id)->hostpos());}

        void host(size_type id, const std::string& val);


        // user property        

        std::string user(size_type id) const {
            return stringbase_src(operator[](id)->userpos());}

        void user(size_type id, const std::string& val);


        // password property        

        std::string password(size_type id) const {
            return stringbase_src(operator[](id)->passpos());}

        void password(size_type id, const std::string& val);


        // server property         

        std::string server(size_type id) const {
            return stringbase_src(operator[](id)->serverpos());}

        void server(size_type id, const std::string& val);


        // group property 

        std::string group(size_type id) const {
            return stringbase_src(operator[](id)->grouppos());}

        void group(size_type id, const std::string& val);


        // group property        

        std::string port(size_type id) const {
            return stringbase_src(operator[](id)->portpos());}

        void port(size_type id, const std::string& val);


        // ether property         

        std::string ether(size_type id) const {
            return stringbase_src(operator[](id)->etherpos());}

        void ether(size_type id, const std::string& val);


        // topic property   

        std::string topic(size_type id) const {
            return stringbase_src(operator[](id)->topicpos());}

        void topic(size_type id, const std::string& val);


        // appid property        

        appidtype appid(size_type id) const {
            return operator[](id)->appid();}


        // chanaltype property

        chnltype chanaltype(size_type id) const {
            return operator[](id)->chanaltype();}

        void chanaltype(size_type id, chnltype val);


        // chanalnum property

        chnlnumtype chanalnum(size_type id) const {
            return operator[](id)->chanalnum();}

        void chanalnum(size_type id, chnlnumtype val);



        // devnum property

        devnumtype devnum(size_type id) const {
            return operator[](id)->devnum();}

        void devnum(size_type id, devnumtype val);


        // devnum property

        protocoltype protocol(size_type id) const {
            return operator[](id)->protocol();}

        void protocol(size_type id, protocoltype val);


        // link property        

        metalink  link(size_type id) const {
            return exists(id) ? metalink(*operator[](id), id , host(id), user(id), password(id), server(id),
                    group(id), port(id), ether(id), topic(id)) : metalink();}


        // link property     

        subcripttype synctype(size_type id) const {
            return operator[](id)->synctype();}

        void  synctype(size_type id, subcripttype val);


        // link property  

        intfvertype ver(size_type id) const {
            return operator[](id)->ver();}

        void  ver(size_type id, intfvertype val);


        // local property          

        lcltype local(size_type id) const {
            return operator[](id)->local();}

        void local(size_type id, lcltype val);


        // deadbound property          

        double deadbound(size_type id) const {
            return operator[](id)->deadbound();}

        void deadbound(size_type id, double val) {
            if (exists(id))
                operator[](id)->deadbound(val);}


        // grouprate property   

        gratetype grouprate(size_type id) const {
            return operator[](id)->grouprate();}

        void grouprate(size_type id, gratetype val) {
            if (exists(id))
                operator[](id)->grouprate(val);}


        // blocksize property

        blksizetype blocksize(size_type id) const {
            return operator[](id)->blocksize();}

        void blocksize(size_type id, blksizetype val) {
            if (exists(id))
                operator[](id)->blocksize(val);}


        // archblocksize property    

        blksizetype archblocksize(size_type id) const {
            return operator[](id)->archblocksize();}

        void archblocksize(size_type id, blksizetype val) {
            if (exists(id))
                operator[](id)->archblocksize(val);}


        // trycount property         

        size_t trycount(size_type id) const {
            return operator[](id)->trycount();}

        void trycount(size_type id, size_t val) {
            if (exists(id))
                operator[](id)->trycount(val);}


        // utiloperation property 

        bool utiloperation(size_type id) const {
            return operator[](id)->utiloperation();}

        void utiloperation(size_type id, bool val) {
            if (exists(id))
                operator[](id)->utiloperation(val);}


        // indicateto property

        timeouttype indicateto(size_type id) const {
            return operator[](id)->indicateto();}

        void indicateto(size_type id, timeouttype val) {
            if (exists(id))
                operator[](id)->indicateto(val);}


        // timeout property       

        timeouttype timeout(size_type id) const {
            return operator[](id)->timeout();}

        void timeout(size_type id, timeouttype val) {
            if (exists(id))
                operator[](id)->timeout(val);}


        // supporttype property        

        bool supporttype(size_type id) const {
            return operator[](id)->supporttype();}

        void  supporttype(size_type id, bool val);


        // config property

        const void* config(size_type id) const {
            return operator[](id)->config();}

        void config(size_type id, void* val) {
            if (exists(id))
                memcpy((operator[](id))->config(), val, GROP_CONFIG_SIZE);}



    protected:

        static void writezero(const fspath& fpath);

        //overloaded


        virtual bool checkname(const std::string& val, size_type parnt = npos);

        virtual bool trigger_write_criteria(size_type id) const {
            return ((exists(id)) && ((appid(id) == NS_GROUP_SYSTEMVAR) || (appid(id) == NS_GROUP_SYSTEM)));}

        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos);

        virtual void uninitstruct(size_type id);


        // triggers

        virtual void trigger_add(size_type id, size_type opt = npos);

        virtual void trigger_remove(size_type id, size_type opt = npos);

        virtual void trigger_util(size_type id, const groupstruct& oldst, const groupstruct& newst);

        virtual size_type parentid(size_type id) {
            return static_cast<num64> (appid(id));}


        void notify_tagmanage(qumsgtype mess, size_type id, size_type group);

        void notify_groupmanage(qumsgtype mess, size_type id, num32 some);

        ///

        void appid(size_type id, appidtype val);

        size_type select_groups_by_appid(appidtype val);

        void clone(size_type idsrc, size_type iddst);} ;




    ///   agroupsbase 

    class agroupsbase : public templatebase<agroupsstruct> {
        friend class tagsbase;

    public:

        agroupsbase(stringbase_ptr strbs, ptagsbase intf_ptr_, const fspath& basepatht) :
        templatebase<agroupsstruct>(intf_ptr_, strbs, basepatht / ALARMGROUPS_FILE_NAME, ALARMGROUPS_MAP_NAME, EXTEND_MEMSHARE_AGRP_SIZE) {}

        virtual ~agroupsbase() {};


        // headername property

        std::string headername(size_type id) const {
            return stringbase_src(operator[](id)->headernamepos());}

        void headername(size_type id, const std::string& val);


    protected:

        static void writezero(const fspath& fpath);

        //overloaded 


        virtual bool checkname(const std::string& val, size_type parnt = npos);


        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos);

        virtual void uninitstruct(size_type id);} ;





    ///   accessrulesbase       

    class accessrulesbase : public templatebase<accessrulesstruct> {
        friend class tagsbase;

    public:

        accessrulesbase(stringbase_ptr strbs, ptagsbase intf_ptr_, const fspath& basepatht) :
        templatebase<accessrulesstruct>(intf_ptr_, strbs, basepatht / ACCESSRULES_FILE_NAME, ACCESSRULES_MAP_NAME, EXTEND_MEMSHARE_ACCESSRUL_SIZE) {}

        virtual ~accessrulesbase() {};



        // user property

        std::string user(size_type id) const {
            return stringbase_src(operator[](id)->userpos());}

        void user(size_type id, const std::string& val);
        
        
        // headername property

        std::string host(size_type id) const {
            return stringbase_src(operator[](id)->hostpos());}

        void host(size_type id, const std::string& val);        


        // headername property

        appidtype appid(size_type id) const {
            return operator[](id)->appid();}

        void appid(size_type id, appidtype val) {
            if (exists(id)) operator[](id)->appid(val);}


        // role property

        rolesettype role(size_type id) const {
            return operator[](id)->role();}

        void role(size_type id, rolesettype val) {
            if (exists(id)) operator[](id)->role(val);}


        // accesslevel property

        acclevtype accesslevel(size_type id) const {
            return operator[](id)->accesslevel();}

        void accesslevel(size_type id, acclevtype val) {
            if (exists(id)) operator[](id)->accesslevel(val);}
        
        // accessrule property

        accessruletype accessrule(size_type id) const {
            return operator[](id)->accessrule();}

        void accessrule(size_type id, accessruletype val) {
            if (exists(id)) operator[](id)->accessrule(val);}
        
        
        // protocoltype property

        protocoltype protocol(size_type id) const {
            return operator[](id)->protocol();}

        void protocol(size_type id, protocoltype val) {
            if (exists(id)) operator[](id)->protocol(val);}  


        // filter property        
        
        const ipfilter& filter(size_type id) const {
            return operator[](id)->filter();}

        void filter(size_type id, const ipfilter& val) {
             if (exists(id)) operator[](id)->filter(val);}


    protected:

        static void writezero(const fspath& fpath);


        //overloaded 


        virtual bool checkname(const std::string& val, size_type parnt = npos);


        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos);

        virtual void uninitstruct(size_type id);

        bool grant_access(appidtype app, const std::string& hst = "", const std::string& ipp = "", const std::string& usr = "",  const std::string& password = "") {
            return true;}} ;





    ///   usersbase

    class usersbase : public templatebase<usersstruct> {
        friend class tagsbase;

    public:

        usersbase(stringbase_ptr strbs, ptagsbase  intf_ptr_,  const fspath& basepatht) :
        templatebase<usersstruct>(intf_ptr_, strbs, basepatht / OPERATOR_FILE_NAME, OPERATOR_MAP_NAME, EXTEND_MEMSHARE_USER_SIZE) {}

        virtual ~usersbase() {};



        // headername property

        virtual std::string password(size_type id) const {
            return stringbase_src(operator[](id)->passpos());}

        void password(size_type id, const std::string& val) {
            if (exists(id)) {
                size_t tmp = operator[](id)->passpos();
                stringbase_src(tmp, val);
                operator[](id)->passpos(tmp);}}


        // headername property        

        acclevtype accesslevel(size_type id) const {
            return  operator[](id)->accesslevel();}

        void accesslevel(size_type id, acclevtype val) {
            if (exists(id)) {
                operator[](id)->accesslevel(val);}}
        


        // role property
        
        
        rolesettype role(size_type id) const {
            return operator[](id)->role();}

        void role(size_type id, rolesettype val) {
            if (exists(id)) operator[](id)->role(val);}
        
        
        
        // filter property        
        
        const ipfilter& filter(size_type id) const {
            return operator[](id)->filter();}

        void filter(size_type id, const ipfilter& val) {
             if (exists(id)) operator[](id)->filter(val);}        


        // headername property        

        bool changepassword(size_type id, const std::string&  newpass);

        bool changepassword(const std::string&  user, const std::string&  newpass);

        bool registrateuser(const std::string&  user, const std::string&  pass);

        acclevtype useraccesslevel(const std::string&  user);

    protected:

        static void writezero(const fspath& fpath);


        //overloaded 


        virtual bool checkname(const std::string& val, size_type parnt = npos);

        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos);

        virtual void uninitstruct(size_type id);} ;




    ///   tagsbase       

    class tagsbase : public templatebase<tagsstruct> {
        friend class groups;
        friend class agroups;
        friend class users;
        friend class groupsbase;
        friend class usersbase;
        friend class agroupsbase;
        friend class accessrulesbase;
        friend class debugbase;
        friend class commandsbase;
        friend class registrybase;
        friend class alarmsbase;
        friend class journalbase;
        friend class clientbase;
        friend class db_writer;
        friend class reporttype_executor;
        friend class trend_observer;
        friend class executor;


        typedef membase_ptr_tmpl<groupsbase>                        groupsbase_ptr;
        typedef membase_ptr_tmpl<agroupsbase>                       agroupsbase_ptr;
        typedef membase_ptr_tmpl<accessrulesbase>                   accessrulesbase_ptr;
        typedef membase_ptr_tmpl<usersbase>                         usersbase_ptr;
        typedef boost::shared_ptr<alarmsbase>                       alarmsbase_ptr;
        typedef boost::shared_ptr<journalbase>                      journalbase_ptr;
        typedef boost::shared_ptr<debugbase>                        debugbase_ptr;
        typedef boost::shared_ptr<commandsbase>                     commandsbase_ptr;
        typedef boost::shared_ptr<registrybase>                     registrybase_ptr;
        typedef boost::shared_ptr<clientbase>                       clientbase_ptr;
        typedef boost::shared_ptr<stringvalue_base>                 stringvalue_base_ptr;

        typedef valuebufferbase_templ<trend_logline>                valuebufferbase;
        typedef valuebufferbase_templ<report_logline>               reportbufferbase;
        typedef boost::shared_ptr<valuebufferbase>                  valuebufferbase_ptr;
        typedef boost::shared_ptr<reportbufferbase>                 reportbufferbase_ptr;



    private:

        static const size_type        AGROUPMASK = 0x40000000;
        static const size_type        GROUPMASK =  0x20000000;
        static const size_type        RESETMASK =  0x0FFFFFFF;

        registrybase_ptr            registry_;
        clientbase_ptr              clients_;
        commandsbase_ptr            commands_;
        journalbase_ptr             journal_;
        groupsbase_ptr              groups_;
        agroupsbase_ptr             agroups_;
        accessrulesbase_ptr         accessrules_;
        usersbase_ptr               users_;
        alarmsbase_ptr              alarms_;
        stringvalue_base_ptr        valstrb_;
        valuebufferbase_ptr         valbuffers_;
        reportbufferbase_ptr        reportbuffers_;
        debugbase_ptr               debug_;
        fspath                      fpath;
        guidtype                    handle_;
        mutable size_t              globalmemsize_;
        appidtype                   appid_;
        static interproc_namemutex* one_init_;
        static interproc_namemutex& one_init();


    public:

        tagsbase(const fspath& basepatht, appidtype app,
                eventtypeset evnts = sIMMINone/*,
                lock_nameexclusive ontimeinit = lock_nameexclusive(tagsbase::one_init())*/);

        virtual ~tagsbase();
        
        fspath  path() const {
            return fpath;};


        static void writezero(const fspath& basepatht, lcltype loc = NS_CODPAGE_UTF8);

        std::string conf_property(const confproptype& name) const;

        template<typename T>
        T conf_numproperty(const confproptype& name) const {
            return str_to<T > (conf_property(name), 0);}

        void conf_property(const confproptype& name, const std::string& val);

        template<typename T>
        void conf_property(const confproptype& name, const T& val) {
            switch (name) {
                case NS_CNFG_LOGLEVEL:{
                    prjcfg_debuglevel(static_cast<debuglvtype> (val));
                    return;}
                case NS_CNFG_DBMANAGER:{
                    prjcfg_dbprovider(static_cast<dbprovtype> (val));
                    return;}
                case NS_CNFG_ANALOGBUFF:{
                    prjcfg_analogbuf(static_cast<bool> (val));
                    return;}
                case NS_CNFG_HISTORYPERIOD:{
                    prjcfg_bddepth(static_cast<num32> (val));
                    return;};
                case NS_CNFG_ADMINPORT:{
                    prjcfg_adminport(to_str<int>(val));
                    return;}
                case NS_CNFG_REMOTEPORT:{
                    prjcfg_remoteport(to_str<int>(val));
                    return;}
                case NS_CNFG_OPCREMOTEPORT:{
                    prjcfg_opcport(to_str<int>(val));
                    return;}
                default:{}}}



        // value property       

        template<typename T>
        T value(size_type id) const {
            return itemex(id)->value<T > ();}
        

        short_value value_shv(size_type id) const {
            return (!IN_TEXTSET(type(id))) ? 
                short_value(itemex(id)->value64(), type(id), valid(id), error(id), time(id)) : 
                short_value(valstringvalue(operator[](id)->value<size_t > ()), valid(id), error(id), time(id));}
        
        short_value value_shv(const std::string& id) const {
            size_type ind = operator ()(id);
            return (ind!=npos) ? value_shv(ind) : short_value();}
        

        num64 value_n64(size_type id) const {
            return (!IN_TEXTSET(type(id))) ? 
                itemex(id)->value64() : 0 ;}
        
        short_value value_n64(const std::string& id) const {
            size_type ind = operator ()(id);
            return (ind!=npos) ? value_n64(ind) : 0;}
        

        std::string value_frmt(size_type id) const {
            return (!IN_TEXTSET(type(id))) ?
                    itemex(id)->value_frmt() : valstringvalue(operator[](id)->value<size_t > ());}

        void value(size_type id, const std::string& value) {
            if (exists(id))
                operator[](id)->value(value);}
        
        // value_expiered     
        bool value_expiered(size_type id, const short_value& rs, double db = 0.0, timeouttype tmo = RESET_LOG_TIME ) const;


        // value property         

        datetime time(size_type id) const {
            return itemex(id)->time();}
        
        datetime time(const std::string& id) const {
            size_type ind = operator ()(id);
            return (ind!=npos) ? time(ind) : nill_time;}

        std::string time_str(size_type id) const {
            return itemex(id)->time_str();}

        void time(size_type id, datetime value) {
            if (exists(id)) operator[](id)->time(value);}


        // value property         

        template<typename T>
        T value_log(size_type id) const {
            return operator[](id)->value_log<T > ();}

        short_value value_log_shv(size_type id) const {
            return short_value(itemex(id)->value_log64(), type(id), valid(id));}
        
        short_value value_log_shv(const std::string& id) const {
            size_type ind = operator ()(id);
            return (ind!=npos) ?  value_log_shv(ind) : short_value();}

        std::string value_log_frmt(size_type id) const {
            return itemex(id)->value_log_frmt();}


        // value property         

        datetime time_log(size_type id) const {
            return operator[](id)->time_log();}
        
        datetime time_log(const std::string& id) const {
            size_type ind = operator ()(id);
            return exists(ind) ? time_log(ind) : nill_time;}

        std::string time_log_str(size_type id) const {
            return operator[](id)->time_log_str();}

        void time_log(size_type id, datetime value) {
            if (exists(id)) operator[](id)->time_log(value);}


        // valid property 

        vlvtype valid(size_type id) const {
            return itemex(id)->valid();}
        
        vlvtype valid(const std::string& id) const {
            size_type ind = operator ()(id);
            return exists(ind) ? valid(ind) : 0;}

        vlvtype reportstate(size_type id);

        bool valid_as_reportsource(size_type id) const;

        bool reportbuffered(size_type id) const;

        void valid(size_type id, vlvtype valid);



        // error property 

        ns_error error(size_type id) const {
            return itemex(id)->error();}
        
        ns_error error(const std::string& id) const {
            return valid(operator ()(id));}

        void error(size_type id, ns_error value);


        // type property         

        tagtype type(size_type id) const {
            return itemex(id)->type();}

        tagtype superstype(size_type id) const {
            return  SUPER_TYPE(type(id));}

        void type(size_type id, tagtype value);


        // error property 

        size_type group(size_type id) const {
            return operator[](id)->group();}

        void group(size_type id, size_type value, bool message = true);


        // error property 

        size_type agroup(size_type id) const {
            return operator[](id)->agroup();}

        void agroup(size_type id, size_type value, bool message = true);


        // comment property         

        std::string comment(size_type id) const {
            return stringbase_src(operator[](id)->poscomment());}
        
        std::string comment(const std::string& id) const {        
            size_type ind = operator ()(id);
            return exists(ind) ? comment(ind) : "";} 

        void comment(size_type id, const std::string&  value);


        // binding property    

        std::string binding(size_type id) const {
            return stringbase_src(operator[](id)->posbinding());}

        void binding(size_type id, const std::string&  value, bool triggered = true);


        // binding property          

        std::string eu(size_type id) const {
            return stringbase_src(operator[](id)->poseu());}
        
        std::string eu(const std::string& id) const {        
            size_type ind = operator ()(id);
            return exists(ind) ? eu(ind) : "";} 

        void eu(size_type id, const std::string&  value);


        // onmsg property 

        std::string onmsg(size_type id) const {
            return stringbase_src(operator[](id)->posonmsg());}

        void onmsg(size_type id, const std::string&  value);

        // onmsged property 

        bool onmsged(size_type id) const {
            return operator[](id)->onmsged();}

        void onmsged(size_type id, bool value) {
            if (exists(id))
                operator[](id)->onmsged(value);}


        // offmsg property         

        std::string offmsg(size_type id) const {
            return stringbase_src(operator[](id)->posoffmsg());}

        void offmsg(size_type id, const std::string& value);

        // offmsged property 

        bool offmsged(size_type id) const {
            return operator[](id)->offmsged();}

        void offmsged(size_type id, bool value) {
            if (exists(id))
                operator[](id)->offmsged(value);}


        // msged property 

        bool msged(size_type id) const {
            return (onmsged(id) || offmsged(id));}


        // alarmmsg property   

        std::string alarmmsg(size_type id) const {
            return stringbase_src(operator[](id)->posalarmmsg());}

        void alarmmsg(size_type id, const std::string&  value);


        // alarmed property        

        bool alarmed(size_type id) const {
            return operator[](id)->alarmlevel();}

        // accesslevel  property

        altype alarmlevel(size_type id) const {
            return operator[](id)->alarmlevel();}

        void alarmlevel(size_type id, altype value) {
            if (exists(id))
                operator[](id)->alarmlevel(value);}

        // accesslevel  property        

        alcstype alarmcase(size_type id) const {
            return  operator[](id)->alarmcase();}

        void alarmcase(size_type id, alcstype value) {
            if (exists(id))
                operator[](id)->alarmcase(value);}

        // alarmon  property

        bool alarmon(size_type id) const {
            return operator[](id)->alarmon();}
        
        bool alarmon(const std::string& id ) const {
            size_type ind = operator ()(id);
            return exists(ind) ? alarmon(ind) : false;}

        // alarmon  property

        bool alarmkvit(size_type id) const {
            return operator[](id)->alarmkvit();}
        
        bool alarmkvit(const std::string& id ) const {
            size_type ind = operator ()(id);
            return exists(ind) ? alarmkvit(ind) : false;}        


        // accesslevel  property        

        acclevtype accesslevel(size_type id) const {
            return operator[](id)->accesslevel();}

        void accesslevel(size_type id, acclevtype value) {
            if (exists(id))
                operator[](id)->accesslevel(value);}

        // accesslevel  property        

        bool rangable(size_type id) const {
            return operator[](id)->rangable();}

        void rangable(size_type id, bool value);


        // alwactive  property           

        bool alwactive(size_type id) const {
            return IN_ALWACTSET(type(id)) ?
                    true : operator[](id)->alwactive();}

        void  alwactive(size_type id, bool value) {
            if (exists(id))
                operator[](id)->alwactive(value);}


        // rwtype  property

        acstgtype rwtype(size_type id) const {
            return operator[](id)->rwtype();}

        void rwtype(size_type id, acstgtype value) {
            if (exists(id))
                operator[](id)->rwtype(value);}


        // refcnt  property

        onum refcnt(size_type id) const {
            return operator[](id)->refcnt();}

        void incref(size_type id);
        
        void incref(const std::string& id);

        void decref(size_type id);
        
        void decref(const std::string& id);


        // logged  property        

        bool logged(size_type id) const {
            return operator[](id)->logged();}

        void logged(size_type id, bool value);


        // reporthistory  property        

        reporthisttype reporthistory(size_type id) const {
            return operator[](id)->reporthistory();}

        void reporthistory(size_type id, reporthisttype val) {
            if (exists(id))
                operator[](id)->reporthistory(val);}


        // reportsubdelt  property        

        reporthistdelt reportsubdelt(size_type id) const {
            return operator[](id)->reportsubdelt();}

        void reportsubdelt(size_type id, reporthistdelt val) {
            if (exists(id))
                operator[](id)->reportsubdelt(val);}


        // reportstatistic  property        

        repstattype reportstatistic(size_type id) const {
            return operator[](id)->reportstatistic();}

        void reportstatistic(size_type id, repstattype val) {
            if (exists(id))
                operator[](id)->reportstatistic(val);}



        // mineu  property   

        std::string mineu(size_type id) const {
            return ((exists(id))  && (IN_NUMBERSET(type(id)))) ?
                    operator[](id)->mineu_str() : "";}

        void mineu(size_type id, const std::string& value) {
            if (exists(id)) {
                operator[](id)->mineu(value);}}

        short_value mineu_shv(size_type id) const {
            return short_value(operator[](id)->mineu64(), type(id), FULL_VALID);}
        
        short_value mineu_shv(const std::string& id) const {
            size_type ind = operator ()(id);
            return exists(ind) ?  mineu_shv(ind) :  short_value();}



        // maxeu  property           


        std::string maxeu(size_type id) const {
            return ((exists(id))  && (IN_NUMBERSET(type(id)))) ?
                    operator[](id)->maxeu_str() : "";}

        void maxeu(size_type id, const std::string& value) {
            if (exists(id)) {
                operator[](id)->maxeu(value);}}
        
        short_value maxeu_shv(size_type id) const {
            return short_value(operator[](id)->maxeu64(), type(id) , FULL_VALID);}
        
        short_value maxeu_shv(const std::string& id) const {
            size_type ind = operator ()(id);
            return exists(ind) ?  maxeu_shv(ind) :  short_value();}



        // alarmconst  property

        std::string alarmconst(size_type id) const {
            return ((exists(id))  && (IN_NUMBERSET(type(id)))) ?
                    operator[](id)->alarmconst_str() : "";}

        void alarmconst(size_type id, const std::string& value) {
            if (exists(id)) operator[](id)->alarmconstr(value);}

        short_value alarmconst_shv(size_type id) const {
            return short_value(operator[](id)->alarmconst64(), type(id) , FULL_VALID);}




        // minraw  property               

        std::string minraw(size_type id) const {
            return ((exists(id))  && (IN_NUMBERSET(type(id)))) ?
                    operator[](id)->minraw_str() : "";}

        void minraw(size_type id, const std::string& value) {
            if (exists(id))
                operator[](id)->minraw(value);}


        // maxraw  property  

        std::string maxraw(size_type id) const {
            return ((exists(id))  && (IN_NUMBERSET(type(id)))) ?
                    operator[](id)->maxraw_str() : "";}

        void maxraw(size_type id, const std::string& value) {
            if (exists(id)) operator[](id)->maxraw(value);}




        // logdb  property           

        double logdb(size_type id) const {
            return operator[](id)->logdb();}

        void logdb(size_type id, double value) {
            if (exists(id))
                operator[](id)->logdb(value);}


        // devdb  property           

        double devdb(size_type id) const {
            return operator[](id)->devdb();}

        void devdb(size_type id, double value) {
            if (exists(id))
                operator[](id)->devdb(value);}


        // devdb  property      
        void group_appid(size_type id, appidtype val);
        



        template<typename T>
        void write_val(size_type id, T val, vlvtype validlvl = FULL_VALID, const datetime& time = nill_time, ns_error error = 0);

        void write_val(size_type id, const std::string& val, vlvtype validlvl = FULL_VALID, const datetime& time = nill_time, ns_error error = 0);

        void write_val(size_type id, const datetime& val, vlvtype validlvl = FULL_VALID, const datetime& tm = nill_time, ns_error err = 0);

        void write_val(size_type id, const short_value& val);





        void write_val_report(size_type id, datetime tm = nill_time, double val = NULL_DOUBLE, ns_error err = 0, bool onlybuffer = false);

        bool write_vals_report(size_type id, const dt_val_map& values, ns_error err = 0);




        void write_val_event(size_type id, datetime dt, double vl = NULL_DOUBLE);

        void write_val_event(size_type id, const dt_val_pair& val);




        template<typename T>
        void send_command(size_type id, T val, addcmdtype queue = acQueuedCommand,  bool setval = false , size_type clid = npos);

        void send_command(size_type id, const std::string& val, addcmdtype queue = acQueuedCommand,  bool setval = false, size_type clid = npos);

        void send_command(size_type id, const short_value& val, addcmdtype queue = acQueuedCommand,  bool setval = false, size_type clid = npos);
        
        void send_command(const std::string& id, const short_value& val, addcmdtype queue = acQueuedCommand,  bool setval = false, size_type clid = npos);



        void kvit(size_type id = npos);

        void kvit(const std::string& vl);



        void debug(const std::string& mess, debuglvtype lev = DEBUG_MESSAGE );

        void debugwarning(const std::string& mess) {
            debug(mess, DEBUG_WARNING);}

        void debugerror(const std::string& mess) {
            debug(mess, DEBUG_ERROR);}

        void debugfatalerror(const std::string& mess) {
            debug(mess, DEBUG_FATALERROR);}
        
        
        
        
        
        
        
        // insert operation
        
        size_type insert_entity(nodetype enttp , const std::string& newname, ns_error& rslt, size_type parentid = npos);   
        
        size_type insert_entity(nodetype enttp , const std::string& newname, ns_error& rslt, const std::string& parentid);
             

        size_type insert_tag(std::string newname, size_type groupid) {
            lower_and_trim(newname);
            if (!groups()->exists(groupid))
                throw dvncierror(NS_ERROR_NOPARENT, "");
            return add(newname, groupid);}

        size_type insert_tag(std::string newname, std::string groupnm="");

        void insert_tags(str_indx_map& newnames , size_type groupid) {
            return addtags(newnames, groupid);}

        void insert_tags(str_indx_map& newnames, const std::string& groupnm) {
            if (!groups()->exists(groupnm))
                throw dvncierror(NS_ERROR_NOPARENT, groupnm);
            insert_tags(newnames, groupnm);}
        
        
        

        size_type insert_group(std::string newname) {
            lower_and_trim(newname);
            checkname_ex(newname);
            size_type newind = groups()->add(newname);
            if (newind != npos) {
                addindex(newind | GROUPMASK);
                trigger_rename(newind | GROUPMASK);}
            return newind;}
        
        

        size_type insert_agroup(std::string newname) {
            lower_and_trim(newname);
            checkname_ex(newname);
            size_type newind = agroups()->add(newname);
            if (newind != npos) {
                addindex(newind | AGROUPMASK);
                trigger_rename(newind | AGROUPMASK);}
            return newind;}
        
        

        size_type insert_accessrule(std::string newname) {
            newname = trim_copy(newname);
            return accessrules()->add(newname);}
        
        

        size_type insert_user(std::string newname) {
            newname = trim_copy(newname);
            return users()->add(newname);}
        
        
        
        
        
        
        // rename operation        
        
        ns_error rename_entity(nodetype enttp , size_type id, const std::string& newname);   
        
        ns_error rename_entity(nodetype enttp , const std::string& id, const std::string& newname);         
        

        void rename_tag(size_type id, std::string newname) {
            if (!exists(id))
                throw dvncierror(ERROR_TAGNOEXIST);
            lower_and_trim(newname);
            name(id, newname);}

        void rename_tag(std::string oldname, std::string newname) {
            lower_and_trim(newname);
            lower_and_trim(oldname);
            if (!exists(oldname))
                throw dvncierror(ERROR_TAGNOEXIST, oldname);
            rename_tag( operator()(oldname), newname);}
        
        

        void rename_group(size_type id, std::string newname) {
            lower_and_trim(newname);
            checkname_ex(newname);
            if (!groups()->exists(id))
                throw dvncierror(ERROR_ENTNOEXIST);
            size_t oldpos = groups()->namepos(id);
            removeindex(id | GROUPMASK);
            groups()->name(id, newname);
            changepos1(oldpos, groups()->namepos(id));
            trigger_rename(id | GROUPMASK);
            trigger_group_rename(id);}

        void rename_group(std::string oldname, std::string newname) {
            lower_and_trim(newname);
            lower_and_trim(oldname);
            if (!groups()->exists(oldname))
                throw dvncierror(ERROR_ENTNOEXIST, oldname);
            rename_group( groups()->operator()(oldname), newname);}
        
        

        void rename_agroup(size_type id, std::string newname) {
            lower_and_trim(newname);
            checkname_ex(newname);
            if (!agroups()->exists(id))
                throw dvncierror(ERROR_ENTNOEXIST);
            removeindex(id | AGROUPMASK);
            agroups()->name(id, newname);
            addindex(id | AGROUPMASK);
            trigger_rename(id | AGROUPMASK);}

        void rename_agroup(std::string oldname, std::string newname) {
            lower_and_trim(newname);
            lower_and_trim(oldname);
            if (!agroups()->exists(oldname))
                throw dvncierror(ERROR_ENTNOEXIST, oldname);
            rename_agroup( agroups()->operator()(oldname), newname);}
        
        

        void rename_accessrule(size_type id, std::string newname) {
            newname = trim_copy(newname);
            if (!accessrules()->exists(id))
                throw dvncierror(ERROR_ENTNOEXIST);
            accessrules()->name(id, newname);}

        void rename_accessrule(std::string oldname, std::string newname) {
            newname = trim_copy(newname);
            oldname = trim_copy(oldname);
            if (!accessrules()->exists(oldname))
                throw dvncierror(ERROR_ENTNOEXIST, oldname);
            rename_agroup( accessrules()->operator()(oldname), newname);}
        
        

        void rename_user(size_type id, std::string newname) {
            newname = trim_copy(newname);
            if (!users()->exists(id))
                throw dvncierror(ERROR_ENTNOEXIST);
            users()->name(id, newname);}

        void rename_user(std::string oldname, std::string newname) {
            newname = trim_copy(newname);
            oldname = trim_copy(oldname);
            if (!users()->exists(oldname))
                throw dvncierror(ERROR_ENTNOEXIST, oldname);
            rename_user( users()->operator()(oldname), newname);}
        
        
        
        
        
        
        // delete operation        

        ns_error delete_entity(nodetype enttp , size_type id, const std::string& strcriteria = "");
        
        ns_error delete_entity(nodetype enttp , const std::string& id, const std::string& strcriteria = "");
        
        
        size_type delete_tag(size_type id) {
            if (exists(id)) {
                trigger_remove(id);
                return remove(id);}
            return npos;}

        size_type delete_tag(const std::string& delname) {
            if (exists(delname)) {
                return remove(operator()(delname));}
            return npos;}
        
        

        size_type delete_group(size_type id) {
            if (group_childcount(id))
                throw dvncierror(ERROR_ENTETYREMOVE_ISNOEMTY, groups()->name(id), id);
            indx rembaseid = operator ()(groups()->name(id));
            size_type remind = groups()->remove(id);
            if (remind != npos)
                removeindex(remind | GROUPMASK);
            if (rembaseid != npos)
                trigger_rename(rembaseid);
            return remind;}
        
 
        size_type delete_group(const std::string& delname) {
            size_type remind = groups()->operator ()(delname);
            return remind != npos ? delete_group(remind) : npos;}
        
        

        size_type delete_agroup(size_type id) {
            indx rembaseid = operator ()(agroups()->name(id));
            size_type remind = agroups()->remove(id);
            if (remind != npos)
                removeindex(remind | AGROUPMASK);
            if (rembaseid != npos)
                trigger_rename(rembaseid);
            return remind;}

        size_type delete_agroup(const std::string& delname) {
            size_type remind = agroups()->operator ()(delname);
            return remind != npos ? delete_agroup(remind) : npos;}
        
        

        size_type delete_accessrule(size_type id) {
            return accessrules()->remove(id);}

        size_type delete_accessrule(const std::string& delname) {
            return accessrules()->remove(delname);}
        
        

        size_type delete_user(size_type id) {
            return users()->remove(id);}

        size_type delete_user(const std::string& delname) {
            return users()->remove(delname);}
        


        
        // duplicate operation        
        

        size_type duplicate_group(size_type id, std::string newname);
        
        size_type duplicate_group(std::string grp, std::string newname);
        
        
        

        
        // merge operation  
        
        
        ns_error merge_entity(nodetype enttp , size_type id);        
        
        void merge_tag(size_type id) {
            writetofile(id);}

        void merge_group(size_type id) {
            groups()->writetofile(id);}

        void merge_agroup(size_type id) {
            agroups()->writetofile(id);}

        void merge_accessrule(size_type id) {
            accessrules()->writetofile(id);}

        void merge_user(size_type id) {
            users()->writetofile(id);}



        

        
        // select operation        

        
        ns_error select_entities(nodetype enttp, iteminfo_map& val, size_type parentid, const std::string& strcriteria = "");
        
        ns_error select_entities(nodetype enttp, iteminfo_map& val, const std::string& parentid, const std::string& strcriteria = "");
        
        ns_error select_entities(nodetype enttp, iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");        
        
        
        void select_tags(iteminfo_map& val, size_type group, const std::string& strcriteria = "");

        void select_tags(iteminfo_map& val, std::string group, const std::string& strcriteria = "");

        void select_tags(iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");
        
         
        void select_tags_report(indx_set& val);       
        
        void select_tags_by_appid(indx_set& val, appidtype appid, bool onlyactive = true);

        void select_tags_by_groupid(indx_set& val, size_type group, bool onlyactive = true);

        void select_tags_by_link(indx_set& val, appidtype app, const metalink& lnk, bool onlyactive = true);
        
        
        

        void select_atags(iteminfo_map& val, size_type agroup, const std::string& strcriteria = "");

        void select_atags(iteminfo_map& val, std::string agroup, const std::string& strcriteria = "");
        
        
        
        
        void select_groups(iteminfo_map& val, const std::string& strcriteria = "");

        void select_groups(iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");
        

        
        void select_groups_by_appid(appidtype appid, indx_set& val);
               
        void select_groups_by_metalink(const metalink& lnk, appidtype app, indx_set& val);

        void select_metalinks_set_by_appid(appidtype appid, metalink_set& val);

        void select_metalinks_vect_by_metalink(const metalink& lnk, metalink_vect& val, devnum_set& utilset);

        
        
        
        void select_agroups(iteminfo_map& val, const std::string& strcriteria = "");

        void select_agroups(iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");
        
        
        

        void select_users(iteminfo_map& val, const std::string& strcriteria = "");

        void select_users(iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");
        

        
        
        void select_accessrules(iteminfo_map& val, const std::string& strcriteria = "");

        void select_accessrules(iteminfo_map& val, const indx_set& idset, const std::string& strcriteria = "");
        

  

        bool select_trendbuff(size_type id, dt_val_map& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time, const double& lgdb = NULL_DOUBLE) const  {
            return valbuffers()->select(logkey(id), vl, from_, to_, lgdb);}

        bool select_trendbuff(const std::string& nm, dt_val_map& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time, const double& lgdb = NULL_DOUBLE) const {
            return select_trendbuff(operator ()(nm), vl, from_, to_, lgdb);}
        
        bool select_trendbuff(size_type id, short_value_vect& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time, const double& lgdb = NULL_DOUBLE) const  {
            dt_val_map tmpvl;
            vl.clear();
            bool rslt=valbuffers()->select(logkey(id), tmpvl, from_, to_, lgdb);
            for (dt_val_map::const_iterator it=tmpvl.begin(); it!=tmpvl.end();++it){
              vl.push_back(short_value(it->second, it->first));}
            return rslt;}

        bool select_trendbuff(const std::string& nm, short_value_vect& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time, const double& lgdb = NULL_DOUBLE) const  {
            return select_trendbuff(operator ()(nm), vl, from_, to_, lgdb);}
                
        bool select_trendsbuff(const str_vect& names, short_values_table& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time, const double& lgdb = NULL_DOUBLE) const;
        

        
        bool select_reportbuff(size_type id, dt_val_map& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time) const {
            return reportbuffers()->select(reportkey(id), vl, from_, to_);}

        bool select_reportbuff(const std::string& nm, dt_val_map& vl, const datetime& from_ = nill_time, const datetime& to_ = nill_time) const {
            return select_reportbuff(operator ()(nm), vl, from_, to_);}

        bool select_reportval_top(size_type id, dt_val_pair& vl) const {
            return reportbuffers()->topvalue(reportkey(id), vl);}

        bool select_reportval_by_time(size_type id, const datetime& tm, dt_val_pair& vl) const {
            return reportbuffers()->value_by_time(reportkey(id), tm , vl);}

        bool select_reportvals_by_time(const datetime& tm, indx_double_map& vlmap) const;

        bool report_history_empty(size_type id) const {
            datetime tmpdt = reportbuffers()->toptime(reportkey(id));
            return ((tmpdt == nill_time) || (tmpdt < time_log(id)));}

        size_t report_history_count(size_type id) const {
            return reportbuffers() ? reportbuffers()->count(reportkey(id)) : 0;}

    
        
        
        template<typename T, typename B>
        size_t select_journal(std::vector<T>& vect, guidtype& gid, size_t& curs, size_t& cnt) const {
            return journal()->get<T, B > (vect, gid, curs, cnt);}
        
        size_t select_journal(vect_journal_row& vect, guidtype& gid, size_t& curs, size_t& cnt) const {
            return journal()->get<journal_row, num64 > (vect, gid, curs, cnt);}

        guidtype guid_journal() {
            return journal()->gloubnum();}
 
        
        

        template<typename T, typename B>
        size_t select_debug(std::vector<T>& vect, guidtype& gid, size_t& curs, size_t& cnt) const {
            return debug()->get<T, B > (vect, gid, curs, cnt);}
        
        size_t select_debug(vect_debug_row& vect, guidtype& gid, size_t& curs, size_t& cnt) const {
            return debug()->get<debug_row, num64 > (vect, gid, curs, cnt);}        

        guidtype guid_debug() {
            return debug()->gloubnum();}
        

        
        
        template<typename T, typename B>
        size_t select_alarms(std::vector<T>& vect, guidtype& vers, std::string agrp , const std::string grp ) const {
            return alarms()->get<T, B > (vect, vers, (*agroups())(agrp), (*groups())(grp));}

        template<typename T, typename B>
        size_t select_alarms(std::vector<T>& vect, guidtype& vers, size_type agrp = npos, size_type grp = npos ) const {
            return alarms()->get<T, B > (vect, vers, agrp, grp);}

        template<typename T, typename B>
        size_t select_alarms(std::vector<T>& vect, size_type agrp = npos, size_type grp = npos ) const {
            guidtype vers = 0;
            return alarms()->get<T, B > (vect, vers, agrp, grp);}
        
        size_t select_alarms(vect_alarms_row& vect, guidtype& vers, size_type agrp = npos, size_type grp = npos ) const {
            return alarms()->get<alarms_row, num64 > (vect, vers, agrp, grp);}
        
        size_t select_alarms(vect_alarms_row& vect, guidtype& vers, std::string agrp , const std::string grp ) const {
            return alarms()->get<alarms_row, num64 > (vect, vers, (*agroups())(agrp), (*groups())(grp));}        
       
        
        
        template<typename T, typename B>
        size_t select_commands(std::vector<T>& vect, guidtype& vers, const std::string grp) const {
            return commands()->get<T, B > (vect, vers, (*groups())(grp));}

        template<typename T, typename B>
        size_t select_commands(std::vector<T>& vect, guidtype& vers, size_type grp = npos) const {
            return commands()->get<T, B > (vect, vers, grp);}

        template<typename T, typename B>
        size_t select_commands(std::vector<T>& vect, size_type grp = npos) const {
            guidtype vers = 0;
            return commands()->get<T, B > (vect, vers, grp);}
      
        
        bool select_commands(command_vector& vect_, size_type group = npos) {
            return commands()->select_commands(vect_, group);}

        bool select_commands(command_vector& vect_, indx_set groups) {
            return commands()->select_commands(vect_, groups);}

        bool clear_commands(size_type group = npos) {
            return commands()->clear_commands(group);}    
        
        
        
        

        template<typename T, typename B>
        size_t select_registry(std::vector<T>& vect, guidtype& vers) const {
            return registry()->get<T, B > (vect, vers);}

        template<typename T, typename B>
        size_t select_registry(std::vector<T>& vect) const {
            guidtype vers = 0;
            return registry()->get<T, B > (vect, vers);}
        
        

        template<typename T, typename B>
        size_t select_clients(std::vector<T>& vect, guidtype& vers) const {
            return clients()->get<T, B > (vect, vers);}

        template<typename T, typename B>
        size_t select_clients(std::vector<T>& vect) const {
            guidtype vers = 0;
            return clients()->get<T, B > (vect, vers);}
        
        


        groupsbase * const groups() const {
            return groups_.get();};

        agroupsbase * const agroups() const {
            return agroups_.get();};

        accessrulesbase * const accessrules() const {
            return accessrules_.get();};

        usersbase * const users() const {
            return users_.get();};
            
            

        mq_class_ptr getqueue() {
            return mq_class_ptr(proccess_queues::getqueue(registry()->selfhadle(), false));}

        void allvalid(vlvtype vld) {
            for (size_type i = 0; i < count(); ++i)
                if (exists(i)) valid(i, vld);}

        void incallcounter(bool inc = true) {
            for (size_type i = 0; i < count(); ++i) {
                inc ? incref(i) : decref(i);}}

        guidtype regclient(const std::string& hst = "", const std::string& ipp = "", const std::string& usr = "",  const std::string& password = "") {
            return clients()->regclient(appid_, hst , ipp , usr , password);}
        
        void unregclient(guidtype clid) {
            clients()->unregclient(clid);}

        void notify_dbmanage(bool connectstate) {
            registry()->notify_dbmanage(connectstate ? MSG_DVNCDBCONNECT : MSG_DVNCDBDISCONNECT);}

    protected:


        size_t globalmemsize() const;

        // mineu  property         

        template<typename T>
        T mineu_prtd(size_type id) const {
            return exists(id) ? operator[](id)->mineu<T > () : 0;}

        template<typename T>
        void mineu_prtd(size_type id, T value) {
            if (exists(id)) {
                operator[](id)->mineu<T > (value);
                if (logkey(id) != npos) {
                    valbuffers()->range( logkey(id), mineu_prtd<double>(id), maxeu_prtd<double>(id));}}}



        // maxeu  property         

        template<typename T>
        T maxeu_prtd(size_type id) const {
            return exists(id) ?
                    operator[](id)->maxeu<T > () : 1;};

        template<typename T>
        void maxeu_prtd(size_type id, T value) {
            if (exists(id)) {
                operator[](id)->maxeu<T > (value);
                if (logkey(id) != npos) {
                    valbuffers()->range( logkey(id), mineu_prtd<double>(id), maxeu_prtd<double>(id));}}}

        template<typename T>
        void restore_raw_range(size_type id, T& val);


        template<typename T>
        bool logdb_expired(size_type id, const T& val);


        bool restore_command_raw_range(commandstruct& cmd);



        // alarmconst  property        

        template<typename T>
        T alarmconst_prtd(size_type id) const {
            return (IN_NUMBERSET(operator[](id)->type())) ?
                    operator[](id)->alarmconst<T > () : 0;}

        template<typename T>
        void alarmconst_prtd(size_type id, T value) {
            if (exists(id)) operator[](id)->alarmconst<T > (value);}



        // minraw  property          

        template<typename T>
        T minraw_prtd(size_type id) const {
            return operator[](id)->minraw<T > ();}

        template<typename T>
        void minraw_prtd(size_type id, T value) {
            if (exists(id))
                operator[](id)->minraw<T > (value);}



        // maxraw  property  

        template<typename T>
        T maxraw_prtd(size_type id) const {
            return operator[](id)->maxraw<T > ();}

        template<typename T>
        void maxraw_prtd(size_type id, T value) {
            if (exists(id)) operator[](id)->maxraw<T > (value);}


        // is rangeed

        template<typename T>
        void restore_eu_range(size_type id, T& val);


        void to_standart_range(size_type id);

        template<typename T>
        bool in_alarm(size_type id) const {
            if (!valid(id)) return false;
            if (!alarmed(id)) return false;
            if (type(id) == TYPE_DISCRET) {
                return value<bool> (id) == alarmconst_prtd<bool> (id);}
            switch (alarmcase(id)) {
                case alarmMore: return (value<T > (id) > alarmconst_prtd<T > (id));
                case alarmLess: return (value<T > (id) < alarmconst_prtd<T > (id));
                default: return (value<T > (id) == alarmconst_prtd<T > (id));}}

        template<typename T>
        bool in_event(size_type id) const {
            if (!valid(id)) return false;
            if (!msged(id)) return false;
            return (value<T > (id) != 0);}

        bool in_sysvar(size_type id) const {
            return ((groups()->appid(group(id)) == NS_GROUP_SYSTEMVAR));}


        //overloaded       


        virtual bool checkname(const std::string& val, size_type parnt = npos);

        bool checkname_ex(const std::string& val);

        virtual bool trigger_write_criteria(size_type id) const {
            return ((exists(id)) && ((groups()->appid(group(id))) == NS_GROUP_SYSTEMVAR));}

        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos);

        virtual void uninitstruct(size_type id);



        // triggers

        virtual void trigger_add(size_type id, size_type opt = npos);

        virtual void trigger_remove(size_type id, size_type opt = npos);

        virtual void trigger_rename(size_type id);

        void trigger_bind(size_type id);

        void trigger_group_rename(size_type id);



        virtual void trigger_util(size_type id, const tagstruct& oldst, const tagstruct& newst);

        void trigger_trendlog(size_type id, bool state);

        void trigger_report(size_type id, tagtype oldtype, tagtype newtype);

        void trigger_texttype(size_type id, bool state);

        void trigger_range(size_type id, bool state);
        
        void trigger_ref(size_type id, bool state); 

        void trigger_systemtype(size_type id, bool state);
        
        
        
        
        

        void notify_tagmanage(qumsgtype mess, size_type id, size_type group) {
            registry()->notify_tagmanage(mess, id, group);}

        void notify_groupmanage(qumsgtype mess, size_type id, num32 some) {
            registry()->notify_groupmanage(mess, id, some);}

        virtual size_t namepos(size_type id) const {
            return itemex(id)->namepos();};

        virtual std::string parentname(size_type id) const {
            return exists(id) ? (groups()->name(group(id)) + NEMESPACEDELIMIT) : "";}

        virtual size_type parentid(size_type id) {
            return  group(id);}

        void changepos1(size_t oldpos1, size_t newpos1);




        //////////////////////



        virtual void buildindex();

        virtual void addindex(size_type id);

        virtual void removeindex(size_type id);

        virtual size_t optinal_pos(size_type id);



        void texttagcnt(size_t val);

        void archtagcnt(size_t val);

        void reporttagcnt(size_t val);

        size_t texttagcnt() const {
            return (*(ptagsstruct_hdr) data()).texttagcnt();}

        size_t archtagcnt() const {
            return (*(ptagsstruct_hdr) data()).archtagcnt();}

        size_t reporttagcnt() const {
            return (*(ptagsstruct_hdr) data()).reporttagcnt();}

        lcltype prjcfg_local() const {
            return (*(ptagsstruct_hdr) data()).local();}

        debuglvtype prjcfg_debuglevel() const {
            return (*(ptagsstruct_hdr) data()).debuglevel();}

        void prjcfg_debuglevel(debuglvtype val);

        dbprovtype prjcfg_dbprovider() const {
            return (*(ptagsstruct_hdr) data()).dbprovider();}

        void prjcfg_dbprovider(dbprovtype val) ;

        bool prjcfg_analogbuf() const {
            return (*(ptagsstruct_hdr) data()).analogbuf();}

        void prjcfg_analogbuf(bool val);

        num32 prjcfg_bddepth() const {
            return (*(ptagsstruct_hdr) data()).bddepth();}

        void prjcfg_bddepth(num32 val);

        std::string prjcfg_name() const {
            return stringbase_src((*(ptagsstruct_hdr) data()).posname());}

        void prjcfg_name(const std::string& value) ;

        std::string prjcfg_comment() const {
            return stringbase_src((*(ptagsstruct_hdr) data()).poscomment());}

        void prjcfg_comment(const std::string& value) ;

        std::string prjcfg_dbstring() const {
            return stringbase_src((*(ptagsstruct_hdr) data()).posdbstring());}

        void prjcfg_dbstring(const std::string& value) ;

        std::string prjcfg_admin() const {
            return stringbase_src((*(ptagsstruct_hdr) data()).posadmin());}

        void prjcfg_admin(const std::string& value);

        std::string prjcfg_password() const {
            return stringbase_src((*(ptagsstruct_hdr) data()).pospass());}

        void prjcfg_password(const std::string& value);

        std::string prjcfg_adminport() const {
            std::string tmp = stringbase_src((*(ptagsstruct_hdr) data()).posadminport());
            return (dvnci::str_to<unum32 > (tmp, 0) < 80) ? DEFAULT_ADMIN_PORT : tmp;}

        void prjcfg_adminport(const std::string& value);

        std::string prjcfg_remoteport() const {
            std::string tmp = stringbase_src((*(ptagsstruct_hdr) data()).posremoteport());
            return (dvnci::str_to<unum32 > (tmp, 0) < 80) ? DEFAULT_REMOTE_PORT : tmp;}

        void prjcfg_remoteport(const std::string& value);

        std::string prjcfg_opcport() const {
            std::string tmp = stringbase_src((*(ptagsstruct_hdr) data()).posopcport());
            return (dvnci::str_to<unum32 > (tmp, 0) < 80) ? DEFAULT_OPC_PORT : tmp;}

        opsystemtype prjcfg_ostype() const {
            return (*(ptagsstruct_hdr) data()).os_type();}

        void prjcfg_opcport(const std::string& value);


        //////////////////////////////////////////////////////////////////////////////////////////

        tagstruct const * const itemex(size_type id) const {
            if (id < count() && (id != npos)) return operator[](id);
            if (id & GROUPMASK) return reinterpret_cast<tagstruct const * const> (groups()->itemconst(id & RESETMASK ));
            if (id & AGROUPMASK) return reinterpret_cast<tagstruct const * const> (agroups()->itemconst(id & RESETMASK ));
            return operator[](id);}

        bool extendexists(size_type id) const;

        journalbase * const journal() const {
            return journal_.get();};

        debugbase * const debug() const {
            return debug_.get();};

        alarmsbase * const alarms() const {
            return alarms_.get();};

        commandsbase * const commands() const {
            return commands_.get();};

        registrybase * const registry() const {
            return registry_.get();};

        clientbase * const clients() const {
            return clients_.get();};

        size_t group_childcount( size_type id);



        void duplicate_tags(const iteminfo_map& maptmpl, const std::string& grpnm);

        bool grant_access(appidtype app, const std::string& hst = "", const std::string& ipp = "", const std::string& usr = "",  const std::string& password = "") {
            return accessrules()->grant_access(app, hst , ipp , usr , password);}



        void checkreporttime(size_type id);

        void increpttime(size_type id);

        datetime trend_history_toptime(size_type id) const {
            return valbuffers()->toptime(logkey(id));}


        bool insert_to_reportbuff_init(size_type id, const dt_val_map& values);

        bool insert_to_reportbuff_init(size_type id);

        bool insert_to_reportbuff_init(size_type id, const datetime& lst);

        bool trendbuff_need_write(size_type id) const {
            return valbuffers()->needwrite(logkey(id));}

        void trendbuff_need_write(size_type id, bool val) {
            valbuffers()->needwrite(logkey(id), val);}

        template <typename T>
        void insert_to_trendbuff(size_type id, T val, const datetime& tm = nill_time) {
            size_type lk = logkey(id);
            if (lk != npos) {
                valbuffers()->insert<T > (lk, tm != nill_time ? tm : now(), val);}}

        void insert_to_trendbuff(size_type id, datetime tm) {
            size_type lk = logkey(id);
            if (lk != npos) {
                valbuffers()->insert(lk, tm);}}

        void insert_to_reportbuff(size_type id, const datetime&  tm, double val =  NULL_DOUBLE) {
            size_type lk = reportkey(id);
            if (lk != npos) {
                reportbuffers()->insert<double>(lk, tm, val);}}




        void send_command_str(size_type id, const std::string& val, addcmdtype queue = acQueuedCommand, bool setval = false, size_type clid = npos) ;

        void addtags(str_indx_map& newnames, size_type groupid);

        void addindexmap(str_indx_map& mp);
        
        
        
        

        bool logbuffered(size_type id) const {
            return ((logged(id)) && (logkey(id) != npos)) ?
                    operator[](id)->logged() : false;}

        valuebufferbase_ptr   valbuffers() const {
            return valbuffers_;}

        size_type logkey(size_type id) const {
            return (IN_NUMBERSET(operator[](id)->type())) ?
                    operator[](id)->logkey() : npos;}

        void logkey(size_type id, size_type value) {
            if (exists(id)) operator[](id)->logkey(value);}


        void fill_logkeys();

        size_type add_logkey(size_type id);

        size_type remove_logkey(size_type id);

        size_type reset_logkey(size_type id) {
            remove_logkey(id);
            return add_logkey(id);}
        
        

        reportbufferbase_ptr   reportbuffers() const {
            return reportbuffers_;}

        size_type reportkey(size_type id) const {
            return (IN_REPORTSET(operator[](id)->type())) ?
                    operator[](id)->logkey() : npos;}

        void reportkey(size_type id, size_type value) {
            if (exists(id)) operator[](id)->logkey(value);}

        void fill_reportkeys();

        size_type add_reportkey(size_type id);

        size_type remove_reportkey(size_type id);

        size_type reset_reportkey(size_type id) {
            remove_reportkey(id);
            return add_reportkey(id);}
        
        

        std::string valstringvalue(size_t pos) const {
            return valstrb_->getstring(pos);}

        void  valstringvalue(size_t& pos, const std::string& value, bool persist) {
            valstrb_->setstring(pos, value, persist);}

        void valuestringremove(size_type id) {
            valstrb_->remove(operator[](id)->value<size_t > ());}

        void valuestringreplace(size_type id, bool to_sys);
        
        

        void kvitall() {
            alarms()->kvitall();}

        void kvit_tag(size_type id) {
            if (exists(id))
                alarms()->kvit_tag(id);}

        void kvit_agroup(size_type id) {
            if (agroups()->exists(id))
                alarms()->kvit_agroup(id);}

        void kvit_group(size_type id) {
            if (groups()->exists(id))
                alarms()->kvit_group(id);}



        void offgroup(size_type group, ns_error error = 0);
        
        void offtag(size_type id, ns_error error = 0);


        virtual void inputsysvargroups(size_type group, bool include);

        void inputsysvartag(size_type id, bool include);



        void reghandle(appidtype app, eventtypeset evts);

        void unreghandle();

        template<typename T>
        void value_internal(size_type id, T value) {
            if (exists(id)) {
                operator[](id)->value<T > (value);}}

        void value_internal(size_type id, const std::string& value);

        template<typename T>
        void value_log(size_type id, T value) {
            if (exists(id)) {
                operator[](id)->value_log<T > (value);}}

        void value_log(size_type id, std::string value) {
            if (exists(id)) {
                operator[](id)->value_log(value);}}

        void notify_journal(size_type line) {
            registry()->notify_journal(line);}

        void insert_to_alarms(size_type id, bool on) {
            if (exists(id)) {
                if (on) alarms()->add(time(id), id);
                else alarms()->remove(id);}}

        void insert_to_journal(const datetime& tm, size_type id, msgtype tp, altype lev = altNone, const double& val = NULL_DOUBLE, size_type userid = npos) {
            if (exists(id))
                journal()->add( tm , id , tp, lev, val, userid);}

        void insert_to_journal(size_type id) {
            if (exists(id))
                insert_to_journal(time(id), id, value<bool>(id) ? msOn : msOff);}

        void insert_evnt_to_journal(size_type id, double val = NULL_DOUBLE) {
            if (exists(id)) {
                if (alarmed(id))
                    alarms()->add(time(id), id, msTimeEvent, val);
                else
                    insert_to_journal(time(id), id, msTimeEvent, altNone , val );}}

        template<typename T>
        void insert_cmd_to_alarms(size_type id, const T& preval, const T& val) {
            if (exists(id))
                insert_to_journal(now(), id, msCmd);}

        void clone(size_type idsrc, size_type iddst);} ;







    template<>
    std::string tagsbase::value<std::string>(size_type id) const;

    template<>
    std::string tagsbase::value_log<std::string>(size_type id) const;

    template<>
    datetime tagsbase::value<datetime>(size_type id) const;

    template<>
    datetime tagsbase::value_log<datetime>(size_type id) const;

    template<>
    std::string tagsbase::minraw_prtd<std::string>(size_type id) const;

    template<>
    std::string tagsbase::maxraw_prtd<std::string>(size_type id) const ;

    template<>
    void tagsbase::restore_raw_range<bool>(size_type id, bool& val);

    template<>
    std::string tagsbase::mineu_prtd<std::string>(size_type id) const;

    template<>
    std::string tagsbase::maxeu_prtd<std::string>(size_type id) const;

    template<>
    void tagsbase::restore_eu_range<bool>(size_type id, bool& val);


    template<>
    bool tagsbase::logdb_expired<bool>(size_type id, const bool& val);

    template<>
    std::string tagsbase::alarmconst_prtd<std::string>(size_type id) const;

    template<typename T>
    void tagsbase::restore_eu_range(size_type id, T& val) {
        if (IN_RANGESET(type(id))) {
            T max_eu = maxeu_prtd<T > (id);
            T min_eu = mineu_prtd<T > (id);
            if (max_eu < min_eu)
                std::swap(min_eu, max_eu);
            T length_eu = max_eu - min_eu;
            if (rangable(id) && (length_eu)) {
                T max_raw = maxraw_prtd<T > (id);
                T min_raw = minraw_prtd<T > (id);
                if (max_raw < min_raw)
                    std::swap(min_raw, max_raw);
                T length_raw = max_raw - min_raw;
                if ((length_raw) && (length_eu)) {
                    if (val < min_raw)
                        val = min_raw;
                    if (val > max_raw)
                        val = max_raw;
                    val = (min_eu + ((1.0 * length_eu)
                                     / (1.0 * length_raw))* (val - min_raw));}}
            else {
                if (length_eu) {
                    if (val < min_eu) {
                        val = min_eu;}
                    else {
                        if (val > max_eu)
                            val = max_eu;}}}}}

    template<typename T>
    void tagsbase::restore_raw_range(size_type id, T& val) {
        if (IN_RANGESET(type(id))) {
            T max_eu = maxeu_prtd<T > (id);
            T min_eu = mineu_prtd<T > (id);
            if (max_eu < min_eu)
                std::swap(min_eu, max_eu);
            T length_eu = max_eu - min_eu;
            if ((rangable(id)) && (length_eu)) {
                T max_raw = maxraw_prtd<T > (id);
                T min_raw = minraw_prtd<T > (id);
                T length_raw = max_raw > min_raw ? max_raw - min_raw : min_raw - max_raw;
                if (length_raw) {
                    if (max_raw < min_raw)
                        std::swap(min_raw, max_raw);
                    if (val < min_eu)
                        val = min_eu;
                    if (val > max_eu)
                        val = max_eu;
                    val = (min_raw + ((1.0 * length_raw)
                                      / (1.0 * length_eu))* (val - min_eu));}}
            else {
                if (length_eu) {
                    if (val < min_eu) {
                        val = min_eu;}
                    else {
                        if (val > max_eu)
                            val = max_eu;}}}}}

    template<typename T>
    bool tagsbase::logdb_expired(size_type id, const T& val) {

        T max_raw = maxraw_prtd<T > (id);
        T min_raw = minraw_prtd<T > (id);
        T logdbtmp = (max_raw > min_raw ? max_raw - min_raw : min_raw - max_raw) * logdb(id);
        return (value_log<T > (id) > val) ?
                ((value_log<T > (id) - val) >= logdbtmp) :  ( val - (value_log<T > (id) ) >= logdbtmp);}

    template<typename T>
    void tagsbase::write_val(size_type id, T val, vlvtype validlvl, const datetime& tm, ns_error err) {
        if (exists(id) && (IN_NUMBERSET(type(id)))) {
            restore_eu_range(id, val);
            bool rstvalid = (valid(id) != (validlvl));
            bool rstvalue = (value<T > (id) != val);
            bool rstlogval = logdb_expired<T > (id, val);
            bool rsttimelog = seconds_between_more_then(tm, time_log(id), 55);
            bool old_in_alarm = in_alarm<T > (id);
            bool old_in_msded = in_event<T > (id);
            value_internal<T > (id, val);
            time(id, tm.is_special() ?  now() : tm);
            valid(id, validlvl);
            error(id, err);
            if ( (rstvalue) || (rstvalid) || (rsttimelog) || (rstlogval)) {

                if ((logged(id)) && (valbuffers())) {
                    if ((rstvalid) || (rstvalue)) {
                        if (validlvl == FULL_VALID)
                            insert_to_trendbuff<T > (id,  val ,  tm.is_special() ?  now() : tm);
                        else
                            insert_to_trendbuff(id,   tm.is_special() ?  now() : tm);
                        if (rstlogval || rsttimelog || rstvalid) {

                            trendbuff_need_write(id, true);
                            time_log(id, tm);
                            value_log<T > (id, val);}}}

                if (msged(id)) {
                    if (valid(id) && (old_in_msded != in_event<T > (id))) {
                        if (((onmsged(id)) && (in_event<T > (id))) ||
                                ((offmsged(id)) && (!in_event<T > (id)))) {
                            insert_to_journal(id);}}}


                if (alarmed(id)) {
                    if ((in_alarm<T > (id) != old_in_alarm) && (valid(id))) {

                        insert_to_alarms(id, in_alarm<T > (id));}}}}}

    template<typename T>
    void tagsbase::send_command(size_type id, T val, addcmdtype queue , bool setval ,size_type clid) {
        if (IN_TEXTSET(type(id))) return;
        if (exists(id)) {
            if ((groups()->exists(group(id)))) {
                switch (groups()->appid(group(id))) {
                    case NS_GROUP_SYSTEM:
                    case NS_GROUP_SYSTEMVAR:{
                        //valid(id, FULL_VALID);
                        write_val<T > (id, val);
                        writetofile(id);
                        break;}
                    case NS_GROUP_SYSTEMREPORT:
                    case NS_GROUP_SYSTEMREPORTCOUNT:
                    case NS_GROUP_SYSTEMCOUNT:{
                        break;}
                    default:{
                        if ((setval) || (queue==acNullCommand)){
                            if (logged(id) || alarmed(id) || msged(id))
                                operator[](id)->valid(0);
                            value_internal<T >(id, val);}
                        if (queue==acNullCommand)
                            return;
                        commands()->add(id, operator[](id)->value<num64 > (), num64_cast<T > (val), operator[](id)->type(), queue, clid);}}
                insert_cmd_to_alarms<T > (id, val, val);}}}}

#endif	/* _MEMFILE_H */


