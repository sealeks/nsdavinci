/* 
 * File:   iec60870_protocol.cpp
 * Author: Serg
 * 
 * Created on 18 ?????? 2010 ?., 17:22
 */

#include "iec60870_protocol.h"

namespace dvnci {
    namespace driver {
        
        bool calculate_mdb_lrc (const std::string& src, num8& lrc, std::string::size_type strt) {
            if (src.size() > strt) {
                lrc = 0;
                for (std::string::size_type it = strt; it < src.size(); ++it ) {
                    lrc = lrc + (src.at(it));}
                lrc = - lrc;
                return true;}
            return false;}

        bool insert_mdb_lrc (std::string& src, std::string::size_type strt) {
            num8 crc = 0;
            if (calculate_mdb_lrc(src, crc, strt)) {
                src = src + primtype_to_string<num8 > (crc);
                return true;}
            return false;}

        bool check_and_clear_mdb_lrc (std::string& src, std::string::size_type strt) {
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
                        return true;}}
            return false;}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*iec60870_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error iec60870_value_manager::parse_response_impl(std::string& val, parcel_ptr prcl, size_t bitn) {
            switch (prcl->kind()) {
                case DISCRET_INPUT_MODBUS_TYPE:
                case COIL_MODBUS_TYPE:{
                    if (!val.empty()) {
                        prcl->value_cast(static_cast<bool> ((val.at(0) & (0x01 << bitn))));}
                    else {
                        prcl->error(ERROR_IO_NO_DATA);}
                    break;};
                case INPUT_REGISTER_MODBUS_TYPE:
                case HOLDING_REGISTER_MODBUS_TYPE:{
                    if (bitn != NULL_BIT_NUM) {
                        unum16 tmp = 0;
                        if (spec_protocol_convertion_out(val)) {
                            if (string_to_primtype<unum16 > (val, tmp))
                                prcl->value_cast(static_cast<bool> (tmp & (0x01 << bitn)));}}
                    else {
                        switch (prcl->type()) {
                            case TYPE_NODEF:{
                                unum16 tmp = 0;
                                if (spec_protocol_convertion_out(val)) {
                                    if (string_to_primtype<unum16 > (val, tmp))
                                        prcl->value_cast<unum16 > (tmp);}
                                else {prcl->error(ERROR_IO_NO_PARSEDATA);};
                                break;}
                            default:{
                                return flatmemory_value_manager::parse_response_impl(val, prcl);}}}}}
            return error(0);}

        ns_error iec60870_value_manager::preapare_cmd_request_impl(std::string& val, parcel_ptr cmd, size_t bitn) {
            switch (cmd->kind()) {
                case DISCRET_INPUT_MODBUS_TYPE:
                case COIL_MODBUS_TYPE:{
                    bool tmp = cmd->value_cast<bool>();
                    val = primtype_to_string<num16 > (tmp ? ON_COIL_MODBUS_NM : OFF_COIL_MODBUS_NM);
                    return error(0);}
                case INPUT_REGISTER_MODBUS_TYPE:
                case HOLDING_REGISTER_MODBUS_TYPE:{
                    if (bitn != NULL_BIT_NUM) {
                        bool tmp = cmd->value_cast<bool>();
                        val = primtype_to_string<num16 > (tmp ? ON_COIL_MODBUS_NM : OFF_COIL_MODBUS_NM);}
                    else {
                        switch (cmd->type()) {
                            case TYPE_NODEF:{
                                if (cmd->isvalue()) {
                                    val = primtype_to_string<unum16 > (cmd->value_cast<unum16>());
                                    spec_protocol_convertion_in(val);
                                    return error(0);}
                                return error(ERROR_IO_NO_GENERATE_REQ);}
                            default:{
                                return flatmemory_value_manager::preapare_cmd_request_impl(val, cmd);}}}}}
            return error(ERROR_IO_NO_GENERATE_REQ);}



}}