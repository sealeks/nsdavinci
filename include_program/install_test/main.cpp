
#include <string>
#include <iostream>
#include <fstream>
#include <exception>


#include <boost/shared_ptr.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/filesystem.hpp>
#include <boost/static_assert.hpp>
#include <boost/system/system_error.hpp>
 #include <boost/interprocess/windows_shared_memory.hpp>

const int UNDEF_ERROR = 1;
const std::string TEST_MAP_NAME="Global\\dvncisys_test_installbase";
std::size_t TEST_MAP_SIZE=1024;


//////////////
//Global objects
/////////////

int test_GLB_helper() {
    boost::interprocess::permissions permis;
    permis.set_unrestricted();
    try {
        boost::interprocess::windows_shared_memory shm(boost::interprocess::create_only, TEST_MAP_NAME.c_str(), boost::interprocess::read_write, TEST_MAP_SIZE, permis);
        return 0;
    } catch (...) {
            boost::interprocess::windows_shared_memory shm(boost::interprocess::open_only, TEST_MAP_NAME.c_str(), boost::interprocess::read_write);
    }
    return 0;
}


int test_GLB() {
    try {
        test_GLB_helper();
    }
    catch(const boost::system::system_error& err) {
        return err.code().value();
    }
    catch(...) {
        return UNDEF_ERROR;
    }    
    return 0;
}




int main(int argc, char** argv) 
{
    if (int tst=test_GLB()){
        std::cout << "Install error: User has not rights for creation global objects. Error cod: "  << std::endl;
        return tst;
    }
    else{
        std::cout << "Install test is completed success" << std::endl;
        return 0;
    }
    return 0;
}

