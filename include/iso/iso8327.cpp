//  Copyright 2013 Alexeev Sergey sealeks@mail.ru

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#include <iso/iso8327.h>


namespace boost {
    namespace itu {
        namespace x225impl {

            std::size_t from_triple_size(const octet_sequnce& val, std::size_t& it) {
                if ((val.empty()) || (val[0] == '\xFF' && val.size() < 3))
                    return 0;
                if (val[0] == '\xFF') {
                    uint16_t sz;
                    if (raw_to_inttype(octet_sequnce(val.begin() + 1, val.end()), sz)) {
                        sz = endiancnv_copy(sz);
                        it += 3;
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

            void spdudata::setPGI(varid_type cod1, varid_type cod2, const octet_sequnce& val) {
                spdudata_type::iterator it = value_->find(cod1);
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

            void spdudata::setPI(varid_type cod, const octet_sequnce& val) {

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

            const octet_sequnce& spdudata::getPGI(varid_type cod1, varid_type cod2) const {
                spdudata_type::const_iterator it = value_->find(cod1);
                if (it == value_->end())
                    return null_val;
                pgi_type::const_iterator itpi = it->second. find(cod2);
                return (itpi != it->second.end()) ? itpi->second : null_val;
            }

            octet_sequnce& spdudata::getPGI(varid_type cod1, varid_type cod2) {
                if (!existPGI(cod1, cod2)) {
                    setPGI(cod1, cod2, octet_sequnce());
                }
                spdudata_type::iterator it = value_->find(cod1);
                pgi_type::iterator itpi = it->second. find(cod2);
                return itpi->second;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, int8_t& val, int8_t def) const {
                const octet_sequnce& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    val = tmp.size() ? static_cast<int8_t> (tmp[0]) : def;
                    return true;
                }
                val = def;

                return false;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, uint8_t& val, uint8_t def) const {
                const octet_sequnce& tmp = getPGI(cod1, cod2);
                if (!tmp.empty()) {
                    val = tmp.size() ? static_cast<varid_type> (tmp[0]) : def;
                    return true;
                }
                val = def;

                return false;
            }

            bool spdudata::getPGI(varid_type cod1, varid_type cod2, int16_t& val, int16_t def) const {
                const octet_sequnce& tmp = getPGI(cod1, cod2);
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
                const octet_sequnce& tmp = getPGI(cod1, cod2);
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

            const octet_sequnce& spdudata::getPI(varid_type cod) const {

                return getPGI(0, cod);
            }

            octet_sequnce& spdudata::getPI(varid_type cod) {

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

            asn_coder_ptr spdudata::sequence(asn_coder_ptr coder, std::size_t& constraints, bool first) const {

                std::size_t codersize = coder->out()->size();
                octet_sequnce tmp;


                spdudata_type::const_iterator strtit = value_->end();
                for (spdudata_type::const_iterator it = value_->begin(); it != value_->end(); ++it) {
                    if ((!it->first && it == value_->begin()))
                        strtit = it;
                    else {
                        octet_sequnce tmppgi;
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
                    octet_sequnce tmppi;
                    for (pgi_type::const_iterator itpgi = strtit->second.begin(); itpgi != strtit->second.end(); ++itpgi) {
                        if ((itpgi->first != PGI_USERDATA) && (itpgi->first != PGI_EXUSERDATA)) {
                            raw_back_insert(tmppi, inttype_to_raw(itpgi->first));
                            raw_back_insert(tmppi, to_triple_size(itpgi->second.size()));
                            raw_back_insert(tmppi, itpgi->second);
                        }
                    }
                    raw_back_insert(tmp, tmppi);
                }

                std::size_t datasize = codersize;
                
                if (constraints && datasize) {

                    bool connect_spdu = (type_ == CN_SPDU_ID);
                    
                    if (constraints < (tmp.size() + (connect_spdu ? 9 : 12) /*(4 -main header + 3 - ENCLOSURE + 4 - data val + 1 data)*/))
                        constraints += (connect_spdu ? 9 : 12); // ??? 

                    std::size_t max_datasize_with_header = constraints - (tmp.size() +((constraints > 0x100) ? 4 : 2/* main header*/) +
                            (connect_spdu ? 0 : 3) /*ENCLOSURE*/);

                    std::size_t max_datasize = (max_datasize_with_header > 0x100) ? (max_datasize_with_header - 4) : (max_datasize_with_header - 2);


                    if (max_datasize < datasize) {
                        datasize = max_datasize;
                        if (!connect_spdu) {
                            raw_back_insert(tmp, inttype_to_raw(PI_ENCLOSURE));
                            raw_back_insert(tmp, to_triple_size(1));
                            raw_back_insert(tmp, inttype_to_raw(first ? ENCLOSURE_BEGIN : ENCLOSURE_MIDLE));
                        }
                    }
                    else {
                        if (!first && !connect_spdu) {
                            raw_back_insert(tmp, inttype_to_raw(PI_ENCLOSURE));
                            raw_back_insert(tmp, to_triple_size(1));
                            raw_back_insert(tmp, inttype_to_raw(ENCLOSURE_MIDLE));
                        }
                    }
                }

                if (codersize) {
                    switch (type_) {
                        case CN_SPDU_ID:
                        {
                            if ((codersize > SIMPLE_USERDATA_LIMIT)) {
                                if (codersize > EXTEDED_USERDATA_LIMIT) {

                                    datasize = (EXTEDED_USERDATA_LIMIT > datasize) ? datasize : EXTEDED_USERDATA_LIMIT;

                                    raw_back_insert(tmp, inttype_to_raw(PGI_EXUSERDATA));
                                    raw_back_insert(tmp, to_triple_size(datasize));
                                }
                                else {
                                    raw_back_insert(tmp, inttype_to_raw(PGI_EXUSERDATA));
                                    raw_back_insert(tmp, to_triple_size(datasize));
                                }
                            }
                            else {
                                raw_back_insert(tmp, inttype_to_raw(PGI_USERDATA));
                                raw_back_insert(tmp, to_triple_size(datasize));
                            }
                            break;
                        }
                        case AA_SPDU_ID:
                        case RF_SPDU_ID:
                        case OA_SPDU_ID:
                        {
                            break; //no data
                        }
                        default:
                        {
                            raw_back_insert(tmp, inttype_to_raw(PGI_USERDATA));
                            raw_back_insert(tmp, to_triple_size(datasize));
                        }
                    }
                }

                coder->out()->add(octet_sequnce(tmp.begin(), tmp.end()), coder->out()->buffers().begin());
                datasize += tmp.size();

                octet_sequnce header(inttype_to_raw(type_));
                raw_back_insert(header, to_triple_size(datasize));
                coder->out()->add(octet_sequnce(header.begin(), header.end()), coder->out()->buffers().begin());
                return coder;
            }

            bool spdudata::parse() {
                octet_sequnce::size_type it = 0;
                if (seq_.size() < 2)
                    return error(true);
                type_ = static_cast<spdu_type> (seq_[it++]);
                std::size_t sz = from_triple_size(octet_sequnce(seq_.begin() + 1, seq_.end()), it);
                if (sz == triple_npos)
                    return error(true);
                if (sz == 0)
                    return false;
                if (sz + it > seq_.size())
                    return false;
                return parse_vars(octet_sequnce(seq_.begin()+(++it), seq_.end()));
            }

            bool spdudata::parse_vars(const octet_sequnce& vl) {
                octet_sequnce::size_type it = 0;
                do {
                    if (vl.size() < 2)
                        return error(true);
                    varid_type vr = static_cast<varid_type> (vl[it++]);
                    std::size_t sz = from_triple_size(octet_sequnce(vl.begin() + it, vl.end()), it);
                    if (sz == triple_npos)
                        return error(true);
                    if (sz + it > vl.size())
                        return false;
                    switch (vr) {
                        case PGI_CONN_ID:
                        case PGI_CONN_ACC:
                        case PGI_LINK_INF:
                        {
                            if (!parse_pgi(vr, octet_sequnce(vl.begin() + it, vl.begin() + it + sz))) return error(true);
                            else break;
                        }
                        default:
                        {
                            setPI(vr, octet_sequnce(vl.begin() + it, vl.begin() + it + sz));
                            break;
                        }
                    }
                    it += sz;
                }
                while (it < vl.size());
                return true;
            }

            bool spdudata::parse_pgi(varid_type tp, const octet_sequnce& vl) {
                octet_sequnce::size_type it = 0;
                do {
                    if (vl.size() < 2)
                        return error(true);
                    varid_type vr = static_cast<varid_type> (vl[it++]);
                    std::size_t sz = from_triple_size(octet_sequnce(vl.begin() + it, vl.end()), it);
                    if (sz == triple_npos)
                        return error(true);
                    if (sz + it > vl.size())
                        return false;
                    setPGI(tp, vr, octet_sequnce(vl.begin() + it, vl.begin() + it + sz));
                    it += sz;
                }
                while (it < vl.size());
                return true;
            }




            //  protocol_option

            protocol_options::protocol_options(const octet_sequnce& called, const octet_sequnce& calling) : vars_(new spdudata()) {
                vars_->setPI(PI_CALLING, calling);
                vars_->setPI(PI_CALLED, called);
                vars_->setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                vars_->setPGI(PGI_CONN_ACC, PI_VERSION, WORK_PROT_VERSION);
                vars_->setPI(PI_SES_USERREQ, FU_WORK);
            }

            protocol_options::protocol_options(const session_selector& ssel) : vars_(new spdudata()) {
                vars_->setPI(PI_CALLING, ssel.calling());
                vars_->setPI(PI_CALLED, ssel.called());
                vars_->setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                vars_->setPGI(PGI_CONN_ACC, PI_VERSION, WORK_PROT_VERSION);
                vars_->setPI(PI_SES_USERREQ, FU_WORK);
            }

            const octet_sequnce& protocol_options::ssap_calling() const {
                return vars_->getPI(PI_CALLING);
            }

            void protocol_options::ssap_calling(const octet_sequnce& val) {
                if (!val.empty())
                    vars_->setPI(PI_CALLING, val);
            }

            const octet_sequnce& protocol_options::ssap_called() const {
                return vars_->getPI(PI_CALLED);
            }

            void protocol_options::ssap_called(const octet_sequnce& val) {
                if (!val.empty())
                    vars_->setPI(PI_CALLED, val);
            }

            const octet_sequnce& protocol_options::data() const {
                return vars_->existPI(PGI_USERDATA) ? vars_->getPI(PGI_USERDATA) :
                        vars_->getPI(PGI_EXUSERDATA);
            }

            octet_sequnce& protocol_options::data() {
                return vars_->existPI(PGI_USERDATA) ? vars_->getPI(PGI_USERDATA) :
                        vars_->getPI(PGI_EXUSERDATA);
            }

            octet_type protocol_options::accept_version() const {
                octet_type tmp;
                return vars_->getPGI(PGI_CONN_ACC, PI_VERSION, tmp) ?
                        ((tmp & VERSION2) ?
                        VERSION2 : VERSION1) : VERSION1;
            }

            void protocol_options::accept_version(octet_type vl) {
                vars_->setPGI(PGI_CONN_ACC, PI_VERSION, (vl > VERSION1) ?
                        VERSION2 : VERSION2);
            }

            octet_type protocol_options::reject_version() const {
                octet_type tmp;
                return vars_->getPI(PI_VERSION, tmp) ?
                        ((tmp & VERSION2) ?
                        VERSION2 : VERSION1) : VERSION1;
            }

            void protocol_options::reject_version(octet_type vl) {
                return vars_->setPI(PI_VERSION, (vl > VERSION1) ?
                        VERSION2 : VERSION2);
            }

            int16_t protocol_options::user_requirement() const {
                int16_t tmp;
                return vars_->getPI(PI_SES_USERREQ, tmp) ? tmp : FU_DEFAULT; // *ref X225 8.3.1.16
            }

            void protocol_options::user_requirement(int16_t vl) {
                return vars_->setPI(PI_SES_USERREQ, vl);
            }

            bool protocol_options::extendedSPDU() const {
                octet_type tmp;
                return vars_->getPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, tmp) ?
                        tmp : false; // *ref X225 8.3.1.7
            }

            void protocol_options::extendedSPDU(bool vl) {
                vars_->setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, vl ? EXTENDED_SPDU : NOEXTENDED_SPDU);
            }

            bool protocol_options::endSPDU() const {
                octet_type tmp;
                return vars_->getPI(PI_ENCLOSURE, tmp) ?
                        (tmp & 2) : true; // *ref X225 8.3.3.3
            }

            bool protocol_options::beginSPDU() const {
                octet_type tmp;
                return vars_->getPI(PI_ENCLOSURE, tmp) ?
                        (tmp & 1) : true; // *ref X225 8.3.3.3
            }

            void protocol_options::endSPDU(bool end, bool beg) {
                if (!end || !beg)
                    vars_->setPI(PI_ENCLOSURE, static_cast<octet_type> ((end ? 2 : 0) | (beg ? 1 : 0))); // *ref X225 8.3.3.19
            }

            bool protocol_options::overflow() const {
                octet_type tmp;
                return vars_->getPI(PI_DATAOVERFLOW, tmp) ?
                        tmp : false; // *ref X225 8.3.1.19
            }

            void protocol_options::overflow(bool vl) {
                vars_->setPI(PI_DATAOVERFLOW, static_cast<octet_type> (vl ? 1 : 0));
            }

            octet_type protocol_options::refuse_reason() const {
                const octet_sequnce& tmp = vars_->getPI(PI_REASON);
                return tmp.empty() ? DR_REASON_NODEF : tmp[0];
            }

            void protocol_options::refuse_reason(octet_type rsn, const octet_sequnce& val) {
                if (val.empty())
                    vars_->setPI(PI_REASON, rsn);
                else {
                    octet_sequnce tmp(1, rsn);
                    tmp.insert(tmp.end(), val.begin(), val.end());
                    vars_->setPI(PI_REASON, tmp);
                }
            }

            uint16_t protocol_options::maxTPDU_src() const {
                const octet_sequnce& tmp = vars_->getPGI(PGI_CONN_ACC, PI_TSDUMAX);
                if (tmp.size() == 4) {
                    return endiancnv_copy<uint16_t > (octet_sequnce(tmp.begin(), tmp.begin() + 2));
                }
                return 0;
            }

            uint16_t protocol_options::maxTPDU_dist() const {
                const octet_sequnce& tmp = vars_->getPGI(PGI_CONN_ACC, PI_TSDUMAX);
                if (tmp.size() == 4) {
                    return endiancnv_copy<uint16_t > (octet_sequnce(tmp.begin() + 2, tmp.end()));
                }
                return 0;
            }

            void protocol_options::maxTPDU(uint16_t self, uint16_t dist) {
                if (self || dist) {
                    octet_sequnce tmpself(inttype_to_raw(endiancnv_copy(self)));
                    octet_sequnce tmpdist(inttype_to_raw(endiancnv_copy(dist)));
                    tmpself.insert(tmpself.begin(), tmpdist.begin(), tmpdist.end());
                    vars_->setPGI(PGI_CONN_ACC, PI_TSDUMAX, tmpself);
                }
            }

            /////////////////////

            bool negotiate_x225impl_option(const protocol_options& self, const protocol_options& dist, octet_type& errorreason) {

#if defined(ITUX200_DEBUG)                 
                std::cout << "Negotiate session level: LOCAL =" << self << " DISTANCE =" << dist << std::endl;
#endif                
                if (!(dist.user_requirement() & FU_WORK) || dist.extendedSPDU()) {
                    errorreason = DR_REASON_NEGOT;
                    return false;
                }

#ifndef CHECK_ISO_SELECTOR        
                if (!self.ssap_called().empty() && self.ssap_called() != dist.ssap_called()) {
                    errorreason = DR_REASON_ADDRESS;
                    return false;
                }
#endif                      
                return true;
            }

            std::size_t generate_header_CN(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(CN_SPDU_ID);
                tmp.setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                tmp.setPGI(PGI_CONN_ACC, PI_VERSION, WORK_PROT_VERSION);
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                if (!opt.ssap_calling().empty())
                    tmp.setPI(PI_CALLING, opt.ssap_calling());
                if (!opt.ssap_called().empty())
                    tmp.setPI(PI_CALLED, opt.ssap_called());
                if (before > EXTEDED_USERDATA_LIMIT) {
                    tmp.setPI(PI_DATAOVERFLOW, MORE_DATA);
                }
                if (opt.maxTPDU_dist() || opt.maxTPDU_src()) {

                }
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_OA(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                data->out()->clear(); // no user data *ref X225 Tab 12
                spdudata tmp(OA_SPDU_ID);
                tmp.setPI(PI_VERSION, VERSION2);
                tmp.sequence(data, constraints, first);
                return data->out()->size();
            }

            std::size_t generate_header_CDO(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(CDO_SPDU_ID);
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_AC(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(AC_SPDU_ID);
                tmp.setPGI(PGI_CONN_ACC, PI_PROTOCOL_OPTION, NOEXTENDED_SPDU);
                tmp.setPGI(PGI_CONN_ACC, WORK_PROT_VERSION, opt.accept_version());
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                if (!opt.ssap_calling().empty())
                    tmp.setPI(PI_CALLING, opt.ssap_calling());
                if (!opt.ssap_called().empty())
                    tmp.setPI(PI_CALLED, opt.ssap_called());
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_RF(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                data->out()->clear(); // no user data *ref X225 Tab 15                               
                spdudata tmp(RF_SPDU_ID);
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                tmp.setPI(PI_SES_USERREQ, FU_WORK);
                tmp.setPI(PI_VERSION, opt.reject_version());
                tmp.setPI(PI_REASON, opt.refuse_reason());
                tmp.sequence(data, constraints, first);
                return data->out()->size();
            }

            std::size_t generate_header_FN(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(FN_SPDU_ID);
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_DN(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(DN_SPDU_ID);
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_AB(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(AB_SPDU_ID);
                tmp.setPI(PI_TRANSPORT_DC, RELEASE_TRANSPORT);
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_AA(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                data->out()->clear(); // no user data *ref X225  8.3.10.2                              
                spdudata tmp(AA_SPDU_ID);
                tmp.sequence(data, constraints, first);
                return data->out()->size();
            }

            std::size_t generate_header_NF(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                std::size_t before = data->out()->size();
                spdudata tmp(NF_SPDU_ID);
                tmp.sequence(data, constraints, first);
                return data->out()->size() - before;
            }

            std::size_t generate_header_DT(const protocol_options& opt, asn_coder_ptr data, std::size_t& constraints, bool first) {
                data->out()->add(SEND_HEADER, data->out()->buffers().begin());
                return SEND_HEADER.size();
            }


            //sender

            sender::sender(spdu_type type, const protocol_options& opt, asn_coder_ptr data, std::size_t segmentsize ) :
            type_(type), segment_size(segmentsize), coder(data), option(opt), eofsegment(segmentsize ? false : true) {
                construct(true);
            }

            void sender::construct(bool first) {
                switch (type_) {
                    case CN_SPDU_ID:
                    {
                        constructCN(first);
                        break;
                    }
                    case OA_SPDU_ID:
                    {
                        constructOA(first);
                        break;
                    }
                    case CDO_SPDU_ID:
                    {
                        constructCDO(first);
                        break;
                    }
                    case AC_SPDU_ID:
                    {
                        constructAC(first);
                        break;
                    }
                    case RF_SPDU_ID:
                    {
                        constructRF(first);
                        break;
                    }
                    case FN_SPDU_ID:
                    {
                        constructFN(first);
                        break;
                    }
                    case AB_SPDU_ID:
                    {
                        constructAB(first);
                        break;
                    }
                    case DN_SPDU_ID:
                    {
                        constructDN(first);
                        break;
                    }
                    case AA_SPDU_ID:
                    {
                        constructAA(first);
                        break;
                    }
                    case DT_SPDU_ID:
                    {
                        constructDT(first);
                        break;
                    }
                    default:
                    {
                    }
                }
            }



            //receiver

            receiver::receiver(const mutable_buffer& buff) :
            state_(waittype),
            size_(0),
            estimatesize_(SI_WITH_LI),
            datasize_(0),
            type_(0),
            first_in_seq_(false),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            type_data(new octet_sequnce(SI_WITH_LI)),
            type_buff_(boost::asio::buffer(*type_data)),
            header_buff_(),
            userbuff_(buff),
            overflowed_(false) {
            }

            receiver::receiver() :
            state_(waittype),
            size_(0),
            estimatesize_(SI_WITH_LI),
            datasize_(0),
            type_(0),
            first_in_seq_(false),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            type_data(new octet_sequnce(SI_WITH_LI)),
            type_buff_(boost::asio::buffer(*type_data)),
            header_buff_(),
            userbuff_(),
            overflowed_(false) {

            }

            mutable_buffer receiver::buffer() {
                switch (state_) {
                    case waittype: return type_buff_ + size_;
                    case waitsize: return type_buff_ + size_;
                    case waitheader: return header_buff_ + size_;
                    case waitdata: return boost::asio::buffer(userbuff_ + datasize_);
                    default: return mutable_buffer();
                }
                return mutable_buffer();
            }

            void receiver::put(std::size_t sz) {
                if (!sz) return;
                size_ += sz;
                if (size_ >= estimatesize_) {
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
                            errcode(ER_PROTOCOL);
                            return;
                        }
                    }

                }
                if (state_ == waitdata) {
                    datasize_ += sz;
                    state(complete);
                }
            }

            receiver::operation_state receiver::state(operation_state val) {
                if (val != state_) {
                    size_ = 0;
                }
                if (val == error) {
                    estimatesize_ = 0;
                }
                return state_ = val;
            }

            error_code receiver::check_type() {
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
                std::size_t li = static_cast<std::size_t> (*boost::asio::buffer_cast<uint8_t*>(buff_ + 1));

                if (li == static_cast<std::size_t> (0xFF)) {
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
                    header_data = octet_sequnce_ptr(new octet_sequnce(li));
                    header_buff_ = mutable_buffer(boost::asio::buffer(*header_data));
                    estimatesize_ = li;
                    return error_code();
                }
                return errcode(ER_PROTOCOL);
            }

            error_code receiver::check_size() {
                mutable_buffer buff_ = type_buff_;
                uint16_t li = 0;
                raw_to_inttype(buffer_to_raw(buff_, 0, 2), li);
                li = endiancnv_copy(li);
                state(waitheader);
                header_data = octet_sequnce_ptr(new octet_sequnce(li));
                header_buff_ = mutable_buffer(boost::asio::buffer(*header_data));
                estimatesize_ = li;
                return error_code();
            }

            error_code receiver::check_header() {
                if (overflowed_) {
                    protocol_options_ptr tmp = protocol_options_ptr(new protocol_options(header_buff_));
                    options_->data().insert(options_->data().end(), tmp->data().begin(), tmp->data().end());
                    overflowed_ = !tmp->endSPDU();
                }
                else {
                    options_ = protocol_options_ptr(new protocol_options(header_buff_));
                    overflowed_ = !options_->endSPDU();
                }

                if (overflowed_) {
                    size_ = 0;
                    estimatesize_ = SI_WITH_LI;
                    datasize_ = 0;
                    type_ = 0;
                    first_in_seq_ = false;
                    class_option_ = 0;
                    reject_reason_ = 0;
                    errcode_ = error_code();
                    type_data = octet_sequnce_ptr(new octet_sequnce(SI_WITH_LI));
                    type_buff_ = boost::asio::buffer(*type_data);
                }
                        
				state(first_in_seq_ ? waittype : (overflowed_ ?  waittype: complete));
                return error_code();
            }

            void receiver::reject_reason(octet_type val) {
                errcode_ = error_code();
                reject_reason_ = val;
            }

            error_code receiver::errcode(const error_code& err) {
                if (!errcode_ && err)
                    errcode_ = err;
                if (err)
                    state_ = error;
                return errcode_;
            }

        }
    }
}
