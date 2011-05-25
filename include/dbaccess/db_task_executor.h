/* 
 * File:   db_task_executor.h
 * Author: Serg
 *
 * Created on 17 Август 2010 г., 12:22
 */

#ifndef DB_TASK_EXECUTOR_H
#define	DB_TASK_EXECUTOR_H



#include <kernel/systemutil.h>

#include <dbaccess/dbconnectionfactory.h>


namespace dvnci {
    namespace database {

        template <typename ResolveHandler>
        struct db_task_unit {

            db_task_unit() {};

            db_task_unit(std::string tag_, dvnci::onum type_, dvnci::datetime starttime_,
                    dvnci::datetime stoptime_, ResolveHandler * handler_) : tag(tag_), type(type_), starttime(starttime_), stoptime(stoptime_), handler(handler_) {};
            std::string tag;
            dvnci::onum type;
            dvnci::datetime starttime;
            dvnci::datetime stoptime;
            ResolveHandler*  handler;} ;

        template <typename ResolveHandler>
        class db_task_executor : public dvnci::executable {
            typedef typename std::deque<db_task_unit<ResolveHandler> > taskdeque;
            
            //static const size_t READBUFFERSIZE = 100;

        public:

            db_task_executor(dvnci::num32 provider_type, std::string constr) : dvnci::executable() {
                provider = provider_type;
                connectstring = constr;}

            virtual ~db_task_executor() {};

            void addtask(std::string tag_, dvnci::onum type_, dvnci::datetime starttime_,
                    dvnci::datetime stoptime_, ResolveHandler* handler_) {
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(add report task)
                db_task_unit<ResolveHandler> task(tag_, type_, starttime_, stoptime_, handler_);
                tasks.push_back(task);}

            bool gettask(db_task_unit<ResolveHandler>& task) {
                THD_EXCLUSIVE_LOCK(mtx);
                if (tasks.empty()) return false;
                DEBUG_STR_DVNCI(get report task)
                task = tasks.front();
                tasks.pop_front();
                return true;}

            virtual bool operator()() {
                db_task_unit<ResolveHandler> temp_task;
                while (!terminated()) {
                    boost::xtime xt_loop;
                    if (init()) {
                        if (gettask(temp_task)) {
                            dvnci::dt_val_map datamap;
                            datamap.clear();
                            if (temp_task.handler) {
                                THD_EXCLUSIVE_LOCK(temp_task.handler->mtx);
                                if (dbdriver->select_report(0, temp_task.type, temp_task.starttime, temp_task.stoptime, datamap)) {
                                    temp_task.handler->report_executed(temp_task.tag, datamap);}
                                else
                                    temp_task.handler->report_executed(temp_task.tag, datamap);}}
                        addmillisec_to_now(xt_loop, 100);}
                    else
                        addmillisec_to_now(xt_loop, 1000);
                    boost::thread::sleep(xt_loop);}
                uninit();
                return true;}

        protected:

            virtual bool initialize() {
                dbdriver = bdconnectionfactory::build(provider, connectstring);
                if (!dbdriver) return false;
                dbdriver->connect();
                if (!dbdriver->isconnected()) return false;
                return true;}

            virtual bool uninitialize() {
                if (dbdriver) {
                    if (dbdriver->isconnected()) dbdriver->disconnect();}
                return true;}
        private:

            db_task_executor(const db_task_executor& orig) {};

            dvnci::num32        provider;
            std::string         connectstring;
            dbdriver_ptr        dbdriver;
            boost::mutex        mtx;
            taskdeque           tasks;} ;}}

#endif	/* DB_TASK_EXECUTOR_H */

