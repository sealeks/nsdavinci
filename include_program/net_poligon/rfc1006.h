

#ifndef RFC1006_H
#define	RFC1006_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)


#include <boost/asio/detail/config.hpp>
#include <boost/asio/basic_socket_acceptor.hpp>
#include <boost/asio/basic_socket_iostream.hpp>
#include <boost/asio/basic_stream_socket.hpp>
#include <boost/asio/detail/socket_option.hpp>
#include <boost/asio/detail/socket_types.hpp>
#include <boost/asio/detail/buffer_sequence_adapter.hpp>
#include <boost/asio/ip/basic_endpoint.hpp>
#include <boost/asio/ip/basic_resolver.hpp>
#include <boost/asio/ip/basic_resolver_iterator.hpp>
#include <boost/asio/ip/basic_resolver_query.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/array.hpp>
#include <boost/bind.hpp>

#include <boost/asio/detail/push_options.hpp>


namespace boost {      
namespace asio {   
namespace ip { 
namespace iec8073 {

      


typedef std::string    transport_selector_type;
    
const std::string TKPT_START =std::string("\x3\x0",2);
const std::string NULLCHAR =std::string("\x0",1);

const std::size_t TKPT_LENGTH = 4;

const int8_t CR_TPDU_ID = '\xE0'; //connection request
const int8_t CC_TPDU_ID = '\xD0'; //connection confirm
const int8_t DR_TPDU_ID = '\x80'; //disconnection request
const int8_t DC_TPDU_ID = '\xC0'; //disconnection  confirm
const int8_t DT_TPDU_ID = '\xF0'; //data
const int8_t ED_TPDU_ID = '\x10'; //expedited data
const int8_t DA_TPDU_ID = '\x60'; //data acknowledgement
const int8_t EA_TPDU_ID = '\x20'; //expedited data acknowledgement
const int8_t RJ_TPDU_ID = '\x50'; //reject
const int8_t ER_TPDU_ID = '\x70'; //error

 enum tpdu_type {   
           NL = 0,
           CR = CR_TPDU_ID, 
           CC = CC_TPDU_ID,
           DR = DR_TPDU_ID,
           DC = DC_TPDU_ID,
           DT = DT_TPDU_ID,
           ED = ED_TPDU_ID,
           DA = DA_TPDU_ID,
           EA = EA_TPDU_ID,
           RJ = RJ_TPDU_ID,
           ER = ER_TPDU_ID};
           
inline int8_t tpdu_type_primitive(tpdu_type val){
    return static_cast<int8_t>(val);} 



tpdu_type tpdu_type_from(int8_t val);

const int8_t TPDU_SIZE8192 = '\xD'; // denied in 0 class
const int8_t TPDU_SIZE4096 = '\xC'; // denied in 0 class
const int8_t TPDU_SIZE2048 = '\xB';
const int8_t TPDU_SIZE1024 = '\xA';
const int8_t TPDU_SIZE512  = '\x9';
const int8_t TPDU_SIZE256 = '\x8';
const int8_t TPDU_SIZE128 = '\x7';
const int8_t TPDU_SIZE4 = '\x5';   /// test


 enum tpdu_size {    
    SIZENULL = 0, 
    SIZE8192 = TPDU_SIZE8192,
    SIZE4096 = TPDU_SIZE4096,
    SIZE2048 = TPDU_SIZE2048,
    SIZE1024 = TPDU_SIZE1024,
    SIZE512 = TPDU_SIZE512,
    SIZE256 = TPDU_SIZE256,
    SIZE128 = TPDU_SIZE128,
    SIZE4 = TPDU_SIZE4};
    
const boost::system::error_code ERROR__SEQ = boost::system::error_code(boost::system::errc::illegal_byte_sequence, boost::system::system_category());
const boost::system::error_code ERROR__ENOBUFS  = boost::system::error_code(boost::system::errc::no_buffer_space, boost::system::system_category());
const boost::system::error_code ERROR__EPROTO  = boost::system::error_code(boost::system::errc:: protocol_error, boost::system::system_category());
const boost::system::error_code ERROR_EFAULT  =  boost::system::error_code(boost::system::errc::bad_address, boost::system::system_category());
const boost::system::error_code ERROR_EADDRNOTAVAIL  =  boost::system::error_code(boost::system::errc::address_not_available, boost::system::system_category());
const boost::system::error_code ERROR_EDOM  =  boost::system::error_code(boost::system::errc::argument_out_of_domain, boost::system::system_category());
const boost::system::error_code ERROR_EIO  =  boost::system::error_code(boost::system::errc::io_error, boost::system::system_category());



boost::system::error_code errorcode_by_reason(int8_t val);
    
inline int8_t tpdu_type_size(tpdu_size val){
    return static_cast<int8_t>(val);} 

inline tpdu_size less_tpdu(const tpdu_size& left, const tpdu_size& right){
   if (left==right && right==SIZENULL) return SIZE2048;
   if (right==SIZENULL) return left;
   if (left==SIZENULL) return right;   
   return (tpdu_type_size(left)<tpdu_type_size(right)) ? left : right;} 

std::size_t tpdu_byte_size(tpdu_size val); 

tpdu_size tpdu_size_frombyte(int8_t val);

const int8_t ERROR_REASON_NODEF = '\x0';   // no def
const int8_t ERROR_REASON_PARAM_CODE = '\x1';   // parameter code error
const int8_t ERROR_REASON_PARAM_TYPE = '\x2';   // parameter type error
const int8_t ERROR_REASON_PARAM_VALUE = '\x3';   // parameter value error

const int8_t TPDU_ENDED = '\x80';
const int8_t TPDU_CONTINIUE = '\x0';

const int8_t WRONG_TPDU = '\xC1';

size_t getPDUsize(int8_t sz);

void generate_TKPTDU(std::string& val);

size_t getPDUsize(int8_t sz);

typedef std::pair<int8_t , std::size_t> headarvar;

typedef std::pair<headarvar , std::string> headarvarvalue;
typedef std::vector<headarvarvalue> headarvarvalues;


const int8_t VAR_TSAPREQ_ID =  '\xC1'; 
const int8_t VAR_TSAPRESP_ID = '\xC2';
const int8_t VAR_TPDU_SIZE  =  '\xC0';
const int8_t VAR_MAXTPDU_SIZE  =  '\xF0';


struct protocol_options{
    
protocol_options() :
       dst_(0), src_(0) {}     
    
protocol_options(int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues()) :
       dst_(dst), src_(src), vars_(vars) {}    
    
protocol_options(int16_t dst, int16_t src, tpdu_size pdusize, const std::string& tsapreq = "",  const std::string& tsapresp = "");

int16_t  dst_tsap() const {
   return dst_;}

void  dst_tsap(int16_t val){
    dst_=val;} 
       
int16_t  src_tsap() const {
   return src_;} 

void  src_tsap(int16_t val){
    src_=val;} 

tpdu_size pdusize() const;

void pdusize(tpdu_size val);

std::string tsapreq() const;

void tsapreq(const std::string& val);

std::string tsapresp() const;

void tsapresp(const std::string& val);

std::size_t maxpdusize() const;

void maxpdusize(std::size_t val);

private:    
    int16_t dst_; 
    int16_t src_;
    headarvarvalues vars_;
};


bool parse_vars(const std::string& str, headarvarvalues& vars);
 
std::string generate_header(int8_t type, int16_t dst, int16_t src, const headarvarvalues& vars = headarvarvalues());

std::string generate_header_TKPT_CR(const protocol_options& opt);

std::string generate_header_TKPT_CC(const protocol_options& opt);

std::string generate_header_TKPT_DR(int16_t dst, int16_t src, int8_t rsn);

std::string generate_header_TKPT_DC(int16_t dst, int16_t src);

std::string generate_header_TKPT_DT_single(const std::string& data, bool end);

std::string generate_header_TKPT_ER(int16_t dst, const std::string& errorreason = "", int8_t err = 0);




template <typename InternetProtocol>
class endpoint : public boost::asio::ip::basic_endpoint<InternetProtocol>
{
public:



  endpoint() : boost::asio::ip::basic_endpoint<InternetProtocol>(),ts_selector_()
  {
  }

  endpoint(const InternetProtocol& internet_protocol,
      unsigned short port_num, const transport_selector_type& sel = transport_selector_type())
    :  boost::asio::ip::basic_endpoint<InternetProtocol>(internet_protocol,port_num), ts_selector_(sel)
  {
  }

  endpoint(const boost::asio::ip::address& addr, unsigned short port_num, 
      const transport_selector_type& sel = transport_selector_type())
    :  boost::asio::ip::basic_endpoint<InternetProtocol>(addr,port_num), ts_selector_(sel)
  {
  }

  
  endpoint(const boost::asio::ip::basic_endpoint<tcp>& other )
    :  boost::asio::ip::basic_endpoint<InternetProtocol>(other.address(), other.port()), ts_selector_()
  {
  }
  
  
  operator  boost::asio::ip::basic_endpoint<tcp>(){
      return boost::asio::ip::basic_endpoint<tcp>();
  }

  unsigned short ts_selector() const
  {
    return ts_selector_;
  }

  void ts_selector(const transport_selector_type& sel)
  {
    ts_selector_ = sel;
  }

private:

  transport_selector_type ts_selector_;
};



namespace datail{   
     
  class receive_seq{ 
   public:
       
     enum operation_state{
       nodef,  
       complete,
       error,
       repeat,
       continuous};       
       
       receive_seq(const mutable_buffer& buff) : buff_(buff), size_(0), cursor_(0), 
                           state_(nodef), type_(NL), class_option_(0), reject_reason_(0), errcode_() {/*receive_seq_counter(1);*/}
       
       /*~receive_seq(){receive_seq_counter(-1);};*/
       
       mutable_buffer buffer(){
           return buff_;}
       
       bool ready(){ 
           std::string tmp =std::string(boost::asio::buffer_cast<const char*>(buff_),boost::asio::buffer_size(buff_));
           check();
           tmp =std::string(boost::asio::buffer_cast<const char*>(buff_),boost::asio::buffer_size(buff_));
           return (state_==error || state_==complete);}
       
       operation_state state() const{
           return state_;}
       
       tpdu_type type() const{
           return type_;}       
       
       operation_state state(operation_state val){
           return state_=val;}
     
       
       std::size_t  size(std::size_t  sz=0){
           if (!sz) return size_;
           return size_+=sz;}                   
       
       int8_t  class_option() const {
           return class_option_;} 
       
       int8_t  reject_reason() const {
           return reject_reason_;}  
       
       const protocol_options& options() const {
           return options_;} 
       
       boost::system::error_code errcode(){
           return errcode_;}     
                     

   private:
          
       void  reject_reason(int8_t val);         

       void check();
      
       operation_state check_tpdu(std::size_t& beg);
                           
       mutable_buffer    buff_;
       std::size_t       size_;
       std::size_t       cursor_;
       operation_state   state_; 
       tpdu_type         type_;
       int8_t       class_option_;
       int8_t       reject_reason_;
       protocol_options  options_;
       boost::system::error_code errcode_;
   };   
    
   typedef boost::shared_ptr<receive_seq>               receive_seq_ptr;    
    
    
   
   
   
   
    
  class send_seq{

      typedef std::vector<std::string>::iterator           lines_iterator;      
      typedef std::vector<std::string>                     lines_type;     
      
  public:  
      
      
     enum operation_state{
       nodef,  
       complete,
       error,            
       continuous};
       
      
      send_seq(const const_buffer& buff, tpdu_size pdusize): 
               state_(nodef), type_(DT) , size_(0), currentsize_(0), currentiterator_(0)  {
          constructDT(std::string(boost::asio::buffer_cast<const char*>(buff),boost::asio::buffer_size(buff)), pdusize);}
      
      send_seq(const protocol_options& opt): 
               state_(nodef), type_(CR) , size_(0), currentsize_(0), currentiterator_(0)  {
          constructCR(opt);}  
      
      send_seq(int16_t dst, const protocol_options& opt): 
               state_(nodef), type_(CC) , size_(0), currentsize_(0), currentiterator_(0)  {
          constructCC(opt);}      
      
      send_seq(int16_t dst, const std::string& errorreason, int8_t err) : 
               state_(nodef), type_(ER) , size_(0), currentsize_(0), currentiterator_(0)  {
          constructER(dst, errorreason, err );} 
      
      send_seq(int16_t dst, int16_t src, int8_t rsn) :
               state_(nodef), type_(DR) , size_(0), currentsize_(0), currentiterator_(0)  {
          constructDR(dst, src, rsn );} 
      
  
      
      
      bool ready() const{
         return (state_==complete) || (state_==error);}
      
      const_buffer pop();
      
       operation_state state() const{
           return state_;}      
      
       tpdu_type type() const{
           return type_;} 
       
       std::size_t  size(std::size_t  sz=0);  
       
       std::size_t  receivesize() const{
           return currentsize_>currentiterator_ ? currentsize_-currentiterator_  : 0;}        
       
       
      
      
  private:
      
      void constructDT(const std::string& seq, tpdu_size pdusize);
      
      void constructCR(const protocol_options& opt);
      
      void constructCC(const protocol_options& opt);      
      
      void constructER(int16_t dst, const std::string& errorreason, int8_t err); 
      
      void constructDR(int16_t dst, int16_t src, int8_t rsn);       
      
      //void constructDC(int16_t dst, int16_t src);       
      
            
      lines_type               lines_;
      lines_iterator           iterator_; 
      operation_state          state_; 
      tpdu_type                type_;     
      std::size_t              size_;  
      std::string::size_type   currentsize_; 
      std::string::size_type   currentiterator_;
  };
  
  typedef boost::shared_ptr<send_seq>               send_seq_ptr;    
    
    
    
    

    
template <typename Protocol>
class stream_socket_service
  : public boost::asio::stream_socket_service<tcp>
{
private:
  /// The type of the wrapped stream socket service.
  typedef boost::asio::stream_socket_service<tcp> service_impl_type;

public:
  /// The unique service identifier.
  static boost::asio::io_service::id id;

  /// The protocol type.
  typedef tcp protocol_type;

  /// The endpoint type.
  typedef tcp::endpoint endpoint_type;
  

  /// The implementation type of a stream socket.
  typedef service_impl_type::implementation_type implementation_type;

  /// The native type of a stream socket.
  typedef service_impl_type::native_type native_type;

  /// Construct a new stream socket service for the specified io_service.
  explicit stream_socket_service(boost::asio::io_service& io_service)
    : boost::asio::stream_socket_service<tcp>(io_service),
      service_impl_(boost::asio::use_service<service_impl_type>(io_service))
  {

  }
  
  

  boost::system::error_code open(implementation_type& impl,
      const protocol_type& protocol, boost::system::error_code& ec)
  {
    std::cout << "socket: open" << std::endl;
    return service_impl_.open(impl, protocol, ec);
  }



  /// Close a stream socket implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    std::cout << "socket: close" << std::endl;
    return service_impl_.close(impl, ec);
  }



  /// Connect the stream socket to the specified endpoint.
  boost::system::error_code connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, const protocol_options& options, boost::system::error_code& ec)
  {
    std::cout << "socket: connect" << std::endl;
    return service_impl_.connect(impl, peer_endpoint, ec);
  }

  template <typename ConnectHandler>
  class connect_op
  {
      
  enum stateconnection{
      request,
      response
   };    
   
  typedef boost::array<char, 1024>                      databuff_type;   
  typedef boost::shared_ptr< databuff_type >            databuff_type_ptr;
      
  public:
    connect_op(service_impl_type& service_impl, implementation_type& imp, ConnectHandler handler , 
            const endpoint_type& peer_endpoint, const protocol_options& opt) :
        service_impl_(service_impl),   
        impl(imp),
        handler_(handler),  
        state_(request),        
        options_(opt),
        peer_endpoint_(peer_endpoint),
        start_(1),
        send_(send_seq_ptr( new send_seq(opt))),
        receive_()
    {
        receive_arr = databuff_type_ptr( new databuff_type());
        receive_ = receive_seq_ptr( new receive_seq(mutable_buffer(receive_arr->data(),receive_arr->size())));
    }
        
    void run(){  
        service_impl_.async_connect(impl, peer_endpoint_, *this);
    }   
    
    void operator()(const boost::system::error_code& ec){
        if (!ec)
            operator()(ec,0);
        else
            handler_(protocol_options(), ec);  
    }
    
    void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred){
      if (!ec){
      switch (state_){  
      case request:{    
      switch (start_){
        case 1:{
          start_=0;
          service_impl_.async_send(impl, boost::asio::buffer(send_->pop(),send_->receivesize()) , 0 , *this);
          return;} 
        default:{
          send_->size(bytes_transferred);
          if (!send_->ready()){  
              service_impl_.async_send(impl, boost::asio::buffer(send_->pop(),send_->receivesize()) , 0 , *this); 
              return;}
          else{
              state(response);
              operator()(ec,0);
              return;}}}}
      case response:{ 
      switch (start_){          
        case 1:{
            start_=0;
            service_impl_.async_receive(impl, boost::asio::buffer(
                receive_->buffer()+receive_->size()) , 0 , *this);
			return;}
	default:{  
        receive_->size(bytes_transferred); 
        if (!receive_->ready()){
             service_impl_.async_receive(impl, boost::asio::buffer(
                receive_->buffer()+receive_->size()) , 0 , *this); 
                return;}
        finish(ec);
        return;
			}}}}}
        handler_(protocol_options(),ec);
	  } 
    
  

  private:
      
    void finish(const boost::system::error_code& ec){
       if (receive_->state()==receive_seq::complete){
            switch(receive_->type()){
            case CC:{                   
                   handler_(receive_->options(),ec);
                   std::cout << "connect_op success" << std::endl;
                   return;}
            case ER:            
            case DR:{   
                  boost::system::error_code ecc;
                  service_impl_.close(impl, ecc);
                  handler_(receive_->options(),receive_->errcode() ? receive_->errcode() : ERROR_EIO); 
                  std::cout << "connect_op refuse :" << receive_->errcode() << std::endl;
                  return;}}}
       handler_(protocol_options(),ERROR__EPROTO);}      
      
     void state(stateconnection st){
        if (state_!=st){
            state_=st;
            start_=1;}}
      
    service_impl_type&                      service_impl_;
    implementation_type&                    impl;
    ConnectHandler                          handler_;
    stateconnection                         state_;
    protocol_options                        options_;    
    endpoint_type                           peer_endpoint_;
    int                                     start_;
    send_seq_ptr                            send_;
    receive_seq_ptr                         receive_;
    databuff_type_ptr                       receive_arr;
    
  };

  /// Start an asynchronous connect.
  template <typename Handler>
  void async_connect(implementation_type& impl,
      const endpoint_type& peer_endpoint, const protocol_options& options ,Handler handler)
  {
    std::cout << "socket: asyn connect" << std::endl;
    service_impl_.get_io_service().post(boost::bind(&connect_op<Handler>::run , connect_op<Handler>(service_impl_, impl, handler,peer_endpoint, options)));
  }  
  
  
  
  
  
  template <typename AcceptHandler> 
  class accept_op
  {
      
  enum stateconnection{
      wait,
      send
   };    
   
  typedef boost::array<char, 1024>                      databuff_type;   
  typedef boost::shared_ptr< databuff_type >            databuff_type_ptr;   
      
  public:
      
    accept_op(service_impl_type& service_impl, implementation_type& imp, const protocol_options& options, AcceptHandler handler) :
        service_impl_(service_impl),   
        impl(imp),
        handler_(handler),
        state_(wait),
        options_(options),
        start_(1),
        send_(),
        receive_()       
    {  
        receive_arr = databuff_type_ptr( new databuff_type());
        receive_ = receive_seq_ptr( new receive_seq(mutable_buffer(receive_arr->data(),receive_arr->size())));
    }
        
    void run(){ 
        boost::system::error_code ec;
        operator()(ec,0);
    }   
    

    
    void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred){
      if (!ec){
      switch (state_){  
      case wait:{ 
      switch (start_){          
        case 1:{
            start_=0;
            service_impl_.async_receive(impl, boost::asio::buffer(
                receive_->buffer()+receive_->size()) , 0 , *this);
	return;}
	default:{  
        receive_->size(bytes_transferred); 
        if (!receive_->ready()){
             service_impl_.async_receive(impl, boost::asio::buffer(
                receive_->buffer()+receive_->size()) , 0 , *this); 
                return;}
        parse_response(ec);
        return;}}}          
      case send:{    
      switch (start_){
        case 1:{
          start_=0;
          service_impl_.async_send(impl, boost::asio::buffer(send_->pop(),
                                   send_->receivesize()) , 0 , *this);
          return;} 
        default:{
          send_->size(bytes_transferred);
          if (!send_->ready()){  
              service_impl_.async_send(impl, boost::asio::buffer(send_->pop(),
                                       send_->receivesize()) , 0 , *this); 
              return;}
          finish(ec);
          return;}}}}}    
      handler_(options_, ec);}    

    

  private:
      
     void parse_response(const boost::system::error_code& ec){
       if (receive_->type()!=CR || receive_->state()!=receive_seq::complete){
           handler_(protocol_options(),ERROR__EPROTO);
           return;}
       options_=protocol_options(receive_->options().src_tsap(),options_.src_tsap(),
                       less_tpdu(receive_->options().pdusize(),options_.pdusize()),
                       options_.tsapreq(), receive_->options().tsapreq());
       send_ = send_seq_ptr( new send_seq(1,options_));
       state(send);
       operator()(ec,0);}      
      
    void finish(const boost::system::error_code& ec){
       if (send_->state()==send_seq::complete){
                protocol_options  opt = receive_->options();
                opt.pdusize(options_.pdusize());
                handler_(opt, ec);
                std::cout << "accept_op success" << std::endl;
                return;}
       handler_(protocol_options(),ERROR__EPROTO);}    
    
      
     void state(stateconnection st){
        if (state_!=st){
            state_=st;
            start_=1;}}
     
     
      
    service_impl_type&                      service_impl_;
    implementation_type&                    impl;
    AcceptHandler                           handler_;    
    stateconnection                         state_;
    protocol_options                        options_;
    int                                     start_;
    send_seq_ptr                            send_;
    receive_seq_ptr                         receive_;
    databuff_type_ptr                       receive_arr;
    
  }; 
  
  
  template <typename Handler>  
  void asyn_check_accept(implementation_type& impl, const protocol_options& options, Handler handler){  
      //std::cout << "sevice socket: check_accept" << std::endl;
      service_impl_.get_io_service().post(boost::bind(&accept_op<Handler>::run , accept_op<Handler>(service_impl_, impl, options, handler)));
  }
  
  template <typename SendHandler, typename Const_Buffers>
  class send_op
  {
  public:
    send_op(service_impl_type& service_impl, implementation_type& imp, SendHandler handler , 
            const Const_Buffers& buffers, tpdu_size pdusize , boost::asio::socket_base::message_flags flags) :
        service_impl_(service_impl),   
        impl(imp),
        handler_(handler),      
        in_(send_seq_ptr( new send_seq(buffers, pdusize))),
        flags_(flags),        
        send_lower_(boost::asio::buffer_size(buffers)),
        start_(1)    
        
    {
    }
        
    void run(){
        boost::system::error_code ec;     
        operator()(ec,0);
    }   

    void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred){
      if (!ec){
      switch (start_){
        case 1:{
          start_=0;
          service_impl_.async_send(impl, boost::asio::buffer(in_->pop(),in_->receivesize()) , flags_ , *this);
          return;} 
        default:{
          in_->size(bytes_transferred);
          if (!in_->ready()){  
              service_impl_.async_send(impl, boost::asio::buffer(in_->pop(),in_->receivesize()) , flags_ , *this); 
              return;
          }}}}
        handler_(ec, static_cast<const std::size_t&>(send_lower_));}
    

  private:
      
    service_impl_type&                      service_impl_;
    implementation_type&                    impl;
    SendHandler                             handler_; 
    send_seq_ptr                            in_;
    boost::asio::socket_base::message_flags flags_;
    std::size_t                             send_lower_;
    int                                     start_;

      
  };
  

  template <typename ConstBufferSequence>
  std::size_t send(implementation_type& impl,
      const ConstBufferSequence& buffers,
      socket_base::message_flags flags, tpdu_size tpdusize, boost::system::error_code& ec)
  {
    return service_impl_.send(impl, buffers, flags, ec);
  }  

  /// Start an asynchronous send.
  template <typename Const_Buffers, typename Handler>
  void async_send(implementation_type& impl, const Const_Buffers& buffers,
      boost::asio::socket_base::message_flags flags, tpdu_size tpdusize , Handler handler)
  {
    //logger_.log("Starting asynchronous send");
    service_impl_.get_io_service().post(boost::bind(&send_op<Handler,Const_Buffers>::run , send_op<Handler,Const_Buffers>(service_impl_, 
                                        impl, handler, buffers , tpdusize ,  flags)));
   
  }
  
  
   

  
  
  template <typename ReceiveHandler,typename Mutable_Buffers>
  class receive_op
  {
  public:
    receive_op(service_impl_type& service_impl, implementation_type& imp, ReceiveHandler handler , 
            receive_seq_ptr out, const Mutable_Buffers& buff ,boost::asio::socket_base::message_flags flags) :
        service_impl_(service_impl),   
        impl(imp),
        handler_(handler),      
        out_(out),
        buff_(buff),        
        flags_(flags),
        start_(1)   
        
    {}
        
    void run(){
        boost::system::error_code ec;      
        operator()(ec,0);
    }   

    void operator()(const boost::system::error_code& ec,  std::size_t bytes_transferred){
      std::size_t n = 0;
      if (!ec){
      switch (start_)
      {
        case 1:{
            start_=0;
            service_impl_.async_receive(impl, boost::asio::buffer(
                out_->buffer()+out_->size()) , flags_ , *this);;
	return;}
	default:{  
        
        out_->size(bytes_transferred); 
        if (!out_->ready()){   
             service_impl_.async_receive(impl, boost::asio::buffer(
                out_->buffer()+out_->size()) , flags_ , *this); 
                return;}

        }}};
        handler_(ec, static_cast<const std::size_t&>(out_->size()));}
    

  private:
      
    service_impl_type&                      service_impl_;
    implementation_type&                    impl;
    ReceiveHandler                          handler_;
    const Mutable_Buffers&                  buff_;
    receive_seq_ptr                         out_;
    boost::asio::socket_base::message_flags flags_;   
    int                                     start_;    
  };  

  /// Receive some data from the peer.
  template <typename Mutable_Buffers>
  std::size_t receive(implementation_type& impl,
      const Mutable_Buffers& buffers,
      boost::asio::socket_base::message_flags flags,
      boost::system::error_code& ec)
  {
    //logger_.log("Receiving data on socket");
    return service_impl_.receive(impl, buffers, flags, ec);
  }


  /// Start an asynchronous receive.
  template <typename Mutable_Buffers, typename Handler>
  void async_receive(implementation_type& impl, const Mutable_Buffers& buffers,
      boost::asio::socket_base::message_flags flags, Handler handler)
  {
    service_impl_.get_io_service().post(boost::bind(&receive_op<Handler, Mutable_Buffers>::run , receive_op<Handler, Mutable_Buffers>(service_impl_, 
                                        impl, handler,
                                        receive_seq_ptr( new receive_seq(boost::asio::detail::buffer_sequence_adapter< boost::asio::mutable_buffer, Mutable_Buffers>::first(buffers))), buffers , flags)));    
  }
     
private:
    
  service_impl_type& service_impl_;
  
  
 
};

template <typename Protocol>
boost::asio::io_service::id stream_socket_service<Protocol>::id;
}




class stream_socket : public basic_stream_socket<tcp , datail::stream_socket_service<tcp> >{   
    
public:  
    
   explicit stream_socket(boost::asio::io_service& io_service, tpdu_size pdusize = SIZE2048)
    : basic_stream_socket<tcp, datail::stream_socket_service<tcp> >(io_service),  option_(0,1, pdusize,"","SERVER-TSEL"), pdusize_(pdusize)
  {
  }

  stream_socket(boost::asio::io_service& io_service,
      const endpoint_type& endpoint, tpdu_size pdusize = SIZE2048)
    : basic_stream_socket<tcp, datail::stream_socket_service<tcp> >(io_service, endpoint), option_(0,1, pdusize,"","SERVER-TSEL"), pdusize_(pdusize)
  {
  }
  
  
  void connect(const endpoint_type& peer_endpoint)
  {
    boost::system::error_code ec;
    if (!is_open())
    {
      this->get_service().open(this->get_implementation(),
          peer_endpoint.protocol(), ec);
      boost::asio::detail::throw_error(ec, "connect");
    }
    this->get_service().connect(this->get_implementation(), peer_endpoint, prot_option() , ec);
    boost::asio::detail::throw_error(ec, "connect");
  }


  boost::system::error_code connect(const endpoint_type& peer_endpoint,
      boost::system::error_code& ec)
  {
    if (!is_open())
    {
      if (this->get_service().open(this->get_implementation(),
            peer_endpoint.protocol(), ec))
      {
        return ec;
      }
    }

    return this->get_service().connect(
        this->get_implementation(), peer_endpoint, prot_option(), ec);
  }
  
  
  template <typename ConnectHandler> 
  class connect_op{
  public:
      connect_op(stream_socket* socket, ConnectHandler handler, const endpoint_type& peer_endpoint): 
       socket_(socket), handler_(handler), peer_endpoint_(peer_endpoint) {}
      
      void run(){
          socket_->get_service().async_connect<connect_op>(socket_->get_implementation(),
          peer_endpoint_, socket_->prot_option(), *this );
      }
      
      void operator()(const protocol_options& option, const boost::system::error_code& ec){
          if (!ec){
              socket_->correspond_prot_option(option);}
          handler_(ec);}
      
  private:
      stream_socket* socket_;
      ConnectHandler handler_;
      endpoint_type peer_endpoint_;
  };


  template <typename ConnectHandler>
  void async_connect(const endpoint_type& peer_endpoint,
      BOOST_ASIO_MOVE_ARG(ConnectHandler) handler)
  {
    BOOST_ASIO_CONNECT_HANDLER_CHECK(ConnectHandler, handler) type_check;

    if (!is_open())
    {
      boost::system::error_code ec;
      const protocol_type protocol = peer_endpoint.protocol();
      if (this->get_service().open(this->get_implementation(), protocol, ec))
      {
        this->get_io_service().post(
            boost::asio::detail::bind_handler(
              BOOST_ASIO_MOVE_CAST(ConnectHandler)(handler), ec));
        return;
      }
    }
    this->get_io_service().post(boost::bind(&connect_op<ConnectHandler>::run,connect_op<ConnectHandler>(const_cast<stream_socket*>(this), handler, peer_endpoint)));
  }  

  
  template <typename AcceptHandler> 
  class check_accept_op{
  public:
      check_accept_op(stream_socket* socket, AcceptHandler handler): 
       socket_(socket), handler_(handler) {}
      
      void run(){
         socket_->get_service().asyn_check_accept<check_accept_op>(socket_->get_implementation(),
         socket_->prot_option(), *this );
      }
      
      void operator()(const protocol_options& option, const boost::system::error_code& ec){
          if (!ec){
              socket_->correspond_prot_option(option);}
          handler_(ec);}
      
  private:
      stream_socket* socket_;
      AcceptHandler  handler_;
  }; 
  
  
   template <typename AcceptHandler>  
   void asyn_check_accept(AcceptHandler handler, int16_t  src){
       option_.src_tsap(src);
       this->get_io_service().post(boost::bind(&check_accept_op<AcceptHandler>::run,
              check_accept_op<AcceptHandler>(const_cast<stream_socket*>(this), handler)));
   }
   
   
   

  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers)
  {
    return send(buffers,0);
  }


  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags)
  {
    boost::system::error_code ec;
    std::size_t s = this->get_service().send(
        this->get_implementation(), buffers, flags, pdusize_,  ec);
    boost::asio::detail::throw_error(ec, "send");
    return s;
  }

  template <typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags, boost::system::error_code& ec)
  {
    return this->get_service().send(
        this->get_implementation(), buffers, flags, pdusize_, ec);
  }


  template <typename ConstBufferSequence, typename WriteHandler>
  void async_send(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
     async_send(buffers, 0, handler); 
  }


  template <typename ConstBufferSequence, typename WriteHandler>
  void async_send(const ConstBufferSequence& buffers,
      socket_base::message_flags flags,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {

    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

    this->get_service().async_send(this->get_implementation(), buffers, flags, pdusize_,
        BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }   
   
   
  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers)
  {
    boost::system::error_code ec;
    std::size_t s = this->get_service().send(
        this->get_implementation(), buffers, 0, pdusize_, ec);
    boost::asio::detail::throw_error(ec, "write_some");
    return s;
  }

  template <typename ConstBufferSequence>
  std::size_t write_some(const ConstBufferSequence& buffers,
      boost::system::error_code& ec)
  {
    return this->get_service().send(this->get_implementation(), buffers, 0, pdusize_, ec);
  }

  template <typename ConstBufferSequence, typename WriteHandler>
  void async_write_some(const ConstBufferSequence& buffers,
      BOOST_ASIO_MOVE_ARG(WriteHandler) handler)
  {
    BOOST_ASIO_WRITE_HANDLER_CHECK(WriteHandler, handler) type_check;

    this->get_service().async_send(this->get_implementation(),
        buffers, 0, pdusize_ ,BOOST_ASIO_MOVE_CAST(WriteHandler)(handler));
  }   
  
  
   
   tpdu_size pdusize() const{
       return pdusize_;
   }; 
   
   const protocol_options& prot_option() const{
       return option_;}
   
   void correspond_prot_option(const protocol_options& val){       
       pdusize_=val.pdusize();
       std::cout << "correspond_prot_option tpdu size: " << tpdu_byte_size(pdusize_) << std::endl;
       option_.dst_tsap(val.src_tsap());
       std::cout << "correspond_prot_option req  : " << val.tsapreq() << std::endl;
       std::cout << "correspond_prot_option resp  : " << val.tsapresp() << std::endl;       
       std::cout << "correspond_prot_option dst id : " << option_.dst_tsap() << std::endl;
       std::cout << "correspond_prot_option src id : " << option_.src_tsap() << std::endl;} 
   

   private:
       protocol_options option_;
       tpdu_size        pdusize_;
};



////  Acceptor


namespace datail{

template <typename Protocol>
class socket_acceptor_service
  : public boost::asio::socket_acceptor_service<tcp> 
{
public:

  typedef boost::asio::socket_acceptor_service<tcp> service_impl_type;

  /// The protocol type.
  typedef tcp protocol_type;

  /// The endpoint type.
  typedef tcp::endpoint endpoint_type;
  

  /// The implementation type of a stream socket.
  typedef service_impl_type::implementation_type implementation_type;

  /// The native type of a stream socket.
  typedef service_impl_type::native_type native_type;
  
  static boost::asio::io_service::id id;


  /// Construct a new socket acceptor service for the specified io_service.
  explicit socket_acceptor_service(boost::asio::io_service& io_service)
    : boost::asio::socket_acceptor_service<tcp> (io_service),
      service_impl_(boost::asio::use_service<service_impl_type>(io_service)), src_(0)
  {
  }
  



  /// Close a socket acceptor implementation.
  boost::system::error_code close(implementation_type& impl,
      boost::system::error_code& ec)
  {
    std::cout << "socket acceptor: close" << std::endl; 
    return service_impl_.close(impl, ec);
  }



  /// Accept a new connection.
  template <typename SocketService>
  boost::system::error_code accept(implementation_type& impl,
      basic_socket<protocol_type, SocketService>& peer,
      endpoint_type* peer_endpoint, boost::system::error_code& ec)
  {
    std::cout << "socket acceptor: accept" << std::endl;
    return service_impl_.accept(impl, peer, peer_endpoint, ec);
  }


  
  template <typename Handler, typename Socket>
  class accept_handler
  {
  public:
    accept_handler(service_impl_type& service_impl, implementation_type& impl, Handler h, Socket& socket, endpoint_type* endpoint, int16_t  src) 
      : service_impl_(service_impl), impl_(impl), handler_(h), socket_(socket), endpoint_(endpoint), src_(src)
    {
    }
      
    void run(){
        service_impl_.async_accept(impl_, socket_, endpoint_, *this);
    }  

    void operator()(const boost::system::error_code& ec)
    {
      if (!ec){      
        static_cast<stream_socket*>(&socket_)->asyn_check_accept<Handler>(handler_, src_);
        std::cout << "Asynchronous accept  succeeded first" << std::endl;
        return;}
      handler_(ec);
    }

  private:
    service_impl_type&   service_impl_; 
    implementation_type& impl_;
    Handler              handler_;
    Socket&              socket_;
    endpoint_type*       endpoint_;
    int16_t         src_;

  }; 
  
  
  /// Start an asynchronous accept.
  template <typename SocketService, typename AcceptHandler>
  void async_accept(implementation_type& impl,
      basic_socket<protocol_type, SocketService>& peer,
      endpoint_type* peer_endpoint, AcceptHandler handler)
  {
    std::cout << "socket acceptor: asynaccept" << std::endl;
    service_impl_.get_io_service().post(boost::bind(&accept_handler<AcceptHandler, basic_socket<protocol_type, SocketService> >::run ,
                        accept_handler<AcceptHandler , basic_socket<protocol_type, SocketService> >(service_impl_, impl, handler, peer, peer_endpoint, src())));
  }
  


private:
 
  int16_t  src() const{
     return src_=((src_+1) ? (src_+1) : 1);}
    
  service_impl_type&           service_impl_;
  mutable int16_t         src_;  
};


template <typename Protocol>
boost::asio::io_service::id socket_acceptor_service<Protocol>::id;



}



class socket_acceptor : public basic_socket_acceptor<tcp , datail::socket_acceptor_service<tcp> >{
    
public:
  
    

  explicit socket_acceptor(boost::asio::io_service& io_service)
    : basic_socket_acceptor<tcp , datail::socket_acceptor_service<tcp> >(io_service)
  {
  }

  socket_acceptor(boost::asio::io_service& io_service,
      const endpoint_type& endpoint, bool reuse_addr = true)
    : basic_socket_acceptor<tcp, datail::socket_acceptor_service<tcp> >(io_service, endpoint, reuse_addr)
  {

  }

};




}


class rfc1006
{
public:
  /// The type of a TCP endpoint.
  typedef basic_endpoint<tcp>          endpoint;

  /// (Deprecated: use resolver::query.) The type of a resolver query.
  typedef basic_resolver_query<rfc1006>   resolver_query;

  /// (Deprecated: use resolver::iterator.) The type of a resolver iterator.
  typedef basic_resolver_iterator<rfc1006> resolver_iterator;

  /// Construct to represent the IPv4 TCP protocol.
  static rfc1006 v4()
  {
    return rfc1006(PF_INET);
  }

  /// Construct to represent the IPv6 TCP protocol.
  static rfc1006 v6()
  {
    return rfc1006(PF_INET6);
  }

  /// Obtain an identifier for the type of the protocol.
  int type() const
  {
    return SOCK_STREAM;
  }

  /// Obtain an identifier for the protocol.
  int protocol() const
  {
    return IPPROTO_TCP;
  }

  /// Obtain an identifier for the protocol family.
  int family() const
  {
    return family_;
  }

  /// The TCP socket type.
  typedef iec8073::stream_socket socket;

  /// The TCP acceptor type.
  typedef iec8073::socket_acceptor acceptor;

  /// The TCP resolver type.
  typedef basic_resolver<tcp> resolver;

#if !defined(BOOST_NO_IOSTREAM)
  /// The TCP iostream type.
  typedef basic_socket_iostream<tcp> iostream;
#endif // !defined(BOOST_NO_IOSTREAM)


  typedef boost::asio::detail::socket_option::boolean<
    IPPROTO_TCP, TCP_NODELAY> no_delay;

  /// Compare two protocols for equality.
  friend bool operator==(const rfc1006& p1, const rfc1006& p2)
  {
    return p1.family_ == p2.family_;
  }

  /// Compare two protocols for inequality.
  friend bool operator!=(const rfc1006& p1, const rfc1006& p2)
  {
    return p1.family_ != p2.family_;
  }

private:
  // Construct with a specific family.
  explicit rfc1006(int family)
    : family_(family)
  {
  }

  int family_;
};




} // namespace ip



} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif	/* RFC1006_H */

