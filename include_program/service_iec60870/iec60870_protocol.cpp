/* 
 * File:   iec60870_protocol.cpp
 * Author: Serg
 * 
 * Created on 18 ?????? 2010 ?., 17:22
 */

#include <cstddef>

#include "iec60870_protocol.h"

namespace dvnci {
    namespace prot80670 {

        static string_type_id_map string_type_id_load() {
            string_type_id_map mp;
            mp.insert(string_type_id_pair("M_SP_NA", 1)); // Single-point information
            mp.insert(string_type_id_pair("M_SP_TA", 2)); //Single-point information with time-tag
            mp.insert(string_type_id_pair("M_DP_NA", 3)); //Double-point information
            mp.insert(string_type_id_pair("M_DP_TA", 4)); //Double-point information with time-tag
            mp.insert(string_type_id_pair("M_ST_NA", 5)); //Step position information
            mp.insert(string_type_id_pair("M_ST_TA", 6)); //Step position information with time-tag
            mp.insert(string_type_id_pair("M_BO_NA", 7)); //Bitstring of 32 bits
            mp.insert(string_type_id_pair("M_BO_TA", 8)); //Bitstring of 32 bits with time-tag
            mp.insert(string_type_id_pair("M_ME_NA", 9)); //Measured value, normalized value
            mp.insert(string_type_id_pair("M_ME_TA", 10)); //Measured value, normalized value with time-tag
            mp.insert(string_type_id_pair("M_ME_NB", 11)); //Measured value, scaled value
            mp.insert(string_type_id_pair("M_ME_TB", 12)); //Measured value, scaled value with time-tag
            mp.insert(string_type_id_pair("M_ME_NC", 13)); //Measured value, short floating point value
            mp.insert(string_type_id_pair("M_ME_TC", 14)); //Measured value, short floating point value with time-tag
            mp.insert(string_type_id_pair("M_IT_NA", 15)); //Integrated totals
            mp.insert(string_type_id_pair("M_IT_TA", 16)); //Integrated totals with time-tag
            mp.insert(string_type_id_pair("M_EP_TA", 17)); //Event of protection equipment with time-tag
            mp.insert(string_type_id_pair("M_EP_TB", 18)); //Packed start events of protection equipment with time-tag
            mp.insert(string_type_id_pair("M_EP_TC", 19)); //Packed output circuit information of protection equipment with timetag
            mp.insert(string_type_id_pair("M_PS_NA", 20)); //Packed single point information with status change detection
            mp.insert(string_type_id_pair("M_ME_ND", 21)); //Measured value, normalized value without quality descriptor
            mp.insert(string_type_id_pair("M_SP_TB", 30)); //Single-point information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_DP_TB", 31)); //Double-point information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ST_TB", 32)); //Step position information with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_BO_TB", 33)); //Bitstring of 32 bit with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TD", 34)); //Measured value, normalized value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TE", 35)); //Measured value, scaled value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_ME_TF", 36)); //Measured value, short floating point value with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_IT_TB", 37)); //Integrated totals with time tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TD", 38)); //Event of protection equipment with time-tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TE", 39)); //Packed start events of protection equipment with time-tag CP56Time2a
            mp.insert(string_type_id_pair("M_EP_TF", 40)); //Packed output circuit information of protection equipment with timetag CP56Time2a
            mp.insert(string_type_id_pair("C_SC_NA", 45)); // Single command 
            mp.insert(string_type_id_pair("C_DC_NA", 46)); // Double command
            mp.insert(string_type_id_pair("C_RC_NA", 47)); // Regulating step command
            mp.insert(string_type_id_pair("C_SE_NA", 48)); // Set point command, normalized value
            mp.insert(string_type_id_pair("C_SE_NB", 49)); // Set point command, scaled value
            mp.insert(string_type_id_pair("C_SE_NC", 50)); // Set point command, short floating point value
            mp.insert(string_type_id_pair("C_BO_NA", 51)); // Bitstring of 32 bit
            mp.insert(string_type_id_pair("C_SC_TA", 58)); // Single command with time tag CP56Time 2a 
            mp.insert(string_type_id_pair("C_DC_TA", 59)); // Double command with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_RC_TA", 60)); // Regulating step command with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TA", 61)); // Set point command, normalized value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TB", 62)); // Set point command, scaled value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_SE_TC", 63)); // Set point command, short floating point value with time tag CP56Time 2a
            mp.insert(string_type_id_pair("C_BO_TA", 64)); // Bitstring of 32 bit with time tag CP56Time 2a      
            mp.insert(string_type_id_pair("P_ME_NA", 110)); // Parameter of measured value, normalized value 110
            mp.insert(string_type_id_pair("P_ME_NB", 111)); // Parameter of measured value, scaled value
            mp.insert(string_type_id_pair("P_ME_NC", 112)); // Parameter of measured value, short floating point value
            mp.insert(string_type_id_pair("P_AC_NA", 113)); // Parameter activation            
            return mp;
        }

        static const string_type_id_map& get_type_id_map() {
            static string_type_id_map mp = string_type_id_load();
            return mp;
        }

        type_id find_type_id(const std::string& val) {
            const string_type_id_map& mp = get_type_id_map();
            string_type_id_map::const_iterator fit = mp.find(val);
            if (fit != mp.end())
                return fit->second;
            return 0;
        }

        static type_id_size_map size_type_id_load() {
            type_id_size_map mp;
            mp.insert(type_id_size_pair(M_SP_NA_1, 1)); // Single-point information 1
            mp.insert(type_id_size_pair(M_SP_TA_1, 4)); //Single-point information with time-tag 1 + 3(ta)
            mp.insert(type_id_size_pair(M_DP_NA_1, 1)); //Double-point information 1 
            mp.insert(type_id_size_pair(M_DP_TA_1, 4)); //Double-point information with time-tag  1 + 3(ta)
            mp.insert(type_id_size_pair(M_ST_NA_1, 3)); //Step position information 2 + 1(q)
            mp.insert(type_id_size_pair(6, 6)); //Step position information with time-tag 2 + 1(q) + 3(ta)
            mp.insert(type_id_size_pair(7, 5)); //Bitstring of 32 bits 4 + 1(q)
            mp.insert(type_id_size_pair(8, 8)); //Bitstring of 32 bits with time-tag  4 + 1(q) + 3(ta)
            mp.insert(type_id_size_pair(9, 3)); //Measured value, normalized value 2 + 1(q)
            mp.insert(type_id_size_pair(10, 6)); //Measured value, normalized value with time-tag 2 + 1(q) + 3(ta)
            mp.insert(type_id_size_pair(11, 3)); //Measured value, scaled value 2 + 1(q)
            mp.insert(type_id_size_pair(12, 6)); //Measured value, scaled value with time-tag 2 + 1(q) + 3(ta)
            mp.insert(type_id_size_pair(13, 5)); //Measured value, short floating point value 4 + 1(q)
            mp.insert(type_id_size_pair(14, 8)); //Measured value, short floating point value with time-tag 4 + 1(q) + 3(ta)
            mp.insert(type_id_size_pair(15, 5)); //Integrated totals 4 + 1(q)
            mp.insert(type_id_size_pair(16, 8)); //Integrated totals with time-tag 4 + 1(q) + 2(tm) + 3(ta)
            mp.insert(type_id_size_pair(17, 6)); //Event of protection equipment with time-tag 1 + 2(tm) + 3(ta)
            mp.insert(type_id_size_pair(18, 7)); //Packed start events of protection equipment with time-tag 1 + 1(q) + 2(tm) + 3(ta)
            mp.insert(type_id_size_pair(19, 7)); //Packed output circuit information of protection equipment with timetag 1 + 1(q) + 2(tm) + 3(ta)
            mp.insert(type_id_size_pair(20, 5)); //Packed single point information with status change detection 2 + 2 + 1(q)
            mp.insert(type_id_size_pair(21, 2)); //Measured value, normalized value without quality descriptor 2
            mp.insert(type_id_size_pair(30, 8)); //Single-point information with time tag CP56Time2a 1 + 7(tb)
            mp.insert(type_id_size_pair(31, 8)); //Double-point information with time tag CP56Time2a 1 + 7(tb)
            mp.insert(type_id_size_pair(32, 10)); //Step position information with time tag CP56Time2a 2 + 1(q) + 7(tb)
            mp.insert(type_id_size_pair(33, 12)); //Bitstring of 32 bit with time tag CP56Time2a 4 + 1(q) + 7(tb)
            mp.insert(type_id_size_pair(34, 10)); //Measured value, normalized value with time tag CP56Time2a  2 + 1(q) + 7(tb)
            mp.insert(type_id_size_pair(35, 10)); //Measured value, scaled value with time tag CP56Time2a 2 + 1(q) + 7(tb)
            mp.insert(type_id_size_pair(36, 12)); //Measured value, short floating point value with time tag CP56Time2a  4 + 1(q) + 7(tb)
            mp.insert(type_id_size_pair(37, 14)); //Integrated totals with time tag CP56Time2a  4 + 1(q) + 2(tm) + 7(tb)
            mp.insert(type_id_size_pair(38, 10)); //Event of protection equipment with time-tag CP56Time2a 1 + 2(tm) + 7(ta)
            mp.insert(type_id_size_pair(39, 11)); //Packed start events of protection equipment with time-tag CP56Time2a 1 + 1(q) + 2(tm) + 7(tb)
            mp.insert(type_id_size_pair(40, 11)); //Packed output circuit information of protection equipment with timetag CP56Time2a  1 + 1(q) + 2(tm) + 7(tb)
            mp.insert(type_id_size_pair(45, 1)); // Single command 1
            mp.insert(type_id_size_pair(46, 1)); // Double command 1
            mp.insert(type_id_size_pair(47, 1)); // Regulating step command 1
            mp.insert(type_id_size_pair(48, 3)); // Set point command, normalized value 2 + 1
            mp.insert(type_id_size_pair(49, 3)); // Set point command, scaled value 2 + 1
            mp.insert(type_id_size_pair(50, 5)); // Set point command, short floating point value 4 + 1
            mp.insert(type_id_size_pair(51, 5)); // Bitstring of 32 bit 4 + 1
            mp.insert(type_id_size_pair(58, 8)); // Single command with time tag CP56Time 2a 1 + 7(tb)
            mp.insert(type_id_size_pair(59, 8)); // Double command with time tag CP56Time 2a 1 + 7(tb)
            mp.insert(type_id_size_pair(60, 8)); // Regulating step command with time tag CP56Time 2a 1 + 7(tb)
            mp.insert(type_id_size_pair(61, 10)); // Set point command, normalized value with time tag CP56Time 2a 2 + 1 + 7(tb)
            mp.insert(type_id_size_pair(62, 10)); // Set point command, scaled value with time tag CP56Time 2a 2 + 1 + 7(tb)
            mp.insert(type_id_size_pair(63, 12)); // Set point command, short floating point value with time tag CP56Time 2a 4 + 1 + 7(tb)
            mp.insert(type_id_size_pair(64, 12)); // Bitstring of 32 bit with time tag CP56Time 2a 4 + 1 + 7(tb)              
            mp.insert(type_id_size_pair(100, 1)); // Activation     C_IC_NA
            mp.insert(type_id_size_pair(101, 1)); // Counter reequest     C_CI_NA            
            mp.insert(type_id_size_pair(110, 3)); // Parameter of measured value, normalized value 110 2 + 1
            mp.insert(type_id_size_pair(111, 3)); // Parameter of measured value, scaled value 2 + 1
            mp.insert(type_id_size_pair(112, 5)); // Parameter of measured value, short floating point value 4 + 1
            mp.insert(type_id_size_pair(113, 1)); // Parameter activation  1          
            return mp;
        }

        static const type_id_size_map& get_size_type_id_map() {
            static type_id_size_map mp = size_type_id_load();
            return mp;
        }

        std::size_t find_type_size(type_id val) {
            const type_id_size_map& mp = get_size_type_id_map();
            type_id_size_map::const_iterator fit = mp.find(val);
            if (fit != mp.end())
                return fit->second;
            return 0;
        }



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// dataobject
        /////////////////////////////////////////////////////////////////////////////////////////////////           

        dataobject_ptr dataobject::build_from_bind(device_address dev, std::string bind) {
            /* Name data type without _1 example M_SP_NA_1 => M_SP_NA == X_XX_XX
                         X_XX_XXNNNNN[.B]                
                         main templ = [CMP]_[ABSDEIMPRS][CEPTOS]_[TN][ABCDEF][0-9]{1,6}.{0,1}[0-9]{0,2}   
             */
            if (bind.size() > 7) {
                upper_and_trim(bind);
                std::string typedata = bind.substr(0, 7);
                std::string addrdata = bind.substr(7);
                type_id tp = find_type_id(typedata);
                bit_number bt = NULL_BITNUMBER;
                data_address addr = 0;
                if (tp) {
                    std::string::size_type bitit = addrdata.find('.', 0);
                    if ((bitit != std::string::npos) && (bitit != (addrdata.size() - 1))) {
                        std::string bitdata = addrdata.substr(bitit + 1);
                        addrdata = addrdata.substr(0, bitit);
                        if (!dvnci::str_to(addrdata, bt)) {
                            return dataobject_ptr();
                        }
                    }
                    if (!dvnci::str_to(addrdata, addr))
                        return dataobject_ptr();
                    return dataobject_ptr(new dataobject(dev, tp, addr, bt));
                }
            }
            return dataobject_ptr();

        }

        bool dataobject::readable() const {
            return (type_ && ((type_ <= M_EP_TF_1) || ((type_ >= P_ME_NA_1) || (type_ <= P_AC_NA_1))));
        }

        bool dataobject::command() const {
            return ((type_ >= C_SC_NA_1) || (type_ <= C_BO_TA_1));
        }

        bool operator==(const dataobject& ls, const dataobject& rs) {
            return ((ls.devnum_ == rs.devnum_) && (ls.address_ == rs.address_) && (ls.type_ == rs.type_));
        }

        bool operator<(const dataobject& ls, const dataobject& rs) {
            if (ls.devnum_ == rs.devnum_) {
                if (ls.type_ == rs.type_)
                    return ls.address_ < rs.address_;
                return ls.type_ < rs.type_;
            }
            return ls.devnum_ < rs.devnum_;
        }

        bool operator==(dataobject_ptr ls, dataobject_ptr rs) {
            if (ls && rs)
                return (*ls) == (*rs);
            return (!ls && !rs);
        }

        bool operator<(dataobject_ptr ls, dataobject_ptr rs) {
            if (ls && rs)
                return (*ls)<(*rs);
            if (!ls && !rs)
                return false;
            return !ls;
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
                    switch (tp) {
                        case M_SP_NA_1: /*1*/ //=1
                        {
                            return dvnci::short_value(dt[0]);
                        }
                        case M_SP_TA_1: /*2*/ //= 1 + 3(ta)
                        {
                            return dvnci::short_value::create_timed<boost::uint8_t>(dt[0], to_datetime_3(octet_sequence(dt.begin() + 1, dt.end())));
                        }
                        case M_SP_TB_1: /*30*/
                        {
                            return dvnci::short_value::create_timed<boost::uint8_t>(dt[0], to_datetime_7(octet_sequence(dt.begin() + 1, dt.end())));
                        }
                        case M_ME_TF_1: /*36*/
                        {
                            return dvnci::short_value::create_timed<float>(to_float_4(octet_sequence(dt.begin(), dt.begin() + 4)),
                                    to_datetime_7(octet_sequence(dt.begin() + 5, dt.end())));
                        }
                        default:
                        {
                        }
                    }
                }
            }
            return dvnci::short_value();
        }



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// asdu_body
        /////////////////////////////////////////////////////////////////////////////////////////////////

        asdu_body::asdu_body(dataobject_ptr vl, cause_type cs, bool sq, bool ngt, bool tst) : body_(new octet_sequence()) {
            body_->reserve(MAX_ASDU_SIZE);
            dataobject_vct tmp;
            tmp.push_back(vl);
            encode(tmp, cs, sq, ngt, tst);
        };

        asdu_body::asdu_body(const dataobject_vct& vl, cause_type cs, std::size_t cnt, bool sq, bool ngt, bool tst) : body_(new octet_sequence()) { // sq = 1 only the first information object has an information object address, all other information objects have the addresses +1, +2, ...
            body_->reserve(MAX_ASDU_SIZE);
            encode(vl, cs, sq, ngt, tst);
        }

        asdu_body::asdu_body(const dataobject_vct& vl, cause_type cs, bool sq, bool ngt, bool tst) : body_(new octet_sequence()) {// sq = 0  each information object has its own information object address in the message       
            body_->reserve(MAX_ASDU_SIZE);
            encode(vl, cs, sq, ngt, tst);
        }

        asdu_body::asdu_body(octet_sequence_ptr dt) : body_(dt) {
        }

        asdu_body asdu_body::create_activation(interrogation_type tp, cause_type cs) {
            dataobject_ptr vl(new dataobject(0, C_IC_NA_1, 1, octet_sequence(1, tp)));
            return asdu_body(vl, cs, false, false, false);
        }

        asdu_body asdu_body::create_polling(dataobject_ptr ob, cause_type cs) {
            dataobject_ptr vl(new dataobject(ob->devnum(), C_RD_NA_1, ob->address()));
            return asdu_body(vl, cs, false, false, false);
        }

        bool asdu_body::get(dataobject_vct& rslt) {
            rslt.clear();
            if (body().size() > 6) {
                type_id tp = type();
                device_address devaddr = address();
                std::size_t szdata = find_type_size(tp);
                std::size_t datacnt = count();
                std::size_t it = 6;
                if (!datacnt)
                    return true;
                if (szdata) {
                    if (sq()) {
                        if ((it + 3 + szdata) <= body().size()) {
                            data_address addr = *reinterpret_cast<const data_address*> (&(body()[it])) & 0xFFFFFF;
                            octet_sequence data(&body()[it + 3], &body()[it + 3] + szdata);
                            rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, addr, data)));
                            it = it + 3 + szdata;
                            datacnt--;
                            while ((datacnt--) && ((it + szdata) <= body().size())) {
                                octet_sequence data(&body()[it], &body()[it] + szdata);
                                rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, ++addr, data)));
                                it = it + 3 + szdata;
                            }
                            return !(rslt.empty());
                        }
                    } else {
                        while ((datacnt--) && ((it + 3 + szdata) <= body().size())) {
                            data_address addr = (*reinterpret_cast<const data_address*> (&(body()[it]))) & 0xFFFFFF;
                            octet_sequence data(&body()[it + 3], &body()[it + 3] + szdata);
                            rslt.push_back(dataobject_ptr(new dataobject(devaddr, tp, addr, data)));
                            it = it + 3 + szdata;
                        }
                        return !(rslt.empty());
                    }
                }
            }
            return false;
        }

        void asdu_body::encode(const dataobject_vct& vl, cause_type cs, bool sq, bool ngt, bool tst) {
            body().clear();
            if (!vl.empty()) {
                dataobject_ptr hdrelm = vl[0];
                body().push_back(hdrelm->type());
                boost::uint8_t szobj = static_cast<boost::uint8_t> (vl.size());
                if (sq)
                    szobj |= '\x80';
                body().push_back(szobj);
                if (tst)
                    cs |= '\x80';
                if (ngt)
                    cs |= '\x40';
                body().push_back(cs);
                body().push_back(0);
                device_address tmpdev = hdrelm->devnum();
                body().insert(body().end(), (const char*) &tmpdev, (const char*) &tmpdev + 2);
                if (sq) {
                    for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                        data_address tmpaddr = (*it)->address();
                        body().insert(body().end(), (const char*) &tmpaddr, (const char*) &tmpaddr + 3);
                        body().insert(body().end(), (*it)->data().begin(), (*it)->data().end());
                    }
                } else {
                    data_address tmpaddr = hdrelm->address();
                    body().insert(body().end(), (const char*) &tmpaddr, (const char*) &tmpaddr + 3);
                    for (dataobject_vct::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                        body().insert(body().end(), (*it)->data().begin(), (*it)->data().end());
                    }
                }
            }
        }




        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870_PM
        /////////////////////////////////////////////////////////////////////////////////////////////////         

        iec60870_PM::iec60870_PM(timeouttype tmo, iec60870_data_listener_ptr listr) :
        io_service_(), tmout_timer(io_service_), short_timer(io_service_),
        state_(disconnected), pmstate_(noconnected), timout(tmo), need_disconnect_(false), listener_(listr) {
        }

        iec60870_PM::~iec60870_PM() {
            //if (state_ == connected) disconnect();
        }

        void iec60870_PM::pmstate(iec60870_PM::PMState vl) {
            pmstate_ = vl;
        }

        bool iec60870_PM::initialize() {
            return true;
        }

        bool iec60870_PM::uninitialize() {
            return true;
        }

        bool iec60870_PM::operator()() {
            try{
            connect();
            }
            catch(...){
                
            }
            iec60870_data_listener_ptr lstnr = listener();
            if (lstnr)
                lstnr->terminate60870();
            return true;
        }

        bool iec60870_PM::add_items(const indx_dataobject_vct& cids, indx_dataobject_vct& rslt) {
            THD_EXCLUSIVE_LOCK(mtx)
            for (indx_dataobject_vct::const_iterator it = cids.begin(); it != cids.end(); ++it) {
                dataobject_set::const_iterator fnd = data_.find(it->second);
                if (fnd != data_.end()) {
                    rslt.push_back(indx_dataobject_pair(it->first, dataobject_ptr(new dataobject(*(*fnd)))));
                } else {
                    if (it->second->readable()) {
                        waitrequestdata_.push_back(it->second);
                    }
                }
                if (it->second->readable())
                    inrequestdata_.insert(it->second);
            }
            return !rslt.empty();
        }

        bool iec60870_PM::remove_items(const dataobject_set& cids) {
            THD_EXCLUSIVE_LOCK(mtx)
            for (dataobject_set::const_iterator it = cids.begin(); it != cids.end(); ++it)
                inrequestdata_.erase(*it);
            return true;
        }

        bool iec60870_PM::read_items(const dataobject_set& cids) {
            THD_EXCLUSIVE_LOCK(mtx)
            for (dataobject_set::const_iterator it = cids.begin(); it != cids.end(); ++it)
                if (std::find(waitrequestdata_.begin(), waitrequestdata_.end(), *it) == waitrequestdata_.end())
                    waitrequestdata_.push_back(*it);
            return true;
        }        

        void iec60870_PM::to_listener(const dataobject_vct& dt) {
            iec60870_data_listener_ptr lstnr = listener();
            if (lstnr) {
                THD_EXCLUSIVE_LOCK(mtx)
                for (dataobject_vct::const_iterator it = dt.begin(); it != dt.end(); ++it) {
                    if (inrequestdata_.find(*it) != inrequestdata_.end())
                        lstnr->execute60870(dt);
                }
            }
        }

        void iec60870_PM::error(boost::system::error_code& err) {
            iec60870_data_listener_ptr lstnr = listener();
            if (lstnr)
                lstnr->execute60870(err);
        }

    }
}