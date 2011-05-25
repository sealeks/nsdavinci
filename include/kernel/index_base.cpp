/* 
 * File:   base_indextable.cpp
 * Author: sealeks@mail.ru
 * 
 * Created on 17 Май 2011 г., 23:48
 */

#include <kernel/index_base.h>

namespace dvnci {



    void index_base::test_list() {
        for (indx i = 0; i<static_cast<indx> (count()); i++) {
            std::cout << "i="  << i << " id="  << id(i) << " name="  << name(i) << " pos=" << pos(i) << " pos1=" << pos1(i) <<  std::endl;};
        std::cout << "freeindex="  << freeindex()  << std::endl;}


    indx index_base::erase(indx id, size_t pos, size_t pos1) {
        indx rngpos1 = static_cast<indx> (std::lower_bound(begin(), end(), internal_parcel(pos, 0, id) , lessop) - begin());
        indx rngpos2 = static_cast<indx> (std::upper_bound(begin(), end(), internal_parcel(pos, 0, id) , lessop) - begin());
        if ((rngpos1 != rngpos2) && (rngpos1<static_cast<indx> (count()))) {
            for (indx it = rngpos1; it < rngpos2; it++) {
                if ((operator[](it)->id = id) && (operator[](it)->pos == pos)) {
                    internal_remove(it);
                    break;}}}
        if (pos1 != 0) {
            rngpos1 = static_cast<indx> (std::lower_bound(begin(), end(), internal_parcel(pos, pos1, id) , lessop) - begin());
            rngpos2 = static_cast<indx> (std::upper_bound(begin(), end(), internal_parcel(pos, pos1, id) , lessop) - begin());
            for (indx it = rngpos1; it < rngpos2; it++) {
                if ((operator[](it)->id = id) && (operator[](it)->pos == pos) && (operator[](it)->pos1 == pos1)) {
                    internal_remove(it);
                    break;}}}
        return id;}

    indx index_base::insert(indx id, size_t pos, size_t pos1) {
        indx insertpos = static_cast<indx> (std::lower_bound(begin(), end(), internal_parcel(pos, 0, id) , lessop) - begin());
        if (insertpos != npos) {
            indx newpos = internal_insert(insertpos);
            if (newpos != npos) {
                new (operator[](newpos)) internal_parcel(pos, 0, id);}}
        if (pos1 > 0) {
            insertpos = static_cast<indx> (std::lower_bound(begin(), end(), internal_parcel(pos, pos1, id) , lessop) - begin());
            if (insertpos != npos) {
                indx newpos = internal_insert(insertpos);
                if (newpos != npos) {
                    new (operator[](newpos)) internal_parcel(pos, pos1, id);}}}
        return id;}

    indx index_base::find(const std::string& vl, bool unical) {
        INP_SHARE_LOCK(memlock());
        indx tmp = binary_find(vl);
        if (tmp == npos) return npos;
        if (!unical) return id(tmp);
        return (get_range_equal(tmp) == 0) ? id(tmp) : npos;}

    bool index_base::find_by_pos1(size_t pos1, indx_set& val, bool clearset) {
        INP_SHARE_LOCK(memlock());
        if (clearset) val.clear();
        indx strt = npos;
        indx stp = npos;
        if (binary_find_range_pos1(pos1, strt, stp)) {
            for (indx i = strt; i < stp; i++) {
                if (exists(i)) val.insert(id(i));}}
        return (!val.empty());}
    
    

    void index_base::start_inserter(const std::string& starter) {
        optim_set.clear();
        optim_set.insert(indexpos(starter, 0, 0 , 0));}
    
    

    bool index_base::proccess_inserter(indx id, size_t pos, size_t pos1) {
        indexpos tmppos(namestr(pos, 0), id, pos, 0);
        optim_set.insert(tmppos);
        if (pos1) {
            indexpos tmppos(namestr(pos, pos1), id, pos, pos1);
            optim_set.insert(tmppos);}
        return true;}
    
    

    std::string index_base::stop_inserter() {
        indexpos_set::iterator its = optim_set.begin();
        ++its;
        for (indexpos_set::iterator it = its; it != optim_set.end(); ++it) {
            count(count() + 1);
            if (count()) new (operator[](static_cast<indx> (count() - 1))) internal_parcel(it->pos, it->pos1, it->ind);}
        optim_set.clear();
        return "";}
    
    

    indx index_base::binary_find(const std::string& vl, indx& upperpos) {
        upperpos = 0;
        if (count() == 0) return npos;
        indx ps0 = 0;
        indx ps1 = static_cast<indx> (count() - 1);
        indx psm = 0;
        while ((ps1 - ps0) > 1) {
            psm = (ps1 + ps0) / 2;
            if (name(psm) < vl) ps0 = psm;
            else ps1 = psm;}
        upperpos = name(ps0) < vl ? ps0 + 1 : ps0;
        if ((ps0 != ps1) && ( name(ps1) < vl))
            upperpos = ps1 + 1;
        if (name(ps0) == vl) {
            return ps0;}
        if ((ps0 != ps1) && (name(ps1) == vl)) {
            return ps1;}
        return npos;}
    

    indx index_base::binary_find(const std::string& vl) {
        if (count() == 0) return npos;
        indx ps0 = 0;
        indx ps1 = static_cast<indx> (count() - 1);
        indx psm = 0;
        while ((ps1 - ps0) > 1) {
            psm = (ps1 + ps0) / 2;
            if (name(psm) < vl) ps0 = psm;
            else ps1 = psm;}
        if (name(ps0) == vl) {
            return ps0;}
        if ((ps0 != ps1) && (name(ps1) == vl)) {
            return ps1;}
        return npos;}
    
    

    bool index_base::binary_find_range_pos1(size_t vl, indx& strt, indx& stp) {
        strt = npos;
        stp = npos;
        std::string tst = namestr(vl);
        if (tst == "") return false;
        std::string tst1 = tst + "::";
        std::string tst2 = tst + "@@";
        binary_find(tst1, strt);
        binary_find(tst2, stp);
        return ((strt <= stp) && (stp <= static_cast<indx> (count())));}
    

    size_t index_base::get_range_equal(indx id, indx& strt, indx& stp) {
        strt = static_cast<indx> (std::lower_bound(begin(), end(), *(operator[](id)) , lessop) - begin());
        stp = static_cast<indx> (std::upper_bound(begin(), end(), *(operator[](id)) , lessop) - begin());
        return (strt)< count() ? (stp - strt - 1) : 0;}
    
    

    size_t index_base::get_range_equal(indx id) {
        indx strt = static_cast<indx> (std::lower_bound(begin(), end(), *(operator[](id)) , lessop) - begin());
        indx stp = static_cast<indx> (std::upper_bound(begin(), end(), *(operator[](id)) , lessop) - begin());
        return (strt < count()) ? (stp - strt - 1) : 0;}
    
    

    bool index_base::internal_remove(indx id)  {
        if ((id == npos) || (id >= count())) return false;
        void* dst = (void*) ((num8*) data() + itemsoffset(id));
        void* src = (void*) ((num8*) data() + itemsoffset(id + 1));
        size_t n = (count() - id - 1) * sizeof (internal_parcel);
        if (n > 0)
            memmove(dst, src, n);
        if (count()) count(count() - 1);
        return true;}
    
    

    indx index_base::internal_insert(indx id) {
        if ((id == npos) || (id > count())) return npos;
        void* dst = (void*) ((num8*) data() + itemsoffset(id + 1));
        void* src = (void*) ((num8*) data() + itemsoffset(id));
        size_t n = (count() - id) * sizeof (internal_parcel);
        if (n > 0)
            memmove(dst, src, n);
        count(count() + 1);
        return id;}
    
    

    bool index_base::less(indx id1, indx id2) {
        if ((id1<static_cast<indx> (count())) && (id2<static_cast<indx> (count()))) {
            return (name(id1) < name(id2));}
        return true;}
    
    

    void index_base::sort() {
        std::sort(begin(), end(), lessop);}

    
    
};

