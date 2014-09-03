/* 
 * File:   systemutil.cpp
 * Author: Serg
 * 
 * Created on 27 Апрель 2010 г., 20:05
 */

#include <kernel/systemutil.h>

namespace dvnci {
    using namespace std;

    // filestream

    size_t filestream::filesize(const fspath& filename) {

        if (filestream::exists(filename.string().c_str())) {
            boost::filesystem::path p(filename.string().c_str());
            return static_cast<size_t> (boost::filesystem::file_size(p));
        }
        return 0;
    }

    size_t filestream::read(const fspath& filename, void* addr, size_t offset, size_t size) {
        size_t fsz = filestream::filesize(filename.string().c_str());
        if (fsz) {
            if (offset > fsz) return 0;
            std::ifstream ifs(filename.string().c_str(), std::ios::binary);
            if (!ifs)
                return 0;
            if (offset)
                ifs.seekg(offset, std::ofstream::beg);

            if (!size) size = fsz - offset;
            size_t rsz = (fsz < (offset + size)) ? fsz - offset : size;
            ifs.read((char*) addr, rsz);
            ifs.close();
            return rsz;
        } else return 0;
    }

    size_t filestream::writestr(const fspath& filename, const void* addr, size_t offset, size_t size) {
        if (!size) return 0;
        std::ios_base::openmode mode = std::ios::binary | std::ios::trunc;
        std::ofstream ofs(filename.string().c_str(), mode);
        if (!ofs)
            return 0;
        if (offset)
            ofs.seekp(offset, std::ofstream::beg);
        ofs.write((char*) addr, size);
        ofs.close();
        return 0;
    };

    size_t filestream::write(const fspath& filename, const void* addr, size_t offset, size_t size) {
        if (!size) return 0;
        size_t fsz = filestream::filesize(filename.string());
        std::ios_base::openmode mode = std::ios::binary | std::ios::in;
        if (!fsz) mode = std::ios::binary | std::ios::trunc;
        std::ofstream ofs(filename.string().c_str(), mode);
        if (!ofs)
            return 0;
        if (offset)
            ofs.seekp(offset, std::ofstream::beg);
        ofs.write((char*) addr, size);
        ofs.close();
        return 0;
    };

    ///////////////////////////////////////////////////////////////           

    void util_memory::remove_main() {
#ifdef _DVN_LIN_ 
        try {
            boost::interprocess::shared_memory_object::remove(mapname().c_str());
        }        catch (...) {
        }
#endif    
        ;
    }

    bool util_memory::map(boost::interprocess::mapped_region& rgn, std::string name, size_t size) {
        try {
            boost::interprocess::shared_memory_object shm(boost::interprocess::open_or_create, name.c_str(), boost::interprocess::read_write);
            shm.truncate(size);
            rgn = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
            return true;
        }        catch (...) {
        }
        return false;
    }

    bool util_memory::map_utl(boost::interprocess::mapped_region& rgn, std::string name, bool& isnew, size_t size) {
        isnew = false;
#ifdef _WIN32_WINNT
        try {
            boost::interprocess::windows_shared_memory shm(boost::interprocess::create_only, name.c_str(), boost::interprocess::read_write, size);
            isnew = true;
            rgn = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
            return true;
        }        catch (...) {
            try {
                boost::interprocess::windows_shared_memory shm(boost::interprocess::open_only, name.c_str(), boost::interprocess::read_write);
                isnew = false;
                rgn = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
                return true;
            }            catch (...) {
            }
        }
#endif
#ifdef _DVN_LIN_
        try {
            boost::interprocess::permissions permis;
            permis.set_unrestricted();
            boost::interprocess::shared_memory_object shm(boost::interprocess::create_only, name.c_str(), boost::interprocess::read_write, permis);
            isnew = true;
            shm.truncate(size);
            rgn = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
            return true;
        }        catch (...) {
            try {
                boost::interprocess::shared_memory_object shm(boost::interprocess::open_only, name.c_str(), boost::interprocess::read_write);
                isnew = false;
                shm.truncate(size);
                rgn = boost::interprocess::mapped_region(shm, boost::interprocess::read_write);
                return true;
            }            catch (...) {
            }
        }
#endif
        return false;
    }


    // util_static_size_shmemory  

    util_static_size_shmemory::util_static_size_shmemory(std::string name, size_t sz) : util_memory(name, (sz + ADDITINAL_STATIC_MAPSIZIZE)) {
        init_region();
    }

    util_static_size_shmemory::~util_static_size_shmemory() {
        {
            INP_EXCLUSIVE_LOCK(memlock());
            intern_hdr->cnt--;
        }
        if (!intern_hdr->cnt) {
            remove_main();
        }
    }

    bool util_static_size_shmemory::init_region() {
        map_utl(mainmem, mapname(), isnew_, size_ + sizeof (intern_header));
        if (isnew_) {
            intern_hdr = new (get_address_internal()) intern_header;
            DEBUG_STR_VAL_DVNCI(FIRSTLOAD, mapname());
            size_internal(size_ + sizeof (intern_header));
        } else {
            intern_hdr = (intern_header*) get_address_internal();
        };
        INP_EXCLUSIVE_LOCK(memlock());
        intern_hdr->cnt++;
        return mainmem.get_address();
    }



    // util_static_size_shmemory        

    util_filemapmemory::util_filemapmemory(const std::string& name, const fspath& file, size_t sz) : util_memory(name, sz), filename_(file) {
        if (filestream::exists(file.string())) {
            size_t siz = filestream::filesize(file.string());
            sz += siz;
            sz += sizeof (intern_header);
            size_ = sz;
            if (init_region()) {
                if (isnew()) {
                    intern_hdr = new (get_address_internal()) intern_header;
                    INP_EXCLUSIVE_LOCK(filelock());
                    size_internal(size_);
                    if (!filestream::read(file.string(), get_address(), 0, siz)) {
                        return;
                    }
                } else {
                    intern_hdr = (intern_header*) get_address_internal();
                }
                INP_EXCLUSIVE_LOCK(memlock());
                intern_hdr->cnt++;
            }
        }
    };

    util_filemapmemory::~util_filemapmemory() {
        {
            INP_EXCLUSIVE_LOCK(memlock());
            intern_hdr->cnt--;
        }
        if (!intern_hdr->cnt) {
            remove_main();
        }
    }

    size_t util_filemapmemory::writetofile(size_t offset, size_t sz) {
        if (!sz) return 0;
        INP_EXCLUSIVE_LOCK(filelock());
        return filestream::write(filename().string(), (char*) get_address() + offset, offset, sz);
    }

    size_t util_filemapmemory::writestructtofile(const void* dt, size_t offset, size_t sz) {
        if (!sz) return 0;
        INP_EXCLUSIVE_LOCK(filelock());
        return filestream::write(filename().string(), (const num8*) dt, offset, sz);
    }

    size_t util_filemapmemory::readstructfromfile(void* dt, size_t offset, size_t sz) {
        if (!sz) return 0;
        INP_EXCLUSIVE_LOCK(filelock());
        return filestream::read(filename().string(), (num8*) dt, offset, sz);
    }

    size_t util_filemapmemory::writenosave_to_end(size_t sz) {
        if (!sz) return 0;
        size_t offset = filesize();
        return filestream::write(filename().string(), (num8*) get_address() + offset, offset, sz);
    }


    // staticmemorymap

    staticmemorymap::staticmemorymap(const string& name, size_t size) {
        size_t sz = (size < 4) ? 0xFFFFFF : static_cast<size_t> (size);
        utilptr = util_static_size_shmemory_ptr(new util_static_size_shmemory(name, sz));
        if ((!utilptr) || (!utilptr->get_address())) {
            throw new dvncierror(NS_ERROR_MAPMEMORY, name);
        }
    }


    // filememorymap

    filememorymap::filememorymap(const fspath& filepth, const string& mapname, size_t exsize) {
        if (!filestream::filesize(filepth.string())) {
            throw dvncierror(NS_ERROR_MAINFILENOTFOUND, filepth.string());
        }
        utilptr = util_filemapmemory_ptr(new util_filemapmemory(mapname, filepth.string(), exsize));
        if (!utilptr) {
            throw new dvncierror(NS_ERROR_MAPMEMORY, mapname);
        }
    }


    /////////////////////////////////////////////////////////////////////////////

    mq_class* proccess_queues::getqueue(guidtype val, bool create, size_t sz) {
        std::string vl = get_mq_name(val);
        mq_class* mq;
        if (create) {
            try {
                boost::interprocess::permissions prms;
                prms.set_unrestricted();
                removequeue(val);
                mq = new mq_class(boost::interprocess::create_only, vl.c_str(), sz, sizeof (messagestruct), prms);
                return mq;
            }            catch (boost::interprocess::interprocess_exception &ex) {
                return 0;
            };
        } else {
            try {
                mq = new mq_class(boost::interprocess::open_only, vl.c_str() /*,messsage_queue_count  ,sizeof(messagestruct)*/);
                return mq;
            }            catch (boost::interprocess::interprocess_exception &ex) {
                DEBUG_STR_VAL_DVNCI(getqueue err, ex.what());
                return 0;
            };
        }
        return 0;
    }

    void proccess_queues::removequeue(guidtype val) {
        std::string vl = get_mq_name(val);
        try {
            mq_class::remove(vl.c_str());
        }        catch (boost::interprocess::interprocess_exception &ex) {
        };
    }

    bool proccess_queues::try_send(mq_class* queue, qumsgtype mess, indx id, num32 some) {
        try {
            messagestruct tmp(mess, id, some);
            return queue->try_send(&tmp, sizeof (messagestruct), 0);
        }        catch (boost::interprocess::interprocess_exception &ex) {
            return false;
        };
    }

    bool proccess_queues::try_recieve(mq_class* queue, messagestruct& msg) {
        try {
            unsigned int priority;
            size_t recvd_size = 0;
            return ((queue->try_receive(&msg, sizeof (messagestruct), recvd_size, priority)) && (recvd_size == sizeof (messagestruct)));
        }        catch (boost::interprocess::interprocess_exception &ex) {
            return false;
        };
        return false;
    };




    //////////////////////////////////////////////////////////////////////////    

    string stringed_filterclass::criterias() {
        criteria_ = "";
        filtered_map::iterator it = filtermap.begin();
        while (it != filtermap.end()) {
            criteria_ = criteria_ + it->first + "=\"" + it->second + "\"\n";
            ++it;
        }
        filteredkey_map::iterator it2 = filterkeymap.begin();
        while (it2 != filterkeymap.end()) {
            std::string tmpstr;
            setkeyswithstring(tmpstr, it2->second);
            if (tmpstr != "")
                criteria_ = criteria_ + it2->first + "=\"" + tmpstr + "\"\n";
            ++it2;
        }
        return criteria_;
    }

    void stringed_filterclass::setcriteria(const string name, string val) {
        if (filtermap.find(name) != filtermap.end()) filtermap.erase(filtermap.find(name));
        if (val != "") filtermap.insert(filtered_pair(name, val));
    }

    void stringed_filterclass::addidxcriteria(const string name, const indx val) {
        indx_set* tmp = idxcriteria(name);
        indx_set newtmp;
        if (tmp != NULL) {
            newtmp.insert(tmp->begin(), tmp->end());
        }
        newtmp.insert(val);
        setidxcriteria(name, newtmp);
    }

    void stringed_filterclass::removeidxcriteria(const string name, const indx val) {
        indx_set* tmp = idxcriteria(name);
        indx_set newtmp;
        if (tmp != NULL) {
            newtmp.insert(tmp->begin(), tmp->end());
        }
        if (newtmp.find(val) != newtmp.end()) newtmp.erase(val);
        setidxcriteria(name, newtmp);
    }

    bool stringed_filterclass::included(const string name, string val) {
        if (!iscriteria(name)) return true;
        string tmpcriteria = findCriteria(name);
        boost::trim(tmpcriteria);
        if (tmpcriteria == "") return true;
        boost::regex xfnTemplete(tmpcriteria);
        std::string::const_iterator xItStart = val.begin();
        std::string::const_iterator xItEnd = val.end();
        boost::smatch xresults;
        return boost::regex_search(xItStart, xItEnd, xresults, xfnTemplete);
    }

    bool stringed_filterclass::includedidx(const string name, indx val) {
        if (!isidxcriteria(name)) return true;
        string tmpcriteria = findCriteria(name);
        boost::trim(tmpcriteria);
        if (tmpcriteria == "") return true;
        indx_set set_;
        getkeyswithstring(tmpcriteria, set_);
        return (set_.find(val) != set_.end());
    }

    void stringed_filterclass::clearcriteria() {
        criteria_ = "";
        filtermap.clear();
        filterkeymap.clear();
    }

    void stringed_filterclass::setidxcriteria(const string name, const indx_set& val) {
        clearidxcriteria(name);
        if (!val.empty()) filterkeymap.insert(filteredkey_pair(name, val));
    }

    void stringed_filterclass::readcriteria(const string name) {
        string crittmp = findCriteria(name);
        if (filtermap.find(name) != filtermap.end()) filtermap.erase(filtermap.find(name));
        if (crittmp != "") filtermap.insert(filtered_pair(name, crittmp));
    }

    void stringed_filterclass::readidxcriteria(const string name) {
        string crittmp = findCriteria(name);

        if (filterkeymap.find(name) != filterkeymap.end()) filterkeymap.erase(filterkeymap.find(name));
        if (crittmp != "") {
            indx_set tmpset;
            getkeyswithstring(crittmp, tmpset);
            filterkeymap.insert(filteredkey_pair(name, tmpset));
        }
    }

    void stringed_filterclass::readcriterias() {
        readcriteria(NAME_CRITERIA);
        readcriteria(COMMENT_CRITERIA);
        readcriteria(BIND_CRITERIA);
        readidxcriteria(GROUP_CRITERIA);
        readidxcriteria(TYPEGROUP_CRITERIA);
        readidxcriteria(TYPERT_CRITERIA);
    }

    string stringed_filterclass::findCriteria(string name) {
        boost::regex xfnTemplete(name + "=\"[*A-Za-z_$0-9, ]+\"\n");

        boost::smatch xresults;
        std::string::const_iterator xItStart = criteria_.begin();
        std::string::const_iterator xItEnd = criteria_.end();
        if (boost::regex_search(xItStart, xItEnd, xresults, xfnTemplete)) {
            boost::smatch::iterator it = xresults.begin();
            if (it != xresults.end()) {
                string tmpresult = *it;
                boost::replace_first(tmpresult, name + "=\"", "");
                boost::replace_last(tmpresult, "\"\n", "");
                boost::algorithm::trim(tmpresult);
                return tmpresult;
            }
        }
        return "";
    }

    void stringed_filterclass::getkeyswithstring(const std::string str_, indx_set& set_) {
        set_.clear();
        boost::char_separator<char> sep(",");
        chartokenizer tokens(str_, sep);
        for (chartokenizer::iterator tok_iter = tokens.begin();
                tok_iter != tokens.end(); ++tok_iter) {
            std::string tmpstr = *tok_iter;
            boost::trim(tmpstr);
            indx tmp;
            if (str_to(tmpstr, tmp)) {
                set_.insert(tmp);
            }
        }
    }

    void stringed_filterclass::setkeyswithstring(std::string& str_, const indx_set& set_) {
        indx_set::const_iterator it = set_.begin();
        str_ = "";
        for (indx_set::const_iterator it = set_.begin();
                it != set_.end(); ++it) {
            std::string tmpstr = to_str(*it);
            if (str_ == "") str_ += tmpstr;
            else {
                str_ = str_ + ", " + tmpstr;
            }
        }
    }
}

