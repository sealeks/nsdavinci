#ifndef	_ISO_9506_MMS_1A_H_
#define	_ISO_9506_MMS_1A_H_

#include <iso/asn/asnbase.h>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4065)
 #endif


const boost::array<boost::asio::asn::oidindx_type, 5 >  ISO_9506_MMS_1A_OID_ARR = { 2  ,  2  ,  9506  ,  2  ,  3 };
const boost::asio::asn::oid_type ISO_9506_MMS_1A_OID = boost::asio::asn::oid_type(ISO_9506_MMS_1A_OID_ARR);


namespace ISO_9506_MMS_1A  {


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
	struct  ObtainFile_Request;

 	//  type is  SEQUENCE
	struct  FileOpen_Request;

 	//  type is  SEQUENCE
	struct  FileOpen_Response;

 	//  type is  SEQUENCE
	struct  FileRead_Response;

 	//  type is  SEQUENCE
	struct  FileRename_Request;

 	//  type is  SEQUENCE
	struct  FileDirectory_Request;

 	//  type is  SEQUENCE
	struct  FileDirectory_Response;

 	//  type is  SEQUENCE
	struct  DirectoryEntry;

 	//  type is  SEQUENCE
	struct  FileAttributes;

 	//  type is  SEQUENCE
	struct  DefineScatteredAccess_Request;

 	//  type is  SEQUENCE
	struct  GetScatteredAccessAttributes_Response;

 	//  type is  NULL
	typedef  null_type   ObtainFile_Response;

 	//  type is  INTEGER
	typedef  int   ObtainFile_Error;

 	//  type is  NULL
	typedef  null_type   FileClose_Response;

 	//  type is  NULL
	typedef  null_type   FileRename_Response;

 	//  type is  INTEGER
	typedef  int   FileRename_Error;

 	//  type is  NULL
	typedef  null_type   FileDelete_Response;

 	//  type is  NULL
	typedef  null_type   DefineScatteredAccess_Response;

 	//   SEQUENCE_OF is ScatteredAccessDescription 
	struct ScatteredAccessDescription_sequence_of;
	typedef std::vector<ScatteredAccessDescription_sequence_of >   ScatteredAccessDescription;

}
#include "ISO-9506-MMS-1.h"
#include "MMS-Environment-1.h"
 


namespace ISO_9506_MMS_1A  {

 
	//import type
	using ISO_9506_MMS_1::FileName;
	using ISO_9506_MMS_1::ObjectName;
	using ISO_9506_MMS_1::AlternateAccess;
	using ISO_9506_MMS_1::VariableSpecification;
	using ISO_9506_MMS_1::Identifier;
	using ISO_9506_MMS_1::Integer32;
	using ISO_9506_MMS_1::Unsigned32;
	using MMS_Environment_1::ApplicationReference;
 
	//   SEQUENCE_OF is ScatteredAccessDescription 
	//start==============================================================
	//It is  INTERNAL SEQUENCE  

		struct  ScatteredAccessDescription_sequence_of{

			boost::shared_ptr<Identifier > componentName;   //  OPTIONAL
			BOOST_ASN_VALUE_FUNC_DECLARATE(Identifier ,  componentName)

 			boost::asio::asn::value_holder<VariableSpecification >  variableSpecification;
			boost::shared_ptr<AlternateAccess > alternateAccess;   //  OPTIONAL
			BOOST_ASN_VALUE_FUNC_DECLARATE(AlternateAccess ,  alternateAccess)

 
			ScatteredAccessDescription_sequence_of()  : variableSpecification() , alternateAccess()  {}

			 template<typename Archive> void serialize(Archive& arch){

				BOOST_ASN_IMPLICIT_TAG(componentName ,0);
				BOOST_ASN_CHOICE_TAG(variableSpecification ,1);
				BOOST_ASN_IMPLICIT_TAG(alternateAccess ,2);
			}
		};

	//end==============================================================
	typedef std::vector<ScatteredAccessDescription_sequence_of >   ScatteredAccessDescription;

	//  ref is  Integer32
	typedef Integer32 FileRead_Request;

 	//  ref is  Integer32
	typedef Integer32 FileClose_Request;

 	//  ref is  FileName
	typedef FileName FileDelete_Request;

 	//  ref is  ObjectName
	typedef ObjectName GetScatteredAccessAttributes_Request;

 //start==============================================================
//It is   SEQUENCE  

	struct  GetScatteredAccessAttributes_Response{


		boost::asio::asn::value_holder<bool >  mmsDeletable;
		boost::asio::asn::value_holder<ScatteredAccessDescription >  scatteredAccessDescription;
		boost::shared_ptr<Identifier > accessControlList;   //  OPTIONAL
		BOOST_ASN_VALUE_FUNC_DECLARATE(Identifier ,  accessControlList)

 
		GetScatteredAccessAttributes_Response()  : mmsDeletable() , scatteredAccessDescription()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(mmsDeletable ,0);
			BOOST_ASN_IMPLICIT_TAG(scatteredAccessDescription ,1);
			BOOST_ASN_IMPLICIT_TAG(accessControlList ,2);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  DefineScatteredAccess_Request{

		boost::asio::asn::value_holder<ObjectName >  scatteredAccessName;
		boost::asio::asn::value_holder<ScatteredAccessDescription >  scatteredAccessDescription;

		DefineScatteredAccess_Request()  : scatteredAccessName() , scatteredAccessDescription()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_CHOICE_TAG(scatteredAccessName ,0);
			BOOST_ASN_IMPLICIT_TAG(scatteredAccessDescription ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileAttributes{


		boost::asio::asn::value_holder<Unsigned32 >  sizeOfFile;
		boost::shared_ptr<gentime_type > lastModified;   //  OPTIONAL
		BOOST_ASN_VALUE_FUNC_DECLARATE(gentime_type ,  lastModified)

 
		FileAttributes()  : sizeOfFile()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(sizeOfFile ,0);
			BOOST_ASN_IMPLICIT_TAG(lastModified ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  DirectoryEntry{

		boost::asio::asn::value_holder<FileName >  fileName;
		boost::asio::asn::value_holder<FileAttributes >  fileAttributes;

		DirectoryEntry()  : fileName() , fileAttributes()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(fileName ,0);
			BOOST_ASN_IMPLICIT_TAG(fileAttributes ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileDirectory_Response{
		//   SEQUENCE_OF is listOfDirectoryEntry 
		typedef std::vector<DirectoryEntry >   listOfDirectoryEntry_type;



		boost::asio::asn::value_holder<listOfDirectoryEntry_type >  listOfDirectoryEntry;
		boost::shared_ptr<bool > moreFollows;   //  DEFAULT   
 		BOOST_ASN_VALUE_FUNC_DECLARATE(bool ,  moreFollows)

 
		FileDirectory_Response()  : listOfDirectoryEntry()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_EXPLICIT_TAG(listOfDirectoryEntry ,0);
			BOOST_ASN_IMPLICIT_TAG(moreFollows ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileDirectory_Request{

		boost::shared_ptr<FileName > fileSpecification;   //  OPTIONAL
		BOOST_ASN_VALUE_FUNC_DECLARATE(FileName ,  fileSpecification)

 		boost::shared_ptr<FileName > continueAfter;   //  OPTIONAL
		BOOST_ASN_VALUE_FUNC_DECLARATE(FileName ,  continueAfter)

 
		FileDirectory_Request()  : fileSpecification() , continueAfter()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(fileSpecification ,0);
			BOOST_ASN_IMPLICIT_TAG(continueAfter ,1);
		}
	};

//end==============================================================

	const int FileRename_Error_source_file = 0;
	const int FileRename_Error_destination_file = 1;

//start==============================================================
//It is   SEQUENCE  

	struct  FileRename_Request{

		boost::asio::asn::value_holder<FileName >  currentFileName;
		boost::asio::asn::value_holder<FileName >  newFileName;

		FileRename_Request()  : currentFileName() , newFileName()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(currentFileName ,0);
			BOOST_ASN_IMPLICIT_TAG(newFileName ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileRead_Response{



		boost::asio::asn::value_holder<octetstring_type >  fileData;
		boost::shared_ptr<bool > moreFollows;   //  DEFAULT   
 		BOOST_ASN_VALUE_FUNC_DECLARATE(bool ,  moreFollows)

 
		FileRead_Response()  : fileData()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(fileData ,0);
			BOOST_ASN_IMPLICIT_TAG(moreFollows ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileOpen_Response{

		boost::asio::asn::value_holder<Integer32 >  frsmID;
		boost::asio::asn::value_holder<FileAttributes >  fileAttributes;

		FileOpen_Response()  : frsmID() , fileAttributes()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(frsmID ,0);
			BOOST_ASN_IMPLICIT_TAG(fileAttributes ,1);
		}
	};

//end==============================================================
//start==============================================================
//It is   SEQUENCE  

	struct  FileOpen_Request{

		boost::asio::asn::value_holder<FileName >  fileName;
		boost::asio::asn::value_holder<Unsigned32 >  initialPosition;

		FileOpen_Request()  : fileName() , initialPosition()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(fileName ,0);
			BOOST_ASN_IMPLICIT_TAG(initialPosition ,1);
		}
	};

//end==============================================================

	const int ObtainFile_Error_source_file = 0;
	const int ObtainFile_Error_destination_file = 1;

//start==============================================================
//It is   SEQUENCE  

	struct  ObtainFile_Request{

		boost::shared_ptr<ApplicationReference > sourceFileServer;   //  OPTIONAL
		BOOST_ASN_VALUE_FUNC_DECLARATE(ApplicationReference ,  sourceFileServer)

 		boost::asio::asn::value_holder<FileName >  sourceFile;
		boost::asio::asn::value_holder<FileName >  destinationFile;

		ObtainFile_Request()  : sourceFileServer() , sourceFile() , destinationFile()  {}

		 template<typename Archive> void serialize(Archive& arch){

			BOOST_ASN_IMPLICIT_TAG(sourceFileServer ,0);
			BOOST_ASN_IMPLICIT_TAG(sourceFile ,1);
			BOOST_ASN_IMPLICIT_TAG(destinationFile ,2);
		}
	};

//end==============================================================

}



#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif