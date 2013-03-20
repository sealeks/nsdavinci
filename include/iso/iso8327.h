
/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOx225impl_H_H
#define ISOx225impl_H_H

#include <iso/rfc1006.h>

namespace boost {
    namespace itu {
        namespace x225impl {

            // ref X225 = ITU-T Rec. X.225(1995 E)           

            using boost::asio::basic_socket;
            using boost::asio::basic_socket_acceptor;


            typedef uint8_t spdu_type;
            typedef uint16_t valuelenth_type;
            typedef uint8_t varid_type;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   x225 utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     


            // SPDU identifier  *ref X225 5.6  Table 3 вЂ“ Functional units (only kernel and half-duplex implemented here)
            // Kernel FU
            const spdu_type CN_SPDU_ID = 13; //CONNECT SPDU *ref X225 8.3.1.1
            const spdu_type OA_SPDU_ID = 16; //OVERFLOW ACCEPT *ref X225 8.3.2.1
            const spdu_type CDO_SPDU_ID = 15; //CONNECT DATA OVERFLOW *ref X225 8.3.3.1
            const spdu_type AC_SPDU_ID = 14; //ACCEPT*ref X225 8.3.4.1
            const spdu_type RF_SPDU_ID = 12; //REFUSE *ref X225 8.3.5.1
            const spdu_type FN_SPDU_ID = 9; //FINISH *ref X225 8.3.6.1
            const spdu_type DN_SPDU_ID = 10; //DISCONNECT *ref X225 8.3.7.1
            const spdu_type NF_SPDU_ID = 8; //NOT FINISHED *ref X225 8.3.8.1
            const spdu_type AB_SPDU_ID = 25; //ABORT *ref X225 8.3.9.1
            const spdu_type AA_SPDU_ID = 26; //ABORT ACCEPT *ref X225 8.3.10.1
            const spdu_type DT_SPDU_ID = 1; //DATA TRANSFER *ref X225 8.3.11.1
            const spdu_type PR_SPDU_ID = 7; //PREPARE *ref X225 8.3.26.1

            //  Negotiated realease
            // GIVE TOKENS , PLEASE TOKENS             

            //Half-duplex FU
            const spdu_type GT_SPDU_ID = 1; // GIVE TOKENS  *ref X225 8.3.16.1
            const spdu_type PT_SPDU_ID = 2; //PLEASE TOKENS  *ref X225 8.3.17.1             

            //Duplex FU    
            //

            //Expedited data FU
            const spdu_type EX_SPDU_ID = 5; //EXPEDITED *ref X225 8.3.12.1  

            //Typed data FU
            const spdu_type TD_SPDU_ID = 33; //TYPED DATA *ref X225 8.3.13.1  

            //Capability data exchange FU
            const spdu_type CD_SPDU_ID = 61; //CAPABILITY DATA *ref X225 8.3.14.1  
            const spdu_type CDA_SPDU_ID = 62; //CAPABILITY DATA ACK *ref X225 8.3.15.1  

            // Minor synchronize FU
            const spdu_type MIP_SPDU_ID = 49; //MINOR SYNC POINT  *ref X225 8.3.20.1
            const spdu_type MIA_SPDU_ID = 50; //MINOR SYNC ACK *ref X225 8.3.21.1
            // GIVE TOKENS , PLEASE TOKENS

            // Symmetric synchronize FU                
            // MINOR SYNC POINT , MINOR SYNC ACK 

            //Major synchronize FU
            const spdu_type MAP_SPDU_ID = 41; //MAJOR SYNC POINT *ref X225 8.3.22.1 
            const spdu_type MAA_SPDU_ID = 42; //MAJOR SYNC ACK  *ref X225 8.3.23.1
            // PREPARE ,GIVE TOKENS, PLEASE TOKENS   

            // Resynchronize FU     
            const spdu_type RS_SPDU_ID = 53; //RESYNCHRONIZE MINOR  *ref X225 8.3.24.1    
            const spdu_type RA_SPDU_ID = 34; //RESYNCHRONIZE ACK   *ref X225 8.3.25.1
            // PREPARE 

            // Exceptions FU                 
            const spdu_type ER_SPDU_ID = 0; //EXCEPTION REPORT   *ref X225 8.3.27.1
            const spdu_type ED_SPDU_ID = 48; //EXCEPTION DATA  *ref X225 8.3.28.1

            // Activity management FU
            const spdu_type AS_SPDU_ID = 45; //ACTIVITY START   *ref X225 8.3.29.1
            const spdu_type AR_SPDU_ID = 29; //ACTIVITY RESUME  *ref X225 8.3.30.1       
            const spdu_type AI_SPDU_ID = 25; //ACTIVITY INTERRUPT  *ref X225 8.3.31.1               
            const spdu_type AIA_SPDU_ID = 26; //ACTIVITY INTERRUPT ACK  *ref X225 8.3.32.1 
            const spdu_type AD_SPDU_ID = 57; //ACTIVITY DISCARD   *ref X225 8.3.33.1
            const spdu_type ADA_SPDU_ID = 58; //ACTIVITY DISCARD ACK   *ref X225 8.3.34.1
            const spdu_type AE_SPDU_ID = 41; //ACTIVITY END   *ref X225 8.3.35.1
            const spdu_type AEA_SPDU_ID = 42; //ACTIVITY END ACK   *ref X225 8.3.36.1            
            const spdu_type GTC_SPDU_ID = 21; //GIVE TOKENS CONFIRM *ref X225 8.3.18.1
            const spdu_type GTA_SPDU_ID = 22; //GIVE TOKENS ACK *ref X225 8.3.19.1
            //GIVE TOKENS, PLEASE TOKENS, PREPARE   


            // PGI Connection Identifier *ref X225 Tab 11, 14, 15
            const varid_type PGI_CONN_ID = 1;
            // PGI Connect/Accept Item *ref X225 Tab 11, 14           
            const varid_type PGI_CONN_ACC = 5;
            // PGI Linking Information *ref X225 Tab 38
            const varid_type PGI_LINK_INF = 33;
            // PGI  User Data *ref X225 Tab 11 .. 46          
            const varid_type PGI_USERDATA = 193; // pi here
            // PGI  Extended User Data *ref X225 Tab 11           
            const varid_type PGI_EXUSERDATA = 194; // pi here  

            //  User data limitation  *ref X225 8.3.1.19
            const std::size_t SIMPLE_USERDATA_LIMIT = 512;
            const std::size_t EXTEDED_USERDATA_LIMIT = 10240;



            // PI Session User Requirements *ref X225 Tab 11, 14, 15
            const varid_type PI_SES_USERREQ = 20;

            //  Session User Requirements mask *ref X225 8.3.1.16 , 7.1.1 c), 7.4.1 d), 7.5.1 c)
            const int16_t FU_HALFDUPLEX = 0x1; //half-duplex FU            
            const int16_t FU_DUPLEX = 0x2; // duplex FU
            const int16_t FU_EXPDATA = 0x4; //expedited data FU            
            const int16_t FU_MINORSYNC = 0x8; // minor synchronize FU
            const int16_t FU_MAJORORSYNC = 0x10; //major synchronize FU         
            const int16_t FU_RESYNC = 0x20; // resynchronize FU;
            const int16_t FU_ACTIVEMG = 0x40; //activity management FU            
            const int16_t FU_NEGOTREL = 0x80; // negotiated release FU               
            const int16_t FU_CAPABDATA = 0x100; //capability data exchange FU
            const int16_t FU_EXCEPTION = 0x200; //exceptions FU 
            const int16_t FU_TYPEDDATA = 0x400; //typed data FU 
            const int16_t FU_SYMSYNC = 0x800; //symmetric synchronize FU  
            const int16_t FU_DATASEP = 0x1000; //data separation FU     

            const int16_t FU_WORK = FU_DUPLEX; // this implementation
            const int16_t FU_DEFAULT = FU_HALFDUPLEX | FU_MINORSYNC | FU_ACTIVEMG | FU_CAPABDATA | FU_EXCEPTION; //default *ref X225 8.3.1.16       


            // PI Version Number *ref X225 Tab 11, 12 , 14, 15
            const varid_type PI_VERSION = 22;

            // Version Number *ref X225 8.3.1.9 
            const octet_type VERSION1 = 1;
            const octet_type VERSION2 = 2;

            const octet_type WORK_PROT_VERSION = 3; // both version implemented here


            // PI Protocol Options Selector *ref X225 Tab 11 , 14 and 8.3.1.7            
            const varid_type PI_PROTOCOL_OPTION = 19;

            const octet_type NOEXTENDED_SPDU = 0;
            const octet_type EXTENDED_SPDU = 1;


            // PI Calling Session Selector *ref X225 Tab 11,  14  and 8.3.1.17
            const varid_type PI_CALLING = 51;


            // PI Called Session Selector *ref X225 Tab 11 and 8.3.1.18
            const varid_type PI_CALLED = 52;


            // PI TSDU Maximum Size *ref X225 Tab 11 , 14 and 8.3.1.8
            const varid_type PI_TSDUMAX = 21;


            // PI Data Overflow *ref X225 Tab 11 and 8.3.1.19
            const varid_type PI_DATAOVERFLOW = 60;


            // PI Enclosure Item *ref X225 Tab 13 .. 46 and 8.3.3.3            
            const varid_type PI_ENCLOSURE = 25;


            // PI Transport Disconnect *ref X225 Tab 15, 16, 19  and 8.3.5.6            
            const varid_type PI_TRANSPORT_DC = 17;

            // Transport Disconnect *ref X225 8.3.5.6             
            const octet_type KEEP_TRANSPORT = 0;
            const octet_type RELEASE_TRANSPORT = 1;


            // Refuse Reason Code *ref X225 Tab 15 and  8.3.5.10   
            const varid_type PI_REASON = 50;

            // see Disconnection  REASON CODE  iso.h






            const octet_type SEND_HEADERarr[] = {'\x1', '\x0', '\x1', '\x0'};
            const octet_sequnce SEND_HEADER = octet_sequnce(SEND_HEADERarr, SEND_HEADERarr + 4);

            const octet_type ECHO_NEGOTIATEarr[] = {'e', 'c', 'h', 'o', ':', ' '};
            const octet_sequnce ECHO_NEGOTIATE = octet_sequnce(ECHO_NEGOTIATEarr, ECHO_NEGOTIATEarr + 6);

            enum release_type {
                SESSION_FN_RELEASE = FN_SPDU_ID,
                SESSION_AB_RELEASE = AB_SPDU_ID
            };

            inline static spdu_type release_type_to_spdu(release_type vl) {
                return static_cast<spdu_type> (vl);
            }

            const std::size_t triple_npos = static_cast<std::size_t> (0xFFFF + 1);

            inline static octet_sequnce to_triple_size(std::size_t val) {
                if (val < 0xFF)
                    return inttype_to_raw(static_cast<uint8_t> (val));
                octet_sequnce rslt(1, '\xFF');
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(static_cast<uint16_t> (val))));
                return rslt;
            }

            inline static bool valid_triple_size(const octet_sequnce& val) {
                return !((val.empty()) || (val[0] == '\xFF' && val.size() < 3));
            }

            // return triple_npos if no success
            std::size_t from_triple_size(const octet_sequnce& val, std::size_t& it);


            typedef std::pair<varid_type, octet_sequnce> pi_type;
            typedef std::map<varid_type, octet_sequnce > pgi_type;
            typedef std::pair<varid_type, pgi_type> pgis_type;
            typedef std::map<varid_type, pgi_type> spdudata_type; // (it->first==0 contain pi_type in vector






            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   spdudata utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                 

            class spdudata {
                typedef boost::shared_ptr<spdudata_type> spdudata_type_ptr;

            public:

                spdudata() : value_(new spdudata_type()), type_(0), error_(false) {
                }

                explicit spdudata(spdu_type spdu) : value_(new spdudata_type()), type_(spdu), error_(false) {
                }

                explicit spdudata(const const_buffer& vl) : value_(new spdudata_type()), seq_(), type_(0), error_(false) {
                    parse_vars(buffer_to_raw(vl));
                }

                spdu_type type() const {
                    return type_;
                }

                bool error() const {
                    return error_;
                }

                void setPGI(varid_type cod1, varid_type cod2, const octet_sequnce& val = octet_sequnce());

                void setPGI(varid_type cod1, varid_type cod2, int8_t val);

                void setPGI(varid_type cod1, varid_type cod2, uint8_t val);

                void setPGI(varid_type cod1, varid_type cod2, int16_t val);

                void setPGI(varid_type cod1, varid_type cod2, uint16_t val);


                void setPI(varid_type cod, const octet_sequnce& val = octet_sequnce());

                void setPI(varid_type cod, int8_t val);

                void setPI(varid_type cod, uint8_t val);

                void setPI(varid_type cod, int16_t val);

                void setPI(varid_type cod, uint16_t val);


                const octet_sequnce& getPGI(varid_type cod1, varid_type cod2) const;

                bool getPGI(varid_type cod1, varid_type cod2, int8_t& val, int8_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, uint8_t& val, uint8_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, int16_t& val, int16_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, uint16_t& val, uint16_t def = 0) const;

                const octet_sequnce& getPI(varid_type cod) const;

                bool getPI(varid_type cod, int8_t& val, int8_t def = 0) const;

                bool getPI(varid_type cod, uint8_t& val, uint8_t def = 0) const;

                bool getPI(varid_type cod, int16_t& val, int16_t def = 0) const;

                bool getPI(varid_type cod, uint16_t& val, uint16_t def = 0) const;


                bool existPGI(varid_type cod1, varid_type cod2) const;

                bool existPI(varid_type cod) const;

                bool nullPGI(varid_type cod1, varid_type cod2) const;

                bool nullPI(varid_type cod) const;

                const_sequences_ptr sequence(asn_coder_ptr seq) const;

            private:

                bool error(bool val) {
                    return error_ = val;
                }

                bool parse();
                bool parse_vars(const octet_sequnce& vl);
                bool parse_pgi(varid_type tp, const octet_sequnce& vl);

                mutable octet_sequnce seq_;
                spdu_type type_;
                bool error_;
                octet_sequnce null_val;
                spdudata_type_ptr value_;
            };




            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   protocol_options   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

            struct protocol_options {
                typedef boost::shared_ptr<spdudata> spdudata_ptr;

                protocol_options() : vars_(new spdudata()) {
                }

                protocol_options(const const_buffer & vl) : vars_(new spdudata(vl)) {
                }

                protocol_options(const octet_sequnce& called, const octet_sequnce& calling = octet_sequnce());

                protocol_options(const session_selector & ssel);

                const octet_sequnce & ssap_calling() const;

                void ssap_calling(const octet_sequnce & val);

                const octet_sequnce & ssap_called() const;

                void ssap_called(const octet_sequnce & val);

                const octet_sequnce & data() const;

                octet_type accept_version() const;

                void accept_version(octet_type vl);

                octet_type reject_version() const;

                void reject_version(octet_type vl);

                int16_t user_requirement() const;

                void user_requirement(int16_t vl);

                bool extendedSPDU() const;

                void extendedSPDU(bool vl);

                bool beginSPDU() const;

                bool endSPDU() const;

                void endSPDU(bool end = true, bool beg = true);

                bool overflow() const;

                void overflow(bool val);

                void refuse_reason(octet_type rsn, const octet_sequnce& val = octet_sequnce());

                octet_type refuse_reason() const;

                uint16_t maxTPDU_self() const;

                uint16_t maxTPDU_dist() const;

                void maxTPDU(uint16_t self, uint16_t dist);

            private:
                spdudata_ptr vars_;
            };

            const protocol_options NULL_PROTOCOL_OPTION = protocol_options();

#if defined(ITUX200_DEBUG) 

            inline static std::ostream& operator<<(std::ostream& stream, const protocol_options& self) {
                octet_sequnce calling = self.ssap_calling();
                octet_sequnce called = self.ssap_called();
                return stream << "session option  " << "\n" <<
                        "  userReq = " << self.user_requirement() << "\n" <<
                        "  calling = " << std::string(calling.begin(), calling.end()) << "\n" <<
                        "  called = " << std::string(called.begin(), called.end()) << " \n" <<
                        "  extendedSPDU = " << (self.extendedSPDU() ? "yes" : "no") << "\n" <<
                        "  maxspdu_self = " << self.maxTPDU_self() << "\n" <<
                        "  maxspdu_dist = " << self.maxTPDU_dist() << "\n" << "\n";
            }
#endif           



            //negotiate_x225impl_option
            bool negotiate_x225impl_option(protocol_options& self, const protocol_options& dist);

            const_sequences_ptr generate_header_CN(const protocol_options& opt, asn_coder_ptr data); //CONNECT SPDU

            const_sequences_ptr generate_header_AC(const protocol_options& opt, asn_coder_ptr data); //ACCEPT SPDU

            const_sequences_ptr generate_header_RF(const protocol_options& opt, asn_coder_ptr data); //REFUSE  SPDU        

            const_sequences_ptr generate_header_FN(const protocol_options& opt, asn_coder_ptr data); //FINISH SPDU            

            const_sequences_ptr generate_header_DN(const protocol_options& opt, asn_coder_ptr data); //DISCONNECT  SPDU          

            const_sequences_ptr generate_header_AB(const protocol_options& opt, asn_coder_ptr data); //ABORT SPDU                     

            const_sequences_ptr generate_header_AA(const protocol_options& opt, asn_coder_ptr data); //ABORT ACCEPT  SPDU                              

            const_sequences_ptr generate_header_NF(const protocol_options& opt, asn_coder_ptr data); //NOT FINISH  SPDU                      





            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   data_sender_sequences    //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////           

            template <typename ConstBufferSequence>
            class data_sender_sequences : public basic_sender_sequences {
            public:

                data_sender_sequences(const ConstBufferSequence& bf) : basic_sender_sequences() {
                    construct(bf);
                }

                void construct(const ConstBufferSequence& bf) {

                    typename ConstBufferSequence::const_iterator it = bf.begin();
                    typename ConstBufferSequence::const_iterator end = bf.end();
                    typename ConstBufferSequence::value_type val;

                    buff().push_back(const_buffer(&SEND_HEADER[0], SEND_HEADER.size()));

                    while (it != end) {
                        buff().push_back(const_buffer(*it));
                        it++;
                    }

                }

            };


            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  optimized data_sender_sequences    //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////               

            template<>
            class data_sender_sequences<const_sequences> : public basic_sender_sequences {
            public:

                data_sender_sequences<const_sequences>(const const_sequences& bf) :
                basic_sender_sequences(const_cast<const_sequences&> (bf)) {
                    construct();
                }

                void construct() {
                    buff().insert(buff().begin(), const_buffer(&SEND_HEADER[0], SEND_HEADER.size()));
                }

            };



            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   x225 sender  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////              

            class sender {
            public:

                sender(spdu_type type) : type_(type) {

                }

                sender(spdu_type type, const protocol_options& opt, asn_coder_ptr data) :
                type_(type) {
                    switch (type) {
                        case CN_SPDU_ID:
                        {
                            constructCN(opt, data);
                            break;
                        }
                        case AC_SPDU_ID:
                        {
                            constructAC(opt, data);
                            break;
                        }
                        case RF_SPDU_ID:
                        {
                            constructRF(opt, data);
                            break;
                        }
                        case FN_SPDU_ID:
                        {
                            constructFN(opt, data);
                            break;
                        }
                        case AB_SPDU_ID:
                        {
                            constructAB(opt, data);
                            break;
                        }
                        case DN_SPDU_ID:
                        {
                            constructDN(opt, data);
                            break;
                        }
                        case AA_SPDU_ID:
                        {
                            constructAA(opt, data);
                            break;
                        }
                        default:
                        {
                        }
                    }
                }

                virtual ~sender() {
                }

                bool ready() const {
                    return (!buf_) || (buf_->ready());
                }

                const const_sequences& pop() {
                    return buf_ ? buf_->pop() : NULL_CONST_SEQUENCE;
                }

                std::size_t size(std::size_t sz) {
                    return ready() ? 0 : buf_->size(sz);
                }

                std::size_t receive_size() const {
                    return ready() ? 0 : buf_->receive_size();
                }

                spdu_type type() const {
                    return type_;
                }




            protected:

                void constructCN(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_CN(opt, data)));
                }

                void constructAC(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_AC(opt, data)));
                }

                void constructRF(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_RF(opt, data)));
                }

                void constructFN(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_FN(opt, data)));
                }

                void constructAB(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_AB(opt, data)));
                }

                void constructDN(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_DN(opt, data)));
                }

                void constructAA(const protocol_options& opt, asn_coder_ptr data) {
                    buf_ = sender_sequnces_ptr(new basic_sender_sequences(generate_header_AA(opt, data)));
                }

                spdu_type type_;
                sender_sequnces_ptr buf_;
            };








            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   x225 data_sender  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

            template <typename ConstBufferSequence >
            class data_sender : public sender {
            public:

                data_sender(const ConstBufferSequence& buff) : sender(DN_SPDU_ID) {
                    constructDT(buff);
                }

            protected:

                void constructDT(const ConstBufferSequence& buff) {
                    buf_ = sender_sequnces_ptr(new data_sender_sequences<ConstBufferSequence > (buff));
                }

            };





            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   x225 receiver  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

            const std::size_t SI_WITH_LI = 2;
            const std::size_t HDR_LI = 2;

            class receiver {
            public:

                typedef boost::shared_ptr< protocol_options > protocol_options_ptr;

                enum operation_state {
                    waittype,
                    waitsize,
                    waitheader,
                    waitdata,
                    complete,
                    error
                };

                receiver(const mutable_buffer& buff);

                receiver();

                mutable_buffer buffer();

                void put(std::size_t sz);

                bool ready() const {
                    return (state_ == error || state_ == complete);
                }

                operation_state state() const {
                    return state_;
                }

                spdu_type type() const {
                    return type_;
                }

                std::size_t datasize() const {
                    return datasize_;
                }

                octet_type class_option() const {
                    return class_option_;
                }

                octet_type reject_reason() const {
                    return reject_reason_;
                }

                const protocol_options& options() const {
                    return options_;
                }

                error_code errcode() const {
                    return errcode_;
                }


            private:

                operation_state state(operation_state val);

                error_code errcode(const error_code& err);

                void reject_reason(octet_type val);

                error_code check_type();

                error_code check_size();

                error_code check_header();



                operation_state state_;
                std::size_t size_;
                std::size_t estimatesize_;
                std::size_t datasize_;
                spdu_type type_;
                bool first_in_seq_;
                octet_type class_option_;
                octet_type reject_reason_;
                protocol_options options_;
                error_code errcode_;


                octet_sequnce_ptr type_data;
                mutable_buffer type_buff_;
                octet_sequnce_ptr header_data;
                mutable_buffer header_buff_;
                mutable_buffer userbuff_;
            };













            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  x225 stream_socket  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

            class stream_socket : protected boost::itu::rfc1006::socket {
                typedef boost::itu::rfc1006::socket super_type;
                typedef boost::itu::asn_coder_templ<> default_coder_type;

                typedef boost::shared_ptr<receiver> receiver_ptr;
                typedef boost::shared_ptr<sender> sender_ptr;

                friend class socket_acceptor;

            public:

                typedef super_type::protocol_type protocol_type;
                typedef super_type::lowest_layer_type lowest_layer_type;
                typedef super_type::native_handle_type native_handle_type;
                typedef super_type::native_type native_type;
                typedef super_type::message_flags message_flags;
                typedef super_type::endpoint_type endpoint_type;
                typedef super_type::service_type service_type;
                typedef super_type::shutdown_type shutdown_type;
                typedef super_type::implementation_type implementation_type;


                using super_type::assign;
                using super_type::at_mark;
                using super_type::available;
                using super_type::bind;
                using super_type::cancel;
                using super_type::close;
                using super_type::get_io_service;
                using super_type::get_option;
                using super_type::io_control;
                using super_type::is_open;
                using super_type::lowest_layer;
                using super_type::native;
                using super_type::native_handle;
                using super_type::native_non_blocking;
                using super_type::non_blocking;
                using super_type::open;
                using super_type::remote_endpoint;
                using super_type::set_option;
                using super_type::shutdown;

                using super_type::ready;
                using super_type::is_acceptor;


            protected:


                using super_type::get_service;
                using super_type::get_implementation;

            public:



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                explicit stream_socket(boost::asio::io_service& io_service, const session_selector& ssel = session_selector(), asn_coder_ptr coder = asn_coder_ptr(new default_coder_type()))
                : boost::itu::rfc1006::socket(io_service, ssel.tselector()), option_(ssel.called(), ssel.calling()), rootcoder_(coder), session_version_(VERSION2) {
                }

                stream_socket(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const session_selector& ssel = session_selector(), asn_coder_ptr coder = asn_coder_ptr(new default_coder_type()))
                : boost::itu::rfc1006::socket(io_service, ssel.tselector()), option_(ssel.called(), ssel.calling()), rootcoder_(coder), session_version_(VERSION2) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Connnect operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void connect(const endpoint_type& peer_endpoint) {
                    error_code ec;
                    connect(peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "connect");
                }

                error_code connect(const endpoint_type& peer_endpoint,
                        error_code& ec) {
                    rootcoder()->in()->clear();
                    return connect_impl(peer_endpoint, ec);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ConnectHandler>
                class connect_operation {
                    typedef connect_operation <ConnectHandler> operation_type;

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    connect_operation(stream_socket& sock, ConnectHandler handlr) :
                    socket(sock),
                    handler(handlr),
                    state_(request),
                    sender_(sender_ptr(new sender(CN_SPDU_ID, sock.session_option(), sock.rootcoder()))),
                    receiver_(new receiver()) {

                    }

                    void start(const error_code& ec) {
                        if (!ec)
                            execute(ec, 0);
                        else
                            exit_handler(ec);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, * this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    else {
                                        state(response);
                                        execute(ec, 0);
                                        return;
                                    }
                                }
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), 0,
                                                boost::bind(&operation_type::execute, * this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                            }
                        }
                        exit_handler(ec);
                    }

                private:

                    void finish(const error_code& ec) {
                        if (receiver_->state() == receiver::complete) {
                            switch (receiver_->type()) {
                                case AC_SPDU_ID:
                                {
                                    socket.negotiate_session_option(receiver_->options());
                                    socket.rootcoder()->in()->add(receiver_->options().data());
                                    socket.session_version_ = (receiver_->options().accept_version() & VERSION2) ? VERSION2 : VERSION1;
#if defined(ITUX200_DEBUG) 
                                    std::cout << "SESSION SUCCESS CONNECT " << (socket.is_acceptor() ? " It is acceptor" : " It is requester") << "\n" <<
                                            " with" << socket.session_option() << std::endl;
#endif                                                                
                                    exit_handler(ec);
                                    return;
                                }
                                case RF_SPDU_ID:
                                {
                                    error_code ecc;
                                    //socket.close(ecc);
                                    exit_handler(ER_REFUSE);
                                    return;
                                }
                                default:
                                {
                                    error_code ecc;
                                    //socket.close(ecc);
                                }
                            }
                        }
                        exit_handler(ER_PROTOCOL);
                    }

                    void exit_handler(const error_code& ec) {
                        socket.rootcoder()->out()->clear();
                        handler(ec);
                    }

                    void state(stateconnection st) {
                        if (state_ != st)
                            state_ = st;
                    }

                    stream_socket& socket;
                    ConnectHandler handler;
                    stateconnection state_;
                    sender_ptr sender_;
                    receiver_ptr receiver_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ConnectHandler>
                void async_connect(const endpoint_type& peer_endpoint,
                        BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {

                    BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

                    typedef connect_operation<ConnectHandler> connect_operation_type;

                    rootcoder()->in()->clear();
                    super_type::async_connect(peer_endpoint, boost::bind(&connect_operation_type::start,
                            connect_operation_type(*this, handler), boost::asio::placeholders::error));
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Release operation  //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

                void release() {

                    error_code ec;
                    release(ec);
                    boost::asio::detail::throw_error(ec, "release");
                }

                error_code release(error_code& ec) {
                    rootcoder()->in()->clear();
                    return release_impl(SESSION_FN_RELEASE, ec);
                }

                void abort() {

                    error_code ec;
                    release(ec);
                    boost::asio::detail::throw_error(ec, "abort");
                }

                error_code abort(error_code& ec) {
                    rootcoder()->in()->clear();
                    return release_impl(SESSION_AB_RELEASE, ec);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            private:

                template <typename ReleaseHandler>
                class release_operation {
                    typedef release_operation<ReleaseHandler> operation_type;

                    enum stateconnection {
                        request,
                        response,
                        transportdisconnect
                    };

                public:

                    release_operation(stream_socket& sock, ReleaseHandler handlr, release_type type) :
                    socket(sock),
                    handler(handlr),
                    sender_(sender_ptr(new sender(release_type_to_spdu(type), sock.session_option(), sock.rootcoder()))),
                    receiver_(new receiver()),
                    type_(type),
                    state_(request) {
                    }

                    void start() {
                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, * this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    state(response);
                                    execute(ec, 0);
                                    return;
                                }
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), 0,
                                                boost::bind(&operation_type::execute, * this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case transportdisconnect:
                                {
                                    socket.super_type::async_release(
                                            boost::bind(&operation_type::disconnect, * this,
                                            boost::asio::placeholders::error));
                                    return;
                                }
                            }

                        }
                        exit_handler(ec);
                    }

                    void disconnect(const error_code& ec) {
                        exit_handler(ec);
                    }


                private:

                    void finish(const error_code& ec) {
                        if (receiver_->state() == receiver::complete) {
                            switch (receiver_->type()) {
                                case DN_SPDU_ID:
                                {
                                    socket.rootcoder()->in()->add(receiver_->options().data());
                                    state(transportdisconnect);
                                    start();
                                    return;
                                }
                                case AA_SPDU_ID:
                                {
                                    socket.rootcoder()->in()->add(receiver_->options().data());
                                    state(transportdisconnect);
                                    start();
                                    return;
                                }
                                default:
                                {
                                }
                            }
                        }
                        error_code ecc;
                        //socket.close(ecc);
                        exit_handler(ER_PROTOCOL);
                    }

                    void exit_handler(const error_code& ec) {
                        //socket.rootcoder()->out()->clear();
                        handler(ec);
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket& socket;
                    ReleaseHandler handler;
                    sender_ptr sender_;
                    receiver_ptr receiver_;
                    release_type type_;
                    stateconnection state_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                   


            public:

                template <typename ReleaseHandler>
                void async_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler) {

                    typedef release_operation<ReleaseHandler > release_operation_type;

                    rootcoder()->in()->clear();
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_operation_type::start,
                                release_operation<ReleaseHandler > (*this, handler, SESSION_FN_RELEASE)));
                    }
                    else
                        handler(ER_REFUSE);
                }

                template <typename ReleaseHandler>
                void async_abort(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler) {

                    typedef release_operation<ReleaseHandler > release_operation_type;

                    rootcoder()->in()->clear();
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_operation_type::start,
                                release_operation_type(*this, handler, SESSION_AB_RELEASE)));
                    }
                    else
                        handler(ER_REFUSE);
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

            protected:

                void check_accept() {

                    error_code ec;
                    check_accept(ec);
                    boost::asio::detail::throw_error(ec, "connect");
                }

                error_code check_accept(error_code& ec) {

                    rootcoder()->in()->clear();
                    return check_accept_imp(ec);
                }


            private:

                template <typename CheckAcceptHandler>
                class check_accept_operation {
                    typedef check_accept_operation<CheckAcceptHandler> operation_type;

                    enum stateconnection {
                        response,
                        request,
                        refuse
                    };

                public:

                    check_accept_operation(stream_socket& sock, CheckAcceptHandler handlr) :
                    socket(sock),
                    handler(handlr),
                    state_(response),
                    sender_(),
                    receiver_(new receiver()) {
                    }

                    void start() {

                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case response:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    parse_response(ec);
                                    return;
                                }
                                case request:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case refuse:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    exit_handler(ER_OUTDOMAIN);
                                    return;
                                }
                            }
                        }
                        exit_handler(ec);
                    }




                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   


                private:

                    void parse_response(const error_code& ec) {
                        if (receiver_->type() != CN_SPDU_ID || receiver_->state() != receiver::complete) {
                            exit_handler(ER_PROTOCOL);
                            return;
                        }
                        bool nouserreject = true;
                        protocol_options options_ = socket.session_option();
                        socket.rootcoder()->in()->add(receiver_->options().data());
                        if (!negotiate_x225impl_option(options_, receiver_->options()) ||
                                !(nouserreject = socket.negotiate_session_accept())) {
                            if (!nouserreject)
                                options_.refuse_reason(DR_REASON_USER);
                            sender_ = sender_ptr(new sender(RF_SPDU_ID, options_, socket.rootcoder()));
                            state(refuse);
                            execute(ec, 0);
                            return;
                        }
#if defined(ITUX200_DEBUG) 
                        std::cout << "SESSION SUCCESS CONNECT " << (socket.is_acceptor() ? " It is acceptor" : " It is requester") << "\n" <<
                                " with" << socket.session_option() << std::endl;
#endif                           
                        socket.session_version_ = (options_.accept_version() & VERSION2) ? VERSION2 : VERSION1;
                        sender_ = sender_ptr(new sender(AC_SPDU_ID, options_, socket.rootcoder()));
                        state(request);
                        execute(ec, 0);
                    }

                    void finish(const error_code& ec) {

                        const protocol_options& opt = receiver_->options();
                        socket.negotiate_session_option(opt);
                        exit_handler(ec);
                    }

                    void exit_handler(const error_code& ec) {
                        socket.rootcoder()->out()->clear();
                        handler(ec);
                    }

                    void state(stateconnection st) {

                        if (state_ != st)
                            state_ = st;
                    }



                    stream_socket& socket;
                    CheckAcceptHandler handler;
                    stateconnection state_;
                    sender_ptr sender_;
                    receiver_ptr receiver_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

            protected:

                template <typename CheckAcceptHandler>
                void async_check_accept(BOOST_ASIO_MOVE_ARG(CheckAcceptHandler) handler) {

                    typedef check_accept_operation<CheckAcceptHandler > check_accept_operation_type;

                    rootcoder()->in()->clear();
                    get_io_service().post(boost::bind(&check_accept_operation_type::start,
                            check_accept_operation_type(*this, handler)));
                }








                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Send operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       

            public:

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers) {

                    return send(buffers, 0);
                }

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers,
                        message_flags flags) {
                    error_code ec;
                    std::size_t s = send(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "send");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers) {
                    error_code ec;
                    std::size_t s = send(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "write_some");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers,
                        error_code& ec) {

                    return send(buffers, 0, ec);
                }

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    return send_impl(buffers, flags, ec);
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

            private:

                template <typename SendHandler, typename ConstBufferSequence>
                class send_operation {
                    typedef send_operation<SendHandler, ConstBufferSequence> operation_type;

                public:

                    send_operation(stream_socket& sock, SendHandler handlr,
                            const ConstBufferSequence& buffers, message_flags flags) :
                    socket(sock),
                    handler(handlr),
                    sender_(sender_ptr(new data_sender<ConstBufferSequence>(buffers))),
                    flags_(flags),
                    send_lower_(boost::asio::buffer_size(buffers)) {
                    }

                    void start() {

                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            sender_->size(bytes_transferred);
                            if (!sender_->ready()) {
                                socket.super_type::async_send(sender_->pop(), flags_,
                                        boost::bind(&operation_type::execute, *this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));
                                return;
                            }
                        }
                        handler(ec, ec ? 0 : static_cast<std::size_t> (send_lower_));
                    }


                private:

                    stream_socket& socket;
                    SendHandler handler;
                    sender_ptr sender_;
                    message_flags flags_;
                    std::size_t send_lower_;


                };




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       


            public:

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send(buffers, 0, handler);
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_write_some(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_send(const ConstBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

                    typedef send_operation<WriteHandler, ConstBufferSequence> send_operation_type;

                    get_io_service().post(boost::bind(&send_operation_type::start,
                            send_operation_type(*this, handler, buffers, flags)));
                }









                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Receive  operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers) {
                    return receive<MutableBufferSequence > (buffers, 0);
                }

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers,
                        message_flags flags) {
                    error_code ec;
                    std::size_t s = receive(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "receive");
                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers,
                        error_code& ec) {

                    return receive(buffers, 0, ec);
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers) {
                    error_code ec;
                    std::size_t s = receive(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "read_some");

                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    return receive_impl(buffers, flags, ec);
                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            private:

                template <typename ReceiveHandler, typename Mutable_Buffers>
                class receive_operation {
                    typedef receive_operation<ReceiveHandler, Mutable_Buffers> operation_type;

                    enum stateconnection {
                        request,
                        response,
                        trasportdisconnect
                    };



                public:

                    receive_operation(stream_socket& sock, ReceiveHandler handlr,
                            receiver_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket(sock),
                    handler(handlr),
                    receiver_(receive),
                    buff_(buff),
                    sender_(),
                    state_(request),
                    flags_(flags) {
                    }

                    void start() {
                        error_code ec;
                        execute(ec, 0);
                    }

                    void execute(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    receiver_->put(bytes_transferred);
                                    if (!receiver_->ready()) {
                                        socket.super_type::async_receive(boost::asio::buffer(receiver_->buffer()), flags_,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    if (!success()) return;
                                    break;
                                }
                                case response:
                                {
                                    sender_->size(bytes_transferred);
                                    if (!sender_->ready()) {
                                        socket.super_type::async_send(sender_->pop(), 0,
                                                boost::bind(&operation_type::execute, *this,
                                                boost::asio::placeholders::error,
                                                boost::asio::placeholders::bytes_transferred));
                                        return;
                                    }
                                    state(trasportdisconnect);
                                    start();
                                    return;
                                }
                                case trasportdisconnect:
                                {
                                    socket.super_type::async_release(
                                            boost::bind(&operation_type::disconnect, * this,
                                            boost::asio::placeholders::error));
                                    return;
                                }
                            }
                        }
                        handler(ec, ec ? 0 : static_cast<std::size_t> (receiver_->datasize()));
                    }

                    void disconnect(const error_code& ec) {
                        handler(ER_REFUSE, 0);
                    }


                private:

                    bool success() {
                        switch (receiver_->type()) {
                            case DT_SPDU_ID:
                            {
                                return true;
                            }
                            case FN_SPDU_ID:
                            {
                                socket.rootcoder()->in()->clear();
                                socket.rootcoder()->in()->add(receiver_->options().data());
                                socket.negotiate_session_release();
                                sender_ = sender_ptr(new sender(DN_SPDU_ID, socket.session_option(), socket.rootcoder()));
                                state(response);
                                start();
                                return false;
                            }
                            case AB_SPDU_ID:
                            {
                                socket.rootcoder()->in()->clear();
                                //socket.rootcoder()->in()->add(receiver_->options().data());
                                socket.negotiate_session_abort();
                                state(trasportdisconnect);
                                start();
                                return false;
                            }
                            default:
                            {
                                socket.rootcoder()->in()->clear();
                                socket.rootcoder()->in()->add(receiver_->options().data());
                                sender_ = sender_ptr(new sender(AB_SPDU_ID, socket.session_option(), socket.rootcoder()));
                                state(response);
                                start();
                            }
                        }

                        return false;
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket& socket;
                    ReceiveHandler handler;
                    const Mutable_Buffers& buff_;
                    receiver_ptr receiver_;
                    sender_ptr sender_;
                    stateconnection state_;
                    message_flags flags_;
                };





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            public:

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_receive(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, handler, 0);
                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_read_some(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_receive(const MutableBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;


                    if (ready()) {

                        typedef receive_operation<ReadHandler, MutableBufferSequence> receive_operation_type;
                        typedef boost::asio::detail::buffer_sequence_adapter< mutable_buffer, MutableBufferSequence> sequence_adapter_type;

                        get_io_service().post(boost::bind(&receive_operation_type::start, receive_operation_type(*this, handler,
                                receiver_ptr(new receiver(sequence_adapter_type::first(buffers))), buffers, flags)));
                    }
                    else
                        super_type::async_receive(buffers, flags, handler);

                }

                asn_coder_ptr rootcoder() {
                    return rootcoder_;
                }

                asn_coder_ptr rootcoder() const {
                    return rootcoder_;
                }

                octet_type session_version() const {
                    return session_version_;
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  protected member  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            protected:

                virtual bool negotiate_session_accept() {
                    rootcoder()->out()->clear();
                    rootcoder()->out()->add(ECHO_NEGOTIATE);
                    rootcoder()->out()->add(rootcoder()->in()->buffers());
                    return true;
                }

                virtual bool negotiate_session_release() {
                    rootcoder()->out()->clear();
                    rootcoder()->out()->add(ECHO_NEGOTIATE);
                    rootcoder()->out()->add(rootcoder()->in()->buffers());
                    return true;
                }

                virtual bool negotiate_session_abort() {
                    return true;
                }

                void session_option(const session_selector& ssel) {
                    option_ = protocol_options(ssel);
                }

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  private member  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                       

            private:

                const protocol_options& session_option() const {
                    return option_;
                }

                void negotiate_session_option(const protocol_options& val) {

                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  private implementator  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    

                error_code connect_impl(const endpoint_type& peer_endpoint,
                        error_code& ec) {
                    if (super_type::connect(peer_endpoint, ec))
                        return connect_impl_exit(ec);

                    sender_ptr sender_(sender_ptr(new sender(CN_SPDU_ID, session_option(), rootcoder())));
                    while (!ec && !sender_->ready())
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
                    if (ec)
                        return connect_impl_exit(ec);
                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
                    }
                    if (ec)
                        return connect_impl_exit(ec);
                    if (receiver_->state() == receiver::complete) {
                        switch (receiver_->type()) {
                            case AC_SPDU_ID:
                            {
                                negotiate_session_option(receiver_->options());
                                rootcoder()->in()->add(receiver_->options().data());
                                session_version_ = (receiver_->options().accept_version() & VERSION2) ? VERSION2 : VERSION1;
                                return connect_impl_exit(ec);
                            }
                            case RF_SPDU_ID:
                            {
                                error_code ecc;
                                //close(ecc);
                                return connect_impl_exit(ER_REFUSE);
                            }
                            default:
                            {
                            }
                        }
                    }
                    return connect_impl_exit(ec = ER_PROTOCOL);
                }

                const error_code& connect_impl_exit(const error_code& err) {
                    rootcoder()->out()->clear();
                    return err;
                }

                error_code release_impl(release_type type, error_code& ec) {
                    if (is_open()) {
                        sender_ptr sender_(new sender(release_type_to_spdu(type), session_option(), rootcoder()));
                        while (!ec && !sender_->ready())
                            sender_->size(super_type::send(sender_->pop(), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        receiver_ptr receiver_(receiver_ptr(new receiver()));
                        while (!ec && !receiver_->ready())
                            receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        if (receiver_->state() == receiver::complete) {
                            switch (receiver_->type()) {
                                case DN_SPDU_ID:
                                {
                                    rootcoder()->in()->add(receiver_->options().data());
                                    error_code ecc;
                                    //close(ecc);
                                    return release_impl_exit(ec);
                                }
                                case AA_SPDU_ID:
                                {
                                    rootcoder()->in()->add(receiver_->options().data());
                                    error_code ecc;
                                    //close(ecc);
                                    return release_impl_exit(ec);
                                }
                                default:
                                {
                                }
                            }
                        }
                        error_code ecc;
                        //close(ecc);
                    }
                    return release_impl_exit(ec = ER_REFUSE);
                }

                const error_code& release_impl_exit(const error_code& err) {
                    rootcoder()->out()->clear();
                    return err;
                }

                error_code check_accept_imp(error_code& ec) {
                    bool canseled = false;
                    receiver_ptr receiver_(receiver_ptr(new receiver()));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
                    }
                    if (ec)
                        return check_accept_imp_exit(ec);
                    sender_ptr sender_;

                    protocol_options options_ = session_option();
                    if (receiver_->type() != CN_SPDU_ID || receiver_->state() != receiver::complete) {
                        error_code ecc;
                        //close(ecc);
                        return check_accept_imp_exit(ER_PROTOCOL);
                    }
                    bool nouserreject = true;
                    rootcoder()->in()->add(receiver_->options().data());
                    if (!negotiate_x225impl_option(options_, receiver_->options()) ||
                            !(nouserreject = negotiate_session_accept())) {
                        if (!nouserreject)
                            options_.refuse_reason(DR_REASON_USER);
                        canseled = true;
                        sender_ = sender_ptr(new sender(RF_SPDU_ID, options_, rootcoder()));
                    }
                    else {
                        session_version_ = (options_.accept_version() & VERSION2) ? VERSION2 : VERSION1;
                        sender_ = sender_ptr(new sender(AC_SPDU_ID, options_, rootcoder()));
                    }

                    while (!ec && !sender_->ready())
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
                    if (ec)
                        return check_accept_imp_exit(ec);
                    if (canseled) {
                        error_code ecc;
                        //close(ecc);
                    }
                    else {
                        const protocol_options& opt = receiver_->options();
                        negotiate_session_option(receiver_->options());
                    }
                    return check_accept_imp_exit(ec = canseled ? ER_OUTDOMAIN : ec);
                }

                const error_code& check_accept_imp_exit(const error_code& err) {
                    rootcoder()->out()->clear();
                    return err;
                }

                template <typename ConstBufferSequence>
                std::size_t send_impl(const ConstBufferSequence& buffers,
                        message_flags flags, error_code& ec) {
                    sender_ptr sender_(new data_sender<ConstBufferSequence > (buffers));
                    while (!ec && !sender_->ready())
                        sender_->size(super_type::send(sender_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    if (!ready())
                        return super_type::receive(boost::asio::buffer(buffers), flags, ec);

                    receiver_ptr receiver_(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers)));
                    while (!ec && !receiver_->ready()) {
                        receiver_->put(super_type::receive(boost::asio::buffer(receiver_->buffer()), 0, ec));
                    }
                    if (ec)
                        return 0;
                    switch (receiver_->type()) {
                        case DT_SPDU_ID:
                        {
                            return receiver_->datasize();
                        }
                        case FN_SPDU_ID:
                        {
                            rootcoder()->in()->clear();
                            rootcoder()->in()->add(receiver_->options().data());
                            negotiate_session_release();
                            sender_ptr sender_ = sender_ptr(new sender(DN_SPDU_ID, session_option(), rootcoder()));
                            while (!ec && !sender_->ready())
                                sender_->size(super_type::send(sender_->pop(), 0, ec));
                            error_code ecc;
                            close(ecc);
                            ec = ER_RELEASE;
                            return 0;
                        }
                        case AB_SPDU_ID:
                        {
                            rootcoder()->in()->clear();
                            negotiate_session_abort();
                            error_code ecc;
                            super_type::release(ecc);
                            ec = ER_ABORT;
                            return 0;
                        }
                        default:
                        {
                            /*if (sender_) {
                                while (!ec && !sender_->ready())
                                    sender_->size(super_type::send(sender_->pop(), 0, ec));
                                ec = ER_REFUSE;
                                error_code ecc;
                                super_type::release(ecc);
                                return 0;

                            }*/
                        }
                    }
                    error_code ecc;
                    //close(ecc);
                    ec = ER_PROTOCOL;
                    return 0;
                }

                protocol_options option_;
                asn_coder_ptr rootcoder_;
                octet_type session_version_;

            };






            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  x225 socket_acceptor_service //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            class socket_acceptor : protected boost::itu::rfc1006impl::socket_acceptor {
                typedef boost::itu::rfc1006impl::socket_acceptor super_type;

                friend class stream_socket;

            public:

                typedef super_type::protocol_type protocol_type;
                typedef super_type::endpoint_type endpoint_type;
                typedef super_type::implementation_type implementation_type;
                typedef super_type::service_type service_type;
                typedef super_type::message_flags message_flags;
                typedef super_type::native_handle_type native_handle_type;
                typedef super_type::native_type native_type;

                using super_type::assign;
                using super_type::bind;
                using super_type::cancel;
                using super_type::close;
                using super_type::get_io_service;
                using super_type::get_option;
                using super_type::io_control;
                using super_type::is_open;
                using super_type::listen;
                using super_type::local_endpoint;
                using super_type::native;
                using super_type::native_handle;
                using super_type::native_non_blocking;
                using super_type::non_blocking;
                using super_type::open;
                using super_type::set_option;


            protected:

                using super_type::get_service;
                using super_type::get_implementation;


            public:

                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                

                explicit socket_acceptor(boost::asio::io_service& io_service, const session_selector& ssel = session_selector())
                : boost::itu::rfc1006impl::socket_acceptor(io_service, ssel.tselector()), session_selector_(ssel) {
                }

                socket_acceptor(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const session_selector& ssel = session_selector(), bool reuse_addr = true)
                : boost::itu::rfc1006impl::socket_acceptor(io_service, endpoint, ssel.tselector(), reuse_addr), session_selector_(ssel) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

                void accept(stream_socket& peer) {
                    error_code ec;
                    accept_impl(peer, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                error_code accept(
                        stream_socket& peer,
                        error_code& ec) {
                    return accept_impl(peer, ec);
                }

                void accept(stream_socket& peer,
                        endpoint_type& peer_endpoint) {
                    error_code ec;
                    accept_impl(peer, peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                error_code accept(
                        stream_socket & peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    return accept_impl(peer, peer_endpoint, ec);
                }

                template <typename AcceptHandler>
                void async_accept(stream_socket& peer,
                        endpoint_type& peer_endpoint,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    async_accept_impl(peer, peer_endpoint, handler);
                }

                template <typename AcceptHandler>
                void async_accept(stream_socket& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    async_accept_impl(peer, handler);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            private:

                template <typename AcceptHandler>
                class accept_operation {
                    typedef accept_operation<AcceptHandler> operation_type;

                public:

                    accept_operation(AcceptHandler handlr, stream_socket& sock)
                    : handler(handlr), socket(sock) {
                    }

                    void execute(const error_code& ec) {
                        if (!ec)
                            socket.async_check_accept(boost::bind(&operation_type::accept_result, *this,
                                boost::asio::placeholders::error));
                        else
                            handler(ec);
                    }

                    void accept_result(const error_code& ec) {
                        handler(ec);
                    }

                private:
                    AcceptHandler handler;
                    stream_socket& socket;
                };



                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

                template <typename AcceptHandler>
                void async_accept_impl(stream_socket& peer,
                        endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;

                    typedef accept_operation<AcceptHandler > accept_operation_type;

                    peer.session_option(session_selector_);
                    super_type::async_accept(peer, peer_endpoint, boost::bind(&accept_operation_type::execute,
                            accept_operation_type(handler, peer), boost::asio::placeholders::error));

                }

                template <typename AcceptHandler>
                void async_accept_impl(stream_socket& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {

                    BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;

                    typedef accept_operation<AcceptHandler > accept_operation_type;

                    peer.session_option(session_selector_);
                    super_type::async_accept(peer, boost::bind(&accept_operation_type::execute,
                            accept_operation_type(handler, peer), boost::asio::placeholders::error));

                }

                error_code accept_impl(
                        stream_socket& peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    peer.session_option(session_selector_);
                    super_type::accept(peer, peer_endpoint, ec);
                    if (ec)
                        return ec;
                    peer.check_accept(ec);
                    return ec;
                }

                error_code accept_impl(
                        stream_socket& peer,
                        error_code& ec) {
                    peer.session_option(session_selector_);
                    super_type::accept(peer, ec);
                    if (ec)
                        return ec;
                    peer.check_accept(ec);
                    return ec;
                }

            private:
                session_selector session_selector_;

            };
        }





        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //  x225 declaration  //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

        class x225 {
        public:

            typedef boost::asio::ip::basic_endpoint<boost::asio::ip::tcp> endpoint;

            typedef session_selector selector;

            typedef transport_selector lowselector;

            static x225 v4() {

                return x225(PF_INET);
            }

            static x225 v6() {

                return x225(PF_INET6);
            }

            int type() const {

                return SOCK_STREAM;
            }

            int protocol() const {

                return IPPROTO_TCP;
            }

            int family() const {

                return family_;
            }

            typedef x225impl::stream_socket socket;

            typedef x225impl::socket_acceptor acceptor;

            typedef boost::asio::ip::basic_resolver<boost::asio::ip::tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
            typedef boost::asio::basic_socket_iostream<boost::asio::ip::tcp> iostream;
#endif 


            typedef boost::asio::detail::socket_option::boolean<
            IPPROTO_TCP, TCP_NODELAY> no_delay;

            /// Compare two protocols for equality.

            friend bool operator==(const x225& p1, const x225& p2) {

                return p1.family_ == p2.family_;
            }

            friend bool operator!=(const x225& p1, const x225& p2) {

                return p1.family_ != p2.family_;
            }

        private:

            explicit x225(int family)
            : family_(family) {
            }

            int family_;
        };

    }


} // namespace boost



#endif  