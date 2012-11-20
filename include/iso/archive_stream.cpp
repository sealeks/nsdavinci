/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 */

#include <iosfwd>
#include <iostream>
#include <sstream>

#include <iso/archive_stream.h>


namespace boost {
    namespace asio {
        namespace iso {

            list_mutable_buffers intersect( const list_mutable_buffers& val, std::size_t start, std::size_t size ) {
                if (!(size || start)) return val;
                list_mutable_buffers::const_iterator it = val.begin();
                std::size_t sz = 0;
                list_mutable_buffers tmp;
                std::size_t szc = 0 ;
                std::size_t szb = 0;
                std::size_t sze =0;                
                while ((((start + sz) < size) || (!size)) && (it != val.end())) {
                    szc = boost::asio::buffer_size(*it);
                    if (!((sz + szc) < start)) {
                        szb = sz > start ? 0 : start - sz;
                        sze =( !size || ((szb + size) > szc)) ? szc-szb  : size;
                        tmp.push_back(boost::asio::buffer(*it + szb, sze ));
                    }
                    else {
                        sz += szc;
                    }
                    ++it;
                }
                return tmp;
            }
            
            bool row_cast( const list_mutable_buffers& val, row_type& raw,  std::size_t start, std::size_t size){
                 if (!(size || start)) return false;
                list_mutable_buffers::const_iterator it = val.begin();
                std::size_t sz = 0;
                std::size_t szc = 0 ;
                std::size_t szb = 0;
                std::size_t sze =0;                   
                while ((((start + sz) < size) || (!size)) && (it != val.end())) {
                    szc = boost::asio::buffer_size(*it);
                    if (!((sz + szc) < start)) {
                        szb = sz > start ? 0 : start - sz;
                        sze =( !size || ((szb + size) > szc)) ? szc-szb  : size;
                        mutable_buffer tmp= boost::asio::buffer(*it + szb, sze );
                        raw.insert(raw.end(), boost::asio::buffer_cast<row_type::value_type*>(tmp), boost::asio::buffer_cast<row_type::value_type*>(tmp) + boost::asio::buffer_size(tmp));
                    }
                    else {
                        sz += szc;
                    }
                    ++it;
                } 
                return (raw.size()==size);
            }            




        }
    }
}
