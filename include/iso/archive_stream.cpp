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

            bool splice_frontlist(list_mutable_buffers& val,  std::size_t firstend, std::size_t secondend) {
                if ((!firstend) || (firstend > secondend))
                    return false;
                if (firstend == secondend)
                    return true;

                list_mutable_buffers::iterator fit = val.end();
                list_mutable_buffers::iterator sit = val.end();
                bool fset = false;
                bool sset = false;

                for (list_mutable_buffers::iterator it = val.begin() ; it != val.end(); ++it) {
                    mutable_buffer tmp = *it;
                    std::size_t size = boost::asio::buffer_size(*it);
                    if (!fset) {
                        if (size >= firstend) {
                            if (size == firstend) {
                                fit = it;
                                fset = true;
                            }
                            else {
                                size = firstend;
                                it = val.insert(val.erase(it) , tmp + firstend);
                                fit = it = val.insert(it, boost::asio::buffer(tmp,  firstend));
                                tmp = *it;
                                fset = true;
                            }
                        }
                    }
                    if (!sset) {
                        if (size >= secondend) {
                            if (size == secondend) {
                                sit = it;
                                sset = true;
                                break;
                            }
                            else {
                                size = secondend;
                                it = val.insert(val.erase(it) , tmp + secondend);
                                sit = it = val.insert(it, boost::asio::buffer(tmp,  secondend));
                                sset = true;
                                break;
                            }
                        }
                    }

                    if (firstend)
                        firstend = (firstend < size) ? 0 : (firstend - size);
                    if (secondend)
                        secondend = (secondend < size) ? 0 : (secondend - size);

                }

                if (fset && sset) {
                   // std::cout << " This Need splice " << std::endl;
                  //  std::cout << "before " << val << std::endl;
                    val.splice(++sit , val , val.begin() , ++fit );
                  //  std::cout << "after " << val << std::endl;
                    return true;
                }

                return false;
            }

            bool find_eof(const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, std::size_t& rslt, std::size_t start) {
                rslt = 0;
                bool findend = false;
                for (list_mutable_buffers::const_iterator it = bit; it != val.end(); ++it) {
                    mutable_buffer tmp = *it;
                    std::size_t size = boost::asio::buffer_size(*it);
                    if (size > start) {
                        for (std::size_t i = 0; i < size; ++i) {
                            if (i >= start) {
                                if (findend) {
                                    if (!(*boost::asio::buffer_cast<row_type::value_type*>(boost::asio::buffer(tmp + i, 1)))) {
                                        rslt--;
                                        return true;
                                    }
                                    findend = false;
                                }
                                else
                                    findend = !(*boost::asio::buffer_cast<row_type::value_type*>(boost::asio::buffer(tmp + i, 1)));
                            }
                            rslt++;
                        }
                    }
                    else
                        rslt += size;

                    if (start)
                        start = (start < size) ? 0 : (start - size);
                }
                return false;
            }

            bool row_cast( const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, row_type& raw,  std::size_t start, std::size_t size) {
                if (!size)
                    return true;
                list_mutable_buffers::const_iterator it = bit;
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

            std::ostream& operator<<(std::ostream& stream, const list_const_buffers& self) {
                for (list_const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
                    stream << binary_to_hexsequence_debug(std::string(boost::asio::buffer_cast<const char*>(*it), boost::asio::buffer_size(*it) ));
                stream << std::endl;

                return stream;
            }

            std::ofstream& operator<<(std::ofstream& stream, const list_const_buffers& self) {
                for (list_const_buffers::const_iterator it = self.begin(); it != self.end(); ++it)
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
