/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iso/rfc1006.h>


namespace boost {
    namespace iso {
        namespace prot8073 {
            
            

            boost::system::error_code errorcode_by_reason(octet_type val) {
                if (!val)
                    return ERROR_EIO;
                if (val & '\x1')
                    return ERROR_EDOM;
                return ERROR_EIO;
            }

            tpdu_type tpdu_type_from(octet_type val) {
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

            std::size_t getPDUsize(octet_type sz) {
                switch (sz) {
                    case TPDU_SIZE2048: return 2048;
                    case TPDU_SIZE1024: return 1024;
                    case TPDU_SIZE512: return 512;
                    case TPDU_SIZE256: return 256;
                    case TPDU_SIZE128: return 128;
                }
                return 0;
            }

            std::size_t tpdu_byte_size(tpdu_size val) {
                return getPDUsize(tpdu_type_size(val));
            }

            tpdu_size tpdu_size_frombyte(octet_type val) {
                switch (val) {
                    case TPDU_SIZE2048: return SIZE2048;
                    case TPDU_SIZE1024: return SIZE1024;
                    case TPDU_SIZE512: return SIZE512;
                    case TPDU_SIZE256: return SIZE256;
                    case TPDU_SIZE128: return SIZE128;
                }
                return SIZENULL;
            }

            bool parse_vars(const raw_type& data, headarvarvalues& vars) {
                vars.clear();
                std::size_t it = 0;
                while (it + 2 < data.size()) {
                    octet_type par = static_cast<octet_type> (data[it]);
                    std::size_t len = static_cast<std::size_t> (static_cast<uint8_t> (data[it + 1]));
                    if ((it + 2 + len) > data.size()) {
                        vars.clear();
                        return false;
                    }
                    vars.push_back(headarvarvalue(headarvar(par, len), raw_type(data.begin() +(it + 2), data.begin() +(it + 2 + len))));
                    it += (2 + len);
                }
                return it == data.size();
            }


            ///   protocol_options

            protocol_options::protocol_options(int16_t dst, int16_t src, tpdu_size pdusize, const raw_type& called, const raw_type& calling) :
            dst_(dst), src_(src) {
                if (SIZENULL != pdusize) vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1), inttype_to_raw(static_cast<int8_t> (tpdu_type_size(pdusize)))));
                if (!calling.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, calling.size()), calling));
                if (!called.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, called.size()), called));
            }

            tpdu_size protocol_options::pdusize() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TPDU_SIZE && !it->second.empty()) {
                        return tpdu_size_frombyte(static_cast<octet_type> (it->second[0]));
                    }
                }
                return SIZENULL;
            }

            void protocol_options::pdusize(tpdu_size val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TPDU_SIZE) {
                        it->second = inttype_to_raw(static_cast<octet_type> (tpdu_type_size(val)));
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1), inttype_to_raw(static_cast<octet_type> (tpdu_type_size(val)))));
            }

            const raw_type& protocol_options::tsap_calling() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLING_ID && !it->second.empty()) {
                        return it->second;
                    }
                }
                return null_;
            }

            void protocol_options::tsap_calling(const raw_type& val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLING_ID) {
                        it->second = val;
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, val.size()), raw_type(val.begin(), val.end())));
            }

            const raw_type& protocol_options::tsap_called() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLED_ID && !it->second.empty()) {
                        return it->second;
                    }
                }
                return null_;
            }

            void protocol_options::tsap_called(const raw_type& val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLED_ID) {
                        it->second = val;
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, val.size()), raw_type(val.begin(), val.end())));
            }

            std::size_t protocol_options::maxpdusize() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_MAXTPDU_SIZE && !it->second.empty()) {
                        return 128;
                    }
                }
                return 128;
            }

            void protocol_options::maxpdusize(std::size_t val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_MAXTPDU_SIZE) {
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_MAXTPDU_SIZE, 1), inttype_to_raw(static_cast<octet_type> ('\x80'))));
            }



            /////////////////////

            bool negotiate_prot8073_option(protocol_options& self, const protocol_options& dist, octet_type& error) {
                if (!self.tsap_called().empty() && self.tsap_called() != dist.tsap_called()) {
                    error = REJECT_REASON_ADDR;
                    return false;
                }
                self = protocol_options(dist.src_tsap(), self.src_tsap(),
                        less_tpdu(dist.pdusize(), self.pdusize()),
                        self.tsap_calling(), dist.tsap_calling());
                return true;
            }


            ////////////////////

            void generate_TKPTDU(raw_type& val) {
                raw_type hdr = TKPT_START;
                raw_back_insert(hdr, inttype_to_raw(endiancnv_copy(static_cast<int16_t> (val.size() + TKPT_LENGTH))));
                raw_front_insert(val, hdr);
            }

            raw_type generate_header(octet_type type, int16_t dst, int16_t src, const headarvarvalues& vars) {
                raw_type rslt;
                rslt.insert(rslt.end(), type);
                raw_back_insert(rslt, inttype_to_raw(dst));
                raw_back_insert(rslt, inttype_to_raw(src));
                rslt.insert(rslt.end(), '\x0');
                for (headarvarvalues::const_iterator it = vars.begin(); it != vars.end(); ++it) {
                    raw_back_insert(rslt, inttype_to_raw(it->first.first));
                    raw_back_insert(rslt, inttype_to_raw(static_cast<octet_type> (it->first.second)));
                    raw_back_insert(rslt, it->second);
                }
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                return rslt;
            }

            raw_type generate_header_TKPT_CR(const protocol_options& opt) {
                raw_type rslt;
                rslt.insert(rslt.end(), CR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(static_cast<int16_t> (0))));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                rslt.insert(rslt.end(), '\x0');
                if (opt.pdusize() != SIZENULL) {
                    rslt.insert(rslt.end(), VAR_TPDU_SIZE);
                    rslt.insert(rslt.end(), static_cast<octet_type> (1));
                    raw_back_insert(rslt, inttype_to_raw(tpdu_type_size(opt.pdusize())));
                }
                if (!opt.tsap_calling().empty()) {
                    rslt.insert(rslt.end(), VAR_TSAPCALLING_ID);
                    rslt.insert(rslt.end(), static_cast<octet_type> (opt.tsap_calling().size()));
                    raw_back_insert(rslt, opt.tsap_calling());
                }
                if (!opt.tsap_called().empty()) {
                    rslt.insert(rslt.end(), VAR_TSAPCALLED_ID);
                    rslt.insert(rslt.end(), static_cast<octet_type> (opt.tsap_called().size()));
                    raw_back_insert(rslt, opt.tsap_called());
                }
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            raw_type generate_header_TKPT_CC(const protocol_options& opt) {
                raw_type rslt;
                rslt.insert(rslt.end(), CC_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.dst_tsap())));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                rslt.insert(rslt.end(), '\x0');
                if (opt.pdusize() != SIZENULL) {
                    rslt.insert(rslt.end(), VAR_TPDU_SIZE);
                    rslt.insert(rslt.end(), static_cast<octet_type> (1));
                    raw_back_insert(rslt, inttype_to_raw(tpdu_type_size(opt.pdusize())));
                }
                if (!opt.tsap_calling().empty()) {
                    rslt.insert(rslt.end(), VAR_TSAPCALLING_ID);
                    rslt.insert(rslt.end(), static_cast<octet_type> (opt.tsap_calling().size()));
                    raw_back_insert(rslt, opt.tsap_calling());
                }
                if (!opt.tsap_called().empty()) {
                    rslt.insert(rslt.end(), VAR_TSAPCALLED_ID);
                    rslt.insert(rslt.end(), static_cast<octet_type> (opt.tsap_called().size()));
                    raw_back_insert(rslt, opt.tsap_called());
                }
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            raw_type generate_header_TKPT_DR(int16_t dst, int16_t src, octet_type rsn) {
                raw_type rslt;
                rslt.insert(rslt.end(), DR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(dst)));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(src)));
                rslt.insert(rslt.end(), rsn);
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            raw_type generate_header_TKPT_DC(int16_t dst, int16_t src) {
                raw_type rslt;
                rslt.insert(rslt.end(), DR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(dst)));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(src)));
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            raw_type generate_header_TKPT_ER(int16_t dst, const raw_type& errorreason, octet_type err) {
                raw_type rslt;
                rslt.insert(rslt.end(), ER_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(dst)));
                rslt.insert(rslt.end(), err);
                rslt.insert(rslt.end(), WRONG_TPDU);
                rslt.insert(rslt.end(), static_cast<octet_type> (errorreason.size()));
                raw_back_insert(rslt, raw_type(errorreason.begin(), errorreason.end()));
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }




            /////////////////////////////////////////////////////////////////////////////////////////

            receive_seq::receive_seq(const mutable_buffer& buff, std::size_t waitingsize, bool ef) :
            state_(waitingsize ? waitdata : waittkpt),
            size_(0),
            estimatesize_(waitingsize ? ((boost::asio::buffer_size(buff) < waitingsize) ? boost::asio::buffer_size(buff) : waitingsize) : TKPT_WITH_LI),
            datasize_(0),
            waitdatasize_(waitingsize),
            type_(waitingsize ? DT : NL),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            eof_(ef),
            tkpt_data(new data_type(TKPT_WITH_LI)),
            tkpt_buff_(boost::asio::buffer(*tkpt_data)),
            header_buff_(),
            userbuff_(buff) {
            }

            receive_seq::receive_seq() :
            state_(waittkpt),
            size_(0),
            estimatesize_(TKPT_WITH_LI),
            datasize_(0),
            waitdatasize_(0),
            type_(NL),
            class_option_(0),
            reject_reason_(0),
            errcode_(),
            eof_(true),
            tkpt_data(new data_type(TKPT_WITH_LI)),
            tkpt_buff_(boost::asio::buffer(*tkpt_data)),
            header_buff_(),
            userbuff_() {

            }

            mutable_buffer receive_seq::buffer() {
                switch (state_) {
                    case waittkpt: return tkpt_buff_ + size_;
                    case waitheader: return header_buff_ + size_;
                    case waitdata: return boost::asio::buffer(userbuff_ + datasize_, estimatesize_);
                    default: return mutable_buffer();
                }
                return mutable_buffer();
            }

            void receive_seq::put(std::size_t sz) {
                if (!sz) return;
                size_ += sz;
                if ((size_ + sz) >= estimatesize_) {
                    switch (state_) {
                        case waittkpt:
                        {
                            check_tkpt();
                            return;
                        }
                        case waitheader:
                        {
                            check_header();
                            return;
                        }
                        case waitdata:
                        {
                            waitdatasize_ -= ((sz > waitdatasize_) ? waitdatasize_ : sz);
                            datasize_ += sz;
                            if (eof_ || !boost::asio::buffer_size(userbuff_ + datasize_)) {
                                state_ = complete;
                            }
                            else {
                                state(waittkpt);
                                estimatesize_ = TKPT_WITH_LI;
                            }
                            return;
                        }
                        default:
                        {
                            errcode(ERROR__SEQ);
                            return;
                        }
                    }

                }
                if (state_ == waitdata) {
                    waitdatasize_ -= ((sz > waitdatasize_) ? waitdatasize_ : sz);
                    datasize_ += sz;
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

            boost::system::error_code receive_seq::check_tkpt() {
                mutable_buffer buff_ = tkpt_buff_;
                raw_type hdr = raw_type(boost::asio::buffer_cast<const raw_type::value_type*>(buff_), boost::asio::buffer_cast<const raw_type::value_type*>(buff_) + 2);
                if (hdr != TKPT_START) {
                    return errcode(ERROR__SEQ);
                }
                int16_t pdsz = endiancnv_copy<int16_t > (raw_type(boost::asio::buffer_cast<const char*>(buff_ + 2), boost::asio::buffer_cast<const char*>(buff_ + 2) + 2));
                if (pdsz < 0) {
                    return errcode(ERROR__EPROTO);
                }
                std::size_t li = static_cast<std::size_t> (*boost::asio::buffer_cast<unsigned char*>(buff_ + 4));
                if (!li)
                    return errcode(ERROR__EPROTO);
                state_ = waitheader;
                header_data = data_type_ptr(new data_type(li));
                header_buff_ = mutable_buffer(boost::asio::buffer(*header_data));
                size_ = 0;
                if (li > 128)
                    return errcode(ERROR__EPROTO);
                estimatesize_ = li;
                waitdatasize_ = pdsz - 5 - li;
                return boost::system::error_code();
            }

            boost::system::error_code receive_seq::check_header() {
                mutable_buffer buff_ = header_buff_;
                octet_type nativetp = *boost::asio::buffer_cast<octet_type*>(buff_);
                type_ = tpdu_type_from(((nativetp & '\xF0') == CR_TPDU_ID) ? (nativetp & '\xF0') : nativetp);
                /* запрос возможен и от др классов*/
                switch (type_) {
                    case DT:
                    {
                        octet_type eof = *boost::asio::buffer_cast<octet_type*>(buff_ + 1);
                        if (estimatesize_ != 2 || !((eof == TPDU_CONTINIUE) || (eof == TPDU_ENDED)))
                            return errcode(ERROR__EPROTO); /* !!должен быть только класс 0 см. 13.7*/
                        estimatesize_ = (boost::asio::buffer_size(userbuff_ + datasize_) < waitdatasize_) ? boost::asio::buffer_size(userbuff_ + datasize_) : waitdatasize_;
                        eof_ = (eof == TPDU_ENDED);
                        state(boost::asio::buffer_size(userbuff_) ? waitdata : complete);
                        return boost::system::error_code();
                    }
                    case CR:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ERROR__EPROTO); /* невозможно см. 13.3.1*/
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 1), boost::asio::buffer_cast<const char*>(buff_ + 1) + 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 3), boost::asio::buffer_cast<const char*>(buff_ + 3) + 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 5), boost::asio::buffer_cast<const char*>(buff_ + 5) + 1), class_option_);
                        headarvarvalues vars;
                        ;
                        if (!parse_vars(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 6), boost::asio::buffer_cast<const char*>(buff_ + 6)+ (estimatesize_ - 6)), vars))
                            return errcode(ERROR__EPROTO);
                        options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                        state(complete);
                        return boost::system::error_code();
                    }
                    case CC:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ERROR__EPROTO); /* невозможно см. 13.3.1*/
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 1), boost::asio::buffer_cast<const char*>(buff_ + 1) + 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 3), boost::asio::buffer_cast<const char*>(buff_ + 3) + 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 5), boost::asio::buffer_cast<const char*>(buff_ + 5) + 1), class_option_);
                        headarvarvalues vars;
                        if (!parse_vars(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 6), boost::asio::buffer_cast<const char*>(buff_ + 6) + (estimatesize_ - 6)), vars))
                            return errcode(ERROR__EPROTO);
                        options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                        state(complete);
                        return boost::system::error_code();
                    }
                    case DR:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ERROR__EPROTO);
                        ; /* невозможно см. 13.3.2*/
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 1), boost::asio::buffer_cast<const char*>(buff_ + 1) + 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 3), boost::asio::buffer_cast<const char*>(buff_ + 3) + 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        octet_type rsn = 0;
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 5), boost::asio::buffer_cast<const char*>(buff_ + 5) + 1), rsn);
                        reject_reason(rsn);
                        headarvarvalues vars;
                        if (!parse_vars(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 6), boost::asio::buffer_cast<const char*>(buff_ + 6) + (estimatesize_ - 6)), vars))
                            return errcode(ERROR__EPROTO);
                        ;
                        options_ = protocol_options(dst_tsap_, src_tsap_, vars);
                        state(complete);
                        return boost::system::error_code();
                    }
                    case ER:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 4)
                            return errcode(ERROR__EPROTO);
                        ; /* невозможно см. 13.3.1*/
                        int16_t dst_tsap_ = 0;
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 1), boost::asio::buffer_cast<const char*>(buff_ + 1) + 2), dst_tsap_);
                        raw_to_inttype(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 3), boost::asio::buffer_cast<const char*>(buff_ + 3) + 1), reject_reason_);
                        headarvarvalues vars;
                        if (!parse_vars(raw_type(boost::asio::buffer_cast<const char*>(buff_ + 4), boost::asio::buffer_cast<const char*>(buff_ + 4) + (estimatesize_ - 4)), vars))
                            return errcode(ERROR__EPROTO);
                        ;
                        state(complete);
                        return boost::system::error_code();

                    }
                    default:
                    {
                        errcode(ERROR__EPROTO);
                    }
                }
                return errcode(ERROR__EPROTO);
            }

            void receive_seq::reject_reason(octet_type val) {
                errcode_ = errorcode_by_reason(val);
                reject_reason_ = val;
            }

            boost::system::error_code receive_seq::errcode(const boost::system::error_code& err) {
                if (!errcode_ && err)
                    errcode_ = err;
                if (err)
                    state_ = error;
                return errcode_;
            }







            ///////////////////////////////////////////////////////////////////////////////////////

            void send_seq::constructCR(const protocol_options& opt) {
                buf_ = send_buffer_ptr(new sevice_send_buffer_implb(generate_header_TKPT_CR(opt)));
            }

            void send_seq::constructCC(const protocol_options& opt) {
                buf_ = send_buffer_ptr(new sevice_send_buffer_implb(generate_header_TKPT_CC(opt)));
            }

            void send_seq::constructER(int16_t dst, const raw_type& errorreason, octet_type err) {
                buf_ = send_buffer_ptr(new sevice_send_buffer_implb(generate_header_TKPT_ER(dst, errorreason, err)));
            }

            void send_seq::constructDR(int16_t dst, int16_t src, octet_type rsn) {
                buf_ = send_buffer_ptr(new sevice_send_buffer_implb(generate_header_TKPT_DR(dst, src, rsn)));
            }

        }
    }
}