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
                    intf->rename_tag(key_, val);}
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
                    intf->rename_group(key_, val);}
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
                    intf->rename_user(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};};};

        /////////////////////////////////////////////////////////////////////////////

        void   localaccessruleintf::name(const std::string& val) {
            if (exists()) {
                try {
                    intf->rename_accessrule(key_, val);}
                catch (dvncierror& err_) {
                    root->adderror(err_);};};};

        /////////////////////////////////////////////////////////////////////////////

        localadminintf::localadminintf(const fspath& pth, appidtype app, eventtypeset evts) : adminintf(), path(pth), 
                appid(app), events(evts),  regclid(0) {
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
            serviceintf_ = serviceintf_ptr(new localserviceintf()); std::cout  << "Start local5"  << std::endl;
            ;};
        
        localadminintf::localadminintf(tagsbase_ptr inf) : adminintf(), intf(inf),  
                appid(0), events(0),  regclid(0){
            if (intf) path=intf->path();
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
            serviceintf_ = serviceintf_ptr(new localserviceintf());
            if (intf) {
                _state = adminintf::connected;
                setintf(intf.get());
                metaintf_.connect(path);
                _error = 0;
                adminname = conf_property(NS_CNFG_ADMINNAME);}
            else{
                setintf(0);
                _error = 1;
                _state = adminintf::disconnected;}}

        bool localadminintf::connect(const std::string& user, const std::string& password) {
            clearerrors();
            if (_state == adminintf::connected) return true;
            try {
                DEBUG_STR_VAL_DVNCI(opend local, path);
                if ((path.string().empty()) || (!boost::filesystem::exists(path)))
                    return false;
                intf = tagsbase_ptr (new tagsbase(path , appid, events));
                _state = adminintf::connected;
                setintf(intf.get());
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
            if (regclid){ 
                    intf->unregclient(regclid);}
            if (_state == adminintf::disconnected) {
                return true;}
            try {
                metaintf_.disconnect();
                _state = adminintf::disconnected;
                setintf(0);
                intf.reset();
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

        ns_error localadminintf::select_entities(nodetype parenttp,  iteminfo_map& mappack, indx parentid,
			const std::string& strcriteria ,  bool clearer ) {{
				THD_EXCLUSIVE_LOCK(mutex);
                if (clearer) clearerrors();
                mappack.clear();
                switch (parenttp) {

                    case NT_TAG:
                    case NT_ATAG:
                    case NT_GROUP:
                    case NT_AGROUP:
                    case NT_ROOT_GROUPS:
                    case NT_ROOT_AGROUPS:
                    case NT_ROOT_USERS:
                    case NT_ROOT_ACCESSRULES:{
                        intf->select_entities(nodetp_child_by_parent(parenttp),mappack, parentid, strcriteria);
                        return 0;}

                    case NT_ROOT_SERVICES:{
                        mappack.clear();
                        if (!svm())
                            std::cout << "SVM: !!!!!!!!!!!!!!!!"  << std::endl;
                        else
                            std::cout << "SVM: "  << std::endl;
                        if (svm()){ 
                             svm()->signature(mappack);
                             return 0;}
                        return NS_ERROR_ENTITY_OPERATE;}

                    default:{
                        if (nodetp_is_meta(parenttp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.sign(parenttp, parentid, mappack, strcriteria);
								return 0;}}}}}
            adminintf::select_entities(parenttp ,  mappack, parentid, strcriteria);
            return NS_ERROR_ENTITY_OPERATE;}



        ns_error localadminintf::entities_internal_signature(nodetype ittp, indx_set& idset, iteminfo_map& mappack,
                const std::string& strcriteria  ) {{
                THD_EXCLUSIVE_LOCK(mutex);
                mappack.clear();
                switch (ittp) {
                    case NT_TAG:
                    case NT_ATAG:
                    case NT_GROUP:
                    case NT_AGROUP:
                    case NT_ACCESSRULE:
                    case NT_USER:{
                        return intf->select_entities(ittp, mappack, idset, strcriteria);}
                    default:{
                        if (nodetp_is_meta(ittp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.sign(ittp, idset , mappack );
                                return NS_ERROR_SUCCESS;}}}}}
            return NS_ERROR_ENTITY_OPERATE;}
        


        ns_error localadminintf::merge_entities(nodetype ittp,  indx_set& idset, iteminfo_map& mappack) {
            entities_internal_signature(ittp,  idset, mappack);
            adminintf::merge_entities(ittp, idset , mappack);
            return NS_ERROR_SUCCESS;};
            
            

        ns_error localadminintf::insert_entity(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
			string newnm  ) {
				ns_error errrst=0;{
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                pairpack.first = npos;
                try {
                    switch (ittp) {
                        case NT_TAG:
                        case NT_GROUP:
                        case NT_AGROUP:
                        case NT_USER:
                        case NT_ACCESSRULE:{
                            pairpack.first = intf->insert_entity(ittp, newnm, errrst, parentid);
                            pairpack.second = name_with_type(newnm, ittp);
                            if (errrst)
                                 adderror(dvncierror(errrst));
                            break;}

                        default:{
                            if (nodetp_is_meta(ittp)) {
                                if (metaintf_.state() == meta::connected) {
                                    metaintf_.add(ittp, parentid, pairpack, newnm );}}}}}
                catch (dvncierror& err_) {
                    errrst=err_.code();
                    adderror(err_);}
				return errrst;}

            adminintf::insert_entity(ittp, parentid, pairpack);
            return errrst;};



        ns_error localadminintf::insert_entities(nodetype ittp, indx parentid, str_indx_map& mpnew) {
            THD_EXCLUSIVE_LOCK(mutex);
            try {
                switch (ittp) {
                    case NT_TAG:{
                        createtags(mpnew, parentid);
                        break;}}}
            catch (dvncierror& err_) {
                adderror(err_);}
            return 0;}

        void localadminintf::createtags( str_indx_map& mpnew, string group) {
            intf->insert_tags(mpnew, group);}

        void localadminintf::createtags( str_indx_map& mpnew, indx group) {
            intf->insert_tags(mpnew, group);}
        
        

        ns_error localadminintf::delete_entities(nodetype ittp, const indx_set& idset) {{
		THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                indx_set::const_iterator it = idset.begin();
                if (nodetp_is_meta(ittp)) {
                    if (metaintf_.state() == meta::connected) {
                        metaintf_.remove(ittp, idset);}}
                else {
                    while (it != idset.end()) {
                        try {
                            switch (ittp) {
                                case NT_TAG:
                                case NT_GROUP:
                                case NT_AGROUP:
                                case NT_USER:
                                case NT_ACCESSRULE:{
                                    intf->delete_entity(ittp, *it);
                                    break;}

                                default:{}}}
                        catch (dvncierror& err_) {
                            adderror(err_);}
						it++;}}}
            adminintf::delete_entities(ittp, idset);
            return 0;};


        ns_error localadminintf::change_parent_entities(nodetype ittp, indx_set& idset, indx parentid) {
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
        

        ns_error localadminintf::duplicate_entity(nodetype ittp, indx id, const std::string& newname, iteminfo_pair& pairpack){
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
            return 0;}

        bool localadminintf::duplicategroup(indx id, const std::string& newname, iteminfo_pair& pairpack) {
            pairpack.first= intf->duplicate_group(id, newname);
            if (pairpack.first!=npos) {
                pairpack.second.name(newname);
                pairpack.second.typeex(nodeinfotype(NT_GROUP,intf->groups()->appid(pairpack.first)));}
            return true;}



        ns_error localadminintf::merge_entities(nodetype ittp, const indx_set& idset) {
            indx_set::const_iterator it = idset.begin();
            try{
            while (it != idset.end()) {
                switch (ittp) {
                    case NT_TAG:
                    case NT_GROUP:
                    case NT_AGROUP:
                    case NT_USER:
                    case NT_ACCESSRULE:{
                        intf->merge_entity(ittp, *it);
                        break;};
                    default:{
                        if (nodetp_is_meta(ittp)) {
                            if (metaintf_.state() == meta::connected) {
                                metaintf_.merge();}}}}
                it++;}}
           catch (dvncierror& err_) {
                  adderror(err_);}
            return 0;}

        bool localadminintf::merge_entities(nodetype ittp, indx id) {
            THD_EXCLUSIVE_LOCK(mutex);
            indx_set tmp;
            tmp.insert(id);
            return merge_entities(ittp, tmp);}



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
                intf->send_command(id, val, setqueue ? acQueuedCommand : acNewCommand );
                return true;}
            return false;}

        ns_error localadminintf::operation_autorizate(const std::string& user, const std::string& password) {
             if (!isautorizated_){
                  regclid=intf->regclient(address.to_string(),"IP",user, password);
                  if (regclid) {
                       isautorizated_=true;
                        return 0;}
                    else{
                      isautorizated_=false;
                      return ERROR_AUTORIZATION_FAIL;}}      
                return 0;}

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
            dynamic_cast<localtagintf*> (tag_.get())->setintf(intf.get());
            dynamic_cast<localgroupintf*> (group_.get())->setintf(intf.get());
            dynamic_cast<localagroupintf*> (agroup_.get())->setintf(intf.get());
            dynamic_cast<localuserintf*> (users_.get())->setintf(intf.get());
            dynamic_cast<localaccessruleintf*> (accessrules_.get())->setintf(intf.get());
            dynamic_cast<localclientsintf*> (clients_.get())->setintf(intf.get());
            dynamic_cast<localjournalintf*> (journal_.get())->setintf(intf.get());
            dynamic_cast<localalarmsintf*> (alarms_.get())->setintf(intf.get());
            dynamic_cast<localregistryintf*> (reg_.get())->setintf(intf.get());
            dynamic_cast<localcommandintf*> (command_.get())->setintf(intf.get());
            dynamic_cast<localdebugintf*> (debug_.get())->setintf(intf.get());
            dynamic_cast<localmetaintf*> (clientmeta_.get())->setintf(&metaintf_);};}}


