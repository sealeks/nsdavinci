/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 РњР°СЂС‚ 2010 Рі., 0:05
 */

#ifndef _DVNCI_KRNL_NS_RPCCLIENT_H
#define	_DVNCI_KRNL_NS_RPCCLIENT_H



#include <boost/asio/read_at.hpp>

#include <kernel/rpcioclient.h>
#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/constdef.h>

namespace dvnci {
    namespace rpc {

        class rpcmessage {
        public:

            enum {
                header_length = 10} ;

            rpcmessage(std::string vl, num16 _type = 0) {
                body_length_ = 0;
                body_ = vl;
                type_ = _type;
                encode_header();}

            rpcmessage() {
                body_length_ = 0;
                type_ = 0;
                encode_header();}

            const std::string& message() {
                return body_;}

            const std::string& header() const {
                return header_;}

            const size_t body_length() const {

                return header().size() < header_length ? 0 : static_cast<size_t> (*((num64*) (header().c_str())));}

            const num16 type() const {
                return header().size() < header_length ? 0 :  *((num16*) ((char*) header().c_str() + 8));}

            void build_message(std::string mesg, num16 _type) {
                body_ = mesg;
                type_ = _type;
                encode_header();}

            void setheader(const char* val) {
                header_.clear();
                header_.append(val, 10);
                decode_header();}

            void setbody(boost::asio::streambuf& val) {
                body_.clear();
                body_.append(boost::asio::buffer_cast<const char*>(val.data()), val.size());
                encode_header();}


        private:

            void encode_header() {
                header_.clear();
                num64 tmp_length = body_.size();
                body_length_ = body_.size();
                header_.append((char*) &tmp_length, 8);
                header_.append((char*) &type_, 2);}

            bool decode_header() {
                body_length_ = static_cast<size_t> (*((num64*) header().c_str()));
                type_ = *((num16*) ((char*) header().c_str() + 8));
                return true;}

            std::string body_;
            std::string header_;
            size_t body_length_;
            num16 type_;} ;






        class rpcioclient;
        typedef boost::shared_ptr<rpcioclient> rpcioclient_ptr;

        class rpcioclient : public boost::enable_shared_from_this<rpcioclient> {
        public:

            enum connectionState {
                connected, disconnected} ;

            rpcioclient();

            virtual ~rpcioclient();

            connectionState state() {
                return state_;}

            void connect(std::string host, std::string port, unsigned int timout_ = DEFAULT_DVNCI_TIMOUT);
            void disconnect();
            bool req(rpcmessage& msg, rpcmessage& resp);


        private:

            void handle_resolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_connect(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_write(const boost::system::error_code& err);

            void handle_readheader(const boost::system::error_code& err);

            void handle_endreq(const boost::system::error_code& err);

            void handle_timout_expire(const boost::system::error_code& err);


            boost::asio::io_service      io_service_;
            boost::asio::ip::tcp::socket socket_;
            connectionState              state_;
            boost::asio::deadline_timer  tmout_timer;
            unsigned int                 timout;


            rpcmessage                   respmsg;
            boost::asio::streambuf       response_body;
            boost::array<char, 10 >      buf;

            volatile bool                is_data_ready;
            volatile bool                is_timout;
            volatile bool                is_connect;
            volatile bool                is_error;
            volatile int                 error_cod;} ;}}


#endif	/* _NS_IOCLIENT_H */

