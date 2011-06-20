
/* 
 * File:   netintf.h
 * Author: Serg
 *
 * Created on 20 Р пїЅРЎР‹Р В»РЎРЉ 2010 Р С–., 14:24
 */

#ifndef _DVNCI_LOCALNETINTF_H
#define	_DVNCI_LOCALNETINTF_H



#include <custom/netintf.h>
#include <kernel/memfile.h>



namespace dvnci {
    namespace custom {
        namespace net {
            
            

            class localnetintf : public netintf {
                
                typedef refcounter_templ<tagsbase>                                              refcounter;
                typedef boost::shared_ptr<refcounter>                                           refcounter_ptr;
                
                
                static const size_t MAX_TASK_SIZE = 0x1000;
                static const num64  TASK_TIMOUT = 1000;
                
                
                

                struct deadbound_short_value {

                    deadbound_short_value(double dbnd = 0.0) : db_(dbnd), sh_() {}

                    ~deadbound_short_value() {}

                    const short_value & value() const {
                        return sh_;}

                    void value(const short_value & val) {
                        sh_ = val;}

                    double db() const {
                        return db_;}

                    void db(const short_value & val) {
                        sh_ = val;}

                private:
                    double db_;
                    short_value sh_;};

                typedef std::pair<indx, deadbound_short_value >          indx_deadb_shv_pair;
                typedef std::map<indx, deadbound_short_value,
                std::less<indx>, std::allocator<indx_deadb_shv_pair > >  indx_deadb_shv_map;
                
                
                
                
                
              struct report_task{
                  num64    cid;
                  datetime creatitime;
                  datetime begin;
                  datetime end;}; 
                  
              typedef std::pair<indx, report_task >                    indx_reporttask_pair;
              typedef std::map<indx, report_task,
              std::less<indx>, std::allocator<indx_reporttask_pair> >  indx_reporttask_map;
              
              
              
              
              struct event_task{
                  num64    cid;
                  datetime creatitime;
                  datetime from;}; 
                  
              typedef std::pair<indx, event_task >                    indx_eventtask_pair;
              typedef std::map<indx, event_task,
              std::less<indx>, std::allocator<indx_eventtask_pair> >  indx_eventtask_map;                  
                  
                


            public:

                localnetintf(tagsbase_ptr inf) : netintf() , 
                        intf(inf), isautorizate_(false), regclid(0)  {
                     refcntr=refcounter_ptr(new refcounter(intf,true));
				     isconnected();};

                virtual  ~localnetintf() {
                   disconnect();};
                
                

                virtual ns_error auth_req( const std::string& user, const std::string& pass);
                virtual ns_error add_items( const vect_cid_key& cids, vect_sid_key& sids,  vect_error_item& errors);
                virtual ns_error add_items_ex( const vect_cid_key_ex cids, vect_sid_key_ex& sids,  vect_error_ex_item& errors);
                virtual ns_error remove_items( const vect_num64& sids,  vect_num64& succ_sids , vect_error_item& errors);
                virtual ns_error read_values( const vect_num64& sids, vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors);
                virtual ns_error read_values(vect_data_item& lines , vect_data_item_str& linesstr, vect_error_item& errors);
                virtual ns_error read_values_ex(const vect_num64& rsids, vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors);
                virtual ns_error read_values_ex(vect_data_item& lines , vect_data_item_str& linesstr, vect_sid_key_ex& sids, vect_error_item& errors);
                virtual ns_error send_commands(const vect_command_data& cmds, vect_error_item& errors);
                virtual ns_error read_report(const vect_reporttask& tasks , vect_report_value_data& dt, vect_error_item& errors);
                virtual ns_error read_events(const vect_eventtask& tasks , vect_event_value_item& dt, vect_error_item& errors);
                virtual ns_error read_trend(const vect_trendtask& tasks, vect_trend_value_data& dt , vect_error_item& errors);
                virtual ns_error read_alarms(const unum64& guid, vect_alarms_data& dt);
                virtual ns_error read_journal(const unum64& guid, const unum64& cursor, const unum64& cnt, vect_journal_data& dt);
                

                virtual void setaddress(const boost::asio::ip::address& adr){
                    address=adr;}

            protected:                
                
                
                virtual ns_error connect_impl();

                virtual ns_error disconnect_impl();


            private:
                
                ns_error execute_report(vect_report_value_data& dt, vect_error_item& errors);
                ns_error execute_event(vect_event_value_item& dt, vect_error_item& errors);

                tagsbase_ptr              intf;
                boost::asio::ip::address  address;
                bool                      isautorizate_;
                guidtype                  regclid;
                refcounter_ptr            refcntr;
                indx_deadb_shv_map        value_map;
                
                indx_reporttask_map       report_task_map;
                indx_eventtask_map        event_task_map;} ;}}}

#endif	/* NETINTF_H */

