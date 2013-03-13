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

#include <iso/base_coder.h>
#include <iso/asn/asnbase.h>

//#define CHECK_ISO_SELECTOR


namespace boost {
    namespace iso {

        const boost::system::error_code ERROR__SEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
        const boost::system::error_code ERROR__ENOBUFS = boost::system::error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
        const boost::system::error_code ERROR__EPROTO = boost::system::error_code(boost::system::errc::protocol_error, boost::system::system_category());
        const boost::system::error_code ERROR_EFAULT = boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
        const boost::system::error_code ERROR_EADDRNOTAVAIL = boost::system::error_code(boost::system::errc::address_not_available, boost::system::system_category());
        const boost::system::error_code ERROR_EDOM = boost::system::error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
        const boost::system::error_code ERROR_EIO = boost::system::error_code(boost::system::errc::io_error, boost::system::system_category());
        const boost::system::error_code ERROR_ECONNREFUSED = boost::system::error_code(boost::system::errc::connection_refused, boost::system::system_category());


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


        ///   selectors type            

        class selectorvalue_type {
        public:

            selectorvalue_type() {
            }

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
                return value_.empty() ? "" : std::string(value_.begin(), value_.end());
            }

            const raw_type& to_raw() const {
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

            const raw_type& called() const {
                return called_.to_raw();
            }

            const raw_type& calling() const {
                return calling_.to_raw();
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

            explicit session_selector(const selectorvalue_type& called) : called_(called), tselector_() {
            }

            explicit session_selector(const selectorvalue_type& called, const selectorvalue_type& calling) : called_(called), calling_(calling), tselector_() {
            }

            explicit session_selector(const selectorvalue_type& called, const transport_selector& tselector) : called_(called), tselector_(tselector) {
            }

            explicit session_selector(const selectorvalue_type& called, const selectorvalue_type& calling, const transport_selector& tselector) : called_(called), calling_(calling), tselector_(tselector) {
            }

            session_selector(const transport_selector& tselector) : tselector_(tselector) {
            }

            const raw_type& called() const {
                return called_.to_raw();
            }

            const raw_type& calling() const {
                return calling_.to_raw();
            }

            const transport_selector& tselector() const {
                return tselector_;
            }

        private:
            transport_selector tselector_;
            selectorvalue_type called_;
            selectorvalue_type calling_;
        };


        ///

        class presentation_selector {
        public:

            presentation_selector() : sselector_() {
            }

            explicit presentation_selector(const selectorvalue_type& called) : called_(called), sselector_() {
            }

            explicit presentation_selector(const selectorvalue_type& called, const selectorvalue_type& calling) : called_(called), calling_(calling), sselector_() {
            }

            explicit presentation_selector(const selectorvalue_type& called, const session_selector& sselector) : called_(called), sselector_(sselector) {
            }

            explicit presentation_selector(const selectorvalue_type& called, const selectorvalue_type& calling, const session_selector& sselector) : called_(called), calling_(calling), sselector_(sselector) {
            }

            presentation_selector(const session_selector& sselector) : sselector_(sselector) {
            }

            std::string called() const {
                return called_.to_string();
            }

            std::string calling() const {
                return calling_.to_string();
            }

            void called(const std::string& val) {
                called_ = selectorvalue_type(val);
            }

            void calling(const std::string& val) {
                calling_ = selectorvalue_type(val);
            }

            const session_selector& sselector() const {
                return sselector_;
            }

        private:

            session_selector sselector_;
            selectorvalue_type called_;
            selectorvalue_type calling_;

        };

    }
} // namespace boost

#endif	

