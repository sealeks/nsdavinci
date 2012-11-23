/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Р В Р’В Р В Р вЂ№Р В Р’В Р вЂ™Р’ВµР В Р’В Р В РІР‚В¦Р В Р Р‹Р Р†Р вЂљРЎв„ўР В Р Р‹Р В Р РЏР В Р’В Р вЂ™Р’В±Р В Р Р‹Р В РІР‚С™Р В Р Р‹Р В Р вЂ° 2012 Р В Р’В Р РЋРІР‚вЂњ., 15:58
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


using  namespace boost::asio::asn::x690;
using  namespace boost::asio::asn;

/*typedef int                                                                              Presentation_context_identifier;
typedef oid_type                                                                    Abstract_syntax_name;
typedef oid_type                                                                   Transfer_syntax_name;

struct Context_list {
    Presentation_context_identifier           presentation_context_identifier;
    Abstract_syntax_name                              abstract_syntax_name;
    set_of_type< Transfer_syntax_name > transfer_syntax_name;

    friend oarchive& operator<<(oarchive& stream,  const Context_list & vl)  {
        stream.save_implicit( vl.presentation_context_identifier );
        stream.save_implicit( vl.abstract_syntax_name);
        stream.save_implicit( vl.transfer_syntax_name);
        return stream;
    }

} ;

struct Default_context_name {
    Abstract_syntax_name abstract_syntax_name;
    Transfer_syntax_name transfer_syntax_name;

    friend oarchive& operator<<(oarchive& stream,  const Default_context_name & vl)  {
        stream.save_implicit( vl.abstract_syntax_name  , 0);
        stream.save_implicit( vl.transfer_syntax_name , 1);
        return stream;
    }

} ;


typedef int                                              Mode_selector;
typedef bitstring_type                          Protocol_version;
typedef octetstring_type                     Presentation_selector;
typedef Presentation_selector   Calling_presentation_selector;
typedef Presentation_selector   Called_presentation_selector;
typedef Context_list                            Presentation_context_definition_list;
typedef bitstring_type                         Presentation_requirements;
typedef bitstring_type                         User_session_requirements;

struct CP {
    Mode_selector modeselector;

    struct Normal_mode_parameters {
        Protocol_version                                           protocol_version;
        Calling_presentation_selector               calling_presentation_selector;
        Called_presentation_selector                 called_presentation_selector;
        Presentation_context_definition_list presentation_context_definition_list;
        Default_context_name                                      default_context_name;
        Presentation_requirements                      presentation_requirements;
        User_session_requirements                    user_session_requirements;
        boost::shared_ptr<int>                                   optional;

        friend oarchive& operator<<(oarchive& stream,  const Normal_mode_parameters & vl)  {
            stream.save_implicit( vl.protocol_version  , 0);
            stream.save_implicit( vl.calling_presentation_selector , 1);
            stream.save_implicit( vl.called_presentation_selector , 2);
            stream.save_implicit( vl.presentation_context_definition_list , 3);
            stream.save_implicit( vl.default_context_name , 4);
            stream.save_implicit( vl.presentation_requirements , 5);
            stream.save_implicit( vl.user_session_requirements , 6);
            stream.save_optional_implicit( vl.optional, 7);
            return stream;
        }
    } ;


    Normal_mode_parameters normal_mode_parameters;

    friend oarchive& operator<<(oarchive& stream,  const CP & vl)  {
        stream.save_implicit( vl.modeselector , 0);
        stream.save_implicit( vl.normal_mode_parameters , 2);
        return stream;
    }

} ;

class TestStruct  {
public:

    TestStruct(int i_,  oid_type o_, octetstring_type s_, reloid_type r_) : i(i_), o(o_), s(s_), r(r_) {
    }

    TestStruct() : i(), o(), s(), r() {
    }

    int i;
    oid_type o;
    reloid_type r;
    octetstring_type s;

    friend oarchive& operator<<(oarchive& stream,  const TestStruct& vl)  {
        oarchive::list_iterators_map __map_;
        stream.save_map_explicit(vl.i , __map_, 2000);
        stream.save_map_implicit(vl.i , __map_, 190);
        stream.save_map_implicit(vl.i, __map_, 180);
        stream.save_map_explicit(vl.i , __map_, 110);
        stream.save_map_implicit(vl.i , __map_, 100);
        stream.save_map_implicit(vl.i, __map_, 90);
        stream.save_map_implicit(vl.o, __map_);
        stream.save_map_implicit(vl.s, __map_);
        stream.save_map_implicit(vl.i , __map_);
        stream.save_map_implicit(vl.r , __map_);
        return stream;
    }
} ;


class TestStruct2  {
public:

    TestStruct2(int i_,  oid_type o_, octetstring_type s_,   reloid_type r_) : i(i_), o(o_), r(r_) , s(s_), t(i_ + 1, o_, s_, r_) {
    }

    TestStruct2() : i(), o(), s(), t(), r() {
    }

    int i;
    oid_type o;
    reloid_type r;
    octetstring_type s;
    TestStruct t;
    boost::shared_ptr<TestStruct> ot;

    friend oarchive& operator<<(oarchive& stream,  const TestStruct2& vl)  {
        oarchive::list_iterators_map __map_;
        stream.save_map_implicit(vl.o, __map_);
        stream.save_map_implicit(vl.s, __map_);
        stream.save_map_implicit(vl.i , __map_);
        stream.save_map_implicit(vl.r , __map_);
        stream.save_map_explicit(vl.t  , __map_, 1008);
        return stream;
    }
    
     template<typename Archive>
    void serialize(Archive& arch) {
         
     }   
    
} ;*/

struct TestStruct1  {
    int i;
    int  j;

    TestStruct1() : i(0), j(0) {
    }

    TestStruct1(int i_, int j_) : i(i_), j(j_) {
    }
    //TestStruct2 x;

    template<typename Archive>
            void serialize(Archive & arch) {
        arch & implicit_value<int>(i, 0);
        arch & implicit_value<int>(j, 1);
        // arch & implicit_value<TestStruct2>(x, 2);        
    }
} ;

struct TestStruct2  {
    bool b;
    octetstring_type  o;

    template<typename Archive>
            void serialize(Archive & arch) {
        arch & implicit_value<bool>(b, 0);
        arch & implicit_value<octetstring_type > (o, 1);
    }




} ;

struct TestStruct3  {

    struct choice {
        boost::shared_ptr<int> ch1;
        boost::shared_ptr<TestStruct1> ch2;

        template<typename Archive>
                void serialize(Archive & arch) {
            arch & optional_explicit_value<int>(ch1 , 500);
            arch & optional_explicit_value<TestStruct1 > (ch2 , 501);
        }
    } ;

    int i;
    int  j;
    double d;
    TestStruct1 y;
    oid_type o;
    reloid_type r;
    octetstring_type s;
    boost::shared_ptr<int> io;
    boost::shared_ptr<TestStruct1> yo;
    choice ch;    


    //TestStruct2 x;

    template<typename Archive>
            void serialize(Archive & arch) {

        arch & choice_value<choice>(ch);    
        arch & optional_explicit_value<TestStruct1 > (yo, 356);        
        arch & implicit_value<int>(i, 0);
        arch & implicit_value<int>(j, 1);
        arch & explicit_value<TestStruct1 > (y, 3);
        arch & implicit_value<double>(d, UNIVERSAL_CLASS);
        arch & implicit_value<oid_type > (o, UNIVERSAL_CLASS);
        arch & implicit_value<reloid_type > (r, UNIVERSAL_CLASS);
        arch & implicit_value<octetstring_type > (s, UNIVERSAL_CLASS);
        arch & optional_implicit_value<int>(io);

    }

} ;

struct TestStruct3u  {
    
     struct choice {
         
        boost::shared_ptr<int> ch1;
        boost::shared_ptr<TestStruct1> ch2;

        template<typename Archive>
                void serialize(Archive & arch) {
            arch & optional_explicit_value<int>(ch1 , 500);
            arch & optional_explicit_value<TestStruct1 > (ch2 , 501);
        }
    };   
    
    
    int i;
    int  j;
    float d;
    TestStruct1 y;
    oid_type o;
    reloid_type r;
    octetstring_type s;
    boost::shared_ptr<int> io;
    boost::shared_ptr<TestStruct1> yo;
    choice ch;
    //TestStruct2 x;
    

    template<typename Archive>
            void serialize(Archive & arch) {
        arch & choice_value<choice>(ch);         
        arch & optional_explicit_value<TestStruct1 > (yo, 356);
        arch & implicit_value<int>(i, 0);
        arch & implicit_value<int>(j, 1);
        arch & explicit_value<TestStruct1 > (y, 3);
        arch & implicit_value<float>(d, UNIVERSAL_CLASS);
        arch & implicit_value<oid_type > (o, UNIVERSAL_CLASS);
        arch & implicit_value<reloid_type > (r, UNIVERSAL_CLASS);
        arch & implicit_value<octetstring_type > (s, UNIVERSAL_CLASS);
        arch & optional_implicit_value<int>(io);

    }

} ;

inline std::ostream& operator<<(std::ostream& stream, const TestStruct1& vl) {
    return stream << "TestStruct1 : i: " << vl.i  << " j: " << vl.j  << " : "  <<  "\n";
}

int main(int argc, char* argv[]) {



    try {


        std::string OUT_FILE = "f:\\outfile.der";

        int id = 0x1100220;

        int len = 0x1111;

        const_buffers  buff;

        //boost::asio::asn::length tst(len,false);
        // boost::asio::const_buffer buff = tst.get();

        //  const oidindx_type idetifire[] = {1, 0, 9506, 2, 3};



        //build_implicit(9);

        /*boost::asio::asn::OBJECT_ID tst( idetifire , 5);

        buff << tst;

        std::cout << buff;
        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << buff;
        }

        buff.clear();


        
        typedef boost::uint64_t    test_type;
        
        test_type tstvl=0xfffffffffffffffflu;
        
        boost::asio::asn::INTEGER tstint(tstvl);

        buff << tstint;

        std::cout << buff;

        std::cerr << "Integer: " << tstint.value<test_type>() << "\n";

          buff.clear();

           boost::asio::asn::REAL tstreal(1.11f); 

          buff << tstreal;

          std::cout << buff;  

        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << buff;
        }*/


        // SET_OBJECT_ID_CONSTANT(TDSOID,uuu)
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


        // oarchive OARCV(CER_ENCODING);
        oarchive OARCV;
        iarchive  IARCV;

        // ARCVO << OIDTEST2;
        //std::string intstryu="01";
        //for (int i=0; i< 15000; i++)
        //  intstryu+=(i    % 2) ? "0" : "1";

        // bitstring_type  bs(/*static_cast<boost::uint16_t> (0x8001u)*/ boost::dynamic_bitset<>(std::string(intstryu.c_str())));

        //octetstring_type  bs(std::string("Hellow World!"));


        /* CP cptest;

         cptest.modeselector = 0;
         cptest.normal_mode_parameters.called_presentation_selector = octetstring_type("called_________________________________________________________________________________________________________________________________");
         cptest.normal_mode_parameters.calling_presentation_selector = octetstring_type("calling________________________________________________________________________________________________________________________________");
         cptest.normal_mode_parameters.default_context_name.abstract_syntax_name = OIDTEST2;
         cptest.normal_mode_parameters.default_context_name.transfer_syntax_name = OIDTEST;
         cptest.normal_mode_parameters.presentation_requirements = boost::dynamic_bitset<>(std::string("01"));
         cptest.normal_mode_parameters.protocol_version = boost::dynamic_bitset<>(std::string("1"));
         cptest.normal_mode_parameters.user_session_requirements = boost::dynamic_bitset<>(std::string("01000000"));
         cptest.normal_mode_parameters.presentation_context_definition_list.abstract_syntax_name = OIDTEST;
         cptest.normal_mode_parameters.presentation_context_definition_list.presentation_context_identifier = 2;
         cptest.normal_mode_parameters.presentation_context_definition_list.transfer_syntax_name.push_back(OIDTEST);
         cptest.normal_mode_parameters.presentation_context_definition_list.transfer_syntax_name.push_back(OIDTEST2);
         cptest.normal_mode_parameters.optional = boost::shared_ptr<int>( new int(9));
         std::string strtest_ = "qwer";

         // for (int ii=0;ii<1000;++ii)
         //    strtest_+="fft";

         typedef set_of_type< explicit_value<TestStruct> >            test_set_type;

         typedef set_of_type< TestStruct >                                          teststruct_set_type;

         typedef set_of_type< explicit_value<test_set_type> >       super_test_set_type;

         // typedef implicit_value< test_set_type ,  20 >                               test_set_type_imp;

         test_set_type bs1;

         //bs1.push_back( explicit_value<TestStruct>(TestStruct(12, OIDTEST, std::string("111"), RELOIDTEST), 3, CONTEXT_CLASS) );
         //bs1.push_back( explicit_value<TestStruct>(TestStruct(124, OIDTEST, std::string("112"), RELOIDTEST), 57, CONTEXT_CLASS));

         test_set_type bs2;


         //bs2.push_back( explicit_value<TestStruct>(TestStruct(125, OIDTEST2, std::string("113"), RELOIDTEST), 57, CONTEXT_CLASS));
         //bs2.push_back( explicit_value<TestStruct>(TestStruct(126, OIDTEST2, std::string(strtest_), RELOIDTEST), 58, CONTEXT_CLASS));

         super_test_set_type bs;

         teststruct_set_type st;
         for (int ii = 0; ii < 1000; ++ii)
             st.push_back(TestStruct(123, OIDTEST, std::string("111"), RELOIDTEST));*/

        std::string strtest_ = "";

        for (int ii = 0; ii < 5; ++ii)
            strtest_ += "fftt";


        TestStruct3 ts3;
        ts3.ch.ch2= boost::shared_ptr<TestStruct1 > (new TestStruct1(-50, 60));
        ts3.i = 20;
        ts3.j = 40;
        ts3.d = 0.011; //-1.22456846;  
        ts3.o = OIDTEST2;
        ts3.r = RELOIDTEST;
        ts3.s = octetstring_type(strtest_);
        ts3.io = boost::shared_ptr<int>(new int(1234567));
        ts3.y = TestStruct1(120, 240);
        ts3.yo = boost::shared_ptr<TestStruct1 > (new TestStruct1(120000, -240000));

        TestStruct3u ts33;
        // ts3.x.b=false;
        //  ts3.x.o=octetstring_type("rrrrrrrrrrrr");         


        //octetstring_type strtest(strtest_);

        // OARCV << implicit_value<octetstring_type>(strtest);


        //OARCV << explicit_value<super_test_set_type>(bs, 10);//explicit_value<TestStruct>(TestStruct(123, OIDTEST, std::string("111")), 56, CONTEXT_CLASS);//explicit_value< super_test_set_type ,  20 >(bs);
        // TestStruct2 tst(-12212, OIDTEST, std::string("111"),  RELOIDTEST) ;
        //OARCV << implicit_value<TestStruct2>(tst, 3, CONTEXT_CLASS) ;

        OARCV & implicit_value<TestStruct3 > (ts3, 345, CONTEXT_CLASS) ;

        IARCV.add(OARCV);
        //  implicit_value<TestStruct3 > impls (ts33, 345, CONTEXT_CLASS);

        IARCV & implicit_value<TestStruct3u > (ts33, 345, CONTEXT_CLASS) ;

        std::cout << OARCV;

        std::cout << "ts33 i: " << ts33.i  << " j: " << ts33.j  << " d: " << ts33.d << " o: " << ts33.o << " r: " << ts33.r <<  " s: " << ts33.s <<  " io: " << (ts33.io ?  (*ts33.io) : 0) << " y: " << ts33.y;

        if (ts33.yo) {
            std::cout  << " yo: " << *ts33.yo   <<  std::endl;
        }
        else {
            std::cout  <<  std::endl;
        }

        //test_decoder(test_decode(OARCV));

        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << OARCV;
        }




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
