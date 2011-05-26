/* 
 * File:   driver_service.h
 * Author: Serg
 *
 * Created on 27 РћРєС‚СЏР±СЂСЊ 2010 Рі., 15:17
 */

#ifndef _DVNCI_KRNL_DRIVERIOSERVICE_H
#define	_DVNCI_KRNL_DRIVERIOSERVICE_H

#include <kernel/basis_iostream.h>
#include <kernel/driver_blockmodel.h>

namespace dvnci {
    namespace driver {


        bool insert_ccitt_crc(std::string& src, std::string::size_type strt);
        bool check_and_clear_ccitt_crc(std::string& src, std::string::size_type strt);


        bool insert_ibm_crc16(std::string& src, std::string::size_type strt);
        bool check_and_clear_ibm_crc16(std::string& src, std::string::size_type strt);

        inline static num16 be_le_convert_num16(num16 vl) {
            return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));}

        inline static num32 be_le_convert_num32(num32 vl) {
            return (((vl >> 16) & 0xFFFF) | (0xFFFF0000 & (vl << 16)));}

        inline static num64 be_le_convert_num64(num64 vl) {
            return (((vl >> 32) & 0xFFFFFFFFLL) | (0xFFFFFFFF00000000LL & (vl << 32)));}

        bool be_le16_convert_string(std::string& vl);

        std::string binary_block_to_hexsequence_debug(const std::string& vl);

        std::string binary_block_to_hexsequence(const std::string& vl);

        bool hexsequence_to_binary_block(const std::string& vl, std::string& rslt);



        const std::string NUL = "\x0";
        const std::string SOH = "\x1";
        const std::string STX = "\x2";
        const std::string ETX = "\x3";
        const std::string EOT = "\x4";
        const std::string ENQ = "\x5";
        const std::string ACK = "\x6";
        const std::string BEL = "\x7";
        const std::string BS = "\x8";
        const std::string HT = "\x9";
        //const std::string nl  =  "\xA";
        const std::string LF = "\xA";
        const std::string VT = "\xB";
        const std::string NP = "\xC";
        const std::string FF = "\xC";
        const std::string CR = "\xD";
        const std::string SO = "\xE";
        const std::string SI = "\xF";
        const std::string DLE = "\x10";
        const std::string DCL = "\x11";
        const std::string NAK = "\x15";
        const std::string SYN = "\x16";
        const std::string ETB = "\x17";
        const std::string CAN = "\x18";
        const std::string EM = "\x19";
        const std::string SUB = "\x1A";
        const std::string ESC = "\x1B";
        const std::string FS = "\x1C";
        const std::string GS = "\x1D";
        const std::string RS = "\x1E";
        const std::string US = "\x1F";
        const std::string IS1 = "\x1F";
        const std::string SP = "\x20";

        const size_t NULL_BIT_NUM = 0xFFFF;


        const num32  UTIL_INTERVAL_NONE =  0;
        const num32  UTIL_INTERVAL_MINUTE =  60;
        const num32  UTIL_INTERVAL_HOUR =  3600;
        const num32  UTIL_INTERVAL_DAY =  3600 * 24;
        const num32  UTIL_INTERVAL_MONTH =  3600 * 24 * 28;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый обработчик протокола*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class abstract_protocol {
        public:

            abstract_protocol(basis_iostream_ptr io) : ios(io), lasterror(0) {}

            virtual ~abstract_protocol() {};

            ns_error operator<<(block& blk);

            ns_error operator<<(commands_vect& comds);

            virtual bool init() {
                return true;}
            
            virtual bool uninit() {
                return true;}

            virtual ns_error connect() {
                return error(ios ? ios->open() : ERROR_IO_DEVICE_CHANAL_NOT_DEF);}

            virtual ns_error disconnect() {
                return error( ios ? ios->close() : 0);}
            
           
            virtual bool utiloperation(const num32_set& vl){
                return true;}


            ns_error error() const {
                return lasterror;};

            ns_error error(ns_error err) {
                return (lasterror = err);};


        protected:
            
            virtual ns_error readblock(block& blk) = 0;

            virtual ns_error writecmd(const std::string& vl, parcel_ptr cmd) = 0;
                     
            virtual ns_error set_value(const std::string& val, block& blk) = 0;

            virtual ns_error get_value(std::string& val, parcel_ptr cmd) = 0;    
            
            const std::string& rdata() const {
                return readdata;}

            void wdata(std::string& val) {
                writedata = val;}
            
            ns_error clearbuff() {
                if (!ios) return error(ERROR_IO_DEVICE_CHANAL_NOT_DEF);
                ios->clearbuff();
                return error();}

            ns_error clearbuff_deep() {
                if (!ios) return error(ERROR_IO_DEVICE_CHANAL_NOT_DEF);
                ios->clearbuff_deep();
                return error();} 
            
            basis_iostream_ptr io() {
                return ios ? ios : basis_iostream_ptr();}

            basis_iostream_ptr ios;
            std::string readdata;
            std::string writedata;

        private:

            ns_error lasterror;};


        typedef boost::shared_ptr<abstract_protocol> ioprotocol_ptr;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый установщик значении*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class abstract_value_manager {
        public:

            abstract_value_manager() : lasterror(0) {}

            virtual ~abstract_value_manager() {};
            virtual ns_error set_value(const std::string& val, block& blk) = 0;
            virtual ns_error get_value(std::string& val, parcel_ptr cmd) = 0;

            ns_error error() const {
                return lasterror;};

            ns_error error(ns_error err) {
                return (lasterror = err);};


        private:
            ns_error lasterror;};


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Установщик значении линейного отображения памяти*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class linemem_value_manager : public abstract_value_manager {
        public:

            linemem_value_manager() : abstract_value_manager() {}

            virtual ns_error set_value(const std::string& dbk, block& blk);

            virtual ns_error get_value(std::string& val, parcel_ptr cmd);

        protected:

            virtual size_t getbitnum(parcel_const_iterator strt, parcel_const_iterator stp) {
                return NULL_BIT_NUM;}

            virtual bool spec_protocol_convertion_out(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return true;}

            virtual bool spec_protocol_convertion_in(std::string& val, size_t bitn = NULL_BIT_NUM) {
                return true;}

            virtual ns_error set_val(std::string& val, parcel_ptr prcl, size_t bitn = NULL_BIT_NUM);

            bool get_data_block(const std::string& dbk, std::string& vl, std::string::size_type offset, std::string::size_type dtsize);

            virtual ns_error get_val(std::string& val, parcel_ptr cmd, size_t bitn = NULL_BIT_NUM);};



        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Шаблон обработчика протокола с установщиком значений*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template < typename VALUEMANAGER>
        class templ_protocol : public abstract_protocol {
        public:

            templ_protocol(basis_iostream_ptr io) : abstract_protocol(io) {}


        protected:
            
            
            virtual ns_error set_value(const std::string& val, block& blk) {
                return valmanager.set_value(val, blk);}

            virtual ns_error get_value(std::string& val, parcel_ptr cmd) {
                return valmanager.get_value(val, cmd);}
            
            VALUEMANAGER valmanager;};

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый генератор протокола*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        struct protocol_factory {

            virtual ioprotocol_ptr build(const metalink& lnk, ns_error & err) {
                err = ERROR_IO_DEVICE_CHANAL_NOT_DEF;
                return ioprotocol_ptr();}};

        typedef boost::shared_ptr<protocol_factory> protocol_factory_ptr;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Базовый класс менеджера устройства*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        class base_device_service {
        public:

            base_device_service(const metalink& lnk, num32 utilint = 0) : link(lnk), init_(false),
                                         connectred_(false), connectredinit_(false), util_interval_(utilint){
                util_time_= incmonth(now(),-120);};

            virtual ~base_device_service() {};

            virtual bool init();

            virtual bool connected();

            virtual bool afterinit();

            virtual bool uninit();

            virtual bool beforeuninit();
            
            ns_error operator<<(block& blk){
                return error(read(blk));}

            ns_error operator<<(commands_vect& comds){
                return error(write(comds));}

            ns_error error() const {
                return lasterror;};

            ns_error error(ns_error err) {
                return (lasterror = err);};
                
            void  util_device(num32_set& val){
                util_device_set_=val;}


        protected:
            
            virtual ns_error read(block& blk);
                
            virtual ns_error write(commands_vect& comds);

            void util_interval(num32 val) {
                util_interval_=val;}
          
            num32 util_interval() const {
                return util_interval_;}
            
            datetime util_time() const {
                return util_time_;}

            bool is_need_util();

            void check_need_util();


            ioprotocol_ptr       io_protocol;
            protocol_factory_ptr io_protocolbuilder;
            metalink             link;
            bool                 init_;
            bool                 connectred_;
            bool                 connectredinit_;
            num32                util_interval_;
            datetime             util_time_;

        private:
            ns_error             lasterror;
            num32_set            util_device_set_;};


        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /*Шаблон менеджера устройства с генератором протокола*/
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        template < typename PROTOCOLBUILDER>
        class templ_device_service : public base_device_service {
        public:

            templ_device_service(const metalink& lnk, num32 utilint = 0) : base_device_service(lnk, utilint) {
                io_protocolbuilder = protocol_factory_ptr(new PROTOCOLBUILDER());}};}}


#endif	/* driver_service.h_H */

