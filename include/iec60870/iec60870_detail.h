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

            iec_option(ADDRESS_sizetype adr, COT_sizetype ct, SECTOR_sizetype sct, IOA_sizetype ioa);

            iec_option(const std::string& vl) : opton_(vl) {
            };


            ADDRESS_sizetype addr() const;

            std::size_t addr_sz() const {
                return static_cast<std::size_t> (addr());
            }

            void addr(ADDRESS_sizetype vl);

            COT_sizetype cot() const;

            std::size_t cot_sz() const {
                return static_cast<std::size_t> (cot());
            }

            void cot(COT_sizetype vl);

            SECTOR_sizetype sector() const;

            std::size_t sector_sz() const {
                return static_cast<std::size_t> (sector());
            }

            void sector(SECTOR_sizetype vl);

            IOA_sizetype ioa() const;

            std::size_t ioa_sz() const {
                return static_cast<std::size_t> (ioa());
            }

            void ioa(IOA_sizetype vl);

            std::size_t trycount() const;

            void trycount(std::size_t vl);

            std::size_t t0() const;

            void t0(std::size_t vl);

            std::size_t t1() const;

            void t1(std::size_t vl);

            std::size_t t2() const;

            void t2(std::size_t vl);

            std::size_t t3() const;

            void t3(std::size_t vl);
            
            std::size_t k() const;

            void k(std::size_t vl);

            std::size_t w() const;

            void w(std::size_t vl);            

            std::string to_value();



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

