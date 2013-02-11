/* 
 * Author: sealeks@mail.ru
 * 
 * 
 */

#include <cstdlib>
#include <deque>
#include <iostream>


#include <kernel/constdef.h>
#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>
#include <kernel/templ.h>

#include <iso/rfc1006.h>
#include <iso/iso8327.h>
#include <iso/asn/itu_X690.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <boost/any.hpp>


#include "ASN1C-UsefulInformationObjectClasses.h"
#include "ISO8823-PRESENTATION.h"
#include "ASN1-Object-Identifier-Module.h"
#include "ACSE-1.h"

typedef boost::asio::iso::archive_temp<>    trans_data;
typedef boost::asio::iso::archive_ptr            trans_data_type;

using  namespace boost::asio::asn::x690;
using  namespace boost::asio::asn;

namespace test {

    BOOST_ASN_IMPLICIT_TYPEDEF(Date, visiblestring_type , 3, APPLICATION_CLASS)
    BOOST_ASN_IMPLICIT_TYPEDEF(EmployeeNumber, int , 2, APPLICATION_CLASS)
    
    struct TestSet;
    
   // struct Name_base;
    
   //     BOOST_ASN_IMPLICIT_TYPEDEF(Name_base, Name_base2  , 1, APPLICATION_CLASS)
    

    struct Name_base {
        visiblestring_type givenName;
        visiblestring_type initial;
        visiblestring_type famelyName;
        boost::shared_ptr<TestSet> ts;

        template<typename Archive>
                void serialize(Archive & arch) {
            BOOST_ASN_BIND_TAG( givenName);
            BOOST_ASN_BIND_TAG( initial);
            BOOST_ASN_BIND_TAG( famelyName);
            BOOST_ASN_EXPLICIT_TAG( ts, 5);
        }
    } ;

    BOOST_ASN_IMPLICIT_TYPEDEF(Name, Name_base  , 1, APPLICATION_CLASS)


   
    
    struct TestSet {

        TestSet() : i1(1), i2(2), i3(3), i4(4) {
        }
        int i1;
        int  i2;
        int  i3;
        int  i4;

    void start_accept() {
        trans_data_type trans_ = trans_data_type( new   trans_data());

            BOOST_ASN_EXPLICIT_TAG( i1 , 4);
            BOOST_ASN_EXPLICIT_TAG( i2 , 3);
            BOOST_ASN_EXPLICIT_TAG( i3 , 0);
            BOOST_ASN_EXPLICIT_TAG( i4 , 1);


        }

    } ;

    struct TestSet2 {

} ;

class client {
public:

    client(boost::asio::io_service& io_service,
            resolver_type::iterator endpoint_iterator, const std::string& called = "")
    : io_service_(io_service),
    socket_(io_service, SELECTOR) {
        endpoint_type endpoint = *endpoint_iterator;

        trans_ = trans_data_type( new   trans_data(/*"Hello server from test"*/));
        trans_->request_str(start_request());

        template<typename Archive>
                void serialize(Archive & arch) {

            BOOST_ASN_EXPLICIT_TAG( s1 , 4);
            BOOST_ASN_EXPLICIT_TAG( s2 , 3);
            BOOST_ASN_EXPLICIT_TAG( s3 , 0);
            BOOST_ASN_EXPLICIT_TAG( s4 , 1);


        }
    }

    void release() {
        std::cout << "Start release"  << std::endl;
#if defined(PRES_PROT)
        io_service_.reset();
        boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        io_service_.poll();
#elif defined(SESSION_PROT)
        io_service_.reset();
        trans_ = trans_data_type( new   trans_data());
        socket_.asyn_releaseconnect(boost::bind(&client::handle_release, this, boost::asio::placeholders::error), boost::asio::iso::SESSION_NORMAL_RELEASE, trans_);
        io_service_.poll();
#else
        io_service_.reset();
         trans_ = trans_data_type();
        boost::asio::asyn_releaseconnect(socket_, boost::bind(&client::handle_release, this, boost::asio::placeholders::error));
        io_service_.poll();
#endif           

    } ;

    enum choice_enum {
        testchoice_null = 0,
        testchoice_ch1,
        testchoice_ch2
    } ;

    struct  testchoice :  public BOOST_ASN_CHOICE_STRUCT(choice_enum) {

        testchoice() : BOOST_ASN_CHOICE_STRUCT(choice_enum) () {
        }

        BOOST_ASN_VALUE_CHOICE(ch1, TestSet,  testchoice_ch1)
        BOOST_ASN_VALUE_CHOICE(ch2, TestSet2,  testchoice_ch2)

                template<typename Archive>
                void serialize(Archive & arch) {
            
           
            if ( BOOST_ASN_CHOICE_CHECK(testchoice_ch1) ) {
                if (BOOST_ASN_EXPLICIT_TAG( value<TestSet > (arch.__input__(), testchoice_ch1) , 7))
                    return;
            }
            if ( BOOST_ASN_CHOICE_CHECK(testchoice_ch2) ) {
                if (BOOST_ASN_EXPLICIT_TAG( value<TestSet2 > (arch.__input__(), testchoice_ch2) , 8))
                    return;
            
    /*        if (arch.__input__()){
                switch(arch.test_class()){
                    case 0: break;
                    case 0x20: break;   
                    case 0x40: break;
                    default: {
                        switch(arch.test_id()){                        
                            case 7: BOOST_ASN_EXPLICIT_TAG( value<TestSet > (true, testchoice_ch1) , 7); break;
                            case 8: BOOST_ASN_EXPLICIT_TAG( value<TestSet > (true, testchoice_ch2) , 8); break;  
                            default: break;
                        }
                    }                   
                }
            }
            else{
                switch(type()){
                    case testchoice_null: break;
                    case testchoice_ch1: BOOST_ASN_EXPLICIT_TAG( value<TestSet > (false, testchoice_ch1) , 7); break;
                    case testchoice_ch2: BOOST_ASN_EXPLICIT_TAG( value<TestSet2 > (false, testchoice_ch2) , 8); break;                  
                }
            }*/
            }
            
        }

            trans_ = trans_data_type( new   trans_data());
            trans_->request_str("Hello server from test");

    struct ChildInfo {
        Name name;
        Date  dateofBirth;
        Date  dateofBirth3;
        Date  dateofBirth4;
        boost::shared_ptr<TestSet> tset;
        boost::shared_ptr<TestSet> tset2;

        template<typename Archive>
                void serialize(Archive & arch) {

            BOOST_ASN_IMPLICIT_TAG( tset , 5);
            BOOST_ASN_EXPLICIT_TAG( dateofBirth4 , 4);
            BOOST_ASN_EXPLICIT_TAG( dateofBirth3 , 3);
            BOOST_ASN_IMPLICIT_TAG( tset2 , 8);
            BOOST_ASN_EXPLICIT_TAG( dateofBirth , 0);
            BOOST_ASN_BIND_TAG(name);

        }

    } ;

    struct PR {
        visiblestring_type title1;
        Name name;
        visiblestring_type title;
        EmployeeNumber number;
        Date dateofHire;
        Name nameOfSpouse;
        std::vector<ChildInfo> childs;
        testchoice  ch;

        template<typename Archive>
                void serialize(Archive & arch) {
            BOOST_ASN_EXPLICIT_TAG( title1, 100);
            BOOST_ASN_BIND_TAG( name);
            BOOST_ASN_EXPLICIT_TAG( title, 0);
            BOOST_ASN_BIND_TAG( number);
            BOOST_ASN_EXPLICIT_TAG(dateofHire, 1);
            BOOST_ASN_EXPLICIT_TAG(nameOfSpouse, 2);
            // BOOST_ASN_EXPLICIT_TAG(dateend, 3); 
            BOOST_ASN_EXPLICIT_TAG(childs, 3);
            BOOST_ASN_CHOICE(ch);
            //BOOST_ASN_BIND_TAG( testseq);  
            //  BOOST_ASN_BIND_TAG( testset);        
        }

    } ;

    struct PR2 {
        Name name;
        visiblestring_type title;
        EmployeeNumber number;
        //Date dateofHire;   
        // boost::shared_ptr<Date> dateend;
        //Name nameOfSpouse;   
        std::vector<ChildInfo> childs;
        //std::vector<EmployeeNumber> testseq;
        //vector_set_of<visiblestring_type> testset;   
        testchoice  ch;

        template<typename Archive>
                void serialize(Archive & arch) {

            BOOST_ASN_BIND_TAG( name);
            BOOST_ASN_EXPLICIT_TAG( title, 0);
            BOOST_ASN_BIND_TAG( number);
            // BOOST_ASN_EXPLICIT_TAG(dateofHire, 1);
            // BOOST_ASN_EXPLICIT_TAG(nameOfSpouse, 2);   
            // BOOST_ASN_EXPLICIT_TAG(dateend, 3); 
            BOOST_ASN_EXPLICIT_TAG(childs, 3);
            BOOST_ASN_CHOICE(ch);
            //BOOST_ASN_BIND_TAG( testseq);  
            //  BOOST_ASN_BIND_TAG( testset);        
        }

    } ;

}

//BOOST_ASN_TYPE_REGESTRATE(test::Name, 1, APPLICATION_CLASS)
//BOOST_ASN_TYPE_REGESTRATE(test::EmployeeNumber, 2, APPLICATION_CLASS)

BOOST_ASN_SET_REGESTRATE(test::ChildInfo)
//BOOST_ASN_SET_REGESTRATE(test::TestSet)

//inline std::ostream& operator<<(std::ostream& stream, const TestStruct1& vl) {
//  return stream << "TestStruct1 : i: " << vl.i  << " j: " << vl.j  << " : "  <<  "\n";
//}

int main(int argc, char* argv[]) {

    
            const boost::array<oidindx_type, 5 > OIDTEST_ARR = {1, 2, 3, 4, 5};
        const oid_type OIDTEST = oid_type(OIDTEST_ARR);
        std::cout << "oidtest: " << OIDTEST << "\n";

        const boost::array<oidindx_type, 5 > OIDTEST_ARR2 = {1, 2, 3000, 4, 5};
        const oid_type OIDTEST2 = oid_type(OIDTEST_ARR2);
        std::cout << "oidtest: " << OIDTEST2 << "\n";


    try {
        
        ISO8823_PRESENTATION::CP_type cpt;
        ISO8823_PRESENTATION::CP_type cpt1;
        
        MyTest::PersonnelRecord prec;
        prec.value().title="hhhh";
        
        cpt.mode_selector.mode_value = ISO8823_PRESENTATION::Mode_selector::mode_value_normal_mode;
        cpt.normal_mode_parameters = boost::shared_ptr<ISO8823_PRESENTATION::CP_type::normal_mode_parameters_type>( new ISO8823_PRESENTATION::CP_type::normal_mode_parameters_type());
  //      cpt.mode_selector->mode_value = new int(1);
        cpt.normal_mode_parameters->called_presentation_selector = 
                boost::shared_ptr<ISO8823_PRESENTATION::Called_presentation_selector>( new ISO8823_PRESENTATION::Called_presentation_selector("11"));
        cpt.normal_mode_parameters->calling_presentation_selector = 
                boost::shared_ptr<ISO8823_PRESENTATION::Calling_presentation_selector>( new ISO8823_PRESENTATION::Calling_presentation_selector("22"));    
        cpt.normal_mode_parameters->presentation_requirements = 
			boost::shared_ptr<ISO8823_PRESENTATION::Presentation_requirements>( new ISO8823_PRESENTATION::Presentation_requirements(boost::uint8_t(0),6));
                
        cpt.normal_mode_parameters->default_context_name.abstract_syntax_name = OIDTEST;
         cpt.normal_mode_parameters->default_context_name.transfer_syntax_name = OIDTEST;       
        
        ISO8823_PRESENTATION::Context_list_sequence_of cl1;
        cl1.abstract_syntax_name = OIDTEST; 
        cl1.presentation_context_identifier =1;
        //ISO8823_PRESENTATION::Context_list_sequence_of::transfer_syntax_name_list_type tr1 = OIDTEST;
        cl1.transfer_syntax_name_list.push_back(OIDTEST);
        
                
        ISO8823_PRESENTATION::Context_list_sequence_of cl2;    
        cl2.abstract_syntax_name = OIDTEST2;
        cl2.presentation_context_identifier =2; 
        cl2.transfer_syntax_name_list.push_back(OIDTEST2);
        
        cpt.normal_mode_parameters->presentation_context_definition_list.push_back(cl1);
        cpt.normal_mode_parameters->presentation_context_definition_list.push_back(cl2);        
        
        
        //ACSE_1::AARE_apdu  aarp;
        
        //aarp.aSO_context_name;

        
        std::string OUT_FILE = "f:\\outfile.der";

        int id = 0x1100220;

        int len = 0x1111;

        //  const_buffers  buff;

        const boost::array<oidindx_type, 5 > OIDTEST_ARR = {1, 2, 3, 4, 5};
        const oid_type OIDTEST = oid_type(OIDTEST_ARR);
        std::cout << "oidtest: " << OIDTEST << "\n";

        const boost::array<oidindx_type, 5 > OIDTEST_ARR2 = {1, 2, 3000, 4, 5};
        const oid_type OIDTEST2 = oid_type(OIDTEST_ARR2);
        std::cout << "oidtest: " << OIDTEST2 << "\n";

        std::cout << "oidtest: " << (OIDTEST2 == OIDTEST) << "\n";

        const boost::array<oidindx_type, 3 > RELOIDTEST_ARR = {456, 67, 45};
        const reloid_type RELOIDTEST = reloid_type(RELOIDTEST_ARR);
        std::cout << "reoidtest: " << RELOIDTEST << "\n";


        boost::asio::asn::x690::oarchive OARCV/*(CER_ENCODING)*/;
        boost::asio::asn::x690::oarchive OARCV1/*(CER_ENCODING)*/;
        boost::asio::asn::x690::iarchive  IARCV;
        boost::asio::asn::x690::iarchive  IARCV1;



        test::PR pr;
        test::PR pr2;        
        pr.name.value().famelyName = "Alexeev";
        pr.name.value().givenName = "Serg";
        pr.name.value().initial = "Valerievich";
        pr.name.value().ts = boost::shared_ptr<test::TestSet > ( new test::TestSet());

        pr.title = "Programmer";

        pr.number = 34;

        pr.dateofHire = visiblestring_type("19780625");
        //pr.dateend = boost::shared_ptr<test::Date> ( new test::Date(visiblestring_type("20121221")));

        pr.nameOfSpouse.value().famelyName = "Alexeeva";
        pr.nameOfSpouse.value().givenName = "M";
        pr.nameOfSpouse.value().initial = "N";



        for (int i = 0; i < 2; ++i) {
            pr.childs.push_back(test::ChildInfo());
            pr.childs.back().dateofBirth = visiblestring_type("19780625");
            pr.childs.back().dateofBirth3 = visiblestring_type("3333333333");
            pr.childs.back().dateofBirth4 = visiblestring_type("4444444444");
            pr.childs.back().name.value().famelyName = "Alexeev";
            pr.childs.back().name.value().givenName = "Serg";
            pr.childs.back().name.value().initial = "Valerievich";
            if ( i % 2)
                pr.childs.back().tset = boost::shared_ptr<test::TestSet > ( new test::TestSet());
            if (!(i % 2))
                pr.childs.back().tset2 = boost::shared_ptr<test::TestSet > ( new test::TestSet());
        }

        pr.ch.ch2( new test::TestSet2());

        if (pr.ch.check(test::testchoice_ch1)) {
            test::TestSet ff = *(pr.ch.ch1());
            std::cout << " choice 1" << std::endl;
        }
        if (pr.ch.check(test::testchoice_ch2)) {
            test::TestSet2 ff = *(pr.ch.ch2());
            std::cout << " choice 2" << std::endl;
        }



        //for (int i=0;i<20;++i)
        //     pr.testseq.push_back(i);


        /* for (int i=0;i<20;++i)
             pr.testset.push_back(visiblestring_type("20121221"));      */
     //   ISO8823_PRESENTATION::CP_type cpt;

        pr.serialize(OARCV1);
        /*OARCV << implicit_value<ISO8823_PRESENTATION::CP_type>( 145, CONTEXT_CLASS)*/;
                                                                                       
        ISO8823_PRESENTATION::Fully_encoded_data   fdta;
        ISO8823_PRESENTATION::PDV_list pdlst;
        pdlst.presentation_context_identifier =1;
        
        //ISO8823_PRESENTATION::PDV_list::presentation_data_values_type dtval;
        
        //dtval.single_ASN1_type( new ABSTRACT_SYNTAX());

       
        pdlst.presentation_data_values.single_ASN1_type(new ABSTRACT_SYNTAX());
        pdlst.presentation_data_values.single_ASN1_type()->bind(OARCV1);
        
        fdta.push_back(pdlst);
        
        
        cpt.normal_mode_parameters->user_data.fully_encoded_data(new ISO8823_PRESENTATION::Fully_encoded_data(fdta));
        cpt.serialize(OARCV);

        IARCV.add(OARCV);
        //  implicit_value<TestStruct3 > impls (ts33, 345, CONTEXT_CLASS);

        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << OARCV;
        }

        //test::PR2 IARCV1;
        
        

       // IARCV & implicit_value<test::PR2 > (pr2 , 345, CONTEXT_CLASS) ;

        cpt1.serialize(IARCV);
        
        boost::shared_ptr<ISO8823_PRESENTATION::Fully_encoded_data> dt = cpt.normal_mode_parameters->user_data.fully_encoded_data();
        boost::shared_ptr<ABSTRACT_SYNTAX> dvl = dt->front().presentation_data_values.single_ASN1_type();
        
        dvl->bind(IARCV1);
        pr2.serialize(IARCV1);
      /*  if (pr.ch.check(test::testchoice_ch1)) {
            test::TestSet ff = *(pr.ch.ch1());
            std::cout << " choice 1" << std::endl;
        }
        if (pr.ch.check(test::testchoice_ch2)) {
            test::TestSet2 ff = *(pr.ch.ch2());
            std::cout << " choice 2" << std::endl;
        }*/
        //std::cout << OARCV;


        //std::cout << pr2.name.value().famelyName;

        std::string quit_in;
        while (true) {

            std::getline(std::cin, quit_in);
            if (quit_in == "q") break;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

}
