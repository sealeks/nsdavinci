/* 
 * File:   service.h
 * Author: Serg
 *
 * Created on 28 Р�СЋР»СЊ 2010 Рі., 14:58
 */

#ifndef _DVNCI_KRNL_BASESERVICE_H
#define	_DVNCI_KRNL_BASESERVICE_H

#include <kernel/proccesstmpl.h>

namespace dvnci {

    template<typename IDTYPE = indx >
    class rootbasisservice : public executable {

    public:


        typedef std::pair<IDTYPE, group_proccessor_ptr > idtype_threads_map_pair;
        typedef std::map<IDTYPE, group_proccessor_ptr, std::less<IDTYPE>,
        std::allocator<idtype_threads_map_pair > > idtype_threads_map_map;
        typedef typename idtype_threads_map_map::iterator idtype_threads_map_iteator;

        typedef std::pair<IDTYPE, threadgroup_ptr > idtype_thread_pair;
        typedef std::map<IDTYPE, threadgroup_ptr, std::less<IDTYPE>,
        std::allocator<idtype_thread_pair > > idtype_thread_map;
        typedef typename idtype_thread_map::iterator idtype_thread_iterator;

        rootbasisservice(const fspath& pth, eventtypeset evts = (sIMMITagManage | sIMMIGroupManage), appidtype app = 0, bool extededmes = false) :
        executable(), appid(app), path(pth), events(evts), extededmess(extededmes) {
        };

        virtual ~rootbasisservice() {
        }

        virtual bool operator()() {
            messagestruct message;
            boost::xtime xt;
            while (!terminated()) {
                if (init()) {
                    if (terminated()) break;
                    addmillisec_to_now(xt, 3);
                    if (main_queue)
                        if (proccess_queues::try_recieve(main_queue.get(), message)) {
                            serv_func(message.mess, message.id, message.some);
                        }
                    if (terminated()) break;
                    boost::thread::sleep(xt);
                }
            }
            uninitialize();
            intf.reset();
            return true;
        }

    protected:

        virtual bool initialize() {

            if (!intf) intf = dvnci::krnl::factory::build(path, appid, events);
            if (intf) {
                main_queue = intf->getqueue();
                if (initialize_impl()) {
                    intf->debugwarning("Start service main thread");
                    return true;
                }
            }
            return false;
        }

        virtual bool initialize_impl() {
            return true;
        }

        virtual bool uninitialize() {
            DEBUG_STR_DVNCI(STARTTERMINATE)
            for (idtype_threads_map_iteator it = threads_map.begin(); it != threads_map.end(); ++it) {
                it->second->terminate();
            }
            for (idtype_thread_iterator itth = th_map.begin(); itth != th_map.end(); ++itth) {
                itth->second->join();
            }
            th_map.clear();
            threads_map.clear();
            uninitialize_impl();
            intf->debugwarning("Stop service main thread");
            return true;
        }

        virtual bool uninitialize_impl() {
            return true;
        }

        virtual void execute_thread(const IDTYPE& id) {
        }

        virtual void termitate_thread(const IDTYPE& id) {
            idtype_threads_map_iteator it = threads_map.find(id);
            activeid(id, false);
            idtype_thread_iterator itth = th_map.find(id);
            if (it != threads_map.end()) {
                it->second->terminate();
            }
            if (itth != th_map.end()) {
                itth->second->join();
                th_map.erase(itth);
            }
            if (it != threads_map.end()) {
                threads_map.erase(id);
            }
            DEBUG_STR_DVNCI(GROUPSTOP);
        };

        virtual void activeid(const IDTYPE& id, bool act) {
        }

        virtual bool check_thread(indx id) {
            return false;
        }

        virtual void addmessage(indx group, qumsgtype mess, indx id, indx some) {
            for (idtype_threads_map_iteator it = threads_map.begin(); it != threads_map.end(); ++it) {
                if ((extededmess) || (it->second->group_included(group)))
                    it->second->addmessage(mess, id, some);
            }
        }

        virtual void serv_func(qumsgtype mess, indx id, indx some) {
#ifdef DVNCI_DEDUG
            intf->debug("MESSSAGE_" + to_str(mess) + "_" + messagestrin_test(mess) + " id=" + to_str(id) + " some=" + to_str(some));
#endif
            switch (mess) {
                case MSG_DVNCIGROUPCHAPP:
                {
                    check_thread(id);
                    break;
                }
                case MSG_DVNCTAGDELFROMGR:
                case MSG_DVNCTAGADDTOGR:
                case MSG_DVNCINEWREF:
                case MSG_DVNCIREMREF:
                case MSG_DVNCITAGREPORT:
                {
                    addmessage(some, mess, id, some);
                    break;
                }
                case MSG_DVNCTAGREPNAME:
                {
                    if (extededmess) {
                        addmessage(some, mess, id, some);
                    }
                    break;
                }
            }
        }


    protected:
        appidtype appid;
        tagsbase_ptr intf;
        mq_class_ptr main_queue;
        idtype_threads_map_map threads_map;
        idtype_thread_map th_map;
        fspath path;
        eventtypeset events;
        bool extededmess;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class basisservice : public rootbasisservice<indx> {

    public:

        basisservice(const fspath& pth, eventtypeset evts = (sIMMITagManage | sIMMIGroupManage), appidtype app = 0, bool extededmes = false) :
        rootbasisservice<indx>(pth, evts, app, extededmes) {
        };

        virtual bool initialize_impl() {
            indx_set groupset;
            intf->select_groups_by_appid(appid, groupset);
            for (indx_set::iterator it = groupset.begin(); it != groupset.end(); ++it) {
                execute_thread(*it);
            }
            return true;
        }

        virtual bool check_thread(indx id) {
            appidtype newappid = intf->groups()->exists(id) ? intf->groups()->appid(id) : 0;
            ;
            idtype_threads_map_iteator it = threads_map.find(id);
            if (it != threads_map.end()) {
                termitate_thread(id);
                if (newappid != appid) {
                    return true;
                }
            }
            if (newappid == appid) {
                execute_thread(id);
            }
            return true;
        }

        virtual void activeid(const indx& id, bool act) {
            if (intf)
                intf->groups()->active(id, false);
        }
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename proccessortype>
    class uniintfservice : public basisservice {

        typedef proccessortype groupproccessor;

    public:

        uniintfservice(const fspath& pth, appidtype app = 0, bool extededmes = false) : basisservice(pth,
        (sIMMITagManage | sIMMIGroupManage),
        app, extededmes) {
        }

    protected:

        virtual void execute_thread(const indx& id) {
            idtype_threads_map_map::iterator it = threads_map.find(id);
            if (it != threads_map.end()) return;
            DEBUG_STR_VAL_DVNCI(ADDGROUPFROMBASEEND, id);
            group_proccessor_ptr tmp = group_proccessor_ptr(new groupproccessor(intf, appid, id));
            threads_map.insert(idtype_threads_map_pair(id, tmp));
            th_map.insert(idtype_thread_pair(id, threadgroup_ptr(new boost::thread(tmp))));
        }
    };


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename proccessortype>
    class linkdriverservice : public rootbasisservice<metalink> {

        typedef proccessortype groupproccessor;

    public:

        linkdriverservice(const fspath& pth, appidtype app = 0) : rootbasisservice<metalink>(pth,
        (sIMMITagManage | sIMMIGroupManage), app, false) {
        }

    protected:

        bool initialize_impl() {
            metalink_set linkset;
            intf->select_metalinks_set_by_appid(appid, linkset);
            for (metalink_set::iterator it = linkset.begin(); it != linkset.end(); ++it) {
                execute_thread(*it);
            }
            return true;
        }

        virtual void execute_thread(const metalink& id) {
            idtype_threads_map_iteator it = threads_map.find(id);
            if (it != threads_map.end()) return;
            group_proccessor_ptr tmp = group_proccessor_ptr(new groupproccessor(intf, appid, id));
            threads_map.insert(idtype_threads_map_pair(id, tmp));
            th_map.insert(idtype_thread_pair(id, threadgroup_ptr(new boost::thread(tmp))));
        }

        virtual void activeid(const metalink& id, bool act) {
        }

        virtual bool check_thread(indx id) {
            appidtype newappid = intf->groups()->exists(id) ? intf->groups()->appid(id) : 0;
            metalink newlnk = intf->groups()->exists(id) ? intf->groups()->link(id) : metalink();
            bool newlink_no_empty = threads_map.find(newlnk) != threads_map.end();
            intf->debugerror(" check_thread find change CHECK");
            intf->debugerror(" check_thread find change CHECK id=" + to_str(id));
            for (idtype_threads_map_iteator it = threads_map.begin(); it != threads_map.end(); ++it) {
                if (it->second->group_included(id)) {
                    intf->debugerror(" check_thread find change");
                    indx_set mlksettmp;
                    intf->select_groups_by_metalink(it->second->link(), appid, mlksettmp);
                    bool oldlink_no_empty = !mlksettmp.empty();
                    metalink oldlnk = it->second->link();
                    if ((newappid != appid) || ((oldlnk != newlnk))) {
                        intf->debugerror(" check_thread find change LINK REMOVE");
                        termitate_thread(oldlnk);
                        if (oldlink_no_empty) {
                            intf->debugerror(" check_thread find change LINK ADD WITHOUT");
                            execute_thread(oldlnk);
                        }
                        if (newappid != appid) return true;
                        break;
                    } else {
                        intf->debugerror(" check_thread find change  NOLINKCHAGE is need restart");
                        termitate_thread(oldlnk);
                        execute_thread(newlnk);
                        return true;
                    }
                }
            }

            if (newappid == appid) {
                if (newlink_no_empty) {
                    intf->debugerror("check_thread newlink_no_empty need terminate old REMOVE NEW LINK");
                    termitate_thread(newlnk);
                }
                intf->debugerror("check_thread find change ADD NEW LINK");
                execute_thread(newlnk);
                return true;
            }
            return false;
        };
    };

}

#endif	/* BASESERVICE_H */

