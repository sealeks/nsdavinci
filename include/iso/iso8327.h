
/* 
 * File:   iso.cpp
 * Author: sealeks@mail.ru
 * 
 * 
 */

#ifndef         ISOPROT8327_H_H
#define ISOPROT8327_H_H

#include <iso/rfc1006.h>

namespace boost {
    namespace iso {
        namespace prot8327 {

            using boost::asio::basic_socket;
            
            typedef boost::asio::socket_base::message_flags message_flags;
            

            

            typedef uint8_t spdu_type;
            typedef uint16_t valuelenth_type;  
            typedef uint8_t varid_type;                
            typedef uint8_t session_version_type; 
            
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   iso8327 utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            
            const octet_type SEND_HEADERarr[] = { '\x1' ,'\x0', '\x1', '\x0'};
            const raw_type SEND_HEADER = raw_type(SEND_HEADERarr, SEND_HEADERarr + 4);
            
            const octet_type ECHO_NEGOTIATEarr[] = { 'e' ,'c', 'h', 'o', ':', ' '};
            const raw_type ECHO_NEGOTIATE = raw_type(ECHO_NEGOTIATEarr, ECHO_NEGOTIATEarr + 6);            

            const octet_type REFUSE_REASON_ADDRarr[] = { '\x1' , '\x81' };
            const raw_type REFUSE_REASON_ADDR = raw_type(REFUSE_REASON_ADDRarr, REFUSE_REASON_ADDRarr + 2);
            
            const octet_type REFUSE_REASON_NEGOTIATEarr[] = { '\x1' , '\x82' };
            const raw_type REFUSE_REASON_NEGOTIATE = raw_type(REFUSE_REASON_NEGOTIATEarr, REFUSE_REASON_NEGOTIATEarr + 2);        
            
            const octet_type REFUSE_REASON_USERarr[] = { '\x1' , '\x85' };
            const raw_type REFUSE_REASON_USER = raw_type(REFUSE_REASON_USERarr, REFUSE_REASON_USERarr + 2);                    

            const octet_type ABORT_REASON_ADDR = '\x0';                      

            const octet_type WORK_PROT_OPTION = '\x0';
            const octet_type FAIL_PROT_OPTION = '\x1';            
            const octet_type WORK_PROT_VERSION = '\x3';

            const octet_type TDSK_NOKEEPCON = '\x1';
            const octet_type TDSK_USER_ABORT = '\x2'; 
            const octet_type TDSK_PROT_ERROR = '\x4';              
            const octet_type TDSK_NO_REASON = '\x8';    
            const octet_type TDSK_IMPLRESTRICT = '\x10';            
            
            
            const octet_type  VERSIONMASK1='\x1';
            const octet_type  VERSIONMASK2='\x2';                   
        
            const std::size_t  SIMPLE_CONNECT_PDUSIZE_LIMIT = 512;
            const std::size_t  EXTENDED_CONNECT_PDUSIZE_LIMIT = 10240;            

            const spdu_type CN_SPDU_ID = 13; //CONNECT SPDU
            const spdu_type OA_SPDU_ID = 16; //OVERFLOW ACCEPT
            const spdu_type CDO_SPDU_ID = 15; //CONNECT DATA OVERFLOW
            const spdu_type AC_SPDU_ID = 14; //ACCEPT
            const spdu_type RF_SPDU_ID = 12; //REFUSE 
            const spdu_type FN_SPDU_ID = 9; //FINISH 
            const spdu_type DN_SPDU_ID = 10; //DISCONNECT
            const spdu_type NF_SPDU_ID = 8; //NOT FINISHED
            const spdu_type AB_SPDU_ID = 25; //ABORT
            const spdu_type AA_SPDU_ID = 26; //ABORT ACCEPT
            const spdu_type DT_SPDU_ID = 1; //DATA TRANSFER 
            const spdu_type PR_SPDU_ID = 7; //PREPARE 
            //const spdu_type NF_SPDU_ID = 8;      //NOT FINISHED

            //  Negotiated realease

            
            
            //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
            //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS

            //half-duplex
            const spdu_type GT_SPDU_ID = 1; //GIVE TOKENS
            const spdu_type PT_SPDU_ID = 2; //PLEASE TOKENS               

            //duplex      
            //

            //expedited data functional unit;
            const spdu_type EX_SPDU_ID = 5; //EXPEDITED

            //typed data functional unit
            const spdu_type TD_SPDU_ID = 33; //TYPED DATA

            //capability data exchange functional unit;
            const spdu_type CD_SPDU_ID = 61; //CAPABILITY DATA
            const spdu_type CDA_SPDU_ID = 62; //CAPABILITY DATA ACK

            // minor synchronize functional unit;
            const spdu_type MIP_SPDU_ID = 49; //MINOR SYNC POINT
            const spdu_type MIA_SPDU_ID = 50; //MINOR SYNC ACK
            //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
            //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS   

            // symmetric synchronize functional unit;                
            //const spdu_type MIP_SPDU_ID = 49;      //MINOR SYNC POINT
            //const spdu_type MIA_SPDU_ID = 50;    //MINOR SYNC ACK  

            //major synchronize functional unit;
            const spdu_type MAP_SPDU_ID = 41; //MAJOR SYNC POINT
            const spdu_type MAA_SPDU_ID = 42; //MAJOR SYNC ACK 
            //const spdu_type PR_SPDU_ID = 7;      //PREPARE               
            //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
            //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS   

            // resynchronize functional unit     
            const spdu_type RS_SPDU_ID = 53; //RESYNCHRONIZE        
            const spdu_type RA_SPDU_ID = 34; //RESYNCHRONIZE ACK
            //const spdu_type PR_SPDU_ID = 7;      //PREPARE 

            //exceptions functional unit;                 
            const spdu_type ER_SPDU_ID = 0; //EXCEPTION REPORT
            const spdu_type ED_SPDU_ID = 48; //EXCEPTION DATA


            const spdu_type AS_SPDU_ID = 45; //ACTIVITY START
            const spdu_type AR_SPDU_ID = 29; //ACTIVITY RESUME       
            const spdu_type AI_SPDU_ID = 25; //ACTIVITY INTERRUPT               
            const spdu_type AIA_SPDU_ID = 26; //ACTIVITY INTERRUPT ACK 
            const spdu_type AD_SPDU_ID = 57; //ACTIVITY DISCARD
            const spdu_type ADA_SPDU_ID = 58; //ACTIVITY DISCARD ACK
            const spdu_type AE_SPDU_ID = 41; //ACTIVITY END
            const spdu_type AEA_SPDU_ID = 42; //ACTIVITY END ACK   

            //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
            //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS
            //const spdu_type PR_SPDU_ID = 7;      //PREPARE               
            const spdu_type GTC_SPDU_ID = 21; //GIVE TOKENS CONFIRM
            const spdu_type GTA_SPDU_ID = 22; //GIVE TOKENS ACK


            //  Function unit

            const int16_t FU_HALFDUPLEX = 0x1; //half-duplex functional unit;            
            const int16_t FU_DUPLEX = 0x2; // duplex functional unit;
            const int16_t FU_EXPDATA = 0x4; //expedited data functional unit;            
            const int16_t FU_MINORSYNC = 0x8; // minor synchronize functional unit;
            const int16_t FU_MAJORORSYNC = 0x10; //major synchronize functional unit;         
            const int16_t FU_RESYNC = 0x20; // resynchronize functional unit;;
            const int16_t FU_ACTIVEMG = 0x40; //activity management functional unit;            
            const int16_t FU_NEGOTREL = 0x80; // negotiated release functional unit;               
            const int16_t FU_CAPABDATA = 0x100; //capability data exchange functional unit;
            const int16_t FU_EXCEPTION = 0x200; //exceptions functional unit; 
            const int16_t FU_TYPEDDATA = 0x400; //typed data functional unit; 
            const int16_t FU_SYMSYNC = 0x800; //symmetric synchronize functional unit;  
            const int16_t FU_DATASEP = 0x1000; //data separation functional unit;


            const int16_t FU_WORK = FU_DUPLEX; //work;
            const int16_t FU_DEFAULT = FU_HALFDUPLEX | FU_MINORSYNC | FU_ACTIVEMG | FU_CAPABDATA |  FU_EXCEPTION; //default;


            const varid_type PGI_CN_IND = 1; // Connection Identifier              
            const varid_type PGI_CN_AC = 5; // Connect/Accept Item
            //const varid_type    PGI_CN_AC = 33; // AR  SPDU Linking Information         

            const varid_type PI_PROPT = 19; // Protocol Options
            const varid_type PI_TSDUMAX = 21; // TSDU Maximum Size              
            const varid_type PI_VERS = 22; // Version Number  

            const varid_type PI_SUREQ = 20; //Session User Requirements               
            const varid_type PI_CALLING = 51; //Calling Session Selector
            const varid_type PI_CALLED = 52; //Responding Session Selector
            const varid_type PI_DTOVER = 60; //  Data Overflow 
            const varid_type PI_USERDATA = 193; //User Data        
            const varid_type PI_EXUSERDATA = 194; //Extended User Data
            const varid_type PI_ENCLOSURE = 25; //Enclosure Item
            const varid_type PI_REASON = 50; //Reason Code 
            const varid_type PI_TRANDISK = 17; //Transport Disconnect                

            const session_version_type  VERSION1=1;
            const session_version_type  VERSION2=2;
            
            

        enum release_type {
            SESSION_FN_RELEASE = FN_SPDU_ID ,
            SESSION_AB_RELEASE = AB_SPDU_ID,
            SESSION_DN_RELEASE = DN_SPDU_ID ,
            SESSION_AA_RELEASE = AA_SPDU_ID,           
        };
        
        inline static spdu_type release_type_to_spdu(release_type vl){
            return static_cast<spdu_type>(vl);
        }
            
            const std::size_t triple_npos = static_cast<std::size_t> (0xFFFF + 1);

            inline static raw_type to_triple_size(std::size_t val) {
                if (val < 0xFF)
                    return inttype_to_raw(static_cast<uint8_t> (val));
                raw_type rslt(1, '\xFF');
                raw_back_insert(rslt, inttype_to_raw(endiancnv_copy(static_cast<uint16_t> (val))));
                return rslt;
            }

            inline static bool valid_triple_size(const raw_type& val) {
                return !((val.empty()) || (val[0] == '\xFF' && val.size() < 3));
            }

            // return triple_npos if no success
            std::size_t from_triple_size(const raw_type& val, std::size_t& it);


            typedef std::pair<varid_type, raw_type> pi_type;
            typedef std::map<varid_type, raw_type > pgi_type;
            typedef std::pair<varid_type, pgi_type> pgis_type;
            typedef std::map<varid_type, pgi_type> spdudata_type; // (it->first==0 contain pi_type in vector
            
            
            
            
            
            
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   spdudata utill   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                 
            

            class spdudata : protected spdudata_type {
            public:

                spdudata() : spdudata_type(), type_(0), error_(false) {
                }

                explicit spdudata(spdu_type spdu) : spdudata_type(), type_(spdu), error_(false) {
                }

                explicit spdudata(const const_buffer& vl) : spdudata_type(), seq_(), type_(0), error_(false) {
                    parse_vars(buffer_to_raw(vl));
                }

                spdu_type type() const {
                    return type_;
                }

                bool error() const {
                    return error_;
                }

                void setPGI(varid_type cod1, varid_type cod2, const raw_type& val = raw_type());

                void setPGI(varid_type cod1, varid_type cod2, int8_t val);

                void setPGI(varid_type cod1, varid_type cod2, uint8_t val);

                void setPGI(varid_type cod1, varid_type cod2, int16_t val);

                void setPGI(varid_type cod1, varid_type cod2, uint16_t val);


                void setPI(varid_type cod, const raw_type& val = raw_type());

                void setPI(varid_type cod, int8_t val);

                void setPI(varid_type cod, uint8_t val);

                void setPI(varid_type cod, int16_t val);

                void setPI(varid_type cod, uint16_t val);


                const raw_type&  getPGI(varid_type cod1, varid_type cod2) const;

                bool getPGI(varid_type cod1, varid_type cod2, int8_t& val, int8_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, uint8_t& val, uint8_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, int16_t& val, int16_t def = 0) const;

                bool getPGI(varid_type cod1, varid_type cod2, uint16_t& val, uint16_t def = 0) const;

                const raw_type&  getPI(varid_type cod) const;

                bool getPI(varid_type cod, int8_t& val, int8_t def = 0) const;

                bool getPI(varid_type cod, uint8_t& val, uint8_t def = 0) const;

                bool getPI(varid_type cod, int16_t& val, int16_t def = 0) const;

                bool getPI(varid_type cod, uint16_t& val, uint16_t def = 0) const;


                bool existPGI(varid_type cod1, varid_type cod2) const;

                bool existPI(varid_type cod) const;

                bool nullPGI(varid_type cod1, varid_type cod2) const;

                bool nullPI(varid_type cod) const;

                const_sequence_ptr sequence(isocoder_ptr seq) const;
                
            private:

                bool error(bool val) {
                    return error_ = val;
                }

                bool parse();
                bool parse_vars(const raw_type& vl);
                bool parse_pgi(varid_type tp, const raw_type& vl);

                mutable raw_type seq_;
                spdu_type type_;
                bool error_;
                raw_type null_val;

            };
            
            
            
            
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   protocol_options   //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                
            
            struct protocol_options {
                
                typedef boost::shared_ptr<spdudata> spdudata_ptr;

                protocol_options() : vars_( new spdudata()) {
                }

                protocol_options(const const_buffer & vl) : vars_( new spdudata(vl))  {
                }

                protocol_options(const raw_type& called, const raw_type& calling = raw_type());

                const raw_type& ssap_calling() const;

                void ssap_calling(const raw_type & val);

                const raw_type& ssap_called() const;

                void ssap_called(const raw_type & val);

                const raw_type& data() const; 
                
                octet_type accept_version() const;   
                
                void accept_version(octet_type vl);                 
                
                octet_type reject_version() const;  
                
                void reject_version(octet_type vl);   
                
                int16_t user_requirement() const;  
                
                void user_requirement(int16_t vl);          
                
                octet_type prot_option() const;  
                
                void prot_option(octet_type vl);                

                void reason(const raw_type & val);
                
                const raw_type& reason() const;                  
                
            private:
                spdudata_ptr vars_;
            };

            

            //negotiate_prot8327_option
            bool negotiate_prot8327_option(protocol_options& self, const protocol_options& dist);

            const_sequence_ptr generate_header_CN(const protocol_options& opt, isocoder_ptr data); //CONNECT SPDU

            const_sequence_ptr generate_header_AC(const protocol_options& opt, isocoder_ptr data); //ACCEPT SPDU

            const_sequence_ptr generate_header_RF(const protocol_options& opt, isocoder_ptr data); //REFUSE  SPDU        
            
            const_sequence_ptr generate_header_FN(const protocol_options& opt, isocoder_ptr data); //FINISH SPDU            

            const_sequence_ptr generate_header_DN(const protocol_options& opt,  isocoder_ptr data); //DISCONNECT  SPDU          

            const_sequence_ptr generate_header_AB(const protocol_options& opt, isocoder_ptr data); //ABORT SPDU                     

            const_sequence_ptr generate_header_AA(const protocol_options& opt, isocoder_ptr data); //ABORT ACCEPT  SPDU                              

            const_sequence_ptr generate_header_NF(const protocol_options& opt, isocoder_ptr data); //NOT FINISH  SPDU                      

            
            
            

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   data_send_buffer_impl    //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////           

            template <typename ConstBufferSequence>
            class data_send_buffer_impl : public send_buffer_impl {
            public:

                data_send_buffer_impl(const ConstBufferSequence& bf) : send_buffer_impl() {
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
            //   iso8327 send_seq  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////              

            class send_seq {
            public:

                send_seq(spdu_type type) : type_(type) {

                }

                send_seq(spdu_type type, const protocol_options& opt,  isocoder_ptr data) :
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
                            //buf_ = send_buffer_ptr(new send_buffer_impl(""));
                        }
                    }
                }

                virtual ~send_seq() {
                }

                bool ready() const {
                    return (!buf_) || (buf_->ready());
                }

                const const_sequence& pop() {
                    return buf_ ? buf_->pop() : NULL_CONST_SEQUENCE;
                }

                std::size_t size(std::size_t sz) {
                    return ready() ? 0 : buf_->size(sz);
                }

                std::size_t receivesize() const {
                    return ready() ? 0 : buf_->receivesize();
                }

                spdu_type type() const {
                    return type_;
                }




            protected:

                void constructCN(const protocol_options& opt,  isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_CN(opt, data)));
                }

                void constructAC(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_AC(opt, data)));
                }

                void constructRF(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_RF(opt , data)));
                }

                void constructFN(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_FN(opt, data)));
                }

                void constructAB(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_AB(opt, data)));
                }

                void constructDN(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_DN(opt, data)));
                }

                void constructAA(const protocol_options& opt, isocoder_ptr data) {
                    buf_ = send_buffer_ptr(new send_buffer_impl(generate_header_AA(opt, data)));
                }

                spdu_type type_;
                send_buffer_ptr buf_;
            };

            typedef boost::shared_ptr<send_seq> send_seq_ptr;








            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //   iso8327 send_seq_data  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                

            template <typename ConstBufferSequence >
            class send_seq_data : public send_seq {
            public:

                send_seq_data(const ConstBufferSequence& buff) : send_seq(DN_SPDU_ID) {
                    constructDT(buff);
                }

            protected:

                void constructDT(const ConstBufferSequence& buff) {
                    buf_ = send_buffer_ptr(new data_send_buffer_impl<ConstBufferSequence > (buff));
                }

            };



            //receive_seq

            const std::size_t SI_WITH_LI = 2;
            const std::size_t HDR_LI = 2;

            class receive_seq {
            public:

                typedef raw_type data_type;
                typedef boost::shared_ptr< data_type > data_type_ptr;

                enum operation_state {
                    waittype,
                    waitsize,
                    waitheader,
                    waitdata,
                    complete,
                    error
                };

                receive_seq(const mutable_buffer& buff);

                receive_seq();

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

                boost::system::error_code errcode() const {
                    return errcode_;
                }


            private:

                operation_state state(operation_state val);

                boost::system::error_code errcode(const boost::system::error_code& err);

                void reject_reason(octet_type val);

                boost::system::error_code check_type();

                boost::system::error_code check_size();

                boost::system::error_code check_header();



                operation_state state_;
                std::size_t size_;
                std::size_t estimatesize_;
                std::size_t datasize_;
                spdu_type type_;
                bool first_in_seq_;
                octet_type class_option_;
                octet_type reject_reason_;
                protocol_options options_;
                boost::system::error_code errcode_;


                data_type_ptr type_data;
                mutable_buffer type_buff_;
                data_type_ptr header_data;
                mutable_buffer header_buff_;
                mutable_buffer userbuff_;
            };

            typedef boost::shared_ptr<receive_seq> receive_seq_ptr;











            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  rf1006 stream_socket  //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

            class stream_socket : public boost::iso::rfc1006::socket {
                
                typedef boost::iso::rfc1006::socket super_type;
                typedef boost::iso::isocoder_templ<>  default_coder_type;
                
            public:



                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                explicit stream_socket(boost::asio::io_service& io_service, const session_selector& ssel = session_selector(), isocoder_ptr coder = isocoder_ptr( new default_coder_type()))
                : boost::iso::rfc1006::socket(io_service, ssel.tselector()), option_(ssel.called(), ssel.calling()), rootcoder_(coder), session_version_(VERSION2) {
                }

                stream_socket(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, const session_selector& ssel = session_selector(), isocoder_ptr coder = isocoder_ptr( new default_coder_type()))
                : boost::iso::rfc1006::socket(io_service, ssel.tselector()), option_(ssel.called(), ssel.calling()) , rootcoder_(coder), session_version_(VERSION2) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Connnect operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void connect(const endpoint_type& peer_endpoint) {
                    boost::system::error_code ec;
                    connect(peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "connect");
                }

                boost::system::error_code connect(const endpoint_type& peer_endpoint,
                        boost::system::error_code& ec) {
                    rootcoder()->in()->clear();                    
                    if (!is_open()) {
                        if (this->get_service().open(this->get_implementation(),
                                peer_endpoint.protocol(), ec)) {
                            return ec;
                        }
                    }
                    return connect_impl(peer_endpoint,  ec);
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

                    connect_op(stream_socket* socket, ConnectHandler handler,
                            const endpoint_type& peer_endpoint ) :
                    socket_(socket),
                    handler_(handler),
                    state_(request),
                    options_(socket->session_option()),
                    peer_endpoint_(peer_endpoint),
                    send_(send_seq_ptr(new send_seq(CN_SPDU_ID, socket->session_option(), socket_->rootcoder()))),
                    receive_(new receive_seq()){
                        
                    }

                    void run(const boost::system::error_code& ec) {
                        operator()(ec, 0);
                    }

                    void operator()(const boost::system::error_code& ec) {
                        if (!ec)
                            operator()(ec, 0);
                        else
                            exit_handler(ec);
                    }

                    void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred) {
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

                    void finish(const boost::system::error_code& ec) {
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case AC_SPDU_ID:
                                {
                                    socket_->negotiate_session_option(receive_->options());
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    socket_->session_version_=(receive_->options().accept_version() & VERSIONMASK2) ? VERSION2 : VERSION1;
                                    exit_handler(ec);
                                    return;
                                }
                                case RF_SPDU_ID:
                                {
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                    exit_handler(ERROR_ECONNREFUSED);
                                    return;
                                }                                
                                default:
                                {
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                }
                            }
                        }
                        exit_handler(ERROR__EPROTO);
                    }
                    
                    void exit_handler(const boost::system::error_code& ec) {
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
                    protocol_options options_;
                    endpoint_type peer_endpoint_;
                    send_seq_ptr send_;
                    receive_seq_ptr receive_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            public:


                template <typename ConnectHandler>
                void async_connect(const endpoint_type& peer_endpoint,
                        BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {
                    rootcoder()->in()->clear(); 
                    if (!is_open()) {
                        boost::system::error_code ec;
                        const protocol_type protocol = peer_endpoint.protocol();
                        if (this->get_service().open(get_implementation(), protocol, ec)) {
                            this->get_io_service().post(
                                    boost::asio::detail::bind_handler(handler, ec));
                            return;
                        }
                    } 
                    super_type::async_connect(peer_endpoint, boost::bind(&connect_op<ConnectHandler>::run, connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler, peer_endpoint), boost::asio::placeholders::error));
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Release operation  //
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 

                void release() {

                    boost::system::error_code ec;
                    release(ec);
                    boost::asio::detail::throw_error(ec, "release");
                }

                boost::system::error_code release(boost::system::error_code& ec) {
                    rootcoder()->in()->clear();
                    return release_impl(SESSION_FN_RELEASE, ec);
                }
                
                void abort() {

                    boost::system::error_code ec;
                    release(ec);
                    boost::asio::detail::throw_error(ec, "abort");
                }

                boost::system::error_code abort(boost::system::error_code& ec) {
                    rootcoder()->in()->clear();
                    return release_impl(SESSION_AB_RELEASE, ec);
                }                


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            private:

                template <typename ReleaseHandler>
                class release_op {

                    enum stateconnection {
                        request,
                        response
                    };

                public:

                    release_op(stream_socket* socket, ReleaseHandler handler, release_type type) :
                    socket_(socket),
                    handler_(handler),
                    send_(send_seq_ptr(new send_seq( release_type_to_spdu(type), socket->session_option(), socket_->rootcoder()))),
                    receive_(new receive_seq()),
                    type_(type),
                    state_(request) {
                    }

                    void run() {
                        boost::system::error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred) {
                        if (!ec) {
                            switch (state_) {
                                case request:
                                {
                                    send_->size(bytes_transferred);
                                    if (!send_->ready()) {
                                        socket_->super_type::async_send(send_->pop(), 0, *this);
                                        return;
                                    }
                                    state(response);
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
                            }
                        }
                        boost::system::error_code ecc;
                        socket_->close(ecc);                        
                        exit_handler(ec);
                    }


                private:

                    void finish(const boost::system::error_code& ec) {
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case DN_SPDU_ID:
                                {
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                    exit_handler(ec);                                    
                                    return;
                                }
                                case AA_SPDU_ID:
                                {
                                    socket_->rootcoder()->in()->add(receive_->options().data());
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                    exit_handler(ec);                                    
                                    return;
                                }
                                default:
                                {
                                }
                            }
                        }
                        boost::system::error_code ecc;
                        socket_->close(ecc);
                        exit_handler(ERROR__EPROTO);
                    }
                    
                    void exit_handler(const boost::system::error_code& ec) {
                        socket_->rootcoder()->out()->clear();
                        handler_(ec);
                    }                      

                    void state(stateconnection st) {
                        if (state_ != st) {
                            state_ = st;
                        }
                    }

                    stream_socket* socket_;
                    ReleaseHandler handler_;
                    send_seq_ptr send_;
                    receive_seq_ptr receive_;
                    release_type type_;
                    stateconnection state_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                   


            public:

                template <typename ReleaseHandler>
                void asyn_release(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler , release_type type = SESSION_FN_RELEASE) {
                    //BOOST_ASIO_CONNECT_HANDLER_CHECK(ReleaseHandler, handler) type_check;
                    rootcoder()->in()->clear(); 
                    if (is_open()) {
                        this->get_io_service().post(boost::bind(&release_op<ReleaseHandler>::run,
                                release_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, type)));
                    }
                    else
                        handler(ERROR_ECONNREFUSED);
                }

                template <typename ReleaseHandler>
                void asyn_abort(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler ) {
                    //BOOST_ASIO_CONNECT_HANDLER_CHECK(ReleaseHandler, handler) type_check;
                    rootcoder()->in()->clear(); 
                    if (is_open()) {
                        this->get_io_service().post(boost::bind(&release_op<ReleaseHandler>::run,
                                release_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, SESSION_AB_RELEASE)));
                    }
                    else
                        handler(ERROR_ECONNREFUSED);
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Check accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

                void check_accept() {

                    boost::system::error_code ec;
                    check_accept( ec);
                    boost::asio::detail::throw_error(ec, "connect");
                }

                boost::system::error_code check_accept(boost::system::error_code& ec) {
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
                    options_(socket->session_option()),
                    send_(),
                    receive_(new receive_seq()){
                    }

                    void run() {

                        boost::system::error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred) {
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
                                    boost::system::error_code ecc;
                                    socket_->close(ecc);
                                    exit_handler(ERROR_EDOM);
                                    return;
                                }
                            }
                        }
                        exit_handler(ec);
                    }




                    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   


                private:

                    void parse_response(const boost::system::error_code& ec) {
                        if (receive_->type() != CN_SPDU_ID || receive_->state() != receive_seq::complete) {
                            boost::system::error_code ecc;
                            socket_->close(ecc);
                            exit_handler(ERROR__EPROTO);
                            return;
                        }
                        bool nouserreject = true;
                        socket_->rootcoder()->in()->add(receive_->options().data());
                        if (!negotiate_prot8327_option(options_, receive_->options()) || 
                                !(nouserreject =socket_->negotiate_session_accept())) {
                            if (!nouserreject)
                                options_.reason(REFUSE_REASON_USER);
                            send_ = send_seq_ptr(new send_seq(RF_SPDU_ID, options_, socket_->rootcoder()));
                            state(refuse);
                            operator()(ec, 0);
                            return;
                        }
                        socket_->session_version_=(options_.accept_version() & VERSIONMASK2) ? VERSION2 : VERSION1;
                        send_ = send_seq_ptr(new send_seq(AC_SPDU_ID, options_, socket_->rootcoder()));
                        state(send);
                        operator()(ec, 0);
                    }

                    void finish(const boost::system::error_code& ec) {

                        protocol_options opt = receive_->options();
                        socket_->negotiate_session_option(opt);
                        exit_handler(ec);
                    }
                    
                    void exit_handler(const boost::system::error_code& ec) {
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
                    protocol_options options_;
                    send_seq_ptr send_;
                    receive_seq_ptr receive_;

                };


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////   

            public:

                template <typename CheckAcceptHandler>
                void asyn_check_accept(BOOST_ASIO_MOVE_ARG(CheckAcceptHandler) handler) {
                    // BOOST_ASIO_CONNECT_HANDLER_CHECK(CheckAcceptHandler, handler) type_check;
                    rootcoder()->in()->clear();
                    this->get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
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
                        socket_base::message_flags flags) {
                    boost::system::error_code ec;
                    std::size_t s = send(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "send");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers) {
                    boost::system::error_code ec;
                    std::size_t s = send(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "write_some");

                    return s;
                }

                template <typename ConstBufferSequence>
                std::size_t write_some(const ConstBufferSequence& buffers,
                        boost::system::error_code& ec) {

                    return send(buffers, 0, ec);
                }

                template <typename ConstBufferSequence>
                std::size_t send(const ConstBufferSequence& buffers,
                        socket_base::message_flags flags, boost::system::error_code& ec) {

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
                    in_(send_seq_ptr(new send_seq_data<ConstBufferSequence>(buffers))),
                    flags_(flags),
                    send_lower_(boost::asio::buffer_size(buffers)) {
                    }

                    void run() {

                        boost::system::error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred) {
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
                    send_seq_ptr in_;
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
                        socket_base::message_flags flags,
                        BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                    //BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;
                    this->get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
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
                        socket_base::message_flags flags) {
                    boost::system::error_code ec;
                    std::size_t s = receive(buffers, flags, ec);
                    boost::asio::detail::throw_error(ec, "receive");
                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers,
                        boost::system::error_code& ec) {

                    return receive(buffers, 0, ec);
                }

                template <typename MutableBufferSequence>
                std::size_t read_some(const MutableBufferSequence& buffers) {
                    boost::system::error_code ec;
                    std::size_t s = receive(buffers, 0, ec);
                    boost::asio::detail::throw_error(ec, "read_some");

                    return s;
                }

                template <typename MutableBufferSequence>
                std::size_t receive(const MutableBufferSequence& buffers,
                        socket_base::message_flags flags, boost::system::error_code& ec) {

                    return receive_impl(buffers, flags, ec);
                }





                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                    

            private:

                template <typename ReceiveHandler, typename Mutable_Buffers>
                class receive_op {

                    enum stateconnection {
                        request,
                        response,       
                    };
                    

                public:

                    receive_op(stream_socket* socket, ReceiveHandler handler,
                            receive_seq_ptr receive, const Mutable_Buffers& buff, message_flags flags) :
                    socket_(socket),
                    handler_(handler),
                    receive_(receive),
                    buff_(buff),
                    send_(),
                    state_(request),
                    flags_(flags) {
                    }

                    void run() {
                        boost::system::error_code ec;
                        operator()(ec, 0);
                    }

                    void operator()(const boost::system::error_code& ec, std::size_t bytes_transferred) {
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
                                    handler_(ERROR_ECONNREFUSED, static_cast<std::size_t> (receive_->datasize()));
                                    return;
                                }
                            }
                        }
                        handler_(ec, static_cast<std::size_t> (receive_->datasize()));
                    }
                    
                    void release(const boost::system::error_code& ec) {
                        std::cout << " FINISH pdu"  << std::endl;
                        handler_(ec, 0);
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
                                socket_->asyn_release(boost::bind(&receive_op<ReceiveHandler, Mutable_Buffers>::release, 
                                          this, boost::asio::placeholders::error), SESSION_DN_RELEASE);
                                return false;                         
                            }
                            case AB_SPDU_ID:
                            {          
                                socket_->rootcoder()->in()->clear();                                
                                socket_->rootcoder()->in()->add(receive_->options().data());
                                socket_->negotiate_session_release();
                                socket_->asyn_release(boost::bind(&receive_op<ReceiveHandler, Mutable_Buffers>::release, 
                                          this, boost::asio::placeholders::error), SESSION_AA_RELEASE);
                                return false;                         
                            }                            
                            default:
                            {
                                send_ = socket_->session_release_reaction(receive_);
                                if (send_) {
                                    boost::system::error_code ecc;
                                    state(response);
                                    operator()(ecc, 0);
                                    return false;
                                }
                                boost::system::error_code ecc;
                                socket_->close(ecc);
                                handler_(ERROR_ECONNREFUSED, 0);
                                return false;
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
                    receive_seq_ptr receive_;
                    send_seq_ptr send_;
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
                        socket_base::message_flags flags,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {
                    //BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                    if (input_empty())
                        this->get_io_service().post(boost::bind(&receive_op<ReadHandler, MutableBufferSequence>::run, receive_op<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                            receive_seq_ptr(new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers))), buffers, flags)));
                    else
                        this->super_type::async_receive(buffers, flags, handler);

                }

                template <typename MutableBufferSequence, typename ReadHandler>
                void async_read_some(const MutableBufferSequence& buffers,
                        BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                    async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                }


                isocoder_ptr  rootcoder() {
                    return rootcoder_;
                }

                isocoder_ptr  rootcoder() const {
                    return rootcoder_;
                }
                
                session_version_type session_version() const{
                    return session_version_;
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  protected member  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            protected:

                virtual send_seq_ptr session_release_reaction(receive_seq_ptr receive) {
                    if (!receive)
                        return send_seq_ptr();
                    if (rootcoder()) {
                        rootcoder()->clear();
                        rootcoder()->in()->add(receive->options().data());
                    }
                    switch (receive->type()) {
                        case FN_SPDU_ID: return send_seq_ptr(new send_seq(DN_SPDU_ID, session_option(), rootcoder()));
                        case AB_SPDU_ID: return send_seq_ptr(new send_seq(AC_SPDU_ID, session_option(), rootcoder()));
                        default:
                        {
                        }
                    }
                    return send_seq_ptr();
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

                boost::system::error_code connect_impl(const endpoint_type& peer_endpoint, 
                        boost::system::error_code& ec) {
                    if (super_type::connect(peer_endpoint, ec))
                        return connect_impl_exit(ec);

                    send_seq_ptr send_(send_seq_ptr(new send_seq(CN_SPDU_ID, session_option(), rootcoder())));
                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    if (ec)
                        return connect_impl_exit(ec);
                    receive_seq_ptr receive_(receive_seq_ptr(new receive_seq()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return connect_impl_exit(ec);
                    if (receive_->state() == receive_seq::complete) {
                        switch (receive_->type()) {
                            case AC_SPDU_ID:
                            {
                                negotiate_session_option(receive_->options());
                                rootcoder()->in()->add(receive_->options().data());
                                session_version_=(receive_->options().accept_version() & VERSIONMASK2) ? VERSION2 : VERSION1;
                                return connect_impl_exit(ec);
                            }
                            case RF_SPDU_ID:
                            {
                                boost::system::error_code ecc;
                                close(ecc);
                                return connect_impl_exit(ERROR_ECONNREFUSED);
                            }                                           
                            default:
                            {
                            }
                        }
                    }
                    return connect_impl_exit(ec = ERROR__EPROTO);
                }
                
                const boost::system::error_code& connect_impl_exit(const boost::system::error_code& err){
                    rootcoder()->out()->clear();
                    return err;
                }    
                

                boost::system::error_code release_impl(release_type type, boost::system::error_code& ec) {
                    if (is_open()) {
                        send_seq_ptr send_(new send_seq( release_type_to_spdu(type) , session_option(), rootcoder()));
                        while (!ec && !send_->ready())
                            send_->size(super_type::send(send_->pop(), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        receive_seq_ptr receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready())
                            receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                        if (ec)
                            return release_impl_exit(ec);
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case DN_SPDU_ID:
                                {
                                rootcoder()->in()->add(receive_->options().data());
                                    boost::system::error_code ecc;
                                    close(ecc);
                                    return release_impl_exit(ec);
                                }
                                case AA_SPDU_ID:
                                {
                                rootcoder()->in()->add(receive_->options().data());
                                    boost::system::error_code ecc;
                                    close(ecc);
                                    return release_impl_exit(ec);
                                }
                                default:
                                {
                                }
                            }
                        }
                        boost::system::error_code ecc;
                        close(ecc);
                    }
                    return release_impl_exit(ec = ERROR_ECONNREFUSED);
                }
                
                const boost::system::error_code& release_impl_exit(const boost::system::error_code& err){
                    rootcoder()->out()->clear();
                    return err;
                }                    

                boost::system::error_code check_accept_imp(boost::system::error_code& ec) {
                    bool canseled = false;
                    receive_seq_ptr receive_(receive_seq_ptr(new receive_seq()));
                    while (!ec && !receive_->ready()) {
                        receive_->put(super_type::receive(boost::asio::buffer(receive_->buffer()), 0, ec));
                    }
                    if (ec)
                        return check_accept_imp_exit(ec);
                    send_seq_ptr send_;

                    protocol_options options_ = session_option();
                    if (receive_->type() != CN_SPDU_ID || receive_->state() != receive_seq::complete) {
                        boost::system::error_code ecc;
                        close(ecc);
                        return check_accept_imp_exit(ERROR__EPROTO);
                    }
                    bool nouserreject = true;
                    rootcoder()->in()->add(receive_->options().data());
                    if (!negotiate_prot8327_option(options_, receive_->options()) ||
                            !(nouserreject =negotiate_session_accept())) {
                        if (!nouserreject)
                            options_.reason(REFUSE_REASON_USER);
                        canseled = true;
                        send_ = send_seq_ptr(new send_seq(RF_SPDU_ID, options_, rootcoder()));
                    }
                    else {
                        session_version_=(options_.accept_version() & VERSIONMASK2) ? VERSION2 : VERSION1;
                        send_ = send_seq_ptr(new send_seq(AC_SPDU_ID, options_, rootcoder()));
                    }

                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    if (ec)
                        return check_accept_imp_exit(ec);
                    if (canseled) {
                        boost::system::error_code ecc;
                        close(ecc);
                    }
                    else {
                        protocol_options opt = receive_->options();
                        negotiate_session_option(receive_->options());
                    }
                    return check_accept_imp_exit(ec = canseled ? ERROR_EDOM : ec);
                }
                
                const boost::system::error_code& check_accept_imp_exit(const boost::system::error_code& err){
                    rootcoder()->out()->clear();
                    return err;
                }                  

                template <typename ConstBufferSequence>
                std::size_t send_impl(const ConstBufferSequence& buffers,
                        socket_base::message_flags flags, boost::system::error_code& ec) {
                    send_seq_ptr send_(new send_seq_data<ConstBufferSequence > (buffers));
                    while (!ec && !send_->ready())
                        send_->size(super_type::send(send_->pop(), 0, ec));
                    return ec ? 0 : boost::asio::buffer_size(buffers);
                }

                template <typename MutableBufferSequence>
                std::size_t receive_impl(const MutableBufferSequence& buffers,
                        socket_base::message_flags flags, boost::system::error_code& ec) {

                    if (!input_empty())
                        return super_type::receive(boost::asio::buffer(buffers), flags, ec);

                    receive_seq_ptr receive_(new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers)));
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
                        default:
                        {
                            send_seq_ptr send_ = session_release_reaction(receive_);
                            if (send_) {
                                while (!ec && !send_->ready())
                                    send_->size(super_type::send(send_->pop(), 0, ec));
                                ec = ERROR_ECONNREFUSED;
                                boost::system::error_code ecc;
                                close(ecc);
                                return receive_->datasize();

                            }
                        }
                    }
                    boost::system::error_code ecc;
                    close(ecc);
                    ec = ERROR__EPROTO;
                    return 0;
                }

                protocol_options option_;
                isocoder_ptr rootcoder_;
                session_version_type session_version_;
                
            };






            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////    
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            //  iso8327 socket_acceptor_service //
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

            class socket_acceptor : public boost::iso::prot8073::socket_acceptor {
                
                typedef boost::iso::prot8073::socket_acceptor super_type;

            public:




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Constructors  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                

                explicit socket_acceptor(boost::asio::io_service& io_service)
                : boost::iso::prot8073::socket_acceptor(io_service) {
                }

                socket_acceptor(boost::asio::io_service& io_service,
                        const endpoint_type& endpoint, bool reuse_addr = true)
                : boost::iso::prot8073::socket_acceptor(io_service, endpoint, reuse_addr) {
                }




                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //  Accept operation  //
                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

                template <typename SocketService>
                void accept(basic_socket<protocol_type, SocketService>& peer) {
                    boost::system::error_code ec;
                    accept_impl(peer, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }

                template <typename SocketService>
                boost::system::error_code accept(
                        basic_socket<protocol_type, SocketService>& peer,
                        boost::system::error_code& ec) {
                    return accept_impl(peer, ec);
                }

                template <typename SocketService>
                void accept(basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint) {
                    boost::system::error_code ec;
                    accept_impl(peer, peer_endpoint, ec);
                    boost::asio::detail::throw_error(ec, "accept");
                }


                template <typename SocketService>
                boost::system::error_code accept(
                        basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, boost::system::error_code& ec) {
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
                    async_accept_impl(peer,  BOOST_ASIO_MOVE_CAST(AcceptHandler)(handler));
                }


                //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                     

            private:

                template <typename Handler>
                class accept_op {
                public:

                    accept_op(Handler h, stream_socket* socket)
                    : handler_(h), socket_(socket) {
                    }

                    void operator()(const boost::system::error_code& ec) {
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
                boost::system::error_code accept_impl(
                        basic_socket<protocol_type, SocketService>& peer,
                        endpoint_type& peer_endpoint, boost::system::error_code& ec) {
                    super_type::accept(peer, peer_endpoint, ec);
                    if (ec)
                        return ec;
                    static_cast<stream_socket*> (&peer)->check_accept(ec);
                    return ec;
                }

                template <typename SocketService>
                boost::system::error_code accept_impl(
                        basic_socket<protocol_type, SocketService>& peer,
                        boost::system::error_code& ec) {
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
        //  iso8327 declaration  //
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////     
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            

        class iso8327 {
        public:

            typedef boost::asio::ip::basic_endpoint<boost::asio::ip::tcp> endpoint;

            typedef session_selector selector;

            typedef transport_selector lowselector;

            static iso8327 v4() {

                return iso8327(PF_INET);
            }

            static iso8327 v6() {

                return iso8327(PF_INET6);
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

            typedef prot8327::stream_socket socket;

            typedef prot8327::socket_acceptor acceptor;

            typedef boost::asio::ip::basic_resolver<boost::asio::ip::tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
            typedef boost::asio::basic_socket_iostream<boost::asio::ip::tcp> iostream;
#endif 


            typedef boost::asio::detail::socket_option::boolean<
            IPPROTO_TCP, TCP_NODELAY> no_delay;

            /// Compare two protocols for equality.

            friend bool operator==(const iso8327& p1, const iso8327& p2) {

                return p1.family_ == p2.family_;
            }

            friend bool operator!=(const iso8327& p1, const iso8327& p2) {

                return p1.family_ != p2.family_;
            }

        private:

            explicit iso8327(int family)
            : family_(family) {
            }

            int family_;
        };

    }

    inline static bool input_empty(boost::iso::prot8327::stream_socket& s) {
        return s.input_empty();
    }


} // namespace boost



#endif  