/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOPROT8823_H_H
#define	ISOPROT8823_H_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <iso/iso.h>
#include <iso/iso8327.h>
#include <iso/asn/itu_X690.h>
#include <boost/asio/detail/push_options.hpp>


#include <iso/archive_stream.h>
#include <iso/presentation/ISO8823-PRESENTATION.h>


namespace boost {
    namespace asio {
        namespace iso {

            typedef ISO8823_PRESENTATION::Transfer_syntax_name transfer_syntax_type;
            typedef ISO8823_PRESENTATION::Abstract_syntax_name abstract_syntax_type;
            typedef std::vector<transfer_syntax_type > transfer_syntaxs_list;



            typedef std::set<oid_type>   transfer_synaxes_type;

            class presentation_context {
            public:

                presentation_context(int id_, const oid_type& asyntax, const encoding_rule& tsyntax, const transfer_synaxes_type&  tsxs);

                presentation_context(int id_, const oid_type& asyntax, const transfer_synaxes_type&  tsxs);

                oid_type abstract_syntax() const {
                    return archiver_ ? archiver_->abstract_syntax() : oid_type();
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


            private:
                oid_type abstract_syntax_;
                transfer_synaxes_type transfer_syntaxes_;
                archive_ptr archiver_;
            } ;

            ///

            class presentation_pm {
            public:

                presentation_pm(const default_context_type& dctx ) :  default_context_( new default_context_type(dctx)) {
                }

                default_context_ptr  default_context() const {
                    return default_context_;
                }

                void  default_context(default_context_ptr val)  {
                    default_context_ = val;
                }

            private:

                default_context_ptr  default_context_;
            } ;


            namespace prot8823 {



                typedef ISO8823_PRESENTATION::CP_type CP_type;
                typedef ISO8823_PRESENTATION::Mode_selector p_mode_type;
                typedef ISO8823_PRESENTATION::Called_presentation_selector p_cd_selector;
                typedef ISO8823_PRESENTATION::Calling_presentation_selector p_cng_selector;
                typedef ISO8823_PRESENTATION::Context_list_sequence_of p_context_type;
                typedef ISO8823_PRESENTATION::Fully_encoded_data p_full_data_type;
                typedef ISO8823_PRESENTATION::PDV_list pdv_list_type;


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////stream_socket                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                class stream_socket : protected boost::asio::iso::iso8327::socket  {
                    typedef boost::asio::asn::x690::iarchive                                                                          input_archive_type;
                    typedef boost::asio::asn::x690::oarchive                                                                         output_archive_type;
                    typedef boost::asio::iso::archive_temp<input_archive_type, output_archive_type>              presentation_archive;
                    typedef boost::asio::iso::iso8327::socket    super_type;

                public:

                    explicit stream_socket(boost::asio::io_service& io_service, const presentation_selector& psel)
                    : boost::asio::iso::iso8327::socket(io_service,  psel.sselector()),
                    selector_ (psel), basiccoder(new presentation_archive()) {
                    }

                    stream_socket(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, const presentation_selector& psel)
                    : boost::asio::iso::iso8327::socket(io_service, psel.sselector()),
                    selector_ (psel), basiccoder(new presentation_archive())  {
                    }

                    template <typename ConnectHandler>
                    class connect_opp {
                    public:

                        connect_opp(stream_socket* socket , ConnectHandler handler ,
                                const endpoint_type& peer_endpoint, archiver_map archs) :
                        socket_(socket),
                        handler_(handler),
                        peer_endpoint_(peer_endpoint),
                        archs_(archs) {

                        }

                        void run(const boost::system::error_code& ec) {
                            operator()(ec);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec) {
                                socket_->parse_CR(archs_);
                            }

                            handler_( ec);
                        }



                    private:


                        stream_socket*                           socket_;
                        ConnectHandler                           handler_;
                        endpoint_type                          peer_endpoint_;
                        archiver_map                          archs_;

                    } ;


                public:

                    template <typename ConnectHandler>
                    void async_connect(const endpoint_type& peer_endpoint, archiver_map archs,
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
                        build_CP(archs);
                        super_type::async_connect(peer_endpoint, basiccoder, boost::bind(&connect_opp<ConnectHandler>::run, connect_opp<ConnectHandler > (const_cast<stream_socket*> (this), handler, peer_endpoint, archs), boost::asio::placeholders::error));
                    }



                private:

                    void build_CP(archiver_map archs) {
                        this->basiccoder->clear();
                        CP_type cp;
                        cp.mode_selector.mode_value = p_mode_type::mode_value_normal_mode;
                        cp.normal_mode_parameters__new();
                        if (!selector_.called().empty())
                            cp.normal_mode_parameters->called_presentation_selector__assign(p_cd_selector(selector_.called()));
                        if (!selector_.calling().empty())
                            cp.normal_mode_parameters->calling_presentation_selector__assign(p_cng_selector(selector_.calling()));
                        /* if (option_.option().default_conext())
                             cp.normal_mode_parameters->default_context_name = option_.option().default_conext();
                         if (option_.option().p_requirements())
                             cp.normal_mode_parameters->presentation_requirements = option_.option().p_requirements();
                         if (option_.option().u_requirements())
                             cp.normal_mode_parameters->user_session_requirements = option_.option().u_requirements();*/
                        //if (!option_.option().conexts().empty()) {
                        cp.normal_mode_parameters->presentation_context_definition_list__new();
                        for (archiver_map::iterator it = archs.begin(); it != archs.end(); ++it) {
                            p_context_type ctx;
                            ctx.abstract_syntax_name = it->second->abstract_syntax();
                            ctx.presentation_context_identifier = it->first;
                            ctx.transfer_syntax_name_list = ISO8823_PRESENTATION::Context_list_sequence_of::transfer_syntax_name_list_type(1, BASIC_ENCODING_OID);
                            cp.normal_mode_parameters->presentation_context_definition_list->push_back(ctx);
                        }
                        cp.normal_mode_parameters->user_data.fully_encoded_data(new p_full_data_type());
                        for (archiver_map::iterator it = archs.begin(); it != archs.end(); ++it) {
                            if (it->second->out() && it->second->out()->size()) {
                                pdv_list_type pdv_lst;
                                pdv_lst.presentation_context_identifier = it->first;
                                //pdv_lst.transfer_syntax_name__new();
                                pdv_lst.presentation_data_values.single_ASN1_type( new boost::asio::asn::any_type());
                                pdv_lst.presentation_data_values.single_ASN1_type()->bind(*(it->second->out()));
                                cp.normal_mode_parameters->user_data.fully_encoded_data()->push_back(pdv_lst);
                            }
                        }
                        //}
                        (basiccoder->output()) & cp;
                    }

                    bool parse_CR(archiver_map archs) {
                        int cl = this->basiccoder->input().test_class();
                        int id = this->basiccoder->input().test_id();
                        switch (this->basiccoder->input().test_class()) {

                        }
                        return false;
                    }

                    boost::system::error_code connect_impl(const endpoint_type& peer_endpoint, archiver_map archs,
                            boost::system::error_code& ec) {
                        return ec = ERROR__EPROTO;
                    }


                    presentation_selector                                           selector_;
                    boost::shared_ptr<presentation_archive>               basiccoder;

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

        }





    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	

