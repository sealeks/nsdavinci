/* 
 * File:   modbus_protocol.h
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


        const parcelkind DISCRET_INPUT_MODBUS_TYPE = 1;
        const parcelkind COIL_MODBUS_TYPE = 2;
        const parcelkind INPUT_REGISTER_MODBUS_TYPE = 3;
        const parcelkind HOLDING_REGISTER_MODBUS_TYPE = 4;

        const blksizetype MAX_MODBUS_BLOCK_SIZE = 242;

        const protocoltype INTPR_RS_MODBUS_ASCII = 0x1;
        const protocoltype INTPR_RS_MODBUS_RTU = 0x0;
        const protocoltype INTPR_TCP_MODBUS = 0x2;

        const num16 ON_COIL_MODBUS_NM = 0x00FF;
        const num16 OFF_COIL_MODBUS_NM = 0x0000;

        const std::string MODBUS_TCP_PORT = "502";

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
        /*modbus_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class modbus_value_manager : public flatmemory_value_manager {

        public:

            modbus_value_manager() : flatmemory_value_manager() {
            }

        protected:

            virtual size_t getbitnum(parcel_const_iterator strt, parcel_const_iterator stp) {
                if ((strt->first->kind() == DISCRET_INPUT_MODBUS_TYPE) || (strt->first->kind() == COIL_MODBUS_TYPE)) {
                    return (stp->first->addr() - strt->first->addr()) % 8;
                }
                return stp->first->indx();
            }

            virtual bool spec_protocol_convertion_out(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return be_le16_convert_string(val);
            }

            virtual bool spec_protocol_convertion_in(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return be_le16_convert_string(val);
            }

            virtual ns_error parse_response_impl(std::string& val, parcel_ptr prcl, size_t bitn = NULL_BIT_NUM);

            virtual ns_error preapare_cmd_request_impl(std::string& val, parcel_ptr cmd, size_t bitn = NULL_BIT_NUM);
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*basis_modbus_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = modbus_value_manager>
        class basis_modbus_protocol : public templ_protocol<VALUEMANAGER> {

        private:

            typedef templ_protocol<VALUEMANAGER> basetype;

        public:

            typedef unum8 mdbdevn;

            static const mdbdevn MAX_MODBUS_DEV_NUM = 247;
            static const mdbdevn NO_MODBUS_DEV_NUM = 0xFF;

            basis_modbus_protocol(basis_iostream_ptr io) : templ_protocol<modbus_value_manager>(io) {
            }

        protected:

            virtual ns_error readblock(block& blk) {
                basetype::error(0);
                mdbdevn dvnum = ((blk.begin()->first->devnum() > 0) && (blk.begin()->first->devnum() <= MAX_MODBUS_DEV_NUM)) ?
                        static_cast<mdbdevn> (blk.begin()->first->devnum()) : NO_MODBUS_DEV_NUM;
                if (dvnum == NO_MODBUS_DEV_NUM) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                if (dvnum == 0) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                return read_impl(blk, dvnum);
            }

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd) {
                basetype::error(0);
                mdbdevn dvnum = ((cmd->devnum() >= 0) && (cmd->devnum() <= MAX_MODBUS_DEV_NUM)) ? static_cast<unum8> (cmd->devnum()) : -1;
                if (dvnum == NO_MODBUS_DEV_NUM) return basetype::error(ERROR_IO_NO_CORRECT_ADDR);
                DEBUG_VAL_DVNCI(binary_block_to_hexsequence_debug(vl))
                write_impl(cmd, vl, dvnum);
                DEBUG_VAL_DVNCI(basetype::error())
                return basetype::error();
            }

            unum8 byte_from_str(const std::string& vl, std::string::size_type n) {
                if (vl.size() <= n) {
                    basetype::error(ERROR_IO_PARSERESP);
                    return 0;
                }
                return static_cast<unum8> (vl.at(n));
            }

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
                        parse_envelope(resp, dvnum, read_fnc_by_type(tp), tst_cnt);
                    }
                }
                return basetype::error();
            }

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
                            parse_envelope(resp, dvnum, write_fnc_by_type(tp, vl.size()));
                    }
                }
                return basetype::error();
            }

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) = 0;

            virtual ns_error generate_body_impl(std::string& vl) = 0;

            ns_error generate_body_read(std::string& vl, mdbdevn dvnum, const std::string& fnc, num32 startaddr, size_t cnt) {
                vl = primtype_to_string<mdbdevn > (dvnum);
                vl = vl + fnc;
                vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) +
                        primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (cnt)));
                generate_body_impl(vl);
                return basetype::error();
            }

            ns_error generate_body_write(std::string& vl, mdbdevn dvnum, const std::string& fnc, num32 startaddr, const std::string& wval, size_t bitnum = NULL_BIT_NUM) {
                vl = primtype_to_string<mdbdevn > (dvnum);
                vl = vl + fnc;
                if ((bitnum == NULL_BIT_NUM) || (fnc != MDB_FC_WRITE_MASKH)) {
                    if ((fnc == MDB_FC_WRITE_SC) || (fnc == MDB_FC_WRITE_SH)) {
                        vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) + wval;
                    } else {
                        if (fnc == MDB_FC_WRITE_MH) {
                            vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr))) +
                                    primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (wval.size() / 2))) +
                                    primtype_to_string<unum8 > (static_cast<unum8> (wval.size())) + wval;
                        } else
                            return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                    }
                } else {
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (startaddr)));
                    num16 and_mask = ~(0x01 << bitnum);
                    num16 or_mask = 0;
                    if (!string_to_primtype<num16 > (wval, or_mask)) return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                    if (or_mask) or_mask = (0x01 << bitnum);
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (and_mask)));
                    vl = vl + primtype_to_string<num16 > (be_le_convert_num16(static_cast<num16> (or_mask)));
                }
                generate_body_impl(vl);
                return basetype::error();
            }

            ns_error parse_envelope(std::string& resp, mdbdevn dvnum, const std::string& fnc, size_t cnt = 0) {
                if (!basetype::error(check_envelope(resp, dvnum, fnc.empty() ? 0 : fnc.at(0)))) {
                    if ((cnt == resp.size()) || (cnt == 0)) {
                        basetype::readdata = resp;
                        return basetype::error(0);
                    }
                }
                return basetype::error(ERROR_IO_PARSERESP);
            }

            std::string read_fnc_by_type(parcelkind tp) {
                switch (tp) {
                    case DISCRET_INPUT_MODBUS_TYPE:
                    {
                        return MDB_FC_READ_D;
                    }
                    case COIL_MODBUS_TYPE:
                    {
                        return MDB_FC_READ_C;
                    };
                    case INPUT_REGISTER_MODBUS_TYPE:
                    {
                        return MDB_FC_READ_I;
                    }
                    case HOLDING_REGISTER_MODBUS_TYPE:
                    {
                        return MDB_FC_READ_H;
                    }
                }
                return "";
            }

            std::string write_fnc_by_type(parcelkind tp, std::string::size_type sz, size_t binnum = NULL_BIT_NUM) {
                switch (tp) {
                    case COIL_MODBUS_TYPE:
                    {
                        return MDB_FC_WRITE_SC;
                    };
                    case HOLDING_REGISTER_MODBUS_TYPE:
                    {
                        return (binnum == NULL_BIT_NUM) ?
                                ((sz == 2) ? MDB_FC_WRITE_SH : MDB_FC_WRITE_MH) : MDB_FC_WRITE_MASKH;
                    }
                }
                return "";
            }

            bool fnc_is_write(unum8 fnc) {
                return ((MDB_FC_WRITE_SH.at(0) == fnc) || (MDB_FC_WRITE_MH.at(0) == fnc) ||
                        (MDB_FC_WRITE_SC.at(0) == fnc) || (MDB_FC_WRITE_MASKH.at(0) == fnc));
            }

            virtual ns_error check_envelope(std::string& resp, unum8 dvnum, unum8 fnc) {
                size_t cnt = static_cast<size_t> (resp.size());
                if (cnt > 2) {
                    if ((byte_from_str(resp, 1) != fnc) || (cnt == 3)) {
                        if (byte_from_str(resp, 1) != (0x80 | fnc))
                            return basetype::error(ERROR_IO_PARSERESP);
                        num8 mdb_err = byte_from_str(resp, 2);
                        return basetype::error(ERROR_IO_MODBUS_ERR);
                    }
                    cnt = cnt - 3;
                    if ((!fnc_is_write(fnc)) && (byte_from_str(resp, 0) == dvnum)
                            && (byte_from_str(resp, 2) == cnt)) {
                        resp = resp.substr(3);
                        return basetype::error(0);
                    }
                }
                return basetype::error(ERROR_IO_PARSERESP);
            }

            ns_error chek_type(parcelkind tp) {
                if ((tp < DISCRET_INPUT_MODBUS_TYPE) || (tp > HOLDING_REGISTER_MODBUS_TYPE))
                    return basetype::error(ERROR_IO_NO_GENERATE_REQ);
                return basetype::error(0);
            }

            ns_error chek_write_type(parcelkind tp) {
                if ((tp == COIL_MODBUS_TYPE) || (tp == HOLDING_REGISTER_MODBUS_TYPE))
                    return basetype::error(0);
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);
            }
        };



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*rtu_modbus_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = modbus_value_manager>
        class rtu_modbus_protocol : public basis_modbus_protocol<VALUEMANAGER> {

        private:

            typedef basis_modbus_protocol<VALUEMANAGER> basetype;

        public:

            rtu_modbus_protocol(basis_iostream_ptr io) : basis_modbus_protocol<VALUEMANAGER>(io) {
            }

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
                            return basetype::error(check_and_clear_ibm_crc16(resp, 0) ? 0 : ERROR_IO_CRC);
                        }
                    }
                }
                return basetype::error();
            }

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    if (insert_ibm_crc16(vl, 0))
                        return basetype::error(0);
                }
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*class ascii_modbus_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = modbus_value_manager>
        class ascii_modbus_protocol : public basis_modbus_protocol<VALUEMANAGER> {

        private:

            typedef basis_modbus_protocol<VALUEMANAGER> basetype;

        public:

            ascii_modbus_protocol(basis_iostream_ptr io) :
            basis_modbus_protocol<VALUEMANAGER>(io) {
            }

        protected:

            virtual ns_error request(std::string& req, std::string& resp, bool echo = false) {
                resp = "";
                if (!basetype::error(basetype::ios->write(req))) {
                    if (echo) {
                        if (!basetype::error(basetype::ios->read(resp, req.size()))) {
                            return basetype::error((req == resp) ? 0 : ERROR_IO_PARSERESP);
                        }
                        return basetype::error();
                    }
                    if (!basetype::error(basetype::ios->read_until(resp, boost::regex(ASCII_MDB_RESPONSE_REGEX_TMPL)))) {
                        if (resp.size() < 4) return basetype::error(ERROR_IO_PARSERESP);
                        resp = resp.substr(1, resp.size() - 3);
                        basetype::error(check_and_clear_mdb_lrc(resp, 0) ? 0 : ERROR_IO_CRC);
                        if (!basetype::error()) {
                            if (resp.size() < 2) return basetype::error(ERROR_IO_PARSERESP);
                            std::string tmpresp = resp;
                            return basetype::error(hexsequence_to_binary_block(tmpresp, resp) ? 0 : ERROR_IO_PARSERESP);
                        }
                    }
                }
                return basetype::error();
            }

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    if (insert_mdb_lrc(vl, 0)) {
                        binary_block_to_hexsequence(vl);
                        vl = MDB_ASCII_START_ENV + vl + CR + LF;
                        return basetype::error(0);
                    }
                }
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);
            }
        };

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*tcp_modbus_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template <typename VALUEMANAGER = modbus_value_manager>
        class tcp_modbus_protocol : public basis_modbus_protocol<VALUEMANAGER> {

        private:

            typedef basis_modbus_protocol<VALUEMANAGER> basetype;

        public:

            tcp_modbus_protocol(basis_iostream_ptr io) :
            basis_modbus_protocol<VALUEMANAGER>(io), trasactcnt(0) {
            }

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
                            return basetype::error(0);
                        }
                    }
                }
                return basetype::error();
            }

            num16 tcp_reaqust_env_bytecount(const std::string& startreq) {
                if (startreq.size() < 6) {
                    basetype::error(ERROR_IO_PARSERESP);
                    return 0;
                }
                num16* tmpsz = (num16*)const_cast<char*> (startreq.data());
                tmpsz = tmpsz + 2;
                return be_le_convert_num16(*tmpsz);
            }

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() > 1) {
                    vl = primtype_to_string<num16 > (be_le_convert_num16(/*trasactcnt++*/0)) +
                            primtype_to_string<num16 > (0) + primtype_to_string<num8 > (0) +
                            primtype_to_string<unum8 > (static_cast<unum8> (vl.size())) + vl;
                    return basetype::error(0);
                }
                return basetype::error(ERROR_IO_NO_GENERATE_REQ);
            }

            num16 trasactcnt;
        };
    }
};

#endif	/* MODBUS_PROTOCOL_H */

