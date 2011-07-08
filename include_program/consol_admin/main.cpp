/* 
 * File:   main.cpp
 * Author: sealeks@mail.ru
 *
 * Created on 6 Июль 2011 г., 23:36
 */


#include <kernel/memfile.h>
#include <kernel/systemutil.h>
#include <kernel/serviceapp.h>
#include <kernel/factory.h>


#include <admin/factory.h>
#include <admin/adminsession.h>
#include "adminconsol.h"

#include <locale>


using namespace std;
using namespace dvnci;
using namespace dvnci::admin;
using namespace boost::interprocess;
using namespace adminconsol;


fspath                                 basepath;
std::string                            dvnci::DVNCI_SERVICE_NAME="";
dvnci::appidtype                       dvnci::DVNCI_SERVICE_APPID=0;
dvnci::executable_ptr                  dvnci::mainserv;

 

size_t argumetsparser(int argc, char** argv, stdstr_vect& val){
    val.clear();
    if (argc==1) return 0;
    for (int i=1;i<argc;++i){
        val.push_back(std::string(argv[i]));}
    return val.size();}



main_executor_ptr                        executr;


int main(int argc, char** argv) {
    

    stdstr_vect  arg;
    std::wstring  quit_in;
    argumetsparser(argc, argv, arg);
    basepath = getlocalbasepath();
    
    if (arg.empty()){
        executr=main_executor_ptr( new main_executor(basepath));
        if (executr) {
            if (!executr->inited()) 
                executr.reset();}}
    else{
        executr=main_executor_ptr( new main_executor(arg));}
    
    setlocale(LC_ALL, "" );
/*   
#if defined(_DVN_WIN_)
    setlocale(LC_ALL, "" );
#elif defined(_DVN_LIN_)    
    std::setlocale(LC_ALL, "ru_RU.utf8" );
#else
    std::setlocale(LC_ALL, "ru_RU.utf8" );
#endif
*/ 
    
    std::cout << "locale is " << std::wcout.getloc().name() << std::endl;
            
    while (true){
        std::getline(std::wcin,quit_in);
        if (dvnci::lower_copy(dvnci::trim_copy(quit_in))==L"q"){
            return 0;}
        if (executr){
            executr->execute(quit_in);}
        else{
            std::wcout << "No inteface connected!" << std::endl;}}
    return 0;}

