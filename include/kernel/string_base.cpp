/* 
 * File:   string_bases.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 18 Май 2011 г., 0:01
 */

#include <kernel/string_base.h>

namespace dvnci {
    

    // stringbase

    std::string stringbase::getstring(size_t pos) const {
        if  ((pos > 0) && (pos < capacity())) {
            INP_SHARE_LOCK(memlock());
            return std::string(string_data(pos), string_size(pos));}
        else
            return std::string("");}

    void stringbase::setstring(size_t& pos, const std::string& value, size_t resevmem) {
        if (value.size() > MAXSTRSIZE) throw dvncierror(NS_ERROR_STRING_LONG, "");
        if (pos > capacity()) pos = 0;
        INP_EXCLUSIVE_LOCK(memlock());
        if ( value.empty()) {
            if (pos != 0)
                string_size(pos, DELETEDSTRSIZE);
            pos = 0;
            return;}
        set_string_data(pos, value, resevmem);}

    void stringbase::setfreeregion(bool vl) {
        if (vl != isfreeregion()) {
            unum64* tmp = (unum64*) data();
            *tmp = vl ? 1 : 0;
            utilptr->writetofile( 0 , sizeof (unum64));}}

    void stringbase::string_size(size_t pos, size_t vl) {
        if (pos < 8) return;
        unum16* tmpsz = (unum16*) ((unum8*) data() + pos);
        if (vl == DELETEDSTRSIZE) {
            setfreeregion(true);
            *tmpsz = static_cast<unum16> (DELETEDSTRSIZE);
            utilptr->writetofile(pos, 2);}
        else {
            *tmpsz = static_cast<unum16> ((vl < MAXSTRSIZE) ? vl : MAXSTRSIZE);}}

    void stringbase::set_string_data(size_t& pos, const std::string& value, size_t resevmem) {

        if ((pos == 0) || (string_capacity(pos)<(value.size()))) {
            if (pos != 0) {
                string_size(pos, DELETEDSTRSIZE);}
            resevmem = (pos == 0) ? (resevmem + 5) : (string_capacity(pos) + resevmem + 5);
            if (resevmem < (value.size() + 5)) resevmem = resevmem + (value.size() + 7);
            size_t flsz = filesize();
            if (!findfreeregion(pos, value.size(), flsz)) {
                if (static_cast<size_t> (flsz + resevmem) > capacity())
                    throw dvncierror(RESERV_MEMSHARE_EXTEND, "");
                INP_EXCLUSIVE_LOCK(filelock());
                pos = filesize();
                if (pos == 0) pos = 8;
                string_size(pos, value.size());
                string_capacity(pos, resevmem - 5);
                memcpy( (void*) string_data(pos), value.data(),  (value.size()));
                utilptr->writenosave_to_end(resevmem);
                return;}}
        string_size(pos, value.size());
        memcpy( (void*) string_data(pos), value.data(),  (value.size()));
        utilptr->writetofile(pos, string_capacity(pos) + 5);}

    bool stringbase::findfreeregion(size_t& pos, size_t needsize, size_t filesz) {
        if (!isfreeregion()) return false;
        bool isfinded = false;
        size_t findpos = 8;
        while ((((string_size(findpos) != DELETEDSTRSIZE) || (string_capacity(findpos) < needsize)))  && (findpos < filesz)) {
            if (string_size(findpos) == DELETEDSTRSIZE) isfinded = true;
            findpos = findpos + string_capacity(findpos) + 5;}

        if (((string_size(findpos) == DELETEDSTRSIZE) && (string_capacity(findpos) >= needsize))  && (findpos < filesz)) {
            pos = findpos;
            return true;}

        setfreeregion(isfinded );
        return false;}    
    
    

    

}

