/* 
 * File:   mg_protocol.h
 * Author: Serg
 *
 * Created on 16 ?????? 2010 ?., 18:01
 */

#ifndef LGK_MG_PROTOCOL_H
#define	LGK_MG_PROTOCOL_H


#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/driver_detail.h>
#include <kernel/basis_iostream.h>

namespace dvnci {
    namespace driver {


        const parcelkind LGKA_TYPEITEM_SMPL    = 0;
        const parcelkind LGKA_TYPEITEM_ARCHIVE = 1;
        const parcelkind LGKA_TYPEITEM_ARRAY   = 2;

        const num32 LGKA_PROT_SP    = 0;
        const num32 LGKA_PROT_MEC   = 1;

        // ????????????? ????????
        // ???????  ( ???? ?????? - ?????)
        // ?????? ????????
        const std::string MG_FC_RD_VAL_R =  "\x1D";
        const std::string MG_FC_RD_VAL_A =  "\x03";
        // ?????? ????????
        const std::string MG_FC_WR_VAL_R =  "\x03";
        const std::string MG_FC_WR_VAL_A =  "\x16";
        // ?????? ???????
        const std::string MG_FC_RD_ARR_R =  "\x0C";
        const std::string MG_FC_RD_ARR_A =  "\x14";
        // ?????? ???????
        const std::string MG_FC_WR_ARR_R =  "\x14";
        const std::string MG_FC_WR_ARR_A =  "\x7F";
        //?????? ??????
        const std::string MG_FC_RD_ARH_R =  "\x0E";
        const std::string MG_FC_RD_ARH_A =  "\x16";

        const std::string MG_START_ENV   =  DLE + SOH;
        const std::string MG_FUNC_ENV    =  DLE + IS1;

        const std::string MG_START_BODY  =  DLE + STX;
        const std::string MG_END_BODY    =  DLE + ETX;

        // Regex ????????? ?????????????? ?????????

        const std::string MG_RD_VAL_RESP       = MG_START_ENV + ".{0,2}?" + MG_FUNC_ENV + MG_FC_RD_VAL_A +  MG_START_BODY + ".{0,}" + MG_END_BODY + ".{2,2}";
        const std::string MG_RD_ARR_RESP       = MG_START_ENV + ".{0,2}?" + MG_FUNC_ENV + MG_FC_RD_ARR_A +  MG_START_BODY + ".{0,}" + MG_END_BODY + ".{2,2}";
        const std::string MG_RD_ARH_RESP       = MG_START_ENV + ".{0,2}?" + MG_FUNC_ENV + MG_FC_RD_ARH_A +  MG_START_BODY + ".{0,}" + MG_END_BODY + ".{2,2}";

        //////////////////////////////////////////////////////////////////////////////////

        const num32 TIME_SYNC_NM = 21;
        const num32 DATE_SYNC_NM = 20;

        const num32   MAX_NUM_MG = 30;

        std::string mg_lgk_datetime_to_str ( const datetime& dt);
        std::string mg_lgk_date_to_str ( const datetime& dt);
        std::string mg_lgk_time_to_str (const datetime& dt);
        std::string lgk_date_to_str ( const datetime& dt);
        std::string lgk_time_to_str (const datetime& dt);
        datetime    mg_lgk_str_to_datetime (std::string vl);

        class mg_value_manager : public abstract_value_manager {

            struct parcel_addr {

                parcel_addr() : chanal(-1), number(-1) , index(-1) {};

                parcel_addr( num32 ch, num32 num, num32 inx = -1) : chanal(ch), number(num) , index(inx) {};

                friend bool operator<(const parcel_addr& ls, const parcel_addr & rs) {
                    if (ls.chanal != rs.chanal) return (ls.chanal < rs.chanal);
                    if (ls.number != rs.number) return (ls.number < rs.number);
                    if (ls.index != rs.index) return (ls.index < rs.index);
                    return false;}

                friend bool operator==(const parcel_addr& ls, const parcel_addr & rs) {
                    return ((ls.chanal == rs.chanal) && (ls.number == rs.number) && (ls.index == rs.index));}

                friend bool operator!=(const parcel_addr& ls, const parcel_addr & rs) {
                    return (ls != rs);}
                num32 chanal;
                num32 number;
                num32 index;} ;

            typedef std::pair<parcel_addr, std::string > parcel_addr_strval_pair;
            typedef std::map<parcel_addr,  std::string , std::less<parcel_addr>,
            std::allocator<parcel_addr_strval_pair > > parcel_addr_strval_map;

            typedef std::pair<std::string, std::string > str_str_pair;
            typedef std::vector<str_str_pair > str_str_vect;

            typedef std::pair<parcel_addr, str_str_vect > parcel_addr_str_str_vect_pair;
            typedef std::map<parcel_addr,  str_str_vect , std::less<parcel_addr>,
            std::allocator<parcel_addr_str_str_vect_pair > > parcel_addr_str_str_vect_map;



        public:

            mg_value_manager() :  abstract_value_manager() {}

            virtual ns_error set_value(const std::string& val, block& blk);

            virtual ns_error get_value(std::string& val, parcel_ptr cmd);

        protected:

            ////////////////////////////////////////////////////////////////////////////////////

            void set_val(const block& blk);

            void set_val(parcel_ptr prcl);

            void set_arch(const block& blk);

            void set_arch(parcel_ptr prcl);

            bool get_val(std::string& vl, num32 ch, num32 num, num32 inx);

            /////////////////////////////////////////////////////////////////////////////////////////////////////////

            bool parse_address(const std::string& val, parcel_addr& addr);

            size_t  parse_vals(const std::string& val);

            bool parse_val(const std::string& val, std::string& vl);

            size_t   parse_arrs(const std::string& val);

            size_t   parse_arhs(const std::string& val);

            bool parse_arh(const std::string& val, std::string& vl, std::string& dt);

            str_vect                      tmpvct1;
            str_vect                      tmpvct2;
            parcel_addr_strval_map        valuemap;
            parcel_addr_str_str_vect_map  archvalmap;} ;


            

        class mg_protocol : public templ_protocol<mg_value_manager> {
        public:

            mg_protocol(basis_iostream_ptr io) : templ_protocol<mg_value_manager>(io) {}

            virtual bool init() { return (ios) && (!check_proxy());}



            virtual bool utiloperation(const num32_set& vl){
                DEBUG_STR_DVNCI(UTILOPERATION)
                for (num32_set::const_iterator it=vl.begin();it!=vl.end();++it){
                    sync_time_device(*it);
                    DEBUG_VAL_DVNCI(*it);}
                return true;}


        protected:
            
            virtual ns_error readblock(block& blk);

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd);
            
            ns_error check_proxy();

            ns_error parse_proxy_address(const std::string& vl, num8& addr);

            ns_error check_envelope(std::string& rsp,  const std::string& fnc, num8 srcaddr, num8 rcvaddr );

            ns_error parse_envelope(std::string& resp, const std::string& fnc,  num8 dvnum) {
                if (!check_envelope(resp, fnc, (proxyaddr | 0x80), dvnum )) {
                    readdata = resp;}
                return error();}

            std::string& generate_envelope(std::string& vl, const std::string& fnc, num8 srcaddr = -1 , num8 rcvaddr = - 1);

            std::string& generate_body(std::string& vl) {
                vl = MG_START_BODY  + vl + MG_END_BODY;
                return vl;}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error request(std::string& req, std::string& resp, const std::string& resptempl) {
                insert_ccitt_crc(req, 2);
                if (!error(ios->write(req))) {
                    if (!error(ios->read_until(resp, boost::regex(resptempl)))) {
                        error(check_and_clear_ccitt_crc(resp, 2) ? 0 : ERROR_IO_CRC);}}
                return error();}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error  read_val(const block& blk, num8 dvnum);

            std::string&  generate_body_vals(std::string& vl, const block& blk, num8 dvnum);

            std::string   generate_val(num32 ch, num32 nm) {
                return HT + to_str(ch) + HT + to_str(nm) + FF;}

            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error  read_arr(const block& blk, num8 dvnum);

            std::string&  generate_body_arrs(std::string& vl, const block& blk, num8 dvnum);

            std::string  generate_arr(num32 ch, num32 nm, num32 ind, num32 cnt) {
                return HT + to_str(ch) + HT + to_str(nm) + HT + to_str(ind) + HT + to_str(cnt) + FF;}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error  read_arh(const block& blk, num8 dvnum);

            std::string&  generate_body_arhs(std::string& vl, const block& blk, num8 dvnum);

            std::string  generate_arh(num32 ch, num32 nm, datetime& start, datetime& stop) {
                return HT + to_str(ch) + HT + to_str(nm) + FF   + mg_lgk_datetime_to_str(stop) + FF + mg_lgk_datetime_to_str(start) + FF;}


            //////////////////////////////////////////////////////////////////////////////////////////////////////////

            ns_error  write_val(parcel_ptr cmd, const std::string& vl, num8 dvnum);

            std::string&  generate_write_body_val(std::string& vl, const std::string& vlstr, num32 ch, num32 nm,  num8 dvnum) {
                vl = HT + to_str(ch) + HT + to_str(nm) + FF + HT + vlstr + FF;
                generate_envelope(generate_body(vl), MG_FC_WR_VAL_R, dvnum, (proxyaddr | 0x80));
                insert_ccitt_crc(vl, 2);
                return vl;}

            ////////////////////////////////////////////////////////////////////////

            ns_error write_arr(parcel_ptr cmd, const std::string& vl, num8 dvnum);

            std::string&  generate_write_body_arr(std::string& vl, const std::string& vlstr, num32 ch, num32 nm, num32 ind,  num8 dvnum) {
                vl = HT + to_str(ch) + HT + to_str(nm) + HT + to_str(ind) + HT + "1" + FF + HT + vlstr + FF;
                generate_envelope(generate_body(vl), MG_FC_WR_ARR_R, dvnum, (proxyaddr | 0x80));
                insert_ccitt_crc(vl, 2);
                return vl;}

            ns_error  sync_time_device(num32 devnum);

            str_vect   tmpvct;
            num8    proxyaddr;} ;



}}

#endif	/* MG_PROTOCOL_H */

