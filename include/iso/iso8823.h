/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef     ISOPROT8823_H_H
#define	ISOPROT8823_H_H


#include <iso/iso8327.h>
#include <iso/asn/itu_X690.h>


namespace boost {
    namespace asio {
        namespace iso {


            namespace prot8823 {



                typedef int                                                     context_id_type;
                typedef boost::asio::asn::bitstring_type            presentation_req_type;
                typedef boost::asio::asn::bitstring_type            userses_req_type;
                typedef boost::asio::asn::bitstring_type            presentation_ver_type;

                const presentation_ver_type PRSNT_VERSION = boost::asio::asn::bitstring_type(true, 0);

                const presentation_req_type PRSNT_CONTEXT_MREQ = boost::asio::asn::bitstring_type(true, 0);
                const presentation_req_type PRSNT_REST_MREQ = boost::asio::asn::bitstring_type(true, 1);
                const presentation_req_type PRSNT_NULL_MREQ = boost::asio::asn::bitstring_type((int8_t) 0, 6);

                typedef boost::asio::asn::x690::iarchive                                                                                    x690_iarchive_type;
                typedef boost::asio::asn::x690::oarchive                                                                                   x690_oarchive_type;
                typedef boost::asio::iso::archive_temp<x690_iarchive_type, x690_oarchive_type>              x690_archive;


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                typedef std::set<oid_type>   transfer_synaxes_type;

                class presentation_context_unit {
                public:

                    presentation_context_unit(const oid_type& asyntax, const encoding_rule& tsyntax );

                    oid_type abstract_syntax() const {
                        return abstract_syntax_;
                    }

                    const transfer_synaxes_type&  transfer_syntaxs() const {
                        return transfer_syntaxes_;
                    }

                    encoding_rule encoding() const {
                        return archiver_ ? archiver_->rule() : NULL_ENCODING;
                    }

                    bool encoding(encoding_rule val);

                    oid_type transfer_syntax() const {
                        return archiver_ ? archiver_->transfer_syntax() : oid_type();
                    }

                    bool transfer_syntax(const oid_type& val);

                    bool valid() {
                        return archiver_;
                    }

                    archive_ptr archiver() {
                        return archiver_;
                    }

                    template<typename T> bool set(T& data) {
                        if (archiver_) {
                            switch (encoding()) {
                                case BER_ENCODING:
                                case DER_ENCODING:
                                case CER_ENCODING:
                                {
                                    data.serialize(boost::static_pointer_cast<x690_archive , base_archive > (archiver_)->output());
                                    return true;
                                };
                                default:
                                {
                                }
                            }
                        }
                        return false;
                    }

                    template<typename T> bool get(T& data) {
                        if (archiver_) {
                            switch (encoding()) {
                                case BER_ENCODING:
                                case DER_ENCODING:
                                case CER_ENCODING:
                                {
                                    data.serialize(boost::static_pointer_cast<x690_archive , base_archive > (archiver_)->input());
                                    return true;
                                };
                                default:
                                {
                                }
                            }
                        }
                        return false;
                    }



                private:
                    oid_type abstract_syntax_;
                    transfer_synaxes_type transfer_syntaxes_;
                    archive_ptr archiver_;
                } ;

                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                typedef boost::shared_ptr<presentation_context_unit>   presentation_context_unit_ptr;

                bool operator<(presentation_context_unit_ptr ls, presentation_context_unit_ptr rs);

                typedef std::set<presentation_context_unit_ptr>  presentation_context_unit_set;


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////           

                class presentation_connection_option {
                public:

                    presentation_connection_option(const oid_type& asyntax, const encoding_rule& tsyntax = BER_ENCODING, const presentation_req_type& req = presentation_req_type());

                    presentation_connection_option(const oid_type& asyntax1, const oid_type& asyntax2, const encoding_rule& tsyntax = BER_ENCODING , const presentation_req_type& req = presentation_req_type());

                    const presentation_req_type&  p_requirements() const {
                        return preq_;
                    }

                    const presentation_context_unit_set& abstract_syntaxes() const {
                        return connection_syntax_;
                    }

                    presentation_context_unit_set abstract_syntaxes() {
                        connection_syntax_;
                    }

                    void insert_abstract_syntax(presentation_context_unit_ptr val) {
                        connection_syntax_.insert(val);
                    }

                    void insert_abstract_syntax(const oid_type& asyntax, const encoding_rule& tsyntax = BER_ENCODING );

                    bool has_abstract_syntax(const oid_type& asyntax, const encoding_rule& tsyntax = BER_ENCODING );

                private:

                    presentation_context_unit_set  connection_syntax_;
                    presentation_req_type  preq_;

                } ;


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


                typedef std::pair<context_id_type, presentation_context_unit_ptr>   presentation_context_type;
                typedef std::map<context_id_type, presentation_context_unit_ptr>  presentation_context_map;


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////                

                class presentation_pm {
                public:

                    presentation_pm(const presentation_connection_option& opt , context_id_type  id = 1 );

                    presentation_pm(const presentation_req_type& preq = PRSNT_NULL_MREQ , context_id_type  id = 1 );

                    presentation_context_unit_ptr  default_context() const {
                        return (is_default_context() && (!contexts_.empty())) ? contexts_.begin()->second : presentation_context_unit_ptr();
                    }

                    context_id_type insert_context(context_id_type id, const oid_type& asyntax, const encoding_rule& tsyntax  = BER_ENCODING);

                    context_id_type insert_context(context_id_type id, presentation_context_unit_ptr ctx);

                    context_id_type remove_contex(context_id_type id);

                    archive_ptr find(context_id_type id) {
                        presentation_context_map::iterator it = contexts_.find(id);
                        return it != contexts_.end() ? it->second->archiver() : archive_ptr();
                    }

                    archive_ptr exists(context_id_type id) {
                        presentation_context_map::iterator it = contexts_.find(id);
                        return it != contexts_.end() ? it->second->archiver() : archive_ptr();
                    }

                    void clear() {
                        for (presentation_context_map::iterator it = contexts_.begin(); it != contexts_.end(); ++it) {
                            if (it->second->archiver())
                                it->second->archiver()->clear();
                        }
                    }

                    void clear_output() {
                        for (presentation_context_map::iterator it = contexts_.begin(); it != contexts_.end(); ++it) {
                            if (it->second->archiver())
                                it->second->archiver()->clear_output();
                        }
                    }

                    void clear_input() {
                        for (presentation_context_map::iterator it = contexts_.begin(); it != contexts_.end(); ++it) {
                            if (it->second->archiver())
                                it->second->archiver()->clear_input();
                        }
                    }

                    bool has_input() const {
                        for (presentation_context_map::const_iterator it = contexts_.begin(); it != contexts_.end(); ++it) {
                            if (it->second->archiver() && (it->second->archiver()->in()->size())) return true;
                        }
                        return false;
                    }

                    bool transfer_syntax(context_id_type id, const oid_type& val) {
                        presentation_context_map::iterator it = contexts_.find(id);
                        if (it != contexts_.end()) {
                            it->second->transfer_syntax(val);
                            return true;
                        }
                        return false;
                    }

                    template<typename T> bool set(context_id_type id, T& data) {
                        presentation_context_map::iterator it = contexts_.find(id);
                        if (it != contexts_.end())
                            return it->second->set(data);
                        return false;
                    }

                    template<typename T> bool get(context_id_type id, T& data) {
                        presentation_context_map::iterator it = contexts_.find(id);
                        if (it != contexts_.end())
                            return it->second->get(data);
                        return false;
                    }

                    template<typename T> bool set(const oid_type& oid, T& data) {
                        presentation_context_map::iterator it = find(oid);
                        if (it != contexts_.end())
                            return it->second->set(data);
                        return false;
                    }

                    template<typename T> bool get(const oid_type& oid , T& data) {
                        presentation_context_map::iterator it = find(oid);
                        if (it != contexts_.end())
                            return it->second->get(data);
                        return false;
                    }

                    presentation_context_map&  contexts() {
                        return contexts_;
                    }

                    const presentation_context_map&  contexts() const {
                        return contexts_;
                    }

                    const presentation_req_type&  p_requirements() const {
                        return preq_;
                    }

                    void p_requirements(const presentation_req_type& val) {
                        preq_ = val;
                    }

                    bool is_context_menagment() const {
                        return ((!preq_.empty()) && (preq_.bit(0)));
                    }

                    bool is_restoration() const {
                        return ((preq_.size() > 1) && (preq_.bit(1)));
                    }

                    bool is_simple_encoding() const {
                        return  ((contexts_.size() == 1) && (!is_context_menagment()));
                    }

                    bool is_default_context() const {
                        return  ((contexts_.size() == 1) && (!is_context_menagment()));
                    }


                private:

                    context_id_type insert_context(presentation_context_unit_ptr ctx);

                    context_id_type insert_context(const oid_type& asyntax, const encoding_rule& tsyntax = BER_ENCODING);

                    presentation_context_map::iterator find(const oid_type& oid);


                    context_id_type                    nextid_;
                    presentation_req_type           preq_;
                    presentation_context_map     contexts_;

                } ;

                typedef boost::shared_ptr<presentation_pm>   presentation_pm_ptr;


                const std::size_t BUFFER_SIZE = 512;

                enum ppdu_enum {
                    null_ppdu,
                    error_ppdu,
                    cp_ppdu,
                    cpa_ppdu,
                    cpr_ppdu,
                    dt_ppdu,
                    ac_ppdu,
                    aca_ppdu,
                    aru_ppdu,
                    arp_ppdu
                } ;



                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////stream_socket                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                class stream_socket : protected boost::asio::iso::prot8327::stream_socket  {
                    typedef x690_iarchive_type                                                                                              input_archive_type;
                    typedef x690_oarchive_type                                                                                             output_archive_type;
                    typedef x690_archive                                                                                                       presentation_archive;
                    typedef boost::shared_ptr<presentation_archive>                                                              presentation_archive_ptr;
                    typedef boost::asio::iso::prot8327::stream_socket                                                             super_type;

                public:

                    explicit stream_socket(boost::asio::io_service& io_service, const presentation_selector& psel, const presentation_connection_option& connectoption)
                    : super_type(io_service,  psel.sselector()),
                    basiccoder(new presentation_archive()),  selector_ (psel),  ppm_( new presentation_pm(connectoption)) {
                    }

                    stream_socket(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, const presentation_selector& psel)
                    : super_type(io_service, psel.sselector()),
                    basiccoder(new presentation_archive()), selector_ (psel),  ppm_( new presentation_pm())  {
                    }

                    void connect(const endpoint_type& peer_endpoint) {
                        boost::system::error_code ec;
                        connect(peer_endpoint,  ec);
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code connect(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {
                        if (!ppm()) {
                            ec = ERROR_EDOM;
                            return ec;
                        }
                        if (!is_open()) {
                            if (this->get_service().open(this->get_implementation(),
                                    peer_endpoint.protocol(), ec)) {
                                return ec;
                            }
                        }
                        return connect_impl(peer_endpoint, ec);
                    }



                    ///

                private:

                    template <typename ConnectHandler>
                    class connect_op {
                    public:

                        connect_op(stream_socket* socket , ConnectHandler handler) : socket_(socket), handler_(handler) {
                        }

                        void run(const boost::system::error_code& ec) {
                            operator()(ec);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec) {
                                socket_->parse_CR();
                            }

                            socket_->clear_output();

                            handler_( ec);
                        }

                    private:

                        stream_socket*                           socket_;
                        ConnectHandler                           handler_;
                    } ;


                public:

                    template <typename ConnectHandler>
                    void async_connect(const endpoint_type& peer_endpoint,
                            BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {

                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                        if (!ppm()) {
                            handler(ERROR_EDOM);
                            return;
                        }
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
                        clear_input();
                        build_CP_type();
                        super_type::async_connect(peer_endpoint, coder() , boost::bind(&connect_op<ConnectHandler>::run,
                                connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));
                    }


                private:

                    template <typename RequestHandler>
                    class request_op {
                    public:

                        request_op(stream_socket* socket , RequestHandler handler) :

                        socket_(socket),
                        handler_(handler) {
                        }

                        void run(const boost::system::error_code& ec) {
                            operator()(ec);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec) {
                                //socket_->parse_CR();
                            }

                            socket_->clear_output();

                            handler_( ec);
                        }

                    private:
                        stream_socket*                           socket_;
                        RequestHandler                           handler_;
                    } ;


                public:

                    template <typename RequestHandler>
                    void async_request(
                            BOOST_ASIO_MOVE_ARG(RequestHandler) handler) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

                        clear_input();

                        build_DT_type();

                        super_type::async_write_some( coder()->output().const_buffers() , boost::bind(&request_op<RequestHandler>::run,
                                request_op<RequestHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));
                    }

                private:

                    template <typename RespondHandler>
                    class respond_op {
                    public:

                        respond_op(stream_socket* socket , RespondHandler handler) :
                        socket_(socket),
                        handler_(handler) {
                        }

                        void run(const boost::system::error_code& error, size_t bytes_transferred) {
                            operator()(error, bytes_transferred);
                        }

                        void operator()(const boost::system::error_code& error, size_t bytes_transferred) {
                            if (!error) {
                                socket_->coder()->input().add(raw_type(socket_->databuff, socket_->databuff + bytes_transferred));
                                if (!socket_->input_empty()) {
                                    socket_->super_type::async_read_some(
                                            boost::asio::buffer(socket_->databuff, BUFFER_SIZE),
                                            boost::bind(&respond_op<RespondHandler >::run,
                                            respond_op<RespondHandler > (socket_, handler_)   , boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                                    return;
                                }
                                else {
                                    socket_->parse_RESPONSE();
                                }
                            }

                            socket_->clear_output();

                            handler_(error);
                        }

                    private:
                        stream_socket*                           socket_;
                        RespondHandler                           handler_;

                    } ;


                public:

                    template <typename RespondHandler>
                    void async_respond(
                            BOOST_ASIO_MOVE_ARG(RespondHandler) handler) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(RespondHandler, handler) type_check;

                        ppm()->clear_input();
                        coder()->clear_input();

                        super_type::async_read_some( boost::asio::buffer(databuff,  BUFFER_SIZE),
                                boost::bind(&respond_op<RespondHandler >::run,
                                respond_op<RespondHandler > (const_cast<stream_socket*> (this), handler) , boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
                    }

                    presentation_pm_ptr ppm() {
                        return ppm_;
                    }

                    presentation_pm_ptr ppm() const {
                        return ppm_;
                    }

                    void clear_input() {
                        if (ppm())
                            ppm()->clear_input();
                        coder()->clear_input();
                    }

                    void clear_output() {
                        if (ppm())
                            ppm()->clear_output();
                        coder()->clear_output();
                    }

                protected:

                    presentation_archive_ptr coder() {
                        return basiccoder;
                    }

                    presentation_archive_ptr coder() const {
                        return basiccoder;
                    }

                    presentation_selector& selector() {
                        return selector_;
                    }

                    const presentation_selector& selector() const {
                        return selector_;
                    }



                private:

                    boost::system::error_code connect_impl(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {
                        build_CP_type();
                        if (!super_type::connect(peer_endpoint,  coder() , ec)) {
                            parse_CR();
                            return ec;
                        }
                        return ec;
                    }

                    ppdu_enum check_response();

                    void build_CP_type();

                    void build_DT_type();

                    ppdu_enum parse_CR();

                    ppdu_enum parse_RESPONSE();

                    presentation_archive_ptr                                      basiccoder;
                    presentation_selector                                           selector_;
                    presentation_pm_ptr                                            ppm_;
                    int8_t                                                                  databuff[BUFFER_SIZE];


                } ;

                class socket_acceptor : public boost::asio::iso::iec8073_tcp::socket_acceptor  {
                    typedef boost::asio::iso::iec8073_tcp::socket_acceptor       super_type;

                public:

                    /* explicit socket_acceptor(boost::asio::io_service& io_service)
                     : boost::asio::iso::iec8073_tcp::socket_acceptor(io_service) {
                     }

                     socket_acceptor(boost::asio::io_service& io_service,
                             const endpoint_type& endpoint, bool reuse_addr = true)
                     : boost::asio::iso::iec8073_tcp::socket_acceptor(io_service, endpoint, reuse_addr) {
                     }



                 public:

                     template <typename SocketService>
                     void accept(basic_socket<protocol_type, SocketService>& peer) {
                         boost::system::error_code ec;
                         accept_impl(peer, archive_ptr(), ec);
                         boost::asio::detail::throw_error(ec, "accept");
                     }

                     template <typename SocketService>
                     boost::system::error_code accept(
                             basic_socket<protocol_type, SocketService>& peer,
                             boost::system::error_code& ec) {
                         return accept_impl(peer,  archive_ptr(), ec);
                     }

                     template <typename SocketService>
                     void accept(basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint) {
                         boost::system::error_code ec;
                         accept_impl(peer, peer_endpoint, archive_ptr(), ec);
                         boost::asio::detail::throw_error(ec, "accept");
                     }

                     template <typename SocketService>
                     boost::system::error_code accept(
                             basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint, boost::system::error_code& ec) {
                         return accept_impl(peer, peer_endpoint, archive_ptr(), ec);
                     }

                     template <typename SocketService>
                     void accept(basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata) {
                         boost::system::error_code ec;
                         accept_impl(peer, transdata , ec);
                         boost::asio::detail::throw_error(ec, "accept");
                     }

                     template <typename SocketService>
                     boost::system::error_code accept(
                             basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata,
                             boost::system::error_code& ec) {
                         return accept_impl(peer, transdata , ec);
                     }

                     template <typename SocketService>
                     void accept(basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint, archive_ptr  transdata) {
                         boost::system::error_code ec;
                         accept_impl(peer, peer_endpoint, transdata, ec);
                         boost::asio::detail::throw_error(ec, "accept");
                     }

                     template <typename SocketService>
                     boost::system::error_code accept(
                             basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata,
                             endpoint_type& peer_endpoint, boost::system::error_code& ec) {
                         return accept_impl(peer, peer_endpoint, transdata, ec);
                     }

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept(basic_socket<protocol_type, SocketService>& peer,
                             BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         async_accept_impl(peer,  archive_ptr(),  BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                     }

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept(basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         async_accept_impl(peer, peer_endpoint ,  archive_ptr(), BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                     }

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept(basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata,
                             BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         async_accept_impl(peer,  transdata ,  BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                     }

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept(basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint,  archive_ptr  transdata, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         async_accept_impl(peer, peer_endpoint ,  transdata, BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                     }

                 private:

                     template <typename Handler>
                     class accept_op {
                     public:

                         accept_op(Handler h,  stream_socket* socket, archive_ptr transdata)
                         :  handler_(h), socket_(socket),  transdata_( transdata) {
                         }

                         void operator()(const boost::system::error_code& ec) {
                             if (!ec)
                                 static_cast<stream_socket*> (socket_)->asyn_check_accept(handler_, transdata_);
                             else
                                 handler_(ec);
                         }

                     private:
                         Handler                              handler_;
                         stream_socket*                socket_;
                         archive_ptr                transdata_;
                     } ;

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept_impl(basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint, archive_ptr  transdata, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         super_type::async_accept(peer,  peer_endpoint, accept_op<AcceptHandler > (handler, static_cast<stream_socket*> (&peer), transdata));
                     }

                     template <typename SocketService, typename AcceptHandler>
                     void async_accept_impl(basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata,
                             BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                         BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                         super_type::async_accept(peer,   accept_op<AcceptHandler > (handler , static_cast<stream_socket*> (&peer), transdata));
                     }

                     template <typename SocketService>
                     boost::system::error_code accept_impl(
                             basic_socket<protocol_type, SocketService>& peer,
                             endpoint_type& peer_endpoint, archive_ptr  transdata, boost::system::error_code& ec) {
                         super_type::accept(peer, peer_endpoint, ec);
                         if (ec)
                             return ec;
                         static_cast<stream_socket*> ( &peer)->check_accept(transdata, ec);
                         return ec;
                     }

                     template <typename SocketService>
                     boost::system::error_code accept_impl(
                             basic_socket<protocol_type, SocketService>& peer, archive_ptr  transdata,
                             boost::system::error_code& ec) {
                         super_type::accept(peer,  ec);
                         if (ec)
                             return ec;
                         static_cast<stream_socket*> ( &peer)->check_accept(transdata, ec);
                         return ec;
                     }*/


                } ;

            }

            class iso8823 {
            public:
                /// The type of a TCP endpoint.

                typedef boost::asio::ip::basic_endpoint<boost::asio::ip::tcp>          endpoint;

                typedef presentation_selector                                                         selector;

                typedef session_selector                                                               lowselector;

                typedef transport_selector                                                             lowerselector;

                /// Construct to represent the IPv4 TCP protocol.

                static iso8823 v4() {

                    return iso8823(PF_INET);
                }

                /// Construct to represent the IPv6 TCP protocol.

                static iso8823 v6() {

                    return iso8823(PF_INET6);
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
                typedef prot8823::stream_socket socket;

                /// The TCP acceptor type.
                typedef prot8823::socket_acceptor acceptor;

                /// The TCP resolver type.
                typedef boost::asio::ip::basic_resolver<boost::asio::ip::tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
                /// The TCP iostream type.
                typedef basic_socket_iostream<boost::asio::ip::tcp> iostream;
#endif // !defined(BOOST_NO_IOSTREAM)


                typedef boost::asio::detail::socket_option::boolean<
                IPPROTO_TCP, TCP_NODELAY> no_delay;

                /// Compare two protocols for equality.

                friend bool operator==(const iso8823& p1, const iso8823& p2) {

                    return p1.family_ == p2.family_;
                }

                /// Compare two protocols for inequality.

                friend bool operator!=(const iso8823& p1, const iso8823& p2) {

                    return p1.family_ != p2.family_;
                }

            private:
                // Construct with a specific family.

                explicit iso8823(int family)
                : family_(family) {
                }

                int family_;
            } ;

            typedef boost::asio::iso::prot8823::presentation_pm_ptr                  presentation_pm_ptr;
            typedef boost::asio::iso::prot8823::presentation_connection_option   presentation_option;

        }
    } // namespace asio
} // namespace boost



#endif	

