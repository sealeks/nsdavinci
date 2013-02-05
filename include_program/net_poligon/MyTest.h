#ifndef	_MyTest_H_
#define	_MyTest_H_


#include <iso/asn/asnbase.h>


namespace MyTest  {


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
 	using  boost::asio::asn::ABSTRACT_SYNTAX;

	//  type is  preextend SET
	struct  PersonnelRecord__impl;

 	//  type is  SET
	struct  ChildInformation;

 	//  type is  preextend SEQUENCE
	struct  Name__impl;

 	//  type is extended  SET
	BOOST_ASN_IMPLICIT_TYPEDEF(PersonnelRecord , PersonnelRecord__impl , 0  ,APPLICATION_CLASS)
 
 
 	//  type is extended  SEQUENCE
	BOOST_ASN_IMPLICIT_TYPEDEF(Name , Name__impl , 1  ,APPLICATION_CLASS)
 
 
 	//  type is extended  INTEGER
	BOOST_ASN_IMPLICIT_TYPEDEF(EmployeeNumber , int , 2  ,APPLICATION_CLASS)
 
 
 	//  type is extended  VisibleString
	BOOST_ASN_IMPLICIT_TYPEDEF(Date , visiblestring_type , 3  ,APPLICATION_CLASS)
 
 
 	//it is typeref Date;
	BOOST_ASN_IMPLICIT_TYPEDEF(DateEx , Date , 3  ,APPLICATION_CLASS)
 
 //start==============================================================
//It is   SEQUENCE  

	struct  Name__impl{




		visiblestring_type  givenName;
		visiblestring_type  initial;
		visiblestring_type  familyName;

		Name__impl()  : givenName() , initial() , familyName()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(givenName ,0);
			BOOST_ASN_IMPLICIT_TAG(initial ,1);
			BOOST_ASN_IMPLICIT_TAG(familyName ,2);
		}
	};

//end==============================================================
//start==============================================================
//It is   SET  

	struct  ChildInformation{

		Name  name;
		Date  dateOfBirth;

		ChildInformation()  : name() , dateOfBirth()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(name ,0);
			BOOST_ASN_IMPLICIT_TAG(dateOfBirth ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SET  

	struct  PersonnelRecord__impl{

		//   SEQUENCE_OF is children 
		typedef std::vector<ChildInformation >   children_type;


		Name  name;
		visiblestring_type  title;
		EmployeeNumber  number;
		Date  dateOfHire;
		Name  nameOfSpouse;
		boost::shared_ptr<children_type > children;   //  DEFAULT     
 
		PersonnelRecord__impl()  : name() , title() , number() , dateOfHire() , nameOfSpouse()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(name ,0);
			BOOST_ASN_IMPLICIT_TAG(title ,1);
			BOOST_ASN_IMPLICIT_TAG(number ,2);
			BOOST_ASN_IMPLICIT_TAG(dateOfHire ,3);
			BOOST_ASN_IMPLICIT_TAG(nameOfSpouse ,4);
			BOOST_ASN_IMPLICIT_TAG(children ,5);
		}
	};

//end==============================================================

}

BOOST_ASN_SET_REGESTRATE(MyTest::PersonnelRecord__impl) 
BOOST_ASN_SET_REGESTRATE(MyTest::ChildInformation) 

#endif