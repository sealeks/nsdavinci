/* 
 * File:   iec60870_detail.h
 * Author: Alexeev
 */

#ifndef _DVNCI_KRNL_IEC60870_DETAIL_H
#define	_DVNCI_KRNL_IEC60870_DETAIL_H

#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>

namespace dvnci {
    namespace prot80670 {

        enum IEC_PROTOCOL {

            IEC_101 = 1,
            IEC_102 = 2,
            IEC_103 = 3,
            IEC_104 = 4,
        };

         inline IEC_PROTOCOL protocol_from(protocoltype vl) {
            return (!vl || (vl > 4)) ? IEC_101 : static_cast<IEC_PROTOCOL> (vl);
        }

        inline protocoltype protocol_to(IEC_PROTOCOL vl) {
            return static_cast<protocoltype> (vl);
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

            iec_option(const std::string& vl) : opton_(vl) {
            };

            iec_option(ADDRESS_sizetype adr, COT_sizetype ct, SECTOR_sizetype sct, IOA_sizetype ioa) : opton_("\x0") {
                opton_[0] |= adr;
                opton_[0] |= ((ct - 1) << 2);
                opton_[0] |= ((sct - 1) << 3);
                opton_[0] |= ((ioa - 1) << 4);
            }

            ADDRESS_sizetype addr() const {
                if (opton_.empty() || ((opton_[0]&3) == 3))
                    return lasz_none;
                return static_cast<ADDRESS_sizetype> (opton_[0]&3);
            }

            void addr(ADDRESS_sizetype vl) {
                if (opton_.empty())
                    opton_ = "\x0";
                opton_[0] |= static_cast<std::string::value_type> (vl);
            }

            COT_sizetype cot() const {
                if (opton_.empty())
                    return ctsz_one;
                return static_cast<COT_sizetype> ((((opton_[0]&4) >> 2) & 1) + 1);
            }

            void cot(COT_sizetype vl) {
                if (opton_.empty())
                    opton_ = "\x0";
                opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 2);
            }

            SECTOR_sizetype sector() const {
                if (opton_.empty())
                    return select_one;
                return static_cast<SECTOR_sizetype> ((((opton_[0]&8) >> 3) & 1) + 1);
            }

            void sector(SECTOR_sizetype vl) {
                if (opton_.empty())
                    opton_ = "\x0";
                opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 3);
            }

            IOA_sizetype ioa() const {
                if (opton_.empty())
                    return ioa_one;
                std::string::value_type tmp = (((opton_[0]&8) >> 4) & 1) + 1;
                if (tmp > 3)
                    tmp = 3;
                return static_cast<IOA_sizetype> (tmp);
            }

            void ioa(IOA_sizetype vl) {
                if (opton_.empty())
                    opton_ = "\x0";
                opton_[0] |= ((static_cast<std::string::value_type> (vl) - 1) << 4);
            }

            std::size_t trycount() const {
                return get<1, 3, 20, 3>();
            }

            void trycount(std::size_t vl) {
                return set<1, 3, 20>(vl);
            }

            std::size_t t0() const {
                return get<2, 1, 127, 30>();
            }

            void t0(std::size_t vl) {
                return set<2, 1, 127>(vl);
            }

            std::size_t t1() const {
                return get<3, 3, 127, 10>();
            }

            void t1(std::size_t vl) {
                return set<3, 3, 127>(vl);
            }

            std::size_t t2() const {
                return get<4, 1, 127, 15>();
            }

            void t2(std::size_t vl) {
                return set<4, 1, 127>(vl);
            }

            std::size_t t3() const {
                return get<5, 1, 127, 20>();
            }

            void t3(std::size_t vl) {
                return set<5, 1, 127>(vl);
            }

            std::size_t k() const {
                return get<6, 1, 127, 12>();
            }

            void k(std::size_t vl) {
                return set<6, 1, 127>(vl);
            }

            std::size_t w() const {
                return get<7, 1, 127, 8>();
            }

            void w(std::size_t vl) {
                return set<7, 1, 127>(vl);
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
                return opton_;
            }


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
                    opton_ = std::string('\x0', POS + 1);
                if (opton_.size() <= POS)
                    opton_ += std::string('\x0', POS - opton_.size() + 1);
                opton_[POS] = static_cast<std::string::value_type> (vl < MIN ? MIN : (vl > MAX ? MAX : vl));
            }

            std::string opton_;

        };









        using dvnci::driver::com_option_setter;
        using dvnci::driver::com_port_option;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*com_option_setter*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct iec60870_com_option_setter : public com_option_setter {

            iec60870_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {
            };

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*iec60870_metalink_checker*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct iec60870_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls) {
                return ((ls.inf().cominf.boundrate != rs.inf().cominf.boundrate)) ? ERROR_IO_NOSYNC_LINK : 0;
            }
        };





    }
}



#endif	/* MODBUS_DETAIL_H */

