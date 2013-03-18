/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef RFC1006_H
#define RFC1006_H

#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <iso/iso.h>
#include <boost/asio/detail/push_options.hpp>


namespace boost {
    namespace itu {
        namespace rfc1006impl {

            // ref X224 = ITU-T Rec. X.224(1995 E)


            using boost::asio::basic_socket;
            using boost::asio::basic_socket_acceptor;

            typedef boost::asio::socket_base::message_flags message_flags;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   rfc1006 utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                  


            // TPDU code *ref X224  13.1 Table 8   only class 0 implemented ( over rfc1006 )
            const octet_type CR_TPDU_ID = '\xE0'; //Connection request   !!xxxx - out class 0
            const octet_type CC_TPDU_ID = '\xD0'; //Connection confirm   !!xxxx - out class 0
            const octet_type DR_TPDU_ID = '\x80'; //Disconnection request 
            const octet_type DC_TPDU_ID = '\xC0'; //Disconnection  confirm                              !!not used here
            const octet_type DT_TPDU_ID = '\xF0'; //Data !!y - out class 0
            const octet_type ED_TPDU_ID = '\x10'; //Expedited data !!not use here impl                  !!not used here
            const octet_type DA_TPDU_ID = '\x60'; //Data acknowledgement !!not use here impl
            const octet_type EA_TPDU_ID = '\x20'; //Expedited data acknowledgement                      !!not used here
            const octet_type RJ_TPDU_ID = '\x50'; //Reject                                              !!not used here
            const octet_type ER_TPDU_ID = '\x70'; //Error


            // see Disconnection  REASON CODE  iso.h

            // Error REASON CODE *ref X224  13.12.3 c)   
            const octet_type ERT_REASON_NODEF = '\x0'; // Reason not specified    - all ER_PROTOCOL
            const octet_type ERT_REASON_PARAM_CODE = '\x1'; // Invalid parameter code
            const octet_type ERT_REASON_TPDU_TYPE = '\x2'; // Invalid TPDU type
            const octet_type ERT_REASON_PARAM_VALUE = '\x3'; // Invalid parameter value

            // Error REASON CODE *ref X224  13.12.4
            const octet_type ERT_PARAM_ID = '\xC1'; //Parameter code:        

            // VAR ID  *ref X224  13.3.4
            const octet_type VAR_TSAPCALLING_ID = '\xC1'; //calling Transport-Selector *ref X224 13.3.4 a)
            const octet_type VAR_TSAPCALLED_ID = '\xC2'; //called Transport-Selector *ref X224 13.3.4 a)
            const octet_type VAR_TPDU_SIZE = '\xC0'; //TPDU size *ref X224 13.3.4 b)
            const octet_type VAR_MAXTPDU_SIZE = '\xF0'; // Preferred maximum TPDU size *ref X224 13.3.4 c)

            // EOT *ref X224  13.7.3  d)
            const octet_type TPDU_ENDED = '\x80';
            const octet_type TPDU_CONTINIUE = '\x0';

            enum tpdu_type {
                NL = 0,
                CR = CR_TPDU_ID,
                CC = CC_TPDU_ID,
                DR = DR_TPDU_ID,
                DC = DC_TPDU_ID,
                DT = DT_TPDU_ID,
                ED = ED_TPDU_ID,
                DA = DA_TPDU_ID,
                EA = EA_TPDU_ID,
                RJ = RJ_TPDU_ID,
                ER = ER_TPDU_ID
            };

            inline octet_type tpdu_type_primitive(tpdu_type val) {
                return static_cast<octet_type> (val);
            }

            tpdu_type tpdu_type_from(octet_type val);

            inline octet_type tpdu_type_size(tpdu_size val) {
                return static_cast<octet_type> (val);
            }

            inline tpdu_size less_tpdu(const tpdu_size& left, const tpdu_size& right) {
                if (left == right && right == SIZENULL) return SIZE2048;
                if (right == SIZENULL) return left;
                if (left == SIZENULL) return right;
                return (tpdu_type_size(left) < tpdu_type_size(right)) ? left : right;
            }

            std::size_t tpdu_byte_size(tpdu_size val);

            tpdu_size tpdu_size_frombyte(octet_type val);


            size_t getPDUsize(octet_type sz);

            void generate_TKPTDU(octet_sequnce& val);

            typedef std::pair<octet_type, std::size_t> headarvar;

            typedef std::pair<headarvar, octet_sequnce> headarvarvalue;
            typedef std::vector<headarvarvalue> headarvarvalues;


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 protocol_options   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

            struct protocol_options {

                protocol_options() :
                dst_(0), src_(0) {
                }

                protocol_options(int16_t dst, int16_t src,
                        const headarvarvalues& vars = headarvarvalues()) :
                dst_(dst), src_(src), vars_(vars) {
                }

                protocol_options(int16_t dst, int16_t src, tpdu_size pdusize,
                        const octet_sequnce& called = octet_sequnce(), const octet_sequnce& calling = octet_sequnce());

                int16_t dst_tsap() const {
                    return dst_;
                }

                void dst_tsap(int16_t val) {
                    dst_ = val;
                }

                int16_t src_tsap() const {
                    return src_;
                }

                void src_tsap(int16_t val) {
                    src_ = val;
                }

                tpdu_size pdusize() const;

                void pdusize(tpdu_size val);

                const octet_sequnce & tsap_calling() const;

                void tsap_calling(const octet_sequnce & val);

                const octet_sequnce & tsap_called() const;

                void tsap_called(const octet_sequnce & val);

                std::size_t maxpdusize() const;

                void maxpdusize(std::size_t val);

            private:
                int16_t dst_;
                int16_t src_;
                headarvarvalues vars_;
                octet_sequnce null_;
            };


            const protocol_options NULL_PROTOCOL_OPTION = protocol_options();



            bool negotiate_rfc1006impl_option(protocol_options& self, const protocol_options& dist, octet_type& error);

            bool parse_vars(const octet_sequnce& str, headarvarvalues& vars);

            octet_sequnce generate_header(octet_type type, int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues());

            octet_sequnce generate_header_TKPT_CR(const protocol_options& opt);

            octet_sequnce generate_header_TKPT_CC(const protocol_options& opt);

            octet_sequnce generate_header_TKPT_DR(int16_t dst, int16_t src, octet_type rsn);

            octet_sequnce generate_header_TKPT_DC(int16_t dst, int16_t src);

            octet_sequnce generate_header_TKPT_ER(int16_t dst, const octet_sequnce& errorseq = octet_sequnce(), octet_type err = 0);



            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 data_sender_sequences   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    


            // see RFC1006
            const octet_type TKPT_STARTar[] = {'\x3', '\x0'};
            const octet_sequnce TKPT_START = octet_sequnce(TKPT_STARTar, TKPT_STARTar + 2);

            const octet_sequnce::size_type DT_SEND_BUFF_HEADER = 7;

            const std::size_t TKPT_LENGTH = 4;

            template <typename ConstBufferSequence>
            class data_sender_sequences : public basic_sender_sequences {
            public:

                data_sender_sequences(const ConstBufferSequence& bf, tpdu_size pdusize) :
                basic_sender_sequences(), headercontinue_(), headereof_() {
                    construct(bf, pdusize);

                }

                void construct(const ConstBufferSequence& bf, tpdu_size pdusize) {
                    std::size_t pdusz = tpdu_byte_size(pdusize);
                    if (!pdusz) pdusz = 2048;
                    pdusz -= 3;

                    headercontinue_.reserve(DT_SEND_BUFF_HEADER);
                    uint16_t normalsz = endiancnv_copy(static_cast<uint16_t> (pdusz + 7));
                    headercontinue_ = TKPT_START;
                    raw_back_insert(headercontinue_, inttype_to_raw(normalsz));
                    headercontinue_.insert(headercontinue_.end(), '\x2');
                    headercontinue_.insert(headercontinue_.end(), DT_TPDU_ID);
                    headercontinue_.insert(headercontinue_.end(), TPDU_CONTINIUE);

                    typedef typename ConstBufferSequence::const_iterator constbuffseq_iterator;
                    typedef typename ConstBufferSequence::value_type constbuffseq_value;

                    constbuffseq_iterator it = bf.begin();
                    constbuffseq_iterator end = bf.end();
                    constbuffseq_iterator pend = end;
                    if (it != end)
                        --pend;

                    constbuffseq_value val;

                    const_sequences tmp;
                    std::size_t tmpsize = 0;

                    bool ended = (it == end) || (it == pend);
                    while (it != end) {
                        val = *it;
                        do {
                            if ((boost::asio::buffer_size(val) + tmpsize) > pdusz) {
                                buff().push_back(const_buffer(&headercontinue_.front(), headercontinue_.size()));
                                if (!tmp.empty())
                                    std::copy(tmp.begin(), tmp.end(), std::back_inserter(buff()));
                                tmp.clear();
                                buff().push_back(boost::asio::buffer(val, pdusz - tmpsize));
                                val = val + (pdusz - tmpsize);
                                tmpsize = 0;
                            }
                            else {
                                if (ended) {
                                    uint16_t eofsz = endiancnv_copy(static_cast<uint16_t> (boost::asio::buffer_size(val) + boost::asio::buffer_size(tmp) + 7));
                                    headereof_.reserve(DT_SEND_BUFF_HEADER);
                                    headereof_ = TKPT_START;
                                    raw_back_insert(headereof_, inttype_to_raw(eofsz));
                                    headereof_ .insert(headereof_ .end(), '\x2');
                                    headereof_ .insert(headereof_ .end(), DT_TPDU_ID);
                                    headereof_ .insert(headereof_ .end(), TPDU_ENDED);
                                    buff().push_back(const_buffer(&headereof_.front(), headereof_.size()));
                                    if (!tmp.empty())
                                        std::copy(tmp.begin(), tmp.end(), std::back_inserter(buff()));
                                    tmp.clear();
                                    buff().push_back(const_buffer(val));
                                    val = val + pdusz;
                                    tmpsize = 0;
                                }
                                else {
                                    tmp.push_back(const_buffer(val));
                                    tmpsize += boost::asio::buffer_size(val);
                                    val = val + pdusz;
                                }
                            }
                        }
                        while (boost::asio::buffer_size(val));
                        ++it;
                        ended = (it == end) || (it == pend);
                    }
                }

            private:

                octet_sequnce headercontinue_;
                octet_sequnce headereof_;
            };

            template<>
            class data_sender_sequences<const_sequences> : public basic_sender_sequences {
            public:

                data_sender_sequences<const_sequences>(const const_sequences& bf, tpdu_size pdusize) :
                basic_sender_sequences(const_cast<const_sequences&> (bf)), headercontinue_(), headereof_() {
                    construct(pdusize);
                }

                void construct(tpdu_size pdusize) {
                    if (buff().empty()) return;
                    std::size_t pdusz = tpdu_byte_size(pdusize);
                    if (!pdusz) pdusz = 2048;
                    pdusz -= 3;
                    std::size_t tmpsize = 0;
                    std::size_t buffsize = 0;
                    const_sequences::iterator it = buff().begin();
                    const_sequences::iterator insert_pos = it;

                    while (it != buff().end()) {
                        buffsize = boost::asio::buffer_size(*it);
                        if ((buffsize + tmpsize) >= pdusz) {

                            if (headercontinue_.empty()) {
                                uint16_t normalsz = endiancnv_copy(static_cast<uint16_t> (pdusz + 7));
                                headercontinue_.reserve(DT_SEND_BUFF_HEADER);
                                headercontinue_ = TKPT_START;
                                raw_back_insert(headercontinue_, inttype_to_raw(normalsz));
                                headercontinue_.insert(headercontinue_.end(), '\x2');
                                headercontinue_.insert(headercontinue_.end(), DT_TPDU_ID);
                                headercontinue_.insert(headercontinue_.end(), TPDU_CONTINIUE);
                            }

                            if ((buffsize + tmpsize) == pdusz) {
                                buff().insert(insert_pos, const_buffer(static_cast<const octet_type*> (&headercontinue_[0]), headercontinue_.size()));
                                insert_pos = it;
                                ++insert_pos;
                                tmpsize = 0;
                            }
                            else {
                                const_buffer firstpart = boost::asio::buffer(*it, (pdusz - tmpsize));
                                const_buffer secondpart = (*it)+(pdusz - tmpsize);
                                buff().insert(insert_pos, const_buffer(static_cast<const octet_type*> (&headercontinue_[0]), headercontinue_.size()));
                                insert_pos = buff().insert(buff().erase(it), secondpart);
                                it = buff().insert(insert_pos, firstpart);
                                tmpsize = 0;
                            }
                        }
                        else
                            tmpsize += buffsize;
                        ++it;
                    }
                    if (tmpsize) {
                        headereof_.reserve(DT_SEND_BUFF_HEADER);
                        headereof_ = TKPT_START;
                        uint16_t eofsz = endiancnv_copy(static_cast<uint16_t> (tmpsize + 7));
                        raw_back_insert(headereof_, inttype_to_raw(eofsz));
                        headereof_ .insert(headereof_ .end(), '\x2');
                        headereof_ .insert(headereof_ .end(), DT_TPDU_ID);
                        headereof_ .insert(headereof_ .end(), TPDU_ENDED);
                        buff().insert(insert_pos, const_buffer(static_cast<const octet_type*> (&headereof_[0]), headereof_.size()));
                    }
                }

            private:

                octet_sequnce headercontinue_;
                octet_sequnce headereof_;

            };





            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 sender   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                  

            class sender {
            public:

                sender(tpdu_type type) :
                type_(type) {
                }

                sender(const protocol_options& opt) :
                type_(CR) {
                    constructCR(opt);
                }

                sender(int16_t dst, const protocol_options& opt) :
                type_(CC) {
                    constructCC(opt);
                }

                sender(int16_t dst, const octet_sequnce& errorreason, octet_type err) :
                type_(ER) {
                    constructER(dst, errorreason, err);
                }

                sender(int16_t dst, int16_t src, octet_type rsn) :
                type_(DR) {
                    constructDR(dst, src, rsn);
                }

                virtual ~sender() {
                }

                bool ready() const {
                    return (!buf_) || (buf_->ready());
                }

                const const_sequences& pop() {
                    return buf_ ? buf_->pop() : NULL_CONST_SEQUENCE;
                }

                std::size_t size(std::size_t sz) {
                    return ready() ? 0 : buf_->size(sz);
                }

                std::size_t receive_size() const {
                    return ready() ? 0 : buf_->receive_size();
                }

                tpdu_type type() const {
                    return type_;
                }




            protected:


                void constructCR(const protocol_options& opt);

                void constructCC(const protocol_options& opt);

                void constructER(int16_t dst, const octet_sequnce& errorreason, octet_type err);

                void constructDR(int16_t dst, int16_t src, octet_type rsn);

                tpdu_type type_;
                sender_sequnces_ptr buf_;
            };




            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 data_sender   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

            template <typename ConstBufferSequence >
            class data_sender : public sender {
            public:

                data_sender(const ConstBufferSequence& buff, tpdu_size pdusize) : sender(DT) {
                    constructDT(buff, pdusize);
                }

            protected:

                void constructDT(const ConstBufferSequence& buff, tpdu_size pdusize) {
                    buf_ = sender_sequnces_ptr(new data_sender_sequences<ConstBufferSequence > (buff, pdusize));
                }

            };


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 receiver   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

            const std::size_t TKPT_WITH_LI = 5;

            class receiver {
            public:

                typedef boost::shared_ptr< protocol_options > protocol_options_ptr;

                enum operation_state {
                    waittkpt,
                    waitheader,
                    waitdata,
                    complete,
                    error
                };

                receiver(const mutable_buffer& buff, std::size_t waitingsize, bool ef);

                receiver();

                mutable_buffer buffer();

                void put(std::size_t sz);

                bool ready() const {
                    return (state_ == error || state_ == complete);
                }

                operation_state state() const {
                    return state_;
                }

                tpdu_type type() const {
                    return type_;
                }

                bool eof() const {
                    return eof_;
                }

                std::size_t datasize() const {
                    return datasize_;
                }

                std::size_t waitdatasize() const {
                    return waitdatasize_;
                }

                const protocol_options& options() const {
                    return options_ ? *options_ : NULL_PROTOCOL_OPTION;
                }

                error_code errcode() const {
                    return errcode_ ? errcode_ : ER_REFUSE;
                }


            private:

                operation_state state(operation_state val);

                error_code errcode(const error_code& err);

                void reject_reason(octet_type val);

                error_code check_tkpt();

                error_code check_header();

                operation_state state_;
                std::size_t size_;
                std::size_t estimatesize_;
                std::size_t datasize_;
                std::size_t waitdatasize_;
                tpdu_type type_;
                error_code errcode_;
                bool eof_;
                octet_sequnce_ptr tkpt_data;
                octet_sequnce_ptr header_data;
                mutable_buffer tkpt_buff_;
                mutable_buffer header_buff_;
                mutable_buffer userbuff_;
                protocol_options_ptr options_;
            };






            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rf1006 stream_socket  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

            class stream_socket : public boost::asio::basic_stream_socket<boost::asio::ip::tcp > {
                typedef boost::shared_ptr<receiver> receiver_ptr;
                typedef boost::shared_ptr<sender> sender_ptr;

            public:


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

                explicit stream_socket(boost::asio::io_service& io_service, const transport_selector& tsel = transport_selector())
                : boost::asio::basic_stream_socket<boost::asio::ip::tcp>(io_service), pdusize_(tsel.pdusize()),
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
                }

                stream_socket(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const transport_selector& tsel = transport_selector())
                : boost::asio::basic_stream_socket<boost::asio::ip::tcp >(io_service, endpoint), pdusize_(tsel.pdusize()),
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
                }

                boost::asio::basic_stream_socket<boost::asio::ip::tcp >& basic_cast() {
                    return *this;
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Available  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                std::size_t available() const {
                    error_code ec;
                    std::size_t s = available(ec);
                    boost::asio::detail::throw_error(ec, "available");
                    return s;
                }

                std::size_t available(error_code& ec) const {
                    std::size_t s = get_service().available(get_implementation(), ec);
                    if (ec) return 0;
                    return waiting_data_size_ < s ? waiting_data_size_ : s;
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Data indication  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                bool input_empty() const {
                    return (!waiting_data_size_) && (eof_state_);
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Colose operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void close() {
                    error_code ecc;
                    get_service().close(get_implementation(), ecc);
                    boost::asio::detail::throw_error(ecc, "close");
                }

                boost::system::error_code close(boost::system::error_code& ec) {
                    get_service().close(get_implementation(), ec);
                    return ec;
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Connnect operations  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void connect(const endpoint_type& peer_endpoint) {

                    error_code ec;
                    connect(peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "connect");
                }

                error_code connect(const endpoint_type& peer_endpoint,
                        error_code& ec) {
                    if (!is_open()) {
                        if (get_service().open(get_implementation(),
                                peer_endpoint.protocol(), ec)) {
                            return ec;
                        }
                    }
                    return connect_impl(peer_endpoint, ec);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ConnectHandler>
                class connect_operation {

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    connect_operation(stream_socket* socket, ConnectHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(request),
                    sender_(sender_ptr(new sender(socket->transport_option()))),
                    receiver_(new receiver()) {
                    }

                    void run(const error_code& ec) {
                        operator()(ec);
                    }

                    void operator()(const error_code& ec) {
                        if (!ec)
                            operator()(ec, 0);
                        else
                            handler_(ec);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), sender_->pop(), 0, *this);
                                        return;
                                    }
                                    else {
                                        state(response);
                                        operator()(ec, 0);
                                        return;
                                    }
                                }
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receiver_->buffer()), 0, *this);
                                        return;
                                    }
                                    finish(ec);

                                    return;
                                }
                            }
                        }
                        handler_(ec);
                    }



                private:

                    void finish(const error_code& ec) {
                        if (receiver_->state() == receiver::complete) {
                            switch (receiver_->type()) {
                                case CC:
                                {
                                    socket_->negotiate_transport_option(receiver_->options());
                                    handler_(ec);
                                    return;
                                }
                                case ER:
                                {
                                    socket_->self_shutdown();
                                    handler_(ER_PROTOCOL);
                                    return;
                                }
                                case DR:
                                {
                                    socket_->self_shutdown();
                                    handler_(receiver_->errcode());
                                    return;
                                }
                            }
                        }
                        socket_->self_shutdown();
                        handler_(ER_PROTOCOL);
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket* socket_;
                    ConnectHandler handler_;
                    stateconnection state_;
                    sender_ptr sender_;
                    receiver_ptr receiver_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ConnectHandler>
                void async_connect(const endpoint_type& peer_endpoint,
                        BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {
                    BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

                    if (!is_open()) {
                        error_code ec;
                        const protocol_type protocol = peer_endpoint.protocol();
                        if (get_service().open(get_implementation(), protocol, ec)) {
                            get_io_service().post(
                                    boost::asio::detail::bind_handler(
                                    BOOST_ASIO_MOVE_CAST(ConnectHandler)(handler), ec));
                            return;
                        }
                    }

                    get_service().async_connect(get_implementation(), peer_endpoint, boost::bind(&connect_operation<ConnectHandler>::run,
                            connect_operation<ConnectHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));

                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Release operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void release(octet_type rsn = 0) {
                    error_code ec;
                    release(ec, rsn);
                    boost::asio::detail::throw_error(ec, "release");
                }

                error_code release(error_code& ec, octet_type rsn = DR_REASON_NORM) {
                    return release_impl(ec, rsn);
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ReleaseHandler>
                class release_operation {
                public:

                    release_operation(stream_socket* socket, ReleaseHandler handler, octet_type rsn) :
                    socket_(socket),
                    handler_(handler),
                    sender_(sender_ptr(new sender(socket->transport_option().dst_tsap(), socket->transport_option().src_tsap(), rsn))) {
                    }

                    void run() {
                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            sender_->size(bytes_transferred);
                            if (!sender_->ready()) {
                                socket_->get_service().async_send(socket_->get_implementation(), sender_->pop(), 0, *this);
                                return;
                            }
                        }
                        self_shutdown();
                        handler_(ec);
                    }


                private:
                    stream_socket* socket_;
                    ReleaseHandler handler_;
                    sender_ptr sender_;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ReleaseHandler>
                void asyn_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                        octet_type rsn = 0) {
                    BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_operation<ReleaseHandler>::run,
                                release_operation<ReleaseHandler > (const_cast<stream_socket*> (this), handler, rsn)));
                    }
                    else
                        handler(ER_REFUSE);
                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void check_accept(int16_t src) {
                    error_code ec;
                    boost::asio::detail::throw_error(ec, "connect");
                }

                error_code check_accept(int16_t src, error_code& ec) {
                    return check_accept_imp(src, ec);
                }


            private:

                template <typename CheckAcceptHandler>
                class accept_operation {

                    enum stateconnection {
                        wait,
                        send,
                        refuse
                    };

                public:

                    accept_operation(stream_socket* socket, CheckAcceptHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(wait),
                    sender_(),
                    tpdusize(socket->transport_option().pdusize()),
                    receiver_(new receiver()) {
                    }

                    void run() {

                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case wait:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receiver_->buffer()), 0, *this);
                                        return;
                                    }
                                    parse_response(ec);
                                    return;
                                }
                                case send:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), sender_->pop(), 0, *this);
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case refuse:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), sender_->pop(), 0, *this);
                                        return;
                                    }
                                    socket_->self_shutdown();
                                    handler_(ER_OUTDOMAIN);
                                    return;
                                }
                            }
                        }
                        socket_->self_shutdown();
                        handler_(ec);
                    }


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                private:

                    void parse_response(const error_code& ec) {
                        if (receiver_->type() != CR || receiver_->state() != receiver::complete) {
                            socket_->self_shutdown();
                            handler_(ER_PROTOCOL);
                            return;
                        }
                        protocol_options options_ = socket_->transport_option();
                        octet_type error_accept = 0;
                        if (!negotiate_rfc1006impl_option(options_, receiver_->options(), error_accept)) {
                            sender_ = sender_ptr(new sender(receiver_->options().src_tsap(), options_.src_tsap(), error_accept));
                            state(refuse);
                            operator()(ec, 0);
                            return;
                        }
                        tpdusize = options_.pdusize();
                        sender_ = sender_ptr(new sender(1, options_));
                        state(send);
                        operator()(ec, 0);
                    }

                    void finish(const error_code& ec) {
                        socket_->negotiate_transport_option(receiver_->options());
                        handler_(ec);
                    }

                    void state(stateconnection st) {

                        if (state_ != st)
                            state_ = st;
                    }



                    stream_socket* socket_;
                    CheckAcceptHandler handler_;
                    stateconnection state_;
                    sender_ptr sender_;
                    receiver_ptr receiver_;
                    tpdu_size tpdusize;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            public:

                template <typename CheckAcceptHandler>
                void asyn_check_accept(CheckAcceptHandler handler, int16_t src) {

                    transport_option_.src_tsap(src);
                    get_io_service().post(boost::bind(&accept_operation<CheckAcceptHandler>::run,
                            accept_operation<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler)));
                }








                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Send operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers) {

                    return send(buffers, 0);
                }

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers,
                        message_flags flags) {
                    error_code ec;
                    std::size_t s = send(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "send");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers) {
                    error_code ec;
                    std::size_t s = send(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "write_some");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers,
                        error_code& ec) {

                    return send(buffers, 0, ec);
                }

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    return send_impl(buffers, flags, ec);
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            private:

                template <typename SendHandler, typename ConstBufferSequence>
                class send_operation {
                public:

                    send_operation(stream_socket* socket, SendHandler handler,
                            const ConstBufferSequence& buffers, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    in_(sender_ptr(new data_sender<ConstBufferSequence>(buffers, socket->pdusize()))),
                    flags_(flags),
                    send_lower_(boost::asio::buffer_size(buffers)) {
                    }

                    void run() {

                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            in_->size(bytes_transferred);
                            if (!in_->ready()) {
                                socket_->get_service().async_send(socket_->get_implementation(), in_->pop(), flags_, *this);
                                return;
                            }
                        }
                        handler_(ec, static_cast<std::size_t> (send_lower_));
                    }


                private:

                    stream_socket* socket_;
                    SendHandler handler_;
                    sender_ptr in_;
                    message_flags flags_;
                    std::size_t send_lower_;


                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

            public:

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send(buffers, 0, handler);
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;
                    get_io_service().post(boost::bind(&send_operation<WriteHandler, ConstBufferSequence>::run,
                            send_operation<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_write_some(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                }







                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Receive  operation  //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers) {

                    return receive<MutableBufferSequence > (buffers, 0);
                }

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers,
                        message_flags flags) {
                    error_code ec;
                    std::size_t s = receive(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "receive");

                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers,
                        error_code& ec) {

                    return receive(buffers, 0, ec);
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers) {
                    error_code ec;
                    std::size_t s = receive(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "read_some");

                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    return receive_impl(buffers, flags, ec);
                }

            private:


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                      

                template <typename ReceiveHandler, typename Mutable_Buffers>
                class receive_operation {
                public:

                    receive_operation(stream_socket* socket, ReceiveHandler handler,
                            receiver_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    receiver_(receive),
                    buff_(buff),
                    flags_(flags) {
                    }

                    void run() {

                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        std::size_t n = 0;
                        if (!ec) {
                            receiver_->put(bytes_transferred);
                            if (!receiver_->ready()) {
                                socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receiver_->buffer()), flags_, *this);
                                return;
                            }

                            if (!success()) return;
                        }
                        socket_->waiting_data_size(receiver_->waitdatasize(), receiver_->eof());
                        handler_(ec, static_cast<std::size_t> (receiver_->datasize()));
                    }


                private:

                    bool success() {
                        switch (receiver_->type()) {
                            case CR:
                            {
                                error_code ecc;
                                handler_(ecc, 0);
                                return false;
                            }
                            case DT:
                            {
                                return true;
                            }
                            case ER:
                            {
                                socket_->self_shutdown();
                                handler_(ER_PROTOCOL, static_cast<std::size_t> (receiver_->datasize()));
                                break;
                            }
                            case DR:
                            {
                                socket_->self_shutdown();
                                handler_(ER_REFUSE, static_cast<std::size_t> (receiver_->datasize()));
                                break;
                            }
                            default:
                            {
                                socket_->self_shutdown();
                                handler_(ER_PROTOCOL, 0);
                            }
                        }

                        return false;
                    }

                    stream_socket* socket_;
                    ReceiveHandler handler_;
                    const Mutable_Buffers& buff_;
                    receiver_ptr receiver_;
                    message_flags flags_;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                      

            public:

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_receive(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, handler, 0);
                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_receive(const MutableBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                    get_io_service().post(boost::bind(&receive_operation<ReadHandler, MutableBufferSequence>::run, receive_operation<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                            receiver_ptr(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state())), buffers, flags)));

                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_read_some(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  protected member  //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

            protected:

                std::size_t waiting_data_size() const {
                    return waiting_data_size_;
                }

                void waiting_data_size(std::size_t val, bool st) {
                    eof_state_ = st;
                    waiting_data_size_ = val;
                }

                bool eof_state() const {
                    return eof_state_;
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  private member  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

            private:

                boost::system::error_code self_shutdown() {
                    error_code ecc;
                    get_service().shutdown(get_implementation(), boost::asio::socket_base::shutdown_both, ecc);
                    return ecc;
                }

                tpdu_size pdusize() const {
                    return pdusize_;
                };

                const protocol_options& transport_option() const {
                    return transport_option_;
                }

                protocol_options& transport_option() {
                    return transport_option_;
                }

                void negotiate_transport_option(const protocol_options& val) {
                    pdusize_ = val.pdusize();
                    transport_option_.dst_tsap(val.src_tsap());
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  private implementator  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

                error_code connect_impl(const endpoint_type& peer_endpoint,
                        error_code& ec) {

                    if (get_service().connect(get_implementation(), peer_endpoint, ec))
                        return ec;

                    sender_ptr sender_(sender_ptr(new sender(transport_option())));
                    while (!ec && !sender_->ready())
                        sender_->size(get_service().send(get_implementation(), sender_->pop(), 0, ec));
                    if (ec) {
                        self_shutdown();
                        return ec;
                    }

                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(get_service().receive(get_implementation(), boost::asio::buffer(receiver_->buffer()), 0, ec));
                    }
                    if (ec) {
                        self_shutdown();
                        return ec;
                    }

                    if (receiver_->state() == receiver::complete) {
                        switch (receiver_->type()) {
                            case CC:
                            {
                                negotiate_transport_option(receiver_->options());
                                return ec;
                            }
                            case ER:
                            {
                                self_shutdown();
                                return ec = ER_PROTOCOL;
                            }
                            case DR:
                            {
                                self_shutdown();
                                return ec = receiver_->errcode();
                            }
                            default:
                            {
                            }
                        }
                    }
                    self_shutdown();
                    return ec = ER_PROTOCOL;
                }

                error_code release_impl(error_code& ec, octet_type rsn = DR_REASON_NORM) {
                    if (is_open()) {
                        sender_ptr sender_(sender_ptr(new sender(transport_option().dst_tsap(), transport_option().src_tsap(), rsn)));
                        while (!ec && !sender_->ready())
                            sender_->size(get_service().send(get_implementation(), sender_->pop(), 0, ec));
                        self_shutdown();
                        return ec;
                    }
                    return ec = ER_REFUSE;
                }

                error_code check_accept_imp(int16_t src, error_code& ec) {
                    transport_option_.src_tsap(src);
                    bool canseled = false;
                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(get_service().receive(get_implementation(), boost::asio::buffer(receiver_->buffer()), 0, ec));
                    }
                    if (ec) {
                        self_shutdown();
                        return ec;
                    }
                    sender_ptr sender_;
                    protocol_options options_ = transport_option();
                    if (receiver_->type() != CR || receiver_->state() != receiver::complete) {
                        self_shutdown();
                        return ER_PROTOCOL;
                    }
                    octet_type error_accept = 0;
                    if (!negotiate_rfc1006impl_option(options_, receiver_->options(), error_accept)) {
                        canseled = true;
                        sender_ = sender_ptr(new sender(receiver_->options().src_tsap(), options_.src_tsap(), error_accept));
                    }
                    else {
                        sender_ = sender_ptr(new sender(1, options_));
                    }
                    while (!ec && !sender_->ready())
                        sender_->size(get_service().send(get_implementation(), sender_->pop(), 0, ec));
                    if (ec) {
                        self_shutdown();
                        return ec;
                    }
                    if (canseled) {
                        self_shutdown();
                    }
                    else {

                        protocol_options opt = receiver_->options();
                        opt.pdusize(options_.pdusize());
                        negotiate_transport_option(receiver_->options());
                    }
                    return ec = canseled ? ER_BADADDRESS : ec;
                }

                template <typename ConstBufferSequence>
                std::size_t send_impl(const ConstBufferSequence& buffers,
                        message_flags flags, error_code& ec) {
                    sender_ptr sender_(new data_sender<ConstBufferSequence > (buffers, pdusize()));
                    while (!ec && !sender_->ready())
                        sender_->size(get_service().send(get_implementation(), sender_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {
                    receiver_ptr receiver_(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(get_service().receive(get_implementation(), boost::asio::buffer(
                                receiver_->buffer()), 0, ec));
                    }
                    if (ec)
                        return 0;
                    switch (receiver_->type()) {
                        case CR:
                        case DT:
                        {
                            waiting_data_size(receiver_->waitdatasize(), receiver_->eof());
                            return receiver_->datasize();
                        }
                        case ER:
                        case DR:
                        {
                            self_shutdown();
                            ec = (receiver_->type() == DR) ? ER_REFUSE : ER_PROTOCOL;
                            return static_cast<std::size_t> (receiver_->datasize());
                        }
                    }
                    self_shutdown();
                    ec = ER_PROTOCOL;
                    return 0;
                }


                tpdu_size pdusize_;
                protocol_options transport_option_;
                std::size_t waiting_data_size_;
                bool eof_state_;
            };






            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 socket_acceptor_service //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


            namespace datail {

                template <typename Protocol>
                class socket_acceptor_service
                : public boost::asio::socket_acceptor_service<boost::asio::ip::tcp> {
                public:

                    typedef boost::asio::socket_acceptor_service<boost::asio::ip::tcp> service_impl_type;
                    typedef boost::asio::ip::tcp protocol_type;
                    typedef boost::asio::ip::tcp::endpoint endpoint_type;
                    typedef service_impl_type::implementation_type implementation_type;
                    typedef service_impl_type::native_type native_type;

                    static boost::asio::io_service::id id;


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //  Constructors  //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                         

                    explicit socket_acceptor_service(boost::asio::io_service& io_service)
                    : boost::asio::socket_acceptor_service<Protocol> (io_service),
                    service_impl_(boost::asio::use_service<service_impl_type>(io_service)), src_(0) {
                    }




                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                    //  Accept  operation //
                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                        

                    template <typename SocketService>
                    error_code accept(implementation_type& impl,
                            basic_socket<protocol_type, SocketService>& peer,
                            endpoint_type* peer_endpoint, error_code& ec) {
                        if (!service_impl_.accept(impl, peer, peer_endpoint, ec)) {
                            if (static_cast<stream_socket*> (&peer)->check_accept(src(), ec)) {
                                error_code ecc;
                                //static_cast<stream_socket*> (&peer)->close(ecc);
                            }
                        }
                        return ec;
                    }


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                         

                private:

                    template <typename Handler, typename Socket>
                    class accept_handler {
                    public:

                        accept_handler(service_impl_type& service_impl, implementation_type& impl, Handler h, Socket& socket, endpoint_type* endpoint, int16_t src)
                        : service_impl_(service_impl), impl_(impl), handler_(h), socket_(socket), endpoint_(endpoint), src_(src) {
                        }

                        void run() {
                            service_impl_.async_accept(impl_, socket_, endpoint_, *this);
                        }

                        void operator()(const error_code& ec) {
                            if (!ec) {
                                static_cast<stream_socket*> (&socket_)->asyn_check_accept<Handler > (handler_, src_);
                                return;
                            }
                            handler_(ec);
                        }

                    private:
                        service_impl_type& service_impl_;
                        implementation_type& impl_;
                        Handler handler_;
                        Socket& socket_;
                        endpoint_type* endpoint_;
                        int16_t src_;
                    };


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                         

                public:

                    template <typename SocketService, typename AcceptHandler>
                    void async_accept(implementation_type& impl,
                            basic_socket<protocol_type, SocketService>& peer,
                            endpoint_type* peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                        service_impl_.get_io_service().post(boost::bind(&accept_handler<AcceptHandler, basic_socket<protocol_type, SocketService> >::run,
                                accept_handler<AcceptHandler, basic_socket<protocol_type, SocketService> >(service_impl_, impl, handler, peer, peer_endpoint, src())));
                    }


                private:

                    int16_t src() const {
                        boost::mutex::scoped_lock(mtx);
                        return src_ = ((src_ + 1) ? (src_ + 1) : 1);
                    }

                    service_impl_type& service_impl_;
                    mutable int16_t src_;
                    boost::mutex mtx;

                };


                template <typename Protocol>
                boost::asio::io_service::id socket_acceptor_service<Protocol>::id;
            }



            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 socket_ acceptor  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

            class socket_acceptor : public basic_socket_acceptor<boost::asio::ip::tcp, datail::socket_acceptor_service<boost::asio::ip::tcp> > {
            public:

                explicit socket_acceptor(boost::asio::io_service& io_service)
                : basic_socket_acceptor<boost::asio::ip::tcp, datail::socket_acceptor_service<boost::asio::ip::tcp> >(io_service) {
                }

                socket_acceptor(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, bool reuse_addr = true)
                : basic_socket_acceptor<boost::asio::ip::tcp, datail::socket_acceptor_service<boost::asio::ip::tcp> >(io_service, endpoint, reuse_addr) {
                }

            };

        }




        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //  rfc1006 declaration  //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

        class rfc1006 {
        public:

            typedef boost::asio::ip::basic_endpoint<boost::asio::ip::tcp> endpoint;

            typedef transport_selector selector;

            static rfc1006 v4() {

                return rfc1006(PF_INET);
            }

            static rfc1006 v6() {

                return rfc1006(PF_INET6);
            }

            int type() const {

                return SOCK_STREAM;
            }

            int protocol() const {

                return IPPROTO_TCP;
            }

            int family() const {

                return family_;
            }

            typedef rfc1006impl::stream_socket socket;

            typedef rfc1006impl::socket_acceptor acceptor;

            typedef boost::asio::ip::basic_resolver<boost::asio::ip::tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
            //typedef boost::asio::basic_socket_iostream<boost::asio::ip::tcp> iostream;
#endif 


            typedef boost::asio::detail::socket_option::boolean<
            IPPROTO_TCP, TCP_NODELAY> no_delay;

            friend bool operator==(const rfc1006& p1, const rfc1006& p2) {

                return p1.family_ == p2.family_;
            }

            friend bool operator!=(const rfc1006& p1, const rfc1006& p2) {

                return p1.family_ != p2.family_;
            }

        private:

            explicit rfc1006(int family)
            : family_(family) {
            }

            int family_;
        };




    }
}

#include <boost/asio/detail/pop_options.hpp>

#endif  /* RFC1006_H */