/* 
 * File:   mg_protocol.cpp
 * Author: Serg
 * 
 * Created on 16 ������ 2010 �., 18:01
 *
 *
 */
#include "mg_protocol.h"

namespace dvnci {
    namespace driver {

        using namespace std;

        std::string mg_lgk_datetime_to_str (const datetime& dt) {
            return mg_lgk_date_to_str(dt) + mg_lgk_time_to_str(dt);}

        std::string mg_lgk_date_to_str (const datetime& dt) {
            std::string day_ = to_str(dt.date().day());
            std::string month_ = to_str(dt.date().month().as_number());
            std::string year_ = to_str((dt.date().year()) % 100);
            return day_ + HT + month_ + HT + year_ + HT;}

        std::string mg_lgk_time_to_str (const datetime& dt) {
            std::string hour_ = to_str(dt.time_of_day().hours());
            std::string minute_ = to_str(dt.time_of_day().minutes());
            std::string second_ = to_str(dt.time_of_day().seconds());
            return hour_ + HT + minute_ + HT + second_ + HT;}

        std::string lgk_date_to_str (const datetime& dt) {
            std::string day_ = to_str(dt.date().day());
            std::string month_ = to_str(dt.date().month().as_number());
            std::string year_ = to_str((dt.date().year()) % 100);
            return fill_first_null_digit(day_,2) + "-" + fill_first_null_digit(month_,2) + "-" + fill_first_null_digit(year_,2);}

        std::string lgk_time_to_str (const datetime& dt) {
            std::string hour_ = to_str(dt.time_of_day().hours());
            std::string minute_ = to_str(dt.time_of_day().minutes());
            std::string second_ = to_str(dt.time_of_day().seconds());
            return fill_first_null_digit(hour_,2) + "-" + fill_first_null_digit(minute_,2) + "-" + fill_first_null_digit(second_,2);}


        datetime    mg_lgk_str_to_datetime (std::string src) {
            try {
                if (src.size()<17) return datetime();
                std::string::size_type it1 = src.find_first_of("/");
                if (it1==std::string::npos) return datetime();
                std::string dt_str = src.substr(0, it1);
                if ((it1+1)==src.size()) return datetime();
                std::string tm_str = src.substr(it1+1);
                if ((dt_str.size()<8) || (tm_str.size()<8)) return datetime();

                std::string dtday_str = dt_str.substr(0, 2);
                std::string dtmonth_str = dt_str.substr(3, 2);
                std::string dtyear_str = dt_str.substr(6);

                std::string tmhour_str = tm_str.substr(0, 2);
                std::string tmminute_str = tm_str.substr(3, 2);
                std::string tmsec_str = tm_str.substr(6);

                num16 dtday_, dtmonth_, dtyear_ = 0;
                num16 tmhour_, tmminute_, tmsec_ = 0;

                if ((!str_to<num16>(dtday_str, dtday_)) ||
                        (!str_to<num16>(dtmonth_str, dtmonth_)) ||
                        (!str_to<num16>(dtyear_str, dtyear_))) return datetime();

                if ((!str_to<num16>(tmhour_str, tmhour_)) ||
                        (!str_to<num16>(tmminute_str, tmminute_)) ||
                        (!str_to<num16>(tmsec_str, tmsec_))) return datetime();

                dtyear_ = (dtyear_<100) ?
                        ((dtyear_<50) ? ( 2000 + dtyear_) : (1900 + dtyear_)) : dtyear_;


                return datetime(boost::gregorian::date(dtyear_, dtmonth_, dtday_),
                        boost::posix_time::hours(tmhour_) +
                        boost::posix_time::minutes(tmminute_) +
                        boost::posix_time::seconds(tmsec_));}
            catch (...) {}
            return datetime();}


         ns_error mg_value_manager::set_value(const std::string& val, block& blk) {
                clearerror();
                num32 tp =    blk.start->first->type();
                switch (tp) {
                    case LGKA_TYPEITEM_SMPL:{
                        if  ((parse_vals(val)>0)) set_val(blk);
                        return error();}
                    case LGKA_TYPEITEM_ARCHIVE:{
                        if  (parse_arhs(val)>0) set_arch(blk);
                        return error();}
                    case LGKA_TYPEITEM_ARRAY:{
                        if  (parse_arrs(val)>0) set_val(blk);
                        return error();}}
                return error();}

        ns_error mg_value_manager::get_value(std::string& val, parcel_ptr cmd) {
                clearerror();
                val = cmd->val_as_str();
                return error(0);};

        void mg_value_manager::set_val(const block& blk) {
            parcel_const_iterator endit = blk.stop;
            endit++;
            for (parcel_const_iterator it = blk.start; it!=endit; ++it) {
                set_val(it->first);}}

        void mg_value_manager::set_val(parcel_ptr prcl) {
            std::string tmp;
            if (get_val(tmp, prcl->chanel() , prcl->addr(),
                    ((prcl->type()==LGKA_TYPEITEM_SMPL) ?  -1 : prcl->tp()))) {
                prcl->set_simpl_val_from_str(tmp);}}

        void mg_value_manager::set_arch(const block& blk) {
            set_arch(blk.start->first);}

        void mg_value_manager::set_arch(parcel_ptr prcl) {
            parcel_addr_str_str_vect_map::iterator itval
                    = archvalmap.find(parcel_addr(prcl->chanel() , prcl->addr()));
            if (itval!=archvalmap.end()) {
                str_str_vect tmpvctdt = itval->second;
                dt_val_map tmpdtvlmap;
                std::string tmpstrvl;
                std::string tmpdt;
                for (str_str_vect::const_iterator itdt = tmpvctdt.begin(); itdt!=tmpvctdt.end(); ++itdt) {
                    tmpstrvl = strcomma_to_dot(itdt->first);
                    double tmpval = 0;
                    datetime tmpdt = mg_lgk_str_to_datetime(itdt->second);
                    if (!tmpdt.is_special()) {
                        if (str_to<double>(tmpstrvl, tmpval)) {
                            tmpdtvlmap.insert(dt_val_pair(mg_lgk_str_to_datetime(itdt->second), tmpval));}
                        else tmpdtvlmap.insert(dt_val_pair(mg_lgk_str_to_datetime(itdt->second), NULL_DOUBLE));}}
                if (!tmpdtvlmap.empty())
                    prcl->set_report_val(tmpdtvlmap);}}

        bool mg_value_manager::get_val(std::string& vl, num32 ch, num32 num, num32 inx) {
            parcel_addr_strval_map::const_iterator it = valuemap.find(parcel_addr(ch, num, inx));
            if (it != valuemap.end()) {
                vl = it->second;
                return true;}
            return false;}

        bool mg_value_manager::parse_address(const std::string& val, parcel_addr& addr) {
            split_str_prefix(val, HT, tmpvct2);
            if (tmpvct2.size() < 2) return false;
            if (!str_to<num32 > (tmpvct2.at(0), addr.chanal)) return false;
            if (!str_to<num32 > (tmpvct2.at(1), addr.number)) return false;
            if (tmpvct2.size() == 2) return true;
            if (!str_to<num32 > (tmpvct2.at(2), addr.index)) return false;
            return true;}

        size_t  mg_value_manager::parse_vals(const std::string& val) {
            valuemap.clear();
            split_str_postfix(val, FF, tmpvct1);
            for (str_vect::size_type  i = 0; i<(tmpvct1.size()-1); i = i + 2 ) {
                parcel_addr tmpaddr;
                if (parse_address(tmpvct1.at(i), tmpaddr)) {
                    std::string tmpvl;
                    if (parse_val(tmpvct1.at(i+1), tmpvl)) {
                        valuemap.insert(parcel_addr_strval_pair(tmpaddr, tmpvl));}}}
            return valuemap.size();}

        bool mg_value_manager::parse_val(const std::string& val, std::string& vl) {
            split_str_prefix(val, HT, tmpvct2);
            if (tmpvct2.empty()) return false;
            vl = tmpvct2.at(0);
            return true;}

        size_t   mg_value_manager::parse_arrs(const std::string& val) {
            valuemap.clear();
            split_str_postfix(val, FF, tmpvct1);
            if (tmpvct1.size()>1) {
                parcel_addr tmpaddr;
                if (parse_address(tmpvct1.at(0), tmpaddr)) {
                    if (tmpaddr.index!=npos) {
                        for (str_vect::size_type  i = 1; i<tmpvct1.size(); ++i) {
                            std::string tmpvl;
                            if (parse_val(tmpvct1.at(i), tmpvl)) {
                                valuemap.insert(parcel_addr_strval_pair(tmpaddr, tmpvl));}
                            tmpaddr.index++;}}}}
            return valuemap.size();}

        size_t   mg_value_manager::parse_arhs(const std::string& val) {
            archvalmap.clear();
            split_str_postfix(val, FF, tmpvct1);
            if ((tmpvct1.size()>3)) {
                parcel_addr tmpaddr;
                if (parse_address(tmpvct1.at(0), tmpaddr)) {
                    str_str_vect tmpvectdt;
                    for (str_vect::size_type  i = 3; i<tmpvct1.size(); ++i) {
                        std::string tmpvl;
                        std::string tmpdt;
                        if (parse_arh(tmpvct1.at(i), tmpvl, tmpdt)) {
                            tmpvectdt.push_back(str_str_pair(tmpvl, tmpdt));}}
                    archvalmap.insert(parcel_addr_str_str_vect_pair(tmpaddr, tmpvectdt));}}
            return archvalmap.size();}

        bool mg_value_manager::parse_arh(const std::string& val, std::string& vl, std::string& dt) {
            split_str_prefix(val, HT, tmpvct2);
            if (tmpvct2.size()<3) return false;
            vl = tmpvct2.at(0);
            dt = tmpvct2.at(2);
            return true;}

        ////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////////////////////////////////////


        ns_error mg_protocol::readblock(block& blk) {
                clearerror();
                num32 tp =    blk.start->first->type();
                num8  dvnum = ((blk.start->first->devnum() >= 0) && (blk.start->first->devnum() <= MAX_NUM_MG)) ? static_cast<num8> (blk.start->first->devnum()) : -1;
                if (dvnum==proxyaddr) dvnum = -1;
                switch (tp) {
                    case LGKA_TYPEITEM_SMPL:    return  read_val(blk, dvnum);
                    case LGKA_TYPEITEM_ARCHIVE: return  read_arh(blk, dvnum);
                    case LGKA_TYPEITEM_ARRAY:   return  read_arr(blk, dvnum);}
                return error();}

        ns_error mg_protocol::writecmd(const std::string& vl, parcel_ptr cmd) {
                clearerror();
                num32 tp =    cmd->type();
                num8  dvnum = ((cmd->devnum() >= 0) && (cmd->devnum() <= MAX_NUM_MG)) ? static_cast<num8> (cmd->devnum()) : -1;
                if (dvnum==proxyaddr) dvnum = -1;
                switch (tp) {
                    case LGKA_TYPEITEM_SMPL:    return  write_val(cmd, vl, dvnum);
                    case LGKA_TYPEITEM_ARRAY:   return write_arr(cmd, vl, dvnum);}
                return error();}

        ns_error mg_protocol::check_proxy() {
            std::string vl = generate_val(0, 3);
            std::string resp;
            if (!error(request(generate_envelope(generate_body(vl), MG_FC_RD_VAL_R), resp, MG_RD_VAL_RESP))) {
                if (!parse_envelope(resp, MG_FC_RD_VAL_A, -1)) {
                    tmpvct.clear();
                    split_str_postfix(resp, FF, tmpvct);
                    if (tmpvct.size()>=2) {
                        resp = tmpvct[1];
                        tmpvct.clear();
                        split_str_prefix(resp, HT, tmpvct);
                        if (tmpvct.size()>0) {
                            std::string tmp = tmpvct[0];
                            return parse_proxy_address(tmp, proxyaddr);}}}}
            return error(ERROR_IO_NOINIT_PROTOCOL);}

        ns_error mg_protocol::parse_proxy_address(const std::string& vl, num8& addr) {
            if (vl.size() < 10) return false;
            std::string tmp = vl.substr(5, 2);
            clear_first_null_digit(tmp);
            num16 tmpaddr = 0;
            if (str_to<num16> (tmp, tmpaddr)) {
                addr = static_cast<num8> (tmpaddr);
                return 0;}
            return error(ERROR_IO_NOINIT_PROTOCOL);}

        ns_error  mg_protocol::read_val(const block& blk, num8 dvnum) {
            std::string req;
            std::string resp;
            generate_body_vals(req, blk, dvnum);
            if (!error(request(req, resp, MG_RD_VAL_RESP))) {
                parse_envelope(resp, MG_FC_RD_VAL_A, dvnum);}
            return error();}

        std::string&  mg_protocol::generate_body_vals(std::string& vl, const block& blk, num8 dvnum) {
            vl = "";
            parcel_const_iterator endit = blk.stop;
            endit++;
            parcel_ptr lastparcel;
            for (parcel_const_iterator it = blk.start; it!=endit; ++it) {
                if ((!lastparcel) || ((*lastparcel)!=(*(it->first))))
                    vl += generate_val(it->first->chanel(), it->first->addr());
                lastparcel = it->first;}
            generate_envelope(generate_body(vl), MG_FC_RD_VAL_R, dvnum, (proxyaddr | 0x80));
            return vl;}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error  mg_protocol::read_arr(const block& blk, num8 dvnum) {
            std::string req;
            std::string resp;
            generate_body_arrs(req, blk, dvnum);
            if (!error(request(req, resp, MG_RD_ARR_RESP))) {
                parse_envelope(resp, MG_FC_RD_ARR_A, dvnum);}
            return error();}

        std::string&  mg_protocol::generate_body_arrs(std::string& vl, const block& blk, num8 dvnum) {
            vl = "";
            num32 cnt = blk.stop->first->tp() - blk.start->first->tp();
            cnt = dvnci::abs<num32>(cnt);
            cnt = cnt + 1;
            vl = generate_arr(blk.start->first->chanel(), blk.start->first->addr(), blk.start->first->tp(), cnt);
            generate_envelope(generate_body(vl), MG_FC_RD_ARR_R, dvnum, (proxyaddr | 0x80));
            return vl;}


        //////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error  mg_protocol::read_arh(const block& blk, num8 dvnum) {
            std::string req;
            std::string resp;
            generate_body_arhs(req, blk, dvnum);
            if (!error( request(req, resp, MG_RD_ARH_RESP))) {
                parse_envelope(resp, MG_FC_RD_ARH_A, dvnum);}
            return error();}

        std::string&  mg_protocol::generate_body_arhs(std::string& vl, const block& blk, num8 dvnum) {
            vl = "";
            datetime strt, stp;
            blk.start->first->get_report_range(strt , stp);
            vl = generate_arh(blk.start->first->chanel(), blk.start->first->addr(), strt, stp);
            generate_envelope(generate_body(vl), MG_FC_RD_ARH_R, dvnum, (proxyaddr | 0x80));
            return vl;}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error mg_protocol::check_envelope(std::string& rsp,  const std::string& fnc, num8 srcaddr, num8 rcvaddr ) {
            std::string rgxsearch = ((srcaddr == -1) || (rcvaddr == -1)) ?
                    (MG_START_ENV + MG_FUNC_ENV) :
                    (MG_START_ENV + std::string((char*) &srcaddr, 1) + std::string((char*) &rcvaddr, 1)  + MG_FUNC_ENV) ;

            rgxsearch += (fnc == "") ? "." : fnc;
            rgxsearch += MG_START_BODY;
            std::string rgxmatch = rgxsearch + ".{0,}" + MG_END_BODY;
            rgxsearch = "(?<=" + rgxsearch + ").{0,}(?=" + MG_END_BODY + ")";
            if (boost::regex_match(rsp,  boost::regex(rgxmatch))) {
                boost::smatch rslt1;
                if (boost::regex_search(rsp,  rslt1,  boost::regex(rgxsearch))) {
                    if (rslt1.size() == 1) {
                        rsp = rslt1[0];
                        return error(0);}}}
            return error(ERROR_IO_PARSERESP);}

        std::string& mg_protocol::generate_envelope(std::string& vl, const std::string& fnc, num8 srcaddr , num8 rcvaddr) {
            vl = ((srcaddr == -1) || (rcvaddr == -1)) ?
                    MG_START_ENV + MG_FUNC_ENV + fnc + vl  :
                    MG_START_ENV + std::string((char*) &srcaddr, 1) + std::string((char*) &rcvaddr, 1)
                    + MG_FUNC_ENV + fnc + vl;
            return vl;}

        ///////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error  mg_protocol::write_val(parcel_ptr cmd, const std::string& vl, num8 dvnum) {
            std::string req;
            generate_write_body_val(req, vl, cmd->chanel(), cmd->addr(), dvnum);
            if (!error(ios->write(req))) {
                return error(0);}
            return 0;}


        ////////////////////////////////////////////////////////////////////////

        ns_error  mg_protocol::write_arr(parcel_ptr cmd, const std::string& vl, num8 dvnum) {
            std::string req;
            generate_write_body_arr(req, vl, cmd->chanel(), cmd->addr(), cmd->tp(), dvnum);
            if (!error(ios->write(req))) {
                return 0;}
            return 0;}

        //////////////////////////////////////////////////////////////////////////

        ns_error  mg_protocol::sync_time_device(num32 devnum){
                num8  dvnum = ((devnum >= 0) && (devnum <= MAX_NUM_MG)) ? static_cast<num8> (devnum) : -1;
                if (dvnum==proxyaddr) dvnum = -1;
                std::string req="";
                generate_write_body_val(req, lgk_time_to_str(now()), 0, TIME_SYNC_NM, dvnum );
                 if (!error(ios->write(req))) {
                      req="";
                      generate_write_body_val(req, lgk_date_to_str(now()), 0, DATE_SYNC_NM, dvnum );
                      if (!error(ios->write(req))) {;}}
            return error(0);}
    }}