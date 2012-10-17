

#ifndef RFC1006_H
#define	RFC1006_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include <boost/asio/detail/push_options.hpp>


namespace boost {
    namespace asio {
        namespace ip {
            namespace iec8073 {

                template <typename T> std::string
                inline static inttype_to_str(T vl) {
                    return std::string(((const char*) &vl), sizeof (T));
                }

                inline static int16_t be_le_convert16(int16_t vl) {
                    return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
                }

                inline static uint16_t be_le_convert16(uint16_t vl) {
                    return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
                }

                template <typename T>
                inline static bool str_to_inttype(const std::string& dblk, T& vl) {
                    if (sizeof (vl) > dblk.size()) return false;
                    vl = *(reinterpret_cast<T*> (const_cast<char*> (dblk.data())));
                    return true;
                }


                typedef std::string    transport_selector_type;

                const std::string TKPT_START = std::string("\x3\x0", 2);
                const std::string NULLCHAR = std::string("\x0", 1);

                const std::size_t TKPT_LENGTH = 4;

                const int8_t CR_TPDU_ID = '\xE0'; //connection request
                const int8_t CC_TPDU_ID = '\xD0'; //connection confirm
                const int8_t DR_TPDU_ID = '\x80'; //disconnection request
                const int8_t DC_TPDU_ID = '\xC0'; //disconnection  confirm
                const int8_t DT_TPDU_ID = '\xF0'; //data
                const int8_t ED_TPDU_ID = '\x10'; //expedited data
                const int8_t DA_TPDU_ID = '\x60'; //data acknowledgement
                const int8_t EA_TPDU_ID = '\x20'; //expedited data acknowledgement
                const int8_t RJ_TPDU_ID = '\x50'; //reject
                const int8_t ER_TPDU_ID = '\x70'; //error

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
                } ;

                inline int8_t tpdu_type_primitive(tpdu_type val) {
                    return static_cast<int8_t> (val);
                }



                tpdu_type tpdu_type_from(int8_t val);

                const int8_t TPDU_SIZE8192 = '\xD'; // denied in 0 class
                const int8_t TPDU_SIZE4096 = '\xC'; // denied in 0 class
                const int8_t TPDU_SIZE2048 = '\xB';
                const int8_t TPDU_SIZE1024 = '\xA';
                const int8_t TPDU_SIZE512  = '\x9';
                const int8_t TPDU_SIZE256 = '\x8';
                const int8_t TPDU_SIZE128 = '\x7';
                const int8_t TPDU_SIZE4 = '\x5';   /// test

                enum tpdu_size {
                    SIZENULL = 0,
                    SIZE8192 = TPDU_SIZE8192,
                    SIZE4096 = TPDU_SIZE4096,
                    SIZE2048 = TPDU_SIZE2048,
                    SIZE1024 = TPDU_SIZE1024,
                    SIZE512 = TPDU_SIZE512,
                    SIZE256 = TPDU_SIZE256,
                    SIZE128 = TPDU_SIZE128,
                    SIZE4 = TPDU_SIZE4
                } ;

                const boost::system::error_code ERROR__SEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
                const boost::system::error_code ERROR__ENOBUFS  = boost::system::error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
                const boost::system::error_code ERROR__EPROTO  = boost::system::error_code(boost::system::errc::protocol_error, boost::system::system_category());
                const boost::system::error_code ERROR_EFAULT  =  boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
                const boost::system::error_code ERROR_EADDRNOTAVAIL  =  boost::system::error_code(boost::system::errc::address_not_available, boost::system::system_category());
                const boost::system::error_code ERROR_EDOM  =  boost::system::error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
                const boost::system::error_code ERROR_EIO  =  boost::system::error_code(boost::system::errc::io_error, boost::system::system_category());
                const boost::system::error_code ERROR_ECONNREFUSED  =  boost::system::error_code(boost::system::errc::connection_refused, boost::system::system_category());


                const int8_t REJECT_REASON_NORM = '\x80'; // normal release
                const int8_t REJECT_REASON_SESS = '\x02'; // session   error  
                const int8_t REJECT_REASON_ADDR = '\x03'; // address   error 
                const int8_t REJECT_REASON_NODEF = '\x00'; // address   error               

                boost::system::error_code errorcode_by_reason(int8_t val);

                inline int8_t tpdu_type_size(tpdu_size val) {
                    return static_cast<int8_t> (val);
                }

                inline tpdu_size less_tpdu(const tpdu_size& left, const tpdu_size& right) {
                    if (left == right && right == SIZENULL) return SIZE2048;
                    if (right == SIZENULL) return left;
                    if (left == SIZENULL) return right;
                    return (tpdu_type_size(left) < tpdu_type_size(right)) ? left : right;
                }

                std::size_t tpdu_byte_size(tpdu_size val);

                tpdu_size tpdu_size_frombyte(int8_t val);

                const int8_t ERROR_REASON_NODEF = '\x0';   // no def
                const int8_t ERROR_REASON_PARAM_CODE = '\x1';   // parameter code error
                const int8_t ERROR_REASON_PARAM_TYPE = '\x2';   // parameter type error
                const int8_t ERROR_REASON_PARAM_VALUE = '\x3';   // parameter value error

                const int8_t TPDU_ENDED = '\x80';
                const int8_t TPDU_CONTINIUE = '\x0';

                const int8_t WRONG_TPDU = '\xC1';

                size_t getPDUsize(int8_t sz);

                void generate_TKPTDU(std::string& val);

                size_t getPDUsize(int8_t sz);

                typedef std::pair<int8_t , std::size_t> headarvar;

                typedef std::pair<headarvar , std::string> headarvarvalue;
                typedef std::vector<headarvarvalue> headarvarvalues;


                const int8_t VAR_TSAPCALLING_ID =  '\xC1';
                const int8_t VAR_TSAPCALLED_ID = '\xC2';
                const int8_t VAR_TPDU_SIZE  =  '\xC0';
                const int8_t VAR_MAXTPDU_SIZE  =  '\xF0';

                struct protocol_options {

                    protocol_options() :
                    dst_(0), src_(0) {
                    }

                    protocol_options(int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues()) :
                    dst_(dst), src_(src), vars_(vars) {
                    }

                    protocol_options(int16_t dst, int16_t src, tpdu_size pdusize, const std::string& called = "",  const std::string& calling = "");

                    int16_t  dst_tsap() const {
                        return dst_;
                    }

                    void  dst_tsap(int16_t val) {
                        dst_ = val;
                    }

                    int16_t  src_tsap() const {
                        return src_;
                    }

                    void  src_tsap(int16_t val) {
                        src_ = val;
                    }

                    tpdu_size pdusize() const;

                    void pdusize(tpdu_size val);

                    std::string tsap_calling() const;

                    void tsap_calling(const std::string & val);

                    std::string tsap_called() const;

                    void tsap_called(const std::string & val);

                    std::size_t maxpdusize() const;

                    void maxpdusize(std::size_t val);

                private:
                    int16_t dst_;
                    int16_t src_;
                    headarvarvalues vars_;
                } ;

                class  send_buffer_impl {
                public:
                    typedef boost::shared_ptr<const_buffer>      const_buffs_ptr;
                    typedef std::vector<const_buffs_ptr>                    vector_buffer;
                    typedef vector_buffer::iterator                                  vector_buffer_iterator;

                    send_buffer_impl() : size_(0) {
                        iterator_ = buff_.begin();
                    }

                    virtual ~send_buffer_impl() {
                    }

                    const_buffer pop() {
                        return iterator_ == buff_.end() ? const_buffer(boost::asio::const_buffer()) : (*(*iterator_));
                    }

                    std::size_t  size(std::size_t  sz = 0) {
                        if (sz == 0) return size_;
                        if (iterator_ == buff_.end()) return 0;
                        *iterator_ = const_buffs_ptr( new const_buffer(*(*iterator_) + sz));
                        if (!buffer_size(*(*iterator_))) {
                            size_ = 0;
                            iterator_++;
                            return size_;
                        }
                        return size_ += sz;
                    }

                    std::size_t  receivesize() const {
                        return  iterator_ == buff_.end() ? 0 : buffer_size(*(*iterator_));
                    }

                    bool ready() const {
                        return iterator_ == buff_.end();
                    }


                protected:
                    vector_buffer_iterator iterator_;
                    vector_buffer                buff_;
                    std::size_t                      size_;
                } ;



                typedef boost::shared_ptr<send_buffer_impl>      send_buffer_ptr;

                class  sevice_send_buffer_impl : public send_buffer_impl {
                public:

                    sevice_send_buffer_impl(const std::string& send) : send_buffer_impl(), send_(send) {
                        buff_.push_back(const_buffs_ptr( new const_buffer(const_buffer(send_.data(), send_.size()))));
                        iterator_ = buff_.begin();
                    }
                private:
                    std::string send_;
                } ;

                class  data_send_buffer_impl : public send_buffer_impl {
                public:

                    data_send_buffer_impl(const const_buffer& buff, tpdu_size pdusize) : send_buffer_impl() {
                        construct(buff, pdusize);
                        iterator_ = buff_.begin();
                    }

                    void construct(const const_buffer& buff, tpdu_size pdusize);

                private:
                    std::string size_;
                    std::string sizeeof_;
                } ;


                bool parse_vars(const std::string& str, headarvarvalues& vars);

                std::string generate_header(int8_t type, int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues());

                std::string generate_header_TKPT_CR(const protocol_options& opt);

                std::string generate_header_TKPT_CC(const protocol_options& opt);

                std::string generate_header_TKPT_DR(int16_t dst, int16_t src, int8_t rsn);

                std::string generate_header_TKPT_DC(int16_t dst, int16_t src);

                std::string generate_header_TKPT_DT_single(const std::string& data, bool end);

                std::string generate_header_TKPT_ER(int16_t dst, const std::string& errorreason = "", int8_t err = 0);



                const std::size_t MAX_SEVICE_TPDUSIZE = 256;


                typedef boost::array<char, MAX_SEVICE_TPDUSIZE >                             databuff_type;
                typedef boost::shared_ptr< databuff_type >                                            databuff_type_ptr;

                class receive_seq {
                public:

                    enum operation_state {
                        nodef,
                        complete,
                        error,
                        repeat,
                        continuous
                    } ;

                    receive_seq(const mutable_buffer& buff) : sevice_buff_(),  buff_(buff), size_(0), cursor_(0),
                    state_(nodef), type_(NL), class_option_(0), reject_reason_(0), errcode_() {
                    }

                    receive_seq() : sevice_buff_( new  databuff_type()), buff_(mutable_buffer(sevice_buff_->data(), sevice_buff_->size())), size_(0), cursor_(0),
                    state_(nodef), type_(NL), class_option_(0), reject_reason_(0), errcode_() {
                    }

                    mutable_buffer buffer() {
                        return buff_;
                    }

                    bool ready() {
                        std::string tmp = std::string(boost::asio::buffer_cast<const char*>(buff_), boost::asio::buffer_size(buff_));
                        check();
                        tmp = std::string(boost::asio::buffer_cast<const char*>(buff_), boost::asio::buffer_size(buff_));
                        return (state_ == error || state_ == complete);
                    }

                    operation_state state() const {
                        return state_;
                    }

                    tpdu_type type() const {
                        return type_;
                    }

                    operation_state state(operation_state val) {
                        return state_ = val;
                    }

                    std::size_t  size(std::size_t  sz = 0) {
                        if (!sz) return size_;
                        return size_ += sz;
                    }

                    int8_t  class_option() const {
                        return class_option_;
                    }

                    int8_t  reject_reason() const {
                        return reject_reason_;
                    }

                    const protocol_options& options() const {
                        return options_;
                    }

                    boost::system::error_code errcode() {
                        return errcode_;
                    }


                private:

                    void  reject_reason(int8_t val);

                    void check();

                    operation_state check_tpdu(std::size_t& beg);

                    databuff_type_ptr  sevice_buff_;
                    mutable_buffer    buff_;
                    std::size_t       size_;
                    std::size_t       cursor_;
                    operation_state   state_;
                    tpdu_type         type_;
                    int8_t       class_option_;
                    int8_t       reject_reason_;
                    protocol_options  options_;
                    boost::system::error_code errcode_;

                } ;

                typedef boost::shared_ptr<receive_seq>               receive_seq_ptr;

                class send_seq {
                    typedef std::vector<std::string>::iterator           lines_iterator;
                    typedef std::vector<std::string>                          lines_type;

                public:

                    send_seq(const const_buffer& buff, tpdu_size pdusize) :
                    type_(DT)  {
                        constructDT(buff , pdusize);
                    }

                    send_seq(const protocol_options& opt) :
                    type_(CR)   {
                        constructCR(opt);
                    }

                    send_seq(int16_t dst, const protocol_options& opt) :
                    type_(CC)   {
                        constructCC(opt);
                    }

                    send_seq(int16_t dst, const std::string& errorreason, int8_t err) :
                    type_(ER)   {
                        constructER(dst, errorreason, err );
                    }

                    send_seq(int16_t dst, int16_t src, int8_t rsn) :
                    type_(DR)  {
                        constructDR(dst, src, rsn );
                    }

                    bool ready() const {
                        return (!buf_) ||  (buf_->ready());
                    }

                    const_buffer pop() {
                        return ready()  ?  const_buffer() : buf_->pop();
                    }

                    std::size_t  size(std::size_t  sz) {
                        return ready() ? 0 : buf_->size(sz);
                    }

                    std::size_t  receivesize() const {
                        return ready() ? 0 : buf_->receivesize();
                    }

                    tpdu_type type() const {
                        return type_;
                    }




                private:

                    void constructDT(const const_buffer& buff , tpdu_size pdusize);

                    void constructCR(const protocol_options& opt);

                    void constructCC(const protocol_options& opt);

                    void constructER(int16_t dst, const std::string& errorreason, int8_t err);

                    void constructDR(int16_t dst, int16_t src, int8_t rsn);

                    tpdu_type                      type_;
                    send_buffer_ptr           buf_;
                } ;

                typedef boost::shared_ptr<send_seq>               send_seq_ptr;






                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////stream_socket                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       

                class stream_socket : public basic_stream_socket<tcp > {
                public:

                    explicit stream_socket(boost::asio::io_service& io_service, const std::string& called = "")
                    : basic_stream_socket<tcp>(io_service), pdusize_(SIZE4), option_(0, 1, pdusize_, called) {
                    }

                    stream_socket(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, const std::string& called = "")
                    : basic_stream_socket<tcp >(io_service, endpoint), pdusize_(SIZE4), option_(0, 1, pdusize_, called) {
                    }



                    ///   Connect operation  ///

                    void connect(const endpoint_type& peer_endpoint) {
                        boost::system::error_code ec;
                        connect(peer_endpoint, ec);
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code connect(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {
                        if (!is_open()) {
                            if (this->get_service().open(this->get_implementation(),
                                    peer_endpoint.protocol(), ec)) {
                                return ec;
                            }
                        }
                        return connect_impl(peer_endpoint, ec);
                    }


                    // connect handler

                    template <typename ConnectHandler>
                    class connect_op {

                        enum stateconnection {
                            request,
                            response
                        } ;

                    public:

                        connect_op(stream_socket* socket , ConnectHandler handler ,
                                const endpoint_type& peer_endpoint) :
                        socket_(socket),
                        handler_(handler),
                        state_(request),
                        options_(socket->prot_option()),
                        peer_endpoint_(peer_endpoint),
                        start_(1),
                        send_(send_seq_ptr( new send_seq(socket->prot_option()))),
                        receive_(new receive_seq()) {
                        }

                        void run() {
                            socket_->get_service().async_connect(socket_->get_implementation(), peer_endpoint_, *this);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec)
                                operator()(ec, 0);
                            else
                                handler_( ec);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case request:
                                    {
                                        switch (start_) {
                                            case 1:
                                            {
                                                start_ = 0;
                                                socket_->get_service().async_send(socket_->get_implementation(),  boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);
                                                return;
                                            }
                                            default:
                                            {
                                                send_->size(bytes_transferred);
                                                if (!send_->ready()) {
                                                    socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);
                                                    return;
                                                }
                                                else {
                                                    state(response);
                                                    operator()(ec, 0);
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                    case response:
                                    {
                                        switch (start_) {
                                            case 1:
                                            {
                                                start_ = 0;
                                                socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                        receive_->buffer() + receive_->size()) , 0 , *this);
                                                return;
                                            }
                                            default:
                                            {
                                                receive_->size(bytes_transferred);
                                                if (!receive_->ready()) {
                                                    socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                            receive_->buffer() + receive_->size()) , 0 , *this);
                                                    return;
                                                }
                                                finish(ec);
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                            handler_(ec);
                        }



                    private:

                        void finish(const boost::system::error_code& ec) {
                            if (receive_->state() == receive_seq::complete) {
                                switch (receive_->type()) {
                                    case CC:
                                    {
                                        handler_(ec);
                                        socket_->correspond_prot_option(receive_->options());
                                        std::cout << "connect_op success" << std::endl;
                                        return;
                                    }
                                    case ER:
                                    case DR:
                                    {
                                        boost::system::error_code ecc;
                                        socket_->get_service().close(socket_->get_implementation() , ecc);
                                        handler_(receive_->errcode() ? receive_->errcode() : ERROR_EIO);
                                        std::cout << "connect_op refuse :" << receive_->errcode() << std::endl;
                                        return;
                                    }
                                }
                            }
                            handler_(ERROR__EPROTO);
                        }

                        void state(stateconnection st) {
                            if (state_ != st) {
                                state_ = st;
                                start_ = 1;
                            }
                        }

                        stream_socket*                           socket_;
                        ConnectHandler                          handler_;
                        stateconnection                          state_;
                        protocol_options                        options_;
                        endpoint_type                             peer_endpoint_;
                        int                                                  start_;
                        send_seq_ptr                               send_;
                        receive_seq_ptr                           receive_;

                    } ;

                    template <typename ConnectHandler>
                    void async_connect(const endpoint_type& peer_endpoint,
                            BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

                        if (!is_open()) {
                            boost::system::error_code ec;
                            const protocol_type protocol = peer_endpoint.protocol();
                            if (this->get_service().open(this->get_implementation(), protocol, ec)) {
                                this->get_io_service().post(
                                        boost::asio::detail::bind_handler(
                                        BOOST_ASIO_MOVE_CAST(ConnectHandler)(handler), ec));
                                return;
                            }
                        }
                        this->get_io_service().post(boost::bind(&connect_op<ConnectHandler>::run, connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler, peer_endpoint)));
                    }





                    ///   Releease operation  ///    

                    void releaseconnect(int8_t rsn) {
                        boost::system::error_code ec;
                        releaseconnect(rsn, ec);
                        boost::asio::detail::throw_error(ec, "releaseconnect");
                    }

                    boost::system::error_code releaseconnect(int8_t rsn, boost::system::error_code& ec) {
                        return releaseconnect_impl(rsn, ec);
                    }

                    template <typename ReleaseHandler>
                    class releaseconnect_op {
                    public:

                        releaseconnect_op(stream_socket*  socket, ReleaseHandler handler, int8_t rsn) :
                        socket_(socket),
                        handler_(handler),
                        send_(send_seq_ptr( new send_seq(socket->prot_option().dst_tsap(),  socket->prot_option().src_tsap(), rsn))),
                        start_(1) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            std::size_t n = 0;
                            if (!ec) {
                                switch (start_) {
                                    case 1:
                                    {
                                        start_ = 0;
                                        socket_->get_service().async_send(socket_->get_implementation(),  boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);
                                        return;
                                    }
                                    default:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);
                                            return;
                                        }
                                    }
                                }
                            }
                            handler_(ec);
                        }


                    private:
                        stream_socket*                                              socket_;
                        ReleaseHandler                                              handler_;
                        send_seq_ptr                                                  send_;
                        int                                                                     start_;
                    } ;

                    template <typename ReleaseHandler>
                    void asyn_releaseconnect(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                            int8_t rsn = REJECT_REASON_NORM) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                        if (is_open()) {
                            this->get_io_service().post(boost::bind(&releaseconnect_op<ReleaseHandler>::run,
                                    releaseconnect_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, rsn)));
                        }
                        else
                            handler(ERROR_ECONNREFUSED);
                    }






                    ///  Check Accept operation  ///

                    void  check_accept(int16_t  src = 1) {
                        boost::system::error_code ec;
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code  check_accept(int16_t  src,  boost::system::error_code& ec) {
                        return check_accept_imp(src, ec);
                    }

                    template <typename CheckAcceptHandler>
                    class accept_op {

                        enum stateconnection {
                            wait,
                            send,
                            refuse
                        } ;

                    public:

                        accept_op(stream_socket* socket,  CheckAcceptHandler handler) :
                        socket_(socket),
                        handler_(handler),
                        state_(wait),
                        options_(socket->prot_option()),
                        start_(1),
                        send_(),
                        receive_(new receive_seq()) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case wait:
                                    {
                                        switch (start_) {
                                            case 1:
                                            {
                                                start_ = 0;
                                                socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                        receive_->buffer() + receive_->size()) , 0 , *this);
                                                return;
                                            }
                                            default:
                                            {
                                                receive_->size(bytes_transferred);
                                                if (!receive_->ready()) {
                                                    socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                            receive_->buffer() + receive_->size()) , 0 , *this);
                                                    return;
                                                }
                                                parse_response(ec);
                                                return;
                                            }
                                        }
                                    }
                                    case send:
                                    {
                                        switch (start_) {
                                            case 1:
                                            {
                                                start_ = 0;
                                                socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                        send_->receivesize()) , 0 , *this);
                                                return;
                                            }
                                            default:
                                            {
                                                send_->size(bytes_transferred);
                                                if (!send_->ready()) {
                                                    socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                            send_->receivesize()) , 0 , *this);
                                                    return;
                                                }
                                                finish(ec);
                                                return;
                                            }
                                        }
                                    }
                                    case refuse:
                                    {
                                        switch (start_) {
                                            case 1:
                                            {
                                                start_ = 0;
                                                socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                        send_->receivesize()) , 0 , *this);
                                                return;
                                            }
                                            default:
                                            {
                                                send_->size(bytes_transferred);
                                                if (!send_->ready()) {
                                                    socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                            send_->receivesize()) , 0 , *this);
                                                    return;
                                                }
                                                boost::system::error_code ecc;
                                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                                handler_(ERROR_EDOM);
                                                return;
                                            }
                                        }
                                    }
                                }
                            }
                            handler_(ec);
                        }



                    private:

                        void parse_response(const boost::system::error_code& ec) {
                            if (receive_->type() != CR || receive_->state() != receive_seq::complete) {
                                boost::system::error_code ecc;
                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                handler_(ERROR__EPROTO);
                                return;
                            }
                            if (!options_.tsap_called().empty() && options_.tsap_called() != receive_->options().tsap_called()) {
                                send_ = send_seq_ptr( new send_seq(receive_->options().src_tsap(), options_.src_tsap(), REJECT_REASON_ADDR));
                                state(refuse);
                                operator()(ec, 0);
                                return;
                            }
                            options_ = protocol_options(receive_->options().src_tsap(), options_.src_tsap(),
                                    less_tpdu(receive_->options().pdusize(), options_.pdusize()),
                                    options_.tsap_calling(), receive_->options().tsap_calling());
                            send_ = send_seq_ptr( new send_seq(1, options_));
                            state(send);
                            operator()(ec, 0);
                        }

                        void finish(const boost::system::error_code& ec) {
                            protocol_options  opt = receive_->options();
                            opt.pdusize(options_.pdusize());
                            socket_->correspond_prot_option(opt);
                            handler_(ec);
                            std::cout << "accept_op success" << std::endl;
                        }

                        void state(stateconnection st) {
                            if (state_ != st) {
                                state_ = st;
                                start_ = 1;
                            }
                        }



                        stream_socket*                              socket_;
                        CheckAcceptHandler                    handler_;
                        stateconnection                            state_;
                        protocol_options                          options_;
                        int                                                    start_;
                        send_seq_ptr                                 send_;
                        receive_seq_ptr                             receive_;

                    } ;

                    template <typename CheckAcceptHandler>
                    void asyn_check_accept(CheckAcceptHandler handler, int16_t  src) {
                        option_.src_tsap(src);
                        this->get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
                                accept_op<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler)));
                    }






                    ///   Send operation  ///                          

                    template <typename ConstBufferSequence>
                    std::size_t send(const ConstBufferSequence& buffers) {
                        return send(buffers, 0);
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags) {
                        boost::system::error_code ec;
                        std::size_t s = send(buffers, flags,  ec);
                        boost::asio::detail::throw_error(ec, "send");
                        return s;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t write_some(const ConstBufferSequence& buffers) {
                        boost::system::error_code ec;
                        std::size_t s = send(buffers, 0,  ec);
                        boost::asio::detail::throw_error(ec, "write_some");
                        return s;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t write_some(const ConstBufferSequence& buffers,
                            boost::system::error_code& ec) {
                        return send(buffers, 0, ec);
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        return send_impl(buffers, flags, ec);
                    }

                    template <typename SendHandler, typename Const_Buffers>
                    class send_op {
                    public:

                        send_op(stream_socket*   socket, SendHandler handler ,
                                const Const_Buffers& buffers, boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        in_(send_seq_ptr( new send_seq(buffers, socket->pdusize()))),
                        flags_(flags),
                        send_lower_(boost::asio::buffer_size(buffers)),
                        start_(1) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (start_) {
                                    case 1:
                                    {
                                        start_ = 0;
                                        socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(in_->pop(), in_->receivesize()) , flags_ , *this);
                                        return;
                                    }
                                    default:
                                    {
                                        in_->size(bytes_transferred);
                                        if (!in_->ready()) {
                                            socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(in_->pop(), in_->receivesize()) , flags_ , *this);
                                            return;
                                        }
                                    }
                                }
                            }
                            handler_(ec, static_cast<std::size_t> (send_lower_));
                        }


                    private:

                        stream_socket*                                             socket_;
                        SendHandler                                                  handler_;
                        send_seq_ptr                                                 in_;
                        boost::asio::socket_base::message_flags flags_;
                        std::size_t                                                       send_lower_;
                        int                                                                    start_;


                    } ;

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
                        this->get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
                    }

                    template <typename ConstBufferSequence, typename WriteHandler>
                    void async_write_some(const ConstBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {
                        async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                    }







                    ///   Recieve operation  ///     

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers) {
                        return receive<MutableBufferSequence > (buffer, 0);
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags) {
                        boost::system::error_code ec;
                        std::size_t s = receive( buffers, flags, ec);
                        boost::asio::detail::throw_error(ec, "receive");
                        return s;
                    }

                    template <typename MutableBufferSequence>
                    std::size_t read_some(const MutableBufferSequence& buffers,
                            boost::system::error_code& ec) {
                        return receive(buffers, 0, ec);
                    }

                    template <typename MutableBufferSequence>
                    std::size_t read_some(const MutableBufferSequence& buffers) {
                        boost::system::error_code ec;
                        std::size_t s =  receive(buffers, 0, ec);
                        boost::asio::detail::throw_error(ec, "read_some");
                        return s;
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        return receive_impl(buffers, flags, ec);
                    }

                    template <typename ReceiveHandler, typename Mutable_Buffers>
                    class receive_op {
                    public:

                        receive_op(stream_socket*   socket, ReceiveHandler handler ,
                                receive_seq_ptr out, const Mutable_Buffers& buff , boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        out_(out),
                        buff_(buff),
                        flags_(flags),
                        start_(1) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            std::size_t n = 0;
                            if (!ec) {
                                switch (start_) {
                                    case 1:
                                    {
                                        start_ = 0;
                                        socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                out_->buffer() + out_->size()) , flags_ , *this);
                                        ;
                                        return;
                                    }
                                    default:
                                    {

                                        out_->size(bytes_transferred);
                                        if (!out_->ready()) {
                                            socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(
                                                    out_->buffer() + out_->size()) , flags_ , *this);
                                            return;
                                        }
                                        if (!success()) return;
                                    }
                                }
                            };
                            handler_(ec, static_cast<std::size_t> (out_->size()));
                        }


                    private:

                        bool success() {
                            switch (out_->type()) {
                                case CR:
                                {
                                    boost::system::error_code decc;
                                    handler_( decc,  0);
                                    return false;
                                }
                                case DT:
                                {
                                    return true;
                                }
                                case ER:
                                {
                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_( ERROR__SEQ,  static_cast<std::size_t> (out_->size()));
                                    break;
                                }
                                case DR:
                                {
                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_( ERROR_ECONNREFUSED ,  static_cast<std::size_t> (out_->size()));
                                    break;
                                }
                                default:
                                {
                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_(ERROR__EPROTO ,  0);
                                }
                            }

                            return false;
                        }

                        stream_socket*                                              socket_;
                        ReceiveHandler                                              handler_;
                        const Mutable_Buffers&                               buff_;
                        receive_seq_ptr                                             out_;
                        boost::asio::socket_base::message_flags flags_;
                        int                                                                     start_;
                    } ;

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_receive(const MutableBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
                        async_receive<MutableBufferSequence, ReadHandler > (buffers, handler, 0 );
                    }

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                        BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                        this->get_io_service().post(boost::bind(&receive_op<ReadHandler, MutableBufferSequence>::run, receive_op<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                                receive_seq_ptr( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers))), buffers, 0)));

                    }

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_read_some(const MutableBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
                        async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                    }

                    tpdu_size pdusize() const {
                        return pdusize_;
                    };

                    const protocol_options& prot_option() const {
                        return option_;
                    }

                    void correspond_prot_option(const protocol_options& val) {
                        pdusize_ = val.pdusize();
                        std::cout << "correspond_prot_option tpdu size: " << tpdu_byte_size(pdusize_) << std::endl;
                        option_.dst_tsap(val.src_tsap());
                        std::cout << "correspond_prot_option calling  : " << val.tsap_calling() << std::endl;
                        std::cout << "correspond_prot_option called  : " << val.tsap_called() << std::endl;
                        std::cout << "correspond_prot_option dst id : " << option_.dst_tsap() << std::endl;
                        std::cout << "correspond_prot_option src id : " << option_.src_tsap() << std::endl;
                    }


                private:

                    boost::system::error_code connect_impl(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {

                        if (this->get_service().connect(this->get_implementation(), peer_endpoint, ec))
                            return ec;

                        send_seq_ptr  send_ (send_seq_ptr( new send_seq(prot_option())));
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        if (ec)
                            return ec;
                        receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->size(this->get_service().receive(this->get_implementation(), boost::asio::buffer(
                                    receive_->buffer() + receive_->size()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case CC:
                                {
                                    correspond_prot_option(receive_->options());
                                    std::cout << "connect_op success" << std::endl;
                                    return ec;
                                }
                                case ER:
                                case DR:
                                {
                                    boost::system::error_code ecc;
                                    this->get_service().close(this->get_implementation() , ecc);
                                    std::cout << "connect_op refuse :" << receive_->errcode() << std::endl;
                                    return ec = receive_->errcode() ? receive_->errcode() : ERROR_EIO;
                                }
                            }
                        }
                        return ec = ERROR__EPROTO;
                    }

                    boost::system::error_code releaseconnect_impl(int8_t rsn, boost::system::error_code& ec) {
                        if (is_open()) {
                            send_seq_ptr  send_ (send_seq_ptr( new send_seq(prot_option().dst_tsap(), prot_option().src_tsap(), rsn)));
                            while (!ec && !send_->ready())
                                send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                            return ec;
                        }
                        return ec =  ERROR_ECONNREFUSED;
                    }

                    boost::system::error_code  check_accept_imp(int16_t  src,  boost::system::error_code& ec) {
                        option_.src_tsap(src);
                        bool canseled = false;
                        receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->size(this->get_service().receive(this->get_implementation(), boost::asio::buffer(
                                    receive_->buffer() + receive_->size()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        send_seq_ptr  send_ ;
                        protocol_options options_ = this->prot_option();
                        if (receive_->type() != CR || receive_->state() != receive_seq::complete) {
                            return ERROR__EPROTO;
                        }
                        if (!options_.tsap_called().empty() && options_.tsap_called() != receive_->options().tsap_called()) {
                            canseled = true;
                            send_ = send_seq_ptr( new send_seq(receive_->options().src_tsap(), options_.src_tsap(), REJECT_REASON_ADDR));
                        }
                        else {
                            options_ = protocol_options(receive_->options().src_tsap(), options_.src_tsap(),
                                    less_tpdu(receive_->options().pdusize(), options_.pdusize()),
                                    options_.tsap_calling(), receive_->options().tsap_calling());
                            send_ = send_seq_ptr( new send_seq(1, options_));
                        }
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        if (ec)
                            return ec;
                        if (canseled ) {
                            boost::system::error_code ecc;
                            this->get_service().close(this->get_implementation(), ecc);
                        }
                        else {
                            protocol_options  opt = receive_->options();
                            opt.pdusize(options_.pdusize());
                            correspond_prot_option(receive_->options());
                        }
                        return ec = canseled ? ERROR_EDOM : ec;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send_impl(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        send_seq_ptr  send_( new send_seq(buffers, pdusize()));
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        return ec;
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive_impl(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        receive_seq_ptr receive_( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers)));
                        while (!ec && !receive_->ready()) {
                            receive_->size(this->get_service().receive(this->get_implementation(), boost::asio::buffer(
                                    receive_->buffer() + receive_->size()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        switch (receive_->type()) {
                            case CR:
                            case DT:  return receive_->size();
                            case ER:
                            case DR:
                            {
                                boost::system::error_code ecc;
                                this->get_service().close(this->get_implementation(), ecc);
                                ec = ( receive_->type() == DR)  ? ERROR_ECONNREFUSED :  ERROR__SEQ ;
                                return static_cast<std::size_t> (receive_->size());
                            }
                        }
                        boost::system::error_code ecc;
                        this->get_service().close(this->get_implementation(), ecc);
                        ec = ERROR__EPROTO;
                        return 0;
                    }


                    tpdu_size        pdusize_;
                    protocol_options option_;
                } ;



                ////  Acceptor


                namespace datail {

                    template <typename Protocol>
                    class socket_acceptor_service
                    : public boost::asio::socket_acceptor_service<tcp> {
                    public:

                        typedef boost::asio::socket_acceptor_service<tcp> service_impl_type;

                        /// The protocol type.
                        typedef tcp protocol_type;

                        /// The endpoint type.
                        typedef tcp::endpoint endpoint_type;


                        /// The implementation type of a stream socket.
                        typedef service_impl_type::implementation_type implementation_type;

                        /// The native type of a stream socket.
                        typedef service_impl_type::native_type native_type;

                        static boost::asio::io_service::id id;


                        /// Construct a new socket acceptor service for the specified io_service.

                        explicit socket_acceptor_service(boost::asio::io_service& io_service)
                        : boost::asio::socket_acceptor_service<tcp> (io_service),
                        service_impl_(boost::asio::use_service<service_impl_type>(io_service)), src_(0) {
                        }

                        template <typename SocketService>
                        boost::system::error_code accept(implementation_type& impl,
                                basic_socket<protocol_type, SocketService>& peer,
                                endpoint_type* peer_endpoint, boost::system::error_code& ec) {
                            std::cout << "socket acceptor: accept" << std::endl;
                            return service_impl_.accept(impl, peer, peer_endpoint, ec);
                        }

                        template <typename Handler, typename Socket>
                        class accept_handler {
                        public:

                            accept_handler(service_impl_type& service_impl, implementation_type& impl, Handler h, Socket& socket, endpoint_type* endpoint, int16_t  src)
                            : service_impl_(service_impl), impl_(impl), handler_(h), socket_(socket), endpoint_(endpoint), src_(src) {
                            }

                            void run() {
                                service_impl_.async_accept(impl_, socket_, endpoint_, *this);
                            }

                            void operator()(const boost::system::error_code& ec) {
                                if (!ec) {
                                    static_cast<stream_socket*> (&socket_)->asyn_check_accept<Handler > (handler_, src_);
                                    std::cout << "Asynchronous accept  succeeded first" << std::endl;
                                    return;
                                }
                                handler_(ec);
                            }

                        private:
                            service_impl_type&       service_impl_;
                            implementation_type& impl_;
                            Handler                           handler_;
                            Socket&                           socket_;
                            endpoint_type*              endpoint_;
                            int16_t                             src_;

                        } ;


                        /// Start an asynchronous accept.

                        template <typename SocketService, typename AcceptHandler>
                        void async_accept(implementation_type& impl,
                                basic_socket<protocol_type, SocketService>& peer,
                                endpoint_type* peer_endpoint, AcceptHandler handler) {
                            std::cout << "socket acceptor: asynaccept" << std::endl;
                            service_impl_.get_io_service().post(boost::bind(&accept_handler<AcceptHandler, basic_socket<protocol_type, SocketService> >::run ,
                                    accept_handler<AcceptHandler , basic_socket<protocol_type, SocketService> >(service_impl_, impl, handler, peer, peer_endpoint, src())));
                        }



                    private:

                        int16_t  src() const {
                            return src_ = ((src_ + 1) ? (src_ + 1) : 1);
                        }

                        service_impl_type&           service_impl_;
                        mutable int16_t                 src_;
                    } ;


                    template <typename Protocol>
                    boost::asio::io_service::id socket_acceptor_service<Protocol>::id;
                }

                class socket_acceptor : public basic_socket_acceptor<tcp , datail::socket_acceptor_service<tcp> > {
                public:

                    explicit socket_acceptor(boost::asio::io_service& io_service)
                    : basic_socket_acceptor<tcp , datail::socket_acceptor_service<tcp> >(io_service) {
                    }

                    socket_acceptor(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, bool reuse_addr = true)
                    : basic_socket_acceptor<tcp, datail::socket_acceptor_service<tcp> >(io_service, endpoint, reuse_addr) {

                    }

                } ;




            }

            class rfc1006 {
            public:
                /// The type of a TCP endpoint.
                typedef basic_endpoint<tcp>          endpoint;

                /// Construct to represent the IPv4 TCP protocol.

                static rfc1006 v4() {
                    return rfc1006(PF_INET);
                }

                /// Construct to represent the IPv6 TCP protocol.

                static rfc1006 v6() {
                    return rfc1006(PF_INET6);
                }

                /// Obtain an identifier for the type of the protocol.

                int type() const {
                    return SOCK_STREAM;
                }

                /// Obtain an identifier for the protocol.

                int protocol() const {
                    return IPPROTO_TCP;
                }

                /// Obtain an identifier for the protocol family.

                int family() const {
                    return family_;
                }

                /// The TCP socket type.
                typedef iec8073::stream_socket socket;

                /// The TCP acceptor type.
                typedef iec8073::socket_acceptor acceptor;

                /// The TCP resolver type.
                typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
                /// The TCP iostream type.
                typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_NO_IOSTREAM)


                typedef boost::asio::detail::socket_option::boolean<
                IPPROTO_TCP, TCP_NODELAY> no_delay;

                /// Compare two protocols for equality.

                friend bool operator==(const rfc1006& p1, const rfc1006& p2) {
                    return p1.family_ == p2.family_;
                }

                /// Compare two protocols for inequality.

                friend bool operator!=(const rfc1006& p1, const rfc1006& p2) {
                    return p1.family_ != p2.family_;
                }

            private:
                // Construct with a specific family.

                explicit rfc1006(int family)
                : family_(family) {
                }

                int family_;
            } ;




        } // namespace ip

        template<typename ReleaseConnectHandler>
        void asyn_releaseconnect( boost::asio::ip::iec8073::stream_socket& s, ReleaseConnectHandler  handler, int8_t rsn = boost::asio::ip::iec8073::REJECT_REASON_NORM) {
            s.asyn_releaseconnect<ReleaseConnectHandler > (handler, rsn);
        }


    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

