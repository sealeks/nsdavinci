/* 
 * File:   iec60870_protocol.h
 * Author: Serg
 *
 * Created on 18 ?????? 2010 ?., 17:22
 */

#ifndef IEC60870_PROTOCOL_H
#define	 IEC60870_PROTOCOL_H

#include <kernel/utils.h>
#include <kernel/systemutil.h>
#include <kernel/error.h>
#include <kernel/constdef.h>

namespace dvnci {
    namespace prot80670 {

        typedef std::vector<boost::uint8_t> octet_sequence;
        typedef boost::shared_ptr<octet_sequence> octet_sequence_ptr;         
        
        typedef boost::uint8_t type_id;
        typedef boost::uint8_t cause_type;    
        typedef boost::uint8_t interrogation_type;
        typedef boost::uint32_t data_address;
        typedef boost::uint16_t device_address;
        typedef boost::uint8_t bit_number;
        typedef boost::uint16_t tcpcounter_type;
        const bit_number NULL_BITNUMBER = '\xFF';


        const cause_type CS_CYCLIC = 1; //  periodical, cyclic
        const cause_type CS_PROCIMG = 2; //  generated for renewal of the process image
        const cause_type CS_SPONT = 3; //  spontaneous
        const cause_type CS_INIT = 4; //  initialized
        const cause_type CS_POLL = 5; //  polled
        const cause_type CS_ACT = 6; //  activation
        const cause_type CS_CONF_ACT = 7; //  confirmation of activation
        const cause_type CS_ABORT_ACT = 8; //  aborting of activation
        const cause_type CS_ABORT_ACT_CONF = 9; //  confirmation of aborting of activation
        const cause_type CS_END_ACT = 10; //  end of activation
        const cause_type SC_STATUS_REMCMD = 11; //  status information, caused by a remote command
        const cause_type SC_STATUS_LOCCMD = 12; //  status information, caused by a local command
        const cause_type SC_INTERROG_GEN = 20; //  interrogated by general interrogation
        const cause_type SC_INTERROG_G1 = 21; //  interrogated by interrogation of group 1
        const cause_type SC_INTERROG_G2 = 22; //  interrogated by interrogation of group 2
        const cause_type SC_INTERROG_G3 = 23; //  interrogated by interrogation of group 3
        const cause_type SC_INTERROG_G4 = 24; //  interrogated by interrogation of group 4
        const cause_type SC_INTERROG_G5 = 25; //  interrogated by interrogation of group 5
        const cause_type SC_INTERROG_G6 = 26; //  interrogated by interrogation of group 6
        const cause_type SC_INTERROG_G7 = 27; //  interrogated by interrogation of group 7
        const cause_type SC_INTERROG_G8 = 28; //  interrogated by interrogation of group 8
        const cause_type SC_INTERROG_G9 = 29; //  interrogated by interrogation of group 9
        const cause_type SC_INTERROG_G10 = 30; //  interrogated by interrogation of group 10
        const cause_type SC_INTERROG_G11 = 31; //  interrogated by interrogation of group 11
        const cause_type SC_INTERROG_G12 = 32; //  interrogated by interrogation of group 12
        const cause_type SC_INTERROG_G13 = 33; //  interrogated by interrogation of group 13
        const cause_type SC_INTERROG_G14 = 34; //  interrogated by interrogation of group 14
        const cause_type SC_INTERROG_G15 = 35; //  interrogated by interrogation of group 15
        const cause_type SC_INTERROG_G16 = 36; //  interrogated by interrogation of group 16
        const cause_type SC_INTERROG_CNT_GEN = 37; //  interrogated by general counter interrogation
        const cause_type SC_INTERROG_CNT_G1 = 38; //  interrogated by interrogation of counter group 1
        const cause_type SC_INTERROG_CNT_G2 = 39; //  interrogated by interrogation of counter group 2
        const cause_type SC_INTERROG_CNT_G3 = 40; //  interrogated by interrogation of counter group 3
        const cause_type SC_INTERROG_CNT_G4 = 41; //  interrogated by interrogation of counter group 4
        const cause_type SC_INTERROG_CNT_SNGL = 42; //  interrogated by interrogation of a single counter



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
        const type_id F_SC_NB_1 = 127; // Query log ? Request archive file
        
        const interrogation_type INTERROG_GLOBAL = 20; // station interrogation (global)

        typedef std::pair<std::string, type_id> string_type_id_pair;
        typedef std::map<std::string, type_id> string_type_id_map;
        typedef std::pair<type_id, std::size_t> type_id_size_pair;
        typedef std::map<type_id, std::size_t> type_id_size_map;        

        type_id find_type_id(const std::string& val);
        std::size_t find_type_size(type_id val);        

      
        


        /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// dataobject
        /////////////////////////////////////////////////////////////////////////////////////////////////    

        class dataobject;
        typedef boost::shared_ptr<dataobject> dataobject_ptr;

        class dataobject {

        public:

            dataobject() : devnum_(0), address_(0), type_(0), bit_(NULL_BITNUMBER) {
            };

            dataobject(device_address dev, type_id tp, data_address addr, const octet_sequence& dt = octet_sequence()) :
            devnum_(dev), address_(addr), type_(tp), data_(dt), bit_(NULL_BITNUMBER) {
            };

            dataobject(device_address dev, type_id tp, data_address addr, bit_number bt, const octet_sequence& dt = octet_sequence()) :
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

            const octet_sequence& data() const {
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
            octet_sequence data_;
        };

        bool operator==(dataobject_ptr ls, dataobject_ptr rs);
        bool operator<(dataobject_ptr ls, dataobject_ptr rs);


        typedef std::set<dataobject_ptr> dataobject_set;
        typedef std::vector<dataobject_ptr> dataobject_vct;        
        
        
        
         /////////////////////////////////////////////////////////////////////////////////////////////////
        //////// asdu_body
        /////////////////////////////////////////////////////////////////////////////////////////////////
        
        const std::size_t MAX_ASDU_SIZE = 249;        
        
        class asdu_body{
        public:
            
            asdu_body(dataobject_ptr vl, cause_type cs, bool sq=false, bool ngt=false, bool tst=false);
            asdu_body(const dataobject_vct& vl, cause_type cs, std::size_t cnt, bool sq=false, bool ngt=false, bool tst=false); // sq = 1 only the first information object has an information object address, all other information objects have the addresses +1, +2, ...
            asdu_body(const dataobject_vct& vl, cause_type cs, bool sq=false, bool ngt=false, bool tst=false); // sq = 0  each information object has its own information object address in the message         
            asdu_body(octet_sequence_ptr dt);
            ~asdu_body(){}
            
            static asdu_body create_activation(interrogation_type tp=INTERROG_GLOBAL, cause_type cs = CS_ACT);
            
            octet_sequence& body() {
                return *body_;
            }   
            
            const octet_sequence& body() const {
                return *body_;
            }  
 
            octet_sequence_ptr body_ptr() const {
                return body_;
            }        
            
            
            type_id type() const {
                if (!body().empty())
                    return body()[0];
                return 0;
            }
            
            bool sq() const {
                if (body().size()>1)
                    return body()[1] & '\x80';
                return false;
            }          
            
            std::size_t count() const {
                if (body().size()>1)
                    return static_cast<std::size_t>(body()[1] & '\x7F');
                return 0;
            }       
            
            bool test() const {
                if (body().size()>2)
                    return body()[2] & '\x80';
                return false;
            }             
            
            bool negative() const {
                if (body().size()>2)
                    return body()[2] & '\x40';
                return false;
            }               
            
            cause_type cause() const {
                if (body().size()>2)
                    return static_cast<cause_type>(body()[2] & '\x3F');
                return 0;
            }         
            
            boost::uint8_t oa() const {
                if (body().size()>3)
                    return static_cast<boost::uint8_t>(body()[3]);
                return 0;
            }     
            
            
            device_address address() const {
                if (body().size()>5)
                    return *reinterpret_cast<const device_address*>(&(body()[4]));
                return 0;
            } 
            
            bool get(dataobject_vct& rslt);
            
        private:
            
            void encode(const dataobject_vct& vl, cause_type cs, bool sq, bool ngt, bool tst);
            
            
            octet_sequence_ptr body_;
        };
        
        


       
    }
}

#endif	/* MODBUS_PROTOCOL_H */

