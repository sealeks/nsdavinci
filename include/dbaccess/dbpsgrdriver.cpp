/* 
 * File:   dbpsgrdriver.cpp
 * Author: Serg
 * 
 * Created on 18 Май 2010 г., 17:44
 */

#include <dbaccess/dbpsgrdriver.h>

#ifdef _MSC_VER
#include "soci-postgresql.h"
#endif // _MSC_VER


namespace dvnci {
    namespace database {

        using namespace soci;

        std::string dbpsgrdriver::connection_string() {
            return ((server() == "") && (port() == "")) ? ("dbname=" + database() + " user=" + user() + " password=" + password()) :
                    ((server() != "") && (port() == "")) ? ("host=" + server() + " dbname=" + database() + " user=" + user() + " password=" + password()) :
                    ((server() == "") && (port() != "")) ? ("dbname=" + database() + " user=" + user() + " password=" + password()) :
                    ("host=" + upper_copy(server()) + /*" port=" + port() + */" dbname=" + database() + " user=" + user() + " password=" + password());
        }

        void dbpsgrdriver::raisdisconnect(bool throwerr) {
            try {
                sql.close();
            } catch (...) {
            }
            state_ = st_disconnected;
            if (throwerr) throw dvncierror(ERROR_NO_DATABASE_CONN);
        }

        bool dbpsgrdriver::getmeta() {
            try {
                rowset_tp rs = (sql.prepare << "select tablename from pg_tables");
                for (rowset_tp::const_iterator it = rs.begin(); it != rs.end(); ++it) {
                    soci::row const& row = *it;
                    std::string tmptbl = row.get<std::string > (0);
                    dvnci::lower_and_trim(tmptbl);
                    tables_.insert(tmptbl);
                }
                tablesset_init = true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                throw e;
                return false;
            } catch (...) {
                return false;
            }
            return true;
        }

        bool dbpsgrdriver::metaexists(const std::string& tn) {
            try {

                clearerror();
                std::string const& req = "select tablename from pg_tables where tablename=\'" + tn + "\'";
                soci::indicator ind;
                std::string tn_;
                DEBUG_VAL_DVNCI(req)
                sql << req, soci::into(tn_, ind);
                if (sql.got_data()) {
                    switch (ind) {
                        case soci::i_ok:
                        case soci::i_truncated:
                        {
                            return true;
                        }
                        default:
                        {
                            return false;
                        }
                    }
                }
                return false;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
            return true;
        }

        bool dbpsgrdriver::createreptable(std::string tn) {
            if (tableexist(tn)) return true;
            try {

                clearerror();
                //set client_min_messages = warning;
                std::string const& req = "create table " + tn + " (cod integer not null, tm bigint not null, val float null, constraint " + tn + "_pkey "
                        " primary key(cod, tm)); create index cod_" + tn + " on " + tn + " (cod)";
                sql << req;
                dvnci::lower_and_trim(tn);
                tables_.insert(tn);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return true;
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
        }

        bool dbpsgrdriver::createtrtable(std::string tn) {
            if (tableexist(tn)) return true;
            try {

                clearerror();
                //set client_min_messages = warning;
                std::string const& req = "create table " + tn + " (cod integer not null, tm bigint not null, val float null)  "
                        "; create index cod_" + tn + " on " + tn + " (cod)";
                sql << req;
                dvnci::lower_and_trim(tn);
                tables_.insert(tn);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return true;
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
        }

        bool dbpsgrdriver::createjrnltable(std::string tn) {
            if (tableexist(tn)) return true;
            try {

                clearerror();
                std::string const& req = "create table " + tn + " (tm bigint, itag char(150), icomment char(350), iagroup char(150) ,"
                        "itype integer, ilevel integer, ival char(250), iuser char(150) , ihost char(150)); create index tm_" + tn + " on " + tn + " (tm)";
                sql << req;
                dvnci::lower_and_trim(tn);
                tables_.insert(tn);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return true;
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
        }

        bool dbpsgrdriver::createdbgtable(std::string tn) {
            if (tableexist(tn)) return true;
            try {

                clearerror();
                std::string const& req = "create table " + tn + " (tm bigint, imessage char(350), app integer, ilevel integer); create index tm_" + tn + " on " + tn + " (tm)";
                sql << req;
                dvnci::lower_and_trim(tn);
                tables_.insert(tn);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return true;
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                return false;
            }
        }

        bool dbpsgrdriver::createtrenddef() {
            if (tableexist("trenddef")) return true;
            try {

                clearerror();
                std::string tn = TRENDDEF_TABLE;
                std::string const& req = "create table " + tn + " (cod integer, iname char(150), icomment text, eu text, mineu float, maxeu float, "
                        "type integer, onmsg integer, offmsg integer , almsg integer, logged integer,  primary key(cod))";
                sql << req;
                dvnci::lower_and_trim(tn);
                tables_.insert(tn);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return true;
                throw e;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
        }

        bool dbpsgrdriver::insert_journal_impl(const datetime& tm, const std::string& tg, const std::string& comment, const std::string& agroup, num32 type,
                num32 alevel, const std::string& val, const std::string& user, const std::string& host) {
            try {

                clearerror();
                std::string tn = dt_to_journaltabelname(tm);
                if ((tn != lastalarm) && (!tableexist(tn))) {
                    if (createjrnltable(tn)) lastalarm = tn;
                } else lastalarm = tn;
                num64 const& tmp_tm = castnum64_from_datetime(tm);
                std::string const& req = "insert into " + tn + "(tm, itag, icomment, iagroup, itype, ilevel, ival, iuser,  ihost)"
                        " values (:tm, :tag, :comment, :agroup, :type ,:level, :val, :user ,:host)";
                sql << req, use(tmp_tm), use(tg), use(comment), use(agroup), use(type), use(alevel), use(val), use(user), use(host);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION) return true;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_journal_by_one_impl(const journal_item_vect& vctval) {
            bool rslt = true;
            for (journal_item_vect::const_iterator it = vctval.begin(); it != vctval.end(); ++it) {
                if (!insert_journal_impl(it->time, it->tag, it->text, it->agroup, static_cast<msgtype> (it->type), static_cast<altype> (it->level),
                        it->value, it->user, "")) rslt = false;
            }
            return rslt;
        }

        bool dbpsgrdriver::insert_journal_impl(const journal_item_vect& vctval) {
            if (vctval.empty()) return true;
            datetime tm = vctval[0].time;
            try {

                clearerror();
                std::string tn = dt_to_journaltabelname(tm);
                if ((tn != lastalarm) && (!tableexist(tn))) {
                    if (createjrnltable(tn)) lastalarm = tn;
                } else lastalarm = tn;
                num64 tmp_tm = 0;
                std::string tg = "";
                std::string comment = "";
                std::string agroup = "";
                num32 type = 0;
                std::string val = "";
                num32 alevel = 0;
                std::string user = "";
                std::string host = "";
                soci::statement stmnt = (sql.prepare << "insert into " + tn + "(tm, itag, icomment, iagroup, itype, ilevel, ival, iuser,  ihost)"
                        " values (:tm, :tag, :comment, :agroup, :type ,:level, :val, :user ,:host)",
                        use(tmp_tm), use(tg), use(comment), use(agroup), use(type), use(alevel), use(val), use(user), use(host));
                for (journal_item_vect::const_iterator it = vctval.begin(); it != vctval.end(); ++it) {
                    tmp_tm = num64_cast<datetime>(it->time);
                    tg = it->tag;
                    comment = it->text;
                    agroup = it->agroup;
                    type = static_cast<num32> (it->type);
                    val = it->value;
                    alevel = it->level;
                    user = it->user;
                    host = "";
                    stmnt.execute(true);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION)
                    return insert_journal_by_one_impl(vctval);
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_debug_impl(const datetime& tm, const std::string& message, num32 app, num32 lev) {
            try {

                clearerror();
                std::string tn = dt_to_debugtabelname(tm);
                if ((tn != lastalarm) && (!tableexist(tn))) {
                    if (createdbgtable(tn)) lastalarm = tn;
                } else lastalarm = tn;
                num64 const& tmp_tm = castnum64_from_datetime(tm);
                std::string const& req = "insert into " + tn + "(tm, imessage, app, ilevel)"
                        " values (:tm, :imessage, :app, :level)";
                sql << req, use(tmp_tm), use(message), use(app), use(lev);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION) return true;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_debug_by_one_imp(const debug_item_vect& vctval) {
            bool rslt = true;
            for (debug_item_vect::const_iterator it = vctval.begin(); it != vctval.end(); ++it) {
                if (!insert_debug_impl(it->time, it->message, static_cast<appidtype> (it->appid), static_cast<debuglvtype> (it->level)))
                    rslt = false;
            }
            return rslt;
        }

        bool dbpsgrdriver::insert_debug_impl(const debug_item_vect& vctval) {
            if (vctval.empty()) return true;
            datetime tm = vctval[0].time;
            try {

                clearerror();
                std::string tn = dt_to_debugtabelname(tm);
                if ((tn != lastalarm) && (!tableexist(tn))) {
                    if (createdbgtable(tn)) lastalarm = tn;
                } else lastalarm = tn;
                num64 tmp_tm = 0;
                std::string message = "";
                num32 app = 0;
                num32 lev = 0;
                soci::statement stmnt = (sql.prepare << "insert into " + tn + "(tm, imessage, app, ilevel)"
                        " values (:tm, :imessage, :app, :level)",
                        use(tmp_tm), use(message), use(app), use(lev));
                for (debug_item_vect::const_iterator it = vctval.begin(); it != vctval.end(); ++it) {
                    tmp_tm = num64_cast<datetime>(it->time);
                    message = it->message;
                    app = static_cast<num32> (it->appid);
                    lev = static_cast<num32> (it->level);
                    stmnt.execute(true);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION)
                    return insert_debug_by_one_imp(vctval);
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_trend_impl(num32 id, datetime tm, double data) {
            try {

                clearerror();
                std::string tn = dt_to_trendtabelname(tm);
                if ((tn != lasttrend) && (!tableexist(tn))) {
                    if (createtrtable(tn)) lasttrend = tn;
                } else lasttrend = tn;
                num64 const& tmp_tm = castnum64_from_datetime(tm);
                if (data == data) {
                    std::string const& req = "insert into " + tn + " (cod, tm, val) values (:cod, :tm, :val)";
                    sql << req, use(id), use(tmp_tm), use(data);
                } else {
                    std::string const& req = "insert into " + tn + " (cod, tm) values (:cod, :tm)";
                    sql << req, use(id), use(tmp_tm);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION) return true;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_trend_impl(const dt_val_deque& vctval) {
            try {

                clearerror();
                if (vctval.empty()) return true;
                datetime tm = vctval[0].second.first;
                std::string tn = dt_to_trendtabelname(tm);
                if ((tn != lasttrend) && (!tableexist(tn))) {
                    if (createtrtable(tn)) lasttrend = tn;
                } else lasttrend = tn;
                num64 tmp_tm = 0;
                ;
                num32 cod = 0;
                double val = 0.0;
                soci::statement stmnt = (sql.prepare << "insert into " + tn + " (cod, tm, val) values (:cod, :tm, :val)", soci::use(cod), soci::use(tmp_tm), soci::use(val));
                soci::statement nullstmnt = (sql.prepare << "insert into " + tn + " (cod, tm) values (:cod, :tm)", soci::use(cod), soci::use(tmp_tm));
                for (dt_val_deque::const_iterator it = vctval.begin(); it != vctval.end(); ++it) {
                    tmp_tm = castnum64_from_datetime(it->second.first);
                    cod = static_cast<num32> (it->first);
                    val = it->second.second;
                    if (val != val) nullstmnt.execute(true);
                    else stmnt.execute(true);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION) return true;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_report_impl(num32 id, num32 type, double data, const dvnci::datetime& tm) {
            try {

                clearerror();
                std::string tn = dt_to_reporttabelname(tm, type);
                if ((tn != select_lastreporttime) && (!tableexist(tn))) {
                    if (createreptable(tn)) select_lastreporttime = tn;
                } else select_lastreporttime = tn;

                num64 const& tmp_tm = castnum64_from_datetime(tm);
                std::string const& req = "insert into " + tn + " (cod, tm, val) values (:cod, :tm, :val)";
                sql << req, use(id), use(tmp_tm), use(data);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION) return true;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::insert_report_by_one_imp(num32 id, num32 type, const dt_val_map& values) {
            bool rslt = true;
            for (dt_val_map::const_iterator it = values.begin(); it != values.end(); ++it) {
                if (!insert_report_impl(id, type, it->second, it->first))
                    rslt = false;
            }
            return rslt;
        }

        bool dbpsgrdriver::insert_report_impl(num32 id, num32 type, const dt_val_map& values) {
            if (values.empty()) return true;
            try {

                clearerror();
                datetime tm = values.begin()->first;
                std::string tn = dt_to_reporttabelname(tm, type);
                if ((tn != select_lastreporttime) && (!tableexist(tn))) {
                    if (createreptable(tn)) select_lastreporttime = tn;
                } else select_lastreporttime = tn;
                num64 tmp_tm = 0;
                ;
                num32 cod = 0;
                double val = 0.0;
                soci::statement stmnt = (sql.prepare << "insert into " + tn + " (cod, tm, val) values (:cod, :tm, :val)", soci::use(id), soci::use(tmp_tm), soci::use(val));
                for (dt_val_map::const_iterator it = values.begin(); it != values.end(); ++it) {
                    if ((it->second == it->second) && (it->first != nill_time)) {
                        tmp_tm = castnum64_from_datetime(it->first);
                        cod = static_cast<num32> (id);
                        val = it->second;
                        stmnt.execute(true);
                    }
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRRCOD, e.code());
                if (e.code() == UNIQUE_VIOLATION)
                    return insert_report_by_one_imp(id, type, values);
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::select_impl(const std::string& req_, sql_result& result) {
            try {
                clearerror();
                std::string const& req = req_;

                soci::rowset<soci::row> rs = (sql.prepare << req);

                bool wrhead = false;

                for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {

                    soci::row const& row = *it;

                    if (!wrhead) {
                        wrhead = true;
                        for (std::size_t col = 0; col < row.size(); ++col)
                            result.first.push_back(sql_resultheader(row.get_properties(col).get_name(), static_cast<int> (row.get_properties(col).get_data_type())));
                    }

                    str_vect tmprow;
                    for (std::size_t col = 0; col < row.size(); ++col) {
                        if (row.get_indicator(col) == i_ok) {
                            switch (row.get_properties(col).get_data_type()) {
                                case dt_string:
                                {
                                    tmprow.push_back(to_str(row.get<std::string>(col)));
                                    break;
                                }
                                case dt_date:
                                {
                                    std::tm tmp = row.get<std::tm>(col);
                                    tmprow.push_back(to_str(datetime(boost::gregorian::date(tmp.tm_year + 1900, tmp.tm_mon, tmp.tm_mday),
                                            boost::posix_time::time_duration(tmp.tm_hour, tmp.tm_min, tmp.tm_sec))));
                                    break;
                                }
                                case dt_double:
                                {
                                    tmprow.push_back(to_str(row.get<double>(col)));
                                    break;
                                }
                                case dt_integer:
                                {
                                    tmprow.push_back(to_str(row.get<int>(col)));
                                    break;
                                }
                                case dt_unsigned_long:
                                {
                                    tmprow.push_back(to_str(row.get<unsigned long>(col)));
                                    break;
                                }
                                case dt_long_long:
                                {
                                    tmprow.push_back(to_str(static_cast<num64> (row.get<long long>(col))));
                                    break;
                                }
                                default:
                                {
                                    tmprow.push_back("");
                                    break;
                                }
                            }
                        } else
                            tmprow.push_back("");
                    }
                    result.second.push_back(tmprow);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                result.first.clear();
                result.second.clear();
                return false;
            }            catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                result.first.clear();
                result.second.clear();
            }
            return false;
        }

        bool dbpsgrdriver::select_journal_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_journal_row& result) {
            try {

                clearerror();

                str_set tabnameset;
                datetime tmptime = stop;

                while (tmptime > start) {
                    std::string tn = dt_to_journaltabelname(tmptime);
                    if (tableexist(tn)) tabnameset.insert(tn);
                    incperiod(tmptime, dvnci::MONTH_TM, -1);
                }
                if ((dt_to_journaltabelname(tmptime) == dt_to_journaltabelname(start)) &&
                        (tabnameset.find(dt_to_journaltabelname(start)) == tabnameset.end())) {
                    if (tableexist(dt_to_journaltabelname(start))) tabnameset.insert(dt_to_journaltabelname(start));
                }

                if (tabnameset.empty()) {
                    result.clear();
                    return true;
                }

                std::string req_ = "select * from ";
                str_set::const_iterator it = tabnameset.begin();
                if (tabnameset.size() <= 1) {
                    if (it != tabnameset.end())
                        req_ = req_ + *it + " where  tm>=" + to_str<num64 > (castnum64_from_datetime(start)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stop));
                    else {
                        result.clear();
                        return true;
                    }
                } else {

                    bool first = true;
                    for (str_set::const_iterator it = tabnameset.begin(); it != tabnameset.end(); ++it) {
                        if (first) {
                            req_ = req_ + "  " + *it;
                            first = false;
                        } else
                            req_ = req_ + " union select * from " + *it;
                        req_ = req_ + " where  tm>=" + to_str<num64 > (castnum64_from_datetime(start)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stop));
                    }
                }

                req_ = req_ + " order by tm asc ";
                DEBUG_STR_DVNCI(req_);

                std::string const& req = req_;

                soci::rowset<soci::row> rs = (sql.prepare << req);

                for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {

                    soci::row const& row = *it;

                    journal_row tmprow;
                    tmprow.index = 0; //((row.get_indicator(0)==i_ok) && (row.size()>=0)) ?  static_cast<num64>(row.get<int>(0));
                    tmprow.time = ((row.get_indicator(0) == i_ok) && (row.size() >= 0)) ? cast_datetime_fromnum64(row.get<num64>(0)) : nill_time;
                    tmprow.tag = ((row.get_indicator(1) == i_ok) && (row.size() >= 1)) ? row.get<std::string>(1) : "";
                    tmprow.text = ((row.get_indicator(2) == i_ok) && (row.size() >= 2)) ? row.get<std::string>(2) : "";
                    tmprow.agroup = ((row.get_indicator(3) == i_ok) && (row.size() >= 3)) ? row.get<std::string>(3) : "";
                    tmprow.type = ((row.get_indicator(4) == i_ok) && (row.size() >= 4)) ? static_cast<num64> (row.get<int>(4)) : 0;
                    tmprow.level = ((row.get_indicator(5) == i_ok) && (row.size() >= 5)) ? static_cast<num64> (row.get<int>(5)) : 0;
                    tmprow.value = ((row.get_indicator(6) == i_ok) && (row.size() >= 6)) ? row.get<std::string>(6) : "";
                    tmprow.user = ((row.get_indicator(7) == i_ok) && (row.size() >= 7)) ? row.get<std::string>(7) : "";

                    result.push_back(tmprow);
                }

                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                result.clear();
                return false;
            }            catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                result.clear();
            }
            return false;
        }

        bool dbpsgrdriver::select_debug_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_debug_row& result) {
            try {

                clearerror();

                str_set tabnameset;
                datetime tmptime = stop;

                while (tmptime > start) {
                    std::string tn = dt_to_debugtabelname(tmptime);
                    if (tableexist(tn)) tabnameset.insert(tn);
                    incperiod(tmptime, dvnci::MONTH_TM, -1);
                }
                if ((dt_to_debugtabelname(tmptime) == dt_to_debugtabelname(start)) &&
                        (tabnameset.find(dt_to_debugtabelname(start)) == tabnameset.end())) {
                    if (tableexist(dt_to_debugtabelname(start))) tabnameset.insert(dt_to_debugtabelname(start));
                }

                if (tabnameset.empty()) {
                    result.clear();
                    return true;
                }

                std::string req_ = "select * from ";
                str_set::const_iterator it = tabnameset.begin();
                if (tabnameset.size() <= 1) {
                    if (it != tabnameset.end())
                        req_ = req_ + *it + " where  tm>=" + to_str<num64 > (castnum64_from_datetime(start)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stop));
                    else {
                        result.clear();
                        return true;
                    }
                } else {

                    bool first = true;
                    for (str_set::const_iterator it = tabnameset.begin(); it != tabnameset.end(); ++it) {
                        if (first) {
                            req_ = req_ + "  " + *it;
                            first = false;
                        } else
                            req_ = req_ + " union select * from " + *it;
                        req_ = req_ + " where  tm>=" + to_str<num64 > (castnum64_from_datetime(start)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stop));
                    }
                }

                //req_ =req_ + " where  tm>=" + to_str<num64 > (castnum64_from_datetime(start)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stop)) + " order by tm asc";
                req_ = req_ + " order by tm asc ";
                DEBUG_STR_DVNCI(req_);

                std::string const& req = req_;

                soci::rowset<soci::row> rs = (sql.prepare << req);

                for (soci::rowset<soci::row>::const_iterator it = rs.begin(); it != rs.end(); ++it) {

                    soci::row const& row = *it;

                    debug_row tmprow;
                    tmprow.time = ((row.get_indicator(0) == i_ok) && (row.size() >= 0)) ? cast_datetime_fromnum64(row.get<num64>(0)) : nill_time;
                    tmprow.message = ((row.get_indicator(1) == i_ok) && (row.size() >= 1)) ? row.get<std::string>(1) : "";
                    tmprow.appid = ((row.get_indicator(2) == i_ok) && (row.size() >= 2)) ? static_cast<num64> (row.get<int>(2)) : 0;
                    tmprow.level = ((row.get_indicator(3) == i_ok) && (row.size() >= 3)) ? static_cast<num64> (row.get<int>(3)) : 0;


                    result.push_back(tmprow);
                }

                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                result.clear();
                return false;
            }            catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                result.clear();
            }
            return false;
        }

        bool dbpsgrdriver::select_lastreporttime_impl(num32 id, num32 type, dvnci::datetime& tm) {
            try {

                clearerror();
                soci::indicator ind;
                num64 tmptm;
                std::string tn = dt_to_reporttabelname(tm, type);
                if (!tableexist(tn)) return false;
                std::string const& req = "select max(tm) from " + tn + "  tm where cod=" + dvnci::to_str<num32 > (id);
                sql << req, into(tmptm, ind);
                if (sql.got_data()) {
                    switch (ind) {
                        case soci::i_ok:
                        {
                            tm = cast_datetime_fromnum64(tmptm);
                            return true;
                        }
                        default: return false;
                    }
                }
                return false;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::select_trend_statistic_impl(num32 id, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) {
            try {

                clearerror();
                str_set tabnameset;
                datetime tmptime = stoptime;
                while (tmptime > starttime) {
                    std::string tn = dt_to_trendtabelname(tmptime);
                    if (tableexist(tn))
                        tabnameset.insert(tn);
                    else {
                        DEBUG_STR_VAL_DVNCI(NOTEXISTS, tn);
                        DEBUG_STR_VAL_DVNCI(ex_write, ex_write)
                    }
                    incperiod(tmptime, dvnci::DAY_TM, -1);
                }
                if ((dt_to_trendtabelname(tmptime) == dt_to_trendtabelname(starttime)) &&
                        (tabnameset.find(dt_to_trendtabelname(starttime)) == tabnameset.end())) {
                    if (tableexist(dt_to_trendtabelname(starttime))) tabnameset.insert(dt_to_trendtabelname(starttime));
                }
                if (tabnameset.empty()) {
                    val = NULL_DOUBLE;
                    return true;
                }
                std::string req_ = "select " + preparestatisticstring(stat) + " from ";
                str_set::const_iterator it = tabnameset.begin();
                if (it != tabnameset.end()) {
                    req_ = req_ + *it;
                    ++it;
                    while (it != tabnameset.end()) {
                        req_ = req_ + " " + *it;
                        ++it;
                    }
                } else {
                    val = NULL_DOUBLE;
                    return true;
                }

                req_ = req_ + " where cod=" + dvnci::to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime)) +
                        " and val is not null";
                std::string const& req = req_;

                DEBUG_VAL_DVNCI(req)
                soci::indicator ind;
                double vltmp;

                sql << req, into(vltmp, ind);

                if (sql.got_data()) {
                    switch (ind) {
                        case soci::i_ok:
                        {
                            val = vltmp;
                            return true;
                        }
                        default:
                        {
                            val = NULL_DOUBLE;
                            return true;
                        }
                    }
                }

                val = NULL_DOUBLE;
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                val = NULL_DOUBLE;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::select_trend_impl(num32 id, const datetime& starttime, const datetime& stoptime, dvnci::dt_val_map& datamap) {
            try {

                clearerror();
                str_set tabnameset;
                datetime tmptime = stoptime;
                while (tmptime > starttime) {
                    std::string tn = dt_to_trendtabelname(tmptime);
                    if (tableexist(tn)) tabnameset.insert(tn);
                    incperiod(tmptime, dvnci::DAY_TM, -1);
                }
                if ((dt_to_trendtabelname(tmptime) == dt_to_trendtabelname(starttime)) &&
                        (tabnameset.find(dt_to_trendtabelname(starttime)) == tabnameset.end())) {
                    if (tableexist(dt_to_trendtabelname(starttime))) tabnameset.insert(dt_to_trendtabelname(starttime));
                }

                if (tabnameset.empty()) {
                    datamap.clear();
                    return true;
                }

                std::string req_ = "select tm, val from ";

                if (tabnameset.size() <= 1) {

                    str_set::const_iterator it = tabnameset.begin();

                    if (it != tabnameset.end()) {
                        req_ = req_ + *it;
                    } else {
                        datamap.clear();
                        return true;
                    }
                    req_ = req_ + " where cod=" + to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime));
                } else {
                    bool first = true;

                    for (str_set::const_iterator it = tabnameset.begin(); it != tabnameset.end(); ++it) {
                        if (first) {
                            req_ = req_ + "  " + *it;
                            first = false;
                        } else
                            req_ = req_ + " union select tm, val from " + *it;
                        req_ = req_ + " where cod=" + to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime));
                    }
                }

                std::string const& req = req_;

                DEBUG_VAL_DVNCI(req)

                        const int MAX_FETCH = 10000;

                std::vector<num64> timevect(MAX_FETCH);
                std::vector<double> valvect(MAX_FETCH);
                std::vector<soci::indicator> indvect(MAX_FETCH);

                soci::statement st = (sql.prepare << req, soci::into(timevect), soci::into(valvect, indvect));

                st.execute();

                while (st.fetch()) {
                    std::vector<num64>::iterator ittime = timevect.begin();
                    std::vector<double>::iterator itval = valvect.begin();
                    std::vector<soci::indicator>::iterator itind = indvect.begin();
                    for (; ((ittime != timevect.end()) || (itval != valvect.end()) || (itind != indvect.end())); ++ittime, ++itval, ++itind) {

                        switch (*itind) {
                            case soci::i_ok:
                            {
                                datamap.insert(dt_val_pair(cast_datetime_fromnum64(*ittime), *itval));
                            }
                            default:
                            {
                                datamap.insert(dt_val_pair(cast_datetime_fromnum64(*ittime), NULL_DOUBLE));
                            }
                        }
                    }
                    timevect.resize(MAX_FETCH);
                    valvect.resize(MAX_FETCH);
                    indvect.resize(MAX_FETCH);
                }

                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                datamap.clear();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        bool dbpsgrdriver::select_report_statistic_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) {
            try {

                clearerror();
                str_set tabnameset;
                datetime tmptime = stoptime;
                while (tmptime > starttime) {
                    std::string tn = dt_to_reporttabelname(tmptime, type);
                    if (tableexist(tn)) tabnameset.insert(tn);
                    if (!beforetabletime(tmptime, type)) break;
                }

                if ((dt_to_reporttabelname(tmptime, type) == dt_to_reporttabelname(starttime, type)) &&
                        (tabnameset.find(dt_to_reporttabelname(tmptime, type)) == tabnameset.end())) {
                    if (tableexist(dt_to_reporttabelname(starttime, type))) tabnameset.insert(dt_to_reporttabelname(starttime, type));
                }

                if (tabnameset.empty()) {
                    val = NULL_DOUBLE;
                    return true;
                }

                std::string req_ = "select " + preparestatisticstring(stat) + " from ";
                str_set::const_iterator it = tabnameset.begin();
                if (it != tabnameset.end()) {
                    req_ = req_ + *it;
                    ++it;
                    while (it != tabnameset.end()) {
                        req_ = req_ + " " + *it;
                        ++it;
                    }
                } else {
                    val = dvnci::NULL_DOUBLE;
                    return true;
                }

                req_ = req_ + " where cod=" + dvnci::to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime)) +
                        " and val is not null";
                std::string const& req = req_;

                DEBUG_VAL_DVNCI(req)
                soci::indicator ind;
                double vltmp;

                sql << req, into(vltmp, ind);

                if (sql.got_data()) {
                    switch (ind) {
                        case soci::i_ok:
                        {
                            val = vltmp;
                            return true;
                        }
                        default:
                        {
                            val = NULL_DOUBLE;
                            return true;
                        }
                    }
                }

                val = NULL_DOUBLE;
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                val = NULL_DOUBLE;
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                val = NULL_DOUBLE;
            }
            return false;
        }

        bool dbpsgrdriver::select_report_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap, size_t cnt) {
            try {

                clearerror();
                str_set tabnameset;
                datetime tmptime = stoptime;

                while (tmptime > starttime) {
                    std::string tn = dt_to_reporttabelname(tmptime, type);
                    if (tableexist(tn)) tabnameset.insert(tn);
                    if (!beforetabletime(tmptime, type)) break;
                }

                if ((dt_to_reporttabelname(tmptime, type) == dt_to_reporttabelname(starttime, type)) &&
                        (tabnameset.find(dt_to_reporttabelname(tmptime, type)) == tabnameset.end())) {
                    if (tableexist(dt_to_reporttabelname(starttime, type))) tabnameset.insert(dt_to_reporttabelname(starttime, type));
                }

                if (tabnameset.empty()) {
                    datamap.clear();
                    return true;
                }

                std::string req_ = "select tm, val from ";



                if (tabnameset.size() <= 1) {

                    str_set::const_iterator it = tabnameset.begin();

                    if (it != tabnameset.end()) {
                        req_ = req_ + *it;
                    } else {
                        datamap.clear();
                        return true;
                    }
                    req_ = req_ + " where cod=" + dvnci::to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime));
                } else {
                    bool first = true;

                    for (str_set::const_iterator it = tabnameset.begin(); it != tabnameset.end(); ++it) {
                        if (first) {
                            req_ = req_ + "  " + *it;
                            first = false;
                        } else
                            req_ = req_ + " union select tm, val from " + *it;
                        req_ = req_ + " where cod=" + dvnci::to_str<num32 > (id) + " and tm>" + to_str<num64 > (castnum64_from_datetime(starttime)) + " and tm<=" + to_str<num64 > (castnum64_from_datetime(stoptime)) + " ";
                    }
                }

                if (cnt) req_ = req_ + " order by tm desc limit " + to_str(cnt) + " ";
                std::string const& req = req_;

                DEBUG_VAL_DVNCI(req)

                        const int MAX_FETCH = 10000;

                std::vector<num64> timevect(MAX_FETCH);
                std::vector<double> valvect(MAX_FETCH);
                std::vector<soci::indicator> indvect(MAX_FETCH);

                soci::statement st = (sql.prepare << req, soci::into(timevect), soci::into(valvect, indvect));

                st.execute();

                while (st.fetch()) {
                    std::vector<num64>::iterator ittime = timevect.begin();
                    std::vector<double>::iterator itval = valvect.begin();
                    std::vector<soci::indicator>::iterator itind = indvect.begin();
                    for (; ((ittime != timevect.end()) || (itval != valvect.end()) || (itind != indvect.end())); ++ittime, ++itval, ++itind) {
                        switch (*itind) {
                            case soci::i_ok:
                            {
                                datamap.insert(dvnci::dt_val_pair(cast_datetime_fromnum64(*ittime), *itval));
                            }
                            default:
                            {
                                datamap.insert(dvnci::dt_val_pair(cast_datetime_fromnum64(*ittime), NULL_DOUBLE));
                            }
                        }
                    }
                    timevect.resize(MAX_FETCH);
                    valvect.resize(MAX_FETCH);
                    indvect.resize(MAX_FETCH);
                }

                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) {
                    error(dvncierror(ERROR_DB_REFUSECONNECTION, e.what()));
                    raisdisconnect();
                } else
                    error(dvncierror(ERROR_DB_SQLREQ, e.what()));
                datamap.clear();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                datamap.clear();
            }
            return false;
        }

        bool dbpsgrdriver::select_reports_impl(tagtype type, const datetime& tm, indx_double_map& vlmap) {
            try {

                clearerror();

                if (vlmap.empty()) return true;
                for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); it++) {
                    it->second = NULL_DOUBLE;
                }

                std::string tn = dt_to_reporttabelname(tm, type);
                if (!tableexist(tn)) return true;

                std::string valsstr = "";
                for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); it++) {
                    valsstr += ((it == vlmap.begin()) ? ("aliastbrep" + to_str(it->first) + ".val ") : (", aliastbrep" + to_str(it->first) + ".val "));
                }

                std::string req_ = "select  " + valsstr + " from ";

                for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); it++) {
                    req_ += ((it == vlmap.begin()) ? (tn + " as aliastbrep" + to_str(it->first)) : (", " + tn + " as aliastbrep" + to_str(it->first)));
                }

                req_ += " where ";

                for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); it++) {
                    if (it != vlmap.begin()) req_ += " and ";
                    req_ += ("aliastbrep" + to_str(it->first) + ".cod=" + to_str(it->first) +
                            " and aliastbrep" + to_str(it->first) + ".tm=" + to_str<num64 > (castnum64_from_datetime(tm)));
                }

                DEBUG_VAL_DVNCI(req_)

                rowset_tp rs = (sql.prepare << req_);
                for (rowset_tp::const_iterator rslt = rs.begin(); rslt != rs.end(); ++rslt) {
                    soci::row const& rslt_row = *rslt;
                    size_t ind = 0;
                    for (indx_double_map::iterator it = vlmap.begin(); it != vlmap.end(); it++) {
                        if ((ind < rslt_row.size()) && (rslt_row.get_indicator(ind) == soci::i_ok)) {
                            it->second = rslt_row.get<double>(ind);
                        }
                        ind++;
                    }
                    return true;
                }

                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

        /* bool dbpsgrdriver::select_exprassion_impl(num32 id, num32 type, const std::string& krn_st, const std::string& case_st, const str_indx_map& stringidset, const dvnci::datetime& tm, double& val) {
             try {
                 str_set set;
                 std::string tn = dt_to_reporttabelname(tm, type);
                 if (!tableexist(tn)) {
                     val = NULL_DOUBLE;
                     return true;}

                 std::string krn_st_tmp = krn_st;
                 std::string case_st_tmp = case_st;

                 for (str_indx_map::const_iterator itst = stringidset.begin(); itst != stringidset.end(); ++itst) {
                     boost::replace_all(krn_st_tmp, itst->first, std::string(itst->first + "_aliastab.val"));
                     boost::replace_all(case_st_tmp, itst->first, std::string(itst->first + "_aliastab.val"));}

                 std::string req_ = "select (" + krn_st_tmp + ") from "; //+ tn + " ";

                 for (str_indx_map::const_iterator ittb = stringidset.begin(); ittb != stringidset.end(); ++ittb) {
                     if (ittb == stringidset.begin()) req_ = req_ + " " + tn + " as " + ittb->first + "_aliastab";
                     else req_ = req_ + ",  " + tn + " as " + ittb->first + "_aliastab";}

                 req_ = req_ + " where ";

                 for (str_indx_map::const_iterator it = stringidset.begin(); it != stringidset.end(); ++it) {
                     indx subid = it->second;
                     if (subid < 0) {
                         val = NULL_DOUBLE;
                         return false;}
                     if (it == stringidset.begin()) {
                         req_ = req_ + " " + it->first + "_aliastab.cod=" + to_str(subid) + " and " + it->first + "_aliastab.tm=" + to_str<num64 > (castnum64_from_datetime(tm));}
                     else {
                         req_ = req_ + " and " + it->first + "_aliastab.cod=" + to_str(subid) + " and " + it->first + "_aliastab.tm=" + to_str<num64 > (castnum64_from_datetime(tm));};}

                 if (case_st_tmp != "") req_ = req_ + " and " + case_st_tmp;


                 std::string const& req = req_;

                 DEBUG_VAL_DVNCI(req)
                 soci::indicator ind;
                 double vltmp;

                 sql << req, into(vltmp, ind);

                 if (sql.got_data()) {
                     switch (ind) {
                         case soci::i_ok:{
                             val = vltmp;
                             return true;}
                         default:{
                             val = NULL_DOUBLE;
                             return true;}}}

                 val = NULL_DOUBLE;
                 return true;}
             catch (soci::soci_error const & e) {
                 DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                 if (e.code()==LOOSING_CONNECTEON) raisdisconnect();
                 val = NULL_DOUBLE;
                 return false;}
             catch (...) {
                 DEBUG_STR_DVNCI(UNDEFDBERROR);
                 val = NULL_DOUBLE;}
                 return false;}*/

        bool dbpsgrdriver::insert_trendef_impl(const str_trenddef_map& vl) {
            try {

                clearerror();
                if (!tableexist(TRENDDEF_TABLE))
                    createtrenddef();
                num32 cod = 0;
                std::string name = "";
                std::string comment = "";
                std::string eu = "";
                num32 type = 0;
                double mineu = 0;
                double maxeu = 0;
                num32 onmsg = 0;
                num32 offmsg = 0;
                num32 allmsg = 0;
                num32 logged = 0;
                soci::statement stmnt = (sql.prepare << "insert into " + TRENDDEF_TABLE + " (cod, iname, mineu, maxeu, type , icomment, eu, onmsg, offmsg, almsg, logged) "
                        "values(:cod, :name, :mineu, :maxeu,  :type , :comment, :eu, :onmsg, :offmsg, :almsg, :logged)",
                        soci::use(cod), soci::use(name), soci::use(mineu), soci::use(maxeu), soci::use(type), soci::use(comment),
                        soci::use(eu), soci::use(onmsg), soci::use(offmsg), soci::use(allmsg), soci::use(logged));
                for (str_trenddef_map::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                    cod = static_cast<num32> (it->second.cod);
                    name = it->second.name;
                    comment = it->second.comment;
                    eu = it->second.eu;
                    type = static_cast<num32> (it->second.type);
                    mineu = it->second.mineu;
                    maxeu = it->second.maxeu;
                    onmsg = it->second.onmsg;
                    offmsg = it->second.offmsg;
                    allmsg = it->second.almsg;
                    logged = it->second.logged;
                    stmnt.execute(true);
                }
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
                return false;
            }
        }

        bool dbpsgrdriver::connect() {
            if (isconnected()) disconnect();
            try {

                clearerror();
                DEBUG_STR_DVNCI(connection_string())
#ifdef _MSC_VER
                        sql.open(postgresql, connection_string());
#else
                        sql.open("postgresql", connection_string());
#endif
                state_ = st_connected;
                init();
                return true;
            } catch (soci::soci_error const & e) {
                error(dvncierror(ERROR_DB_NOCONNECTION, e.what()));
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
            } catch (...) {
                error(ERROR_DB_NODEF);
                state_ = st_disconnected;
                return false;
            }
            return true;
        }

        bool dbpsgrdriver::disconnect() {
            if (!isconnected()) return true;
            try {

                clearerror();
                sql.close();
                state_ = st_disconnected;
                return true;
            } catch (...) {
                return false;
            }
        }

        bool dbpsgrdriver::insert_trendef_item(num32 id, const std::string& tg, const std::string& comment, const std::string& eu, double mineu, double maxeu,
                num32 type, bool onmsg, bool offmsg, bool almsg, bool logged) {
            try {
                if (!tableexist(TRENDDEF_TABLE))
                    createtrenddef();
                num32 const& tmp_type = static_cast<num32> (type);
                num32 const& tmp_onmsg = static_cast<num32> (onmsg);
                num32 const& tmp_offmsg = static_cast<num32> (offmsg);
                num32 const& tmp_almsg = static_cast<num32> (almsg);
                num32 const& tmp_logged = static_cast<num32> (logged);
                std::string const& req = "insert into " + TRENDDEF_TABLE + " (cod, iname, mineu, maxeu, type , icomment, eu, onmsg, offmsg, almsg, logged) "
                        "values(:cod, :name, :mineu, :maxeu,  :type , :comment, :eu, :onmsg, :offmsg, :almsg, :logged)";
                sql << req, use(id), use(tg), use(mineu), use(maxeu), use(tmp_type), use(comment), use(eu), use(tmp_onmsg), use(tmp_offmsg), use(tmp_almsg), use(tmp_logged);
                return true;
            } catch (soci::soci_error const & e) {
                DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());
                if (e.code() == UNIQUE_VIOLATION) return false;
                if (e.code() == LOOSING_CONNECTEON) raisdisconnect();
                return false;
            } catch (...) {
                DEBUG_STR_DVNCI(UNDEFDBERROR);
                error(ERROR_DB_NODEF);
            }
            return false;
        }

    }
}