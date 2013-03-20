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


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            // optimized rfc1006 data_sender_sequences   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

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

            class stream_socket : protected boost::asio::basic_stream_socket<boost::asio::ip::tcp > {
                typedef boost::shared_ptr<receiver> receiver_ptr;
                typedef boost::shared_ptr<sender> sender_ptr;
                typedef boost::asio::basic_stream_socket<boost::asio::ip::tcp > super_type;

                friend class socket_acceptor;

            public:

                typedef super_type::protocol_type protocol_type;
                typedef super_type::lowest_layer_type lowest_layer_type;
                typedef super_type::native_handle_type native_handle_type;
                typedef super_type::native_type native_type;
                typedef super_type::message_flags message_flags;
                typedef super_type::endpoint_type endpoint_type;
                typedef super_type::service_type service_type;
                typedef super_type::shutdown_type shutdown_type;
                typedef super_type::implementation_type implementation_type;


                using super_type::assign;
                using super_type::at_mark;
                using super_type::available;
                using super_type::bind;
                using super_type::cancel;
                using super_type::close;
                using super_type::get_io_service;
                using super_type::get_option;
                using super_type::io_control;
                using super_type::is_open;
                using super_type::lowest_layer;
                using super_type::native;
                using super_type::native_handle;
                using super_type::native_non_blocking;
                using super_type::non_blocking;
                using super_type::open;
                using super_type::remote_endpoint;
                using super_type::set_option;
                using super_type::shutdown;

            protected:

                using super_type::get_service;
                using super_type::get_implementation;

            public:


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

                explicit stream_socket(boost::asio::io_service& io_service, const transport_selector& tsel = transport_selector())
                : super_type(io_service), pdusize_(tsel.pdusize()),
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
                }

                stream_socket(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const transport_selector& tsel = transport_selector())
                : super_type(io_service, endpoint), pdusize_(tsel.pdusize()),
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Data indication  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                bool ready() const {
                    return (!waiting_data_size_) && (eof_state_);
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
                    return connect_impl(peer_endpoint, ec);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ConnectHandler>
                class connect_operation {
                    
                    typedef connect_operation <ConnectHandler> operation_type;

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    connect_operation(stream_socket& sock, ConnectHandler handlr) :
                    socket(sock),
                    handler(handlr),
                    state_(request),
                    sender_(sender_ptr(new sender(sock.transport_option()))),
                    receiver_(new receiver()) {
                    }

                    void start(const error_code& ec) {
                        if (!ec)
                            execute(ec, 0);
                        else
                            handler(ec);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, * this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    else {
                                        state(response);
                                        execute(ec, 0);
                                        return;
                                    }
                                }
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                            }
                        }
                        handler(ec);
                    }



                private:

                    void finish(const error_code& ec) {
                        if (receiver_->state() == receiver::complete) {
                            switch (receiver_->type()) {
                                case CC:
                                {
                                    socket.negotiate_transport_option(receiver_->options());
                                    handler(ec);
                                    return;
                                }
                                case ER:
                                {
                                    socket.self_shutdown();
                                    handler(ER_PROTOCOL);
                                    return;
                                }
                                case DR:
                                {
                                    socket.self_shutdown();
                                    handler(receiver_->errcode());
                                    return;
                                }
                            }
                        }
                        socket.self_shutdown();
                        handler(ER_PROTOCOL);
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket& socket;
                    ConnectHandler handler;
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

                    typedef connect_operation<ConnectHandler> connect_operation_type;

                    super_type::async_connect(peer_endpoint, boost::bind(&connect_operation_type::start,
                            connect_operation_type(*this, handler), boost::asio::placeholders::error));

                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Release operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void release(octet_type rsn = DR_REASON_NORM) {

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
                    
                    typedef release_operation<ReleaseHandler> operation_type;

                public:

                    release_operation(stream_socket& sock, ReleaseHandler handlr, octet_type rsn) :
                    socket(sock),
                    handler(handlr),
                    sender_(sender_ptr(new sender(sock.transport_option().dst_tsap(), sock.transport_option().src_tsap(), rsn))) {
                    }

                    void start() {
                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            sender_->size(bytes_transferred);
                            if (!sender_->ready()) {
                                socket.super_type::async_send(sender_->pop(), 0,
                                        boost::bind(&operation_type::execute, *this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                                return;
                            }
                        }
                        socket.self_shutdown();
                        handler(ec);
                    }


                private:
                    stream_socket& socket;
                    ReleaseHandler handler;
                    sender_ptr sender_;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ReleaseHandler>
                void async_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                        octet_type rsn = DR_REASON_NORM) {

                    typedef release_operation<ReleaseHandler > release_operation_type;

                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_operation_type::start,
                                release_operation_type(*this, handler, rsn)));
                    }
                    //else
                    //    handler(ER_NOLINK);
                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

            protected:

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
                                      
                    typedef accept_operation<CheckAcceptHandler> operation_type;                    

                    enum stateconnection {
                        response,
                        request,
                        refuse
                    };

                public:

                    accept_operation(stream_socket& sock, CheckAcceptHandler handlr) :
                    socket(sock),
                    handler(handlr),
                    state_(response),
                    sender_(),
                    tpdusize(sock.transport_option().pdusize()),
                    receiver_(new receiver()) {
                    }

                    void start() {
                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    parse_response(ec);
                                    return;
                                }
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case refuse:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    socket.self_shutdown();
                                    handler(ER_PROTOPT);
                                    return;
                                }
                            }
                        }
                        socket.self_shutdown();
                        handler(ec);
                    }


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                private:

                    void parse_response(const error_code& ec) {
                        
                        if (receiver_->type() != CR || receiver_->state() != receiver::complete) {
                            socket.self_shutdown();
                            handler(ER_PROTOCOL);
                            return;
                        }
                        protocol_options options_ = socket.transport_option();
                        octet_type error_accept = 0;
                        if (!negotiate_rfc1006impl_option(options_, receiver_->options(), error_accept)) {
                            sender_ = sender_ptr(new sender(receiver_->options().src_tsap(), options_.src_tsap(), error_accept));
                            state(refuse);
                            execute(ec, 0);
                            return;
                        }
                        tpdusize = options_.pdusize();
                        sender_ = sender_ptr(new sender(1, options_));
                        state(request);
                        execute(ec, 0);
                    }

                    void finish(const error_code& ec) {
                        socket.negotiate_transport_option(receiver_->options());
                        handler(ec);
                    }

                    void state(stateconnection st) {

                        if (state_ != st)
                            state_ = st;
                    }

                    stream_socket& socket;
                    CheckAcceptHandler handler;
                    stateconnection state_;
                    sender_ptr sender_;
                    receiver_ptr receiver_;
                    tpdu_size tpdusize;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            protected:

                template <typename CheckAcceptHandler>
                void async_check_accept(BOOST_ASIO_MOVE_ARG(CheckAcceptHandler) handler, int16_t src) {
                    
                    typedef accept_operation<CheckAcceptHandler > accept_operation_type;

                    transport_option_.src_tsap(src);
                    get_io_service().post(boost::bind(&accept_operation_type::start,
                            accept_operation_type(*this, handler)));
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
                    
                 typedef send_operation<SendHandler, ConstBufferSequence>  operation_type;
                    
                    
                public:

                    send_operation(stream_socket& sock, SendHandler handlr,
                            const ConstBufferSequence& buffers, message_flags flags) :
                    socket(sock),
                    handler(handlr),
                    sender_(sender_ptr(new data_sender<ConstBufferSequence>(buffers, sock.pdusize()))),
                    flags_(flags),
                    sendsize(boost::asio::buffer_size(buffers)) {
                    }

                    void start() {
                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            sender_->size(bytes_transferred);
                            if (!sender_->ready()) {
                                socket.super_type::async_send(sender_->pop(), flags_ ,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                return;
                            }
                        }
                        handler(ec, ec ? 0 : static_cast<std::size_t> (sendsize));
                    }


                private:

                    stream_socket& socket;
                    SendHandler handler;
                    sender_ptr sender_;
                    message_flags flags_;
                    std::size_t sendsize;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

            public:

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send(buffers, 0, handler);
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_write_some(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {                   
                    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

                    typedef send_operation<WriteHandler, ConstBufferSequence>  send_operation_type;        
                    
                    get_io_service().post(boost::bind(&send_operation_type::start, 
                    send_operation_type (*this, handler, buffers, flags)));
                    
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
                    
                 typedef receive_operation<ReceiveHandler,  Mutable_Buffers>  operation_type;                    
                    
                public:

                    receive_operation(stream_socket& sock, ReceiveHandler handlr,
                            receiver_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket(sock),
                    handler(handlr),
                    receiver_(receive),
                    buff_(buff),
                    flags_(flags) {
                    }

                    void start() {

                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {                        
                        if (!ec) {
                            receiver_->put(bytes_transferred);
                            if (!receiver_->ready()) {
                                socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), flags_ ,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                return;
                            }
                            if (!success()) return;
                        }
                        socket.waiting_data_size(receiver_->waitdatasize(), receiver_->eof());
                        handler(ec, static_cast<std::size_t> (receiver_->datasize()));
                    }


                private:

                    bool success() {
                        switch (receiver_->type()) {
                            case CR:
                            {
                                error_code ecc;
                                handler(ecc, 0);
                                return false;
                            }
                            case DT:
                            {
                                return true;
                            }
                            case ER:
                            {
                                socket.self_shutdown();
                                handler(ER_PROTOCOL, static_cast<std::size_t> (receiver_->datasize()));
                                break;
                            }
                            case DR:
                            {
                                socket.self_shutdown();
                                handler(ER_REFUSE, static_cast<std::size_t> (receiver_->datasize()));
                                break;
                            }
                            default:
                            {
                                socket.self_shutdown();
                                handler(ER_PROTOCOL, 0);
                            }
                        }
                        return false;
                    }

                    stream_socket& socket;
                    ReceiveHandler handler;
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
                void async_read_some(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_receive(const MutableBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;
                    
                    typedef receive_operation<ReadHandler, MutableBufferSequence> receive_operation_type;
                    typedef boost::asio::detail::buffer_sequence_adapter< mutable_buffer, MutableBufferSequence>   sequence_adapter_type;                    

                    get_io_service().post(boost::bind(&receive_operation_type::start, receive_operation_type (*this, handler,
                            receiver_ptr(new receiver(sequence_adapter_type::first(buffers), waiting_data_size(), eof_state())), buffers, flags)));

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
                    super_type::shutdown(boost::asio::socket_base::shutdown_both, ecc);
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

                    if (super_type::connect(peer_endpoint, ec))
                        return ec;

                    sender_ptr sender_(sender_ptr(new sender(transport_option())));
                    while (!ec && !sender_->ready())
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
                    if (ec) {
                        self_shutdown();
                        return ec;
                    }

                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
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
                            sender_->size(super_type::send(sender_->pop(), 0, ec));
                        self_shutdown();
                        return ec;
                    }
                    return ec = ER_NOLINK;
                }

                error_code check_accept_imp(int16_t src, error_code& ec) {
                    transport_option_.src_tsap(src);
                    bool canseled = false;
                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
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
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
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
                    return ec = canseled ? ER_PROTOPT : ec;
                }

                template <typename ConstBufferSequence>
                std::size_t send_impl(const ConstBufferSequence& buffers,
                        message_flags flags, error_code& ec) {
                    sender_ptr sender_(new data_sender<ConstBufferSequence > (buffers, pdusize()));
                    while (!ec && !sender_->ready())
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {
                    receiver_ptr receiver_(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(
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
            //  rfc1006 socket_ acceptor  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

            class socket_acceptor : protected basic_socket_acceptor<boost::asio::ip::tcp> {
                typedef basic_socket_acceptor<boost::asio::ip::tcp> super_type;

                friend class stream_socket;

            public:

                typedef super_type::protocol_type protocol_type;
                typedef super_type::endpoint_type endpoint_type;
                typedef super_type::implementation_type implementation_type;
                typedef super_type::service_type service_type;
                typedef super_type::message_flags message_flags;
                typedef super_type::native_handle_type native_handle_type;
                typedef super_type::native_type native_type;

                using super_type::assign;
                using super_type::bind;
                using super_type::cancel;
                using super_type::close;
                using super_type::get_io_service;
                using super_type::get_option;
                using super_type::io_control;
                using super_type::is_open;
                using super_type::listen;
                using super_type::local_endpoint;
                using super_type::native;
                using super_type::native_handle;
                using super_type::native_non_blocking;
                using super_type::non_blocking;
                using super_type::open;
                using super_type::set_option;


            protected:

                using super_type::get_service;
                using super_type::get_implementation;


            public:

                explicit socket_acceptor(boost::asio::io_service& io_service)
                : super_type(io_service), src_(0) {
                }

                socket_acceptor(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, bool reuse_addr = true)
                : super_type(io_service, endpoint, reuse_addr), src_(0) {
                }

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

                void accept(stream_socket& peer) {
                    error_code ec;
                    accept_impl(peer, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                error_code accept(
                        stream_socket& peer,
                        error_code& ec) {
                    return accept_impl(peer, ec);
                }

                void accept(stream_socket& peer,
                        endpoint_type& peer_endpoint) {
                    error_code ec;
                    accept_impl(peer, peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                error_code accept(
                        stream_socket& peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    return accept_impl(peer, peer_endpoint, ec);
                }

                template <typename AcceptHandler>
                void async_accept(stream_socket& peer,
                        endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    async_accept_impl(peer, peer_endpoint, handler);
                }

                template <typename AcceptHandler>
                void async_accept(stream_socket& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    async_accept_impl(peer, handler);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                         

            private:

                template <typename AcceptHandler>
                class accept_operation {
                public:

                    accept_operation(AcceptHandler hendlr, stream_socket& sock, int16_t src)
                    : handler(hendlr), socket(sock), src_(src) {
                    }


                    void execute(const error_code& ec) {
                        if (!ec) {
                            socket.async_check_accept<AcceptHandler > (handler, src_);
                            return;
                        }
                        handler(ec);
                    }

                private:
                    AcceptHandler handler;
                    stream_socket& socket;
                    int16_t src_;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                         

                template <typename AcceptHandler>
                void async_accept_impl(stream_socket& peer,
                        endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    
                    BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;

                    typedef accept_operation<AcceptHandler > accept_operation_type;        
                    
                    super_type::async_accept(peer, peer_endpoint, boost::bind(&accept_operation_type::execute, 
                    accept_operation_type(handler, peer, src()),  boost::asio::placeholders::error));
                    
                }

                template < typename AcceptHandler>
                void async_accept_impl(stream_socket& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    
                    BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;          

                    typedef accept_operation<AcceptHandler > accept_operation_type;                    
                    
                    super_type::async_accept(peer, boost::bind(&accept_operation_type::execute,
                    accept_operation_type (handler, peer, src()), boost::asio::placeholders::error));
                    
                }

                error_code accept_impl(
                        stream_socket& peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    super_type::accept(peer, peer_endpoint, ec);
                    if (ec)
                        return ec;
                    peer.check_accept(src(), ec);
                    return ec;
                }

                error_code accept_impl(
                        stream_socket& peer,
                        error_code& ec) {
                    super_type::accept(peer, ec);
                    if (ec)
                        return ec;
                    peer.check_accept(src(), ec);
                    return ec;
                }

                int16_t src() const {
                    boost::mutex::scoped_lock(mtx);
                    return src_ = ((src_ + 1) ? (src_ + 1) : 1);
                }


                mutable int16_t src_;
                boost::mutex mtx;

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