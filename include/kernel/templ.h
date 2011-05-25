/* 
 * File:   template.h
 * Author: Serg
 *
 * Created on 13 Август 2010 г., 2:49
 */

#ifndef _DVNCI_KRNL_TEMPLATE_H
#define	_DVNCI_KRNL_TEMPLATE_H

#include <kernel/constdef.h>


template<typename maintype>
class sync_share_ptr_tmpl {

    typedef typename boost::shared_ptr<maintype>      internal_sh_ptr;
    typedef typename boost::shared_ptr<boost::mutex>  mutex_ptr;
    typedef          boost::mutex                     &mutex_ref;

public:

    sync_share_ptr_tmpl(){
       mut_ptr = dvnci::mutex_ptr( new boost::mutex());};

    virtual ~sync_share_ptr_tmpl(){};

    sync_share_ptr_tmpl(maintype* src){
       sh_ptr=internal_sh_ptr(src);
       mut_ptr = dvnci::mutex_ptr( new boost::mutex());}

    sync_share_ptr_tmpl(const sync_share_ptr_tmpl& val){
       sh_ptr=val.sh_ptr;
       mut_ptr=val.mut_ptr;}

    sync_share_ptr_tmpl& operator=(const sync_share_ptr_tmpl& val){
       sh_ptr=val.sh_ptr;
       mut_ptr=val.mut_ptr;
       return *this;}

    maintype* ptr(){
        return sh_ptr.get();}

    maintype& operator* () const {
        return sh_ptr.operator* ();}

    maintype* operator-> () const{
        return sh_ptr.operator ->();}

    maintype* get() const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    operator mutex_ref(){
         return *mut_ptr;}

    void reset(){
        sh_ptr.reset();}

    void swap(sync_share_ptr_tmpl& other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}

protected:
    internal_sh_ptr     sh_ptr;
    mutex_ptr           mut_ptr;};



template<typename maintype>
class intrusive_sync_share_ptr_tmpl {

    typedef typename boost::shared_ptr<maintype>  internal_sh_ptr;
    typedef          boost::mutex                 &mutex_ref;

public:

    intrusive_sync_share_ptr_tmpl(){};

    virtual ~intrusive_sync_share_ptr_tmpl(){ if (!(sh_ptr.use_count()-1)) {DEBUG_STR_DVNCI(INTUSIVE_DESTRUCTOR);};};

    intrusive_sync_share_ptr_tmpl(maintype* src){
       sh_ptr=internal_sh_ptr(src);}

    intrusive_sync_share_ptr_tmpl(const intrusive_sync_share_ptr_tmpl& val){
      sh_ptr=val.sh_ptr;}

    intrusive_sync_share_ptr_tmpl& operator=(const intrusive_sync_share_ptr_tmpl& val){
       sh_ptr=val.sh_ptr;
       return *this;}

    maintype* ptr(){
        return sh_ptr.get();}

    maintype& operator* () const {
        return sh_ptr.operator* ();}

    maintype* operator-> () const{
        return sh_ptr.operator ->();}

    maintype* get() const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    operator mutex_ref(){
         return *(sh_ptr->mtx_internal());}

    void reset(){
        sh_ptr.reset();}

    void swap(intrusive_sync_share_ptr_tmpl& other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}

protected:
    internal_sh_ptr sh_ptr;};



namespace dvnci{
/// шаблон обертка умного указателя для  базы
template<typename maintype>
class membase_sync_ptr_tmpl {

    typedef typename  boost::shared_ptr<maintype>        internal_sh_ptr;
    typedef typename  maintype::struct_type_ptr          type_ptr;
    typedef typename  maintype::struct_type_ptr const    const_type_ptr;
    typedef           boost::mutex                       &mutex_ref;
    
public:

    membase_sync_ptr_tmpl(){
        mut_ptr = mutex_ptr( new boost::mutex());};

    virtual ~membase_sync_ptr_tmpl(){};

    membase_sync_ptr_tmpl(maintype* src){
       sh_ptr=internal_sh_ptr(src);
       mut_ptr = dvnci::mutex_ptr( new boost::mutex());}

    membase_sync_ptr_tmpl(const membase_sync_ptr_tmpl& val){
      sh_ptr=val.sh_ptr;
      mut_ptr=val.mut_ptr;}

    membase_sync_ptr_tmpl& operator=(const membase_sync_ptr_tmpl& val){
       sh_ptr=val.sh_ptr;
       mut_ptr=val.mut_ptr;
       return *this;}

    maintype* ptr(){
        return sh_ptr.get();}

    type_ptr    operator[]  (indx id){
                            return ((sh_ptr) && (sh_ptr->operator[](id))) ? sh_ptr->operator[](id) : 0;}

    bool        operator[]  (const std::string& vl){
                            return ((sh_ptr) && (sh_ptr->operator[](vl)));}

    indx        operator()(const std::string& vl){
                            return ((sh_ptr) && (sh_ptr->operator[](vl))) ? sh_ptr->operator()(vl) : npos;}

    maintype& operator* () const {
        return sh_ptr.operator* ();}

    maintype* operator-> () const{
        return sh_ptr.operator ->();}

    maintype* get() const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    operator mutex_ref(){
         return *mut_ptr;}

    void reset(){
        sh_ptr.reset();}

    void swap(membase_sync_ptr_tmpl& other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}
    
protected:
    internal_sh_ptr     sh_ptr;
    mutex_ptr           mut_ptr;
};



template<typename maintype>
class membase_ptr_tmpl {

    typedef typename boost::shared_ptr<maintype>  internal_sh_ptr;
    typedef  typename maintype::struct_type_ptr   type_ptr;

public:

    membase_ptr_tmpl(){};

    virtual ~membase_ptr_tmpl(){};

    membase_ptr_tmpl(maintype* src){
       sh_ptr=internal_sh_ptr(src);}

    membase_ptr_tmpl(const membase_ptr_tmpl& val){
      sh_ptr=val.sh_ptr;}

    membase_ptr_tmpl& operator=(const membase_ptr_tmpl& val){
       sh_ptr=val.sh_ptr;
       return *this;}

    maintype* ptr(){
        return sh_ptr.get();}

    type_ptr  operator[]  (indx id){
                            return ((sh_ptr) && (sh_ptr->exists(id))) ? sh_ptr->operator[](id) : 0;}

    bool      operator[]  (const std::string& vl){
                            return ((sh_ptr) && (sh_ptr->exists(vl))) ? sh_ptr->operator[](vl) : 0;}

    indx        operator()(const std::string& vl){
                            return ((sh_ptr) && (sh_ptr->exists(vl))) ? sh_ptr->operator()(vl) : npos;}

    maintype& operator* () const {
        return sh_ptr.operator* ();}

    maintype* operator-> () const{
        return sh_ptr.operator ->();}

    maintype* get() const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    void reset(){
        sh_ptr.reset();}

    void swap(membase_ptr_tmpl& other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}


protected:
    internal_sh_ptr sh_ptr;
};

}

 /////////////////////////////////////////////////////////


template <typename T>
class callable_shared_ptr{
public:
    typedef typename boost::shared_ptr<T> sh_ptrtype;

    callable_shared_ptr(){};

    virtual ~callable_shared_ptr(){ if (!(sh_ptr.use_count()-1)) {DEBUG_STR_DVNCI(CALLABDLE__DESTRUCTOR);} };

    callable_shared_ptr(T* src){
       sh_ptr=sh_ptrtype(src);}

    callable_shared_ptr(const callable_shared_ptr& val){
      sh_ptr=val.sh_ptr;}

    sh_ptrtype ptr(){
        return sh_ptr;}

    void operator()(){
       sh_ptr->operator()();}

    callable_shared_ptr& operator=(const callable_shared_ptr& val){
       sh_ptr=val.sh_ptr;
       return *this;}

    T& operator* () const {
        return sh_ptr.operator* ();}

    T* operator-> () const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    void reset(){
        sh_ptr.reset();}

    void swap(callable_shared_ptr & other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}

    void terminate(){
       if (sh_ptr)  sh_ptr->terminate();}


 private:
    sh_ptrtype sh_ptr;};


    /////////////////////////////////////////////////////////


template <typename T>
class intrusivesync_callable_shared_ptr{

    typedef          boost::mutex                 &mutex_ref;

public:
    typedef typename boost::shared_ptr<T> sh_ptrtype;

    intrusivesync_callable_shared_ptr(){};

    virtual ~intrusivesync_callable_shared_ptr(){
        if (!(sh_ptr.use_count()-1)){DEBUG_STR_DVNCI(INTRUSIVE_SYNC_CALLABDLE__DESTRUCTOR);}; };

    intrusivesync_callable_shared_ptr(T* src){
       sh_ptr=sh_ptrtype(src);}

    intrusivesync_callable_shared_ptr(const intrusivesync_callable_shared_ptr& val){
      sh_ptr=val.sh_ptr;}

    sh_ptrtype ptr(){
        return sh_ptr;}

    void operator()(){
       sh_ptr->operator()();}

    intrusivesync_callable_shared_ptr& operator=(const intrusivesync_callable_shared_ptr& val){
       sh_ptr=val.sh_ptr;
       return *this;}

    T& operator* () const {
        return sh_ptr.operator* ();}

    T* operator-> () const{
        return sh_ptr.operator ->();}

    operator bool(){
        return sh_ptr;}

    void reset(){
        sh_ptr.reset();}

    void swap(intrusivesync_callable_shared_ptr & other) {
       sh_ptr.swap(other.sh_ptr);}

    bool unique() const {
        return sh_ptr.unique();}

    long use_count() const {
        return sh_ptr.use_count();}

    void terminate(){
       if (sh_ptr)  sh_ptr->terminate();}

    operator mutex_ref(){
         return *(sh_ptr->mtx_internal());}


 private:
    sh_ptrtype sh_ptr;};


 /////////////////////////////////////////////////////////


template <typename firsttype, typename secondtype>
class bidirectinal_map_one_to_many {
public:
    typedef std::pair <firsttype, secondtype> first_pair;
    typedef std::multimap<firsttype,secondtype> first_mmap;
    typedef typename first_mmap::iterator first_iterator;
    typedef typename std::pair<first_iterator,first_iterator> first_iterators_range;

    typedef std::pair <secondtype,firsttype> second_pair;
    typedef std::map  <secondtype,firsttype,std::less<secondtype>, std::allocator<second_pair > > second_map;
    typedef typename second_map::iterator second_iterator;
    typedef std::set<secondtype ,std::less<secondtype>, std::allocator<secondtype> > secondtype_set;


public:

    bidirectinal_map_one_to_many(){}
    virtual ~bidirectinal_map_one_to_many(){}

    // добавлен ли новый first элемент
    bool add(firsttype f, secondtype s){
       first_iterator  itf=fmap.find(f);
       second_iterator its=smap.find(s);
       int logic_automat=0;
       if (itf!=fmap.end()) logic_automat=logic_automat | 0x1;
       if (its!=smap.end()) logic_automat=logic_automat | 0x2;
       switch (logic_automat){
           case 0: {
               // не в первой не во второй
               fmap.insert(first_pair(f,s));
               smap.insert(second_pair(s,f));
               return true;}
           case 1: {
               //  в первой, но не во второй
               fmap.insert(first_pair(f,s));
               smap.insert(second_pair(s,f));
               return false;}
           case 2: {
               //  не в первой, но  во второй
               remove_by_second_internal(s);
               fmap.insert(first_pair(f,s));
               return false;}
           case 3: {
               //   в первой и  во второй
               remove_by_second(s);
               fmap.insert(first_pair(f,s));
               return false;}}
       return false;}



    bool remove_by_first(firsttype f){
       first_iterator  itf=fmap.find(f);
       if (itf=!fmap.end()) {
           first_iterators_range rgit= fmap.equal_range(f);
           for (first_iterator  itfrg=rgit.first;itfrg!=rgit.second;++itfrg){
             remove_by_second_internal(itfrg->second);}
           return true;}
       return false;}



    bool remove_by_second(secondtype s){
       second_iterator  its=smap.find(s);
       if (its!=smap.end()) {
           firsttype fdel=its->second;
           smap.erase(s);
           return remove_by_first_internal(fdel,s);}
       return false;}

    bool is_first(firsttype f){
        return fmap.find(f)!=fmap.end();}

    bool is_second(secondtype s){
        return smap.find(s)!=smap.end();}


    bool second_by_first(firsttype f, secondtype_set& ss){
       ss.clear();
       first_iterator  itf=fmap.find(f);
       if (itf!=fmap.end()) {
           first_iterators_range rgit= fmap.equal_range(f);
           for (first_iterator  itfrg=rgit.first;itfrg!=rgit.second;++itfrg){
             ss.insert(itfrg->second);}}
        return (!ss.empty());}

    unsigned int count(firsttype f){
        secondtype_set ss;
        second_by_first(f, ss);
        return ss.size();}

    firsttype first_by_second(secondtype s){
        second_iterator its=smap.find(s);
        return its!=smap.end() ? its->second : firsttype();}


   void clear(){
       fmap.clear();
       smap.clear();}

   bool empty(){
       if (fmap.empty() && (smap.empty())) return true;
       if (!fmap.empty() && (!smap.empty())) return false;
       return false;;}

   const first_mmap& firstmap(){
       return fmap;}

   const second_map& secondmap(){
       return smap;}

 public:

    first_mmap  fmap;
    second_map  smap;

    bool remove_by_first_internal(firsttype f,secondtype s){
       first_iterator  itf=fmap.find(f);
       if (itf!=fmap.end()) {
           first_iterators_range rgit= fmap.equal_range(f);
           for (first_iterator  itfrg=rgit.first;itfrg!=rgit.second;++itfrg){
               if (itfrg->second==s) {fmap.erase(itfrg); break;}}
           if (fmap.count(f)>0) return false;
           itf=fmap.find(f);
           if (itf!=fmap.end()) fmap.erase(f);
           return true;}
       return true;}

    bool remove_by_second_internal(secondtype s){
       second_iterator  its=smap.find(s);
       if (its!=smap.end()){
            smap.erase(s);
            return true;}
       return false;}


};







#endif	/* TEMPLATE_H */

