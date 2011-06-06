/* 
 * File:   filebase_templ.h
 * Author: sealeks@mail.ru
 *
 * Created on 18 РњР°Р№ 2011 Рі., 0:21
 */

#ifndef _KERNEL_FILEBASE_TEMPL_H
#define	_KERNEL_FILEBASE_TEMPL_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/string_base.h>

namespace dvnci {
    
    class                                      tagsbase;
    typedef tagsbase*                          ptagsbase;

    template <typename BASIS>
    class templatebase : protected filememorymap {
        
        friend class tagsbase;

        typedef BASIS                                           structs_type;
        typedef structs_type * const                            structs_type_ptr;
        typedef typename structs_type::head_type                header_type;
        typedef typename structs_type::head_type * const        header_type_ptr;
        typedef boost::shared_ptr<index_base>                   indexitem_ptr;

    public:

        typedef typename structs_type::item_type                struct_type;
        typedef typename structs_type::item_type const * const  const_struct_type_ptr;
        typedef typename structs_type::item_type * const        struct_type_ptr;
        typedef dvnci::indx                                     size_type;
        
        static  const size_type    npos = dvnci::npos;

        templatebase(const fspath& filepath, const std::string& mapname, size_t exsize) :
        filememorymap(filepath, mapname, exsize) , systemnotifyer(0) {
            ;}

        templatebase(stringbase_ptr stringsptr, const fspath& filepath, const std::string& mapname, size_t exsize) :
        filememorymap(filepath, mapname, exsize), systemnotifyer(0) {
            stringbs_ = stringsptr;
            item_indexer = indexitem_ptr(new  index_base(stringbs_, mapname + "_index", capacity() / sizeof (struct_type) ));
            if (item_indexer->isnew()) {
                INP_EXCLUSIVE_LOCK(item_indexer->memlock())
                buildindex();}}

        templatebase(ptagsbase notyf, stringbase_ptr stringsptr, const fspath& filepath, const std::string& mapname, size_t exsize) :
        filememorymap(filepath, mapname, exsize), systemnotifyer(notyf) {
            stringbs_ = stringsptr;
            item_indexer = indexitem_ptr(new  index_base(stringbs_, mapname + "_index", capacity() / sizeof (struct_type)));
            if (item_indexer->isnew()) {
                INP_EXCLUSIVE_LOCK(item_indexer->memlock())
                buildindex();}}

        virtual ~templatebase() {}
        
        
        size_type count() const {
            return static_cast<size_type> ((*(structs_type_ptr) data()).header.count());}
              

        size_type operator()(const std::string&  vl) const {
            return item_indexer->find(vl);}
        

        struct_type_ptr operator[] (size_type id)  {
            return ((id < count()) && (((structs_type_ptr) data())->items[id].id() != nill_ptr)) ?
                    &((structs_type_ptr) data())->items[id] : &static_cast<structs_type_ptr> (data())->items[count()];}
        
        bool operator[] (std::string  vl) {
            return (item_indexer->find(vl) != npos);}
        

        bool exists(size_type id) const {
            return ((id < count()) && (((structs_type_ptr) data())->items[id].id() != nill_ptr));}
        

        bool exists(const std::string& vl) const {
            return operator()(vl) != npos;}
        

        size_type id(size_type id) const {
            return exists(id) ? id : npos;}
        

        std::string name(size_type id) const {
            return parentname(id) + stringbase_src(namepos(id));}
        

        virtual size_t mapsize() const {
            return (item_indexer) ? filememorymap::mapsize() + item_indexer->mapsize() : filememorymap::mapsize();}
        

        const_struct_type_ptr begin() const {
            return &static_cast<structs_type_ptr> (data())->items[0];};
            

        const_struct_type_ptr end() const {
            return &static_cast<structs_type_ptr> (data())->items[count()];};



    protected:



        virtual bool checkname(const std::string& val, size_type parnt = npos) = 0;
                
        virtual bool checkdelete(size_type id) {
            return true;} 

        
        virtual void initstruct(size_type id, const std::string& newname, size_type parent = npos) {
            struct_type tmp;
            tmp.id(able_ptr);
            ((structs_type_ptr) data())->items[id] = tmp;
            name(id, newname, false);
            writetofile(id, false);}
        

        virtual void uninitstruct(size_type id) {
            size_t tmp = namepos(id);
            stringbase_src(tmp, "");
            ((structs_type_ptr) data())->items[id].id(nill_ptr);
            writetofile(id);}
        
        
        
        virtual struct_type struct_for_write(size_type id) {         
            if ((id < count()) && (exists(id))) 
                return ((structs_type_ptr) data())->items[id].get_for_write_to_file(trigger_write_criteria(id));
            else
                return struct_type();}
                  
        virtual bool trigger_write_criteria(size_type id) const {
            return false;}        

        
        
        // triggers
        
        virtual void trigger_util(size_type id, const struct_type& oldst,  const struct_type& newst){}
         
        virtual void trigger_add(size_type id , size_type opt = npos) {};
        
        virtual void trigger_remove(size_type id, size_type opt = npos) {};
        
        virtual void trigger_rename(size_type id) {};
        

    
                
        virtual void buildindex() {
            size_type frinx = npos;
            item_indexer->clear_index();
            item_indexer->start_inserter();
            for (size_type i = 0; i < count(); i++) {
                if (exists(i)) {
                    item_indexer->proccess_inserter(i, namepos(i), optinal_pos(i));}
                else {
                    if (frinx == npos) frinx = i;}}
            item_indexer->stop_inserter();
            item_indexer->freeindex((frinx == npos) ? count() : frinx);}
        
        

        virtual void addindex(size_type id) {
            if (exists(id)) {
                INP_EXCLUSIVE_LOCK(item_indexer->memlock())
                item_indexer->insert(id, namepos(id), optinal_pos(id));
                findfreeindex(id);}}
        

        virtual void removeindex(size_type id) {
            if (exists(id)) {
                INP_EXCLUSIVE_LOCK(item_indexer->memlock())
                item_indexer->erase(id, namepos(id), optinal_pos(id));
                if (item_indexer->freeindex() > id)
                    item_indexer->freeindex(id);}}
                
        virtual size_t optinal_pos(size_type id) {
            return 0;}
        
        
        
        /// impl
        

        
        virtual size_t namepos(size_type id) const {
            return operator[](id)->namepos();}
        

        void namepos(size_type id, size_t vl) {
            if ((exists(id)) && (vl != namepos(id)))
                operator[](id)->namepos(vl);}
        
        virtual size_type parentid(size_type id) {
            return npos;}
        
        virtual std::string parentname(size_type id) const {
            return "";}
        
        
        
        void count(size_t value) {
            INP_EXCLUSIVE_LOCK(memlock())
                    (*(structs_type_ptr) data()).header.count(value);
            writeheader();}
        

        const_struct_type_ptr operator[] (size_type id) const {
            return id < count() ? &((structs_type_ptr) data())->items[id] : end();}
        
        
        size_t itemsoffset(size_type id) {
            return (sizeof (header_type) + id * sizeof (struct_type));}
        

        const_struct_type_ptr itemconst(size_type id) const {
            return id < count() ? &((structs_type_ptr) data())->items[id] : end();}       
        

        interproc_mutex& memlock() const {
            return utilptr->memlock();};
            

        
        std::string stringbase_src(size_t pos) const {
            return stringbs_->getstring(pos);}
        

        void  stringbase_src(size_t& pos, const std::string& value, size_t resevmem = DVNCI_DEFRES_STRINGSIZE) {
            stringbs_->setstring(pos, value, resevmem);}
        
        


        
        

        virtual size_type add(const std::string& newname, size_type parnt = npos, bool indexed = true) {
            size_type freeitem = nill_ptr;
            checkname(newname, parnt);
            freeitem = item_indexer->freeindex();
            if (exists(freeitem)) freeitem = count();
            if ((sizeof (header_type)+ (sizeof (struct_type) * static_cast<size_t> (freeitem + 1))) > capacity())
                throw dvncierror(RESERV_MEMSHARE_EXTEND, newname);
            if (freeitem == (count())) count(count()  + 1);
            initstruct(freeitem , newname, parnt);
            if (indexed) {
                addindex(freeitem);
                trigger_add(freeitem, parnt);}
            return (freeitem);}
        

   
        virtual void name(size_type id, std::string val, bool message = true) {
            remove_namespace_delimit(val);
            checkname(val, parentid(id));
            if (exists(id)) {
                if (name(id) != val) {
                    size_t oldpos = namepos(id);
                    size_t newpos = oldpos;
                    if (message)
                        removeindex(id);
                    stringbase_src(newpos, val, DVNCI_DEFRES_NAMESIZE);
                    namepos(id, newpos);
                    if (message) {
                        addindex(id);
                        trigger_rename(id);}}}};

                        
        virtual size_type remove(size_type id, bool indexed = true) {
            if (!exists(id)) return npos;
            checkdelete(id);
            size_type parent = static_cast<size_type> (parentid(id));
            if (indexed) removeindex(id);
            uninitstruct(id);
            trigger_remove(id, parent);
            return id;}
        

        size_type remove(std::string val) {
            return remove((*this)(val));}
        
        
        

        virtual void writeheader() {
            header_type tmp = (*(header_type_ptr) data());
            utilptr->writestructtofile( (void*) & tmp, 0 , sizeof (header_type));}
        

        virtual void writetofile(size_type id, bool triggered = true) {
            if (triggered) {
                struct_type tmpold = readstructfromdisk(id);
                struct_type tmpnew = struct_for_write(id);
                writestructtodisk(tmpnew, id);
                trigger_util(id, tmpold,tmpnew);}
            else{    
                struct_type tmpnew = struct_for_write(id);
                writestructtodisk(tmpnew, id);}
            if (exists(id))
                operator[](id)->incmonitor();}
        

     
        size_t writestructtodisk(const struct_type& dst, size_type id) {
            return utilptr->writestructtofile((const void*) &dst, itemsoffset(id), sizeof (struct_type));}
        
                
        struct_type readstructfromdisk(size_t id) {
            struct_type tmp;
            utilptr->readstructfromfile((void*)&tmp, itemsoffset(id), sizeof (struct_type));
            return tmp;}
        

        void findfreeindex(size_type id) {
            for (size_type i = id; i < count(); i++) {
                if (!exists(i)) {
                    item_indexer->freeindex(i);
                    return;}}
            item_indexer->freeindex(count());}
        

        stringbase_ptr  stringbs_;
        indexitem_ptr   item_indexer;
        ptagsbase       systemnotifyer;};}


#endif	/* FILEBASE_TEMPL_H */

