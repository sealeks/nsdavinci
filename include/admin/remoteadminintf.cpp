/* 
 * File:   kernel_nsRemoteInterface.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 8 Январь 2010 г., 23:00
 */

#include <admin/remoteadminintf.h>

namespace dvnci {
    namespace admin {

        using namespace dvnci::rpc;
        using namespace std;

        size_t remoteregistryintf::load() {
            return rintf.regs_net_req(vect, version_);}

        size_t remoteclientsintf::load() {
            return rintf.clients_net_req(vect, version_);}

        size_t remotealarmsintf::load(const std::string& grp , const std::string& agrp ) {
            return rintf.alarms_net_req(vect, version_, grp, agrp);}

        size_t remotecommandintf::load(const std::string& grp) {
            return rintf.commands_net_req(vect, version_, grp);}

        size_t remotejournalintf::load(const std::string& agroup ) {
            vect_journal_data vect;
            rintf.journal_net_req(vect,  guid_, cursor_, count_);
            filldata(vect);
            return count_;}

        size_t remotedebugintf::load(debuglvtype lev) {
            vect_debug_data vect;
            rintf.debug_net_req(vect,  guid_, cursor_, count_);
            filldata(vect);
            return count_;}

        remotemetaintf::remotemetaintf(entitytype_metamaps_maps* maps_) : metaintf() {
            maps = maps_;
            maps->insert(nodetype_metamap_pair(NT_MF_ROOT, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_HOME, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_REPLIST, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_TRENDLIST, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_MESSLIST, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_REPHEADER, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_TRENDHEADER, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_MESSHEADER, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_REPARR, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_TRENDARR, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_MESSARR, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_UNIT, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_TREND, indx_metaitem_map()));
            maps->insert(nodetype_metamap_pair(NT_MF_MESSAGE, indx_metaitem_map()));};

        remoteadminintf::remoteadminintf(std::string hst, std::string port_, unsigned int timout) : adminintf(),  client_io( new dvnci::rpc::rpcioclient()) {
            host_= hst;
            port = port_;
            timeout = in_bounded<unsigned int>(100, 600000, timout);
            tag_ = tagintf_ptr(new remotetagintf(&tags_map));
            group_ = groupintf_ptr(new remotegroupintf(&groups_map));
            agroup_ = agroupintf_ptr(new remoteagroupintf(&agroups_map));
            clientmeta_ = metaintf_ptr(new remotemetaintf(&meta_maps));
            users_ = userintf_ptr(new remoteuserintf(&users_map));
            accessrules_ = accessruleintf_ptr(new remoteaccessruleintf(&accessrules_map));
            reg_ = registryintf_ptr(new remoteregistryintf(*this));
            debug_ = debugintf_ptr(new remotedebugintf(*this));
            command_ = commandintf_ptr(new remotecommandintf(*this));
            journal_ = journalintf_ptr(new remotejournalintf(*this));
            alarms_ = alarmsintf_ptr(new remotealarmsintf(*this));
            clients_ = clientsintf_ptr(new remoteclientsintf(*this));
            serviceintf_ = serviceintf_ptr(new remoteserviceintf(&services_map));}

        ns_error remoteadminintf::entities_internal_signature(nodetype ittp, indx_set& idset, iteminfo_map& mappack,
                const std::string&  strcriteria, num64 numcriteria) {

            mappack.clear();
            switch (ittp) {
                case NT_ROOT_SERVERS_AVAIL_R:
                case NT_ROOT_SERVERS_AVAIL:{
                    return NS_ERROR_SUCCESS;}

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

                case NT_USER:{
                    users(mappack, idset);
                    return NS_ERROR_SUCCESS;}

                default:{
                    if (nodetp_is_meta(ittp)) {
                        metas(ittp, mappack, idset  );
                        return NS_ERROR_SUCCESS;}}}
            return NS_ERROR_SUCCESS;}

        bool remoteadminintf::tags(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria , num64 numcriteria) {
            mappack.clear();
            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                mappack.insert(iteminfo_pair(*it, name_with_type(tag(*it).name(), NT_TAG,  tag(*it).type(), group(tag(*it).group()).appid())));}
            return true;}

        bool remoteadminintf::groups(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria , num64 numcriteria) {
            mappack.clear();
            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                mappack.insert(iteminfo_pair(*it, name_with_type(group(*it).name(), NT_GROUP,  static_cast<appidtype> (group(*it).appid()))));}
            return true;}

        bool remoteadminintf::agroups(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria , num64 numcriteria) {
            mappack.clear();
            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                mappack.insert(iteminfo_pair(*it, name_with_type(agroup(*it).name(), NT_AGROUP)));}
            return true;}

        bool remoteadminintf::users(iteminfo_map& mappack, indx_set& idset, std::string  strcriteria , num64 numcriteria) {
            mappack.clear();
            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                mappack.insert(iteminfo_pair(*it, name_with_type(user(*it).name(), NT_USER)));}
            return true;}

        bool remoteadminintf::metas(nodetype ittp, iteminfo_map& mappack, indx_set& idset, std::string  strcriteria , num64 numcriteria) {
            mappack.clear();
            std::string  nm_attr = dvnci::meta::nameAttribute(ittp);
            if (nm_attr == "") return true;
            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                mappack.insert(iteminfo_pair(*it, name_with_type(meta(ittp, *it).property(nm_attr), ittp)));}
            return true;}

        ns_error remoteadminintf::entities_load(nodetype ittp,  indx_set& idset) {
            THD_EXCLUSIVE_LOCK(mutex);
            clearerrors();
            switch (ittp) {
                case NT_TAG:               return readtags(idset);
                case NT_ATAG:              return readtags(idset);
                case NT_GROUP:             return readgroups(idset);
                case NT_AGROUP:            return readagroups(idset);
                case NT_USER:              return readusers(idset);
                case NT_ACCESSRULE:        return readaccessrules(idset);
                case NT_SERVICE:           return readservices(idset);
                case NT_ROOT_SERVERS_AVAIL_R:
                case NT_ROOT_SERVERS_AVAIL:  return readconfig(idset);
                default: if (nodetp_is_meta(ittp)) return readmetas(ittp, idset);}
            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::entities_merge(nodetype ittp,  indx_set& idset, iteminfo_map& mappack) {{
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                switch (ittp) {
                    case NT_TAG:{
                        sendtags(idset);
                        break;}
                    case NT_ATAG:{
                        sendtags(idset);
                        break;}
                    case NT_GROUP:{
                        sendgroups(idset);
                        break;}
                    case NT_AGROUP:{
                        sendagroups(idset);
                        break;}
                    case NT_USER:{
                        sendusers(idset);
                        break;}
                    case NT_ACCESSRULE:{
                        sendaccessrules(idset);
                        break;}
                    case NT_SERVICE:{
                        sendservices(idset);
                        break;}
                    case NT_ROOT_SERVERS_AVAIL:{
                        sendconfig(idset);
                        break;}
                    default: if (nodetp_is_meta(ittp)) sendmetas(ittp, idset);}
                entities_internal_signature(ittp, idset, mappack);}
            adminintf::entities_merge(ittp, idset, mappack);
            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::entities_change_parent(nodetype ittp, indx_set& idset, indx parentid) {
            THD_EXCLUSIVE_LOCK(mutex);
            clearerrors();
            try{
            switch (ittp) {
                case NT_TAG:{
                    changeparenttag(idset, parentid);
                    break;}

                case NT_ATAG:{
                    changeparentatag(idset, parentid);
                    break;}

                default: return NS_ERROR_SUCCESS;}
            iteminfo_map tmpmap_;

            entities_merge(ittp, idset, tmpmap_);}
            catch (dvncierror& err_) {
                  adderror(err_);}

            return NS_ERROR_SUCCESS;}

        bool remoteadminintf::changeparenttag( indx_set& idset, indx parentid) {

            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                tag(*it).group(parentid);}
            return true;}

        bool remoteadminintf::changeparentatag( indx_set& idset, indx parentid) {

            for (indx_set::iterator it = idset.begin(); it != idset.end(); ++it) {
                tag(*it).agroup(parentid);}
            return true;}

        std::string  remoteadminintf::conf_property(const confproptype&  name) const {
            confinfo_map::const_iterator it = config_map.find(name);
            return (it != config_map.end()) ? config_.str_data[it->second] : "";}

        int remoteadminintf::conf_numproperty(const confproptype&  name) {
            confinfo_map::iterator it = config_map.find(name);
            std::string tmp = (it != config_map.end()) ? config_.str_data[it->second] : "";
            int reslt = 0;
            if (tmp == "") return 0;
            if (str_to(tmp, reslt)) return reslt;
            return 0;}

        void remoteadminintf::conf_property(const confproptype&  name, const std::string&  val) {
            confinfo_map::iterator it = config_map.find(name);
            if (it != config_map.end()) {
                config_.str_data[it->second] = val;
                config_.changeset |= (0x1LL << it->second);}}

        void remoteadminintf::conf_property(const confproptype&  name, int val) {
            confinfo_map::iterator it = config_map.find(name);
            if (it != config_map.end()) {
                std::string tmp = "";
                config_.str_data[it->second] = to_str(val);
                config_.changeset |= (0x1LL << it->second);}}

        bool remoteadminintf::operation_setvalue(indx id, const std::string& val, vlvtype valid) {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_SET_VALUE;
            execute_op.numpar2 = id;
            execute_op.strpar1 = val;
            execute_op.numpar3 = valid;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_setvalid(indx id, vlvtype valid) {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_SET_VALID;
            execute_op.numpar2 = id;
            execute_op.numpar3 = valid;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_setallvalid(vlvtype valid) {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_SETALL_VALID;
            execute_op.numpar2 = valid;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_setcounter(indx id, bool inc) {
            req_adminoperation execute_op;
            execute_op.numpar1 = inc ? OPERATION_INCCOUNT : OPERATION_DECCOUNT;
            execute_op.numpar2 = id;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_setallcounter(bool inc) {
            req_adminoperation execute_op;
            execute_op.numpar1 = inc ? OPERATION_INCCOUNTALL : OPERATION_DECCOUNTALL;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_kvit() {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_ACTION_KVIT;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_kvitgroup(indx id) {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_KVIT_GROUP;
            execute_op.numpar2 = id;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_kvitagroup(indx id) {
            req_adminoperation execute_op;
            execute_op.numpar1 = OPERATION_KVIT_AGROUP;
            execute_op.numpar2 = id;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_startservice(appidtype val) {
            req_adminoperation execute_op;
            execute_op.numpar1 = SERVICE_OPEATION_START;
            execute_op.numpar2 = val;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::operation_stopservice(appidtype val) {
            req_adminoperation execute_op;
            execute_op.numpar1 = SERVICE_OPEATION_STOP;
            execute_op.numpar2 = val;
            executeoperation(execute_op);
            return true;}

        bool remoteadminintf::connect_(std::string user, std::string password) {

            try {
                client_io->connect(host_, port, timeout);
                _state = (client_io->state() == client_io->connected ) ?
                        adminintf::connected :  adminintf::disconnected;
                if (client_io->state() == client_io->connected) {
                    ns_error tmperror = operation_autorizate(user, password);
                    if (tmperror != NS_ERROR_SUCCESS) {
                        client_io->disconnect();
                        _state = adminintf::disconnected;
                        if (tmperror == ERROR_AUTORIZATION_FAIL) throw dvncierror(ERROR_AUTORIZATION_FAIL);
                        dvncierror tmperr(tmperror);
                        adderror(tmperr);}}
                else {
                    dvncierror tmperr(ERROR_BASENOTFOUND);
                    adderror(tmperr);}}
            catch (dvncierror& err_) {
                if ((err_.code() == ERROR_FAILNET_CONNECTED) || (err_.code() == ERROR_NONET_CONNECTED) || (err_.code() == ERROR_AUTORIZATION_FAIL)) {
                    releaseconnection();
                    throw err_;}
                adderror(err_);}
            catch (...) {
                _state = (client_io->state() == client_io->connected ) ?
                        adminintf::connected :  adminintf::disconnected;
                if (client_io->state() == client_io->connected) {
                    dvncierror tmperr(ERROR_BASENOTFOUND);
                    adderror(tmperr);}}

            return (_state == adminintf::connected);}

        bool remoteadminintf::disconnect_() {
            try {
                client_io->disconnect();
                _state = (client_io->state() == client_io->connected ) ?
                        adminintf::connected :  adminintf::disconnected;}
            catch (...) {
                _state = (client_io->state() == client_io->connected ) ?
                        adminintf::connected :  adminintf::disconnected;}

            return (_state == adminintf::disconnected);}

        ns_error remoteadminintf::entities_signature(nodetype parenttp, indx parentid, iteminfo_map& mappack,
                const std::string& strcriteria , num64 numcriteria, bool clearer) {{

                THD_EXCLUSIVE_LOCK(mutex);
                if (clearer) clearerrors();
                try {
                    mappack.clear();
                    req_entitysigs tmpreq;
                    resp_entitysigs tpmresp;

                    tmpreq.tpitem = static_cast<num64> (parenttp);
                    tmpreq.parentid = static_cast<num64> (parentid);
                    tmpreq.numcriteria = numcriteria;
                    tmpreq.strcriteria = strcriteria;

                    if (querytmpl<req_entitysigs, resp_entitysigs, RPC_OPERATION_REQ_ENTITYSIGS, RPC_OPERATION_RESP_ENTITYSIGS > (tmpreq, tpmresp)) {
                        mappack << tpmresp;}}

                catch (dvncierror& err) {
                    parseerror(err);}
                catch (...) {
                    parseundeferror();}}

            adminintf::entities_signature(parenttp, parentid,  mappack, strcriteria, numcriteria);
            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readtags(indx_set& idset) {

            try {
                req_tags tmpreq;
                resp_tags tpmresp;

                tmpreq << idset;

                if (querytmpl<req_tags, resp_tags, RPC_OPERATION_REQ_TAGS, RPC_OPERATION_RESP_TAGS > (tmpreq, tpmresp)) {
                    tags_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendtags(indx_set& idset) {

            try {
                req_sendtags tmpreq;
                resp_sendtags tpmresp;

                assign_tag_data(idset, tmpreq.tags);

                for (vect_tag_data::iterator it = tmpreq.tags.begin(); it != tmpreq.tags.end(); ++it) {
                    it->changeset = ((remotetagintf&) (tag(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendtags, resp_sendtags, RPC_OPERATION_REQ_SENDTAGS, RPC_OPERATION_RESP_SENDTAGS > (tmpreq, tpmresp)) {
                    tags_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readgroups(indx_set& idset) {

            try {
                req_groups tmpreq;
                resp_groups tpmresp;

                tmpreq << idset;

                if (querytmpl<req_groups, resp_groups, RPC_OPERATION_REQ_GROUPS, RPC_OPERATION_RESP_GROUPS > (tmpreq, tpmresp)) {
                    groups_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendgroups(indx_set& idset) {
            try {
                req_sendgroups tmpreq;
                resp_sendgroups tpmresp;


                assign_group_data(idset, tmpreq.groups);

                for (vect_group_data::iterator it = tmpreq.groups.begin(); it != tmpreq.groups.end(); ++it) {
                    it->changeset = ((remotegroupintf&) (group(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendgroups, resp_sendgroups, RPC_OPERATION_REQ_SENDGROUPS, RPC_OPERATION_RESP_SENDGROUPS > (tmpreq, tpmresp)) {
                    groups_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readagroups(indx_set& idset) {

            try {
                req_agroups tmpreq;
                resp_agroups tpmresp;

                tmpreq << idset;

                if (querytmpl<req_agroups, resp_agroups, RPC_OPERATION_REQ_AGROUPS, RPC_OPERATION_RESP_AGROUPS > (tmpreq, tpmresp)) {
                    agroups_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendagroups(indx_set& idset) {
            try {
                req_sendagroups tmpreq;
                resp_sendagroups tpmresp;


                assign_agroup_data(idset, tmpreq.agroups);

                for (vect_agroup_data::iterator it = tmpreq.agroups.begin(); it != tmpreq.agroups.end(); ++it) {
                    it->changeset = ((remoteagroupintf&) (agroup(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendagroups, resp_sendagroups, RPC_OPERATION_REQ_SENDAGROUPS, RPC_OPERATION_RESP_SENDAGROUPS > (tmpreq, tpmresp)) {
                    agroups_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readusers(indx_set& idset) {

            try {
                req_users tmpreq;
                resp_users tpmresp;

                tmpreq << idset;

                if (querytmpl<req_users, resp_users, RPC_OPERATION_REQ_USERS, RPC_OPERATION_RESP_USERS > (tmpreq, tpmresp)) {
                    users_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}


        ns_error  remoteadminintf::sendusers(indx_set& idset) {
            try {
                req_sendusers tmpreq;
                resp_sendusers tpmresp;


                assign_user_data(idset, tmpreq.users);

                for (vect_user_data::iterator it = tmpreq.users.begin(); it != tmpreq.users.end(); ++it) {
                    it->changeset = ((remoteuserintf&) (user(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendusers, resp_sendusers, RPC_OPERATION_REQ_SENDUSERS, RPC_OPERATION_RESP_SENDUSERS > (tmpreq, tpmresp)) {
                    users_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}
            return NS_ERROR_SUCCESS;}
     
        ns_error remoteadminintf::readaccessrules(indx_set& idset) {

            try {
                req_accessrules tmpreq;
                resp_accessrules tpmresp;

                tmpreq << idset;

                if (querytmpl<req_accessrules, resp_accessrules, RPC_OPERATION_REQ_ACCESSRULES, RPC_OPERATION_RESP_ACCESSRULES > (tmpreq, tpmresp)) {
                    accessrules_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}


           ns_error  remoteadminintf::sendaccessrules(indx_set& idset) {
            try {
                req_sendaccessrules tmpreq;
                resp_sendaccessrules tpmresp;


                assign_accessrule_data(idset, tmpreq.accessrules);

                for (vect_accessrule_data::iterator it = tmpreq.accessrules.begin(); it != tmpreq.accessrules.end(); ++it) {
                    it->changeset = ((remoteaccessruleintf&) (accessrule(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendaccessrules, resp_sendaccessrules, RPC_OPERATION_REQ_SENDACCESSRULES, RPC_OPERATION_RESP_SENDACCESSRULES > (tmpreq, tpmresp)) {
                    accessrules_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}
            return NS_ERROR_SUCCESS;}



        ns_error remoteadminintf::readservices(indx_set& idset) {
            try {
                req_services tmpreq;
                resp_services tpmresp;

                tmpreq << idset;

                if (querytmpl<req_services, resp_services, RPC_OPERATION_REQ_SERVICES, RPC_OPERATION_RESP_SERVICES > (tmpreq, tpmresp)) {
                    services_map << tpmresp;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendservices(indx_set& idset) {
            try {
                req_sendservices tmpreq;
                resp_sendservices tpmresp;


                assign_service_data(idset, tmpreq.services);

                for (vect_service_data::iterator it = tmpreq.services.begin(); it != tmpreq.services.end(); ++it) {
                    it->changeset = ((remoteserviceintf&) (service(static_cast<indx> (it->key)))).gets_()->changeset;}

                if (querytmpl<req_sendservices, resp_sendservices, RPC_OPERATION_REQ_SENDSERVICES, RPC_OPERATION_RESP_SENDSERVICES > (tmpreq, tpmresp)) {
                    services_map << tpmresp;
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readconfig(indx_set& idset) {
            try {
                req_config tmpreq;
                resp_config tpmresp;
                tmpreq.ver = intrf_ver;

                tmpreq << idset;

                if (querytmpl<req_config, resp_config, RPC_OPERATION_REQ_CONFIG, RPC_OPERATION_RESP_CONFIG > (tmpreq, tpmresp)) {
                    for (confinfo_map::iterator it = config_map.begin(); it != config_map.end(); ++it) {
                        if (it->second < 20) {
                            config_.str_data[it->second] = tpmresp.config.str_data[it->second];};}
                    config_.changeset = 0;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendconfig(indx_set& idset) {
            try {
                req_sendconfig tmpreq;
                resp_sendconfig tpmresp;

                assign_config_data(idset, tmpreq.config);

                tmpreq.config.changeset = config_.changeset;


                if (querytmpl<req_sendconfig, resp_sendconfig, RPC_OPERATION_REQ_SENDCONFIG, RPC_OPERATION_RESP_SENDCONFIG > (tmpreq, tpmresp)) {
                    for (confinfo_map::iterator it = config_map.begin(); it != config_map.end(); ++it) {
                        if (it->second < 20) {
                            config_.str_data[it->second] = tpmresp.config.str_data[it->second];};}
                    config_.changeset = 0;}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::readmetas(nodetype ittp, indx_set& idset) {
            try {
                req_metas tmpreq;
                resp_metas tpmresp;

                tmpreq << idset;
                tmpreq.meta_type = ittp;

                if (querytmpl<req_metas, resp_metas, RPC_OPERATION_REQ_METAS, RPC_OPERATION_RESP_METAS > (tmpreq, tpmresp)) {
                    for (vect_meta_data::iterator it = tpmresp.metas.begin(); it != tpmresp.metas.end(); ++it) {
                        ((remotemetaintf&) meta()).set(static_cast<nodetype> (it->meta_type), static_cast<indx> (it->key), *it);}}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::sendmetas(nodetype ittp, indx_set& idset) {
            try {
                req_sendmetas tmpreq;
                resp_sendmetas tpmresp;


                assign_meta_data(idset, ittp, tmpreq.metas);

                for (vect_meta_data::iterator it = tmpreq.metas.begin(); it != tmpreq.metas.end(); ++it) {
                    if (((remotemetaintf&) (meta())).get(ittp, static_cast<indx> (it->key)))
                        it->changeset = ((remotemetaintf&) (meta())).get(ittp, static_cast<indx> (it->key))->changeset;}

                if (querytmpl<req_sendmetas, resp_sendmetas, RPC_OPERATION_REQ_SENDMETAS, RPC_OPERATION_RESP_SENDMETAS > (tmpreq, tpmresp)) {
                    for (vect_meta_data::iterator it = tpmresp.metas.begin(); it != tpmresp.metas.end(); ++it) {
                        ((remotemetaintf&) meta()).set(static_cast<nodetype> (it->meta_type), static_cast<indx> (it->key), *it);}
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::entity_create(nodetype ittp, indx parentid, iteminfo_pair& pairpack,
                string newname_, num64 numcriteria) {{
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                try {
                    req_addentity tmpreq;
                    resp_addentity tpmresp;


                    tmpreq.tpitem = ittp;
                    tmpreq.parentkey = parentid;
                    tmpreq.newname = newname_;
                    tmpreq.numcriteria = numcriteria;

                    if (querytmpl<req_addentity, resp_addentity, RPC_OPERATION_REQ_ADDENTITY, RPC_OPERATION_RESP_ADDENTITY > (tmpreq, tpmresp)) {

                        pairpack.first = static_cast<indx> (tpmresp.sig.key);
                        pairpack.second = name_with_type(tpmresp.sig.name, nodeinfotype(tpmresp.sig.tpitem));
                        set_vect_error_entity(tpmresp.error);}}

                catch (dvncierror& err) {
                    parseerror(err);}
                catch (...) {
                    parseundeferror();}}

            adminintf::entity_create(ittp, parentid, pairpack);

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::entities_erase(nodetype ittp, indx_set& idset) {
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                try {
                    req_removeentity tmpreq;
                    resp_removeentity tpmresp;


                    tmpreq.tpitem = ittp;
                    idset >> tmpreq.keys;

                    if (querytmpl<req_removeentity, resp_removeentity, RPC_OPERATION_REQ_REMOVEENTITY, RPC_OPERATION_RESP_REMOVEENTITY > (tmpreq, tpmresp)) {
                        set_vect_error_entity(tpmresp.error);}}

                catch (dvncierror& err) {
                    parseerror(err);}
                catch (...) {
                    parseundeferror();}

            adminintf::entities_erase(ittp, idset);

            return NS_ERROR_SUCCESS;};

       ns_error remoteadminintf::entity_duplicate(nodetype ittp,  indx id,  const std::string& newname, iteminfo_pair& pairpack){
                THD_EXCLUSIVE_LOCK(mutex);
                clearerrors();
                try {
                    req_dupentity tmpreq;
                    resp_dupentity tpmresp;


                    tmpreq.tpitem = ittp;
                    tmpreq.soursekey = id;
                    tmpreq.newname = newname;

                    if (querytmpl<req_dupentity, resp_dupentity, RPC_OPERATION_REQ_DUPENTITY, RPC_OPERATION_RESP_DUPENTITY > (tmpreq, tpmresp)) {

                        pairpack.first = static_cast<indx> (tpmresp.sig.key);
                        pairpack.second = name_with_type(tpmresp.sig.name, nodeinfotype(tpmresp.sig.tpitem));
                        set_vect_error_entity(tpmresp.error);}}

                catch (dvncierror& err) {
                    parseerror(err);}
                catch (...) {
                    parseundeferror();}

            //adminintf::entity_create(ittp, parentid, pairpack);

            return NS_ERROR_SUCCESS;}

        size_t remoteadminintf::alarms_net_req(vect_alarms_data& vect, guidtype& vers,  const std::string& agrp, const std::string& grp  ) {
            try {

                req_alarms  tmpreq = {vers, agrp, grp};
                resp_alarms tpmresp;
                if (querytmpl<req_alarms, resp_alarms, RPC_OPERATION_REQ_ALARMS, RPC_OPERATION_RESP_ALARMS > (tmpreq, tpmresp)) {
                    if (vers !=  tpmresp.vers) {
                        vers = tpmresp.vers;
                        vect.swap(tpmresp.lines);}}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        size_t remoteadminintf::commands_net_req(vect_commands_data& vect, guidtype& vers, const std::string& grp) {
            try {

                req_commands  tmpreq = {vers, grp};
                resp_commands tpmresp;
                if (querytmpl<req_commands, resp_commands, RPC_OPERATION_REQ_COMMANDS, RPC_OPERATION_RESP_COMMANDS > (tmpreq, tpmresp)) {
                    if (vers !=  tpmresp.vers) {
                        vers = tpmresp.vers;
                        vect.swap(tpmresp.lines);}}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        size_t remoteadminintf::regs_net_req(vect_registry_data& vect, guidtype& vers) {
            try {

                req_registry  tmpreq = {vers};
                resp_registry tpmresp;
                if (querytmpl<req_registry, resp_registry, RPC_OPERATION_REQ_REGISTRY, RPC_OPERATION_RESP_REGISTRY > (tmpreq, tpmresp)) {
                    if (vers !=  tpmresp.vers) {
                        vers = tpmresp.vers;
                        vect.swap(tpmresp.lines);}}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        size_t remoteadminintf::clients_net_req(vect_clients_data& vect, guidtype& vers) {
            try {

                req_clients  tmpreq = {vers};
                resp_clients tpmresp;
                if (querytmpl<req_clients, resp_clients, RPC_OPERATION_REQ_CLIENTS, RPC_OPERATION_RESP_CLIENTS > (tmpreq, tpmresp)) {
                    if (vers !=  tpmresp.vers) {
                        vers = tpmresp.vers;
                        vect.swap(tpmresp.lines);}}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        size_t remoteadminintf::debug_net_req(vect_debug_data& vect, guidtype& guid, size_t& curs, size_t& cnt) {
            try {

                req_debug  tmpreq = {guid, curs, cnt};
                resp_debug tpmresp;
                if (querytmpl<req_debug, resp_debug, RPC_OPERATION_REQ_DEBUG, RPC_OPERATION_RESP_DEBUG > (tmpreq, tpmresp)) {
                    if (guid !=  tpmresp.guid) {
                        guid = tpmresp.guid;
                        vect.swap(tpmresp.lines);}
                    curs = static_cast<size_t> (tpmresp.cursor);
                    cnt = static_cast<size_t> (tpmresp.cnt);}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        size_t remoteadminintf::journal_net_req(vect_journal_data& vect, guidtype& guid, size_t& curs, size_t& cnt) {
            try {

                req_journal  tmpreq = {guid, curs, cnt};
                resp_journal tpmresp;
                if (querytmpl<req_journal, resp_journal, RPC_OPERATION_REQ_JOURNAL, RPC_OPERATION_RESP_JOURNAL > (tmpreq, tpmresp)) {
                    if (guid !=  tpmresp.guid) {
                        guid = tpmresp.guid;
                        vect.swap(tpmresp.lines);}
                    curs = static_cast<size_t> (tpmresp.cursor);
                    cnt = static_cast<size_t> (tpmresp.cnt);}
                return vect.size();}
            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return 0;}

        ns_error remoteadminintf::executeoperation(req_adminoperation& operat) {
            THD_EXCLUSIVE_LOCK(mutex);
            try {
                req_adminoperation tmpreq = operat;
                tmpreq.ver = intrf_ver;
                resp_adminoperation tpmresp;
                if (querytmpl<req_adminoperation, resp_adminoperation, RPC_OPERATION_REQ_ADMINOPERATION, RPC_OPERATION_RESP_ADMINOPERATION > (tmpreq, tpmresp)) {
                    set_vect_error_entity(tpmresp.error);}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            return NS_ERROR_SUCCESS;}

        ns_error remoteadminintf::operation_autorizate(const std::string& user, const std::string& password, const std::string& hst, const std::string& ipadr) {
            THD_EXCLUSIVE_LOCK(mutex);
            resp_autorization tpmresp;
            try {
                req_autorization tmpreq;
                tmpreq.name = user;
                tmpreq.password = password;
                tmpreq.ver = intrf_ver;
                if (querytmpl<req_autorization, resp_autorization, RPC_OPERATION_REQ_AUTORIZATION, RPC_OPERATION_RESP_AUTORIZATION > (tmpreq, tpmresp)) {}}

            catch (dvncierror& err) {
                parseerror(err);}
            catch (...) {
                parseundeferror();}

            isautorizated_ = (tpmresp.err == NS_ERROR_SUCCESS);

            return static_cast<ns_error> (tpmresp.err);}

        void remoteadminintf::releaseconnection() {
            groups_map.clear();
            tags_map.clear();
            agroups_map.clear();
            users_map.clear();
            meta_maps.clear();
            key_name_map.clear();
            services_map.clear();
            globalnum_journalmap_ = 0;
            globalnum_alarmsmap_ = 0;
            globalnum_logmap_ = 0;
            globalnum_commandmap_ = 0;
            count_journalmap_ = 0;
            count_alarmsmap_ = 0;
            count_logmap_ = 0;
            count_commandmap_ = 0;
            disconnect_();
            _state =  adminintf::disconnected;
            DEBUG_STR_DVNCI(RELEASCONNECTION)}

        void remoteadminintf::parseerror(dvncierror& err) {
            if ((err.code() == ERROR_FAILNET_CONNECTED) ||
                    (err.code() == ERROR_NONET_CONNECTED)) {
                releaseconnection();
                throw err;}
            adderror(err);}

        void remoteadminintf::parseundeferror() {
            dvncierror tmperr(NS_ERROR_ERRRESP);
            adderror(tmperr);}}}
