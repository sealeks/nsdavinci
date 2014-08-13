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


    
    class objectname;

    typedef MMSO::Identifier mmsidentifier_type;
    typedef MMS::ObjectName mmsobject_type;

    typedef MMS::Read_Response::ListOfAccessResult_type resultslist_type;

    typedef MMS::AccessResult accessresult_type;
    typedef boost::shared_ptr<accessresult_type> accessresult_ptr;

    typedef MMS::ServiceError serviceerror_type;
    typedef boost::shared_ptr< serviceerror_type> serviceerror_ptr;

    typedef boost::shared_ptr<mmsobject_type> mmsobject_ptr;
    typedef boost::shared_ptr<objectname> objectname_ptr;

    class objectname {

    public:

        objectname();
        objectname(const std::string& id, const std::string& domain = "");

        ~objectname() {
        }

        static objectname_ptr create(const std::string& id, const std::string& domain = "");
        static objectname_ptr create_aa(const std::string& id);

        // 1 @bind and @domain  =>  domainspesific : @domain | @bind
        // 2 only @bind a) "xxxx" => vmdspesific
        //                         b) "xxxx : yyyy" domain specific @xxxx | @yyyy !!!! high prior  defdomain ignore if exists
        //                         c) "@xxxx" application spesific @xxxx
        static objectname_ptr create_from_bind(const std::string& id, const std::string& defdomain = "");

        mmsobject_type internal() const {
            return internal_ ? (*internal_) : mmsobject_type();
        }

        mmsobject_ptr internal_ptr() const {
            return internal_;
        }


        operator bool() const;

        friend bool operator==(const objectname& ls, const objectname& rs);
        friend bool operator<(const objectname& ls, const objectname& rs);
        friend bool operator==(const objectname_ptr& ls, const objectname_ptr& rs);
        friend bool operator<(const objectname_ptr& ls, const objectname_ptr& rs);



    private:

        mmsobject_ptr internal_;
    };

    typedef boost::shared_ptr<objectname> objectname_ptr;

    typedef std::vector<objectname_ptr> objectname_vct;
    typedef std::set<objectname_ptr> objectname_set;

    typedef std::pair<dvnci::indx, objectname_ptr> bindobject_pair;
    typedef std::map<dvnci::indx, objectname_ptr> bindobject_map;

    typedef std::pair<objectname_ptr, serviceerror_ptr> accesserror_pair;
    typedef std::map<objectname_ptr, serviceerror_ptr> accesserror_map;

    typedef std::pair<objectname_ptr, accessresult_ptr> accessresult_pair;
    typedef std::map<objectname_ptr, accessresult_ptr> accessresult_map;

    class list_of_variable {

    public:

        list_of_variable(const std::string& vl) : key_(objectname::create_aa(vl)) {
        }

        ~list_of_variable() {
        };

        objectname_ptr key() const {
            return key_;
        }

        const accessresult_map& values() const {
            return values_;
        };

        accessresult_map& values() {
            return values_;
        };

        bool empty() const {
            return values_.empty();
        };

        bool insert(const objectname_vct& vls);
        bool insert(const objectname_set& vls);
        bool remove(const objectname_vct& vls);
        bool remove(const objectname_set& vls);

    private:

        objectname_ptr key_;
        accessresult_map values_;
    };




    class mmsintf;
    typedef boost::shared_ptr<mmsintf> mmsintf_ptr;

    class mmsintf {

    public:

        enum intfstate {

            disconnected, connected
        };

        mmsintf(const std::string hst, const std::string prt, const std::string opt,
                timeouttype tmo = DEFAULT_DVNCI_TIMOUT);

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

        ns_error add_items(const bindobject_map& cids, accessresult_map& results, accesserror_map& errors);
        ns_error remove_items(const objectname_set& cids, accesserror_map& errors);
        ns_error read_values(accessresult_map& sids);
        //ns_error send_commands(const vect_command_data& cmds, vect_error_item& errors);

        virtual void setaddress(const boost::asio::ip::address& adr) {
        }

        static mmsintf_ptr build(const std::string host, const std::string port, const std::string opt, timeouttype tmout = DEFAULT_DVNCI_TIMOUT);

    protected:

        virtual ns_error connect_impl();

        virtual ns_error disconnect_impl();

        ns_error updatenamedlist(const list_of_variable& lst);
        ns_error removenamedlist(const list_of_variable& lst);
        ns_error readnamedlist(list_of_variable& lst);

        ns_error error(ns_error err) {
            return error_ = err;
        }

        intfstate state_;
        ns_error error_;

    private:

        prot9506::mmsioclient_ptr client_io;
        std::string host;
        std::string port;
        std::string option;
        timeouttype tmout;
        list_of_variable list_;
    };



}

#endif	/* EXTNETINTF_H */

