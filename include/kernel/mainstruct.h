/* 
 * File:   mainstruct.h
 * Author: Serg
 *
 * Created on 1 Р РЋР ВµР Р…РЎвЂљРЎРЏР В±РЎР‚РЎРЉ 2010 Р С–., 20:14
 */

#ifndef _DVNCI_KRNLMAINSTRUCT_H
#define	_DVNCI_KRNLMAINSTRUCT_H

#include <kernel/constdef.h>
#include <kernel/short_value.h>
#include <kernel/utils.h>
#include <kernel/error.h>

namespace dvnci {


#pragma  pack(push,4)

    // tagstruct 

    typedef struct tagstruct {
    public:
        
        static const num64 ALLWAYSACTIVE = 0x1;
        static const num64 RANGABLE      = 0x2;

        tagstruct(indx mid = nill_ptr, indx group = npos);

        ~tagstruct() {
            id(nill_ptr);}

        void id(indx val) {
            id_ = static_cast<unum64> (val);}

        indx id() const {
            return static_cast<indx> (id_);}
        

        template <typename T>
                void value(T val) {
            value_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));}

        template <typename T >
                T value() const {
            return num64_and_type_cast<T > (value_, static_cast<tagtype> (type_));}

        num64 value64() const {
            return value_;}

        void value64(num64 vl) {
            value_ = vl;}

        std::string value_str() const {
            return num64_and_type_cast<std::string>(value_, static_cast<tagtype> (type_));}

        std::string value_frmt() const {
            return num64_and_type_cast(value_, static_cast<tagtype> (type_), landscape_range());}

        void value(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                value_ = tmp;}}
        
        

        template <typename T>
                void value_log(T val) {
            value_log_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));}

        template <typename T >
                T value_log() const {
            return num64_and_type_cast<T > (value_log_, static_cast<tagtype> (type_));}

        num64 value_log64() const {
            return value_log_;}

        void value_log64(num64 vl) {
            value_log_ = vl;}

        std::string value_log_str() const {
            return num64_and_type_cast<std::string>(value_log_, static_cast<tagtype> (type_));}

        std::string value_log_frmt() const {
            return num64_and_type_cast(value_log_, static_cast<tagtype> (type_), landscape_range());}

        void value_log(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                value_log_ = tmp;}}
        
        

        template <typename T>
        void value_before(T val) {
            value_before_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));}

        template <typename T >
        T value_before() const {
            return num64_and_type_cast<T > (value_before_, static_cast<tagtype> (type_));}

        num64 value_before64() const {
            return value_before_;}

        void value_before64(num64 vl) {
            value_before_ = vl;}

        std::string value_before_str() const {
            return num64_and_type_cast<std::string>(value_before_, static_cast<tagtype> (type_));}

        std::string value_before_frmt() const {
            return num64_and_type_cast(value_before_, static_cast<tagtype> (type_), landscape_range());}

        void value_before(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                value_before_ = tmp;}}
        
        
        

        void time(datetime val) {
            time_ = castnum64_from_datetime(val);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        void time_n64(num64 val) {
            time_ = val;}

        num64 time_n64() const {
            return time_;}

        std::string time_str() const {
            return datetime_to_string(time_);}
        
        
        

        void time_log(datetime val) {
            time_log_ = castnum64_from_datetime(val);}

        datetime time_log() const {
            return cast_datetime_fromnum64(time_log_);}

        void time_log_n64(num64 val) {
            time_log_ = val;}

        num64 time_log_n64() const {
            return time_log_;}

        std::string time_log_str() const {
            return datetime_to_string(time_log_);}
        
        

        void error(ns_error val) {
            error_ = static_cast<num32> (val);}

        ns_error error() const {
            return static_cast<ns_error> (error_);}
        
        

        void type(tagtype val) {
            type_ = static_cast<num64> (0x1FF & val);
            helper_util();}

        tagtype type() const {
            return static_cast<tagtype> (0x1FF & type_);}
        
        
        

        void valid(vlvtype val) {
            valid_ = static_cast<num32> (in_bounded<vlvtype > (0, 100, val));}

        vlvtype valid() const {
            return static_cast<vlvtype> (valid_);}
        
        
        

        void refcnt(onum val) {
            refcnt_ = static_cast<num32> (val);}

        void increfcnt() {
            refcnt_++;}

        void decrefcnt() {
            if (refcnt_) refcnt_--;}

        onum refcnt() const {
            return (allwaysactiv_helper()) ?
                    1 + static_cast<onum> (refcnt_) : static_cast<onum> (refcnt_);}
        
        

        void group(indx val) {
            group_ = static_cast<unum64> (val + 1);}

        indx group() const {
            return static_cast<indx> (group_) - 1;}
        
        

        void agroup(indx val) {
            agroup_ = static_cast<unum64> (val + 1);}

        indx agroup() const {
            return static_cast<indx> (agroup_) - 1;}
        
        
        

        void logkey(indx val) {
            logkey_ = static_cast<unum64> (val + 1);}

        indx logkey() const {
            return static_cast<indx> (logkey_) - 1;}
        
        
        

        void alarmlevel(altype val) {
            alarmlevel_ = static_cast<num32> (val & 0x3);
            helper_util();}

        altype alarmlevel() const {
            return IN_ALARMEDSET(type()) ?
                    static_cast<altype> (alarmlevel_ & 0x3) : 0;}
        
        

        void alarmcase(alcstype val) {
            if ((alarmcase_ = static_cast<num32> (val & 3)) > 2)
                alarmcase_ = 0;}

        alcstype alarmcase() const {
            return ((alarmcase_ >= 0) && (alarmcase_ < 3))
                    ? static_cast<alcstype> (alarmcase_) : 0;}
        
        

        void logged(bool val) {
            logged_ = static_cast<num32> (val);
            helper_util();}

        bool logged() const {
            return IN_NUMBERSET(type()) ?
                    static_cast<bool> (logged_) : false;}
        
        

        void onmsged(bool val) {
            onmsged_ = static_cast<num32> (val);
            helper_util();}

        bool onmsged() const {
            return IN_NUMBERSET(type()) ?
                    static_cast<bool> (onmsged_) : false;}
        
        

        void offmsged(bool val) {
            offmsged_ = static_cast<num32> (val);
            helper_util();}

        bool offmsged() const {
            return IN_NUMBERSET(type()) ?
                    static_cast<bool> (offmsged_) : false;}
        
        

        void alarmon(bool val) {
            if (IN_ALARMEDSET(type()))
                alarmon_ = static_cast<num32> (val);}

        bool alarmon() const {
            return IN_ALARMEDSET(type()) ?
                    static_cast<bool> (alarmon_) : false;}
        
        

        void alarmkvit(bool val) {
            if (IN_ALARMEDSET(type()))
                alarmkvit_ = static_cast<num32> (val);}

        bool alarmkvit() const {
            return IN_ALARMEDSET(type()) ?
                    static_cast<bool> (alarmkvit_) : false;}
        
        

        acclevtype accesslevel() const {
            return static_cast<acclevtype> (accesslevel_ & 0x3FF);}

        void accesslevel(acclevtype val) {
            accesslevel_ = static_cast<num32> (val & 0x3FF);}
        
        

        void alwactive(bool val) {
            alwactive_ = val;
            helper_util();}

        bool alwactive() const {
            return alwactive_;}
        
        

        void rwtype(acstgtype val) {
            if ((rwtype_ = static_cast<num32> (val & 3)) > 2)
                rwtype_ = 0;}

        acstgtype rwtype() const {
            return IN_COMMADSET(type()) ?
                    static_cast<acstgtype> (rwtype_ & 3) : rwReadOnly;}
        
        

        bool rangable() const {
            return rangeble_helper();}
        
        

        void reporthistory(reporthisttype val) {
            reporthisttype tmp = static_cast<reporthisttype> (val);
            normilize_history_bound(type(), tmp);
            reporthistory_ = static_cast<num32> (tmp);}

        reporthisttype reporthistory() const {
            if (IN_REPORTSET(type())) {
                reporthisttype tmp = static_cast<reporthisttype> (reporthistory_);
                normilize_history_bound(type(), tmp);
                return tmp;}
            return 0;}
        
        

        void reportsubdelt(reporthistdelt val) {
            reporthistdelt tmp = static_cast<reporthistdelt> (val);
            normilize_report_subperiod(type(), tmp);
            reportsubdelt_ = static_cast<num32> (tmp);}

        reporthistdelt reportsubdelt() const {
            if (IN_REPORTSET(type())) {
                reporthistdelt tmp = static_cast<reporthistdelt> (reportsubdelt_);
                normilize_report_subperiod(type(), tmp);
                return tmp;}
            return 0;}


        void reportstatistic(repstattype val);

        repstattype reportstatistic() const;
        
        

        void namepos(size_t val) {
            posname_ = static_cast<unum64> (val);}

        size_t namepos() const {
            return static_cast<size_t> (posname_);}

        void poscomment(size_t val) {
            poscomment_ = static_cast<unum64> (val);}

        size_t poscomment() const {
            return static_cast<size_t> (poscomment_);}

        void posbinding(size_t val) {
            posbinding_ = static_cast<unum64> (val);}

        size_t posbinding() const {
            return static_cast<size_t> (posbinding_);}

        void poseu(size_t val) {
            poseu_ = static_cast<unum64> (val);}

        size_t poseu() const {
            return static_cast<size_t> (poseu_);}

        void posonmsg(size_t val) {
            posonmsg_ = static_cast<unum64> (val);}

        size_t posonmsg() const {
            return static_cast<size_t> (posonmsg_);}

        void posoffmsg(size_t val) {
            posoffmsg_ = static_cast<unum64> (val);}

        size_t posoffmsg() const {
            return static_cast<size_t> (posoffmsg_);}

        void posalarmmsg(size_t val) {
            posalarmmsg_ = static_cast<unum64> (val);}

        size_t posalarmmsg() const {
            return static_cast<size_t> (posalarmmsg_);}
        
        
        

        template <typename T>
        void minraw(T val) {
            minraw_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));
            helper_util();}

        template <typename T >
        T minraw() const {
            return num64_and_type_cast<T > (minraw_, static_cast<tagtype> (type_));}

        num64 minraw64() const {
            return minraw_;}

        std::string minraw_str() const {
            return (IN_NUMBERSET(static_cast<tagtype> (type_))) ? 
                num64_and_type_cast<std::string>(minraw_, static_cast<tagtype> (type_)) : "";}

        void minraw(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                minraw_ = num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp) ?
                        tmp : num64_for_type_min(static_cast<tagtype> (type_));}
            helper_util();}
        
        

        template <typename T>
        void maxraw(T val) {
            maxraw_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));
            helper_util();}

        template <typename T >
        T maxraw() const {
            return num64_and_type_cast<T > (maxraw_, static_cast<tagtype> (type_));}

        num64 maxraw64() const {
            return maxraw_;}

        std::string maxraw_str() const {
            return (IN_NUMBERSET(static_cast<tagtype> (type_))) ? 
                num64_and_type_cast<std::string>(maxraw_, static_cast<tagtype> (type_)) : "";}

        void maxraw(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                maxraw_ = num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp) ? 
                    tmp : num64_for_type_max(static_cast<tagtype> (type_));}
            helper_util();}

        
        
        template <typename T>
        void mineu(T val) {
            mineu_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));
            helper_util();}

        template <typename T >
        T mineu() const {
            return num64_and_type_cast<T > (mineu_, static_cast<tagtype> (type_));}

        num64 mineu64() const {
            return mineu_;}

        std::string mineu_str() const {
            return (IN_NUMBERSET(static_cast<tagtype> (type_))) ? 
                num64_and_type_cast<std::string>(mineu_, static_cast<tagtype> (type_)) : "";}

        void mineu(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                mineu_ = num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp) ? 
                    tmp : num64_for_type_min(static_cast<tagtype> (type_));}
            helper_util();}

        
        
        template <typename T>
        void maxeu(T val) {
            maxeu_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));
            helper_util();}

        template <typename T >
         T maxeu() const {
            return num64_and_type_cast<T > (maxeu_, static_cast<tagtype> (type_));}

        num64 maxeu64() const {
            return maxeu_;}

        std::string maxeu_str() const {
            return (IN_NUMBERSET(static_cast<tagtype> (type_))) ?
                num64_and_type_cast<std::string>(maxeu_, static_cast<tagtype> (type_)) : "";}

        void maxeu(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                maxeu_ = num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp) ?
                    tmp : num64_for_type_max(static_cast<tagtype> (type_));}
            helper_util();}

        
        



        
        
        
        template <typename T>
        void alarmconst(T val) {
            alarmconst_ = num64_from_vt_cast<T > (val, static_cast<tagtype> (type_));}

        template <typename T >
                T alarmconst() const {
            return type_==TYPE_DISCRET ? 
                !from_num64_cast<bool>(alarmconst_) : 
                num64_and_type_cast<T > (alarmconst_, static_cast<tagtype> (type_));}

        num64 alarmconst64() const {
            return alarmconst_;}

        std::string alarmconst_str() const {
            return (IN_NUMBERSET(static_cast<tagtype> (type_))) ? num64_and_type_cast<std::string>(alarmconst_, static_cast<tagtype> (type_)) : "";}

        void alarmconstr(const std::string & val) {
            num64 tmp = 0;
            if (num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp)) {
                alarmconst_ = num64_from_vt_cast(val, static_cast<tagtype> (type_), tmp) ? tmp : num64_for_type_null(static_cast<tagtype> (type_));}}

        
        
        void devdb(double val) {
            if (val<0) val=0;
            if (val>100) val=100;
            devdb_ =  num64_cast<double>(val);}

        double devdb() const {
            return in_bounded<double>(0.0, 100.0, from_num64_cast<double>(devdb_));}


        
        
        
        void logdb(double val) {
            if (val<0) val=0;
            if (val>100) val=100;
            logdb_ = num64_cast<double>(val);}

        double logdb() const {
            return in_bounded<double>(0.0, 100.0, from_num64_cast<double>(logdb_));}
        
        
        
        
        void incmonitor() {
            monitor_++;}

        onum monitor() const {
            return static_cast<onum> (monitor_);}


        static void clone(tagstruct& dst, const tagstruct & src);

        tagstruct get_for_write_to_file(bool firstcriteria = false);
        
        bool allwaysactiv_helper() const {
            return static_cast<bool> (util_helper_ & ALLWAYSACTIVE);}
        
        bool rangeble_helper() const {
            return static_cast<bool> (util_helper_ & RANGABLE);}


    private:

        onum landscape_range() const;


        void helper_util();


        unum64 id_;
        num64 value_;
        num64 time_;
        num64 type_;
        num32 valid_;
        num32 error_;
        unum64 posname_;
        num64 value_log_;
        num64 value_before_;
        num64 time_log_;
        num64 unusetime_;
        num64 minraw_, maxraw_, mineu_, maxeu_;
        num64 logdb_;
        num64 devdb_;
        num64 alarmconst_;
        num64 util_helper_;
        unum64 logkey_;
        unum64 group_;
        unum64 agroup_;
        num64 alwactive_;
        num64  monitor_;
        unum64 poscomment_;
        unum64 posbinding_;
        unum64 poseu_;
        unum64 posonmsg_;
        unum64 posoffmsg_;
        unum64 posalarmmsg_;
        unum64 unusepos1_;
        unum64 unusepos2_;
        num32 refcnt_;
        num32 alarmlevel_;
        num32 alarmcase_;
        num32 logged_;
        num32 onmsged_;
        num32 offmsged_;
        num32 reporthistory_;
        num32 reportsubdelt_;
        num32 reportstatistic_;
        num32 alarmon_;
        num32 alarmkvit_;
        num32 alarmonserv_;
        num32 accesslevel_;
        num32 rwtype_;
        num32 nouse1_;
        num64 nouse2_;} *ptagstruct;





    // tagsstruct_hdr     

    typedef struct tagsstruct_hdr {
        explicit tagsstruct_hdr(lcltype loc = NS_CODPAGE_UTF8);

        tagsstruct_hdr(const tagsstruct_hdr & src);

        tagsstruct_hdr & operator=(const tagsstruct_hdr & src);

        tagsstruct_hdr & operator++();

        tagsstruct_hdr & operator++(int);

        onum incmonitor() {
            monitor_++;
            return static_cast<onum> (monitor_);}

        num64 version() const {
            return version_;}

        size_t headersize() const {
            return static_cast<size_t> (headersize_);}

        size_t recordsize() const {
            return static_cast<size_t> (recordsize_);}

        size_t count() const {
            return static_cast<size_t> (count_);}

        void count(size_t val);

        size_t datasize() const {
            return static_cast<size_t> (sizeof (tagsstruct_hdr) + count_ * (sizeof (tagstruct)));}

        lcltype local() const {
            return static_cast<lcltype> (local_ & 3);}

        void local(lcltype val) {
            local_ = static_cast<num64> (val & 3);}

        debuglvtype debuglevel() const {
            return static_cast<debuglvtype> (debuglevel_ & 3);}

        void debuglevel(debuglvtype val) {
            debuglevel_ = static_cast<num64> (val & 3);}

        void posname(size_t val) {
            posname_ = static_cast<unum64> (val);}

        size_t posname() const {
            return static_cast<size_t> (posname_);}

        void poscomment(size_t val) {
            poscomment_ = static_cast<unum64> (val);}

        size_t poscomment() const {
            return static_cast<size_t> (poscomment_);}

        void posdbstring(size_t val) {
            posdbstring_ = static_cast<unum64> (val);}

        size_t posdbstring() const {
            return static_cast<size_t> (posdbstring_);}

        void posadmin(size_t val) {
            posadmin_ = static_cast<unum64> (val);}

        size_t posadmin() const {
            return static_cast<size_t> (posadmin_);}

        void pospass(size_t val) {
            pospass_ = static_cast<unum64> (val);}

        size_t pospass() const {
            return static_cast<size_t> (pospass_);}

        void posadminport(size_t val) {
            posadminport_ = static_cast<unum64> (val);}

        size_t posadminport() const {
            return static_cast<size_t> (posadminport_);}

        void posremoteport(size_t val) {
            posremoteport_ = static_cast<unum64> (val);}

        size_t posremoteport() const {
            return static_cast<size_t> (posremoteport_);}

        void posopcport(size_t val) {
            posopcport_ = static_cast<unum64> (val);}

        size_t posopcport() const {
            return static_cast<size_t> (posopcport_);}

        opsystemtype os_type() const {
            return static_cast<opsystemtype> (os_type_);}

        void os_type(opsystemtype val) {
            os_type_ = static_cast<num64> (val);}

        size_t texttagcnt() const {
            return static_cast<size_t> (texttagcnt_);}

        void texttagcnt(size_t val) {
            texttagcnt_ = static_cast<num64> (val);}

        size_t archtagcnt() const {
            return static_cast<size_t> (archtagcnt_);}

        void archtagcnt(size_t val) {
            archtagcnt_ = static_cast<num64> (val);}

        size_t reporttagcnt() const {
            return static_cast<size_t> (reporttagcnt_);}

        void reporttagcnt(size_t val) {
            reporttagcnt_ = static_cast<num64> (val);}

        dbprovtype dbprovider() const {
            return static_cast<dbprovtype> (dbprovider_);}

        void dbprovider(dbprovtype val) {
            dbprovider_ = static_cast<num64> (val);}

        bool analogbuf() const {
            return !static_cast<bool> (analogbuf_);}

        void analogbuf(bool val) {
            analogbuf_ = static_cast<num64> (!val);}

        num32 bddepth() const {
            return (bddepth_ >= 0) ? static_cast<num32> (bddepth_) : 0;}

        void bddepth(num32 val) {
            bddepth_ = static_cast<num64> (val);}

        void monitor(onum val) {
            monitor_ = static_cast<num64> (val);}

        onum monitor() const {
            return static_cast<onum> (monitor_);}

    private:

        num64 version_;
        num64 headersize_;
        num64 recordsize_;
        num64 count_;
        num64 datasize_;
        num64 os_type_;
        num64 local_;
        num64 monitor_;
        num64 debuglevel_;
        unum64 posname_;
        unum64 poscomment_;
        num64 dbprovider_;
        unum64 posdbstring_;
        num64 analogbuf_;
        num64 bddepth_;
        unum64 posadmin_;
        unum64 pospass_;
        unum64 posadminport_;
        unum64 posremoteport_;
        unum64 posopcport_;
        num64 texttagcnt_;
        num64 archtagcnt_;
        num64 reporttagcnt_;
        num64 n_use1;
        num64 n_use2;
        num64 n_use3;} *ptagsstruct_hdr;

    typedef struct tagsstruct {
        typedef tagsstruct_hdr head_type;
        typedef tagstruct item_type;

        tagsstruct_hdr header;
        tagstruct items[];} *ptagsstruct;



    ///smplheader     

    typedef struct smplheader {

        smplheader() : count_(0) {}

        ~smplheader() {
            count_ = 0;}

        size_t count() const {
            return static_cast<size_t> (count_);}

        void count(size_t val) {
            count_ = static_cast<num64> (val);}

    private:
        num64 count_;} *psmplheader;




    //groupstruct    

    typedef struct groupstruct {
        groupstruct(indx mid = nill_ptr);

        ~groupstruct() {
            id(nill_ptr);}


        void id(indx val) {
            id_ = static_cast<unum64> (val);}

        indx id() const {
            return static_cast<indx> (id_);}

        void active(bool val) {
            active_ = static_cast<num64> (val);}

        bool active() const {
            return static_cast<bool> (active_);}

        void error(ns_error val) {
            error_ = static_cast<num32> (val);}

        ns_error error() const {
            return static_cast<ns_error> (error_);}

        vlvtype valid() const {
            return static_cast<vlvtype> (valid_);}

        void valid(vlvtype val) {
            valid_ = static_cast<num32> (in_bounded<vlvtype > (0, 100, val));}

        void time(datetime val) {
            time_ = castnum64_from_datetime(val);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        void time_n64(num64 val) {
            time_ = val;}

        num64 time_n64() const {
            return time_;}

        std::string time_str() const {
            return datetime_to_string(time_);}

        void namepos(size_t val) {
            namepos_ = static_cast<unum64> (val);}

        size_t namepos() const {
            return static_cast<size_t> (namepos_);}

        void hostpos(size_t val) {
            hostpos_ = static_cast<unum64> (val);}

        size_t hostpos() const {
            return static_cast<size_t> (hostpos_);}

        void serverpos(size_t val) {
            serverpos_ = static_cast<unum64> (val);}

        size_t serverpos() const {
            return static_cast<size_t> (serverpos_);}

        void userpos(size_t val) {
            userpos_ = static_cast<unum64> (val);}

        size_t userpos() const {
            return static_cast<size_t> (userpos_);}

        void passpos(size_t val) {
            passpos_ = static_cast<unum64> (val);}

        size_t passpos() const {
            return static_cast<size_t> (passpos_);}

        void grouppos(size_t val) {
            grouppos_ = static_cast<unum64> (val);}

        size_t grouppos() const {
            return static_cast<size_t> (grouppos_);}

        void portpos(size_t val) {
            portpos_ = static_cast<unum64> (val);}

        size_t portpos() const {
            return static_cast<size_t> (portpos_);}

        void etherpos(size_t val) {
            etherpos_ = static_cast<unum64> (val);}

        size_t etherpos() const {
            return static_cast<size_t> (etherpos_);}

        void topicpos(size_t val) {
            topicpos_ = static_cast<unum64> (val);}

        size_t topicpos() const {
            return static_cast<size_t> (topicpos_);}

        void strpos1(size_t val) {
            strpos1_ = static_cast<unum64> (val);}

        size_t strpos1() const {
            return static_cast<size_t> (strpos1_);}

        void strpos2(size_t val) {
            strpos2_ = static_cast<unum64> (val);}

        size_t strpos2() const {
            return static_cast<size_t> (strpos2_);}

        void strpos3(size_t val) {
            strpos3_ = static_cast<unum64> (val);}

        size_t strpos3() const {
            return static_cast<size_t> (strpos3_);}

        void strpos4(size_t val) {
            strpos4_ = static_cast<unum64> (val);}

        size_t strpos4() const {
            return static_cast<size_t> (strpos4_);}

        void strpos5(size_t val) {
            strpos5_ = static_cast<unum64> (val);}

        size_t strpos5() const {
            return static_cast<size_t> (strpos5_);}

        void strpos6(size_t val) {
            strpos6_ = static_cast<unum64> (val);}

        size_t strpos6() const {
            return static_cast<size_t> (strpos6_);}

        void appid(appidtype val) {
            appid_ = static_cast<num64> (val);}

        appidtype appid() const {
            return static_cast<appidtype> (appid_);}

        void chanaltype(chnltype val) {
            chanaltype_ = static_cast<num64> (in_bounded<chnltype > (0, 4, val));}

        chnltype chanaltype() const {
            return in_bounded<chnltype > (0, 4, static_cast<chnltype> (chanaltype_));}

        void chanalnum(chnlnumtype val) {
            chanalnum_ = static_cast<num64> (val);}

        chnlnumtype chanalnum() const {
            return static_cast<chnlnumtype> (chanalnum_);}

        void devnum(devnumtype val) {
            devnum_ = static_cast<num64> (val);}

        devnumtype devnum() const {
            return static_cast<devnumtype> (devnum_);}

        void devspec(devspectype val) {
            devspec_ = static_cast<num64> (val);}

        devspectype devspec() const {
            return static_cast<devspectype> (devspec_);}

        void protocol(protocoltype val) {
            protocol_ = static_cast<num64> (val);}

        protocoltype protocol() const {
            return static_cast<protocoltype> (protocol_);}

        timeouttype timeout() const {
            return in_bounded<timeouttype > (0, 100000, static_cast<timeouttype> (timeout_));}

        void timeout(timeouttype val) {
            timeout_ = static_cast<num64> (in_bounded<timeouttype > (10, 1000000, val));}

        double deadbound() const {
            return in_bounded<double>(0, 100, from_num64_cast<double>(deadbound_));}

        void deadbound(double val) {
            deadbound_ = num64_cast<double>(in_bounded<double>(0, 100, val));}

        gratetype grouprate() const {
            return in_bounded<gratetype > (0, 1000000, static_cast<gratetype> (grouprate_));}

        void grouprate(gratetype val) {
            grouprate_ = static_cast<num64> (in_bounded<gratetype > (0, 1000000, val));}

        blksizetype blocksize() const {
            return in_bounded<blksizetype > (0, 1000000, static_cast<blksizetype> (blocksize_));}

        void blocksize(blksizetype val) {
            blocksize_ = static_cast<num64> (in_bounded<blksizetype > (0, 1000000, val));}

        blksizetype archblocksize() const {
            return in_bounded<blksizetype > (0, 1000000, static_cast<blksizetype> (archblocksize_));}

        void archblocksize(blksizetype val) {
            archblocksize_ = static_cast<num64> (in_bounded<blksizetype > (0, 1000000, val));}

        size_t trycount() const {
            return in_bounded<num32 > (1, 100, static_cast<size_t> (trycount_));}

        void trycount(size_t val) {
            trycount_ = static_cast<num64> (in_bounded<size_t > (1, 100, val));}

        bool utiloperation() const {
            return static_cast<bool> (utiloperation_);}

        void utiloperation(bool val) {
            utiloperation_ = static_cast<num64> (val);}

        timeouttype indicateto() const {
            return in_bounded<timeouttype > (0, 1000000, static_cast<timeouttype> (indicateto_));}

        void indicateto(timeouttype val) {
            indicateto_ = static_cast<num64> (in_bounded<timeouttype > (0, 1000000, val));}

        lcltype local() const {
            return static_cast<lcltype> (local_ & 3);}

        void local(lcltype val) {
            local_ = static_cast<num64> (val & 3);}

        void synctype(subcripttype val) {
            synctype_ = static_cast<num64> (in_bounded<subcripttype > (0, 2, val));}

        subcripttype synctype() const {
            return in_bounded<subcripttype> (0, 2, static_cast<subcripttype> (synctype_));}

        void ver(intfvertype val) {
            ver_ = static_cast<num64> (val & 3);}

        intfvertype ver() const {
            return static_cast<intfvertype> (ver_ & 3);}

        void supporttype(bool val) {
            supporttype_ = static_cast<num64> (val);}

        bool supporttype() const {
            return static_cast<bool> (supporttype_);}

        void usehda(bool val) {
            supporttype_ = static_cast<num64> (val);}

        bool usehda() const {
            return static_cast<bool> (supporttype_);}

        void* config() {
            return config_;}

        const void* config() const {
            return config_;}

        void incmonitor() {
            monitor_++;}

        onum monitor() const {
            return static_cast<onum> (monitor_);}


        groupstruct get_for_write_to_file(bool firstcriteria = false);

        static void clone(groupstruct& dst, const groupstruct & src);

    private:
        unum64 id_;
        num64  active_;
        num64  time_;
        num64  unusetype_;
        num32  valid_;
        num32  error_;
        unum64 namepos_;
        num64  appid_;
        unum64 hostpos_;
        unum64 serverpos_;
        unum64 userpos_;
        unum64 passpos_;
        unum64 grouppos_;
        unum64 portpos_;
        unum64 etherpos_;
        unum64 topicpos_;
        unum64 strpos1_;
        unum64 strpos2_;
        unum64 strpos3_;
        unum64 strpos4_;
        unum64 strpos5_;
        unum64 strpos6_;
        num64 chanaltype_;
        num64 chanalnum_;
        num64 devspec_;
        num64 devnum_;
        num64 protocol_;
        num64 unuse6_;
        num64 timeout_;
        num64 deadbound_;
        num64 grouprate_;
        num64 utiloperation_;
        num64 blocksize_;
        num64 archblocksize_;
        num64 trycount_;
        num64 indicateto_;
        num64 tcpport_;
        num64 local_;
        num64 synctype_;
        num64 ver_;
        num64 supporttype_;
        num64 monitor_;
        num64 unuse1_;
        num64 unuse2_;
        num64 unuse3_;
        num64 unuse4_;
        num64 unuse5_;
        char config_[GROP_CONFIG_SIZE];} *pgroupstruct;


    bool baudratevalid(baudratetype vl);




    // rs232_property

    typedef struct rs232_property { // dcb

        void baudrate(baudratetype val) {
            baudrate_ = baudratevalid(val) ? static_cast<num64> (val) : static_cast<num64> (NT_RS_DOUNDRATE_9600);}

        baudratetype baudrate() const {
            return baudratevalid(static_cast<baudratetype> (baudrate_)) ? static_cast<baudratetype> (baudrate_) : NT_RS_DOUNDRATE_9600;}

        num32 databit() const {
            return in_bounded<num32 > (5, 8, static_cast<num32> (databit_));}

        void databit(num32 val) {
            databit_ = static_cast<num64> (in_bounded<num32 > (5, 8, val));}

        rsstopbittype stopbit() const {
            return in_bounded<rsstopbittype > (0, 2, static_cast<rsstopbittype> (stopbit_));}

        void stopbit(rsstopbittype val) {
            stopbit_ = static_cast<num64> (in_bounded<rsstopbittype > (0, 2, val));}

        rsparitytype parity() const {
            return in_bounded<rsparitytype > (0, 4, static_cast<rsparitytype> (parity_));}

        void parity(rsparitytype val) {
            parity_ = static_cast<num64> (in_bounded<rsparitytype > (0, 4, val));}

        bool flowcontrol() const {
            return static_cast<bool> (flowcontrol_);}

        void flowcontrol(bool val) {
            flowcontrol_ = static_cast<num64> (val);}

        num32 flowcontrolbeforesleep() const {
            return in_bounded<num32 > (0, 100000, static_cast<num32> (flowcontrolbeforesleep_));}

        void flowcontrolbeforesleep(num32 val) {
            flowcontrolbeforesleep_ = static_cast<num64> (in_bounded<num32 > (0, 1000000, val));}

        num32 flowcontrolaftersleep() const {
            return in_bounded<num32 > (0, 100000, static_cast<num32> (flowcontrolaftersleep_));}

        void flowcontrolaftersleep(num32 val) {
            flowcontrolaftersleep_ = static_cast<num64> (in_bounded<num32 > (0, 1000000, val));}

        num32 readinterval() const {
            return in_bounded<num32 > (10, 100000, static_cast<num32> (readinterval_));}

        void readinterval(num32 val) {
            readinterval_ = static_cast<num64> (in_bounded<num32 > (10, 1000000, val));}

        num32 rtm() const {
            return in_bounded<num32 > (50, 100000, static_cast<num32> (rtm_));}

        void rtm(num32 val) {
            rtm_ = static_cast<num64> (in_bounded<num32 > (50, 1000000, val));}

        num32 rtc() const {
            return in_bounded<num32 > (50, 100000, static_cast<num32> (rtc_));}

        void rtc(num32 val) {
            rtc_ = static_cast<num64> (in_bounded<num32 > (50, 1000000, val));}

        num32 wtm() const {
            return in_bounded<num32 > (50, 100000, static_cast<num32> (wtm_));}

        void wtm(num32 val) {
            wtm_ = static_cast<num64> (in_bounded<num32 > (50, 1000000, val));}

        num32 wtc() const {
            return in_bounded<num32 > (50, 100000, static_cast<num32> (wtc_));}

        void wtc(num32 val) {
            wtc_ = static_cast<num64> (in_bounded<num32 > (50, 1000000, val));}


    private:
        num64 baudrate_; //  current baud rate 110 - 115200
        num64 databit_; //  databit           5, 6, 7 ,8
        num64 stopbit_; //  stopbit           1, 1.5, 2
        num64 parity_; //  parity            even, odd , mark, space, none
        num64 flowcontrol_; //  on /off
        num64 flowcontrolbeforesleep_; //  ms
        num64 flowcontrolaftersleep_; //  ms
        num64 readinterval_; //  ms
        num64 rtm_; //  ms
        num64 rtc_; //  ms
        num64 wtm_; //  ms
        num64 wtc_; //  ms
        num64 unus1_;
        num64 unus2_;
        num64 unus3_;
        num64 unus4_;
        num64 unus5_;} *prs232_property;

    typedef struct groupsstruct {
        typedef smplheader head_type;
        typedef groupstruct item_type;

        smplheader header;
        groupstruct items[];} *pgroupsstruct;



    //metalink

    typedef struct metalink {

        struct nillinfo {};



        struct comportinfo {
            baudratetype  boundrate;
            rsparitytype  parity;
            rsstopbittype stopbit;
            bool          flowcontrol;
            num32         flowcontrolbeforesleep;
            num32         flowcontrolaftersleep;
            num32         readinterval;
            num32         rtm;
            num32         rtc;
            num32         wtm;
            num32         wtc;};

        union info {
            nillinfo nilinf;
            comportinfo cominf;};


        static const size_t struct_size = sizeof (indx) + sizeof (chnltype) + sizeof (num32) * 9;

        metalink() :
        id_(nill_ptr), appid_(0), chanaltype_(0), chanalnum_(0),  protocol_(0),
        blocksize_(0), archblocksize_(0), eventblocksize_(0), indicateto_(0), host_(""), port_("") {}

        metalink(chnltype tp) :
        id_(nill_ptr), appid_(0), chanaltype_(tp), chanalnum_(0),  protocol_(0),
        blocksize_(0), archblocksize_(0), eventblocksize_(0), indicateto_(0), host_(""), port_("") {}

        metalink(const groupstruct & src, indx idn, const std::string& hst = "",
                const std::string& usr = "",
                const std::string& pass = "",
                const std::string& serv = "",
                const std::string& grp = "",
                const std::string& prt = "",
                const std::string& ethr = "",
                const std::string& tpc = "");

        operator bool() const {
            return (chanaltype_ != 0);}

        indx id() const {
            return id_;};

        appidtype appid() const {
            return appid_;};

        chnltype chanaltype() const {
            return chanaltype_;};

        protocoltype protocol() const {
            return protocol_;};

        blksizetype blocksize() const {
            return blocksize_;};

        blksizetype archblocksize() const {
            return archblocksize_;};

        blksizetype eventblocksize() const {
            return DEFAULT_EVENTSBLOCK_SIZE;};

        chnlnumtype chanalnum() const {
            return chanalnum_;};

        timeouttype indicateto() const {
            return indicateto_;}

        timeouttype timeout() const {
            return timeout_;}

        devnumtype devicenum() const {
            return devnum_;}

        bool echoresp() const {
            return false;}

        std::string host() const {
            return host_;};

        std::string port() const {
            return port_;};

        const info & inf() const {
            return inf_;};

        friend bool operator==(const metalink& ls, const metalink & rs);

        friend bool operator!=(const metalink& ls, const metalink & rs);

        friend bool operator<(const metalink& ls, const metalink & rs);


    private:

        indx          id_;
        appidtype     appid_;
        chnltype      chanaltype_;
        chnlnumtype   chanalnum_;
        devnumtype    devnum_;
        protocoltype  protocol_;
        blksizetype   blocksize_;
        blksizetype   archblocksize_;
        blksizetype   eventblocksize_;
        timeouttype   indicateto_;
        timeouttype   timeout_;
        info          inf_;
        std::string   host_;
        std::string   user_;
        std::string   password_;
        std::string   server_;
        std::string   group_;
        std::string   port_;
        std::string   ether_;
        std::string   topic_;} pmetalink;



    typedef std::set<metalink, std::less<metalink>, std::allocator<metalink> > metalink_set;

    typedef std::vector<metalink > metalink_vect;


    /////////////////////////////////////////////////////////////////////////   

    struct metalink_checker {

        metalink_checker() {};

        virtual ~metalink_checker() {};

        virtual ns_error operator()(const metalink_vect & mlvect);

        virtual ns_error compare(const metalink& rs, const metalink & ls) {
            return (ls == rs) ? 0 : ERROR_IO_NOSYNC_LINK;}};


    /////////////////////////////////////////////////////////////////////////

    typedef struct agroupstruct {
        agroupstruct(indx mid = nill_ptr);

        ~agroupstruct() {
            id(nill_ptr);}

        void id(indx val) {
            id_ = static_cast<unum64> (val);}

        indx id() const {
            return static_cast<indx> (id_);}

        void namepos(size_t val) {
            namepos_ = static_cast<unum64> (val);}

        size_t namepos() const {
            return static_cast<size_t> (namepos_);}

        void headernamepos(size_t val) {
            headernamepos_ = static_cast<unum64> (val);}

        size_t headernamepos() const {
            return static_cast<size_t> (headernamepos_);}
        
                
        void incmonitor() {}

        onum monitor() const {
            return 0;}

        agroupstruct get_for_write_to_file(bool firstcriteria = false);



    private:
        unum64 id_;
        num64  unusevalue_;
        num64  unusetime_;
        num64  unusetype_;
        num32  unusevalid_;
        num32  unuseerror_;
        unum64 namepos_;
        unum64 headernamepos_;
        num64  notuse1;
        num64  notuse2;} *pagroupstruct;

    typedef struct agroupsstruct {
        typedef smplheader head_type;
        typedef agroupstruct item_type;

        smplheader header;
        agroupstruct items[];} *pagroupsstruct;


    //userstruct

    typedef struct userstruct {
        userstruct(indx mid = nill_ptr);

        ~userstruct() {
            id(nill_ptr);}

        void id(indx val) {
            id_ = static_cast<unum64> (val);}

        indx id() const {
            return static_cast<indx> (id_);}

        void namepos(size_t val) {
            namepos_ = static_cast<unum64> (val);}

        size_t namepos() const {
            return static_cast<size_t> (namepos_);}

        void passpos(size_t val) {
            passpos_ = static_cast<unum64> (val);}

        size_t passpos() const {
            return static_cast<size_t> (passpos_);}

        acclevtype accesslevel() const {
            return in_bounded<acclevtype > (0, 10000, static_cast<acclevtype> (accesslevel_));}

        void accesslevel(acclevtype val) {
            accesslevel_ = static_cast<num64> (in_bounded<acclevtype > (0, 100, val));}
        
        void incmonitor() {}

        onum monitor() const {
            return 0;}

        userstruct get_for_write_to_file(bool firstcriteria = false);

    private:
        unum64 id_;
        unum64 namepos_;
        unum64 passpos_;
        num64 accesslevel_;
        num64 notuse1;
        num64 notuse2;
        num64 notuse3;} *puserstruct;

    typedef struct usersstruct {
        typedef smplheader head_type;
        typedef userstruct item_type;

        smplheader header;
        userstruct items[];} *pusersstruct;



    ///////////////////////////////////////////////////////////////////////////////

    typedef struct accessrulestruct {
        accessrulestruct(indx mid = nill_ptr);

        ~accessrulestruct() {
            id(nill_ptr);}

        void id(indx val) {
            id_ = static_cast<unum64> (val);}

        indx id() const {
            return static_cast<indx> (id_);}

        void namepos(size_t val) {
            namepos_ = static_cast<unum64> (val);}

        size_t namepos() const {
            return static_cast<size_t> (namepos_);}

        void cidrpos(size_t val) {
            cidrpos_ = static_cast<unum64> (val);}

        size_t cidrpos() const {
            return static_cast<size_t> (cidrpos_);}

        void apppos(size_t val) {
            apppos_ = static_cast<unum64> (val);}

        size_t apppos() const {
            return static_cast<size_t> (apppos_);}

        appidtype appid() const {
            return static_cast<appidtype> (appid_);}

        void appid(appidtype val) {
            appid_ = static_cast<num64> (val);}

        accessruletype rule() const {
            return in_bounded<accessruletype > (0, 2, static_cast<accessruletype> (rule_));}

        void rule(accessruletype val) {
            rule_ = static_cast<num64> (in_bounded<accessruletype > (0, 2, val));}

        acclevtype accesslevel() const {
            return static_cast<acclevtype> (accesslevel_);}

        void accesslevel(acclevtype val) {
            accesslevel_ = static_cast<num64> (val);}
        
                
        void incmonitor() {}

        onum monitor() const {
            return 0;}

        accessrulestruct get_for_write_to_file(bool firstcriteria = false);



    private:
        unum64 id_;
        unum64 namepos_;
        unum64 cidrpos_;
        unum64 apppos_;
        unum64 unusepos1_;
        unum64 unusepos2_;
        num64 appid_;
        num64 rule_;
        num64 accesslevel_;
        num64 notuse1;
        num64 notuse2;
        num64 notuse3;
        num64 notuse4;
        num64 notuse5;
        num64 notuse6;} *paccessrulestruct;

    typedef struct accessrulesstruct {
        typedef smplheader head_type;
        typedef accessrulestruct item_type;

        smplheader header;
        accessrulestruct items[];} *paccessrulesstruct;



    /////////////////////////////////////////////////////////////////////////////

    typedef struct cyclicheaderstruct {

        cyclicheaderstruct(size_t maxcnt = 0x8000) : count_(0), cursor_(0), gloubnum_(0) {
            ;
            maxcount_ = (maxcnt == 0) ? 0x8000 : (maxcnt / 2) *2;}

        size_t count() const {
            return static_cast<size_t> (count_);}

        size_t maxcount() const {
            return static_cast<size_t> (maxcount_);}

        size_t cursor() const {
            return static_cast<size_t> (cursor_);}

        size_t inc() {
            if (count() < maxcount()) count_++;
            size_t last = static_cast<size_t> (cursor_);
            cursor_ = ((++gloubnum_) % maxcount_);
            return last;}

        void setfree() {
            count_ = 0;
            cursor_ = 0;
            gloubnum_ = 0;}

        guidtype gloubnum() const {
            return static_cast<guidtype> (gloubnum_);}

    private:

        unum64 count_;
        unum64 cursor_;
        unum64 gloubnum_;
        unum64 maxcount_;} *pcyclicheaderstruct;

    typedef struct journalstruct {
        journalstruct(guidtype gid, const datetime& tm, indx tgid, msgtype tp,
                altype lev, indx agrp, double val = NULL_DOUBLE, indx userid = npos);

        explicit journalstruct(guidtype gid) {
            guid_ = static_cast<unum64> (gid);}

        ~journalstruct() {}

        guidtype guid() const {
            return static_cast<debuglvtype> (guid_);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        num64 time_n64() const {
            return time_;}

        indx tagid() const {
            return static_cast<indx> (tagid_);}

        indx agroup() const {
            return static_cast<indx> (agroup_);}

        msgtype type() const {
            return static_cast<msgtype> (type_ & 7);}

        altype level() const {
            return static_cast<altype> (level_ & 3);}

        double value() const {
            return static_cast<double> (value_);}

        bool isvalue() const {
            return (value() == value());}

        indx userid() const {
            return static_cast<indx> (user_);}

        friend bool operator<(const journalstruct& ls, const journalstruct & rs) {
            return ls.guid_ < rs.guid_;}


    private:
        unum64 guid_;
        num64 time_;
        num64 tagid_;
        num64 agroup_;
        num64 type_;
        num64 value_;
        num64 user_;
        num32 level_;} *pjournalstruct;

    typedef struct journalsstruct {
        typedef cyclicheaderstruct head_type;
        typedef journalstruct item_type;

        cyclicheaderstruct header;
        journalstruct items[];} *pjournalsstruct;
        
        
        
        
        
        
        

    typedef struct debugstruct {
        debugstruct(guidtype gid, const datetime& tm, const std::string& msg,
                debuglvtype lev, appidtype app = 0);

        explicit debugstruct(guidtype gid) {
            guid_ = static_cast<unum64> (gid);}

        ~debugstruct() {}

        guidtype guid() const {
            return static_cast<debuglvtype> (guid_);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        num64 time_n64() const {
            return time_;}

        debuglvtype level() const {
            return static_cast<debuglvtype> (level_ & 3);}

        appidtype appid() const {
            return static_cast<appidtype> (appid_);}

        std::string message() const {
            return pascalstr_to_string((void*) (&debugmessage_));}

        friend bool operator<(const debugstruct& ls, const debugstruct & rs) {
            return ls.guid_ < rs.guid_;}

    private:
        unum64 guid_;
        num64 time_;
        num64 level_;
        num64 appid_;
        num8 debugmessage_[LOGMESSAGE_STRINGSIZE + 2];} *pdebugstruct;

    typedef struct debugsstruct {
        typedef cyclicheaderstruct head_type;
        typedef debugstruct item_type;

        cyclicheaderstruct header;
        debugstruct items[];} *pdebugsstruct;
        
        
        
        
        
        

    typedef struct liveheaderstruct {

        liveheaderstruct(size_t maxcnt = 0x8000) : count_(0), gloubnum_(0), version_(0) {
            maxcount_ = (maxcnt == 0) ? 0x8000 : (maxcnt / 2) *2;}

        ~liveheaderstruct() {
            count(0);}

        size_t count() const {
            return static_cast<size_t> (count_);}

        void count(size_t val) {
            count_ = static_cast<num64> (val);}

        size_t maxcount() const {
            return static_cast<indx> (maxcount_);}

        guidtype gloubnum() const {
            return static_cast<guidtype> (gloubnum_);}

        guidtype version() const {
            return static_cast<guidtype> (version_);}

        guidtype incgloubnum() {
            return (++gloubnum_);}

        guidtype incversion() {
            return (++version_);}


    private:
        num64 count_;
        unum64 gloubnum_;
        unum64 version_;
        num64 maxcount_;} *pliveheaderstruct;



    //alarmsstruct    

    typedef struct alarmsstruct {

        explicit alarmsstruct(guidtype gid) : guid_(static_cast<unum64> (gid)) {}

        alarmsstruct(guidtype gid, datetime tm, indx tgid, msgtype tp, altype lev,
                indx grp, indx agrp, const double& val = NULL_DOUBLE);

        ~alarmsstruct() {
            guid_ = 0;}

        guidtype guid() const {
            return static_cast<guidtype> (guid_);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        num64 time_n64() const {
            return time_;}

        indx tagid() const {
            return static_cast<indx> (tagid_);}

        void kvit(bool val) {
            kvit_ = static_cast<num32> (val);}

        bool kvit() const {
            return static_cast<bool> (kvit_);}

        void off(bool val) {
            off_ = static_cast<num32> (val);}

        bool off() const {
            return static_cast<bool> (off_);}

        void level(altype val) {
            level_ = static_cast<num32> (val & 3);}

        altype level() const {
            return static_cast<altype> (level_ & 3);}

        void type(msgtype val) {
            type_ = static_cast<num64> (val & 7);}

        msgtype type() const {
            return static_cast<msgtype> (type_ & 7);}

        indx group() const {
            return static_cast<indx> (group_);}

        indx agroup() const {
            return static_cast<indx> (agroup_);}

        void time(datetime val) {
            time_ = castnum64_from_datetime(val);}

        std::string value() const {
            return (static_cast<double> (value_) == static_cast<double> (value_)) ?
                    to_str<double>(static_cast<double> (value_)) : "";}

        friend bool operator<(const alarmsstruct& ls, const alarmsstruct & rs) {
            return ls.guid_ < rs.guid_;}

    protected:

        void time_n64(num64 val) {
            time_ = val;}


    private:
        unum64 guid_;
        num64 time_;
        num64 tagid_;
        num64 type_;
        num32 kvit_;
        num32 off_;
        num32 level_;
        num64 group_;
        num64 agroup_;
        num64 value_;} *palarmsstruct;

    typedef struct alarmssstruct {
        typedef liveheaderstruct head_type;
        typedef alarmsstruct item_type;

        liveheaderstruct header;
        alarmsstruct items[];} *palarmssstruct;
        
        
        
        


    //registrystruct   

    typedef struct registrystruct {

        explicit registrystruct(guidtype gid) : guid_(static_cast<unum64> (gid)) {}

        registrystruct(guidtype gid, appidtype app, eventtypeset evs, guidtype hndl);

        ~registrystruct() {
            guid_ = 0;
            handle_ = 0;}

        guidtype guid() const {
            return static_cast<guidtype> (guid_);}

        guidtype handle() const {
            return static_cast<guidtype> (handle_);}

        eventtypeset eventsset() const {
            return static_cast<eventtypeset> (eventsset_);}

        appidtype appid() const {
            return static_cast<appidtype> (appid_);}

        friend bool operator<(const registrystruct& ls, const registrystruct & rs) {
            return ls.guid_ < rs.guid_;}



    private:
        unum64 guid_;
        num64 eventsset_;
        num64 appid_;
        unum64 handle_;} *pregistrystruct;

    typedef struct registrysstruct {
        typedef liveheaderstruct head_type;
        typedef registrystruct item_type;

        liveheaderstruct header;
        registrystruct items[];} *pregistrysstruct;


        
        


    //commandstruct    

    typedef struct commandstruct {
        static const guidtype NULL_CLIENT = 0x0;

        explicit commandstruct(guidtype gid) : guid_(static_cast<unum64> (gid)) {}

        commandstruct(guidtype gid, indx tgid, indx grp, num64 val_b, num64 val_s, guidtype clid = NULL_CLIENT, tagtype tp = 0);

        commandstruct(guidtype gid, indx tgid, indx grp, const std::string& vl, guidtype clid = NULL_CLIENT);

        void reset_commandstruct(num64 val_s, guidtype clid = NULL_CLIENT);

        void reset_commandstruct(const std::string& vl, guidtype clid = NULL_CLIENT);

        ~commandstruct() {
            guid_ = 0;}

        guidtype guid() const {
            return static_cast<guidtype> (guid_);}

        void time(datetime val) {
            time_ = castnum64_from_datetime(val);}

        datetime time() const {
            return cast_datetime_fromnum64(time_);}

        void time_n64(num64 val) {
            time_ = val;}

        num64 time_n64() const {
            return time_;}

        indx tagid() const {
            return static_cast<indx> (tagid_);}

        template <typename T>
                void value_before(T val) {
            value_before_ = num64_cast<T > (val);}

        template <typename T >
                T value_before() const {
            return from_num64_cast<T > (value_before_);}

        template <typename T>
                void value_set(T val) {
            value_set_ = num64_cast<T > (val);}

        template <typename T >
                T value_set() const {
            return from_num64_cast<T > (value_set_);}

        indx group() const {
            return static_cast<indx> (group_);}

        guidtype clientid() const {
            return static_cast<guidtype> (clientid_);}

        guidtype nullclient() const {
            return (static_cast<guidtype> (clientid_) == NULL_CLIENT);}

        tagtype type() const {
            return static_cast<tagtype> (type_);}

        void executed(bool val) {
            executed_ = static_cast<num32> (val);}

        bool executed() const {
            return static_cast<bool> (executed_);}

        bool istext() const {
            return static_cast<bool> (istext_);}

        std::string strvalue() const {
            return pascalstr_to_string((void*) (&strvalue_));}

        std::string value_before_str() const {
            return num64_and_type_cast<std::string>(value_before_, 0);}

        std::string value_str_set() const {
            return istext() ? strvalue() : num64_and_type_cast<std::string>(value_set_, 0);}

        friend bool operator<(const commandstruct& ls, const commandstruct & rs) {
            return ls.guid_ < rs.guid_;}

    private:

        void istext(bool val) {
            istext_ = static_cast<num32> (val);}

        void type(indx val) {
            type_ = static_cast<num32> (val);}

        void group(indx val) {
            group_ = static_cast<num64> (val);}

        void clientid(guidtype val) {
            clientid_ = static_cast<unum64> (val);}

        void strvalue(const std::string & val) {
            string_to_pascalstr((void*) &strvalue_, val.c_str(), DVNCI_MAXVALUESTRSIZE);}

        unum64 guid_;
        num64 tagid_;
        num64 group_;
        unum64 clientid_;
        num64 time_;
        num64 value_before_;
        num64 value_set_;
        num32 executed_;
        num32 istext_;
        num32 type_;
        num8 strvalue_[DVNCI_MAXVALUESTRSIZE + 2];} *pcommandstruct;


    typedef std::vector<commandstruct> command_vector;

    typedef struct commandsstruct {
        typedef liveheaderstruct head_type;
        typedef commandstruct item_type;

        liveheaderstruct header;
        commandstruct items[];} *pcommandsstruct;
        
        
        
        
        
        

    typedef struct clientstruct {

        explicit clientstruct(guidtype gid) {
            guid_ = static_cast<unum64> (gid);}

        clientstruct(guidtype gid, appidtype app, acclevtype lev, const std::string& hst = "",
                const std::string& ip_ = "", const std::string& usernm_ = "", indx clid = npos);

        ~clientstruct() {}

        guidtype guid() const {
            return static_cast<guidtype> (guid_);}

        indx ruleid() const {
            return static_cast<indx> (ruleid_);}

        appidtype appid() const {
            return static_cast<appidtype> (appid_);}

        acclevtype accesslevel() const {
            return static_cast<acclevtype> (accesslevel_);}

        std::string host() const {
            return pascalstr_to_string((void*) (&host_));}

        std::string ip() const {
            return pascalstr_to_string((void*) (&ip_));}

        std::string username() const {
            return pascalstr_to_string((void*) (&username_));}

        indx user() const {
            return static_cast<indx> (user_);}

        friend bool operator<(const clientstruct& ls, const clientstruct & rs) {
            return ls.guid_ < rs.guid_;}

    private:

        void appid(appidtype val) {
            appid_ = static_cast<num64> (val);}

        void ruleid(indx val) {
            ruleid_ = static_cast<num64> (val);}

        void accesslevel(acclevtype val) {
            accesslevel_ = static_cast<num64> (val);}

        void host(const std::string & val) {
            string_to_pascalstr((void*) &host_, val, HOST_STRINGSIZE);}

        void ip(const std::string & val) {
            string_to_pascalstr((void*) &ip_, val, HOST_STRINGSIZE);}

        void username(const std::string & val) {
            string_to_pascalstr((void*) &username_, val, HOST_STRINGSIZE);}

        void user(indx val) {
            user_ = static_cast<num64> (val);}

        unum64 guid_;
        num64 ruleid_;
        num64 appid_;
        num64 accesslevel_;
        num64 sid_;
        num8 host_[HOST_STRINGSIZE + 2];
        num8 ip_[HOST_STRINGSIZE + 2];
        num8 username_[HOST_STRINGSIZE + 2];
        num64 user_;
        num64 unused1;} *pclientstruct;

    typedef struct clientsstruct {
        typedef liveheaderstruct head_type;
        typedef clientstruct item_type;

        liveheaderstruct header;
        clientstruct items[];} *pclientsstruct;
        
        

    typedef struct nodeinfotype {

        nodeinfotype() {
            basis = 0;}

        explicit nodeinfotype(num64 btp) {
            basis = btp;}

        nodeinfotype(nodetype ntp, tagtype ttp , appidtype ptp = 0) {
            basis = static_cast<appidtype> (ptp);
            basis = (basis << 16) | (static_cast<tagtype> (ttp) & 0xFFFF);
            basis = (basis << 16) | (static_cast<nodetype> (ntp) & 0xFFFF);}

        operator num64() {
            return basis;}

        void setbasis(num64 val) {
            basis = val;};

        bool operator<(const nodeinfotype & rs) const {
            return (basis < rs.basis);}

        bool operator==(const nodeinfotype & val) {
            return (basis == val.basis);}

        nodeinfotype & operator=(const num64 & val) {
            basis = val;
            return (*this);}

        nodetype node() const {
            return static_cast<nodetype> ((0xFFFF & basis));};

        tagtype tgtype() const {
            return static_cast<tagtype> ((0xFFFF & (basis >> 16)));};

        appidtype pttype() const {
            return static_cast<appidtype> ((0xFFFF & (basis >> 32)));};
    private:
        num64 basis;} *pnodeinfotype;







    typedef std::pair< indx, nodeinfotype> entity_pair;
    typedef std::map< indx, nodeinfotype, std::less<indx>, std::allocator<entity_pair > > entity_map;

    typedef struct name_with_type {

        name_with_type() : name_(""), type_() {}

        name_with_type(std::string nm, nodetype ntp = NT_ROOT,
                tagtype ttp = TYPE_NODEF, appidtype ptp = 0) : name_(nm), type_(ntp, ttp, ptp) {}

        name_with_type(std::string nm, nodeinfotype tp) : name_(nm), type_(tp) {}

        void name(std::string val) {
            name_ = val;}

        std::string name() const {
            return name_;}

        void typeex(nodeinfotype val) {
            type_ = val;}

        nodeinfotype typeex() const {
            return (type_);}


    private:
        std::string name_;
        nodeinfotype type_;} *pname_with_type;


    typedef std::pair<indx, name_with_type > iteminfo_pair;
    typedef std::map<indx, name_with_type, std::less<indx>, std::allocator<iteminfo_pair > > iteminfo_map;

    typedef struct id_name_with_type {

        id_name_with_type() {
            id_ = npos;
            name_ = "";
            type_ = TYPE_NODEF;}

        id_name_with_type(indx key, std::string nm, tagtype tp = TYPE_NODEF) {
            id_ = key;
            name_ = nm;
            type_ = TYPE_NODEF;}

        void id(indx val) {
            id_ = val;}

        indx id() const {
            return id_;}

        void name(std::string val) {
            name_ = val;}

        std::string name() const {
            return name_;}

        void type(tagtype val) {
            type_ = static_cast<num64> (val);}

        tagtype type() const {
            return static_cast<tagtype> (type_);}
    private:
        indx id_;
        std::string name_;
        tagtype type_;} *pid_name_with_type;

    typedef struct datetime_data {

        datetime_data(float d, datetime dt) {
            data = d;
            tm = dt;}
        datetime tm;
        float data;} *pdatetime_data;



    struct date_time_pair {

        date_time_pair(datetime s1 = nill_time, datetime s2 = nill_time) {
            start = s1;
            stop = s2;}
        datetime start;
        datetime stop;};

    typedef std::pair<indx, date_time_pair > report_task_pair;
    typedef std::map<indx, date_time_pair, std::less< indx >, std::allocator<report_task_pair > > report_task_map;

    typedef std::pair<std::string, date_time_pair > report_nametask_pair;
    typedef std::map<std::string, date_time_pair, std::less< std::string >, std::allocator<report_nametask_pair > > report_nametask_map;

    typedef struct nsconfigurationproject {
        std::string path;
        std::string name;
        std::string comment;
        std::string picture;
        int accesslevel;
        dbprovtype dbmgr;
        std::string ndbstr;
        int analogbuff;
        int historyperiod;
        int loglevel;
        std::string admin;
        std::string password;
        int aport;
        int rport;
        int opcport;} *pnsconfigurationproject;

    struct bind_servdb {

        bind_servdb(std::string binding_ = "") : binding(binding_), servdb(0) {}

        bind_servdb(std::string binding_, double servdb_) : binding(binding_), servdb(servdb_) {}
        std::string binding;
        double servdb;};


    typedef std::pair<indx, bind_servdb > itembinding_pair;
    typedef std::map<indx, bind_servdb, std::less<indx>, std::allocator<itembinding_pair > > itembinding_map;

#pragma  pack(pop)

    BOOST_STATIC_ASSERT(sizeof (tagstruct) == 316);
    BOOST_STATIC_ASSERT(sizeof (tagsstruct_hdr) == 208);
    BOOST_STATIC_ASSERT(sizeof (groupstruct) == 512);
    BOOST_STATIC_ASSERT(sizeof (agroupstruct) == 72);
    BOOST_STATIC_ASSERT(sizeof (userstruct) == 56);
    BOOST_STATIC_ASSERT(sizeof (accessrulestruct) == 120);
    BOOST_STATIC_ASSERT(sizeof (smplheader) == 8);

    ;}


#endif	/* MAINSTRUCT_H */

