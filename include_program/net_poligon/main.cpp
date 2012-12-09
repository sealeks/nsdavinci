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

using  namespace boost::asio::asn::x690;
using  namespace boost::asio::asn;

namespace test {

    BOOST_ASN_IMPLICIT_TYPEDEF(Date, visiblestring_type , 3, APPLICATION_CLASS)
    BOOST_ASN_IMPLICIT_TYPEDEF(EmployeeNumber, int , 2, APPLICATION_CLASS)

    struct Name_base {
        visiblestring_type givenName;
        visiblestring_type initial;
        visiblestring_type famelyName;

        template<typename Archive>
                void serialize(Archive & arch) {
            BOOST_ASN_BIND_TAG( givenName);
            BOOST_ASN_BIND_TAG( initial);
            BOOST_ASN_BIND_TAG( famelyName);
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

        template<typename Archive>
                void serialize(Archive & arch) {

            BOOST_ASN_EXPLICIT_TAG( i1 , 4);
            BOOST_ASN_EXPLICIT_TAG( i2 , 3);
            BOOST_ASN_EXPLICIT_TAG( i3 , 0);
            BOOST_ASN_EXPLICIT_TAG( i4 , 1);


        }

    } ;

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
        // boost::shared_ptr<Date> dateend;
        Name nameOfSpouse;
        std::vector<ChildInfo> childs;
        //std::vector<EmployeeNumber> testseq;
        //vector_set_of<visiblestring_type> testset;   

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

        template<typename Archive>
                void serialize(Archive & arch) {

            BOOST_ASN_BIND_TAG( name);
            BOOST_ASN_EXPLICIT_TAG( title, 0);
            BOOST_ASN_BIND_TAG( number);
            // BOOST_ASN_EXPLICIT_TAG(dateofHire, 1);
            // BOOST_ASN_EXPLICIT_TAG(nameOfSpouse, 2);   
            // BOOST_ASN_EXPLICIT_TAG(dateend, 3); 
            BOOST_ASN_EXPLICIT_TAG(childs, 3);

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



    try {


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


        boost::asio::asn::x690::oarchive OARCV(CER_ENCODING);
        boost::asio::asn::x690::iarchive  IARCV;



        test::PR pr;
        pr.name.value().famelyName = "Alexeev";
        pr.name.value().givenName = "Serg";
        pr.name.value().initial = "Valerievich";

        pr.title = "Programmer";

        pr.number = 34;

        pr.dateofHire = visiblestring_type("19780625");
        //pr.dateend = boost::shared_ptr<test::Date> ( new test::Date(visiblestring_type("20121221")));

        pr.nameOfSpouse.value().famelyName = "Alexeeva";
        pr.nameOfSpouse.value().givenName = "M";
        pr.nameOfSpouse.value().initial = "N";


        for (int i = 0; i < 20; ++i) {
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


        //for (int i=0;i<20;++i)
        //     pr.testseq.push_back(i);


        /* for (int i=0;i<20;++i)
             pr.testset.push_back(visiblestring_type("20121221"));      */

        OARCV & implicit_value<test::PR > (pr, 345, CONTEXT_CLASS) ;

        IARCV.add(OARCV);
        //  implicit_value<TestStruct3 > impls (ts33, 345, CONTEXT_CLASS);

        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << OARCV;
        }

        test::PR2 pr2;

        IARCV & implicit_value<test::PR2 > (pr2 , 345, CONTEXT_CLASS) ;



        //std::cout << OARCV;


        std::cout << pr2.name.value().famelyName;
        // if (pr2.dateend)
        //            std::cout << (*pr2.dateend);

        //   std::wstring testw = ts33.u8.to_wstring();

        //   std::wcout <<testw  << std::endl;

        // std::cout << "ts33 i: " << ts33.i  << " j: " << ts33.j  << " d: " << ts33.d << " o: " << ts33.o << " r: " << ts33.r <<  " s: "
        //         << ts33.s <<  " io: " << (ts33.io ?  (*ts33.io) : 0) << " y: " << ts33.y << " u8 : " <<  ts33.u8 << " t : " <<  ts33.t  << " gt : " <<  ts33.gt;

        //    if (ts33.yo) {
        //        std::cout  << " yo: " << *ts33.yo   <<  std::endl;
        //     }
        //     else {
        //         std::cout  <<  std::endl;
        //    }

        //test_decoder(test_decode(OARCV));






        // std::cout << "Bit string: " << bs << std::endl;

        //std::cerr << "real: " << tstint.value<int>() << "\n";         


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
