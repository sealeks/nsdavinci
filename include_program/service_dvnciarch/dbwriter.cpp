/* 
 * File:   dbwriter.cpp
 * Author: Alexeev
 * 
 * Created on 4 Апрель 2011 г., 14:17
 */

#include "dbwriter.h"


namespace dvnci {

    /*
     *  db_writer
     */

    using namespace dvnci::database;


    dbdriver_ptr db_writer::dbdrv = dbdriver_ptr();

    bool db_writer::operator()() {
        boost::xtime xt;
        while (!terminated()) {
            if (init()) {
                if (terminated()) break;
                addmillisec_to_now(xt, 10);
                THD_EXCLUSIVE_LOCK(*mtx);
                if (j_needwrite()) {
                    intf->select_journal<journal_item, num64 > (journal_vect, j_guid, j_cursor, j_count);
                    if (!journal_vect.empty()) {
                        DEBUG_STR_VAL_DVNCI(journalwtite, journal_vect.size());
                        THD_EXCLUSIVE_LOCK2(dbdrv)
                        if (!connected()) return false;
                        if (dbdrv->insert_journal(journal_vect)) {
                            journal_vect.clear();
                        } else {
                            if (journal_vect.size()>static_cast<std::size_t> (MAX_NUM32_SIGNED)) {
                                journal_vect.clear();
                                intf->debugerror("Journal's data was losted");
                            }
                        }
                    }
                    last_j_time = now();
                }
                if (d_needwrite()) {
                    intf->select_debug<debug_item, num64 > (debug_vect, d_guid, d_cursor, d_count);
                    if (!debug_vect.empty()) {
                        DEBUG_STR_VAL_DVNCI(debugwtite, debug_vect.size());
                        THD_EXCLUSIVE_LOCK2(dbdrv)
                        if (!connected()) return false;
                        if (dbdrv->insert_debug(debug_vect)) {
                            debug_vect.clear();
                        } else {
                            if (debug_vect.size()>static_cast<std::size_t> (MAX_NUM32_SIGNED)) {
                                debug_vect.clear();
                                intf->debugerror("Debug's tabale was  losted");
                            }
                        }
                    }
                    last_d_time = now();
                }
                if (t_needwrite()) {
                    THD_EXCLUSIVE_LOCK2(dbdrv)
                    flash_trend();
                }

                if (terminated()) break;
                boost::thread::sleep(xt);
            }
        }
        uninitialize();
        return true;
    }

    void db_writer::write_trend(indx id, datetime tm, double val) {
        if (!is_connected()) return;
        THD_EXCLUSIVE_LOCK(*mtx);
        trendupdated = true;
        if (tm.is_special()) return;
        if (tm.date().day() != lasttrday) {
            THD_EXCLUSIVE_LOCK(dbdrv)
            flash_trend();
            trendupdated = false;
        }
        if (trend_dqu.size() >= MAX_TREND_BUFFER) trend_dqu.pop_front();
        trend_dqu.push_back(indx_dt_val(id, dt_val_pair(tm, val)));
        lasttrday = tm.date().day();
    }

    void db_writer::write_trends(indx id, const dt_val_map& vlmap) {
        if (vlmap.empty()) return;
        if (!is_connected()) return;
        datetime tm = vlmap.rbegin()->first;
        THD_EXCLUSIVE_LOCK(*mtx);
        trendupdated = true;
        if (tm.is_special()) return;
        if (tm.date().day() != lasttrday) {
            THD_EXCLUSIVE_LOCK(dbdrv)
            flash_trend();
            trendupdated = false;
        }
        if ((trend_dqu.size() + vlmap.size()) > MAX_TREND_BUFFER) {
            dt_val_deque::iterator itstrt = trend_dqu.begin();
            dt_val_deque::iterator itstp = itstrt + ((trend_dqu.size() + vlmap.size()) - MAX_TREND_BUFFER);
            trend_dqu.erase(itstrt, itstp);
            intf->debugwarning("trend data losted");
        }
        for (dt_val_map::const_iterator it = vlmap.begin(); it != vlmap.end(); ++it)
            trend_dqu.push_back(indx_dt_val(id, dt_val_pair(it->first, it->second)));
        lasttrday = tm.date().day();
    }

    bool db_writer::flash_trend() {
        if (!trend_dqu.empty()) {
            if (!connected()) {
                trend_dqu.clear();
            }
            if (dbdrv->insert_trend(trend_dqu)) {
                DEBUG_STR_VAL_DVNCI(trendwtite, trend_dqu.size());
                trend_dqu.clear();
            } else {
                if (!connected()) {
                    trend_dqu.clear();
                    return false;
                }
            }
        }
        last_t_time = now();
        trendupdated = false;
        return true;
    }

    /*
     *  trend_observer
     */


    bool trend_observer::operator()() {
        boost::xtime xt;
        while (!terminated()) {
            if ((init()) && (db_wrtr) && (db_wrtr->is_connected())) {
                THD_EXCLUSIVE_LOCK(*mtx);
                if (!keyset.empty()) {
                    for (indxdt_map::iterator it = keyset.begin(); it != keyset.end(); ++it) {
                        if (terminated()) break;
                        if (intf->trendbuff_need_write(it->first)) {
                            intf->select_trendbuff(it->first, vlmap, it->second, nill_time, intf->logdb(it->first));
                            if (!vlmap.empty()) {
                                db_wrtr->write_trends(it->first, vlmap);
                                it->second = vlmap.rbegin()->first;
                            }
                            intf->trendbuff_need_write(it->first, false);
                        }
                    }
                    addmillisec_to_now(xt, 30);
                } else {
                    addmillisec_to_now(xt, 1000);
                }
            } else {
                addmillisec_to_now(xt, 1000);
            }
            boost::thread::sleep(xt);
        }
        return true;
    }

    void trend_observer::add_trend(indx id) {
        THD_EXCLUSIVE_LOCK(*mtx);
        DEBUG_STR_VAL_DVNCI(trend_observer_add_trend, id);
        if (keyset.find(id) == keyset.end())
            keyset.insert(indxdt_pair(id, nill_time));
    }

    void trend_observer::remove_trend(indx id) {
        THD_EXCLUSIVE_LOCK(*mtx);
        DEBUG_STR_VAL_DVNCI(trend_observer_remove_trend, id);
        if (keyset.find(id) != keyset.end())
            keyset.erase(id);
    }

    bool trend_observer::initialize() {
        if ((!intf) || (!db_wrtr))
            return false;
        THD_EXCLUSIVE_LOCK(*mtx);
        for (indx i = 0; i < intf->count(); ++i) {
            if ((intf->exists(i)) && (intf->logged(i))) {
                keyset.insert(indxdt_pair(i, intf->trend_history_toptime(i)));
            }
        }
        return true;
    }

    bool trend_observer::uninitialize() {
        THD_EXCLUSIVE_LOCK(*mtx);
        keyset.clear();
        return true;
    }
}
