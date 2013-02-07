/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOSTACK_H_H
#define	ISOSTACK_H_H

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
#include <boost/asio/streambuf.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>

#include <boost/asio/detail/push_options.hpp>

#include <iso/archive_stream.h>



namespace boost {
    namespace asio {
        namespace iso {


            /*      class streambuf
 
                      _M_out_beg     pbase()
                      _M_out_cur      pptr()
                      _M_out_end     epptr()
 
                      _M_in_beg        eback()
                      _M_in_cur         gptr()
                      _M_in_end        egptr()
 
                       out     <<
                                                                                                                                      |(pbase())                                      |(pptr())                              |(epptr())
                       in       >>
                       |(eback())                                  |(gptr())                                              |(egptr())
 
                       info set input ptr
                       void setg( beg , cur, end)  inbeg=begin,  incur = cur,  inend = end
 
                      info set out ptr
                      void setp(beg, end)          outbeg=outcur =beg , outend = end;
                      void pbump(num)             outcur +=  num;
         
 
             */

            const boost::system::error_code ERROR__SEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
            const boost::system::error_code ERROR__ENOBUFS  = boost::system::error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
            const boost::system::error_code ERROR__EPROTO  = boost::system::error_code(boost::system::errc::protocol_error, boost::system::system_category());
            const boost::system::error_code ERROR_EFAULT  =  boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
            const boost::system::error_code ERROR_EADDRNOTAVAIL  =  boost::system::error_code(boost::system::errc::address_not_available, boost::system::system_category());
            const boost::system::error_code ERROR_EDOM  =  boost::system::error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
            const boost::system::error_code ERROR_EIO  =  boost::system::error_code(boost::system::errc::io_error, boost::system::system_category());
            const boost::system::error_code ERROR_ECONNREFUSED  =  boost::system::error_code(boost::system::errc::connection_refused, boost::system::system_category());

            template <typename T> std::string
            inline static inttype_to_str(T vl) {
                return std::string(((const char*) &vl), sizeof (T));
            }

            template <typename T>
            inline static bool str_to_inttype(const std::string& dblk, T& vl) {
                if (sizeof (vl) > dblk.size()) return false;
                vl = *(reinterpret_cast<T*> (const_cast<char*> (dblk.data())));
                return true;
            }

            inline static int16_t endiancnv_copy(int16_t vl) {
                return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
            }

            inline static uint16_t endiancnv_copy(uint16_t vl) {
                return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
            }

            template <typename T>
            inline static T endiancnv_copy(const std::string& vl) {
                T tmp = 0;
                return str_to_inttype<T > (vl, tmp) ? (((tmp >> 8) & 0xFF) | (0xFF00 & (tmp << 8))) : 0;
            }




            //   transport

            const int8_t TPDU_SIZE8192 = '\xD'; // denied in 0 class
            const int8_t TPDU_SIZE4096 = '\xC'; // denied in 0 class
            const int8_t TPDU_SIZE2048 = '\xB';
            const int8_t TPDU_SIZE1024 = '\xA';
            const int8_t TPDU_SIZE512  = '\x9';
            const int8_t TPDU_SIZE256 = '\x8';
            const int8_t TPDU_SIZE128 = '\x7';
            //const int8_t TPDU_SIZE4 = '\x5';   /// test

            typedef enum {
                SIZENULL = 0,
                SIZE2048 = TPDU_SIZE2048,
                SIZE1024 = TPDU_SIZE1024,
                SIZE512 = TPDU_SIZE512,
                SIZE256 = TPDU_SIZE256,
                SIZE128 = TPDU_SIZE128,
                //SIZE4 = TPDU_SIZE4
            }   tpdu_size;

            enum release_type {
                SESSION_NORMAL_RELEASE,
                SESSION_ABORT_RELEASE
            } ;



          

            class  sevice_send_buffer_impl : public send_buffer_impl {
            public:

                sevice_send_buffer_impl(const std::string& send) : send_buffer_impl(), send_(send) {
                    buff_.push_back(const_buffer(send_.data(), send_.size()));
                }

            private:
                std::string send_;
            } ;





            ///   selectors

            class transport_selector {
            public:

                transport_selector() :  pdusize_(SIZE2048) {
                }

                transport_selector(const std::string& called) : called_(called), pdusize_(SIZE2048) {
                }

                transport_selector(const std::string& called, const std::string& calling) : called_(called), calling_(calling), pdusize_(SIZE2048) {
                }

                transport_selector(const std::string& called, tpdu_size  pdusize ) : called_(called), pdusize_(pdusize) {
                }

                transport_selector(const std::string& called, const std::string& calling, tpdu_size  pdusize ) : called_(called), calling_(calling), pdusize_(pdusize) {
                }

                transport_selector(tpdu_size  pdusize ) : pdusize_(pdusize) {
                }

                transport_selector(int16_t called) : called_(inttype_to_str(endiancnv_copy(called))), pdusize_(SIZE2048) {
                }

                transport_selector(int16_t called, int16_t calling) : called_(inttype_to_str(endiancnv_copy(called))), calling_(inttype_to_str(endiancnv_copy(calling))), pdusize_(SIZE2048) {
                }

                transport_selector(int16_t called, tpdu_size  pdusize ) : called_(inttype_to_str(endiancnv_copy(called))), pdusize_(pdusize) {
                }

                transport_selector(int16_t called, int16_t calling, tpdu_size  pdusize ) : called_(inttype_to_str(endiancnv_copy(called))), calling_(inttype_to_str(endiancnv_copy(calling))), pdusize_(pdusize) {
                }

                std::string called() const {
                    return called_;
                }

                std::string calling() const {
                    return calling_;
                }

                tpdu_size pdusize() const {
                    return pdusize_;
                }

            private:
                std::string called_;
                std::string calling_;
                tpdu_size  pdusize_;
            } ;



            // session            

            class session_selector {
            public:

                session_selector() :  tselector_() {
                }

                explicit session_selector(const std::string& called) : called_(called), tselector_() {
                }

                explicit session_selector(const std::string& called, const std::string& calling) : called_(called), calling_(calling), tselector_() {
                }

                explicit session_selector(const std::string& called, const transport_selector&  tselector) : called_(called), tselector_(tselector) {
                }

                explicit session_selector(const std::string& called, const std::string& calling,  const transport_selector&  tselector ) : called_(called), calling_(calling), tselector_(tselector) {
                }

                session_selector(const transport_selector&  tselector) : tselector_(tselector) {
                }

                std::string called() const {
                    return called_;
                }

                std::string calling() const {
                    return calling_;
                }

                const transport_selector& tselector() const {
                    return tselector_;
                }

            private:
                transport_selector   tselector_;
                std::string                called_;
                std::string                calling_;
            } ;






        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

