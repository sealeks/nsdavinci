/* 
 * File:   db_task_executor.h
 * Author: Serg
 *
 * Created on 17 РђРІРіСѓСЃС‚ 2010 Рі., 12:22
 */

#ifndef DB_TASK_EXECUTOR_H
#define	DB_TASK_EXECUTOR_H



#include <kernel/systemutil.h>

#include <dbaccess/dbconnectionfactory.h>


namespace dvnci {
    namespace database {

        class root_db_task {
        public:

            root_db_task() {};

            ~root_db_task() {};
            virtual bool execute() = 0;

            dvnci::dvncierror error() const {
                return error_;}

            void error(const dvnci::dvncierror& val) {
                error_ = val;}

        protected:
            dvnci::dvncierror error_;} ;

        typedef boost::shared_ptr<root_db_task>          root_db_task_ptr;

        template<typename VALUETYPE>
        class template_db_task : public root_db_task {
        public:

            typedef VALUETYPE    valuetype;

            template_db_task() : root_db_task() {}

            virtual void event(const valuetype& val, const dvnci::dvncierror& error) = 0;

            virtual bool execute() {
                event(value_, error_);
                return true;}

            virtual bool set(const valuetype& val) {
                value_ = val;
                return true;}

        protected:
            valuetype       value_;} ;
            
        class db_task_executor;   

        class connect_db_task : public template_db_task<str_trenddef_map> {
        public:

            connect_db_task(num32 provider, const std::string& connectstring, bool trenddef = false, num32 timeout = 15) : template_db_task<str_trenddef_map>(),
            provider_(provider), connectstring_(connectstring), trenddef_(trenddef), timeout_(timeout), executor_(0) {};

            num32 provider() const {
                return provider_;}

            std::string connectstring() const {
                return connectstring_;}
            
            bool trenddef() const {
                return trenddef_;}            

            num32 timeout() const {
                return timeout_;}
            
            db_task_executor* executor() const {
                return executor_;}            
           
            void executor(db_task_executor* val) {
                executor_=val;}               

        private:

            num32 provider_;
            std::string connectstring_;
            bool trenddef_;
            num32 timeout_;
            db_task_executor* executor_;
} ;

        typedef boost::shared_ptr<connect_db_task>          connect_db_task_ptr;

        class disconnect_db_task : public template_db_task<bool> {
        public:

            disconnect_db_task() : template_db_task<bool>() {};} ;

        typedef boost::shared_ptr<disconnect_db_task>          disconnect_db_task_ptr;
        
        
        
        

        class trend_db_task : public template_db_task<result_trend_pair_map> {
        public:

            trend_db_task(const str_set& tags, dvnci::datetime start,
                    dvnci::datetime stop) : template_db_task<result_trend_pair_map>(), tags_(tags), start_(start), stop_(stop) {};

            const str_set& tags() const {
                return tags_;}

            dvnci::datetime start() const {
                return start_;}

            dvnci::datetime stop() const {
                return stop_;}

        private:
            str_set tags_;
            dvnci::datetime start_;
            dvnci::datetime stop_;} ;

        typedef boost::shared_ptr<trend_db_task>          trend_db_task_ptr;
        
        
        class report_db_task : public template_db_task<result_trend_pair_map> {
        public:

            report_db_task(const str_set& tags, dvnci::datetime start,
                    dvnci::datetime stop) : template_db_task<result_trend_pair_map>(), tags_(tags), start_(start), stop_(stop) {};

            const str_set& tags() const {
                return tags_;}

            dvnci::datetime start() const {
                return start_;}

            dvnci::datetime stop() const {
                return stop_;}

        private:
            str_set tags_;
            dvnci::datetime start_;
            dvnci::datetime stop_;} ;

        typedef boost::shared_ptr<report_db_task>          report_db_task_ptr;   
        
        
        
        
        class select_db_task : public template_db_task<sql_result_ptr> {
        public:

            select_db_task(const std::string& req) : template_db_task<sql_result_ptr>(), req_(req) {};

            const std::string& req() const {
                return req_;}

        private:
            std::string req_;} ;

        typedef boost::shared_ptr<select_db_task>          select_db_task_ptr;
        
        
        
        
        class select_db_journal_task : public template_db_task<vect_journal_row_ptr> {
        public:

            select_db_journal_task(dvnci::datetime start, dvnci::datetime stop, const std::string& filter = "") : 
            template_db_task<vect_journal_row_ptr>(), start_(start), stop_(stop), filter_(filter) {};

            dvnci::datetime start() const {
                return start_;}

            dvnci::datetime stop() const {
                return stop_;}            
              
            const std::string& filter() const {
                return filter_;}

        private:
            dvnci::datetime start_;
            dvnci::datetime stop_;            
            std::string filter_;} ;

        typedef boost::shared_ptr<select_db_journal_task>          select_db_journal_task_ptr;         
        
        
        class select_db_debug_task : public template_db_task<vect_debug_row_ptr> {
        public:

            select_db_debug_task(dvnci::datetime start, dvnci::datetime stop, const std::string& filter = "") : 
                  template_db_task<vect_debug_row_ptr>(), start_(start), stop_(stop), filter_(filter) {};

            dvnci::datetime start() const {
                return start_;}

            dvnci::datetime stop() const {
                return stop_;}           
            
            const std::string& filter() const {
                return filter_;}

        private:
            dvnci::datetime start_;
            dvnci::datetime stop_;            
            std::string filter_;} ;

        typedef boost::shared_ptr<select_db_debug_task>          select_db_debug_task_ptr;         
        
        
        

        class db_task_executor : public dvnci::executable {
            
            typedef std::deque<root_db_task_ptr>              root_db_task_deq;
            typedef root_db_task_deq::iterator                root_db_task_iterator;
            typedef std::deque<trend_db_task_ptr>             trend_db_task_deq;
            typedef std::deque<report_db_task_ptr>            report_db_task_deq;
            typedef std::deque<select_db_task_ptr>            select_db_task_deq; 
            typedef std::deque<select_db_journal_task_ptr>    select_db_journal_task_deq;
            typedef std::deque<select_db_debug_task_ptr>      select_db_debug_task_deq;            

        public:

            static const dvnci::ns_error SUCCESS = 0;
            static const dvnci::ns_error NOCONNECT = ERROR_DB_NOCONNECTION;
            static const dvnci::ns_error NOTRENDEF = ERROR_DB_NOTRENDDEF;
            static const dvnci::ns_error NOINDEX = ERROR_DB_NOINDEX;

            db_task_executor(connect_db_task_ptr conntask) : dvnci::executable(),
            conntask_(conntask), createtime_(now()), connecting_(true)  {}

            bool insert_trend_task(trend_db_task_ptr val);
            
            bool insert_report_task(report_db_task_ptr val); 
            
            bool insert_select_task(select_db_task_ptr val); 
            
            bool insert_journal_task(select_db_journal_task_ptr val);
            
            bool insert_debug_task(select_db_debug_task_ptr val);              

            virtual bool operator()();

            bool call();
            
            bool disconnect();

        protected:

            virtual bool initialize();

            virtual bool uninitialize();

            bool execute_trend_task();
            
            bool execute_report_task();
            
            bool execute_select_task();
            
            bool execute_journal_task(); 
            
            bool execute_debug_task();           



        private:

            db_task_executor(const db_task_executor& orig) {};

            connect_db_task_ptr         conntask_;
            dbdriver_ptr                dbdriver;
            datetime                    createtime_;
            volatile bool               connecting_;
            boost::mutex                mtx;
            str_trenddef_map            trenddef;
            trend_db_task_deq           trend_tasks;
            report_db_task_deq          report_tasks;
            select_db_task_deq          select_tasks;
            select_db_journal_task_deq  journal_tasks;
            select_db_debug_task_deq    debug_tasks;            
            root_db_task_deq            prepared_tasks;} ;

        typedef callable_shared_ptr<db_task_executor>          db_task_executor_ptr;
        
        
    }}

#endif	/* DB_TASK_EXECUTOR_H */

