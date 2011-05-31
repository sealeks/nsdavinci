#include <kernel/utils.h>

#undef max
#undef min

namespace dvnci {

    using namespace std;

    void string_to_pascalstr(void* val, const std::string& source, size_t len) {
        if (len < 2) return;
        len = len - 2;
        unum16* sz = static_cast<unum16*> (val);
        if (len) {
            num8* dst = reinterpret_cast<num8*> (sz + 1);
            *sz = static_cast<unum16> ((source.size() > len) ? len : source.size());
            memcpy(dst, source.data(), (source.size() > len) ? len : source.size());};};

    std::string pascalstr_to_string(void* dest) {
        if (!dest) return "";
        unum16* sz = static_cast<unum16*> (dest);
        std::string::size_type szstr = static_cast<std::string::size_type> (*sz);
        return std::string(reinterpret_cast<num8*> (sz + 1), szstr);}

    void formatmem_in_null(void* ptr, size_t len) {
        if ((ptr) && (len)) {
            char* ptr_tmp = static_cast<char*> (ptr);
            while (--len) *ptr_tmp = 0;}}

    bool remove_namespace_delimit(std::string& vl) {
        std::string::size_type delimitpos = vl.find_first_of(NEMESPACEDELIMIT);
        if (delimitpos != std::string::npos) vl = vl.substr(delimitpos + 2);
        return (delimitpos != std::string::npos);}

    std::string retremoved_namespace_delimit(const std::string& vl) {
        std::string::size_type delimitpos = vl.find_first_of(NEMESPACEDELIMIT);
        return (delimitpos != std::string::npos) ? vl.substr(delimitpos + 2) : vl;}

    void fulltrim(std::string& val) {
        boost::algorithm::replace_all(val, WSP_STRING, "");
        boost::algorithm::trim(val);}

    void upper_and_trim(string& val) {
        boost::algorithm::to_upper(val);
        boost::algorithm::trim(val);}

    void lower_and_trim(string& val) {
        boost::algorithm::to_lower(val);
        boost::algorithm::trim(val);}

    void upper_and_fulltrim(string& val) {
        boost::algorithm::to_upper(val);
        fulltrim(val);}

    void lower_and_fulltrim(string& val) {
        boost::algorithm::to_lower(val);
        fulltrim(val);}

    string upper_copy(const std::string& val) {
        return boost::algorithm::to_upper_copy(val);}

    string lower_copy(const std::string& val) {
        return boost::algorithm::to_lower_copy(val);}

    string trim_copy(const std::string& val) {
        return boost::algorithm::trim_copy(val);};

    std::string freechar_copy(const std::string& val, const std::string& del) {
        return boost::algorithm::replace_all_copy(val, del, "");}

    size_t regex_tokin_parser(const std::string& val, str_vect& dst, const boost::regex& re) {
        dst.clear();
        boost::sregex_token_iterator it(val.begin(), val.end(), re);
        boost::sregex_token_iterator end;
        while (it != end) {
            dst.push_back(*it++);}
        return dst.size();}

    std::string fulltrim_copy(const std::string& val) {
        return freechar_copy(val, WSP_STRING);}

    std::string binary_block_to_hexsequence_copy(const std::string& vl) {
        std::string rslt = "";
        for (std::string::size_type it = 0; it < vl.size(); ++it) {
            rslt = rslt + num8_to_hexstr(vl.at(it));}
        return rslt;}

    void binary_block_to_hexsequence(std::string& vl) {
        std::string rslt = binary_block_to_hexsequence_copy(vl);
        vl = rslt;}

    std::string binary_block_to_hexsequence_debug(const std::string& vl) {
        std::string rslt = "";
        for (std::string::size_type it = 0; it < vl.size(); ++it) {
            rslt = rslt + " " + num8_to_hexstr(vl.at(it));}
        return rslt;}

    bool hexsequence_to_binary_block(const std::string& vl, std::string& rslt) {
        rslt = "";
        num8 tmp = 0;
        if ((vl.size() % 2) != 0) return false;
        for (std::string::size_type i = 0; i < vl.size(); i = i + 2) {
            if (hexstr_to<num8 > (vl.substr(i, 2), tmp))
                rslt = rslt + std::string(((const char*) &tmp), 1);
            else return false;}
        return true;}

    bool be_le16_convert_string(std::string& vl) {
        if ((vl.size() % 2) != 0) return false;
        std::string vltmp = "";
        num16 vltmp16 = 0;
        for (std::string::size_type i = 0; i < vl.size(); i = i + 2) {
            if (string_to_primtype<num16 > (vl.substr(i, 2), vltmp16)) {
                vltmp = vltmp + primtype_to_string<num16 > (be_le_convert_num16(vltmp16));} else
                return false;}
        vl = vltmp;
        return true;}

    size_t split_str(const string& source, const string& delimit, str_vect& vectstr) {
        vectstr.clear();
        boost::algorithm::split(vectstr, source, boost::algorithm::is_any_of(delimit));
        return vectstr.size();}

    size_t split_str_prefix(const std::string& source, const std::string& delimit, str_vect& vectstr) {
        split_str(source, delimit, vectstr);
        if ((vectstr.begin() != vectstr.end()) && (*vectstr.begin() == ""))
            vectstr.erase(vectstr.begin());
        return vectstr.size();}

    size_t split_str_postfix(const std::string& source, const std::string& delimit, str_vect& vectstr) {
        split_str(source, delimit, vectstr);
        if ((vectstr.rbegin() != vectstr.rend()) && (*vectstr.rbegin() == "")) {
            str_vect::iterator it = vectstr.begin()+(vectstr.size() - 1);
            vectstr.erase(it);}
        return vectstr.size();}

    void split_2str(const string& source, const string& delimit, string& val1, string& val2) {
        str_vect vect;
        if (split_str(source, delimit, vect) > 0) {
            if (vect.size() > 1) {
                val1 = vect[0];
                val2 = vect[1];} else {
                val1 = vect[0];
                val2 = "";}} else {
            val1 = source;
            val2 = "";}}

    void split_3str(const string& source, const string& delimit, string& val1, string& val2, string& val3) {
        str_vect vect;
        if (split_str(source, delimit, vect) > 0) {
            if (vect.size() > 2) {
                val1 = vect[0];
                val2 = vect[1];
                val3 = vect[2];} else {
                if (vect.size() > 1) {
                    val1 = vect[0];
                    val2 = vect[1];
                    val3 = "";} else {
                    if (vect.size() > 1) {
                        val1 = vect[0];
                        val2 = "";
                        val3 = "";} else {
                        val1 = "";
                        val2 = "";
                        val3 = "";}}}}}

    void split_4str(const string& source, const string& delimit, string& val1, string& val2, string& val3, string& val4) {
        str_vect vect;
        if (split_str(source, delimit, vect) > 0) {
            if (vect.size() > 3) {
                val1 = vect[0];
                val2 = vect[1];
                val3 = vect[2];
                val4 = vect[3];} else {
                if (vect.size() > 2) {
                    val1 = vect[0];
                    val2 = vect[1];
                    val3 = vect[2];
                    val4 = "";} else {
                    if (vect.size() > 1) {
                        val1 = vect[0];
                        val2 = vect[1];
                        val3 = "";
                        val4 = "";} else {
                        if (vect.size() > 1) {
                            val1 = vect[0];
                            val2 = "";
                            val3 = "";
                            val4 = "";} else {
                            val1 = "";
                            val2 = "";
                            val3 = "";
                            val4 = "";}}}}}}

    void comma_to_point(string& val) {
        boost::replace_all(val, ",", ".");}

    void point_to_comma(string& val) {
        boost::replace_all(val, ".", ",");}

    string comma_to_point_copy(const string& val) {
        return boost::replace_all_copy(val, ",", ".");}

    string point_to_comma_copy(const string& val) {
        return boost::replace_all_copy(val, ".", ",");}

    void parse_servinfo(const string& source, string& host, string& port, unsigned int& timout, string& admin, string& pass) {
        string tmp;
        string tmp_to;
        split_3str(source, "\15", tmp, admin, pass);
        split_3str(tmp, ":", host, port, tmp_to);
        str_to<unsigned int>(tmp_to, DEFAULT_DVNCI_TIMOUT, timout);}

    string generate_servinfo(const string& host, const string& port, unsigned int timout, const string& admin, const string& pass) {
        return timout != DEFAULT_DVNCI_TIMOUT ? host + ":" + port + ":" + to_str(timout) + "\15" + admin + "\15" + pass : host + ":" + port + "\15" + admin + "\15" + pass;}

    void clear_first_null_digit(string& vl) {
        if (vl.empty()) return;
        string::size_type it = vl.find_first_not_of("0");
        vl = (it != string::npos) ? vl.substr(it) : "0";}

    void fill_first_null_digit(string& vl, size_t needcsize) {
        if (vl.size() >= needcsize) return;
        while (vl.size() < needcsize) {
            vl = "0" + vl;}}

    std::string clear_first_null_digit_copy(const std::string& vl) {
        std::string val = vl;
        clear_first_null_digit(val);
        return val;}

    std::string fill_first_null_digit_copy(const std::string& vl, size_t needcsize) {
        std::string val = vl;
        fill_first_null_digit(val, needcsize);
        return val;}

    std::string num8_to_hexstr(num8 vl) {
        return std::string(static_cast<const num8*> (&hex_char_array_const[((vl >> 4) & 0xF)]), 1) +
                std::string(static_cast<const num8*> (&hex_char_array_const[((vl) & 0xF)]), 1);}

    std::string num16_to_hexstr(num16 vl) {
        return num8_to_hexstr(static_cast<num8> ((vl >> 8) & 0xFF)) +
                num8_to_hexstr(static_cast<num8> (vl & 0xFF));}

    std::string num32_to_hexstr(num32 vl) {
        return num16_to_hexstr(static_cast<num16> ((vl >> 16) & 0xFFFF)) +
                num16_to_hexstr(static_cast<num16> (vl & 0xFFFF));}

    std::string num64_to_hexstr(num64 vl) {
        return num32_to_hexstr(static_cast<num32> ((vl >> 32) & 0xFFFFFFFF)) +
                num32_to_hexstr(static_cast<num32> (vl & 0xFFFFFFFF));}

    bool str_to(const std::string& val, datetime& result) {
        try {
            result = boost::posix_time::time_from_string(val);}        catch (...) {
            return false;}
        return true;}

    void str_to(const std::string& val, const datetime& def, datetime& result) {
        result = def;
        try {
            result = boost::posix_time::time_from_string(val);}        catch (...) {
            result = def;}}

    bool to_str(datetime val, std::string& result) {
        try {
            result = datetime_to_string(val);}        catch (...) {
            return false;}
        return true;}

    std::string to_str(const datetime& val) {
        return datetime_to_string(val);}

    template <> bool abs<bool>(const bool& v) {
        return v;}

    template <> datetime abs<datetime>(const datetime& v) {
        return v;}

    template <> unum64 abs<unum64>(const unum64& v) {
        return v;}

    template <> unum32 abs<unum32>(const unum32& v) {
        return v;}

    template <> unum16 abs<unum16>(const unum16& v) {
        return v;}

    template <> unum8 abs<unum8>(const unum8& v) {
        return v;}

    template <> std::string abs<std::string>(const std::string& v) {
        return v;}



    template<>  const bool& from_num64_cast<bool>(const num64& val) {
        return ((ptype_punned)(&val))->bl;}

    template<>  const num64& from_num64_cast<num64>(const num64& val) {
        return ((ptype_punned)(&val))->n64;}

    template<>  const unum64& from_num64_cast<unum64>(const num64& val) {
        return ((ptype_punned)(&val))->u64;}

    template<>  const num32& from_num64_cast<num32>(const num64& val) {
        return ((ptype_punned)(&val))->n32;}

    template<>  const unum32& from_num64_cast<unum32>(const num64& val) {
        return ((ptype_punned)(&val))->u32;}

    template<>  const num16& from_num64_cast<num16>(const num64& val) {
        return ((ptype_punned)(&val))->n16;}

    template<>  const unum16& from_num64_cast<unum16>(const num64& val) {
        return ((ptype_punned)(&val))->u16;}

    template<>  const num8& from_num64_cast<num8>(const num64& val) {
        return ((ptype_punned)(&val))->n8;}

    template<>  const unum8& from_num64_cast<unum8>(const num64& val) {
        return ((ptype_punned)(&val))->u8;}

    template<>  const float& from_num64_cast<float>(const num64& val) {
        return ((ptype_punned)(&val))->fl;}

    template<>  const double& from_num64_cast<double>(const num64& val) {
        return ((ptype_punned)(&val))->dbl;}
    
    template<>  const datetime& from_num64_cast<datetime>(const num64& val) {
        return (*(datetime*)((char*)(&val)));}
    
    

    
    template<>  num64 num64_cast<datetime>(const datetime& val) {
        return *((num64*)((char*)(&val)));}
    
    template<>  num64 num64_cast<std::string>(const std::string& val){
        return 0;}

    template<> datetime num64_and_type_cast<datetime>(const num64& value, tagtype type) {
        return (type == TYPE_TM) ? from_num64_cast<datetime > (value) : nill_time;}

    template<> std::string num64_and_type_cast<std::string>(const num64& val, tagtype type) {
        num64* val_ = const_cast<num64*> (&val);
        switch (type) {
            case TYPE_NODEF: return to_str(*reinterpret_cast<double*> (val_));
            case TYPE_DOUBLE: return to_str(*reinterpret_cast<double*> (val_));
            case TYPE_FLOAT: return to_str(*reinterpret_cast<float*> (val_));
            case TYPE_DISCRET: return val != 0 ? "1": "0";
            case TYPE_NUM64: return to_str(*reinterpret_cast<num64*> (val_));
            case TYPE_UNUM64: return to_str(*reinterpret_cast<unum64*> (val_));
            case TYPE_NUM32: return to_str(*reinterpret_cast<num32*> (val_));
            case TYPE_UNUM32: return to_str(*reinterpret_cast<unum32*> (val_));
            case TYPE_NUM16: return to_str(*reinterpret_cast<num16*> (val_));
            case TYPE_UNUM16: return to_str(*reinterpret_cast<unum16*> (val_));
            case TYPE_NUM8: return to_str((num16) (*reinterpret_cast<num8*> (val_)));
            case TYPE_UNUM8: return to_str((unum16) (*reinterpret_cast<unum8*> (val_)));
            case TYPE_TM: return datetime_to_string(val);
            case TYPE_TEXT: return "";
            default: return to_str(*reinterpret_cast<double*> (val_));}
        return to_str(*reinterpret_cast<double*> (val_));
        return "";}

    std::string num64_and_type_cast(const num64& val, tagtype type, const std::string& formt) {
        try {
            num64* val_ = const_cast<num64*> (&val);
            switch (type) {
                case TYPE_NODEF:{
                    boost::format format(formt.empty() ? "%8.2f": formt.c_str());
                    format % (*reinterpret_cast<double*> (val_));
                    return format.str();}
                case TYPE_DOUBLE:{
                    boost::format format(formt.empty() ? "%8.2f": formt.c_str());
                    format % (*reinterpret_cast<double*> (val_));
                    return format.str();}
                case TYPE_FLOAT:{
                    boost::format format(formt.empty() ? "%8.2f": formt.c_str());
                    format % (*reinterpret_cast<float*> (val_));
                    return format.str();}
                case TYPE_DISCRET: return val != 0 ? "1": "0";
                case TYPE_NUM64:{
                    boost::format format(formt.empty() ? "%d": formt.c_str());
                    format % (*reinterpret_cast<num64*> (val_));
                    return format.str();}
                case TYPE_UNUM64:{
                    boost::format format(formt.empty() ? "%u": formt.c_str());
                    format % (*reinterpret_cast<unum64*> (val_));
                    return format.str();}
                case TYPE_NUM32:{
                    boost::format format(formt.empty() ? "%d": formt.c_str());
                    format % (*reinterpret_cast<num32*> (val_));
                    return format.str();}
                case TYPE_UNUM32:{
                    boost::format format(formt.empty() ? "%u": formt.c_str());
                    format % (*reinterpret_cast<unum32*> (val_));
                    return format.str();}
                case TYPE_NUM16:{
                    boost::format format(formt.empty() ? "%d": formt.c_str());
                    format % (*reinterpret_cast<num16*> (val_));
                    return format.str();}
                case TYPE_UNUM16:{
                    boost::format format(formt.empty() ? "%u": formt.c_str());
                    format % (*reinterpret_cast<unum16*> (val_));
                    return format.str();}
                case TYPE_NUM8:{
                    boost::format format(formt.empty() ? "%d": formt.c_str());
                    format % (*reinterpret_cast<num8*> (val_));
                    return format.str();}
                case TYPE_UNUM8:{
                    boost::format format(formt.empty() ? "%u": formt.c_str());
                    format % (*reinterpret_cast<num8*> (val_));
                    return format.str();}
                case TYPE_TM: num64_and_type_cast<std::string > (val, type);
                default:{
                    boost::format format(formt.empty() ? "%8.2f" : formt.c_str());
                    format % (*reinterpret_cast<double*> (val_));
                    return format.str();}}}        catch (...) {}
        return "";}

    std::string num64_and_type_cast(const num64& val, tagtype type, onum ladsk) {
        return (ladsk > 0) ?
                num64_and_type_cast(val, type, "%12." + to_str(ladsk > 10 ? 10 : ladsk) + "f") : num64_and_type_cast<std::string > (val, type);}

    template<> num64 num64_from_vt_cast<datetime>(const datetime& val, tagtype type) {
        return (type == TYPE_TM) ? num64_cast<datetime > (val) : 0;}

    template<> num64 num64_from_vt_cast<std::string>(const std::string& val, tagtype type) {
        num64 def = 0;
        num64 tmpresult = def;
        switch (type) {
            case TYPE_DISCRET: return val != "0" ? 1: 0;
            case TYPE_NUM64:{
                return str_to<num64 > (val, tmpresult) ? tmpresult : def;}
            case TYPE_UNUM64:{
                unum64* tmp = reinterpret_cast<unum64*> (&tmpresult);
                return str_to<unum64 > (val, *tmp) ? tmpresult : def;}
            case TYPE_NUM32:{
                num32* tmp = reinterpret_cast<num32*> (&tmpresult);
                return str_to<num32 > (val, *tmp) ? (tmpresult & 0xFFFFFFFF) : def;}
            case TYPE_UNUM32:{
                unum32* tmp = reinterpret_cast<unum32*> (&tmpresult);
                return str_to<unum32 > (val, *tmp) ? (tmpresult & 0xFFFFFFFF) : def;}
            case TYPE_NUM16:{
                num16* tmp = reinterpret_cast<num16*> (&tmpresult);
                return str_to<num16 > (val, *tmp) ? (tmpresult & 0xFFFF) : def;}
            case TYPE_UNUM16:{
                unum16* tmp = reinterpret_cast<unum16*> (&tmpresult);
                return str_to<unum16 > (val, *tmp) ? (tmpresult & 0xFFFF) : def;}
            case TYPE_NUM8:{
                num8* tmp = reinterpret_cast<num8*> (&tmpresult);
                return str_to<num8 > (val, *tmp) ? (tmpresult & 0xFF) : def;}
            case TYPE_UNUM8:{
                unum8* tmp = reinterpret_cast<unum8*> (&tmpresult);
                return str_to<unum8 > (val, *tmp) ? (tmpresult & 0xFF) : def;}
            case TYPE_DOUBLE:{
                double* tmp = reinterpret_cast<double*> (&tmpresult);
                return str_to<double>(val, *tmp) ? tmpresult : def;}
            case TYPE_FLOAT:{
                float* tmp = reinterpret_cast<float*> (&tmpresult);
                return str_to<float>(val, *tmp) ? (tmpresult & 0xFFFFFFFF) : def;}
            case TYPE_TM:{
                datetime tmp = nill_time;
                str_to(val, tmp);
                return castnum64_from_datetime(tmp);}
            default:{
                double* tmp = reinterpret_cast<double*> (&tmpresult);
                return str_to<double>(val, *tmp) ? tmpresult : def;}}
        double* tmp = reinterpret_cast<double*> (&tmpresult);
        return str_to<double>(val, *tmp) ? tmpresult : def;}

    bool num64_from_vt_cast(const std::string& val, tagtype type, num64& rslt) {

        switch (type) {
            case TYPE_DISCRET:{
                rslt = (val != "0") ? 1 : 0;
                return true;
                ;}
            case TYPE_NUM64:{
                return str_to<num64 > (val, rslt);}
            case TYPE_UNUM64:{
                unum64* tmp = reinterpret_cast<unum64*> (&rslt);
                return str_to<unum64 > (val, *tmp);}
            case TYPE_NUM32:{
                num32* tmp = reinterpret_cast<num32*> (&rslt);
                return str_to<num32 > (val, *tmp);}
            case TYPE_UNUM32:{
                unum32* tmp = reinterpret_cast<unum32*> (&rslt);
                return str_to<unum32 > (val, *tmp);}
            case TYPE_NUM16:{
                num16* tmp = reinterpret_cast<num16*> (&rslt);
                return str_to<num16 > (val, *tmp);}
            case TYPE_UNUM16:{
                unum16* tmp = reinterpret_cast<unum16*> (&rslt);
                return str_to<unum16 > (val, *tmp);}
            case TYPE_NUM8:{
                num8* tmp = reinterpret_cast<num8*> (&rslt);
                return str_to<num8 > (val, *tmp);}
            case TYPE_UNUM8:{
                unum8* tmp = reinterpret_cast<unum8*> (&rslt);
                return str_to<unum8 > (val, *tmp);}
            case TYPE_DOUBLE:{
                double* tmp = reinterpret_cast<double*> (&rslt);
                return str_to<double>(val, *tmp);}
            case TYPE_FLOAT:{
                float* tmp = reinterpret_cast<float*> (&rslt);
                return str_to<float>(val, *tmp);}
            default:{
                double* tmp = reinterpret_cast<double*> (&rslt);
                return str_to<double>(val, *tmp);}}
        double* tmp = reinterpret_cast<double*> (&rslt);
        return str_to<double>(val, *tmp);}

    num64 num64_for_type_min(tagtype type) {

        switch (type) {
            case TYPE_DISCRET:{
                return 0;}
            case TYPE_NUM64:{
                return std::numeric_limits<num64 >::min();}
            case TYPE_UNUM64:{
                return std::numeric_limits<unum64 >::min();}
            case TYPE_NUM32:{
                return std::numeric_limits<num32 >::min();}
            case TYPE_UNUM32:{
                return std::numeric_limits<unum32 >::min();}
            case TYPE_NUM16:{
                return std::numeric_limits<num16 >::min();}
            case TYPE_UNUM16:{
                return std::numeric_limits<unum16 >::min();}
            case TYPE_NUM8:{
                return std::numeric_limits<num8 >::min();}
            case TYPE_UNUM8:{
                return std::numeric_limits<unum8 >::min();}
            case TYPE_FLOAT:{
                return static_cast<num64> (std::numeric_limits<float >::min());}
            default:{
                return num64_from_vt_cast<double>(0, 0);}}
        return num64_from_vt_cast<double>(0, 0);}

    num64 num64_for_type_max(tagtype type) {

        switch (type) {
            case TYPE_DISCRET:{
                return 1;}
            case TYPE_NUM64:{
                return std::numeric_limits<num64 >::max();}
            case TYPE_UNUM64:{
                return std::numeric_limits<unum64 >::max();}
            case TYPE_NUM32:{
                return std::numeric_limits<num32 >::max();}
            case TYPE_UNUM32:{
                return std::numeric_limits<unum32 >::max();}
            case TYPE_NUM16:{
                return std::numeric_limits<num16 >::max();}
            case TYPE_UNUM16:{
                return std::numeric_limits<unum16 >::max();}
            case TYPE_NUM8:{
                return std::numeric_limits<num8 >::max();}
            case TYPE_UNUM8:{
                return std::numeric_limits<unum8 >::max();}
            case TYPE_FLOAT:{
                return static_cast<num64> (std::numeric_limits<float >::max());}
            default:{
                return num64_from_vt_cast<double>(100, 0);}}
        return num64_from_vt_cast<double>(100, 0);}

    num64 num64_for_type_null(tagtype type) {

        switch (type) {
            case TYPE_DISCRET:
            case TYPE_NUM64:
            case TYPE_UNUM64:
            case TYPE_NUM32:
            case TYPE_UNUM32:
            case TYPE_NUM16:
            case TYPE_UNUM16:
            case TYPE_NUM8:
            case TYPE_UNUM8:{
                return 0;}
            case TYPE_FLOAT:{
                return num64_from_vt_cast<double>(0, 0);}
            default:{
                return num64_from_vt_cast<double>(0, 0);}}
        return num64_from_vt_cast<double>(0, 0);}



    ////////////////////////////////////////////////////////////////////////////////////

    datetime now() {
        return boost::posix_time::microsec_clock::local_time();}

    boost::xtime utc_now() {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        return xt;}

    boost::xtime utc_now_plus_millsec(num32 tmout) {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += tmout / 1000;
        if ((xt.nsec + (tmout % 1000) * 1000000) < 1000000000) {
            xt.nsec += (tmout % 1000) * 1000000;} else {
            xt.sec += 1;
            xt.nsec += ((tmout % 1000) * 1000000 + xt.nsec - 1000000000);}
        return xt;}

    boost::xtime utc_now_plus_sec(num32 tmout) {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += tmout;
        return xt;}

    bool expire_from_utc_millsec(const boost::xtime& vl, num32 tmout) {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec -= tmout / 1000;
        if (xt.nsec > ((tmout % 1000) * 1000000)) {
            xt.nsec -= ((tmout % 1000) * 1000000);} else {
            xt.sec -= 1;
            xt.nsec = 1000000000 - ((tmout % 1000) * 1000000 - xt.nsec);}
        return ((vl.sec < xt.sec) || ((vl.sec == xt.sec) && (vl.nsec < xt.nsec)));}

    bool expire_from_utc_sec(const boost::xtime& vl, num32 tmout) {
        boost::xtime xt;
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec -= tmout;
        return ((vl.sec < xt.sec) || ((vl.sec == xt.sec) && (vl.nsec < xt.nsec)));}

    void addmillisec_to_now(boost::xtime& xt, num64 milsec) {
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += milsec / 1000;
        if ((xt.nsec + (milsec % 1000) * 1000000) < 1000000000) {
            xt.nsec += (milsec % 1000) * 1000000;} else {
            xt.sec += 1;
            xt.nsec += ((milsec % 1000) * 1000000 + xt.nsec - 1000000000);}}

    void addmicrosec_to_now(boost::xtime& xt, num64 microsec) {
        boost::xtime_get(&xt, boost::TIME_UTC);
        xt.sec += microsec / 1000000;
        if ((xt.nsec + (microsec % 1000000) * 1000) < 1000000000) {
            xt.nsec += (microsec % 1000000) * 1000;} else {
            xt.sec += 1;
            xt.nsec += ((microsec % 1000000) * 1000 + xt.nsec - 1000000000);}}

    num64 nownum64() {
        return castnum64_from_datetime(now());}

    boost::posix_time::time_duration duration_between(datetime t1, datetime t2) {
        boost::posix_time::time_period td(t1, t2);
        return td.length();}

    num64 secondsbetween(datetime t1, datetime t2) {
        if ((t1.is_special()) || (t2.is_special())) {
            return ((t1.is_special()) && (t1.is_special())) ? 0 : 0xFFFFFFFF;}
        return duration_between(t1, t2).total_seconds();}

    num64 millisecondsbetween(datetime t1, datetime t2) {
        if ((t1.is_special()) || (t2.is_special())) {
            return ((t1.is_special()) && (t1.is_special())) ? 0 : 0xFFFFFFFF;}
        return duration_between(t1, t2).total_milliseconds();}

    num64 microsecondsbetween(datetime t1, datetime t2) {
        if ((t1.is_special()) || (t2.is_special())) {
            return ((t1.is_special()) && (t1.is_special())) ? 0 : 0xFFFFFFFF;}
        return duration_between(t1, t2).total_microseconds();}

    num64 secondsbetween(num64 t1, num64 t2) {
        return secondsbetween(cast_datetime_fromnum64(t1), cast_datetime_fromnum64(t2));}

    bool seconds_between_more_then(datetime t1, datetime t2, num64 range) {
        num64 val = secondsbetween(t1, t2);
        val = val < 0 ? (-1) * val : val;
        return (range <= val);}

    bool seconds_between_more_then(num64 t1, num64 t2, num64 range) {
        return seconds_between_more_then(cast_datetime_fromnum64(t1), cast_datetime_fromnum64(t2), range);}

    datetime cast_datetime_fromnum64(num64 val) {
        try {
            return val != 0 ? * reinterpret_cast<datetime*> (&val) : datetime();}        catch (...) {}
        return nill_time;}

    num64 castnum64_from_datetime(datetime val) {
        return (!val.is_not_a_date_time()) ? * reinterpret_cast<num64*> (&val) : 0;}

    num64 datetime_to_epoch(const datetime& val) {
        return val.is_special() ? 0 : static_cast<num64> (static_cast<boost::posix_time::time_duration> (val - epoch_time).total_seconds());}

    num64 datetime_to_epoch_msc(const datetime& val) {
        return val.is_special() ? 0 : static_cast<num64> (static_cast<boost::posix_time::time_duration> (val - epoch_time).total_milliseconds());}

    num64 datetime_to_epoch_minute(const datetime& val) {
        return val.is_special() ? 0 : static_cast<num64> (static_cast<boost::posix_time::time_duration> (val - epoch_time).total_seconds() / 60);}

    num64 datetime_to_epoch_hour(const datetime& val) {
        return val.is_special() ? 0 : static_cast<num64> (static_cast<boost::posix_time::time_duration> (val - epoch_time).total_seconds() / 3600);}

    num64 datetime_to_epoch_day(const datetime& val) {
        return val.is_special() ? 0 : static_cast<num64> (static_cast<boost::posix_time::time_duration> (val - epoch_time).total_seconds() / (3600 * 24));}

    std::string datetime_to_string(datetime val, bool withmsec) {
        try {
            if (val.is_special()) return "";
            std::string tmp = boost::gregorian::to_iso_extended_string(val.date()) + " ";
            if (withmsec) {
                boost::format frmt("%02.2d:%02.2d:%02.2d.%03.3d");
                frmt % val.time_of_day().hours() % val.time_of_day().minutes() % val.time_of_day().seconds() % val.time_of_day().total_milliseconds();
                tmp += frmt.str();} else {
                boost::format frmt("%02.2d:%02.2d:%02.2d");
                frmt % val.time_of_day().hours() % val.time_of_day().minutes() % val.time_of_day().seconds();
                tmp += frmt.str();}
            return tmp;}        catch (...) {}
        return "null";}

    std::string datetime_to_string(num64 val, bool withmsec) {
        return datetime_to_string(cast_datetime_fromnum64(val), withmsec);}

    std::string dt_to_journaltabelname(datetime tm) {
        try {
            boost::format frmt("journal%02.2d%04.4d");
            frmt % tm.date().month().as_number() % tm.date().year();
            return frmt.str();}        catch (...) {}
        return "nulljournal";}

    std::string dt_to_debugtabelname(datetime tm) {
        try {
            boost::format frmt("debug%02.2d%04.4d");
            frmt % tm.date().month().as_number() % tm.date().year();
            return frmt.str();}        catch (...) {}
        return "nulldebug";}

    std::string dt_to_trendtabelname(datetime tm) {
        try {
            boost::format frmt("trend%02.2d%02.2d%04.4d");
            frmt % tm.date().day() % tm.date().month().as_number() % tm.date().year();
            return frmt.str();}        catch (...) {}
        return "nulltrend";}

    std::string dt_to_reporttabelname(datetime tm, tagtype type) {
        try {
            switch (type) {
                case REPORTTYPE_YEAR:
                case REPORTTYPE_QVART:
                case REPORTTYPE_MONTH: return "arch";
                case REPORTTYPE_DEC:
                case REPORTTYPE_DAY:{
                    boost::format frmt("arch%04.4d");
                    frmt % tm.date().year();
                    return frmt.str();}}

            boost::format frmt("arch%02.2d%04.4d");
            frmt % tm.date().month().as_number() % tm.date().year();
            return frmt.str();}        catch (...) {}
        return "nullreport";}

    datetime incmillisecond(datetime tm, num64 delt) {
        return delt > 0 ? (tm + boost::posix_time::millisec(delt)) : (tm - boost::posix_time::millisec(-delt));}

    datetime incsecond(datetime tm, num64 delt) {
        return delt > 0 ? (tm + boost::posix_time::seconds(static_cast<long> (delt))) : (tm - boost::posix_time::seconds(static_cast<long> (-delt)));}

    datetime incminute(datetime tm, num64 delt) {
        return incsecond(tm, delt * 60);}

    datetime inchour(datetime tm, num64 delt) {
        return incsecond(tm, delt * 3600);}

    datetime incmonth(datetime tm, num64 delt) {
        return (tm + boost::gregorian::months(static_cast<int> (delt)));}

    datetime incday(datetime tm, num64 delt) {
        return (tm + boost::gregorian::days(static_cast<long> (delt)));}

    datetime incyear(datetime tm, num64 delt) {
        return tm + boost::gregorian::years(static_cast<long> (delt));}

    std::tm to_std_tm(datetime tm) {
        return boost::posix_time::to_tm(tm);}

    bool incperiod(datetime& val, int type, reporthisttype n) {
        using namespace boost::posix_time;
        if (val.is_special()) return false;
        switch (type) {
            case MICSECOND_TM:{
                val = val + microseconds(n);
                break;}
            case MILLISECOND_TM:{
                val = val + milliseconds(n);
                break;}
            case SECOND_TM:{
                val = val + seconds(static_cast<long> (n));
                break;}
            case MINUTE_TM:{
                val = val + minutes(static_cast<long> (n));
                break;}
            case MINUTE10_TM:{
                val = val + minutes(static_cast<long> (10 * n));
                break;}
            case MINUTE30_TM:{
                val = val + minutes(static_cast<long> (30 * n));
                break;}
            case HOUR_TM:{
                val = val + hours(static_cast<long> (n));
                break;}
            case DAY_TM:{
                val = val + boost::gregorian::days(static_cast<long> (n));
                break;}
            case DAY10_TM:{
                val = val + boost::gregorian::days(static_cast<long> (10 * n));
                break;}
            case MONTH_TM:{
                val = val + boost::gregorian::months(static_cast<int> (n));
                break;}
            case QUART_TM:{
                val = val + boost::gregorian::months(static_cast<int> (4 * n));
                break;}
            case YAER_TM:{
                val = val + boost::gregorian::years(static_cast<int> (n));
                break;}}
        return true;}

    bool normalizeperiod(datetime& val, int type) {
        using namespace boost::posix_time;
        if (val.is_special()) return false;
        datetime val_ = val;
        switch (type) {
            case SECOND_TM:{
                val_ = datetime(val.date(),
                        hours(val.time_of_day().hours()) + minutes(val.time_of_day().minutes()) + seconds(val.time_of_day().seconds()));
                break;}
            case MINUTE_TM:{
                val_ = datetime(val.date(),
                        hours(val.time_of_day().hours()) + minutes(val.time_of_day().minutes()));
                break;}
            case MINUTE10_TM:{
                val_ = datetime(val.date(),
                        hours(val.time_of_day().hours()) + minutes(static_cast<int> ((val.time_of_day().minutes()) / 10)*10));
                break;}
            case MINUTE30_TM:{
                val_ = datetime(val.date(),
                        hours(val.time_of_day().hours()) + minutes(static_cast<int> ((val.time_of_day().minutes()) / 30)*30));
                break;}
            case HOUR_TM:{
                val_ = datetime(val.date(), hours(val.time_of_day().hours()));
                break;}
            case DAY_TM:{
                val_ = datetime(boost::gregorian::date(val.date().year(), val.date().month(), val.date().day()));
                break;}
            case DAY10_TM:{
                val_ = static_cast<int> ((val.date().day() / 10)) == 3 ? datetime(boost::gregorian::date(val.date().year(), val.date().month(), 21)) :
                        datetime(boost::gregorian::date(val.date().year(), val.date().month(), 1 + static_cast<int> ((val.date().day() / 10))*10));
                break;}
            case MONTH_TM:{
                val_ = datetime(boost::gregorian::date(val.date().year(), val.date().month(), 1));
                break;}
            case QUART_TM:{
                val_ = datetime(boost::gregorian::date(val.date().year(), 1 + (static_cast<int> ((val.date().month() / 4)) * 4), 1));
                break;}
            case YAER_TM:{
                val_ = datetime(boost::gregorian::date(val.date().year(), 1, 1));
                break;}}
        val = val_;
        return true;}

    bool beforetabletime(datetime& tm, reporttype tp) {
        switch (tp) {
            case REPORTTYPE_MIN:
            case REPORTTYPE_HOUR:
            case REPORTTYPE_10MIN:
            case REPORTTYPE_30MIN:{
                incperiod(tm, MONTH_TM, -1);
                return true;}
            case REPORTTYPE_DEC:
            case REPORTTYPE_DAY:{
                incperiod(tm, YAER_TM, -1);
                return true;}}
        return false;}

    bool normalizereporttime(datetime& val, reporttype tp) {
        switch (tp) {
            case REPORTTYPE_YEAR: return normalizeperiod(val, YAER_TM);
            case REPORTTYPE_MIN: return normalizeperiod(val, MINUTE_TM);
            case REPORTTYPE_HOUR: return normalizeperiod(val, HOUR_TM);
            case REPORTTYPE_DEC: return normalizeperiod(val, DAY10_TM);
            case REPORTTYPE_DAY: return normalizeperiod(val, DAY_TM);
            case REPORTTYPE_MONTH: return normalizeperiod(val, MONTH_TM);
            case REPORTTYPE_10MIN: return normalizeperiod(val, MINUTE10_TM);
            case REPORTTYPE_30MIN: return normalizeperiod(val, MINUTE30_TM);
            case REPORTTYPE_QVART: return normalizeperiod(val, QUART_TM);}
        return normalizeperiod(val, MINUTE_TM);}

    bool increporttime(datetime& val, reporttype tp, reporthisttype n) {
        switch (tp) {
            case REPORTTYPE_YEAR: return incperiod(val, YAER_TM, n);
            case REPORTTYPE_MIN: return incperiod(val, MINUTE_TM, n);
            case REPORTTYPE_HOUR: return incperiod(val, HOUR_TM, n);
            case REPORTTYPE_DEC: return incperiod(val, DAY10_TM, n);
            case REPORTTYPE_DAY: return incperiod(val, DAY_TM, n);
            case REPORTTYPE_MONTH: return incperiod(val, MONTH_TM, n);
            case REPORTTYPE_10MIN: return incperiod(val, MINUTE10_TM, n);
            case REPORTTYPE_30MIN: return incperiod(val, MINUTE30_TM, n);
            case REPORTTYPE_QVART: return incperiod(val, QUART_TM, n);}
        return false;}

    void statistic_functor::operator()(const dt_val_pair& vl) {
        switch (type) {
            case REPORT_STATISTIC_MIN:{
                if (vl.second == vl.second) {
                    value = (value != value) ? vl.second: (value > vl.second ? vl.second: value);
                    cnt++;}
                return;}
            case REPORT_STATISTIC_MAX:{
                if (vl.second == vl.second) {
                    value = (value != value) ? vl.second: (value < vl.second ? vl.second: value);
                    cnt++;}
                return;}
            default:{
                if (vl.second == vl.second) {
                    value = (value != value) ? vl.second : vl.second + value;
                    cnt++;}
                return;}}}

    double statistic_functor::countedvalue() {
        DEBUG_STR_VAL_DVNCI(operatorii, value);
        DEBUG_STR_VAL_DVNCI(operatorii, cnt);
        if ((!cnt) || (value != value)) return NULL_DOUBLE;
        switch (type) {
            case REPORT_STATISTIC_AVER: return value / cnt;
            case REPORT_STATISTIC_INTEG: return value;
            case REPORT_STATISTIC_SUM:
            case REPORT_STATISTIC_MIN:
            case REPORT_STATISTIC_MAX: return value;
            default:return value / cnt;}
        return value / cnt;}

    void integr_statistic_functor::operator()(const dt_val_pair& vl) {
        if ((vl.second == vl.second) && (!vl.first.is_special()) && (!lstpoint.first.is_special())) {
            if (value != value) value = 0;
            value += (dvnci::abs(millisecondsbetween(vl.first, lstpoint.first)) / 1000.0 / 3600.0) * ((vl.second + lstpoint.second) / 2);
            lstpoint = vl;
            cnt++;}}

    double integr_statistic_functor::countedvalue() {
        DEBUG_STR_VAL_DVNCI(operatorii, value);
        DEBUG_STR_VAL_DVNCI(operatorii, cnt);
        return value;}

}

