/* 
 * File:   dvnci_net_subsciptor.h
 * Author: Serg
 *
 * Created on 23 Июль 2010 г., 18:51
 */

#ifndef DVNCI_NET_SUBSCIPTORU_H
#define	DVNCI_NET_SUBSCIPTORU_H


#include <netinterface/factory.h>

namespace dvnci {
    namespace net {

        short_value & operator<<(short_value& lv, const value_item&  rv);

        class dvnci_net_subsciptor : public abstract_subscriptor<netintf>  {
        public:

            dvnci_net_subsciptor(tagsbase_ptr inf, indx grp, const metalink& lnk, tagtype provide_man = TYPE_SIMPL) :
                                   abstract_subscriptor<netintf>(inf, grp, metalink()) {}

        protected:

            virtual bool initialize_impl();

            ns_error getvalue(indx id, short_value& val) {
            if (values_map.find(id) != values_map.end()) {
                val = values_map[id];
                return 0;}

            return ERROR_NODATA;}

            virtual bool prepare_add_items(vect_client_item& clientitems);
            virtual bool prepare_add_command(vect_command_item& cmditems);
            
            virtual bool check_reportitem_in_active(indx id){
                short_value valtmp;
                if (!getvalue(id, valtmp)) {
                      if ((valtmp.valid()==REPORT_NORMAL) && (!is_report_task(id))) {
                              add_report_task(id);
		     return true;}}
		return false;}

            virtual bool set_values_impl(indx id, const short_value& value){
                if (IN_REPORTSET(intf->type(id))){
                    if (values_map.find(id)!=values_map.end()) values_map.erase(id);
                            values_map.insert(executor_value_pair(id, value));
                    return true;}
                return false;}

            virtual num64 nill_server_key() const {return -1;};

            // карта значений
            executor_value_map values_map;
} ;
}}

#endif	/* DVNCI_NET_SUBSCIPTOR_H */

