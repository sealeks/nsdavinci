/* 
 * File:   mg_protocol.cpp
 * Author: Serg
 * 
 * Created on 16 ?????? 2010 ?., 18:01
 *
 *
 */
#include <driverspec/iek1177_protocol.h>

namespace dvnci {
    namespace driver {

        using namespace std;

        std::string iek1177_lgk_datetime_to_str (const datetime& dt) {

            std::string minutes_ = to_str<int>(dt.time_of_day().minutes());
            fill_first_null_digit(minutes_, 2);
            std::string hours_ = to_str<int>(dt.time_of_day().hours());
            fill_first_null_digit(hours_, 2);

            std::string month_ = to_str<int>(static_cast<int> (dt.date().month()));
            fill_first_null_digit(month_, 2);
            std::string days_ = to_str<int>(dt.date().day());
            fill_first_null_digit(days_, 2);
            return (days_ +month_ + hours_ + minutes_);}


                /////////////////////////////////////////////////////////////////////////////////////////////////////

        bool insert_iek_lrc (std::string& src, std::string::size_type strt) {
            num8 crc = 0;
            if (calculate_iek_lrc(src, crc, strt)) {
                src = src + std::string((char*) &crc, 1);
                return true;}
            return false;}

        bool check_iek_lrc (std::string& src, std::string::size_type strt) {
            if (src.size()<(strt+1)) return false;
            num8 crc = 0;
            std::string::size_type it = src.size()-1;
            std::string ch_src = src.substr(0, src.size()-1);
            if (calculate_iek_lrc(ch_src, crc, strt)) {
                if (crc==src.at(it)) {
                    src = ch_src;
                    return true;}}
            return false;}

        bool calculate_iek_lrc (const std::string& src, num8& crc, std::string::size_type strt) {
            if (src.size()>strt) {
                for (std::string::size_type it = strt; it<src.size(); ++it ) {
                    crc = (it==strt) ? (0xFF & (src.at(it))) : (crc ^ (0xFF & (src.at(it))));}
                return true;}
            return false;}

        ////////////////////////////////////////////////////////////////////////////////////////


        ns_error      iek1177_protocol::read_val(parcel_ptr prcl) {
            std::string req = generate_val(prcl->chanel(), prcl->addr());
            std::string resp;
            if (!error(request(req, resp))) {
                iek1177_parce_val(resp);}
            return error();}

        std::string   iek1177_protocol::generate_val(num32 ch, num32 nm) {
            std::string tmp = MK1177_START_BODY_R + generate_addr(LGKA_TYPEITEM_SMPL, MK1177_FC_RD_VAL, ch, nm) + ETX;
            return tmp;}

        ns_error iek1177_protocol::iek1177_parce_val(std::string& resp) {
            std::string tmpvl = "";
            if (!check_body(resp, tmpvl)) {
                readdata = tmpvl;
                return 0;}
            return error();}

        ///////////////////////////////////////////////////////////////////////

        ns_error      iek1177_protocol::read_arr(parcel_ptr prcl) {
            std::string req = generate_arr(prcl->chanel(), prcl->addr(), prcl->indx() );
            std::string resp;
            if (!error(request(req, resp))) {
                iek1177_parce_val(resp);}
            return error();}

        std::string   iek1177_protocol::generate_arr(num32 ch, num32 nm, num32 ind) {
            std::string tmp = MK1177_START_BODY_R +  generate_addr(LGKA_TYPEITEM_ARRAY, MK1177_FC_RD_ARR, ch, nm, ind)  + ETX;
            return tmp;}

        //////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error      iek1177_protocol::read_arh(parcel_ptr prcl) {
            datetime start, stop;
            prcl->report_range(start, stop);
            std::string req = generate_arh(prcl->chanel(), prcl->addr(), start );
            std::string resp;
            if (!error(request(req, resp))) {
                error(parce_arch(resp));}
            return error();}

        std::string   iek1177_protocol::generate_arh(num32 ch, num32 nm, const datetime& dt) {
            ch = ((ch<1000) && (ch>-1)) ? ch : 999;
            nm = ((nm<1000) && (nm>-1)) ? nm : 999;
            std::string chstr = to_str<num32>(ch);
            fill_first_null_digit(chstr, 3);
            std::string nmstr = to_str<num32>(nm);
            fill_first_null_digit(nmstr, 3);
            std::string tmp = MK1177_START_BODY_R +  MK1177_FC_RD_ARH + "." + nmstr +chstr +  iek1177_lgk_datetime_to_str(dt) + ETX;
            return tmp;}

        ns_error iek1177_protocol::parce_arch(std::string& resp) {
            std::string tmpvl = "";
            if (!check_body(resp, tmpvl)) {
                std::string::size_type it = tmpvl.find(" ");
                if ((it!=std::string::npos) && ((it+1)<tmpvl.size())) {
                    tmpvl = tmpvl.substr(it+1);
                    readdata = tmpvl;}}
            return error();}

        /////////////////////////////////////////////////////////////////////////

        ns_error  iek1177_protocol::write_val(parcel_ptr cmd, const std::string& vlstr) {
            std::string req;
            std::string resp;
            generate_write_body_val(req, vlstr, cmd->chanel(), cmd->addr());
            if (!error(request(req, resp))) {
                if (!error(iek1177_is_error(resp))) {
                    return error(0);}}
            return error();}

        ////////////////////////////////////////////////////////////////////////

        ns_error  iek1177_protocol::write_arr(parcel_ptr cmd, const std::string& vlstr) {
            std::string req;
            std::string resp;
            generate_write_body_arr(req, vlstr, cmd->chanel(), cmd->addr(), cmd->indx());
            if (!error(request(req, resp))) {
                if (!error(iek1177_is_error(resp))) {
                    return error(0);}}
            return error();}



}}