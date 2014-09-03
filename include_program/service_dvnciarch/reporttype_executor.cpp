/* 
 * File:   comandcaseexpession.cpp
 * Author: Serg
 * 
 * Created on 18 Июнь 2010 г., 14:10
 */

#include "reporttype_executor.h"

namespace dvnci {

    using namespace dvnci::database;

    dbdriver_ptr reporttype_executor::dbdriver = dbdriver_ptr();

    void reporttype_executor::execute_impl(indx id) {
        if (error()) {
            intf->error(id, error());
            return;
        }
        if (dbdriver) {
            THD_EXCLUSIVE_LOCK(dbdriver);
            if (!dbdriver->isconnected()) {
                dbdriver->connect();
            }
            if (dbdriver->isconnected()) {
                switch (intf->valid(id)) {
                    case REPORT_NEEDKHOWDEEP:
                    {
                        DEBUG_VAL_DVNCI(intf->report_history_count(id))
                        if (!intf->insert_to_reportbuff_init(id)) {
                            dvnci::datetime tm = nill_time;
                            dt_val_map tmpvlmap;
                            dbdriver->select_lastreporttime(intf(expression_), intf->type(id), intf->reporthistory(id), tmpvlmap);
                            intf->insert_to_reportbuff_init(id, tmpvlmap);
                        }
                        break;
                    }
                    case REPORT_DATA:
                    {
                        DEBUG_STR_DVNCI(REPORT_DATA)
                        if (!intf->report_history_empty(id)) {
                            DEBUG_STR_DVNCI(report_history_noempty)
                            dt_val_map tmpvlmap;
                            intf->select_reportbuff(id, tmpvlmap, intf->time_log(id), now());
                            if (!tmpvlmap.empty()) {
                                if (dbdriver->insert_report(intf(expression_), intf->type(id), tmpvlmap))
                                    intf->write_val_report(id, tmpvlmap.rbegin()->first, tmpvlmap.rbegin()->second, 0, true);
                                break;
                            }
                        } else {
                            DEBUG_STR_DVNCI(report_history_empty)
                            if (!isNaN(intf->value<double>(id))) {
                                dbdriver->insert_report(intf(expression_), intf->type(id), intf->value<double>(id), intf->time_log(id));
                            }
                            intf->increpttime(id);
                        }
                        break;
                    }
                    default:
                    {
                    }
                }
            }
        }
    }

    void reporttype_executor::parse(std::string val) {
        error(0);
        if ((intf) && (intf->exists(val))) {
            id = intf->operator ()(val);
            id = ((id != npos) && (IN_REPORTSET(intf->type(id)))) ? id : npos;
            if (id != npos) {
                type = intf->type(id);
                error(0);
                intf->debug("Add report tag id=" + to_str(id) + " bind=" + val);
                return;
            }
        }
        id = npos;
        type = 0;
        error(ERROR_BINDING);
        intf->debug("Error report tag bind=" + val);
        return;
    }
}
