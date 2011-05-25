/* 
 * File:   cyclic_tabble_templ.h
 * Author: sealeks@mail.ru
 *
 * Created on 17 Май 2011 г., 23:10
 */

#ifndef CYCLIC_TABBLE_TEMPL_H
#define	CYCLIC_TABBLE_TEMPL_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>

namespace dvnci {
    
    template <typename BASIS>
    class cyclicbasemem : protected staticmemorymap {
        

        typedef BASIS                                       structstype;
        typedef structstype * const                         structstype_ptr;
        typedef typename structstype::item_type             structtype;
        typedef structtype * const                          structtype_ptr;
        typedef structtype const *  const                   const_structtype_ptr;

    public:

        typedef dvnci::indx                                 size_type;
        
        static  const size_type    npos = dvnci::npos;

        cyclicbasemem(const std::string& mapname, size_t maxcnt) :
        staticmemorymap(mapname, sizeof (structtype)*(maxcnt + 100) + sizeof (cyclicheaderstruct)) {
            if (isnew()) {
                INP_EXCLUSIVE_LOCK(memlock());
                new (data()) cyclicheaderstruct(maxcnt);}}

        size_type count() const {
            return static_cast<size_type> (((pcyclicheaderstruct) data())->count());}

        size_type number(size_type id) const {
            return (operator()(id)) ? id : 0;};

        bool exists(size_type id) const {
            return (static_cast<size_t> (id) < ((pcyclicheaderstruct) data())->count());}

        size_type cursor() const {
            return static_cast<size_type> (((pcyclicheaderstruct) data())->cursor());};


    protected:

        guidtype guid(size_type id) const {
            return exists(id) ? operator[](id)->guid() : 0;};

        guidtype gloubnum() const {
            return ((pcyclicheaderstruct) data())->gloubnum();};

        structtype_ptr begin() const {
            return &static_cast<structstype_ptr> (data())->items[0];};

        structtype_ptr end() const {
            return &static_cast<structstype_ptr> (data())->items[count()];};

        size_type find_guid_morethen(guidtype morethen, size_type b, size_type e) const {
            if ((b >= e) || (b >= count())) return npos;
            structtype tmp(morethen);
            structtype_ptr endside = (e >= count()) ? end() : operator[](e);
            size_type fnded = static_cast<size_type> (std::upper_bound(operator[](b), endside , tmp ) - (operator[](b)));
            return ((fnded + b) >= e) ? npos : fnded + b;}

        structtype_ptr operator[] (size_type id) const {
            return (id < ((pcyclicheaderstruct) data())->maxcount()) ?
                    & static_cast<structstype_ptr> (data())->items[id] : end();}

        structtype_ptr operator() (size_type id) const {
            if (id >= count()) return end();
            return operator[]( (id < cursor()) ? cursor() - id - 1 : count() + cursor() - id - 1);}

        size_type inc() {
            return static_cast<size_type> (((pcyclicheaderstruct) data())->inc());}

        interproc_mutex& memlock() const {
            return utilptr->memlock();}};}


#endif	/* CYCLIC_TABBLE_TEMPL_H */

