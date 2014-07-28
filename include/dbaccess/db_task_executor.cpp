/* 
 * File:   db_task_executor.cpp
 * Author: Serg
 * 
 * Created on 17 Август 2010 г., 12:22
 */

#include <dbaccess/db_task_executor.h>


namespace dvnci {
namespace database {
    
            bool db_task_executor::insert_trend_task(trend_db_task_ptr val) {
                if (connecting_)
                    return false;
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(addtrendtask)
                trend_tasks.push_back(val);
                return true;}
            
            bool db_task_executor::insert_report_task(report_db_task_ptr val) {
                if (connecting_)
                    return false;
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(addreporttask)
                report_tasks.push_back(val);
                return true;}    
            
            bool db_task_executor::insert_select_task(select_db_task_ptr val) {
                if (connecting_)
                    return false;
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(addselecttask)
                select_tasks.push_back(val);
                return true;}   
            
            bool db_task_executor::insert_journal_task(select_db_journal_task_ptr val) {
                if (connecting_)
                    return false;
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(addjournaltask)
                journal_tasks.push_back(val);
                return true;} 
            
            bool db_task_executor::insert_debug_task(select_db_debug_task_ptr val) {
                if (connecting_)
                    return false;
                THD_EXCLUSIVE_LOCK(mtx);
                DEBUG_STR_DVNCI(adddebugtask)
                debug_tasks.push_back(val);
                return true;}         
            
            bool db_task_executor::operator()() {
                while (!terminated()) {
                    boost::xtime xt_loop;
                    if (init()) {
                        if (execute_trend_task()) {addmillisec_to_now(xt_loop, 100); continue;}
                        if (execute_report_task()) {addmillisec_to_now(xt_loop, 100); continue;}
                        if (execute_select_task()) {addmillisec_to_now(xt_loop, 100); continue;}
                        if (execute_journal_task()) {addmillisec_to_now(xt_loop, 100); continue;}
                        if (execute_debug_task()) {addmillisec_to_now(xt_loop, 100); continue;}                        
                        addmillisec_to_now(xt_loop, 100);}
                    else
                        addmillisec_to_now(xt_loop, 1000);
                    boost::thread::sleep(xt_loop);}
                uninit();
                return true;}

            bool db_task_executor::call() {
                THD_EXCLUSIVE_LOCK(mtx);
                for (root_db_task_iterator it = prepared_tasks.begin(); it != prepared_tasks.end(); ++it) {
                    (*it)->execute();}
                prepared_tasks.clear();
                return true;} 
            
            bool db_task_executor::disconnect(){
                THD_EXCLUSIVE_LOCK(mtx);
                if (dbdriver && dbdriver->isconnected()){
                    dbdriver->disconnect();
                }
                return true;
                
            }            
            
            
            
            bool db_task_executor::initialize() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (!conntask_) 
                    return false;
                if (!dbdriver)
                    dbdriver = bdconnectionfactory::build(conntask_->provider(), conntask_->connectstring());
                if (dbdriver && dbdriver->connect() && dbdriver->isconnected()) {
                    connecting_ = false;
                    if (conntask_->trenddef() && dbdriver->select_trenddef()) {
                        trenddef = dbdriver->trenddef();
                        conntask_->error(SUCCESS);
                        conntask_->set(trenddef);
                        conntask_->executor(const_cast<db_task_executor*>(this));
                        prepared_tasks.push_back(conntask_);
                        conntask_=connect_db_task_ptr();
                        return true;}
                    else {
                        conntask_->error(conntask_->trenddef() ? NOTRENDEF : SUCCESS);
                        conntask_->executor(const_cast<db_task_executor*>(this));
                        prepared_tasks.push_back(conntask_);
                        conntask_=connect_db_task_ptr();
                        return true;}}
                else {
                    if (dvnci::abs(secondsbetween(now(), createtime_)) > conntask_->timeout()) {
                        conntask_->error( dbdriver ? dbdriver->error() : dvncierror(ERROR_DB_NOPROVIDER) );
                        prepared_tasks.push_back(conntask_);
                        conntask_=connect_db_task_ptr();
                        return false;}}
                return false;}

            bool db_task_executor::uninitialize() {
                THD_EXCLUSIVE_LOCK(mtx);
                if (dbdriver) {
                    if (dbdriver->isconnected()) dbdriver->disconnect();}
                return true;}

            bool db_task_executor::execute_trend_task() {
                trend_db_task_ptr task;{
                    THD_EXCLUSIVE_LOCK(mtx);
                    if (!dbdriver->isconnected() || trend_tasks.empty()) return false;
                    task = trend_tasks.front();
                    trend_tasks.pop_front();}

            result_trend_pair_map results;
            for (str_set::const_iterator key = task->tags().begin(); key != task->tags().end(); ++key) {
                str_trenddef_map::iterator it = trenddef.find(*key);
                resultheader_item tmp;
                dt_val_map_ptr datamap = dt_val_map_ptr(new dt_val_map());
                tmp.name = *key;
                if (it == trenddef.end()) {
                    tmp.error = NOINDEX;
                    tmp.cod = -1;}
                else {
                    bool success = dbdriver->select_trend(it->second.cod, task->start(), task->stop(), *datamap);
                    if (success && (dbdriver->error().code() != ERROR_DB_REFUSECONNECTION)) {
                        tmp.error = (dbdriver->select_trend(it->second.cod, task->start(), task->stop(), *datamap)) ? SUCCESS : NOINDEX;
                        tmp.cod = it->second.cod;
                        tmp.comment = it->second.comment;
                        tmp.eu = it->second.eu;
                        tmp.mineu = it->second.mineu;
                        tmp.maxeu = it->second.maxeu;
                        results.insert(result_trend_pair(tmp, datamap));}
                    else {
                        task->error(dbdriver->error());
                        {
                            THD_EXCLUSIVE_LOCK(mtx);
                            prepared_tasks.push_back(task);
                        }
                        return true;}}}

            task->set(results);
            task->error(SUCCESS);
            {
                THD_EXCLUSIVE_LOCK(mtx);
                prepared_tasks.push_back(task);
            }
            return true;}
            
            bool db_task_executor::execute_report_task() {
                report_db_task_ptr task;{
                    THD_EXCLUSIVE_LOCK(mtx);
                    if (!dbdriver->isconnected() || report_tasks.empty()) return false;
                    task = report_tasks.front();
                    report_tasks.pop_front();}
                
                result_trend_pair_map results;
            for (str_set::const_iterator key = task->tags().begin(); key != task->tags().end(); ++key) {
                str_trenddef_map::iterator it = trenddef.find(*key);
                resultheader_item tmp;
                dt_val_map_ptr datamap = dt_val_map_ptr(new dt_val_map());
                tmp.name = *key;
                if (it == trenddef.end()) {
                    tmp.error = NOINDEX;
                    tmp.cod = -1;}
                else {
                    bool success = dbdriver->select_report(it->second.cod, it->second.type, task->start(), task->stop(), *datamap);
                    if (success && (dbdriver->error().code() != ERROR_DB_REFUSECONNECTION)) {
                        tmp.error = dbdriver->error();
                        tmp.cod = it->second.cod;
                        tmp.comment = it->second.comment;
                        tmp.eu = it->second.eu;
                        tmp.mineu = it->second.mineu;
                        tmp.maxeu = it->second.maxeu;
                        results.insert(result_trend_pair(tmp, datamap));
                    }
                    else {
                        task->error(dbdriver->error());
                        {
                            THD_EXCLUSIVE_LOCK(mtx);
                            prepared_tasks.push_back(task);
                        }
                        return true;}}}
            task->set(results);
            task->error(SUCCESS);
            {
                THD_EXCLUSIVE_LOCK(mtx);
                prepared_tasks.push_back(task);
            }
            return true;} 
            
            bool db_task_executor::execute_select_task() {
                select_db_task_ptr task;{
                    THD_EXCLUSIVE_LOCK(mtx);
                    if (!dbdriver->isconnected() || select_tasks.empty()) return false;
                    task = select_tasks.front();
                    select_tasks.pop_front();}
               
                    sql_result_ptr result=sql_result_ptr(new sql_result());

                    dvncierror error = (dbdriver->select(task->req(), *result)) ? dvncierror() : dbdriver->error();

                task->set(result);
                task->error(error);{
                    THD_EXCLUSIVE_LOCK(mtx);
                    prepared_tasks.push_back(task);}
                return true;}   
            
            bool db_task_executor::execute_journal_task() {
                select_db_journal_task_ptr task;{
                    THD_EXCLUSIVE_LOCK(mtx);
                    if (!dbdriver->isconnected() || journal_tasks.empty()) return false;
                    task = journal_tasks.front();
                    journal_tasks.pop_front();}
               
                    vect_journal_row_ptr result=vect_journal_row_ptr(new vect_journal_row());

                    dvncierror error = (dbdriver->select_journal(task->start(), task->stop(), task->filter(),  *result)) ? dvncierror() : dbdriver->error();

                task->set(result);
                task->error(error);{
                    THD_EXCLUSIVE_LOCK(mtx);
                    prepared_tasks.push_back(task);}
                return true;}    
            
            bool db_task_executor::execute_debug_task() {
                select_db_debug_task_ptr task;{
                    THD_EXCLUSIVE_LOCK(mtx);
                    if (!dbdriver->isconnected() || debug_tasks.empty()) return false;
                    task = debug_tasks.front();
                    debug_tasks.pop_front();}
               
                    vect_debug_row_ptr result=vect_debug_row_ptr(new vect_debug_row());

                    dvncierror error = (dbdriver->select_debug(task->start(), task->stop(), task->filter(),  *result)) ? dvncierror() : dbdriver->error();

                task->set(result);
                task->error(error);{
                    THD_EXCLUSIVE_LOCK(mtx);
                    prepared_tasks.push_back(task);}
                return true;}             
    
    

}}
