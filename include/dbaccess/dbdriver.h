/* 
 * File:   dbdriver.h
 * Author: Serg
 *
 * Created on 11 Май 2010 г., 15:31
 */

#ifndef _GG_DBDRIVER_H
#define	_GG_DBDRIVER_H


#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/templ.h>
#include <kernel/error.h>
#include <kernel/short_value.h>
#include <kernel/mainstruct.h>

#include <soci/soci.h>


namespace dvnci {
    namespace database {

        const std::string TRENDDEF_TABLE = "trenddef";

        struct journal_item {
            num64        index;
            unum64       guid;
            datetime     time;
            std::string  tag;
            std::string  text;
            std::string  agroup;
            num64        type;
            num64        level;
            std::string  value;
            std::string  user;};

        typedef std::vector<journal_item>   journal_item_vect;

        struct debug_item {
           num64   index;
           unum64  guid;
           datetime   time;
           std::string  message;
           num64  level;
           num64  appid;};

        typedef std::vector<debug_item>     debug_item_vect;



        struct trenddef_item {
            indx        cod;
            std::string name;
            std::string comment;
            std::string eu;
            double      mineu;
            double      maxeu;
            tagtype     type;
            bool        onmsg;
            bool        offmsg;
            bool        almsg;
            bool        logged;};
            
        struct resultheader_item {
            indx        cod;
            std::string name;
            std::string comment;
            std::string eu;
            double      mineu;
            double      maxeu;
            ns_error    error;
            friend bool operator<(const resultheader_item& ls,const resultheader_item& rs){
                return ls.name < rs.name;}
        };
        
        
        typedef std::pair< resultheader_item, dt_val_map_ptr >                                                                  result_trend_pair;
        
        typedef std::pair< resultheader_item, dt_val_map_ptr >                                                                  result_trend_pair;
        typedef std::map<resultheader_item,  dt_val_map_ptr, std::less<resultheader_item>, std::allocator<result_trend_pair > > result_trend_pair_map;
        
        
        typedef std::pair< std::string, int >                                                                                   sql_resultheader;
        
        typedef std::vector<sql_resultheader >                                                                                  sql_header_vect;        
        typedef std::vector<str_vect >                                                                                          str_table;
        typedef std::pair< sql_header_vect, str_table >                                                                         sql_result;
        typedef boost::shared_ptr< sql_result >                                                                                 sql_result_ptr;        
        
        
            


        typedef std::pair<std::string, trenddef_item > str_trenddef_pair;
        typedef std::map<std::string,  trenddef_item, std::less<std::string>, std::allocator<str_trenddef_pair > > str_trenddef_map;

        class dbdriver {

        public:

        typedef soci::rowset<soci::row>   rowset_tp;
        typedef dvnci::str_set            dbtableset_set;
        typedef dvnci::str_vect           dbtableset_vect;

            enum state_connection {
                st_connected,
                st_disconnected} ;

            dbdriver(const std::string& conf, bool ex_write_ = false, bool trdefld = false) : ex_write(ex_write_), tablesset_init(false), state_(st_disconnected),
                   server_(""), user_(""), password_(""), schema_(""), database_(""), port_(""), prop_(""), host_(""), finit(false), trenfdefld(trdefld) {
                property(conf);};

            virtual ~dbdriver() {};

            state_connection state() const {
                return state_;}

            bool isconnected() const {
                return (state_ == st_connected);}

            std::string server() const {
                return (trim_copy(server_).empty()) ? "localhost" : server_;}

            std::string user() const  {
                return user_;}

            std::string password() const  {
                return password_;}

            std::string schema() const  {
                return schema_;}

            std::string database() const {
                return database_;}

            std::string host() const {
                return host_;}

            std::string port() const {
                return port_;}

            const str_trenddef_map&  trenddef() const {
                return trenddefmap;}

            virtual bool connect() = 0;

            virtual bool disconnect() = 0;

            void property(const std::string& val);

            bool tableexist(std::string tn) {
                lower_and_trim(tn);
                return metaexists(tn);}

            bool insert_trend(indx id, const datetime& tm, double data = NULL_DOUBLE) {
                return id != npos ? insert_trend_impl(static_cast<num32> (id), tm, data) : true;}

            bool insert_trend(const dt_val_deque& vctval) {
                return (!vctval.empty()) ? insert_trend_impl(vctval) : true;}

            bool insert_report(indx id, tagtype type, double data, const datetime& tm) {
                return id != npos ? insert_report_impl(static_cast<num32> (id), static_cast<num32> (type), data, tm) : true;}

            bool insert_report(indx id, tagtype type, const dt_val_map& values);

            bool insert_journal(const datetime& tm, const std::string& tg, const std::string& comment, const std::string& agroup,  msgtype type,
                    altype alevel, const std::string& val = "", const std::string& user = "", const std::string& host = "") {
                return insert_journal_impl(tm,  tg,  comment,  agroup, static_cast<num32> (type), static_cast<num32> (alevel), val ,  user , host);}

            bool insert_journal(const journal_item_vect& vctval);

            bool insert_debug(const datetime& tm, const std::string& message, appidtype app, debuglvtype lev){
                        return insert_debug_impl(tm, message, static_cast<num32> (app), static_cast<num32> (lev));}

            bool insert_debug(const debug_item_vect& vctval);

            bool insert_osc(const datetime tm, std::string tg, tagtype delt) {
                return true;}

            virtual bool select_trenddef(str_trenddef_map& val);

            bool select_trenddef(){
                return select_trenddef(trenddefmap);}

            virtual bool insert_trendef_item(num32 id, const std::string& tg, const std::string& comment, const std::string& eu, double mineu, double maxeu,
                              num32 type, bool onmsg, bool offmsg, bool almsg, bool logged) = 0;

            template <typename INTF>
            ns_error insert_trendef(INTF base, bool rewrite = true){
                 if (!base) return ERROR_NILLINF;
                 if (!isconnected()) {
                     connect();
                     if (!isconnected()) return ERROR_NO_DATABASE_CONN;}
                 if (rewrite) droptrenddeftable();
                 str_trenddef_map tmpmap;
                 for (indx i=0;i<base->count();++i){
                      if (base->exists(i)) {
                         short_value minval = base->mineu_shv(i);
                         short_value maxval = base->maxeu_shv(i);
                         trenddef_item itmtmp = {i, base->name(i), base->comment(i), base->eu(i) ,  minval.value<double>(),maxval.value<double>(),
                            base->type(i), base->onmsged(i), base->offmsged(i), base->alarmed(i), base->logged(i)};
                         tmpmap.insert(str_trenddef_pair(base->name(i) , itmtmp));}}

                 return insert_trendef_impl(tmpmap) ? 0 : NS_ERROR_NODEF;}
            
            bool select(const std::string& req, sql_result& result){
                return select_impl(req, result);}
            
            bool select_journal(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_journal_row& result){
                return select_journal_impl(start, stop, filter, result);}   
            
            bool select_debug(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_debug_row& result){
                return select_debug_impl(start, stop, filter, result);}            

            //отчетная статистика по параметру  на основе данных по отчетам

            bool select_report_statistic(indx id, tagtype type, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) {
                DEBUG_STR_DVNCI(getReportStatistic);
                return select_report_statistic_impl(static_cast<num32> (id), static_cast<num32> (type), starttime, stoptime, stat, val);}

            //отчетная статистика по параметру

            bool select_statistic(reportsrctype typecount, indx id, tagtype type, dvnci::datetime starttime, dvnci::datetime stoptime, num32 stat, double& val) {
                if ((typecount != REP_COUNT_BY_LOG) && (typecount != REP_COUNT_BY_REP)) return false;
                if (id == npos) return false;
                switch (typecount) {
                    case REP_COUNT_BY_LOG: return select_trend_statistic(id, starttime, stoptime, stat, val);
                    case REP_COUNT_BY_REP: return select_report_statistic(id, type, starttime, stoptime, stat, val);}
                return false;}

            // получение вычисляемых отчетных данных

            //virtual bool select_exprassion(indx id, tagtype type, const std::string& krn_st, const std::string& case_st, const str_indx_map& stringidset, const datetime& tm, double& val) {
                //if (id == npos) return false;
                //return select_exprassion_impl(static_cast<num32> (id), static_cast<num32> (type), krn_st, case_st, stringidset, tm, val);}

            virtual bool select_report(indx id, tagtype type, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap, size_t cnt = 0) {
                if (id == npos) return false;
                return select_report_impl(static_cast<num32> (id), static_cast<num32> (type), starttime, stoptime, datamap, cnt);}

            virtual bool select_reports(tagtype type, const datetime& tm, indx_double_map& vlmap) {
                vlmap.clear();
                return select_reports_impl(type, tm, vlmap);}

            virtual bool select_trend(indx id, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap){
                if (id == npos) return false;
                return select_trend_impl(static_cast<num32> (id), starttime, stoptime, datamap);}


           // последние данные в таблице отчетов

            datetime select_lastreporttime(indx id, tagtype type, reporthisttype present);
            bool select_lastreporttime(indx id, tagtype type, reporthisttype present, dt_val_map& values, size_t cnt = REPORT_BUFFER_SIZE);

            //отчетная статистика по параметру  на основе данных по графикам

            bool select_trend_statistic(num32 id, const datetime& starttime, const datetime& stoptime, num32 stat, double& val);

            bool drop_archive(int val);

        protected:

            bool             ex_write;
            bool             tablesset_init; // список таблиц запрашивался
            state_connection state_;
            soci::session    sql;
            dbtableset_set   tables_;
            indx_vect        res;

            virtual bool getmeta() = 0;

            virtual bool metaexists(const std::string& tn) = 0;

            virtual std::string connection_string() = 0;

            virtual bool createreptable(std::string tn) = 0;

            virtual bool createtrtable(std::string tn) = 0;

            virtual bool createjrnltable(std::string tn) = 0;

            virtual bool createdbgtable(std::string tn) = 0;

            virtual bool createocstable(std::string tn) {
                return false;};

            virtual bool createtrenddef() = 0;

            virtual bool insert_journal_impl(const datetime& tm, const std::string& tg, const std::string& comment, const std::string& agroup,  num32 type,
                                         num32 alevel, const std::string& val = "", const std::string& user = "", const std::string& host = "") = 0;

            virtual bool insert_journal_impl(const journal_item_vect& vctval) = 0;

            virtual bool insert_debug_impl(const datetime& tm, const std::string& message, num32 app, num32 lev) = 0;

            virtual bool insert_debug_impl(const debug_item_vect& vctval) = 0;

            virtual bool insert_trend_impl(num32 id, datetime tm, double data = NULL_DOUBLE) = 0;

            virtual bool insert_trend_impl(const dt_val_deque& vctval) = 0;

            virtual bool insert_report_impl(num32 id, num32 type, double data, const dvnci::datetime& tm) = 0;

            virtual bool insert_report_impl(num32 id, num32 type, const dt_val_map& values) = 0;

            virtual bool insert_osc_impl(const dvnci::datetime& tm, num32 id, num32 delt) {
                return false;};
                
            virtual bool select_impl(const std::string& req, sql_result& result) = 0;
            
            virtual bool select_journal_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_journal_row& result) = 0; 
            
            virtual bool select_debug_impl(dvnci::datetime start, dvnci::datetime stop, const std::string& filter, vect_debug_row& result) = 0;          

            virtual bool select_lastreporttime_impl(num32 id, num32 type, dvnci::datetime& tm) = 0;

            virtual bool select_trend_statistic_impl(num32 id, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) = 0;

            virtual bool select_trend_impl(num32 id, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap) = 0;

            virtual bool select_report_statistic_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, num32 stat, double& val) = 0;

            virtual bool select_report_impl(num32 id, num32 type, const datetime& starttime, const datetime& stoptime, dt_val_map& datamap, size_t cnt = 0) = 0;

            virtual bool select_reports_impl(tagtype type, const datetime& tm, indx_double_map& vlmap) = 0;

            //virtual bool select_exprassion_impl(num32 id, num32 type, const std::string& krn_st, const std::string& case_st, const str_indx_map& stringidset,
            //                                const dvnci::datetime& tm, double& val) = 0;

            virtual bool insert_trendef_impl(const str_trenddef_map& vl) = 0;



            virtual void init() {
                if (!finit) {
                    if (trenfdefld) select_trenddef(trenddefmap);
                    finit = true;}}

            virtual void uninit() {
                if (finit) {
                    trenddefmap.clear();
                    finit = false;}}

            void resetmeta() {
                tables_.clear();
                tablesset_init = false;}

            virtual bool droptable(std::string tn);

            bool droptrtable(const datetime& tm) {
                return droptable(dvnci::dt_to_trendtabelname(tm));}

            bool dropaltable(const datetime& tm) {
                return droptable(dvnci::dt_to_journaltabelname(tm));}

            bool dropreptable(const datetime& tm) {
                return droptable(dvnci::dt_to_reporttabelname(tm, OLD_REPORTTYPE_HOUR));}

            bool droposctable(const datetime& tm) {
                return true;};

            bool droptrenddeftable() {
                return droptable(TRENDDEF_TABLE);}

            std::string preparestatisticstring(num32 stat, std::string vl = "val") {
                switch (stat) {
                    case REPORT_STATISTIC_INTEG: return std::string("SUM(" + vl + ")");
                    case REPORT_STATISTIC_SUM: return std::string("SUM(" + vl + ")");
                    case REPORT_STATISTIC_MIN: return std::string("MIN(" + vl + ")");
                    case REPORT_STATISTIC_MAX: return std::string("MAX(" + vl + ")");}
                return std::string("AVG(" + vl + ")");}


            //            indx getid(std::string tg) {
            //                dvnci::lower_and_trim(tg);
            //                str_trenddef_map::iterator it = trenddefmap.find(tg);
            //                return (it != trenddefmap.end()) ? it->second.cod : -1;}

           bool read_property_by_name(std::string src, const std::string& prop, std::string& val);

           bool isnull_property(){
                 return ((trim_copy(database_).empty()) || (server().empty())) ;}


        private:




            std::string      server_;
            std::string      user_;
            std::string      password_;
            std::string      schema_;
            std::string      database_;
            std::string      port_;
            std::string      prop_;
            std::string      host_;
            bool             finit;
            bool             trenfdefld;
            str_trenddef_map trenddefmap;} ;}}

#endif	/* _DBDRIVER_H */

