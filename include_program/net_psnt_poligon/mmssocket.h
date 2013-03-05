/* 
 * File:   mmssocket.h
 * Author: sealeks@mail.ru
 *
 * Created on 27 Февраль 2013 г., 22:26
 */

#ifndef MMSSOCKET_H
#define	MMSSOCKET_H

#include <iso/iso8823.h>
#include <iso/mms/MMS-SCI-Module-1.h>



#define BOOST_MMS_REGESTRATE_ENUM_TYPE_(regtype)  inline get_enum_by_mms_type

namespace prot9506 {
    
    
    namespace ACSE = ACSE_1;
    namespace MMS = ISO_9506_MMS_1;
    namespace MMSO = MMS_Object_Module_1;
    
  
    




    typedef boost::asio::iso::presentation_pm_ptr                  presentation_pm_ptr;
    typedef boost::asio::iso::presentation_option                    presentation_option;

    using boost::asio::iso::presentation_selector;


    const boost::array<boost::asio::asn::oidindx_type, 5 > MMS_ARR = {1, 0, 9506 , 2,  1};
    const boost::asio::asn::oid_type MMS_OID = boost::asio::asn::oid_type(MMS_ARR);

    const boost::array<boost::asio::asn::oidindx_type, 5 > MMSA_ARR = {1, 0, 9506 , 2,  3};
    const boost::asio::asn::oid_type MMSA_OID = boost::asio::asn::oid_type(MMSA_ARR);
    
    
     typedef MMSO::Unsigned32  invoke_id_type;    


    presentation_option init_synaxes();
    
    
    template< typename REQ, typename RSP, MMS::ConfirmedServiceRequest_enum REQID, MMS::ConfirmedServiceResponse_enum RSPID >
    class confermed_operation{     
    public:
        
        typedef REQ                             request_type;
        typedef RSP                              response_type;
        typedef MMS::RejectPDU       reject_type;
        
        typedef boost::shared_ptr<request_type>      request_type_ptr;
        typedef boost::shared_ptr<response_type>   response_type_ptr;   
        typedef boost::shared_ptr<reject_type>         reject_type_ptr;          
        
        enum state{
            noproccess_state,
            ok_state,
            rejected_state,
            error_state
        };
        
        confermed_operation() : error_() {}
        
        request_type&  request() {
            if (!request_)  request_=request_type_ptr( new request_type());
            return *request_;
        } 
        
        response_type&  request() {
            if (!response_)  response_=response_type_ptr( new response_type());
            return *response_;
        }       
        
        reject_type&  reject() {
            if (!reject_)  reject_=reject_type_ptr( new reject_type());
            return *reject_;
        }             
        
        MMS::ConfirmedServiceRequest_enum reqid() const {
            return REQID; }
        
        MMS::ConfirmedServiceResponse_enum rspid() const {
            return RSPID; }            
        
        
    private:
        request_type_ptr  request_;
        response_type_ptr  response_;   
        reject_type_ptr          reject_;
        boost::system::error_code  error_;
    };



    void identify_request( presentation_pm_ptr ppm);
    boost::system::error_code identify_response(presentation_pm_ptr ppm);

    using boost::asio::iso::presentation_selector;

    class stream_socket : public boost::asio::iso::prot8823::stream_socket  {
        
        typedef boost::asio::iso::prot8823::stream_socket                                          super_type;       
        typedef boost::asio::iso::prot8823::presentation_context_unit_ptr    application_context_ptr;
        

    public:

        explicit stream_socket(boost::asio::io_service& io_service, const presentation_selector& psel = presentation_selector())
        :  super_type(io_service,  psel , init_synaxes()) {
        }

        stream_socket(boost::asio::io_service& io_service,
                const endpoint_type& endpoint, const presentation_selector& psel = presentation_selector())
        : super_type(io_service, endpoint, psel.sselector())  {

        }


    private:

        template <typename ConnectHandler>
        class connect_op {
        public:

            connect_op(stream_socket* socket , const ConnectHandler handler) : socket_(socket), handler_(handler) {
            }

            void run(const boost::system::error_code& ec) {
                operator()(ec);
            }

            void operator()(const boost::system::error_code& ec) {
               if (!ec) {
                      socket_->init_response();
                      handler_(ec);
                      return;
                 }


               handler_( ec);
            }

        private:

            stream_socket*                            socket_;
            ConnectHandler                          handler_;
        } ;





    public:

        template <typename ConnectHandler>
        void async_connect(const endpoint_type& peer_endpoint,
                BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {


            boost::system::error_code error = init_request();
            if (error){
                handler(error);
            }
                

            super_type::async_connect(peer_endpoint , boost::bind(&connect_op<ConnectHandler>::run,
                                connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));
        }
        
    protected:
        
        
            application_context_ptr   acseppm(){
                return acseppm_;   
            }     
            
            application_context_ptr   acseppm() const {
                return acseppm_;   
            }       
            
            application_context_ptr   mmsppm(){
                return mmsppm_;   
            }     
            
            application_context_ptr   mmsppm() const {
                return mmsppm_;   
            }                  
                    
        
        
        
    private:
        
            boost::system::error_code  init_request();
            boost::system::error_code init_response();
            
            boost::system::error_code identify_request();
            boost::system::error_code identify_response();
             
             application_context_ptr   acseppm_;
             application_context_ptr   mmsppm_;

    } ;


    /////////////////////////////

    class socket_acceptor : public boost::asio::iso::prot8823::socket_acceptor  {
        typedef boost::asio::iso::prot8823::socket_acceptor      super_type;
        typedef boost::asio::basic_socket<protocol_type, boost::asio::socket_acceptor_service< protocol_type > >   basic_socket_type;

    public:

        explicit socket_acceptor(boost::asio::io_service& io_service)
        :  super_type(io_service, init_synaxes()) {
        }

        socket_acceptor(boost::asio::io_service& io_service,
                const endpoint_type& endpoint,  bool reuse_addr = true)
        :  super_type(io_service, endpoint, init_synaxes(), reuse_addr) {
        }




        /* template <typename SocketService>
         boost::system::error_code accept(
                 basic_socket<protocol_type, SocketService>& peer,
                 boost::system::error_code& ec) {
             return accept_impl(peer, ec);
         }

         template <typename SocketService>
         boost::system::error_code accept(
                 basic_socket<protocol_type, SocketService>& peer,
                 endpoint_type& peer_endpoint, boost::system::error_code& ec) {
             return accept_impl(peer, peer_endpoint, ec);
         }

         template <typename SocketService, typename AcceptHandler>
         void async_accept(basic_socket<protocol_type, SocketService>& peer,
                 BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
             BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
             async_accept_impl(peer,  BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
         }

         template <typename SocketService, typename AcceptHandler>
         void async_accept(basic_socket<protocol_type, SocketService>& peer,
                 endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
             BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
             async_accept_impl(peer, peer_endpoint , BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
         }



     private:

         template <typename SocketService, typename AcceptHandler>
         void async_accept_impl(basic_socket<protocol_type, SocketService>& peer,
                 endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
             BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
             static_cast<stream_socket*> ( &peer)->option(option_);
             super_type::async_accept(peer,  peer_endpoint, static_cast<stream_socket*> (&peer)->coder(), handler);
         }

         template <typename SocketService, typename AcceptHandler>
         void async_accept_impl(basic_socket<protocol_type, SocketService>& peer,
                 BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
             BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
             static_cast<stream_socket*> ( &peer)->option(option_);
             super_type::async_accept(peer,   static_cast<stream_socket*> (&peer)->coder(), handler);
         }

         template <typename SocketService>
         boost::system::error_code accept_impl(
                 basic_socket<protocol_type, SocketService>& peer,
                 endpoint_type& peer_endpoint, boost::system::error_code& ec) {
             static_cast<stream_socket*> ( &peer)->option(option_);
             super_type::accept(peer, peer_endpoint, static_cast<stream_socket*> ( &peer)->coder(),  ec);
             return ec;
         }

         template <typename SocketService>
         boost::system::error_code accept_impl(
                 basic_socket<protocol_type, SocketService>& peer,
                 boost::system::error_code& ec) {
             static_cast<stream_socket*> ( &peer)->option(option_);
             super_type::accept(peer, static_cast<stream_socket*> ( &peer)->coder(),  ec);
             return ec;
         }*/
    } ;

}

class iso9506 {
public:
    /// The type of a TCP endpoint.

    typedef boost::asio::ip::basic_endpoint<boost::asio::ip::tcp>          endpoint;

    typedef boost::asio::iso::presentation_selector                                 presentation_selector;

    typedef boost::asio::iso::session_selector                                           session_selector;

    typedef boost::asio::iso::transport_selector                                        transport_selector;

    /// Construct to represent the IPv4 TCP protocol.

    static iso9506 v4() {

        return iso9506(PF_INET);
    }

    /// Construct to represent the IPv6 TCP protocol.

    static iso9506 v6() {

        return iso9506(PF_INET6);
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
    typedef prot9506::stream_socket socket;

    /// The TCP acceptor type.
    typedef prot9506::socket_acceptor acceptor;

    /// The TCP resolver type.
    typedef boost::asio::ip::basic_resolver<boost::asio::ip::tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
    /// The TCP iostream type.
    typedef boost::asio::basic_socket_iostream<boost::asio::ip::tcp> iostream;
#endif // !defined(BOOST_NO_IOSTREAM)


    typedef boost::asio::detail::socket_option::boolean<
    IPPROTO_TCP, TCP_NODELAY> no_delay;

    /// Compare two protocols for equality.

    friend bool operator==(const iso9506& p1, const iso9506& p2) {

        return p1.family_ == p2.family_;
    }

    /// Compare two protocols for inequality.

    friend bool operator!=(const iso9506& p1, const iso9506& p2) {

        return p1.family_ != p2.family_;
    }

private:
    // Construct with a specific family.

    explicit iso9506(int family)
    : family_(family) {
    }

    int family_;
} ;






#endif	/* MMSSOCKET_H */

