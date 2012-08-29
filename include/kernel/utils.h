/* 
 * File:   ns_stringutils.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 8 пїЅпїЅпїЅпїЅпїЅпїЅ 2009 пїЅ., 18:44
 */

#ifndef _DVNCI_KRNL_NS_STRINGUTILS_H
#define	_DVNCI_KRNL_NS_STRINGUTILS_H

#include <kernel/constdef.h>
#include <kernel/utf8.h>

namespace dvnci {


    const int NANOSECOND_TM = 0x0;
    const int MICSECOND_TM = 0x1;
    const int MILLISECOND_TM = 0x2;
    const int SECOND_TM = 0x3;
    const int MINUTE_TM = 0x4;
    const int MINUTE10_TM = 0x5;
    const int MINUTE30_TM = 0x6;
    const int HOUR_TM = 0x7;
    const int DAY_TM = 0x8;
    const int DAY10_TM = 0x9;
    const int MONTH_TM = 0xA;
    const int QUART_TM = 0xB;
    const int YAER_TM = 0xC;

    const char hex_char_array_const[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    const char bad_hex_char = '\xFF';
    const char bad_oct_char = '\xFF';
    const char bad_bin_char = '\xFF';

    struct short_value;


    bool check_utf8(const std::string& val);
    
    std::wstring utf8_to_wstr(const std::string& val);
    bool utf8_to_wstr(const std::string& val, std::wstring& rslt); 
    std::string wstr_to_utf8(const std::wstring& val);
    bool wstr_to_utf8(const std::wstring& val, std::string& rslt);
    
    

    void string_to_pascalstr(void* val, const std::string& source, size_t len);
    std::string pascalstr_to_string(void* dest);

    void formatmem_in_null(void* ptr, size_t len);

    std::string lower_copy(const std::string& val);
    std::wstring lower_copy(const std::wstring& val);
    std::string upper_copy(const std::string& val);
    std::wstring upper_copy(const std::wstring& val);
    std::string trim_copy(const std::string& val);
    std::wstring trim_copy(const std::wstring& val);
    std::string fulltrim_copy(const std::string& val);
    std::wstring fulltrim_copy(const std::wstring& val);
    std::string freechar_copy(const std::string& val, const std::string& del = " ");
    std::wstring freechar_copy(const std::wstring& val, const std::wstring& del = L" ");

    void fulltrim(std::string& val);
    void fulltrim(std::wstring& val);
    void upper_and_trim(std::string& val);
    void upper_and_trim(std::wstring& val);
    void lower_and_trim(std::string& val);
    void lower_and_trim(std::wstring& val);
    void upper_and_fulltrim(std::string& val);
    void upper_and_fulltrim(std::wstring& val);
    void lower_and_fulltrim(std::string& val);
    void lower_and_fulltrim(std::wstring& val);

    size_t regex_tokin_parser(const std::string& val, str_vect& dst, const boost::regex& re);
    size_t regex_tokin_parser(const std::wstring& val, wstr_vect& dst, const boost::wregex& re);
    size_t regex_tokin_parser(const std::wstring& val, str_vect& dst, const boost::wregex& re);

    bool instrincriteria(std::string nm, std::string strcriteria);

    bool remove_namespace_delimit(std::string& vl);
    bool remove_namespace_delimit(std::wstring& vl);
    std::string retremoved_namespace_delimit(const std::string& vl);
    std::wstring retremoved_namespace_delimit(const std::wstring& vl);
    std::string get_namespace_delimit(std::string& vl);
    std::wstring get_namespace_delimit(std::wstring& vl);
    
    
    std::string attribute_expression(std::string val);
    std::wstring attribute_expression(std::wstring val);
    
    std::string attribute_default_expression(std::string val);
    std::wstring attribute_default_expression(std::wstring val);


    size_t split_str(const std::string& source, const std::string& delimit, str_vect& vectstr);
    size_t split_str_prefix(const std::string& source, const std::string& delimit, str_vect& vectstr);
    size_t split_str_postfix(const std::string& source, const std::string& delimit, str_vect& vectstr);
    void split_2str(const std::string& source, const std::string& delimit, std::string& val1, std::string& val2);
    void split_3str(const std::string& source, const std::string& delimit, std::string& val1, std::string& val2, std::string& val3);
    void split_4str(const std::string& source, const std::string& delimit, std::string& val1, std::string& val2, std::string& val3, std::string& val4);
    void parse_servinfo(const std::string& source, std::string& host, std::string& port, unsigned int& timout, std::string& admin, std::string& pass);
    std::string generate_servinfo(const std::string& host, const std::string& port, unsigned int timout, const std::string& admin, const std::string& pass);

    template <typename T> bool string_to_primtype(const std::string& dblk, T& vl) {
        if (sizeof (vl) > dblk.size()) return false;
        vl = *(reinterpret_cast<T*> (const_cast<char*> (dblk.data())));
        return true;}

    template <typename T> std::string primtype_to_string(T vl) {
        return std::string(((const char*) &vl), sizeof (T));}

    inline static num16 be_le_convert_num16(num16 vl) {
        return (((vl >> 8) & 0xFF) | (0xFF00 & (vl << 8)));}

    inline static num32 be_le_convert_num32(num32 vl) {
        return (((vl >> 16) & 0xFFFF) | (0xFFFF0000 & (vl << 16)));}

    inline static num64 be_le_convert_num64(num64 vl) {
        return (((vl >> 32) & 0xFFFFFFFFLL) | (0xFFFFFFFF00000000LL & (vl << 32)));}

    bool be_le16_convert_string(std::string& vl);

    std::string binary_block_to_hexsequence_debug(const std::string& vl);

    std::string binary_block_to_hexsequence_copy(const std::string& vl);

    void binary_block_to_hexsequence(std::string& vl);

    bool hexsequence_to_binary_block(const std::string& vl, std::string& rslt);

    void comma_to_point(std::string& val);
    void comma_to_point(std::wstring& val);
    void point_to_comma(std::string& val);
    void point_to_comma(std::wstring& val);

    std::string comma_to_point_copy(const std::string& val);
    std::wstring comma_to_point_copy(const std::wstring& val);
    std::string point_to_comma_copy(const std::string& val);
    std::wstring point_to_comma_copy(const std::wstring& val);

    void clear_first_null_digit(std::string& vl);
    void clear_first_null_digit(std::wstring& vl);
    void fill_first_null_digit(std::string& vl, size_t needcsize);
    void fill_first_null_digit(std::wstring& vl, size_t needcsize);

    std::string clear_first_null_digit_copy(const std::string& vl);
    std::wstring clear_first_null_digit_copy(const std::wstring& vl);
    std::string fill_first_null_digit_copy(const std::string& vl, size_t needcsize);
    std::wstring fill_first_null_digit_copy(const std::wstring& vl, size_t needcsize);

    std::string num8_to_hexstr(num8 vl);
    std::string num16_to_hexstr(num16 vl);
    std::string num32_to_hexstr(num32 vl);
    std::string num64_to_hexstr(num64 vl);

    template <typename T>
    inline T cycl_btlft(T vl, size_t n) {
        n %= (sizeof (T) * 8);
        return ((vl << n) | (vl >> ((sizeof (T)* 8) - n)));}

    template <typename T>
    inline T cycl_btrgt(T vl, size_t n) {
        n %= (sizeof (T) * 8);
        return ((vl >> n) | (vl << ((sizeof (T)* 8) - n)));}

    static inline char hexchar_to_char(char vl) {
        return ((vl >= 0x30) && (vl <= 0x39)) ? (vl - 0x30) :
                ((vl >= 0x41) && (vl <= 0x46)) ? (vl - 0x37) : bad_hex_char;}

    static inline char octchar_to_char(char vl) {
        return ((vl >= 0x30) && (vl <= 0x37)) ? (vl - 0x30) : bad_oct_char;}

    static inline char binchar_to_char(char vl) {
        return ((vl >= 0x30) && (vl <= 0x31)) ? (vl - 0x30) : bad_bin_char;}

    template <typename T> bool hexstr_to(std::string val, T& result) {
        upper_and_trim(val);
        clear_first_null_digit(val);
        if (val.empty()) return false;
        result = 0;
        char tmpch = 0;
        for (std::string::size_type it = 0; it < val.size(); ++it) {
            tmpch = hexchar_to_char(val.at(it));
            if (tmpch == bad_hex_char) return false;
            result = ((result << 4) | (tmpch & 0xF));}
        return true;}

    template <typename T> bool octstr_to(std::string val, T& result) {
        upper_and_trim(val);
        clear_first_null_digit(val);
        if (val.empty()) return false;
        result = 0;
        char tmpch = 0;
        for (std::string::size_type it = 0; it < val.size(); ++it) {
            tmpch = octchar_to_char(val.at(it));
            if (tmpch == bad_oct_char) return false;
            result = ((result << 3) | (tmpch & 0x7));}
        return true;}

    template <typename T> bool binstr_to(std::string val, T& result) {
        upper_and_trim(val);
        clear_first_null_digit(val);
        if (val.empty()) return false;
        result = 0;
        char tmpch = 0;
        for (std::string::size_type it = 0; it < val.size(); ++it) {
            tmpch = binchar_to_char(val.at(it));
            if (tmpch == bad_bin_char) return false;
            result = ((result << 1) | (tmpch & 0x1));}
        return true;}

    template <typename T> bool bcd_to_dec(const T& src, T& vl) {
        vl = 0;
        for (size_t i = sizeof (T) * 2; i > 0; --i) {
            num8 tmp8 = (src >> ((i - 1) * 4)) & 0xF;
            if (tmp8 > 9) return false;
            else vl = vl * 10 + tmp8;}
        return true;}

    template <typename T> bool bcd_to_dec(T& vl) {
        T tmp = 0;
        bool rslt = bcd_to_dec<T > (vl, tmp);
        vl = tmp;
        return rslt;}

    template <typename T> bool dec_to_bcd(const T& src, T& vl) {
        vl = 1;
        size_t i = sizeof (T);
        while (i--) {
            vl *= 100;}
        if (src >= vl) return false;
        vl = 0;
        T tmp = src;
        i = 0;
        while (tmp) {
            vl |= ((tmp % 10) << (4 * i++));
            tmp /= 10;}
        return true;}

    template <typename T> bool dec_to_bcd(T& vl) {
        T tmp = 0;
        bool rslt = dec_to_bcd<T > (vl, tmp);
        vl = tmp;
        return rslt;}

    template <typename T> std::string to_str(const T& val) {

        std::string result = "";
        try {
            result = boost::lexical_cast<std::string > (val);}
        catch (boost::bad_lexical_cast) {
            return "";}
        return result;}

    template <typename T> std::wstring to_wstr(const T& val) {

        std::wstring result = L"";
        try {
            result = boost::lexical_cast<std::wstring > (val);}
        catch (boost::bad_lexical_cast) {
            return L"";}
        return result;}

    template<typename T> std::string to_str(const T& vl, const std::string& frmt) {
        if (frmt.empty()) return to_str<T > (vl);
        try {
            boost::format f(frmt.c_str());
            f % vl;
            return f.str();}
        catch (...) {}
        return to_str<T > (vl);}

    template<typename T> std::wstring to_wstr(const T& vl, const std::wstring& frmt) {
        if (frmt.empty()) return to_str<T > (vl);
        try {
            boost::format f(frmt.c_str());
            f % vl;
            return f.str();}
        catch (...) {}
        return to_str<T > (vl);}

    std::string to_str(const datetime& val);
    std::wstring to_wstr(const datetime& val);

    template <typename T> bool str_to(const std::string& val, T& result) {

        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return false;}
        return true;}

    template <typename T> bool str_to(const std::wstring& val, T& result) {

        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return false;}
        return true;}

    bool str_to(const std::string& val, datetime& result);
    bool str_to(const std::wstring& val, datetime& result);

    template <typename T> T str_to(const std::string& val, const T& def = 0) {

        try {
            return boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return def;}}

    template <typename T> T str_to(const std::wstring& val, const T& def = 0) {

        try {
            return boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return def;}}


    datetime str_to(const std::string& val, const datetime& def = nill_time);
    datetime str_to(const std::wstring& val, const datetime& def = nill_time);

    template <typename T> void str_to(const std::string& val, const T& def, T& result) {

        result = def;
        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            result = def;}}

    template <typename T> void str_to(const std::wstring& val, const T& def, T& result) {

        result = def;
        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            result = def;}}

    void str_to(const std::string& val, const datetime& def, datetime& result);
    void str_to(const std::wstring& val, const datetime& def, datetime& result);

    template <typename T> T abs(const T& v) {
        return v >= 0 ? v : -v;}

    template <> bool abs<bool>(const bool& v);

    template <> datetime abs<datetime>(const datetime& v);

    template <> unum64 abs<unum64>(const unum64& v);

    template <> unum32 abs<unum32>(const unum32& v);

    template <> unum16 abs<unum16>(const unum16& v);

    template <> unum8 abs<unum8>(const unum8& v);

    template <> std::string abs<std::string>(const std::string& v);

    template <typename T> void in_bound(const T& min, const T& max, T& val) {
        val = max < val ? max : min > val ? min : val;}

    template <typename T> T in_bounded(const T& min, const T& max, T val) {
        val = max < val ? max : min > val ? min : val;
        return val;}

    template<typename T>  const T& from_num64_cast(const num64& val) {
        return ((ptype_punned) (&val))->n64;}

    template<>  const bool& from_num64_cast<bool>(const num64& val);

    template<>  const num64& from_num64_cast<num64>(const num64& val);

    template<>  const unum64& from_num64_cast<unum64>(const num64& val);

    template<>  const num32& from_num64_cast<num32>(const num64& val);

    template<>  const unum32& from_num64_cast<unum32>(const num64& val);

    template<>  const num16& from_num64_cast<num16>(const num64& val);

    template<>  const unum16& from_num64_cast<unum16>(const num64& val);

    template<>  const num8& from_num64_cast<num8>(const num64& val);

    template<>  const unum8& from_num64_cast<unum8>(const num64& val);

    template<>  const float& from_num64_cast<float>(const num64& val);

    template<>  const double& from_num64_cast<double>(const num64& val);

    template<>  const datetime& from_num64_cast<datetime>(const num64& val);

    //template<>  const std::string& from_num64_cast<std::string>(const num64& val);

    template<typename T> num64 num64_cast(const T& val) {
        return type_punned(val).n64;}

    template<> num64 num64_cast<datetime>(const datetime& val);

    template<> num64 num64_cast<std::string>(const std::string& val);

    template<typename T> T num64_and_type_cast(const num64& value, tagtype type) {

        switch (type) {
            case TYPE_DISCRET:{
                return static_cast<T> (from_num64_cast<bool>(value));}
            case TYPE_NUM64:{
                return static_cast<T> (value);}
            case TYPE_UNUM64:{
                return static_cast<T> (from_num64_cast<unum64 > (value));}
            case TYPE_NUM32:{
                return static_cast<T> (from_num64_cast<num32 > (value));}
            case TYPE_UNUM32:{
                return static_cast<T> (from_num64_cast<unum32 > (value));}
            case TYPE_NUM16:{
                return static_cast<T> (from_num64_cast<num16 > (value));}
            case TYPE_UNUM16:{
                return static_cast<T> (from_num64_cast<unum16 > (value));}
            case TYPE_NUM8:{
                return static_cast<T> (from_num64_cast<num8 > (value));}
            case TYPE_UNUM8:{
                return static_cast<T> (from_num64_cast<unum8 > (value));}
            case TYPE_DOUBLE:{
                return static_cast<T> (from_num64_cast<double>(value));}
            case TYPE_FLOAT:{
                return static_cast<T> (from_num64_cast<float>(value));}
            case TYPE_TEXT:{
                return static_cast<T> (from_num64_cast<unum64 > (value));}
            case TYPE_TM:{
                return 0;}}
        return static_cast<T> (from_num64_cast<double>(value));}


    template<> datetime num64_and_type_cast<datetime>(const num64& val, tagtype type);

    template<> std::string num64_and_type_cast<std::string>(const num64& val, tagtype type);
    
    template<> std::wstring num64_and_type_cast<std::wstring>(const num64& val, tagtype type);

    std::string num64_and_type_cast(const num64& val, tagtype type, const std::string& format);

    std::string num64_and_type_cast(const num64& val, tagtype type, onum ladsk);

    template<typename T> num64 num64_from_vt_cast(const T& value, tagtype type) {

        switch (type) {
            case TYPE_DISCRET:{
                return num64_cast<bool>(static_cast<bool> (value));}
            case TYPE_NUM64:{
                return num64_cast<num64 > (static_cast<num64> (value));}
            case TYPE_UNUM64:{
                return num64_cast<unum64 > (static_cast<unum64> (value));}
            case TYPE_NUM32:{
                return num64_cast<num32 > (static_cast<num32> (value));}
            case TYPE_UNUM32:{
                return num64_cast<unum32 > (static_cast<unum32> (value));}
            case TYPE_NUM16:{
                return num64_cast<num16 > (static_cast<num16> (value));}
            case TYPE_UNUM16:{
                return num64_cast<unum16 > (static_cast<unum16> (value));}
            case TYPE_NUM8:{
                return num64_cast<num8 > (static_cast<num8> (value));}
            case TYPE_UNUM8:{
                return num64_cast<unum8 > (static_cast<unum8> (value));}
            case TYPE_DOUBLE:{
                return num64_cast<double>(static_cast<double> (value));};
            case TYPE_FLOAT:{
                return num64_cast<float>(static_cast<float> (value));}
            case TYPE_TEXT:{
                return num64_cast<unum64 > (static_cast<size_t> (value));}
            case TYPE_TM:{
                return 0;}}
        return num64_cast<double>(static_cast<double> (value));}

    template<> num64 num64_from_vt_cast<datetime>(const datetime& val, tagtype type);

    template<> num64 num64_from_vt_cast<std::string>(const std::string& val, tagtype type);

    bool num64_from_vt_cast(const std::string& val, tagtype type, num64& rslt);


    num64 num64_for_type_min(tagtype type);
    num64 num64_for_type_max(tagtype type);
    num64 num64_for_type_null(tagtype type);


    //////////////////////////////////////////////////////////////////////////////////////

    datetime now();
    datetime now_local();
    datetime local_to_utc(const datetime& val);
    datetime utc_to_local(const datetime& val);
    boost::posix_time::time_duration time_zone_offset(const datetime& val);
    double time_zone_hour_offset(const datetime& val);     
    num64 nownum64();
    num64 nownum64_local();    
    
    boost::xtime utc_now();

    boost::xtime utc_now_plus_millsec(timeouttype tmout);
    boost::xtime utc_now_plus_sec(timeouttype tmout);

    bool expire_from_utc_millsec(const boost::xtime& vl, timeouttype tmout);
    bool expire_from_utc_sec(const boost::xtime& vl, timeouttype tmout);

    /* Количество секунд между временными точками*/
    boost::posix_time::time_duration duration_between(datetime t1, datetime t2);
    num64 secondsbetween(datetime t1, datetime t2);
    num64 millisecondsbetween(datetime t1, datetime t2);
    num64 microsecondsbetween(datetime t1, datetime t2);
    num64 secondsbetween(num64 t1, num64 t2);
    bool seconds_between_more_then(datetime t1, datetime t2, num64 range);
    bool seconds_in_range_more_then(num64 t1, num64 t2, num64 range);

    datetime cast_datetime_fromnum64(num64 val);
    num64 castnum64_from_datetime(datetime val);
    num64 datetime_to_epoch(const datetime& val);
    num64 datetime_to_epoch_msc(const datetime& val);
    num64 datetime_to_epoch_msc(const datetime& val);
    num64 datetime_to_epoch_msc_utc(const datetime& val);
    num64 datetime_to_epoch_minute(const datetime& val);
    num64 datetime_to_epoch_hour(const datetime& val);
    num64 datetime_to_epoch_day(const datetime& val);
    std::string datetime_to_string(datetime val, bool withmsec = false);
    std::wstring datetime_to_wstring(datetime val, bool withmsec = false);
    std::string datetime_to_string(num64 val, bool withmsec = false);
    std::wstring datetime_to_wstring(num64 val, bool withmsec = false);

    std::string dt_to_journaltabelname(datetime tm);
    std::string dt_to_debugtabelname(datetime tm);
    std::string dt_to_trendtabelname(datetime tm);
    std::string dt_to_reporttabelname(datetime tm, tagtype type);

    datetime incmillisecond(datetime tm, num64 delt = 1);
    datetime incsecond(datetime tm, num64 delt = 1);
    datetime incminute(datetime tm, num64 delt = 1);
    datetime inchour(datetime tm, num64 delt = 1);
    datetime incmonth(datetime tm, num64 delt = 1);
    datetime incday(datetime tm, num64 delt = 1);
    datetime incyear(datetime tm, num64 delt = 1);

    void addmillisec_to_now(boost::xtime& xt, num64 milsec = 1);
    void addmicrosec_to_now(boost::xtime& xt, num64 microsec = 1);


    std::tm to_std_tm(datetime tm);

    bool incperiod(datetime& val, int type, reporthisttype n = 1);
    bool normalizeperiod(datetime& val_, int type);

    bool beforetabletime(datetime& tm, reporttype tp);
    bool normalizereporttime(datetime& val, reporttype tp);
    bool increporttime(datetime& val, reporttype tp, reporthisttype n = 1);

    // нормализация периода предыстории
    void normilize_history_bound(vlvtype  type, reporthisttype& val);
    void normilize_report_subperiod(vlvtype  type, reporthistdelt& val);


    std::string role_to_str(rolesettype vl);

    rolesettype str_to_role(std::string vl);

    struct statistic_functor {

        statistic_functor(repstattype tp) : type(tp), cnt(0), value(NULL_DOUBLE) {}

        ~statistic_functor() {}

        void operator()(const dt_val_pair & vl);
        double countedvalue();

    private:
        repstattype type;
        size_t cnt;
        double value;} ;

    struct integr_statistic_functor {

        integr_statistic_functor(const dt_val_pair & initvl) : lstpoint(initvl), cnt(0), value(NULL_DOUBLE) {}

        ~integr_statistic_functor() {}

        void operator()(const dt_val_pair & vl);
        double countedvalue();

    private:
        dt_val_pair lstpoint;
        size_t cnt;
        double value;} ;}

#endif	/* _NS_STRINGUTILS_H */

