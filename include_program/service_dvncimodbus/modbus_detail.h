/* 
 * File:   modbus_detail.h
 * Author: Serg
 *
 * Created on 19 ??????? 2010 ?., 17:55
 */

#ifndef _DVNCI_KRNL_MODBUS_DETAIL_H
#define	_DVNCI_KRNL_MODBUS_DETAIL_H

#include <kernel/driver_proccesstmpl.h>
#include <kernel/driver_blockmodel.h>
#include <driverspec/modbus_protocol.h>

namespace dvnci {
    namespace driver {

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Modbus ?????a ??????*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        struct modbus_req_parcel : public basis_req_parcel {
        public:

            modbus_req_parcel(std::string vl, tagtype tgtp, const metalink & mlnk);

            virtual size_t operator-(const basis_req_parcel & rs) const;

            bool parse(std::string vl);

            bool conformaddr(const std::string& vl, std::string rgxstr, num32& addr, size_t& bitnum, num32 maxadr, num32 minadr = 1);

            bool checktagtype() {
                if ((IN_REPORTSET(tgtype_)) || (IN_EVENTSET(tgtype_))) {
                    error(ERROR_TYPENOPROCCESS);
                    return false;}
                return true;}} ;


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Modbus ????????? ????? ??????*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



        class modbus_block_generator : public base_block_generator<modbus_req_parcel> {
        public:

            modbus_block_generator(executor* exectr, tagsbase_ptr inf, const metalink& mlnk) :
            base_block_generator<modbus_req_parcel>(exectr, inf, mlnk) {
                blocksize = ((mlnk.protocol() == NT_MODBUS_ASCII) && (mlnk.chanaltype() != NT_CHTP_TCP_IP)) ?
                        in_bounded<size_t > (8, MAX_MODBUS_BLOCK_SIZE / 2, static_cast<size_t> (mlnk.blocksize())) :
                        in_bounded<size_t > (8, MAX_MODBUS_BLOCK_SIZE, static_cast<size_t> (mlnk.blocksize()));};} ;



      /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*?????????? ???????? Com ????? modbus*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct modbus_com_option_setter : public com_option_setter {

            modbus_com_option_setter(const metalink & lnk) : com_option_setter(lnk) {};

            virtual boost::system::error_code store(com_port_option&  opt, boost::system::error_code & ec) const {
                reset_default_nill(opt);
                //opt.fRtsControl = 0;
		switch (link.protocol()){
		    case NT_MODBUS_ASCII: {
			set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ?  NT_RS_NOPARITY : link.inf().cominf.parity;
                        set_rs232_comoption(opt,7, tmprty,
                                      (tmprty  == NT_RS_NOPARITY) ? NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);
			break;}
		    default :{
                        set_rs232_baudrate(opt, link.inf().cominf.boundrate);
                        rsparitytype tmprty = (link.inf().cominf.parity > NT_RS_EVENPARITY) ?  NT_RS_NOPARITY : link.inf().cominf.parity;
                        set_rs232_comoption(opt,8, tmprty, 
                                      (tmprty  == NT_RS_NOPARITY) ? NT_RS_TWOSTOPBITS : NT_RS_ONESTOPBIT);}}
			return boost::system::error_code();}

            virtual boost::system::error_code load(com_port_option&  opt, boost::system::error_code & ec) {
                return boost::system::error_code();}};


       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*????????????? ??????? ?????????? Modbus*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

     struct modbus_metalink_checker : public metalink_checker {

            virtual ns_error compare(const metalink& rs, const metalink& ls){
                return ((ls.inf().cominf.boundrate!=rs.inf().cominf.boundrate)) ?  ERROR_IO_NOSYNC_LINK : 0;}};

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*????????? ??????????  Modbus*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


     struct modbus_protocol_factory : public protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err) {

                typedef rs_iostream<modbus_com_option_setter> modbus_rs_iostream;

                switch(lnk.chanaltype()){
                    case NT_CHTP_TCP_IP: {
                        
                        basis_iostream_ptr tmp_stream = basis_iostream_ptr( new tcpip_iostream( lnk.timeout(), lnk.host(), MODBUS_TCP_PORT));
                        
                        return ioprotocol_ptr( new tcp_modbus_protocol<modbus_value_manager>(tmp_stream));}

                    case NT_CHTP_RS232_4XX:{
                        
                        basis_iostream_ptr tmp_stream = basis_iostream_ptr(new modbus_rs_iostream(lnk,  lnk.timeout(), lnk.chanalnum(), false));

                        switch (lnk.protocol()){

                            case NT_MODBUS_ASCII: { return ioprotocol_ptr(new ascii_modbus_protocol<modbus_value_manager>(tmp_stream));}
                            default : {return ioprotocol_ptr(new rtu_modbus_protocol<modbus_value_manager>(tmp_stream));}}}

                    default: {
                        err = ERROR_IO_LINK_NOT_SUPPORT;
                        return ioprotocol_ptr();}}


                err = ERROR_IO_LINK_NOT_SUPPORT;
                return ioprotocol_ptr();};};

       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
       /*???????? ?????????  Modbus*/
       /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        class modbus_device_service : public templ_device_service<modbus_protocol_factory> {
        public:
            modbus_device_service(const metalink& lnk) : 
            templ_device_service<modbus_protocol_factory>(lnk) {};};



}}



#endif	/* MODBUS_DETAIL_H */

