/* 
 * File:   iec60870_protocol.cpp
 * Author: Serg
 * 
 * Created on 18 ?????? 2010 ?., 17:22
 */

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

        message_104::message_104() : type_(Null_type), typeU_(NULLu),
        tx_(0), rx_(0), body_(), error_(false) {
        }

        message_104::message_104(apcitypeU u) : type_(U_type), typeU_(u),
        tx_(0), rx_(0), body_(), error_(false) {
            encode_header();
        }

        message_104::message_104(tcpcounter_type rx) : type_(S_type), typeU_(NULLu),
        tx_(0), rx_(rx), body_(), error_(false) {
            encode_header();
        }



        message_104::message_104(tcpcounter_type tx, tcpcounter_type rx, const dataobject& vl, cause_type cs) : type_(I_type), typeU_(NULLu),
        tx_(tx), rx_(rx), error_(false) {
            encode_body(vl, cs);
            encode_header();
        }



        void message_104::message(const boost::asio::streambuf& vl) {
            body_ = octet_sequence(boost::asio::buffer_cast<const num8*>(vl.data()), 
                    boost::asio::buffer_cast<const num8*>(vl.data()) + (vl.size() < body_length() ? vl.size() : body_length()));
        }

        size_t message_104::body_length() const {
            size_t bl = 0;
            if (header_.size() == apci_length) {
                if (header_[0] == FC_START104) {
                    bl = static_cast<size_t> (*((unum8*) & header_[1]));
                    if (bl >= 4) {
                        bl -= 4;
                        return bl;
                    }
                }
            }
            return 0;
        }

        message_104::apcitype message_104::type() const {
            if (header_.size() < apci_length)
                return Null_type;
            octet_sequence::value_type mk = header_[2];
            if (!(header_[2]&1))
                return I_type;
            else if (header_[2]&3)
                return U_type;
            return S_type;
        }

        message_104::apcitypeU message_104::typeU() const {
            if (header_.size() < apci_length)
                return NULLu;
            octet_sequence::value_type mk = header_[2];
            if (mk & 3) {
                switch (0x3F & ((mk & 0xFC) >> 2)) {
                    case 1: return STARTDTact;
                    case 2: return STARTDTcon;
                    case 4: return STOPDTact;
                    case 8: return STOPDTcon;
                    case 16: return TESTFRact;
                    case 32: return TESTFRcon;
                    default:
                    {
                    }
                }
            }
            return NULLu;
        }


        void message_104::encode_header() {
            header_.clear();
            unum8 tmp_length = body_.size() + 4;
            header_.push_back(FC_START104);
            header_.push_back(tmp_length);
            switch (type_) {
                case S_type:
                {
                    unum16 tmprx = (rx_ << 1) & 0xFFFE;
                    header_.insert(header_.end(), (const char*) &HD104_U_IND, (const char*) &HD104_U_IND + 2);
                    header_.insert(header_.end(), (const char*) &tmprx,  (const char*) &tmprx + 2);
                    break;
                }
                case U_type:
                {
                    switch (typeU_) {
                        case TESTFRact:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_TESTFRact,(const char*) &HD104_TESTFRact+ 4);
                            break;
                        }
                        case TESTFRcon:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_TESTFRcon, (const char*) &HD104_TESTFRcon+ 4);
                            break;
                        }
                        case STARTDTact:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_STARTDTact, (const char*) &HD104_STARTDTact + 4);
                            break;
                        }
                        case STARTDTcon:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_STARTDTcon, (const char*) &HD104_STARTDTcon+  4);
                            break;
                        }
                        case STOPDTact:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_STOPDTact,(const char*) &HD104_STOPDTact + 4);
                            break;
                        }
                        case STOPDTcon:
                        {
                            header_.insert(header_.end(),(const char*) &HD104_STOPDTcon, (const char*) &HD104_STOPDTcon + 4);
                            break;
                        }
                        default:
                        {
                            error_ = true;
                        }
                    }
                    break;
                }
                case I_type:
                {
                    unum16 tmptx = (tx_ << 1) & 0xFFFE;
                    unum16 tmprx = (rx_ << 1) & 0xFFFE;
                    header_.insert(header_.end(),(const char*) &tmprx, (const char*) &tmprx + 2);
                    header_.insert(header_.end(),(const char*) &tmprx, (const char*) &tmprx + 2);
                    break;
                }
                default:
                {
                    error_ = true;
                }
            }
        }

        void message_104::encode_body(const dataobject& vl, cause_type cs) {
            body_.clear();
            type_id tmptype = vl.type();
            body_.push_back(tmptype);
            body_.insert(body_.end(), '\x1');
            body_.push_back(cs);
            body_.insert(body_.end(), '\x0');
            device_address tmpdev = vl.devnum();
            body_.insert(body_.end(), (const char*) &tmpdev,  (const char*) &tmpdev + 2);
            data_address tmpaddr = vl.address();
            body_.insert(body_.end(), (const char*) &tmpaddr,  (const char*) &tmpaddr +3);
            body_.insert(body_.end(), vl.data().begin(), vl.data().end());
        }

        /*bool message_104::decode_header() {
            if (header_.size() == apci_length) {
                if (header_[0] == FC_START104) {
                    body_length_ = static_cast<size_t> (*((unum8*) & header_[1]));
                    if (body_length_ >= 4) {
                        body_length_ -= 4;
                        return true;
                    } else
                        error_ = true;
                } else
                    error_ = true;
            } else
                error_ = true;
            body_length_ = 0;
            return false;
            
        }*/
    }
}