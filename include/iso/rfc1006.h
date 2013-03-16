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


            // TPDU code *ref X224  13.1 Table 8   only class 0 implement ( over rfc1006 )
            const octet_type CR_TPDU_ID = '\xE0'; //Connection request   !!xxxx - out class 0
            const octet_type CC_TPDU_ID = '\xD0'; //Connection confirm   !!xxxx - out class 0
            const octet_type DR_TPDU_ID = '\x80'; //Disconnection request 
            const octet_type DC_TPDU_ID = '\xC0'; //Disconnection  confirm                              !!not used here impl
            const octet_type DT_TPDU_ID = '\xF0'; //Data !!y - out class 0
            const octet_type ED_TPDU_ID = '\x10'; //Expedited data !!not use here impl                  !!not used here impl
            const octet_type DA_TPDU_ID = '\x60'; //Data acknowledgement !!not use here impl
            const octet_type EA_TPDU_ID = '\x20'; //Expedited data acknowledgement                      !!not used here impl
            const octet_type RJ_TPDU_ID = '\x50'; //Reject                                              !!not used here impl
            const octet_type ER_TPDU_ID = '\x70'; //Error


           // see Disconnection  REASON CODE  iso.h
     
            // Error REASON CODE *ref X224  13.12.3 c)   
            const octet_type ERT_REASON_NODEF = '\x0'; // Reason not specified    - all ER_PROTOCOL
            const octet_type ERT_REASON_PARAM_CODE = '\x1'; // Invalid parameter code
            const octet_type ERT_REASON_TPDU_TYPE = '\x2'; // Invalid TPDU type
            const octet_type ERT_REASON_PARAM_VALUE = '\x3'; // Invalid parameter value
            
            // Error REASON CODE *ref X224  13.12.4
            const octet_type ERT_PARAM_ID = '\xC1';    //Parameter code:        
            
            // VAR ID  *ref X224  13.3.4
            const octet_type VAR_TSAPCALLING_ID = '\xC1';  //calling Transport-Selector *ref X224 13.3.4 a)
            const octet_type VAR_TSAPCALLED_ID = '\xC2';   //called Transport-Selector *ref X224 13.3.4 a)
            const octet_type VAR_TPDU_SIZE = '\xC0';  //TPDU size *ref X224 13.3.4 b)
            const octet_type VAR_MAXTPDU_SIZE = '\xF0';   // Preferred maximum TPDU size *ref X224 13.3.4 c)
            
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

            void generate_TKPTDU(raw_type& val);

            typedef std::pair<octet_type, std::size_t> headarvar;

            typedef std::pair<headarvar, raw_type> headarvarvalue;
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
                const raw_type& called = raw_type(), const raw_type& calling = raw_type());

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

                const raw_type & tsap_calling() const;

                void tsap_calling(const raw_type & val);

                const raw_type & tsap_called() const;

                void tsap_called(const raw_type & val);

                std::size_t maxpdusize() const;

                void maxpdusize(std::size_t val);

            private:
                int16_t dst_;
                int16_t src_;
                headarvarvalues vars_;
                raw_type null_;
            };
            

            const protocol_options NULL_PROTOCOL_OPTION = protocol_options();
            
            

            bool negotiate_rfc1006impl_option(protocol_options& self, const protocol_options& dist, octet_type& error);

            bool parse_vars(const raw_type& str, headarvarvalues& vars);

            raw_type generate_header(octet_type type, int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues());

            raw_type generate_header_TKPT_CR(const protocol_options& opt);

            raw_type generate_header_TKPT_CC(const protocol_options& opt);

            raw_type generate_header_TKPT_DR(int16_t dst, int16_t src, octet_type rsn);

            raw_type generate_header_TKPT_DC(int16_t dst, int16_t src);

            raw_type generate_header_TKPT_ER(int16_t dst, const raw_type& errorseq = raw_type(), octet_type err = 0);



            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 data_send_buffer_impl   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            
 
            // see RFC1006
            const octet_type TKPT_STARTar[] = {'\x3', '\x0'};
            const raw_type TKPT_START = raw_type(TKPT_STARTar, TKPT_STARTar + 2);           

            const std::size_t DT_SEND_BUFF_HEADER = 5;
            
            const std::size_t TKPT_LENGTH = 4;
            
            template <typename ConstBufferSequence>
            class data_send_buffer_impl : public send_buffer_impl {
            public:

                data_send_buffer_impl(const ConstBufferSequence& bf, tpdu_size pdusize) :
                send_buffer_impl(), sizenorm_(DT_SEND_BUFF_HEADER), sizeeof_(DT_SEND_BUFF_HEADER) {
                    construct(bf, pdusize);

                }

                void construct(const ConstBufferSequence& bf, tpdu_size pdusize) {
                    std::size_t pdusz = tpdu_byte_size(pdusize);
                    if (!pdusz) pdusz = 2048;
                    pdusz -= 3;

                    uint16_t normalsz = endiancnv_copy(static_cast<uint16_t> (pdusz + 7));
                    sizenorm_ = TKPT_START;
                    raw_back_insert(sizenorm_, inttype_to_raw(normalsz));
                    sizenorm_.insert(sizenorm_.end(), '\x2');
                    sizenorm_.insert(sizenorm_.end(), DT_TPDU_ID);
                    sizenorm_.insert(sizenorm_.end(), TPDU_CONTINIUE);

                    typedef typename ConstBufferSequence::const_iterator constbuffseq_iterator;
                    typedef typename ConstBufferSequence::value_type constbuffseq_value;

                    constbuffseq_iterator it = bf.begin();
                    constbuffseq_iterator end = bf.end();
                    constbuffseq_iterator pend = end;
                    if (it != end)
                        --pend;

                    constbuffseq_value val;

                    const_sequence tmp;
                    std::size_t tmpsize = 0;

                    bool ended = (it == end) || (it == pend);
                    while (it != end) {
                        val = *it;
                        do {
                            if ((boost::asio::buffer_size(val) + tmpsize) > pdusz) {
                                buff().push_back(const_buffer(&sizenorm_.front(), sizenorm_.size()));
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
                                    sizeeof_ = TKPT_START;
                                    raw_back_insert(sizeeof_, inttype_to_raw(eofsz));
                                    sizeeof_ .insert(sizeeof_ .end(), '\x2');
                                    sizeeof_ .insert(sizeeof_ .end(), DT_TPDU_ID);
                                    sizeeof_ .insert(sizeeof_ .end(), TPDU_ENDED);
                                    buff().push_back(const_buffer(&sizeeof_.front(), sizeeof_.size()));
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

                raw_type sizenorm_;
                raw_type sizeeof_;
            };
            
            
          


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 send_seq   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                  

            class send_seq {
            public:

                send_seq(tpdu_type type) :
                type_(type) {
                }

                send_seq(const protocol_options& opt) :
                type_(CR) {
                    constructCR(opt);
                }

                send_seq(int16_t dst, const protocol_options& opt) :
                type_(CC) {
                    constructCC(opt);
                }

                send_seq(int16_t dst, const raw_type& errorreason, octet_type err) :
                type_(ER) {
                    constructER(dst, errorreason, err);
                }

                send_seq(int16_t dst, int16_t src, octet_type rsn) :
                type_(DR) {
                    constructDR(dst, src, rsn);
                }

                virtual ~send_seq() {
                }

                bool ready() const {
                    return (!buf_) || (buf_->ready());
                }

                const const_sequence& pop() {
                    return buf_ ? buf_->pop() : NULL_CONST_SEQUENCE;
                }

                std::size_t size(std::size_t sz) {
                    return ready() ? 0 : buf_->size(sz);
                }

                std::size_t receivesize() const {
                    return ready() ? 0 : buf_->receivesize();
                }

                tpdu_type type() const {
                    return type_;
                }




            protected:


                void constructCR(const protocol_options& opt);

                void constructCC(const protocol_options& opt);

                void constructER(int16_t dst, const raw_type& errorreason, octet_type err);

                void constructDR(int16_t dst, int16_t src, octet_type rsn);

                tpdu_type type_;
                send_buffer_ptr buf_;
            };

            typedef boost::shared_ptr<send_seq> send_seq_ptr;
            
            
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 send_seq_data   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            

            template <typename ConstBufferSequence >
            class send_seq_data : public send_seq {
            public:

                send_seq_data(const ConstBufferSequence& buff, tpdu_size pdusize) : send_seq(DT) {
                    constructDT(buff, pdusize);
                }

            protected:

                void constructDT(const ConstBufferSequence& buff, tpdu_size pdusize) {
                    buf_ = send_buffer_ptr(new data_send_buffer_impl<ConstBufferSequence > (buff, pdusize));
                }

            };  


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rfc1006 receive_seq   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

            const std::size_t TKPT_WITH_LI = 5;

            class receive_seq {
            public:

                typedef boost::shared_ptr< protocol_options > protocol_options_ptr;

                enum operation_state {
                    waittkpt,
                    waitheader,
                    waitdata,
                    complete,
                    error
                };

                receive_seq(const mutable_buffer& buff, std::size_t waitingsize, bool ef);

                receive_seq();

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

                octet_type reject_reason() const {
                    return reject_reason_;
                }

                const protocol_options& options() const {
                    return options_ ? *options_ :  NULL_PROTOCOL_OPTION;
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
                octet_type reject_reason_;
                error_code errcode_;
                bool eof_;
                mutable_buffer tkpt_buff_;                
                mutable_buffer header_buff_;
                mutable_buffer userbuff_;         
                raw_type_ptr tkpt_data;
                raw_type_ptr header_data;        
                protocol_options_ptr options_;                
            };


            typedef boost::shared_ptr<receive_seq> receive_seq_ptr;



            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rf1006 stream_socket  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

            class stream_socket : public boost::asio::basic_stream_socket<boost::asio::ip::tcp > {
                
            public:


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

                explicit stream_socket(boost::asio::io_service& io_service, const transport_selector& tsel = transport_selector())
                : boost::asio::basic_stream_socket<boost::asio::ip::tcp>(io_service), pdusize_(SIZE2048), 
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
                }

                stream_socket(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const transport_selector& tsel = transport_selector())
                : boost::asio::basic_stream_socket<boost::asio::ip::tcp >(io_service, endpoint), pdusize_(tsel.pdusize()), 
                transport_option_(0, 1, tsel.pdusize(), tsel.called(), tsel.calling()), waiting_data_size_(0), eof_state_(true) {
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
                class connect_op {

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    connect_op(stream_socket* socket, ConnectHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(request),
                    send_(send_seq_ptr(new send_seq(socket->transport_option()))),
                    receive_(new receive_seq()) {
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
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), send_->pop(), 0, *this);
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
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()), 0, *this);
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
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case CC:
                                {
                                    socket_->negotiate_transport_option(receive_->options());
                                    handler_(ec);
                                    return;
                                }
                                case ER:{
                                    error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);                                    
                                    handler_(ER_PROTOCOL);
                                    return;                                   
                                }
                                case DR:
                                {
                                    error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_(receive_->errcode());
                                    return;
                                }
                            }
                        }
                        error_code ecc;
                        socket_->get_service().close(socket_->get_implementation(), ecc);                        
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
                    send_seq_ptr send_;
                    receive_seq_ptr receive_;

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
                    
                    get_service().async_connect(get_implementation(), peer_endpoint, boost::bind(&connect_op<ConnectHandler>::run, 
                               connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));

                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Release operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void release(octet_type rsn = 0) {
                    error_code ec;
                    release(ec, rsn);
                    boost::asio::detail::throw_error(ec, "release");
                }

                error_code release(error_code& ec, octet_type rsn = 0) {

                    return release_impl(ec , rsn);
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ReleaseHandler>
                class release_op {
                public:

                    release_op(stream_socket* socket, ReleaseHandler handler, octet_type rsn) :
                    socket_(socket),
                    handler_(handler),
                    send_(send_seq_ptr(new send_seq(socket->transport_option().dst_tsap(), socket->transport_option().src_tsap(), rsn))) {
                    }

                    void run() {
                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            send_->size(bytes_transferred);
                            if (!send_->ready()) {
                                socket_->get_service().async_send(socket_->get_implementation(), send_->pop(), 0, *this);
                                return;
                            }
                        }
                        handler_(ec);
                    }


                private:
                    stream_socket* socket_;
                    ReleaseHandler handler_;
                    send_seq_ptr send_;
                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ReleaseHandler>
                void asyn_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                        octet_type rsn = 0) {
                    BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_op<ReleaseHandler>::run,
                                release_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, rsn)));
                    }
                    else
                        handler( ER_REFUSE);
                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void check_accept(int16_t src = 1) {
                    error_code ec;
                    boost::asio::detail::throw_error(ec, "connect");
                }

                error_code check_accept(int16_t src, error_code& ec) {
                    return check_accept_imp(src, ec);
                }


            private:

                template <typename CheckAcceptHandler>
                class accept_op {

                    enum stateconnection {
                        wait,
                        send,
                        refuse
                    };

                public:

                    accept_op(stream_socket* socket, CheckAcceptHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(wait),
                    send_(),
                    tpdusize(socket->transport_option().pdusize()),
                    receive_(new receive_seq()) {
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
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()), 0, *this);
                                        return;
                                    }
                                    parse_response(ec);
                                    return;
                                }
                                case send:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), send_->pop(), 0, *this);
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case refuse:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->get_service().async_send(socket_->get_implementation(), send_->pop(), 0, *this);
                                        return;
                                    }
                                    error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_(ER_OUTDOMAIN);

                                    return;
                                }
                            }
                        }
                        handler_(ec);
                    }


                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                private:

                    void parse_response(const error_code& ec) {
                        if (receive_->type() != CR || receive_->state() != receive_seq::complete) {
                            error_code ecc;
                            socket_->get_service().close(socket_->get_implementation(), ecc);
                            handler_(ER_PROTOCOL);
                            return;
                        }
                        protocol_options options_= socket_->transport_option();
                        octet_type error_accept = 0;
                        if (!negotiate_rfc1006impl_option(options_, receive_->options(), error_accept)) {
                            send_ = send_seq_ptr(new send_seq(receive_->options().src_tsap(), options_.src_tsap(), error_accept));
                            state(refuse);
                            operator()(ec, 0);
                            return;
                        }
                        tpdusize = options_.pdusize();
                        send_ = send_seq_ptr(new send_seq(1, options_));
                        state(send);
                        operator()(ec, 0);
                    }

                    void finish(const error_code& ec) {

                        //receive_->options().pdusize(tpdusize);
                        socket_->negotiate_transport_option(receive_->options());
                        handler_(ec);
                    }

                    void state(stateconnection st) {

                        if (state_ != st)
                            state_ = st;
                    }



                    stream_socket* socket_;
                    CheckAcceptHandler handler_;
                    stateconnection state_;
                    send_seq_ptr send_;
                    receive_seq_ptr receive_;
                    tpdu_size  tpdusize;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            public:

                template <typename CheckAcceptHandler>
                void asyn_check_accept(CheckAcceptHandler handler, int16_t src) {

                    transport_option_.src_tsap(src);
                    get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
                            accept_op<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler)));
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
                        socket_base::message_flags flags) {
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
                        socket_base::message_flags flags, error_code& ec) {

                    return send_impl(buffers, flags, ec);
                }



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            private:

                template <typename SendHandler, typename ConstBufferSequence>
                class send_op {
                public:

                    send_op(stream_socket* socket, SendHandler handler,
                            const ConstBufferSequence& buffers, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    in_(send_seq_ptr(new send_seq_data<ConstBufferSequence>(buffers, socket->pdusize()))),
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
                    send_seq_ptr in_;
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
                        socket_base::message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;
                    get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, 
                                     send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
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
                        socket_base::message_flags flags) {
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
                        socket_base::message_flags flags, error_code& ec) {

                    return receive_impl(buffers, flags, ec);
                }

            private:


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                      

                template <typename ReceiveHandler, typename Mutable_Buffers>
                class receive_op {
                public:

                    receive_op(stream_socket* socket, ReceiveHandler handler,
                            receive_seq_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    receive_(receive),
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
                            receive_->put(bytes_transferred);
                            if (!receive_->ready()) {
                                socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()), flags_, *this);
                                return;
                            }

                            if (!success()) return;
                        }
                        socket_->waiting_data_size(receive_->waitdatasize(), receive_->eof());
                        handler_(ec, static_cast<std::size_t> (receive_->datasize()));
                    }


                private:

                    bool success() {
                        switch (receive_->type()) {
                            case CR:
                            {
                                error_code decc;
                                handler_(decc, 0);
                                return false;
                            }
                            case DT:
                            {
                                return true;
                            }
                            case ER:
                            {
                                error_code ecc;
                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                handler_(ER_PROTOCOL, static_cast<std::size_t> (receive_->datasize()));
                                break;
                            }
                            case DR:
                            {
                                error_code ecc;
                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                handler_( ER_REFUSE, static_cast<std::size_t> (receive_->datasize()));
                                break;
                            }
                            default:
                            {
                                error_code ecc;
                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                handler_(ER_PROTOCOL, 0);
                            }
                        }

                        return false;
                    }

                    stream_socket* socket_;
                    ReceiveHandler handler_;
                    const Mutable_Buffers& buff_;
                    receive_seq_ptr receive_;
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
                        socket_base::message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                    get_io_service().post(boost::bind(&receive_op<ReadHandler, MutableBufferSequence>::run, receive_op<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                            receive_seq_ptr(new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state())), buffers, flags)));

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

                    send_seq_ptr send_(send_seq_ptr(new send_seq(transport_option())));
                    while (!ec && !send_->ready())
                        send_->size(get_service().send(get_implementation(), send_->pop(), 0, ec));
                    if (ec)
                        return ec;
                    receive_seq_ptr receive_(receive_seq_ptr(new receive_seq()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(get_service().receive(get_implementation(), boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return ec;
                    if (receive_->state() == receive_seq::complete) {
                        switch (receive_->type()) {
                            case CC:
                            {
                                negotiate_transport_option(receive_->options());
                                return ec;
                            }
                            case ER:{
                                error_code ecc;
                                get_service().close(get_implementation(), ecc);
                                return ec =ER_PROTOCOL;                      
                            }
                            case DR:
                            {
                                error_code ecc;
                                get_service().close(get_implementation(), ecc);
                                return ec = receive_->errcode();
                            }
                            default:
                            {
                            }
                        }
                    }
                    error_code ecc;
                    get_service().close(get_implementation(), ecc);                    
                    return ec = ER_PROTOCOL;
                }

                error_code release_impl(error_code& ec, octet_type rsn) {
                    if (is_open()) {
                        send_seq_ptr send_(send_seq_ptr(new send_seq(transport_option().dst_tsap(), transport_option().src_tsap(), rsn)));
                        while (!ec && !send_->ready())
                            send_->size(get_service().send(get_implementation(), send_->pop(), 0, ec));
                         error_code ecc;
                        get_service().close(get_implementation(), ecc);                          
                        return ec;
                    }
                    return ec =  ER_REFUSE;
                }

                error_code check_accept_imp(int16_t src, error_code& ec) {
                    transport_option_.src_tsap(src);
                    bool canseled = false;
                    receive_seq_ptr receive_(receive_seq_ptr(new receive_seq()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(get_service().receive(get_implementation(), boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return ec;
                    send_seq_ptr send_;
                    protocol_options options_ = transport_option();
                    if (receive_->type() != CR || receive_->state() != receive_seq::complete) {
                        error_code ecc;
                        get_service().close(get_implementation(), ecc);
                        return ER_PROTOCOL;
                    }
                    octet_type error_accept = 0;
                    if (!negotiate_rfc1006impl_option(options_, receive_->options(), error_accept)) {
                        canseled = true;
                        send_ = send_seq_ptr(new send_seq(receive_->options().src_tsap(), options_.src_tsap(), error_accept));
                    }
                    else {
                        send_ = send_seq_ptr(new send_seq(1, options_));
                    }
                    while (!ec && !send_->ready())
                        send_->size(get_service().send(get_implementation(), send_->pop(), 0, ec));
                    if (ec)
                        return ec;
                    if (canseled) {
                        error_code ecc;
                        get_service().close(get_implementation(), ecc);
                    }
                    else {

                        protocol_options opt = receive_->options();
                        opt.pdusize(options_.pdusize());
                        negotiate_transport_option(receive_->options());
                    }
                    return ec = canseled ? ER_BADADDRESS : ec;
                }

                template <typename ConstBufferSequence>
                std::size_t send_impl(const ConstBufferSequence& buffers,
                        socket_base::message_flags flags, error_code& ec) {
                    send_seq_ptr send_(new send_seq_data<ConstBufferSequence > (buffers, pdusize()));
                    while (!ec && !send_->ready())
                        send_->size(get_service().send(get_implementation(), send_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        socket_base::message_flags flags, error_code& ec) {
                    receive_seq_ptr receive_(new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(get_service().receive(get_implementation(), boost::asio::buffer(
                                receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return 0;
                    switch (receive_->type()) {
                        case CR:
                        case DT:
                        {
                            waiting_data_size(receive_->waitdatasize(), receive_->eof());
                            return receive_->datasize();
                        }
                        case ER:
                        case DR:
                        {
                            error_code ecc;
                            get_service().close(get_implementation(), ecc);
                            ec = (receive_->type() == DR) ?  ER_REFUSE : ER_PROTOCOL;
                            return static_cast<std::size_t> (receive_->datasize());
                        }
                    }
                    error_code ecc;
                    get_service().close(get_implementation(), ecc);
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
            typedef boost::asio::basic_socket_iostream<boost::asio::ip::tcp> iostream;
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