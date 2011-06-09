/* 
 * File:   systemutil.h
 * Author: Serg
 *
 * Created on 27 Апрель 2010 г., 20:05
 */

#ifndef _DVNCI_KRNL_SYSTEMUTIL_H
#define	_DVNCI_KRNL_SYSTEMUTIL_H

#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/error.h>
#include <kernel/templ.h>


namespace dvnci {


    static const size_t  ADDITINAL_STATIC_MAPSIZIZE = 20000;

    class executable  {
    public:

        executable() :  terminate_var(true), init_(false) {}

        virtual ~executable() {};

        virtual bool operator()() = 0 ;

        virtual void terminate() {
            terminate_var = false;}

        bool terminated() volatile {
            return (!terminate_var);}

        bool init() {
            if (init_) return true;
            init_ = initialize();
            return init_;}

        bool uninit() {
            if (init_) init_ = (!uninitialize());
            return (!init_);}

    protected:

        void resetinit() {
            init_ = false;}

        virtual bool    initialize() = 0;
        virtual  bool   uninitialize() = 0;
        volatile bool   terminate_var;

    private:
        bool init_;} ;

    typedef callable_shared_ptr<executable>   executable_ptr;
    
    

    //   refcounter_templ

    template<typename T>
    class refcounter_templ {
        typedef T                                      interface_type;
        typedef membase_sync_ptr_tmpl<interface_type>  interface_type_ptr;

    public:

        refcounter_templ(interface_type_ptr interf, bool act = false) : intf(interf), active_(act) {}

        virtual ~refcounter_templ() {
            active(false);}

        void add(indx id) {
            if (countermap.find(id) == countermap.end()) {
                countermap.insert(id);
                if ((active_) && (intf) && (intf->exists(id))) intf->incref(id);}}

        void remove(indx id) {
            if (countermap.find(id) != countermap.end()) {
                countermap.erase(id);
                if ((active_) && (intf) && (intf->exists(id))) intf->decref(id);}}

        void active(bool val) {
            if (val != active_) {
                setallactive(val);
                active_ = val;}}

        bool active() const {
            return active_;}

        void clear() {
            countermap.clear();}

        bool index_included(indx id) {
            return (countermap.find(id) != countermap.end());}

        const indx_set& indexes() const {
            return countermap;}

    private:

        void setallactive(bool val) {
            if (intf) {
                for (indx_set::const_iterator it = countermap.begin(); it != countermap.end(); ++it) {
                    if (intf->exists(*it)) {
                        if (val)
                            intf->incref(*it);
                        else
                            intf->decref(*it);}}}}

        interface_type_ptr intf;
        bool               active_;
        indx_set           countermap;} ;


    ///////////////////////////////////////////////////////////
        
        

    struct messagestruct;

    typedef std::deque<messagestruct> messqueue;

    typedef void (*service_func)( num32  mess, indx id, indx some);

#pragma  pack(push,4)

    typedef struct messagestruct {

        messagestruct() {};

        messagestruct(qumsgtype  mes, indx ids, indx som) :  mess(mes), id(ids), some(som) {}
        qumsgtype      mess;
        indx           id;
        indx           some;}  *pmessagestruct;

#pragma  pack(pop)

    class filestream {
    public:

        /**
         * Существует ли файл
         * @param path путь
         * @return существование файла или директории
         */
        static bool exists(const fspath& filename) {
            //boost::filesystem::path p(filename.string().c_str(),  boost::filesystem::native );
            return boost::filesystem::exists(filename);}

        /**
         * Является ли строка директорией
         * @param path предпологаемый путь
         * @return является ли строка валидной директорией
         */
        static bool isdirectory(const fspath& path) {
            return ((exists(path.string().c_str())) && (boost::filesystem::is_directory(path.string().c_str())));}

        /**
         * Размер файла
         * @param filename Имя файла
         * @return размер файла
         */
        static size_t filesize(const fspath& filename);

        /**
         * Чтение файла в память
         * @param filename Имя файла
         * @param addr начальный адрес пмамяти для записи
         * @param offset  смещение относительно начала файла
         * @param size размер отображаемого блока, 0 - весь файл с учетом смещения
         * @return число прочитанных байт
         */
        static size_t read(const fspath& filename, void* addr, size_t offset = 0, size_t size = 0);

        /**
         * Запись памяти в файл
         * @param filename Имя файла
         * @param addr начальный адрес пмамяти для записи
         * @param offset  смещение относительно начала
         * @param size размер отображаемого блока, 0 - весь файл с учетом смещения
         * @return число записанных байт
         */
        static size_t write(const fspath& filename, const void* addr, size_t offset = 0, size_t size = 0);} ;

    /**
     * Работа с разделяемой памятью и файлолами отображаемыми в
     * память
     */

    class util_memory {
    public:

        util_memory(std::string name, size_t sz = 0xFFFFFF) : isnew_(false), mapname_(name), size_(sz) {}

        virtual ~util_memory() {}

        bool isnew() const {
            return isnew_;}

        virtual size_t size() const {
            return size_;}

        virtual size_t capacity() const {
            return size_;}

        virtual void* get_address() {
            return 0;}

        std::string mapname() const {
            return mapname_;}



    protected:

        void remove_main();

        static bool map(boost::interprocess::mapped_region& rgn, std::string name, size_t size = 0xFFFFFF );

        /**
         * создание именованого сегмента разделяемой памяти
         * @param name имя сегмента
         * @param size размер сегмента
         * @param isnew был ли сегмент создан заново или открыт другим процессом
         * @return успешност выполнения
         */
        static bool map_utl(boost::interprocess::mapped_region& rgn, std::string name,  bool& isnew, size_t size = 0xFFFFFF);

        bool        isnew_;
        std::string mapname_;
        size_t      size_;} ;

    typedef boost::shared_ptr<util_memory> util_memory_ptr;


    //////////////////////////////////////////////////////

    class util_static_size_shmemory : public util_memory {

        struct intern_header {

            intern_header() : size(0) {};
            unum64 size;
            interproc_mutex memlock;} ;

    public:

        util_static_size_shmemory(std::string name, size_t sz) : util_memory(name, (sz + ADDITINAL_STATIC_MAPSIZIZE) ) {
            init_region();}

        virtual ~util_static_size_shmemory() {}

        virtual void* get_address() {
            return static_cast<void*> (static_cast<intern_header*> (get_address_internal()) + 1);}

        virtual size_t size() const {
            return size_internal();}

        virtual size_t capacity() const {
            return size_internal();}

        interproc_mutex& memlock() {
            return (static_cast<intern_header*> (get_address_internal())->memlock);}


    protected:

        void size_internal(size_t vl) {
            static_cast<intern_header*> (mainmem.get_address())->size = static_cast<unum64> (vl);}

        size_t size_internal() const {
            return static_cast<size_t> (static_cast<intern_header*> (mainmem.get_address())->size);}

        void* get_address_internal() {
            return mainmem.get_address();}

        bool init_region();

        intern_header*                     intern_hdr;
        boost::interprocess::mapped_region mainmem;} ;

    typedef boost::shared_ptr<util_static_size_shmemory> util_static_size_shmemory_ptr;


    ///////////////////////////////////////////////////////////////

    class util_filemapmemory : public util_memory {

        struct intern_header {

            intern_header() : size(0) {};
            unum64          size;
            interproc_mutex memlock;
            interproc_mutex filelock;} ;

    public:

        util_filemapmemory(const std::string& name, const fspath& file, size_t sz);

        virtual ~util_filemapmemory() {}

        virtual void* get_address() {
            return static_cast<void*> (static_cast<intern_header*> (get_address_internal()) + 1);}

        virtual size_t size() const {
            return size_internal();}

        fspath filename() const {
            return filename_;}

        virtual size_t capacity() const {
            return size_internal();}

        interproc_mutex& memlock() {
            return (static_cast<intern_header*> (get_address_internal())->memlock);}

        interproc_mutex& filelock() {
            return (static_cast<intern_header*> (get_address_internal())->filelock);}

        size_t writetofile(size_t offset = 0, size_t sz = 0);

        size_t writestructtofile(const void* dt, size_t offset = 0, size_t sz = 0);
        
        size_t readstructfromfile(void* dt, size_t offset = 0 , size_t sz = 0);

        size_t filesize() const {
            return filestream::filesize(filename().string());}

        size_t writenosave_to_end(size_t sz);


    protected:

        void* get_address_internal() {
            return mainmap.get_address();}

        size_t size_internal() const {
            return static_cast<size_t> (static_cast<intern_header*> (mainmap.get_address())->size);}

        void size_internal(size_t vl) {
            static_cast<intern_header*> (mainmap.get_address())->size = static_cast<unum64> (vl);}

        bool init_region() {
            map_utl( mainmap, mapname() , isnew_ , size_);
            return mainmap.get_address();}

        fspath                             filename_;
        intern_header*                     intern_hdr;
        boost::interprocess::mapped_region mainmap;} ;

    typedef boost::shared_ptr<util_filemapmemory> util_filemapmemory_ptr;


    /////////////////////////////////////////////////////////////////////////////////

    class staticmemorymap {
    public:

        staticmemorymap(const std::string& mapname, size_t size = 0xFFFFFF);

        virtual ~staticmemorymap() {};

        bool isnew() const {
            return utilptr->isnew();}

        virtual size_t mapsize() const {
            return utilptr->size();}

        virtual std::string mapname() const {
            return utilptr->mapname();}

    protected:

        void* const data() {
            return utilptr->get_address();};

        void* const data() const {
            return utilptr->get_address();};

        util_static_size_shmemory_ptr utilptr;} ;

    typedef boost::shared_ptr<staticmemorymap> staticmemorymap_ptr;

    class filememorymap {
    public:

        filememorymap(const fspath& filepath, const std::string& mapname, size_t exsize);

        virtual ~filememorymap() {};

        bool isnew() const {
            return utilptr->isnew();}

        std::string mapname() const {
            return utilptr->mapname();}

        fspath filename() const {
            return utilptr->filename();}

        size_t mapsize() const {
            return utilptr->capacity();}

    protected:

        void* const data() {
            return utilptr->get_address();};

        void* const data() const {
            return utilptr->get_address();};

        size_t capacity() const {
            return utilptr->capacity();}

        size_t filesize() const {
            return utilptr->filesize();}

        util_filemapmemory_ptr utilptr;} ;

    typedef boost::shared_ptr<filememorymap>   filememorymap_ptr;



    /////////////////////////////////////////////////////////////////////

    class proccess_queues {
    public:

        static  std::string get_mq_name(guidtype val) {
            return val >= 0 ? (NS_MESSAGEQUEUE_NAME + to_str(val)) : "";}

        static  mq_class*  getqueue(guidtype val, bool create , size_t sz = 1000);

        static  void   removequeue(guidtype val);

        static  bool   try_send(mq_class* queue, qumsgtype  mess, indx id, num32 some = 0);

        static  bool   try_recieve(mq_class* queue, messagestruct& msg);} ;


    //////////////////////////////////////////////////////////////////////////////////     

    class stringed_filterclass {
    public:
        
        static std::string GROUP_CRITERIA;
        static std::string NAME_CRITERIA;
        static std::string BIND_CRITERIA;
        static std::string COMMENT_CRITERIA;
        static std::string TYPEGROUP_CRITERIA;
        static std::string TYPERT_CRITERIA;

        stringed_filterclass(std::string filter_) {
            criteria_ = filter_;
            readcriterias();}

        virtual ~stringed_filterclass() {};

        std::string criterias();

        bool iscriteria(const std::string name) {
            return (filtermap.find(name) != filtermap.end());}

        bool isidxcriteria(const std::string name) {
            return (filterkeymap.find(name) != filterkeymap.end());}
        void setcriteria(const std::string name, std::string val);
        void addidxcriteria(const std::string name, const indx val);
        void removeidxcriteria(const std::string name, const indx val);

        void clearidxcriteria(const std::string name) {
            if (filterkeymap.find(name) != filterkeymap.end()) filterkeymap.erase(filterkeymap.find(name));}

        std::string criteria(const std::string name) {
            return (filtermap.find(name) != filtermap.end()) ?  filtermap.find(name)->second : "";}

        indx_set* idxcriteria(const std::string name) {
            return isidxcriteria(name) ? &filterkeymap.find(name)->second : NULL;}
        bool included(const std::string name, std::string val);
        bool includedidx(const std::string name, indx val);

        bool isEnable() {
            return ((filtermap.size() > 0) || (filterkeymap.size() > 0));}
        void clearcriteria();

    private:

        void setidxcriteria(const std::string name, const indx_set& val);
        void readcriteria(const std::string name);
        void readidxcriteria(const std::string name);
        void readcriterias();
        std::string findCriteria(std::string name);
        void getkeyswithstring(const std::string str_, indx_set& set_);
        void setkeyswithstring(std::string& str_, const indx_set& set_);

        filtered_map    filtermap;
        std::string     criteria_;
        filteredkey_map filterkeymap;} ;}

#endif	/* _SYSTEMUTIL_H */

