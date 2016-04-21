

/*#if defined(_DVN_WIN_)
#include <windows.h>
#endif*/
#include <kernel/constdef.h>

#if defined(_DVN_OLDWIN_)
namespace dvnci {

    fspath getlocalbasepath() {
        HKEY avp_out = 0;
        char value[1024];
        LONG len = 1024;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
            DEBUG_STR_DVNCI(SUCCESSFULLOPENKEY)
            if (RegQueryValueA(avp_out, "path", value, &len) != ERROR_SUCCESS) {
                DEBUG_STR_DVNCI(ERROROPENKEY)
                DEBUG_VAL_DVNCI(GetLastError());
            }
            std::string value_ = std::string(((char*) &value));
            RegCloseKey(avp_out);
            return len > 0 ? value_ : "";
        }
        DEBUG_STR_DVNCI(ERROROPENKEY)
        return "";
    }

    fspath setlocalbasepath(const fspath& path) {

        HKEY avp_out;
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
            RegDeleteKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI");
            RegCloseKey(avp_out);
        }
        if (RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\DVNCI", &avp_out) == ERROR_SUCCESS) {
            std::string tmp = path.string();
            RegSetValueA(avp_out, "path", REG_SZ, (LPCSTR) tmp.c_str(), tmp.size());
            RegCloseKey(avp_out);
        }
        return getlocalbasepath();
    }
}
#else
namespace dvnci {

    fspath getlocalbasepath() {
        HKEY avp_out = 0;
        std::wstring::value_type value[1024];
        LONG len = 1024;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
            DEBUG_STR_DVNCI(SUCCESSFULLOPENKEY)
            if (RegQueryValueW(avp_out, L"path", value, &len) != ERROR_SUCCESS) {
                DEBUG_STR_DVNCI(ERROROPENKEY)
                DEBUG_VAL_DVNCI(GetLastError());
            }
            std::wstring value_ = std::wstring(((std::wstring::value_type*) &value));
            RegCloseKey(avp_out);
            return len > 0 ? value_ : L"";
        }
        DEBUG_STR_DVNCI(ERROROPENKEY)
        return L"";
    }

    fspath setlocalbasepath(const fspath& path) {

        HKEY avp_out;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI", 0, KEY_ALL_ACCESS, &avp_out) == ERROR_SUCCESS) {
            RegDeleteKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI");
            RegCloseKey(avp_out);
        }
        if (RegCreateKeyW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\DVNCI", &avp_out) == ERROR_SUCCESS) {
            std::wstring tmp = path.wstring();
            RegSetValueW(avp_out, L"path", REG_SZ, (LPCWSTR) tmp.c_str(), tmp.size());
            RegCloseKey(avp_out);
        }
        return getlocalbasepath();
    }
}
#endif

//#endif

