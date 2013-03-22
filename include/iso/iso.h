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
    namespace itu {

        // ref X224 = ITU-T Rec. X.224(1995 E)

        using boost::system::error_code;

        const error_code ER_BEDSEQ = error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
        const error_code ER_REQBUSY = error_code(boost::system::errc::device_or_resource_busy, boost::system::system_category());
        const error_code ER_NOBUFFER = error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
        const error_code ER_PROTOCOL = error_code(boost::system::errc::protocol_error, boost::system::system_category());
        const error_code ER_BADADDRESS = error_code(boost::system::errc::bad_address, boost::system::system_category());
        const error_code ER_NAADDRESS = error_code(boost::system::errc::address_not_available, boost::system::system_category());
        const error_code ER_OUTDOMAIN = error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
        const error_code ER_PROTOPT = error_code(boost::system::errc::no_protocol_option, boost::system::system_category());
        const error_code ER_INOUT = error_code(boost::system::errc::io_error, boost::system::system_category());
        const error_code ER_REFUSE = error_code(boost::system::errc::connection_refused, boost::system::system_category());
        const error_code ER_ABORT = error_code(boost::system::errc::connection_aborted, boost::system::system_category());
        const error_code ER_RELEASE = error_code(boost::system::errc::connection_reset, boost::system::system_category());
        const error_code ER_NOLINK = error_code(boost::system::errc::no_link, boost::system::system_category());
        const error_code ER_EAGAIN = error_code(boost::system::errc::resource_unavailable_try_again, boost::system::system_category());
        const error_code ER_TIMEOUT = error_code(boost::system::errc::timed_out, boost::system::system_category());
        const error_code ER_INPROGRESS = error_code(boost::system::errc::operation_in_progress, boost::system::system_category());

        //   transport
        // TPDU size  ref X224  13.3.4 b)
        const octet_type TPDU_SIZE8192 = '\xD'; // not denied in 0 class
        const octet_type TPDU_SIZE4096 = '\xC'; // not denied in 0 class
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
            SIZE128 = TPDU_SIZE128
        } tpdu_size;


        // Disconnection  REASON CODE *ref X224  13.5.3 d) and  *ref X225 8.3.5.10          
        const octet_type DR_REASON_NODEF = '\x00'; // Reason not specified         
        const octet_type DR_REASON_CONGST = '\x01'; // Congestion at TSAP  - ER_EAGAIN             
        const octet_type DR_REASON_SESSION = '\x02'; // Session entity not attached to TSAP                       
        const octet_type DR_REASON_ADDRESS = '\x03'; // address   error  - ER_NAADDRESS
        const octet_type DR_REASON_NORM = '\x80'; // Normal disconnect initiated by session entity.  -ER_RELEASE
        const octet_type DR_REASON_RCNGS = '\x81'; //Remote transport entity congestion at connect request time. -ER_REQBUSY   
        const octet_type DR_REASON_NEGOT = '\x82'; // Connection negotiation failed [i.e. proposed class(es) not supported].-ER_REQBUSY
        const octet_type DR_REASON_PROTO = '\x85'; // Protocol error.  -ER_PROTOCOL
        const octet_type DR_REASON_USER = '\x86'; // User refuse.  -ER_PROTOCOL        
        const octet_type DR_REASON_INVLN = '\x8A'; // Header or parameter length invalid.

        error_code errorcode_by_reason(octet_type val);

        ///   selectors type            

        class selectorvalue_type {
        public:

            selectorvalue_type() {
            }

            selectorvalue_type(const std::string& vl) : value_(octet_sequnce(vl.begin(), vl.end())) {
            }

            explicit selectorvalue_type(const octet_sequnce& vl) : value_(vl) {
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

            const octet_sequnce& to_raw() const {
                return value_;
            }

        private:
            octet_sequnce value_;
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

            const octet_sequnce& called() const {
                return called_.to_raw();
            }

            const octet_sequnce& calling() const {
                return calling_.to_raw();
            }

            std::string called_str() const {
                return called_.to_string();
            }

            std::string calling_str() const {
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

            const octet_sequnce& called() const {
                return called_.to_raw();
            }

            const octet_sequnce& calling() const {
                return calling_.to_raw();
            }

            std::string called_str() const {
                return called_.to_string();
            }

            std::string calling_str() const {
                return calling_.to_string();
            }

            const transport_selector& tselector() const {
                return tselector_;
            }

        private:
            selectorvalue_type called_;
            selectorvalue_type calling_;
            transport_selector tselector_;            
        };



        /// Presentation

        class presentation_selector {
        public:

            presentation_selector() :  called_(), calling_(),sselector_() {
            }

            explicit presentation_selector(const selectorvalue_type& called) : called_(called),  calling_(), sselector_(){
            }

            explicit presentation_selector(const selectorvalue_type& called, const selectorvalue_type& calling) : called_(called), calling_(calling), sselector_() {
            }

            explicit presentation_selector(const selectorvalue_type& called, const session_selector& sselector) : called_(called), calling_(),  sselector_(sselector) {
            }

            explicit presentation_selector(const selectorvalue_type& called, const selectorvalue_type& calling, const session_selector& sselector) : called_(called), calling_(calling), sselector_(sselector) {
            }

            presentation_selector(const session_selector& sselector) : called_(), calling_(), sselector_(sselector) {
            }

            const octet_sequnce& called() const {
                return called_.to_raw();
            }

            const octet_sequnce& calling() const {
                return calling_.to_raw();
            }

            void called(const octet_sequnce& val) {
                called_ = selectorvalue_type(val);
            }

            void calling(const octet_sequnce& val) {
                calling_ = selectorvalue_type(val);
            }

            std::string called_str() const {
                return called_.to_string();
            }

            std::string calling_str() const {
                return calling_.to_string();
            }

            const session_selector& sselector() const {
                return sselector_;
            }

        private:

            selectorvalue_type called_;
            selectorvalue_type calling_;
            session_selector sselector_;

        };



#if defined(ITUX200_DEBUG) 

        inline static std::ostream& operator<<(std::ostream& stream, const transport_selector& self) {
            return stream << "Transport selector is called  = " << self.called_str() << ",  calling = " << self.calling_str() << ",  tpdusize = " << (int) self.pdusize() << " ;\n";
        }

        inline static std::ostream& operator<<(std::ostream& stream, const session_selector& self) {
            stream << "Session selector is called  = " << self.called_str() << ",  calling = " << self.calling_str() << ";\n";
            return stream << self.tselector();
        }

        inline static std::ostream& operator<<(std::ostream& stream, const presentation_selector& self) {
            stream << "Presentation selector is called  = " << self.called_str() << ",  calling = " << self.calling_str() << ";\n";
            return stream << self.sselector();
        }

#endif                   

    }
} // namespace boost

#endif	

