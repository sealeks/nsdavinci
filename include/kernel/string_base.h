/* 
 * File:   string_bases.h
 * Author: sealeks@mail.ru
 *
 * Created on 18 Май 2011 г., 0:01
 */

#ifndef _KERNEL_STRING_BASES_H
#define	_KERNEL_STRING_BASES_H

#include <kernel/constdef.h>
#include <kernel/systemutil.h>
#include <kernel/utils.h>

namespace dvnci {

    // stringbase

    class stringbase : public filememorymap {

        static const size_t DELETEDSTRSIZE = 0xFFFF;
        static const size_t MAXSTRSIZE = 0xFFFA;

    public:

        stringbase(const fspath& filepath, const std::string& mapname, size_t exsize) :
        filememorymap(filepath, mapname, exsize) {
        };

        virtual ~stringbase() {
        };

        std::string getstring(size_t pos) const;

        void setstring(size_t& pos, const std::string& value, size_t resevmem = DVNCI_DEFRES_STRINGSIZE);

        static void writezero(const fspath& path) {
            unum64 tmp = 0;
            filestream::write(path.string(), (num8*) & tmp, 0, sizeof (unum64));
        }

    protected:

        size_t string_capacity(size_t pos) const {
            return (pos == 0) ? 0 : static_cast<size_t> (*((unum16*) ((unum8*) data() + pos + 2)));
        }

        void string_capacity(size_t pos, size_t vl) {
            if (pos < 8) return;
            unum16* tmpsz = (unum16*) ((unum8*) data() + pos + 2);
            *tmpsz = static_cast<unum16> ((vl < MAXSTRSIZE) ? vl : MAXSTRSIZE);
        }

        size_t string_size(size_t pos) const {
            return static_cast<size_t> (*((unum16*) ((unum8*) data() + pos)));
        }

        void string_size(size_t pos, size_t vl);

        bool isfreeregion() const {
            return (*((unum64*) data()) != 0);
        }

        void setfreeregion(bool vl);

        char* string_data(size_t pos) const {
            return ((char*) ((unum8*) data() + pos + 4));
        }

        char* string_data(size_t pos) {
            return ((char*) ((unum8*) data() + pos + 4));
        }

        void set_string_data(size_t& pos, const std::string& value, size_t resevmem);

        bool findfreeregion(size_t& pos, size_t needsize, size_t filesz);

        interproc_mutex& memlock() const {
            return utilptr->memlock();
        }

        interproc_mutex& filelock() const {
            return utilptr->filelock();
        };
    };

    typedef boost::shared_ptr<stringbase> stringbase_ptr;
}

#endif	/* STRING_BASES_H */

