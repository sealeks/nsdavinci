
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
            typedef boost::asio::socket_base::message_flags message_flags;


            typedef uint8_t spdu_type;
            typedef uint16_t valuelenth_type;
            typedef uint8_t varid_type;

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   x225 utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     


            // SPDU identifier  *ref X225 5.6  Table 3 – Functional units (only kernel and half-duplex implemented here)
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

                typedef octet_sequnce data_type;
                typedef boost::shared_ptr< data_type > data_type_ptr;

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


                data_type_ptr type_data;
                mutable_buffer type_buff_;
                data_type_ptr header_data;
                mutable_buffer header_buff_;
                mutable_buffer userbuff_;
            };













            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  x225 stream_socket  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

            class stream_socket : public boost::itu::rfc1006::socket {
                
                typedef boost::itu::rfc1006::socket super_type;
                typedef boost::itu::asn_coder_templ<> default_coder_type;

                typedef boost::shared_ptr<receiver> receiver_ptr;
                typedef boost::shared_ptr<sender> sender_ptr;

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
                    if (!is_open()) {
                        if (get_service().open(get_implementation(),
                                peer_endpoint.protocol(), ec)) {
                            return ec;
                        }
                    }
                    return connect_impl(peer_endpoint, ec);
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            private:

                template <typename ConnectHandler>
                class connect_op {

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    connect_op(stream_socket* socket, ConnectHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(request),
                    send_(sender_ptr(new sender(CN_SPDU_ID, socket->session_option(), socket_->rootcoder()))),
                    receive_(new receiver()) {

                    }

                    void run(const error_code& ec) {
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec) {
                        if (!ec)
                            operator()(ec, 0);
                        else
                            exit_handler(ec);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    else {
                                        state(response);
                                        operator()(ec, 0);
                                        return;
                                    }
                                }
                                case response:
                                {
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), 0, *this);
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
                        if (receive_->state() == receiver::complete) {
                            switch (receive_->type()) {
                                case AC_SPDU_ID:
                                {
                                    socket_->negotiate_session_option(receive_->options());
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    socket_->session_version_ = (receive_->options().accept_version() & VERSION2) ? VERSION2 : VERSION1;
                                    exit_handler(ec);
                                    return;
                                }
                                case RF_SPDU_ID:
                                {
                                    error_code ecc;
                                    //socket_->close(ecc);
                                    exit_handler(ER_REFUSE);
                                    return;
                                }
                                default:
                                {
                                    error_code ecc;
                                    //socket_->close(ecc);
                                }
                            }
                        }
                        exit_handler(ER_PROTOCOL);
                    }

                    void exit_handler(const error_code& ec) {
                        socket_->rootcoder()->out()->clear();
                        handler_(ec);
                    }

                    void state(stateconnection st) {
                        if (state_ != st)
                            state_ = st;
                    }

                    stream_socket* socket_;
                    ConnectHandler handler_;
                    stateconnection state_;
                    sender_ptr send_;
                    receiver_ptr receive_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:

                template <typename ConnectHandler>
                void async_connect(const endpoint_type& peer_endpoint,
                        BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {
                    rootcoder()->in()->clear();
                    if (!is_open()) {
                        error_code ec;
                        const protocol_type protocol = peer_endpoint.protocol();
                        if (get_service().open(get_implementation(), protocol, ec)) {
                            get_io_service().post(
                                    boost::asio::detail::bind_handler(handler, ec));
                            return;
                        }
                    }
                    super_type::async_connect(peer_endpoint, boost::bind(&connect_op<ConnectHandler>::run, 
                    connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler), boost::asio::placeholders::error));
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
                class release_op {

                    enum stateconnection {
                        request,
                        response,
                        waitclose,
                        stop
                    };

                public:

                    release_op(stream_socket* socket, ReleaseHandler handler, release_type type) :
                    socket_(socket),
                    handler_(handler),
                    send_(sender_ptr(new sender(release_type_to_spdu(type), socket->session_option(), socket_->rootcoder()))),
                    receive_(new receiver()),
                    type_(type),
                    state_(request) {
                    }

                    void run() {
                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    operator()(ec, 0);
                                    return;
                                }
                                case response:
                                {
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), 0, *this);
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case waitclose:
                                {
                                    socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), 0, *this);
                                    state(stop);
                                    return;
                                }
                            }

                        }
                        exit_handler(ec);
                    }


                private:

                    void finish(const error_code& ec) {
                        if (receive_->state() == receiver::complete) {
                            switch (receive_->type()) {
                                case DN_SPDU_ID:
                                {
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    error_code ecc;
                                    //socket_->close(ecc);
                                    exit_handler(ec);
                                    return;
                                }
                                case AA_SPDU_ID:
                                {
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    error_code ecc;
                                    //socket_->close(ecc);
                                    exit_handler(ec);
                                    return;
                                }
                                default:
                                {
                                }
                            }
                        }
                        error_code ecc;
                        //socket_->close(ecc);
                        exit_handler(ER_PROTOCOL);
                    }

                    void exit_handler(const error_code& ec) {
                        //socket_->rootcoder()->out()->clear();
                        handler_(ec);
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket* socket_;
                    ReleaseHandler handler_;
                    sender_ptr send_;
                    receiver_ptr receive_;
                    release_type type_;
                    stateconnection state_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                   


            public:

                template <typename ReleaseHandler>
                void asyn_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler) {
                    //BOOST_ASIO_CONNECT_HANDLER_CHECK(ReleaseHandler, handler) type_check;
                    rootcoder()->in()->clear();
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_op<ReleaseHandler>::run,
                                release_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, SESSION_FN_RELEASE)));
                    }
                    else
                        handler(ER_REFUSE);
                }

                template <typename ReleaseHandler>
                void asyn_abort(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler) {
                    //BOOST_ASIO_CONNECT_HANDLER_CHECK(ReleaseHandler, handler) type_check;
                    rootcoder()->in()->clear();
                    if (is_open()) {
                        get_io_service().post(boost::bind(&release_op<ReleaseHandler>::run,
                                release_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, SESSION_AB_RELEASE)));
                    }
                    else
                        handler(ER_REFUSE);
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

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
                class accept_op {

                    enum stateconnection {
                        wait,
                        send,
                        refuse
                    };

                public:

                    accept_op(stream_socket* socket, CheckAcceptHandler handler) :
                    socket_(socket),
                    handler_(handler),
                    state_(wait),
                    send_(),
                    receive_(new receiver()) {
                    }

                    void run() {

                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case wait:
                                {
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), 0, *this);
                                        return;
                                    }
                                    parse_response(ec);
                                    return;
                                }
                                case send:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    finish(ec);
                                    return;
                                }
                                case refuse:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    error_code ecc;
                                    //socket_->close(ecc);
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
                        if (receive_->type() != CN_SPDU_ID || receive_->state() != receiver::complete) {
                            error_code ecc;
                            //socket_->close(ecc);
                            exit_handler(ER_PROTOCOL);
                            return;
                        }
                        bool nouserreject = true;
                        protocol_options options_ = socket_->session_option();
                        socket_->rootcoder()->in()->add(receive_->options().data());
                        if (!negotiate_x225impl_option(options_, receive_->options()) ||
                                !(nouserreject = socket_->negotiate_session_accept())) {
                            if (!nouserreject)
                                options_.refuse_reason(DR_REASON_USER);
                            send_ = sender_ptr(new sender(RF_SPDU_ID, options_, socket_->rootcoder()));
                            state(refuse);
                            operator()(ec, 0);
                            return;
                        }
                        socket_->session_version_ = (options_.accept_version() & VERSION2) ? VERSION2 : VERSION1;
                        send_ = sender_ptr(new sender(AC_SPDU_ID, options_, socket_->rootcoder()));
                        state(send);
                        operator()(ec, 0);
                    }

                    void finish(const error_code& ec) {

                        protocol_options opt = receive_->options();
                        socket_->negotiate_session_option(opt);
                        exit_handler(ec);
                    }

                    void exit_handler(const error_code& ec) {
                        socket_->rootcoder()->out()->clear();
                        handler_(ec);
                    }

                    void state(stateconnection st) {

                        if (state_ != st)
                            state_ = st;
                    }



                    stream_socket* socket_;
                    CheckAcceptHandler handler_;
                    stateconnection state_;
                    sender_ptr send_;
                    receiver_ptr receive_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

            public:

                template <typename CheckAcceptHandler>
                void asyn_check_accept(BOOST_ASIO_MOVE_ARG(CheckAcceptHandler) handler) {
                    // BOOST_ASIO_CONNECT_HANDLER_CHECK(CheckAcceptHandler, handler) type_check;
                    rootcoder()->in()->clear();
                    get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
                            accept_op<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler)));
                }








                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Send operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                        

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
                class send_op {
                public:

                    send_op(stream_socket* socket, SendHandler handler,
                            const ConstBufferSequence& buffers, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    in_(sender_ptr(new data_sender<ConstBufferSequence>(buffers))),
                    flags_(flags),
                    send_lower_(boost::asio::buffer_size(buffers)) {
                    }

                    void run() {

                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            in_->size(bytes_transferred);
                            if (!in_->ready()) {
                                socket_->super_type::async_send(in_->pop(), flags_, *this);
                                return;
                            }
                        }
                        handler_(ec, static_cast<std::size_t> (send_lower_));
                    }


                private:

                    stream_socket* socket_;
                    SendHandler handler_;
                    sender_ptr in_;
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
                void async_send(const ConstBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    //BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;
                    get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
                }

                template <typename ConstBufferSequence, typename WriteHandler>
                void async_write_some(const ConstBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {
                    //BOOST_ASIO_CONNECT_HANDLER_CHECK(WriteHandler, handler) type_check;

                    async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
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
                class receive_op {

                    enum stateconnection {
                        request,
                        response
                    };



                public:

                    receive_op(stream_socket* socket, ReceiveHandler handler,
                            receiver_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    receive_(receive),
                    buff_(buff),
                    send_(),
                    state_(request),
                    flags_(flags) {
                    }

                    void run() {
                        error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    receive_->put(bytes_transferred);
                                    if (!receive_->ready()) {
                                        socket_->super_type::async_receive(boost::asio::buffer(receive_->buffer()), flags_, *this);
                                        return;
                                    }
                                    if (!success()) return;
                                    break;
                                }
                                case response:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    handler_(ER_REFUSE, static_cast<std::size_t> (receive_->datasize()));
                                    return;
                                }
                            }
                        }
                        handler_(ec, static_cast<std::size_t> (receive_->datasize()));
                    }


                private:

                    bool success() {
                        switch (receive_->type()) {
                            case DT_SPDU_ID:
                            {
                                return true;
                            }
                            case FN_SPDU_ID:
                            {
                                socket_->rootcoder()->in()->clear();
                                socket_->rootcoder()->in()->add(receive_->options().data());
                                socket_->negotiate_session_release();
                                send_ = sender_ptr(new sender(DN_SPDU_ID, socket_->session_option(), socket_->rootcoder()));
                                state(response);
                                run();
                                return false;
                            }
                            case AB_SPDU_ID:
                            {
                                socket_->rootcoder()->in()->clear();
                                socket_->rootcoder()->in()->add(receive_->options().data());
                                socket_->negotiate_session_abort();
                                error_code ecc;
                                socket_->close(ecc);
                                handler_(ER_ABORT, 0);
                                return false;
                            }
                            default:
                            {
                                socket_->rootcoder()->in()->clear();
                                socket_->rootcoder()->in()->add(receive_->options().data());
                                send_ = sender_ptr(new sender(AB_SPDU_ID, socket_->session_option(), socket_->rootcoder()));
                                state(response);
                                run();
                            }
                        }

                        return false;
                    }

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket* socket_;
                    ReceiveHandler handler_;
                    const Mutable_Buffers& buff_;
                    receiver_ptr receive_;
                    sender_ptr send_;
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
                void async_receive(const MutableBufferSequence& buffers,
                        message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
                    //BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                    if (input_empty())
                        get_io_service().post(boost::bind(&receive_op<ReadHandler, MutableBufferSequence>::run, receive_op<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                            receiver_ptr(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers))), buffers, flags)));
                    else
                        super_type::async_receive(buffers, flags, handler);

                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_read_some(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
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

                virtual sender_ptr session_release_reaction(receiver_ptr receive) {
                    if (!receive)
                        return sender_ptr();
                    if (rootcoder()) {
                        rootcoder()->clear();
                        rootcoder()->in()->add(receive->options().data());
                    }
                    switch (receive->type()) {
                        case FN_SPDU_ID: return sender_ptr(new sender(DN_SPDU_ID, session_option(), rootcoder()));
                        case AB_SPDU_ID: return sender_ptr(new sender(AC_SPDU_ID, session_option(), rootcoder()));
                        default:
                        {
                        }
                    }
                    return sender_ptr();
                }

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

                    sender_ptr send_(sender_ptr(new sender(CN_SPDU_ID, session_option(), rootcoder())));
                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    if (ec)
                        return connect_impl_exit(ec);
                    receiver_ptr receive_(receiver_ptr(new receiver()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return connect_impl_exit(ec);
                    if (receive_->state() == receiver::complete) {
                        switch (receive_->type()) {
                            case AC_SPDU_ID:
                            {
                                negotiate_session_option(receive_->options());
                                rootcoder()->in()->add(receive_->options().data());
                                session_version_ = (receive_->options().accept_version() & VERSION2) ? VERSION2 : VERSION1;
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
                        sender_ptr send_(new sender(release_type_to_spdu(type), session_option(), rootcoder()));
                        while (!ec && !send_->ready())
                            send_->size(super_type::send(send_->pop(), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        receiver_ptr receive_(receiver_ptr(new receiver()));
                        while (!ec && !receive_->ready())
                            receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        if (receive_->state() == receiver::complete) {
                            switch (receive_->type()) {
                                case DN_SPDU_ID:
                                {
                                    rootcoder()->in()->add(receive_->options().data());
                                    error_code ecc;
                                    //close(ecc);
                                    return release_impl_exit(ec);
                                }
                                case AA_SPDU_ID:
                                {
                                    rootcoder()->in()->add(receive_->options().data());
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
                    receiver_ptr receive_(receiver_ptr(new receiver()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return check_accept_imp_exit(ec);
                    sender_ptr send_;

                    protocol_options options_ = session_option();
                    if (receive_->type() != CN_SPDU_ID || receive_->state() != receiver::complete) {
                        error_code ecc;
                        //close(ecc);
                        return check_accept_imp_exit(ER_PROTOCOL);
                    }
                    bool nouserreject = true;
                    rootcoder()->in()->add(receive_->options().data());
                    if (!negotiate_x225impl_option(options_, receive_->options()) ||
                            !(nouserreject = negotiate_session_accept())) {
                        if (!nouserreject)
                            options_.refuse_reason(DR_REASON_USER);
                        canseled = true;
                        send_ = sender_ptr(new sender(RF_SPDU_ID, options_, rootcoder()));
                    }
                    else {
                        session_version_ = (options_.accept_version() & VERSION2) ? VERSION2 : VERSION1;
                        send_ = sender_ptr(new sender(AC_SPDU_ID, options_, rootcoder()));
                    }

                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    if (ec)
                        return check_accept_imp_exit(ec);
                    if (canseled) {
                        error_code ecc;
                        //close(ecc);
                    }
                    else {
                        protocol_options opt = receive_->options();
                        negotiate_session_option(receive_->options());
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
                    sender_ptr send_(new data_sender<ConstBufferSequence > (buffers));
                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        message_flags flags, error_code& ec) {

                    if (!input_empty())
                        return super_type::receive(boost::asio::buffer(buffers), flags, ec);

                    receiver_ptr receive_(new receiver(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers)));
                    while (!ec && !receive_->ready()) {
                        receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return 0;
                    switch (receive_->type()) {
                        case DT_SPDU_ID:
                        {
                            return receive_->datasize();
                        }
                        case FN_SPDU_ID:
                        {
                            rootcoder()->in()->clear();
                            rootcoder()->in()->add(receive_->options().data());
                            negotiate_session_release();
                            sender_ptr send_ = sender_ptr(new sender(DN_SPDU_ID, session_option(), rootcoder()));
                            while (!ec && !send_->ready())
                                send_->size(super_type::send(send_->pop(), 0, ec));
                            error_code ecc;
                            close(ecc);
                            ec = ER_RELEASE;
                            return 0;
                        }
                        case AB_SPDU_ID:
                        {
                            rootcoder()->in()->clear();
                            rootcoder()->in()->add(receive_->options().data());
                            negotiate_session_abort();
                            error_code ecc;
                            close(ecc);
                            ec = ER_ABORT;
                            return 0;
                        }
                        default:
                        {
                            sender_ptr send_ = session_release_reaction(receive_);
                            if (send_) {
                                while (!ec && !send_->ready())
                                    send_->size(super_type::send(send_->pop(), 0, ec));
                                ec = ER_REFUSE;
                                error_code ecc;
                                // close(ecc);
                                return receive_->datasize();

                            }
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

            class socket_acceptor : public boost::itu::rfc1006impl::socket_acceptor {
                typedef boost::itu::rfc1006impl::socket_acceptor super_type;

            public:




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                

                explicit socket_acceptor(boost::asio::io_service& io_service)
                : boost::itu::rfc1006impl::socket_acceptor(io_service) {
                }

                socket_acceptor(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, bool reuse_addr = true)
                : boost::itu::rfc1006impl::socket_acceptor(io_service, endpoint, reuse_addr) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

                template <typename SocketService>
                void accept(basic_socket<protocol_type, SocketService>& peer) {
                    error_code ec;
                    accept_impl(peer, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                template <typename SocketService>
                error_code accept(
                        basic_socket<protocol_type, SocketService>& peer,
                        error_code& ec) {
                    return accept_impl(peer, ec);
                }

                template <typename SocketService>
                void accept(basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint) {
                    error_code ec;
                    accept_impl(peer, peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                template <typename SocketService>
                error_code accept(
                        basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    return accept_impl(peer, peer_endpoint, ec);
                }

                template <typename SocketService, typename AcceptHandler>
                void async_accept(basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    //BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                    async_accept_impl(peer, peer_endpoint, BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                }

                template <typename SocketService, typename AcceptHandler>
                void async_accept(basic_socket<protocol_type, SocketService>& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    //BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                    async_accept_impl(peer, BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            private:

                template <typename Handler>
                class accept_op {
                public:

                    accept_op(Handler h, stream_socket* socket)
                    : handler_(h), socket_(socket) {
                    }

                    void operator()(const error_code& ec) {
                        if (!ec)
                            static_cast<stream_socket*> (socket_)->asyn_check_accept(handler_);
                        else
                            handler_(ec);
                    }

                private:
                    Handler handler_;
                    stream_socket* socket_;
                };



                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

                template <typename SocketService, typename AcceptHandler>
                void async_accept_impl(basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    //BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                    super_type::async_accept(peer, peer_endpoint, accept_op<AcceptHandler > (handler, static_cast<stream_socket*> (&peer)));
                }

                template <typename SocketService, typename AcceptHandler>
                void async_accept_impl(basic_socket<protocol_type, SocketService>& peer,
                        BOOST_ASIO_MOVE_ARG(AcceptHandler) handler) {
                    //BOOST_ASIO_ACCEPT_HANDLER_CHECK(AcceptHandler, handler) type_check;
                    super_type::async_accept(peer, accept_op<AcceptHandler > (handler, static_cast<stream_socket*> (&peer)));
                }

                template <typename SocketService>
                error_code accept_impl(
                        basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, error_code& ec) {
                    super_type::accept(peer, peer_endpoint, ec);
                    if (ec)
                        return ec;
                    static_cast<stream_socket*> (&peer)->check_accept(ec);
                    return ec;
                }

                template <typename SocketService>
                error_code accept_impl(
                        basic_socket<protocol_type, SocketService>& peer,
                        error_code& ec) {
                    super_type::accept(peer, ec);
                    if (ec)
                        return ec;
                    static_cast<stream_socket*> (&peer)->check_accept(ec);
                    return ec;
                }


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