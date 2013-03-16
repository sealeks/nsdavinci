/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */
#include <iso/iso8327.h>
#include <string>


namespace boost {
    namespace itu {
        namespace x225impl {

            std::size_t from_triple_size(const raw_type& val, std::size_t& it) {
                if ((val.empty()) || (val[0] == '\xFF' && val.size() < 3))
                    return 0;
                if (val[0] == '\xFF') {
                    uint16_t sz;
                    if (raw_to_inttype(raw_type(val.begin() + 1, val.end()), sz)) {
                        sz = endiancnv_copy(sz);
                        it += 2;
                        return static_cast<std::size_t> (sz);
                    }
                }
                else {
                    uint8_t sz;
                    if (raw_to_inttype(val, sz)) {
                        it += 1;
                        return static_cast<std::size_t> (sz);
                    }
                }
                return triple_npos;
            }


            //  spdudata 

            void spdudata::setPGI(varid_type cod1, varid_type cod2, const raw_type& val) {
                spdudata_type::iterator it =value_->find(cod1);
                if (it == value_->end()) {
                    pgi_type pgi;
                    pgi.insert(pi_type(cod2, val));
                    value_->insert(pgis_type(cod1, pgi));
                }
                else
                    it->second.insert(pi_type(cod2, val));
            }

            void spdudata::setPGI(varid_type cod1, varid_type cod2, int8_t val) {

                setPGI(cod1, cod2, inttype_to_raw(val));
            }

            void spdudata::setPGI(varid_type cod1, varid_type cod2, uint8_t val) {

                setPGI(cod1, cod2, inttype_to_raw(val));
            }

            void spdudata::setPGI(varid_type cod1, varid_type cod2, int16_t val) {

                setPGI(cod1, cod2, inttype_to_raw(endiancnv_copy(val)));
            }

            void spdudata::setPGI(varid_type cod1, varid_type cod2, uint16_t val) {

                setPGI(cod1, cod2, inttype_to_raw(endiancnv_copy(val)));
            }

            void spdudata::setPI(varid_type cod, const raw_type& val) {

                setPGI(0, cod, val);
            }

            void spdudata::setPI(varid_type cod, int8_t val) {

                setPI(cod, inttype_to_raw(val));
            }

            void spdudata::setPI(varid_type cod, uint8_t val) {

                setPI(cod, inttype_to_raw(val));
            }

            void spdudata::setPI(varid_type cod, int16_t val) {

                setPI(cod, inttype_to_raw(endiancnv_copy(val)));
            }

            void spdudata::setPI(varid_type cod, uint16_t val) {

                setPI(cod, inttype_to_raw(endiancnv_copy(val)));
            }

            const raw_type& spdudata::getPGI(varid_type cod1, varid_type cod2) const {
                spdudata_type::const_iterator it = value_->find(cod1);
                if (it == value_->end())
                    return null_val;
                pgi_type::const_iterator itpi = it->second. find(cod2);
                return (itpi != it->second.end()) ? itpi->second : null_val;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, int8_t& val, int8_t def) const {
                const raw_type& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    val = tmp.size() ? static_cast<int8_t> (tmp[0]) : def;
                    return true;
                }
                val = def;

                return false;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, uint8_t& val, uint8_t def) const {
                const raw_type& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    val = tmp.size() ? static_cast<varid_type> (tmp[0]) : def;
                    return true;
                }
                val = def;

                return false;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, int16_t& val, int16_t def) const {
                const raw_type& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    if (raw_to_inttype(tmp, val))
                        val = endiancnv_copy(val);
                    else
                        val = def;
                    return true;
                }
                val = def;
                return false;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, uint16_t& val, uint16_t def) const {
                const raw_type& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    if (raw_to_inttype(tmp, val))
                        val = endiancnv_copy(val);
                    else
                        val = def;
                    return true;
                }
                val = def;

                return false;
            }

            const raw_type& spdudata::getPI(varid_type cod) const {

                return getPGI(0, cod);
            }

            bool spdudata::getPI(varid_type cod, int8_t& val, int8_t def) const {

                return getPGI(0, cod, val, def);
            }

            bool spdudata::getPI(varid_type cod, uint8_t& val, uint8_t def) const {

                return getPGI(0, cod, val, def);
            }

            bool spdudata::getPI(varid_type cod, int16_t& val, int16_t def) const {

                return getPGI(0, cod, val, def);
            }

            bool spdudata::getPI(varid_type cod, uint16_t& val, uint16_t def) const {

                return getPGI(0, cod, val, def);
            }

            bool spdudata::existPGI(varid_type cod1, varid_type cod2) const {
                spdudata_type::const_iterator it = value_->find(cod1);
                if (it == value_->end())
                    return false;
                pgi_type::const_iterator itpi = it->second.find(cod2);

                return (itpi != it->second.end());
            }

            bool spdudata::existPI(varid_type cod) const {

                return existPGI(0, cod);
            }

            bool spdudata::nullPGI(varid_type cod1, varid_type cod2) const {
                spdudata_type::const_iterator it = value_->find(cod1);
                if (it == value_->end())
                    return false;
                pgi_type::const_iterator itpi = it->second.find(cod2);

                return (itpi != it->second.end() ? (!itpi->second.empty()) : false);
            }

            bool spdudata::nullPI(varid_type cod) const {

                return nullPGI(0, cod);
            }

            const_sequence_ptr spdudata::sequence(isocoder_ptr coder) const {
                raw_type tmp;
                spdudata_type::const_iterator strtit = value_->end();
                for (spdudata_type::const_iterator it = value_->begin(); it != value_->end(); ++it) {
                    if ((!it->first && it == value_->begin()))
                        strtit = it;
                    else {
                        raw_type tmppgi;
                        for (pgi_type::const_iterator itpgi = it->second.begin(); itpgi != it->second.end(); ++itpgi) {
                            raw_back_insert(tmppgi, inttype_to_raw(itpgi->first));
                            raw_back_insert(tmppgi, to_triple_size(itpgi->second.size()));
                            raw_back_insert(tmppgi, itpgi->second);
                        }
                        raw_back_insert(tmp, inttype_to_raw(it->first));
                        raw_back_insert(tmp, to_triple_size(tmppgi.size()));
                        raw_back_insert(tmp, tmppgi);
                    }
                }
                if (strtit != value_->end()) {
                    raw_type tmppi;
                    for (pgi_type::const_iterator itpgi = strtit->second.begin(); itpgi != strtit->second.end(); ++itpgi) {
                        if ((itpgi->first != PGI_USERDATA) && (itpgi->first != PGI_EXUSERDATA)) {
                            raw_back_insert(tmppi, inttype_to_raw(itpgi->first));
                            raw_back_insert(tmppi, to_triple_size(itpgi->second.size()));
                            raw_back_insert(tmppi, itpgi->second);
                        }
                    }
                    raw_back_insert(tmp, tmppi);
                }
                if (coder->out()->size()) {
                    if ((type_ == CN_SPDU_ID) && (coder->out()->size() > SIMPLE_USERDATA_LIMIT)) {
                        raw_back_insert(tmp, inttype_to_raw(PGI_EXUSERDATA));
                        raw_back_insert(tmp, to_triple_size(coder->out()->size()));
                    }
                    else {
                        raw_back_insert(tmp, inttype_to_raw(PGI_USERDATA));
                        raw_back_insert(tmp, to_triple_size(coder->out()->size()));
                    }
                }
                coder->out()->add(raw_type(tmp.begin(), tmp.end()), coder->out()->buffers().begin());
                raw_type header(inttype_to_raw(type_));
                raw_back_insert(header, to_triple_size(coder->out()->size()));
                coder->out()->add(raw_type(header.begin(), header.end()), coder->out()->buffers().begin());
                return coder->out()->buffers_ptr();
            }

            bool spdudata::parse() {
                raw_type::size_type it = 0;
                if (seq_.size() < 2)
                    return error(true);
                type_ = static_cast<spdu_type> (seq_[it++]);
                std::size_t sz = from_triple_size(raw_type(seq_.begin() + 1, seq_.end()), it);
                if (sz == triple_npos)
                    return error(true);
                if (sz == 0)
                    return false;
                if (sz + it > seq_.size())
                    return false;
                return parse_vars(raw_type(seq_.begin()+(++it), seq_.end()));
            }

            bool spdudata::parse_vars(const raw_type& vl) {
                raw_type::size_type it = 0;
                do {
                    if (vl.size() < 2)
                        return error(true);
                    varid_type vr = static_cast<varid_type> (vl[it++]);
                    std::size_t sz = from_triple_size(raw_type(vl.begin() + it, vl.end()), it);
                    if (sz == triple_npos)
                        return error(true);
                    if (sz + it > vl.size())
                        return false;
                    switch (vr) {
                        case PGI_CONN_ID:
                        case PGI_CONN_ACC:
                        case PGI_LINK_INF:    
                        {
                            if (!parse_pgi(vr, raw_type(vl.begin() + it, vl.begin() + it + sz))) return error(true);
                            else break;
                        }
                        default:
                        {
                            setPI(vr, raw_type(vl.begin() + it, vl.begin() + it + sz));
                            break;
                        }
                    }
                    it += sz;
                }
                while (it < vl.size());
                return true;
            }

            bool spdudata::parse_pgi(varid_type tp, const raw_type& vl) {
                raw_type::size_type it = 0;
                do {
                    if (vl.size() < 2)
                        return error(true);
                    varid_type vr = static_cast<varid_type> (vl[it++]);
                    std::size_t sz = from_triple_size(raw_type(vl.begin() + it, vl.end()), it);
                    if (sz == triple_npos)
                        return error(true);
                    if (sz + it > vl.size())
                        return false;
                    setPGI(tp, vr, raw_type(vl.begin() + it, vl.begin() + it + sz));
                    it += sz;
                }
                while (it < vl.size());
                return true;
            }




            //  protocol_option

            protocol_options::protocol_options(const raw_type& called, const raw_type& calling)  : vars_( new spdudata()) {
                vars_->setPI(PI_CALLING, calling);
                vars_->setPI(PI_CALLED, called);
                vars_->setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                vars_->setPGI(PGI_CONN_ACC, PI_VERSION, WORK_PROT_VERSION);
                vars_->setPI(PI_SES_USERREQ, FU_WORK);
            }

            const raw_type& protocol_options::ssap_calling() const {
                return vars_->getPI(PI_CALLING);
            }

            void protocol_options::ssap_calling(const raw_type& val) {
                if (!val.empty())
                    vars_->setPI(PI_CALLING, val);
            }

            const raw_type& protocol_options::ssap_called() const {
                return vars_->getPI(PI_CALLED);
            }

            void protocol_options::ssap_called(const raw_type& val) {
                if (!val.empty())
                    vars_->setPI(PI_CALLED, val);
            }

            const raw_type& protocol_options::data() const {
                return vars_->existPI(PGI_EXUSERDATA) ? vars_->getPI(PGI_EXUSERDATA) : vars_->getPI(PGI_USERDATA);
            }      
            
            
           octet_type protocol_options::accept_version() const{
                octet_type tmp;
                return vars_->getPGI(PGI_CONN_ACC, PI_VERSION,tmp) ?
                    ( (tmp & VERSION2) ? 
                        VERSION2 : VERSION1)  : VERSION1;
            }                  
            
            void protocol_options::accept_version(octet_type vl) {
                vars_->setPGI( PGI_CONN_ACC, PI_VERSION , (vl > VERSION1) ?
                    VERSION2 : VERSION2);
            } 
            
            octet_type protocol_options::reject_version() const{
                octet_type tmp;
                return vars_->getPI( PI_VERSION,tmp) ? 
                    ( (tmp & VERSION2) ? 
                        VERSION2 : VERSION1)  : VERSION1;
            }              
                  
            void protocol_options::reject_version(octet_type vl) {
                return vars_->setPI(  PI_VERSION , (vl > VERSION1) ?
                    VERSION2 : VERSION2);
            }

            int16_t protocol_options::user_requirement() const {
                int16_t tmp;
                return vars_->getPI( PI_SES_USERREQ ,tmp) ? tmp : FU_DEFAULT; // *ref X225 8.3.1.16
            }

            void protocol_options::user_requirement(int16_t vl) {
                return vars_->setPI(  PI_SES_USERREQ,  vl );
            }            
            
           bool protocol_options::extendedSPDU() const{
                octet_type tmp;
                return vars_->getPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION,tmp) ?
                    tmp   : false; // *ref X225 8.3.1.7
            }                  
            
            void protocol_options::extendedSPDU(bool vl) {
                vars_->setPGI( PGI_CONN_ACC, PI_PROTOCOL_OPTION , vl ? EXTENDED_SPDU : NOEXTENDED_SPDU );
            }    
            
           bool protocol_options::endSPDU() const{
                octet_type tmp;
                return vars_->getPI(PI_ENCLOSURE, tmp) ?
                    (tmp & 2)  : true; // *ref X225 8.3.3.3
            }      
           
           bool protocol_options::beginSPDU() const{
                octet_type tmp;
                return vars_->getPI(PI_ENCLOSURE, tmp) ?
                    (tmp & 1)  : true; // *ref X225 8.3.3.3
            }               
            
            void protocol_options::endSPDU(bool end, bool beg) {
                if ( !end ||  !beg)                  
                vars_->setPI( PI_ENCLOSURE, static_cast<octet_type>(( end ?  2 : 0) | ( beg ? 1 : 0 ) )); // *ref X225 8.3.3.19
            }   
            
           bool protocol_options::overflow() const{
                octet_type tmp;
                return vars_->getPI(PI_DATAOVERFLOW ,tmp) ?
                    tmp   : false; // *ref X225 8.3.1.19
            }                  
            
            void protocol_options::overflow(bool vl) {
                vars_->setPI( PI_DATAOVERFLOW , static_cast<octet_type>(vl ? 1 : 0));
            }            
            

            octet_type protocol_options::refuse_reason() const {
                const raw_type& tmp = vars_->getPI(PI_REASON);
                return tmp.empty() ? DR_REASON_NODEF : tmp[0];
            }

            void protocol_options::refuse_reason(octet_type rsn, const raw_type& val) {
                if (val.empty())
                   vars_->setPI(PI_REASON, rsn);
                else{
                   raw_type tmp(1,rsn);
                   tmp.insert(tmp.end(), val.begin(), val.end());
                   vars_->setPI(PI_REASON, tmp);
                }                   
            }
            
            uint16_t protocol_options::maxTPDU_self() const {
                const raw_type& tmp = vars_->getPGI(PGI_CONN_ACC, PI_TSDUMAX);
                if (tmp.size()==4){
                    return endiancnv_copy<uint16_t>(raw_type(tmp.begin(), tmp.begin()+2));
                }
                return 0;
            }

            uint16_t protocol_options::maxTPDU_dist() const {
                const raw_type& tmp = vars_->getPGI(PGI_CONN_ACC, PI_TSDUMAX);
                if (tmp.size()==4){
                    return endiancnv_copy<uint16_t>(raw_type(tmp.begin()+2, tmp.end()));
                }
                return 0;
            }            

            void protocol_options::maxTPDU(uint16_t self, uint16_t dist) {
                if (self || dist){
                    raw_type tmpself(inttype_to_raw(endiancnv_copy(self)));
                    raw_type tmpdist(inttype_to_raw(endiancnv_copy(dist)));
                    tmpself.insert(tmpself.begin(), tmpdist.begin(), tmpdist.end());
                    vars_->setPGI(PGI_CONN_ACC, PI_TSDUMAX , tmpself);                   
                }
            }

            /////////////////////

            bool negotiate_x225impl_option(protocol_options& self, const protocol_options& dist) {
                
                self = protocol_options(self.ssap_calling(), dist.ssap_calling());
                
                //std::cout << "negotiate session : UREQ=" << ((int) dist.user_requirement()) << " PROTOP=" << ((int) dist.extendedSPDU()) << " VER=" << ((int) dist.accept_version()) << std::endl;
                
                if (!(dist.user_requirement() & FU_WORK) || dist.extendedSPDU()){
                    self.refuse_reason(DR_REASON_NEGOT);
                    self.user_requirement(FU_WORK);    
                    self.extendedSPDU(false);                        
                    return false;
                }  
                
#ifndef CHECK_ISO_SELECTOR        
                if (!self.ssap_called().empty() && self.ssap_called() != dist.ssap_called()) {
                    self.refuse_reason(DR_REASON_ADDRESS);
                    return false;
                }
#endif                      
                self.accept_version(dist.accept_version());
                self.user_requirement(FU_WORK);         
                self.extendedSPDU(false);                  
                return true;
            }

            const_sequence_ptr generate_header_CN(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(CN_SPDU_ID);
                tmp.setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                tmp.setPGI(PGI_CONN_ACC, PI_VERSION, WORK_PROT_VERSION);
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                tmp.setPI(PI_CALLING, opt.ssap_calling());
                tmp.setPI(PI_CALLED, opt.ssap_called());       
                return tmp.sequence(data);
            }

            const_sequence_ptr generate_header_AC(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(AC_SPDU_ID);
                tmp.setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                tmp.setPGI(PGI_CONN_ACC, WORK_PROT_VERSION, opt.accept_version());
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                tmp.setPI(PI_CALLING, opt.ssap_calling());
                tmp.setPI(PI_CALLED, opt.ssap_called());
                return tmp.sequence(data);
            }
            

            const_sequence_ptr generate_header_RF(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(RF_SPDU_ID);
                data->out()->clear(); // no user data *ref X225 Tab 15
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                tmp.setPI(PI_VERSION, opt.reject_version());
                tmp.setPI(PI_REASON, opt.refuse_reason());
                return tmp.sequence(data);
            }            
            

            const_sequence_ptr generate_header_FN(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(FN_SPDU_ID);
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                return tmp.sequence(data);
            }            

            const_sequence_ptr generate_header_DN(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(DN_SPDU_ID);
                return tmp.sequence(data);
            }

            const_sequence_ptr generate_header_AB(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(AB_SPDU_ID);
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                return tmp.sequence(data);
            }

            const_sequence_ptr generate_header_AA(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(AA_SPDU_ID);
                data->out()->clear(); // no user data *ref X225  8.3.10.2             
                return tmp.sequence(data);
            }

            const_sequence_ptr generate_header_NF(const protocol_options& opt, isocoder_ptr data) {
                spdudata tmp(NF_SPDU_ID);
                return tmp.sequence(data);
            }


            //receive_seq

            receive_seq::receive_seq(const mutable_buffer& buff) :
            state_(waittype),
            size_(0),
            estimatesize_(SI_WITH_LI),
            datasize_(0),
            type_(0),
            first_in_seq_(false),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            type_data(new data_type(SI_WITH_LI)),
            type_buff_(boost::asio::buffer(*type_data)),
            header_buff_(),
            userbuff_(buff) {
            }

            receive_seq::receive_seq() :
            state_(waittype),
            size_(0),
            estimatesize_(SI_WITH_LI),
            datasize_(0),
            type_(0),
            first_in_seq_(false),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            type_data(new data_type(SI_WITH_LI)),
            type_buff_(boost::asio::buffer(*type_data)),
            header_buff_(),
            userbuff_() {

            }

            mutable_buffer receive_seq::buffer() {
                switch (state_) {
                    case waittype: return type_buff_ + size_;
                    case waitsize: return type_buff_ + size_;
                    case waitheader: return header_buff_ + size_;
                    case waitdata: return boost::asio::buffer(userbuff_ + datasize_);
                    default: return mutable_buffer();
                }
                return mutable_buffer();
            }

            void receive_seq::put(std::size_t sz) {
                if (!sz) return;
                size_ += sz;
                if ((size_ + sz) >= estimatesize_) {
                    switch (state_) {
                        case waittype:
                        {
                            check_type();
                            return;
                        }
                        case waitsize:
                        {
                            check_size();
                            return;
                        }
                        case waitheader:
                        {
                            check_header();
                            return;
                        }
                        case waitdata:
                        {
                            break;
                        }
                        default:
                        {
                            errcode(ER_BEDSEQ);
                            return;
                        }
                    }

                }
                if (state_ == waitdata) {
                    datasize_ += sz;
                    state(complete);
                }
            }

            receive_seq::operation_state receive_seq::state(operation_state val) {
                if (val != state_) {
                    size_ = 0;
                }
                if (val == error) {
                    estimatesize_ = 0;
                }
                return state_ = val;
            }

            error_code receive_seq::check_type() {
                mutable_buffer buff_ = type_buff_;
                spdu_type tp = *boost::asio::buffer_cast<spdu_type*>(buff_);
                first_in_seq_ = !type_ && !first_in_seq_;

                switch (tp) {
                    case GT_SPDU_ID:
                    {
                        type_ = tp;
                        break;
                    }
                    case PT_SPDU_ID:
                    {
                        type_ = tp;
                        break;
                    }
                    default:
                    {
                        type_ = *boost::asio::buffer_cast<spdu_type*>(buff_);
                        first_in_seq_ = false;
                    }
                }
                std::size_t li = static_cast<std::size_t> (*boost::asio::buffer_cast<unsigned char*>(buff_ + 1));

                if (li == '\xFF') {
                    estimatesize_ = HDR_LI;
                    state(waitsize);
                    return error_code();
                }

                if (!li) {
                    if (first_in_seq_) {
                        estimatesize_ = HDR_LI;
                        size_ = 0;
                        return error_code();
                    }
                    else {
                        state(tp == DT_SPDU_ID ? waitdata : complete);
                        return error_code();
                    }
                }
                else {
                    state(waitheader);
                    header_data = data_type_ptr(new data_type(li));
                    header_buff_ = mutable_buffer(boost::asio::buffer(*header_data));
                    estimatesize_ = li;
                    return error_code();
                }
                return errcode(ER_PROTOCOL);
            }

            error_code receive_seq::check_size() {
                mutable_buffer buff_ = type_buff_;
                uint16_t li = 0;
                raw_to_inttype(buffer_to_raw(buff_, 0, 2), li);
                li = endiancnv_copy(li);
                state(waitheader);
                header_data = data_type_ptr(new data_type(li));
                estimatesize_ = li;
                return error_code();
            }

            error_code receive_seq::check_header() {
                options_ = protocol_options(header_buff_);
                state(first_in_seq_ ? waittype : complete);
                return error_code();
            }

            void receive_seq::reject_reason(octet_type val) {
                errcode_ = error_code();
                reject_reason_ = val;
            }

            error_code receive_seq::errcode(const error_code& err) {
                if (!errcode_ && err)
                    errcode_ = err;
                if (err)
                    state_ = error;
                return errcode_;
            }

        }
    }
}
