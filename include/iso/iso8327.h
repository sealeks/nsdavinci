

#ifndef         ISOPROT8327_H_H
#define	ISOPROT8327_H_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
#pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <iso/iso.h>
#include <boost/asio/detail/push_options.hpp>

#include <kernel/constdef.h>
#include <kernel/utils.h>



namespace boost {
    namespace asio {
        namespace iso {
            namespace prot8327 {


                //using  
                // SPDU type


                //  Kernel
                
                const std::string SEND_HEADER=std::string("\x1\x0\x1\x0",4);
                
                const int8_t WORK_PROT_OPTION='\x0';
                const int8_t WORK_PROT_VERSION='\x2';                

                typedef  uint8_t        spdu_type;

                const spdu_type CN_SPDU_ID = 13;  //CONNECT SPDU
                const spdu_type OA_SPDU_ID = 16;   //OVERFLOW ACCEPT
                const spdu_type CDO_SPDU_ID = 15; //CONNECT DATA OVERFLOW
                const spdu_type AC_SPDU_ID = 14;   //ACCEPT
                const spdu_type RF_SPDU_ID = 12;    //REFUSE 
                const spdu_type FN_SPDU_ID = 9;      //FINISH 
                const spdu_type DN_SPDU_ID = 10;    //DISCONNECT
                const spdu_type NF_SPDU_ID = 8;      //NOT FINISHED
                const spdu_type AB_SPDU_ID = 25;    //ABORT
                const spdu_type AA_SPDU_ID = 26;   //ABORT ACCEPT
                const spdu_type DT_SPDU_ID = 1;     //DATA TRANSFER 
                const spdu_type PR_SPDU_ID = 7;      //PREPARE 

                //  Negotiated realease

                //const spdu_type NF_SPDU_ID = 8;      //NOT FINISHED
                //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
                //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS

                //half-duplex
                const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
                const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS               

                //duplex      
                //

                //expedited data functional unit;
                const spdu_type EX_SPDU_ID = 5;     //EXPEDITED

                //typed data functional unit
                const spdu_type TD_SPDU_ID = 33;  //TYPED DATA

                //capability data exchange functional unit;
                const spdu_type CD_SPDU_ID = 61;   //CAPABILITY DATA
                const spdu_type CDA_SPDU_ID = 62; //CAPABILITY DATA ACK

                // minor synchronize functional unit;
                const spdu_type MIP_SPDU_ID = 49;      //MINOR SYNC POINT
                const spdu_type MIA_SPDU_ID = 50;    //MINOR SYNC ACK
                //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
                //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS   

                // symmetric synchronize functional unit;                
                //const spdu_type MIP_SPDU_ID = 49;      //MINOR SYNC POINT
                //const spdu_type MIA_SPDU_ID = 50;    //MINOR SYNC ACK  

                //major synchronize functional unit;
                const spdu_type MAP_SPDU_ID = 41;   //MAJOR SYNC POINT
                const spdu_type MAA_SPDU_ID = 42;    //MAJOR SYNC ACK 
                //const spdu_type PR_SPDU_ID = 7;      //PREPARE               
                //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
                //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS   

                // resynchronize functional unit     
                const spdu_type RS_SPDU_ID = 53;     //RESYNCHRONIZE        
                const spdu_type RA_SPDU_ID = 34;     //RESYNCHRONIZE ACK
                //const spdu_type PR_SPDU_ID = 7;      //PREPARE 

                //exceptions functional unit;                 
                const spdu_type ER_SPDU_ID = 0;    //EXCEPTION REPORT
                const spdu_type ED_SPDU_ID = 48;   //EXCEPTION DATA


                const spdu_type AS_SPDU_ID = 45;    //ACTIVITY START
                const spdu_type AR_SPDU_ID = 29;     //ACTIVITY RESUME       
                const spdu_type AI_SPDU_ID = 25;     //ACTIVITY INTERRUPT               
                const spdu_type AIA_SPDU_ID = 26;      //ACTIVITY INTERRUPT ACK 
                const spdu_type AD_SPDU_ID = 57;    //ACTIVITY DISCARD
                const spdu_type ADA_SPDU_ID = 58;   //ACTIVITY DISCARD ACK
                const spdu_type AE_SPDU_ID = 41;    //ACTIVITY END
                const spdu_type AEA_SPDU_ID = 42;     //ACTIVITY END ACK   

                //const spdu_type GT_SPDU_ID = 1;   //GIVE TOKENS
                //const spdu_type  PT_SPDU_ID = 2;           //PLEASE TOKENS
                //const spdu_type PR_SPDU_ID = 7;      //PREPARE               
                const spdu_type GTC_SPDU_ID = 21;      //GIVE TOKENS CONFIRM
                const spdu_type GTA_SPDU_ID = 22;    //GIVE TOKENS ACK


                //  Function unit

                const int16_t FU_HALFDUPLEX = 0x1;  //half-duplex functional unit;            
                const int16_t FU_DUPLEX = 0x2;   // duplex functional unit;
                const int16_t FU_EXPDATA = 0x4;  //expedited data functional unit;            
                const int16_t FU_MINORSYNC = 0x8;   // minor synchronize functional unit;
                const int16_t FU_MAJORORSYNC = 0x10;  //major synchronize functional unit;         
                const int16_t FU_RESYNC = 0x20;   // resynchronize functional unit;;
                const int16_t FU_ACTIVEMG = 0x40;  //activity management functional unit;            
                const int16_t FU_NEGOTREL = 0x80;   // negotiated release functional unit;               
                const int16_t FU_CAPABDATA = 0x100;   //capability data exchange functional unit;
                const int16_t FU_EXCEPTION = 0x200;   //exceptions functional unit; 
                const int16_t FU_TYPEDDATA = 0x400;   //typed data functional unit; 
                const int16_t FU_SYMSYNC = 0x800;   //symmetric synchronize functional unit;  
                const int16_t FU_DATASEP = 0x1000;   //data separation functional unit;
                
                
                const int16_t FU_WORK = FU_DUPLEX ;   //work;


                typedef  uint8_t        varid_type;

                const varid_type  PGI_CN_IND = 1; // Connection Identifier              
                const varid_type  PGI_CN_AC = 5; // Connect/Accept Item
                //const varid_type    PGI_CN_AC = 33; // AR  SPDU Linking Information         

                const varid_type  PI_PROPT =       19;       // Protocol Options
                const varid_type  PI_TSDUMAX = 21; // TSDU Maximum Size              
                const varid_type  PI_VERS =         22; // Version Number  

                const varid_type PI_SUREQ = 20;                  //Session User Requirements               
                const varid_type PI_CALLING = 51;              //Calling Session Selector
                const varid_type PI_CALLED = 52;                //Responding Session Selector
                const varid_type PI_DTOVER = 60;              //  Data Overflow 
                const varid_type PI_USERDATA = 193;        //User Data        
                const varid_type PI_EXUSERDATA = 194;    //Extended User Data
                const varid_type PI_ENCLOSURE = 25;        //Enclosure Item
                const varid_type PI_REASON = 50;               //Reason Code 
                const varid_type PI_TRANDISK = 17;           //Transport Disconnect                

                const std::size_t  triple_npos = static_cast<std::size_t> (0xFFFF + 1);

                inline static std::string to_triple_size(std::size_t val) {
                    return  (val < 0xFF) ? inttype_to_str(static_cast<uint8_t> (val)) : ( (val < triple_npos) ? ("\xFF" +  inttype_to_str(endiancnv_copy(static_cast<uint16_t> (val)))) : "");
                }

                inline static bool valid_triple_size(const std::string& val) {
                    return  !((!val.size()) || (val[0] == '\xFF' && val.size() < 3));
                }

                // return triple_npos if no success
                std::size_t from_triple_size(const std::string& val, std::size_t& it);


                typedef std::pair<std::size_t, std::string>                           parameter_ln_type;
                typedef std::pair<varid_type, parameter_ln_type>           pi_type;
                typedef std::map<varid_type, parameter_ln_type>          pgi_type;
                typedef std::pair<varid_type,  pgi_type>                            pgis_type;
                typedef std::map<varid_type,  pgi_type>                           spdudata_type;  // (it->first==0 contain pi_type in vector

                class spdudata  : protected spdudata_type {
                public:

                    spdudata() : spdudata_type() , type_(0), error_(false) {
                    }

                    explicit spdudata(spdu_type spdu) : spdudata_type(), type_(spdu), error_(false)  {
                    }

                    explicit spdudata(const std::string& vl) : spdudata_type(), seq_( vl), type_(0) , error_(false) {
                        parse();
                    }

                    spdu_type type() const {
                        return type_;
                    }

                    bool error() const {
                        return error_;
                    }

                    void setPGI(varid_type cod1 , varid_type cod2 , const std::string& val = "");

                    void setPGI(varid_type cod1 , varid_type cod2, int8_t val);

                    void setPGI(varid_type cod1 , varid_type cod2, uint8_t val);

                    void setPGI(varid_type cod1 , varid_type cod2, int16_t val);

                    void setPGI(varid_type cod1 , varid_type cod2, uint16_t val);


                    void setPI(varid_type cod , const std::string& val = "");

                    void setPI(varid_type cod, int8_t val);

                    void setPI(varid_type cod, uint8_t val);

                    void setPI(varid_type cod, int16_t val);

                    void setPI(varid_type cod, uint16_t val);


                    bool getPGI(varid_type cod1 , varid_type cod2,  std::string& val) const;

                    bool getPGI(varid_type cod1 , varid_type cod2,  int8_t& val, int8_t def = 0) const;

                    bool getPGI(varid_type cod1 , varid_type cod2,  uint8_t& val, uint8_t def = 0) const;

                    bool getPGI(varid_type cod1 , varid_type cod2,  int16_t& val, int16_t def = 0) const;

                    bool getPGI(varid_type cod1 , varid_type cod2,  uint16_t& val, uint16_t def = 0) const;

                    bool getPI(varid_type cod, std::string& val) const;

                    bool getPI(varid_type cod,  int8_t& val, int8_t def = 0) const;

                    bool getPI(varid_type cod,  uint8_t& val, uint8_t def = 0)  const;

                    bool getPI(varid_type cod,  int16_t& val, int16_t def = 0)  const;

                    bool getPI(varid_type cod,  uint16_t& val, uint16_t def = 0)  const;


                    bool existPGI(varid_type cod1 , varid_type cod2) const;

                    bool existPI(varid_type cod) const;

                    bool nullPGI(varid_type cod1 , varid_type cod2) const;

                    bool nullPI(varid_type cod) const;


                    std::size_t getPGIsize(varid_type cod1 , varid_type cod2) const;

                    std::size_t getPIsize(varid_type cod) const;

                    const std::string&  sequence() const;




                private:
                    
                    bool error(bool val){
                        return error_=val;
                    }

                    bool parse();
                    bool parse_vars(const std::string& vl);        
                    bool parse_pgi(varid_type tp, const std::string& vl);                            

                    mutable std::string seq_;
                    spdu_type type_;
                    bool  error_;

                } ;

                //test

                std::ostream& operator<<(std::ostream& strm, const spdudata& vrs);

                struct protocol_options {

                    protocol_options() {
                    }

                    protocol_options(int16_t dst, int16_t src, const spdudata& vars = spdudata()) :
                    vars_(vars) {
                    }

                    protocol_options(const std::string& called = "",  const std::string& calling = "");

                    std::string ssap_calling() const;

                    void ssap_calling(const std::string & val);

                    std::string ssap_called() const;

                    void ssap_called(const std::string & val);

                private:
                    spdudata  vars_;
                } ;
                
                
                
  
                
                template <typename ConstBufferSequence>
                class  data_send_buffer_impl : public send_buffer_impl {
                public:

                    data_send_buffer_impl(const ConstBufferSequence& buff) : send_buffer_impl() {
                        iterator_ = buff_.begin();
                    }

                    void construct(const  ConstBufferSequence& buff)  {
                        header_ = SEND_HEADER;
                        buff_.push_back(const_buffs_ptr( new  const_buffers_1(const_buffer(header_.data(), header_.size()))));
                        buff_.push_back(const_buffs_ptr( new  const_buffers_1(buff)));
                    }

                private:
                    std::string header_;
                } ;  
                
                
                 
                
                
                std::string generate_header_CN(const protocol_options& opt, const std::string& data ="");  //CONNECT SPDU
                
                 std::string generate_header_AC(const protocol_options& opt, const std::string& data ="");  //ACCEPT SPDU
                 
                 std::string generate_header_RF(const std::string& data ="");  //REFUSE  SPDU                     
                 
                 std::string generate_header_DN(const std::string& data ="");  //DISCONNECT  SPDU          
                 
                 std::string generate_header_AB(const std::string& data ="");  //ABORT SPDU                     
                 
                 std::string generate_header_AA(const std::string& data ="");  //ABORT ACCEPT  SPDU         
                 
                 std::string generate_header_FN(const std::string& data ="");  //FINISH SPDU                     
                 
                 std::string generate_header_NF(const std::string& data ="");  //NOT FINISH  SPDU                      

           
                ////  send_seq                

                class send_seq {
                public:

                    send_seq(spdu_type type):  type_(type){
                        
                    }
                    send_seq(spdu_type type, const protocol_options& opt, const std::string data="") :
                    type_(type)   {
                        switch(type){
                            case CN_SPDU_ID: {constructCN(opt, data); break;}
                            case AC_SPDU_ID: {constructAC(opt, data); break;}
                            default:{
                                buf_ = send_buffer_ptr( new sevice_send_buffer_impl(""));
                            }
                        }
                    }
                    
                    virtual ~send_seq() {
                    }

                    bool ready() const {
                        return (!buf_) ||  (buf_->ready());
                    }

                    const_buffers_1 pop() {
                        return ready()  ?  const_buffers_1(const_buffer()) : buf_->pop();
                    }

                    std::size_t  size(std::size_t  sz) {
                        return ready() ? 0 : buf_->size(sz);
                    }

                    std::size_t  receivesize() const {
                        return ready() ? 0 : buf_->receivesize();
                    }

                    spdu_type type() const {
                        return type_;
                    }




                protected:


                    void constructCN(const protocol_options& opt, const std::string& data){
                            buf_ = send_buffer_ptr( new sevice_send_buffer_impl(generate_header_CN(opt,data)));}
                    
                    void constructAC(const protocol_options& opt, const std::string& data){
                            buf_ = send_buffer_ptr( new sevice_send_buffer_impl(generate_header_AC(opt,data)));}                    



                    spdu_type                          type_;
                    send_buffer_ptr              buf_;
                } ;

                typedef boost::shared_ptr<send_seq>               send_seq_ptr;
                
                

                template <typename ConstBufferSequence >
                class send_seq_data  : public send_seq {
                public:

                    send_seq_data(const ConstBufferSequence& buff) : send_seq(DN_SPDU_ID) {
                        constructDT(buff);
                    }

                protected:

                    void constructDT(const ConstBufferSequence& buff) {
                        buf_ = send_buffer_ptr( new data_send_buffer_impl<ConstBufferSequence > (buff));
                    }

                } ;
                
                
                

            }
        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	

