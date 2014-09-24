/* 
 * File:   stringvalue_base.h
 * Author: sealeks@mail.ru
 *
 * Created on 18 Май 2011 г., 14:22
 */

#ifndef _KERNEL_STRINGVALUE_BASE_H
#define	_KERNEL_STRINGVALUE_BASE_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>

namespace dvnci {


    // stringvalue_base

    class stringvalue_base : public filememorymap {

        static const size_t DELETEDSTRSIZE = 0xFFFF;
        static const size_t MAXSTRSIZE = DVNCI_MAXVALUESTRSIZE;

        struct headerstruct {

            headerstruct() :
            entetyfreeindex_(0),
            entetycount_(0),
            sessionfirst_(0),
            sessionfreeindex_(0),
            sessioncount_(0),
            count_(0) {
                ;
            }

            headerstruct(const headerstruct & src) {
                entetyfreeindex_ = src.entetyfreeindex_;
                entetycount_ = src.entetycount_;
                sessionfirst_ = 0;
                sessionfreeindex_ = 0;
                sessioncount_ = 0;
                count_ = 0;
            }

            headerstruct & operator=(const headerstruct & src) {
                entetyfreeindex_ = src.entetyfreeindex_;
                entetycount_ = src.entetycount_;
                sessionfirst_ = 0;
                sessionfreeindex_ = 0;
                sessioncount_ = 0;
                count_ = 0;
                return (*this);
            }

            static void init(headerstruct& src, size_t sessfst, size_t cnt) {
                src.sessionfirst_ = sessfst;
                src.sessionfreeindex_ = sessfst;
                src.sessioncount_ = sessfst;
                src.count_ = cnt;
            }

            size_t entetyfreenindex() const {
                return static_cast<size_t> (entetyfreeindex_);
            }

            void entetyfreenindex(size_t val) {
                entetyfreeindex_ = static_cast<unum64> (val);
            }

            size_t entetycount() const {
                return static_cast<size_t> (entetycount_);
            }

            void entetycount(size_t val) {
                entetycount_ = static_cast<unum64> (val);
            }

            size_t entetymaxcount() const {
                return sessionfirst() - 1;
            }

            size_t sessionfreeindex() const {
                return static_cast<size_t> (sessionfreeindex_);
            }

            void sessionfreeindex(size_t val) {
                sessionfreeindex_ = static_cast<unum64> (val);
            }

            size_t sessioncount() const {
                return static_cast<size_t> (sessioncount_);
            }

            void sessioncount(size_t val) {
                sessioncount_ = static_cast<unum64> (val);
            }

            size_t sessionfirst() const {
                return static_cast<size_t> (sessionfirst_);
            }

            size_t count() const {
                return static_cast<size_t> (count_);
            }

        private:
            unum64 entetyfreeindex_;
            unum64 entetycount_;
            unum64 sessionfirst_;
            unum64 sessionfreeindex_;
            unum64 sessioncount_;
            unum64 count_;
        };

        struct valuestringitem {

            std::string value() const {
                if (isfree()) return "";
                return std::string((num8*) value_, size());
            }

            void value(const std::string & vl) {
                std::string tmp = (vl.size() <= MAXSTRSIZE) ? vl : vl.substr(MAXSTRSIZE);
                memcpy((void*) value_, tmp.data(), tmp.size());
                size(tmp.size());
            }

            void remove() {
                setfree();
            }

            size_t size() const {
                return static_cast<size_t> (size_);
            }

            bool isfree() const {
                return (size() > 0xFC);
            }

        private:

            void size(size_t vl) {
                size_ = static_cast<unum16> ((vl < 0xFC) ? vl : 0xFC);
            }

            void setfree() {
                size_ = static_cast<unum16> (DELETEDSTRSIZE);
            }

            unum16 size_;
            num8 value_[MAXSTRSIZE + 1];
        };

        struct valuestringstruct {

            headerstruct header;
            valuestringitem items[];
        };


    public:

        stringvalue_base(const fspath& filepath, const std::string& mapname, size_t textcnt, size_t exsize) :
        filememorymap(filepath, mapname, 2 * exsize + textcnt * EXTEND_MEMSHARE_STRSTATIC + sizeof (valuestringitem)*2) {
            if (isnew()) {
                INP_EXCLUSIVE_LOCK(memlock());
                size_t allignsz = (sizeof (valuestringitem) % 8) ?
                        (sizeof (valuestringitem) / 8 + 1) * 8 : (sizeof (valuestringitem));
                size_t sesssion_first = (filesize() + exsize) / allignsz;
                size_t total_count = capacity() / allignsz;
                headerstruct::init(*((headerstruct*) data()), sesssion_first, total_count);
                ;
            }
        };

        virtual ~stringvalue_base() {
        };

        std::string getstring(size_t pos) const;

        void setstring(size_t& pos, const std::string& value, bool ispersist);

        void remove(size_t pos);

        void replace_from_sys(size_t& pos);

        void replace_to_sys(size_t& pos);

        static void writezero(const fspath& path) {
            unum64 tmp[] = {0, 0, 0, 0, 0, 0};
            filestream::write(path.string(), (num8*) tmp, 0, sizeof (headerstruct));
        }

    protected:

        bool exists(size_t id) const {
            return (id < count());
        }

        valuestringitem * operator[](size_t id) const {
            return (exists(id)) ? &((valuestringstruct*) data())->items[id] : 0;
        }

        size_t findfree(size_t strt, size_t stp) const {
            for (size_t i = strt; i < stp; i++) {
                if (operator[](i)->isfree()) {
                    return (i);
                }
            }
            return stp;
        }

        size_t itemsoffset(indx id) {
            return (sizeof (headerstruct) + id * sizeof (valuestringitem));
        }

        size_t count() const {
            return ((headerstruct*) data())->count();
        }

        size_t entetycount() const {
            return ((headerstruct*) data())->entetycount();
        }

        void entetycount(size_t vl) {
            ((headerstruct*) data())->entetycount(vl);
            writeheader();
        }

        size_t entetymaxcount() const {
            return ((headerstruct*) data())->entetymaxcount();
        }

        size_t entetyfree() const {
            return ((headerstruct*) data())->entetyfreenindex();
        }

        void entetyfree(size_t vl) {
            ((headerstruct*) data())->entetyfreenindex(vl);
            writeheader();
        }

        size_t sessionfirst() const {
            return ((headerstruct*) data())->sessionfirst();
        }

        size_t sessioncount() const {
            return ((headerstruct*) data())->sessioncount();
        }

        void sessioncount(size_t vl) {
            ((headerstruct*) data())->sessioncount(vl);
        }

        size_t sessionfree() const {
            return ((headerstruct*) data())->sessionfreeindex();
        }

        void sessionfree(size_t vl) {
            return ((headerstruct*) data())->sessionfreeindex(vl);
        }

        void writeitem(size_t id) {
            if (id < entetycount()) {
                utilptr->writetofile(itemsoffset(id), sizeof (valuestringitem));
            }
        }

        void writeheader() {
            //headerstruct tmp = *((headerstruct*) data());
            utilptr->writetofile(0, sizeof (headerstruct));
        }

        bool invalidpos(size_t vl) const {
            return capacity()< ((vl + 1) * sizeof (valuestringitem));
        }

        interproc_mutex& memlock() const {
            return utilptr->memlock();
        }
    };
}

#endif	/* STRINGVALUE_BASE_H */

