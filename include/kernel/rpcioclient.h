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
#include <kernel/prb_binary_archive.h>
#include <kernel/prb_binary_iarchive.h>
#include <kernel/prb_binary_oarchive.h>

namespace dvnci {
    namespace rpc {

        class rpcmessage {
            
        public:

            enum {
                header_length = 10} ;

            rpcmessage(const std::string& vl = "", rpcmsgtype tp = 0) : body_(vl), body_length_(0), type_(tp)  {
                encode_header();}
            
            rpcmessage(const boost::asio::streambuf& val) : body_(boost::asio::buffer_cast<const num8*>(val.data()), val.size()), body_length_(0), type_(0)  {
                encode_header();}

            const std::string& message() const {
                return body_;}

	    void message(const boost::asio::streambuf& vl) {
		body_=std::string(boost::asio::buffer_cast<const num8*>(vl.data()) , vl.size() < body_length() ? vl.size() : body_length() );}

            const size_t body_length() const {
                return header().size() < header_length ? 0 : static_cast<size_t> (*((unum64*) (header().c_str())));}

            const rpcmsgtype type() const {
                return header().size() < header_length ? 0 :  *((rpcmsgtype*) ((num8*) header().c_str() + 8));}
            
            void header(const char* val) {
                header_.clear();
                header_.append(val, 10);
                decode_header();}
            
            const std::string& header() const {
                return header_;}


        private:
            

            void encode_header() {
                header_.clear();
                unum64 tmp_length = body_.size();
                body_length_ = body_.size();
                header_.append((char*) &tmp_length, 8);
                header_.append((char*) &type_, 2);}

            bool decode_header() {
                body_length_ = static_cast<size_t> (*((unum64*) header().c_str()));
                type_ = *((rpcmsgtype*) ((num8*) header().c_str() + 8));
                return true;}

            std::string body_;
            std::string header_;
            size_t body_length_;
            rpcmsgtype type_;} ;






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

            void connect(std::string host, std::string port, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);
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
            timeouttype                  timout;


            rpcmessage                   respmsg;
            boost::asio::streambuf       response_body;
            boost::array<char, 10 >      buf;

            volatile bool                is_data_ready;
            volatile bool                is_timout;
            volatile bool                is_connect;
            volatile bool                is_error;
            volatile int                 error_cod;} ;}}


#endif	/* _NS_IOCLIENT_H */

