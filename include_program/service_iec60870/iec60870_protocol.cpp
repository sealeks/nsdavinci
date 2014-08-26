/* 
 * File:   iec60870_protocol.cpp
 * Author: Serg
 * 
 * Created on 18 ?????? 2010 ?., 17:22
 */

#include "iec60870_protocol.h"

namespace dvnci {
    namespace driver {

        static string_parcelkind_map string_parcelkind_load() {
            string_parcelkind_map mp;
            mp.insert(string_parcelkind_pair("M_SP_NA", 1)); // Single-point information
            mp.insert(string_parcelkind_pair("M_SP_TA", 2)); //Single-point information with time-tag
            mp.insert(string_parcelkind_pair("M_DP_NA", 3)); //Double-point information
            mp.insert(string_parcelkind_pair("M_DP_TA", 4)); //Double-point information with time-tag
            mp.insert(string_parcelkind_pair("M_ST_NA", 5)); //Step position information
            mp.insert(string_parcelkind_pair("M_ST_TA", 6)); //Step position information with time-tag
            mp.insert(string_parcelkind_pair("M_BO_NA", 7)); //Bitstring of 32 bits
            mp.insert(string_parcelkind_pair("M_BO_TA", 8)); //Bitstring of 32 bits with time-tag
            mp.insert(string_parcelkind_pair("M_ME_NA", 9)); //Measured value, normalized value
            mp.insert(string_parcelkind_pair("M_ME_TA", 10)); //Measured value, normalized value with time-tag
            mp.insert(string_parcelkind_pair("M_ME_NB", 11)); //Measured value, scaled value
            mp.insert(string_parcelkind_pair("M_ME_TB", 12)); //Measured value, scaled value with time-tag
            mp.insert(string_parcelkind_pair("M_ME_NC", 13)); //Measured value, short floating point value
            mp.insert(string_parcelkind_pair("M_ME_TC", 14)); //Measured value, short floating point value with time-tag
            mp.insert(string_parcelkind_pair("M_IT_NA", 15)); //Integrated totals
            mp.insert(string_parcelkind_pair("M_IT_TA", 16)); //Integrated totals with time-tag
            mp.insert(string_parcelkind_pair("M_EP_TA", 17)); //Event of protection equipment with time-tag
            mp.insert(string_parcelkind_pair("M_EP_TB", 18)); //Packed start events of protection equipment with time-tag
            mp.insert(string_parcelkind_pair("M_EP_TC", 19)); //Packed output circuit information of protection equipment with timetag
            mp.insert(string_parcelkind_pair("M_PS_NA", 20)); //Packed single point information with status change detection
            mp.insert(string_parcelkind_pair("M_ME_ND", 21)); //Measured value, normalized value without quality descriptor
            mp.insert(string_parcelkind_pair("M_SP_TB", 30)); //Single-point information with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_DP_TB", 31)); //Double-point information with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_ST_TB", 32)); //Step position information with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_BO_TB", 33)); //Bitstring of 32 bit with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_ME_TD", 34)); //Measured value, normalized value with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_ME_TE", 35)); //Measured value, scaled value with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_ME_TF", 36)); //Measured value, short floating point value with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_IT_TB", 37)); //Integrated totals with time tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_EP_TD", 38)); //Event of protection equipment with time-tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_EP_TE", 39)); //Packed start events of protection equipment with time-tag CP56Time2a
            mp.insert(string_parcelkind_pair("M_EP_TF", 40)); //Packed output circuit information of protection equipment with timetag CP56Time2a
            mp.insert(string_parcelkind_pair("C_SC_NA", 45)); // Single command 
            mp.insert(string_parcelkind_pair("C_DC_NA", 46)); // Double command
            mp.insert(string_parcelkind_pair("C_RC_NA", 47)); // Regulating step command
            mp.insert(string_parcelkind_pair("C_SE_NA", 48)); // Set point command, normalized value
            mp.insert(string_parcelkind_pair("C_SE_NB", 49)); // Set point command, scaled value
            mp.insert(string_parcelkind_pair("C_SE_NC", 50)); // Set point command, short floating point value
            mp.insert(string_parcelkind_pair("C_BO_NA", 51)); // Bitstring of 32 bit
            mp.insert(string_parcelkind_pair("C_SC_TA", 58)); // Single command with time tag CP56Time 2a 
            mp.insert(string_parcelkind_pair("C_DC_TA", 59)); // Double command with time tag CP56Time 2a
            mp.insert(string_parcelkind_pair("C_RC_TA", 60)); // Regulating step command with time tag CP56Time 2a
            mp.insert(string_parcelkind_pair("C_SE_TA", 61)); // Set point command, normalized value with time tag CP56Time 2a
            mp.insert(string_parcelkind_pair("C_SE_TB", 62)); // Set point command, scaled value with time tag CP56Time 2a
            mp.insert(string_parcelkind_pair("C_SE_TC", 63)); // Set point command, short floating point value with time tag CP56Time 2a
            mp.insert(string_parcelkind_pair("C_BO_TA", 64)); // Bitstring of 32 bit with time tag CP56Time 2a      
            mp.insert(string_parcelkind_pair("P_ME_NA", 110)); // Parameter of measured value, normalized value 110
            mp.insert(string_parcelkind_pair("P_ME_NB", 111)); // Parameter of measured value, scaled value
            mp.insert(string_parcelkind_pair("P_ME_NC", 112)); // Parameter of measured value, short floating point value
            mp.insert(string_parcelkind_pair("P_AC_NA", 113)); // Parameter activation            
            return mp;
        }

        static const string_parcelkind_map& get_parcelkind_map() {
            static string_parcelkind_map mp = string_parcelkind_load();
            return mp;
        }

        parcelkind find_parcelkind(const std::string& val) {
            const string_parcelkind_map& mp = get_parcelkind_map();
            string_parcelkind_map::const_iterator fit = mp.find(val);
            if (fit != mp.end())
                return fit->second;
            return 0;
        }

        bool calculate_mdb_lrc(const std::string& src, num8& lrc, std::string::size_type strt) {
            if (src.size() > strt) {
                lrc = 0;
                for (std::string::size_type it = strt; it < src.size(); ++it) {
                    lrc = lrc + (src.at(it));
                }
                lrc = -lrc;
                return true;
            }
            return false;
        }

        bool insert_mdb_lrc(std::string& src, std::string::size_type strt) {
            num8 crc = 0;
            if (calculate_mdb_lrc(src, crc, strt)) {
                src = src + primtype_to_string<num8 > (crc);
                return true;
            }
            return false;
        }

        bool check_and_clear_mdb_lrc(std::string& src, std::string::size_type strt) {
            if (src.size()<(strt + 2)) return false;
            num8 crc = 0;
            num8 reqcrc = 0;
            std::string::size_type it = src.size() - 2;
            std::string ch_src = src.substr(0, it);
            std::string txt_crc = src.substr(it);
            std::string ch_src_cnv = "";
            if (!hexsequence_to_binary_block(ch_src, ch_src_cnv))
                return false;
            if (calculate_mdb_lrc(ch_src_cnv, crc, strt)) {
                if (hexstr_to<num8 > (txt_crc, reqcrc))
                    if (crc == reqcrc) {
                        src = ch_src;
                        return true;
                    }
            }
            return false;
        }


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*iec60870_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error iec60870_value_manager::parse_response_impl(std::string& val, parcel_ptr prcl, size_t bitn) {
            switch (prcl->kind()) {
                case DISCRET_INPUT_MODBUS_TYPE:
                case COIL_MODBUS_TYPE:
                {
                    if (!val.empty()) {
                        prcl->value_cast(static_cast<bool> ((val.at(0) & (0x01 << bitn))));
                    } else {
                        prcl->error(ERROR_IO_NO_DATA);
                    }
                    break;
                };
                case INPUT_REGISTER_MODBUS_TYPE:
                case HOLDING_REGISTER_MODBUS_TYPE:
                {
                    if (bitn != NULL_BIT_NUM) {
                        unum16 tmp = 0;
                        if (spec_protocol_convertion_out(val)) {
                            if (string_to_primtype<unum16 > (val, tmp))
                                prcl->value_cast(static_cast<bool> (tmp & (0x01 << bitn)));
                        }
                    } else {
                        switch (prcl->type()) {
                            case TYPE_NODEF:
                            {
                                unum16 tmp = 0;
                                if (spec_protocol_convertion_out(val)) {
                                    if (string_to_primtype<unum16 > (val, tmp))
                                        prcl->value_cast<unum16 > (tmp);
                                } else {
                                    prcl->error(ERROR_IO_NO_PARSEDATA);
                                };
                                break;
                            }
                            default:
                            {
                                return flatmemory_value_manager::parse_response_impl(val, prcl);
                            }
                        }
                    }
                }
            }
            return error(0);
        }

        ns_error iec60870_value_manager::preapare_cmd_request_impl(std::string& val, parcel_ptr cmd, size_t bitn) {
            switch (cmd->kind()) {
                case DISCRET_INPUT_MODBUS_TYPE:
                case COIL_MODBUS_TYPE:
                {
                    bool tmp = cmd->value_cast<bool>();
                    val = primtype_to_string<num16 > (tmp ? ON_COIL_MODBUS_NM : OFF_COIL_MODBUS_NM);
                    return error(0);
                }
                case INPUT_REGISTER_MODBUS_TYPE:
                case HOLDING_REGISTER_MODBUS_TYPE:
                {
                    if (bitn != NULL_BIT_NUM) {
                        bool tmp = cmd->value_cast<bool>();
                        val = primtype_to_string<num16 > (tmp ? ON_COIL_MODBUS_NM : OFF_COIL_MODBUS_NM);
                    } else {
                        switch (cmd->type()) {
                            case TYPE_NODEF:
                            {
                                if (cmd->isvalue()) {
                                    val = primtype_to_string<unum16 > (cmd->value_cast<unum16>());
                                    spec_protocol_convertion_in(val);
                                    return error(0);
                                }
                                return error(ERROR_IO_NO_GENERATE_REQ);
                            }
                            default:
                            {
                                return flatmemory_value_manager::preapare_cmd_request_impl(val, cmd);
                            }
                        }
                    }
                }
            }
            return error(ERROR_IO_NO_GENERATE_REQ);
        }



    }
}