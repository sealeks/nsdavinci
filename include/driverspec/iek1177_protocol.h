/* 
 * File:   mg_protocol.h
 * Author: Serg
 *
 * Created on 16 ?????? 2010 ?., 18:01
 */

#ifndef LGK_MK1177_PROTOCOL_H
#define	LGK_MK1177_PROTOCOL_H


#include <driverspec/spbmg_protocol.h>


namespace dvnci {
    namespace driver {

        //////////////////////////////////////////////////////////////////////////////////

        // ??? ????????

        const std::string MK1177_FC_R =  "R";
        const std::string MK1177_FC_W =  "W";

        const std::string MK1177_ASCII =  "1";

        const std::string MK1177_START_ENV_R   =  SOH + MK1177_FC_R + MK1177_ASCII;
        const std::string MK1177_START_ENV_W    = SOH + MK1177_FC_W + MK1177_ASCII;

        const std::string MK1177_START_BODY_R   =  MK1177_START_ENV_R + STX;
        const std::string MK1177_START_BODY_W    = MK1177_START_ENV_W + STX;

        // ?????? ????????
        const std::string MK1177_FC_RD_VAL =  "035";
        // ?????? ????????
        const std::string MK1177_FC_WR_VAL =  "003";
        // ?????? ???????
        const std::string MK1177_FC_RD_ARR =  "014";
        // ?????? ???????
        const std::string MK1177_FC_WR_ARR =  "024";
        //?????? ??????
        const std::string MK1177_FC_RD_ARH =  "016";

        const std::string MK1177_RESP      =  "((" + STX + "\\(.{0,}\\)" + ETX + ".{1,1})|" + NAK + "|" + ACK + ")";


        ///////////////////////////////////////////////////////////////////////////////////


        std::string iek1177_lgk_datetime_to_str (const datetime& dt);


        bool calculate_iek_lrc (const std::string& src, num8& crc, std::string::size_type strt);
        bool insert_iek_lrc (std::string& src, std::string::size_type strt);
        bool check_iek_lrc (std::string& src, std::string::size_type strt);

        class lgk_iek1177_value_manager : public abstract_value_manager {
        public:

            lgk_iek1177_value_manager() :  abstract_value_manager() {}

            virtual ns_error set_value(const std::string& val, block& blk) {
                error(0);
                std::string tmpvl = "";
                parcelkind tp =    blk.begin()->first->kind();
                switch (tp) {
                    case LGKA_TYPEITEM_SMPL:{
                        if (!parse_val(val, tmpvl)) 
                            blk.begin()->first->value_cast(tmpvl);
                        return error();}
                    case LGKA_TYPEITEM_ARCHIVE:{
                        if (!parse_val(val, tmpvl)) 
                            blk.begin()->first->value_cast(tmpvl);
                        return error();}
                    case LGKA_TYPEITEM_ARRAY:{
                        datetime start, stop;
                        dt_val_map mp;
                        blk.begin()->first->report_range(start, stop);
                        parse_arh(tmpvl, start, mp );
                        blk.begin()->first->value_report(mp);
                        return error();}}
                return 0;}

            virtual ns_error get_value(std::string& val, parcel_ptr cmd) {
                val = cmd->value_cast<std::string>();
                return 0;};

        protected:

            ns_error parse_val(const std::string& vl, std::string& val) {
                val = comma_to_point_copy(vl);
                return error(0);}

            ns_error parse_arh(const std::string& val, const datetime& dt, dt_val_map& mp) {
                mp.clear();
                std::string strval = comma_to_point_copy(val);
                double vl = 0;
                if (!str_to<double>(strval, vl)) vl = NULL_DOUBLE;
                mp.insert(dt_val_pair(dt, vl));
                return error(0);}} ;

        class iek1177_protocol : public templ_protocol<lgk_iek1177_value_manager> {
        public:

            iek1177_protocol(basis_iostream_ptr io) : templ_protocol<lgk_iek1177_value_manager>(io) {}




        protected:
            
            virtual ns_error readblock(block& blk) {
                error(0);
                num8  dvnum = ((blk.begin()->first->devnum() >= 0) && (blk.begin()->first->devnum() <= 30)) ? static_cast<num8> (blk.begin()->first->devnum()) : -1;
                switch (blk.begin()->first->kind()) {
                    case LGKA_TYPEITEM_SMPL:    return    read_val(blk.begin()->first);
                    case LGKA_TYPEITEM_ARCHIVE:   return  read_arh(blk.begin()->first);
                    case LGKA_TYPEITEM_ARRAY:    return   read_arr(blk.begin()->first);}
                return error();}

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd) {
                error(0);
                switch (cmd->kind()) {
                    case LGKA_TYPEITEM_SMPL:    return  write_val(cmd, vl);
                    case LGKA_TYPEITEM_ARRAY:   return  write_arr(cmd, vl);}
                return error();}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error request(std::string& req, std::string& resp) {
                insert_iek_lrc(req, 1);
                if (!error(ios->write(req))) {
                    if (!error(ios->read_until(resp, boost::regex(MK1177_RESP)))) {
                        error(check_iek_lrc(resp, 1) ? 0 : ERROR_IO_CRC);}}
                return error();}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error     check_body(std::string& rsp, std::string& vl) {
                std::string rgxsearch = "(?<=" + STX + "\\()" + ".{0,}" + "(?=\\)" + ETX + ")";
                std::string rgxmatch = STX + "\\(.{0,}\\)" + ETX;
                if (boost::regex_match(rsp,  boost::regex(rgxmatch))) {
                    boost::smatch rslt1;
                    if (boost::regex_search(rsp,  rslt1,  boost::regex(rgxsearch))) {
                        if (rslt1.size() == 1) {
                            vl = rslt1[0];
                            std::string::size_type it = vl.find_first_of("*");
                            if (it != std::string::npos) vl = vl.substr(0, it);
                            return error(0);}}}
                return error(ERROR_IO_PARSERESP);}

            ns_error iek1177_is_error(const std::string& vl) {
                if (vl.size() == 0) return ERROR_IO_PARSERESP;
                if (vl.size() == 1) {
                    if (vl.at(0) != ACK.at(0)) return ERROR_IO_PARSERESP;}
                return 0;}

            std::string generate_addr(num32 tp, const std::string& fnc, num32 ch, num32 nm, num32 ind = -1) {
                ch = ((ch < 1000) && (ch>-1)) ? ch : 999;
                nm = ((nm < 1000) && (nm>-1)) ? nm : 999;
                ind = ((ind < 1000) && (ind>-1)) ? ind : 999;
                std::string chstr = to_str<num32 > (ch);
                fill_first_null_digit(chstr, 3);
                std::string nmstr = to_str<num32 > (nm);
                fill_first_null_digit(nmstr, 3);
                std::string indstr = to_str<num32 > (ind);
                fill_first_null_digit(indstr, 3);
                switch (tp) {
                    case LGKA_TYPEITEM_SMPL:     return   fnc + "." + chstr + nmstr;
                    case LGKA_TYPEITEM_ARRAY:    return   fnc + "." + nmstr + chstr + indstr;}
                return "";}

            ////////////////////////////////////////////////////////////////////////

            ns_error      read_val(parcel_ptr prcl);

            std::string   generate_val(num32 ch, num32 nm);

            ns_error      iek1177_parce_val(std::string& resp);

            ///////////////////////////////////////////////////////////////////////

            ns_error      read_arr(parcel_ptr prcl);

            std::string   generate_arr(num32 ch, num32 nm, num32 ind);

            //////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error      read_arh(parcel_ptr prcl);

            std::string   generate_arh(num32 ch, num32 nm, const datetime& dt);

            ns_error     parce_arch(std::string& resp);

            ///////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error  write_val(parcel_ptr cmd, const std::string& vlstr);

            std::string&  generate_write_body_val(std::string& vl, std::string vlstr, num32 ch, num32 nm) {
                vl = MK1177_START_BODY_W +  generate_addr(LGKA_TYPEITEM_SMPL, MK1177_FC_WR_VAL, ch, nm) + comma_to_point_copy(vlstr) + ")" + ETX;
                return vl;}

            ////////////////////////////////////////////////////////////////////////

            ns_error  write_arr(parcel_ptr cmd, const std::string& vlstr);

            std::string&  generate_write_body_arr(std::string& vl, std::string vlstr, num32 ch, num32 nm, num32 ind) {
                vl = MK1177_START_BODY_W +  generate_addr(LGKA_TYPEITEM_ARRAY, MK1177_FC_WR_ARR, ch, nm, ind)  + "(" + comma_to_point_copy(vlstr) +  ")" + ETX;
                return vl;}

} ;

}}

#endif	/* MG_PROTOCOL_H */

