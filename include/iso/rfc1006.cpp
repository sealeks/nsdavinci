/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iso/rfc1006.h>


namespace boost {
    namespace itu {
        namespace rfc1006impl {

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


            /// tpdu_size

            tpdu_size::tpdu_size() : preferred_(), basic_(), size_(0) {
                basic(TPDU_SIZE2048);
                preferred(PREFFERED_TPDU_SIZE);
            }

            tpdu_size::tpdu_size(octet_type bas) : preferred_(), basic_(), size_(0) {
                basic(bas);
            }

            tpdu_size::tpdu_size(const octet_sequnce& pref, octet_type bas) : preferred_(), basic_(), size_(0) {
                if (pref.empty() && pref.size() > 2) {
                    basic(bas);
                    preferred_ = 0;
                }
                else {
                    if (pref.size() == 1) {
                        preferred(static_cast<uint16_t> (pref[0]));
                    }
                    else {
                        uint16_t tmp;
                        if (raw_to_inttype(pref, tmp)) {
                            preferred(endiancnv_copy(tmp));
                        }
                        else {
                            basic(bas);
                            preferred_ = 0;
                        }
                    }
                }
            }

            std::size_t tpdu_size::size_from_octet(octet_type val) {
                switch (val) {
                    case TPDU_SIZE8192: return 8192;
                    case TPDU_SIZE4096: return 4096;
                    case TPDU_SIZE2048: return 2048;
                    case TPDU_SIZE1024: return 1024;
                    case TPDU_SIZE512: return 512;
                    case TPDU_SIZE256: return 256;
                    case TPDU_SIZE128: return 128;
                }
                return 128;
            }





            /////

            bool parse_vars(const octet_sequnce& data, headarvarvalues& vars) {
                vars.clear();
                std::size_t it = 0;
                while (it + 2 < data.size()) {
                    octet_type par = static_cast<octet_type> (data[it]);
                    std::size_t len = static_cast<std::size_t> (static_cast<uint8_t> (data[it + 1]));
                    if ((it + 2 + len) > data.size()) {
                        vars.clear();
                        return false;
                    }
                    vars.push_back(headarvarvalue(headarvar(par, len), octet_sequnce(data.begin() +(it + 2), data.begin() +(it + 2 + len))));
                    it += (2 + len);
                }
                return it == data.size();
            }


            ///   protocol_options

            protocol_options::protocol_options(int16_t dst, int16_t src, const tpdu_size& pdusz, const octet_sequnce& called, const octet_sequnce& calling) :
            dst_(dst), src_(src) {
                vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1), inttype_to_raw<octet_type > (pdusz.basic())));
                if (pdusz.preferred())
                    vars_.push_back(headarvarvalue(headarvar(VAR_MAXTPDU_SIZE, 2), inttype_to_raw<uint16_t > (pdusz.preferred())));
                if (!calling.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, calling.size()), calling));
                if (!called.empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, called.size()), called));
            }

            protocol_options::protocol_options(const transport_selector& tsl, const tpdu_size& pdusz) :
            dst_(0), src_(0) {
                vars_.push_back(headarvarvalue(headarvar(VAR_TPDU_SIZE, 1), inttype_to_raw(pdusz.basic())));
                if (pdusz.preferred())
                    vars_.push_back(headarvarvalue(headarvar(VAR_MAXTPDU_SIZE, 2), inttype_to_raw(pdusz.preferred())));
                if (!tsl.calling().empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, tsl.calling().size()), tsl.calling()));
                if (!tsl.called().empty()) vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, tsl.called().size()), tsl.called()));
            }

            tpdu_size protocol_options::pdusize() const {
                octet_type basic = TPDU_SIZE128;
                octet_sequnce preferred;
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TPDU_SIZE && !it->second.empty()) {
                        basic = static_cast<octet_type> (it->second[0]);
                    }
                    if (it->first.first == VAR_MAXTPDU_SIZE && !it->second.empty()) {
                        preferred = it->second;
                    }
                }
                return preferred.empty() ? tpdu_size(basic) : tpdu_size(preferred, basic);
            }

            const octet_sequnce& protocol_options::tsap_calling() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLING_ID && !it->second.empty()) {
                        return it->second;
                    }
                }
                return null_;
            }

            void protocol_options::tsap_calling(const octet_sequnce& val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLING_ID) {
                        it->second = val;
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLING_ID, val.size()), octet_sequnce(val.begin(), val.end())));
            }

            const octet_sequnce& protocol_options::tsap_called() const {
                for (headarvarvalues::const_reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLED_ID && !it->second.empty()) {
                        return it->second;
                    }
                }
                return null_;
            }

            void protocol_options::tsap_called(const octet_sequnce& val) {
                for (headarvarvalues::reverse_iterator it = vars_.rbegin(); it != vars_.rend(); ++it) {
                    if (it->first.first == VAR_TSAPCALLED_ID) {
                        it->second = val;
                        return;
                    }
                }
                vars_.push_back(headarvarvalue(headarvar(VAR_TSAPCALLED_ID, val.size()), octet_sequnce(val.begin(), val.end())));
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

            bool negotiate_rfc1006impl_option(protocol_options& self, const protocol_options& dist, octet_type& error) {
#ifndef CHECK_ISO_SELECTOR
                if (!self.tsap_called().empty() && self.tsap_called() != dist.tsap_called()) {
                    error = DR_REASON_ADDRESS;
                    return false;
                }
#endif                
                self = protocol_options(dist.src_tsap(), self.src_tsap(),
                        less_tpdu(dist.pdusize(), self.pdusize()),
                        self.tsap_calling(), dist.tsap_calling());
                return true;
            }


            ////////////////////

            void generate_TKPTDU(octet_sequnce& val) {
                octet_sequnce hdr = TKPT_START;
                raw_back_insert(hdr, inttype_to_raw(endiancnv_copy(static_cast<int16_t> (val.size() + TKPT_LENGTH))));
                raw_front_insert(val, hdr);
            }

            octet_sequnce generate_header_TKPT_CR(const protocol_options& opt, const tpdu_size& tpdusize) {
                octet_sequnce rslt;
                rslt.insert(rslt.end(), CR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(static_cast<int16_t> (0))));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                rslt.insert(rslt.end(), '\x0');

                rslt.insert(rslt.end(), VAR_TPDU_SIZE);
                rslt.insert(rslt.end(), static_cast<octet_type> (1));
                raw_back_insert(rslt, inttype_to_raw(tpdusize.basic()));

                if (tpdusize.preferred()) {
                    rslt.insert(rslt.end(), VAR_MAXTPDU_SIZE);
                    rslt.insert(rslt.end(), static_cast<octet_type> (2));
                    raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(tpdusize.preferred())));
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

            octet_sequnce generate_header_TKPT_CC(const protocol_options& opt, const tpdu_size& tpdusize) {
                octet_sequnce rslt;
                rslt.insert(rslt.end(), CC_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.dst_tsap())));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                rslt.insert(rslt.end(), '\x0');

                if (tpdusize.preferred()) {
                    rslt.insert(rslt.end(), VAR_MAXTPDU_SIZE);
                    rslt.insert(rslt.end(), static_cast<octet_type> (2));
                    raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(tpdusize.preferred())));
                }
                else {
                    rslt.insert(rslt.end(), VAR_TPDU_SIZE);
                    rslt.insert(rslt.end(), static_cast<octet_type> (1));
                    raw_back_insert(rslt, inttype_to_raw(tpdusize.basic()));
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

            octet_sequnce generate_header_TKPT_DC(const protocol_options& opt) {
                octet_sequnce rslt;
                rslt.insert(rslt.end(), DR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.dst_tsap())));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            octet_sequnce generate_header_TKPT_DR(const protocol_options& opt, octet_type rsn) {
                octet_sequnce rslt;
                rslt.insert(rslt.end(), DR_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.dst_tsap())));
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.src_tsap())));
                rslt.insert(rslt.end(), rsn);
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }

            octet_sequnce generate_header_TKPT_ER(const protocol_options& opt, octet_type err, const octet_sequnce& errorseq) {
                octet_sequnce rslt;
                rslt.insert(rslt.end(), ER_TPDU_ID);
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(opt.dst_tsap())));
                rslt.insert(rslt.end(), err);
                rslt.insert(rslt.end(), ERT_PARAM_ID);
                rslt.insert(rslt.end(), static_cast<octet_type> (errorseq.size()));
                raw_back_insert(rslt, octet_sequnce(errorseq.begin(), errorseq.end()));
                std::size_t sz = rslt.size();
                raw_front_insert(rslt, inttype_to_raw(static_cast<octet_type> (sz)));
                generate_TKPTDU(rslt);
                return rslt;
            }




            /////////////////////////////////////////////////////////////////////////////////////////

            receiver::receiver(const mutable_buffer& buff, std::size_t waitingsize, bool ef) :
            state_(waitingsize ? waitdata : waittkpt),
            size_(0),
            estimatesize_(waitingsize ? ((boost::asio::buffer_size(buff) < waitingsize) ? boost::asio::buffer_size(buff) : waitingsize) : TKPT_WITH_LI),
            datasize_(0),
            waitdatasize_(waitingsize),
            type_(waitingsize ? DT : NL),
            errcode_(),
            eof_(ef),
            tkpt_data(new octet_sequnce(TKPT_WITH_LI)),
            tkpt_buff_(boost::asio::buffer(*tkpt_data)),
            header_buff_(),
            userbuff_(buff) {
            }

            receiver::receiver() :
            state_(waittkpt),
            size_(0),
            estimatesize_(TKPT_WITH_LI),
            datasize_(0),
            waitdatasize_(0),
            type_(NL),
            errcode_(),
            eof_(true),
            tkpt_data(new octet_sequnce(TKPT_WITH_LI)),
            tkpt_buff_(boost::asio::buffer(*tkpt_data)),
            header_buff_(),
            userbuff_() {

            }

            mutable_buffer receiver::buffer() {
                switch (state_) {
                    case waittkpt: return tkpt_buff_ + size_;
                    case waitheader: return header_buff_ + size_;
                    case waitdata: return boost::asio::buffer(userbuff_ + datasize_, estimatesize_);
                    default: return mutable_buffer();
                }
                return mutable_buffer();
            }

            void receiver::put(std::size_t sz) {
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
                            errcode(ER_PROTOCOL);
                            return;
                        }
                    }

                }
                if (state_ == waitdata) {
                    waitdatasize_ -= ((sz > waitdatasize_) ? waitdatasize_ : sz);
                    datasize_ += sz;
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

            error_code receiver::check_tkpt() {
                mutable_buffer buff_ = tkpt_buff_;
                octet_sequnce hdr = buffer_to_raw(buff_, 0, 2);
                if (hdr != TKPT_START) {
                    return errcode(ER_PROTOCOL);
                }
                int16_t pdsz = endiancnv_copy<int16_t > (buffer_to_raw(buff_, 2, 2));
                if (pdsz < 0) {
                    return errcode(ER_PROTOCOL);
                }
                std::size_t li = static_cast<std::size_t> (*boost::asio::buffer_cast<uint8_t*>(buff_ + 4));
                if (!li)
                    return errcode(ER_PROTOCOL);
                state_ = waitheader;
                if (li > 128)
                    return errcode(ER_PROTOCOL);
                header_data = octet_sequnce_ptr(new octet_sequnce(li));
                header_buff_ = mutable_buffer(boost::asio::buffer(*header_data));
                size_ = 0;
                estimatesize_ = li;
                waitdatasize_ = pdsz - TKPT_WITH_LI - li;
                return error_code();
            }

            error_code receiver::check_header() {
                mutable_buffer buff_ = header_buff_;
                octet_type nativetp = *boost::asio::buffer_cast<octet_type*>(buff_);
                type_ = tpdu_type_from(((nativetp & '\xF0') == CR_TPDU_ID) ? (nativetp & '\xF0') : nativetp);
                switch (type_) {
                    case DT:
                    {
                        octet_type eof = *boost::asio::buffer_cast<octet_type*>(buff_ + 1);
                        if (estimatesize_ != 2 || !((eof == TPDU_CONTINIUE) || (eof == TPDU_ENDED)))
                            return errcode(ER_PROTOCOL);
                        estimatesize_ = (boost::asio::buffer_size(userbuff_ + datasize_) < waitdatasize_) ?
                                boost::asio::buffer_size(userbuff_ + datasize_) : waitdatasize_;
                        eof_ = (eof == TPDU_ENDED);
                        state(boost::asio::buffer_size(userbuff_) ? waitdata : complete);
                        return error_code();
                    }
                    case CR:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ER_PROTOCOL);
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        octet_type class_option;
                        raw_to_inttype(buffer_to_raw(buff_, 1, 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 3, 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 5, 1), class_option);
                        headarvarvalues vars;
                        if (!parse_vars(buffer_to_raw(buff_, 6, (estimatesize_ - 6)), vars))
                            return errcode(ER_PROTOCOL);
                        options_ = protocol_options_ptr(new protocol_options(dst_tsap_, src_tsap_, vars));
                        state(complete);
                        return error_code();
                    }
                    case CC:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ER_PROTOCOL);
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        octet_type class_option;
                        raw_to_inttype(buffer_to_raw(buff_, 1, 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 3, 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 5, 1), class_option);
                        headarvarvalues vars;
                        if (!parse_vars(buffer_to_raw(buff_, 6, (estimatesize_ - 6)), vars))
                            return errcode(ER_PROTOCOL);
                        options_ = protocol_options_ptr(new protocol_options(dst_tsap_, src_tsap_, vars));
                        state(complete);
                        return error_code();
                    }
                    case DR:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 6)
                            return errcode(ER_PROTOCOL);
                        int16_t dst_tsap_ = 0;
                        int16_t src_tsap_ = 0;
                        raw_to_inttype(buffer_to_raw(buff_, 1, 2), dst_tsap_);
                        dst_tsap_ = endiancnv_copy(dst_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 3, 2), src_tsap_);
                        src_tsap_ = endiancnv_copy(src_tsap_);
                        octet_type rsn = 0;
                        raw_to_inttype(buffer_to_raw(buff_, 5, 1), rsn);
                        reject_reason(rsn);
                        headarvarvalues vars;
                        if (!parse_vars(buffer_to_raw(buff_, 6, (estimatesize_ - 6)), vars))
                            return errcode(ER_PROTOCOL);
                        options_ = protocol_options_ptr(new protocol_options(dst_tsap_, src_tsap_, vars));
                        state(complete);
                        return error_code();
                    }
                    case ER:
                    {
                        waitdatasize_ = 0;
                        if (estimatesize_ < 4)
                            return errcode(ER_PROTOCOL);
                        int16_t dst_tsap_ = 0;
                        octet_type reject_rsn = 0;
                        raw_to_inttype(buffer_to_raw(buff_, 1, 2), dst_tsap_);
                        raw_to_inttype(buffer_to_raw(buff_, 3, 1), reject_rsn);
                        headarvarvalues vars;
                        if (!parse_vars(buffer_to_raw(buff_, 4, (estimatesize_ - 4)), vars))
                            state(complete);
                        return error_code();

                    }
                    default:
                    {
                        errcode(ER_PROTOCOL);
                    }
                }
                return errcode(ER_PROTOCOL);
            }

            void receiver::reject_reason(octet_type val) {
                errcode_ = errorcode_by_reason(val);
            }

            error_code receiver::errcode(const error_code& err) {
                if (!errcode_ && err)
                    errcode_ = err;
                if (err)
                    state_ = error;
                return errcode_;
            }



            ///////////////////////////////////////////////////////////////////////////////////////                 

            class service_sender_sequences : public basic_sender_sequences {
            public:

                service_sender_sequences(const octet_sequnce& send) : basic_sender_sequences(), send_(send) {
                    buff().push_back(send_.empty() ? const_buffer() : const_buffer(&send_.front(), send_.size()));
                }

            private:
                octet_sequnce send_;
            };



            ///////////////////////////////////////////////////////////////////////////////////////

            sender::sender(tpdu_type type, const protocol_options& opt, octet_type reason_or_error, const octet_sequnce& errorseq) :
            type_(type) {
                switch (type_) {
                    case DR:
                    {
                        constructDR(opt, reason_or_error);
                        break;
                    }
                    case ER:
                    {
                        constructER(opt, reason_or_error, errorseq);
                        break;
                    }
                    default:
                    {
                    }
                }
            }

            sender::sender(tpdu_type type, const protocol_options& opt, const tpdu_size& tpdusize) :
            type_(type) {
                switch (type_) {
                    case CR:
                    {
                        constructCR(opt, tpdusize);
                        break;
                    }
                    case CC:
                    {
                        constructCC(opt, tpdusize);
                        break;
                    }
                }
            }

            void sender::constructCR(const protocol_options& opt, const tpdu_size& tpdusize) {
                buf_ = sender_sequnces_ptr(new service_sender_sequences(generate_header_TKPT_CR(opt, tpdusize)));
            }

            void sender::constructCC(const protocol_options& opt, const tpdu_size& tpdusize) {
                buf_ = sender_sequnces_ptr(new service_sender_sequences(generate_header_TKPT_CC(opt, tpdusize)));
            }

            void sender::constructDR(const protocol_options& opt, octet_type rsn) {
                buf_ = sender_sequnces_ptr(new service_sender_sequences(generate_header_TKPT_DR(opt, rsn)));
            }

            void sender::constructER(const protocol_options& opt, octet_type errtype, const octet_sequnce& errorseq) {
                buf_ = sender_sequnces_ptr(new service_sender_sequences(generate_header_TKPT_ER(opt, errtype, errorseq)));
            }



        }
    }
}