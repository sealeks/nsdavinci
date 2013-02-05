#ifndef	_P_EXAMPLE_1_H_
#define	_P_EXAMPLE_1_H_

#include <iso/asn/asnbase.h>


#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065)
 #endif


const boost::array<boost::asio::asn::oidindx_type, 11 >  P_EXAMPLE_1_OID_ARR = { 1  ,  3  ,  6  ,  1  ,  4  ,  1  ,  3817  ,  999  ,  1  ,  1  ,  1 };
const boost::asio::asn::oid_type P_EXAMPLE_1_OID = boost::asio::asn::oid_type(P_EXAMPLE_1_OID_ARR);

namespace P_EXAMPLE_1  {


	using  boost::asio::asn::null_type;
 	using  boost::asio::asn::enumerated_type;
 	using  boost::asio::asn::bitstring_type;
 	using  boost::asio::asn::octetstring_type;
 	using  boost::asio::asn::oid_type;
 	using  boost::asio::asn::reloid_type;
 	using  boost::asio::asn::utctime_type;
 	using  boost::asio::asn::gentime_type;
 	using  boost::asio::asn::ia5string_type;
 	using  boost::asio::asn::printablestring_type;
 	using  boost::asio::asn::visiblestring_type;
 	using  boost::asio::asn::visiblestring_type;
 	using  boost::asio::asn::numericstring_type;
 	using  boost::asio::asn::universalstring_type;
 	using  boost::asio::asn::bmpstring_type;
 	using  boost::asio::asn::utf8string_type;
 	using  boost::asio::asn::generalstring_type;
 	using  boost::asio::asn::graphicstring_type;
 	using  boost::asio::asn::t61string_type;
 	using  boost::asio::asn::t61string_type;
 	using  boost::asio::asn::videotexstring_type;
 	using  boost::asio::asn::any_type;

	//  type is  CHOICE
	struct  CM_apdu;

 	//  type is  CHOICE
	struct  DATA_apdu;

 	//  type is  preextend SEQUENCE
	struct  DATA_REQ_apdu__impl;

 	//  type is  preextend SEQUENCE
	struct  DATA_RSP_apdu__impl;

 	//  type is extended  GraphicString
	BOOST_ASN_EXPLICIT_TYPEDEF(CM_CONNECT_REQ_apdu , graphicstring_type , 0  ,APPLICATION_CLASS)
 
 
 	//  type is extended  GraphicString
	BOOST_ASN_EXPLICIT_TYPEDEF(CM_CONNECT_RSP_apdu , graphicstring_type , 1  ,APPLICATION_CLASS)
 
 
 	//  type is extended  GraphicString
	BOOST_ASN_EXPLICIT_TYPEDEF(CM_RELEASE_REQ_apdu , graphicstring_type , 2  ,APPLICATION_CLASS)
 
 
 	//  type is extended  GraphicString
	BOOST_ASN_EXPLICIT_TYPEDEF(CM_RELEASE_RSP_apdu , graphicstring_type , 3  ,APPLICATION_CLASS)
 
 
 	//  type is extended  GraphicString
	BOOST_ASN_EXPLICIT_TYPEDEF(CM_ABORT_apdu , graphicstring_type , 4  ,APPLICATION_CLASS)
 
 
 	//  type is extended  SEQUENCE
	BOOST_ASN_EXPLICIT_TYPEDEF(DATA_REQ_apdu , DATA_REQ_apdu__impl , 0  ,APPLICATION_CLASS)
 
 
 	//  type is extended  SEQUENCE
	BOOST_ASN_EXPLICIT_TYPEDEF(DATA_RSP_apdu , DATA_RSP_apdu__impl , 1  ,APPLICATION_CLASS)
 
 
 //start==============================================================
//It is   SEQUENCE  

	struct  DATA_RSP_apdu__impl{



		int  msgId;
		graphicstring_type  information;

		DATA_RSP_apdu__impl()  : msgId() , information()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_BIND_TAG(msgId);
			BOOST_ASN_BIND_TAG(information);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  DATA_REQ_apdu__impl{



		int  msgId;
		graphicstring_type  information;

		DATA_REQ_apdu__impl()  : msgId() , information()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_BIND_TAG(msgId);
			BOOST_ASN_BIND_TAG(information);
		}
	};

//end==============================================================
//start==============================================================
//It is   CHOICE

	enum DATA_apdu_enum {
		DATA_apdu_null = 0  , 
		DATA_apdu_DATA_REQ_apdu , 
		DATA_apdu_DATA_RSP_apdu , 
	};

	struct  DATA_apdu : public BOOST_ASN_CHOICE_STRUCT(DATA_apdu_enum) {


		DATA_apdu() : BOOST_ASN_CHOICE_STRUCT(DATA_apdu_enum) ()  {}


		BOOST_ASN_VALUE_CHOICE(req, DATA_REQ_apdu,  DATA_apdu_DATA_REQ_apdu)
		BOOST_ASN_VALUE_CHOICE(rsp, DATA_RSP_apdu,  DATA_apdu_DATA_RSP_apdu)

		 template<typename Archive> void serialize(Archive& arch){

			if (arch.__input__()){
				int __tag_id__ =arch.test_id();
				switch(arch.test_class()){
					case 0x0: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0x40: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0xC0: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0x80: {
						switch(__tag_id__){
						default:{}}
						;}
					default:{
						 if(BOOST_ASN_BIND_TAG(value<DATA_REQ_apdu > (true , DATA_apdu_DATA_REQ_apdu))) return; 
					 if(BOOST_ASN_BIND_TAG(value<DATA_RSP_apdu > (true , DATA_apdu_DATA_RSP_apdu))) return; 
					;}}}
			else {
				 switch(type()){
					case DATA_apdu_DATA_REQ_apdu: {BOOST_ASN_BIND_TAG(value<DATA_REQ_apdu > (false , DATA_apdu_DATA_REQ_apdu)); break;}
					case DATA_apdu_DATA_RSP_apdu: {BOOST_ASN_BIND_TAG(value<DATA_RSP_apdu > (false , DATA_apdu_DATA_RSP_apdu)); break;}
					default:{}}}
		}
	};

//start==============================================================
//It is   CHOICE

	enum CM_apdu_enum {
		CM_apdu_null = 0  , 
		CM_apdu_CM_CONNECT_REQ_apdu , 
		CM_apdu_CM_CONNECT_RSP_apdu , 
		CM_apdu_CM_RELEASE_REQ_apdu , 
		CM_apdu_CM_RELEASE_RSP_apdu , 
		CM_apdu_CM_ABORT_apdu , 
	};

	struct  CM_apdu : public BOOST_ASN_CHOICE_STRUCT(CM_apdu_enum) {


		CM_apdu() : BOOST_ASN_CHOICE_STRUCT(CM_apdu_enum) ()  {}


		BOOST_ASN_VALUE_CHOICE(connect_req, CM_CONNECT_REQ_apdu,  CM_apdu_CM_CONNECT_REQ_apdu)
		BOOST_ASN_VALUE_CHOICE(connect_rsp, CM_CONNECT_RSP_apdu,  CM_apdu_CM_CONNECT_RSP_apdu)
		BOOST_ASN_VALUE_CHOICE(release_req, CM_RELEASE_REQ_apdu,  CM_apdu_CM_RELEASE_REQ_apdu)
		BOOST_ASN_VALUE_CHOICE(release_rsp, CM_RELEASE_RSP_apdu,  CM_apdu_CM_RELEASE_RSP_apdu)
		BOOST_ASN_VALUE_CHOICE(abort, CM_ABORT_apdu,  CM_apdu_CM_ABORT_apdu)

		 template<typename Archive> void serialize(Archive& arch){

			if (arch.__input__()){
				int __tag_id__ =arch.test_id();
				switch(arch.test_class()){
					case 0x0: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0x40: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0xC0: {
						switch(__tag_id__){
						default:{}}
						;}
					case 0x80: {
						switch(__tag_id__){
						default:{}}
						;}
					default:{
						if(BOOST_ASN_BIND_TAG(value<CM_CONNECT_RSP_apdu > (true , CM_apdu_CM_CONNECT_RSP_apdu))) return; 
						 if(BOOST_ASN_BIND_TAG(value<CM_CONNECT_REQ_apdu > (true , CM_apdu_CM_CONNECT_REQ_apdu))) return; 

					 if(BOOST_ASN_BIND_TAG(value<CM_RELEASE_REQ_apdu > (true , CM_apdu_CM_RELEASE_REQ_apdu))) return; 
					 if(BOOST_ASN_BIND_TAG(value<CM_RELEASE_RSP_apdu > (true , CM_apdu_CM_RELEASE_RSP_apdu))) return; 
					 if(BOOST_ASN_BIND_TAG(value<CM_ABORT_apdu > (true , CM_apdu_CM_ABORT_apdu))) return; 
					;}}}
			else {
				 switch(type()){
					case CM_apdu_CM_CONNECT_REQ_apdu: {BOOST_ASN_BIND_TAG(value<CM_CONNECT_REQ_apdu > (false , CM_apdu_CM_CONNECT_REQ_apdu)); break;}
					case CM_apdu_CM_CONNECT_RSP_apdu: {BOOST_ASN_BIND_TAG(value<CM_CONNECT_RSP_apdu > (false , CM_apdu_CM_CONNECT_RSP_apdu)); break;}
					case CM_apdu_CM_RELEASE_REQ_apdu: {BOOST_ASN_BIND_TAG(value<CM_RELEASE_REQ_apdu > (false , CM_apdu_CM_RELEASE_REQ_apdu)); break;}
					case CM_apdu_CM_RELEASE_RSP_apdu: {BOOST_ASN_BIND_TAG(value<CM_RELEASE_RSP_apdu > (false , CM_apdu_CM_RELEASE_RSP_apdu)); break;}
					case CM_apdu_CM_ABORT_apdu: {BOOST_ASN_BIND_TAG(value<CM_ABORT_apdu > (false , CM_apdu_CM_ABORT_apdu)); break;}
					default:{}}}
		}
	};


}


BOOST_ASN_CHOISE_REGESTRATE(P_EXAMPLE_1::CM_apdu) 
BOOST_ASN_CHOISE_REGESTRATE(P_EXAMPLE_1::DATA_apdu) 

#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif