/* 
 * File:   ns_adminsession.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 Март 2010 г., 19:01
 */

#ifndef _NS_ADMINSESSION_H
#define	_NS_ADMINSESSION_H


#include <kernel/rpcioclient.h>
#include <kernel/constdef.h>

#include <admin/factory.h>


namespace dvnci {
    namespace admin {

        class adminsession
        : public boost::enable_shared_from_this<adminsession> {

        public:

            adminsession(boost::asio::io_service& io_service, adminintf_ptr inf)
            : io(io_service), socket_(io_service), adminintf(inf) {
                DEBUG_STR_DVNCI(chat_session.chat_session);
            }

            virtual ~adminsession() {
            }

            boost::asio::ip::tcp::socket& socket() {
                return socket_;
            }

            void start() {

                DEBUG_STR_DVNCI(admin_session);
                adminintf->setaddress(socket_.remote_endpoint().address());
                boost::asio::async_read(socket_,
                        boost::asio::buffer(boost::asio::buffer(bufheader), dvnci::rpc::rpcmessage::header_length),
                        boost::bind(
                        &adminsession::handle_read_header, shared_from_this(),
                        boost::asio::placeholders::error));
            }

            void handle_read_header(const boost::system::error_code& error) {
                DEBUG_STR_DVNCI(chat_session.handle_read_header);

                if (!error) {
                    read_msg_.header(bufheader.c_array());
                    request.consume(request.size());
                    boost::asio::async_read(socket_,
                            request,
                            boost::asio::transfer_at_least(read_msg_.body_length()),
                            boost::bind(&adminsession::handle_prepare, shared_from_this(),
                            boost::asio::placeholders::error));
                }
            }

            void handle_prepare(const boost::system::error_code& error) {
                DEBUG_STR_DVNCI(chat_session.handle_prepare);
                read_msg_.message(request);

                if (!error) {
                    preparerequest(read_msg_, write_msg_);
                    boost::asio::deadline_timer t(io, boost::posix_time::millisec(1));
                    t.async_wait(boost::bind(&adminsession::handle_read_body, shared_from_this()));
                }
            }

            void handle_read_body() {
                DEBUG_STR_DVNCI(chat_session.handle_read_body);
                boost::asio::async_write(socket_,
                        boost::asio::buffer(write_msg_.header(), dvnci::rpc::rpcmessage::header_length),
                        boost::bind(&adminsession::handle_write_header, shared_from_this(),
                        boost::asio::placeholders::error));
            }

            void handle_write_header(const boost::system::error_code& error) {
                DEBUG_STR_DVNCI(chat_session.handle_write);
                if (!error) {
                    boost::asio::async_write(socket_,
                            boost::asio::buffer(write_msg_.message(), write_msg_.body_length()),
                            boost::bind(&adminsession::handle_write_body, shared_from_this(),
                            boost::asio::placeholders::error));
                }
            }

            void handle_write_body(const boost::system::error_code& error) {
                DEBUG_STR_DVNCI(chat_session.handle_write);
                if (!error) {
                    boost::asio::async_read(socket_,
                            boost::asio::buffer(boost::asio::buffer(bufheader), dvnci::rpc::rpcmessage::header_length),
                            boost::bind(
                            &adminsession::handle_read_header, shared_from_this(),
                            boost::asio::placeholders::error));
                }
            }

            template<class _REQTYPE, class _RESPTYPE>
            bool generate(dvnci::rpc::rpcmessage& in_, dvnci::rpc::rpcmessage& out_) {
                try {
                    _REQTYPE reqstruct;
                    _RESPTYPE respstruct;
                    std::ostringstream out_archive_stream(std::ostringstream::binary);
                    std::istringstream in_archive_stream(std::istringstream::binary);
                    std::string out_string;
                    in_archive_stream.str(in_.message());
                    prb_binary_iarchive in_archive(in_archive_stream);
                    in_archive >> reqstruct;

                    num16 resptp = adminintf->generate_impl(reqstruct, respstruct);

                    prb_binary_oarchive out_archive(out_archive_stream);
                    out_archive << respstruct;
                    out_string = out_archive_stream.str();
                    out_ = dvnci::rpc::rpcmessage(out_string, resptp);
                }                catch (...) {
                    out_ = dvnci::rpc::rpcmessage();
                    return false;
                }

                return true;
            };

            bool preparerequest(dvnci::rpc::rpcmessage& in, dvnci::rpc::rpcmessage& out);



        private:
            boost::asio::io_service& io;
            boost::asio::ip::tcp::socket socket_;
            dvnci::rpc::rpcmessage read_msg_;
            dvnci::rpc::rpcmessage write_msg_;
            std::string read_str;
            std::string write_str;
            boost::array<char, 10 > bufheader;
            boost::asio::streambuf request;
            adminintf_ptr adminintf;
        };

        typedef boost::shared_ptr<adminsession> ns_adminsession_ptr;
    }
}

#endif	/* _NS_ADMINSESSION_H */

