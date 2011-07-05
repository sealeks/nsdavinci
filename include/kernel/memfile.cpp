/* 
 * File:   memfile.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 29 ??????? 2009 ?., 15:25
 */

#include <kernel/memfile.h>

namespace dvnci {


    using namespace std;

    void test_immi_struct() {
        cout << "num64: " << sizeof (num64) << endl;
        cout << "num32: " << sizeof (num32) << endl;
        cout << "bool: " << sizeof (bool) << endl;
        cout << "tagsstruct_hdr: " << sizeof (tagsstruct_hdr) << endl;
        cout << "tagstruct " << sizeof (tagstruct) << endl;
        cout << "groupstruct: " << sizeof (groupstruct) << endl;
        cout << "agroupstruct: " << sizeof (agroupstruct) << endl;
        cout << "userstruct: " << sizeof (userstruct) << endl;
        cout << "accessrulestruct: " << sizeof (accessrulestruct) << endl;
        cout << "smplheader: " << sizeof (smplheader) << endl;
        cout << "datetime " << sizeof (datetime) << endl;
        DEBUG_VAL_DVNCI(EXTEND_MEMSHARE_TAG_SIZE);
        DEBUG_VAL_DVNCI(EXTEND_MEMSHARE_GRP_SIZE);
        DEBUG_VAL_DVNCI(EXTEND_MEMSHARE_AGRP_SIZE);
        DEBUG_VAL_DVNCI(EXTEND_MEMSHARE_USER_SIZE);
        DEBUG_VAL_DVNCI(EXTEND_MEMSHARE_STR_SIZE);}



    // journalbase

    std::string  journalbase::text(size_type id) const {
        if (exists(id)) {
            switch (type(id)) {
                case  msNew:
                case  msKvit:
                case  msOut:{
                    return tgbs_ptr->alarmmsg(tagid(id));}
                case  msOn:{
                    return tgbs_ptr->onmsg(tagid(id));}
                case  msOff:{
                    return tgbs_ptr->offmsg(tagid(id));}
                default:{
                    return tgbs_ptr->comment(tagid(id));}}};
        return "";}

    std::string   journalbase::tag(size_type id) const {
        return exists(id) ? tgbs_ptr->name(tagid(id)) : "";};

    std::string  journalbase::text_retrosp(size_type id) const {
        if (exists(id)) {
            switch (type_retrosp(id)) {
                case msNew:
                case  msKvit:
                case  msOut:{
                    return tgbs_ptr->alarmmsg(tagid_retrosp(id));}
                case  msOn:{
                    return tgbs_ptr->onmsg(tagid_retrosp(id));}
                case  msOff:{
                    return tgbs_ptr->offmsg(tagid_retrosp(id));}
                default:{
                    return tgbs_ptr->comment(tagid_retrosp(id));}}};
        return "";}

    std::string   journalbase::tag_retrosp(size_type id) const {
        return exists(id) ? tgbs_ptr->name(tagid_retrosp(id)) : "";};

    void journalbase::add(const datetime& tm, size_type tgid, msgtype tp, altype lev , const double& val, size_type userid) {
        size_type adrp = tgbs_ptr->agroup(tgid);
        INP_EXCLUSIVE_LOCK(memlock());
        size_type newindx = inc();
        new (operator[](newindx)) journalstruct(gloubnum(), tm, tgid, tp, lev, adrp, val, userid);
        tgbs_ptr->notify_journal(newindx);}

    std::string  journalbase::agroupname(size_type id) const {
        size_type agrp = exists(id) ? operator[](id)->agroup() : npos;
        return tgbs_ptr->agroups()->exists(agrp) ? tgbs_ptr->agroups()->name(agrp) : "";}

    journalbase::size_type journalbase::agroup(const std::string& nm) const {
        return tgbs_ptr->agroups()->operator ()(nm);};

    // debugs


    // alarms

    std::string   alarmsbase::text(size_type id) const {
        return  tgbs_ptr->exists(tagid(id)) ?  tgbs_ptr->alarmmsg(tagid(id)) : "";};

    std::string   alarmsbase::tag(size_type id) const {
        return  tgbs_ptr->exists(tagid(id)) ?  tgbs_ptr->name(tagid(id)) : "";};

    alarmsbase::size_type alarmsbase::find_by_tagid(size_type id) {
        for (size_type i = 0; i < count(); ++i) {
            if (operator[](i)->tagid() == id) return i;}
        return npos;}

    void alarmsbase::checkout() {

        for (size_type i = 0; i < count() ; ) {
            if ((exists(i)) && (kvit(i)) && (off(i))) {
                if (type(i) == msNew)
                    tgbs_ptr->insert_to_journal(now(), tagid(i) , msOut, tgbs_ptr->alarmlevel(tagid(i)));
                incversion();
                internal_remove(i);}
            else i++;}}

    void   alarmsbase::add(const datetime& tm, size_type id, msgtype msgtp, const double& val) {

        if (! tgbs_ptr->exists(id)) return;
        if (! tgbs_ptr->alarmed(id)) return;

        INP_EXCLUSIVE_LOCK(memlock());

        (*tgbs_ptr)[id]->alarmkvit(false);
        (*tgbs_ptr)[id]->alarmon(msgtp == msNew);

        size_type fned = find_by_tagid(id);
        if (msgtp == msNew) {
            if (fned != npos) {
                kvit(fned, false);
                incversion();
                return;}}
        else {
            if (fned != npos) {
                time(fned, tm);
                tgbs_ptr->insert_to_journal( tgbs_ptr->time(id), id , msgtp, tgbs_ptr->alarmlevel(id), val);
                incversion();
                return;}}

        if (count() == maxcount()) pop_begin();

        size_type newid = inc();

        if (newid != npos) {
            new (operator[](newid)) alarmsstruct( globalnum(), tm, id, msgtp,  tgbs_ptr->alarmlevel(id),
                    tgbs_ptr->group(id),  tgbs_ptr->agroup(id));
            if (msgtp != msNew) operator[](newid)->off(true);
            incversion();
            tgbs_ptr->insert_to_journal( tgbs_ptr->time(id), id , msgtp, tgbs_ptr->alarmlevel(id), val);}}

    void alarmsbase::remove(size_type id) {
        INP_EXCLUSIVE_LOCK(memlock());
        size_type tmp = find_by_tagid(id);
        if (tmp != npos) {
            operator[](tmp)->off(true);
            checkout();}}

    void      alarmsbase::kvitall() {
        INP_EXCLUSIVE_LOCK(memlock());
        for (size_type i = 0; i < count(); ++i) {
            if (!(kvit(i))) {
                tgbs_ptr->insert_to_journal(now(), operator[](i)->tagid() , msKvit, tgbs_ptr->alarmlevel(tagid(i)));
                incversion();
                operator[](i)->kvit(true);}}
        checkout();}

    void       alarmsbase::kvit_agroup(size_type agrnum) {
        INP_EXCLUSIVE_LOCK(memlock());
        for (size_type i = 0; i < count(); ++i) {
            if ((operator[](i)->agroup() == agrnum) && (!(kvit(i)))) {
                tgbs_ptr->insert_to_journal(now(), operator[](i)->tagid() , msKvit, tgbs_ptr->alarmlevel(tagid(i)));
                incversion();
                operator[](i)->kvit(true);}}
        checkout();}

    void       alarmsbase::kvit_group(size_type grnum) {
        INP_EXCLUSIVE_LOCK(memlock());
        for (size_type i = 0; i < count(); ++i) {
            if ((operator[](i)->group() == grnum) && (!(kvit(i)))) {
                tgbs_ptr->insert_to_journal(now(), operator[](i)->tagid() , msKvit, tgbs_ptr->alarmlevel(tagid(i)));
                incversion();
                operator[](i)->kvit(true);}}
        checkout();}

    void       alarmsbase::kvit_tag(size_type id) {
        INP_EXCLUSIVE_LOCK(memlock());
        for (size_type i = 0; i < count(); ++i) {
            if ((operator[](i)->tagid() == id) && (!(kvit(i)))) {
                tgbs_ptr->insert_to_journal(now(), operator[](i)->tagid() , msKvit, tgbs_ptr->alarmlevel(tagid(i)));
                incversion();
                operator[](i)->kvit(true);}}
        checkout();}


    // commands

    void commandsbase::checkout() {

        for (size_type i = 0; i < count(); ) {
            if ((operator[](i))->executed())  {
                internal_remove(i);
                incversion();}
            else i++;}}

    commandsbase::size_type commandsbase::find_by_tagid(size_type id) {
        for (size_type i = 0; i < count(); ++i) {
            if (operator[](i)->tagid() == id) return i;}
        return npos;}

    std::string commandsbase::tag(size_type id) const {
        return (exists(id)) ? tgbs_ptr->name(tagid(id)) : "";};

    std::string commandsbase::groupname(size_type id) const {
        return (exists(id)) ? tgbs_ptr->groups()->name(id) : "";};

    std::string commandsbase::user(size_type id) const {
        return "";};

    std::string commandsbase::host(size_type id) const {
        return "";};

    addcmdtype commandsbase::add(size_type id, num64 preval, num64 val, tagtype tp, bool queue, guidtype clid) {

        INP_EXCLUSIVE_LOCK(memlock());

        if (!queue) {
            size_type tmp = find_by_tagid(id);
            if (tmp != npos) {
                operator[](id)->reset_commandstruct(val, clid);
                incversion();
                return acQueuedCommand;}}
        if (count() == maxcount()) pop_begin();
        size_type newid = inc();
        if (( tgbs_ptr->exists(id)) && ((newid != npos))) {
            new (operator[](newid)) commandstruct(globalnum(), id, tgbs_ptr->group(id), preval, val, clid, tp );
            incversion();
            return acNewCommand;}
        return acNullCommand;}

    addcmdtype commandsbase::add(size_type id, const std::string& val,  bool queue, guidtype clid) {

        INP_EXCLUSIVE_LOCK(memlock());

        if (!queue) {
            size_type tmp = find_by_tagid(id);
            if (tmp != npos) {
                operator[](id)->reset_commandstruct(val, clid);
                incversion();
                return acQueuedCommand;}}

        if (count() == maxcount()) pop_begin();
        size_type newid = inc();
        if (( tgbs_ptr->exists(id)) && ((newid != npos))) {
            new (operator[](newid)) commandstruct(globalnum(), id, tgbs_ptr->group(id), val, clid );
            incversion();
            return acNewCommand;}
        return acNullCommand;}

    bool   commandsbase::select_commands(command_vector& vect_, size_type group) {
        INP_EXCLUSIVE_LOCK(memlock());
        vect_.clear();
        bool tmp_find = false;
        bool comlete = false;
        indx_set tmpmp;
        if ((!count()) || (!tgbs_ptr)) return false;
        for (size_type i = count() - 1; ((i < count()) && (!comlete)) ; i--) {
            if (((operator[](i))->group() == group) || (group == npos)) {
                if (tmpmp.find(tagid(i)) == tmpmp.end()) {
                    (operator[](i))->executed(true);
                    commandstruct tmp = *operator[](i);
                    if (tgbs_ptr->restore_command_raw_range(tmp))
                        vect_.push_back(tmp);
                    tmpmp.insert(tagid(i));
                    tmp_find = true;}
                else comlete = true;}}
        if (tmp_find) checkout();
        return tmp_find;}

    bool commandsbase::select_commands(command_vector& vect_, indx_set groups) {
        INP_EXCLUSIVE_LOCK(memlock());
        vect_.clear();
        bool tmp_find = false;
        bool comlete = false;
        indx_set tmpmp;
        if ((!count()) || (!tgbs_ptr)) return false;
        for (size_type i = count() - 1; ((i < count()) && (!comlete)) ; i--) {
            if (groups.find((operator[](i))->group()) != groups.end()) {
                if (tmpmp.find(tagid(i)) == tmpmp.end()) {
                    (operator[](i))->executed(true);
                    commandstruct tmp = *operator[](i);
                    if (tgbs_ptr->restore_command_raw_range(tmp))
                        vect_.push_back(tmp);
                    tmpmp.insert(tagid(i));
                    tmp_find = true;}
                else comlete = true;}}
        if (tmp_find) checkout();
        return tmp_find;}

    bool   commandsbase::clear_commands(size_type group) {
        command_vector vect_;
        return select_commands(vect_, group);}



    // registry

    guidtype registrybase::reghandle(appidtype app,  eventtypeset evts) {
        if (app == 0) return 0;
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());

        if (count() == maxcount()) pop_begin();
        size_type newid = inc();
        if  (newid == npos) return npos;
        if ((evts != sIMMINone))
            selfhadle_ = globalnum();
        else
            selfhadle_ = 0;

        new (operator[](newid)) registrystruct(globalnum(), app,  evts, selfhadle_);

        if (selfhadle_ > 0) {
            mq_class*  queue = proccess_queues::getqueue(selfhadle_, true, tgbs_ptr->count() * 2 + EXTEND_MEMSHARE_TAGCNT / 4);
            if (queue) {
                mq_class_ptr ptr(queue);
                guid_mqs_mp.insert(guid_mq_pair(globalnum(), ptr));}}
        incversion();
        return (globalnum());}

    guidtype registrybase::unreghandle(guidtype gid) {
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());
        size_type rem = remove_by_guid(gid);
        incversion();
        return rem == npos ? 0 : gid;}

    void registrybase::rebuild_messageset() {
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());
        ev_mqs_map.clear();
        guidtype_set guids;
        for (size_type i = 0; i < count(); ++i) {
            if ((queuehandle(i) != 0)) {
                guids.insert(queuehandle(i));
                if (evset(i) & (sIMMILog)) {
                    evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMILog);
                    if (it == ev_mqs_map.end()) {
                        ev_mqs_map.insert(evst_indxmqmap_pair(sIMMILog, indx_mq_map()));
                        it = ev_mqs_map.find(sIMMILog);}
                    if (it != ev_mqs_map.end()) {
                        it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}}
            if (evset(i) & (sIMMIJournal)) {
                evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMIJournal);
                if (it == ev_mqs_map.end()) {
                    ev_mqs_map.insert(evst_indxmqmap_pair(sIMMIJournal, indx_mq_map()));
                    it = ev_mqs_map.find(sIMMIJournal);}
                if (it != ev_mqs_map.end()) {
                    it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}
            if (evset(i) & (sIMMIGroupManage)) {
                evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMIGroupManage);
                if (it == ev_mqs_map.end()) {
                    ev_mqs_map.insert(evst_indxmqmap_pair(sIMMIGroupManage, indx_mq_map()));
                    it = ev_mqs_map.find(sIMMIGroupManage);}
                if (it != ev_mqs_map.end()) {
                    it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}
            if (evset(i) & (sIMMITagManage)) {
                evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMITagManage);
                if (it == ev_mqs_map.end()) {
                    ev_mqs_map.insert(evst_indxmqmap_pair(sIMMITagManage, indx_mq_map()));
                    it = ev_mqs_map.find(sIMMITagManage);}
                if (it != ev_mqs_map.end()) {
                    it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}
            if (evset(i) & (sIMMIDBManage)) {
                evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMIDBManage);
                if (it == ev_mqs_map.end()) {
                    ev_mqs_map.insert(evst_indxmqmap_pair(sIMMIDBManage, indx_mq_map()));
                    it = ev_mqs_map.find(sIMMIDBManage);}
                if (it != ev_mqs_map.end()) {
                    it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}
            if (evset(i) & (sIMMIDebug)) {
                evst_indxmqmap_map::iterator it = ev_mqs_map.find(sIMMIDebug);
                if (it == ev_mqs_map.end()) {
                    ev_mqs_map.insert(evst_indxmqmap_pair(sIMMIDebug, indx_mq_map()));
                    it = ev_mqs_map.find(sIMMIDebug);}
                if (it != ev_mqs_map.end()) {
                    it->second.insert(indx_mq_pair(i, getproccessqueue(queuehandle(i))));}}}
        removeproccessqueue(guids);
        lastguid_ = version();}

    mq_class_ptr   registrybase::getproccessqueue(guidtype val) {
        if (val < 0) return mq_class_ptr();
        guid_mq_map::const_iterator it = guid_mqs_mp.find(val);
        if (it != guid_mqs_mp.end()) return it->second;
        mq_class* tmp = proccess_queues::getqueue(val, false);
        if (!tmp) return mq_class_ptr();
        mq_class_ptr ptr(tmp);
        guid_mqs_mp.insert(guid_mq_pair(val, ptr));
        return ptr;}

    void registrybase::removeproccessqueue(const guidtype_set& rmset) {
        guid_mq_map::iterator it = guid_mqs_mp.begin();
        while (it != guid_mqs_mp.end()) {
            if (rmset.find(it->first) != rmset.end()) ++it;
            else guid_mqs_mp.erase(it++);}}

    void registrybase::notify(qumsgtype mess, size_type id, num32 some, eventtypeset event) {
        if (version() != lastguid_) {
            rebuild_messageset();}
        THD_EXCLUSIVE_LOCK(mtx());
        evst_indxmqmap_map::iterator it = ev_mqs_map.find(event);
        if (it != ev_mqs_map.end()) {
            for (indx_mq_map::iterator itevset = it->second.begin(); itevset != it->second.end(); ++itevset) {
                if (itevset->second) {
                    proccess_queues::try_send(itevset->second.get(), mess, id, some);}}}}

    // clients

    guidtype clientbase::regclient(appidtype app, const std::string& hst , const std::string& ipp , const std::string& usr ,  const std::string& password) {
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());
        if (tgbs_ptr->grant_access(app,  hst , ipp , usr , password)) {
            size_type newid = inc();
            new (operator[](newid)) clientstruct (globalnum(), app, 0, hst , ipp, usr, npos);
            clientscls->insert(globalnum());
            incversion();
            return globalnum();}
        return 0;}

    guidtype clientbase::unregclient(guidtype gid) {
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());
        size_type rem = remove_by_guid(gid);
        clientscls->eraise(globalnum());
        incversion();
        return rem == npos ? 0 : gid;}

    guidtype clientbase::unregclient_from_set(guidtype gid) {
        THD_EXCLUSIVE_LOCK(mtx());
        INP_EXCLUSIVE_LOCK(memlock());
        size_type rem = remove_by_guid(gid);
        incversion();
        return rem == npos ? 0 : gid;}


    // groups

    void groupsbase::active(size_type id, bool val) {
        if (exists(id)) {
            if (operator[](id)->active() != val) {
                time(id, now());
                operator[](id)->active(val);}}}

    void groupsbase::valid(size_type id, vlvtype val) {
        if (exists(id)) {
            if (operator[](id)->valid() != val) {
                time(id, now());
                operator[](id)->valid(val);}}}

    void groupsbase::host(size_type id, const std::string& val) {
        if (exists(id)) {
            if (host(id) != val) {
                size_t tmp = operator[](id)->hostpos();
                stringbase_src(tmp, val);
                operator[](id)->hostpos(tmp);}}}

    void groupsbase::user(size_type id, const std::string& val) {
        if (exists(id)) {
            if (user(id) != val) {
                size_t tmp = operator[](id)->userpos();
                stringbase_src(tmp, val);
                operator[](id)->userpos(tmp);}}}

    void groupsbase::password(size_type id, const std::string& val) {
        if (exists(id)) {
            if (password(id) != val) {
                size_t tmp = operator[](id)->passpos();
                stringbase_src(tmp, val);
                operator[](id)->passpos(tmp);}}}

    void groupsbase::server(size_type id, const std::string& val) {
        if (exists(id)) {
            if (server(id) != val) {
                size_t tmp = operator[](id)->serverpos();
                stringbase_src(tmp, val);
                operator[](id)->serverpos(tmp);}}}

    void groupsbase::port(size_type id, const std::string& val) {
        if (exists(id)) {
            if (port(id) != val) {
                size_t tmp = operator[](id)->portpos();
                stringbase_src(tmp, val);
                operator[](id)->portpos(tmp);}}}

    void groupsbase::group(size_type id, const std::string& val) {
        if (exists(id)) {
            if (group(id) != val) {
                size_t tmp = operator[](id)->grouppos();
                stringbase_src(tmp, val);
                operator[](id)->grouppos(tmp);}}}

    void groupsbase::topic(size_type id, const std::string& val) {
        if (exists(id)) {
            if (topic(id) != val) {
                size_t tmp = operator[](id)->topicpos();
                stringbase_src(tmp, val);
                operator[](id)->topicpos(tmp);}}}

    void groupsbase::ether(size_type id, const std::string& val) {
        if (exists(id)) {
            if (ether(id) != val) {
                size_t tmp = operator[](id)->etherpos();
                stringbase_src(tmp, val);
                operator[](id)->etherpos(tmp);}}}

    void  groupsbase::local(size_type id, lcltype val) {
        if (exists(id)) {
            if (operator[](id)->local() != val) {
                operator[](id)->local(val);}}}

    void groupsbase::chanaltype(size_type id, chnltype  val) {
        if (exists(id)) {
            if (operator[](id)->chanaltype() != val) {
                operator[](id)->chanaltype(val);}}}

    void  groupsbase::chanalnum(size_type id, chnlnumtype val) {
        if (exists(id)) {
            if (operator[](id)->chanalnum() != val) {
                operator[](id)->chanalnum(val);}}}


    //void  groupsbase::portnum(size_type id, num32  val) {
    //    if (exists(id)) {
    //        if (operator[](id)->portnum() != val) {
    //            metalink oldlnk = link(id);
    //            operator[](id)->portnum(val);}}}

    void  groupsbase::devnum(size_type id, devnumtype  val) {
        if (exists(id)) {
            if (operator[](id)->devnum() != val) {
                operator[](id)->devnum(val);}}}

    void  groupsbase::protocol(size_type id, protocoltype  val) {
        if (exists(id)) {
            if (operator[](id)->protocol() != val) {
                operator[](id)->protocol(val);}}}

    void  groupsbase::synctype(size_type id, subcripttype val) {
        if (exists(id)) {
            if (operator[](id)->synctype() != val) {
                operator[](id)->synctype(val);}}}

    void  groupsbase::ver(size_type id, intfvertype val) {
        if (exists(id)) {
            if (operator[](id)->ver() != val) {
                operator[](id)->ver(val);}}}

    void  groupsbase::supporttype(size_type id, bool val) {
        if (exists(id)) {
            if (operator[](id)->supporttype() != val) {
                operator[](id)->supporttype(val);}}}

    void groupsbase::writezero(const fspath&  fpath) {
        smplheader inhdr;
        filestream::write(fpath / GROUPS_FILE_NAME, (num8*) & inhdr, 0, sizeof (smplheader));}

    bool groupsbase::checkname(const string& val, size_type parnt)  {
        if ((operator [](val)))
            throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, operator ()(val));
        boost::regex xtagTemplete(CORRECT_ENTETYNAME_REGEXTAMPL);
        if (!boost::regex_match( val, xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        boost::regex ex_xtagTemplete(EXCL_CORRECT_ENTETYNAME_REGEXTAMPL);
        if (boost::regex_match( val, ex_xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        return true;}

    void groupsbase::initstruct(size_type id, const std::string& newname, size_type parent) {
        new ( &((pgroupsstruct) data())->items[id] ) groupstruct(able_ptr);
        name(id, newname, false);
        appid(id, 0);
        writetofile(id);}

    void groupsbase::uninitstruct(size_type id) {
        host(id, "");
        user(id, "");
        password(id, "");
        server(id, "");
        group(id, "");
        port(id, "");
        topic(id, "");
        ether(id, "");
        templatebase<groupsstruct>::uninitstruct(id);}

    void groupsbase::trigger_add(size_type id, size_type opt) {
        notify_groupmanage(MSG_DVNCIGROUPNEW, id, 0);};

    void groupsbase::trigger_remove(size_type id, size_type opt) {
        notify_groupmanage(MSG_DVNCIGROUPDELETE, id, 0);};

    void groupsbase::trigger_util(size_type id, const struct_type& oldst,  const struct_type& newst) {
        notify_groupmanage(MSG_DVNCIGROUPCHAPP, id , static_cast<num32> (newst.id() ? newst.appid() : 0));}

    void groupsbase::notify_tagmanage(qumsgtype mess, size_type id, size_type group) {
        if (systemnotifyer)
            systemnotifyer->notify_tagmanage(mess, id, group);}

    void groupsbase::notify_groupmanage(qumsgtype mess, size_type id, num32 some) {
        if (systemnotifyer)
            systemnotifyer->notify_groupmanage(mess, id, some);}

    void groupsbase::appid(size_type id, appidtype  val)  {
        if (exists(id)) {
            if (operator[](id)->appid() != val) {
                formatmem_in_null(operator[](id)->config(), GROP_CONFIG_SIZE);
                operator[](id)->appid(val);}}}

    groupsbase::size_type groupsbase::select_groups_by_appid(appidtype val) {
        for (size_type i = 0; i < count(); ++i) {
            if (exists(i))
                if (appid(i) == val) return i;}
        return npos;}

    void groupsbase::clone(size_type idsrc, size_type iddst) {
        if ((!exists(idsrc)) || (!exists(iddst))) return;
        groupstruct::clone(((pgroupsstruct) data())->items[idsrc],
                ((pgroupsstruct) data())->items[iddst]);
        host(idsrc, host(iddst));
        ether(idsrc, ether(iddst));
        password(idsrc,  password(iddst));
        port(idsrc,  port(iddst));
        server(idsrc,  server(iddst));
        topic(idsrc,  topic(iddst));
        user(idsrc,  user(iddst));
        writetofile(idsrc);}




    // agroups

    void agroupsbase::headername(size_type id, const std::string&  val) {
        if (exists(id)) {
            if (headername(id) != val) {
                size_t tmp = operator[](id)->headernamepos();
                stringbase_src(tmp, val);
                operator[](id)->headernamepos(tmp);}}}

    void agroupsbase::writezero(const fspath&  fpath) {
        smplheader inhdr;
        filestream::write(fpath / ALARMGROUPS_FILE_NAME, (num8*) & inhdr, 0, sizeof (smplheader));}

    bool agroupsbase::checkname(const string& val, size_type parnt)   {
        if ((operator [](val)))
            throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, operator ()(val));
        boost::regex xtagTemplete(CORRECT_ENTETYNAME_REGEXTAMPL);
        if (!boost::regex_match( val, xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        boost::regex ex_xtagTemplete(EXCL_CORRECT_ENTETYNAME_REGEXTAMPL);
        if (boost::regex_match( val, ex_xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        return true;}

    void agroupsbase::initstruct(size_type id, const std::string& newname, size_type parent) {
        new  ( &((pagroupsstruct) data())->items[id] ) agroupstruct(able_ptr);
        name(id, newname, false);
        headername(id, "");
        writetofile(id);}

    void agroupsbase::uninitstruct(size_type id) {
        headername(id, "");
        templatebase<agroupsstruct>::uninitstruct(id);}






    void accessrulesbase::user(size_type id, const std::string&  val) {
        if (exists(id)) {
            if (user(id) != val) {
                size_t tmp = operator[](id)->userpos();
                stringbase_src(tmp, val);
                operator[](id)->userpos(tmp);}}}
    
     void accessrulesbase::host(size_type id, const std::string&  val) {
        if (exists(id)) {
            if (host(id) != val) {
                size_t tmp = operator[](id)->hostpos();
                stringbase_src(tmp, val);
                operator[](id)->hostpos(tmp);}}}   

    void accessrulesbase::writezero(const fspath&  fpath) {
        smplheader inhdr;
        filestream::write(fpath / ACCESSRULES_FILE_NAME, (num8*) & inhdr, 0, sizeof (smplheader));}

    bool accessrulesbase::checkname(const string& val, size_type parnt)   {
        if ((operator [](val)))
            throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, operator ()(val));
        return true;}

    void accessrulesbase::initstruct(size_type id, const std::string& newname, size_type parent) {
        new ( &((paccessrulesstruct) data())->items[id] ) accessrulestruct(able_ptr);
        name(id, newname, false);
        user(id, "");
        writetofile(id);}

    void accessrulesbase::uninitstruct(size_type id) {
        user(id, "");
        templatebase<accessrulesstruct>::uninitstruct(id);}



    // users

    bool usersbase::changepassword(size_type id, const std::string&  newpass) {
        if (exists(id)) {
            password(id, newpass);
            return true;}
        return false;}

    bool usersbase::changepassword(const std::string&  user, const std::string&  newpass) {
        if (exists(user)) return changepassword((*this)(user), newpass);
        return false;}

    bool usersbase::registrateuser(const std::string&  user, const std::string&  pass) {
        if (exists(user)) return false;
        return true;}

    acclevtype usersbase::useraccesslevel(const std::string&  user) {
        if (exists(user)) return 0;
        return ((*this)[(*this)(user)]->accesslevel());}

    void usersbase::writezero(const fspath&  fpath) {
        smplheader inhdr;
        filestream::write(fpath / OPERATOR_FILE_NAME, (num8*) & inhdr, 0, sizeof (smplheader));}

    bool usersbase::checkname(const string& val, size_type parnt)  {
        if ((operator [](val)))
            throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, operator ()(val));
        return true;}

    void usersbase::initstruct(size_type id, const std::string& newname, size_type parent) {
        new ( &((pusersstruct) data())->items[id]) userstruct (able_ptr);
        name(id, newname, false);
        password(id, "");
        writetofile(id);}

    void usersbase::uninitstruct(size_type id) {
        password(id, "");
        templatebase<usersstruct>::uninitstruct(id);}



    // tagsbase

    interproc_namemutex* tagsbase::one_init_ = 0;

    interproc_namemutex& tagsbase::one_init() {
        boost::interprocess::permissions permis;
        permis.set_unrestricted();
        if (!one_init_) one_init_ =
                new interproc_namemutex(boost::interprocess::open_or_create, NS_ONETIMEINIT_MTXNAME.c_str(), permis);
        return (*one_init_);}

    tagsbase::tagsbase(const fspath& basepatht, appidtype app, eventtypeset evnts , lock_nameexclusive ontimeinit) :
    templatebase<tagsstruct>(basepatht / MAIN_FILE_NAME , MAIN_MAP_NAME, EXTEND_MEMSHARE_TAG_SIZE ) , fpath(basepatht), globalmemsize_(0), appid_(app) {

        stringbs_ = stringbase_ptr(new stringbase(basepatht / STRING_FILE_NAME, STRING_MAP_NAME, EXTEND_MEMSHARE_STR_SIZE));
        valstrb_ =  stringvalue_base_ptr(new stringvalue_base(basepatht / VALSTRING_FILE_NAME , VALSTRING_MAP_NAME, texttagcnt(), EXTEND_MEMSHARE_STRSTATIC_SIZE));
        groups_        =  groupsbase_ptr(new groupsbase(stringbs_, this, basepatht));
        agroups_       =  agroupsbase_ptr(new agroupsbase(stringbs_, this, basepatht));
        size_t tmp = ((capacity() / sizeof (tagstruct)) * 2) +
                ((groups_->capacity() / sizeof (groupstruct))) +
                ((agroups_->capacity() / sizeof (agroupstruct))) + 10000;
        item_indexer = indexitem_ptr(new  index_base(stringbs_, MAIN_MAP_NAME + "_index", tmp));
        handle_ = 0;
        registry_      =  registrybase_ptr(new registrybase(this, REGISTRATION_MAP_NAME));
        debug_           =  debugbase_ptr(new debugbase(DEBUGS_MAP_NAME));
        ((tagsstruct_hdr*) data())->os_type(NS_CURRENT_OS_TYPE);
        commands_      =  commandsbase_ptr(new commandsbase(this, COMMAND_MAP_NAME));
        journal_       =  journalbase_ptr(new journalbase(this, ALARMS_MAP_NAME));
        alarms_        =  alarmsbase_ptr(new alarmsbase(this, ALARMLOCALS_MAP_NAME));
        clients_       =   clientbase_ptr(new clientbase(this, CLIENTBASE_MAP_NAME));
        accessrules_   =  accessrulesbase_ptr(new accessrulesbase(stringbs_, this, basepatht));
        users_         =  usersbase_ptr(new usersbase(stringbs_, this, basepatht));

        if (item_indexer->isnew()) {
            INP_EXCLUSIVE_LOCK(item_indexer->memlock())
            buildindex();}


        valbuffers_ = valuebufferbase_ptr( new valuebufferbase(ANALOBUFF_MAP_NAME, archtagcnt()));
        if ((valbuffers()) && (valbuffers()->isnew())) {
            fill_logkeys();}

        reportbuffers_ = reportbufferbase_ptr( new reportbufferbase(REPORTBUFF_MAP_NAME, reporttagcnt()));
        if ((reportbuffers()) && (reportbuffers()->isnew())) {
            fill_reportkeys();}

        debugwarning("Report count is " + to_str(reporttagcnt()));
        debugwarning("Achive count is " + to_str(archtagcnt()));
        debugwarning("Text count is " + to_str(texttagcnt()));

        reghandle(app, evnts);

#ifdef DVNCI_DEDUG
        std::string tmpdbg2 = std::string("Stop maininit isnew = ") + std::string(isnew() ? "NEW" : "n") + "rank = " + to_str(handle_ );
        debugwarning(tmpdbg2);
#endif
        ;}

    tagsbase::~tagsbase() {
#ifdef DVNCI_DEDUG
        /*debugwarning(mapname() + "MAIN size=" + to_str(mapsize() / 1024) + "kb");
        if (stringbs_) debugwarning(stringbs_->mapname() + "  stringbs_ size=" + to_str(stringbs_->mapsize() / 1024) + "kb");
        if (valstrb_) debugwarning(valstrb_->mapname() + "  valstrb_ size=" + to_str(valstrb_->mapsize() / 1024) + "kb");
        if (commands_) debugwarning(commands_->mapname() + "  commands_ size=" + to_str(commands_->mapsize() / 1024) + "kb");
        if (journal_) debugwarning(journal_->mapname() + "   journal_ size=" + to_str(journal_->mapsize() / 1024) + "kb");
        if (alarms_) debugwarning(alarms_->mapname() + "   alarms_ size=" + to_str(alarms_->mapsize() / 1024) + "kb");
        if (debug_) debugwarning(debug_->mapname() + "   debug_ size=" + to_str(debug_->mapsize() / 1024) + "kb");
        if (registry_) debugwarning(registry_->mapname() + "   registry_ size=" + to_str(registry_->mapsize() / 1024) + "kb");
        if (clients_) debugwarning(clients_->mapname() + "   registry_ size=" + to_str(clients_->mapsize() / 1024) + "kb");
        if (groups()) debugwarning(groups()->mapname() + "   groups() size=" + to_str(groups()->mapsize() / 1024) + "kb");
        if (agroups()) debugwarning(agroups()->mapname() + "   agroups() size=" + to_str(agroups()->mapsize() / 1024) + "kb");
        if (accessrules()) debugwarning(accessrules()->mapname() + "   accessrules() size=" + to_str(accessrules()->mapsize() / 1024) + "kb");
        if (users()) debugwarning(users()->mapname() + "  users() size=" + to_str(users()->mapsize() / 1024) + "kb");
        if (valbuffers()) debugwarning(valbuffers()->mapname() + "  valbuffers() size=" + to_str(valbuffers()->mapsize() / 1024) + "kb");
        if (reportbuffers()) debugwarning(reportbuffers()->mapname() + "  reportbuffers() size=" + to_str(reportbuffers()->mapsize() / 1024) + "kb");*/
        DEBUG_STR_DVNCI( "d_tor tagbase!!!!!")
#endif
        //debug("d_tor tagbase  rank=" + to_str(handle_));
        unreghandle();
        //debug("d_tor tagbase after unreg rank=" + to_str(handle_))
			;}

    void tagsbase::writezero(const fspath& basepatht, lcltype loc ) {
        num64 str_head = 1;
        char* str_ptr = (char*) &str_head;
        stringbase::writezero(basepatht / STRING_FILE_NAME);
        stringvalue_base::writezero(basepatht / VALSTRING_FILE_NAME);
        tagsstruct_hdr ang_head(loc);
        filestream::write(basepatht / MAIN_FILE_NAME, (char*) &ang_head, 0, ang_head.datasize());
        str_head = 0;
        str_ptr = (char*) &str_head;
        groupsbase::writezero(basepatht);
        agroupsbase::writezero(basepatht);
        accessrulesbase::writezero(basepatht);
        usersbase::writezero(basepatht);
        std::string metanull = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><meta DBProvider=\"\" constring=\"\" host=\"\"><HomeList key=\"0\">"
                "<ReportArr key=\"0\"></ReportArr><TrendArr key=\"0\"></TrendArr></HomeList>"
                "<ReportList key=\"0\"></ReportList><TrendList key=\"0\"></TrendList>"
                "<MessageList key=\"0\"></MessageList></meta>\n";
        filestream::write(basepatht / META_FILE_NAME, (char*) metanull.c_str(), 0, metanull.size());}

    std::string tagsbase::conf_property(const confproptype& name) const {
        switch (name) {
            case NS_CNFG_PATH: return fpath.string();
            case NS_CNFG_LOGLEVEL: return to_str<debuglvtype > (prjcfg_debuglevel());
            case NS_CNFG_LOCAL: return to_str<lcltype > (prjcfg_local());
            case NS_CNFG_MAPSZ: return to_str<num32 > (globalmemsize());
            case NS_CNFG_ARCHCNT: return to_str<num32 > (archtagcnt());
            case NS_CNFG_DBMANAGER: return to_str<dbprovtype > (prjcfg_dbprovider());
            case NS_CNFG_ANALOGBUFF: return prjcfg_analogbuf() ? "1": "0";
            case NS_CNFG_HISTORYPERIOD: return to_str<num32 > (prjcfg_bddepth());
            case NS_CNFG_DBCONSTR: return prjcfg_dbstring();
            case NS_CNFG_NAME: return prjcfg_name();
            case NS_CNFG_COMMENT: return prjcfg_comment();
            case NS_CNFG_ADMINNAME: return prjcfg_admin();
            case NS_CNFG_ADMINPASS: return prjcfg_password();
            case NS_CNFG_ADMINPORT: return prjcfg_adminport();
            case NS_CNFG_REMOTEPORT: return prjcfg_remoteport();
            case NS_CNFG_OPCREMOTEPORT: return prjcfg_opcport();
            case NS_CNFG_OSTYPE: return to_str<num32 > (prjcfg_ostype());
            default:{};}
        return "";}

    void tagsbase::conf_property(const confproptype& name, const std::string& val) {
        switch (name) {
            case NS_CNFG_LOGLEVEL:{
                debuglvtype tmp = 0;
                if (str_to<debuglvtype > (val, tmp)) prjcfg_debuglevel(tmp);
                return;}
            case NS_CNFG_DBMANAGER:{
                dbprovtype tmp = 0;
                if (str_to<dbprovtype > (val, tmp)) prjcfg_dbprovider(tmp);
                return;}
            case NS_CNFG_ANALOGBUFF:{
                prjcfg_analogbuf( val == "1");
                return;}
            case NS_CNFG_HISTORYPERIOD:{
                num32 tmp = 0;
                if (str_to<num32 > (val, tmp)) prjcfg_bddepth(tmp);
                return;}
            case NS_CNFG_DBCONSTR:{
                prjcfg_dbstring(val);
                return;}
            case NS_CNFG_NAME:{
                prjcfg_name(val);
                return;}
            case NS_CNFG_COMMENT:{
                prjcfg_comment(val);
                return;}
            case NS_CNFG_ADMINNAME:{
                prjcfg_admin(val);
                return;}
            case NS_CNFG_ADMINPASS:{
                prjcfg_password(val);
                return;}
            case NS_CNFG_ADMINPORT:{
                prjcfg_adminport(val);
                return;}
            case NS_CNFG_REMOTEPORT:{
                prjcfg_remoteport(val);
                return;}
            case NS_CNFG_OPCREMOTEPORT:{
                prjcfg_opcport(val);
                return;}
            default:{};}}
    
    
    // value_expiered     
    bool tagsbase::value_expiered(size_type id, const short_value& rs, double db, timeouttype tmo) const{
        if (!exists(id)) return false;
        short_value ls= value_shv(id);
        if ((ls.valid()!=rs.valid()) || (ls.error()!=rs.error()) || (ls.type()!=rs.type())) 
                return true;
        if ((ls.time().is_special())!=(rs.time().is_special())) 
                return true;
        if ((!(ls.time().is_special())) && (tmo>0)) {
             if (dvnci::abs(secondsbetween(ls.time(),rs.time()))>static_cast<num64>(tmo)) 
                    return true;}
        switch(type(id)) {
               case TYPE_NODEF:{
                    return (dvnci::abs(ls.value<double>()-rs.value<double>())>(dvnci::abs(maxeu_prtd<double>(id)-mineu_prtd<double>(id))) * db / 100);}
               case TYPE_DISCRET:{
                    return ls.value<bool>()!=rs.value<bool>();}
               case TYPE_NUM64:{
                    return dvnci::abs(ls.value<num64>()-rs.value<num64>())>((dvnci::abs(maxeu_prtd<num64>(id)-mineu_prtd<num64>(id))) * db / 100);}
               case TYPE_UNUM64:{
                    return dvnci::abs(ls.value<unum64>()-rs.value<unum64>())>((dvnci::abs(maxeu_prtd<unum64>(id)-mineu_prtd<unum64>(id))) * db / 100);}
               case TYPE_NUM32:{
                    return dvnci::abs(ls.value<num32>()-rs.value<num32>())>((dvnci::abs(maxeu_prtd<num32>(id)-mineu_prtd<num32>(id))) * db / 100);}
               case TYPE_UNUM32:{
                    return dvnci::abs(ls.value<unum32>()-rs.value<unum32>())>((dvnci::abs(maxeu_prtd<unum32>(id)-mineu_prtd<unum32>(id))) * db / 100);}
               case TYPE_NUM16:{
                    return dvnci::abs(ls.value<num16>()-rs.value<num16>())>((dvnci::abs(maxeu_prtd<num16>(id)-mineu_prtd<num16>(id))) * db / 100);}
               case TYPE_UNUM16:{
                    return dvnci::abs(ls.value<unum16>()-rs.value<unum16>())>((dvnci::abs(maxeu_prtd<unum16>(id)-mineu_prtd<unum16>(id))) * db / 100);}
               case TYPE_NUM8:{
                    return dvnci::abs(ls.value<num8>()-rs.value<num8>())>((dvnci::abs(maxeu_prtd<num8>(id)-mineu_prtd<num8>(id))) * db / 100);}
               case TYPE_UNUM8:{
                   return dvnci::abs(ls.value<unum8>()-rs.value<unum8>())>((dvnci::abs(maxeu_prtd<unum8>(id)-mineu_prtd<unum8>(id))) * db / 100);}
               case TYPE_DOUBLE:{
                    return (dvnci::abs(ls.value<double>()-rs.value<double>())>(dvnci::abs(maxeu_prtd<double>(id)-mineu_prtd<double>(id))) * db / 100);}
               case TYPE_FLOAT:{
                    return (dvnci::abs(ls.value<float>()-rs.value<float>())>(dvnci::abs(maxeu_prtd<float>(id)-mineu_prtd<float>(id))) * db / 100);}
               case TYPE_TIME:{
                    return true;}
               case TYPE_TEXT:{
                    return ls.value<std::string>()!=rs.value<std::string>();}
            default:{
                return false;}}
            return false;}

    void tagsbase::valid(size_type id, vlvtype vld) {
        if (exists(id)) {
            operator[](id)->valid(vld);}}

    bool tagsbase::reportbuffered(size_type id) const {
        return (reportkey(id) != npos);}

    vlvtype tagsbase::reportstate(size_type id) {
        if ((exists(id)) && (IN_REPORTSET(type(id)))) {
            switch (operator[](id)->valid()) {
                case REPORT_NODATA:{
                    increpttime(id);
                    break;}
                case REPORT_NORMAL:{
                    checkreporttime(id);
                    break;}
                case REPORT_NOACTIVE:{
                    operator[](id)->valid(REPORT_NEEDKHOWDEEP);}}
            return operator[](id)->valid();}
        return 1;}

    bool tagsbase::valid_as_reportsource(size_type id) const {
        return ((exists(id)) && (valid(id) == FULL_VALID) &&
                ((!IN_REPORTSET(type(id))) || (time_log(id) > now())));}

    void tagsbase::error(size_type id, ns_error value) {
        if (exists(id)) {
            if (value) valid(id, 0);
            operator[](id)->error(value);}}

    void tagsbase::type(size_type id, tagtype value) {
        if ((exists(id)) && (IN_TYPESET(value))) {
            if (value != type(id)) {
                operator[](id)->type(value);
                to_standart_range(id);}}}

    void tagsbase::group(size_type id, size_type value, bool message) {
        if ((exists(id)) && (groups_->exists(value))) {
            checkname(retremoved_namespace_delimit(name(id)), value);
            size_type grnum = group(id);
            if (grnum != value) {
                removeindex(id);
                operator[](id)->group(value);
                addindex(id);
                valid(id, (groups()->appid(value) == NS_GROUP_SYSTEMVAR) ? FULL_VALID : NULL_VALID);}
            writetofile(id);
            if ((message) && (refcnt(id))) notify_tagmanage(MSG_DVNCTAGDELFROMGR, id, grnum);
            if ((message) && (refcnt(id))) notify_tagmanage(MSG_DVNCTAGADDTOGR, id, value);}}

    void tagsbase::agroup(size_type id, size_type value, bool message) {
        if ((exists(id)) && (agroups_->exists(value))) {
            checkname(retremoved_namespace_delimit(name(id)), value);
            size_type agrnum = operator[](id)->agroup();
            if (agrnum != value) {
                operator[](id)->agroup(value);
                writetofile(id);}}}

    void tagsbase::comment(size_type id, const std::string&  value) {
        if (exists(id)) {
            size_t tmp = operator[](id)->poscomment();
            stringbase_src(tmp, value);
            operator[](id)->poscomment(tmp);}}

    void tagsbase::binding(size_type id, const std::string&  value, bool triggered) {
        if (exists(id)) {
            if (value != binding(id)) {
                size_t tmp = operator[](id)->posbinding();
                stringbase_src(tmp, value, DVNCI_DEFRES_NAMESIZE);
                operator[](id)->posbinding(tmp);
                if (triggered) {
                    trigger_bind(id);}}}}

    void  tagsbase::eu(size_type id, const std::string&  value) {
        if (exists(id)) {
            size_t tmp = operator[](id)->poseu();
            stringbase_src(tmp, value, DVNCI_DEFRES_NAMESIZE);
            operator[](id)->poseu(tmp);}}

    void tagsbase::onmsg(size_type id, const std::string&  value) {
        if (exists(id)) {
            size_t tmp = operator[](id)->posonmsg();
            stringbase_src(tmp, value);
            operator[](id)->posonmsg(tmp);}}

    void tagsbase::offmsg(size_type id, const std::string& value) {
        if (exists(id)) {
            size_t tmp = operator[](id)->posoffmsg();
            stringbase_src(tmp, value);
            operator[](id)->posoffmsg(tmp);}}

    void tagsbase::alarmmsg(size_type id, const std::string&  value) {
        if (exists(id)) {
            size_t tmp = operator[](id)->posalarmmsg();
            stringbase_src(tmp, value);
            operator[](id)->posalarmmsg(tmp);}}

    void tagsbase::logged(size_type id, bool value) {
        if (exists(id)) {
            if (operator[](id)->logged() != value) {
                operator[](id)->logged(value);}}}
    
    

    void tagsbase::incref(size_type id) {
        if ((exists(id )) && (!IN_ALWACTSET(type(id)))) {
            operator[](id)->increfcnt();
            if (operator[](id)->refcnt() == 1)  
                registry()->notify_newref(id, group(id));}}
    
    void  tagsbase::incref(const std::string& id){
             size_type ind = operator ()(id);
             if (exists(ind)) 
                 incref(ind);}  

    void tagsbase::decref(size_type id) {
        if ((exists(id )) && (!IN_ALWACTSET(type(id)))) {
            if (refcnt(id)) {
                operator[](id)->decrefcnt();
                if (!operator[](id)->refcnt()) {
                    offtag(id);
                    registry()->notify_remref(id, group(id));}}}} 
    
            
    void tagsbase::decref(const std::string& id){
             size_type ind = operator ()(id);
             if (exists(ind)) 
                 decref(ind);}  
    

    void tagsbase::group_appid(size_type id, appidtype val) {
        if (groups()->exists(id)) {
            appidtype old_appid = groups()->appid(id);
            if (val != groups()->appid(id)) {
                groups()->appid(id, val);
                if (old_appid == NS_GROUP_SYSTEMVAR) inputsysvargroups(id, false);
                if (val == NS_GROUP_SYSTEMVAR) inputsysvargroups(id, true);}}}

    void tagsbase::write_val(size_type id, const std::string& val, vlvtype validlvl,  const datetime& tm, ns_error err ) {
        if (exists(id)) {
            switch (type(id)) {
                case TYPE_DISCRET:{
                    val != "0" ? write_val<bool>(id, 1, validlvl, tm, err) : write_val<bool>(id, 0, validlvl, tm, err);
                    return;}
                case TYPE_NUM64:{
                    num64 tmp;
                    if (str_to<num64 > (val, tmp)) write_val<num64 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_UNUM64:{
                    unum64 tmp;
                    if (str_to<unum64 > (val, tmp)) write_val<unum64 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_NUM32:{
                    num32 tmp;
                    if (str_to<num32 > (val, tmp)) write_val<num32 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_UNUM32:{
                    unum32 tmp;
                    if (str_to<unum32 > (val, tmp)) write_val<unum32 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_NUM16:{
                    num16 tmp;
                    if (str_to<num16 > (val, tmp)) write_val<num16 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_UNUM16:{
                    unum16 tmp;
                    if (str_to<unum16 > (val, tmp)) write_val<unum16 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_NUM8:{
                    num8 tmp;
                    if (str_to<num8 > (val, tmp)) write_val<num8 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_UNUM8:{
                    unum8 tmp;
                    if (str_to<unum8 > (val, tmp)) write_val<unum8 > (id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_DOUBLE:{
                    double tmp;
                    if (str_to<double>(val, tmp)) write_val<double>(id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_FLOAT:{
                    float tmp;
                    if (str_to<float>(val, tmp)) write_val<float>(id, tmp, validlvl, tm, err);
                    return;}
                case TYPE_TEXT:{
                    value_internal(id, val);
                    time(id, ((tm == nill_time) ? now() : tm));
                    valid(id, validlvl);
                    error(id, err);
                    return;}}
            double tmp;
            if (str_to<double>(val, tmp)) write_val<double>(id, tmp, validlvl, tm, err);}}

    void tagsbase::write_val(size_type id, const datetime& val, vlvtype validlvl, const datetime& tm, ns_error err) {
        if (exists(id)) {
            operator[](id)->value64( castnum64_from_datetime(val));
            time(id, ((tm == nill_time) ? now() : tm));
            valid(id, validlvl);
            error(id, err);}}

    void tagsbase::write_val(size_type id, const short_value& val) {
        if (exists(id)) {
            bool istxt = (val.type() == TYPE_TEXT);
            switch (type(id)) {
                case TYPE_NONE:{
                    write_val<double>(id, val.value<double>(), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_DISCRET:{
                    write_val<bool>(id, val.value<bool>(), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_NUM64:{
                    write_val<num64 > (id, val.value<num64 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_UNUM64:{
                    write_val<unum64 > (id, val.value<unum64 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_NUM32:{
                    write_val<num32 > (id, val.value<num32 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_UNUM32:{
                    write_val<unum32 > (id, val.value<unum32 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_NUM16:{
                    write_val<num16 > (id, val.value<num16 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_UNUM16:{
                    write_val<unum16 > (id, val.value<unum16 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_NUM8:{
                    write_val<num8 > (id, val.value<num8 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_UNUM8:{
                    write_val<unum8 > (id, val.value<unum8 > (), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_DOUBLE:{
                    write_val<double>(id, val.value<double>(), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}
                case TYPE_TM:{
                    write_val(id, cast_datetime_fromnum64(val.value64()) , val.valid(), val.time(), val.error());
                    return;}
                case TYPE_TEXT:{
                    write_val(id, val.value<std::string > () , val.valid(), val.time(), val.error());
                    return;}
                case TYPE_FLOAT:{
                    write_val<float>(id, val.value<float>(), val.valid(), val.time(), val.error());
                    if (istxt)
                        error( val.error());
                    return;}}
            write_val<double>(id, val.value<double>(), val.valid(), val.time(), val.error());}}

    void tagsbase::write_val_report(size_type id, datetime tm , double val , ns_error err, bool onlybuffer ) {
        if ((exists(id)) && (!tm.is_special())) {
            insert_to_reportbuff(id, tm , val);
            normalizeperiod(tm, type(id));
            error(id, err);
            if ((isNaN(val)) || (onlybuffer))
                increporttime(tm, type(id), 1);
            if (!isNaN(val))
                value_internal<double>(id, val);
            time_log(id, tm);
            increporttime(tm, type(id), -1);
            time(id, tm);
            if (isNaN(val) || (onlybuffer)) {
                valid(id, time_log(id) > now() ? REPORT_NORMAL : REPORT_NEEDREQUEST);}
            else {
                valid(id,  REPORT_DATA);}}}

    bool tagsbase::write_vals_report(size_type id, const dt_val_map& values, ns_error err) {
        if ((reportkey(id) == npos)) return false;
        if (reportbuffers()->insert(reportkey(id), values)) {
            for (dt_val_map::const_iterator it = values.begin(); it != values.end(); ++it) {
                if (!it->first.is_special()) {
                    value_internal<double>(id, it->second);
                    valid(id, REPORT_DATA);
                    error(id, err);
                    return true;}}}
        return false;}

    void tagsbase::write_val_event(size_type id, datetime dt, double vl) {
        if ((exists(id)) && (IN_EVENTSET(type(id)))) {
            time(id, dt);
            insert_evnt_to_journal(id, vl);}}

    void tagsbase::write_val_event(size_type id, const dt_val_pair& val) {
        write_val_event(id, val.first, val.second);}

    void tagsbase::send_command(size_type id, const std::string& val, bool queue , size_type clid) {
        if (exists(id)) {
            switch (type(id)) {
                case TYPE_TEXT:{
                    send_command_str(id, val, queue, clid);
                    return;}
                case TYPE_DISCRET:{
                    bool tmp = false;
                    if (str_to<bool>(val, tmp)) send_command<bool>(id, tmp, queue, clid);
                    return;}
                case TYPE_NUM64:{
                    num64 tmp = 0;
                    if (str_to<num64 > (val, tmp)) send_command<num64 > (id, tmp, queue, clid);
                    return;}
                case TYPE_UNUM64:{
                    unum64 tmp = 0;
                    if (str_to<unum64 > (val, tmp)) send_command<unum64 > (id, tmp, queue, clid);
                    return;}
                case TYPE_NUM32:{
                    num32 tmp = 0;
                    if (str_to<num32 > (val, tmp)) send_command<num32 > (id, tmp, queue, clid);
                    return;}
                case TYPE_UNUM32:{
                    unum32 tmp = 0;
                    if (str_to<unum32 > (val, tmp)) send_command<unum32 > (id, tmp, queue, clid);
                    return;}
                case TYPE_NUM16:{
                    num16 tmp = 0;
                    if (str_to<num16 > (val, tmp)) send_command<num16 > (id, tmp, queue, clid);
                    return;}
                case TYPE_UNUM16:{
                    unum16 tmp = 0;
                    if (str_to<unum16 > (val, tmp)) send_command<unum16 > (id, tmp, queue, clid);
                    return;};
                case TYPE_NUM8:{
                    num8 tmp = 0;
                    if (str_to<num8 > (val, tmp)) send_command<num8 > (id, tmp, queue, clid);
                    return;}
                case TYPE_UNUM8:{
                    unum8 tmp = 0;
                    if (str_to<unum8 > (val, tmp)) send_command<unum8 > (id, tmp, queue, clid);
                    return;}
                case TYPE_DOUBLE:{
                    double tmp = 0;
                    if (str_to<double>(val, tmp)) send_command<double>(id, tmp, queue, clid);
                    return;}
                case TYPE_FLOAT:{
                    float tmp = 0;
                    if (str_to<float>(val, tmp)) send_command<float>(id, tmp, queue, clid);
                    return;}}
            double tmp = 0;
            if (str_to<double>(val, tmp)) send_command<double>(id, tmp, queue, clid);}}

    void tagsbase::send_command(size_type id, const short_value& val , bool queue , size_type clid) {
        if (exists(id)) {
            switch (type(id)) {
                case TYPE_TEXT:{
                    return;}
                case TYPE_DISCRET:{
                    send_command<bool>(id, val.value<bool>(), queue, clid);
                    return;}
                case TYPE_NUM64:{
                    send_command<num64 > (id, val.value<num64 > (), queue, clid);
                    return;}
                case TYPE_UNUM64:{
                    send_command<unum64 > (id, val.value<unum64 > (), queue, clid);
                    return;}
                case TYPE_NUM32:{
                    send_command<num32 > (id, val.value<num32 > (), queue, clid);
                    return;}
                case TYPE_UNUM32:{
                    send_command<unum32 > (id, val.value<unum32 > (), queue, clid);
                    return;}
                case TYPE_NUM16:{
                    send_command<num16 > (id, val.value<num16 > (), queue, clid);
                    return;}
                case TYPE_UNUM16:{
                    send_command<unum16 > (id, val.value<unum16 > (), queue, clid);
                    return;}
                case TYPE_NUM8:{
                    send_command<num8 > (id, val.value<num8 > (), queue, clid);
                    return;}
                case TYPE_UNUM8:{
                    send_command<unum8 > (id, val.value<unum8 > (), queue, clid);
                    return;}
                case TYPE_DOUBLE:{
                    send_command<double>(id, val.value<double>(), queue, clid);
                    return;}
                case TYPE_FLOAT:{
                    send_command<float>(id, val.value<float>(), queue, clid);
                    return;}}
            send_command<double>(id, val.value<double>(), queue, clid);}}
    
    void tagsbase::send_command(const std::string& id, const short_value& val, bool queue, size_type clid){
             size_type ind = operator ()(id);
             if (exists(ind))
                 send_command(ind, val, queue, clid);}

    void tagsbase::kvit(size_type id) {
        if (id == npos) kvitall();
        else {
            if (exists(id)) kvit_tag(id);
            else {
                if ((id & GROUPMASK) && (groups()->exists(id & RESETMASK)))
                    alarms()->kvit_group(id & RESETMASK);
                if ((id & AGROUPMASK) && (agroups()->exists(id & RESETMASK)))
                    alarms()->kvit_agroup(id & RESETMASK);}}}

    void tagsbase::kvit(const std::string& vl) {
        size_type idx = operator ()(vl);
        if (extendexists(idx)) {
            kvit(idx);}}

    void tagsbase::debug(const std::string& mess, debuglvtype lev) {
        debuglvtype clv = (*(ptagsstruct_hdr) data()).debuglevel();
        if (clv >= lev) {
            if (DEBUGLEVEL_LOW < clv) registry()->notify_debug();
            debug()->add(now(), mess, lev, appid_);}}
    
    
    ns_error tagsbase::insert_entity(nodetype enttp , const std::string& newname, const std::string& parentid){
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        insert_tag(newname, parentid);
                        return 0;}

                    case NT_GROUP:{
                        insert_group(newname);
                        return 0;}

                    case NT_AGROUP:{
                        insert_agroup(newname);
                        return 0;}

                    case NT_USER:{
                        insert_user(newname);
                        return 0;}

                    case NT_ACCESSRULE:{
                        insert_accessrule(newname);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}
    
    ns_error tagsbase::insert_entity(nodetype enttp , const std::string& newname, size_type parentid){
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        insert_tag(newname, parentid);
                        return 0;}

                    case NT_GROUP:{
                        insert_group(newname);
                        return 0;}

                    case NT_AGROUP:{
                        insert_agroup(newname);
                        return 0;}

                    case NT_USER:{
                        insert_user(newname);
                        return 0;}

                    case NT_ACCESSRULE:{
                        insert_accessrule(newname);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}
    
    
    
    ns_error tagsbase::replace_entity(nodetype enttp , const std::string& id, const std::string& newname){
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        replace_tag(id, newname);
                        return 0;}

                    case NT_GROUP:{
                        replace_group(id, newname);
                        return 0;}

                    case NT_AGROUP:{
                        replace_agroup(id, newname);
                        return 0;}

                    case NT_USER:{
                        replace_user(id, newname);
                        return 0;}

                    case NT_ACCESSRULE:{
                        replace_accessrule(id, newname);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}
    
    
    ns_error tagsbase::replace_entity(nodetype enttp , size_type id, const std::string& newname){
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        replace_tag(id, newname);
                        return 0;}

                    case NT_GROUP:{
                        replace_group(id, newname);
                        return 0;}

                    case NT_AGROUP:{
                        replace_agroup(id, newname);
                        return 0;}

                    case NT_USER:{
                        replace_user(id, newname);
                        return 0;}

                    case NT_ACCESSRULE:{
                        replace_accessrule(id, newname);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}   
     
    
    
    ns_error tagsbase::delete_entity(nodetype enttp , const std::string& id, const std::string& strcriteria){           
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        delete_tag(id);
                        return 0;}

                    case NT_GROUP:{
                        delete_group(id);
                        return 0;}

                    case NT_AGROUP:{
                        delete_agroup(id);
                        return 0;}

                    case NT_USER:{
                        delete_user(id);
                        return 0;}

                    case NT_ACCESSRULE:{
                        delete_accessrule(id);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}     
    
    
    ns_error tagsbase::delete_entity(nodetype enttp , size_type id, const std::string& strcriteria){           
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        delete_tag(id);
                        return 0;}

                    case NT_GROUP:{
                        delete_group(id);
                        return 0;}

                    case NT_AGROUP:{
                        delete_agroup(id);
                        return 0;}

                    case NT_USER:{
                        delete_user(id);
                        return 0;}

                    case NT_ACCESSRULE:{
                        delete_accessrule(id);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}     
    
    tagsbase::size_type tagsbase::duplicate_group(std::string grp, std::string newname) {
            lower_and_trim(grp);
            lower_and_trim(newname);
            if (!groups()->exists(grp))
                throw dvncierror(ERROR_ENTNOEXIST, grp);
            return duplicate_group( groups()->operator ()(grp), newname);}
    
    tagsbase::size_type tagsbase::duplicate_group(size_type id, std::string newname) {
        lower_and_trim(newname);
        checkname_ex(newname);
        if (!groups()->exists(id))
            throw dvncierror(ERROR_ENTNOEXIST);
        size_type newgroupindx = groups()->add(newname);
        if (newgroupindx == npos) return npos;
        iteminfo_map tagsmap;
        select_tags(tagsmap, id);
        if (tagsmap.empty()) return newgroupindx;
        str_indx_map tagidsmap;
        for (iteminfo_map::const_iterator it = tagsmap.begin(); it != tagsmap.end(); ++it) {
            tagidsmap.insert(str_indx_pair(retremoved_namespace_delimit(it->second.name()), it->first));}
        addtags(tagidsmap, newgroupindx);
        duplicate_tags(tagsmap, groups()->name(newgroupindx));
        groups()->clone(newgroupindx, id);
        return newgroupindx;} 
    
    
    ns_error tagsbase::merge_entity(nodetype enttp , size_type id){           
           try{     
             switch (enttp) {

                    case NT_TAG:
                    case NT_ATAG:{
                        merge_tag(id);
                        return 0;}

                    case NT_GROUP:{
                        merge_group(id);
                        return 0;}

                    case NT_AGROUP:{
                        merge_agroup(id);
                        return 0;}

                    case NT_USER:{
                        merge_user(id);
                        return 0;}

                    case NT_ACCESSRULE:{
                        merge_accessrule(id);
                        return 0;}
                    
                    default:{}}}
           catch(const dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;} 
    

    
    
    ns_error tagsbase::select_entities(nodetype enttp, iteminfo_map& val, size_type parentid, const std::string& strcriteria){
        try{
                val.clear();
                switch (enttp) {

                    case NT_TAG:{
                        select_tags(val, parentid, strcriteria);
                        return 0;}
                    
                    case NT_ATAG:{
                        select_atags(val, parentid, strcriteria);
                        return 0;}

                    case NT_GROUP:{
                        select_groups(val, strcriteria);
                        return 0;}

                    case NT_AGROUP:{
                        select_agroups(val, strcriteria);
                        return 0;}

                    case NT_USER:{
                        select_users(val, strcriteria);
                        return 0;}

                    case NT_ACCESSRULE:{
                        select_accessrules(val, strcriteria);
                        return 0;}
                    
                    default:{}}}
           catch(dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;} 
    
    ns_error tagsbase::select_entities(nodetype enttp, iteminfo_map& val, const std::string& parentid, const std::string& strcriteria){
        try{
                val.clear();
                switch (enttp) {

                    case NT_TAG:{
                        select_tags(val, parentid, strcriteria);
                        return 0;}
                    
                    case NT_ATAG:{
                        select_atags(val, parentid, strcriteria);
                        return 0;}

                    case NT_GROUP:{
                        select_groups(val, strcriteria);
                        return 0;}

                    case NT_AGROUP:{
                        select_agroups(val, strcriteria);
                        return 0;}

                    case NT_USER:{
                        select_users(val, strcriteria);
                        return 0;}

                    case NT_ACCESSRULE:{
                        select_accessrules(val, strcriteria);
                        return 0;}
                    
                    default:{}}}
           catch(dvncierror& err){
               return err.code();}
           catch(...){
               return NS_ERROR_NODEF;}                    
                return NS_ERROR_ENTITY_OPERATE;}     


    void tagsbase::select_tags(iteminfo_map& val, size_type grop, const std::string& strcriteria) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        if (grop == npos) {
            for (size_type i = 0; i < count(); i++) {
                if ((exists(i))) {
                    if ((!filtered_.isEnable()) ||
                            ((filtered_.included(stringed_filterclass::NAME_CRITERIA,    name(i))) &&
                             (filtered_.included(stringed_filterclass::BIND_CRITERIA,    binding(i))) &&
                             (filtered_.included(stringed_filterclass::COMMENT_CRITERIA, comment(i))) &&
                             (filtered_.includedidx(stringed_filterclass::GROUP_CRITERIA, group(i)))
                             )) {
                        val.insert(iteminfo_pair(i, name_with_type(name(i), NT_TAG , type(i), groups()->appid(group(i)))));}}}}
        else {
            indx_set tmpset;
            if (item_indexer->find_by_pos1(groups()->namepos(grop), tmpset)) {
                for (indx_set::const_iterator it = tmpset.begin(); it != tmpset.end(); ++it) {
                    if ((exists(*it))) {
                        if ((!filtered_.isEnable()) ||
                                ((filtered_.included(stringed_filterclass::NAME_CRITERIA,    name(*it))) &&
                                 (filtered_.included(stringed_filterclass::BIND_CRITERIA,    binding(*it))) &&
                                 (filtered_.included(stringed_filterclass::COMMENT_CRITERIA, comment(*it))) &&
                                 (filtered_.includedidx(stringed_filterclass::GROUP_CRITERIA, group(*it)))
                                 )) {
                            val.insert(iteminfo_pair(*it, name_with_type(name(*it), NT_TAG , type(*it), groups()->appid(group(*it)))));}}}}}}

    void tagsbase::select_tags(iteminfo_map& val, string group, const std::string& strcriteria) {
        if (!groups()->exists(group)) {
            val.clear();
            return;}
        select_tags(val, groups()->operator ()(group), strcriteria);}

    void tagsbase::select_tags(iteminfo_map& val, indx_set& set_, const std::string& strcriteria ) {
        val.clear();
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            if (exists(*it))  {
                val.insert(iteminfo_pair(*it, name_with_type(name(*it), NT_TAG, type(*it), groups()->appid(group(*it)))));}
            it++;}}

    void tagsbase::select_atags(iteminfo_map& val, size_type agrop, const std::string& strcriteria) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        for (size_type i = 0; i < count(); i++) {
            if ((exists(i) && (agroup(i) == agrop))  || (agrop == npos)) {
                if ((!filtered_.isEnable()) || (filtered_.included("name", (*this).name(i)))) {
                    val.insert(iteminfo_pair(i, name_with_type(name(i), NT_ATAG, type(i))));};}}}

    void tagsbase::select_atags(iteminfo_map& val, string agroup, const std::string& strcriteria) {
        if (!agroups()->exists(agroup)) {
            val.clear();
            return;}
        select_atags(val, agroups()->operator ()(agroup), strcriteria);}

    void tagsbase::select_tags_by_appid(indx_set& val, appidtype appid, bool onlyactive) {
        val.clear();
        size_type indxtmp = groups()->select_groups_by_appid(appid);
        if (indxtmp != npos) {
            iteminfo_map tmp;
            select_tags(tmp, indxtmp);
            for (iteminfo_map::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
                if ((exists(it->first)) && (refcnt(it->first)))
                    val.insert(it->first);}}}

    void tagsbase::select_tags_by_groupid(indx_set& val, size_type group, bool onlyactive) {
        val.clear();
        if (group != npos) {
            iteminfo_map tmp;
            select_tags(tmp, group);
            for (iteminfo_map::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
                if ((exists(it->first)) && (refcnt(it->first))) 
                    val.insert(it->first);}}}

    void tagsbase::select_tags_by_link(indx_set& val, appidtype app, const metalink& lnk, bool onlyactive) {
        val.clear();
        if (lnk) {
            for (size_type i = 0; i < groups()->count(); i++) {
                if ((groups()->exists(i)) && (groups()->appid(i) == app) && (groups()->link(i) == lnk)) {
                    indx_set tmpst;
                    tmpst.clear();
                    select_tags_by_groupid(tmpst, i, onlyactive);
                    if (!tmpst.empty())
                        val.insert(tmpst.begin(), tmpst.end());}}}}

    void tagsbase::select_tags_report(indx_set& val) {
        val.clear();
        for (size_type i = 0; i < count(); i++) {
            if ((exists(i)) && (IN_REPORTSET(type(i))))
                val.insert(i);}}

    void tagsbase::select_groups_by_appid(appidtype appid,  indx_set& val) {
        val.clear();
        for (size_type i = 0; i < groups()->count(); i++) {
            if (groups()->exists(i))
                if (groups()->appid(i) == appid) val.insert(i);}}

    void tagsbase::select_metalinks_set_by_appid(appidtype appid, metalink_set& val) {
        val.clear();
        for (size_type i = 0; i < groups()->count(); i++) {
            if (groups()->exists(i))
                if (groups()->appid(i) == appid) val.insert(groups()->link(i));}}

    void tagsbase::select_metalinks_vect_by_metalink(const metalink& lnk, metalink_vect& val, devnum_set& utilset) {
        val.clear();
        utilset.clear();
        for (size_type i = 0; i < groups()->count(); i++) {
            if (groups()->exists(i))
                if (groups()->link(i) == lnk) {
                    if (groups()->utiloperation(i))
                        utilset.insert(groups()->devnum(i));
                    val.push_back(groups()->link(i));}}}

    void tagsbase::select_groups_by_metalink(const metalink& lnk, appidtype app, indx_set& val) {
        val.clear();
        for (size_type i = 0; i < groups()->count(); i++) {
            if ((groups()->exists(i)) && (groups()->appid(i) == app))
                if (groups()->link(i) == lnk) {
                    val.insert(i);}}}
    
    
    void tagsbase::select_groups(iteminfo_map& val, const std::string& strcriteria ) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        for (size_type i = 0; (i < (*groups()).count()); i++)
            if (groups()->exists(i)) {
                if ((!filtered_.isEnable()) ||
                        (filtered_.included(stringed_filterclass::NAME_CRITERIA, groups()->name(i)))) {
                    val.insert(iteminfo_pair(i, name_with_type(groups()->name(i), NT_GROUP,
                            static_cast<tagtype> (groups()->appid(i)))));};}}

    void tagsbase::select_groups(iteminfo_map& val, indx_set& set_, const std::string& strcriteria) {
        val.clear();
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            pgroupstruct tmp = groups()->operator [](*it);
            if ((tmp) && ((groups()->exists(*it)))) {
                val.insert(iteminfo_pair(*it, name_with_type(groups()->name(*it), NT_GROUP,
                        static_cast<tagtype> (groups()->appid(*it)))));}
            it++;}}

    void tagsbase::select_agroups(iteminfo_map& val, const std::string& strcriteria) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        for (size_type i = 0; (i < (*agroups()).count()); i++)
            if (agroups()->exists(i)) {
                if ((!filtered_.isEnable()) ||
                        (filtered_.included(stringed_filterclass::NAME_CRITERIA, agroups()->name(i)))) {
                    val.insert(iteminfo_pair(i, name_with_type(agroups()->name(i), NT_AGROUP)));}}}

    void tagsbase::select_agroups(iteminfo_map& val, indx_set& set_, const std::string& strcriteria) {
        val.clear();
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            if (agroups()->exists(*it)) {
                val.insert(iteminfo_pair(*it, name_with_type(agroups()->name(*it), NT_AGROUP)));}
            it++;}}

    void tagsbase::select_users(iteminfo_map& val, const std::string& strcriteria) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        for (size_type i = 0; (i < (*users()).count()); i++)
            if (users()->exists(i)) {
                if ((!filtered_.isEnable()) ||
                        (filtered_.included(stringed_filterclass::NAME_CRITERIA, users()->name(i)))) {
                    val.insert(iteminfo_pair(i, name_with_type(users()->name(i), NT_USER)));};}}

    void tagsbase::select_users(iteminfo_map& val, indx_set& set_, const std::string& strcriteria) {
        val.clear();
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            if (users()->exists(*it)) {
                val.insert(iteminfo_pair(*it, name_with_type(users()->name(*it), NT_USER)));}
            it++;}}

    void tagsbase::select_accessrules(iteminfo_map& val, const std::string& strcriteria) {
        val.clear();
        stringed_filterclass filtered_(strcriteria);
        for (size_type i = 0; (i < (*accessrules()).count()); i++)
            if (accessrules()->exists(i)) {
                if ((!filtered_.isEnable()) ||
                        (filtered_.included(stringed_filterclass::NAME_CRITERIA, accessrules()->name(i)))) {
                    val.insert(iteminfo_pair(i, name_with_type(accessrules()->name(i), NT_ACCESSRULE)));};}}

    void tagsbase::select_accessrules(iteminfo_map& val, indx_set& set_, const std::string& strcriteria) {
        val.clear();
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            if (accessrules()->exists(*it)) {
                val.insert(iteminfo_pair(*it, name_with_type(accessrules()->name(*it), NT_ACCESSRULE)));}
            it++;}}    
    

    bool tagsbase::select_reportvals_by_time(const datetime& tm, indx_double_map& vlmap) const {
        dt_val_pair vl;
        for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); ++it) {
            if (!select_reportval_by_time(it->first, tm, vl)) {
                return false;}
            else {
                it->second = vl.second;}}
        return true;}
    

    void tagsbase::texttagcnt(size_t val) {
        if ((val + 1) == 0) return;
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).texttagcnt(val);
        writeheader();}

    void tagsbase::archtagcnt(size_t val) {
        if ((val + 1) == 0) return;
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).archtagcnt(val);
        writeheader();}

    void tagsbase::reporttagcnt(size_t val) {
        if ((val + 1) == 0) return;
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).reporttagcnt(val);
        writeheader();}

    void tagsbase::prjcfg_debuglevel(debuglvtype val) {
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).debuglevel(val);
        writeheader();}

    void tagsbase::prjcfg_dbprovider(dbprovtype val) {
        INP_EXCLUSIVE_LOCK(memlock())
        if ((*(ptagsstruct_hdr) data()).dbprovider() != val) {
            (*(ptagsstruct_hdr) data()).dbprovider(val);
            writeheader();
            registry()->notify_dbmanage(MSG_DVNCICONNSTRCH);}}

    void tagsbase::prjcfg_analogbuf(bool val) {
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).analogbuf(val);
        writeheader();}

    void tagsbase::prjcfg_bddepth(num32 val) {
        INP_EXCLUSIVE_LOCK(memlock())
                (*(ptagsstruct_hdr) data()).bddepth(val);
        writeheader();}

    void tagsbase::prjcfg_name(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posname();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posname(tmp);
            writeheader();}}

    void tagsbase::prjcfg_comment(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).poscomment();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).poscomment(tmp);
            writeheader();}}

    void tagsbase::prjcfg_dbstring(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posdbstring();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posdbstring(tmp);
            writeheader();
            registry()->notify_dbmanage(MSG_DVNCICONNSTRCH);}}

    void tagsbase::prjcfg_admin(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posadmin();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posadmin(tmp);
            writeheader();}}

    void tagsbase::prjcfg_password(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).pospass();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).pospass(tmp);
            writeheader();}}

    void tagsbase::prjcfg_adminport(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posadminport();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posadminport(tmp);
            writeheader();}}

    void tagsbase::prjcfg_remoteport(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posremoteport();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posremoteport(tmp);
            writeheader();}}

    void tagsbase::prjcfg_opcport(const std::string& value) {
        INP_EXCLUSIVE_LOCK(memlock())
        size_t tmp = (*(ptagsstruct_hdr) data()).posopcport();
        if (stringbase_src(tmp) != value) {
            stringbase_src(tmp, value);
            (*(ptagsstruct_hdr) data()).posopcport(tmp);
            writeheader();}}

    void tagsbase::inputsysvartag(size_type id, bool include) {
        if (exists(id)) {
            if (include) {
                operator[](id)->valid(FULL_VALID);
                if (IN_TEXTSET(type(id)))
                    valuestringreplace(id, true);
                writetofile(id);}
            else {
                operator[](id)->valid(NULL_VALID);
                if (IN_TEXTSET(type(id)))
                    valuestringreplace(id, false);
                writetofile(id);}}}

    void tagsbase::inputsysvargroups(size_type group, bool include) {
        if (groups()->exists(group)) {
            iteminfo_map tmp;
            select_tags(tmp, group);
            for (iteminfo_map::iterator it = tmp.begin(); it != tmp.end(); ++it) {
                inputsysvartag(it->first, include);}}}

    void tagsbase::offgroup(size_type group, ns_error err) {
        if (groups()->exists(group)) {
            iteminfo_map tmp;
            select_tags(tmp, group);
            for (iteminfo_map::iterator it = tmp.begin(); it != tmp.end(); ++it) {
                offtag(it->first, err);}}}
    
    void tagsbase::offtag(size_type id, ns_error err){
            if ((exists(id))/*  && (IN_SMPLSET(type(id)))*/){
                valid(id, 0);
                switch (alarmcase(id)) {
                case alarmEqual:{
                    if (alarmconst_prtd<num64 >(id) == 0) {
                        value_internal<num64 > (id, 1);} else {
                        value_internal<num64 > (id, 0);}
                    break;}
                default:{
                    value_internal<num64 > (id, alarmconst_prtd<num64 > (id));
                    break;}}
                    value_log<num64>(id, 0);
                    error(id, err);
                    time(id, nill_time);
                    time_log(id, nill_time);}}

    void tagsbase::rangable(size_type id, bool value) {
        if (exists(id)) {
            if (value != rangable(id)) {
                if (value) {
                    switch (type(id)) {
                        case TYPE_NODEF:{
                            operator[](id)->minraw<double>(0);
                            operator[](id)->maxraw<double>(100);
                            break;}
                        case TYPE_DOUBLE:{
                            operator[](id)->minraw<double>(-std::numeric_limits<double>::max());
                            operator[](id)->maxraw<double>(std::numeric_limits<double>::max());
                            break;}
                        case TYPE_FLOAT:{
                            operator[](id)->minraw<float>(-std::numeric_limits<float>::max());
                            operator[](id)->maxraw<float>(std::numeric_limits<float>::max());
                            break;}
                        case TYPE_DISCRET:{
                            operator[](id)->minraw<bool>(false);
                            operator[](id)->maxraw<bool>(true);
                            break;}
                        case TYPE_NUM64:{
                            operator[](id)->minraw<num64 > (std::numeric_limits<num64>::min());
                            operator[](id)->maxraw<num64 > (std::numeric_limits<num64>::max());
                            break;}
                        case TYPE_UNUM64:{
                            operator[](id)->minraw<unum64 > (std::numeric_limits<unum64>::min());
                            operator[](id)->maxraw<unum64 > (std::numeric_limits<unum64>::max());
                            break;}
                        case TYPE_NUM32:{
                            operator[](id)->minraw<num32 > (std::numeric_limits<num32>::min());
                            operator[](id)->maxraw<num32 > (std::numeric_limits<num32>::max());
                            break;}
                        case TYPE_UNUM32:{
                            operator[](id)->minraw<unum32 > (std::numeric_limits<unum32>::min());
                            operator[](id)->maxraw<unum32 > (std::numeric_limits<unum32>::max());
                            break;}
                        case TYPE_NUM16:{
                            operator[](id)->minraw<num16 > (std::numeric_limits<num16>::min());
                            operator[](id)->maxraw<num16 > (std::numeric_limits<num16>::max());
                            break;}
                        case TYPE_UNUM16:{
                            operator[](id)->minraw<unum16 > (std::numeric_limits<unum16>::min());
                            operator[](id)->maxraw<unum16 > (std::numeric_limits<unum16>::max());
                            break;}
                        case TYPE_NUM8:{
                            operator[](id)->minraw<num8 > (std::numeric_limits<num8>::min());
                            operator[](id)->maxraw<num8 > (std::numeric_limits<num8>::max());
                            break;}
                        case TYPE_UNUM8:{
                            operator[](id)->minraw<unum8 > (std::numeric_limits<unum8>::min());
                            operator[](id)->maxraw<unum8 > (std::numeric_limits<unum8>::max());
                            break;}}}
                else {
                    operator[](id)->minraw<num64 > (0);
                    operator[](id)->maxraw<num64 > (0);}}}}




    void tagsbase::duplicate_tags(const iteminfo_map& maptmpl, const std::string& grpnm) {
        for (iteminfo_map::const_iterator it = maptmpl.begin(); it != maptmpl.end(); ++it) {
            std::string tmpnm = grpnm + NEMESPACEDELIMIT + retremoved_namespace_delimit(it->second.name());
            size_type tmpindx = operator ()(tmpnm);
            if ((it->first != npos) && (tmpindx != npos)) {
                clone(tmpindx, it->first);}}}

    size_t tagsbase::group_childcount( size_type id) {
        if (!groups()->exists(id)) return 0;
        iteminfo_map tmp;
        select_tags(tmp, id);
        return tmp.size();}

    void tagsbase::clone(size_type idsrc, size_type iddst) {
        if ((!exists(idsrc)) || (!exists(iddst))) return;
        binding(idsrc, binding(iddst), false);
        comment(idsrc, comment(iddst));
        eu(idsrc, eu(iddst));
        onmsg(idsrc, onmsg(iddst));
        offmsg(idsrc, offmsg(iddst));
        alarmmsg(idsrc, alarmmsg(iddst));
        tagstruct::clone(((ptagsstruct) data())->items[idsrc],
                ((ptagsstruct) data())->items[iddst]);
        if (IN_REPORTSET(type(idsrc))) {
            notify_tagmanage(MSG_DVNCITAGREPORT, idsrc, 1);
            add_reportkey(idsrc);}
        if  (logged(idsrc)) {
            add_logkey(idsrc);
            registry()->notify_log(idsrc, true);}
        writetofile(idsrc);}



    void tagsbase::to_standart_range(size_type id) {
        if (exists(id)) {
            switch (type(id)) {
                case TYPE_NODEF:{
                    operator[](id)->minraw<double>(0);
                    operator[](id)->maxraw<double>(0);
                    operator[](id)->mineu<double>(0);
                    operator[](id)->maxeu<double>(100);
                    operator[](id)->alarmconst<double>(0);
                    break;}
                case TYPE_DOUBLE:{
                    operator[](id)->minraw<double>(0);
                    operator[](id)->maxraw<double>(0);
                    operator[](id)->mineu<double>(-std::numeric_limits<double>::max());
                    operator[](id)->maxeu<double>(std::numeric_limits<double>::max());
                    operator[](id)->alarmconst<double>(0);
                    break;}
                case TYPE_DISCRET:{
                    operator[](id)->minraw<bool>(0);
                    operator[](id)->minraw<bool>(0);
                    operator[](id)->mineu<bool>(0);
                    operator[](id)->maxeu<bool>(1);
                    operator[](id)->alarmconst<bool>(0);
                    break;}
                case TYPE_NUM64:{
                    operator[](id)->minraw<num64 > (0);
                    operator[](id)->minraw<num64 > (0);
                    operator[](id)->mineu<num64 > (std::numeric_limits<num64>::min());
                    operator[](id)->maxeu<num64 > (std::numeric_limits<num64>::max());
                    operator[](id)->alarmconst<num64 > (0);
                    break;}
                case TYPE_UNUM64:{
                    operator[](id)->minraw<unum64 > (0);
                    operator[](id)->maxraw<unum64 > (0);
                    operator[](id)->mineu<unum64 > (std::numeric_limits<unum64>::min());
                    operator[](id)->maxeu<unum64 > (std::numeric_limits<unum64>::max());
                    operator[](id)->alarmconst<unum64 > (0);
                    break;}
                case TYPE_NUM32:{
                    operator[](id)->minraw<num32 > (0);
                    operator[](id)->maxraw<num32 > (0);
                    operator[](id)->mineu<num32 > (std::numeric_limits<num32>::min());
                    operator[](id)->maxeu<num32 > (std::numeric_limits<num32>::max());
                    operator[](id)->alarmconst<num32 > (0);
                    break;}
                case TYPE_UNUM32:{
                    operator[](id)->minraw<unum32 > (0);
                    operator[](id)->maxraw<unum32 > (0);
                    operator[](id)->mineu<unum32 > (std::numeric_limits<unum32>::min());
                    operator[](id)->maxeu<unum32 > (std::numeric_limits<unum32>::max());
                    operator[](id)->alarmconst<unum32 > (0);
                    break;}
                case TYPE_NUM16:{
                    operator[](id)->minraw<num16 > (0);
                    operator[](id)->maxraw<num16 > (0);
                    operator[](id)->mineu<num16 > (std::numeric_limits<num16>::min());
                    operator[](id)->maxeu<num16 > (std::numeric_limits<num16>::max());
                    operator[](id)->alarmconst<num16 > (0);
                    break;}
                case TYPE_UNUM16:{
                    operator[](id)->minraw<unum16 > (0);
                    operator[](id)->maxraw<unum16 > (0);
                    operator[](id)->mineu<unum16 > (std::numeric_limits<unum16>::min());
                    operator[](id)->maxeu<unum16 > (std::numeric_limits<unum16>::max());
                    operator[](id)->alarmconst<unum16 > (0);
                    break;}
                case TYPE_NUM8:{
                    operator[](id)->minraw<num8 > (0);
                    operator[](id)->maxraw<num8 > (0);
                    operator[](id)->mineu<num8 > (std::numeric_limits<num8>::min());
                    operator[](id)->maxeu<num8 > (std::numeric_limits<num8>::max());
                    operator[](id)->alarmconst<num8 > (0);
                    break;}
                case TYPE_UNUM8:{
                    operator[](id)->minraw<unum8 > (0);
                    operator[](id)->maxraw<unum8 > (0);
                    operator[](id)->mineu<unum8 > (std::numeric_limits<unum8>::min());
                    operator[](id)->maxeu<unum8 > (std::numeric_limits<unum8>::max());
                    operator[](id)->alarmconst<unum8 > (0);
                    break;}
                case TYPE_FLOAT:{
                    operator[](id)->minraw<float>(0);
                    operator[](id)->maxraw<float>(0);
                    operator[](id)->mineu<float>(-std::numeric_limits<float>::max());
                    operator[](id)->maxeu<float>(std::numeric_limits<float>::max());
                    operator[](id)->alarmconst<float>(0);
                    break;}
                default:{
                    operator[](id)->minraw<num64 > (0);
                    operator[](id)->maxraw<num64 > (0);
                    operator[](id)->mineu<num64 > (std::numeric_limits<num64>::min());
                    operator[](id)->maxeu<num64 > (std::numeric_limits<num64>::max());
                    operator[](id)->alarmconst<num64 > (0);
                    return;}}}}

    void tagsbase::buildindex() {
        size_type frinx = npos;
        item_indexer->clear_index();
        item_indexer->start_inserter();
        for (size_type i = 0; i < count(); i++) {
            if (exists(i)) {
                item_indexer->proccess_inserter(i, namepos(i), optinal_pos(i));}
            else {
                if (frinx == npos) frinx = i;}}
        for (size_type i = 0; i < groups()->count(); i++) {
            if (groups()->exists(i)) {
                item_indexer->proccess_inserter(GROUPMASK | i, groups()->namepos(i), 0);}}
        for (size_type i = 0; i < agroups()->count(); i++) {
            if (agroups()->exists(i)) {
                item_indexer->proccess_inserter(AGROUPMASK | i, agroups()->namepos(i), 0);}}
        item_indexer->stop_inserter();
        item_indexer->freeindex((frinx == npos) ? count() : frinx);}

    bool tagsbase::extendexists(size_type id) const {
        if (id == npos) return false;
        if (id < count() && (id != npos)) return exists(id);
        if (id & GROUPMASK) return groups()->exists(id & RESETMASK);
        if (id & AGROUPMASK) return agroups()->exists(id & RESETMASK);
        return false;}

    void tagsbase::addindex(size_type id) {
        bool exsts = exists(id);
        if ((exsts) || (extendexists(id))) {
            INP_EXCLUSIVE_LOCK(item_indexer->memlock())
            item_indexer->insert(id, namepos(id), optinal_pos(id));
            if (exsts) findfreeindex(id);}}

    void tagsbase::removeindex(size_type id) {
        bool exsts = exists(id);
        if ((exsts) || (extendexists(id))) {
            INP_EXCLUSIVE_LOCK(item_indexer->memlock())
            item_indexer->erase(id, namepos(id), optinal_pos(id));
            if ((exsts) && (item_indexer->freeindex() > id))
                item_indexer->freeindex(id);}}

    size_t tagsbase::optinal_pos(size_type id) {
        return ((exists(id)) && (groups()->exists(group(id)))) ?
                groups()->namepos(group(id)) : 0;}

    void tagsbase::fill_logkeys() {
        if (!valbuffers()) return;
        for (size_type i = 0; i < count(); i++) {
            add_logkey(i);}}

    tagsbase::size_type tagsbase::add_logkey(size_type id) {
        size_type tmp = npos;
        if ((valbuffers()) && logged(id) && (IN_NUMBERSET(type(id)))) {
            switch (type(id)) {
                case TYPE_NODEF:{
                    tmp = valbuffers()->regist<double>(mineu_prtd<double>(id), maxeu_prtd<double>(id));
                    break;}
                case TYPE_DOUBLE:{
                    tmp = valbuffers()->regist<double>(mineu_prtd<double>(id), maxeu_prtd<double>(id));
                    break;}
                case TYPE_DISCRET:{
                    tmp = valbuffers()->regist<bool>(0, 1);
                    break;}
                case TYPE_NUM64:{
                    tmp = valbuffers()->regist<num64 > (mineu_prtd<num64 > (id), maxeu_prtd<num64 > (id));
                    break;}
                case TYPE_UNUM64:{
                    tmp = valbuffers()->regist<unum64 > (mineu_prtd<unum64 > (id), maxeu_prtd<unum64 > (id));
                    break;}
                case TYPE_NUM32:{
                    tmp = valbuffers()->regist<num32 > (mineu_prtd<num32 > (id), maxeu_prtd<num32 > (id));
                    break;}
                case TYPE_UNUM32:{
                    tmp = valbuffers()->regist<unum32 > (mineu_prtd<unum32 > (id), maxeu_prtd<unum32 > (id));
                    break;}
                case TYPE_NUM16:{
                    tmp = valbuffers()->regist<num16 > (mineu_prtd<num16 > (id), maxeu_prtd<num16 > (id));
                    break;}
                case TYPE_UNUM16:{
                    tmp = valbuffers()->regist<unum16 > (mineu_prtd<unum16 > (id), maxeu_prtd<unum16 > (id));
                    break;}
                case TYPE_NUM8:{
                    tmp = valbuffers()->regist<num8 > (mineu_prtd<num8 > (id), maxeu_prtd<num8 > (id));
                    break;}
                case TYPE_UNUM8:{
                    tmp = valbuffers()->regist<unum8 > (mineu_prtd<unum8 > (id), maxeu_prtd<unum8 > (id));
                    break;}
                case TYPE_FLOAT:{
                    tmp = valbuffers()->regist<float>(mineu_prtd<float>(id), maxeu_prtd<float>(id));
                    break;}}
            if (tmp != npos) logkey(id, tmp);}
        return tmp;}

    tagsbase::size_type tagsbase::remove_logkey(size_type id) {
        if (valbuffers()) {
            if (logkey(id) != npos)
                valbuffers()->unregist(logkey(id));
            logkey(id, npos);}
        return npos;}

    void tagsbase::fill_reportkeys() {
        if (!reportbuffers()) return;
        for (size_type i = 0; i < count(); i++) {
            add_reportkey(i);}}

    tagsbase::size_type tagsbase::add_reportkey(size_type id) {
        size_type tmp = npos;
        if ((reportbuffers()) && IN_REPORTSET(type(id))) {
            tmp = reportbuffers()->regist();
            if (tmp != npos) reportkey(id, tmp);}
        return tmp;}

    tagsbase::size_type tagsbase::remove_reportkey(size_type id) {
        if (reportbuffers()) {
            if (reportkey(id) != npos)
                reportbuffers()->unregist(reportkey(id));
            reportkey(id, npos);}
        return npos;}

    bool tagsbase::restore_command_raw_range(commandstruct& cmd) {
        size_type id = cmd.tagid();
        if ((exists(id)) && (IN_COMMADSET(type(id)))) {
            switch (cmd.type()) {
                case TYPE_NODEF:{
                    double tmp = cmd.value_set<double>();
                    restore_raw_range<double>(id, tmp);
                    cmd.value_set<double>(tmp);
                    return true;}
                case TYPE_DISCRET:{
                    bool tmp = cmd.value_set<bool>();
                    restore_raw_range<bool>(id, tmp);
                    cmd.value_set<bool>(tmp);
                    return true;}
                case TYPE_NUM64:{
                    num64 tmp = cmd.value_set<num64 > ();
                    restore_raw_range<num64 > (id, tmp);
                    cmd.value_set<num64 > (tmp);
                    return true;}
                case TYPE_UNUM64:{
                    unum64 tmp = cmd.value_set<unum64 > ();
                    restore_raw_range<unum64 > (id, tmp);
                    cmd.value_set<unum64 > (tmp);
                    return true;}
                case TYPE_NUM32:{
                    num32 tmp = cmd.value_set<num32 > ();
                    restore_raw_range<num32 > (id, tmp);
                    cmd.value_set<num32 > (tmp);
                    return true;}
                case TYPE_UNUM32:{
                    unum32 tmp = cmd.value_set<unum32 > ();
                    restore_raw_range<unum32 > (id, tmp);
                    cmd.value_set<unum32 > (tmp);
                    return true;}
                case TYPE_NUM16:{
                    num16 tmp = cmd.value_set<num16 > ();
                    restore_raw_range<num16 > (id, tmp);
                    cmd.value_set<num16 > (tmp);
                    return true;}
                case TYPE_UNUM16:{
                    unum16 tmp = cmd.value_set<unum16 > ();
                    restore_raw_range<unum16 > (id, tmp);
                    cmd.value_set<unum16 > (tmp);
                    return true;}
                case TYPE_NUM8:{
                    num8 tmp = cmd.value_set<num8 > ();
                    restore_raw_range<num8 > (id, tmp);
                    cmd.value_set<num8 > (tmp);
                    return true;}
                case TYPE_UNUM8:{
                    unum8 tmp = cmd.value_set<unum8 > ();
                    restore_raw_range<unum8 > (id, tmp);
                    cmd.value_set<unum8 > (tmp);
                    return true;}
                case TYPE_DOUBLE:{
                    double tmp = cmd.value_set<double>();
                    restore_raw_range<double>(id, tmp);
                    cmd.value_set<double>(tmp);
                    return true;}
                case TYPE_FLOAT:{
                    float tmp = cmd.value_set<float>();
                    restore_raw_range<float>(id, tmp);
                    cmd.value_set<float>(tmp);
                    return true;}
                default: return true;}}
        return false;}

    void tagsbase::send_command_str(size_type id, const std::string& val, bool queue , size_type clid) {
        if (IN_TEXTSET(type(id))) {
            if ((groups()->exists(group(id)))) {
                switch (groups()->appid(group(id))) {
                    case NS_GROUP_SYSTEM:
                    case NS_GROUP_SYSTEMVAR:{
                        valid(id, FULL_VALID);
                        write_val (id, val);
                        break;}
                    case NS_GROUP_SYSTEMREPORT:
                    case NS_GROUP_SYSTEMREPORTCOUNT:
                    case NS_GROUP_SYSTEMCOUNT:{
                        break;}
                    default:{
                        commands()->add(id, val, queue, clid);}}
                journal()->add(now(), id, msCmd, 0);}}}

    bool tagsbase::checkname(const string& val, size_type parnt)  {
        std::string fullnamed = groups()->name(parnt) + NEMESPACEDELIMIT + val;
        if (((operator [](fullnamed))) || (groups()->operator [](val)) || (agroups()->operator [](val)))
            throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, operator ()(val));
        boost::regex xtagTemplete(CORRECT_ENTETYNAME_REGEXTAMPL);
        if (!boost::regex_match( val, xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        boost::regex ex_xtagTemplete(EXCL_CORRECT_ENTETYNAME_REGEXTAMPL);
        if (boost::regex_match( val, ex_xtagTemplete)) throw dvncierror(ERROR_NAMEENTETY_CORRECT, val, 0);
        return true;}

    bool tagsbase::checkname_ex(const std::string& val) {
        if (item_indexer->find(val, false) != npos) throw dvncierror(ERROR_NAMEENTETY_DUBLICATE, val, 0);
        return true;}

    void tagsbase::trigger_add(size_type id, size_type opt) {
        notify_tagmanage(MSG_DVNCTAGNEW, id, static_cast<size_type> (opt));
        if (refcnt(id)) 
            notify_tagmanage(MSG_DVNCTAGADDTOGR, id, static_cast<size_type> (opt));};

    void tagsbase::trigger_remove(size_type id, size_type opt) {
        if (logbuffered(id)) {
            if (archtagcnt()) {
                archtagcnt(archtagcnt() - 1);}
            remove_logkey(id);}
        if (reportbuffered(id)) {
            if (reporttagcnt()) {
                reporttagcnt(reporttagcnt() - 1);}
            remove_reportkey(id);}
        if (IN_TEXTSET(type(id))) {
            texttagcnt(texttagcnt() - 1);
            valuestringremove(id);}
        notify_tagmanage(MSG_DVNCITAGREPORT, id, 0);
        notify_tagmanage(MSG_DVNCTAGDELFROMGR, id, opt);
        notify_tagmanage(MSG_DVNCTAGDELETE, id, opt);};
        

    void tagsbase::trigger_rename(size_type id) {
        notify_tagmanage(MSG_DVNCTAGREPNAME, id, group(id));}
    

    void tagsbase::trigger_bind(size_type id) {
        if ((refcnt(id))){
        notify_tagmanage(MSG_DVNCTAGDELFROMGR, id, group(id));
        notify_tagmanage(MSG_DVNCTAGADDTOGR, id, group(id));}}
    

    void tagsbase::trigger_group_rename(size_type id) {
        iteminfo_map mapgr;
        select_tags(mapgr , id);
        if (!mapgr.empty()) {
            for (iteminfo_map::const_iterator it = mapgr.begin(); it != mapgr.end(); ++it)
                trigger_rename(it->first);}}
    

    void tagsbase::trigger_util(size_type id, const tagstruct& oldst, const tagstruct& newst) {
        if (newst.id() != npos) {
            bool change = false;

            if (oldst.logged() != newst.logged()) {
                trigger_trendlog(id, newst.logdb());}
            if (newst.type() != oldst.type()) {
                change = true;
                if (IN_REPORTSET(oldst.type()) || IN_REPORTSET(newst.type())) {
                    trigger_report(id , oldst.type(), newst.type());}
                if (IN_TEXTSET(oldst.type()) || IN_TEXTSET(oldst.type())) {
                    trigger_texttype(id , IN_TEXTSET(newst.type()));}}
            if (newst.allwaysactiv_helper()!=oldst.allwaysactiv_helper()){
                if ((newst.allwaysactiv_helper()) && (refcnt(id)==1))
                    trigger_ref(id,true);
                if ((!newst.allwaysactiv_helper()) && (!refcnt(id)))
                    trigger_ref(id,false);}
            if (IN_RANGESET(newst.type()) && (((oldst.mineu64() != newst.mineu64())
                                               || (oldst.maxeu64() != newst.maxeu64())) || (oldst.type() != newst.type()))) {
                trigger_range(id, newst.rangable());}
            
            if ((IN_NUMBERSET(newst.type())) && (IN_NUMBERSET(oldst.type()))){
                if (newst.devdb()!=oldst.devdb())
                    change=true;}

            if (change && (refcnt(id))) {
                notify_tagmanage(MSG_DVNCTAGDELFROMGR, id, group(id));
                notify_tagmanage(MSG_DVNCTAGADDTOGR, id, group(id));}}};
                

    void tagsbase::trigger_trendlog(size_type id, bool state) {
        if (state) {
            archtagcnt(archtagcnt() + 1);
            add_logkey(id);
            registry()->notify_log(id, true);}
        else {
            archtagcnt( archtagcnt() ? archtagcnt() - 1 : archtagcnt());
            remove_logkey(id);
            registry()->notify_log(id, false);}};

    void tagsbase::trigger_report(size_type id, tagtype oldtype, tagtype newtype) {
        if (oldtype == newtype) return;
        if (IN_REPORTSET(newtype)) {
            if (IN_REPORTSET(oldtype)) {
                reset_reportkey(id);}
            else {
                reporttagcnt(reporttagcnt() + 1);
                add_reportkey(id);}}
        else {
            if (reporttagcnt())
                reporttagcnt(reporttagcnt() - 1);
            remove_reportkey(id);}};

    void tagsbase::trigger_texttype(size_type id, bool state) {
        if (!state)
            valuestringremove(id);
        else
            operator[](id)->value<size_t > (0);

        texttagcnt( state ? texttagcnt() + 1 : (texttagcnt() ? texttagcnt() - 1 : 0));}

    void tagsbase::trigger_range(size_type id, bool state) {
        if (logkey(id) != npos) {
            valbuffers()->range( logkey(id), mineu_prtd<double>(id), maxeu_prtd<double>(id));}};
            
    void tagsbase::trigger_ref(size_type id, bool state) {
        if (state) {
            registry()->notify_newref(id, group(id));}
        else{
            registry()->notify_remref(id, group(id));}};            

    void tagsbase::trigger_systemtype(size_type id, bool state) {};

    void tagsbase::changepos1(size_t oldpos1, size_t newpos1) {
        INP_EXCLUSIVE_LOCK(item_indexer->memlock());
        buildindex();}
    
    

    void tagsbase::initstruct(size_type id, const std::string& newname, size_type parent) {

        new ( &((ptagsstruct) data())->items[id] ) tagstruct(able_ptr , parent);
        name(id, newname, false);
        comment(id, "");
        binding(id, "", false);
        onmsg(id, "");
        offmsg(id, "");
        alarmmsg(id, "");
        eu(id, "");
        writetofile(id);}

    void tagsbase::uninitstruct(size_type id) {

        comment(id, "");
        binding(id, "", false);
        onmsg(id, "");
        offmsg(id, "");
        alarmmsg(id, "");
        eu(id, "");
        templatebase<tagsstruct>::uninitstruct(id);}

    void tagsbase::reghandle(appidtype app, eventtypeset evts) {
        handle_ = registry()->reghandle(app, evts);}

    void tagsbase::unreghandle() {
        if (handle_ ) registry()->unreghandle(handle_);
        handle_ = 0;}

    void tagsbase::addtags(str_indx_map& newnames, size_type groupid) {
        for (str_indx_map::iterator it = newnames.begin(); it != newnames.end(); ++it) {
            it->second = npos;};
        std::string tmpstr;
        for (str_indx_map::iterator it = newnames.begin(); it != newnames.end(); ++it) {
            try {
                tmpstr = it->first;
                lower_and_trim(tmpstr);
                it->second = add(tmpstr, groupid, false);}
            catch (dvncierror& err) {
                it->second = npos;}}
        addindexmap(newnames);}

    void tagsbase::addindexmap(str_indx_map& mp) {
        INP_EXCLUSIVE_LOCK(item_indexer->memlock());
        buildindex();}

    size_t tagsbase::globalmemsize() const {
        if (globalmemsize_) return globalmemsize_;
        size_t tmp = 0;
        tmp += mapsize();
        if (stringbs_) tmp += stringbs_->mapsize();
        if (valstrb_) tmp += valstrb_->mapsize();
        if (commands_) tmp += commands_->mapsize();
        if (journal_) tmp += journal_->mapsize();
        if (alarms_) tmp += alarms_->mapsize();
        if (debug_) tmp += debug_->mapsize();
        if (registry_) tmp += registry_->mapsize();
        if (clients_) tmp += clients_->mapsize();
        if (groups()) tmp += groups()->mapsize();
        if (agroups()) tmp += agroups()->mapsize();
        if (accessrules()) tmp += accessrules()->mapsize();
        if (users()) tmp += users()->mapsize();
        if (valbuffers_) tmp += valbuffers_->mapsize();
        if (reportbuffers_) tmp += reportbuffers_->mapsize();
        return (globalmemsize_ = tmp);}

    void tagsbase::checkreporttime(size_type id) {
        if ((exists(id)) && (IN_REPORTSET(type(id)))) {
            datetime tm = time_log(id);
            if (!tm.is_special()) {
                normalizeperiod(tm, type(id));
                if (tm < now()) {
                    valid(id, REPORT_NEEDREQUEST);}
                else {
                    valid(id, REPORT_NORMAL);}}}}

    void tagsbase::increpttime(size_type id) {
        if ((exists(id)) && (IN_REPORTSET(type(id)))) {
            datetime tm = time_log(id);
            if (!tm.is_special()) {
                normalizeperiod(tm, type(id));
                if (tm < now()) {
                    time(id, tm);
                    increporttime(tm, type(id), 1);
                    time_log(id, tm);}
                if (tm < now()) {
                    valid(id, REPORT_NEEDREQUEST);}
                else {
                    valid(id, REPORT_NORMAL);}}}}

    bool tagsbase::insert_to_reportbuff_init(size_type id, const dt_val_map& values) {
        if (!values.empty()) {
            reportbuffers()->insert(reportkey(id), values);
            write_val_report(id, values.rbegin()->first, values.rbegin()->second, 0 , true);
            return true;}
        datetime tm = dvnci::now();
        normalizereporttime(tm, type(id));
        increporttime(tm, type(id), -reporthistory(id));
        write_val_report(id, tm, NULL_DOUBLE, true);
        return true;}

    bool tagsbase::insert_to_reportbuff_init(size_type id) {
        if (report_history_count(id)) {
            dt_val_pair value;
            if (select_reportval_top(id, value)) {
                write_val_report(id, value.first, value.second, 0, true);
                DEBUG_STR_VAL_DVNCI(report_history_simple_init, reportkey(id))
                return true;}}
        return false;}

    bool tagsbase::insert_to_reportbuff_init(size_type id, const datetime& lst) {
        if (lst == nill_time) return false;
        write_val_report(id, lst, NULL_DOUBLE, 0, true);
        return true;}

    void tagsbase::valuestringreplace(size_type id, bool to_sys) {
        if (to_sys) {
            size_t tmppos = operator[](id)->value<size_t > ();
            valstrb_->replace_to_sys(tmppos);
            operator[](id)->value<size_t > (tmppos);}
        else {
            size_t tmppos = operator[](id)->value<size_t > ();
            valstrb_->replace_from_sys(tmppos);
            operator[](id)->value<size_t > (tmppos);}}
    
    void tagsbase::value_internal(size_type id, const std::string& value) {
            if (exists(id)) {
                if (IN_TEXTSET(type(id))) {
                    size_t tmppos = operator[](id)->value<size_t > ();
                    valstringvalue(tmppos, value, in_sysvar(id));
                    if (tmppos != operator[](id)->value<size_t > ()) {
                        operator[](id)->value<size_t > (tmppos);
                        if (groups()->appid(group(id))==NS_GROUP_SYSTEMVAR)
                             writetofile(id);}}}}

    template<>
    std::string tagsbase::value<std::string>(size_type id) const {
        return (!IN_TEXTSET(type(id))) ? itemex(id)->value_str() : valstringvalue(operator[](id)->value<size_t > ());}

    template<>
    datetime tagsbase::value<datetime>(size_type id) const {
        return (type(id) == TYPE_TM) ? cast_datetime_fromnum64(operator[](id)->value64()) : nill_time;}

    template<>
    std::string tagsbase::value_log<std::string>(size_type id) const {
        if (!exists(id)) return "";
        return (!IN_TEXTSET(type(id))) ? operator[](id)->value_str() : "";}

    template<>
    datetime tagsbase::value_log<datetime>(size_type id) const {
        return (type(id) == TYPE_TM) ? cast_datetime_fromnum64(operator[](id)->value_log64()) : nill_time;}

    template<>
    std::string tagsbase::minraw_prtd<std::string>(size_type id) const {
        return exists(id) ? operator[](id)->minraw_str() : "";}

    template<>
    std::string tagsbase::maxraw_prtd<std::string>(size_type id) const {
        return exists(id) ? operator[](id)->maxraw_str() : "";}

    template<>
    void tagsbase::restore_raw_range<bool>(size_type id, bool& val) {}

    template<>
    std::string tagsbase::mineu_prtd<std::string>(size_type id) const {
        return exists(id) ? operator[](id)->mineu_str() : "";}

    template<>
    std::string tagsbase::maxeu_prtd<std::string>(size_type id) const {
        return exists(id) ? operator[](id)->maxeu_str() : "";}

    template<>
    void tagsbase::restore_eu_range<bool>(size_type id, bool& val) {}

    template<>
    bool tagsbase::logdb_expired(size_type id, const bool& val) {
        return value_log<bool>(id) != val;}

    template<>
    std::string tagsbase::alarmconst_prtd<std::string>(size_type id) const {
        return exists(id) ?
                operator[](id)->alarmconst_str() : "";}}




