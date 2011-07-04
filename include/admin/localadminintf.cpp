/* 
 * File:   kernel_nsLocalIntrface.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 21 Декабрь 2009 г., 17:02
 */

#include <admin/localadminintf.h>


namespace dvnci {
    namespace admin {


        using namespace std;
        
        /////////////////////////////////////////////////////////////////////////////

        void   localtagintf::name(const std::string& val) {
            if (exists()) {
                try {
                    intf->replace_tag(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void  localtagintf::group(indx val){
            if (exists()) {
                try {
                    intf->group(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void  localtagintf::agroup(indx val){
            if (exists()) {
                try {
                    intf->agroup(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        /////////////////////////////////////////////////////////////////////////////

        void   localgroupintf::name(const std::string& val) {
            if (exists()) {
                try {
                    intf->replace_group(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::host(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->host(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::user(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->user(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::password(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->password(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::server(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->server(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::group(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->group(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::port(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->port(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::topic(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->topic(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::ether(const std::string& val) {
            if (exists()) {
                try {
                    intf->groups()->ether(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};}};

        void   localgroupintf::appid(appidtype val) {
            if (exists()) {
                try {
                    intf->group_appid(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);}}};

        /////////////////////////////////////////////////////////////////////////////

        void   localuserintf::name(const std::string& val) {
            if (exists()) {
                try {
                    intf->replace_user(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};};};

        /////////////////////////////////////////////////////////////////////////////

        void   localaccessruleintf::name(const std::string& val) {
            if (exists()) {
                try {
                    intf->replace_accessrule(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};};};

        /////////////////////////////////////////////////////////////////////////////

        localadminintf::localadminintf(const fspath& pth, appidtype app, eventtypeset evts) : adminintf(), path(pth), appid(app), events(evts) {

            tag_ = tagintf_ptr(new localtagintf(this));
            group_ = groupintf_ptr(new localgroupintf(this));
            agroup_ = agroupintf_ptr(new localagroupintf(this));
            users_ = userintf_ptr(new localuserintf(this));
            accessrules_ = accessruleintf_ptr(new localaccessruleintf(this));
            journal_ = journalintf_ptr(new localjournalintf(this));
            alarms_ = alarmsintf_ptr(new localalarmsintf(this));
            reg_ = registryintf_ptr(new localregistryintf(this));
            clients_ = clientsintf_ptr(new localclientsintf(this));
            command_ = commandintf_ptr(new localcommandintf(this));
            debug_ = debugintf_ptr(new localdebugintf(this));
            clientmeta_ = metaintf_ptr(new localmetaintf(this));
            serviceintf_ = serviceintf_ptr(new localserviceintf());}

        bool localadminintf::connect(const std::string& user, const std::string& password) {
            clearerrors();
            if (_state == adminintf::connected) return true;
            try {
                DEBUG_STR_VAL_DVNCI(opend local, path);
                intf = new tagsbase(path , appid, events);
                _state = adminintf::connected;
                setintf(intf);
                metaintf_.connect(path);
                _error = 0;
                adminname = conf_property(NS_CNFG_ADMINNAME);
                DEBUG_STR_VAL_DVNCI(adminname, adminname);
                adminpassword = conf_property(NS_CNFG_ADMINPASS);
                DEBUG_STR_VAL_DVNCI(adminpass, adminpassword);
                isautorizated_ = true;
                return true;}
            catch (dvncierror& err) {
                setintf(0);
                _error = err.code();
                _state = adminintf::disconnected;
                adderror(err);}
            catch (...) {
                setintf(0);
                _error = 1;
                _state = adminintf::disconnected;
                dvncierror tmperr(NS_ERROR_NODEF);
                adderror(tmperr);}
            return false;};

        bool localadminintf::disconnect() {
            clearerrors();
            if (_state == adminintf::disconnected) {
                return true;}
            try {
                if (intf) delete intf;
                metaintf_.disconnect();
                _state = adminintf::disconnected;
                setintf(0);
                _error = 0;
                return true;}
            catch (dvncierror& err) {
                setintf(0);
                _error = err.code();
                _state = adminintf::disconnected;
                adderror(err);}
            catch (...) {
                setintf(0);
                _error = 1;
                _state = adminintf::disconnected;}
            return true;};

        void localadminintf::operation_mapprj(std::string path_) {
            // clearerrors();
            if (_state == adminintf::connected) {
                disconnect();}
            path = path_;
            connect();}

        void localadminintf::operation_unmapprj() {
            //   clearerrors();
            disconnect();};

        void localadminintf::operation_newprj(std::string path_) {
            //  clearerrors();
            if (_state == adminintf::connected) {
                disconnect();}
            path = path_;
            connect();};

        ns_error localadminintf::entities_signature(nodetype parenttp, indx parentid, iteminfo_map& mappack,
                const std::string& strcriteria ,  bool clearer ) {{
                THD_EXCLUSIVE_LOCK(mutex);
                if (clearer) clearerrors();
                mappack.clear();
                switch (parenttp) {

                    case NT_TAG:{
                        return NS_ERROR_SUCCESS;}

                    case NT_ATAG:{
                        return NS_ERROR_SUCCESS;}

                    case NT_GROUP:{
                        tags(mappack, parentid, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_AGROUP:{
                        atags(mappack, parentid, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_ROOT_GROUPS:{
                        groups(mappack, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_ROOT_AGROUPS:{
                        agroups(mappack, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_ROOT_USERS:{
                        users(mappack, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_ROOT_ACCESSRULES:{
                        accessrules(mappack, strcriteria);
                        return NS_ERROR_SUCCESS;}

                    case NT_ROOT_SERVICES:{
                        services(mappack);
                        return NS_ERROR_SUCCESS;}

                    default:{
                        if (nodetp_is_meta(parenttp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.sign(parenttp, parentid, mappack, strcriteria);
                                return NS_ERROR_SUCCESS;}}}}}
            adminintf::entities_signature(parenttp , parentid,  mappack, strcriteria);
            return NS_ERROR_SUCCESS;}

        bool localadminintf::tags(iteminfo_map& mappack, indx group, const std::string& strcriteria) {
            mappack.clear();
            intf->select_tags(mappack, group,  strcriteria);
            return true;}

        bool localadminintf::atags(iteminfo_map& mappack, indx agroup, const std::string& strcriteria) {
            mappack.clear();
            intf->select_atags(mappack, agroup,  strcriteria);
            return true;}

        bool localadminintf::groups(iteminfo_map& mappack, const std::string& strcriteria ) {
            mappack.clear();
            intf->select_groups(mappack, strcriteria);
            return true;}

        bool localadminintf::agroups(iteminfo_map& mappack, const std::string& strcriteria) {
            mappack.clear();
            intf->select_agroups(mappack, strcriteria);
            return true;}

        bool localadminintf::users(iteminfo_map& mappack, const std::string& strcriteria) {
            mappack.clear();
            intf->select_users(mappack, strcriteria);
            return true;}

        bool localadminintf::accessrules(iteminfo_map& mappack, const std::string& strcriteria) {
            mappack.clear();
            intf->select_accessrules(mappack, strcriteria);
            return true;}

        bool localadminintf::services(iteminfo_map& mappack, const std::string& strcriteria) {
            mappack.clear();
            if (svm()){ 
                svm()->signature(mappack);
                return true;}
            return false;}

        ns_error localadminintf::entities_internal_signature(nodetype ittp, indx_set& idset, iteminfo_map& mappack,
                const std::string& strcriteria  ) {{
                THD_EXCLUSIVE_LOCK(mutex);
                mappack.clear();
                switch (ittp) {
                    case NT_TAG:{
                        tags(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    case NT_ATAG:{
                        tags(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    case NT_GROUP:{
                        groups(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    case NT_AGROUP:{
                        agroups(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    case NT_ACCESSRULE:{
                        accessrules(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    case NT_USER:{
                        users(mappack, idset);
                        return NS_ERROR_SUCCESS;}

                    default:{
                        if (nodetp_is_meta(ittp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.sign(ittp, idset , mappack );
                                return NS_ERROR_SUCCESS;}}}}}
            return NS_ERROR_SUCCESS;}

        bool localadminintf::tags(iteminfo_map& mappack, indx_set& idset, const std::string& strcriteria  ) {
            mappack.clear();
            intf->select_tags(mappack, idset,  strcriteria);
            return true;}

        bool localadminintf::groups(iteminfo_map& mappack, indx_set& idset, const std::string& strcriteria ) {
            mappack.clear();
            intf->select_groups(mappack, idset, strcriteria);
            return true;}

        bool localadminintf::agroups(iteminfo_map& mappack, indx_set& idset, const std::string& strcriteri) {
            mappack.clear();
            intf->select_agroups(mappack, idset);
            return true;}

        bool localadminintf::users(iteminfo_map& mappack, indx_set& idset, const std::string& strcriteria) {
            mappack.clear();
            intf->select_users(mappack, idset, strcriteria);
            return true;}

        bool localadminintf::accessrules(iteminfo_map& mappack, indx_set& idset, const std::string& strcriteria ) {
            mappack.clear();
            intf->select_accessrules(mappack, idset, strcriteria);
            return true;}

        ns_error localadminintf::entities_merge(nodetype ittp,  indx_set& idset, iteminfo_map& mappack) {
            entities_internal_signature(ittp,  idset, mappack);
            adminintf::entities_merge(ittp, idset , mappack);
            return NS_ERROR_SUCCESS;};

        ns_error localadminintf::entity_create(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
                string newnm  ) {{
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                pairpack.first = npos;
                try {
                    switch (ittp) {
                        case NT_TAG:{
                            pairpack.first = createtag(newnm, parentid);
                            pairpack.second = name_with_type(newnm, NT_TAG);
                            break;}

                        case NT_GROUP:{
                            pairpack.first = creategroup(newnm);
                            pairpack.second = name_with_type(newnm, NT_GROUP);
                            break;}

                        case NT_AGROUP:{
                            pairpack.first = createagroup(newnm);
                            pairpack.second = name_with_type(newnm, NT_AGROUP);
                            break;}

                        case NT_USER:{
                            pairpack.first = createuser(newnm);
                            pairpack.second = name_with_type(newnm, NT_USER);
                            break;}

                        case NT_ACCESSRULE:{
                            pairpack.first = createaccessrule(newnm);
                            pairpack.second = name_with_type(newnm, NT_ACCESSRULE);
                            break;}

                        default:{
                            if (nodetp_is_meta(ittp)) {
                                if (metaintf_.state() == meta::connected) {
                                    metaintf_.add(ittp, parentid, pairpack, newnm );}}}}}
                catch (dvncierror& err_) {
                    adderror(err_);}
                return NS_ERROR_SUCCESS;}

            adminintf::entity_create(ittp, parentid, pairpack);
            return NS_ERROR_SUCCESS;};

        indx localadminintf::createtag( string name, string group) {
            return intf->insert_tag(name, group);}

        indx localadminintf::createtag( string name, indx group) {
            return intf->insert_tag(name, group);}

        indx localadminintf::creategroup( string name) {
            return intf->insert_group(name);}

        indx localadminintf::createagroup( string name) {
            return intf->insert_agroup(name);}

        indx localadminintf::createuser( string name) {
            return intf->insert_user(name);}

        indx localadminintf::createaccessrule( string name) {
            return intf->insert_accessrule(name);}

        ns_error localadminintf::entities_create(nodetype ittp, indx parentid, str_indx_map& mpnew) {
            THD_EXCLUSIVE_LOCK(mutex);
            try {
                switch (ittp) {
                    case NT_TAG:{
                        createtags(mpnew, parentid);
                        break;}}}
            catch (dvncierror& err_) {
                adderror(err_);}
            return NS_ERROR_SUCCESS;}

        void localadminintf::createtags( str_indx_map& mpnew, string group) {
            intf->insert_tags(mpnew, group);}

        void localadminintf::createtags( str_indx_map& mpnew, indx group) {
            intf->insert_tags(mpnew, group);}

        ns_error localadminintf::entities_erase(nodetype ittp, indx_set& idset) {{
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                indx_set::iterator it = idset.begin();
                if (nodetp_is_meta(ittp)) {
                    if (metaintf_.state() == meta::connected) {
                        metaintf_.remove(ittp, idset);}}
                else {
                    while (it != idset.end()) {

                        try {
                            switch (ittp) {
                                case NT_TAG:{
                                    deletetag(*it);
                                    break;}

                                case NT_GROUP:{
                                    deletegroup(*it);
                                    break;}

                                case NT_AGROUP:{
                                    deleteagroup(*it);
                                    break;}

                                case NT_USER:{
                                    deleteuser(*it);
                                    break;}

                                case NT_ACCESSRULE:{
                                    deleteaccessrule(*it);
                                    break;}

                                default:{}}}
                        catch (dvncierror& err_) {
                            adderror(err_);}
                        it++;}}}
            adminintf::entities_erase(ittp, idset);
            return NS_ERROR_SUCCESS;};

        bool localadminintf::deletetag(indx id) {
            return (id == intf->delete_tag(id));}

        bool localadminintf::deletegroup(indx id) {
            return (id == intf->delete_group(id));}

        bool localadminintf::deleteagroup(indx id) {
            return (id == intf->delete_agroup(id));}

        bool localadminintf::deleteuser(indx id) {
            return (id == intf->delete_user(id));}

        bool localadminintf::deleteaccessrule(indx id) {
            return (id == intf->delete_accessrule(id));}

        ns_error localadminintf::entities_change_parent(nodetype ittp, indx_set& idset, indx parentid) {
            THD_EXCLUSIVE_LOCK(mutex);
            try{
            clearerrors();
            switch (ittp) {
                case NT_TAG:{
                    changeparenttag(idset, parentid);
                    break;}

                case NT_ATAG:{
                    changeparentatag(idset, parentid);
                    break;}}}
            catch (dvncierror& err_) {
                   adderror(err_);}
            return NS_ERROR_SUCCESS;}

        bool localadminintf::changeparenttag( indx_set& idset, indx parentid) {
            indx_set::iterator it = idset.begin();
            while (it != idset.end()) {
                intf->group(*it, parentid);
                it++;}
            return true;}

        bool localadminintf::changeparentatag( indx_set& idset, indx parentid) {
            indx_set::iterator it = idset.begin();
            while (it != idset.end()) {
                intf->agroup(*it, parentid);
                it++;}
            return true;}

        ns_error localadminintf::entity_duplicate(nodetype ittp, indx id, const std::string& newname, iteminfo_pair& pairpack){
            THD_EXCLUSIVE_LOCK(mutex);
            clearerrors();
            try{
            pairpack.first=npos;
            switch (ittp) {
                case NT_GROUP:{
                    duplicategroup(id, newname, pairpack);
                    break;}}}
             catch (dvncierror& err_) {
                  adderror(err_);}

            return NS_ERROR_SUCCESS;}

        bool localadminintf::duplicategroup(indx id, const std::string& newname, iteminfo_pair& pairpack) {
            pairpack.first= intf->duplicate_group(id, newname);
            if (pairpack.first!=npos) {
                pairpack.second.name(newname);
                pairpack.second.typeex(nodeinfotype(NT_GROUP,intf->groups()->appid(pairpack.first)));}
            return true;}



        ns_error localadminintf::entities_merge(nodetype ittp,  indx_set& idset) {
            indx_set::iterator it = idset.begin();
            try{
            while (it != idset.end()) {
                switch (ittp) {
                    case NT_TAG:{
                        writetostoregetag(*it);
                        break;};
                    case NT_GROUP:{
                        writetostoregroup(*it);
                        break;};
                    case NT_AGROUP:{
                        writetostoreagroup(*it);
                        break;};
                    case NT_USER:{
                        writetostoreuser(*it);
                        break;};
                    case NT_ACCESSRULE:{
                        writetostoreaccessrule(*it);
                        break;};
                    default:{
                        if (nodetp_is_meta(ittp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.merge();}}}}
                it++;}}
           catch (dvncierror& err_) {
                  adderror(err_);}
            return NS_ERROR_SUCCESS;}

        bool localadminintf::entities_merge(nodetype ittp, indx id) {
            THD_EXCLUSIVE_LOCK(mutex);
            indx_set tmp;
            tmp.insert(id);
            return entities_merge(ittp, tmp);}

        bool localadminintf::writetostoregetag(indx id) {
            intf->merge_tag(id);
            return true;}

        bool localadminintf::writetostoregroup(indx id) {
            intf->merge_group(id);
            return true;}

        bool localadminintf::writetostoreagroup(indx id) {
            intf->merge_agroup(id);
            return true;}

        bool localadminintf::writetostoreuser(indx id) {
            intf->merge_user(id);
            return true;}

        bool localadminintf::writetostoreaccessrule(indx id) {
            intf->merge_accessrule(id);
            return true;}

        string localadminintf::conf_property(const confproptype& name) const {
            return (intf) ? intf->conf_property(name) : "";}

        int localadminintf::conf_numproperty(const confproptype& name) {
            return (intf) ?  intf->conf_numproperty<int>(name) : 0;}

        void localadminintf::conf_property(const confproptype& name, const std::string& val) {
            if (intf) intf->conf_property(name, val);}

        void localadminintf::conf_property(const confproptype& name, int val) {
            if (intf) intf->conf_property(name, val);}

        bool localadminintf::operation_setvalue(indx id, const std::string& val, vlvtype valid) {
            if (intf) {
                intf->write_val(id, val, valid);
                return true;}
            return false;}

        bool localadminintf::operation_setvalid(indx id, vlvtype valid) {
            if (intf) {
                intf->valid(id, valid);
                return true;}
            return false;}

        bool localadminintf::operation_setallvalid(vlvtype valid) {
            if (intf) {
                intf->allvalid(valid);
                return true;}
            return false;}

        bool localadminintf::operation_setcounter(indx id, bool inc) {
            if (intf) {
                inc ?  intf->incref(id) : intf->decref(id);
                return true;}
            return false;}

        bool localadminintf::operation_setallcounter(bool inc) {
            if (intf) {
                intf->incallcounter(inc);
                return true;}
            return false;}

        bool localadminintf::operation_kvit() {
            if (intf) {
                intf->kvit();
                return true;}
            return false;}

        bool localadminintf::operation_kvitgroup(indx id) {
            if (intf) {
                //intf->kvit_group(id);
                return true;}
            return false;}

        bool localadminintf::operation_kvitagroup(indx id) {
            if (intf) {
                //intf->kvit_agroup(id);
                return true;}
            return false;}

        bool localadminintf::operation_send_command(indx id, std::string val, bool setqueue) {
            if (intf) {
                intf->send_command(id, val, setqueue);
                return true;}
            return false;}

        ns_error localadminintf::operation_autorizate(const std::string& user, const std::string& password, const std::string& hst, const std::string& ipadr) {
            return (intf->regclient(hst, ipadr, user, password)) ? NS_ERROR_SUCCESS : ERROR_AUTORIZATION_FAIL;}

        bool localadminintf::operation_startservice(appidtype val) {
            OUTSTRVAL_DVNCI(operation_startservice, val) ;
            return svm() ? svm()->operation( val, SERVICE_OPEATION_START) : false;}

        bool localadminintf::operation_stopservice(appidtype val) {
            return  svm() ? svm()->operation(val, SERVICE_OPEATION_STOP) : false;}
        
        servicemanager_ptr localadminintf::svm() const{
            if (dynamic_cast<localserviceintf*> (serviceintf_.get()))
                return dynamic_cast<localserviceintf*> (serviceintf_.get())->svm_;
		    return servicemanager_ptr();} 

        void localadminintf::setintf(tagsbase* intf_) {
            intf = intf_;
            dynamic_cast<localtagintf*> (tag_.get())->setintf(intf);
            dynamic_cast<localgroupintf*> (group_.get())->setintf(intf);
            dynamic_cast<localagroupintf*> (agroup_.get())->setintf(intf);
            dynamic_cast<localuserintf*> (users_.get())->setintf(intf);
            dynamic_cast<localaccessruleintf*> (accessrules_.get())->setintf(intf);
            dynamic_cast<localclientsintf*> (clients_.get())->setintf(intf);
            dynamic_cast<localjournalintf*> (journal_.get())->setintf(intf);
            dynamic_cast<localalarmsintf*> (alarms_.get())->setintf(intf);
            dynamic_cast<localregistryintf*> (reg_.get())->setintf(intf);
            dynamic_cast<localcommandintf*> (command_.get())->setintf(intf);
            dynamic_cast<localdebugintf*> (debug_.get())->setintf(intf);
            dynamic_cast<localmetaintf*> (clientmeta_.get())->setintf(&metaintf_);};}}


