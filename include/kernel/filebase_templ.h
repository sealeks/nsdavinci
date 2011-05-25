/* 
 * File:   filebase_templ.h
 * Author: sealeks@mail.ru
 *
 * Created on 18 Май 2011 г., 0:21
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

   
        virtual std::string nametemlete() const = 0;
        
        
        virtual bool checkname(const std::string& val, size_type parnt = npos) = 0;
        
          
        virtual bool checkdelete(size_type id) {
            return true;} 
        
        
        virtual struct_type writestruct(size_type id) {
            
            if ((id < count()) && (exists(id))) 
                return ((structs_type_ptr) data())->items[id].get_for_write_to_file(write_criteria(id));
            else
                return struct_type();}
        
        virtual bool write_criteria(size_type id) const {
            return false;}
        
        
        virtual void initstruct(size_type id, const std::string& newname, num64 numcriteria = -1) {
            struct_type tmp;
            tmp.id(able_ptr);
            ((structs_type_ptr) data())->items[id] = tmp;
            name(id, newname, false);
            writetofile(id);}
        

        virtual void uninitstruct(size_type id) {
            size_t tmp = namepos(id);
            stringbase_src(tmp, "");
            ((structs_type_ptr) data())->items[id].id(nill_ptr);
            writetofile(id);}
        
        // triggers
        
        
        virtual void trigger_add(size_type id, num64 numcriteria = -1) {};
        
        virtual void trigger_remove(size_type id, num64 numcriteria = -1) {};
        
        virtual void trigger_rename(size_type id) {};
        
        virtual void trigger_write(size_type id) {};
        
        
        
        
        
        
        
        virtual size_type parent_id(size_type id) {
            return npos;}
        
        
        virtual std::string parentname(size_type id) const {
            return "";}
        
                virtual size_t namepos(size_type id) const {
            return operator[](id)->namepos();}
        

        virtual void namepos(size_type id, size_t vl) {
            if ((exists(id)) && (vl != namepos(id)))
                operator[](id)->namepos(vl);}


        virtual size_type string_to_numcriteria(const std::string&  strcriteria) {
            return npos;}

        
        virtual size_t optinal_pos(size_type id) {
            return 0;}
        
                
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
        
        
        
        /// impl
        
        
        
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
            

        stringbase_ptr stringbs() {
            return stringbs_;}
        

        stringbase_ptr stringbs() const {
            return stringbs_;}
        

        std::string stringbase_src(size_t pos) const {
            return stringbs()->getstring(pos);}
        

        void  stringbase_src(size_t& pos, const std::string& value, size_t resevmem = DVNCI_DEFRES_STRINGSIZE) {
            stringbs()->setstring(pos, value, resevmem);}
        

        size_type add() {
            std::string str_tmp = nametemlete();
            size_type i = 0;
            while (exists(str_tmp + to_str(i))) i++;
            return add(str_tmp + to_str(i));}
        

        size_type add(const std::string& newname, const std::string& groupnm)  {
            return add(newname, string_to_numcriteria(groupnm));}
        

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
                trigger_add(freeitem, static_cast<num64> (parnt));}
            return (freeitem);}
        

   
        virtual void name(size_type id, std::string val, bool message = true) {
            remove_namespace_delimit(val);
            checkname(val, parent_id(id));
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
            num64 ncrt = static_cast<size_type> (parent_id(id));
            if (indexed) removeindex(id);
            uninitstruct(id);
            trigger_remove(id, ncrt);
            return id;}
        

        size_type remove(std::string val) {
            return remove((*this)(val));}
        

        virtual void writeheader() {
            header_type tmp = (*(header_type_ptr) data());
            writestructtodisk( (void*) & tmp, 0 , sizeof (header_type));}
        

        virtual void writetofile(size_type id) {
            struct_type tmp = writestruct(id);
            writestructtodisk( (void*) &tmp, itemsoffset(id), sizeof (struct_type));
            if (exists(id))
                operator[](id)->incmonitor();
            trigger_write(id);}
        

        virtual void writetofileall() {
            for (size_type i = 0 ; i < count() ; i++)
                writetofile(i);}
        

        size_t writetodisk(size_t offset = 0, size_t sz = 0) {
            return utilptr->writetofile(offset, sz);}
        

        size_t writestructtodisk(void* dt, size_t offset = 0, size_t sz = 0) {
            return utilptr->writestructtofile(dt, offset, sz);}
        

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

