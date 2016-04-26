
#include <string>
#include <iostream>
#include <fstream>
#include <exception>

#include <windows.h>
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

#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

const int UNDEF_ERROR = 1;
const std::string TEST_MAP_NAME = "Global\\dvncisys_test_installbase";
std::size_t TEST_MAP_SIZE = 1024;

const int GLB_ERROR = 1;
const int REG_ERROR = 2;

//
//  1. check registry permission -r
//  2. check local politic permission -g
//  3. copy project folder to program folder -c project_folder program_folder
//  4. set chromium Preferences -b user_folder program_folder
//  5. exists path -e path
//  6. write registry -w path


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
    } catch (const boost::system::system_error& err) {
        return err.code().value();
    } catch (...) {
        return UNDEF_ERROR;
    }
    return 0;
}


namespace fs = boost::filesystem;
const std::wstring REGESTRY_TEST_NAME = L"SOFTWARE\\DVNCITEST";
const std::wstring REGESTRY_TEST_KEY = L"test";



//////////////
//Global objects
/////////////

int test_REG_helper() {
    HKEY avp_out;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, REGESTRY_TEST_NAME.c_str(), 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
        RegDeleteKeyW(HKEY_LOCAL_MACHINE, REGESTRY_TEST_NAME.c_str());
        RegCloseKey(avp_out);
    }
    if (RegCreateKeyW(HKEY_LOCAL_MACHINE, REGESTRY_TEST_NAME.c_str(), &avp_out) == ERROR_SUCCESS) {
        std::wstring tmp = L"test";
        RegSetValueW(avp_out, L"test", REG_SZ, (LPCWSTR) tmp.c_str(), tmp.size());
        RegDeleteKeyW(HKEY_LOCAL_MACHINE, REGESTRY_TEST_NAME.c_str());
        RegCloseKey(avp_out);
    } else
        throw 1; //boost::system::system_error(boost::system::errc::permission_denied, "");
    return 0;
}

int test_REG() {
    try {
        test_REG_helper();
    } catch (const boost::system::system_error& err) {
        return err.code().value();
    } catch (...) {
        return UNDEF_ERROR;
    }
    return 0;
}

int write_REG(fs::path const & pth) {
    HKEY avp_out;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
        RegDeleteKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI");
        RegCloseKey(avp_out);
    }
    if (RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI", &avp_out) == ERROR_SUCCESS) {
        std::wstring tmp = pth.wstring();
        RegSetValueW(avp_out, L"path", REG_SZ, (LPCWSTR) tmp.c_str(), tmp.size());
        RegCloseKey(avp_out);
        return true;
    }
    return false;
}


//////////////
//Copy Dir
/////////////

bool copyDir(fs::path const & source, fs::path const & destination, bool prinerr = true) {

    try {
        // Check whether the function call is valid
        if (
                !fs::exists(source) ||
                !fs::is_directory(source)
                ) {
            if (prinerr)
                std::cout << "Source directory " << source.string()
                << " does not exist or is not a directory." << '\n';
            return false;
        }
        if (fs::exists(destination)) {
            if (prinerr)
                std::cout << "Destination directory " << destination.string()
                << " already exists." << '\n';
            return false;
        }
        // Create the destination directory
        if (!fs::create_directory(destination)) {
            if (prinerr)
                std::cout << "Unable to create destination directory"
                    << destination.string() << '\n';
            return false;
        }
    } catch (fs::filesystem_error const & e) {
        if (prinerr)
            std::cout << e.what() << '\n';
        return false;
    }
    // Iterate through the source directory
    for (
            fs::directory_iterator file(source);
            file != fs::directory_iterator(); ++file
            ) {
        try {
            fs::path current(file->path());
            if (fs::is_directory(current)) {
                // Found directory: Recursion
                if (
                        !copyDir(
                        current,
                        destination / current.filename()
                        )
                        ) {
                    return false;
                }
            } else {
                // Found file: Copy
                fs::copy_file(
                        current,
                        destination / current.filename()
                        );
            }
        } catch (fs::filesystem_error const & e) {
            if (prinerr)
                std::cout << e.what() << '\n';
        }
    }
    return true;
}




//////////////
//Create Preferences
/////////////

bool createifnotExist(fs::path const & prefpath, fs::path const & add) {
    fs::path preffile = prefpath / add;
    if (!fs::exists(preffile))
        fs::create_directories(preffile);
    return fs::exists(preffile);
}

bool createPreferences(fs::path const & pref, fs::path const & startpage) {
    std::ofstream fs(pref.generic_string().c_str(), std::ios_base::out | std::ios_base::trunc);
    std::string bpath = boost::algorithm::replace_all_copy(startpage.generic_string(), "\\", "/");
    if (fs) {
        fs << "{" << std::endl;
        fs << "   \"session\": {" << std::endl;
        fs << "       \"restore_on_startup\": 4," << std::endl;
        fs << "       \"urls_to_restore_on_startup\": [ \"file:///";
        fs << bpath;
        fs << "\" ]" << std::endl;
        fs << "    }" << std::endl;
        fs << "}" << std::endl;
        return true;
    }
    return false;
}

bool writePreferences(fs::path const & prefpath, fs::path const & startpage, bool prinerr = true) {
    if (createifnotExist(prefpath, fs::path("Chromium")))
        if (createifnotExist(prefpath / fs::path("Chromium"), fs::path("User Data")))
            if (createifnotExist(prefpath / fs::path("Chromium") / fs::path("User Data"), fs::path("Default")))
                return createPreferences(prefpath / fs::path("Chromium") / fs::path("User Data") / fs::path("Default") / fs::path("Preferences"), startpage);
    return false;
}


//////////////
//exist path
/////////////

bool existsPath(fs::path const & pth) {
    return fs::exists(pth);
}


typedef std::vector<std::string> paramvect;

int main(int argc, char** argv) {
    paramvect params;
    if (argc > 1)
        for (int i = 1; i < argc; i++)
            params.push_back(std::string(argv[i]));
    if (!params.empty()) {
        if (params[0].find("r") != std::string::npos) {
            int tst = test_REG();
            if (params.size() > 1) {
                if (tst)
                    std::cout << "Install error: User has not rights for creation global objects. " << std::endl;
                else
                    std::cout << "Install REG test is completed success" << std::endl;
            }
            return tst ? 1 : 0;
        } else if (params[0].find("g") != std::string::npos) {
            int tst = test_GLB();
            if (params.size() > 1) {
                if (tst)
                    std::cout << "Install error: User has not rights for write registry" << std::endl;
                else
                    std::cout << "Install GLB test is completed success" << std::endl;
            }
            return tst ? 1 : 0;
        } else if (params[0].find("c") != std::string::npos) {
            if (params.size() > 2) {
                bool tst = copyDir(params[1].c_str(), params[2].c_str(), params.size() > 3);
                return tst ? 1 : 0;
            }
            return 1;
        } else if (params[0].find("b") != std::string::npos) {
            if (params.size() > 2) {
                bool tst = writePreferences(params[1].c_str(), params[2].c_str(), params.size() > 3);
                return tst ? 1 : 0;
            }
            return 1;
        } else if (params[0].find("e") != std::string::npos) {
            if (params.size() > 1) {
                bool tst = existsPath(params[1].c_str());
                return tst ? 1 : 0;
            }
            return 1;
        }
        else if (params[0].find("w") != std::string::npos) {
            if (params.size() > 1) {
                bool tst = write_REG(params[1].c_str());
                return tst ? 1 : 0;
            }
            return 1;
        }
    }
    return 0;
}

