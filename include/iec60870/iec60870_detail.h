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

        enum IEC_PROTOCOL {

            IEC_NULL = 0,
            IEC_101 = 1,
            IEC_102 = 2,
            IEC_103 = 3,
            IEC_104 = 4,
        };

        inline IEC_PROTOCOL protocol_from(protocoltype vl) {
            return (vl > 4) ? IEC_NULL : static_cast<IEC_PROTOCOL> (vl);
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
            
            iec_option() {
            };            

            iec_option(const std::string& vl) : opton_(vl) {
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
                return (rslt>2) ? rslt : 2;
            }

            void t0(std::size_t vl) {
                return set<2, 1, 127>(vl);
            }

            std::size_t t1() const {
                std::size_t rslt = get<3, 3, 127, 10>();                
                return (rslt >t0()) ? (t0()-1) : rslt;
            }

            void t1(std::size_t vl) {
                return set<3, 3, 127>(vl);
            }

            std::size_t t2() const {
                std::size_t rslt = get<4, 1, 127, 15>();                
                return (rslt >t0()) ? (t0()-1) : rslt;
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
                return (rslt>k()) ? k() : rslt;
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
                std::size_t rslt = get2<9, 10, 3600,3600>();                
                return rslt;
            }

            void tymesync(std::size_t vl) {
                return set2<9, 10, 3600>(vl);
            }     
            
            bool sync() const {
                std::size_t rslt = get<11, 0, 1 ,0>();                
                return rslt;
            }

            void sync(bool vl) {
                return set<11, 0, 1>(vl ? 1 : 0);
            }         
            
            std::size_t read_tmo() const {
                std::size_t rslt = get2<12, 10, 65000,1000>();                
                return rslt;
            }

            void read_tmo(std::size_t vl) {
                return set2<12, 10, 65000>(vl);
            }       
            
            std::size_t poll_tmo() const {
                std::size_t rslt = get2<14, 10, 65000,1000>();                
                return rslt;
            }

            void poll_tmo(std::size_t vl) {
                return set2<14, 10, 65000>(vl);
            }          
            
            std::size_t R_tmo() const {
                std::size_t rslt = get2<16, 10, 65000,1000>();                
                return rslt;
            }

            void R_tmo(std::size_t vl) {
                return set2<16, 10, 65000>(vl);
            }                   
            
            bool init() const {
                std::size_t rslt = get<18, 0, 1 ,0>();                
                return rslt;
            }

            void init(bool vl) {
                return set<18, 0, 1>(vl ? 1 : 0);
            }              
            
            bool poll() const {
                std::size_t rslt = get<19, 0, 1 ,0>();                
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
                if (opton_.size() <= (POS+1))
                    return DFLT;
                std::size_t tmp = *reinterpret_cast<const boost::uint16_t*> (&opton_[POS]);
                return (tmp < MIN) ? DFLT : ((tmp > MAX) ? MAX : tmp);
            }

            template<std::size_t POS, std::size_t MIN, std::size_t MAX>
            void set2(std::size_t vl) {
                if (opton_.empty())
                    opton_ = std::string(POS + 2, '\x0');
                if (opton_.size() <= (POS+1))
                    opton_ += std::string(POS - opton_.size() + 2, '\x0');
                std::size_t vln=vl < MIN ? MIN : (vl > MAX ? MAX : vl);
                opton_[POS] = static_cast<boost::uint8_t> (vln & 0xFF);
                opton_[POS+1] = static_cast<boost::uint8_t> ((vln >> 8) & 0xFF);
            }            

            mutable std::string opton_;

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

