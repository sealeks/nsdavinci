

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

                    protocol_options(const std::string& called,  const std::string& calling = "");

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
                
                
                
                //receive_seq
                
                const std::size_t SI_WITH_LI = 2; 
                const std::size_t HDR_LI = 2;                

                class receive_seq {
                public:

                    typedef std::vector<int8_t>                                                                                data_type;
                    typedef boost::shared_ptr< data_type >                                                          data_type_ptr;

                    enum operation_state {
                        waittype,
                        waitsize,                        
                        waitheader,
                        waitdata,
                        complete,
                        error
                    } ;

                    receive_seq(const mutable_buffer& buff, std::size_t waitingsize, bool ef);

                    receive_seq();

                    mutable_buffer buffer();

                    void  put(std::size_t  sz);

                    bool ready() const {
                        return (state_ == error || state_ == complete);
                    }

                    operation_state state() const {
                        return state_;
                    }

                    spdu_type  type() const {
                        return type_;
                    }

                    bool eof() const {
                        return eof_;
                    }

                    std::size_t  datasize() const {
                        return datasize_;
                    }

                    std::size_t  waitdatasize() const {
                        return waitdatasize_;
                    }

                    int8_t  class_option() const {
                        return class_option_;
                    }

                    int8_t  reject_reason() const {
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

                    boost::system::error_code errcode( const boost::system::error_code& err);

                    void  reject_reason(int8_t val);

                    boost::system::error_code check_type();
                    
                    boost::system::error_code check_size();                    

                    boost::system::error_code check_header();



                    operation_state                        state_;
                    std::size_t                                size_;
                    std::size_t                                estimatesize_;
                    std::size_t                                datasize_;
                    std::size_t                                waitdatasize_;
                    spdu_type                                type_;
                    bool                                         next_;                    
                    int8_t                                        class_option_;
                    int8_t                                        reject_reason_;
                    protocol_options                     options_;
                    boost::system::error_code     errcode_;
                    bool                                           eof_;

                    data_type_ptr                         type_data;
                    mutable_buffer                      type_buff_;
                    data_type_ptr                         header_data;
                    mutable_buffer                      header_buff_;
                    mutable_buffer                       userbuff_;


                } ;  
                
                typedef boost::shared_ptr<receive_seq>               receive_seq_ptr;                
                
                
                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //////////////////stream_socket                
                ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////       

                class stream_socket : public basic_stream_socket<boost::asio::ip::tcp > {
                public:

                    explicit stream_socket(boost::asio::io_service& io_service, const session_selector& ssel = session_selector() )
                    : basic_stream_socket<boost::asio::ip::tcp>(io_service),  option_( ssel.called(), ssel.calling() ), waiting_data_size_(0), eof_state_(true) {
                    }

                    stream_socket(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, const session_selector& ssel = session_selector())
                    : basic_stream_socket<boost::asio::ip::tcp >(io_service, endpoint), option_ (ssel.called(), ssel.calling()), waiting_data_size_(0), eof_state_(true) {
                    }


                    // Available

                    std::size_t available() const {
                        boost::system::error_code ec;
                        std::size_t s = available(ec);
                        boost::asio::detail::throw_error(ec, "available");
                        return s;
                    }

                    std::size_t available(boost::system::error_code& ec) const {
                        std::size_t s = this->get_service().available(this->get_implementation(), ec);
                        if (ec) return 0;
                        return waiting_data_size_ < s ? waiting_data_size_ : s;
                    }
                    
                    
                    // Data indication true is end od block

                    bool dataindication() const {
                        return is_open() && !waiting_data_size();
                    }

                 


                    ///   Connect operation  ///

                    void connect(const endpoint_type& peer_endpoint) {

                        boost::system::error_code ec;
                        connect(peer_endpoint, ec);
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code connect(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {
                        if (!is_open()) {
                            if (this->get_service().open(this->get_implementation(),
                                    peer_endpoint.protocol(), ec)) {
                                return ec;
                            }
                        }
                        return connect_impl(peer_endpoint, ec);
                    }


                    // connect handler

                    template <typename ConnectHandler>
                    class connect_op {

                        enum stateconnection {
                            request,
                            response
                        } ;

                    public:

                        connect_op(stream_socket* socket , ConnectHandler handler ,
                                const endpoint_type& peer_endpoint) :
                        socket_(socket),
                        handler_(handler),
                        state_(request),
                        options_(socket->prot_option()),
                        peer_endpoint_(peer_endpoint),
                        send_(send_seq_ptr( new send_seq(CN_SPDU_ID,socket->prot_option()))),
                        receive_(new receive_seq()) {
                        }

                        void run() {

                            socket_->get_service().async_connect(socket_->get_implementation(), peer_endpoint_, *this);
                        }

                        void operator()(const boost::system::error_code& ec) {
                            if (!ec)
                                operator()(ec, 0);

                            else
                                handler_( ec);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case request:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);
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
                                            socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()), 0 , *this);
                                            return;
                                        }
                                        finish(ec);

                                        return;
                                    }
                                }
                            }
                            handler_(ec);
                        }



                    private:

                        void finish(const boost::system::error_code& ec) {
                            if (receive_->state() == receive_seq::complete) {
                                switch (receive_->type()) {
                                    case AC_SPDU_ID:
                                    {
                                        socket_->correspond_prot_option(receive_->options());
                                        handler_(ec);
                                        std::cout << "connect_op success" << std::endl;
                                        return;
                                    }
                                    /*case ER:
                                    case DR:
                                    {
                                        boost::system::error_code ecc;
                                        socket_->get_service().close(socket_->get_implementation() , ecc);
                                        handler_(receive_->errcode() ? receive_->errcode() : ERROR_EIO);
                                        std::cout << "connect_op refuse :" << receive_->errcode() << std::endl;

                                        return;
                                    }*/
                                }
                            }
                            handler_(ERROR__EPROTO);
                        }

                        void state(stateconnection st) {
                            if (state_ != st) {

                                state_ = st;
                            }
                        }

                        stream_socket*                           socket_;
                        ConnectHandler                          handler_;
                        stateconnection                          state_;
                        protocol_options                        options_;
                        endpoint_type                             peer_endpoint_;
                        send_seq_ptr                               send_;
                        receive_seq_ptr                           receive_;

                    } ;

                    template <typename ConnectHandler>
                    void async_connect(const endpoint_type& peer_endpoint,
                            BOOST_ASIO_MOVE_ARG(ConnectHandler) handler) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

                        if (!is_open()) {
                            boost::system::error_code ec;
                            const protocol_type protocol = peer_endpoint.protocol();
                            if (this->get_service().open(this->get_implementation(), protocol, ec)) {
                                this->get_io_service().post(
                                        boost::asio::detail::bind_handler(
                                        BOOST_ASIO_MOVE_CAST(ConnectHandler)(handler), ec));

                                return;
                            }
                        }
                        this->get_io_service().post(boost::bind(&connect_op<ConnectHandler>::run, connect_op<ConnectHandler > (const_cast<stream_socket*> (this), handler, peer_endpoint)));
                    }





                    ///   Releease operation  ///    

                    void releaseconnect(int8_t rsn) {

                        boost::system::error_code ec;
                        releaseconnect(rsn, ec);
                        boost::asio::detail::throw_error(ec, "releaseconnect");
                    }

                    boost::system::error_code releaseconnect(int8_t rsn, boost::system::error_code& ec) {

                        return releaseconnect_impl(rsn, ec);
                    }

                    template <typename ReleaseHandler>
                    class releaseconnect_op {
                    public:

                        releaseconnect_op(stream_socket*  socket, ReleaseHandler handler, int8_t rsn) :
                        socket_(socket),
                        handler_(handler),
                        send_(send_seq_ptr( new send_seq(DN_SPDU_ID,socket->prot_option()))) {
                        }

                        void run() {

                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            std::size_t n = 0;
                            if (!ec) {
                                send_->size(bytes_transferred);
                                if (!send_->ready()) {
                                    socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()) , 0 , *this);

                                    return;
                                }
                            }
                            handler_(ec);
                        }


                    private:
                        stream_socket*                                              socket_;
                        ReleaseHandler                                              handler_;
                        send_seq_ptr                                                  send_;
                    } ;

                    template <typename ReleaseHandler>
                    void asyn_releaseconnect(BOOST_ASIO_MOVE_ARG(ReleaseHandler) handler,
                            int8_t rsn = 0) {
                        BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;
                        if (is_open()) {
                            this->get_io_service().post(boost::bind(&releaseconnect_op<ReleaseHandler>::run,
                                    releaseconnect_op<ReleaseHandler > (const_cast<stream_socket*> (this), handler, rsn)));
                        }

                        else
                            handler(ERROR_ECONNREFUSED);
                    }






                    ///  Check Accept operation  ///

                    void  check_accept(int16_t  src = 1) {

                        boost::system::error_code ec;
                        boost::asio::detail::throw_error(ec, "connect");
                    }

                    boost::system::error_code  check_accept(int16_t  src,  boost::system::error_code& ec) {

                        return check_accept_imp(src, ec);
                    }

                    template <typename CheckAcceptHandler>
                    class accept_op {

                        enum stateconnection {
                            wait,
                            send,
                            refuse
                        } ;

                    public:

                        accept_op(stream_socket* socket,  CheckAcceptHandler handler) :
                        socket_(socket),
                        handler_(handler),
                        state_(wait),
                        options_(socket->prot_option()),
                        send_(),
                        receive_(new receive_seq()) {
                        }

                        void run() {

                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                switch (state_) {
                                    case wait:
                                    {
                                        receive_->put(bytes_transferred);
                                        if (!receive_->ready()) {
                                            socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()) , 0 , *this);
                                            return;
                                        }
                                        parse_response(ec);
                                        return;
                                    }
                                    case send:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                    send_->receivesize()) , 0 , *this);
                                            return;
                                        }
                                        finish(ec);
                                        return;
                                    }
                                    case refuse:
                                    {
                                        send_->size(bytes_transferred);
                                        if (!send_->ready()) {
                                            socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(send_->pop(),
                                                    send_->receivesize()) , 0 , *this);
                                            return;
                                        }
                                        boost::system::error_code ecc;
                                        socket_->get_service().close(socket_->get_implementation(), ecc);
                                        handler_(ERROR_EDOM);

                                        return;
                                    }
                                }
                            }
                            handler_(ec);
                        }



                    private:

                        void parse_response(const boost::system::error_code& ec) {
                            if (receive_->type() != CN_SPDU_ID || receive_->state() != receive_seq::complete) {
                                boost::system::error_code ecc;
                                socket_->get_service().close(socket_->get_implementation(), ecc);
                                handler_(ERROR__EPROTO);
                                return;
                            }
                            /*if (!options_.tsap_called().empty() && options_.tsap_called() != receive_->options().tsap_called()) {
                                send_ = send_seq_ptr( new send_seq(receive_->options().src_tsap(), options_.src_tsap(), REJECT_REASON_ADDR));
                                state(refuse);
                                operator()(ec, 0);

                                return;
                            }
                            options_ = protocol_options(receive_->options().src_tsap(), options_.src_tsap(),
                                    less_tpdu(receive_->options().pdusize(), options_.pdusize()),
                                    options_.tsap_calling(), receive_->options().tsap_calling());*/
                            send_ = send_seq_ptr( new send_seq(1, options_));
                            state(send);
                            operator()(ec, 0);
                        }

                        void finish(const boost::system::error_code& ec) {

                            protocol_options  opt = receive_->options();
                            //opt.pdusize(options_.pdusize());
                            socket_->correspond_prot_option(opt);
                            handler_(ec);
                            std::cout << "accept_op success" << std::endl;
                        }

                        void state(stateconnection st) {

                            if (state_ != st)
                                state_ = st;
                        }



                        stream_socket*                              socket_;
                        CheckAcceptHandler                    handler_;
                        stateconnection                            state_;
                        protocol_options                          options_;
                        send_seq_ptr                                 send_;
                        receive_seq_ptr                             receive_;

                    } ;

                    template <typename CheckAcceptHandler>
                    void asyn_check_accept(CheckAcceptHandler handler, int16_t  src) {

                        //option_.src_tsap(src);
                        this->get_io_service().post(boost::bind(&accept_op<CheckAcceptHandler>::run,
                                accept_op<CheckAcceptHandler > (const_cast<stream_socket*> (this), handler)));
                    }






                    ///   Send operation  ///                          

                    template <typename ConstBufferSequence>
                    std::size_t send(const ConstBufferSequence& buffers) {

                        return send(buffers, 0);
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags) {
                        boost::system::error_code ec;
                        std::size_t s = send(buffers, flags,  ec);
                        boost::asio::detail::throw_error(ec, "send");

                        return s;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t write_some(const ConstBufferSequence& buffers) {
                        boost::system::error_code ec;
                        std::size_t s = send(buffers, 0,  ec);
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

                    template <typename SendHandler, typename ConstBufferSequence>
                    class send_op {
                    public:

                        send_op(stream_socket*   socket, SendHandler handler ,
                                const ConstBufferSequence& buffers, boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        in_(send_seq_ptr( new send_seq_data<ConstBufferSequence>(buffers))),
                        flags_(flags),
                        send_lower_(boost::asio::buffer_size(buffers)) {
                        }

                        void run() {

                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            if (!ec) {
                                in_->size(bytes_transferred);
                                if (!in_->ready()) {
                                    socket_->get_service().async_send(socket_->get_implementation(), boost::asio::buffer(in_->pop(), in_->receivesize()) , flags_ , *this);

                                    return;
                                }
                            }
                            handler_(ec, static_cast<std::size_t> (send_lower_));
                        }


                    private:

                        stream_socket*                                             socket_;
                        SendHandler                                                  handler_;
                        send_seq_ptr                                                 in_;
                        boost::asio::socket_base::message_flags flags_;
                        std::size_t                                                       send_lower_;


                    } ;

                    template <typename ConstBufferSequence, typename WriteHandler>
                    void async_send(const ConstBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                        async_send(buffers, 0, handler);
                    }

                    template <typename ConstBufferSequence, typename WriteHandler>
                    void async_send(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags,
                            BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                        BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;
                        this->get_io_service().post(boost::bind(&send_op<WriteHandler, ConstBufferSequence>::run, send_op<WriteHandler, ConstBufferSequence > (const_cast<stream_socket*> (this), handler, buffers, flags)));
                    }

                    template <typename ConstBufferSequence, typename WriteHandler>
                    void async_write_some(const ConstBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(WriteHandler) handler) {

                        async_send<ConstBufferSequence, WriteHandler > (buffers, 0, handler);
                    }







                    ///   receive operation  ///     

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers) {

                        return receive<MutableBufferSequence > (buffer, 0);
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags) {
                        boost::system::error_code ec;
                        std::size_t s = receive( buffers, flags, ec);
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
                        std::size_t s =  receive(buffers, 0, ec);
                        boost::asio::detail::throw_error(ec, "read_some");

                        return s;
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {

                        return receive_impl(buffers, flags, ec);
                    }

                    template <typename ReceiveHandler, typename Mutable_Buffers>
                    class receive_op {
                    public:

                        receive_op(stream_socket*   socket, ReceiveHandler handler ,
                                receive_seq_ptr receive, const Mutable_Buffers& buff , boost::asio::socket_base::message_flags flags) :
                        socket_(socket),
                        handler_(handler),
                        receive_(receive),
                        buff_(buff),
                        flags_(flags) {
                        }

                        void run() {

                            boost::system::error_code ec;
                            operator()(ec, 0);
                        }

                        void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred) {
                            std::size_t n = 0;
                            if (!ec) {
                                receive_->put(bytes_transferred);
                                if (!receive_->ready()) {
                                    socket_->get_service().async_receive(socket_->get_implementation(), boost::asio::buffer(receive_->buffer()) , flags_ , *this);
                                    return;
                                }

                                if (!success()) return;
                            }
                            socket_->waiting_data_size(receive_->waitdatasize(), receive_->eof());
                            handler_(ec, static_cast<std::size_t> (receive_->datasize()));
                        }


                    private:

                        bool success() {
                            switch (receive_->type()) {
                                case  DT_SPDU_ID:
                                {
                                    return true;
                                }
                                /*case ER:
                                {
                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_( ERROR__SEQ,  static_cast<std::size_t> (receive_->datasize()));
                                    break;
                                }
                                case DR:
                                {
                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_( ERROR_ECONNREFUSED ,  static_cast<std::size_t> (receive_->datasize()));
                                    break;
                                }*/
                                default:
                                {

                                    boost::system::error_code ecc;
                                    socket_->get_service().close(socket_->get_implementation(), ecc);
                                    handler_(ERROR__EPROTO ,  0);
                                }
                            }

                            return false;
                        }

                        stream_socket*                                              socket_;
                        ReceiveHandler                                              handler_;
                        const Mutable_Buffers&                               buff_;
                        receive_seq_ptr                                             receive_;
                        boost::asio::socket_base::message_flags flags_;
                    } ;

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_receive(const MutableBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                        async_receive<MutableBufferSequence, ReadHandler > (buffers, handler, 0 );
                    }

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_receive(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                        BOOST_ASIO_READ_HANDLER_CHECK(ReadHandler, handler) type_check;

                        this->get_io_service().post(boost::bind(&receive_op<ReadHandler, MutableBufferSequence>::run, receive_op<ReadHandler, MutableBufferSequence > (const_cast<stream_socket*> (this), handler,
                                receive_seq_ptr( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state())), buffers, flags)));

                    }

                    template <typename MutableBufferSequence, typename ReadHandler>
                    void async_read_some(const MutableBufferSequence& buffers,
                            BOOST_ASIO_MOVE_ARG(ReadHandler) handler) {

                        async_receive<MutableBufferSequence, ReadHandler > (buffers, 0, handler);
                    }
                    
                    






                private:
                    
                    

                    const protocol_options& prot_option() const {

                        return option_;
                    }

                    void correspond_prot_option(const protocol_options& val) {


                        //std::cout << "correspond_prot_option tpdu size: " << tpdu_byte_size(pdusize_) << std::endl;
                        //option_.dst_tsap(val.src_tsap());
                        //std::cout << "correspond_prot_option calling  : " << val.tsap_calling() << std::endl;
                        //std::cout << "correspond_prot_option called  : " << val.tsap_called() << std::endl;
                       //std::cout << "correspond_prot_option dst id : " << option_.dst_tsap() << std::endl;
                       // std::cout << "correspond_prot_option src id : " << option_.src_tsap() << std::endl;
                    }
                   
                    std::size_t  waiting_data_size() const {
                        return waiting_data_size_;
                    }

                    void  waiting_data_size( std::size_t val, bool st) {
                        //std::cout << "waitig data : " << val <<  " eof:" << st << std::endl;
                        eof_state_ = st;
                        waiting_data_size_ = val;
                    }

                    std::size_t  eof_state() const {
                        return eof_state_;
                    }

                    boost::system::error_code connect_impl(const endpoint_type& peer_endpoint,
                            boost::system::error_code& ec) {

                        if (this->get_service().connect(this->get_implementation(), peer_endpoint, ec))
                            return ec;

                        send_seq_ptr  send_ (send_seq_ptr( new send_seq( CN_SPDU_ID, prot_option())));
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        if (ec)
                            return ec;
                        receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->put(this->get_service().receive(this->get_implementation(), boost::asio::buffer(receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        if (receive_->state() == receive_seq::complete) {
                            switch (receive_->type()) {
                                case  AC_SPDU_ID:
                                {
                                    correspond_prot_option(receive_->options());
                                    return ec;
                                }
                                /**case ER:
                                case DR:
                                {
                                    boost::system::error_code ecc;
                                    this->get_service().close(this->get_implementation() , ecc);

                                    return ec = receive_->errcode() ? receive_->errcode() : ERROR_EIO;
                                }*/
                                default:
                                {
                                    ec = ERROR__EPROTO;
                                }
                            }
                        }
                        return ec = ERROR__EPROTO;
                    }

                    boost::system::error_code releaseconnect_impl(int8_t rsn, boost::system::error_code& ec) {
                        if (is_open()) {
                            send_seq_ptr  send_ (send_seq_ptr( new send_seq( DN_SPDU_ID)));
                            while (!ec && !send_->ready())
                                send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));

                            return ec;
                        }
                        return ec =  ERROR_ECONNREFUSED;
                    }

                    boost::system::error_code  check_accept_imp(int16_t  src,  boost::system::error_code& ec) {
                       // option_.src_tsap(src);
                        bool canseled = false;
                       /* receive_seq_ptr   receive_(receive_seq_ptr(new receive_seq()));
                        while (!ec && !receive_->ready()) {
                            receive_->put(this->get_service().receive(this->get_implementation(), boost::asio::buffer(receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return ec;
                        send_seq_ptr  send_ ;
                        protocol_options options_ = this->prot_option();
                        if (receive_->type() != CR || receive_->state() != receive_seq::complete) {
                            return ERROR__EPROTO;
                        }
                        if (!options_.tsap_called().empty() && options_.tsap_called() != receive_->options().tsap_called()) {
                            canseled = true;
                            send_ = send_seq_ptr( new send_seq(receive_->options().src_tsap(), options_.src_tsap(), REJECT_REASON_ADDR));
                        }
                        else {
                            options_ = protocol_options(receive_->options().src_tsap(), options_.src_tsap(),
                                    less_tpdu(receive_->options().pdusize(), options_.pdusize()),
                                    options_.tsap_calling(), receive_->options().tsap_calling());
                            send_ = send_seq_ptr( new send_seq(1, options_));
                        }
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        if (ec)
                            return ec;
                        if (canseled ) {
                            boost::system::error_code ecc;
                            this->get_service().close(this->get_implementation(), ecc);
                        }
                        else {

                            protocol_options  opt = receive_->options();
                            opt.pdusize(options_.pdusize());
                            correspond_prot_option(receive_->options());
                        }*/
                        return ec = canseled ? ERROR_EDOM : ec;
                    }

                    template <typename ConstBufferSequence>
                    std::size_t send_impl(const ConstBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        send_seq_ptr  send_( new send_seq_data<ConstBufferSequence > (buffers));
                        while (!ec && !send_->ready())
                            send_->size( this->get_service().send(this->get_implementation(), boost::asio::buffer(send_->pop(), send_->receivesize()), 0, ec));
                        return ec ? 0 : boost::asio::buffer_size(buffers);
                    }

                    template <typename MutableBufferSequence>
                    std::size_t receive_impl(const MutableBufferSequence& buffers,
                            socket_base::message_flags flags, boost::system::error_code& ec) {
                        receive_seq_ptr receive_( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, MutableBufferSequence>::first(buffers), waiting_data_size(), eof_state()));
                        while (!ec && !receive_->ready()) {
                            receive_->put(this->get_service().receive(this->get_implementation(), boost::asio::buffer(
                                    receive_->buffer()) , 0, ec));
                        }
                        if (ec)
                            return 0;
                        switch (receive_->type()) {

                            case DT_SPDU_ID:
                            {
                                waiting_data_size(receive_->waitdatasize(), receive_->eof());
                                return receive_->datasize();
                            }
                           /* case DR:
                            {
                                boost::system::error_code ecc;
                                this->get_service().close(this->get_implementation(), ecc);
                                ec = ( receive_->type() == DR)  ? ERROR_ECONNREFUSED :  ERROR__SEQ ;
                                return static_cast<std::size_t> (receive_->datasize());
                            }*/
                        }
                        boost::system::error_code ecc;
                        this->get_service().close(this->get_implementation(), ecc);
                        ec = ERROR__EPROTO;
                        return 0;
                    }


                    tpdu_size                                         pdusize_;
                    protocol_options                           option_;
                    std::size_t                                        waiting_data_size_;
                    bool                                                eof_state_;
                } ;



                ////  Acceptor


                namespace datail {

                    template <typename Protocol>
                    class socket_acceptor_service
                    : public boost::asio::socket_acceptor_service<boost::asio::ip::tcp> {
                    public:

                        typedef boost::asio::socket_acceptor_service<boost::asio::ip::tcp> service_impl_type;

                        /// The protocol type.
                        typedef boost::asio::ip::tcp protocol_type;

                        /// The endpoint type.
                        typedef boost::asio::ip::tcp::endpoint endpoint_type;

                        typedef service_impl_type::implementation_type implementation_type;

                        typedef service_impl_type::native_type native_type;

                        static boost::asio::io_service::id id;

                        explicit socket_acceptor_service(boost::asio::io_service& io_service)
                        : boost::asio::socket_acceptor_service<Protocol> (io_service),
                        service_impl_(boost::asio::use_service<service_impl_type>(io_service)), src_(0) {
                        }

                        template <typename SocketService>
                        boost::system::error_code accept(implementation_type& impl,
                                basic_socket<protocol_type, SocketService>& peer,
                                endpoint_type* peer_endpoint, boost::system::error_code& ec) {
                            if (!service_impl_.accept(impl, peer, peer_endpoint, ec)) {
                                if (static_cast<stream_socket*> (&peer)->check_accept(src(), ec)) {
                                    boost::system::error_code ecc;
                                    static_cast<stream_socket*> (&peer)->close(ecc);
                                }
                            }
                            return ec;
                        }

                        template <typename Handler, typename Socket>
                        class accept_handler {
                        public:

                            accept_handler(service_impl_type& service_impl, implementation_type& impl, Handler h, Socket& socket, endpoint_type* endpoint, int16_t  src)
                            : service_impl_(service_impl), impl_(impl), handler_(h), socket_(socket), endpoint_(endpoint), src_(src) {
                            }

                            void run() {
                                service_impl_.async_accept(impl_, socket_, endpoint_, *this);
                            }

                            void operator()(const boost::system::error_code& ec) {
                                if (!ec) {
                                    static_cast<stream_socket*> (&socket_)->asyn_check_accept<Handler > (handler_, src_);
                                    std::cout << "Asynchronous accept  succeeded first" << std::endl;
                                    return;
                                }
                                handler_(ec);
                            }

                        private:
                            service_impl_type&       service_impl_;
                            implementation_type& impl_;
                            Handler                           handler_;
                            Socket&                           socket_;
                            endpoint_type*              endpoint_;
                            int16_t                             src_;
                        } ;


                        /// Start an asynchronous accept.

                        template <typename SocketService, typename AcceptHandler>
                        void async_accept(implementation_type& impl,
                                basic_socket<protocol_type, SocketService>& peer,
                                endpoint_type* peer_endpoint, AcceptHandler handler) {

                            service_impl_.get_io_service().post(boost::bind(&accept_handler<AcceptHandler, basic_socket<protocol_type, SocketService> >::run ,
                                    accept_handler<AcceptHandler , basic_socket<protocol_type, SocketService> >(service_impl_, impl, handler, peer, peer_endpoint, src())));
                        }


                    private:

                        int16_t  src() const {
                            boost::mutex::scoped_lock(mtx);
                            return src_ = ((src_ + 1) ? (src_ + 1) : 1);
                        }

                        service_impl_type&            service_impl_;
                        mutable int16_t                src_;
                        boost::mutex                       mtx;

                    } ;


                    template <typename Protocol>
                    boost::asio::io_service::id socket_acceptor_service<Protocol>::id;
                }

                class socket_acceptor : public basic_socket_acceptor<boost::asio::ip::tcp , datail::socket_acceptor_service<boost::asio::ip::tcp> > {
                public:

                    explicit socket_acceptor(boost::asio::io_service& io_service)
                    : basic_socket_acceptor<boost::asio::ip::tcp , datail::socket_acceptor_service<boost::asio::ip::tcp> >(io_service) {
                    }

                    socket_acceptor(boost::asio::io_service& io_service,
                            const endpoint_type& endpoint, bool reuse_addr = true)
                    : basic_socket_acceptor<boost::asio::ip::tcp, datail::socket_acceptor_service<boost::asio::ip::tcp> >(io_service, endpoint, reuse_addr) {
                    }

                } ;

            }                
                
   
        }

    } // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	

