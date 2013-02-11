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





namespace boost {
    namespace asio {
        namespace iso {
            namespace prot8823 {
                
                  
                typedef boost::asio::asn::x690::iarchive                                                                 input_archive_type; 
                typedef boost::asio::asn::x690::oarchive                                                                output_archive_type;    
                typedef boost::asio::iso::archive_temp<input_archive_type, output_archive_type>    presentation_archive;
                typedef boost::shared_ptr<presentation_archive>                                                    presentation_archive_ptr;                
                


                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////stream_socket                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                class stream_socket : protected boost::asio::iso::iso8327::socket  {
                    
                    typedef boost::asio::iso::iso8327::socket           super_type;

                public:

                    explicit stream_socket(boost::asio::io_service& io_service, const presentation_selector& psel)
                    : boost::asio::iso::iso8327::socket(io_service,  psel.sselector()), option_ (psel) , archiver( new presentation_archive() ) {
                    }

                    stream_socket(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, const presentation_selector& psel)
                    : boost::asio::iso::iso8327::socket(io_service, psel.sselector()), option_ (psel) , archiver( new presentation_archive() ) {
                    }





                    ///   Connect operation  ///


                   void connect(const endpoint_type& peer_endpoint, archiver_map& archs) {

                        boost::system::error_code ec;
                        connect(peer_endpoint, archs, ec);
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code connect(const endpoint_type& peer_endpoint, archiver_map& archs,
                            boost::system::error_code& ec) {
                        if (!is_open()) {
                            if (this->get_service().open(this->get_implementation(),
                                    peer_endpoint.protocol(), ec)) {
                                return ec;
                            }
                        }
                        return connect_impl(peer_endpoint, archs, ec);
                    }


                    // connect handler


                private:

                    template <typename ConnectHandler>
                    class connect_op {


                    public:

                        connect_op(stream_socket* socket , ConnectHandler handler ,
                                const endpoint_type& peer_endpoint, archiver_map archs) :
                        socket_(socket),
                        handler_(handler),
                        peer_endpoint_(peer_endpoint),
                        archs_(archs)        
                        {
                            
                        }

                        void run(const boost::system::error_code& ec) {
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec){
                                parse_CR(archs_);
                                operator()(ec, 0);}
                            
                            else
                                handler_( ec);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                
                            }
                            handler_(ec);
                        }



                    private:


                        stream_socket*                       socket_;
                        ConnectHandler                       handler_;
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
                        super_type::async_connect(peer_endpoint, boost::bind(&connect_op<ConnectHandler>::run, connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler, peer_endpoint, archs), boost::asio::placeholders::error));
                    }





                    ///   Releease operation  ///    

         /*          void releaseconnect(release_type type, archive_ptr data) {

                        boost::system::error_code ec;
                        releaseconnect(type, data, ec);
                        boost::asio::detail::throw_error(ec, "releaseconnect");
                    }

                    boost::system::error_code releaseconnect(release_type type, archive_ptr data , boost::system::error_code& ec) {
                        return releaseconnect_impl(type, data , ec);
                    }

                private:

                    template <typename ReleaseHandler>
                    class releaseconnect_op {

                        enum stateconnection {
                            request,
                            response
                        } ;

                    public:

                        releaseconnect_op(stream_socket*  socket, ReleaseHandler handler, release_type type,  archive_ptr transdata) :
                        socket_(socket),
                        handler_(handler),
                        send_(send_seq_ptr( new send_seq(type == SESSION_NORMAL_RELEASE ? FN_SPDU_ID : AB_SPDU_ID , socket->prot_option(), transdata ? transdata->request_str() : "" ))),
                        receive_(new receive_seq()),
                        type_(type),
                        transdata_(transdata),
                        state_(request) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case request:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->super_type::async_send(send_->pop() , 0 , *this);
                                            return;
                                        }
                                        state(response);
                                        operator()(ec, 0);
                                        return;
                                    }
                                    case response:
                                    {
                                        receive_->put(bytes_transferred);
                                        if (!receive_->ready()) {
                                            socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), 0 , *this);
                                            return;
                                        }
                                        finish(ec);
                                        return;
                                    }
                                }
                            }
                            handler_(ec);
                            boost::system::error_code ecc;
                            socket_->close(ecc);
                        }


                    private:

                        void finish(const boost::system::error_code& ec) {
                            if (receive_->state() == receive_seq::complete) {
                                switch (receive_->type()) {
                                    case DN_SPDU_ID:
                                    {
                                        if (transdata_)
                                            transdata_->respond_str(receive_->options().data());
                                        handler_(ec);
                                        boost::system::error_code ecc;
                                        socket_->close(ecc);
                                        return;
                                    }
                                    case AA_SPDU_ID:
                                    {
                                        if (transdata_)
                                            transdata_->respond_str(receive_->options().data());
                                        handler_(ec);
                                        boost::system::error_code ecc;
                                        socket_->close(ecc);
                                        return;
                                    }
                                    default:
                                    {
                                        handler_(ERROR__EPROTO);
                                    }
                                }
                            }
                            boost::system::error_code ecc;
                            socket_->close(ecc);
                        }

                        void state(stateconnection st) {
                            if (state_ != st) {
                                state_ = st;
                            }
                        }

                        stream_socket*                                              socket_;
                        ReleaseHandler                                              handler_;
                        send_seq_ptr                                                  send_;
                        receive_seq_ptr                                              receive_;
                        release_type                                                   type_;
                        archive_ptr                                              transdata_;
                        stateconnection                                               state_;

                    } ;


                public:

                    template <typename ReleaseHandler>
                    void asyn_releaseconnect(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                            release_type type,  archive_ptr trans) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                        if (is_open()) {
                            this->get_io_service().post(boost::bind(&releaseconnect_op<ReleaseHandler>::run,
                                    releaseconnect_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, type, trans)));
                        }
                        else
                            handler(ERROR_ECONNREFUSED);
                    }



                    ///  Check Accept operation  ///

                    void  check_accept(archive_ptr  transdata) {

                        boost::system::error_code ec;
                        check_accept(transdata, ec);
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code  check_accept(archive_ptr  transdata, boost::system::error_code& ec) {
                        return check_accept_imp(transdata, ec);
                    }


                private:

                    template <typename CheckAcceptHandler>
                    class accept_op {

                        enum stateconnection {
                            wait,
                            send,
                            refuse
                        } ;

                    public:

                        accept_op(stream_socket* socket,  CheckAcceptHandler handler,  archive_ptr  transdata) :
                        socket_(socket),
                        handler_(handler),
                        state_(wait),
                        options_(socket->prot_option()),
                        send_(),
                        receive_(new receive_seq()),
                        transdata_(transdata) {
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
                                        receive_->put(bytes_transferred);
                                        if (!receive_->ready()) {
                                            socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()) , 0 , *this);
                                            return;
                                        }
                                        parse_response(ec);
                                        return;
                                    }
                                    case send:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->super_type::async_send(send_->pop() , 0 , *this);
                                            return;
                                        }
                                        finish(ec);
                                        return;
                                    }
                                    case refuse:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->super_type::async_send(send_->pop() , 0 , *this);
                                            return;
                                        }
                                        boost::system::error_code ecc;
                                        socket_->close(ecc);
                                        handler_(ERROR_EDOM);
                                        return;
                                    }
                                }
                            }
                            handler_(ec);
                        }



                    private:

                        void parse_response(const boost::system::error_code& ec) {
                            if (receive_->type() != CN_SPDU_ID || receive_->state() != receive_seq::complete) {
                                boost::system::error_code ecc;
                                socket_->close(ecc);
                                handler_(ERROR__EPROTO);
                                return;
                            }
                            std::string error_accept = "";
                            if (!correspond_protocol_option(options_,  receive_->options(), error_accept))  {
                                options_.reason(error_accept);
                                send_ = send_seq_ptr( new send_seq(RF_SPDU_ID, options_));
                                state(refuse);
                                operator()(ec, 0);
                                return;
                            }
                            if (transdata_)
                                transdata_->respond_str(receive_->options().data());
                            send_ = send_seq_ptr( new send_seq(AC_SPDU_ID, options_, transdata_ ? transdata_->request_str() : ""));
                            state(send);
                            operator()(ec, 0);
                        }

                        void finish(const boost::system::error_code& ec) {

                            protocol_options  opt = receive_->options();
                            //opt.pdusize(options_.pdusize());
                            socket_->correspond_prot_option(opt);
                            handler_(ec);
                            std::cout << "accept_op success" << std::endl;
                        }

                        void state(stateconnection st) {

                            if (state_ != st)
                                state_ = st;
                        }



                        stream_socket*                              socket_;
                        CheckAcceptHandler                    handler_;
                        stateconnection                            state_;
                        protocol_options                          options_;
                        send_seq_ptr                                 send_;
                        receive_seq_ptr                             receive_;
                        archive_ptr                             transdata_;

                    } ;


                public:

                    template <typename CheckAcceptHandler>
                    void asyn_check_accept(CheckAcceptHandler handler, archive_ptr  transdata) {

                        //option_.src_tsap(src);
                        this->get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
                                accept_op<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler, transdata)));
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


                private:

                    template <typename SendHandler, typename ConstBufferSequence>
                    class send_op {
                    public:

                        send_op(stream_socket*   socket, SendHandler handler ,
                                const ConstBufferSequence& buffers, boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        in_(send_seq_ptr( new send_seq_data<ConstBufferSequence>(buffers))),
                        flags_(flags),
                        send_lower_(boost::asio::buffer_size(buffers)) {
                        }

                        void run() {

                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                in_->size(bytes_transferred);
                                if (!in_->ready()) {
                                    socket_->super_type::async_send(in_->pop(), flags_ , *this);
                                    return;
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


                    } ;

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
                        this->get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
                    }

                    template <typename ConstBufferSequence, typename WriteHandler>
                    void async_write_some(const ConstBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                        async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                    }







                    ///   receive operation  ///     

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

                private:

                    template <typename ReceiveHandler, typename Mutable_Buffers>
                    class receive_op {

                        enum stateconnection {
                            request,
                            response
                        } ;

                    public:

                        receive_op(stream_socket*   socket, ReceiveHandler handler ,
                                receive_seq_ptr receive, const Mutable_Buffers& buff , boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        receive_(receive),
                        buff_(buff),
                        send_(),
                        state_(request),
                        flags_(flags) {
                        }

                        void run() {
                            boost::system::error_code ec;
                            if (socket_->input_empty())
                                operator()(ec, 0);
                            else
                                socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()) , flags_ , handler_);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case request:
                                    {
                                        receive_->put(bytes_transferred);
                                        if (!receive_->ready()) {
                                            socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()) , flags_ , *this);
                                            return;
                                        }
                                        if (!success()) return;
                                        break;
                                    }
                                    case response:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->super_type::async_send(send_->pop() , 0 , *this);
                                            return;
                                        }
                                        handler_(ERROR_ECONNREFUSED, static_cast<std::size_t> (receive_->datasize()));
                                        return;
                                    }
                                }
                            }
                            handler_(ec, static_cast<std::size_t> (receive_->datasize()));
                        }




                    private:

                        bool success() {
                            switch (receive_->type()) {
                                case  DT_SPDU_ID:
                                {
                                    return true;
                                }
                                default:
                                {
                                    send_ = socket_->session_release_reaction(receive_);
                                    if (send_) {
                                        boost::system::error_code ecc;
                                        state(response);
                                        operator()(ecc, 0);
                                        return false;
                                    }
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                    handler_(ERROR_ECONNREFUSED ,  0);
                                    return false;
                                }
                            }

                            return false;
                        }

                        void state(stateconnection st) {
                            if (state_ != st) {
                                state_ = st;
                            }
                        }

                        stream_socket*                                              socket_;
                        ReceiveHandler                                              handler_;
                        const Mutable_Buffers&                               buff_;
                        receive_seq_ptr                                             receive_;
                        send_seq_ptr                                                 send_;
                        stateconnection                                             state_;
                        boost::asio::socket_base::message_flags flags_;
                    } ;

                public:

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
                                receive_seq_ptr( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers))), buffers, flags)));

                    }

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_read_some(const MutableBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                        async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                    }

                    //archive_ptr    session_releasedata() const {
                    //    return session_data_;
                    //}


                protected:

                    virtual  send_seq_ptr session_release_reaction(receive_seq_ptr receive) {

                        if (session_data_){
                            session_data_->clear();
                            session_data_->request_str(receive->options().data());}
                        switch (receive->type()) {
                            case FN_SPDU_ID: return send_seq_ptr( new send_seq(DN_SPDU_ID, prot_option()));
                            case AB_SPDU_ID: return send_seq_ptr( new send_seq(AC_SPDU_ID, prot_option()));
                            default:
                            {
                            }
                        }
                        return send_seq_ptr();
                    }

                    //void session_releasedata(archive_ptr data ) {
                    //    session_data_ = data;
                    //}*/


                private:

                    /*const protocol_options& prot_option() const {
                        return option_;
                    }

                    void correspond_prot_option(const protocol_options& val) {

                        std::cout << "correspond_prot_option calling  : " << val.ssap_calling() << std::endl;
                        std::cout << "correspond_prot_option called  : " << val.ssap_called() << std::endl;
                    }*/
                    
                    void build_CP(archiver_map archs);
                    
                    bool parse_CR(archiver_map archs);                    

                    boost::system::error_code connect_impl(const endpoint_type& peer_endpoint, archiver_map archs,
                            boost::system::error_code& ec) {
                        
                        /*session_data_=data;
                        
                        if (super_type::connect(peer_endpoint, ec))
                            return ec;

                        send_seq_ptr  send_ (send_seq_ptr( new send_seq( CN_SPDU_ID, prot_option(), data ? data->request_str() : "")));
                        while (!ec && !send_->ready())
                            send_->size( super_type::send(send_->pop() , 0, ec));
                        if (ec)
                            return ec;
                        receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case AC_SPDU_ID:
                                {
                                    correspond_prot_option(receive_->options());
                                    if (data)
                                        data->respond_str(receive_->options().data());
                                    return ec;
                                }
                                default:
                                {
                                    ec = ERROR__EPROTO;
                                }
                            }
                        }*/
                        return ec = ERROR__EPROTO;
                    }

                 /*   boost::system::error_code releaseconnect_impl(release_type type, archive_ptr data , boost::system::error_code& ec) {
                        if (is_open()) {
                            send_seq_ptr  send_( new send_seq(type == SESSION_NORMAL_RELEASE ? FN_SPDU_ID : AB_SPDU_ID , prot_option(), data ? data->request_str() : "" ));
                            while (!ec && !send_->ready())
                                send_->size( super_type::send(send_->pop(), 0, ec));
                            if (ec)
                                return ec;
                            receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                            while (!ec && !receive_->ready())
                                receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()) , 0, ec));
                            if (ec)
                                return ec;
                            if (receive_->state() == receive_seq::complete) {
                                switch (receive_->type()) {
                                    case DN_SPDU_ID:
                                    {
                                        if (data)
                                            data->respond_str(receive_->options().data());
                                        boost::system::error_code ecc;
                                        close(ecc);
                                        return ec;
                                    }
                                    case AA_SPDU_ID:
                                    {
                                        if (data)
                                            data->respond_str(receive_->options().data());
                                        boost::system::error_code ecc;
                                        close(ecc);
                                        return ec;
                                    }
                                    default:
                                    {
                                    }
                                }
                            }
                            boost::system::error_code ecc;
                            close(ecc);
                        }
                        return ec =  ERROR_ECONNREFUSED;
                    }

                    boost::system::error_code  check_accept_imp(archive_ptr  transdata, boost::system::error_code& ec) {
                        bool canseled = false;

                        receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->put(super_type::receive( boost::asio::buffer(receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        send_seq_ptr  send_ ;

                        protocol_options options_ = this->prot_option();
                        if (receive_->type() != CN_SPDU_ID || receive_->state() != receive_seq::complete) {
                            boost::system::error_code ecc;
                            close(ecc);
                            return ERROR__EPROTO;
                        }
                        std::string error_accept = "";
                        if (!correspond_protocol_option(options_,  receive_->options(), error_accept))  {
                            canseled = true;
                            options_.reason(error_accept);
                            send_ = send_seq_ptr( new send_seq(RF_SPDU_ID, options_));
                        }
                        else {
                            if (transdata)
                                transdata->respond_str(receive_->options().data());
                            send_ = send_seq_ptr( new send_seq(AC_SPDU_ID, options_, transdata ? transdata->request_str() : ""));
                        }

                        while (!ec && !send_->ready())
                            send_->size(super_type::send(send_->pop(), 0, ec));
                        if (ec)
                            return ec;
                        if (canseled ) {
                            boost::system::error_code ecc;
                            close(ecc);
                        }
                        else {
                            protocol_options  opt = receive_->options();
                            correspond_prot_option(receive_->options());
                        }
                        return ec = canseled ? ERROR_EDOM : ec;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send_impl(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        send_seq_ptr  send_( new send_seq_data<ConstBufferSequence > (buffers));
                        while (!ec && !send_->ready())
                            send_->size( super_type::send(send_->pop(), 0, ec));
                        return ec ? 0 : boost::asio::buffer_size(buffers);
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive_impl(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {

                        if (!input_empty())
                            return super_type::receive(boost::asio::buffer(buffers) , flags, ec );

                        receive_seq_ptr receive_( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers)));
                        while (!ec && !receive_->ready()) {
                            receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return 0;
                        switch (receive_->type()) {
                            case DT_SPDU_ID:
                            {
                                return receive_->datasize();
                            }
                            default:
                            {
                                send_seq_ptr  send_  = session_release_reaction(receive_);
                                if (send_) {
                                    while (!ec && !send_->ready())
                                        send_->size( super_type::send(send_->pop(), 0, ec));
                                    ec = ERROR_ECONNREFUSED;
                                    boost::system::error_code ecc;
                                    close(ecc);                                    
                                    return receive_->datasize();
                                    
                                }
                            }
                        }
                        boost::system::error_code ecc;
                        close(ecc);
                        ec = ERROR__EPROTO;
                        return 0;
                    }*/

                    presentation_selector                          option_;
                    presentation_archive_ptr               archiver;
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

