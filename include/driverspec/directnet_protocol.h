/* 
 * File:   modbus_protocol.h
 * Author: Serg
 *
 * Created on 18 ?????? 2010 ?., 17:22
 */

#ifndef DIRECTNET_PROTOCOL_H
#define	DIRECTNET_PROTOCOL_H

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/driver_detail.h>
#include <kernel/basis_iostream.h>



namespace dvnci {
    namespace driver {


        const blksizetype MAX_KOYO_BLOCK_SIZE = 246;

        bool insert_hex_koyo_lrc(std::string& src);

        bool insert_ascii_koyo_lrc(std::string& src);

        bool check_hex_koyo_lrc(std::string& src);

        bool check_ascii_koyo_lrc(std::string& src);

        bool calculate_koyo_lrc(const std::string& src, num8& lrc, std::string::size_type strt);
        
        

        const std::string DIRECTNET_NREQ = "N";

        const std::string KSEQUENCE_NREQ = "K";

        const std::string DIRECTNET_FC_READ = "\x30";

        const std::string DIRECTNET_FC_WRITE = "\x38";

        const std::string KSEQUENCE_FC_SETBIT = "\x44";

        const std::string KSEQUENCE_FC_RESETBIT = "\x45";

        const std::string DIRECTNET_V_DTTP = "\x31";

        const std::string DIRECTNET_I_DTTP = "\x32";

        const std::string DIRECTNET_O_DTTP = "\x33";

        const timeouttype DIRECTNET_TIMEOUT1 = 800;

        const timeouttype DIRECTNET_TIMEOUT2 = 2000;


        // ECOM spec

        const blksizetype MAX_ECOM_BLOCK_SIZE = 128;

        const std::string ECOM_UDP_PORT = "28784";

        const std::string ECOM_ENV = "HAP";

        const std::string ECOM_CCM_RESP = "\x19";

        const std::string ECOM_KSEQ_RESP = "\x1A";

        const std::string ECOM_CCM_FC_READ = "\x1E";

        const std::string ECOM_CCM_FC_WRITE = "\x20";

        const std::string ECOM_V_DTTP = "\x31";

        const std::string ECOM_ACK = "\x20";

        const std::string ECOM_CCM_RD_REQ = "\x22";

        const size_t ECOM_BUFF_SIZE = 3072;



        bool calculate_ecom_crc(const std::string& src, unum16& crc, std::string::size_type strt);


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*directnet_value_manager*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class directnet_value_manager : public flatmemory_value_manager {
        public:

            directnet_value_manager() : flatmemory_value_manager() {}

        protected:

            virtual size_t getbitnum(parcel_const_iterator strt, parcel_const_iterator stp) {
                if (stp->first->indx() >= 0) {
                    return static_cast<size_t> (stp->first->indx());};
                return NULL_BIT_NUM;}


            virtual ns_error parse_response_impl(std::string& val, parcel_ptr prcl, size_t bitn = NULL_BIT_NUM);

            virtual ns_error preapare_cmd_request_impl(std::string& val, parcel_ptr cmd, size_t bitn = NULL_BIT_NUM);};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*basis_koyo_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class basis_koyo_protocol : public templ_protocol<directnet_value_manager> {
        public:

            typedef unum8 koyodevn;

            static const koyodevn MAX_KOYO_DEV_NUM = 90;
            static const koyodevn NO_KOYO_DEV_NUM = 0xFF;

            basis_koyo_protocol(basis_iostream_ptr io) : templ_protocol<directnet_value_manager>(io) {}


        protected:
            
            
            virtual ns_error readblock(block& blk);

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd);

            virtual size_t ex_koef() {
                return 1;}

            unum8 byte_from_str(const std::string& vl, std::string::size_type n);

            num32 kseq_addr(num32 vl);

            ns_error set_mask(std::string& vl, size_t bitnum, bool on = true);

            virtual ns_error read_impl(const block& blk, koyodevn dvnum);

            virtual ns_error write_impl(parcel_ptr cmd, const std::string& vl, koyodevn dvnum);

            virtual ns_error generate_body_impl(std::string& vl);

            ns_error generate_body_kseq_write(std::string& vl, num32 startaddr, bool on = true);

            virtual ns_error read_request(koyodevn dvnum, num32 startaddr, size_t cnt, std::string& resp) = 0;

            virtual ns_error write_request(const std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt) = 0;

            virtual ns_error kseq_write_request(koyodevn dvnum, num32 startaddr, bool on) = 0;

            virtual ns_error check_envelope(std::string& resp, size_t cnt);};

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*hex_direcnet_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class hex_direcnet_protocol : public basis_koyo_protocol {
        public:

            hex_direcnet_protocol(basis_iostream_ptr io) : basis_koyo_protocol(io) {}

        protected:

            virtual ns_error enq_impl(koyodevn dvnum, const std::string protstrt = DIRECTNET_NREQ);

            virtual ns_error read_eot_impl();

            ns_error eot_impl() {
                error(ios->write(EOT));
                return error();}

            virtual ns_error read_request(koyodevn dvnum, num32 startaddr, size_t cnt, std::string& resp);

            virtual ns_error write_request(const std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt);

            virtual ns_error kseq_write_request(koyodevn dvnum, num32 startaddr, bool on = true);


            virtual ns_error directnet_read_request(std::string& req, std::string& resp, size_t cnt);

            virtual ns_error directnet_write_request(std::string& req, const std::string& wstr);

            ns_error directnet_generate_body_read(std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt);

            ns_error directnet_generate_body_write(std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt);};


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*ascii_direcnet_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class ascii_direcnet_protocol : public hex_direcnet_protocol {
        public:

            ascii_direcnet_protocol(basis_iostream_ptr io) : hex_direcnet_protocol(io) {}

        protected:

            virtual size_t ex_koef() {
                return 2;}

            virtual ns_error enq_impl(koyodevn dvnum, const std::string protstrt = DIRECTNET_NREQ);

            virtual ns_error read_eot_impl();

            virtual ns_error directnet_read_request(std::string& req, std::string& resp, size_t cnt);

            virtual ns_error directnet_write_request(std::string& req, const std::string& wstr);

            virtual ns_error generate_body_impl(std::string& vl) {
                if (vl.size() < 2)
                    return error(ERROR_IO_NO_GENERATE_REQ);
                if (!insert_ascii_koyo_lrc(vl))
                    return error(ERROR_IO_NO_GENERATE_REQ);
                return error(0);}

            virtual ns_error check_envelope(std::string& resp, size_t cnt) {
                std::string tmp = "";
                if (!hexsequence_to_binary_block(resp, tmp))
                    return error(ERROR_IO_PARSERESP);
                if (cnt != tmp.size())
                    return error(ERROR_IO_PARSERESP);
                resp = tmp;
                return error(0);}};


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*ecom_protocol*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class ecom_protocol : public basis_koyo_protocol {
        public:

            ecom_protocol(basis_iostream_ptr io) : basis_koyo_protocol(io), trasactcnt(0) {}


        protected:
            
            
            virtual ns_error readblock(block& blk);

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd);

            virtual ns_error read_request(koyodevn dvnum, num32 startaddr, size_t cnt, std::string& resp);

            virtual ns_error write_request(const std::string& vl, koyodevn dvnum, num32 startaddr, size_t cnt);

            virtual ns_error kseq_write_request(koyodevn dvnum, num32 startaddr, bool on = true);

            ns_error ccm_generate_body(std::string& vl, num32 startaddr, const std::string fnc, size_t cnt, std::string wval = "");

            ns_error ccm_kseq_generate_body(std::string& vl, num32 startaddr, bool on = true);

            ns_error ccm_response(std::string& resp);

            virtual ns_error check_envelope(std::string& resp, size_t cnt);

            unum16 trasactcnt;};
}}



#endif	/* MODBUS_PROTOCOL_H */

