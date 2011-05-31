/* 
 * File:   stringvalue_base.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 18 Май 2011 г., 14:22
 */

#include <kernel/stringvalue_base.h>


namespace dvnci {
    
    // valuestring

    std::string stringvalue_base::getstring(size_t pos) const {
        INP_SHARE_LOCK(memlock());
        if ((!pos) || (pos >= count()) || (invalidpos(pos)) ) return "";
        return operator[](pos - 1)->value();}

    void stringvalue_base::setstring(size_t& pos, const std::string& value, bool ispersist) {
        INP_EXCLUSIVE_LOCK(memlock());
        if ((pos > count()) || (invalidpos(pos))){ 
            pos = 0;}
        if (pos == 0) {
            if (ispersist) {
                size_t freetmp = findfree(entetyfree(), entetycount());
                if (freetmp < entetymaxcount()) {
                    if (freetmp == entetycount()) {
                        entetycount(entetycount() + 1);
                        entetyfree(entetycount());
                        pos = entetycount() - 1;}
                    else {
                        pos = freetmp;
                        freetmp = findfree(freetmp + 1, entetycount());
                        entetyfree(freetmp);}
                    pos = pos + 1;}}
            else {
                size_t freetmp = findfree(sessionfree(), sessioncount());
                if (freetmp < count()) {
                    if (freetmp == sessioncount()) {
                        sessioncount(sessioncount() + 1);
                        sessionfree(sessioncount());
                        pos = sessioncount() - 1;}
                    else {
                        pos = freetmp;
                        freetmp = findfree(freetmp + 1, sessioncount());
                        sessionfree(freetmp);}
                    pos = pos + 1;}}}
        if (!pos) return;
        operator[](pos - 1)->value(value);
        if ((ispersist) && ((pos - 1) < entetycount()))
            writeitem(pos - 1);}
    

    void stringvalue_base::remove(size_t pos) {
        INP_EXCLUSIVE_LOCK(memlock());
        if (!pos) return;
        if ((pos - 1) < entetycount()) {
            if (entetyfree()>(pos - 1)) entetyfree(pos - 1);
            operator[](pos - 1)->remove();
            writeitem(pos - 1);}
        if (((pos - 1) < sessioncount()) && ((pos - 1) >= sessionfirst())) {
            if (sessionfree()>(pos - 1)) sessionfree(pos - 1);
            operator[](pos - 1)->remove();}}
    

    void stringvalue_base::replace_from_sys(size_t& pos) {
        std::string tmp = getstring(pos);
        remove(pos);
        setstring(pos, tmp, false);}
    

    void stringvalue_base::replace_to_sys(size_t& pos) {
        std::string tmp = getstring(pos);
        remove(pos);
        setstring(pos, tmp, true);}}

