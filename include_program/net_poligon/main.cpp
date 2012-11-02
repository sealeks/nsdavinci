/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 27 Р РЋР ВµР Р…РЎвЂљРЎРЏР В±РЎР‚РЎРЉ 2012 Р С–., 15:58
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

#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>

#include <cstdio>
#include <cstdlib>
#include <cstring>


using  namespace boost::asio::iso::asn;



int main(int argc, char* argv[]) {



    try {






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
