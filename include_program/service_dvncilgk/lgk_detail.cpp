/* 
 * File:   modbus_detail.cpp
 * Author: Serg
 * 
 * Created on 19 ??????? 2010 ?., 17:55
 */

#include "lgk_detail.h"

namespace dvnci {
    namespace driver {

        bool lgk_req_parcel::parse(std::string vl) {

            /* [chNN:]nKK[:iLL]

              NN chanal numb , 0 or blank  is system
              KK parameter number , no blank
              LL array number for  arrays parameter, blank  isnt arrays parameter

              main templ = (CH[0-9]{1,3}:)?N[0-9]{1,3}(:I[0-9]{1,3})?

             *  */

            upper_and_trim(vl);
            boost::regex regexbind("(CH[0-9]{1,3}:)?N[0-9]{1,3}(:I[0-9]{1,3})?");
            boost::smatch rslt;
            if (boost::regex_match(vl,  rslt, regexbind)) {
                parcelkind tp = 0;
                num32      ch = 0;
                num32      nm = 0;
                num32      arrnm = 0;
                if (conformaddr(vl, tp, ch, nm, arrnm)) {
                    kind_ = tp;
                    chanel_ = ch;
                    addr_ = nm;
                    indx_ = arrnm;
                    return true;}}
            error(ERROR_BINDING);
            return false;}

        bool lgk_req_parcel::conformaddr(const std::string& vl, parcelkind& tp, num32& ch, num32& nm, num32& arrnm) {
            size_= 1;
            boost::smatch rslt1;
            boost::regex rgx1("(?<=:I)[0-9]{1,3}");
            tp = LGKA_TYPEITEM_SMPL;
            if (boost::regex_search(vl,  rslt1, rgx1)) {
                if (rslt1.size()==1)
                    if (!str_to<num32>(rslt1[0], arrnm)) return false;
                tp = LGKA_TYPEITEM_ARRAY;}

            ch = 0;
            boost::smatch rslt2;
            boost::regex rgx2("(?<=CH)[0-9]{1,3}");
            if (boost::regex_search(vl,  rslt2, rgx2)) {
                if (rslt2.size()==1)
                    if (!str_to<num32>(rslt2[0], ch)) return false;}

            boost::smatch rslt3;
            boost::regex rgx3("(?<=N)[0-9]{1,3}");
            if (boost::regex_search(vl,  rslt3, rgx3)) {
                if (rslt3.size()==1)
                    if (!str_to<num32>(rslt3[0], nm)) return false;}

            bool isreport = IN_REPORTSET(type());
            if (isreport) {
                if (tp==LGKA_TYPEITEM_ARRAY) return false;
                tp = LGKA_TYPEITEM_ARCHIVE;}

            return true;}

        ////////////////////////////////////////////////////////////////////////

        void lgk_block_model::dev_block::add(parcelkind tp, const block& val) {

            switch (tp) {
                case LGKA_TYPEITEM_SMPL:{
                    simpl.push_back(val);
                    smpl_fl = false;
                    break;}
                case LGKA_TYPEITEM_ARCHIVE:{
                    arch.push_back(val);
                    arch_fl = false;
                    break;}
                case LGKA_TYPEITEM_ARRAY:{
                    arr.push_back(val);
                    arr_fl = false;
                    break;}}}

        bool lgk_block_model::dev_block::next(block& vl, bool& lpready) {
            switch (curtype()) {
                case LGKA_TYPEITEM_SMPL:{
                    return next_templ(vl, smpl_fl, lpready, simpl, smpl_it);}
                case LGKA_TYPEITEM_ARCHIVE:{
                    return next_templ(vl, arch_fl, lpready, arch, arch_it);}
                case LGKA_TYPEITEM_ARRAY:{
                    return next_templ(vl, arr_fl, lpready, arr, arr_it);}
                default:{
                    return false;}}
            return false;}

        bool lgk_block_model::dev_block::next_templ(block& vl, bool& fl, bool& lpready, block_vector& vct, block_vector::const_iterator& it) {
            if (vct.begin()==vct.end()) return false;
            if (it==vct.end()) {
                fl = true;
                it = vct.begin();}
            vl = (*it);
            ++it;
            if (!loop_is_ready())
                lpready = true;
            return true;};

        parcelkind   lgk_block_model::dev_block::curtype(parcelkind lev) {
            if (lev<3) {
                switch (curtype_) {
                    case LGKA_TYPEITEM_SMPL:{
                        if (simpl.empty()) {
                            curtype_++;
                            return curtype(++lev);}
                        else  return curtype_++;};
                    case LGKA_TYPEITEM_ARCHIVE:{
                        if (arch.empty())  {
                            curtype_++;
                            return  curtype(++lev);}
                        else  return curtype_++;};
                    case LGKA_TYPEITEM_ARRAY:{
                        if (arr.empty())  {
                            curtype_ = LGKA_TYPEITEM_SMPL;
                            return curtype(++lev);}
                        else {
                            curtype_ = LGKA_TYPEITEM_SMPL;
                            return LGKA_TYPEITEM_ARRAY;}}}}
            return -1;}

        void lgk_block_model::generate_impl() {
            parcel_iterator its = bmap.left.begin();
            if (its==bmap.left.end()) {
                needgenerate = false;
                return;}
            num32_dev_block_map transitmap;
            block blkit(its, its, intf->group(its->second),
                    intf->groups()->indicateto(intf->group(its->second)),
                    intf->groups()->trycount(intf->group(its->second)));
            its++;
            if (its==bmap.left.end()) {
                filltransitmap(transitmap, blkit);}
            else {
		size_t counter = 1;
                for (parcel_iterator it = its; it!=bmap.left.end(); ++it) {
                    if ((it->first->devnum()!=its->first->devnum()) ||
                            (it->first->kind()!=its->first->kind()) ||
                            (it->first->kind()==LGKA_TYPEITEM_ARCHIVE) ||
                            ((it->first->kind()==LGKA_TYPEITEM_ARRAY) && ((*(it->first))-(*(its->first))>blocksize)) ||
                            (counter>blocksize) ||
                            (it->first->protocol()==LGKA_PROT_MEC)) {
                        counter = 1;
                        filltransitmap(transitmap, blkit);
                        blkit.groupid(intf->group(it->second));
                        blkit.timout(intf->groups()->indicateto(blkit.groupid()));
                        blkit.trycount(intf->groups()->trycount(blkit.groupid()));
                        blkit.begin() = it;
                        blkit.end() = it;
                        its = it;}
                    else {
                        counter++;
                        blkit.end() = it;}}
                filltransitmap(transitmap, blkit);}
            generate_by_transitmap(transitmap);
            needgenerate = false;}

        void lgk_block_model::filltransitmap(num32_dev_block_map& mp, const block& blk) {
            num32_dev_block_iterator it = mp.find(blk.begin()->first->devnum());
            if (it==mp.end()) {
                dev_block tmp;
                tmp.add(blk.begin()->first->kind(), blk);
                mp.insert(num32_dev_block_pair(blk.begin()->first->devnum(), tmp));}
            else {
                it->second.add(blk.begin()->first->kind(), blk);}}

        void lgk_block_model::generate_by_transitmap(num32_dev_block_map& mp) {
            bool needfl = true;
            block blktmp;
            for (num32_dev_block_iterator it = mp.begin(); it!=mp.end(); ++it) {
                it->second.def_iterator();}
            while (needfl) {
                needfl = false;
                for (num32_dev_block_iterator it = mp.begin(); it!=mp.end(); ++it) {
                    if (it->second.next(blktmp, needfl)) blocks.push_back(blktmp);}}}}}

