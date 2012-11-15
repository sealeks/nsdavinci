/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Р В Р Р‹Р В Р’ВµР В Р вЂ¦Р РЋРІР‚С™Р РЋР РЏР В Р’В±Р РЋР вЂљР РЋР Р‰ 2012 Р В РЎвЂ“., 15:58
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
#include <iso/asn/asnbase.h>

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>


using  namespace boost::asio::asn;


        struct TestStruct{
            
            TestStruct(int i_,  oid_type o_, octetstring_type s_) : i(i_), o(o_), s(s_){}
            TestStruct() : i(), o(), s(){}           
            
            int i;
            oid_type o;
            octetstring_type s;
        
        
                friend archive& operator<<(archive& stream,  const TestStruct& vl)  {
                archive::list_iterators_map __map_;    
               /* stream <<  build_implicit(vl.i);
                stream <<  build_implicit(vl.o);
                stream <<  build_implicit(vl.s);*/
                //stream.save_explicit(vl.s,__map_,240); 

               //stream.save_explicit(vl.i,__map_,322); 
                stream.save_explicit(vl.i ,__map_, 200);                  
                stream.save_implicit(vl.i ,__map_, 190);                    
                stream.save_implicit(vl.i,__map_, 180);                 
                stream.save_explicit(vl.i ,__map_, 110);                  
                stream.save_implicit(vl.i ,__map_, 100);                    
                stream.save_implicit(vl.i,__map_, 90);                 
                stream.save_implicit(vl.o,__map_);               
                stream.save_implicit(vl.s,__map_);         
                stream.save_implicit(vl.i ,__map_);  
                

				                
								                
                //stream.sort_tlv(__map_);
                return stream;
            }       
        };
        
        
         struct TestStruct2{
            
            TestStruct2(int i_,  oid_type o_, octetstring_type s_) : i(i_), o(o_), s(s_), t(i_+1,o_,s_){}
            TestStruct2() : i(), o(), s(), t() {}           
            
            int i;
            oid_type o;
            octetstring_type s;
            TestStruct t;
            boost::shared_ptr<TestStruct> ot;
        
        
                friend archive& operator<<(archive& stream,  const TestStruct2& vl)  {
                archive::list_iterators_map __map_;    
           
                stream.save_explicit(vl.t  ,__map_, 1100);                 
                stream.save_implicit(vl.o,__map_);               
                stream.save_implicit(vl.s,__map_);         
                stream.save_implicit(vl.i ,__map_);
                 
                

				                
								                
                //stream.sort_tlv(__map_);
                return stream;
            }       
        };      
        




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




        archive ARCV;

        // ARCV << OIDTEST2;
        //std::string intstryu="01";
        //for (int i=0; i< 15000; i++)
         //  intstryu+=(i    % 2) ? "0" : "1";
        
        // bitstring_type  bs(/*static_cast<boost::uint16_t> (0x8001u)*/ boost::dynamic_bitset<>(std::string(intstryu.c_str())));
        
        //octetstring_type  bs(std::string("Hellow World!"));
        
        

            
                 std::string strtest_="qwer";
        
        for (int ii=0;ii<1000;++ii)
            strtest_+="fft";

        
        
        typedef set_of_type< explicit_value<TestStruct> >            test_set_type;
        
        typedef set_of_type< explicit_value<test_set_type> >       super_test_set_type;
        
       // typedef implicit_value< test_set_type ,  20 >                               test_set_type_imp;
        
        test_set_type bs1;
        
        bs1.push_back( explicit_value<TestStruct>(TestStruct(12, OIDTEST, std::string("111")), 3, CONTEXT_CLASS) );
        bs1.push_back( explicit_value<TestStruct>(TestStruct(124, OIDTEST, std::string("112")), 57, CONTEXT_CLASS));
        
        test_set_type bs2;
        
         
        bs2.push_back( explicit_value<TestStruct>(TestStruct(125, OIDTEST2, std::string("113")), 57, CONTEXT_CLASS));
        bs2.push_back( explicit_value<TestStruct>(TestStruct(126, OIDTEST2, std::string(strtest_)), 58, CONTEXT_CLASS));
        
        super_test_set_type bs;
        
        bs.push_back(explicit_value<test_set_type>(bs1, 100));
        bs.push_back(explicit_value<test_set_type>(bs2, 100));
        
        //bs.push_back(bs2);       
        

        
        octetstring_type strtest(strtest_);
        
       // ARCV << implicit_value<octetstring_type>(strtest);


        //ARCV << explicit_value<super_test_set_type>(bs, 10);//explicit_value<TestStruct>(TestStruct(123, OIDTEST, std::string("111")), 56, CONTEXT_CLASS);//explicit_value< super_test_set_type ,  20 >(bs);
        
        ARCV << implicit_value<TestStruct2>(TestStruct2(12, OIDTEST, std::string("111")), 3, CONTEXT_CLASS) ;

        std::cout << ARCV;

        {
            std::ofstream ofs( OUT_FILE.c_str() , std::ios::binary | std::ios::trunc );
            if (ofs)
                ofs << ARCV;
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
