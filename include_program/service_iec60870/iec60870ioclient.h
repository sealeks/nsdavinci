/* 
 * File:   ns_ioclient.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 17 РњР°СЂС‚ 2010 Рі., 0:05
 */

#ifndef _DVNCI_KRNL_NS_IEC60850CLIENT_H
#define	_DVNCI_KRNL_NS_IEC60850CLIENT_H

#include <boost/asio/read_at.hpp>

#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/constdef.h>

namespace dvnci {
    namespace prot80670 {

        typedef boost::uint16_t type_id;
        typedef boost::uint32_t data_address;
        typedef boost::uint16_t device_address;
        typedef boost::uint8_t bit_number;

        const bit_number NULL_BITNUMBER = '\xFF';

        const type_id M_SP_NA_1 = 1; //Single-point information
        const type_id M_SP_TA_1 = 2; //Single-point information with time-tag
        const type_id M_DP_NA_1 = 3; //Double-point information
        const type_id M_DP_TA_1 = 4; //Double-point information with time-tag
        const type_id M_ST_NA_1 = 5; //Step position information
        const type_id M_ST_TA_1 = 6; //Step position information with time-tag
        const type_id M_BO_NA_1 = 7; //Bitstring of 32 bits
        const type_id M_BO_TA_1 = 8; //Bitstring of 32 bits with time-tag
        const type_id M_ME_NA_1 = 9; //Measured value, normalized value
        const type_id M_ME_TA_1 = 10; //Measured value, normalized value with time-tag
        const type_id M_ME_NB_1 = 11; //Measured value, scaled value
        const type_id M_ME_TB_1 = 12; //Measured value, scaled value with time-tag
        const type_id M_ME_NC_1 = 13; //Measured value, short floating point value
        const type_id M_ME_TC_1 = 14; //Measured value, short floating point value with time-tag
        const type_id M_IT_NA_1 = 15; //Integrated totals
        const type_id M_IT_TA_1 = 16; //Integrated totals with time-tag
        const type_id M_EP_TA_1 = 17; //Event of protection equipment with time-tag
        const type_id M_EP_TB_1 = 18; //Packed start events of protection equipment with time-tag
        const type_id M_EP_TC_1 = 19; //Packed output circuit information of protection equipment with timetag
        const type_id M_PS_NA_1 = 20; //Packed single point information with status change detection
        const type_id M_ME_ND_1 = 21; //Measured value, normalized value without quality descriptor
        const type_id M_SP_TB_1 = 30; //Single-point information with time tag CP56Time2a
        const type_id M_DP_TB_1 = 31; //Double-point information with time tag CP56Time2a
        const type_id M_ST_TB_1 = 32; //Step position information with time tag CP56Time2a
        const type_id M_BO_TB_1 = 33; //Bitstring of 32 bit with time tag CP56Time2a
        const type_id M_ME_TD_1 = 34; //Measured value, normalized value with time tag CP56Time2a
        const type_id M_ME_TE_1 = 35; //Measured value, scaled value with time tag CP56Time2a
        const type_id M_ME_TF_1 = 36; //Measured value, short floating point value with time tag CP56Time2a
        const type_id M_IT_TB_1 = 37; //Integrated totals with time tag CP56Time2a
        const type_id M_EP_TD_1 = 38; //Event of protection equipment with time-tag CP56Time2a
        const type_id M_EP_TE_1 = 39; //Packed start events of protection equipment with time-tag CP56Time2a
        const type_id M_EP_TF_1 = 40; //Packed output circuit information of protection equipment with timetag CP56Time2a

        const type_id C_SC_NA_1 = 45; // Single command 
        const type_id C_DC_NA_1 = 46; // Double command
        const type_id C_RC_NA_1 = 47; // Regulating step command
        const type_id C_SE_NA_1 = 48; // Set point command, normalized value
        const type_id C_SE_NB_1 = 49; // Set point command, scaled value
        const type_id C_SE_NC_1 = 50; // Set point command, short floating point value
        const type_id C_BO_NA_1 = 51; // Bitstring of 32 bit
        const type_id C_SC_TA_1 = 58; // Single command with time tag CP56Time 2a 
        const type_id C_DC_TA_1 = 59; // Double command with time tag CP56Time 2a
        const type_id C_RC_TA_1 = 60; // Regulating step command with time tag CP56Time 2a
        const type_id C_SE_TA_1 = 61; // Set point command, normalized value with time tag CP56Time 2a
        const type_id C_SE_TB_1 = 62; // Set point command, scaled value with time tag CP56Time 2a
        const type_id C_SE_TC_1 = 63; // Set point command, short floating point value with time tag CP56Time 2a
        const type_id C_BO_TA_1 = 64; // Bitstring of 32 bit with time tag CP56Time 2a      

        const type_id M_EI_NA_1 = 70; //End of initialization

        const type_id C_IC_NA_1 = 100; // Interrogation command 100
        const type_id C_CI_NA_1 = 101; // Counter interrogation command
        const type_id C_RD_NA_1 = 102; // Read command
        const type_id C_CS_NA_1 = 103; // Clock synchronization command
        const type_id C_TS_NA_1 = 104; // Test command
        const type_id C_RP_NA_1 = 105; // Reset process command
        const type_id C_CD_NA_1 = 106; // Delay acquisition command
        const type_id C_TS_TA_1 = 107; // Test command with time tag CP56time2a      

        const type_id P_ME_NA_1 = 110; // Parameter of measured value, normalized value 110
        const type_id P_ME_NB_1 = 111; // Parameter of measured value, scaled value
        const type_id P_ME_NC_1 = 112; // Parameter of measured value, short floating point value
        const type_id P_AC_NA_1 = 113; // Parameter activation

        const type_id F_FR_NA_1 = 120; // File ready 120
        const type_id F_SR_NA_1 = 121; // Section ready
        const type_id F_SC_NA_1 = 122; // Call directory, select file, call file, call section
        const type_id F_LS_NA_1 = 123; // Last section, last segment
        const type_id F_AF_NA_1 = 124; // Ack file, ack section
        const type_id F_SG_NA_1 = 125; // Segment
        const type_id F_DR_TA_1 = 126; // Directory {blank or X, only available in monitor (standard) direction}
        const type_id F_SC_NB_1 = 127; // Query log � Request archive file

        typedef std::pair<std::string, type_id> string_type_id_pair;
        typedef std::map<std::string, type_id> string_type_id_map;

        type_id find_type_id(const std::string& val);


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// dataobject
        /////////////////////////////////////////////////////////////////////////////////////////////////    

        class dataobject;
        typedef boost::shared_ptr<dataobject> dataobject_ptr;

        class dataobject {

        public:

            dataobject() : devnum_(0), address_(0), type_(0), bit_(NULL_BITNUMBER) {
            };

            dataobject(device_address dev, type_id tp, data_address addr, const std::string& dt = "") :
            devnum_(dev), address_(addr), type_(tp), data_(dt), bit_(NULL_BITNUMBER) {
            };

            dataobject(device_address dev, type_id tp, data_address addr, bit_number bt, const std::string& dt = "") :
            devnum_(dev), address_(addr), type_(tp), data_(dt), bit_(bt) {
            };

            ~dataobject() {
            };

            static dataobject_ptr build_from_bind(device_address dev, std::string bind);

            device_address devnum() const {
                return devnum_;
            }

            data_address address() const {
                return address_;
            }

            type_id type() const {
                return type_;
            }

            bit_number bit() const {
                return bit_;
            }

            bool has_bit() const {
                return bit_ != NULL_BITNUMBER;
            }

            const std::string& data() const {
                return data_;
            }

            bool valid() const {
                return type_;
            }

            friend bool operator==(const dataobject& ls, const dataobject& rs);
            friend bool operator<(const dataobject& ls, const dataobject& rs);
        protected:

            device_address devnum_;
            data_address address_;
            type_id type_;
            bit_number bit_;
            std::string data_;
        };

        bool operator==(dataobject_ptr ls, dataobject_ptr rs);
        bool operator<(dataobject_ptr ls, dataobject_ptr rs);


        typedef std::set<dataobject_ptr> dataobject_set;


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// class iec60870tcp_message
        /////////////////////////////////////////////////////////////////////////////////////////////////           



        /* class iec60870tcp_message {

         public:

             enum {

                 header_length = 10
             };

             iec60870tcp_message(const std::string& vl = "", iec60870tcp_msgtype tp = 0) : body_(vl), body_length_(0), type_(tp) {
                 encode_header();
             }

             iec60870tcp_message(const boost::asio::streambuf& val) : body_(boost::asio::buffer_cast<const num8*>(val.data()), val.size()), body_length_(0), type_(0) {
                 encode_header();
             }

             const std::string& message() const {
                 return body_;
             }

             void message(const boost::asio::streambuf& vl) {
                 body_ = std::string(boost::asio::buffer_cast<const num8*>(vl.data()), vl.size() < body_length() ? vl.size() : body_length());
             }

             const size_t body_length() const {
                 return header().size() < header_length ? 0 : static_cast<size_t> (*((unum64*) (header().c_str())));
             }

             const iec60870tcp_msgtype type() const {
                 return header().size() < header_length ? 0 : *((iec60870tcp_msgtype*) ((num8*) header().c_str() + 8));
             }

             void header(const char* val) {
                 header_.clear();
                 header_.append(val, 10);
                 decode_header();
             }

             const std::string& header() const {
                 return header_;
             }


         private:

             void encode_header() {
                 header_.clear();
                 unum64 tmp_length = body_.size();
                 body_length_ = body_.size();
                 header_.append((char*) &tmp_length, 8);
                 header_.append((char*) &type_, 2);
             }

             bool decode_header() {
                 body_length_ = static_cast<size_t> (*((unum64*) header().c_str()));
                 type_ = *((iec60870tcp_msgtype*) ((num8*) header().c_str() + 8));
                 return true;
             }

             std::string body_;
             std::string header_;
             size_t body_length_;
             iec60870tcp_msgtype type_;
         };*/



        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// iec60870ioclient
        /////////////////////////////////////////////////////////////////////////////////////////////////     


        class iec60870ioclient;
        typedef boost::shared_ptr<iec60870ioclient> iec60870ioclient_ptr;

        class iec60870ioclient : public boost::enable_shared_from_this<iec60870ioclient> {

        public:

            enum connectionState {

                connected, disconnected
            };

            iec60870ioclient();

            virtual ~iec60870ioclient();

            connectionState state() {
                return state_;
            }

            void connect(std::string host, std::string port, timeouttype tmo = DEFAULT_DVNCI_TIMOUT);
            void disconnect();
            //bool req(iec60870tcp_message& msg, iec60870tcp_message& resp);


        private:

            void handle_resolve(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_connect(const boost::system::error_code& err,
                    boost::asio::ip::tcp::resolver::iterator endpoint_iterator);

            void handle_write(const boost::system::error_code& err);

            void handle_readheader(const boost::system::error_code& err);

            void handle_endreq(const boost::system::error_code& err);

            void handle_timout_expire(const boost::system::error_code& err);


            boost::asio::io_service io_service_;
            boost::asio::ip::tcp::socket socket_;
            connectionState state_;
            boost::asio::deadline_timer tmout_timer;
            timeouttype timout;


            //iec60870tcp_message respmsg;
            //boost::asio::streambuf response_body;
            //boost::array<char, 10 > buf;

            volatile bool is_data_ready;
            volatile bool is_timout;
            volatile bool is_connect;
            volatile bool is_error;
            volatile int error_cod;
        };

    }
}


#endif	/* _NS_IOCLIENT_H */

