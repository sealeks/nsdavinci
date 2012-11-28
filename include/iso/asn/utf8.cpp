#include <iso/asn/utf8.h>


#if defined(__MINGW32__) && defined(_amd64_)
        #define ASNUTF8_DEF_WCHAR16
#elif defined(__MINGW32__)
        #define ASNUTF8_DEF_WCHAR16
#elif defined(_MSC_VER) && defined(_WIN64)
        #define ASNUTF8_DEF_WCHAR16
#elif defined(_MSC_VER) 
        #define ASNUTF8_DEF_WCHAR16 
#elif defined(__GNUC__) && defined(__amd64__)
        #define ASNUTF8_DEF_WCHAR32
#elif defined(__GNUC__)
        #define ASNUTF8_DEF_WCHAR32 
#else
        #error PlatformXCompiler spec dont defined
#endif





namespace boost {
    namespace asio {
        namespace asn {
            
            using namespace boost::asio::asn::utf8;
            using namespace std;            


 bool check_utf8(const std::string& val) {
        try {
            return boost::asio::asn::utf8::is_valid(val.begin(), val.end());} catch (...) {}
        return false;}

    std::wstring utf8_to_wstr(const std::string& val) {
        try {
            string::const_iterator end_it = boost::asio::asn::utf8::find_invalid(val.begin(), val.end());
            if (end_it != val.end()) {
                return L"?-noUTF8";}
            std::size_t length = boost::asio::asn::utf8::distance(val.begin(), end_it);
            std::vector<wchar_t> unicodeline;
            if (length)
                unicodeline.reserve(length);
            else
                return L"";
#if defined(ASNUTF8_DEF_WCHAR16)
            boost::asio::asn::utf8::utf8to16(val.begin(), end_it, back_inserter(unicodeline));
#elif defined(ASNUTF8_DEF_WCHAR32)
            boost::asio::asn::utf8::utf8to32(val.begin(), end_it, back_inserter(unicodeline));
#else    
            return L"?";
#endif        
            return std::wstring(unicodeline.begin(), unicodeline.end());}        catch (...) {}
        return L"";}

    bool utf8_to_wstr(const std::string& val, std::wstring& rslt) {
        try {
            string::const_iterator end_it = boost::asio::asn::utf8::find_invalid(val.begin(), val.end());
            if (end_it != val.end()) {
                return false;}
            std::size_t length = boost::asio::asn::utf8::distance(val.begin(), end_it);
            std::vector<wchar_t> unicodeline;
            if (length)
                unicodeline.reserve(length);
            else
                return L"";
#if defined(ASNUTF8_DEF_WCHAR16)
            boost::asio::asn::utf8::utf8to16(val.begin(), end_it, back_inserter(unicodeline));
#elif defined(ASNUTF8_DEF_WCHAR32)
            boost::asio::asn::utf8::utf8to32(val.begin(), end_it, back_inserter(unicodeline));
#else    
            return false;
#endif        
            rslt = std::wstring(unicodeline.begin(), unicodeline.end());
            return true;}        catch (...) {}
        return false;}

    std::string wstr_to_utf8(const std::wstring& val) {
        try {
            std::string utf8line;
#if defined(ASNUTF8_DEF_WCHAR16)      
            boost::asio::asn::utf8::utf16to8(val.begin(), val.end(), back_inserter(utf8line));
#elif defined(ASNUTF8_DEF_WCHAR32) 
            boost::asio::asn::utf8::utf32to8(val.begin(), val.end(), back_inserter(utf8line));
#else    
            return L"?";
#endif        
            return utf8line;}        catch (...) {}
        return "";}

    bool wstr_to_utf8(const std::wstring& val, std::string& rslt) {
        try {
            std::string utf8line;
#if defined(ASNUTF8_DEF_WCHAR16)      
            boost::asio::asn::utf8::utf16to8(val.begin(), val.end(), back_inserter(utf8line));
#elif defined(ASNUTF8_DEF_WCHAR32)
            boost::asio::asn::utf8::utf32to8(val.begin(), val.end(), back_inserter(utf8line));
#else    
            return L"?";
#endif        
            rslt = utf8line;
            return true;}        catch (...) {}
        return false;}          


        }
    }
}

