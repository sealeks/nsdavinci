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
            
            
            
            typedef std::vector<const_buffer>                                                      vector_buffer;
            typedef const vector_buffer&                                                         const_vector_buffer;
            typedef vector_buffer::iterator                                                      vector_buffer_iterator;

            const vector_buffer NULL_VECTOR_BUFFER = vector_buffer();


            typedef  std::vector<int8_t>                                     raw_type;
            typedef  boost::shared_ptr<raw_type>                      raw_type_ptr;
            typedef  std::vector<raw_type_ptr>                          vect_raw_type_ptr;

            typedef  std::list<mutable_buffer>                                                                                             list_mutable_buffers;
            typedef  std::list<const_buffer>                                                                                                 list_const_buffers;



            std::size_t pop_frontlist(list_mutable_buffers& val,  std::size_t start);
            bool splice_frontlist(list_mutable_buffers& val,  std::size_t firstend, std::size_t secondend);            
            bool find_eof(const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit,  std::size_t& rslt, std::size_t start = 0);
            bool row_cast( const list_mutable_buffers& val, list_mutable_buffers::const_iterator bit, raw_type& raw,  std::size_t start , std::size_t size);

            
            
                       

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
               
               vector_buffer  const_buffers() const {
                   return vector_buffer(listbuffers_.begin(),listbuffers_.end());
                }               

                iterator  add(const raw_type& vl)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(raw_type_ptr( new raw_type(vl)));
                    size_ += vl.size();
                    return listbuffers_.insert(listbuffers_.end(), const_buffer(&(rows_vect.back()->operator[](0)), rows_vect.back()->size()));
                }

                iterator  add(const raw_type& vl, iterator it)  {
                    if (vl.empty()) return
                        listbuffers_.end();
                    rows_vect.push_back(raw_type_ptr( new raw_type(vl)));
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
                
                bool  bind(raw_type& vl){
                    vl.clear();
                    for(iterator it=listbuffers_.begin();it!=listbuffers_.end();++it)
                        vl.insert(vl.end(),
                                const_cast<raw_type::value_type*> (boost::asio::buffer_cast<const raw_type::value_type*>(*it)),
                                const_cast<raw_type::value_type*> (boost::asio::buffer_cast<const raw_type::value_type*>(*it)) + boost::asio::buffer_size(*it));
                      clear();
                      return true;
                }
                
                virtual int test_id() {
                    return 0;
                }
                
                virtual int test_class() {
                    return 0;
                }                
                
   


            protected:

                list_buffers               listbuffers_;
                vect_raw_type_ptr    rows_vect;
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

                void add(const raw_type& vl) {
                    rows_vect.push_back( raw_type_ptr(new raw_type(vl.begin(), vl.end())));
                    size_ += vl.size();
                    listbuffers_.push_back(mutable_buffer(&rows_vect.back()->operator [](0), rows_vect.back()->size()));
                }

                void add(const base_oarchive& vl) {
                    listbuffers_.clear();
                    list_const_buffers buffers = vl.buffers();
                   /* for (list_const_buffers::const_iterator it = buffers.begin(); it != buffers.end(); ++it) {
                        listbuffers_.push_back(mutable_buffer(const_cast<raw_type::value_type*> (boost::asio::buffer_cast<const raw_type::value_type*>(*it)), boost::asio::buffer_size(*it)));
                        size_ += boost::asio::buffer_size(*it);
                    }*/
                    
                    raw_type newdata;
                    for (list_const_buffers::const_iterator it = buffers.begin(); it != buffers.end(); ++it) {
                        newdata.insert(newdata.end(),
                                const_cast<raw_type::value_type*> (boost::asio::buffer_cast<const raw_type::value_type*>(*it)),
                                const_cast<raw_type::value_type*> (boost::asio::buffer_cast<const raw_type::value_type*>(*it)) + boost::asio::buffer_size(*it)
                                );
                    }
                    add(newdata);                     
                     
                    std::cout << "IARCHVE size:"  << size_  << std::endl;
                }

                void pop_front(std::size_t sz) {
                    decsize(pop_frontlist(listbuffers_, sz));
                }

                bool is_endof(std::size_t beg = 0) const {
                    raw_type  data;
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

                bool  bind(const raw_type& vl){
                      clear();
                      add(vl);
                      return true;
                }
                
                virtual int test_id() = 0;
                
                virtual int test_class() = 0;                

            protected:

                void decsize(std::size_t sz)  {
                    size_ =  size_ < sz ? 0 : (size_ - sz);
                    std::cout << "decsize IARCHVE size:"  << size_  << std::endl;
                }

                list_buffers                listbuffers_;
                vect_raw_type_ptr     rows_vect;
                std::size_t                 size_;
                
            } ;
            
  
             

            //////////////////////////////////////////////////////////////////////////////
             
             
             
            class base_archive {

               
            public:
                        
                typedef  boost::shared_ptr<base_iarchive>                       iarchive_ptr;                
                typedef  boost::shared_ptr<base_oarchive>                      oarchive_ptr;                
              
                base_archive(iarchive_ptr in, oarchive_ptr out) : input_(in), output_(out) {}
                virtual ~base_archive(){}
                
                vector_buffer request() const {
                    return output_->const_buffers();}
                
                void insert_to_input(const raw_type& vl){
                    input_->add(vl);}
                
                 std::string request_str() const {
                        const vector_buffer& tmp = request();
                        std::string rslt;
                        for (vector_buffer::const_iterator it = tmp.begin(); it != tmp.end(); ++it) {
                        rslt.insert(rslt.end(),
                                const_cast<std::string::value_type*> (boost::asio::buffer_cast<const std::string::value_type*>(*it)),
                                const_cast<std::string::value_type*> (boost::asio::buffer_cast<const std::string::value_type*>(*it)) + boost::asio::buffer_size(*it)
                                );
                        }
                        return rslt;
                };

                void respond_str(const std::string&  val) {
                    insert_to_input(raw_type(val.begin(), val.end()));
                };                  
                
            protected:
                             
                
                iarchive_ptr input_;
                oarchive_ptr output_;
            };
            
            

             typedef  boost::shared_ptr<base_archive>                      archive_ptr; 
             
             
             
             template<typename INPUT_TYPE,  typename OUTPUT_TYPE>
              class archive_temp : public base_archive{
                 
              public:                   
                 
                 typedef INPUT_TYPE in_archive_type;
                 typedef OUTPUT_TYPE out_archive_type;                 
                 
                archive_temp() : base_archive(iarchive_ptr(in_archive_type()), oarchive_ptr(out_archive_type())) {}
                
                in_archive_type& input() {
                    return *boost::static_pointer_cast<in_archive_type, base_iarchive>(input_);
                }
                
                const in_archive_type& input() const {
                    return *boost::static_pointer_cast<in_archive_type, base_iarchive>(input_);
                }         
                
                out_archive_type& output() {
                    return *boost::static_pointer_cast<out_archive_type, base_oarchive>(output_);
                }
                
                const out_archive_type& output() const {
                    return *boost::static_pointer_cast<out_archive_type, base_oarchive>(output_);
                }                  
                          
                  
             };
             
            //////////////////////////////////////////////////////////////////////////////             
             
             

            std::ostream& operator<<(std::ostream& stream, const list_const_buffers& self);

            std::ofstream& operator<<(std::ofstream& stream, const list_const_buffers& self);

            std::ostream& operator<<(std::ostream& stream, const base_oarchive& vl);

            std::ofstream& operator<<(std::ofstream& stream, const base_oarchive& vl);

            std::ostream& operator<<(std::ostream& stream, const  list_mutable_buffers& vl);

            std::ofstream& operator<<(std::ofstream& stream, const  list_mutable_buffers& vl);
            
            

            ///////////////////////////////////////////////////////////////////////////////////////////////////////
            ///////////////////////////////////////////////////////////////////////////////////////////////////////            
           //   class  send_buffer_impl 

            class  send_buffer_impl {
            public:

                send_buffer_impl() : size_(0) {
                }

                virtual ~send_buffer_impl() {
                }

                const_vector_buffer  pop() {
                    return buff_ ;
                }

                std::size_t  size(std::size_t  sz = 0) {

                    if (sz == 0) return size_;
                    std::size_t tmpsize = sz;
                    while ((!buff_.empty()) && tmpsize) {
                        vector_buffer_iterator it = buff_.begin();
                        if (tmpsize < buffer_size(*it)) {
                            *it = const_buffer((*it) + sz);
                            return size_ += sz;
                        }
                        else {
                            tmpsize = buffer_size(*it) > tmpsize ? 0 : (tmpsize - buffer_size(*it));
                            buff_.erase(it);
                        }
                    }
                    return size_ += sz;
                }

                std::size_t  receivesize() const {
                    return  buffer_size(buff_);
                }

                bool ready() const {
                    return  !buffer_size(buff_);
                }


            protected:
                vector_buffer                  buff_;
                std::size_t                        size_;
            } ;


            typedef boost::shared_ptr<send_buffer_impl>      send_buffer_ptr; 


        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

