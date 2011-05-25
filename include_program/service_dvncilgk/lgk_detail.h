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
#include <kernel/driver_blockgenerator.h>
#include <kernel/error.h>

#include "mg_protocol.h"
#include "iek1177_protocol.h"


namespace dvnci {
    namespace driver {



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*?????? ?????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_block_item : public basis_block_item {
        public:

            lgk_block_item(std::string vl, tagtype tgtp, const metalink & mlnk) : basis_block_item(vl, tgtp, mlnk) {
                devnum_ = (mlnk.protocol() == LGKA_PROT_MEC) ? 0xFF : mlnk.devicenum();
                iscorrect_ = checktagtype();
                if (!iscorrect_) return;
                iscorrect_ = parse(vl);}

            virtual size_t operator-(const basis_block_item & rs) const  {
                if (type() == LGKA_TYPEITEM_ARRAY)
                    return (rs.addr() == addr()) ? dvnci::abs<size_t > (rs.tp() - tp()) : MAXDISTANSE;
                return MAXDISTANSE;};

            bool parse(std::string vl);

            bool conformaddr(const std::string& vl, num32& tp, num32& ch, num32& nm, num32 & arrnm);

            virtual void set_simpl_val_from_str(std::string val) {
                val = strcomma_to_dot(val);
                basis_block_item::set_simpl_val_from_str(val);}

            virtual std::string val_as_str() {
                return strdot_to_comma(basis_block_item::val_as_str());}

            bool checktagtype() {
                if (IN_EVENTSET(tgtype_)) {
                    error_ = ERROR_TYPENOPROCCESS;
                    return false;}
                return true;}} ;

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*????????? ????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class lgk_block_generator : public base_block_generator<lgk_block_item> {
        public:

            typedef abstract_block_generator::block                            block;
            typedef abstract_block_generator::block_vector                     block_vector;
            typedef abstract_block_generator::parcel_iterator                  parcel_iterator;

            lgk_block_generator(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            base_block_generator<lgk_block_item>(exectr, inf, mlnk) {
                protocol = (mlnk.protocol() != LGKA_PROT_MEC) ? LGKA_PROT_SP : LGKA_PROT_MEC;
                blocksize = (protocol == LGKA_PROT_MEC) ? 1 : in_bounded<size_t > (1, 30, mlnk.blocksize());
                archblocksize  = (protocol == LGKA_PROT_MEC) ? 1 : in_bounded<num32 > (1, 30, mlnk.archblocksize());}

        protected:

            struct dev_block {

                dev_block() : smpl_fl(true), arr_fl(true), arch_fl(true), curtype_(LGKA_TYPEITEM_SMPL) {}

                void def_iterator() {
                    smpl_it = simpl.begin() ;
                    arch_it = arch.begin();
                    arr_it = arr.begin();}
                void add(num32 tp, const block & val);
                bool next(block& vl, bool& lpready);

            private:

                bool loop_is_ready() {
                    return ((smpl_fl) && (arr_fl) && (arch_fl));}
                bool next_templ(block& vl, bool& fl, bool& lpready, block_vector& vct, block_vector::const_iterator & it);
                num32   curtype(num32 lev = 0);

                block_vector                  simpl, arch, arr;
                block_vector::const_iterator  smpl_it, arr_it, arch_it;
                bool                          smpl_fl, arr_fl, arch_fl;
                num32                         curtype_;} ;

            typedef std::pair<num32 , dev_block>                                    num32_dev_block_pair;
            typedef std::map< num32, dev_block , std::less<num32>,
            std::allocator<num32_dev_block_pair > >                                 num32_dev_block_map;
            typedef num32_dev_block_map::iterator                                   num32_dev_block_iterator;



            virtual void generate_impl();
            void filltransitmap(num32_dev_block_map& mp, const block& blk);
            void generate_by_transitmap(num32_dev_block_map& mp);};


       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*?????????? ???????? Com ????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct lgk_com_option_setter : public com_option_setter {

            lgk_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {};

            virtual boost::system::error_code store(com_port_option&  opt, boost::system::error_code & ec) const {
                reset_default_nill(opt);
                //opt.fRtsControl = 0;
                switch (link.protocol()) {
                    case LGKA_PROT_MEC:{
                        set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        set_rs232_comoption( 7,  NT_RS_EVENPARITY, NT_RS_ONESTOPBIT);
			break;}
                    default:{
                        set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        set_rs232_comoption( 8, NT_RS_NOPARITY, NT_RS_ONESTOPBIT);}}
                return boost::system::error_code ();}

            virtual boost::system::error_code load(com_port_option&  opt, boost::system::error_code & ec) {
                return boost::system::error_code();}} ;


       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*????????????? ??????? ?????????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     struct lgk_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls){
                return (((ls.protocol()==LGKA_PROT_MEC)!=(rs.protocol()==LGKA_PROT_MEC)) ||
                        (ls.inf().cominf.boundrate!=rs.inf().cominf.boundrate))?  ERROR_IO_NOSYNC_LINK : 0;}};

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*????????? ?????????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        struct lgk_protocol_factory : public protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err) {

                typedef rs_iostream<lgk_com_option_setter> lgk_rs_iostream;

                if (lnk.chanaltype() != NT_CHTP_RS232_4XX){
                    err = ERROR_IO_LINK_NOT_SUPPORT;
                    ioprotocol_ptr();}

                basis_iostream_ptr tmp_stream = basis_iostream_ptr(new lgk_rs_iostream(lnk,
                        0, lnk.timeout(), lnk.chanalnum(), false));

                switch (lnk.protocol()){
                    case LGKA_PROT_MEC: { return ioprotocol_ptr(new iek1177_protocol(tmp_stream));}
                    default : {return ioprotocol_ptr(new mg_protocol(tmp_stream));}}

                err = ERROR_IO_LINK_NOT_SUPPORT;
                return ioprotocol_ptr();}};

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*???????? ????????? LGK*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class lgk_device_service : public templ_device_service<lgk_protocol_factory> {
        public:

            lgk_device_service(const metalink& lnk) : templ_device_service<lgk_protocol_factory>(lnk, UTIL_INTERVAL_DAY) {
                /*protocol_ = ((protocol_ != LGKA_PROT_MEC)) ? LGKA_PROT_SP :  protocol_*/;};};




}}



#endif	/* MODBUS_DETAIL_H */

