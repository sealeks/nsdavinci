/* 
 * File:   blockgenerator.cpp
 * Author: Serg
 * 
 * Created on 19 Октябрь 2010 г., 16:19
 */

#include <kernel/driver_blockgenerator.h>

namespace dvnci {
    namespace driver {

        basis_block_item::basis_block_item(std::string vl , tagtype tgtp , const metalink& mlnk) :
        iscorrect_(false), devnum_(0), type_(tgtp), chanel_(0), addr_(0), tp_(0), specificator_(0), size_(0),
        protocol_(0), tgtype_(tgtp), error_(0), isvalue_(false), value_(0) {
            chanel_ = mlnk.chanaltype();
            devnum_ = mlnk.devicenum();
            protocol_ = mlnk.protocol();};

        bool  basis_block_item::operator==(const basis_block_item& rs) const  {
            if (devnum() != rs.devnum()) return false;
            if (type() != rs.type()) return false;
            if (chanel() != rs.chanel()) return false;
            if (addr() != rs.addr()) return false;
            if (tp() != rs.tp()) return false;
            if (size() != rs.size()) return false;
            return true;};

        bool  basis_block_item::operator<(const basis_block_item& rs) const {
            if (devnum() != rs.devnum()) return (devnum() < rs.devnum());
            if (type() != rs.type()) return (type() < rs.type());
            if (chanel() != rs.chanel()) return (chanel() < rs.chanel());
            if (addr() != rs.addr()) return (addr() < rs.addr());
            if (tp() != rs.tp()) return (tp() < rs.tp());
            if (size() != rs.size()) return (size() < rs.size());
            return false;}
        
        
       template<> 
       void basis_block_item::value_cast<double>(double val) {
              value_=short_value(val);
              isvalue_ = true;
              error(0);} 
       
       template<> 
       void basis_block_item::value_cast<float>(float val) {
              value_=short_value(val);
              isvalue_ = true;
              error(0);} 


        std::string basis_block_item::to_str() {
            return string_fromnum64_and_type(value_.value64(), value_.type() );};




        void  basis_block_item::value_event(const datetime& dt, double vl) {
            eventvalue_.reset();
            isvalue_ = true;
            eventvalue_ = datetime_val_ptr( new dt_val_pair(dt, vl));
            error_ = 0;}

        dt_val_pair  basis_block_item::value_event() const {
            if (isvalue_) {
                if (eventvalue_) {
                    dt_val_pair tmp = *eventvalue_;
                    isvalue_ = false;
                    eventvalue_.reset();
                    return tmp;}}
            isvalue_ = false;
            return dt_val_pair(nill_time, NULL_DOUBLE);}

        void  basis_block_item::set_report_val(const dt_val_map& dt) {
            reportvalue_.reset();
            isvalue_ = true;
            reportvalue_ = dt_val_map_ptr( new dt_val_map());
            *reportvalue_ = dt;
            error_ = 0;}

        bool  basis_block_item::get_report_val(dt_val_map& dt) {
            dt.clear();
            if (isvalue_) {
                if (reportvalue_) {
                    dt = (*reportvalue_);
                    isvalue_ = false;
                    reportvalue_.reset();
                    return true;}}
            isvalue_ = false;
            return false;}

        void basis_block_item::set_report_range(datetime start, datetime stop) {
            reportrange_.reset();
            reportrange_ = datetime_pair_ptr( new datetime_pair(start, stop));}

        bool basis_block_item::get_report_range(datetime& start, datetime& stop) {
            if (reportrange_) {
                start = reportrange_->first;
                stop = reportrange_->second;
                return true;}
            return false;}

        size_t  calculate_blocksize(parcel_ptr msblk, parcel_ptr lsblk) {
            return ((*msblk)-(*lsblk)) == MAXDISTANSE ? MAXDISTANSE : std::max<size_t > (((*msblk)-(*lsblk)) + msblk->size(), lsblk->size());}

        std::ostream & operator<< (std::ostream& os, const block& ns) {
            os << " parsels_line [ ";
            os << "  " << *(ns.start->first) << " , "   << *(ns.stop->first) ;
            return os << " ] ";}

        parcels_vect &  operator<<  (parcels_vect& vct, const block& blk) {
            vct.clear();
            if (blk.start == blk.stop) {
                vct.push_back(blk.start->first);
                return vct;}
            else {
                for (parcel_iterator it = blk.start; it != blk.stop; ++it) {
                    vct.push_back(it->first);}}
            vct.push_back(blk.stop->first);
            return vct;}

        std::ostream & operator<< (std::ostream& os, const parcels_vect& ns) {
            os << " parsels_set [ ";
            for (parcels_vect::const_iterator it = ns.begin(); it != ns.end(); ++it) {
                if (it==ns.begin()) os << " { " << *(*it) << " } -";
                else {
                   if ((it+1)==ns.end()) os << " { " << *(*it) << " }";}}
            return os << " ] ";}


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс генератора блока опроса*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        bool abstract_block_generator::next(block& blk) {
            if (needgenerate) {
                currentblockiteator = begin();}
            if (blocks.empty()) return false;
            if (currentblockiteator == end()) currentblockiteator = begin();
            blk = (*currentblockiteator);
            parcel_iterator bgn = blk.start;
            parcel_iterator ed = blk.stop;
            if (check_block_active(blk, bgn, ed)) {
                if (bgn != blk.start) blk.start = bgn;
                if (ed != blk.stop) blk.stop = ed;
                return true;}
            currentblockiteator++;
            return false;}

        bool abstract_block_generator::command(commands_vect& cmdvect) {
            command_vector cmds;
            cmdvect.clear();
            intf->select_commands(cmds, executr->groupset());
            //DEBUG_STR_VAL_DVNCI(bkgrtr, cmds.size())
            if (!cmds.empty()) {
                for (command_vector::const_iterator it = cmds.begin(); it != cmds.end(); ++it) {
                    tags_iterator itfnd = bmap.right.find(it->tagid());
                    if (itfnd != bmap.right.end()) {
                        itfnd->second->value(short_value(it->value_set<num64 > (), it->type()));
                        cmdvect.push_back(itfnd->second);}}
                return (!cmdvect.empty());}
            return false;}

        void abstract_block_generator::read_ok(block& blk) {
            if (currentblockiteator != end()) currentblockiteator->set_ok();
            currentblockiteator++;
            parcel_iterator endit = blk.stop;
            endit++;
            num64 tmpval = 0;
            for (parcel_iterator it = blk.start; it != endit; ++it) {
                if (it->first->isvalue()) {
                    if (it->first->error()) {
                        executr->error(it->second, it->first->error());}
                    else {
                        if (IN_REPORTSET(it->first->tgtype())) {
                            dt_val_map tmprepmp;
                            if (it->first->get_report_val(tmprepmp))
                                executr->write_val_report(it->second, tmprepmp);}
                        else {
                            if (IN_EVENTSET(it->first->tgtype())) {
                                if (it->first->isvalue())
                                    executr->write_val_event(it->second,it->first->value_event());}
                            else {
                                if (it->first->error()) {
                                    executr->error(it->second, it->first->error());}
                                else{
                                    if (!it->first->error()) {
                                         executr->write_val(it->second, it->first->value());}
                                    else{
                                         executr->error(it->second, it->first->error() ? it->first->error(): ERROR_IO_NO_DATA);
									}}}}}} 
				else{
					if (it->first->error()) {
						executr->error(it->second, it->first->error());}}}}

        bool abstract_block_generator::check_parcel_active(parcel_iterator& prsl) {
            if (IN_REPORTSET(intf->type(prsl->second))) {
                if (executr->requested(prsl->second)) {
                    datetime tmpstart = intf->time_log(prsl->second);
                    datetime tmpstop = tmpstart;
                    increporttime(tmpstop, intf->type(prsl->second), archblocksize);
                    prsl->first->set_report_range(tmpstart, tmpstop);
                    return true;}
                else return false;}
            return executr->requested(prsl->second);}

        bool abstract_block_generator::check_block_active(block& blk, parcel_iterator& bgn, parcel_iterator& ed) {
            if (!intf) return false;
            executr->push_all_report();
            parcel_iterator stpit = blk.stop;
            if (blk.start == stpit) {
                return check_parcel_active(blk.start);}
            ++stpit;
            for (parcel_iterator it = blk.start; it != stpit; ++it) {
                if (!check_parcel_active(it)) ++bgn;
                else {
                    if (it != ed) {
                        for (it = ed; it != bgn; --it) {
                            if (!check_parcel_active(it)) ed--;
							else return true;}}
                    return true;}}
            return false;}



}}

