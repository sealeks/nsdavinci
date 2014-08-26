/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 �?юнь 2011 г., 16:16
 */

#include "iec60870intf.h"

namespace dvnci {

    namespace prot80670 {



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec69870intf
        /////////////////////////////////////////////////////////////////////////////////////////////////  

        iec69870intf::iec69870intf(const std::string hst, const std::string prt, timeouttype tmo) :
        client_io(/*iec60870ioclient_ptr(new iec69870ioclient())*/), host(hst), port(prt), tmout(tmo) {
        }

        iec69870intf_ptr iec69870intf::build(const std::string host, const std::string port, timeouttype tmout) {
            iec69870intf_ptr tmpintf = iec69870intf_ptr(new iec69870intf(host, port, tmout));
            return tmpintf;
        }

        ns_error iec69870intf::connect_impl() {
            try {
                if (!client_io) return error(ERROR_IO_DEVICE_CHANAL_NOT_DEF);
                if (client_io->state() == client_io->connected) {
                    state_ = connected;
                    return error(0);
                }
                client_io->connect(host, port, static_cast<std::size_t> (tmout));
                state_ = (client_io->state() == client_io->connected) ? connected : disconnected;
                if (state_ == connected) {
                    DEBUG_VAL_DVNCI(host)
                    DEBUG_VAL_DVNCI(port)
                    DEBUG_VAL_DVNCI(tmout)
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

        ns_error iec69870intf::disconnect_impl() {
            try {
                if ((client_io) && (client_io->state() == client_io->connected)) {
                    client_io->disconnect();
                }
            } catch (...) {
            }
            state_ = disconnected;
            return error(0);
        }

        ns_error iec69870intf::add_items(const dataobject_set& cids, dataobject_set& errors) {

            check_connecton_state();

            /*try {
                typedef prot80670::getvaraccess_operation_type getvaraccess_operation_type;
                typedef prot80670::read_operation_type read_operation_type;
                typedef prot80670::identify_operation_type identify_operation_type;

                objectname_vct actuals;

                for (bindobject_map::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                    boost::shared_ptr<getvaraccess_operation_type> operationA(new getvaraccess_operation_type());
                    operationA->request_new();
                    operationA->request()->name(new mmsobject_type(it->second->obj()));
                    if (client_io->req<getvaraccess_operation_type>(operationA)) {
                        if ((operationA->response())) {
                            if ((operationA->response()->typeDescription().type() != MMSO::TypeDescription_array) &&
                                    (operationA->response()->typeDescription().type() != MMSO::TypeDescription_structure) &&
                                    (operationA->response()->typeDescription().type() != MMSO::TypeDescription_objId)) {
                                results.insert(accessresult_pair(it->second, mmsresult_ptr()));
                                actuals.push_back(it->second);
                                actuals.back()->access(operationA->response());
                            } else
                                errors.insert(accesserror_pair(it->second, serviceerror_ptr()));
                        } else if (operationA->serviceerror()) {
                            errors.insert(accesserror_pair(it->second, operationA->serviceerror()));
                        } else {
                            errors.insert(accesserror_pair(it->second, serviceerror_ptr()));
                        }
                    }
                }

                if (!actuals.empty()) {
                    if (client_io->can_namedlist()) {
                        if (error(insert_in_namedlist(actuals)))
                            return error();
                    } else {
                        simplelist_.insert(results.begin(), results.end());
                    }
                }

            } catch (const boost::itu::error_code& errcode) {
                parse_error(errcode);
            } catch (...) {
                parse_error(boost::itu::ER_PROTOCOL);
            }*/
            return error();
        }

        ns_error iec69870intf::remove_items(const dataobject_set& cids, dataobject_set& errors) {
            /*error(0);
            if (!lists_.empty()) {
                if (error(remove_from_namedlist(cids)))
                    return error();
            }
            for (objectname_set::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                accessresult_map::iterator fit = simplelist_.find(*it);
                if (simplelist_.find(*it) != simplelist_.end()) {
                    simplelist_.erase(fit);
                }
            }*/
            return error();
        }

        ns_error iec69870intf::read_values(const dataobject_set& cids, dataobject_set& errors) {
            /*if ((!simplelist_.empty()) || !(lists_.empty())) {
                if (!simplelist_.empty())
                    if (error(read_simlelist()))
                        return error();
                if (!lists_.empty())
                    if (error(read_all_namedlist()))
                        return error();

                for (accessresult_map::iterator it = sids.begin(); it != sids.end(); ++it) {

                    mmsresult_ptr locrslt;
                    accessresult_map::const_iterator sfit = simplelist_.find(it->first);
                    if (sfit != simplelist_.end()) {
                        locrslt = sfit->second;
                    } else {
                        for (list_of_variable_vct::const_iterator lit = lists_.begin(); lit != lists_.end(); ++lit) {
                            accessresult_map::const_iterator fit = (*lit)->values().find(it->first);
                            if (fit != (*lit)->values().end()) {
                                locrslt = fit->second;
                                break;
                            }
                        }
                    }
                    it->second = locrslt;
                }
            }*/
            return error();
        }

        ns_error iec69870intf::send_commands(/*const mmscommand_vct& cmds, accesserror_map& errors*/) {

            check_connecton_state();

            /*try {

                errors.clear();
                typedef prot80670::write_operation_type write_operation_type;

                boost::shared_ptr<write_operation_type > operationW =
                        boost::shared_ptr<write_operation_type > (new write_operation_type());

                operationW->request_new();
                operationW->request()->variableAccessSpecification().listOfVariable__new();

                std::size_t currentcnt = 0;

                mmscommand_vct::const_iterator sit = cmds.begin();
                mmscommand_vct::const_iterator it = sit;

                while (it != cmds.end()) {

                    mmscommand_vct::const_iterator lsit = sit;

                    for (; it != cmds.end(); ++it) {

                        MMS::Data dt;

                        if (to_mms_command(it->second, find_access(it->first), dt)) {

                            MMS::VariableAccessSpecification::ListOfVariable_type_sequence_of vacs;
                            vacs.variableSpecification().name(new mmsobject_type(it->first->obj()));

                            operationW->request()->variableAccessSpecification().listOfVariable()->push_back(vacs);
                            operationW->request()->listOfData().push_back(dt);

                            if (++currentcnt >= blocksize) {
                                sit = ++it;
                                currentcnt = 0;
                                break;
                            }
                        } else
                            errors.insert(accesserror_pair(it->first, serviceerror_ptr()));

                        if (client_io->req<write_operation_type>(operationW)) {
                            if (operationW->response()) {
                            
                                mmscommand_vct::const_iterator vit = lsit;           
                                for (MMS::Write_Response::const_iterator rit=operationW->response()->begin();rit!=operationW->response()->end();++rit) {
                                    if (vit != cmds.end())
                                        if (rit->failure()){
                                            errors.insert(accesserror_pair(vit->first,  serviceerror_ptr()));
                                        }
                                        else
                                            break;
                                    
                                }

                            }
                        } else if (operationW->serviceerror()) {
                            errors.insert(accesserror_pair(it->first, operationW->serviceerror()));
                        } else {
                            errors.insert(accesserror_pair(it->first, serviceerror_ptr()));
                        }

                        operationW->request_new();
                        operationW->request()->variableAccessSpecification().listOfVariable__new();
                    }
                }
                } catch (const boost::itu::error_code& errcode) {
                    parse_error(errcode);
                } catch (...) {
                    parse_error(boost::itu::ER_PROTOCOL);
                }*/

            return error();
        }

        /*void iec69870intf::parse_error(const boost::itu::error_code& errcode) {
            if (errcode == boost::itu::ER_NOLINK) {
                error(ERROR_NONET_CONNECTED);
                throw dvnci::dvncierror(ERROR_NONET_CONNECTED);
            } else if (errcode == boost::itu::ER_BEDSEQ) {
                error(ERROR_PROTOCOL_SEQ);
                throw dvnci::dvncierror(ERROR_PROTOCOL_SEQ);
            } else if (errcode == boost::itu::ER_TIMEOUT) {
                error(ERROR_FAILNET_CONNECTED);
                throw dvnci::dvncierror(ERROR_FAILNET_CONNECTED);
            }
            error(ERROR_FAILNET_CONNECTED);
            throw dvnci::dvncierror(ERROR_PROTOCOL_ERROR);
        }*/

        void iec69870intf::check_connecton_state() {
            if (!isconnected()) {
                error(ERROR_IO_LINK_NOT_CONNECTION);
                throw dvncierror(ERROR_IO_LINK_NOT_CONNECTION);
            }
            error(0);
        }

    }
}

