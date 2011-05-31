/* 
 * File:   modbus_protocol.cpp
 * Author: Serg
 * 
 * Created on 18 ?????? 2010 ?., 17:22
 */

#include <driverspec/directnet_protocol.h>

namespace dvnci {
    namespace driver {

        bool insert_hex_koyo_lrc (std::string& src) {
            num8 crc = 0;
            if (calculate_koyo_lrc(src.substr(0, src.size() - 1), crc, 1)) {
                src = src + primtype_to_string<num8 > (crc);
                return true;}
            return false;}

        bool insert_ascii_koyo_lrc (std::string& src) {
            num8 crc = 0;
            if (calculate_koyo_lrc(src.substr(0, src.size() - 1), crc, 1)) {
                src = src + num8_to_hexstr(crc);
                return true;}
            return false;}

        bool check_hex_koyo_lrc (std::string& src) {
            if (src.size() < 4) return false;
            num8 crc = 0;
            std::string ch_src = src.substr(1, src.size() - 3);
            num8 reqcrc = src.at(src.size() - 1);
            if (calculate_koyo_lrc(ch_src, crc, 0)) {
                if (crc == reqcrc) {
                    src = ch_src;
                    return true;}}
            return false;}

        bool check_ascii_koyo_lrc (std::string& src) {
            if (src.size() < 5) return false;
            num8 crc = 0;
            std::string ch_src = src.substr(1, src.size() - 4);
            std::string txt_crc = src.substr(src.size() - 2);
            num8 reqcrc = 0;
            if (calculate_koyo_lrc(ch_src, crc, 0)) {
                if (hexstr_to<num8 > (txt_crc, reqcrc))
                    if (crc == reqcrc) {
                        src = ch_src;
                        return true;}}
            return false;}

        bool calculate_koyo_lrc (const std::string& src, num8& lrc, std::string::size_type strt) {
            if (src.size() > strt) {
                lrc = 0;
                for (std::string::size_type it = strt; it < src.size(); ++it ) {
                    lrc = (it == strt) ? (0xFF & (src.at(it))) : (lrc ^ (0xFF & (src.at(it))));}
                return true;}
            return false;}


        const   unum16 ecom_crctab[] = {
            0x0000,  0x1021,  0x2042,  0x3063,  0x4084,  0x50a5,  0x60c6,  0x70e7,
            0x8108,  0x9129,  0xa14a,  0xb16b,  0xc18c,  0xd1ad,  0xe1ce,  0xf1ef,
            0x1231,  0x0210,  0x3273,  0x2252,  0x52b5,  0x4294,  0x72f7,  0x62d6,
            0x9339,  0x8318,  0xb37b,  0xa35a,  0xd3bd,  0xc39c,  0xf3ff,  0xe3de,
            0x2462,  0x3443,  0x0420,  0x1401,  0x64e6,  0x74c7,  0x44a4,  0x5485,
            0xa56a,  0xb54b,  0x8528,  0x9509,  0xe5ee,  0xf5cf,  0xc5ac,  0xd58d,
            0x3653,  0x2672,  0x1611,  0x0630,  0x76d7,  0x66f6,  0x5695,  0x46b4,
            0xb75b,  0xa77a,  0x9719,  0x8738,  0xf7df,  0xe7fe,  0xd79d,  0xc7bc,
            0x48c4,  0x58e5,  0x6886,  0x78a7,  0x0840,  0x1861,  0x2802,  0x3823,
            0xc9cc,  0xd9ed,  0xe98e,  0xf9af,  0x8948,  0x9969,  0xa90a,  0xb92b,
            0x5af5,  0x4ad4,  0x7ab7,  0x6a96,  0x1a71,  0x0a50,  0x3a33,  0x2a12,
            0xdbfd,  0xcbdc,  0xfbbf,  0xeb9e,  0x9b79,  0x8b58,  0xbb3b,  0xab1a,
            0x6ca6,  0x7c87,  0x4ce4,  0x5cc5,  0x2c22,  0x3c03,  0x0c60,  0x1c41,
            0xedae,  0xfd8f,  0xcdec,  0xddcd,  0xad2a,  0xbd0b,  0x8d68,  0x9d49,
            0x7e97,  0x6eb6,  0x5ed5,  0x4ef4,  0x3e13,  0x2e32,  0x1e51,  0x0e70,
            0xff9f,  0xefbe,  0xdfdd,  0xcffc,  0xbf1b,  0xaf3a,  0x9f59,  0x8f78,
            0x9188,  0x81a9,  0xb1ca,  0xa1eb,  0xd10c,  0xc12d,  0xf14e,  0xe16f,
            0x1080,  0x00a1,  0x30c2,  0x20e3,  0x5004,  0x4025,  0x7046,  0x6067,
            0x83b9,  0x9398,  0xa3fb,  0xb3da,  0xc33d,  0xd31c,  0xe37f,  0xf35e,
            0x02b1,  0x1290,  0x22f3,  0x32d2,  0x4235,  0x5214,  0x6277,  0x7256,
            0xb5ea,  0xa5cb,  0x95a8,  0x8589,  0xf56e,  0xe54f,  0xd52c,  0xc50d,
            0x34e2,  0x24c3,  0x14a0,  0x0481,  0x7466,  0x6447,  0x5424,  0x4405,
            0xa7db,  0xb7fa,  0x8799,  0x97b8,  0xe75f,  0xf77e,  0xc71d,  0xd73c,
            0x26d3,  0x36f2,  0x0691,  0x16b0,  0x6657,  0x7676,  0x4615,  0x5634,
            0xd94c,  0xc96d,  0xf90e,  0xe92f,  0x99c8,  0x89e9,  0xb98a,  0xa9ab,
            0x5844,  0x4865,  0x7806,  0x6827,  0x18c0,  0x08e1,  0x3882,  0x28a3,
            0xcb7d,  0xdb5c,  0xeb3f,  0xfb1e,  0x8bf9,  0x9bd8,  0xabbb,  0xbb9a,
            0x4a75,  0x5a54,  0x6a37,  0x7a16,  0x0af1,  0x1ad0,  0x2ab3,  0x3a92,
            0xfd2e,  0xed0f,  0xdd6c,  0xcd4d,  0xbdaa,  0xad8b,  0x9de8,  0x8dc9,
            0x7c26,  0x6c07,  0x5c64,  0x4c45,  0x3ca2,  0x2c83,  0x1ce0,  0x0cc1,
            0xef1f,  0xff3e,  0xcf5d,  0xdf7c,  0xaf9b,  0xbfba,  0x8fd9,  0x9ff8,
            0x6e17,  0x7e36,  0x4e55,  0x5e74,  0x2e93,  0x3eb2,  0x0ed1,  0x1ef0};

        bool calculate_ecom_crc (const std::string& src, unum16& crc, std::string::size_type strt) {
            if (strt >= src.size()) return false;
            crc = 0;
            for (std::string::size_type it =  strt; it < src.size(); ++it)
                crc = (crc << 8) ^ ecom_crctab
                    [ static_cast<size_t> ( static_cast<unum16> (crc >> 8)  ^ static_cast<unum16> (src.at(it)))];
            return true;}



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*directnet_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error directnet_value_manager::set_val(std::string& val, parcel_ptr prcl, size_t bitn) {
            unum16 tmp = 0;
            if (bitn != NULL_BIT_NUM) {
                if (string_to_primtype<unum16 > (val, tmp)) {
                    prcl->value_cast(static_cast<bool> (tmp & (0x01 << (bitn))));}
                else {prcl->error(ERROR_IO_NO_DATA);}}
            else {
                switch (prcl->type()) {
                    case TYPE_NODEF:{
                        if (string_to_primtype<unum16 > (val, tmp))
                            prcl->value_cast<unum16 > (tmp);
                        else {
                            prcl->error(ERROR_IO_NO_PARSEDATA);};
                        break;}
                    default:{
                        return linemem_value_manager::set_val(val, prcl);}}}
            return error(0);}

        ns_error directnet_value_manager::get_val(std::string& val, parcel_ptr cmd, size_t bitn ) {
            unum16 tmp = 0;
            if (bitn != NULL_BIT_NUM) {
                val = cmd->value_cast<bool>() ? "on" : "of";
                return error(0);}
            else {
                switch (cmd->type()) {
                    case TYPE_NODEF:{
                        unum16 tmp =  cmd->value_cast<unum16>();;
                        if (cmd->isvalue()) {
                            val = primtype_to_string<unum16 > (cmd->value_cast<unum16>());
                            return error(0);}
                        return error(ERROR_IO_NO_GENERATE_REQ);}
                    default:{
                        return linemem_value_manager::get_val( val, cmd);}}}
            return error(ERROR_IO_NO_GENERATE_REQ);}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*basis_koyo_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error basis_koyo_protocol::readblock(block& blk) {
            error(0);
            koyodevn dvnum = ((blk.begin()->first->devnum() > 0) && (blk.begin()->first->devnum() <= MAX_KOYO_DEV_NUM)) ? 
                static_cast<num8> (blk.begin()->first->devnum()) : NO_KOYO_DEV_NUM;
            if (dvnum == NO_KOYO_DEV_NUM) return error(ERROR_IO_NO_CORRECT_ADDR);
            return read_impl(blk, dvnum);}

        ns_error basis_koyo_protocol::read_impl(const block& blk, koyodevn dvnum) {

            std::string resp = "";
            num32 strtaddr = blk.begin()->first->addr();
            size_t cnt = calculate_blocksize(blk.end()->first, blk.begin()->first);
            return error(read_request(dvnum, strtaddr, cnt, resp));}

        ns_error basis_koyo_protocol::writecmd(const std::string& vl, parcel_ptr cmd) {
            error(0);
            koyodevn dvnum = ((cmd->devnum() >= 0) && (cmd->devnum() <= MAX_KOYO_DEV_NUM)) ? 
                static_cast<num8> (cmd->devnum()) : -1;
            if (dvnum == NO_KOYO_DEV_NUM) 
                return error(ERROR_IO_NO_CORRECT_ADDR);
            write_impl(cmd, vl, dvnum);
            DEBUG_VAL_DVNCI(error())
            return error();}

        ns_error basis_koyo_protocol::write_impl(parcel_ptr cmd, const std::string& vl, koyodevn dvnum) {
            std::string req = "";
            size_t bitnum = cmd->indx();
            num32 strtaddr = cmd->addr();
            size_t cnt = 2;
            if (bitnum == NULL_BIT_NUM) {
                cnt = vl.size();
                return error(write_request(vl, dvnum, strtaddr, cnt * ex_koef()));}
            else {
                if ((strtaddr >= 040000) && (strtaddr <= 041177)) {
                    strtaddr = kseq_addr(strtaddr) + bitnum;
                    if (!error(kseq_write_request(dvnum, strtaddr, (vl == "on")))) {
                        return error(0);}}
                else {
                    std::string setv = "";
                    if (!error(read_request(dvnum, strtaddr, 2, setv))) {
                        if (setv.size() != 2) return error(ERROR_IO_PARSERESP);
                        if (!error(set_mask(setv, bitnum, (vl == "on")))) {
                            return error(write_request(setv, dvnum, strtaddr, cnt * ex_koef()));}}}}
            return error(ERROR_IO_NO_GENERATE_REQ);}

        ns_error basis_koyo_protocol::generate_body_impl(std::string& vl) {
            if (vl.size() < 2)
                return error(ERROR_IO_NO_GENERATE_REQ);
            if (!insert_hex_koyo_lrc(vl))
                return error(ERROR_IO_NO_GENERATE_REQ);
            return error(0);}

        ns_error basis_koyo_protocol::generate_body_kseq_write(std::string& vl, num32 startaddr, bool on) {
            std::string fnc = on ? KSEQUENCE_FC_SETBIT : KSEQUENCE_FC_RESETBIT;
            vl = SOH  + fnc + primtype_to_string<unum8 > (1) +
                    primtype_to_string<unum16 > (static_cast<unum16> (be_le_convert_num16(startaddr))) + ETB;
            basis_koyo_protocol::generate_body_impl(vl);
            return error(0);}

        ns_error basis_koyo_protocol::set_mask(std::string& vl, size_t bitnum, bool on ) {
            if ((vl.size() == 2) && (bitnum < 16)) {
                unum16 tmp = 0;
                unum16 btmp = 0x1;
                btmp = btmp << bitnum;
                if (string_to_primtype<unum16 > (vl, tmp)) {
                    tmp = on ? (tmp | btmp) : (tmp & (~btmp));
                    vl = primtype_to_string<unum16 > (tmp);
                    return error(0);}}
            return error(ERROR_IO_NO_GENERATE_REQ);}

        unum8 basis_koyo_protocol::byte_from_str(const std::string& vl, std::string::size_type n) {
            if (vl.size() <= n) {
                error(ERROR_IO_PARSERESP);
                return 0;}
            return vl.at(n);}

        num32 basis_koyo_protocol::kseq_addr(num32 vl) {
            if (vl < 040200) return 0xC000 + (vl - 040000) * 16;
            if (vl < 040400) return 0xD000 + (vl - 040200) * 16;
            if (vl < 040500) return 0xE000 + (vl - 040400) * 16;
            if (vl < 040600) return 0xE800 + (vl - 040500) * 16;
            return 0xF000 + (vl - 040600) * 16;}

        ns_error basis_koyo_protocol::check_envelope(std::string& resp, size_t cnt) {
            if (cnt != resp.size())
                return error(ERROR_IO_PARSERESP);
            readdata = resp;
            return error(0);};



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*HEX ??????? DIRECTNET*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error hex_direcnet_protocol::enq_impl(koyodevn dvnum, const std::string protstrt) {

            std::string req = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + ENQ;
            if (!error(ios->write(req))) {
                std::string resp = "";
                error(ios->read(resp, 3, DIRECTNET_TIMEOUT1));
                if (!error()) {
                    std::string resp_tmpl = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + ACK;
                    if (resp_tmpl == resp)
                        return error(0);
                    resp_tmpl = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + NAK;
                    error((resp_tmpl == resp) ? ERROR_IO_DEVICE_NAK : ERROR_IO_PARSERESP);}}
            return error();}

        ns_error hex_direcnet_protocol::read_eot_impl() {

            if (!error(ios->write(ACK))) {
                std::string resp = "";
                error(ios->read(resp, 1, DIRECTNET_TIMEOUT1));
                if (!error()) {
                    if (resp.size() < 1)
                        error(ERROR_IO_PARSERESP);
                    else {
                        if (resp != (EOT)) {
                            error(ERROR_IO_DEVICE_NAK);}}}}
            return error(eot_impl());}

        ns_error hex_direcnet_protocol::read_request(koyodevn dvnum,  num32 startaddr, size_t cnt, std::string& resp) {

            std::string req = "";
            if (!error(enq_impl(dvnum))) {
                if (!directnet_generate_body_read(req, dvnum, startaddr, cnt * ex_koef())) {
                    resp = "";
                    if (!error(directnet_read_request(req, resp, cnt * ex_koef()))) {
						if (!error(read_eot_impl())){
                             check_envelope(resp, cnt);
							 return error(0);}}}}
            //eot_impl();
			return error();}

        ns_error hex_direcnet_protocol::write_request(const std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt) {
            std::string req = "";
            if (!error(enq_impl(dvnum))) {
                cnt = vl.size();
                if (!directnet_generate_body_write(req, dvnum, startaddr, cnt * ex_koef())) {
                    return error(directnet_write_request(req, vl));}}
            return error(ERROR_IO_NO_GENERATE_REQ);}

        ns_error hex_direcnet_protocol::directnet_read_request(std::string& req, std::string& resp, size_t cnt) {
            resp = "";
            bool nk_tmpl = false;
            if (!error(ios->write(req))) {
                error(ios->read(resp, cnt + 4,  DIRECTNET_TIMEOUT2));
                if (!error()) {
                    if (resp.size() > 4) {
                        nk_tmpl = (resp.substr(0, 1) != ACK);
                        if (resp.substr(0, 1) == ACK) {
                            resp = resp.substr(1);
                            if (resp.substr(0, 1) == STX) {
                                return error(check_hex_koyo_lrc(resp) ? 0 : ERROR_IO_CRC);}}}}}
            return error(nk_tmpl ? ERROR_IO_DEVICE_NAK : ERROR_IO_PARSERESP);}

        ns_error hex_direcnet_protocol::directnet_write_request(std::string& req,  const std::string& wstr) {
            std::string resp = "";
            if (!error(ios->write(req))) {
                error(ios->read(resp, 1 , DIRECTNET_TIMEOUT2));
                if (!error()) {
                    if (resp.size() != 1) return error(ERROR_IO_PARSERESP);
                    if (resp.at(0) != ACK.at(0)) return error(ERROR_IO_DEVICE_NAK);
                    req = STX + wstr + ETX;
                    if (!generate_body_impl(req)) {
                        if (!error(ios->write(req))) {
                            resp = "";
                            error(ios->read(resp, 1, DIRECTNET_TIMEOUT2));
                            if (!error()) {
                                if (resp.size() != 1) return error(ERROR_IO_PARSERESP);
                                if (resp.at(0) != ACK.at(0)) return error(ERROR_IO_DEVICE_NAK);
                                eot_impl();
                                return error(0);}}}}}
            return error();}

        ns_error hex_direcnet_protocol::directnet_generate_body_read(std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt) {
            koyodevn bcddevnum = dvnum;
            if (!dec_to_bcd<koyodevn > (bcddevnum)) return error(ERROR_IO_NO_GENERATE_REQ);
            vl = SOH + num8_to_hexstr(static_cast<num8> (bcddevnum)) + DIRECTNET_FC_READ + DIRECTNET_V_DTTP +
                    num16_to_hexstr(static_cast<num16> (startaddr + 1)) +
                    num8_to_hexstr(static_cast<unum8> (0)) + num8_to_hexstr(static_cast<unum8> (cnt)) +
                    num8_to_hexstr(static_cast<unum8> (1)) + ETB;
            generate_body_impl(vl);
            return error(0);}

        ns_error hex_direcnet_protocol::directnet_generate_body_write(std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt) {
            koyodevn bcddevnum = dvnum;
            if (!dec_to_bcd<koyodevn > (bcddevnum)) return error(ERROR_IO_NO_GENERATE_REQ);
            vl = SOH + num8_to_hexstr(static_cast<num8> (bcddevnum)) + DIRECTNET_FC_WRITE + DIRECTNET_V_DTTP +
                    num16_to_hexstr(static_cast<num16> (startaddr + 1)) +
                    num8_to_hexstr(static_cast<unum8> (0)) + num8_to_hexstr(static_cast<unum8> (cnt)) +
                    num8_to_hexstr(static_cast<unum8> (1)) + ETB;
            generate_body_impl(vl);
            return error(0);}

        ns_error  hex_direcnet_protocol::kseq_write_request(koyodevn dvnum, num32 startaddr, bool on) {
            std::string req = "";
            if (!error(generate_body_kseq_write(req, startaddr, on))) {
                std::string resp = "";
                if (!error(enq_impl(dvnum, KSEQUENCE_NREQ))) {
                    if (!error(ios->write(req))) {
                        if (!error(ios->read(resp, 8,  DIRECTNET_TIMEOUT2))) {
                            if (resp.size() != 8) return error(ERROR_IO_PARSERESP);
                            if (resp.substr(0, 1) != ACK) return error(ERROR_IO_DEVICE_NAK);
                            read_eot_impl();
                            return error(0);}}}}
            return error(ERROR_IO_NO_GENERATE_REQ);}



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*??????? DIRECTNET ASCII*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error ascii_direcnet_protocol::enq_impl(koyodevn dvnum, const std::string protstrt) {

            std::string req = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + ENQ;
            if (!error(ios->write(req))) {
                std::string resp = "";
                error(ios->read(resp, 4, DIRECTNET_TIMEOUT1));
                if (!error()) {
                    std::string resp_tmpl = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + ACK + CR;
                    if (resp_tmpl == resp) return error(0);
                    resp_tmpl = protstrt + primtype_to_string<koyodevn > (dvnum + 0x20) + NAK + CR;
                    error((resp_tmpl == resp) ? ERROR_IO_DEVICE_NAK : ERROR_IO_PARSERESP);}}
            return error();}

        ns_error ascii_direcnet_protocol::read_eot_impl() {

            if (!error(ios->write(ACK))) {
                std::string resp = "";
                error(ios->read(resp, 1, DIRECTNET_TIMEOUT1));
                if (!error()) {
                    if (resp.size() < 2)
                        error(ERROR_IO_PARSERESP);
                    else {
                        if (resp != (EOT + CR)) {
                            error(ERROR_IO_DEVICE_NAK);}}}}
            eot_impl();
            return error();}

        ns_error ascii_direcnet_protocol::directnet_read_request(std::string& req, std::string& resp, size_t cnt) {
            resp = "";
            bool nk_tmpl = false;
            if (!error(ios->write(req))) {
                error(ios->read(resp, cnt + 7, DIRECTNET_TIMEOUT2));
                if (!error()) {
                    if (resp.size() > 7) {
                        nk_tmpl = (resp.substr(0, 2) != (ACK + CR));
                        if (resp.substr(0, 2) == (ACK + CR)) {
                            if (resp.substr(resp.size() - 1) == (CR)) {
                                resp = resp.substr(2, resp.size() - 3);
                                if ((resp.substr(0, 1) == STX) && ((resp.substr(resp.size() - 3, 1) == ETX))) {
                                    return error(check_ascii_koyo_lrc(resp) ? 0 : ERROR_IO_CRC);}}}}}}
            return error(nk_tmpl ? ERROR_IO_DEVICE_NAK : ERROR_IO_PARSERESP);}

        ns_error ascii_direcnet_protocol::directnet_write_request(std::string& req,  const std::string& wstr) {
            std::string resp = "";
            if (!error(ios->write(req))) {
                error(ios->read(resp, 2, DIRECTNET_TIMEOUT2));
                if (!error()) {
                    if (resp.size() != 2) return error(ERROR_IO_PARSERESP);
                    if (resp != (ACK + CR)) return error(ERROR_IO_DEVICE_NAK);
                    req = STX + wstr + ETX;
                    if (!generate_body_impl(req)) {
                        if (!error(ios->write(req))) {
                            resp = "";
                            error(ios->read(resp, 1, DIRECTNET_TIMEOUT2));
                            if (!error()) {
                                if (resp.size() != 2) return error(ERROR_IO_PARSERESP);
                                if (resp != (ACK + CR)) return error(ERROR_IO_DEVICE_NAK);
                                eot_impl();
                                return error(0);}}}}}
            return error();}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*???????? ECOM*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error ecom_protocol::readblock(block& blk) {
            error(0);
            return read_impl(blk, 1);}

        ns_error ecom_protocol::writecmd(const std::string& vl, parcel_ptr cmd) {
            error(0);
            DEBUG_VAL_DVNCI(binary_block_to_hexsequence_debug(vl))
            write_impl(cmd, vl, 1);
            DEBUG_VAL_DVNCI(error())
            return error();}

        ns_error ecom_protocol::read_request(koyodevn dvnum, num32 startaddr, size_t cnt, std::string& resp) {

            std::string req = "";
            if (!error(ccm_generate_body(req, startaddr, ECOM_CCM_FC_READ, cnt))) {
                if (!error(ios->write(req))) {
                    if (!error(ccm_response(resp))) {
                        if (resp.size() > 0) {
                            if (resp.substr(0, 1) == ECOM_ACK) {
                                if (!error(ccm_response(resp))) {
                                    if (!error(check_envelope(resp, cnt))) {
                                        readdata = resp;
                                        return error(0);}}}}}}}
            return error(ERROR_IO_PARSERESP);}

        ns_error ecom_protocol::write_request(const std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt) {

            std::string req = "";
            std::string resp = "";
            if (!error(ccm_generate_body(req, startaddr, ECOM_CCM_FC_WRITE, cnt, vl))) {
                if (!error(ios->write(req))) {
                    if (!error(ccm_response(resp))) {
                        if (resp.size() > 0) {
                            if (resp.substr(0, 1) == ECOM_ACK) {
                                if (!error(ccm_response(resp))) {
                                    return error(0);}}}}}}
            return error(ERROR_IO_PARSERESP);}

        ns_error ecom_protocol::kseq_write_request(koyodevn dvnum, num32 startaddr, bool on ) {

            std::string req = "";
            std::string resp = "";
            if (!ccm_kseq_generate_body(req, startaddr, on)) {
                if (!error(ios->write(req))) {
                    if (!error(ccm_response(resp))) {
                        if (resp.size() > 0) {
                            if (resp.substr(0, 1) == ECOM_ACK) {
                                if (!error(ccm_response(resp))) {
                                    return error(0);}}}}}}
            return error(ERROR_IO_PARSERESP);}

        ns_error ecom_protocol::ccm_generate_body(std::string& vl, num32 startaddr, const std::string fnc, size_t cnt, std::string wval) {

            unum16 crc = 0;
            vl = ECOM_CCM_RESP + primtype_to_string<unum8 > (static_cast<unum8> (0)) +
                    primtype_to_string<unum8 > (static_cast<unum8> (1)) + fnc + primtype_to_string<unum8 > (static_cast<unum8> (cnt)) +
                    primtype_to_string<num16 > (startaddr + 1) + ECOM_V_DTTP;
            if (fnc == ECOM_CCM_FC_WRITE)
                vl = vl + wval;
            unum16 msgsz = static_cast<unum16> (vl.size());
            if (calculate_ecom_crc(vl, crc, 0)) {
                vl = ECOM_ENV + primtype_to_string<unum16 > (++trasactcnt) +
                        primtype_to_string<unum16 > (crc) + primtype_to_string<unum16 > (msgsz) + vl;
                return error(0);}
            return error(ERROR_IO_NO_GENERATE_REQ);}

        ns_error ecom_protocol::ccm_kseq_generate_body(std::string& vl, num32 startaddr, bool on) {

            unum16 crc = 0;
            std::string kseqpeq = "";
            if (!error(generate_body_kseq_write(kseqpeq, startaddr, on ))) {
                vl = ECOM_KSEQ_RESP + primtype_to_string<unum8 > (static_cast<unum8> (0)) +
                        primtype_to_string<unum8 > (static_cast<unum8> (kseqpeq.size()))  +
                        primtype_to_string<unum8 > (static_cast<unum8> (0)) + kseqpeq;
                unum16 msgsz = static_cast<unum16> (vl.size());
                if (calculate_ecom_crc(vl, crc, 0)) {
                    vl = ECOM_ENV + primtype_to_string<unum16 > (++trasactcnt) +
                            primtype_to_string<unum16 > (crc) + primtype_to_string<unum16 > (msgsz) + vl;
                    return error(0);}}
            return error(ERROR_IO_NO_GENERATE_REQ);}

        ns_error ecom_protocol::ccm_response(std::string& resp) {
            resp = "";
            error(ios->read(resp, 9));
            if (!error()) {
                if (resp.size() >= 9) {
                    unum16 msg_sz = 0;
                    unum16 crc = 0;
                    unum16 msg_cnt = 0;
                    std::string tmp_cnt = resp.substr(7, 2);
                    if ((resp.substr(0, 3) == ECOM_ENV) &&
                            (string_to_primtype<unum16 > (resp.substr(3, 2), msg_cnt)) &&
                            (string_to_primtype<unum16 > (resp.substr(5, 2), crc)) &&
                            (string_to_primtype<unum16 > (tmp_cnt, msg_sz))) {
                        resp = "";
                        if (msg_cnt != trasactcnt) {
                            resp = "";
                            ios->clearbuff_deep(10, 5);
                            return error(ERROR_IO_PARSERESP);}
                        if (!error(ios->read(resp, static_cast<size_t> (msg_sz)))) {
                            unum16 crc_check = 0;
                            if (calculate_ecom_crc(resp, crc_check, 0))
                                return error(crc_check == crc ? 0 : 0);}}}}
            ios->clearbuff();
            return error(ERROR_IO_PARSERESP);}

        ns_error ecom_protocol::check_envelope(std::string& resp, size_t cnt) {
            if (resp.size() > 4) {
                if (resp.substr(0, 2) == (ECOM_CCM_RD_REQ + ECOM_CCM_RESP)) {
                    resp = resp.substr(4);
                    return error(cnt == resp.size() ? 0 : ERROR_IO_PARSERESP);}}
            return error(ERROR_IO_PARSERESP);}

}}