/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 Июнь 2011 г., 16:16
 */

#include "mmsintf.h"

namespace dvnci {

    objectname::objectname() : internal_(new mmsobject_type()) {
    }

    objectname::objectname(const std::string& id, const std::string& domain) :
    internal_(domain.size() ? new mmsobject_type(MMS::ObjectName::Domain_specific_type(mmsidentifier_type(domain),
    mmsidentifier_type(id)), MMS::ObjectName_domain_specific) : new mmsobject_type(mmsidentifier_type(id), MMS::ObjectName_vmd_specific)) {
    }

    objectname_ptr objectname::create(const std::string& id, const std::string& domain) {
        return objectname_ptr(new objectname(id, domain));
    }

    objectname_ptr objectname::create_aa(const std::string& id) {
        objectname_ptr obj(new objectname());
        obj->internal_ = mmsobject_ptr(new mmsobject_type(mmsidentifier_type(id), MMS::ObjectName_aa_specific));
        return obj;
    }

    // 1 @bind and @domain  =>  domainspesific : @domain | @bind
    // 2 only @bind a) "xxxx" => vmdspesific
    //                         b) "xxxx : yyyy" domain specific @xxxx | @yyyy !!!! high prior,  defdomain ignore if exists
    //                         c) "@xxxx" application spesific @xxxx    

    objectname_ptr objectname::create_from_bind(const std::string& id, const std::string& defdomain) {
        std::string tstid = fulltrim_copy(id);
        std::string tstdom = fulltrim_copy(defdomain);
        std::string::size_type it = tstid.find('/');
        std::string::size_type ita = tstid.find('@');
        if (ita == 0) {
            if (tstid.size() > 0)
                return create_aa(tstid.substr(1));
        } else if ((it != std::string::npos) && (it != (tstid.size() - 1))) {
            tstdom = tstid.substr(0, it);
            tstid = tstid.substr(it + 1);
        }
        if (tstid.size())
            return create(tstid, tstdom);
        return objectname_ptr();
    }

    objectname::operator bool() const {
        return (internal_ && (internal_->type() != MMS::ObjectName_null));
    }

    bool operator==(const objectname& ls, const objectname& rs) {
        if (ls.internal_ && rs.internal_) {
            if (ls.internal_->type() == rs.internal_->type()) {
                switch (ls.internal_->type()) {
                    case MMS::ObjectName_vmd_specific:
                        return *(ls.internal_->vmd_specific()) == *(rs.internal_->vmd_specific());
                    case MMS::ObjectName_domain_specific:
                        return ((ls.internal_->domain_specific()->domainID() == rs.internal_->domain_specific()->domainID()) &&
                                (ls.internal_->domain_specific()->itemID() == rs.internal_->domain_specific()->itemID()));
                    case MMS::ObjectName_aa_specific:
                        return *(ls.internal_->aa_specific()) == *(rs.internal_->aa_specific());
                    default:
                    {
                    }
                        return true;
                }
            }
            return false;
        } else if (!ls.internal_ && !rs.internal_)
            return true;
        return false;
    }

    bool operator<(const objectname& ls, const objectname& rs) {
        if (ls.internal_ && rs.internal_) {
            if (ls.internal_->type() == rs.internal_->type()) {
                switch (ls.internal_->type()) {
                    case MMS::ObjectName_vmd_specific:
                        return *(ls.internal_->vmd_specific()) < *(rs.internal_->vmd_specific());
                    case MMS::ObjectName_domain_specific:
                    {
                        if (ls.internal_->domain_specific()->domainID() == rs.internal_->domain_specific()->domainID())
                            return (ls.internal_->domain_specific()->itemID() < rs.internal_->domain_specific()->itemID());
                        return (ls.internal_->domain_specific()->domainID() < rs.internal_->domain_specific()->domainID());
                    }
                    case MMS::ObjectName_aa_specific:
                        return *(ls.internal_->aa_specific()) < *(rs.internal_->aa_specific());
                    default:
                    {
                    }
                        return false;
                }
            } else if (ls.internal_->type() == MMS::ObjectName_null)
                return true;
            else if (rs.internal_->type() == MMS::ObjectName_null)
                return false;
            return (int) ls.internal_->type() < (int) rs.internal_->type();
        } else if (ls.internal_ && !rs.internal_)
            return false;
        else if (ls.internal_ && !rs.internal_)
            return false;
        else if (!ls.internal_ && !rs.internal_)
            return true;
        return false;
    }

    bool operator==(const objectname_ptr& ls, const objectname_ptr& rs) {
        if (ls && rs)
            return *ls == *rs;
        if (!ls && !rs)
            return true;
        return false;
    }

    bool operator<(const objectname_ptr& ls, const objectname_ptr& rs) {
        if (ls && rs)
            return *ls < *rs;
        if ((!ls && !rs) || (!rs))
            return false;
        return true;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////// list_of_variable
    /////////////////////////////////////////////////////////////////////////////////////////////////    

    bool list_of_variable::insert(const objectname_vct& vls) {
        bool inserted = false;
        for (objectname_vct::const_iterator it = vls.begin(); it != vls.end(); ++it) {
            if (values_.find(*it) == values_.end()) {
                values_.insert(accessresult_pair((*it), accessresult_ptr()));
                inserted = true;
            }
        }
        return inserted;
    }

    bool list_of_variable::insert(const objectname_set& vls) {
        bool inserted = false;
        for (objectname_set::const_iterator it = vls.begin(); it != vls.end(); ++it) {
            if (values_.find(*it) == values_.end()) {
                values_.insert(accessresult_pair((*it), accessresult_ptr()));
                inserted = true;
            }
        }
        return inserted;
    }

    bool list_of_variable::remove(const objectname_vct& vls) {
        bool finded = false;
        for (objectname_vct::const_iterator it = vls.begin(); it != vls.end(); ++it) {
            if (values_.find(*it) != values_.end()) {
                values_.erase(*it);
                finded = true;
            }
        }
        return finded;
    }

    bool list_of_variable::remove(const objectname_set& vls) {
        bool finded = false;
        for (objectname_set::const_iterator it = vls.begin(); it != vls.end(); ++it) {
            if (values_.find(*it) != values_.end()) {
                values_.erase(*it);
                finded = true;
            }
        }
        return finded;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////// mmsintf
    /////////////////////////////////////////////////////////////////////////////////////////////////  

    mmsintf::mmsintf(const std::string hst, const std::string prt, const std::string opt,
            timeouttype tmo) : client_io(new prot9506::mmsioclient()),
    host(hst), port(prt), option(opt), tmout(tmo), list_("@test") {
    }

    mmsintf_ptr mmsintf::build(const std::string host, const std::string port, const std::string opt, timeouttype tmout) {
        mmsintf_ptr tmpintf = mmsintf_ptr(new mmsintf(host, port, opt, tmout));
        return tmpintf;
    }

    ns_error mmsintf::connect_impl() {
        try {
            if (!client_io) return error(ERROR_IO_DEVICE_CHANAL_NOT_DEF);
            if (client_io->state() == client_io->connected) {
                state_ = connected;
                return error(0);
            }
            client_io->connect(host, port, option, tmout);
            state_ = (client_io->state() == client_io->connected) ? connected : disconnected;
            if (state_ == connected) {
                return error(0);
            } else {
                state_ = disconnected;
                return error(ERROR_IO_LINK_NOT_CONNECTION);
            }
        } catch (...) {
        }
        state_ = disconnected;
        return error(ERROR_BASENOTFOUND);
    }

    ns_error mmsintf::disconnect_impl() {
        try {
            if ((client_io) && (client_io->state() == client_io->connected)) {
                client_io->disconnect();
            }
        } catch (...) {
        }
        state_ = disconnected;
        return error(0);
    }

    ns_error mmsintf::add_items(const bindobject_map& cids, accessresult_map& results, accesserror_map& errors) {
        try {

            typedef prot9506::getvaraccess_operation_type getvaraccess_operation_type;
            typedef prot9506::read_operation_type read_operation_type;
            typedef prot9506::identify_operation_type identify_operation_type;

            boost::shared_ptr<identify_operation_type> operationI(new identify_operation_type());
            operationI->request_new();
            if (client_io->req<identify_operation_type>(operationI)) {

            }

            objectname_vct actuals;

            error(0);

            for (bindobject_map::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                boost::shared_ptr<getvaraccess_operation_type> operationA(new getvaraccess_operation_type());
                operationA->request_new();
                operationA->request()->name(new mmsobject_type(it->second->internal()));
                if (client_io->req<getvaraccess_operation_type>(operationA)) {
                    if (operationA->response()) {
                        results.insert(accessresult_pair(it->second, accessresult_ptr()));
                        actuals.push_back(it->second);
                    } else if (operationA->serviceerror()) {
                        errors.insert(accesserror_pair(it->second, operationA->serviceerror()));
                    } else {

                    }
                }
            }

            for (accessresult_map::iterator it = results.begin(); it != results.end(); ++it) {
                boost::shared_ptr<read_operation_type> operationR(new read_operation_type());
                operationR->request_new();
                operationR->request()->variableAccessSpecification().listOfVariable__new();

                MMS::VariableAccessSpecification::ListOfVariable_type_sequence_of vacs;

                vacs.variableSpecification().name(new mmsobject_type(it->first->internal()));

                operationR->request()->variableAccessSpecification().listOfVariable()->push_back(vacs);

                if (client_io->req<read_operation_type>(operationR)) {
                    if (operationR->response()) {
                        const resultslist_type& lst = operationR->response()->listOfAccessResult();
                        if (lst.size() == 1) {
                            it->second = accessresult_ptr(new accessresult_type(lst[0]));
                        }
                    } else if (operationR->serviceerror()) {
                        //errors.insert(accesserror_pair((*it),operationA->serviceerror()));
                    } else {

                    }
                }
            }

            if (!actuals.empty()) {
                bool needcreate = list_.empty();
                if (list_.insert(actuals)) {
                    if (updatenamedlist(list_))
                        list_.remove(actuals);
                }
            }

        } catch (dvncierror& err_) {
            error(err_.code());
            if ((err_.code() == ERROR_FAILNET_CONNECTED) ||
                    (err_.code() == ERROR_NONET_CONNECTED))
                throw err_;
            ;
        } catch (...) {
            error(NS_ERROR_ERRRESP);
        }
        return error();
    }

    ns_error mmsintf::remove_items(const objectname_set& cids, accesserror_map& errors) {
        error(0);
        if (list_.remove(cids)) {
            removenamedlist(list_);
        }
        return error();
    }

    ns_error mmsintf::read_values(accessresult_map& sids) {
        readnamedlist(list_);
        for (accessresult_map::iterator it = sids.begin(); it != sids.end(); ++it) {
            accessresult_map::const_iterator fit = list_.values().find(it->first);
            if (fit != list_.values().end()) {
                it->second = fit->second;
            } else {
                it->second = accessresult_ptr();
            }
        }
        return error();
    }

    /*ns_error mmsintf::send_commands(const vect_command_data& cmds, vect_error_item& errors) {
        try {
            error(0);
            req_send_commands req;
            resp_send_commands resp;
            assign_req_commands(req, cmds);
            if (querytmpl<req_send_commands, resp_send_commands, RPC_OPERATION_REQ_SEND_COMMANDS, RPC_OPERATION_RESP_SEND_COMMANDS > (req, resp)) {
                assign_resp_commands(resp, errors);
            } else
                error(ERROR_IO_NO_DATA);
        } catch (dvncierror& err_) {
            error(err_.code());
            if ((err_.code() == ERROR_FAILNET_CONNECTED) ||
                    (err_.code() == ERROR_NONET_CONNECTED))
                throw err_;
        } catch (...) {
            error(NS_ERROR_ERRRESP);
        }
        return error();
    }*/


    ns_error mmsintf::updatenamedlist(const list_of_variable& lst) {
        try {

            typedef prot9506::definelist_operation_type definelist_operation_type;

            error(0);

            removenamedlist(lst);

            boost::shared_ptr<definelist_operation_type> operationDF =
                    boost::shared_ptr<definelist_operation_type > (new definelist_operation_type());

            operationDF->request_new();

            operationDF->request()->variableListName(lst.key()->internal());

            for (accessresult_map::const_iterator it = lst.values().begin(); it != lst.values().end(); ++it) {
                operationDF->request()->listOfVariable().push_back(MMS::DefineNamedVariableList_Request::ListOfVariable_type_sequence_of(
                        MMS::VariableSpecification(it->first->internal(),
                        MMS::VariableSpecification_name)));
            }

            if (client_io->req<definelist_operation_type>(operationDF)) {
                if (operationDF->response()) {

                }
            } else if (operationDF->serviceerror()) {
                return error(NS_ERROR_ERRRESP);
            } else {
                return error(NS_ERROR_ERRRESP);
            }
        } catch (dvncierror& err_) {
            error(err_.code());
            if ((err_.code() == ERROR_FAILNET_CONNECTED) ||
                    (err_.code() == ERROR_NONET_CONNECTED))
                throw err_;
        } catch (...) {
            error(NS_ERROR_ERRRESP);
        }
        return error();
    }

    ns_error mmsintf::removenamedlist(const list_of_variable& lst) {
        try {

            typedef prot9506::deletelist_operation_type deletelist_operation_type;

            error(0);

            boost::shared_ptr<deletelist_operation_type> operationDL =
                    boost::shared_ptr<deletelist_operation_type > (new deletelist_operation_type());

            operationDL->request_new();

            MMS::DeleteNamedVariableList_Request::ListOfVariableListName_type lstv;
            lstv.push_back(lst.key()->internal());

            operationDL->request()->listOfVariableListName(lstv);

            if (client_io->req<deletelist_operation_type>(operationDL)) {
                if (operationDL->response()) {

                }
            } else if (operationDL->serviceerror()) {
                return error(NS_ERROR_ERRRESP);
            } else {
                return error(NS_ERROR_ERRRESP);
            }
        } catch (dvncierror& err_) {
            error(err_.code());
            if ((err_.code() == ERROR_FAILNET_CONNECTED) ||
                    (err_.code() == ERROR_NONET_CONNECTED))
                throw err_;
        } catch (...) {
            error(NS_ERROR_ERRRESP);
        }
        return error();
    }

    ns_error mmsintf::readnamedlist(list_of_variable& lst) {
        error(0);
        if (!list_.empty()) {
            try {

                typedef prot9506::read_operation_type read_operation_type;


                boost::shared_ptr<read_operation_type> operationR =
                        boost::shared_ptr<read_operation_type > (new read_operation_type());

                operationR->request_new();
                operationR->request()->variableAccessSpecification(
                        MMS::VariableAccessSpecification(lst.key()->internal(), MMS::VariableAccessSpecification_variableListName));

                if (client_io->req<read_operation_type>(operationR)) {
                    if (operationR->response()) {
                        const resultslist_type& vlst = operationR->response()->listOfAccessResult();
                        accessresult_map::iterator vit = lst.values().begin();
                        for (resultslist_type::const_iterator it = vlst.begin(); it != vlst.end(); ++it) {
                            if (vit != lst.values().end())
                                vit->second = accessresult_ptr(new accessresult_type(*it));
                            ++vit;
                        }
                    }
                } else if (operationR->serviceerror()) {
                    return error(NS_ERROR_ERRRESP);
                } else {
                    return error(NS_ERROR_ERRRESP);
                }
            } catch (dvncierror& err_) {
                error(err_.code());
                if ((err_.code() == ERROR_FAILNET_CONNECTED) ||
                        (err_.code() == ERROR_NONET_CONNECTED))
                    throw err_;
            } catch (...) {
                error(NS_ERROR_ERRRESP);
            }
        }
        return error();
    }




}

