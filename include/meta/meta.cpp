/* 
 * File:   meta.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 25 Январь 2010 г., 23:04
 */

#include <meta/meta.h>

namespace dvnci {

    using namespace pugi;
    using namespace std;
    using namespace dvnci;


    string STR_meta = "meta";
    string STR_HomeList = "HomeList";
    string STR_ReportList = "ReportList";
    string STR_TrendList = "TrendList";
    string STR_MessageList = "MessageList";
    string STR_TrendHeader = "TrendHeader";
    string STR_ReportHeader = "ReportHeader";
    string STR_MessageHeader = "MessageHeader";
    string STR_ReportArr = "ReportArr";
    string STR_TrendArr = "TrendArr";
    string STR_MessageArr = "MessageArr";
    string STR_unit = "unit";
    string STR_trend = "trend";
    string STR_message = "message";

    meta::meta() {

        reportHeader_nodes = new num_xmlnode_map;
        trendHeader_nodes = new num_xmlnode_map;
        messageHeader_nodes = new num_xmlnode_map;
        reportArr_nodes = new num_xmlnode_map;
        trendArr_nodes = new num_xmlnode_map;
        messageArr_nodes = new num_xmlnode_map;
        unit_nodes = new num_xmlnode_map;
        trend_nodes = new num_xmlnode_map;
        message_nodes = new num_xmlnode_map;
        init_s();
        _state = disconnected;}

    meta::meta(const fspath& dir_) {

        reportHeader_nodes = new num_xmlnode_map;
        trendHeader_nodes = new num_xmlnode_map;
        messageHeader_nodes = new num_xmlnode_map;
        reportArr_nodes = new num_xmlnode_map;
        trendArr_nodes = new num_xmlnode_map;
        messageArr_nodes = new num_xmlnode_map;
        unit_nodes = new num_xmlnode_map;
        trend_nodes = new num_xmlnode_map;
        message_nodes = new num_xmlnode_map;
        init_s();
        _state = disconnected;
        connect(dir_);}

    meta::~meta() {
        delete reportHeader_nodes;
        delete trendHeader_nodes;
        delete messageHeader_nodes;
        delete reportArr_nodes;
        delete trendArr_nodes;
        delete messageArr_nodes;
        delete unit_nodes;
        delete trend_nodes;
        delete message_nodes;
}

    void meta::clear() {

        reportHeader_nodes->clear();
        trendHeader_nodes->clear();
        messageHeader_nodes->clear();
        reportArr_nodes->clear();
        trendArr_nodes->clear();
        messageArr_nodes->clear();
        unit_nodes->clear();
        trend_nodes->clear();
        message_nodes->clear();}

    void meta::init_s() {
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_meta, NT_MF_ROOT));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_HomeList, NT_MF_HOME));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_ReportList, NT_MF_REPLIST));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_TrendList, NT_MF_TRENDLIST));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_MessageList, NT_MF_MESSLIST));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_ReportHeader, NT_MF_REPHEADER));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_TrendHeader, NT_MF_TRENDHEADER));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_MessageHeader, NT_MF_MESSHEADER));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_ReportArr, NT_MF_REPARR));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_TrendArr, NT_MF_TRENDARR));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_MessageArr, NT_MF_MESSARR));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_unit, NT_MF_UNIT));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_trend, NT_MF_TREND));
        convert_str_to_type.insert(stdstr_nodetype_pair(STR_message, NT_MF_MESSAGE));

        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_ROOT, STR_meta));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_HOME, STR_HomeList));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_REPLIST, STR_ReportList));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_TRENDLIST, STR_TrendList));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_MESSLIST, STR_MessageList));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_REPHEADER, STR_ReportHeader));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_TRENDHEADER, STR_TrendHeader));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_MESSHEADER, STR_MessageHeader));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_REPARR, STR_ReportArr));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_TRENDARR, STR_TrendArr));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_MESSARR, STR_MessageArr));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_UNIT, STR_unit));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_TREND, STR_trend));
        convert_type_to_str.insert(nodetype_stdstr_pair(NT_MF_MESSAGE, STR_message));

        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_REPHEADER, reportHeader_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_TRENDHEADER, trendHeader_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_MESSHEADER, messageHeader_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_REPARR, reportArr_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_TRENDARR, trendArr_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_MESSARR, messageArr_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_UNIT, unit_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_TREND, trend_nodes));
        xmlnodes_registry.insert(nodetype_xmlnodes_pair(NT_MF_MESSAGE, message_nodes));}

    bool meta::connect(const fspath&  dir_) {
        try {
            _dir = dir_;
            _path = dir_ / "AppMetaInfo.xml";
            doc.load_file(_path.string().c_str());
            //if (doc.name()==STR_meta){
            loadSructure(doc);
            _state = connected;
            return true;}
        catch (...) {
            clear();
            _state = disconnected;}
        return false;}

    bool meta::disconnect() {
        if (_state == disconnected) return true;
        clear();
        _state = disconnected;
        return true;}

    string meta::nodeStr(nodetype val) {
        nodetype_stdstr_map::iterator it = convert_type_to_str.find(val);
        if (it != convert_type_to_str.end()) return it->second;
        return "null";}

    nodetype meta::nodeType(string val) {
        stdstr_nodetype_map::iterator it = convert_str_to_type.find(val);
        if (it != convert_str_to_type.end()) return it->second;
        return 0;}

    num_xmlnode_map* meta::registry(nodetype val) {
        nodetype_xmlnodes_map::iterator it = xmlnodes_registry.find(val);
        if (it != xmlnodes_registry.end()) return it->second;
        return 0;}

    xml_node* meta::items(nodetype val, indx id_) {

        if (val == NT_MF_ROOT) return &meta_node;
        else
            if (val == NT_MF_HOME) return &homeList_node;
        else
            if (val == NT_MF_REPLIST) return &reportList_node;
        else
            if (val == NT_MF_TRENDLIST) return &trendList_node;
        else
            if (val == NT_MF_MESSLIST) return &messageList_node;
        else {
            num_xmlnode_map* tmpreg = registry(val);
            if (tmpreg) {
                num_xmlnode_map::iterator it = tmpreg->find(id_);
                if (it != tmpreg->end()) return &it->second;}}
        return 0;}

    void meta::loadSructure(xml_node& val) {
        if (val == 0) return;
        nodetype type_ = nodeType(val.name());
        if (type_ == NT_MF_ROOT) meta_node = val;
        if (type_ == NT_MF_HOME) homeList_node = val;
        if (type_ == NT_MF_REPLIST) reportList_node = val;
        if (type_ == NT_MF_TRENDLIST) trendList_node = val;
        if (type_ == NT_MF_MESSLIST) messageList_node = val;
        num_xmlnode_map* tmpreg = registry(type_);
        if (tmpreg) {
            xml_attribute atr = val.attribute("key");
            if (!atr.empty())
                tmpreg->insert(num_xmlnode_pair(atr.as_int(), val));}
        xml_node_iterator it = val.begin();
        while (it != val.end()) {
            loadSructure(*it);
            it++;}}

    string meta::nameAttribute(nodetype val) {
        if ((val == NT_MF_REPHEADER) || (val == NT_MF_TRENDHEADER) || (val == NT_MF_MESSHEADER) ||
                (val == NT_MF_REPARR) || (val == NT_MF_TRENDARR) || (val == NT_MF_MESSARR)) return "name";
        if ((val == NT_MF_UNIT) || (val == NT_MF_TREND) || (val == NT_MF_MESSAGE)) return "tg";
        return "";}

    bool meta::sign(nodetype parenttp, indx parentid, iteminfo_map& mappack,
            const string& strcriteria, num64 numcriteria) {
        mappack.clear();
        xml_node* parentnode = items(parenttp, parentid);

        if (parentnode) {
            xml_node_iterator it = parentnode->begin();
            cout << parentnode->name() << endl;
            while (it != parentnode->end()) {
                bool tmp_sys_node = false;
                string nm = it->name();
                string name_;
                nodetype tmp_tp = nodeType(nm);
                if (tmp_tp != 0) {
                    if ((tmp_tp == NT_MF_ROOT) || (tmp_tp == NT_MF_HOME) || (tmp_tp == NT_MF_REPLIST)
                            || (tmp_tp == NT_MF_TRENDLIST) || (tmp_tp == NT_MF_MESSLIST)) tmp_sys_node = true;
                    xml_attribute at = it->attribute("key");
                    indx tmpkey_ = npos;
                    if ((!at.empty()) || (tmp_sys_node)) {
                        try {
                            if (tmp_sys_node) {
                                if (tmp_tp == NT_MF_ROOT) tmpkey_ = 4;
                                if (tmp_tp == NT_MF_HOME) tmpkey_ = 0;
                                if (tmp_tp == NT_MF_REPLIST) tmpkey_ = 1;
                                if (tmp_tp == NT_MF_TRENDLIST) tmpkey_ = 2;
                                if (tmp_tp == NT_MF_MESSLIST) tmpkey_ = 3;}
                            else
                                tmpkey_ = at.as_int();
                            if (tmp_sys_node) {
                                name_ = "metaclient." + nodeStr(tmp_tp);}
                            else {
                                string attrib_nm = nameAttribute(tmp_tp);
                                xml_attribute at_nm = it->attribute(attrib_nm.c_str());
                                if (!at_nm.empty()) {
                                    name_ = at_nm.value();}}

                            name_with_type nwt;
                            nwt.name(name_);
                            nwt.typeex(nodeinfotype(tmp_tp,0));
                            mappack.insert(iteminfo_pair(tmpkey_, nwt));}
                        catch (...) {}}}
                it++;}}
        return true;}

    bool meta::sign(dvnci::nodetype ittp, indx_set& set_, iteminfo_map& mappack,
            const string& strcriteria , num64 numcriteria) {
        mappack.clear();
        if ((ittp == NT_MF_ROOT) || (ittp == NT_MF_HOME) || (ittp == NT_MF_REPLIST)
                || (ittp == NT_MF_TRENDLIST) || (ittp == NT_MF_MESSLIST)) return true;
        indx_set::const_iterator it = set_.begin();
        while (it != set_.end()) {
            xml_node* tpmnode = items(ittp, *it);
            if (tpmnode) {
                string name_;
                string attrib_nm = nameAttribute(ittp);
                xml_attribute at_nm = tpmnode->attribute(attrib_nm.c_str());
                if (!at_nm.empty()) {
                    name_ = at_nm.value();
                    name_with_type nwt;
                    nwt.name(name_);
                    nwt.typeex(nodeinfotype(ittp,0));
                    mappack.insert(iteminfo_pair(*it, nwt));}}
            it++;}
        return true;}

    string  meta::getItemProperty(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return "";
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.value();}
        return "";}

    int  meta::getItemProperty_int(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return static_cast<int>(npos);
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.as_int();}
        return static_cast<int>(npos);}

    unsigned int  meta::getItemProperty_uint(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return 0;
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.as_uint();}
        return 0;}

    double  meta::getItemProperty_double(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return 0;
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.as_double();}
        return 0;}

    float  meta::getItemProperty_float(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return 0;
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.as_float();}
        return 0;}

    bool  meta::getItemProperty_bool(nodetype ittp, indx id_, string property_) {
        xml_node* tmp_node = items(ittp, id_);
        if (!tmp_node) return false;
        xml_attribute at = tmp_node->attribute(property_.c_str());
        if (!at.empty()) {
            return at.as_bool();}
        return 0;}

    void  meta::property(nodetype ittp, indx id, const string& prop, const string& val) {
        xml_node* tmp_node = items(ittp, id);
        if (!tmp_node) return;
        xml_attribute at = tmp_node->attribute(prop.c_str());
        if (at.empty()) {
            tmp_node->append_attribute(prop.c_str());
            at = tmp_node->attribute(prop.c_str());};
        if (!at.empty()) {
            at.set_value(val.c_str());};}

    bool meta::checknodetypebyParentType(nodetype ittp, nodetype paritem_) {
        if (paritem_ == NT_MF_ROOT) return false;
        if ((paritem_ == NT_MF_HOME) && ((ittp == NT_MF_REPARR) || (ittp == NT_MF_TRENDARR))) return true;
        if ((paritem_ == NT_MF_REPLIST) && (ittp == NT_MF_REPHEADER)) return true;
        if ((paritem_ == NT_MF_TRENDLIST) && (ittp == NT_MF_TRENDHEADER)) return true;
        if ((paritem_ == NT_MF_MESSLIST) && (ittp == NT_MF_MESSHEADER)) return true;
        if ((paritem_ == NT_MF_REPHEADER) && (ittp == NT_MF_REPARR)) return true;
        if ((paritem_ == NT_MF_TRENDHEADER) && (ittp == NT_MF_TRENDARR)) return true;
        if ((paritem_ == NT_MF_MESSHEADER) && (ittp == NT_MF_MESSARR)) return true;
        if ((paritem_ == NT_MF_REPARR) && (ittp == NT_MF_UNIT)) return true;
        if ((paritem_ == NT_MF_TRENDARR) && (ittp == NT_MF_TREND)) return true;
        if ((paritem_ == NT_MF_MESSARR) && (ittp == NT_MF_MESSAGE)) return true;
        return false;}

    nodetype meta::getnodetypebyChildType(nodetype chitem_) {
        if (chitem_ == NT_MF_ROOT) return 0;
        if (chitem_ == NT_MF_HOME) return NT_MF_ROOT;
        if (chitem_ == NT_MF_REPHEADER) return NT_MF_REPLIST;
        if (chitem_ == NT_MF_TRENDHEADER) return NT_MF_TRENDLIST;
        if (chitem_ == NT_MF_MESSHEADER) return NT_MF_MESSLIST;
        if (chitem_ == NT_MF_REPLIST) return NT_MF_ROOT;
        if (chitem_ == NT_MF_TRENDLIST) return NT_MF_ROOT;
        if (chitem_ == NT_MF_MESSLIST) return NT_MF_ROOT;
        if (chitem_ == NT_MF_REPARR) return NT_MF_REPHEADER;
        if (chitem_ == NT_MF_TRENDARR) return NT_MF_TRENDHEADER;
        if (chitem_ == NT_MF_MESSARR) return NT_MF_MESSHEADER;
        if (chitem_ == NT_MF_UNIT) return NT_MF_REPARR;
        if (chitem_ == NT_MF_TREND) return NT_MF_TRENDARR;
        if (chitem_ == NT_MF_MESSAGE) return NT_MF_MESSARR;
        return 0;}

    indx meta::getNewKey(nodetype ittp) {
        num_xmlnode_map* tmpreg = registry(ittp);
        indx result = npos;
        if (tmpreg) {
            for (num_xmlnode_map::iterator it = tmpreg->begin(); it != tmpreg->end(); ++it) {
                if (it->first > result) result = it->first;}}
        return (result + 1);}

    bool meta::merge() {
        if (state() == connected) {
            doc.save_file(_path.string().c_str());
            return true;}
        return false;}

    void  meta::add(nodetype ittp, indx parentid, iteminfo_pair& pair_,  string newname_) {

        nodetype parent_tp = getnodetypebyChildType(ittp);
        if (checknodetypebyParentType(ittp, parent_tp)) {
            xml_node* parentnode = items(parent_tp, parentid);

            if (parentnode) {
                indx newkey_ = getNewKey(ittp);
                string name_ = nodeStr(ittp);
                if (name_ != "") {
                    xml_node newnode = parentnode->append_child();
                    newnode.set_name(name_.c_str());
                    newnode.append_attribute("key");
                    xml_attribute at = newnode.attribute("key");
                    if (!at.empty()) {
                        at.set_value(static_cast<int>(newkey_));}
                    string attrib_nm = nameAttribute(ittp);
                    newnode.append_attribute(attrib_nm.c_str());
                    at = newnode.attribute(attrib_nm.c_str());
                    if (!at.empty()) {
                        at.set_value(newname_.c_str());}
                    pair_.first = newkey_;
                    pair_.second.name(newname_);
                    pair_.second.typeex(nodeinfotype(ittp,0));
                    num_xmlnode_map* tmpreg = registry(ittp);
                    if (tmpreg) {
                        tmpreg->insert(num_xmlnode_pair(newkey_, newnode));
                        doc.save_file(_path.string().c_str());}

                    return;}}}

        pair_.first = npos;
        pair_.second.name("");
        pair_.second.typeex(nodeinfotype(0,0));}

    ns_error meta::remove(nodetype ittp,const indx_set& keyset_) {

        num_xmlnode_map* tmpreg = registry(ittp);
        if (tmpreg) {
            indx_set::const_iterator it = keyset_.begin();
            while (it != keyset_.end()) {
                deleteNode(*tmpreg, *it);
                it++;}}
        doc.save_file(_path.string().c_str());

        return NS_ERROR_SUCCESS;}

    bool meta::deleteNode(num_xmlnode_map& regestry_, indx itid_) {
        xml_node parentnode;
        num_xmlnode_map::iterator it = regestry_.find(itid_);
        if (it != regestry_.end()) {
            xml_node val = it->second;
            parentnode = val.parent();
            if (!parentnode.empty()) {
                parentnode.remove_child(val);
                regestry_.erase(itid_);
                return true;}}
        return false;}

}











