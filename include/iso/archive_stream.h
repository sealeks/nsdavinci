/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOARCHIVESTREAM_H_H
#define         ISOARCHIVESTREAM_H_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <boost/asio/detail/push_options.hpp>



namespace boost {
    namespace asio {
        namespace iso {


            typedef  std::vector<int8_t>                                     row_type;
            typedef  boost::shared_ptr<row_type>                      row_type_ptr;
            typedef  std::vector<row_type_ptr>                          vect_row_type_ptr;


            typedef  std::vector<const_buffer>                          const_buffers;
            typedef  boost::shared_ptr<const_buffers>               const_buffers_ptr;


            typedef  std::vector<mutable_buffer>                      mutable_buffers;
            typedef  boost::shared_ptr<mutable_buffers>           mutable_buffers_ptr;

            typedef  std::list<mutable_buffer>                                                                                             list_mutable_buffers;
            typedef  list_mutable_buffers::iterator                                                                                        iterator_list_mutable_buffers;
            typedef std::pair<iterator_list_mutable_buffers, iterator_list_mutable_buffers>                              list_mutable_iterator_pair;


            list_mutable_buffers sublist( const list_mutable_buffers& val, std::size_t start = 0 , std::size_t size = 0 );
            std::size_t pop_frontlist(list_mutable_buffers& val, std::size_t start);
            bool find_eof(const list_mutable_buffers& val, std::size_t& rslt);            
            bool row_cast( const list_mutable_buffers& val, row_type& raw,  std::size_t start , std::size_t size);







            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            class base_oarchive {
            public:

                typedef  std::list<const_buffer>                                                                                         list_const_buffers;
                typedef  list_const_buffers::iterator                                                                                    iterator_list_const_buffers;
                typedef std::pair<iterator_list_const_buffers, iterator_list_const_buffers>                              list_iterator_pair;

                base_oarchive() : size_(0) {
                }

                const_buffers  buffers() const {
                    return const_buffers(listbuffers_.begin(), listbuffers_.end());
                }

                iterator_list_const_buffers  add(const row_type& vl)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    size_ += vl.size();
                    return listbuffers_.insert(listbuffers_.end(), const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator_list_const_buffers  add(const row_type& vl, iterator_list_const_buffers it)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    size_ += vl.size();
                    return listbuffers_.insert(it, const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator_list_const_buffers  last()  {
                    return  listbuffers_.empty()  ? listbuffers_.end() :  (--listbuffers_.end());
                }

                std::size_t  size(std::size_t sz = 0) const  {
                    return (sz < size_) ? (size_ - sz) : 0;
                }

                void clear()  {
                    listbuffers_.clear();
                    rows_vect.clear();
                    size_ = 0;
                }

            protected:

                list_const_buffers listbuffers_;
                vect_row_type_ptr rows_vect;
                std::size_t                size_;
            } ;
            
            
            //////////////////////////////////////////////////////////////////////////////

            class base_iarchive {
            public:

                base_iarchive() : size_(0) {
                }

                void add(const row_type& vl) {
                    rows_vect.push_back( row_type_ptr(new row_type(vl.begin(), vl.end())));
                    size_+=vl.size();
                    listbuffers_.push_back(mutable_buffer(&rows_vect.back()->operator [](0), rows_vect.back()->size()));
                    size_ += rows_vect.back()->size();
                }

                void add(const std::string& vl) {
                    rows_vect.push_back( row_type_ptr(new row_type(vl.begin(), vl.end())));
                    listbuffers_.push_back(mutable_buffer(&rows_vect.back()->operator [](0), rows_vect.back()->size()));
                    size_ += rows_vect.back()->size();
                }

                void add(const base_oarchive& vl) {
                    listbuffers_.clear();
                    const_buffers buffers = vl.buffers();
                    for (const_buffers::const_iterator it = buffers.begin(); it != buffers.end(); ++it) {
                        listbuffers_.push_back(mutable_buffer(const_cast<row_type::value_type*> (boost::asio::buffer_cast<const row_type::value_type*>(*it)), boost::asio::buffer_size(*it)));
                        size_ += boost::asio::buffer_size(*it);
                    }
                    std::cout << "IARCHVE size:"  << size_  << std::endl;
                }


                void pop_front(std::size_t sz) {
                    decsize(pop_frontlist(listbuffers_, sz));
                }
                
                bool is_endof() {
                    row_type  data;
                    if (row_cast(listbuffers_, data,  0 , 2)){
                        if ((data.size()==2) && (data[0]==0) && (data[1]==0)){
                            decsize(pop_frontlist(listbuffers_, 2));
                            return true;
                        } 
                    }
                    return false;
                }                

                const list_mutable_buffers&  buffers() const {
                    return listbuffers_;
                }

                list_mutable_buffers&  buffers() {
                    return listbuffers_;
                }

                iterator_list_mutable_buffers  last()  {
                    return  listbuffers_.empty()  ? listbuffers_.end() :  (--listbuffers_.end());
                }

                std::size_t  size(std::size_t sz = 0) const  {
                    return (sz < size_) ? (size_ - sz) : 0;
                }

                void clear()  {
                    listbuffers_.clear();
                    size_ = 0;
                }
                
                std::size_t size() const {
                    return size_;
                }

            protected:
                
                void decsize(std::size_t sz)  {
                    size_ =  size_<sz ? 0 : (size_-sz);
                    std::cout << "IARCHVE size:"  << size_  << std::endl;
                }                

                list_mutable_buffers listbuffers_;
                vect_row_type_ptr     rows_vect;
                std::size_t                size_;
            } ;





            std::ostream& operator<<(std::ostream& stream, const const_buffers& self);

            std::ofstream& operator<<(std::ofstream& stream, const const_buffers& self);

            std::ostream& operator<<(std::ostream& stream, const mutable_buffers& self);

            std::ofstream& operator<<(std::ofstream& stream, const mutable_buffers& self);


            std::ostream& operator<<(std::ostream& stream, const base_oarchive& vl);

            std::ofstream& operator<<(std::ofstream& stream, const base_oarchive& vl);

            std::ostream& operator<<(std::ostream& stream, const  list_mutable_buffers& vl);

            std::ofstream& operator<<(std::ofstream& stream, const  list_mutable_buffers& vl);


        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

