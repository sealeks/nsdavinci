/* 
 * File:   ns_stringutils.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 8 пїЅпїЅпїЅпїЅпїЅпїЅ 2009 пїЅ., 18:44
 */

#ifndef _DVNCI_KRNL_NS_STRINGUTILS_H
#define	_DVNCI_KRNL_NS_STRINGUTILS_H

#include <kernel/constdef.h>

namespace dvnci {


    const int NANOSECOND_TM    = 0x0;
    const int MICSECOND_TM     = 0x1;
    const int MILLISECOND_TM   = 0x2;
    const int SECOND_TM        = 0x3;
    const int MINUTE_TM        = 0x4;
    const int MINUTE10_TM      = 0x5;
    const int MINUTE30_TM      = 0x6;
    const int HOUR_TM          = 0x7;
    const int DAY_TM           = 0x8;
    const int DAY10_TM         = 0x9;
    const int MONTH_TM         = 0xA;
    const int QUART_TM         = 0xB;
    const int YAER_TM          = 0xC;

    const char hex_char_array_const[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    const char bad_hex_char = '\xFF';
    const char bad_oct_char = '\xFF';
    const char bad_bin_char = '\xFF';
    struct short_value;
    
    


    void         string_to_pascalstr(void* val, const std::string&  source, size_t len);
    std::string  pascalstr_to_string(void* dest);

    void formatmem_in_null (void* ptr, size_t len);

    std::string to_lower_copy(const std::string&  val);
    std::string to_upper_copy(const std::string&  val);
    std::string to_trim_copy(const std::string&  val);
    std::string to_fulltrim_copy(const std::string&  val);
    std::string to_freechar_copy(const std::string&  val, const std::string& del= " ");

    void  fulltrim(std::string& val);
    void  upper_and_trim(std::string& val);
    void  lower_and_trim(std::string& val);
    void  upper_and_fulltrim(std::string& val);
    void  lower_and_fulltrim(std::string& val);
    
    
    size_t regex_tokin_parser(const std::string& val, str_vect& dst, const boost::regex& re);


    bool  instrincriteria(std::string nm, std::string strcriteria);

    bool  remove_namespace_delimit(std::string& vl);
    std::string  retremoved_namespace_delimit(const std::string& vl);

    size_t  split_str(const std::string&  source, const std::string&  delimit , str_vect& vectstr);
    size_t  split_str_prefix(const std::string&  source, const std::string&  delimit , str_vect& vectstr);
    size_t  split_str_postfix(const std::string&  source, const std::string&  delimit , str_vect& vectstr);
    void    split_2str(const std::string&  source, const std::string&  delimit , std::string& val1, std::string& val2);
    void    split_3str(const std::string& source, const std::string& delimit , std::string& val1, std::string& val2, std::string& val3);
    void    split_4str(const std::string&  source, const std::string&  delimit , std::string& val1, std::string& val2, std::string& val3, std::string& val4);
    void    parse_servinfo(const std::string& source, std::string& host, std::string& port, unsigned int& timout, std::string& admin, std::string& pass);
    std::string    generate_servinfo(const std::string& host, const std::string& port, unsigned int timout, const std::string& admin, const std::string& pass);

    std::string    strcomma_to_dot(std::string val);
    std::string    strdot_to_comma(std::string val);

    std::string&   clear_first_null_digit(std::string& vl);
    std::string&   fill_first_null_digit(std::string& vl, size_t needcsize);

    std::string num8_to_hexstr(num8 vl);
    std::string num16_to_hexstr(num16 vl);
    std::string num32_to_hexstr(num32 vl);
    std::string num64_to_hexstr(num64 vl);

    template <typename T>
    inline T cycl_btlft(T vl, size_t n){
        n %=  (sizeof(T) * 8);
        return ((vl << n) | (vl >> ((sizeof(T)* 8) - n)));}

    template <typename T>
    inline T cycl_btrgt(T vl, size_t n){
        n %=  (sizeof(T) * 8);
        return ((vl >> n) | (vl << ((sizeof(T)* 8) - n)));}

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
        for (std::string::size_type it = 0 ; it < val.size(); ++it ) {
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
        for (std::string::size_type it = 0 ; it < val.size(); ++it ) {
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
        for (std::string::size_type it = 0 ; it < val.size(); ++it ) {
            tmpch = binchar_to_char(val.at(it));
            if (tmpch == bad_bin_char) return false;
            result = ((result << 1) | (tmpch & 0x1));}
        return true;}

    template <typename T>  bool bcd_to_dec(const T& src, T& vl) {
        vl = 0;
        for (size_t i = sizeof (T) * 2 ; i > 0; --i ) {
            num8 tmp8 =  (src >> ((i - 1) * 4)) & 0xF;
            if (tmp8 > 9) return false;
            else vl = vl * 10 + tmp8;}
        return true;}

    template <typename T>  bool bcd_to_dec(T& vl) {
        T tmp = 0;
        bool rslt = bcd_to_dec<T > (vl, tmp);
        vl = tmp;
        return rslt;}

    template <typename T>  bool dec_to_bcd(const T& src, T& vl) {
        vl = 1;
        size_t i = sizeof (T);
        while (i--) {
            vl *= 100;}
        if (src >= vl) return false;
        vl = 0;
        T tmp = src;
        i = 0;
        while (tmp) {
            vl |=  (( tmp % 10) << (4 * i++));
            tmp /= 10;}
        return true;}

    template <typename T>  bool dec_to_bcd(T& vl) {
        T tmp = 0;
        bool rslt = dec_to_bcd<T > (vl, tmp);
        vl = tmp;
        return rslt;}

    template <typename T> bool to_str(T val, std::string& result) {

        try {
            result = boost::lexical_cast<std::string > (val);}
        catch (boost::bad_lexical_cast) {
            return false;}
        return true;}

    bool to_str(datetime val, std::string& result);

    template <typename T> std::string to_str(T val) {

        std::string result = "";
        try {
            result = boost::lexical_cast<std::string > (val);}
        catch (boost::bad_lexical_cast) {
            return "";}
        return result;}
    
    template<typename T> std::string to_str_frmt(const T& vl, const std::string& frmt = ""){
        if (frmt.empty()) return to_str<T>(vl);
        try{
            boost::format f(frmt.c_str());
            f % vl;
            return f.str();}
        catch(...){}
     return to_str<T>(vl);}

     std::string to_str(datetime val);

    template <typename T> bool str_to(const std::string& val, T& result) {

        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return false;}
        return true;}

    bool str_to(const std::string& val, datetime& result);

    template <typename T> T str_to(const std::string& val, const T& def = 0) {

        try {
            return boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            return def;}}

    datetime str_to(const std::string& val, const datetime& def = nill_time);


    template <typename T> void str_to(const std::string& val, const T& def, T& result) {

        result = def;
        try {
            result = boost::lexical_cast<T > (val);}
        catch (boost::bad_lexical_cast) {
            result = def;}}

     void str_to(const std::string& val, const datetime& def, datetime& result);

    template <typename T> T abs(T v) {
        return v >= 0 ? v : -v;}

    template <typename T> void in_bound(const T& min, const T& max, T& val) {
        val = max < val  ? max : min > val ? min : val;}

    template <typename T> T in_bounded(const T& min, const T& max, T val) {
        val = max < val  ? max : min > val ? min : val;
        return val;}

    /*template<typename T> T from_num64_cast(num64 val) {
        return *reinterpret_cast<T*> (&val);}

    template<typename T> num64 to_num64_cast(T val) {
       
        switch (sizeof (T)) {
            case 8: return (*reinterpret_cast<num64*> (&val));
            case 4: return ((*reinterpret_cast<num64*> (&val)) & 0xFFFFFFFF);
            case 2: return ((*reinterpret_cast<num64*> (&val)) & 0xFFFF);
            case 1: return ((*reinterpret_cast<num64*> (&val)) & 0xFF);}
        return (*reinterpret_cast<num64*> (&val));}*/
    
    template<typename T> T from_num64_cast(num64 val) {
        return *((T*)&val);}

    template<typename T> num64 to_num64_cast(T val) {
       
        switch (sizeof (T)) {
            case 8: return (*((num64*)&val));
            case 4: return ((*((num64*)&val)) & 0xFFFFFFFF);
            case 2: return ((*((num64*)&val)) & 0xFFFF);
            case 1: return ((*((num64*)&val)) & 0xFF);}
        return *((num64*)&val);}
    
    


    template<typename T> T num64_and_type_cast(num64 value, tagtype type) {

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
            case TYPE_TM:{
                return 0;}}
        return static_cast<T> (from_num64_cast<double>(value));}
    

    template<typename T> num64 to_num64_value_and_type_cast(T value, tagtype type) {

        switch (type) {
            case TYPE_DISCRET:{
                return to_num64_cast<bool>(static_cast<bool> (value));}
            case TYPE_NUM64:{
                return to_num64_cast<num64 > (static_cast<num64> (value));}
            case TYPE_UNUM64:{
                return to_num64_cast<unum64 > (static_cast<unum64> (value));}
            case TYPE_NUM32:{
                return to_num64_cast<num32 > (static_cast<num32> (value));}
            case TYPE_UNUM32:{
                return to_num64_cast<unum32 > (static_cast<unum32> (value));}
            case TYPE_NUM16:{
                return to_num64_cast<num16 > (static_cast<num16> (value));}
            case TYPE_UNUM16:{
                return to_num64_cast<unum16 > (static_cast<unum16> (value));}
            case TYPE_NUM8:{
                return to_num64_cast<num8 > (static_cast<num8> (value));}
            case TYPE_UNUM8:{
                return to_num64_cast<unum8 > (static_cast<unum8> (value));}
            case TYPE_DOUBLE:{
                return to_num64_cast<double>(static_cast<double> (value));};
            case TYPE_FLOAT:{
                return to_num64_cast<float>(static_cast<float> (value));}
            case TYPE_TM:{
                return  0;}}
        return to_num64_cast<double>(static_cast<double> (value));}

    template<typename T> double differ_in_percent(num64 min, num64 max, num64 last, num64 present) {

        T tmp_min = from_num64_cast<T > (min);
        T tmp_max = from_num64_cast<T > (max);
        T tmp_last = from_num64_cast<T > (last);
        T tmp_present = from_num64_cast<T > (present);
        if (tmp_min == tmp_max) return 101.0;
        return (std::abs((tmp_last - tmp_present)*100.0 / (tmp_max - tmp_min)));}

    num64 num64_from_string_and_type(const std::string& val, tagtype type, num64 def  = 0);
    bool  num64_from_string_and_type_err(const std::string& val, tagtype type, num64& rslt);

    std::string string_fromnum64_and_type(const num64& val, tagtype type);
    std::string string_fromnum64_and_type_format(const num64& val, tagtype type, const std::string& format = "");
    std::string string_fromnum64_and_type_format(const num64& val, tagtype type, onum ladsk);

    num64 num64_from_type_min(tagtype type);
    num64 num64_from_type_max(tagtype type);
    num64 num64_from_type_null(tagtype type);

    bool   bynum64_and_type_outbound(num64 min, num64 max, num64 last, num64 present, tagtype type, double percent);

    template<typename T>
    num64   line_convertion(num64 val,  tagtype tp, T minx, T maxx, T miny, T maxy) {
        if ((minx == maxx) || (miny == maxy)) return val;
        T vl = num64_and_type_cast<T > (val, tp);
        if (vl <= minx) return to_num64_cast<T > (miny);
        if (vl >= maxx) return to_num64_cast<T > (maxy);
        return to_num64_cast<T > ((miny + (maxy - miny) / (maxx - minx) * (vl - minx)));}

    num64   line_lanscape_convertion(num64 val,  tagtype tp, double minraw, double maxraw, double mineu, double maxeu);
    num64   line_lanscape_convertion_serv(num64 val,  double minraw, double maxraw, double mineu, double maxeu);



    //////////////////////////////////////////////////////////////////////////////////////

    datetime now();
    num64 nownum64();
    boost::xtime utc_now();

    boost::xtime utc_now_plus_millsec(num32 tmout);
    boost::xtime utc_now_plus_sec(num32 tmout);

    bool expire_from_utc_millsec(const boost::xtime& vl, num32 tmout);
    bool expire_from_utc_sec(const boost::xtime& vl, num32 tmout);

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
    num64 datetime_to_epoch_minute(const datetime& val);
    num64 datetime_to_epoch_hour(const datetime& val);
    num64 datetime_to_epoch_day(const datetime& val);
    std::string datetime_to_string(datetime val, bool withmsec = false);
    std::string datetime_to_string(num64 val, bool withmsec = false);

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

    bool incperiod(datetime& val, int type, num64 n = 1);
    bool normalizeperiod(datetime& val_, int type);

    bool beforetabletime(datetime& tm, reporttype tp);
    bool normalizereporttime(datetime& val, reporttype tp);
    bool increporttime(datetime& val, reporttype tp, num64 n = 1);


    struct statistic_functor{

        statistic_functor(repstattype tp) : type(tp),cnt(0), value(NULL_DOUBLE) {}
        ~statistic_functor(){}

        void operator()(const dt_val_pair& vl);
        double countedvalue();

    private:
      repstattype type;
      size_t      cnt;
      double      value;};


    struct integr_statistic_functor{

        integr_statistic_functor(const dt_val_pair& initvl) : lstpoint(initvl),cnt(0), value(NULL_DOUBLE) {}
        ~integr_statistic_functor(){}

        void operator()(const dt_val_pair& vl);
        double countedvalue();

    private:
      dt_val_pair   lstpoint;
      size_t        cnt;
      double        value;};

}

#endif	/* _NS_STRINGUTILS_H */

