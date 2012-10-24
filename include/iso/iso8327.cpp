/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 */

#include <iosfwd>
#include <iostream>
#include <sstream>

#include <iso/iso8327.h>


namespace boost {
    namespace asio {
        namespace iso {
            namespace prot8327 {

                std::size_t from_triple_size(const std::string& val, std::size_t& it) {
                    if ((!val.size()) || (val[0] == '\xFF' && val.size() < 3))
                        return 0;
                    if (val[0] == '\xFF') {
                        uint16_t sz;
                        if (str_to_inttype(val.substr(1), sz)) {
                            sz = endiancnv_copy(sz);
                            it += 2;
                            return static_cast<std::size_t> (sz);
                        }
                    }
                    else {
                        uint8_t sz;
                        if (str_to_inttype(val, sz)) {
                            it += 1;
                            return static_cast<std::size_t> (sz);
                        }
                    }
                    return triple_npos;
                }


                //  spdudata 

                void spdudata::setPGI(varid_type cod1 , varid_type cod2 , const std::string& val) {
                    spdudata_type::iterator it = find(cod1);
                    if (it == end()) {
                        pgi_type pgi;
                        pgi.insert(pi_type(cod2, parameter_ln_type(val.size(), val)));
                        insert(pgis_type(cod1, pgi));
                    }

                    else
                        it->second.insert(pi_type(cod2, parameter_ln_type(val.size(), val)));
                }

                void spdudata::setPGI(varid_type cod1 , varid_type cod2, int8_t val) {

                    setPGI(cod1 , cod2 , inttype_to_str(val));
                }

                void spdudata::setPGI(varid_type cod1 , varid_type cod2, uint8_t val) {

                    setPGI(cod1 , cod2 , inttype_to_str(val));
                }

                void spdudata::setPGI(varid_type cod1 , varid_type cod2, int16_t val) {

                    setPGI(cod1 , cod2 , inttype_to_str(endiancnv_copy(val)));
                }

                void spdudata::setPGI(varid_type cod1 , varid_type cod2, uint16_t val) {

                    setPGI(cod1 , cod2 , inttype_to_str(endiancnv_copy(val)));
                }

                void spdudata::setPI(varid_type cod , const std::string& val) {

                    setPGI(0, cod, val);
                }

                void spdudata::setPI(varid_type cod, int8_t val) {

                    setPI(cod, inttype_to_str(val));
                }

                void spdudata::setPI(varid_type cod, uint8_t val) {

                    setPI(cod, inttype_to_str(val));
                }

                void spdudata::setPI(varid_type cod, int16_t val) {

                    setPI(cod,  inttype_to_str(endiancnv_copy(val)));
                }

                void spdudata::setPI(varid_type cod, uint16_t val) {

                    setPI(cod,  inttype_to_str(endiancnv_copy(val)));
                }

                bool spdudata::getPGI(varid_type cod1 , varid_type cod2,  std::string& val) const {
                    spdudata_type::const_iterator it = find(cod1);
                    if (it == end())
                        return false;
                    pgi_type::const_iterator itpi = it->second. find(cod2);
                    val = (itpi != it->second.end()) ? itpi->second.second : "";

                    return itpi != it->second.end();
                }

                bool spdudata::getPGI(varid_type cod1 , varid_type cod2,  int8_t& val, int8_t def) const {
                    std::string tmp;
                    if (getPGI(cod1 , cod2,  tmp)) {
                        val = tmp.size() ? static_cast<int8_t> (tmp[0]) : def;
                        return true;
                    }
                    val = def;

                    return false;
                }

                bool spdudata::getPGI(varid_type cod1 , varid_type cod2,  uint8_t& val, uint8_t def) const {
                    std::string tmp;
                    if (getPGI(cod1 , cod2,  tmp)) {
                        val = tmp.size() ? static_cast<varid_type> (tmp[0]) : def;
                        return true;
                    }
                    val = def;

                    return false;
                }

                bool spdudata::getPGI(varid_type cod1 , varid_type cod2,  int16_t& val, int16_t def) const {
                    std::string tmp;
                    if (getPGI(cod1 , cod2,  tmp)) {
                        if (str_to_inttype(tmp, val))
                            val = endiancnv_copy(val);
                        else
                            val = def;
                        return true;
                    }
                    val = def;

                    return false;
                }

                bool spdudata::getPGI(varid_type cod1 , varid_type cod2,  uint16_t& val, uint16_t def) const {
                    std::string tmp;
                    if (getPGI(cod1 , cod2,  tmp)) {
                        if (str_to_inttype(tmp, val))
                            val = endiancnv_copy(val);
                        else
                            val = def;
                        return true;
                    }
                    val = def;

                    return false;
                }

                bool spdudata::getPI(varid_type cod, std::string& val) const {

                    return getPGI(0, cod, val);
                }

                bool spdudata::getPI(varid_type cod,  int8_t& val, int8_t def) const {

                    return getPGI(0, cod, val, def);
                }

                bool spdudata::getPI(varid_type cod,  uint8_t& val, uint8_t def)  const {

                    return getPGI(0, cod, val, def);
                }

                bool spdudata::getPI(varid_type cod,  int16_t& val, int16_t def)  const {

                    return getPGI(0, cod, val, def);
                }

                bool spdudata::getPI(varid_type cod,  uint16_t& val, uint16_t def)  const {

                    return getPGI(0, cod, val, def);
                }

                bool spdudata::existPGI(varid_type cod1 , varid_type cod2) const {
                    spdudata_type::const_iterator it = find(cod1);
                    if (it == end())
                        return false;
                    pgi_type::const_iterator itpi = it->second.find(cod2);

                    return  (itpi != it->second.end());
                }

                bool spdudata::existPI(varid_type cod) const {

                    return  existPGI(0, cod);
                }

                bool spdudata::nullPGI(varid_type cod1 , varid_type cod2) const {
                    spdudata_type::const_iterator it = find(cod1);
                    if (it == end())
                        return false;
                    pgi_type::const_iterator itpi = it->second.find(cod2);

                    return  (itpi != it->second.end() ? (!itpi->second.first) : false);
                }

                bool spdudata::nullPI(varid_type cod) const {

                    return  nullPGI(0, cod);
                }

                std::size_t spdudata::getPGIsize(varid_type cod1 , varid_type cod2) const {
                    spdudata_type::const_iterator it = find(cod1);
                    if (it == end())
                        return false;
                    pgi_type::const_iterator itpi = it->second. find(cod2);

                    return (itpi != it->second.end()) ? itpi->second.first : 0;
                }

                std::size_t spdudata::getPIsize(varid_type cod) const {

                    return getPGIsize(0, cod);
                }

                const std::string& spdudata::sequence() const {
                    std::string tmp;
                    spdudata_type::const_iterator strtit = end();
                    for (spdudata_type::const_iterator it = begin(); it != end(); ++it) {
                        if ((!it->first && it == begin()))
                            strtit = it;
                        else {
                            std::string tmppgi;
                            for ( pgi_type::const_iterator itpgi = it->second.begin(); itpgi != it->second.end(); ++itpgi) {
                                tmppgi += (inttype_to_str( itpgi->first) + to_triple_size(itpgi->second.first) +  itpgi->second.second);
                            }
                            tmp += (inttype_to_str( it->first) + to_triple_size(tmppgi.size()) + tmppgi);
                        }
                    }
                    if (strtit != end()) {
                        std::string tmppi;
                        for ( pgi_type::const_iterator itpgi = strtit->second.begin(); itpgi != strtit->second.end(); ++itpgi) {
                            tmppi += (inttype_to_str( itpgi->first) + to_triple_size (itpgi->second.first) +  itpgi->second.second);
                        }
                        tmp += tmppi;
                    }
                    tmp = inttype_to_str(type_) + to_triple_size(tmp.size()) + tmp;
                    seq_.swap(tmp);
                    return seq_;
                }

                bool spdudata::parse() {
                    std::string::size_type it = 0;
                    if (seq_.size() < 2)
                        return error(true);
                    type_ = static_cast<spdu_type> (seq_[it++]);
                    std::size_t  sz = from_triple_size(seq_.substr(1), it);
                    if (sz == triple_npos)
                        return error(true);
                    if (sz == 0)
                        return false;
                    if (sz + it > seq_.size())
                        return false;
                    return parse_vars(seq_.substr(++it));
                }

                bool spdudata::parse_vars(const std::string& vl) {
                    std::string::size_type it = 0;
                    do {
                        if (vl.size() < 2)
                            return error(true);
                        varid_type vr = static_cast<varid_type> (vl[it++]);
                        std::size_t  sz = from_triple_size(vl.substr(it), it);
                        if (sz == triple_npos)
                            return error(true);
                        if (sz == 0)
                            return false;
                        if (sz + it > vl.size())
                            return false;
                        switch (vr) {
                            case PGI_CN_IND:
                            case PGI_CN_AC:
                            {
                                if (!parse_pgi(vr, vl.substr(it , sz))) return error(true);
                                else break;
                            }
                            default:
                            {
                                setPI(vr, vl.substr(it, sz));
                                break;
                            }
                        }
                        it += sz;
                    }
                    while (it < vl.size());
                    return true;
                }

                bool spdudata::parse_pgi(varid_type tp, const std::string& vl) {
                    std::string::size_type it = 0;
                    do {
                        if (vl.size() < 2)
                            return error(true);
                        varid_type vr = static_cast<varid_type> (vl[it++]);
                        std::size_t  sz = from_triple_size(vl.substr(it), it);
                        if (sz == triple_npos)
                            return error(true);
                        if (sz + it > vl.size())
                            return false;
                        setPGI(tp, vr, vl.substr(it, sz));
                        it += sz;
                    }
                    while (it < vl.size());
                    return true;
                }

                std::ostream& operator<<(std::ostream& strm, const spdudata& vrs) {
                    return strm << (dvnci::binary_block_to_hexsequence_debug(vrs.sequence()));
                }




                //  protocol_option

                std::string protocol_options::ssap_calling() const {
                    /* for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                         if (it->first.first == VAR_TSAPCALLING_ID  && !it->second.empty()) {
                             return it->second;
                         }
                     }*/
                    return "";
                }

                void protocol_options::ssap_calling(const std::string& val) {
                    /* for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                         if (it->first.first == VAR_TSAPCALLING_ID) {
                             it->second = val;
                             return;
                         }
                     }
                     vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, val.size()), val));*/
                }

                std::string protocol_options::ssap_called() const {
                    /* for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                         if (it->first.first == VAR_TSAPCALLED_ID  && !it->second.empty()) {
                             return it->second;
                         }
                     }*/
                    return "";
                }

                void protocol_options::ssap_called(const std::string& val) {
                    /*for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TSAPCALLED_ID) {
                            it->second = val;
                            return;
                        }
                    }
                    vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, val.size()), val));*/
                }
                
         //
                              //  const int8_t WORK_PROT_OPTION='\x0';
               //const int8_t WORK_PROT_VERSION='\x2';    
                
         std::string generate_header_CN(const protocol_options& opt, const std::string& data){
                    spdudata tmp(CN_SPDU_ID);
                    tmp.setPGI(PGI_CN_AC, PI_PROPT, WORK_PROT_OPTION);
                    tmp.setPGI(PGI_CN_AC, PI_VERS,WORK_PROT_VERSION);
                    tmp.setPI(PI_SUREQ,FU_WORK);
                    tmp.setPI(PI_CALLING,opt.ssap_calling());   
                    tmp.setPI(PI_CALLED,opt.ssap_called());  
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }
         
          std::string generate_header_AC(const protocol_options& opt, const std::string& data){
                    spdudata tmp(AC_SPDU_ID);
                    tmp.setPGI(PGI_CN_AC, PI_PROPT,WORK_PROT_OPTION);
                    tmp.setPGI(PGI_CN_AC, PI_VERS,WORK_PROT_VERSION);
                    tmp.setPI(PI_SUREQ,FU_WORK);
                    tmp.setPI(PI_CALLING,opt.ssap_calling());   
                    tmp.setPI(PI_CALLED,opt.ssap_called());  
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }       
          
          std::string generate_header_DN(const std::string& data){
                    spdudata tmp(DN_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }    
          
          std::string generate_header_RF(const std::string& data){
                    spdudata tmp(RF_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }           
          
          std::string generate_header_AB(const std::string& data){
                    spdudata tmp(AB_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }  
          
           std::string generate_header_AA(const std::string& data){
                    spdudata tmp(AA_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }       
           
           std::string generate_header_FN(const std::string& data){
                    spdudata tmp(FN_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }  
          
           std::string generate_header_NF(const std::string& data){
                    spdudata tmp(NF_SPDU_ID);
                    tmp.setPI(PI_USERDATA,data); 
                    return tmp.sequence();
                }           


            }
        }
    }
}
