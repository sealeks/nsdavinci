/* 
 * File:   index_base.h
 * Author: sealeks@mail.ru
 *
 * Created on 17 Май 2011 г., 23:48
 */

#ifndef _KERNEL_BASE_INDEXTABLE_H
#define	_KERNEL_BASE_INDEXTABLE_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/string_base.h>

namespace dvnci {

    // index_base

    class index_base : public  staticmemorymap {
        
    protected:

        struct indexpos {

            indexpos(const std::string& nm,  indx  id, size_t ps, size_t ps1) : name(nm), ind(id), pos(ps) , pos1(ps1) {}
            std::string name;
            indx        ind;
            size_t      pos;
            size_t      pos1;

            bool operator==(const indexpos & rs) {
                return ((name == rs.name) && (ind == rs.ind) && (pos == rs.pos) && (pos1 == rs.pos1));};} ;

        friend bool operator<(const indexpos& ls, const indexpos& rs) {
            if (ls.name < rs.name) return true;
            if ((ls.name == rs.name) && (ls.ind < rs.ind)) return true;
            if ((ls.name == rs.name) && (ls.ind == rs.ind) && (ls.pos < rs.pos)) return true;
            if ((ls.name == rs.name) && (ls.ind == rs.ind) && (ls.pos == rs.pos) && (ls.pos1 < rs.pos1)) return true;
            return false;}

        typedef std::set<indexpos , std::less<indexpos>, std::allocator<indexpos> > indexpos_set;

        struct internal_header {
            size_t count;
            indx freeindex;} ;

        struct internal_parcel {

            internal_parcel(indx ps = 0, indx ps1 = 0, indx ind = npos) : pos(ps), pos1(ps1), id(ind) {};
            indx    pos;
            indx    pos1;
            indx    id;} ;

        struct internal_table {
            internal_header hdr;
            internal_parcel items[];} ;

        typedef internal_header*    pinternal_header;
        typedef internal_parcel*    pinternal_parcel;
        typedef internal_table*     pinternal_table;

        struct lessoperator : public std::less<internal_parcel> {

            lessoperator(stringbase_ptr strbs) : std::less<internal_parcel > () , strbase(strbs) {}

            bool operator() (const internal_parcel& x, const internal_parcel & y) const {
                return (name(x) < name(y));}

        private:

            std::string name(const internal_parcel & x) const {
                return (x.pos1 == 0) ? strbase->getstring(x.pos) :
                        strbase->getstring(x.pos1) + "::" + strbase->getstring(x.pos);}

            stringbase_ptr   strbase;} ;

    public:

        index_base(stringbase_ptr strbs, std::string mapname, size_t sz) :
        staticmemorymap(mapname, (sizeof (internal_parcel) + 2) * sz + sizeof (internal_header)), strbase(strbs), lessop(strbs) {}

        virtual ~index_base() {};

        interproc_mutex& memlock() const {
            return utilptr->memlock();}

        indx find(const std::string& vl, bool unical = true);

        bool find_by_pos1(size_t pos1, indx_set& val, bool clearset = true);

        void start_inserter(const std::string& starter = "");

        bool proccess_inserter(indx id, size_t pos, size_t pos1 = 0);

        std::string stop_inserter();

        indx insert(indx id, size_t pos, size_t pos1 = 0);

        indx erase(indx id, size_t pos, size_t pos1 = 0);

        void test_list();

        void clear_index() {
            count(0);}

        indx freeindex() const {
            return ((pinternal_table) data())->hdr.freeindex;}

        void freeindex(indx vl) {
            ((pinternal_table) data())->hdr.freeindex = vl;}

    protected:

        pinternal_parcel operator[](indx id) const {
            return (id < static_cast<indx> (count())) ? &(*(pinternal_table) data()).items[id] : 0;}

        pinternal_parcel begin() const {
            return operator[](0);}

        pinternal_parcel end() const {
            return (operator[](0) + count());}

        size_t count() const {
            return ((pinternal_table) data())->hdr.count;}

        void count(size_t vl) {
            ((pinternal_table) data())->hdr.count = vl;}

        indx id(indx id) const {
            return exists(id) ? operator[](id)->id : npos;}

        std::string name(indx id) const {
            if (!exists(id)) return "";
            return (pos1(id) == 0) ? str(id) : str1(id) + "::" + str(id);}

        std::string namestr(size_t pos, size_t pos1 = 0) const {
            return (pos1 == 0) ? strbase->getstring(pos) :
                    strbase->getstring(pos1) + "::" + strbase->getstring(pos);}

        size_t pos(indx id) const {
            return exists(id) ? operator[](id)->pos : 0;}

        size_t pos1(indx id) const {
            return exists(id) ? operator[](id)->pos1 : 0;}

        std::string str(indx id) const {
            return exists(id) ? strbase->getstring(operator[](id)->pos) : "";}

        std::string str1(indx id) const {
            return exists(id) ? strbase->getstring(operator[](id)->pos1) : "";}

        bool exists(indx id) const {
            return ((id != npos) && (id < static_cast<indx> (count())));}

        size_t itemsoffset(indx id) {
            return (sizeof (internal_header) + id * sizeof (internal_parcel));}

        indx binary_find(const std::string& vl, indx& upperpos);

        indx binary_find(const std::string& vl);

        bool binary_find_range_pos1(size_t vl, indx& strt, indx& stp);

        size_t get_range_equal(indx id, indx& strt, indx& stp);

        size_t get_range_equal(indx id);

        void sort();

        bool internal_remove(indx id);

        indx internal_insert(indx id);

        bool less(indx id1, indx id2);

        stringbase_ptr   strbase;
        lessoperator     lessop;
        indexpos_set     optim_set;};};

#endif	/* BASE_INDEXTABLE_H */

