/* 
 * File:   extnetintf.h
 * Author: Alexeev
 *
 * Created on 14 Июнь 2011 г., 16:16
 */

#ifndef MMSINTF_H
#define	MMSINTF_H

#include <kernel/constdef.h>
#include <kernel/error.h>
#include <kernel/memfile.h>
#include <kernel/templ.h>
#include <kernel/utils.h>
#include <kernel/short_value.h>
#include <kernel/interface_proccesstmpl.h>
#include <kernel/extintf_wraper.h>
#include <mms/mmssocket.h>
#include <mms/MMS-Object-Module-1.hpp>
#include <mms/ISO-9506-MMS-1.hpp>
#include "mmsioclient.h"

namespace dvnci {
    
    namespace MMS = ISO_9506_MMS_1;
    namespace MMSO = MMS_Object_Module_1;
    

    typedef MMSO::Identifier mmsidentifier_type;
    typedef MMS::ObjectName objectname_type;
    typedef boost::shared_ptr<objectname_type> objectname_ptr;

    class objectname {

    public:

        objectname();
        objectname(const std::string& id, const std::string& domain = "");

        ~objectname() {
        }

        static objectname create(const std::string& id, const std::string& domain = "");
        static objectname create_aa(const std::string& id);
        
        // 1 @bind and @domain  =>  domainspesific : @domain | @bind
        // 2 only @bind a) "xxxx" => vmdspesific
        //                         b) "xxxx : yyyy" domain specific @xxxx | @yyyy !!!! high prior  defdomain ignore if exists
        //                         c) "@xxxx" application spesific @xxxx
        static objectname create_from_bind(const std::string& id, const std::string& defdomain = "");

        objectname_type internal() const {
            return internal_ ? (*internal_) : objectname_type();
        }
        

        operator bool() const;   

        friend bool operator==(const objectname& ls, const objectname& rs);
        friend bool operator<(const objectname& ls, const objectname& rs);



    private:

        objectname_ptr internal_;
    };
    
    typedef std::vector<objectname> objectname_vct;
    typedef std::set<objectname> objectname_set;    

    /*namespace MMS_Object_Module_1 {

        bool operator==(const objectname_type& ls, const objectname_type& rs) {
            if (ls.type() == rs.type()) {
                if ((ls.aa_specific()) && (rs.aa_specific())) {
                    return (ls.aa_specific() == rs.aa_specific());
                }
            }
            return false;
        }

        bool operator<(const objectname_type& ls, const objectname_type& rs) {
            if (ls.type() == rs.type()) {
                if ((ls.aa_specific()) && (rs.aa_specific())) {
                    return (ls.aa_specific() < rs.aa_specific());
                }
            }
            return false;
        }

    }*/
    
    /*namespace mms {

        class mmsintf {

        public:

            enum intfstate {

                disconnected, connected
            };

            mmsintf() : state_(disconnected), error_(ERROR_NONET_CONNECTED) {
            };

            virtual ~mmsintf() {
            };

            bool isconnected() {
                return ((state_ == connected) || (!error(connect_impl())));
            };

            bool disconnect() {
                return ((state_ != connected) || (!error(disconnect_impl())));
            }

            ns_error error() const {
                return error_;
            }

            ns_error add_items(const vect_cid_key& cids, vect_error_item& errors);
            ns_error remove_items(const vect_num64& sids, vect_num64& succ_sids, vect_error_item& errors);
            ns_error read_values(const vect_num64& sids, vect_data_item& lines, vect_data_item_str& linesstr, vect_error_item& errors);
            ns_error read_values(vect_data_item& lines, vect_data_item_str& linesstr, vect_error_item& errors);
            ns_error send_commands(const vect_command_data& cmds, vect_error_item& errors);


            virtual void setaddress(const boost::asio::ip::address& adr) {
            }

        protected:

            virtual ns_error connect_impl();

            virtual ns_error disconnect_impl();

            ns_error error(ns_error err) {
                return error_ = err;
            }

            intfstate state_;
            ns_error error_;
        };*/
    

    
    namespace external {

        class exmmsintf : public extintf_wraper<objectname> {

        public:

            exmmsintf(tagsbase_ptr intf_, executor* exctr, indx grp);

            virtual ~exmmsintf();


        protected:


            virtual ns_error checkserverstatus();

            virtual ns_error connect_impl();

            virtual ns_error disconnect_impl();

            virtual ns_error add_request_impl();

            virtual ns_error remove_request_impl();

            virtual ns_error value_request_impl();

            virtual ns_error command_request_impl(const sidcmd_map& cmds);

            virtual ns_error report_request_impl();

            virtual ns_error event_request_impl();

        };
    }
}

#endif	/* EXTNETINTF_H */

