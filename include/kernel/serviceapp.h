
#ifndef _DVNCI_KRNL_SERVICEAPP_H
#define _DVNCI_KRNL_SERVICEAPP_H

#include <kernel/memfile.h>
#include <kernel/systemutil.h>

namespace dvnci {
    


    struct servicearraystruct {
        appidtype serviceid;
        std::string servicename;} ;

    const  int SERVICE_COUNT = 9;
    
    const size_t  DEMON_EXECUTE_STRSIZE = 512;
    
    

    /*const  servicearraystruct  SERVICE_ARRAY[] = {{ NS_ADMIN_SERVICE, NS_ADMIN_SERVICE_NAME} ,
                                                  { NS_PERSISTENCE_SERVICE, NS_PERSISTENCE_SERVICE_NAME} ,
                                                  { NS_SYSTEM_SERVICE, NS_SYSTEM_SERVICE_NAME},
                                                  { NS_NET_SERVICE, NS_NET_SERVICE_NAME},
                                                  { NS_OPC_SERVICE, NS_OPC_SERVICE_NAME},
                                                  { NS_DDE_SERVICE, NS_DDE_SERVICE_NAME},
                                                  { NS_MODBUS_SERVICE, NS_MODBUS_SERVICE_NAME},
                                                  { NS_KOYO_SERVICE, NS_KOYO_SERVICE_NAME},
                                                  { NS_LGKA_SERVICE, NS_LGKA_SERVICE_NAME}};*/
    
    

    int  startmain(int argc, char** argv);    
    bool installservice(const std::string& pathservice, const std::string& nameservice);
    bool uninstallservice(const std::string& nameservice);    
        
        
        
        

    
    

    typedef std::pair<appidtype, std::string >                      appidtype_stdstr_pair;
    typedef std::map< appidtype, std::string, std::less<appidtype>,
                            std::allocator<appidtype_stdstr_pair > > appidtype_stdstr_map;



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

    

   
   struct demon_item{
       
        demon_item(appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF) :  appid_(app), starttype_(stt), status_(0), pid_(0) {
            name(nm);}
        
        demon_item() : appid_(0), starttype_(SERVICE_STATUS_NODEF), status_(SERVICE_RUNSTATE_OFF), pid_(0) {
            name("");}
        
        ~demon_item(){}

        
        void appid(appidtype val) {
            appid_ = val;}

        appidtype appid() const {
            return appid_;}
        
        void pid(int val) {
            pid_ = val;}

       int pid() const {
            return pid_;}
        
        void starttype(int val) {
            starttype_ = val;}

        int starttype() const {
            return starttype_;} 
        
        void status(int val) {
            status_ = val;}

        int status() const {
            return status_;} 
        
        
        void name(const std::string& val) {
            string_to_pascalstr((void*) &name_, val, DEMON_EXECUTE_STRSIZE);}

        std::string name() const {
            return pascalstr_to_string((void*) (&name_));}
        
        demon_item get_for_write_to_file(){
            demon_item tmp =*this;
            tmp.pid_=0;
            tmp.status_=SERVICE_STATUS_NODEF;
            return tmp;}
        
        friend bool operator<(const demon_item& ls, const demon_item& rs){
            return ls.appid_<rs.appid_;}
        
        friend bool operator==(const demon_item& ls, const demon_item& rs){
            return ls.appid_==rs.appid_;}
        
        
   private:
       appidtype   appid_;
       num8        name_[DEMON_EXECUTE_STRSIZE + 2]; 
       int         starttype_;
       int         status_;
       int         pid_;};
       
   struct demon_header { 
       
      demon_header(size_t cnt = 0) : count_(cnt){} 
       
      void count(size_t val) {
            count_ = val;}

      size_t count() const {
            return count_;}
       
   private:
       size_t      count_;};     
       
       
    typedef struct demon_proccess {
        
        typedef demon_header head_type;
        typedef demon_item   item_type;

        demon_header header;
        demon_item   items[];} *pdemon_proccess;

    
    


    class servicemanager : protected filememorymap {


        typedef demon_proccess                                  structs_type;
        typedef demon_proccess * const                          structs_type_ptr;
        typedef demon_proccess::head_type                       header_type;
        typedef demon_proccess::head_type * const               header_type_ptr;

    public:

        typedef demon_proccess::item_type                struct_type;
        typedef demon_proccess::item_type const * const  const_struct_type_ptr;
        typedef demon_proccess::item_type *              struct_type_ptr;
        typedef dvnci::indx                              size_type;
        
        static  const size_type    npos = dvnci::npos;
        
        

        servicemanager(const fspath& filepath, const fspath& strtpath="") : 
        filememorymap(filepath/ DEMONENTRY_FILE_NAME , DEMONENTRY_MAP_NAME , sizeof(demon_item)* 200) ,
        starttpath_(strtpath.string().empty() ? filepath : strtpath){
             ;}

        virtual ~servicemanager() {}
        
        fspath starttpath() const {
            return starttpath_;}
        
        ns_error signature(iteminfo_map& map_){
            INP_SHARE_LOCK(memlock());
            map_.clear();
            for (struct_type_ptr it=begin();it!=end();++it){
                if (it->appid()){
                    name_with_type tmp_inf(it->name(), NT_SERVICE , static_cast<tagtype>(it->status()));
                map_.insert(iteminfo_pair(static_cast<indx> (it->appid()), tmp_inf));}
            return NS_ERROR_SUCCESS;}}
        
        
        size_type count() const {
            INP_SHARE_LOCK(memlock());
            return static_cast<size_type> ((*(structs_type_ptr) data()).header.count());}          
        
        struct_type_ptr operator[] (appidtype app)   {
            size_type it=find(app);
            return ((it!=npos) && (app)) ? &((structs_type_ptr) data())->items[it] : end();}
        

        bool exists(appidtype app) const {
            size_type it=find(app);
            return ((app) && (it!=npos)) ;}
        
       
        std::string name(appidtype app) const {
            INP_SHARE_LOCK(memlock());
            return exists(app) ? operator[](app)->name() : "";}
        
        int pid(appidtype app) const;
        
        void pid(appidtype app, int pd);  
        
        int starttype(appidtype app) const;
        
        void starttype(appidtype app, int stt);         
        
        int status(appidtype app) const; 
        
        void status(appidtype app, int sts);
        

        const_struct_type_ptr begin() const {
            return &static_cast<structs_type_ptr> (data())->items[0];};
            

        const_struct_type_ptr end() const {
            return &static_cast<structs_type_ptr> (data())->items[static_cast<size_type> ((*(structs_type_ptr) data()).header.count())];};
            
            
       interproc_mutex& memlock() const {
            return utilptr->memlock();};
            
       bool install_demon(appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF);
       
       bool uninstall_demon(appidtype app);  
       
       bool operation(appidtype app, int oper){
           if (exists(app)){
               return  operation_impl(app, oper);} 
           return false;}
       
       static void writezero(const fspath&  fpath) {
        demon_header inhdr;
        filestream::write(fpath / DEMONENTRY_FILE_NAME, (num8*) & inhdr, 0, sizeof (demon_header));}
       
       friend std::ostream & operator<<(std::ostream& os, servicemanager& tbl){
           INP_SHARE_LOCK(tbl.memlock());
           for (struct_type_ptr it=tbl.begin();it!=tbl.end();++it){
              std::cout  << (it->appid()!=0) << " appid: " << it->appid() << " name: " << it->name() << " pid: " << it->pid() 
                      << " starttype: " << it->starttype() << " status: " << it->status() << std::endl;}}


    protected:
        
        bool demon_fileexists(const std::string& fl){
            try{
            return boost::filesystem::exists( starttpath() / fl.c_str() );}
            catch(...){}
            return false;}
        
        std::string platformspec() const;
        
        
        bool operation_impl(appidtype app, int oper);
        

        struct_type_ptr begin()  {
            return &static_cast<structs_type_ptr> (data())->items[0];};
            

        struct_type_ptr end() {
            return &static_cast<structs_type_ptr> (data())->items[static_cast<size_type> ((*(structs_type_ptr) data()).header.count())];};
            
            
        void sort(){
            std::sort(begin(),end());} 
        
        size_type find(appidtype app) const{
            struct_type tmpfnd;
            tmpfnd.appid(app);
            const_struct_type_ptr it=std::find(begin(),end(), tmpfnd);
            return (it==end()) ? npos : static_cast<size_type>(it - begin());}     


        void initstruct(size_type id, appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF) {
            struct_type tmp(app, nm, stt);
            ((structs_type_ptr) data())->items[id] = tmp;}
        

        void uninitstruct(size_type id) {
            ((structs_type_ptr) data())->items[id].appid(0);}
        
        
        
        virtual struct_type struct_for_write(size_type id) {         
            if ((id < static_cast<size_type> ((*(structs_type_ptr) data()).header.count()))) 
                return ((structs_type_ptr) data())->items[id].get_for_write_to_file();
            else
                return struct_type();}
                     
        
        void count(size_t value) {
            (*(structs_type_ptr) data()).header.count(value);}
        

        const_struct_type_ptr operator[] (size_type id) const {
            return id < static_cast<size_type> ((*(structs_type_ptr) data()).header.count()) ? &((structs_type_ptr) data())->items[id] : end();}
        
        
        size_t itemsoffset(size_type id) {
            return (sizeof (header_type) + id * sizeof (struct_type));}


        size_type add(appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF) {
            if (app<=0) return npos;
            INP_EXCLUSIVE_LOCK(memlock());
            if (!static_cast<size_type> ((*(structs_type_ptr) data()).header.count())){
                count(1);
                initstruct(0, app, nm, stt);
                writetofile();
                return 0;}
            else{
                if (find(app)!=npos)
                    return npos;
                if (!((structs_type_ptr) data())->items[0].appid()){
                   initstruct(0, app, nm, stt);
                   sort();
                   writetofile();
                   return find(app);}
                else{
                   count(((*(structs_type_ptr) data()).header.count())+1);
                   initstruct(((*(structs_type_ptr) data()).header.count() - 1), app, nm, stt);
                   sort();
                   writetofile();
                   return find(app);}}
            
            return npos;}
        
        size_type remove(appidtype app) {
            if (app<=0) return npos;
            INP_EXCLUSIVE_LOCK(memlock());
            size_type it=find(app);
            if (it==npos)
                    return npos;
            uninitstruct(it);
            struct_type tmpfnd;
            size_type newcnt = static_cast<size_type>(std::remove(begin(),end(), tmpfnd)-begin());
            count(newcnt);
            sort();
            writetofile();
            return it;}
        


        void writetofile(size_type id = npos) { 
            if (id != npos) {
                struct_type tmpnew = struct_for_write(id);
                writestructtodisk(tmpnew, id);}
            else{
                utilptr->writetofile(0,itemsoffset(static_cast<size_type> ((*(structs_type_ptr) data()).header.count())));}}
         
        size_t writestructtodisk(const struct_type& dst, size_type id) {
            return utilptr->writestructtofile((const void*) &dst, itemsoffset(id), sizeof (struct_type));}
    
       fspath starttpath_;};  
       
       
            
     typedef boost::shared_ptr<servicemanager> servicemanager_ptr;
     
     
     
     
     
     struct demon_entry_factory{
         
         static servicemanager_ptr build(const fspath& filepath){
             try{
                 return servicemanager_ptr(new servicemanager(filepath));}
             catch(...){}
                 return servicemanager_ptr();}
         
          static bool createstorige(const fspath& filepath){
             try{
                 if (boost::filesystem::exists(filepath / DEMONENTRY_FILE_NAME))
                     return true;
                 servicemanager::writezero(filepath);
                 return (boost::filesystem::exists(filepath / DEMONENTRY_FILE_NAME));}
             catch(...){}
                 return false;}
          
          static bool exists(const fspath& filepath){
             try{
                 if (boost::filesystem::exists(filepath / DEMONENTRY_FILE_NAME))
                     return true;}
             catch(...){}
                 return false;}};

}

#endif
