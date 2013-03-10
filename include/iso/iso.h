/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOSTACK_H_H
#define	ISOSTACK_H_H



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

#include <iso/archive_stream.h>
#include <iso/asn/asnbase.h>


namespace boost {
    namespace asio {
        namespace iso {

            const boost::system::error_code ERROR__SEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
            const boost::system::error_code ERROR__ENOBUFS = boost::system::error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
            const boost::system::error_code ERROR__EPROTO = boost::system::error_code(boost::system::errc::protocol_error, boost::system::system_category());
            const boost::system::error_code ERROR_EFAULT = boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
            const boost::system::error_code ERROR_EADDRNOTAVAIL = boost::system::error_code(boost::system::errc::address_not_available, boost::system::system_category());
            const boost::system::error_code ERROR_EDOM = boost::system::error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
            const boost::system::error_code ERROR_EIO = boost::system::error_code(boost::system::errc::io_error, boost::system::system_category());
            const boost::system::error_code ERROR_ECONNREFUSED = boost::system::error_code(boost::system::errc::connection_refused, boost::system::system_category());

            template <typename T> std::string
            inline static inttype_to_str(T vl) {
                return std::string(((const char*) &vl), sizeof (T));
            }

            template <typename T> raw_type
            inline static inttype_to_raw(T vl) {
                return raw_type(((const octet_type*) &vl), ((const octet_type*) &vl) + sizeof (T));
            }

            template <typename T>
            inline static bool str_to_inttype(const std::string& dblk, T& vl) {
                if (sizeof (vl) > dblk.size()) return false;
                vl = *(reinterpret_cast<T*> (const_cast<char*> (dblk.data())));
                return true;
            }

            template <typename T>
            inline static bool raw_to_inttype(const raw_type& dblk, T& vl) {
                if (sizeof (vl) > dblk.size()) return false;
                vl = *(reinterpret_cast<T*> (const_cast<octet_type*> (&dblk.front())));
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

            template <typename T>
            inline static T endiancnv_copy(const raw_type& vl) {
                T tmp = 0;
                return raw_to_inttype<T > (vl, tmp) ? (((tmp >> 8) & 0xFF) | (0xFF00 & (tmp << 8))) : 0;
            }

            inline static void raw_back_insert(raw_type& dst, const raw_type& src) {
                dst.insert(dst.end(), src.begin(), src.end());
            }

            inline static void raw_front_insert(raw_type& dst, const raw_type& src) {
                dst.insert(dst.begin(), src.begin(), src.end());
            }


            //   transport

            const octet_type TPDU_SIZE8192 = '\xD'; // denied in 0 class
            const octet_type TPDU_SIZE4096 = '\xC'; // denied in 0 class
            const octet_type TPDU_SIZE2048 = '\xB';
            const octet_type TPDU_SIZE1024 = '\xA';
            const octet_type TPDU_SIZE512 = '\x9';
            const octet_type TPDU_SIZE256 = '\x8';
            const octet_type TPDU_SIZE128 = '\x7';
            //const octet_type TPDU_SIZE4 = '\x5';   /// test

            typedef enum {
                SIZENULL = 0,
                SIZE2048 = TPDU_SIZE2048,
                SIZE1024 = TPDU_SIZE1024,
                SIZE512 = TPDU_SIZE512,
                SIZE256 = TPDU_SIZE256,
                SIZE128 = TPDU_SIZE128,
                //SIZE4 = TPDU_SIZE4
            } tpdu_size;

            enum release_type {
                SESSION_NORMAL_RELEASE,
                SESSION_ABORT_RELEASE
            };

            class sevice_send_buffer_impl : public send_buffer_impl {
            public:

                sevice_send_buffer_impl(const std::string& send) : send_buffer_impl(), send_(send) {
                    buff_.push_back(const_buffer(send_.data(), send_.size()));
                }

            private:
                std::string send_;
            };

            class sevice_send_buffer_implb : public send_buffer_impl {
            public:

                sevice_send_buffer_implb(const raw_type& send) : send_buffer_impl(), send_(send) {
                    buff_.push_back(const_buffer(&send_.front(), send_.size()));
                }

            private:
                raw_type send_;
            };


            ///   selectors type            
            
            class selectorvalue_type {
                
            public:
                
                selectorvalue_type()  {}

                selectorvalue_type(const std::string& vl) : value_(raw_type(vl.begin(), vl.end())) {
                }
                explicit selectorvalue_type(const raw_type& vl) : value_(vl) {
                }    
                explicit selectorvalue_type(const int8_t vl) : value_(inttype_to_raw(vl)) {
                }   
                explicit selectorvalue_type(const uint8_t vl) : value_(inttype_to_raw(vl)) {
                } 
                explicit selectorvalue_type(const int16_t vl) : value_(inttype_to_raw(vl)) {
                }   
                explicit selectorvalue_type(const uint16_t vl) : value_(inttype_to_raw(vl)) {
                } 
                explicit selectorvalue_type(const int32_t vl) : value_(inttype_to_raw(vl)) {
                }   
                explicit selectorvalue_type(const uint32_t vl) : value_(inttype_to_raw(vl)) {
                }    
                explicit selectorvalue_type(const int64_t vl) : value_(inttype_to_raw(vl)) {
                }   
                explicit selectorvalue_type(const uint64_t vl) : value_(inttype_to_raw(vl)) {
                }                                           
                std::string to_string() const {
                    return value_.empty() ? "" :  std::string(value_.begin(), value_.end());
                }
                const raw_type& to_raw() const{
                    return value_;
                }                
   
            private:                
                raw_type value_;
            };


            ///   selectors

            class transport_selector {
            public:

                transport_selector() : pdusize_(SIZE2048) {
                }

                transport_selector(const selectorvalue_type& called) : called_(called), pdusize_(SIZE2048) {
                }

                transport_selector(const selectorvalue_type& called, const selectorvalue_type& calling) : called_(called), calling_(calling), pdusize_(SIZE2048) {
                }

                transport_selector(const selectorvalue_type& called, tpdu_size pdusize) : called_(called), pdusize_(pdusize) {
                }

                transport_selector(const selectorvalue_type& called, const selectorvalue_type& calling, tpdu_size pdusize) : called_(called), calling_(calling), pdusize_(pdusize) {
                }

                transport_selector(tpdu_size pdusize) : pdusize_(pdusize) {
                }


                std::string called() const {
                    return called_.to_string();
                }

                std::string calling() const {
                    return calling_.to_string();
                }

                tpdu_size pdusize() const {
                    return pdusize_;
                }

            private:
                selectorvalue_type called_;
                selectorvalue_type calling_;
                tpdu_size pdusize_;
            };



            // session            

            class session_selector {
            public:

                session_selector() : tselector_() {
                }

                explicit session_selector(const std::string& called) : called_(called), tselector_() {
                }

                explicit session_selector(const std::string& called, const std::string& calling) : called_(called), calling_(calling), tselector_() {
                }

                explicit session_selector(const std::string& called, const transport_selector& tselector) : called_(called), tselector_(tselector) {
                }

                explicit session_selector(const std::string& called, const std::string& calling, const transport_selector& tselector) : called_(called), calling_(calling), tselector_(tselector) {
                }

                session_selector(const transport_selector& tselector) : tselector_(tselector) {
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
                transport_selector tselector_;
                std::string called_;
                std::string calling_;
            };


            ///

            class presentation_selector {
            public:

                presentation_selector() : sselector_() {
                }

                explicit presentation_selector(const std::string& called) : called_(called), sselector_() {
                }

                explicit presentation_selector(const std::string& called, const std::string& calling) : called_(called), calling_(calling), sselector_() {
                }

                explicit presentation_selector(const std::string& called, const session_selector& sselector) : called_(called), sselector_(sselector) {
                }

                explicit presentation_selector(const std::string& called, const std::string& calling, const session_selector& sselector) : called_(called), calling_(calling), sselector_(sselector) {
                }

                presentation_selector(const session_selector& sselector) : sselector_(sselector) {
                }

                std::string called() const {
                    return called_;
                }

                std::string calling() const {
                    return calling_;
                }

                void called(const std::string& val) {
                    called_ = val;
                }

                void calling(const std::string& val) {
                    calling_ = val;
                }

                const session_selector& sselector() const {
                    return sselector_;
                }

            private:

                session_selector sselector_;
                std::string called_;
                std::string calling_;

            };






        }

    } // namespace asio
} // namespace boost

#endif	/* RFC1006_H */

