/* 
 * File:   extnetintf.cpp
 * Author: Alexeev
 * 
 * Created on 14 �?юнь 2011 г., 16:16
 */

#include "extiec60870intf.h"

namespace dvnci {


    namespace external {

        using namespace prot80670;


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// external::exiec870intf
        /////////////////////////////////////////////////////////////////////////////////////////////////

        extiec60870intf::extiec60870intf(tagsbase_ptr intf_, executor* exctr, indx grp) :
        extintf_wraper<prot80670::dataobject_ptr>(intf_, exctr, grp, TYPE_SIMPLE_REQ, CONTYPE_ASYNC),
        iec60870_data_listener(), fatal_(), linkaddrsize(0), sync_error_(0) {
        }

        extiec60870intf::extiec60870intf(tagsbase_ptr intf_, executor* exctr, const indx_set& grps, const metalink& lnk) :
        extintf_wraper<prot80670::dataobject_ptr>(intf_, exctr, grps, lnk, TYPE_SIMPLE_REQ, CONTYPE_ASYNC), iec60870_data_listener(), fatal_(),
        linkaddrsize(0), sync_error_(0) {
        }

        extiec60870intf::~extiec60870intf() {
            disconnect();
        }

        void extiec60870intf::execute60870(dataobject_ptr vl, const boost::system::error_code& err) {
            write_val_sid(vl, to_short_value(vl));
        };

        void extiec60870intf::execute60870(const dataobject_vct& vl, const boost::system::error_code& err) {
            for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it)
                execute60870(*it);
        }

        void extiec60870intf::execute60870(device_address dev, const boost::system::error_code& err) {
            error(ERROR_NONET_CONNECTED);
        };

        void extiec60870intf::execute60870(const boost::system::error_code& err) {
            error(ERROR_NONET_CONNECTED);
        }

        void extiec60870intf::terminate60870() {
            fatal_ = dvnci::dvncierror(ERROR_NONET_CONNECTED);
        }

        ns_error extiec60870intf::checkserverstatus() {
            if (fatal_) {
                kill_pm();
                dvnci::dvncierror tmp = fatal_;
                fatal_ = dvnci::dvncierror();
                throw dvnci::dvncierror(ERROR_NONET_CONNECTED);
            }
            return error(pm_connected() ? 0 : ERROR_IO_LINK_NOT_CONNECTION);
        }

        ns_error extiec60870intf::connect_impl() {
            try {
                if (!syncoption()) {
                    if (!thread_io) {
                        IEC_PROTOCOL proto = prot80670::protocol_from(intf->groups()->link(groups().empty() ? group() : (*groups().begin())).protocol());
                        iec_option opt(intf->groups()->option(groups().empty() ? group() : (*groups().begin())));
                        switch (proto) {
                            case prot80670::IEC_104:
                            {
                                tcp_endpoint_struct endp = get_tcp_endpoint(link().host(), "2404");
                                thread_io = create_pm(endp.host, endp.port, opt,
                                        iec60870_data_listener::shared_from_this());
                                break;
                            }
                            default:
                            {
                                opt.baundrate(link().inf().cominf.boundrate);
                                thread_io = create_pm(proto, link().chanalnum(), opt,
                                        iec60870_data_listener::shared_from_this());
                            }
                        }
                    }
                    state_ = connected;
                    return error(pm_connected() ? 0 : ERROR_IO_LINK_NOT_CONNECTION);
                } else
                    error(ERROR_IO_NOSYNC_LINK);
            } catch (...) {
            }
            state_ = disconnected;
            return error(ERROR_BASENOTFOUND);
        }

        ns_error extiec60870intf::disconnect_impl() {
            try {
                if (thread_io) {
                    thread_io->pm()->disconnect();
                    thread_io->join();
                }
            } catch (...) {
            }
            kill_pm();
            return error(0);
        }

        ns_error extiec60870intf::add_request_impl() {
            error(0);
            if (pm_connected()) {
                if (need_add().empty())
                    return error();
                indx_dataobject_vct cids;
                indx_dataobject_vct command_cids;
                indx_set tmpadd = need_add();
                for (indx_set::const_iterator it = tmpadd.begin(); it != tmpadd.end(); ++it) {
                    if (intf->exists(*it)) {
                        dataobject_ptr tmp = dataobject::build_from_bind(linkaddr() ?
                                intf->groups()->devnum(intf->group(*it)) : 0, intf->binding(*it));
                        if (tmp) {
                            if (tmp->readable())
                                cids.push_back(indx_dataobject_pair(*it, tmp));
                            else
                                command_cids.push_back(indx_dataobject_pair(*it, tmp));
                        } else
                            req_error(*it, ERROR_BINDING);
                    } else {
                        req_error(*it, ERROR_ENTNOEXIST);
                    }
                }
                if (cids.empty()) return error(0);

                indx_dataobject_vct rslt;
                thread_io->pm()->add_items(cids, rslt);

                for (indx_dataobject_vct::const_iterator it = cids.begin(); it != cids.end(); ++it)
                    add_simple(it->first, it->second);
                for (indx_dataobject_vct::const_iterator it = command_cids.begin(); it != command_cids.end(); ++it)
                    add_simple(it->first, it->second);
                for (indx_dataobject_vct::const_iterator it = rslt.begin(); it != rslt.end(); ++it)
                    write_val_id(it->first, to_short_value(it->second));
            }
            return error();
        }

        ns_error extiec60870intf::remove_request_impl() {

            error(0);
            if (need_remove().empty())
                return error();

            const dataobject_set& sids = need_remove();

            thread_io->pm()->remove_items(sids);
            remove_clear();

            return error();
        }

        ns_error extiec60870intf::value_request_impl() {

            error(0);

            const serverkeys_tags_map& simpreq = simple_req();
            dataobject_set sids;

            for (serverkey_const_iterator it = simpreq.left.begin(); it != simpreq.left.end(); ++it)
                sids.insert(it->first);

            thread_io->pm()->read_items(sids);

            return error();
        }

        ns_error extiec60870intf::command_request_impl(const sidcmd_map& cmds) {

            /*   error(0);
                   if (cmds.empty())  
                       return error();
                           
                   mmscommand_vct reqcmds; 
                   accesserror_map   errors;

                   for (sidcmd_map::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                       mmscommand_pair cmd = mmscommand_pair(it->first, it->second);
                       reqcmds.push_back(cmd);
                   }
                
                   if (reqcmds.empty())
                       return error(ERROR_NODATA);
                
                   return error(remintf->send_commands(reqcmds, errors));}

               ns_error extiec60870intf::report_request_impl() {
                   return error(0);
               }

               ns_error extiec60870intf::event_request_impl() {
                   return error(0);
               }*/

            return error();
        }

        ns_error extiec60870intf::report_request_impl() {
            return error();
        };

        ns_error extiec60870intf::event_request_impl() {
            return error();
        };

        iec60870_thread_ptr extiec60870intf::create_pm(const std::string& host, const std::string& port,
                const iec_option& opt, iec60870_data_listener_ptr listr) {
            return iec60870_factory::create(host, port, opt, listr);
        }

        iec60870_thread_ptr extiec60870intf::create_pm(prot80670::IEC_PROTOCOL prot,
                chnlnumtype chnm, const iec_option& opt, iec60870_data_listener_ptr listr) {
            return iec60870_factory::create(prot, chnm, opt, listr);
        }

        bool extiec60870intf::pm_connected() const {
            return ((thread_io) && (thread_io->pm()->state() == prot80670::iec60870_PM::connected));
        }

        void extiec60870intf::kill_pm() {
            disconnect_util();
            if (thread_io)
                thread_io.reset();
            state_ = disconnected;
        }

        std::size_t extiec60870intf::linkaddr() const {
            return linkaddrsize;
        }

        void extiec60870intf::linkaddr(IEC_PROTOCOL proto, const iec_option& opotions) {
            if ((proto != prot80670::IEC_104) && (proto != prot80670::IEC_NULL))
                linkaddrsize = static_cast<std::size_t> (opotions.addr());
            else
                linkaddrsize = 0;
        }

        dvnci::ns_error extiec60870intf::syncoption() {
            if (!sync_error_) {
                IEC_PROTOCOL proto1 = prot80670::IEC_NULL;
                if (!groups().empty()) {
                    metalink lnk1 = intf->groups()->link(*groups().begin());
                    proto1 = prot80670::protocol_from(lnk1.protocol());
                    iec_option opt1(intf->groups()->option(*groups().begin()));
                    indx_set::const_iterator it = groups().begin();
                    it++;
                    while (it != groups().end()) {
                        metalink lnk2 = intf->groups()->link(*it);
                        IEC_PROTOCOL proto2 = prot80670::protocol_from(lnk1.protocol());
                        iec_option opt2(intf->groups()->option(*it));
                        if (proto1 != proto2)
                            return sync_error_ = ERROR_IO_NOSYNC_LINK;
                        if (proto1 != prot80670::IEC_104) {
                            if ((opt1.addr() != opt2.addr()) || (opt1.cot() != opt2.cot()) ||
                                    (opt1.ioa() != opt2.ioa()) || (opt1.sector() != opt2.sector()) ||
                                    (lnk1.inf().cominf.boundrate != lnk2.inf().cominf.boundrate))
                                return sync_error_ = ERROR_IO_NOSYNC_LINK;
                        }
                        it++;
                    }
                    if (proto1 == prot80670::IEC_NULL)
                        return sync_error_ = ERROR_IO_NOSYNC_LINK;
                    linkaddr(proto1, opt1);
                    return sync_error_ = 0;
                } else {
                    proto1 = prot80670::protocol_from(intf->groups()->link(group()));
                }
                if (proto1 == prot80670::IEC_NULL)
                    return sync_error_ = ERROR_IO_NOSYNC_LINK;
                iec_option opt1(intf->groups()->option(group()));
                linkaddr(proto1, opt1);
            }
            return sync_error_;
        }

        void error_and_valid_QDS(boost::uint8_t vl, vlvtype& vld, ns_error& err) {
            vld = FULL_VALID;
            err = (vl & 1) ? ERROR_DATA_OUT_OF_RANGE : 0;            
        }

        datetime to_datetime_7(const octet_sequence& vl) {
            try {
                if (vl.size() == 7) {
                    boost::uint16_t ms = *reinterpret_cast<const uint16_t *> (&vl[0]);
                    boost::uint8_t min = (*reinterpret_cast<const uint8_t *> (&vl[2])) & '\x3F';
                    boost::uint8_t hour = *reinterpret_cast<const uint8_t *> (&vl[3]) & '\x1F';
                    boost::uint8_t day = *reinterpret_cast<const uint8_t *> (&vl[4]) & '\x1F';
                    boost::uint8_t month = *reinterpret_cast<const uint8_t *> (&vl[5])& '\xF';
                    boost::uint8_t year = *reinterpret_cast<const uint8_t *> (&vl[6]) & '\x2F';
                    return boost::posix_time::ptime(boost::gregorian::date(2000 + year, month, day)) +
                            boost::posix_time::time_duration(hour, min, ms / 1000) + boost::posix_time::millisec(ms % 1000);
                }
            } catch (...) {

            }
            return datetime();
        }

        boost::int16_t to_int16_t(const octet_sequence& vl) {
            return (vl.size() == 2) ? (*reinterpret_cast<const boost::int16_t *> (&vl[0])) : 0;
        }

        datetime to_datetime_3(const octet_sequence& vl) {
            try {
                if (vl.size() == 3) {
                    boost::uint16_t ms = *reinterpret_cast<const uint16_t *> (&vl[0]);
                    boost::uint8_t min = (*reinterpret_cast<const uint8_t *> (&vl[2])) & '\x3F';
                    datetime n = now();
                    datetime f1 = boost::posix_time::ptime(boost::gregorian::date(n.date())) +
                            boost::posix_time::time_duration(n.time_of_day().hours(), min, ms / 1000) + boost::posix_time::millisec(ms % 1000);
                    datetime f2 = f1 - boost::posix_time::hours(1);
                    return ((f2 - n)>(n - f1)) ? f1 : f2;
                }
            } catch (...) {
            }
            return datetime();
        }

        float to_float_4(const octet_sequence& vl) {
            if (vl.size() == 4) {
                return *reinterpret_cast<const float *> (&vl[0]);
            }
            return std::numeric_limits<float>::quiet_NaN();
        }

        dvnci::short_value to_short_value(dataobject_ptr vl) {
            if (vl) {
                type_id tp = vl->type();
                if ((tp) && (find_type_size(tp) == vl->data().size())) {
                    const octet_sequence& dt = vl->data();
                    vlvtype valid = FULL_VALID;
                    ns_error error = 0;
                    switch (tp) {
                        case M_SP_NA_1: /*1*/ //=1
                        {
                            return dvnci::short_value(dt[0]);
                        }
                        case M_SP_TA_1: /*2*/ //= 1 + 3(ta)
                        {
                            return dvnci::short_value::create_timed<boost::uint8_t>(dt[0], to_datetime_3(octet_sequence(dt.begin() + 1, dt.end())));
                        }
                        case M_ME_NB_1: /*11*/ //= 2 + 1(q)
                        {
                            error_and_valid_QDS(dt[2], valid, error);
                            return dvnci::short_value::create_timed<boost::int16_t>(to_int16_t(octet_sequence(dt.begin(), dt.begin() + 2)), valid, error);
                        }
                        case M_SP_TB_1: /*30*/ // 1 + 7(tb)
                        {
                            return dvnci::short_value::create_timed<boost::uint8_t>(dt[0], to_datetime_7(octet_sequence(dt.begin() + 1, dt.end())));
                        }
                        case M_ME_TE_1: /*35*/ //2 + 1(q) + 7(tb)
                        {
                            error_and_valid_QDS(dt[2], valid, error);
                            return dvnci::short_value::create_timed<boost::int16_t>(to_int16_t(octet_sequence(dt.begin(),
                                    dt.begin() + 2)), to_datetime_7(octet_sequence(dt.begin() + 3, dt.end())), valid, error);
                        }
                        case M_ME_TF_1: /*36*/ //4 + 1(q) + 7(tb)
                        {
                            error_and_valid_QDS(dt[4], valid, error);
                            return dvnci::short_value::create_timed<float>(to_float_4(octet_sequence(dt.begin(), dt.begin() + 4)),
                                    to_datetime_7(octet_sequence(dt.begin() + 5, dt.end())), valid, error);
                        }
                        default:
                        {
                        }
                    }
                }
            }
            return dvnci::short_value();
        }



    }
}

