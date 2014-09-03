/* 
 * File:   modbus_detail.h
 * Author: Serg
 *
 * Created on 19 ??????? 2010 ?., 17:55
 */

#ifndef _DVNCI_KRNL_LGK_DETAIL_H
#define	_DVNCI_KRNL_LGK_DETAIL_H


#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <kernel/error.h>

#include <driverspec/spbmg_protocol.h>
#include <driverspec/iek1177_protocol.h>


namespace dvnci {
    namespace driver {



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_req_parcel*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_req_parcel : public basis_req_parcel {

        public:

            lgk_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_req_parcel(vl, tgtp, mlnk) {
                devnum_ = (mlnk.protocol() == LGKA_PROT_MEC) ? 0xFF : mlnk.devicenum();
                iscorrect_ = parse(vl);
            }

            virtual size_t operator-(const basis_req_parcel & rs) const {
                if (kind() == LGKA_TYPEITEM_ARRAY)
                    return (rs.addr() == addr()) ? dvnci::abs<size_t > (rs.indx() - indx()) : BLOCKMAXDISTANCE;
                return BLOCKMAXDISTANCE;
            };

            bool parse(std::string vl);

        protected:

            bool conformaddr(const std::string& vl, parcelkind& tp, num32& ch, num32& nm, num32 & arrnm);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_block_model*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class lgk_block_model : public flatmemory_block_model<lgk_req_parcel> {

        public:

            typedef abstract_block_model::block block;
            typedef abstract_block_model::block_vector block_vector;
            typedef abstract_block_model::parcel_iterator parcel_iterator;

            lgk_block_model(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            flatmemory_block_model<lgk_req_parcel>(exectr, inf, mlnk) {

                protocol = (mlnk.protocol() != LGKA_PROT_MEC) ? LGKA_PROT_SP : LGKA_PROT_MEC;
                blocksize = (protocol == LGKA_PROT_MEC) ? 1 : in_bounded<size_t > (1, LGKA_MAX_BLOCKSIZE, mlnk.blocksize());
                archblocksize = (protocol == LGKA_PROT_MEC) ? 1 : in_bounded<num32 > (1, LGKA_MAX_BLOCKSIZE, mlnk.archblocksize());
            }

        protected:

            struct dev_block {

                dev_block() : smpl_fl(true), arr_fl(true), arch_fl(true), curtype_(LGKA_TYPEITEM_SMPL) {
                }

                void def_iterator() {
                    smpl_it = simpl.begin();
                    arch_it = arch.begin();
                    arr_it = arr.begin();
                }

                void add(parcelkind tp, const block & val);
                bool next(block& vl, bool& lpready);

            private:

                bool loop_is_ready() {
                    return ((smpl_fl) && (arr_fl) && (arch_fl));
                }

                bool next_templ(block& vl, bool& fl, bool& lpready, block_vector& vct, block_vector::const_iterator & it);

                parcelkind curtype(parcelkind lev = 0);

                block_vector simpl, arch, arr;
                block_vector::const_iterator smpl_it, arr_it, arch_it;
                bool smpl_fl, arr_fl, arch_fl;
                parcelkind curtype_;
            };

            typedef std::pair<devnumtype, dev_block> devnum_block_pair;
            typedef std::map< devnumtype, dev_block, std::less<devnumtype>,
            std::allocator<devnum_block_pair > > devnum_block_map;
            typedef devnum_block_map::iterator devnum_block_iterator;



            virtual void generate_impl();
            void filltransitmap(devnum_block_map& mp, const block& blk);
            void generate_by_transitmap(devnum_block_map& mp);
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_com_option_setter*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_com_option_setter : public com_option_setter {

            lgk_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {
            };

            virtual boost::system::error_code store(com_port_option& opt, boost::system::error_code & ec) const;

            virtual boost::system::error_code load(com_port_option& opt, boost::system::error_code & ec) {
                return boost::system::error_code();
            }
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_metalink_checker*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls) {
                return (((ls.protocol() == LGKA_PROT_MEC) != (rs.protocol() == LGKA_PROT_MEC)) ||
                        (ls.inf().cominf.boundrate != rs.inf().cominf.boundrate)) ?
                        ERROR_IO_NOSYNC_LINK : 0;
            }
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_protocol_factory*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_protocol_factory : public protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err);
        };

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*lgk_device_service*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class lgk_device_service : public templ_device_service<lgk_protocol_factory> {

        public:

            lgk_device_service(const metalink& lnk) : templ_device_service<lgk_protocol_factory>(lnk, UTIL_INTERVAL_DAY) {
                ;
            };
        };




    }
}



#endif	/* MODBUS_DETAIL_H */

