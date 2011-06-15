
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


            public:

                localnetintf(tagsbase_ptr inf) : netintf() , intf(inf)  {};

                virtual  ~localnetintf() {};

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
                
                virtual ns_error connect_impl();

                virtual ns_error disconnect_impl();


            private:

                tagsbase_ptr       intf;
                indx_deadb_shv_map value_map;} ;}}}

#endif	/* NETINTF_H */

