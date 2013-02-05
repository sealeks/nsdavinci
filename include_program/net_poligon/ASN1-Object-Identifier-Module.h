#ifndef	_ASN1_Object_Identifier_Module_H_
#define	_ASN1_Object_Identifier_Module_H_


#include <iso/asn/asnbase.h>


const boost::array<boost::asio::asn::oidindx_type, 5 >  ASN1_Object_Identifier_Module_OID_ARR = { 2  ,  1  ,  0  ,  0  ,  1 };
const boost::asio::asn::oid_type ASN1_Object_Identifier_Module_OID = boost::asio::asn::oid_type(ASN1_Object_Identifier_Module_OID_ARR);

namespace ASN1_Object_Identifier_Module  {


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


}


#endif