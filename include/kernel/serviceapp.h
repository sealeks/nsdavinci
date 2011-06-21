
#ifndef _DVNCI_KRNL_SERVICEAPP_H
#define _DVNCI_KRNL_SERVICEAPP_H

#include <kernel/memfile.h>
#include <kernel/systemutil.h>

namespace dvnci {
    


    struct servicearraystruct {
        servidtype serviceid;
        std::string servicename;} ;

    const  int SERVICE_COUNT = 9;
    
    

    const  servicearraystruct  SERVICE_ARRAY[] = {{ NS_ADMIN_SERVICE, NS_ADMIN_SERVICE_NAME} ,
                                                  { NS_PERSISTENCE_SERVICE, NS_PERSISTENCE_SERVICE_NAME} ,
                                                  { NS_SYSTEM_SERVICE, NS_SYSTEM_SERVICE_NAME},
                                                  { NS_NET_SERVICE, NS_NET_SERVICE_NAME},
                                                  { NS_OPC_SERVICE, NS_OPC_SERVICE_NAME},
                                                  { NS_DDE_SERVICE, NS_DDE_SERVICE_NAME},
                                                  { NS_MODBUS_SERVICE, NS_MODBUS_SERVICE_NAME},
                                                  { NS_KOYO_SERVICE, NS_KOYO_SERVICE_NAME},
                                                  { NS_LGKA_SERVICE, NS_LGKA_SERVICE_NAME}};
    
    

    struct sevicestatus {

        sevicestatus() {
            dysplayname = "nodef";
            path = "";
            runstate = SERVICE_RUNSTATE_NODEF;
            servicetype = 0;
            startname = "";}

        int runstate;
        int servicetype;
        std::string dysplayname;
        std::string path;
        std::string startname;} ;
        
    int serviceargumentparser(int argc, char** argv);       
        
        
        
        
    int  startmain();
    bool installservice(const std::string& pathservice, const std::string& nameservice);
    bool uninstallservice(const std::string& nameservice);
    bool startservice(const std::string& nameservice);
    bool stopservice(const std::string& nameservice);
    bool serviceconfig(const std::string& nameservice, sevicestatus& info);
    bool setserviceconfig(const std::string& nameservice, sevicestatus& info);
    int  servicestatus(const std::string& nameservice);
    
    

    typedef std::pair<servidtype, std::string >                      servidtype_stdstr_pair;
    typedef std::map< servidtype, std::string, std::less<servidtype>,
    std::allocator<servidtype_stdstr_pair > > servidtype_stdstr_map;



    static std::string applicationservicepath;
    static std::string applicationservicename;
    static std::string applicationservicespec;
    static boost::filesystem::path boostapplicationpath;


    extern std::string                  dvnciservicename;
    extern executable_ptr               mainserv;


    int serviceargumentparser(int argc, char** argv);
    int getserviceoperation(std::string val);

    bool startservice();
    bool stopservice();

    
    

    class servicemanager {
    public:

        servicemanager();

        ~servicemanager() {}

        ns_error signature(iteminfo_map& map_);

        bool get_property(servidtype id, sevicestatus& val);

        bool set_property(servidtype id, sevicestatus& val);

        int  status(servidtype id);

        bool operation(servidtype id, int oper);

        bool exists(servidtype id);

    private:

        bool get_property_impl(servidtype id, sevicestatus& val);
        
        bool set_property_impl(servidtype id, sevicestatus val);

        servidtype_stdstr_map servicemap;} ;}

#endif
