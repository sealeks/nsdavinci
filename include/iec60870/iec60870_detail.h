/* 
 * File:   iec60870_detail.h
 * Author: Alexeev
 */

#ifndef _DVNCI_KRNL_IEC60870_DETAIL_H
#define	_DVNCI_KRNL_IEC60870_DETAIL_H

#include <deque>
#include <set>

#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/error.h>
#include <kernel/constdef.h>
#include <kernel/short_value.h>
#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>

#include <boost/asio/serial_port.hpp>
#include <boost/asio/read_at.hpp>


namespace dvnci {
    namespace prot80670 {



        typedef boost::int32_t baudrate_type;
        typedef boost::int32_t rsparity_type;
        typedef boost::int32_t rsdatabit_type;
        typedef boost::int32_t rsstopbit_type;
        typedef boost::int32_t protocol_type;
        typedef std::size_t timeout_type;
        typedef std::size_t chanalnum_type;

        const baudrate_type IEC870_BAUNDRATE_110 = 110;
        const baudrate_type IEC870_BAUNDRATE_300 = 300;
        const baudrate_type IEC870_BAUNDRATE_600 = 600;
        const baudrate_type IEC870_BAUNDRATE_1200 = 1200;
        const baudrate_type IEC870_BAUNDRATE_2400 = 2400;
        const baudrate_type IEC870_BAUNDRATE_4800 = 4800;
        const baudrate_type IEC870_BAUNDRATE_9600 = 9600;
        const baudrate_type IEC870_BAUNDRATE_14400 = 14400;
        const baudrate_type IEC870_BAUNDRATE_19200 = 19200;
        const baudrate_type IEC870_BAUNDRATE_38400 = 38400;
        const baudrate_type IEC870_BAUNDRATE_56000 = 56000;
        const baudrate_type IEC870_BAUNDRATE_57600 = 57600;
        const baudrate_type IEC870_BAUNDRATE_115200 = 115200;
        const baudrate_type IEC870_BAUNDRATE_128000 = 128000;
        const baudrate_type IEC870_BAUNDRATE_256000 = 256000;

        const rsparity_type IEC870_NOPARITY = 0;
        const rsparity_type IEC870_ODDPARITY = 1;
        const rsparity_type IEC870_EVENPARITY = 2;
        const rsparity_type IEC870_MARKPARITY = 3;
        const rsparity_type IEC870_SPACEPARITY = 4;

        const rsstopbit_type IEC870_ONESTOPBIT = 0;
        const rsstopbit_type IEC870_ONE5STOPBITS = 1;
        const rsstopbit_type IEC870_TWOSTOPBITS = 2;

#if defined(_DVN_WIN_)        
        typedef ::DCB com_port_option_type;
#elif defined(_DVN_LIN_)
        typedef ::termios com_port_option_type;
#endif           

        void set_com_cominill(com_port_option_type& opt);
        void set_com_baudrate(com_port_option_type& opt, const baudrate_type& br);
        void set_com_comoption(com_port_option_type& opt, size_t databit, const rsparity_type& prt, const rsstopbit_type& stpbt);
        void set_com_flowcontrol(com_port_option_type& opt, bool vl);

        enum IEC_PROTOCOL {

            IEC_NULL = 0,
            IEC_101 = 1,
            IEC_102 = 2,
            IEC_103 = 3,
            IEC_104 = 4,
        };

        inline IEC_PROTOCOL protocol_from(protocol_type vl) {
            return (vl > 4) ? IEC_NULL : static_cast<IEC_PROTOCOL> (vl);
        }

        inline protocol_type protocol_to(IEC_PROTOCOL vl) {
            return static_cast<protocol_type> (vl);
        }

        enum ADDRESS_sizetype {

            lasz_none = 0,
            lasz_one = 1,
            lasz_double = 2,
        };

        enum COT_sizetype {

            ctsz_one = 1,
            ctsz_double = 2,
        };

        enum SECTOR_sizetype {

            select_one = 1,
            select_double = 2,
        };

        enum IOA_sizetype {

            ioa_one = 1,
            ioa_double = 2,
            ioa_three = 3,
        };

        class iec_option {

        public:

            iec_option() : baundrate_(0) {
            };

            iec_option(const std::string& vl) : opton_(vl), baundrate_(0) {
            };

            iec_option(ADDRESS_sizetype adr, COT_sizetype ct, SECTOR_sizetype sct, IOA_sizetype ioa) : opton_("\x0") {
                opton_[0] |= adr;
                opton_[0] |= ((ct - 1) << 2);
                opton_[0] |= ((sct - 1) << 3);
                opton_[0] |= ((ioa - 1) << 4);
            }

            ADDRESS_sizetype addr() const {
                if (opton_.empty())
                    return lasz_none;
                if ((opton_[0]&3) == 3)
                    opton_[0] &= (~1);
                return static_cast<ADDRESS_sizetype> (opton_[0]&3);
            }

            void addr(ADDRESS_sizetype vl) {
                if (opton_.empty())
                    opton_ = std::string(1, '\x0');
                opton_[0] = opton_[0] & (~0x3);
                opton_[0] = opton_[0] | static_cast<std::string::value_type> (vl);


            }

            COT_sizetype cot() const {
                if (opton_.empty())
                    return ctsz_one;
                return static_cast<COT_sizetype> ((((opton_[0]&4) >> 2) & 1) + 1);
            }

            void cot(COT_sizetype vl) {
                if (opton_.empty())
                    opton_ = std::string(1, '\x0');
                opton_[0] = opton_[0] & (~0x4);
                opton_[0] = opton_[0] | ((static_cast<std::string::value_type> (vl) - 1) << 2);
            }

            SECTOR_sizetype sector() const {
                if (opton_.empty())
                    return select_one;
                return static_cast<SECTOR_sizetype> ((((opton_[0]&8) >> 3)) + 1);
            }

            void sector(SECTOR_sizetype vl) {
                if (opton_.empty())
                    opton_ = std::string(1, '\x0');
                opton_[0] = opton_[0] & (~0x8);
                opton_[0] = opton_[0] | ((static_cast<std::string::value_type> (vl) - 1) << 3);
            }

            IOA_sizetype ioa() const {
                if (opton_.empty())
                    return ioa_one;
                std::string::value_type tmp = (((opton_[0]&0x30) >> 4) & 3) + 1;
                if (tmp > 3)
                    tmp = 3;
                return static_cast<IOA_sizetype> (tmp);
            }

            void ioa(IOA_sizetype vl) {
                if (opton_.empty())
                    opton_ = std::string(1, '\x0');
                opton_[0] = opton_[0] & (~0x30);
                opton_[0] = opton_[0] | ((static_cast<std::string::value_type> (vl) - 1) << 4);
            }

            std::size_t trycount() const {
                return get<1, 3, 20, 3>();
            }

            void trycount(std::size_t vl) {
                return set<1, 3, 20>(vl);
            }

            std::size_t t0() const {
                std::size_t rslt = get<2, 1, 127, 30>();
                return (rslt > 2) ? rslt : 2;
            }

            void t0(std::size_t vl) {
                return set<2, 1, 127>(vl);
            }

            std::size_t t1() const {
                std::size_t rslt = get<3, 3, 127, 10>();
                return (rslt > t0()) ? (t0() - 1) : rslt;
            }

            void t1(std::size_t vl) {
                return set<3, 3, 127>(vl);
            }

            std::size_t t2() const {
                std::size_t rslt = get<4, 1, 127, 15>();
                return (rslt > t0()) ? (t0() - 1) : rslt;
            }

            void t2(std::size_t vl) {
                return set<4, 1, 127>(vl);
            }

            std::size_t t3() const {
                std::size_t rslt = get<5, 1, 127, 20>();
                return (rslt > 5) ? rslt : 5;
            }

            void t3(std::size_t vl) {
                return set<5, 1, 127>(vl);
            }

            std::size_t k() const {
                std::size_t rslt = get<6, 1, 127, 12>();
                return (!rslt) ? 1 : rslt;
            }

            void k(std::size_t vl) {
                return set<6, 1, 127>(vl);
            }

            std::size_t w() const {
                std::size_t rslt = get<7, 1, 127, 8>();
                return (rslt > k()) ? k() : rslt;
            }

            void w(std::size_t vl) {
                return set<7, 1, 127>(vl);
            }

            std::size_t pdu_len() const {
                std::size_t rslt = get<8, 20, 255, 255>();
                return rslt;
            }

            void pdu_len(std::size_t vl) {
                return set<8, 20, 255>(vl);
            }

            std::size_t tymesync() const {
                std::size_t rslt = get2<9, 10, 3600, 3600>();
                return rslt;
            }

            void tymesync(std::size_t vl) {
                return set2<9, 10, 3600>(vl);
            }

            bool sync() const {
                std::size_t rslt = get<11, 0, 1, 0>();
                return rslt;
            }

            void sync(bool vl) {
                return set<11, 0, 1>(vl ? 1 : 0);
            }

            std::size_t read_tmo() const {
                std::size_t rslt = get2<12, 10, 65000, 1000>();
                return rslt;
            }

            void read_tmo(std::size_t vl) {
                return set2<12, 10, 65000>(vl);
            }

            std::size_t poll_tmo() const {
                std::size_t rslt = get2<14, 10, 65000, 1000>();
                return rslt;
            }

            void poll_tmo(std::size_t vl) {
                return set2<14, 10, 65000>(vl);
            }

            std::size_t R_tmo() const {
                std::size_t rslt = get2<16, 10, 65000, 1000>();
                return rslt;
            }

            void R_tmo(std::size_t vl) {
                return set2<16, 10, 65000>(vl);
            }

            bool init() const {
                std::size_t rslt = get<18, 0, 1, 0>();
                return rslt;
            }

            void init(bool vl) {
                return set<18, 0, 1>(vl ? 1 : 0);
            }

            bool poll() const {
                std::size_t rslt = get<19, 0, 1, 0>();
                return rslt;
            }

            void poll(bool vl) {
                return set<19, 0, 1>(vl ? 1 : 0);
            }

            std::string to_value() {
                addr(addr());
                cot(cot());
                sector(sector());
                ioa(ioa());
                trycount(trycount());
                t0(t0());
                t1(t1());
                t2(t2());
                t3(t3());
                k(k());
                w(w());
                pdu_len(pdu_len());
                tymesync(tymesync());
                sync(sync());
                read_tmo(read_tmo());
                poll_tmo(poll_tmo());
                R_tmo(R_tmo());
                init(init());
                poll(poll());
                return opton_;
            }

            baudrate_type baundrate() const {
                return baundrate_;
            };

            void baundrate(baudrate_type vl) {
                baundrate_ = vl;
            };

        private:

            template<std::size_t POS, std::size_t MIN, std::size_t MAX, std::size_t DFLT>
            std::size_t get() const {
                if (opton_.size() <= POS)
                    return DFLT;
                std::size_t tmp = *reinterpret_cast<const boost::uint8_t*> (&opton_[POS]);
                return (tmp < MIN) ? DFLT : ((tmp > MAX) ? MAX : tmp);
            }

            template<std::size_t POS, std::size_t MIN, std::size_t MAX>
            void set(std::size_t vl) {
                if (opton_.empty())
                    opton_ = std::string(POS + 1, '\x0');
                if (opton_.size() <= POS)
                    opton_ += std::string(POS - opton_.size() + 1, '\x0');
                opton_[POS] = static_cast<std::string::value_type> (vl < MIN ? MIN : (vl > MAX ? MAX : vl));
            }

            template<std::size_t POS, std::size_t MIN, std::size_t MAX, std::size_t DFLT>
            std::size_t get2() const {
                if (opton_.size() <= (POS + 1))
                    return DFLT;
                std::size_t tmp = *reinterpret_cast<const boost::uint16_t*> (&opton_[POS]);
                return (tmp < MIN) ? DFLT : ((tmp > MAX) ? MAX : tmp);
            }

            template<std::size_t POS, std::size_t MIN, std::size_t MAX>
            void set2(std::size_t vl) {
                if (opton_.empty())
                    opton_ = std::string(POS + 2, '\x0');
                if (opton_.size() <= (POS + 1))
                    opton_ += std::string(POS - opton_.size() + 2, '\x0');
                std::size_t vln = vl < MIN ? MIN : (vl > MAX ? MAX : vl);
                opton_[POS] = static_cast<boost::uint8_t> (vln & 0xFF);
                opton_[POS + 1] = static_cast<boost::uint8_t> ((vln >> 8) & 0xFF);
            }

            mutable std::string opton_;
            baudrate_type baundrate_;

        };






        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*com_option_type_setter*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct iec60870_com_option_setter {

            iec60870_com_option_setter(const iec_option & opt) : option_(opt) {
            };

            virtual ~iec60870_com_option_setter() {
            };

            virtual boost::system::error_code store(com_port_option_type& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option_type& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }

            virtual baudrate_type boundrate() const {
                return option_.baundrate();
            }

            void reset_default_nill(com_port_option_type & opt) const {
                set_com_cominill(opt);
            }

        protected:
            iec_option option_;
        };







    }
}



#endif	/* MODBUS_DETAIL_H */

