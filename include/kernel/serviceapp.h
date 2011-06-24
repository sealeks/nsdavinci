
#ifndef _DVNCI_KRNL_SERVICEAPP_H
#define _DVNCI_KRNL_SERVICEAPP_H

#include <kernel/memfile.h>
#include <kernel/systemutil.h>

namespace dvnci {
    


    struct servicearraystruct {
        appidtype   serviceid;
        std::string servicename;} ;

    
    const size_t  DEMON_EXECUTE_STRSIZE = 512;

    int  startmain(int argc, char** argv);    
    bool installservice(appidtype app, const std::string& nameservice);
    bool uninstallservice(appidtype app);    
        


    typedef std::pair<appidtype, std::string >                      appidtype_stdstr_pair;
    typedef std::map< appidtype, std::string, std::less<appidtype>,
                            std::allocator<appidtype_stdstr_pair > > appidtype_stdstr_map;


    extern std::string                  DVNCI_SERVICE_NAME;
    extern dvnci::appidtype             DVNCI_SERVICE_APPID;
    
    extern executable_ptr               mainserv;
    

    fspath       FULL_EXEC_PATH(const fspath& fl="");
    fspath       FULL_EXEC_DIR(const fspath& fl="");
    std::string  EXEC_FILE(const std::string& fl="");




    int serviceargumentparser(int argc, char** argv);
	int appargumentparser(int argc, char** argv);
    int getserviceoperation(std::string val);

    bool startservice();
    bool stopservice();

    

   
   struct demon_item{
       
        static const int NO_WAIT_STATE = 0;
        static const int RUN_WAIT_STATE = 1;
        static const int TERM_WAIT_STATE = 2;
        static const int RST_WAIT_STATE = 3;
       
        demon_item(appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF) :  appid_(app),
        starttype_(stt), status_(0), pid_(0), waitstate_(0) {
            name(nm);}
        
        demon_item() : appid_(0), starttype_(SERVICE_STATUS_NODEF), 
        status_(SERVICE_RUNSTATE_OFF), pid_(0),  waitstate_(0) {
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
            starttype_ = ((val<SERVICE_RUNSTATE_NODEF) || (val>SERVICE_RUNSTATE_BOOT)) ? 0 : val;}

        int starttype() const {
            return ((starttype_<SERVICE_RUNSTATE_NODEF) || (starttype_>SERVICE_RUNSTATE_BOOT)) ? 0 : starttype_;} 
        
        void status(int val) {
            status_ = (val & 0x3);}

        int status() const {
            return (status_& 0x3);} 
        
        void waitstate(int val) {
            waitstate_ = (val & 0x3);}

        int waitstate() const {
            return (waitstate_& 0x3);}         
        
        
        void name(const std::string& val) {
            string_to_pascalstr((void*) &name_, val, DEMON_EXECUTE_STRSIZE);}

        std::string name() const {
            return pascalstr_to_string((void*) (&name_));}
        
        demon_item get_for_write_to_file(){
            demon_item tmp =*this;
            tmp.pid_=0;
            tmp.status_=SERVICE_STATUS_NODEF;
            tmp.status_=0;
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
       int         pid_;
       int         waitstate_;};
       
   struct demon_header { 
       
      demon_header(size_t cnt = 0) : count_(cnt), monitor_(0) {} 
       
      void count(size_t val) {
            count_ = val;}

      size_t count() const {
            return count_;}
      
      void incmonitor() {
            monitor_++;}

      int monitor() const {
            return monitor_;}
       
   private:
       size_t      count_;
       int         monitor_;};     
       
       
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

        typedef demon_proccess::item_type                       struct_type;
        typedef demon_proccess::item_type const * const         const_struct_type_ptr;
        typedef demon_proccess::item_type *                     struct_type_ptr;
        typedef dvnci::indx                                     size_type;
        
        static  const size_type    npos = dvnci::npos;
        
        

        servicemanager(const fspath& filepath, const fspath& strtpath="");

        virtual ~servicemanager() {}
        
        fspath starttpath() const {
            return starttpath_;}
                 
        ns_error signature(iteminfo_map& map_);
        
        size_type count() const {
            INP_SHARE_LOCK(memlock());
            return static_cast<size_type> ((*(structs_type_ptr) data()).header.count());}
        
        int monitor() const{
            INP_SHARE_LOCK(memlock());
            return ((*(structs_type_ptr) data()).header.monitor());}        
            

        bool exists(appidtype app) const {
            size_type it=find(app);
            return ((app) && (it!=npos)) ;}
        
       
        std::string name(appidtype app) const;
        
        std::string fullpath(appidtype app) const;
        
        int pid(appidtype app) const;
        
        void pid(appidtype app, int pd);  
        
        int starttype(appidtype app) const;
        
        void starttype(appidtype app, int stt);         
        
        int status(appidtype app) const; 
        
        void status(appidtype app, int sts);
        
        int waitstate(appidtype app) const{
            INP_SHARE_LOCK(memlock());
            return exists(app) ? operator[](app)->waitstate() : 0;}
        
    
        void waitstate(appidtype app, int ws);
        
        const_struct_type_ptr begin() const {
            return &static_cast<structs_type_ptr> (data())->items[0];};
            
        const_struct_type_ptr end() const {
            return &static_cast<structs_type_ptr> (data())->items[static_cast<size_type> 
                    ((*(structs_type_ptr) data()).header.count())];};
                     
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
              return std::cout  << (it->appid()!=0) << " appid: " << it->appid() << " name: " << it->name() << " pid: " << it->pid() 
                      << " starttype: " << it->starttype() << " status: " << it->status() << std::endl;}
	      return os;}


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
        

        const_struct_type_ptr operator[] (appidtype app) const {
            size_type it=find(app);
            return ((it!=npos) && (it < static_cast<size_type> ((*(structs_type_ptr) data()).header.count()))) ?
                &((structs_type_ptr) data())->items[it] : end();}
        
        
        struct_type_ptr operator[] (appidtype app)   {
            size_type it=find(app);
            return ((it!=npos) && (app)) ? &((structs_type_ptr) data())->items[it] : end();}
        
        
        size_t itemsoffset(size_type id) {
            return (sizeof (header_type) + id * sizeof (struct_type));}


        size_type add(appidtype app, const std::string& nm, int stt = SERVICE_RUNSTATE_OFF);
        
        size_type remove(appidtype app);
        
        void writeheader();

        void writetofile(size_type id = npos);
         
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
