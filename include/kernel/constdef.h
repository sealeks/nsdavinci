/* 
 * File:   constdef.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on     тест  30 ноября 2009 года., 22:11
 */

#ifndef _DVNCI_KRNL_CONSTDEF_H
#define	_DVNCI_KRNL_CONSTDEF_H


#if defined(__MINGW32__) && defined(_amd64_)
        #define _DVN_WIN64_MGW_
#elif defined(__MINGW32__)
        #define _DVN_WIN32_MGW_
#elif defined(_MSC_VER) && defined(_WIN64)
        #define _DVN_WIN64_VC_ 
#elif defined(_MSC_VER) 
        #define _DVN_WIN32_VC_ 
#elif defined(__GNUC__) && defined(__amd64__)
        #define _DVN_LIN64_GNU_ 
#elif defined(__GNUC__)
        #define _DVN_LIN32_GNU_ 
#else
        #error PlatformXCompiler spec dont defined
#endif

#if defined(_DVN_WIN32_MGW_) || defined(_DVN_WIN32_VC_)
        #define _DVN_WIN32_
#elif defined(_DVN_WIN64_MGW_) || defined(_DVN_WIN64_VC_)
        #define _DVN_WIN64_
#elif defined(_DVN_LIN32_GNU_)
        #define _DVN_LIN32_
#elif defined(_DVN_LIN64_GNU_)
        #define _DVN_LIN64_
#else
        #error Platform spec dont defined
#endif

#if defined(_DVN_WIN32_) || defined(_DVN_WIN64_)
        #define _DVN_WIN_
#elif defined(_DVN_LIN32_GNU_) || defined(_DVN_LIN64_GNU_)
        #define _DVN_LIN_
#else
        #error Platform spec dont defined
#endif




#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#pragma warning(disable: 4101  4146 )
#endif


// set python styling
// set formating Netbeans
// except Otherparenthesis = true;  Другая круглая скобка
//        Keep Extra Sp    = true;  Сохранять дополненин
//        new line  = else , while , catch
// replace  regex   (?<!/)\n *\}    ->    }
// replace  regex   \n *\{          ->    {
// for С++ and C++ header
//  NB!!  after  commment line exp // hhhhhhhh need set / - > wrong: //  hhhhhh   right: //  hhhhhh /
//  regex search: //.+\n *}

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <deque>
#include <algorithm>
#include <cstddef>
#include <stack>
#include <exception>
#include <limits>


#include <sys/types.h>
#include <sys/stat.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>


#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <boost/token_functions.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/thread/thread.hpp>
#include <boost/filesystem/operations.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/iso_format.hpp>
#include <boost/date_time/date_format_simple.hpp>
#include <boost/date_time/date_facet.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/interprocess/sync/upgradable_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/permissions.hpp>
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_upgradable_mutex.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/filesystem.hpp>
#include <boost/static_assert.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/bimap/bimap.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/regex.hpp>
#include <boost/system/system_error.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/format.hpp>


#ifdef _DVN_WIN_
#include <boost/interprocess/windows_shared_memory.hpp>
#endif



#define OUTSTR_DVNCI(a)  std::cout << #a  << std::endl;
#define OUTSTRVAL_DVNCI(a,b)  std::cout << #a  << " " << #b" = "  << b  << std::endl;


#ifdef DVNCI_DEDUG

#define LOCKGLOBALOUT_DVNCI boost::mutex::scoped_lock lock(global_out_mutex());
#define DEBUG_STR_DVNCI(a)  std::cout << #a  << std::endl;
#define DEBUG_STR_VAL_DVNCI(a,b)  std::cout << #a  << " " << #b" = "  << b  << std::endl;
#define DEBUG_VAL_DVNCI(a)  std::cout << #a" = "  << a  << std::endl;
#define DEBUG_VAL2_DVNCI(a,b)  std::cout << #a" = "  << a  << " " << #b" = "  << b  << std::endl;
#define DEBUG_VAL3_DVNCI(a,b,c)  std::cout << #a" = "  << a  << " " << #b" = "  << b  << " " << #c" = "  << c  << std::endl;



#elif DVNCI_DEDUGFILE

#define LOCKGLOBALOUT_DVNCI boost::mutex::scoped_lock lock(global_out_mutex());
#define DEBUG_STR_DVNCI(a)  std::cout << #a  << std::endl;
#define DEBUG_STR_VAL_DVNCI(a,b)  std::cout << #a  << " " << #b" = "  << b  << std::endl;
#define DEBUG_VAL_DVNCI(a)  std::cout << #a" = "  << a  << std::endl;
#define DEBUG_VAL2_DVNCI(a,b)  std::cout << #a" = "  << a  << " " << #b" = "  << b  << std::endl;
#define DEBUG_VAL3_DVNCI(a,b,c)  std::cout << #a" = "  << a  << " " << #b" = "  << b  << " " << #c" = "  << c  << std::endl;


#else

#define LOCKGLOBALOUT_DVNCI  ;
#define DEBUG_STR_DVNCI(a)  ;
#define DEBUG_STR_VAL_DVNCI(a,b) ;
#define DEBUG_VAL_DVNCI(a)  ;
#define DEBUG_VAL2_DVNCI(a,b)  ;
#define DEBUG_VAL3_DVNCI(a,b,c)  ;


#endif

#define DEBUG_BASE_DVNCI(a,b)  a->log(#b);
#define DEBUGW_BASE_DVNCI(a,b)  a->logwarning(#b);
#define DEBUGE_BASE_DVNCI(a,b)  a->logerror(#b);

#ifdef _MSC_VER
#pragma warning(disable: 4200 4800)
#endif

#ifdef  _DVN_WIN_
#define BOOST_INTERPROCESS_WINDOWS
#endif

#ifdef  _DVN_WIN_
  const std::string SYSTEM_SHARE_SPEC = "Global\\";
#else
  const std::string SYSTEM_SHARE_SPEC = "";
#endif

namespace dvnci {


#if defined(_DVN_WIN32_MGW_)
    typedef unsigned char      unum8;
    typedef char               num8;
    typedef unsigned short     unum16;
    typedef short              num16;
    typedef unsigned int       unum32;
    typedef int                num32;
    typedef unsigned long long unum64;
    typedef long long          num64;
    typedef unum32             ounum;
    typedef num32              onum;
    typedef std::size_t        indx;
#elif defined(_DVN_WIN32_VC_)
    typedef unsigned char      unum8;
    typedef char               num8;
    typedef unsigned short     unum16;
    typedef short              num16;
    typedef unsigned int       unum32;
    typedef int                num32;
    typedef unsigned long long unum64;
    typedef long long          num64;
    typedef unum32             ounum;
    typedef num32              onum;
    typedef std::size_t        indx;
#elif defined(_DVN_LIN64_GNU_)
    typedef unsigned char      unum8;
    typedef char               num8;
    typedef unsigned short     unum16;
    typedef short              num16;
    typedef unsigned int       unum32;
    typedef int                num32;
    typedef unsigned long long unum64;
    typedef long long          num64;

    typedef unum64             ounum;
    typedef num64              onum;
   
    typedef std::size_t        indx;    
#else    
    #error Type not defined. Spec compiler and OS error
#endif

    
    typedef boost::posix_time::ptime datetime;

    typedef union type_punned{
        
         type_punned(const bool& vl) : n64(vl ? 1 : 0) {}
         type_punned(const unum8& vl) : u8(vl) {}
         type_punned(const num8& vl) : n8(vl) {}
         type_punned(const unum16& vl) : u16(vl) {}
         type_punned(const num16& vl) : n16(vl) {}
         type_punned(const unum32& vl) : u32(vl) {}
         type_punned(const num32& vl) : n32(vl) {}
         type_punned(const unum64& vl) : u64(vl) {}
         type_punned(const num64& vl) : n64(vl) {}
         type_punned(const float& vl) : fl(vl) {}
         type_punned(const double& vl) : dbl(vl) {}
         bool     bl;
         unum8    u8;
         num8     n8;
         unum16   u16;
         num16    n16;
         unum32   u32;
         num32    n32;
         unum64   u64;
         num64    n64;
         float    fl;
         double   dbl;} * ptype_punned;

    const indx npos              = static_cast<indx>(-1);

    const  num64 DVNCI_VERSION   = 0x4;

    const  size_t  MAX_NUM32_SIGNED = 0x1000; //FFFFFFF;

    const size_t  DVNCI_MAXVALUESTRSIZE   = 0xFC;

    const unsigned int DEFAULT_DVNCI_TIMOUT = 5000; //FFFFFFF

    const size_t  USERNAME_STRINGSIZE     = 100;
    const size_t  LOGMESSAGE_STRINGSIZE   = 400;
    const size_t  HOST_STRINGSIZE         = 200;

    const size_t  GROP_CONFIG_SIZE         = 144;

    const  double NULL_DOUBLE = std::numeric_limits<double>::quiet_NaN();
    const  double DV_PI_CONST = 3.14159265358979324;
    const  double DV_E_CONST =  2.71828182845904523;

    static inline bool isNaN(const double& vl) {
        return (vl != vl);}

    const   indx nill_ptr = 0;
    const   indx able_ptr = 1;

    
    BOOST_STATIC_ASSERT(sizeof(num8) == 1);
    BOOST_STATIC_ASSERT(sizeof(unum8) == 1);
    BOOST_STATIC_ASSERT(sizeof(num16) == 2);
    BOOST_STATIC_ASSERT(sizeof(unum16) == 2);
    BOOST_STATIC_ASSERT(sizeof(num32) == 4);
    BOOST_STATIC_ASSERT(sizeof(unum32) == 4);
    BOOST_STATIC_ASSERT(sizeof(num64) == 8);
    BOOST_STATIC_ASSERT(sizeof(unum64) == 8);
    BOOST_STATIC_ASSERT(sizeof(double) == 8);
    BOOST_STATIC_ASSERT(sizeof(float) == 4);    
    BOOST_STATIC_ASSERT(sizeof(datetime) == 8);  
    
    

    const   boost::posix_time::ptime nill_time = boost::posix_time::ptime();
    const   boost::posix_time::ptime epoch_time = boost::posix_time::ptime(boost::gregorian::date(1970,1,1));


    // tag type
    typedef onum   tagtype;
    // node type
    typedef tagtype nodetype;
    // application id type
    typedef tagtype appidtype;
    // service id type
    typedef tagtype servidtype;
    // report type
    typedef tagtype reporttype;
    //chanal type for group // RS232, TCP/ID, TCP/IPv6.....
    typedef onum chnltype;
    // operator access level type
    typedef onum acclevtype;
    //locale type
    typedef onum lcltype;
    // debug level type
    typedef onum debuglvtype;
    // valid level type
    typedef onum vlvtype;
    // system queue message type
    typedef num32 qumsgtype;
    // report statisic type
    typedef onum repstattype;
    // database provider type
    typedef onum dbprovtype;
    // event queue type set
    typedef onum eventtypeset;
    // journal message type
    typedef onum msgtype;
    // alarm level type
    typedef onum altype;
    // alarm cse type
    typedef onum alcstype;
    //  access tag type
    typedef onum acstgtype;
    // add command type
    typedef onum addcmdtype;
    // property id type
    typedef onum propidtype;
     // property rs232 baudrate
    typedef num32 baudratetype;
    // property rs232 rsparity
    typedef num32 rsparitytype;
    // property  baudrate
    typedef num32 rsdatabittype;
    // property  rsparity
    typedef num32 rsstopbittype;    
    // property  operation system type
    typedef onum opsystemtype;
    // property  operation system type
    typedef onum accessruletype;
    // guid type
    typedef unum64 guidtype;
    // confproptype provide type
    typedef onum confproptype;
    // protocol type
    typedef num32 protocoltype;

    typedef  boost::filesystem::path      fspath;

    const int SERVICE_OPEATION_INSTALL = 0x1;
    const int SERVICE_OPEATION_UNINSTALL = 0x2;
    const int SERVICE_OPEATION_START = 0x3;
    const int SERVICE_OPEATION_STOP = 0x4;
    const int SERVICE_OPEATION_RESTART = 0x5;
    const int SERVICE_OPEATION_APP = 0x6;

    const int SERVICE_RUNSTATE_NODEF = 0x0;
    const int SERVICE_RUNSTATE_OFF = 0x1;
    const int SERVICE_RUNSTATE_DEMAND = 0x2;
    const int SERVICE_RUNSTATE_AUTO = 0x3;
    const int SERVICE_RUNSTATE_SYSTEM = 0x4;
    const int SERVICE_RUNSTATE_BOOT = 0x5;

    const int SERVICE_STATUS_NODEF = 0x0;
    const int SERVICE_STATUS_RUN = 0x1;
    const int SERVICE_STATUS_STOPED = 0x2;
    const int SERVICE_STATUS_PENDING = 0x3;
    const int SERVICE_STATUS_NOTINSTALL = 0x4;

    const std::string DEFAULT_OPC_PORT = "10200";
    const std::string DEFAULT_REMOTE_PORT = "9050";
    const std::string DEFAULT_ADMIN_PORT = "8050";

    // типы соединения
    const num16 CONTYPE_SUBSCROPC = 0;
    const num16 CONTYPE_ASYNOPC   = 1;
    const num16 CONTYPE_SYNOPC    = 2;


    // политика доступа клиентов
    const accessruletype ACCESS_POLICY_AUTOTH = 0;
    const accessruletype ACCESS_POLICY_CREDIT = 1;
    const accessruletype ACCESS_POLICY_DENY   = 2;


    // поддержка сервисами обработки тегов

  /*  const providetype TYPE_SIMPL =  0x1; // только числовые типы
    const providetype PROVIDE_TEXTCURRENT =  0x2; // только текстовые типы
    const providetype PROVIDE_FULLCURRENT =  TYPE_SIMPL | PROVIDE_TEXTCURRENT;
    const providetype PROVIDE_REPORT      =  0x4; // только отчетные
    const providetype PROVIDE_EVENTS      =  0x8; // только события
    const providetype PROVIDE_ALL         =  PROVIDE_FULLCURRENT | PROVIDE_REPORT | PROVIDE_EVENTS;*/



    //  конфигурация проекта

    const confproptype NS_CNFG_ROOT          = 0x1;
    const confproptype NS_CNFG_PATH          = 0x2;
    const confproptype NS_CNFG_NAME          = 0x3;
    const confproptype NS_CNFG_COMMENT       = 0x4;
    const confproptype NS_CNFG_ARCHCNT       = 0x5;
    const confproptype NS_CNFG_MAPSZ         = 0x6;
    const confproptype NS_CNFG_DBMANAGER     = 0x7;
    const confproptype NS_CNFG_DBCONSTR      = 0x8;
    const confproptype NS_CNFG_ANALOGBUFF    = 0x9;
    const confproptype NS_CNFG_HISTORYPERIOD = 0xA;
    const confproptype NS_CNFG_LOGLEVEL     =  0xB;
    const confproptype NS_CNFG_ADMINNAME    =  0xC;
    const confproptype NS_CNFG_ADMINPASS    =  0xD;
    const confproptype NS_CNFG_ADMINPORT    =  0xE;
    const confproptype NS_CNFG_REMOTEPORT   =  0xF;
    const confproptype NS_CNFG_OPCREMOTEPORT = 0x10;
    const confproptype NS_CNFG_LOCAL         = 0x11;
    const confproptype NS_CNFG_OSTYPE        = 0x12;
    
    

    // meta property name
    const std::string PROPERTY_MF_name       = "name";
    const std::string PROPERTY_MF_color      = "color";
    const std::string PROPERTY_MF_textcolor  = "textcolor";
    const std::string PROPERTY_MF_fontsize   = "fontsize";
    const std::string PROPERTY_MF_delt       = "delt";
    const std::string PROPERTY_MF_group      = "group";
    const std::string PROPERTY_MF_width      = "width";
    const std::string PROPERTY_MF_height     = "height";
    const std::string PROPERTY_MF_type       = "type";
    const std::string PROPERTY_MF_initperiod = "initperiod";
    const std::string PROPERTY_MF_subperiod  = "subperiod";
    const std::string PROPERTY_MF_autoprint  = "autoprint";
    const std::string PROPERTY_MF_autoclose  = "autoclose";
    const std::string PROPERTY_MF_foottext   = "foottext";
    const std::string PROPERTY_MF_tg         = "tg";
    const std::string PROPERTY_MF_sumtype    = "sumtype";
    const std::string PROPERTY_MF_round      = "round";
    const std::string PROPERTY_MF_rowcolor   = "rowcolor";
    const std::string PROPERTY_MF_negcolor   = "negcolor";
    const std::string PROPERTY_MF_fill       = "fill";
    const std::string PROPERTY_MF_pencolor   = "pencolor";
    const std::string PROPERTY_MF_fillcolor  = "fillcolor";
    const std::string PROPERTY_MF_DBProvider = "DBProvider";
    const std::string PROPERTY_MF_constring  = "constring";
    const std::string PROPERTY_MF_host       = "host";


    const std::string NEMESPACEDELIMIT = "::";


    typedef num32 ns_error;

    typedef std::vector<indx>                                                                    date_tame_vect;

    typedef std::pair<std::string, indx>                                                         str_indx_pair;
    typedef std::map<std::string, indx, std::less<std::string>, std::allocator<str_indx_pair > > str_indx_map;

    typedef std::pair<indx, std::string > indx_str_pair;
    typedef std::map<indx, std::string, std::less<indx>, std::allocator<indx_str_pair > >        indx_str_map;


    typedef std::vector<indx>                                             indx_vect;

    typedef std::vector<std::string>                                      str_vect;

    typedef std::vector<num64>                                            num64_vect;

    typedef std::set<indx , std::less<indx>, std::allocator<indx> >       indx_set;

    typedef std::set<unum64 , std::less<unum64>, std::allocator<unum64> > unum64_set;

    typedef std::set<num64 , std::less<num64>, std::allocator<num64> >    num64_set;

    typedef std::set<num32 , std::less<num32>, std::allocator<num32> >    num32_set;

    typedef boost::shared_ptr<std::string>                                stdstr_ptr;

    typedef std::pair<indx, ns_error > errorinfo_pair;
    typedef std::map<indx, ns_error, std::less<indx>, std::allocator<errorinfo_pair > >                errorinfo_map;

    typedef std::pair<indx, datetime > indxdt_pair;
    typedef std::map<indx, datetime, std::less<indx>, std::allocator<indxdt_pair > >                   indxdt_map;

    
    typedef std::pair<std::string, std::string > filtered_pair;
    typedef std::map<std::string, std::string, std::less<std::string>, std::allocator<filtered_pair > > filtered_map;

    typedef std::pair<std::string, indx_set > filteredkey_pair;
    typedef std::map<std::string, indx_set, std::less<std::string>, std::allocator<filteredkey_pair > > filteredkey_map;

    typedef std::pair<datetime, double>                                                                 dt_val_pair;
    typedef std::map<datetime, double, std::less<datetime>, std::allocator<dt_val_pair > >              dt_val_map;

    typedef std::pair<indx , dt_val_pair>                                                               indx_dt_val;
    typedef std::vector<indx_dt_val>                                                                    vect_indx_dt_val;

    typedef std::deque<indx_dt_val, std::allocator<indx_dt_val > >                                      dt_val_deque;
    
    typedef boost::shared_ptr<dt_val_pair>                                                              datetime_val_ptr;

    typedef boost::shared_ptr<datetime>                                                                 datetime_ptr;
    typedef boost::shared_ptr<dt_val_map>                                                               dt_val_map_ptr;

    typedef std::pair<datetime, datetime>                                                               datetime_pair;
    typedef boost::shared_ptr<datetime_pair>                                                            datetime_pair_ptr;

    typedef std::pair<indx, dt_val_map > indx_dtvalmap_pair;
    typedef std::map<indx, dt_val_map, std::less<indx>, std::allocator<indx_dtvalmap_pair > >           indx_dtvalmap_map;

    typedef std::pair<indx, double > indx_double_pair;
    typedef std::map<indx, double, std::less<indx>, std::allocator<indx_double_pair > >                 indx_double_map;

    typedef boost::tokenizer<boost::char_separator<char> >                                              chartokenizer;

    typedef std::set<int , std::less<int>, std::allocator<int > > int_set;
    typedef std::set<std::string , std::less<std::string>, std::allocator<std::string > >               str_set;

    typedef boost::interprocess::message_queue                                                          mq_class;
    typedef boost::shared_ptr<mq_class>                                                                 mq_class_ptr;

    typedef std::pair<indx, mq_class_ptr>                                                               indx_mq_pair;
    typedef std::map<indx, mq_class_ptr, std::less<indx>, std::allocator<indx_mq_pair > >               indx_mq_map;

    typedef std::pair<eventtypeset, indx_mq_map>                                                        evst_indxmqmap_pair;
    typedef std::map<eventtypeset, indx_mq_map, std::less<indx>, std::allocator<evst_indxmqmap_pair > > evst_indxmqmap_map;

    typedef std::set<guidtype , std::less<guidtype>, std::allocator<guidtype > >                        guidtype_set;

    typedef std::pair<guidtype, mq_class_ptr>                                                           guid_mq_pair;
    typedef std::map<guidtype, mq_class_ptr, std::less<guidtype>, std::allocator<guid_mq_pair > >       guid_mq_map;

    typedef std::vector<num64> vect_num64;


#define THD_EXCLUSIVE_LOCK(a)  boost::mutex::scoped_lock thlock( a );
#define THD_EXCLUSIVE_LOCK2(a)  boost::mutex::scoped_lock thlock1( a );

    typedef boost::interprocess::interprocess_upgradable_mutex    interproc_mutex;
    typedef boost::interprocess::sharable_lock<interproc_mutex>   inp_lock_share;
    typedef boost::interprocess::scoped_lock<interproc_mutex>     inp_lock_exclusive;
    typedef boost::interprocess::upgradable_lock<interproc_mutex> inp_lock_upgrate;

#define INP_EXCLUSIVE_LOCK(a)  inp_lock_exclusive iplock( a );
#define INP_SHARE_LOCK(a)      inp_lock_share   iplock( a );
#define INP_UPGRATE_LOCK(a)    inp_lock_upgrate iplock( a );

    typedef boost::interprocess::named_mutex                           interproc_namemutex;
    typedef boost::interprocess::null_mutex                            interproc_nullmutex;
    typedef boost::interprocess::scoped_lock<interproc_namemutex>      lock_nameexclusive;

    typedef boost::shared_ptr<boost::mutex>    mutex_ptr;

    typedef std::pair<indx, datetime > indx_dt_pair;
    typedef std::map<indx, datetime, std::less<indx>, std::allocator<indx_dt_pair > > indx_dt_map;

    indx_set & operator>>(const num64_vect rs,  indx_set& ls);
    num64_vect & operator>>(const indx_set rs, num64_vect & ls);


    // Application
    /* 1) до 0x1000 не создают очередей сообщений
     * 2) 0x1000 - 0x2000 создают очереди сообщения , AppId групп соотносятся
     * с этим значением следующим образом group.appid=(APPID-0x1000) / 0x80 + 0x1000
     * 3) создают очереди group.appid=APPID*/

    const opsystemtype NS_WIN32 = 0x1;
    const opsystemtype NS_WIN64 = 0x2;
    const opsystemtype NS_LIN32 = 0x3;
    const opsystemtype NS_LIN64 = 0x4;

#if defined(_DVN_WIN32_)
    const opsystemtype NS_CURRENT_OS_TYPE = NS_WIN32;
#elif defined(_DVN_WIN64_)
    const opsystemtype NS_CURRENT_OS_TYPE = NS_WIN64;    
#elif defined(_DVN_LIN32_)
    const opsystemtype NS_CURRENT_OS_TYPE = NS_LIN32;
#elif defined(_DVN_LIN64_)
    const opsystemtype NS_CURRENT_OS_TYPE = NS_LIN64;
#endif

    const servidtype NS_ADMIN_APPLICATION   = 0x10;

    const servidtype NS_ADMIN_SERVICE       = 0x11;
    const std::string NS_ADMIN_SERVICE_NAME = "service_dvnciadmin";

    const servidtype NS_PERSISTENCE_SERVICE = 0x1000; //[0x1000-0x107F]
    const std::string NS_PERSISTENCE_SERVICE_NAME = "service_dvnciarch";
    const servidtype NS_SYSTEM_SERVICE      = 0x1001; //[0x1080-0x10FF]
    const std::string NS_SYSTEM_SERVICE_NAME = "service_dvncisys";

    const servidtype NS_NET_SERVICE      = 0x2000; //[0x1080-0x10FF]
    const std::string NS_NET_SERVICE_NAME = "service_dvncinet";

    const servidtype NS_OPC_SERVICE      = 0x2010; //[0x1080-0x10FF]
    const std::string NS_OPC_SERVICE_NAME = "service_dvnciopc";

    const servidtype NS_DDE_SERVICE      = 0x2020; //[0x1080-0x10FF]
    const std::string NS_DDE_SERVICE_NAME = "service_dvncidde";

    const servidtype NS_MODBUS_SERVICE      = 0x4020;
    const std::string NS_MODBUS_SERVICE_NAME = "service_dvncimodbus";

    const servidtype NS_KOYO_SERVICE      = 0x4120;
    const std::string NS_KOYO_SERVICE_NAME = "service_dvncikoyo";

    const servidtype NS_LGKA_SERVICE      = 0x4150;
    const std::string NS_LGKA_SERVICE_NAME = "service_dvncilgk";

    const servidtype NS_TEST_SERVICE      = 10000; //[0x1080-0x10FF]
    const std::string NS_TEST_SERVICE_NAME = "service_dvncitest";


    const appidtype NS_GROUP_DEFAULT       =    0x0;

    const appidtype NS_GROUP_SYSTEM              = 0x1080;
    const appidtype NS_GROUP_SYSTEMVAR           = 0x1081;
    const appidtype NS_GROUP_SYSTEMCOUNT         = 0x1082;
    const appidtype NS_GROUP_SYSTEMREPORT        = 0x1083;
    const appidtype NS_GROUP_SYSTEMREPORTCOUNT   = 0x1084;

    const appidtype NS_GROUP_NET   = 0x2000;
    const appidtype NS_GROUP_OPC   = 0x2010;
    const appidtype NS_GROUP_DDE   = 0x2020;

    const appidtype NS_GROUP_MODBUS   = 0x4020;
    const appidtype NS_GROUP_KOYO   = 0x4120;
    const appidtype NS_GROUP_LGKA   = 0x4150;

    inline static   bool in_EXCLUSIVEGROUP(appidtype val)  {
        return ((val == NS_GROUP_SYSTEM) || (val == NS_GROUP_SYSTEMVAR));};

    const lcltype     NS_CODPAGE_LOC8 = 1;
    const lcltype     NS_CODPAGE_UTF8 = 0;
    const lcltype     NS_CODPAGE_UTF16 = 2;
    const lcltype     NS_CODPAGE_UTF32 = 3;

    const debuglvtype DEBUGLEVEL_HIGH  = 3;
    const debuglvtype DEBUGLEVEL_MIDLE = 2;
    const debuglvtype DEBUGLEVEL_LOW   = 1;
    const debuglvtype DEBUGLEVEL_NONE  = 0;

    const debuglvtype DEBUG_FATALERROR = 0;
    const debuglvtype DEBUG_ERROR      = 1;
    const debuglvtype DEBUG_WARNING    = 2;
    const debuglvtype DEBUG_MESSAGE    = 3;



    const vlvtype  VALID_LEVEL =             90;
    const vlvtype  FULL_VALID =              100;
    const vlvtype  NULL_VALID =              0;
    const vlvtype  REPORT_NOACTIVE =         0;
    const vlvtype  REPORT_NEEDKHOWDEEP =     10;
    const vlvtype  REPORT_NEEDREQUEST =      20;
    const vlvtype  REPORT_NODATA =           30;
    const vlvtype  REPORT_DATA =             40;
    const vlvtype  REPORT_NORMAL =           100;
    const vlvtype  REPORT_WRITE =            50;
    const vlvtype  REPORT_NEEDWAIT =         45;
    const vlvtype  REPORT_WAIT =             46;
    const vlvtype  REPORT_WAITSOURCE =       47;
    const vlvtype  REPORT_WRITED =           60;
    const vlvtype  REPORT_NOWRITED =         61;



    const tagtype  OLD_EVENT_TYPE_WITH_TIME_VAL  = -500;
    const tagtype  OLD_EVENT_TYPE_WITHTIME       = -999;
    const tagtype  OLD_EVENT_TYPE_ALARM          = -850;
    const tagtype  OLD_EVENT_TYPE_OSC            = -501;
    const tagtype  OLD_TYPE_DISCRET              = -101;
    const tagtype  OLD_TYPE_NUM32                = -102;
    const tagtype  OLD_TYPE_DOUBLE               = -103;
    const tagtype  OLD_TYPE_UNUM32               = -104;
    const tagtype  OLD_TYPE_SMALL_INT            = -105;
    const tagtype  OLD_TYPE_UNUM16	         = -106;
    const tagtype  OLD_TYPE_NUM16                = -107;
    const tagtype  OLD_TYPE_UNUM8	         = -108;
    const tagtype  OLD_TYPE_SINGLE	         = -109;
    const tagtype  OLD_TYPE_REAL48	         = -110;
    const tagtype  OLD_TYPE_NUM8	         = -121;
    const tagtype  OLD_TYPE_TEXT	         = -122;
    const tagtype  OLD_TYPE_DT	                 = -130;
    const tagtype  OLD_TYPE_NODEF                = -100;
    const tagtype  OLD_REPORTTYPE_YEAR           = 8;
    const tagtype  OLD_REPORTTYPE_MIN            = 3;
    const tagtype  OLD_REPORTTYPE_HOUR           = 4;
    const tagtype  OLD_REPORTTYPE_DEC            = 5;
    const tagtype  OLD_REPORTTYPE_DAY            = 6;
    const tagtype  OLD_REPORTTYPE_MONTH          = 7;
    const tagtype  OLD_REPORTTYPE_10MIN          = 9;
    const tagtype  OLD_REPORTTYPE_30MIN          = 10;
    const tagtype  OLD_REPORTTYPE_QVART          = 11;
    const tagtype  OLD_REPORTTYPE_CUSTOM         = 12;
    
    
    
    
  

    const tagtype  TYPE_NONE                     = 0x00;
    const tagtype  TYPE_SIMPL                    = 0x01;
    const tagtype  TYPE_TIME                     = 0x10;
    const tagtype  TYPE_TEXT                     = 0x20;
    const tagtype  TYPE_REPORT                   = 0x40;
    const tagtype  TYPE_EVENT                    = 0x80;

    const tagtype  TYPE_FULL                    = TYPE_SIMPL | TYPE_TIME | TYPE_TEXT | TYPE_REPORT | TYPE_EVENT;
    
    const tagtype  TYPE_NO_ALARMED_MSK          = TYPE_TIME | TYPE_TEXT | TYPE_REPORT;


    const tagtype  TYPE_NODEF                  = 0x0;
    const tagtype  TYPE_DOUBLE                 = 0x1;
    const tagtype  TYPE_FLOAT	               = 0x2;
    const tagtype  TYPE_NUM64                  = 0x3;
    const tagtype  TYPE_UNUM64                 = 0x4;
    const tagtype  TYPE_NUM32                  = 0x5;
    const tagtype  TYPE_UNUM32                 = 0x6;
    const tagtype  TYPE_NUM16	               = 0x7;
    const tagtype  TYPE_UNUM16                 = 0x8;
    const tagtype  TYPE_NUM8	               = 0x9;
    const tagtype  TYPE_UNUM8	               = 0xA;
    const tagtype  TYPE_DISCRET                = 0xB;
    const tagtype  TYPE_TM	               = 0x10;

    const tagtype  EVENT_TYPE_WITHTIME         = 0x0 | TYPE_EVENT;
    const tagtype  EVENT_TYPE_OSC              = 0x1 | TYPE_EVENT;

    const tagtype  REPORTTYPE_YEAR             = 0x1  | TYPE_REPORT;
    const tagtype  REPORTTYPE_MIN              = 0x2  | TYPE_REPORT;
    const tagtype  REPORTTYPE_HOUR             = 0x3  | TYPE_REPORT;
    const tagtype  REPORTTYPE_DEC              = 0x4  | TYPE_REPORT;
    const tagtype  REPORTTYPE_DAY              = 0x5  | TYPE_REPORT;
    const tagtype  REPORTTYPE_MONTH            = 0x6  | TYPE_REPORT;
    const tagtype  REPORTTYPE_10MIN            = 0x7  | TYPE_REPORT;
    const tagtype  REPORTTYPE_30MIN            = 0x8  | TYPE_REPORT;
    const tagtype  REPORTTYPE_QVART            = 0x9  | TYPE_REPORT;
    const tagtype  REPORTTYPE_CUSTOM           = 0xA  | TYPE_REPORT;
    const tagtype  REPORTTYPE_NONE             = 0x0  | TYPE_REPORT;

    inline static  size_t GETDV_TYPESIZE(tagtype val)  {
        return val < TYPE_FLOAT ? 8 :
                val < TYPE_NUM64 ? 4 :
                val < TYPE_NUM32 ? 8 :
                val < TYPE_NUM16 ? 4 :
                val < TYPE_NUM8  ? 2 :
                val < TYPE_TEXT  ? 8 :
                val < TYPE_EVENT  ? 254 : 8;}
    
    inline static   bool IN_SMPLSET(tagtype val)  {
        return (val < TYPE_REPORT);};
    
    inline static   bool IN_NUMBERSET(tagtype val)  {
        return (val <TYPE_TM);};
    
    inline static   bool IN_TEXTSET(tagtype val)  {
        return (val == TYPE_TEXT);};

    inline static   bool IN_REPORTSET(tagtype val)  {
        return (val & TYPE_REPORT);};

    inline static   bool IN_EVENTSET(tagtype val)  {
        return (val & TYPE_EVENT);};
        
    inline static   bool IN_FLOATINGSET(tagtype val)  {
        return (val <= TYPE_FLOAT);};        

        
    inline static   bool IN_RANGESET(tagtype val)  {
        return (val <TYPE_DISCRET);};    

    inline static   bool IN_ALWACTSET(tagtype val)  {
        return (val >TYPE_TEXT);};
        
    inline static   bool IN_ALARMEDSET(tagtype val)  {
        return !(val & TYPE_NO_ALARMED_MSK);};
        
    inline static   bool IN_COMMADSET(tagtype val)  {
        return val < TYPE_REPORT;};        

    inline static   bool IN_TYPESET(tagtype val)  {
        return ((val >= 0x00) && (val < EVENT_TYPE_OSC));};
            
    inline static   tagtype SUPER_TYPE(tagtype val){        
            if ((val & 0x80)) return TYPE_EVENT;
            if ((val & 0x40)) return TYPE_REPORT;
            if ((val & 0x20)) return TYPE_TEXT;
            if ((val & 0x10)) return TYPE_TIME;
      return  TYPE_SIMPL;}

    tagtype oldtypetonew(tagtype val);

    const num32  MIN_REPORTTYPE_YEAR             = 1;
    const num32  MIN_REPORTTYPE_MIN              = 100;
    const num32  MIN_REPORTTYPE_HOUR             = 100;
    const num32  MIN_REPORTTYPE_DEC              = 100;
    const num32  MIN_REPORTTYPE_DAY              = 31;
    const num32  MIN_REPORTTYPE_MONTH            = 12;
    const num32  MIN_REPORTTYPE_10MIN            = 100;
    const num32  MIN_REPORTTYPE_30MIN            = 100;
    const num32  MIN_REPORTTYPE_QVART            = 4;
    const num32  MIN_REPORTTYPE_CUSTOM           = 0;
    const num32  MIN_REPORTTYPE_NONE             = 0;

    const num32  MAX_REPORTTYPE_YEAR             = 30;
    const num32  MAX_REPORTTYPE_MIN              = 1200;
    const num32  MAX_REPORTTYPE_HOUR             = 5000;
    const num32  MAX_REPORTTYPE_DEC              = 1000;
    const num32  MAX_REPORTTYPE_DAY              = 1000;
    const num32  MAX_REPORTTYPE_MONTH            = 300;
    const num32  MAX_REPORTTYPE_10MIN            = 1200;
    const num32  MAX_REPORTTYPE_30MIN            = 1200;
    const num32  MAX_REPORTTYPE_QVART            = 100;
    const num32  MAX_REPORTTYPE_CUSTOM           = 0;
    const num32  MAX_REPORTTYPE_NONE             = 0;

    // нормализация периода предыстории
    void normilize_history_bound(vlvtype  type, num32& val);
    void normilize_report_subperiod(vlvtype  type, num32& val);

    const repstattype  REPORT_STATISTIC_NONE           = 0;
    const repstattype  REPORT_STATISTIC_AVER           = 1;
    const repstattype  REPORT_STATISTIC_INTEG          = 2;
    const repstattype  REPORT_STATISTIC_SUM            = 3;
    const repstattype  REPORT_STATISTIC_MIN            = 4;
    const repstattype  REPORT_STATISTIC_MAX            = 5;
    const repstattype  REPORT_STATISTIC_MOD            = 6;


    const size_t RESET_LOG_TIME = 55;

    const num32 REP_COUNT_NODEF  = 0;
    const num32 REP_COUNT_BY_LOG = 1;
    const num32 REP_COUNT_BY_REP = 2;


    const dbprovtype PROPERTY_DB_PROVIDER_NONE = 0x0000;
    const dbprovtype PROPERTY_DB_PROVIDER_POSTGRESS = 0x0001;
    const dbprovtype PROPERTY_DB_PROVIDER_ORACLE = 0x0002;
    const dbprovtype PROPERTY_DB_PROVIDER_MYSQL = 0x0003;


    const eventtypeset sIMMINone       = 0x0000;
    const eventtypeset sIMMIChanged    = 0x0001;
    const eventtypeset sIMMILog        = 0x0002;
    const eventtypeset sIMMIJournal    = 0x0004;
    const eventtypeset sIMMICommand    = 0x0020;
    const eventtypeset sIMMIRef        = 0x0040;
    const eventtypeset sIMMIValid      = 0x0100;
    const eventtypeset sIMMIDebug      = 0x0200;
    const eventtypeset sIMMITagManage  = 0x0400;
    const eventtypeset sIMMIGroupManage = 0x0800;
    const eventtypeset sIMMIDBManage    = 0x1000;


    // sIMMILog - трендовые сообщения
    const qumsgtype MSG_DVNCLOG             = 10011;
    // sIMMIEvent - событийные сообщения
    //const qumsgtype MSG_DVNCEvent           = 10012;
    // sIMMIAlarm - тревожные сообщения
    const qumsgtype MSG_DVNCJOURNAL         = 10013;
    // sIMMICommand - команды
    const qumsgtype MSG_DVNCICOMMAND         = 10015;
    // sIMMIKvit
    const qumsgtype MSG_DVNCIKVIT            = 10016;
    // sIMMIRef
    const qumsgtype MSG_DVNCINEWREF          = 10017;
    const qumsgtype MSG_DVNCIREMREF          = 10018;
    //sIMMIValid
    const qumsgtype MSG_DVNCIVALID           = 10022;
    // sIMMIDebug - лог сообщение
    const qumsgtype MSG_DVNCDEBUG           = 10024;
    //sIMMITagManage  - изменение свойст тега
    const qumsgtype MSG_DVNCTAGDELETE       = 10025;
    const qumsgtype MSG_DVNCTAGNEW          = 10026;
    const qumsgtype MSG_DVNCTAGDELFROMGR    = 10027;
    const qumsgtype MSG_DVNCTAGADDTOGR      = 10028;
    const qumsgtype MSG_DVNCTAGREPNAME      = 10032;
    const qumsgtype MSG_DVNCITAGREPORT      = 10035;

    // sIMMIGroupManage
    const qumsgtype MSG_DVNCIGROUPDELETE    = 10040;
    const qumsgtype MSG_DVNCIGROUPNEW       = 10041;
    const qumsgtype MSG_DVNCIGROUPCHAPP     = 10042;

    // sIMMIDBManage
    const qumsgtype MSG_DVNCICONNSTRCH      = 10050;
    const qumsgtype MSG_DVNCDBCONNECT       = 10051;
    const qumsgtype MSG_DVNCDBDISCONNECT    = 10052;

    std::string messagestrin_test(qumsgtype val);

    const msgtype msNew        = 0x00;
    const msgtype msKvit       = 0x01;
    const msgtype msOut        = 0x02;
    const msgtype msOn         = 0x03;
    const msgtype msOff        = 0x04;
    const msgtype msCmd        = 0x05;
    const msgtype msTimeEvent  = 0x06;
    const msgtype msTimeAlarm  = 0x07;


    const altype altNone       = 0x0;
    const altype altNotice     = 0x1;
    const altype altWarning    = 0x2;
    const altype altAccident   = 0x3;


    const alcstype alarmMore = 0x00;
    const alcstype alarmLess = 0x01;
    const alcstype alarmEqual = 0x02;


    const acstgtype rwReadWrite = 0x00;
    const acstgtype rwReadOnly  = 0x01;
    const acstgtype rwWriteOnly = 0x02;



    const addcmdtype acNullCommand = 0x00;
    const addcmdtype acNewCommand = 0x01;
    const addcmdtype acQueuedCommand = 0x02;


    const std::string  MAIN_MAP_NAME           = SYSTEM_SHARE_SPEC + "dvncisys_analogmem_base";
    const std::string  GROUPS_MAP_NAME         = SYSTEM_SHARE_SPEC + "dvncisys_groupsmem_base";
    const std::string  ALARMGROUPS_MAP_NAME    = SYSTEM_SHARE_SPEC + "dvncisys_agroupsmem_base";
    const std::string  ACCESSRULES_MAP_NAME    = SYSTEM_SHARE_SPEC + "dvncisys_accessrulemem_base";
    const std::string  STRING_MAP_NAME         = SYSTEM_SHARE_SPEC + "dvncisys_string_base";
    const std::string  VALSTRING_MAP_NAME      = SYSTEM_SHARE_SPEC + "dvncisys_valuestring_base";
    const std::string  COMMAND_MAP_NAME        = SYSTEM_SHARE_SPEC + "dvncisys_command_base";
    const std::string  ALARMS_MAP_NAME         = SYSTEM_SHARE_SPEC + "dvncisys_alarms_base";
    const std::string  ALARMLOCALS_MAP_NAME    = SYSTEM_SHARE_SPEC + "dvncisys_alarmlocal_base";
    const std::string  DEBUGS_MAP_NAME         = SYSTEM_SHARE_SPEC + "dvncisys_debug_base";
    const std::string  ANALOGLOCBASE_MAP_NAME  = SYSTEM_SHARE_SPEC + "dvncisys_analoglocbase_base";
    const std::string  REGISTRATION_MAP_NAME   = SYSTEM_SHARE_SPEC + "dvncisys_registration_base";
    const std::string  CLIENTBASE_MAP_NAME     = SYSTEM_SHARE_SPEC + "dvncisys_clientbase_base";
    const std::string  OPERATOR_MAP_NAME       = SYSTEM_SHARE_SPEC + "dvncisys_operator_base";
    const std::string  ANALOBUFF_MAP_NAME      = SYSTEM_SHARE_SPEC + "dvncisys_analobuf_base";
    const std::string  REPORTBUFF_MAP_NAME     = SYSTEM_SHARE_SPEC + "dvncisys_report_base";
    const std::string  NS_MESSAGEQUEUE_NAME    = "dvncisys_messag_queue_";

    const std::string  NS_ONETIMEINIT_MTXNAME  = "dvncisys_onetymeinit_mtx";

    const num32 messsage_queue_count = 1000;
    
    const std::string WSP_STRING_WO_SP                     = "\x9\xD\xA";
    const std::string WSP_STRING                           = "\x20\x9\xD\xA";

    const std::string CORRECT_ENTETYNAME_REGEXTAMPL        = "[A-Za-z_\\$][A-Za-z_\\$0-9]*+";
    const std::string CORRECT_ENTETYFULLNAME_REGEXTAMPL    = CORRECT_ENTETYNAME_REGEXTAMPL + "::" + CORRECT_ENTETYNAME_REGEXTAMPL;
    const std::string EXCL_CORRECT_ENTETYNAME_REGEXTAMPL   = "^num$|^abs$|^real$|^bool$|^min$|^max$|^sin$|^cos$|^pow$|^sqrt$|^sqr$"
                                                             "|^exp$|^ln$|^rnd$|^e$|^pi$|^floor$|^trunc$";
    const std::string NUMBER_REGEXTAMPL_BIN                = "0b[01]{1,63}+u?+l?+u?+|0b[01]{1,31}+u?+";
    const std::string NUMBER_REGEXTAMPL_OCT                = "0[0-7]{0,21}+u?+l?+u?+|0[0-7]{1,10}+u?+";
    const std::string NUMBER_REGEXTAMPL_DEC                = "[1-9][0-9]{0,19}+l?+u?+1?+|[1-9][0-9]{0,9}+u?+|[1-9][0-9]{0,9}+f?+|0f?+";
    const std::string NUMBER_REGEXTAMPL_HEX                = "0x[0-9a-f]{1,16}+l?+u?+1?+|0x[0-9a-f]{1,8}+u?+";
    const std::string NUMBER_REGEXTAMPL_FP                 = "[0-9]*\\.[0-9]++f?+";
    const std::string NUMBER_REGEXTAMPL_EXT                = NUMBER_REGEXTAMPL_FP + "|" + NUMBER_REGEXTAMPL_BIN + "|" + NUMBER_REGEXTAMPL_HEX + "|" +
                                                             NUMBER_REGEXTAMPL_OCT + "|" + NUMBER_REGEXTAMPL_DEC;


    const std::string NUMBER_REGEXTAMPL                    = "[0-9]*[\\.]?[0-9]++";
    const std::string OPERATORS_REGEXTAMPL                 = "\\(|\\)|\\*|/|%|\\+\\+?+|--?+|<<<|>>>|<<|>>|[<>!=]=?+|&?+&|\\^|\\|?\\||&?&|,|\\?|:|@|#";
    const std::string SELECTOR_REGEXTAMPL                  = "\\.bool|\\.real|\\.num|\\.alarmack|\\.alarm|\\.ack|\\.mineu|\\.maxeu"
                                                             "|\\.time|\\.logtime|\\.error|\\.valid|\\.msc|\\.sec|\\.minute|\\.hour|\\.monthdays"
                                                             "|\\.dayweek|\\.dayyear|\\.day|\\.month|\\.year|\\.epochminute|\\.epochhour"
                                                             "|\\.epochday|\\.epochmsc|\\.epoch|\\.lastvalue";
    const std::string FUNCTION_REGEXTAMPL                  = "num(?=\\()|abs(?=\\()|real(?=\\()|bool(?=\\()|min(?=\\()|max(?=\\()"
                                                             "|sinh(?=\\()|cosh(?=\\()|tanh(?=\\()|asin(?=\\()|acos(?=\\()|atan(?=\\()|sin(?=\\()|cos(?=\\()|tan(?=\\()"
                                                             "|pow(?=\\()|sqrt(?=\\()|sqr(?=\\()|exp(?=\\()|log10(?=\\()|log(?=\\()|ln(?=\\()"
                                                             "|rnd(?=\\()|now(?=\\()|e(?=\\()|pi(?=\\()|nan(?=\\()|floor(?=\\()|seil(?=\\()|round(?=\\()"
                                                             "|incday(?=\\()|inchour(?=\\()|incminute(?=\\()|incsec(?=\\()|incmsc(?=\\()";
    const std::string TYPECAST_REGEXTAMPL                 =  "\\(notype\\)|\\(num64\\)|\\(unum64\\)|\\(num32\\)|\\(unum32\\)|\\num16\\)"
                                                             "|\\(unum16\\)|\\(num8\\)|\\(unum8\\)|\\(float\\)|\\(double\\)|\\(bool\\)"
                                                             "|\\(time\\)|\\(text\\)";

    const std::string FULLEXPR_REGEXTAMPL                 = "(" + FUNCTION_REGEXTAMPL + "|" +
                                                                  TYPECAST_REGEXTAMPL + "|" +
                                                                  SELECTOR_REGEXTAMPL + "|" +
                                                                  CORRECT_ENTETYFULLNAME_REGEXTAMPL + "|" +
                                                                  CORRECT_ENTETYNAME_REGEXTAMPL + "|" +
                                                                  OPERATORS_REGEXTAMPL  + "|" +
                                                                  NUMBER_REGEXTAMPL_EXT + ")";

    const boost::regex FULLEXPR_REGEX                     = boost::regex(FULLEXPR_REGEXTAMPL);

    const fspath MAIN_FILE_NAME       = "tagfile.mm";
    const fspath STRING_FILE_NAME     = "stringfile.mm";
    const fspath VALSTRING_FILE_NAME  = "valuestringfile.mm";
    const fspath GROUPS_FILE_NAME     = "groupfile.mm";
    const fspath ALARMGROUPS_FILE_NAME = "alarmgroupfile.mm";
    const fspath ACCESSRULES_FILE_NAME = "accessrulefile.mm";
    const fspath OPERATOR_FILE_NAME   = "operatorfile.mm";
    const fspath META_FILE_NAME       = "AppMetaInfo.xml";
    const fspath DVNCI_GLOBALPATH     = "DVNCI_GLOBALPATHU";


    const num64 CRITERIA_NO_REWRITE = -1;
    const num64 CRITERIA_REWRITE = 1;


    // Тип меток 0x000000XX - служебные
    // Тип меток 0x0000XX00 - теги базы
    // Тип меток 0x0XXX0000 - группы баз

    const nodetype NT_ROOT                    = 0x00; // корневая метка
    const nodetype NT_ROOT_SERVERS_NOTAVAIL   = 0x01; // корневая метка северов
    const nodetype NT_ROOT_SERVERS_AVAIL      = 0x02; // корневая метка северов
    const nodetype NT_ROOT_SERVERS_NOTAVAIL_R = 0x11; // корневая метка северов
    const nodetype NT_ROOT_SERVERS_AVAIL_R    = 0x12;    // корневая метка северов
    const nodetype NT_ROOT_GROUPS             = 0x05; // корневая метка опроса
    const nodetype NT_ROOT_AGROUPS            = 0x06; // корневая групп алармов
    const nodetype NT_ROOT_USERS              = 0x07; // корневая операторов
    const nodetype NT_ROOT_ACCESSRULES        = 0x09; // корневая правил доступа
    const nodetype NT_GROUP                   = 0x400; //  метка группы опроса
    const nodetype NT_AGROUP                  = 0x500; //  метка группы опроса
    const nodetype NT_USER                    = 0x600; //  метка юзера
    const nodetype NT_ACCESSRULE              = 0x700; //  метка правил доступа
    const nodetype NT_CLIENT                  = 0x800; //  метка клиентов
    const nodetype NT_TAG                     = 0x100; //  метка тега базы
    const nodetype NT_ATAG                    = 0x150; //  метка тега базы
    const nodetype NT_ALARM                   = 0x160; //  метка алармов журнала активных тревог
    const nodetype NT_JOURNAL                 = 0x170; //  метка строк журнала
    const nodetype NT_COMMAND                 = 0x180; //  метка строк таблицы команд
    const nodetype NT_REGISTRY                = 0x190; //  метка строк таблицы регистрации приложений
    const nodetype NT_LOG                     = 0x1A0; //  метка строк таблицы лога
    const nodetype NT_ROOT_NODEF              = 0x08;
    const nodetype NT_ROOT_SERVICES           = 0x1B0; //  корень сервисов
    const nodetype NT_SERVICE                 = 0x1C0; //  сервис

    const nodetype NT_UTILGROUP               = 0x1000; //  корень отладки
    const nodetype NT_UTIL_MAINTABLE          = 0x1001; //  основная таблица
    const nodetype NT_UTIL_GROUPTABLE         = 0x1002; //  основная таблица
    const nodetype NT_UTIL_DEBUG              = 0x1003; //  Лог
    const nodetype NT_UTIL_REGISTRY           = 0x1004; //  основная таблица
    const nodetype NT_UTIL_VALCH              = 0x1005; //  основная таблица
    const nodetype NT_UTIL_COMMAND            = 0x1006; //  Лог
    const nodetype NT_UTIL_JOURNAL            = 0x1007; //  основная таблица
    const nodetype NT_UTIL_ALARM              = 0x1008;
    const nodetype NT_UTIL_FINDER             = 0x1009;
    const nodetype NT_UTIL_ACCESSRULES        = 0x100A; //  таблица правил доступа
    const nodetype NT_UTIL_CLIENTS            = 0x100B; //  таблица клиентов

    const nodetype NT_MF_ROOT                 = 0x2000;   // Root metaifo client <meta>
    const nodetype NT_MF_HOME                 = 0x2001;   // Home metaifo client <HomeList>
    const nodetype NT_MF_REPLIST              = 0x2002;   // ReportList metaifo client <ReportList>
    const nodetype NT_MF_TRENDLIST            = 0x2003;   // TrendList metaifo client <TrendList>
    const nodetype NT_MF_MESSLIST             = 0x2004;   // MessageList metaifo client <MessageList>
    const nodetype NT_MF_REPHEADER            = 0x2005;   // ReportList metaifo client <ReportHeader>
    const nodetype NT_MF_TRENDHEADER          = 0x2006;   // TrendList metaifo client <TrendHeader>
    const nodetype NT_MF_MESSHEADER           = 0x2007;   // MessageList metaifo client <MessageHeader>
    const nodetype NT_MF_REPARR               = 0x2008;   // Report metaifo client <ReportArr>
    const nodetype NT_MF_UNIT                 = 0x2009;   // Report metaifo client <unit>
    const nodetype NT_MF_TRENDARR             = 0x2010;   // Report metaifo client <TrendArr>
    const nodetype NT_MF_TREND                = 0x2011;   // Report metaifo client <trend>
    const nodetype NT_MF_MESSARR              = 0x2012;    // Report metaifo client <MessageArr>
    const nodetype NT_MF_MESSAGE              = 0x2013;   // Report metaifo client <message>


    // Тип канала
    const chnltype NT_CHTP_NODEF                   = 0x0;
    const chnltype NT_CHTP_RS232_4XX               = 0x1; // RS chanel
    const chnltype NT_CHTP_TCP_IP                  = 0x2; // TCP/IP
    const chnltype NT_CHTP_UDP_IP                  = 0x3; // UDP/IP
    const chnltype NT_CHTP_IPX                     = 0x4;  //


    const size_t TREND_BUFFER_SIZE = 0x1000;
    const size_t REPORT_BUFFER_SIZE = 0x200;

    //  uart config

    const baudratetype NT_RS_DOUNDRATE_110	= 110;
    const baudratetype NT_RS_DOUNDRATE_300	= 300;
    const baudratetype NT_RS_DOUNDRATE_600	= 600;
    const baudratetype NT_RS_DOUNDRATE_1200	= 1200;
    const baudratetype NT_RS_DOUNDRATE_2400	= 2400;
    const baudratetype NT_RS_DOUNDRATE_4800	= 4800;
    const baudratetype NT_RS_DOUNDRATE_9600	= 9600;
    const baudratetype NT_RS_DOUNDRATE_14400	= 14400;
    const baudratetype NT_RS_DOUNDRATE_19200	= 19200;
    const baudratetype NT_RS_DOUNDRATE_38400	= 38400;
    const baudratetype NT_RS_DOUNDRATE_56000	= 56000;
    const baudratetype NT_RS_DOUNDRATE_57600	= 57600;
    const baudratetype NT_RS_DOUNDRATE_115200	= 115200;
    const baudratetype NT_RS_DOUNDRATE_128000	= 128000;
    const baudratetype NT_RS_DOUNDRATE_256000	= 256000;

    
    const rsparitytype NT_RS_NOPARITY	        = 0;
    const rsparitytype NT_RS_ODDPARITY	        = 1;
    const rsparitytype NT_RS_EVENPARITY	        = 2;
    const rsparitytype NT_RS_MARKPARITY	        = 3;
    const rsparitytype NT_RS_SPACEPARITY	= 4;

    const rsstopbittype NT_RS_ONESTOPBIT	= 0;
    const rsstopbittype NT_RS_ONE5STOPBITS	= 1;
    const rsstopbittype NT_RS_TWOSTOPBITS	= 2;
    
    

    const num32    DEFAULT_BLOCK_SIZE = 255;
    const num32    DEFAULT_ARCHBLOCK_SIZE = 10;
    const num32    DEFAULT_EVENTSBLOCK_SIZE = 10;

    const protocoltype    NT_MODBUS_RTU  = 0x0;
    const protocoltype    NT_MODBUS_ASCII  = 0x1;

    const protocoltype    NT_KOYO_MODBUS           = 0x0;
    const protocoltype    NT_KOYO_DIRECTNET_HEX    = 0x1;
    const protocoltype    NT_KOYO_DIRECTNET_ASCII  = 0x2;
    const protocoltype    NT_KOYO_DIRECTNET_ECOM   = 0x3;

    const num32    DEFAULT_IOTIMOUT           = 3000;
    const num32    MINIMUM_IOTIMOUT           = 10;
    const num32    MAXIMUM_IOTIMOUT           = 1000000;
    
    
    const size_t  DVNCI_DEFRES_NAMESIZE   = 0x20;
    const size_t  DVNCI_DEFRES_STRINGSIZE = 0x99;

    const size_t  MAX_ANALOGBUFFCNT       = 0x4000;

    const size_t EXTEND_MEMSHARE_TAGCNT = 40000;
    const size_t EXTEND_MEMSHARE_GRPCNT = 6000;
    const size_t EXTEND_MEMSHARE_AGRPCNT = 6000;
    const size_t EXTEND_MEMSHARE_USERCNT = 6000;
    const size_t EXTEND_MEMSHARE_ACCESSRULCNT = 400;
    const size_t EXTEND_MEMSHARE_STRCNT = 40000;
    const size_t EXTEND_MEMSHARE_STRMDL = 300;
    const size_t EXTEND_MEMSHARE_STRSTATICCNT = 1000;
    const size_t EXTEND_MEMSHARE_STRSTATIC = 0xFF;

    // узел может быть родителем
    bool     nodetp_canchild(nodetype tp);
    // узел является метаинформацией
    bool     nodetp_is_meta(nodetype tp);
    //  тип дочернего узла по типу tp
    nodetype nodetp_child_by_parent(nodetype tp);
    //  тип родительского узла по типу tp
    nodetype nodetp_paren_by_child(nodetype tp);


    /* Запрос пути к базе из хранилища ОС */
    fspath getlocalbasepath();

    /* Установка пути к базе в хранилище ОС*/
    fspath setlocalbasepath(const fspath& val);

    boost::mutex& global_out_mutex();}

#endif	/* _CONSTDEF_H */

