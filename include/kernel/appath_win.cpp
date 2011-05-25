

#if defined(_DVN_WIN_)
#include <windows.h>
#include <kernel/constdef.h>

namespace dvnci {


    fspath getlocalbasepath() {
        HKEY avp_out = 0;
        char value[1024];
        LONG len = 1024;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS , &avp_out ) == ERROR_SUCCESS) {
            DEBUG_STR_DVNCI(SUCCESSFULLOPENKEY)
            if (RegQueryValue(avp_out, "path", value, &len) != ERROR_SUCCESS) {
                DEBUG_STR_DVNCI(ERROROPENKEY)
                DEBUG_VAL_DVNCI(GetLastError());}
            std::string value_ = std::string(((char*) &value), len - 1);
            RegCloseKey(avp_out);
            return len > 0 ? value_ : "";}
        DEBUG_STR_DVNCI(ERROROPENKEY)
        return "";}

    fspath setlocalbasepath(const fspath& path) {

        HKEY avp_out;
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI",  0, KEY_ALL_ACCESS , &avp_out ) == ERROR_SUCCESS) {
            RegDeleteKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI");
            RegCloseKey(avp_out);}
        if (RegCreateKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI", &avp_out) == ERROR_SUCCESS) {
            std::string tmp = path.string();
            RegSetValue(avp_out, "path", REG_SZ, (LPCSTR) tmp.c_str(), tmp.size() );
            RegCloseKey(avp_out);}
        return getlocalbasepath();
}}

#endif

