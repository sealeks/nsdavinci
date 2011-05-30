/* 
 * File:   driver_service.h.cpp
 * Author: Serg
 * 
 * Created on 27 Октябрь 2010 г., 15:17
 */

#include <kernel/driver_detail.h>

namespace dvnci {
    namespace driver {

        /////////////////////////////////////////////////////////////////////////////////////////////////////
        
        
       bool calculate_ccitt_crc (const std::string& src, num16& crc, std::string::size_type strt) {
            if (src.size() > strt) {
                for (std::string::size_type it = strt; it < src.size(); ++it ) {
                    crc = crc ^ (num16) src.at(it) << 8;
                    for ( num16 j = 0; j < 8; j++ ) {
                        if (crc & 0x8000) crc = (crc << 1) ^ 0x1021;
                        else crc <<= 1;}}
                return true;}
            return false;}

        bool insert_ccitt_crc (std::string& src, std::string::size_type strt) {
            num16 crc = 0;
            if (calculate_ccitt_crc(src, crc, strt)) {
                char Lcrc = static_cast<char> ((crc & 0xFF));
                crc = (crc & 0xFF00) >> 8;
                char Hcrc = static_cast<char> (crc);
                src = src + std::string((char*) &Hcrc, 1) + std::string((char*) &Lcrc, 1);
                return true;}
            return false;}

        bool check_and_clear_ccitt_crc (std::string& src, std::string::size_type strt) {
            if (src.size()<(3 + strt)) return false;
            num16 crc = 0;
            if (calculate_ccitt_crc(src, crc, strt)) {
                src = src.substr(0 , src.size() - 2);
                return (crc == 0);}
            return false;}






        ////////////////////////////////////////////////////////////////////////////////////////////////////

        /*		High-Order Byte Table
Table of CRC values for high–order byte */
        const unum8 auchCRCHi[] = {
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
            0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
            0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
            0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,
            0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
            0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
            0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
            0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,
            0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
            0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
            0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,
            0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
            0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,
            0x40} ;
        /*Low-Order Byte Table
       Table of CRC values for low–order byte */
        const unum8  auchCRCLo[] = {
            0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,
            0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
            0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,
            0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
            0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,
            0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
            0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,
            0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
            0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,
            0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
            0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,
            0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
            0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,
            0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
            0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,
            0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
            0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,
            0x40};
        
        
        bool calculate_ibm_crc16(const std::string& src, num16& crc, std::string::size_type strt) {
            if (src.size() <= strt) return false;
            unum8 uchCRCHi = 0xFF ;
            unum8 uchCRCLo = 0xFF ;
            unum8 uIndex = 0;
            std::string::size_type it = strt;
            while (it < src.size()) {
                uIndex = uchCRCLo ^ src.at(it++) ;
                uchCRCLo = uchCRCHi ^ auchCRCHi[uIndex] ;
                uchCRCHi = auchCRCLo[uIndex] ;}
            crc = uchCRCLo;
            crc = (crc << 8) | (uchCRCHi) ;
            return true;}

        bool insert_ibm_crc16 (std::string& src, std::string::size_type strt) {
            num16 crc = 0;
            if (calculate_ibm_crc16(src, crc, strt)) {
                char Lcrc = static_cast<char> ((crc & 0xFF));
                crc = (crc & 0xFF00) >> 8;
                char Hcrc = static_cast<char> (crc);
                src = src + std::string((char*) &Hcrc, 1) + std::string((char*) &Lcrc, 1);
                return true;}
            return false;}

        bool check_and_clear_ibm_crc16 (std::string& src, std::string::size_type strt) {
            if (src.size()<(3 + strt)) return false;
            num16 crc = 0;
            if (calculate_ibm_crc16(src, crc, strt)) {
                src = src.substr(0 , src.size() - 2);
                return (crc == 0);}
            return false;}
        
        
        
        //////////////////////////////////////////////////////////////
        
         ns_error abstract_protocol::operator<<(block& blk) {
                if (!ios) return error(ERROR_IO_NOLINKSTREAM);
                error(0);
                if (!error(readblock(blk)))
                    set_value(rdata(), blk);
                else
                    clearbuff();
                return error();}

         ns_error abstract_protocol::operator<<(commands_vect& comds) {
                if (!ios) return error(ERROR_IO_NOLINKSTREAM);
                error(0);
                for (commands_vect::const_iterator it = comds.begin(); it != comds.end(); ++it) {
                    error(0);
                    std::string tmpvl;
                    if (!get_value(tmpvl, *it)) {
                        DEBUG_VAL_DVNCI(tmpvl)
                        if (!tmpvl.empty()) {
                            if (error(writecmd(tmpvl, *it))) {
                                clearbuff();};}}}
                return error(0);}


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Установщик значении линейного отображения памяти*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ns_error linemem_value_manager::set_value(const std::string& dbk, block& blk) {
            error(0);
            parcel_const_iterator strtit = blk.begin();
            parcel_const_iterator endit = blk.end();
            endit++;
            std::string vl;
            std::string::size_type adr_offset = 0;
            std::string::size_type dt_size = 0;
            size_t bitnm = 0;
            for (parcel_const_iterator it = strtit; it != endit; ++it) {
                adr_offset = ((*it->first) - (*strtit->first));
                dt_size = it->first->size();
                bitnm = getbitnum(strtit, it);
                if (get_data_block(dbk, vl, adr_offset, dt_size)) {
                    set_val(vl, it->first, bitnm);}
                else {
                    it->first->error(ERROR_IO_NO_DATA);}}
            return error(0);}

        ns_error linemem_value_manager::get_value(std::string& val, parcel_ptr cmd) {
            error(0);
            size_t bitnm = cmd->indx();
            get_val(val, cmd, bitnm );
            return error(0);}

        ns_error linemem_value_manager::set_val(std::string& val, parcel_ptr prcl, size_t bitn) {

            if (!spec_protocol_convertion_out(val, bitn)) {
                return error(0);}
            if (bitn != NULL_BIT_NUM) {
                if (!val.empty()) {
                    prcl->value(static_cast<bool> ((val.at(0) & (0x01 << bitn))));}
                else {
                    prcl->error(ERROR_IO_NO_DATA);}}
            else {
                prcl->value_byte_seq(val);}
            return error(0);}

        bool linemem_value_manager::get_data_block(const std::string& dbk, std::string& vl, std::string::size_type offset, std::string::size_type dtsize) {
            if ((offset + dtsize) > dbk.size()) return false;
            vl = dbk.substr(offset, dtsize);
            return true;}

        ns_error linemem_value_manager::get_val(std::string& val, parcel_ptr cmd, size_t bitn) {
            short_value tmp = cmd->value();
            switch (cmd->tgtype()) {
                case TYPE_NUM64:{
                    if (true/*cmd->get_simpl_val_cast<num64 > (tmp)*/) {
                        val = primtype_to_string<num64 > (tmp.value<num64>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_UNUM64:{
                    if (true/*cmd->get_simpl_val_cast<unum64 > (tmp)*/) {
                        val = primtype_to_string<unum64 > (tmp.value<unum64>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_NUM32:{
                    if (true/*cmd->get_simpl_val_cast<num32 > (tmp)*/) {
                        primtype_to_string<num64 > (tmp.value<num32>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_UNUM32:{
                    if (true/*cmd->get_simpl_val_cast<unum32 > (tmp)*/) {
                        primtype_to_string<unum32 > (tmp.value<unum32>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_NUM16:{
                    if (true/*cmd->get_simpl_val_cast<num16 > (tmp)*/) {
                        primtype_to_string<unum16 > (tmp.value<num16>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_UNUM16:{
                    if (true/*cmd->get_simpl_val_cast<unum16 > (tmp)*/) {
                        primtype_to_string<unum16 > (tmp.value<unum16>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_NUM8:{
                    if (true/*cmd->get_simpl_val_cast<num8 > (tmp)*/) {
                        primtype_to_string<num8 > (tmp.value<num8>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_UNUM8:{
                    if (true/*cmd->get_simpl_val_cast<unum8 > (tmp)*/) {
                        primtype_to_string<unum8 > (tmp.value<unum8>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_DOUBLE:{
                    if (true/*cmd->get_simpl_val_cast(tmp)*/) {
                        primtype_to_string<double > (tmp.value<double>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                case TYPE_FLOAT:{
                    if (true/*cmd->get_simpl_val_cast(tmp)*/) {
                        primtype_to_string<float > (tmp.value<float>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}
                default:{
                    if (true/*cmd->get_simpl_val_cast(tmp)*/) {
                        primtype_to_string<double > (tmp.value<double>());
                        spec_protocol_convertion_in(val);
                        return error(0);}
                    return error(ERROR_IO_NO_GENERATE_REQ);}}
            return error(ERROR_IO_NO_GENERATE_REQ);}
        
     ///////////////////////////////////////////////////////////////////////////////////////////////////
        
            bool base_device_service::init() {
                if (init_) return true;
                if (!io_protocolbuilder) return false;
                if (!io_protocol) io_protocol = io_protocolbuilder->build(link, lasterror);
                if (!io_protocol) return false;
                init_ = true;
                connected();
                return true;};

            bool base_device_service::connected() {
                if (init_) {
                  if ((connectred_) && (connectredinit_))  return true;
                  if (!io_protocol) return false;
                  if ((!connectred_) && (io_protocol->connect())) {
                    error(io_protocol->error());
                    return false;}
                  connectred_=true;
                  if (!afterinit()) {
                    lasterror = ERROR_IO_NOINIT_PROTOCOL;
                    return false;}
                  connectredinit_=true;}
                return true;};

            bool base_device_service::afterinit() {
                return ((io_protocol) && (io_protocol->init()));};

            bool base_device_service::uninit() {
                if (!init_) return true;
                if (!io_protocolbuilder) return true;
                if (!io_protocol) return true;
                beforeuninit();
                connectred_=false;
                connectredinit_=false;
                error(io_protocol->disconnect());
                init_ = false;
                return true;};

            bool base_device_service::beforeuninit() {
                return ((io_protocol) && (io_protocol->uninit()));};
                
            ns_error base_device_service::read(block& blk) {
                check_need_util();
                if (io_protocol) return error((*io_protocol) << blk);
                return error(ERROR_IO_NOINIT_PROTOCOL);};
                

            ns_error base_device_service::write(commands_vect& comds) {
                if (io_protocol) return error((*io_protocol) << comds);
                return error(ERROR_IO_NOINIT_PROTOCOL);};



            bool base_device_service::is_need_util(){
                if (util_interval_<=0) return false;
                return secondsbetween(util_time(),now())>util_interval_;}

            void base_device_service::check_need_util(){
                if (io_protocol){
                   if (is_need_util()){
                       if (io_protocol->utiloperation(util_device_set_))
                          util_time_= now();}}}
        

}}
