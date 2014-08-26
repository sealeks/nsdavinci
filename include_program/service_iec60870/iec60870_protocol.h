/* 
 * File:   iec60870_protocol.h
 * Author: Serg
 *
 * Created on 18 ?????? 2010 ?., 17:22
 */

#ifndef MODBUS_PROTOCOL_H
#define	MODBUS_PROTOCOL_H

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/driver_detail.h>
#include <kernel/basis_iostream.h>



namespace dvnci {
    namespace driver {

       
        const parcelkind M_SP_NA_1 = 1; //Single-point information
        const parcelkind M_SP_TA_1 = 2; //Single-point information with time-tag
        const parcelkind M_DP_NA_1 = 3; //Double-point information
        const parcelkind M_DP_TA_1 = 4; //Double-point information with time-tag
        const parcelkind M_ST_NA_1 = 5; //Step position information
        const parcelkind M_ST_TA_1 = 6; //Step position information with time-tag
        const parcelkind M_BO_NA_1 = 7; //Bitstring of 32 bits
        const parcelkind M_BO_TA_1 = 8; //Bitstring of 32 bits with time-tag
        const parcelkind M_ME_NA_1 = 9; //Measured value, normalized value
        const parcelkind M_ME_TA_1 = 10; //Measured value, normalized value with time-tag
        const parcelkind M_ME_NB_1 = 11; //Measured value, scaled value
        const parcelkind M_ME_TB_1 = 12; //Measured value, scaled value with time-tag
        const parcelkind M_ME_NC_1 = 13; //Measured value, short floating point value
        const parcelkind M_ME_TC_1 = 14; //Measured value, short floating point value with time-tag
        const parcelkind M_IT_NA_1 = 15; //Integrated totals
        const parcelkind M_IT_TA_1 = 16; //Integrated totals with time-tag
        const parcelkind M_EP_TA_1 = 17; //Event of protection equipment with time-tag
        const parcelkind M_EP_TB_1 = 18; //Packed start events of protection equipment with time-tag
        const parcelkind M_EP_TC_1 = 19; //Packed output circuit information of protection equipment with timetag
        const parcelkind M_PS_NA_1 = 20; //Packed single point information with status change detection
        const parcelkind M_ME_ND_1 = 21; //Measured value, normalized value without quality descriptor
        const parcelkind M_SP_TB_1 = 30; //Single-point information with time tag CP56Time2a
        const parcelkind M_DP_TB_1 = 31; //Double-point information with time tag CP56Time2a
        const parcelkind M_ST_TB_1 = 32; //Step position information with time tag CP56Time2a
        const parcelkind M_BO_TB_1 = 33; //Bitstring of 32 bit with time tag CP56Time2a
        const parcelkind M_ME_TD_1 = 34; //Measured value, normalized value with time tag CP56Time2a
        const parcelkind M_ME_TE_1 = 35; //Measured value, scaled value with time tag CP56Time2a
        const parcelkind M_ME_TF_1 = 36; //Measured value, short floating point value with time tag CP56Time2a
        const parcelkind M_IT_TB_1 = 37; //Integrated totals with time tag CP56Time2a
        const parcelkind M_EP_TD_1 = 38; //Event of protection equipment with time-tag CP56Time2a
        const parcelkind M_EP_TE_1 = 39; //Packed start events of protection equipment with time-tag CP56Time2a
        const parcelkind M_EP_TF_1 = 40; //Packed output circuit information of protection equipment with timetag CP56Time2a

        const parcelkind C_SC_NA_1 = 45; // Single command 
        const parcelkind C_DC_NA_1 = 46; // Double command
        const parcelkind C_RC_NA_1 = 47; // Regulating step command
        const parcelkind C_SE_NA_1 = 48; // Set point command, normalized value
        const parcelkind C_SE_NB_1 = 49; // Set point command, scaled value
        const parcelkind C_SE_NC_1 = 50; // Set point command, short floating point value
        const parcelkind C_BO_NA_1 = 51; // Bitstring of 32 bit
        const parcelkind C_SC_TA_1 = 58; // Single command with time tag CP56Time 2a 
        const parcelkind C_DC_TA_1 = 59; // Double command with time tag CP56Time 2a
        const parcelkind C_RC_TA_1 = 60; // Regulating step command with time tag CP56Time 2a
        const parcelkind C_SE_TA_1 = 61; // Set point command, normalized value with time tag CP56Time 2a
        const parcelkind C_SE_TB_1 = 62; // Set point command, scaled value with time tag CP56Time 2a
        const parcelkind C_SE_TC_1 = 63; // Set point command, short floating point value with time tag CP56Time 2a
        const parcelkind C_BO_TA_1 = 64; // Bitstring of 32 bit with time tag CP56Time 2a      

        const parcelkind M_EI_NA_1 = 70;   //End of initialization

       const parcelkind C_IC_NA_1 =100;     // Interrogation command 100
       const parcelkind C_CI_NA_1 =101;     // Counter interrogation command
       const parcelkind C_RD_NA_1 =102;     // Read command
       const parcelkind C_CS_NA_1 =103;     // Clock synchronization command
       const parcelkind C_TS_NA_1 =104;     // Test command
       const parcelkind C_RP_NA_1 =105;     // Reset process command
       const parcelkind C_CD_NA_1 =106;     // Delay acquisition command
       const parcelkind C_TS_TA_1  =107;     // Test command with time tag CP56time2a      
        
       const parcelkind P_ME_NA_1 =110;     // Parameter of measured value, normalized value 110
       const parcelkind P_ME_NB_1 =111;     // Parameter of measured value, scaled value
       const parcelkind P_ME_NC_1 =112;     // Parameter of measured value, short floating point value
       const parcelkind P_AC_NA_1=113;     // Parameter activation

       const parcelkind F_FR_NA_1=120;     // File ready 120
       const parcelkind F_SR_NA_1=121;     // Section ready
       const parcelkind F_SC_NA_1=122;     // Call directory, select file, call file, call section
       const parcelkind F_LS_NA_1=123;     // Last section, last segment
       const parcelkind F_AF_NA_1=124;     // Ack file, ack section
       const parcelkind F_SG_NA_1=125;     // Segment
       const parcelkind F_DR_TA_1=126;     // Directory {blank or X, only available in monitor (standard) direction}
       const parcelkind F_SC_NB_1=127;     // Query log – Request archive file
       
       typedef std::pair<std::string, parcelkind> string_parcelkind_pair;
       typedef std::map<std::string, parcelkind> string_parcelkind_map;    
       
       parcelkind find_parcelkind(const std::string& val);
        
        const parcelkind  DISCRET_INPUT_MODBUS_TYPE    = 1;
        const parcelkind  COIL_MODBUS_TYPE             = 2;
        const parcelkind  INPUT_REGISTER_MODBUS_TYPE   = 3;
        const parcelkind  HOLDING_REGISTER_MODBUS_TYPE = 4;

        const blksizetype MAX_MODBUS_BLOCK_SIZE        = 242;

        const protocoltype INTPR_RS_MODBUS_ASCII       = 0x1;
        const protocoltype INTPR_RS_MODBUS_RTU         = 0x0;
        const protocoltype INTPR_TCP_MODBUS            = 0x2;

        const num16 ON_COIL_MODBUS_NM                  = 0x00FF;
        const num16 OFF_COIL_MODBUS_NM                 = 0x0000;

        const std::string MODBUS_TCP_PORT              = "502";

        /* RTU Version*/

        // discret inputs
        const std::string MDB_FC_READ_D = "\x2";
        // coils
        const std::string MDB_FC_READ_C = "\x1";
        // input registers
        const std::string MDB_FC_READ_I = "\x4";
        // holding registers
        const std::string MDB_FC_READ_H = "\x3";

        // coil write
        const std::string MDB_FC_WRITE_SC = "\x5";
        // holding write
        const std::string MDB_FC_WRITE_SH = "\x6";

        // coils write
        const std::string MDB_FC_WRITE_MC = "\xF";
        // holdings write
        const std::string MDB_FC_WRITE_MH = "\x10";

        // mask holdings write
        const std::string MDB_FC_WRITE_MASKH = "\x16";

        const std::string MDB_ASCII_START_ENV = ":";

        const std::string MDB_TCP_GARBIDGE_ENV = "\x0";

        const std::string ASCII_MDB_RESPONSE_REGEX_TMPL = ":[0-9A-F]{4,}" + CR + LF;
        
        
        
        bool insert_mdb_lrc(std::string& src, std::string::size_type strt);

        bool check_and_clear_mdb_lrc(std::string& src, std::string::size_type strt);

        

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*iec60870_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class iec60870_value_manager : public flatmemory_value_manager {
        public:

            iec60870_value_manager() : flatmemory_value_manager() {}

        protected:

            virtual size_t getbitnum(parcel_const_iterator strt, parcel_const_iterator stp) {
                if ((strt->first->kind() == DISCRET_INPUT_MODBUS_TYPE) || (strt->first->kind() == COIL_MODBUS_TYPE)) {
                    return (stp->first->addr() - strt->first->addr()) % 8;}
                return stp->first->indx();}

            virtual bool spec_protocol_convertion_out(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return be_le16_convert_string(val);}

            virtual bool spec_protocol_convertion_in(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return be_le16_convert_string(val);}

            virtual ns_error parse_response_impl(std::string& val, parcel_ptr prcl, size_t bitn = NULL_BIT_NUM);

            virtual ns_error preapare_cmd_request_impl(std::string& val, parcel_ptr cmd, size_t bitn = NULL_BIT_NUM);};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*basis_iec60870_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = iec60870_value_manager>
                class basis_iec60870_protocol : public templ_protocol<VALUEMANAGER> {
        private:

            typedef templ_protocol<VALUEMANAGER> basetype;

        public:

            typedef unum8 mdbdevn;

            static const mdbdevn MAX_MODBUS_DEV_NUM = 247;
            static const mdbdevn NO_MODBUS_DEV_NUM = 0xFF;

            basis_iec60870_protocol(basis_iostream_ptr io) : templ_protocol<iec60870_value_manager>(io) {}

        protected:
            
             virtual ns_error readblock(block& blk) {
                basetype::error(0);
                mdbdevn dvnum = ((blk.begin()->first->devnum() > 0) && (blk.begin()->first->devnum() <= MAX_MODBUS_DEV_NUM)) ?
                        static_cast<mdbdevn> (blk.begin()->first->devnum()) : NO_MODBUS_DEV_NUM;
                if (dvnum == NO_MODBUS_DEV_NUM) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                if (dvnum == 0) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                return read_impl(blk, dvnum);}

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd) {
                basetype::error(0);
                mdbdevn dvnum = ((cmd->devnum() >= 0) && (cmd->devnum() <= MAX_MODBUS_DEV_NUM)) ? static_cast<unum8> (cmd->devnum()) : -1;
                if (dvnum == NO_MODBUS_DEV_NUM) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                DEBUG_VAL_DVNCI(binary_block_to_hexsequence_debug(vl))
                write_impl(cmd, vl, dvnum);
                DEBUG_VAL_DVNCI(basetype::error())
                return basetype::error();}

            unum8 byte_from_str(const std::string& vl, std::string::size_type n) {
                if (vl.size() <= n) {
                    basetype::error(ERROR_IO_PARSERESP);
                    return 0;}
                return static_cast<unum8> (vl.at(n));}

            ns_error read_impl(const block& blk, mdbdevn dvnum) {
                std::string req = "";
                parcelkind tp = blk.begin()->first->kind();
                if (chek_type(tp)) return basetype::error();
                num32 strtaddr = blk.begin()->first->addr();
                size_t tst_cnt = calculate_blocksize(blk.end()->first, blk.begin()->first);
                size_t cnt = ((tp == INPUT_REGISTER_MODBUS_TYPE) || (tp == HOLDING_REGISTER_MODBUS_TYPE)) ? tst_cnt / 2 : tst_cnt * 8;
                if (!basetype::error(generate_body_read(req, dvnum, read_fnc_by_type(tp), strtaddr, cnt))) {
                    std::string resp = "";
                    if (!basetype::error(request(req, resp))) {
                        parse_envelope(resp, dvnum, read_fnc_by_type(tp), tst_cnt);}}
                return basetype::error();}

            ns_error write_impl(parcel_ptr cmd, const std::string& vl, mdbdevn dvnum) {
                std::string req = "";
                parcelkind tp = cmd->kind();
                if (chek_write_type(tp)) return basetype::error();
                num32 strtaddr = cmd->addr();
                size_t bitnum = cmd->indx();
                if ((bitnum > 15) && (bitnum != NULL_BIT_NUM)) return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                if (!basetype::error(generate_body_write(req, dvnum, write_fnc_by_type(tp, vl.size(), bitnum), strtaddr, vl, bitnum))) {
                    std::string resp = "";
                    bool echo = (bitnum != NULL_BIT_NUM) || (tp == COIL_MODBUS_TYPE);
                    if (!request(req, resp, echo)) {
                        if (!echo)
                            parse_envelope(resp, dvnum, write_fnc_by_type(tp, vl.size()));}}
                return basetype::error();}

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) = 0;

            virtual ns_error generate_body_impl(std::string& vl) = 0;

            ns_error generate_body_read(std::string& vl, mdbdevn dvnum, const std::string& fnc, num32 startaddr, size_t cnt) {
                vl = primtype_to_string<mdbdevn > (dvnum);
                vl = vl + fnc;
                vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) +
                        primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (cnt)));
                generate_body_impl(vl);
                return basetype::error();}

            ns_error generate_body_write(std::string& vl, mdbdevn dvnum, const std::string& fnc, num32 startaddr, const std::string& wval, size_t bitnum = NULL_BIT_NUM) {
                vl = primtype_to_string<mdbdevn > (dvnum);
                vl = vl + fnc;
                if ((bitnum == NULL_BIT_NUM) || (fnc != MDB_FC_WRITE_MASKH)) {
                    if ((fnc == MDB_FC_WRITE_SC) || (fnc == MDB_FC_WRITE_SH)) {
                        vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) + wval;} else {
                        if (fnc == MDB_FC_WRITE_MH) {
                            vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) +
                                    primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (wval.size() / 2))) +
                                    primtype_to_string<unum8 > (static_cast<unum8> (wval.size())) + wval;} else
                            return basetype::error(ERROR_IO_NO_GENERATE_REQ);}} else {
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr)));
                    num16 and_mask = ~(0x01 << bitnum);
                    num16 or_mask = 0;
                    if (!string_to_primtype<num16 > (wval, or_mask)) return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                    if (or_mask) or_mask = (0x01 << bitnum);
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (and_mask)));
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (or_mask)));}
                generate_body_impl(vl);
                return basetype::error();}

            ns_error parse_envelope(std::string& resp, mdbdevn dvnum, const std::string& fnc, size_t cnt = 0) {
                if (!basetype::error(check_envelope(resp, dvnum, fnc.empty() ? 0 : fnc.at(0)))) {
                    if ((cnt == resp.size()) || (cnt == 0)) {
                        basetype::readdata = resp;
                        return basetype::error(0);}}
                return basetype::error(ERROR_IO_PARSERESP);}

            std::string read_fnc_by_type(parcelkind tp) {
                switch (tp) {
                    case DISCRET_INPUT_MODBUS_TYPE:{
                        return MDB_FC_READ_D;}
                    case COIL_MODBUS_TYPE:{
                        return MDB_FC_READ_C;};
                    case INPUT_REGISTER_MODBUS_TYPE:{
                        return MDB_FC_READ_I;}
                    case HOLDING_REGISTER_MODBUS_TYPE:{
                        return MDB_FC_READ_H;}}
                return "";}

            std::string write_fnc_by_type(parcelkind tp, std::string::size_type sz, size_t binnum = NULL_BIT_NUM) {
                switch (tp) {
                    case COIL_MODBUS_TYPE:{
                        return MDB_FC_WRITE_SC;};
                    case HOLDING_REGISTER_MODBUS_TYPE:{
                        return (binnum == NULL_BIT_NUM) ?
                                ((sz == 2) ? MDB_FC_WRITE_SH : MDB_FC_WRITE_MH) : MDB_FC_WRITE_MASKH;}}
                return "";}

            bool fnc_is_write(unum8 fnc) {
                return ((MDB_FC_WRITE_SH.at(0) == fnc) || (MDB_FC_WRITE_MH.at(0) == fnc) ||
                        (MDB_FC_WRITE_SC.at(0) == fnc) || (MDB_FC_WRITE_MASKH.at(0) == fnc));}

            virtual ns_error check_envelope(std::string& resp, unum8 dvnum, unum8 fnc) {
                size_t cnt = static_cast<size_t> (resp.size());
                if (cnt > 2) {
                    if ((byte_from_str(resp, 1) != fnc) || (cnt == 3)) {
                        if (byte_from_str(resp, 1) != (0x80 | fnc))
                            return basetype::error(ERROR_IO_PARSERESP);
                        num8 mdb_err = byte_from_str(resp, 2);
                        return basetype::error(ERROR_IO_MODBUS_ERR);}
                    cnt = cnt - 3;
                    if ((!fnc_is_write(fnc)) && (byte_from_str(resp, 0) == dvnum)
                            && (byte_from_str(resp, 2) == cnt)) {
                        resp = resp.substr(3);
                        return basetype::error(0);}}
                return basetype::error(ERROR_IO_PARSERESP);}

            ns_error chek_type(parcelkind tp) {
                if ((tp < DISCRET_INPUT_MODBUS_TYPE) || (tp > HOLDING_REGISTER_MODBUS_TYPE))
                    return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                return basetype::error(0);}

            ns_error chek_write_type(parcelkind tp) {
                if ((tp == COIL_MODBUS_TYPE) || (tp == HOLDING_REGISTER_MODBUS_TYPE))
                    return basetype::error(0);
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);}};



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*rtu_iec60870_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = iec60870_value_manager>
                class rtu_iec60870_protocol : public basis_iec60870_protocol<VALUEMANAGER> {
        private:

            typedef basis_iec60870_protocol<VALUEMANAGER> basetype;

        public:

            rtu_iec60870_protocol(basis_iostream_ptr io) : basis_iec60870_protocol<VALUEMANAGER>(io) {}

        protected:

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) {
                resp = "";
                basetype::ios->char_silence(3.5);
                if (!basetype::error(basetype::ios->write(req))) {
                    basetype::ios->char_silence(3.5);
                    if (!basetype::error(basetype::ios->read(resp, echo ? req.size() : 3))) {
                        if (echo) return basetype::error(req == resp ? 0 : ERROR_IO_PARSERESP);
                        size_t cntbt = ((basetype::byte_from_str(resp, 1) & 0x80) == 0) ?
                                static_cast<size_t> (basetype::byte_from_str(resp, 2) + 2) : 2;
                        if (!basetype::error(basetype::ios->read(resp, cntbt))) {
                            if (resp.size() < 5) return basetype::error(ERROR_IO_PARSERESP);
                            return basetype::error(check_and_clear_ibm_crc16(resp, 0) ? 0 : ERROR_IO_CRC);}}}
                return basetype::error();}

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    if (insert_ibm_crc16(vl, 0))
                        return basetype::error(0);}
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);}};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*class ascii_iec60870_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = iec60870_value_manager>
                class ascii_iec60870_protocol : public basis_iec60870_protocol<VALUEMANAGER> {
        private:

            typedef basis_iec60870_protocol<VALUEMANAGER> basetype;

        public:

            ascii_iec60870_protocol(basis_iostream_ptr io) :
            basis_iec60870_protocol<VALUEMANAGER>(io) {}

        protected:

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) {
                resp = "";
                if (!basetype::error(basetype::ios->write(req))) {
                    if (echo) {
                        if (!basetype::error(basetype::ios->read(resp, req.size()))) {
                            return basetype::error((req == resp) ? 0 : ERROR_IO_PARSERESP);}
                        return basetype::error();}
                    if (!basetype::error(basetype::ios->read_until(resp, boost::regex(ASCII_MDB_RESPONSE_REGEX_TMPL)))) {
                        if (resp.size() < 4) return basetype::error(ERROR_IO_PARSERESP);
                        resp = resp.substr(1, resp.size() - 3);
                        basetype::error(check_and_clear_mdb_lrc(resp, 0) ? 0 : ERROR_IO_CRC);
                        if (!basetype::error()) {
                            if (resp.size() < 2) return basetype::error(ERROR_IO_PARSERESP);
                            std::string tmpresp = resp;
                            return basetype::error(hexsequence_to_binary_block(tmpresp, resp) ? 0 : ERROR_IO_PARSERESP);}}}
                return basetype::error();}

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    if (insert_mdb_lrc(vl, 0)) {
                        binary_block_to_hexsequence(vl);
                        vl = MDB_ASCII_START_ENV + vl + CR + LF;
                        return basetype::error(0);}}
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);}};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*tcp_iec60870_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = iec60870_value_manager>
                class tcp_iec60870_protocol : public basis_iec60870_protocol<VALUEMANAGER> {
        private:

            typedef basis_iec60870_protocol<VALUEMANAGER> basetype;

        public:

            tcp_iec60870_protocol(basis_iostream_ptr io) :
            basis_iec60870_protocol<VALUEMANAGER>(io), trasactcnt(0) {}

        protected:

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) {
                resp = "";
                if (!basetype::error(basetype::ios->write(req))) {
                    basetype::error(basetype::ios->read(resp, echo ? req.size() : 6));
                    num16 cntenv = tcp_reaqust_env_bytecount(resp);
                    if (!basetype::error()) {
                        if (echo) return basetype::error(req == resp ? 0 : ERROR_IO_PARSERESP);
                        if (!basetype::error(basetype::ios->read(resp, cntenv))) {
                            std::string stopresp = resp;
                            if (resp.size() < 6) return basetype::error(ERROR_IO_PARSERESP);
                            resp = resp.substr(6);
                            return basetype::error(0);}}}
                return basetype::error();}

            num16 tcp_reaqust_env_bytecount(const std::string& startreq) {
                if (startreq.size() < 6) {
                    basetype::error(ERROR_IO_PARSERESP);
                    return 0;}
                num16* tmpsz = (num16*)const_cast<char*> (startreq.data());
                tmpsz = tmpsz + 2;
                return be_le_convert_num16(*tmpsz);}

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    vl = primtype_to_string<num16 > (be_le_convert_num16(/*trasactcnt++*/0)) +
                            primtype_to_string<num16 > (0) + primtype_to_string<num8 > (0) +
                            primtype_to_string<unum8 > (static_cast<unum8> (vl.size())) + vl;
                    return basetype::error(0);}
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);}

            num16 trasactcnt;};}};

#endif	/* MODBUS_PROTOCOL_H */

