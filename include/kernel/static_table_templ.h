/* 
 * File:   static_table_templ.h
 * Author: sealeks@mail.ru
 *
 * Created on 17 Май 2011 г., 23:25
 */

#ifndef _KERNEL_STATIC_TABLE_TEMPL_H
#define	_KERNEL_STATIC_TABLE_TEMPL_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>


namespace dvnci {

    /////////////////////////////////////////////////////////////////////////////////////////////
    /// Deletable line Table Structure
    /////////////////////////////////////////////////////////////////////////////////////////////

    template <typename BASIS>
    class livebasemem : protected staticmemorymap {

        typedef BASIS structstype;
        typedef structstype * const structstype_ptr;
        typedef typename structstype::item_type structtype;
        typedef structtype * const structtype_ptr;

    public:

        typedef dvnci::indx size_type;

        static const size_type npos = dvnci::npos;

        livebasemem(const std::string& mapname, size_t maxcnt) :
        staticmemorymap(mapname, sizeof (structtype)*(maxcnt + 100) + sizeof (cyclicheaderstruct)) {
            if (isnew()) {
                INP_EXCLUSIVE_LOCK(memlock());
                new (data()) liveheaderstruct(maxcnt);
            }
        }

        size_type count() const {
            return static_cast<size_type> ((*(pliveheaderstruct) data()).count());
        }

        bool exists(size_type id) const {
            return (static_cast<size_t> (id)<(*(pliveheaderstruct) data()).count());
        }

        guidtype globalnum() const {
            return (*(pliveheaderstruct) data()).gloubnum();
        };

        structtype_ptr operator[] (size_type id) const {
            return (static_cast<size_t> (id) < (*(pliveheaderstruct) data()).count()) ?
                    & static_cast<structstype_ptr> (data())->items[id] : end();
        }

    protected:

        guidtype guid(size_type id) const {
            return exists(id) ? operator[](id)->guid() : 0;
        };

        structtype_ptr begin() const {
            return &static_cast<structstype_ptr> (data())->items[0];
        }

        structtype_ptr end() const {
            return &static_cast<structstype_ptr> (data())->items[count()];
        }

        guidtype version() const {
            return (*(pliveheaderstruct) data()).version();
        };

        void count(size_type val) {
            (*(pliveheaderstruct) data()).count(static_cast<size_t> (val));
        }

        size_type maxcount() const {
            return static_cast<size_type> ((*(pliveheaderstruct) data()).maxcount());
        }

        size_type inc() {
            if (count() >= maxcount()) return npos;
            count(count() + 1);
            ((pliveheaderstruct) data())->incgloubnum();
            return count() ? (count() - 1) : 0;
        }

        guidtype incversion() {
            return ((pliveheaderstruct) data())->incversion();
        }

        bool pop_begin() {
            return internal_remove(0);
        }

        bool internal_remove(size_type id) {
            if (!exists(id)) return false;
            if ((id + 1) < count()) {
                num8* dst = (num8*) data()+(int) (sizeof (liveheaderstruct) + id * sizeof (structtype));
                const num8* src = (num8*) data()+(sizeof (liveheaderstruct)+(id + 1) * sizeof (structtype));
                size_t n = (count() - id - 1) * sizeof (structtype);
                memmove(dst, src, n);
            }
            if (count()) count(count() - 1);
            return true;
        }

        size_type find_by_guid(guidtype gid) {
            structtype tmp(gid);
            size_type fndbeg = static_cast<size_type> (std::lower_bound(begin(), end(), tmp) - begin());
            size_type fndend = static_cast<size_type> (std::upper_bound(begin(), end(), tmp) - begin());
            return (fndbeg == fndend) ? npos : fndbeg;
        }

        size_type remove_by_guid(guidtype gid) {
            size_type id = find_by_guid(gid);
            if (id != npos) {
                internal_remove(id);
                return id;
            }
            return npos;
        }

        size_type reverse_index(size_type id) const {
            return id < count() ? count() - 1 - id : npos;
        }

        interproc_mutex& memlock() const {
            return utilptr->memlock();
        }
    };
}


#endif	/* _KERNEL_STATIC_TABLE_TEMPL_H */

