/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOARCHIVESTREAM_H_H
#define         ISOARCHIVESTREAM_H_H



#include <boost/asio/detail/config.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/buffers_iterator.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <list>
#include <stack>
#include <set>
#include <map>

namespace boost {
    namespace asn1 {

        typedef std::size_t oidindx_type;


        //// OID_TYPE

        class oid_type : public std::vector<oidindx_type> {
        public:

            oid_type() : std::vector<oidindx_type>() {
            }

            oid_type(const oidindx_type * vl, std::size_t size);

            oid_type(const boost::array<oidindx_type, 2 > & vl);

            oid_type(const boost::array<oidindx_type, 3 > & vl);

            oid_type(const boost::array<oidindx_type, 4 > & vl);

            oid_type(const boost::array<oidindx_type, 5 > & vl);

            oid_type(const boost::array<oidindx_type, 6 > & vl);

            oid_type(const boost::array<oidindx_type, 7 > & vl);

            oid_type(const boost::array<oidindx_type, 8 > & vl);

            oid_type(const boost::array<oidindx_type, 9 > & vl);

            oid_type(const boost::array<oidindx_type, 10 > & vl);

            oid_type(const boost::array<oidindx_type, 11 > & vl);

            oid_type(const boost::array<oidindx_type, 12 > & vl);

            oid_type(const boost::array<oidindx_type, 13 > & vl);

            oid_type(const boost::array<oidindx_type, 14 > & vl);

            oid_type(const boost::array<oidindx_type, 15 > & vl);

            oid_type(const boost::array<oidindx_type, 16 > & vl);

        };



        std::ostream& operator<<(std::ostream& stream, const oid_type& vl);

    }

    namespace itu {

        typedef enum {
            NULL_ENCODING = 0,
            BER_ENCODING,
            CER_ENCODING,
            DER_ENCODING
        } encoding_rule;

        using boost::asio::const_buffer;
        using boost::asio::const_buffers_1;
        using boost::asio::mutable_buffer;
        using boost::asio::mutable_buffers_1;
        using boost::asn1::oid_type;



        typedef int contex_id_type;
        typedef int8_t octet_type;
        typedef std::vector<octet_type> octet_sequnce;
        typedef boost::shared_ptr<octet_sequnce> octet_sequnce_ptr;
        typedef std::vector<octet_sequnce_ptr> vect_octet_sequnce_ptr;

        typedef std::list<mutable_buffer> mutable_sequences;
        typedef boost::shared_ptr<mutable_sequences> mutable_sequences_ptr;
        typedef std::list<const_buffer> const_sequences;
        typedef boost::shared_ptr<const_sequences> const_sequences_ptr;


        const octet_sequnce NULL_OCTET_SEQUENCE = octet_sequnce();
        const const_sequences NULL_CONST_SEQUENCE = const_sequences();


        const oid_type& encoding_to_oid(encoding_rule rule);

        encoding_rule oid_to_encoding(const oid_type& val);

        std::string binary_to_hexsequence_debug(const std::string& vl);

        inline static octet_sequnce buffer_to_raw(const mutable_buffer& buff, std::size_t beg = 0, std::size_t len = 0) {
            std::size_t buffsize = boost::asio::buffer_size(buff);
            len = (buffsize > beg) ? (((buffsize > (beg + len)) && len) ? len : (buffsize - beg)) : 0;
            return len ? octet_sequnce(boost::asio::buffer_cast<const octet_type*>(buff) + beg,
                    boost::asio::buffer_cast<const octet_type*>(buff) + (beg + len)) : octet_sequnce();
        }

        inline static octet_sequnce buffer_to_raw(const const_buffer& buff, std::size_t beg = 0, std::size_t len = 0) {
            std::size_t buffsize = boost::asio::buffer_size(buff);
            len = (buffsize > beg) ? (((buffsize > (beg + len)) && len) ? len : (buffsize - beg)) : 0;
            return len ? octet_sequnce(boost::asio::buffer_cast<const octet_type*>(buff) + beg,
                    boost::asio::buffer_cast<const octet_type*>(buff) + (beg + len)) : octet_sequnce();
        }

        template <typename T> octet_sequnce
        inline static inttype_to_raw(T vl) {
            return octet_sequnce(((const octet_type*) &vl), ((const octet_type*) &vl) + sizeof (T));
        }

        template <typename T>
        inline static bool raw_to_inttype(const octet_sequnce& dblk, T& vl) {
            if (sizeof (vl) > dblk.size()) return false;
            vl = *(reinterpret_cast<T*> (const_cast<octet_type*> (&dblk.front())));
            return true;
        }

        inline static int16_t endiancnv_copy(int16_t vl) {
            return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
        }

        inline static uint16_t endiancnv_copy(uint16_t vl) {
            return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));
        }

        template <typename T>
        inline static T endiancnv_copy(const octet_sequnce& vl) {
            T tmp = 0;
            return raw_to_inttype<T > (vl, tmp) ? (((tmp >> 8) & 0xFF) | (0xFF00 & (tmp << 8))) : 0;
        }

        inline static void raw_back_insert(octet_sequnce& dst, const octet_sequnce& src) {
            dst.insert(dst.end(), src.begin(), src.end());
        }

        inline static void raw_front_insert(octet_sequnce& dst, const octet_sequnce& src) {
            dst.insert(dst.begin(), src.begin(), src.end());
        }

        std::size_t pop_frontlist(mutable_sequences& val, std::size_t start);

        bool splice_frontlist(mutable_sequences& val, std::size_t firstend, std::size_t secondend);

        bool find_eof(const mutable_sequences& val, mutable_sequences::const_iterator bit, std::size_t& rslt, std::size_t start = 0);

        bool row_cast(const mutable_sequences& val, mutable_sequences::const_iterator bit, octet_sequnce& raw, std::size_t start, std::size_t size);


        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        class base_output_coder {
        public:


            typedef const_sequences::iterator iterator_type;

            static bool __input__() {
                return false;
            }

            base_output_coder(encoding_rule rl = NULL_ENCODING) : listbuffers_(new const_sequences()), size_(0) {
            }

            virtual ~base_output_coder() {
            }

            const const_sequences& buffers() const {
                return *listbuffers_;
            }

            const_sequences& buffers() {
                return *listbuffers_;
            }

            const_sequences_ptr buffers_ptr() const {
                return listbuffers_;
            }

            const_sequences_ptr buffers_ptr() {
                return listbuffers_;
            }

            iterator_type add(const octet_sequnce& vl);

            iterator_type add(const octet_sequnce& vl, iterator_type it);

            void add(const mutable_sequences& vl);

            iterator_type last() {
                return listbuffers_->empty() ? listbuffers_->end() : (--(listbuffers_->end()));
            }

            std::size_t size(std::size_t sz = 0) const {
                return (sz < size_) ? (size_ - sz) : 0;
            }

            std::size_t load_sequence(const_sequences& val, std::size_t lim);

            virtual void clear() {
                listbuffers_->clear();
                rows_vect.clear();
                size_ = 0;
            }

            bool bind(octet_sequnce& vl);

            virtual int test_id() {
                return 0;
            }

            virtual int test_class() {
                return 0;
            }

            void resetextention() {
            }

            virtual encoding_rule rule() const {
                return NULL_ENCODING;
            }

            const oid_type& transfer_syntax() const {
                return encoding_to_oid(rule());
            }


        private:

            const_sequences_ptr listbuffers_;
            vect_octet_sequnce_ptr rows_vect;
            std::size_t size_;
        };



        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        class base_input_coder {
        public:

            typedef mutable_sequences::iterator iterator_type;

            static bool __input__() {
                return true;
            }

            base_input_coder() : listbuffers_(new mutable_sequences()), size_(0) {
            }

            virtual ~base_input_coder() {
            }

            const mutable_sequences& buffers() const {
                return *listbuffers_;
            }

            mutable_sequences& buffers() {
                return *listbuffers_;
            }

            void add(const octet_sequnce& vl);

            void add(const const_sequences& vl);

            void pop_front(std::size_t sz) {
                decsize(pop_frontlist(*listbuffers_, sz));
            }

            bool is_endof(std::size_t beg = 0) const;

            iterator_type last() {
                return listbuffers_->empty() ? listbuffers_->end() : (--(listbuffers_->end()));
            }

            std::size_t size(std::size_t sz) {
                return (sz < size_) ? (size_ - sz) : 0;
            }

            virtual void clear();

            std::size_t size() const {
                return size_;
            }

            bool bind(const octet_sequnce& vl);

            virtual int test_id() {
                return 0;
            };

            virtual int test_class() {
                return 0;
            };

            void resetextention() {
            }

        protected:

            void decsize(std::size_t sz) {
                size_ = size_ < sz ? 0 : (size_ - sz);
                //std::cout << "decsize IARCHVE size:"  << size_  << std::endl;
            }

        private:

            mutable_sequences_ptr listbuffers_;
            vect_octet_sequnce_ptr rows_vect;
            std::size_t size_;

        };




        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////

        class basic_coder {
        public:

            typedef boost::shared_ptr<base_input_coder> input_coder_ptr;
            typedef boost::shared_ptr<base_output_coder> output_coder_ptr;

            basic_coder(base_input_coder* in, base_output_coder* out) : input_(in), output_(out) {
            }

            virtual ~basic_coder() {
            }

            input_coder_ptr in() {
                return input_;
            }

            input_coder_ptr in() const {
                return input_;
            }

            output_coder_ptr out() {
                return output_;
            }

            output_coder_ptr out() const {
                return output_;
            }

            const const_sequences& request() const {
                return output_->buffers();
            }

            std::string request_str() const;

            void request_str(const std::string& val);

            std::string respond_str() const;

            void respond_str(const std::string& val);

            virtual void clear() {
                output_->clear();
                input_->clear();
            }

            virtual void clear_input() {
                input_->clear();
            }

            virtual void clear_output() {
                output_->clear();
            }

            virtual oid_type abstract_syntax() const {
                return oid_type();
            }

            friend bool operator<(const basic_coder& ls, const basic_coder& rs) {
                return ls<rs;
            }

            encoding_rule rule() const {
                return output_->rule();
            }

            const oid_type& transfer_syntax() const {
                return output_->transfer_syntax();
            }


        protected:

            input_coder_ptr input_;
            output_coder_ptr output_;
        };



        typedef boost::shared_ptr<basic_coder> asn_coder_ptr;

        template<typename INPUT_TYPE = base_input_coder, typename OUTPUT_TYPE = base_output_coder>
                class asn_coder_templ : public basic_coder {
        public:

            typedef INPUT_TYPE input_coder_type;
            typedef OUTPUT_TYPE output_coder_type;

            asn_coder_templ(const oid_type& asx = oid_type(), encoding_rule rul = NULL_ENCODING) :
            basic_coder(new input_coder_type(), new output_coder_type(rul)), abstract_syntax_(asx) {
            }

            input_coder_type& input() {
                return *boost::static_pointer_cast<input_coder_type, base_input_coder > (input_);
            }

            const input_coder_type& input() const {
                return *boost::static_pointer_cast<input_coder_type, base_input_coder > (input_);
            }

            output_coder_type& output() {
                return *boost::static_pointer_cast<output_coder_type, base_output_coder > (output_);
            }

            const output_coder_type& output() const {
                return *boost::static_pointer_cast<output_coder_type, base_output_coder > (output_);
            }

            virtual oid_type abstract_syntax() const {
                return abstract_syntax_;
            }


        private:

            oid_type abstract_syntax_;

        };


        /*      static inline asn_coder_ptr create_simple_data(const std::string& val) {
                   asn_coder_ptr tmp = asn_coder_ptr(new simple_trans_data());
                   tmp->request_str(val);
                   return tmp;
               }*/

        //////////////////////////////////////////////////////////////////////////////             



        std::ostream& operator<<(std::ostream& stream, const const_sequences& self);

        std::ofstream& operator<<(std::ofstream& stream, const const_sequences& self);

        std::ostream& operator<<(std::ostream& stream, const base_output_coder& vl);

        std::ofstream& operator<<(std::ofstream& stream, const base_output_coder& vl);

        std::ostream& operator<<(std::ostream& stream, const mutable_sequences& vl);

        std::ofstream& operator<<(std::ofstream& stream, const mutable_sequences& vl);



        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////            
        //   class  basic_sender_sequences 
        ///////////////////////////////////////////////////////////////////////////////////////////////////////     
        //////////////////////////////////////////////////////////////////////////////////////////////////////

        class basic_sender_sequences {
            friend class basic_itu_sequences;

        public:

            basic_sender_sequences() : bufferptr_(new const_sequences()), buffer_(*bufferptr_), size_(0) {
            }

            basic_sender_sequences(const_sequences_ptr bf) : bufferptr_(bf), buffer_(*bufferptr_), size_(0) {
            }

            basic_sender_sequences(const_sequences& bf) : buffer_(bf), size_(0) {
            }

            virtual ~basic_sender_sequences() {
            }

            const const_sequences& pop() {
                return buff();
            }

            std::size_t size(std::size_t sz = 0);

            virtual bool ready() const {
                return buff().empty();
            }

            virtual bool overflowed() const {
                return false;
            }

            virtual std::size_t constraint() const {
                return 0;
            }

        protected:

            virtual const_sequences& buff() {
                return buffer_;
            }

            virtual const_sequences& buff() const {
                return buffer_;
            }

        private:
            const_sequences_ptr bufferptr_;
            mutable const_sequences& buffer_;
            std::size_t size_;
        };


        typedef boost::shared_ptr<basic_sender_sequences> sender_sequnces_ptr;


        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////            
        //   class  basic_itu_sequences
        ///////////////////////////////////////////////////////////////////////////////////////////////////////     
        //////////////////////////////////////////////////////////////////////////////////////////////////////       

        class basic_itu_sequences : public basic_sender_sequences {
        public:

            basic_itu_sequences(asn_coder_ptr codr, std::size_t limit = 0) :
            basic_sender_sequences(codr->out()->buffers_ptr()), coder_(codr),
            limit_(limit), limited_(limit && (codr->out()->size() > limit)) {
            }

            virtual bool overflowed() const {
                return limited_;
            }

            virtual std::size_t constraint() const {
                return limited_ ? limit_ : coder_->out()->size();
            }

        protected:

            virtual const_sequences& buff() {
                return limited_ ? prepare() : buffer_;
            }

            virtual const_sequences& buff() const {
                return limited_ ? prepare() : buffer_;
            }

        private:

            const_sequences& prepare() const {
                if (limitedbuff_)
                    return *limitedbuff_;
                limitedbuff_ = const_sequences_ptr(new const_sequences());
                coder_->out()->load_sequence(*limitedbuff_, limit_);
                return *limitedbuff_;
            }

            asn_coder_ptr coder_;
            std::size_t limit_;
            bool limited_;
            mutable const_sequences_ptr limitedbuff_;
        };

        typedef boost::shared_ptr<basic_itu_sequences> basic_itu_sequences_ptr;


    }

    namespace asn1 {

        const boost::asn1::oid_type NULL_ENCODING_OID = boost::asn1::oid_type();

        const boost::asn1::oidindx_type BASIC_ENCODING_ARR[] = {2, 1, 1};
        const boost::asn1::oid_type BASIC_ENCODING_OID = boost::asn1::oid_type(BASIC_ENCODING_ARR, 3);

        const boost::asn1::oidindx_type CANONICAL_ENCODING_ARR[] = {2, 1, 2, 0};
        const boost::asn1::oid_type CANONICAL_ENCODING_OID = boost::asn1::oid_type(CANONICAL_ENCODING_ARR, 4);

        const boost::asn1::oidindx_type DISTINGUISH_ENCODING_ARR[] = {2, 1, 2, 1};
        const boost::asn1::oid_type DISTINGUISH_ENCODING_OID = boost::asn1::oid_type(DISTINGUISH_ENCODING_ARR, 4);

    }


} // namespace boost



#endif	/* RFC1006_H */

