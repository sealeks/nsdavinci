/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 */

#include <iosfwd>
#include <iostream>
#include <sstream>

#include <kernel/constdef.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>
#include <kernel/templ.h>

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
                std::size_t sze = 0;
                while (((sz < (size + start) || (!size))) && (it != val.end())) {
                    szc = boost::asio::buffer_size(*it);
                    if ((sz + szc) > start) {
                        szb = sz > start ? 0 : start - sz;
                        sze = ( !size || ((szb + size) > szc)) ? szc - szb  : size;
                        tmp.push_back(boost::asio::buffer(*it + szb, sze ));
                    }
                    sz += szc;
                    ++it;
                }
                return tmp;
            }
            
            void popfront_list(list_mutable_buffers& val, std::size_t start){
                while (start && (!val.empty())) {
                    if(boost::asio::buffer_size(val.front()) < start){
                        start-=boost::asio::buffer_size(val.front());
                        val.erase(val.begin());
                    }
                    else{
                         val.front()=val.front()+start;
                         return;
                    }
                }
            }            

            bool row_cast( const list_mutable_buffers& val, row_type& raw,  std::size_t start, std::size_t size) {
                if (!(size || start)) return false;
                list_mutable_buffers::const_iterator it = val.begin();
                std::size_t sz = 0;
                std::size_t szc = 0 ;
                std::size_t szb = 0;
                std::size_t sze = 0;
                while ((( sz < (start + size)) || (!size)) && (it != val.end())) {
                    szc = boost::asio::buffer_size(*it);
                    if ((sz + szc) > start) {
                        szb = sz > start ? 0 : start - sz;
                        sze = ( !size || ((szb + size) > szc)) ? szc - szb  : size;
                        mutable_buffer tmp = boost::asio::buffer(*it + szb, sze );
                        raw.insert(raw.end(), boost::asio::buffer_cast<row_type::value_type*>(tmp), boost::asio::buffer_cast<row_type::value_type*>(tmp) + boost::asio::buffer_size(tmp));
                    }
                    sz += szc;
                    ++it;
                }
                return (raw.size() == size);
            }


            
            
                std::ostream& operator<<(std::ostream& stream, const const_buffers& self) {
                    for (const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << dvnci::binary_block_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                    stream << std::endl;
                    return stream;
                }

                std::ofstream& operator<<(std::ofstream& stream, const const_buffers& self) {
                    for (const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) );
                    stream << std::endl;
                    return stream;
                }    
                
                
                std::ostream& operator<<(std::ostream& stream, const mutable_buffers& self) {
                    for (mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << dvnci::binary_block_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                    stream << std::endl;
                    return stream;
                }

                std::ofstream& operator<<(std::ofstream& stream, const mutable_buffers& self) {
                    for (mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) );
                    stream << std::endl;
                    return stream;
                }           
                
                
                std::ostream& operator<<(std::ostream& stream, const base_oarchive& vl) {
                    stream << vl.buffers();
                    return stream;
                }

                std::ofstream& operator<<(std::ofstream& stream, const base_oarchive& vl) {
                    stream << vl.buffers();
                    return stream;
                }            
                
                std::ostream& operator<<(std::ostream& stream, const  list_mutable_buffers& self){
                    for (list_mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << dvnci::binary_block_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                    stream << std::endl;
                    return stream;                    
                    
                }

                std::ofstream& operator<<(std::ofstream& stream, const  list_mutable_buffers& self){
                    for (list_mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                        stream << std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) );
                    stream << std::endl;
                    return stream;                    
                }
            


        }
    }
}
