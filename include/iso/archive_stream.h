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
#include <list>
#include <stack>

#include <boost/asio/detail/push_options.hpp>



namespace boost {
    namespace asio {
        namespace iso {


            std::string binary_to_hexsequence_debug(const std::string& vl);


            typedef  std::vector<int8_t>                                     row_type;
            typedef  boost::shared_ptr<row_type>                      row_type_ptr;
            typedef  std::vector<row_type_ptr>                          vect_row_type_ptr;



            typedef  std::list<mutable_buffer>                                                                                             list_mutable_buffers;
            typedef  std::list<const_buffer>                                                                                                 list_const_buffers;



            list_mutable_buffers sublist( const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, std::size_t start = 0 , std::size_t size = 0 );
            std::size_t pop_frontlist(list_mutable_buffers& val,  std::size_t start);
            bool splice_frontlist(list_mutable_buffers& val,  std::size_t firstend, std::size_t secondend);            
            bool find_eof(const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit,  std::size_t& rslt, std::size_t start = 0);
            bool row_cast( const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, row_type& raw,  std::size_t start , std::size_t size);

            class buffer_sequence : protected  std::list<row_type_ptr> {
                typedef std::list<row_type_ptr> super_rype;

            public:

                typedef super_rype::iterator                              iterator;
                typedef super_rype::const_iterator                     const_iterator;
                typedef super_rype::reverse_iterator                  reverse_iterator;
                typedef super_rype::const_reverse_iterator         const_reverse_iterator;

                buffer_sequence() : std::list<row_type_ptr>(), octet_size_(0) {
                }

                void  push_back(const row_type& vl)  {
                    if (vl.empty()) return;
                    octet_size_ += vl.size();
                    super_rype::push_back(row_type_ptr( new row_type(vl)));
                }

                void  push_front(const row_type& vl)  {
                    if (vl.empty()) return;
                    octet_size_ += vl.size();
                    super_rype::push_front(row_type_ptr( new row_type(vl)));
                }

                iterator  insert(const row_type& vl, iterator it)  {
                    if (vl.empty()) return it;
                    octet_size_ += vl.size();
                    return super_rype::insert(it, row_type_ptr(new row_type(vl)));
                }

                iterator insert(const row_type& vl, std::size_t sz, iterator bg)  {
                    std::size_t tmsz = 0;
                    for (iterator it = bg; it != end(); ++it) {
                        if (((*it)->size() + tmsz) < sz)
                            tmsz += (*it)->size();
                        else {
                            if (((*it)->size() + tmsz) == sz)
                                return insert(vl, ++it);
                            else {
                                std::size_t szdelim = (*it)->size() + tmsz - sz;
                                row_type_ptr tmp = *it;
                                row_type_ptr first = row_type_ptr( new row_type(tmp->begin(), tmp->begin() + szdelim));
                                row_type_ptr thr = row_type_ptr( new row_type(tmp->begin() + szdelim, tmp->end()));
                                it = super_rype::erase(it);
                                it = super_rype::insert(it, first);
                                octet_size_ += vl.size();
                                iterator itr = it = super_rype::insert(it, row_type_ptr( new row_type(vl)));
                                it = super_rype::insert(it, thr);
                                return itr;
                            }
                        }
                    }
                    push_back(vl);
                    return end();
                }

                std::size_t octet_size() const {
                    return octet_size_;
                }


            private:

                std::size_t octet_size_;

            } ;







            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////

            class base_oarchive {
            public:

                typedef  list_const_buffers                 list_buffers;
                typedef  list_const_buffers::iterator    iterator;                

                static bool __input__() {
                    return false;
                }

                base_oarchive() : size_(0) {
                }

               list_buffers  buffers() const {
                   return listbuffers_;
                }

                iterator  add(const row_type& vl)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    size_ += vl.size();
                    return listbuffers_.insert(listbuffers_.end(), const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator  add(const row_type& vl, iterator it)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(row_type_ptr( new row_type(vl)));
                    size_ += vl.size();
                    return listbuffers_.insert(it, const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator  last()  {
                    return  listbuffers_.empty()  ? listbuffers_.end() :  (--listbuffers_.end());
                }

                std::size_t  size(std::size_t sz = 0) const  {
                    return (sz < size_) ? (size_ - sz) : 0;
                }

                virtual void clear()  {
                    listbuffers_.clear();
                    rows_vect.clear();
                    size_ = 0;
                }
                
   


            protected:

                list_buffers               listbuffers_;
                vect_row_type_ptr    rows_vect;
                std::size_t                size_;

            } ;


            //////////////////////////////////////////////////////////////////////////////

            class base_iarchive {
            public:
                
                typedef  list_mutable_buffers                 list_buffers;
                typedef  list_mutable_buffers::iterator    iterator;                 

                static bool __input__() {
                    return true;
                }

                base_iarchive() : size_(0) {
                }

                void add(const row_type& vl) {
                    rows_vect.push_back( row_type_ptr(new row_type(vl.begin(), vl.end())));
                    size_ += vl.size();
                    listbuffers_.push_back(mutable_buffer(&rows_vect.back()->operator [](0), rows_vect.back()->size()));
                    size_ += rows_vect.back()->size();
                }

                void add(const base_oarchive& vl) {
                    listbuffers_.clear();
                    list_const_buffers buffers = vl.buffers();
                    for (list_const_buffers::const_iterator it = buffers.begin(); it != buffers.end(); ++it) {
                        listbuffers_.push_back(mutable_buffer(const_cast<row_type::value_type*> (boost::asio::buffer_cast<const row_type::value_type*>(*it)), boost::asio::buffer_size(*it)));
                        size_ += boost::asio::buffer_size(*it);
                    }
                    std::cout << "IARCHVE size:"  << size_  << std::endl;
                }

                void pop_front(std::size_t sz) {
                    decsize(pop_frontlist(listbuffers_, sz));
                }

                bool is_endof(std::size_t beg = 0) const {
                    row_type  data;
                    if (row_cast(listbuffers_, listbuffers_.begin(), data,  beg , 2)) {
                        if ((data.size() == 2) && (data[0] == 0) && (data[1] == 0)) {
                            return true;
                        }
                    }
                    return false;
                }
                
                

                const list_buffers&  buffers() const {
                    return listbuffers_;
                }

                list_buffers&  buffers() {
                    return listbuffers_;
                }

                iterator  last()  {
                    return  listbuffers_.empty()  ? listbuffers_.end() :  (--listbuffers_.end());
                }

                std::size_t  size(std::size_t sz) {
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
                    size_ =  size_ < sz ? 0 : (size_ - sz);
                    std::cout << "IARCHVE size:"  << size_  << std::endl;
                }

                list_buffers                listbuffers_;
                vect_row_type_ptr     rows_vect;
                std::size_t                 size_;
                
            } ;





            std::ostream& operator<<(std::ostream& stream, const list_const_buffers& self);

            std::ofstream& operator<<(std::ofstream& stream, const list_const_buffers& self);

            std::ostream& operator<<(std::ostream& stream, const base_oarchive& vl);

            std::ofstream& operator<<(std::ofstream& stream, const base_oarchive& vl);

            std::ostream& operator<<(std::ostream& stream, const  list_mutable_buffers& vl);

            std::ofstream& operator<<(std::ofstream& stream, const  list_mutable_buffers& vl);


        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

