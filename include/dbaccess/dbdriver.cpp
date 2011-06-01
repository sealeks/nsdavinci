/* 
 * File:   dbdriver.cpp
 * Author: Serg
 * 
 * Created on 11 Май 2010 г., 15:31
 */

#include <dbaccess/dbdriver.h>


namespace dvnci {
namespace database {


       bool dbdriver::select_trenddef(str_trenddef_map& val) {
                val.clear();
                if (!isconnected()) {
                    connect();
                    if (!isconnected()) return false;}
                if (tableexist(TRENDDEF_TABLE)) {
                    try {
                        std::string const& req = "select * from " + TRENDDEF_TABLE;
                        rowset_tp rs = (sql.prepare << req);
                        for (rowset_tp::const_iterator it = rs.begin(); it != rs.end(); ++it) {
                            trenddef_item tmp;
                            soci::row const& row = *it;
                            tmp.cod = row.get<int>(0);
                            std::string tmpname = row.get<std::string > (1);
                            dvnci::lower_and_trim(tmpname);
                            tmp.name = tmpname;
                            tmp.comment = row.get<std::string > (2); //  icomment
                            tmp.eu = row.get<std::string > (3); //  iname
                            tmp.mineu = row.get<double>(4); //  mineu
                            tmp.maxeu = row.get<double>(5); //  maxeu
                            tmp.type = static_cast<onum> (row.get<double>(6)); //  type
                            tmp.onmsg = (row.get<int>(7) != 0); //  onmsg
                            tmp.offmsg = (row.get<int>(8) != 0); //  offmsg
                            tmp.almsg = (row.get<int>(9) != 0); //  almsg
                            tmp.logged = (row.get<int>(10) != 0); //  logged
                            std::string tmp_name = tmp.name;
                            dvnci::lower_and_trim(tmp_name);
                            val.insert(str_trenddef_pair(tmp_name, tmp));}
                       return true;}
                    catch (soci::soci_error const & e) {
                        DEBUG_STR_VAL_DVNCI(ERRORRR, e.what());}
                    catch (...) {
                        DEBUG_STR_DVNCI(UNDEFDBERROR);}}
                  return false;}

             bool dbdriver::insert_report(indx id, tagtype type, const dt_val_map& values) {
                if (values.empty()) return true;
                if ((values.size()==1) || (dt_to_reporttabelname(values.begin()->first, type)==dt_to_reporttabelname(values.rbegin()->first, type))){
                      return  insert_report_impl(static_cast<num32> (id),type,  values);}
                else{
                    for (dt_val_map::const_iterator it=values.begin();it!=values.end();++it){
                        insert_report(id, type, it->second, it->first);}
                    return true;}
                return false;}
       
       
            bool dbdriver::insert_journal(const journal_item_vect& vctval) {
                if (vctval.empty()) return true;
                if ((vctval.size()==1) || (dt_to_journaltabelname(cast_datetime_fromnum64(vctval.begin()->time))==
                          dt_to_journaltabelname(cast_datetime_fromnum64(vctval.rbegin()->time)))){
                   return insert_journal_impl(vctval);}
                else{
                   for(journal_item_vect::const_iterator it=vctval.begin();it!=vctval.end();++it){
                       insert_journal(cast_datetime_fromnum64(it->time),it->tag,it->text,it->agroup,static_cast<msgtype>(it->type),static_cast<altype>(it->level),
                               it->value, it->user, "");}}
                return true;}

            bool dbdriver::insert_debug(const debug_item_vect& vctval) {
                if (vctval.empty()) return false;
                if ((vctval.size()==1) || (dt_to_debugtabelname(cast_datetime_fromnum64(vctval.begin()->time))==
                          dt_to_debugtabelname(cast_datetime_fromnum64(vctval.rbegin()->time)))){
                   return insert_debug_impl(vctval);}
                else{
                   for(debug_item_vect::const_iterator it=vctval.begin();it!=vctval.end();++it){
                       insert_debug(cast_datetime_fromnum64(it->time),it->message,static_cast<appidtype>(it->appid),static_cast<debuglvtype>(it->level));}}
                return true;}


       // последние данные в таблице отчетов

            bool dbdriver::select_lastreporttime(indx id, tagtype type, reporthisttype present, dvnci::datetime& tm) {
                if (tm.is_special()) tm = dvnci::now();
                datetime tmtmp = tm;
                normilize_history_bound(type, present);
                datetime tm_reporttable = tm;
                normalizereporttime(tmtmp, type);
                increporttime(tmtmp, type, -present);
                if (id == npos) {
                    tm = tmtmp;
                    return false;}
                while (tmtmp < tm_reporttable) {
                    if (select_lastreporttime_impl(static_cast<num32> (id), static_cast<num32> (type), tm_reporttable)) {
                        normalizereporttime(tm_reporttable, type);
                        increporttime(tm_reporttable, type, 1);
                        tm = tm_reporttable;
                        return true;}
                    if (!beforetabletime(tm_reporttable, type)) {
                        tm = tmtmp;
                        return true;}}
                tm = tmtmp;
                return true;}

            bool dbdriver::select_lastreporttime(indx id, tagtype type, reporthisttype present, dvnci::datetime& tm, dt_val_map& values, size_t cnt) {
                if (select_lastreporttime(id, type, present, tm)){
                    datetime starttime = tm;
                    datetime stoptime = tm;
                    if (beforetabletime(starttime, type)){
                         if (select_report(id, type, starttime, stoptime, values, cnt)){}
                         return true;}}
                return false;}


            //отчетная статистика по параметру  на основе данных по графикам

            bool dbdriver::select_trend_statistic(num32 id, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) {
                DEBUG_STR_DVNCI(getTrendStatistic);
                val = NULL_DOUBLE;
                if (stat == REPORT_STATISTIC_INTEG) {
                    dt_val_map datamap;
                    if (select_trend_impl(id, starttime, stoptime, datamap)) {
                         dt_val_map::iterator it=datamap.begin();
                         while (it!=datamap.end()){
                                if (it->second!=it->second)
                                    datamap.erase(it++);
                                else
                                    ++it;}
                         if (datamap.empty()) {
                            return true;}                       
                         dt_val_pair strtval=std::make_pair(starttime, datamap.begin()->second);
                         dt_val_pair stpval=std::make_pair(stoptime, datamap.rbegin()->second);
                         datamap.insert(strtval);
                         datamap.insert(stpval);
                         integr_statistic_functor stfctr(strtval);
                         std::for_each<dt_val_map::const_iterator, integr_statistic_functor&>(datamap.begin(),datamap.end(),stfctr);
                         val=stfctr.countedvalue();
                         DEBUG_STR_VAL_DVNCI(COUNTBYBASEBUFFER INTEGR TREND, val);
                         return true;}
                    else {
                        return false;}}
                else {
                    return select_trend_statistic_impl(id, starttime, stoptime, stat, val);}
                return false;}


            bool dbdriver::drop_archive(int val) {
                if (val < 0) return true;
                int tmp = val < 1 ? 6 : val;

                // очистка трендов
                dvnci::datetime tm = dvnci::incmonth(dvnci::now(), -tmp);
                tm = dvnci::incday(tm, -1);
                for (int i = 0; i < 10; ++i) {
                    droptrtable(tm);
                    tm = dvnci::incday(tm, -1);}

                // очистка журнала
                tm = dvnci::incmonth(dvnci::now(), 1 - tmp);
                dropaltable(tm);

                // очистка отчетов
                tm = dvnci::incyear(dvnci::now(), -tmp);
                tm = dvnci::incmonth(tm, -1);
                dropreptable(tm);
                return true;}

       bool dbdriver::droptable(std::string tn) {
                try {
                    std::string const& rq = "drop table " + tn;
                    sql << rq;
                    lower_and_trim(tn);
                    dbtableset_set::iterator it = tables_.find(tn);
                    if (tables_.find(tn) != tables_.end()) tables_.erase(it);
                    return true;}
                catch (...) {
                    return false;}
                return true;}

    
    
       void dbdriver::property(const std::string& val) {
                if (prop_!=val) {
                str_vect vect;
                std::string tmp;
                split_str(val, ";", vect);
                for (str_vect::iterator it = vect.begin(); it != vect.end(); ++it) {
                    if (read_property_by_name(*it, "server=", tmp)) {
                        std::string lstr, rstr;
                        split_2str(tmp, ":", lstr, rstr);
                        if (rstr == "") server_=tmp;
                        else {
                            server_=lstr;
                            port_=rstr;}}
                    if (read_property_by_name(*it, "database=", tmp)) database_=tmp;
                    if (read_property_by_name(*it, "user=", tmp)) user_=tmp;
                    if (read_property_by_name(*it, "password=", tmp)) password_=tmp;}
                prop_=val;
                if (isconnected()) {
                    try{
                    if (disconnect()){
                        if (!isnull_property()) connect();}}
                     catch(...){}}}}


       bool dbdriver::read_property_by_name(std::string src, const std::string& prop, std::string& val) {
                if (boost::algorithm::find_first(src, prop)) {
                    boost::algorithm::replace_first(src, prop.c_str(), "");
                    if (src != "") {
                        val = src;
                        return true;}}
                return false;}

}}
