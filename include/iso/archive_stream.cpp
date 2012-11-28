/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <iosfwd>
#include <iostream>
#include <sstream>
#include <iostream>
#include <fstream>

#include <iso/archive_stream.h>


namespace boost {
    namespace asio {
        namespace iso {

            const char hex_char_array_const[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
            const char bad_hex_char = '\xFF';


            static inline std::string num8t_to_hexstr(char vl) {
                return std::string(static_cast<const char*> (&hex_char_array_const[((vl >> 4) & 0xF)]), 1) +
                        std::string(static_cast<const char*> (&hex_char_array_const[((vl) & 0xF)]), 1);
            }

            std::string binary_to_hexsequence_debug(const std::string& vl) {
                std::string rslt = "";
                for (std::string::size_type it = 0; it < vl.size(); ++it) {
                    rslt = rslt + " " + num8t_to_hexstr(vl.at(it));
                }
                return rslt;
            }

            list_mutable_buffers sublist( const list_mutable_buffers& val, std::size_t start, std::size_t size ) {
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

            std::size_t pop_frontlist(list_mutable_buffers& val, std::size_t start) {
                std::size_t rslt = 0;
                while (start && (!val.empty())) {
                    if (boost::asio::buffer_size(val.front()) < start) {
                        start -= boost::asio::buffer_size(val.front());
                        rslt += boost::asio::buffer_size(val.front());
                        val.erase(val.begin());
                    }
                    else {
                        rslt += start;
                        val.front() = val.front() + start;
                        return rslt;
                    }
                }
                return rslt;
            }

            bool find_eof(const list_mutable_buffers& val, std::size_t& rslt) {
                rslt = 0;
                bool findend = false;
                for (list_mutable_buffers::const_iterator it = val.begin(); it != val.end(); ++it) {
                    mutable_buffer tmp = *it;
                    std::size_t size = boost::asio::buffer_size(*it);
                    for (std::size_t i = 0; i < size; ++i) {
                        if (findend) {
                            if (!(*boost::asio::buffer_cast<row_type::value_type*>(boost::asio::buffer(tmp + i, 1)))) {
                                rslt--;
                                return true;
                            }
                            findend = false;
                        }
                        else {
                            findend = !(*boost::asio::buffer_cast<row_type::value_type*>(boost::asio::buffer(tmp + i, 1)));
                        }
                        rslt++;
                    }
                }
                return false;
            }

            bool row_cast( const list_mutable_buffers& val, row_type& raw,  std::size_t start, std::size_t size) {
                if (!size)
                    return true;
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
                    stream << binary_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
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
                    stream << binary_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
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

            std::ostream& operator<<(std::ostream& stream, const  list_mutable_buffers& self) {
                for (list_mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                    stream << binary_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                stream << std::endl;
                return stream;

            }

            std::ofstream& operator<<(std::ofstream& stream, const  list_mutable_buffers& self) {
                for (list_mutable_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                    stream << std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) );
                stream << std::endl;
                return stream;
            }



        }
    }
}
