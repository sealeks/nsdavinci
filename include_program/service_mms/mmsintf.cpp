/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 Июнь 2011 г., 16:16
 */

#include "mmsintf.h"

namespace dvnci {

    short_value from_mms_result(accessresult_ptr val) {
        if (val) {
            if (val->success()) {
                switch (val->success()->type()) {
                    case MMS::Data_boolean:
                    {
                        return short_value(*(val->success()->boolean()));
                    }
                    case MMS::Data_bit_string:
                    case MMS::Data_booleanArray:
                    {
                        const MMS::bitstring_type& tmp = val->success()->type() == MMS::Data_bit_string ?
                                (*(val->success()->bit_string())) : (*(val->success()->booleanArray()));
                        if (tmp.sizebits() <= 8)
                            return short_value(tmp. operator uint8_t());
                        else if (tmp.sizebits() <= 16)
                            return short_value(tmp. operator uint16_t());
                        else if (tmp.sizebits() <= 32)
                            return short_value(tmp. operator uint32_t());
                        else
                            return short_value(tmp. operator uint64_t());
                        break;
                    }
                    case MMS::Data_integer:
                    {
                        return short_value(*(val->success()->integer()));
                    }
                    case MMS::Data_unsignedV:
                    {
                        return short_value(*(val->success()->unsignedV()));
                    }
                    case MMS::Data_floating_point:
                    {
                        return short_value(prot9506::from_mmsfloat(*(val->success()->floating_point())));
                    }
                    case MMS::Data_octet_string:
                    {
                        const boost::asn1::octetstring_type& tmp = *(val->success()->octet_string());
                        std::string tmps(tmp.begin(), tmp.end());
                        return short_value(tmps);
                    }
                    case MMS::Data_visible_string:
                    {
                        const boost::asn1::visiblestring_type& tmp = *(val->success()->visible_string());
                        std::string tmps(tmp.begin(), tmp.end());
                        return short_value(tmps);
                    }
                    case MMS::Data_generalized_time:
                    {
                        return short_value(val->success()->generalized_time()->value());
                    }
                    case MMS::Data_binary_time:
                    {
                        return short_value(prot9506::from_mms_datetime(*(val->success()->binary_time())));
                    }
                    case MMS::Data_bcd:
                    {
                        int tmp;
                        if (bcd_to_dec(*(val->success()->bcd()), tmp))
                            return short_value(tmp);
                        else
                            return short_value(0, TYPE_NUM32, FULL_VALID, ERROR_TYPENOCAST);
                    }
                    case MMS::Data_mMSString:
                    {
                        const MMS::MMSString& tmp = *(val->success()->mMSString());
                        std::string tmps(tmp.begin(), tmp.end());
                        return short_value(tmps);
                    }
                    case MMS::Data_utcTime:
                    {
                        return short_value(prot9506::from_mms_utctime(*(val->success()->utcTime())));
                    }
                        /*case MMS::Data_objId:
                        {
                            std::cout << *(val.success()->objId()) << std::endl;
                            break;
                        }*/
                    default:
                    {
                        return short_value(0, TYPE_NUM32, FULL_VALID, ERROR_TYPENOCAST);
                    }
                }
            } else {
                return short_value(0, 0, NULL_VALID, ERROR_TYPENOCAST);
            }
        }
        return short_value();
    }






    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////// objectname
    /////////////////////////////////////////////////////////////////////////////////////////////////        

    objectname::objectname() : internal_(new mmsobject_type()) {
    }

    objectname::objectname(const std::string& id, const std::string& domain) :
    internal_(domain.size() ? new mmsobject_type(MMS::ObjectName::Domain_specific_type(mmsidentifier_type(domain),
    mmsidentifier_type(id)), MMS::ObjectName_domain_specific) : new mmsobject_type(mmsidentifier_type(id), MMS::ObjectName_vmd_specific)) {
    }

    objectname::~objectname() {
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

    bool list_of_variable::insert(const objectname_ptr& vls) {
        bool inserted = false;
        if (values_.find(vls) == values_.end()) {
            values_.insert(accessresult_pair((vls), accessresult_ptr()));
            inserted = true;
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

    bool list_of_variable::remove(const objectname_ptr& vls) {
        bool finded = false;
        if (values_.find(vls) != values_.end()) {
            values_.erase(vls);
            finded = true;
        }
        return finded;
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

    bool operator==(const list_of_variable& ls, const list_of_variable& rs) {
        if ((ls.key()) && (rs.key()))
            return ls.key() == rs.key();
        else if ((!ls.key()) && (!rs.key()))
            return true;
        return false;
    }

    bool operator<(const list_of_variable& ls, const list_of_variable& rs) {
        if ((ls.key()) && (rs.key()))
            return ls.key() < rs.key();
        else if ((!ls.key()) && (!rs.key()))
            return false;
        else if ((!ls.key()) && (rs.key()))
            return true;
        return false;
    }


    /////////////////////////////////////////////////////////////////////////////////////////////////
    //////// mmsintf
    /////////////////////////////////////////////////////////////////////////////////////////////////  

    mmsintf::mmsintf(const std::string hst, const std::string prt, const std::string opt, std::size_t blocksz, timeouttype tmo) :
    client_io(new prot9506::mmsioclient()), host(hst), port(prt), option(opt), tmout(tmo), blocksize(blocksz ? blocksz : BLOCK_SZ_DFLT) {
    }

    mmsintf_ptr mmsintf::build(const std::string host, const std::string port, const std::string opt, std::size_t blocksz, timeouttype tmout) {
        blocksz = (blocksz < 2) ? BLOCK_SZ_DFLT : ((blocksz > BLOCK_SZ_MAX) ? BLOCK_SZ_MAX : blocksz);
        mmsintf_ptr tmpintf = mmsintf_ptr(new mmsintf(host, port, opt, blocksz, tmout));
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

            if (client_io->can_namedlist()) {

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
                    //if (list_.insert(actuals)) {
                    ///  if (update_namedlist(list_))
                    //    list_.remove(actuals);
                    //}
                }
            } else {
                simplelist_.insert(results.begin(), results.end());
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
        if (!lists_.empty()) {
            if (error(remove_from_namedlist(cids)))
                return error();
        }
        for (objectname_set::const_iterator it = cids.begin(); it != cids.end(); ++it) {
            accessresult_map::iterator fit = simplelist_.find(*it);
            if (simplelist_.find(*it) != simplelist_.end()) {
                simplelist_.erase(fit);
            }
        }
        return error();
    }

    ns_error mmsintf::read_values(accessresult_map& sids) {
        if ((!simplelist_.empty()) || !(lists_.empty())) {
            if (!simplelist_.empty())
                if (error(read_simlelist()))
                    return error();
            if (!lists_.empty())
                if (error(read_all_namedlist()))
                    return error();

            for (accessresult_map::iterator it = sids.begin(); it != sids.end(); ++it) {

                accessresult_ptr locrslt;
                accessresult_map::const_iterator sfit = simplelist_.find(it->first);
                if (sfit != simplelist_.end()) {
                    locrslt = sfit->second;
                } else {
                    for (list_of_variable_vct::const_iterator lit = lists_.begin(); lit != lists_.end(); ++lit) {
                        accessresult_map::const_iterator fit = lit->values().find(it->first);
                        if (fit != lit->values().end()) {
                            locrslt = fit->second;
                            break;
                        }
                    }
                    locrslt = accessresult_ptr();
                }
                it->second = locrslt;
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

    list_of_variable& mmsintf::nextlist() {
        std::size_t newindx = 1;
        if (lists_.empty()) {
            lists_.push_back(list_of_variable(VARLIST_TEMPLNAME + dvnci::to_str(newindx)));
            return lists_.front();
        } else {
            for (list_of_variable_vct::iterator it = lists_.begin(); it != lists_.end(); ++it) {
                if (it->values().size() < blocksize)
                    return *it;
            }
        }
        while (std::find(lists_.begin(), lists_.end(),
                list_of_variable(VARLIST_TEMPLNAME + dvnci::to_str(++newindx))) != lists_.end());
        lists_.push_back(list_of_variable(VARLIST_TEMPLNAME + dvnci::to_str(newindx)));
        return lists_.back();
    }

    ns_error mmsintf::insert_in_namedlist(const objectname_vct& vls) {
        error(0);
        if (vls.empty()) {
            std::size_t ncnt = 0;
            objectname_vct::const_iterator it = vls.begin();
            list_of_variable& next = nextlist();
            while (it != vls.end()) {
                next.insert(*it);
                if ((next.values().size()) && (next.values().size() >= blocksize)) {
                    if (error(update_namedlist(next)))
                        return error();
                    next = nextlist();
                    ncnt = 0;
                }
                ++it;
            }
            if (ncnt) {
                if (error(update_namedlist(next)))
                    return error();
            }
        }
        return error();
    }

    ns_error mmsintf::remove_from_namedlist(const objectname_set& vls) {
        error(0);
        if (!lists_.empty()) {
            for (list_of_variable_vct::iterator it = lists_.begin(); it != lists_.end(); ++it) {
                if (it->remove(vls)) {
                    if (error(update_namedlist(*it)))
                        return error();
                }
            }
        }
        return error();
    }

    ns_error mmsintf::update_namedlist(const list_of_variable& lst) {
        try {

            typedef prot9506::definelist_operation_type definelist_operation_type;

            error(0);

            remove_namedlist(lst);

            if (!lst.empty()) {

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

    ns_error mmsintf::remove_namedlist(const list_of_variable& lst) {
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

    ns_error mmsintf::read_all_namedlist() {
        error(0);
        if (!lists_.empty()) {
            for (list_of_variable_vct::iterator it = lists_.begin(); it != lists_.end(); ++it) {
                if (error(read_namedlist(*it)))
                    return error();
            }
        }
        return error();
    }

    ns_error mmsintf::read_namedlist(list_of_variable& lst) {
        error(0);
        if (!lst.empty()) {
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
                            else break;
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

    ns_error mmsintf::read_simlelist() {
        error(0);
        if (!simplelist_.empty()) {
            try {

                typedef prot9506::read_operation_type read_operation_type;

                boost::shared_ptr<read_operation_type> operationR =
                        boost::shared_ptr<read_operation_type > (new read_operation_type());

                operationR->request_new();
                operationR->request()->variableAccessSpecification().listOfVariable__new();

                std::size_t currentcnt = 0;

                accessresult_map::iterator sit = simplelist_.begin();
                accessresult_map::iterator it = sit;

                while (it != simplelist_.end()) {

                    accessresult_map::iterator lsit = sit;

                    for (; it != simplelist_.end(); ++it) {

                        MMS::VariableAccessSpecification::ListOfVariable_type_sequence_of vacs;
                        vacs.variableSpecification().name(new mmsobject_type(it->first->internal()));

                        operationR->request()->variableAccessSpecification().listOfVariable()->push_back(vacs);
                        if (++currentcnt >= blocksize) {
                            sit = ++it;
                            currentcnt = 0;
                            break;
                        }
                    }
                    if (client_io->req<read_operation_type>(operationR)) {
                        if (operationR->response()) {
                            const resultslist_type& vlst = operationR->response()->listOfAccessResult();
                            accessresult_map::iterator vit = lsit;
                            for (resultslist_type::const_iterator rit = vlst.begin(); rit != vlst.end(); ++rit) {
                                if (vit != simplelist_.end())
                                    vit->second = accessresult_ptr(new accessresult_type(*rit));
                                else
                                    break;
                                ++vit;
                            }
                        }
                    } else if (operationR->serviceerror()) {
                        return error(NS_ERROR_ERRRESP);
                    } else {
                        return error(NS_ERROR_ERRRESP);
                    }

                    operationR->request_new();
                    operationR->request()->variableAccessSpecification().listOfVariable__new();
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

