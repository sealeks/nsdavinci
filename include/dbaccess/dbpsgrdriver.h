/* 
 * File:   dbpsgrdriver.h
 * Author: Serg
 *
 * Created on 18 Май 2010 г., 17:44
 */

#ifndef _GG_DBPSGRDRIVER_H
#define	_GG_DBPSGRDRIVER_H

#include <dbaccess/dbdriver.h>

namespace dvnci {
    namespace database {


        class dbpsgrdriver : public dbdriver {

        static const int UNIQUE_VIOLATION = 23505;
        static const int LOOSING_CONNECTEON = 0x8000;

        private:
            std::string lasttrend;
            std::string lastalarm;
            std::string lastosc;
            std::string select_lastreporttime;


        protected:

            virtual std::string connection_string();

            virtual bool getmeta();

            virtual bool metaexists(const std::string& tn);

            virtual bool createreptable(std::string tn);

            virtual bool createtrtable(std::string tn);

            virtual bool createjrnltable(std::string tn);

            virtual bool createdbgtable(std::string tn);

            virtual bool createtrenddef();

            virtual bool insert_journal_impl(const datetime& tm, const std::string& tg, const std::string& comment, const std::string& agroup,  num32 type,
                    num32 alevel, const std::string& val = 0, const std::string& user = "", const std::string& host = "");

            bool insert_journal_by_one_impl(const journal_item_vect& vctval);

            virtual bool insert_journal_impl(const journal_item_vect& vctval);

            virtual bool insert_debug_impl(const datetime& tm, const std::string& message, num32 app, num32 lev);

            bool insert_debug_by_one_imp(const debug_item_vect& vctval);

            virtual bool insert_debug_impl(const debug_item_vect& vctval);

            virtual bool insert_trend_impl(num32 id, datetime tm, double data = NULL_DOUBLE);

            virtual bool insert_trend_impl(const dt_val_deque& vctval);

            virtual bool insert_report_impl(num32 id, num32 type, double data, const dvnci::datetime& tm);

            bool insert_report_by_one_imp(num32 id, num32 type, const dt_val_map& values);

            virtual bool insert_report_impl(num32 id, num32 type, const dt_val_map& values);
            
            virtual bool select_impl(const std::string& req, sql_result& result);
            
            virtual bool select_journal_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_journal_row& result); 
            
            virtual bool select_debug_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_debug_row& result);             

            virtual bool select_lastreporttime_impl(num32 id, num32 type, dvnci::datetime& tm);

            virtual bool select_trend_statistic_impl(num32 id, const datetime& starttime, const datetime& stoptime, num32 stat, double& val);

            virtual bool select_trend_impl(num32 id, const datetime& starttime, const datetime& stoptime, dvnci::dt_val_map& datamap);

            virtual bool select_report_statistic_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, num32 stat, double& val);

            virtual bool select_report_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap, size_t cnt = 0);

            virtual bool select_reports_impl(tagtype type, const datetime& tm, indx_double_map& vlmap);

            //virtual bool select_exprassion_impl(num32 id, num32 type, const std::string& krn_st, const std::string& case_st, const str_indx_map& stringidset, const dvnci::datetime& tm, double& val);

            virtual bool insert_trendef_impl(const str_trenddef_map& vl);

            void raisdisconnect(bool throwerr = false);


        public:

            dbpsgrdriver(std::string conf, bool ex_write_ = false) : dbdriver(conf, ex_write_) {};

            virtual bool connect();

            virtual bool disconnect();
            
            virtual bool insert_trendef_item(num32 id, const std::string& tg, const std::string& comment, const std::string& eu, double mineu, double maxeu, 
                              num32 type, bool onmsg, bool offmsg, bool almsg, bool logged);

        } ;}}

#endif	/* _DBPSGRDRIVER_H */

