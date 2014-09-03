/* 
 * File:   main.cpp
 * Author: Serg
 *
 * Created on 21 Июнь 2010 г., 15:08
 */

//#define IS_DVNCI_SERVICE

#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/service.h>

#include "expr_executor.h"

using namespace dvnci;
using namespace std;
using namespace dvnci::database;

dvnci::executable_ptr dvnci::mainserv;
std::string dvnci::DVNCI_SERVICE_NAME = NS_SYSTEM_SERVICE_NAME;
dvnci::appidtype dvnci::DVNCI_SERVICE_APPID = NS_SYSTEM_SERVICE;
fspath basepath;

class membaseservice : public basisservice {
    typedef system_executor<expr_executor> expression_executor;
    typedef group_proccessor_templ<expression_executor, (TYPE_SIMPL | TYPE_TIME) > groupcount;

    typedef system_executor<sysreport_executor> sysrep_executor;
    typedef group_proccessor_templ<sysrep_executor, TYPE_REPORT> systemreporttag;

    typedef system_executor<sysreportcnt_executor> sysrepcnt_executor;
    typedef group_proccessor_templ<sysrepcnt_executor, TYPE_REPORT> systemreportcounttag;


public:

    membaseservice() : basisservice(basepath,
    (sIMMITagManage | sIMMIGroupManage),
    NS_SYSTEM_SERVICE, true), provider_database(0), connection_string(""), dbdrv() {
    }

protected:

    virtual bool initialize_impl() {

        setdbdriver();

        indx_set groupset;
        intf->select_groups_by_appid(NS_GROUP_SYSTEMCOUNT, groupset);
        for (indx_set::iterator it = groupset.begin(); it != groupset.end(); ++it) {
            execute_thread(*it);
        }
        groupset.clear();
        intf->select_groups_by_appid(NS_GROUP_SYSTEMREPORT, groupset);
        for (indx_set::iterator it = groupset.begin(); it != groupset.end(); ++it) {
            execute_thread(*it);
        }
        groupset.clear();
        intf->select_groups_by_appid(NS_GROUP_SYSTEMREPORTCOUNT, groupset);
        for (indx_set::iterator it = groupset.begin(); it != groupset.end(); ++it) {
            execute_thread(*it);
        }
        return true;
    }

    virtual void execute_thread(indx id) {
        if (intf->groups()->exists(id)) {
            group_proccessor_ptr tmp;
            switch (intf->groups()->appid((id))) {
                case NS_GROUP_SYSTEMCOUNT:
                {
                    tmp = group_proccessor_ptr(new groupcount(intf, NS_GROUP_SYSTEMCOUNT, id));
                    break;
                }
                case NS_GROUP_SYSTEMREPORT:
                {
                    tmp = group_proccessor_ptr(new systemreporttag(intf, NS_GROUP_SYSTEMREPORT, id));
                    break;
                }
                case NS_GROUP_SYSTEMREPORTCOUNT:
                {
                    tmp = group_proccessor_ptr(new systemreportcounttag(intf, NS_GROUP_SYSTEMREPORTCOUNT, id));
                    break;
                }
                default:
                {
                }
            }
            if (tmp) {
                threads_map.insert(idtype_threads_map_pair(id, tmp));
                th_map.insert(idtype_thread_pair(id, threadgroup_ptr(new boost::thread(tmp))));
                intf->groups()->active(id, true);
            }
        }
    }

    void setdbdriver() {
        if (intf) {
            std::string con_str = intf->conf_property(NS_CNFG_DBCONSTR);
            dbprovtype provider_db = intf->conf_numproperty<dbprovtype>(NS_CNFG_DBMANAGER);
            if ((provider_database != provider_db) || (connection_string != con_str)) {
                dbdriver_ptr newdrv;
                if (dbdrv) {
                    THD_EXCLUSIVE_LOCK(dbdrv);
                    if ((provider_db != 0) && (!con_str.empty()))
                        newdrv = bdconnectionfactory::build(provider_db, con_str);
                    dbdrv.swap(newdrv);
                    sysreport_executor::setdbdriver(dbdrv);
                    sysreportcnt_executor::setdbdriver(dbdrv);
                } else {
                    if ((provider_db != 0) && (!con_str.empty()))
                        newdrv = bdconnectionfactory::build(provider_db, con_str);
                    dbdrv.swap(newdrv);
                    if (dbdrv) {
                        THD_EXCLUSIVE_LOCK(dbdrv);
                        sysreport_executor::setdbdriver(dbdrv);
                        sysreportcnt_executor::setdbdriver(dbdrv);
                    }
                }
            }
            provider_database = provider_db;
            connection_string = con_str;
        }
    }

    virtual bool check_thread(indx id) {

        appidtype newappid = intf->groups()->exists(id) ? intf->groups()->appid(id) : 0;
        idtype_threads_map_iteator it = threads_map.find(id);
        if (it != threads_map.end()) {
            num32 oldappid = it->second->appid();
            if ((newappid != NS_GROUP_SYSTEMCOUNT) && (newappid != NS_GROUP_SYSTEMREPORT) && (newappid != NS_GROUP_SYSTEMREPORTCOUNT)) {
                termitate_thread(id);
                return true;
            }
            if (newappid != oldappid) {
                termitate_thread(id);
            } else {
                return true;
            }
        }
        if ((newappid == NS_GROUP_SYSTEMCOUNT) || (newappid == NS_GROUP_SYSTEMREPORT) || (newappid == NS_GROUP_SYSTEMREPORTCOUNT)) {
            execute_thread(id);
        }
        return true;
    }

private:
    dbprovtype provider_database;
    std::string connection_string;
    dbdriver_ptr dbdrv;
};

int main(int argc, char** argv) {
    std::string quit_in;
    basepath = dvnci::getlocalbasepath();
#ifdef DVNCI_DEDUGFILE
    ofstream file("C:\\wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww.txt");
    std::cout.rdbuf(file.rdbuf());
#endif
    mainserv = executable_ptr(new membaseservice());
    DEBUG_VAL_DVNCI(basepath.string())
#ifndef DVNCI_DEDUG
            if (serviceargumentparser(argc, argv) == SERVICE_OPEATION_APP) {
#endif

        try {
            DEBUG_STR_DVNCI(start app)
            boost::thread th = boost::thread(mainserv);
            while ((std::cin >> quit_in) && ((quit_in != "q") && (quit_in != "Q")));
            mainserv.terminate();
            th.join();
        }        catch (std::exception& err) {
            DEBUG_VAL_DVNCI(err.what());
        }
#ifndef DVNCI_DEDUG
    }
#endif
    DEBUG_STR_DVNCI(FIN)
    return (EXIT_SUCCESS);
}

