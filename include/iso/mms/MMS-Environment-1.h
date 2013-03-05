#ifndef	_MMS_Environment_1_H_
#define	_MMS_Environment_1_H_

#include <iso/asn/asnbase.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065)
 #endif


const boost::array<boost::asio::asn::oidindx_type, 5 >  MMS_Environment_1_OID_ARR = { 2  ,  2  ,  9506  ,  2  ,  4 };
const boost::asio::asn::oid_type MMS_Environment_1_OID = boost::asio::asn::oid_type(MMS_Environment_1_OID_ARR);


namespace MMS_Environment_1  {


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
 	using  boost::asio::asn::objectdescriptor_type;
 	using  boost::asio::asn::external_type;
 	using  boost::asio::asn::embeded_type;
 	using  boost::asio::asn::characterstring_type;
 	using  boost::asio::asn::any_type;

	//  type is  SEQUENCE
	struct  ApplicationReference;

 }
#include "ACSE-1.h"
 


namespace MMS_Environment_1  {

 
	//import type
	using ACSE_1::AP_title;
	using ACSE_1::AP_invocation_identifier;
	using ACSE_1::AE_qualifier;
	using ACSE_1::AE_invocation_identifier;
 
//start==============================================================
//It is   SEQUENCE  

	struct  ApplicationReference{


		ApplicationReference()  {}

		 template<typename Archive> void serialize(Archive& arch){

		}
	};
        
                	struct  Authentication_value{


		Authentication_value()  {}

		 template<typename Archive> void serialize(Archive& arch){

		}
	};  

//end==============================================================

}



#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif