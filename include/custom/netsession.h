/* 
 * File:   ns_adminsession.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 Март 2010 г., 19:01
 */

#ifndef _NS_NETSESSION_H
#define	_NS_NETSESSION_H




#include <custom/netfactory.h>
#include <kernel/constdef.h>
#include <kernel/rpcioclient.h>




namespace dvnci {
    namespace custom {
        namespace net {

            class netsession
            : public boost::enable_shared_from_this<netsession> {
            public:

                netsession(boost::asio::io_service& io_service, netintf_ptr inf)
                : io(io_service), socket_(io_service), netintf(inf) {
                    DEBUG_STR_DVNCI(client connected netsession);}

                virtual ~netsession() {
                    DEBUG_STR_DVNCI(netsession destructor);}

                boost::asio::ip::tcp::socket& socket() {
                    return socket_;}

                void start() {

                    netintf->setaddress(socket_.remote_endpoint().address());
                    boost::asio::async_read(socket_,
                            boost::asio::buffer(boost::asio::buffer(bufheader), dvnci::rpc::rpcmessage::header_length),
                            boost::bind(
                            &netsession::handle_read_header, shared_from_this(),
                            boost::asio::placeholders::error));}

                void handle_read_header(const boost::system::error_code& error) {


                    if (!error) {
                        read_msg_.setheader(bufheader.c_array());

                        request.consume(request.size());
                        boost::asio::async_read(socket_,
                                request,
                                boost::asio::transfer_at_least(read_msg_.body_length()),
                                boost::bind(&netsession::handle_prepare, shared_from_this(),
                                boost::asio::placeholders::error));}}

                void handle_prepare(const boost::system::error_code& error) {

                    read_msg_.setbody(request);

                    if (!error) {
                        preparerequest(read_msg_, write_msg_);
                        boost::asio::deadline_timer t(io, boost::posix_time::millisec(1));
                        t.async_wait(boost::bind(&netsession::handle_read_body, shared_from_this()));}}

                void handle_read_body() {

                    boost::asio::async_write(socket_,
                            boost::asio::buffer(write_msg_.header(), dvnci::rpc::rpcmessage::header_length),
                            boost::bind(&netsession::handle_write_header, shared_from_this(),
                            boost::asio::placeholders::error));}

                void handle_write_header(const boost::system::error_code& error) {


                    if (!error) {
                        boost::asio::async_write(socket_,
                                boost::asio::buffer(write_msg_.message(), write_msg_.body_length()),
                                boost::bind(&netsession::handle_write_body, shared_from_this(),
                                boost::asio::placeholders::error));}}

                void handle_write_body(const boost::system::error_code& error) {
                    if (!error) {
                        boost::asio::async_read(socket_,
                                boost::asio::buffer(boost::asio::buffer(bufheader), dvnci::rpc::rpcmessage::header_length),
                                boost::bind(
                                &netsession::handle_read_header, shared_from_this(),
                                boost::asio::placeholders::error));}}

                template<class REQTYPE, class RESPTYPE>
                bool generate(dvnci::rpc::rpcmessage& in_, dvnci::rpc::rpcmessage& out_) {
                    try {
                        REQTYPE reqstruct;
                        RESPTYPE respstruct;
                        std::ostringstream out_archive_stream(std::ostringstream::binary);
                        std::istringstream in_archive_stream(std::istringstream::binary);
                        std::string out_string;
                        in_archive_stream.str(in_.message());
                        boost::archive::binary_iarchive in_archive(in_archive_stream);
                        in_archive >> reqstruct;
                        num16 resptp = netintf->generate_impl(reqstruct, respstruct);
                        boost::archive::binary_oarchive out_archive(out_archive_stream);
                        out_archive << respstruct;
                        out_string = out_archive_stream.str();
                        out_.build_message(out_string, resptp);}
                    catch (...) {
                        out_.build_message("", 0);
                        return false;}
                    return true;};

                bool preparerequest(dvnci::rpc::rpcmessage& in, dvnci::rpc::rpcmessage& out);



            private:
                boost::asio::io_service&     io;
                boost::asio::ip::tcp::socket socket_;
                dvnci::rpc::rpcmessage       read_msg_;
                dvnci::rpc::rpcmessage       write_msg_;
                std::string                  read_str;
                std::string                  write_str;
                boost::array<char, 10 >      bufheader;
                boost::asio::streambuf       request;
                netintf_ptr                  netintf;} ;

            }}}

#endif	/* _NS_ADMINSESSION_H */

