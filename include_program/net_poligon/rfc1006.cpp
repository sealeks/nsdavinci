/* 
 * File:   rfc1006.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 28 РЎРµРЅС‚СЏР±СЂСЊ 2012 Рі., 22:51
 */

#include <iosfwd>

#include "rfc1006.h"



namespace boost {
    namespace asio {
        namespace ip {


            namespace iec8073 {

                boost::system::error_code errorcode_by_reason(int8_t val) {
                    if (!val)
                        return ERROR_EIO;
                    if (val & '\x1')
                        return ERROR_EDOM;
                    return ERROR_EIO;
                }

                tpdu_type tpdu_type_from(int8_t val) {
                    switch (val) {
                        case CR_TPDU_ID: return CR;
                        case CC_TPDU_ID: return CC;
                        case DR_TPDU_ID: return DR;
                        case DC_TPDU_ID: return DR;
                        case DT_TPDU_ID: return DT;
                        case ED_TPDU_ID: return ED;
                        case DA_TPDU_ID: return DA;
                        case EA_TPDU_ID: return EA;
                        case RJ_TPDU_ID: return RJ;
                        case ER_TPDU_ID: return ER;
                    };
                    return NL;
                }

                std::size_t getPDUsize(int8_t sz) {
                    switch (sz) {
                        case TPDU_SIZE8192: return 8192;
                        case TPDU_SIZE4096: return 4096;
                        case TPDU_SIZE2048: return 2048;
                        case TPDU_SIZE1024: return 1024;
                        case TPDU_SIZE512: return 512;
                        case TPDU_SIZE256: return 256;
                        case TPDU_SIZE128: return 128;
                        case TPDU_SIZE4: return 7;
                    }
                    return 0;
                }

                std::size_t tpdu_byte_size(tpdu_size val) {
                    return getPDUsize(tpdu_type_size(val));
                }

                tpdu_size tpdu_size_frombyte(int8_t val) {
                    switch (val) {
                        case TPDU_SIZE8192: return SIZE8192;
                        case TPDU_SIZE4096: return SIZE4096;
                        case TPDU_SIZE2048: return SIZE2048;
                        case TPDU_SIZE1024: return SIZE1024;
                        case TPDU_SIZE512: return SIZE512;
                        case TPDU_SIZE256: return SIZE256;
                        case TPDU_SIZE128: return SIZE128;
                        case TPDU_SIZE4: return SIZE4;
                    }
                    return SIZENULL;
                }

                bool parse_vars(const std::string& str, headarvarvalues& vars) {
                    vars.clear();
                    std::string::size_type it = 0;
                    while (it + 2 < str.size()) {
                        int8_t par = static_cast<int8_t> (str[it]);
                        std::size_t len = static_cast<std::size_t> (static_cast<uint8_t> (str[it + 1]));
                        if ((it + 2 + len) > str.size()) {
                            vars.clear();
                            return false;
                        }
                        vars.push_back(headarvarvalue(headarvar(par, len), str.substr(it + 2, len)));
                        it += (2 + len);
                    }
                    return it == str.size();
                }


                ///   protocol_options

                protocol_options::protocol_options(int16_t dst, int16_t src, tpdu_size pdusize, const std::string& called,  const std::string& calling) :
                dst_(dst), src_(src) {
                    if (SIZENULL != pdusize) vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1) , inttype_to_str(static_cast<int8_t> (tpdu_type_size(pdusize)))));
                    if (!calling.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, calling.size()), calling));
                    if (!called.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, called.size()), called));
                }

                tpdu_size protocol_options::pdusize() const {
                    for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TPDU_SIZE && !it->second.empty()) {
                            return tpdu_size_frombyte(static_cast<int8_t> (it->second[0]));
                        }
                    }
                    return SIZENULL;
                }

                void protocol_options::pdusize(tpdu_size val) {
                    for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TPDU_SIZE) {
                            it->second = inttype_to_str(static_cast<int8_t> (tpdu_type_size(val)));
                            return;
                        }
                    }
                    vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1), inttype_to_str(static_cast<int8_t> (tpdu_type_size(val)))));
                }

                std::string protocol_options::tsap_calling() const {
                    for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TSAPCALLING_ID  && !it->second.empty()) {
                            return it->second;
                        }
                    }
                    return "";
                }

                void protocol_options::tsap_calling(const std::string& val) {
                    for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TSAPCALLING_ID) {
                            it->second = val;
                            return;
                        }
                    }
                    vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, val.size()), val));
                }

                std::string protocol_options::tsap_called() const {
                    for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TSAPCALLED_ID  && !it->second.empty()) {
                            return it->second;
                        }
                    }
                    return "";
                }

                void protocol_options::tsap_called(const std::string& val) {
                    for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_TSAPCALLED_ID) {
                            it->second = val;
                            return;
                        }
                    }
                    vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, val.size()), val));
                }

                std::size_t protocol_options::maxpdusize() const {
                    for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_MAXTPDU_SIZE  && !it->second.empty()) {
                            return 128;
                        }
                    }
                    return 128;
                }

                void protocol_options::maxpdusize(std::size_t val) {
                    for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                        if (it->first.first == VAR_MAXTPDU_SIZE) {
                            //it->second=inttype_to_str(static_cast<int8_t>(tpdu_type_size(val)));
                            return;
                        }
                    }
                    vars_.push_back(headarvarvalue(headarvar(VAR_MAXTPDU_SIZE, 1), inttype_to_str(static_cast<int8_t> (128))));
                }

                void generate_TKPTDU(std::string& val) {
                    val = TKPT_START + inttype_to_str(be_le_convert16(static_cast<int16_t> (val.size() + TKPT_LENGTH))) + val;
                }

                std::string generate_header(int8_t type, int16_t dst, int16_t src, const headarvarvalues& vars) {
                    std::string rslt = inttype_to_str(type) + inttype_to_str(dst) + inttype_to_str(src) + NULLCHAR;
                    for (headarvarvalues::const_iterator it = vars.begin(); it != vars.end(); ++it)
                        rslt += (inttype_to_str(it->first.first) + inttype_to_str(static_cast<int8_t> (it->first.second)) + it->second);
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    return rslt;
                }

                std::string generate_header_TKPT_CR(const protocol_options& opt) {
                    std::string rslt = inttype_to_str(CR_TPDU_ID) +
                            inttype_to_str(be_le_convert16(static_cast<int16_t> (0))) +
                            inttype_to_str(be_le_convert16(opt.src_tsap())) + NULLCHAR;
                    if (opt.pdusize() != SIZENULL)
                        rslt += (inttype_to_str(VAR_TPDU_SIZE) + inttype_to_str(static_cast<int8_t> (1)) + inttype_to_str(tpdu_type_size(opt.pdusize())));
                    if (!opt.tsap_calling().empty())
                        rslt += (inttype_to_str(VAR_TSAPCALLING_ID) + inttype_to_str(static_cast<int8_t> (opt.tsap_calling().size())) + opt.tsap_calling());
                    if (!opt.tsap_called().empty())
                        rslt += (inttype_to_str(VAR_TSAPCALLED_ID) + inttype_to_str(static_cast<int8_t> (opt.tsap_called().size())) + opt.tsap_called());
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                std::string generate_header_TKPT_CC(const protocol_options& opt) {
                    std::string rslt = inttype_to_str(CC_TPDU_ID) +
                            inttype_to_str(be_le_convert16(opt.dst_tsap())) +
                            inttype_to_str(be_le_convert16(opt.src_tsap())) + NULLCHAR;
                    if (opt.pdusize() != SIZENULL)
                        rslt += (inttype_to_str(VAR_TPDU_SIZE) + inttype_to_str(static_cast<int8_t> (1)) + inttype_to_str(tpdu_type_size(opt.pdusize())));
                    if (!opt.tsap_calling().empty())
                        rslt += (inttype_to_str(VAR_TSAPCALLING_ID) + inttype_to_str(static_cast<int8_t> (opt.tsap_calling().size())) + opt.tsap_calling());
                    if (!opt.tsap_called().empty())
                        rslt += (inttype_to_str(VAR_TSAPCALLED_ID) + inttype_to_str(static_cast<int8_t> (opt.tsap_called().size())) + opt.tsap_called());
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                std::string generate_header_TKPT_DR(int16_t dst, int16_t src, int8_t rsn) {
                    std::string rslt = inttype_to_str(DR_TPDU_ID) +
                            inttype_to_str(be_le_convert16(dst)) +
                            inttype_to_str(be_le_convert16(src));
                    rslt += inttype_to_str(rsn);
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                std::string generate_header_TKPT_DC(int16_t dst, int16_t src) {
                    std::string rslt = inttype_to_str(DR_TPDU_ID) +
                            inttype_to_str(be_le_convert16(dst)) +
                            inttype_to_str(be_le_convert16(src));
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                std::string generate_header_TKPT_DT_single(const std::string& data, bool end) {
                    std::string rslt = inttype_to_str(DT_TPDU_ID) +
                            inttype_to_str(end ? TPDU_ENDED : TPDU_CONTINIUE);
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    rslt += data;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                std::string generate_header_TKPT_ER(int16_t dst, const std::string& errorreason, int8_t err) {
                    std::string rslt = inttype_to_str(ER_TPDU_ID) +
                            inttype_to_str(be_le_convert16(dst)) + inttype_to_str(err) + inttype_to_str(WRONG_TPDU) +
                            inttype_to_str(static_cast<int8_t> (errorreason.size())) + errorreason;
                    std::size_t sz = rslt.size();
                    rslt = inttype_to_str(static_cast<int8_t> (sz)) + rslt;
                    generate_TKPTDU(rslt);
                    return rslt;
                }

                void  receive_seq::reject_reason(int8_t val) {
                    errcode_ = errorcode_by_reason(val);
                    reject_reason_ = val;
                }

                void receive_seq::check() {
                    while ((check_tpdu(cursor_) == repeat)) {
                    };
                }

                receive_seq::operation_state receive_seq::check_tpdu(std::size_t& beg) {
                    std::size_t oldbeg = beg;
                    if (size_ < (beg + 2))
                        return state(continuous);
                    std::string hdr = std::string(boost::asio::buffer_cast<const char*>(buff_ + beg), 2);
                    if (hdr != TKPT_START)
                        return state(error);
                    if (size_ < (beg + 4))
                        return state(continuous);
                    std::string strsz = std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 2)), 2);
                    int16_t pdsz = 0;
                    str_to_inttype(strsz, pdsz);
                    pdsz = be_le_convert16(pdsz);
                    if (pdsz < 0)
                        return state(error);
                    if (size_ < (beg + static_cast<std::size_t> (pdsz))) {
                        return state(continuous);
                    }
                    if (size_ < (beg + 6))
                        return state(error);
                    std::size_t li = static_cast<std::size_t> (*boost::asio::buffer_cast<unsigned char*>(buff_ + (beg + 4)));
                    if (size_ < (TKPT_LENGTH + li + 1))
                        return state(error);
                    int8_t nativetp = *boost::asio::buffer_cast<int8_t*>(buff_ + (beg + 5));
                    type_ = tpdu_type_from(((nativetp & '\xF0') == CR_TPDU_ID) ? (nativetp & '\xF0') : nativetp);
                    /* запрос возможен и от др классов*/
                    switch (type_) {
                        case DT:
                        {
                            if (li != 2)
                                return state(error); /* !!должен быть только класс 0 см. 13.7*/
                            int8_t eof = *boost::asio::buffer_cast<int8_t*>(buff_ + (beg + 6));
                            if (eof == TPDU_ENDED) {
                                boost::array<mutable_buffer, 2 > bufsarr = {
                                    mutable_buffer(boost::asio::buffer(buff_, oldbeg)),
                                    mutable_buffer(buff_ + (oldbeg + TKPT_LENGTH + li + 1))
                                };
                                buffer_copy(buff_, bufsarr);
                                size_ -= (TKPT_LENGTH + li + 1);
                                return state(complete);
                            }
                            if (eof != TPDU_CONTINIUE) {
                                return state(error);
                            }
                            beg = beg + static_cast<std::size_t> (pdsz);
                            boost::array<mutable_buffer, 2 > bufsarr = {
                                mutable_buffer(boost::asio::buffer(buff_, oldbeg)),
                                mutable_buffer(buff_ + (oldbeg + TKPT_LENGTH + li + 1))
                            };
                            buffer_copy(buff_, bufsarr);
                            size_ -= (TKPT_LENGTH + li + 1);
                            beg -= (TKPT_LENGTH + li + 1);
                            return state(beg >= size_ ? continuous : repeat);
                        }
                        case CR:
                        {
                            if (li < 6)
                                return state(error); /* невозможно см. 13.3.1*/
                            int16_t dst_tsap_ = 0;
                            int16_t src_tsap_ = 0;
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 6)), 2), dst_tsap_);
                            dst_tsap_ = be_le_convert16(dst_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 8)), 2), src_tsap_);
                            src_tsap_ = be_le_convert16(src_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 10)), 1), class_option_);
                            headarvarvalues vars;
                            if (!parse_vars(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 11)), li - 6), vars))
                                return state(error);
                            options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                            return state(complete);
                        }
                        case CC:
                        {
                            if (li < 6)
                                return state(error); /* невозможно см. 13.3.1*/
                            int16_t dst_tsap_ = 0;
                            int16_t src_tsap_ = 0;
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 6)), 2), dst_tsap_);
                            dst_tsap_ = be_le_convert16(dst_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 8)), 2), src_tsap_);
                            src_tsap_ = be_le_convert16(src_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 10)), 1), class_option_);
                            headarvarvalues vars;
                            if (!parse_vars(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 11)), li - 6), vars))
                                return state(error);
                            options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                            return state(complete);
                        }
                        case DR:
                        {
                            if (li < 6)
                                return state(error); /* невозможно см. 13.3.1*/
                            int16_t dst_tsap_ = 0;
                            int16_t src_tsap_ = 0;
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 6)), 2), dst_tsap_);
                            dst_tsap_ = be_le_convert16(dst_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 8)), 2), src_tsap_);
                            src_tsap_ = be_le_convert16(src_tsap_);
                            int8_t rsn;
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 10)), 1), rsn);
                            reject_reason(rsn);
                            headarvarvalues vars;
                            if (!parse_vars(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 11)), li - 6), vars))
                                return state(error);
                            if (oldbeg) {
                                boost::array<mutable_buffer, 2 > bufsarr = {
                                    mutable_buffer(boost::asio::buffer(buff_, oldbeg)),
                                    mutable_buffer(buff_ + (oldbeg + TKPT_LENGTH + li + 1))
                                };
                                buffer_copy(buff_, bufsarr);
                                size_ -= (TKPT_LENGTH + li + 1);
                            }
                            else {
                                size_ = 0;
                            }
                            options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                            return state(complete);
                        }
                        case ER:
                        {
                            if (li < 3)
                                return state(error); /* невозможно см. 13.3.1*/
                            int16_t dst_tsap_ = 0;
                            int16_t src_tsap_ = 0;
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 6)), 2), dst_tsap_);
                            str_to_inttype(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 8)), 1), reject_reason_);
                            headarvarvalues vars;
                            if (!parse_vars(std::string(boost::asio::buffer_cast<const char*>(buff_ + (beg + 11)), li - 3), vars))
                                return state(error);
                            if (oldbeg) {
                                boost::array<mutable_buffer, 2 > bufsarr = {
                                    mutable_buffer(boost::asio::buffer(buff_, oldbeg)),
                                    mutable_buffer(buff_ + (oldbeg + TKPT_LENGTH + li + 1))
                                };
                                buffer_copy(buff_, bufsarr);
                                size_ -= (TKPT_LENGTH + li + 1);
                            }
                            else {
                                size_ = 0;
                            }
                            return state(complete);

                        }
                    }
                    return state(error);
                }


                ///////////////////////////////////////////////////////////////////////////////////////

                const_buffer send_seq::pop() {
                    if (iterator_ == lines_.end())
                        return const_buffer();
                    const std::string& line = *iterator_;
                    return const_buffer(boost::asio::buffer(line.data() + currentiterator_, currentsize_));
                }

                std::size_t  send_seq::size(std::size_t  sz) {
                    if (!sz) return size_;
                    if (iterator_ == lines_.end()) {
                        state_ = complete;
                        currentiterator_ = 0;
                        currentsize_ = 0;
                        return size_;
                    }
                    currentiterator_ += sz;
                    if (currentiterator_ < currentsize_) {
                        currentsize_ -= sz;
                        state_ = continuous;
                    }
                    else {
                        if (currentiterator_ == currentsize_) {
                            iterator_++;
                            if (iterator_ == lines_.end()) {
                                state_ = complete;
                                currentiterator_ = 0;
                                currentsize_ = 0;
                            }
                            else {
                                state_ = continuous;
                                currentiterator_ = 0;
                                currentsize_ = (*iterator_).size();
                            }
                        }
                        else {
                            state_ = error;
                            iterator_ = lines_.end();
                            currentiterator_ = 0;
                            currentsize_ = 0;
                        }
                    }
                    return size_ += sz;
                }

                void send_seq::constructDT(const std::string& seq, tpdu_size pdusize) {
                    std::string::size_type sz = tpdu_byte_size(pdusize);
                    iterator_ = lines_.end();
                    if (sz <= 3)
                        return;
                    sz -= 3;
                    lines_.clear();
                    std::string::size_type start = 0;
                    do {
                        if ((start + sz) < seq.size())
                            lines_.push_back(std::string( generate_header_TKPT_DT_single(seq.substr(start, sz), false)));
                        else
                            lines_.push_back(std::string( generate_header_TKPT_DT_single(seq.substr(start), true)));
                        start += sz;
                    }
                    while (start < seq.size());
                    iterator_ = lines_.begin();
                    currentsize_ = lines_.begin() != lines_.end() ? lines_.begin()->size() : 0;
                }

                void send_seq::constructCR(const protocol_options& opt) {
                    lines_.push_back(std::string( generate_header_TKPT_CR(opt)));
                    iterator_ = lines_.begin();
                    currentsize_ = lines_.begin() != lines_.end() ? lines_.begin()->size() : 0;
                }

                void send_seq::constructCC(const protocol_options& opt) {
                    lines_.push_back(std::string( generate_header_TKPT_CC(opt)));
                    iterator_ = lines_.begin();
                    currentsize_ = lines_.begin() != lines_.end() ? lines_.begin()->size() : 0;
                }

                void send_seq::constructER(int16_t dst, const std::string& errorreason, int8_t err) {
                    lines_.push_back(std::string( generate_header_TKPT_ER(dst, errorreason, err)));
                    iterator_ = lines_.begin();
                    currentsize_ = lines_.begin() != lines_.end() ? lines_.begin()->size() : 0;
                }

                void send_seq::constructDR(int16_t dst, int16_t src, int8_t rsn) {
                    lines_.push_back(std::string( generate_header_TKPT_DR(dst, src , rsn)));
                    iterator_ = lines_.begin();
                    currentsize_ = lines_.begin() != lines_.end() ? lines_.begin()->size() : 0;
                }

            }
        }
    }
}