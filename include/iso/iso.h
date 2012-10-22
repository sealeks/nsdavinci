

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

#include <boost/asio/detail/push_options.hpp>



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
                T tmp=0;
                return str_to_inttype<T>(vl,tmp) ? (((tmp >> 8) & 0xFF) | (0xFF00 & (tmp<< 8))) : 0;
            }            
            

                         




        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

