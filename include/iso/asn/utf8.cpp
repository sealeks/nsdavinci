#include <iso/asn/utf8.h>
#include <vector>
#include <algorithm>


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
                    return boost::asio::asn::utf8::is_valid(val.begin(), val.end());
                }
                catch (...) {
                }
                return false;
            }

            std::wstring utf8_to_wstr(const std::string& val) {
                try {
                    string::const_iterator end_it = boost::asio::asn::utf8::find_invalid(val.begin(), val.end());
                    if (end_it != val.end()) {
                        return L"?-noUTF8";
                    }
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
                    return std::wstring(unicodeline.begin(), unicodeline.end());
                }
                catch (...) {
                }
                return L"";
            }

            bool utf8_to_wstr(const std::string& val, std::wstring& rslt) {
                try {
                    string::const_iterator end_it = boost::asio::asn::utf8::find_invalid(val.begin(), val.end());
                    if (end_it != val.end()) {
                        return false;
                    }
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
                    return true;
                }
                catch (...) {
                }
                return false;
            }

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
                    return utf8line;
                }
                catch (...) {
                }
                return "";
            }

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
                    return true;
                }
                catch (...) {
                }
                return false;
            }
            
            
            

            bool wstr_to_universalstr(const std::wstring& val, std::string& rslt) {
                try {

#if defined(ASNUTF8_DEF_WCHAR16)    
                    std::string utf8line;
                    boost::asio::asn::utf8::utf16to8(val.begin(), val.end(), back_inserter(utf8line));
                    std::vector<boost::asio::asn::utf8::uint32_t> utf32line;
                    boost::asio::asn::utf8::utf8to32(utf8line.begin(), utf8line.end(), back_inserter(utf32line));
                    for (std::vector<boost::asio::asn::utf8::uint32_t>::const_iterator it = utf32line.begin(); it != utf32line.end(); ++it) {
                        std::copy(reinterpret_cast<const std::string::value_type*> (&(*it)), reinterpret_cast<const std::string::value_type*> (&(*it)) + 4, std::back_inserter(rslt));
                        std::reverse(rslt.end() - 4, rslt.end());
                    }
#elif defined(ASNUTF8_DEF_WCHAR32)
                    for (std::wstring::const_iterator it = val.begin(); it != val.end(); ++it){
                        std::copy(reinterpret_cast<const std::string::value_type*> (&(*it)), reinterpret_cast<const std::string::value_type*> (&(*it)) + 4, std::back_inserter(rslt));
                        std::reverse(rslt.end() - 4, rslt.end());
                    }
#else    
                    return L"?";
#endif        
                    return true;
                }
                catch (...) {
                }
                return false;
            }

            bool wstr_to_bmpstr(const std::wstring& val, std::string& rslt) {
                try {

#if defined(ASNUTF8_DEF_WCHAR16)    
                    for (std::wstring::const_iterator it = val.begin(); it != val.end(); ++it) {
                        std::copy(reinterpret_cast<const std::string::value_type*> (&(*it)), reinterpret_cast<const std::string::value_type*> (&(*it)) + 2, std::back_inserter(rslt));
                        std::reverse(rslt.end() - 2, rslt.end());
                    }
#elif defined(ASNUTF8_DEF_WCHAR32)
                    std::string utf8line;
                    boost::asio::asn::utf8::utf32to8(val.begin(), val.end(), back_inserter(utf8line));
                    std::vector<boost::asio::asn::utf8::uint16_t> utf16line;
                    boost::asio::asn::utf8::utf8to16(utf8line.begin(), utf8line.end(), back_inserter(utf16line));
                    for (std::vector<boost::asio::asn::utf8::uint32_t>::const_iterator it = utf16line.begin(); it != utf16line.end(); ++it) {
                        std::copy(reinterpret_cast<const std::string::value_type*> (&(*it)), reinterpret_cast<const std::string::value_type*> (&(*it)) + 2, std::back_inserter(rslt));
                        std::reverse(rslt.end() - 2, rslt.end());
                    }
#else    
                    return L"?";
#endif        
                    return true;
                }
                catch (...) {
                }
                return false;
            }

            bool universalstr_to_wstr(const std::string& val, std::wstring& rslt) {
                if (val.empty())
                    return true;
                if (!(val.size() % 4))
                    return false;
                try {

#if defined(ASNUTF8_DEF_WCHAR16)    
                    std::vector<boost::asio::asn::utf8::uint32_t> utf32line;
                    std::size_t cnt = 0;
                    for (std::string::const_iterator it = val.begin(); it != val.end(); ++it) {
                        if ((cnt++) % 4)
                            utf32line.push_back(0);
                        utf32line.back() |= (utf32line.back() << 8) | *it;
                    }
                    std::string utf8line;
                    boost::asio::asn::utf8::utf32to8(utf32line.begin(), utf32line.end(), back_inserter(utf8line));
                    boost::asio::asn::utf8::utf8to16(utf32line.begin(), utf32line.end(), back_inserter(rslt));
#elif defined(ASNUTF8_DEF_WCHAR32)
                    std::size_t cnt = 0;
                    for (std::string::const_iterator it = val.begin(); it != val.end(); ++it) {
                        if ((cnt++) % 4)
                            rslt.push_back(0);
                        if (!rslt.empty())
                            rslt[rslt.size() - 1] |= (rslt[rslt.size() - 1] << 8) | *it;
                    }
#else    
                    return L"?";
#endif        
                    return true;
                }
                catch (...) {
                }
                return false;
            }

            bool bmpstr_to_wstr(const std::string& val, std::wstring rslt) {
                if (val.empty())
                    return true;
                if (!(val.size() % 2))
                    return false;
                try {

#if defined(ASNUTF8_DEF_WCHAR16)    
                    std::size_t cnt = 0;
                    for (std::string::const_iterator it = val.begin(); it != val.end(); ++it) {
                        if ((cnt++) % 2)
                            rslt.push_back(0);
                        if (!rslt.empty())
                            rslt[rslt.size() - 1] |= (rslt[rslt.size() - 1] << 8) | *it;
                    }
#elif defined(ASNUTF8_DEF_WCHAR32)
                    std::vector<boost::asio::asn::utf8::uint16_t> utf16line;
                    std::size_t cnt = 0;
                    for (std::string::const_iterator it = val.begin(); it != val.end(); ++it) {
                        if ((cnt++) % 2)
                            utf16line.push_back(0);
                        utf16line.back() |= (utf16line.back() << 8) | *it;
                    }
                    std::string utf8line;
                    boost::asio::asn::utf8::utf16to8(utf32line.begin(), utf32line.end(), back_inserter(utf8line));
                    boost::asio::asn::utf8::utf8to32(utf32line.begin(), utf32line.end(), back_inserter(rslt));
#else    
                    return L"?";
#endif        
                    return true;
                }
                catch (...) {
                }
                return false;
            }

        }
    }
}

