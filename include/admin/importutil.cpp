/* 
 * File:   importutil.cpp
 * Author: Serg
 * 
 * Created on 2 Апрель 2010 г., 13:28
 */

#include <admin/importutil.h>
#include <bits/basic_string.h>


using namespace pugi;
using namespace dvnci;




namespace dvnci {
    namespace admin {

        int gettipeimport(std::string filepath) {
            if (boost::iends_with(filepath, ".xml")) return TIPE_NS_IMPORT_XML;
            if (boost::iends_with(filepath, ".csv")) return TIPE_NS_IMPORT_CSV;
            if (boost::iends_with(filepath, ".esd")) return TIPE_NS_IMPORT_ESD;
            return 0;
        }

        num64 setesdnumcriteria(num16 min, num16 max, num8 type) {
            num64 min_ = min;
            num64 max_ = max;
            num64 type_ = type;
            return ((type_ << 32) | (min_ << 16) | (max_));
        }

        bool in_criteria(num64 mumcriteria, num16 adr, num8 type) {
            num64 min_ = (mumcriteria >> 16) & 0xFFFF;
            num64 max_ = mumcriteria & 0xFFFF;
            num64 type_ = (mumcriteria >> 32) & 0xFF;
            return (((type_ == 0) || (type_ == type)) && ((min_ <= adr) && (max_ >= adr)));
        }

        bool provided_esd(num8 val) {
            return ((val == esd_type_x) || (val == esd_type_y) || (val == esd_type_c) ||
                    (val == esd_type_v) || (val == esd_type_s) || (val == esd_type_gx) || (val == esd_type_gy));
        }

        std::string binding_esd(num8 type, unum32 adr, std::string vw) {
            std::string postfix = "";
            if (trim_copy(vw) == "bcd") postfix = ":B";
            // if (trim_copy(vw)=="real") postfix=":R";
            switch (type) {
                case esd_type_v: return (trim_copy(boost::str(boost::format("V%o") % adr)) + postfix);
                case esd_type_x: return (trim_copy(boost::str(boost::format("X%o") % adr)));
                case esd_type_y: return (trim_copy(boost::str(boost::format("Y%o") % adr)));
                case esd_type_c: return (trim_copy(boost::str(boost::format("C%o") % adr)));
                case esd_type_s: return (trim_copy(boost::str(boost::format("S%o") % adr)));
                case esd_type_gx: return (trim_copy(boost::str(boost::format("V%o") % (040000 + (adr / 16)))) + "." +
                            (trim_copy(boost::str(boost::format("%d") % (adr % 16)))));
                case esd_type_gy: return (trim_copy(boost::str(boost::format("V%o") % (040200 + (adr / 16)))) + "." +
                            (trim_copy(boost::str(boost::format("%d") % (adr % 16)))));
                case esd_type_sp: return (trim_copy(boost::str(boost::format("SP%o") % adr)));

                default: return "";
            };
            return "";
        }

#pragma  pack(push,1)

struct TDocV {
            unum16 unUsed0;
            num8 MemType;
            unum32 addr;
            num8 Name[17];
            num8 WI[17];
            num8 Comment[164];
        };

        struct TDocFile {
            num8 header[1229];
            TDocV docV[100000];
        };
#pragma  pack(pop)

        void clearbase(base_data& base) {
            base.agroups.clear();
            base.groups.clear();
            base.tags.clear();
            base.users.clear();
        }

        bool getattribute(std::string& result, const std::string name, pugi::xml_node_iterator val) {
            result = "";
            if (!val->attribute(name.c_str()).empty()) {
                result = val->attribute(name.c_str()).value();
                return true;
            }
            return false;
        }

        bool getchildval(std::string& result, const std::string name, pugi::xml_node_iterator val) {

            result = "";
            if (!val->child(name.c_str()).empty()) {
                if (!val->child(name.c_str()).first_child().empty())
                    result = val->child(name.c_str()).first_child().value();
                return true;
            }
            return false;
        }

        void xml_loadgroups(pugi::xml_node& val, base_data& base) {

            for (pugi::xml_node_iterator it = val.begin(); it != val.end(); ++it) {
                if (it->name() == NS_XML_GROUP_IMPORT) {
                    std::string tmp = "";
                    group_data tmpstruct;
                    if ((getattribute(tmp, "name", it)) && (tmp != "")) {
                        tmpstruct.name = tmp;
                        ((groupstruct*) & tmpstruct.groupinfo)->appid((getchildval(tmp, "app", it)) ? str_to<int>(tmp, 0) : 0);
                        ((groupstruct*) & tmpstruct.groupinfo)->chanaltype((getchildval(tmp, "chanaltype", it)) ? str_to<int>(tmp, 0) : 0);
                        ((groupstruct*) & tmpstruct.groupinfo)->chanalnum((getchildval(tmp, "chanalnum", it)) ? str_to<int>(tmp, 0) : 0);
                        //((groupstruct*)&tmpstruct.groupinfo)->portnum((getchildval(tmp, "port", it)) ? str_to<int>(tmp,0) : 0);
                        ((groupstruct*) & tmpstruct.groupinfo)->protocol((getchildval(tmp, "device", it)) ? str_to<int>(tmp, 0) : 0);
                        tmpstruct.changeset = MASK_GR_EXPORT1;
                        base.groups.push_back(tmpstruct);
                    };
                }
            }
        }

        void xml_loadagroups(pugi::xml_node& val, base_data& base) {

            for (pugi::xml_node_iterator it = val.begin(); it != val.end(); ++it) {
                if (it->name() == NS_XML_AGROUP_IMPORT) {
                    std::string tmp = "";
                    agroup_data tmpstruct;
                    if ((getattribute(tmp, "name", it)) && (tmp != "")) {
                        tmpstruct.name = tmp;
                        tmpstruct.changeset = MASK_AGR_EXPORT1;
                        base.agroups.push_back(tmpstruct);
                    };
                }
            }
        }

        void xml_loadusers(pugi::xml_node& val, base_data& base) {

            for (pugi::xml_node_iterator it = val.begin(); it != val.end(); ++it) {
                if (it->name() == NS_XML_USER_IMPORT) {
                    std::string tmp = "";
                    user_data tmpstruct;
                    if ((getattribute(tmp, "name", it)) && (tmp != "")) {
                        tmpstruct.name = tmp;
                        tmpstruct.changeset = MASK_USER_EXPORT1;
                        base.users.push_back(tmpstruct);
                    };
                }
            }
        }

        void xml_loadtags(pugi::xml_node& val, base_data& base) {

            for (pugi::xml_node_iterator it = val.begin(); it != val.end(); ++it) {
                if (it->name() == NS_XML_TAG_IMPORT) {
                    std::string tmp = "";
                    tag_data tmpstruct;

                    if ((getattribute(tmp, "name", it)) && (tmp != "")) {
                        tmpstruct.name = tmp;
                        tmpstruct.group = (getattribute(tmp, "group", it)) ? tmp : "";
                        tmpstruct.comment = (getchildval(tmp, "comment", it)) ? tmp : "";
                        tmpstruct.bind = (getchildval(tmp, "bind", it)) ? tmp : "";
                        tmpstruct.comment = (getchildval(tmp, "comment", it)) ? tmp : "";
                        tmpstruct.ue = (getchildval(tmp, "eu", it)) ? tmp : "";
                        tmpstruct.almsg = (getchildval(tmp, "alarmmsgtext", it)) ? tmp : "";
                        tmpstruct.offmsg = (getchildval(tmp, "offmsgtext", it)) ? tmp : "";
                        tmpstruct.onmsg = (getchildval(tmp, "onmsgtext", it)) ? tmp : "";
                        ((tagstruct*) & tmpstruct.tginfo)->type((getchildval(tmp, "type", it)) ? str_to<int>(tmp, 0) : 0);
                        ((tagstruct*) & tmpstruct.tginfo)->minraw(getchildval(tmp, "minraw", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->maxraw(getchildval(tmp, "maxraw", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->mineu(getchildval(tmp, "mineu", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->maxeu(getchildval(tmp, "maxeu", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->logdb(str_to<double>(getchildval(tmp, "db", it) ? comma_to_point_copy(tmp) : "0"));
                        ((tagstruct*) & tmpstruct.tginfo)->devdb(str_to<double>(getchildval(tmp, "devdb", it) ? comma_to_point_copy(tmp) : "0"));
                        ((tagstruct*) & tmpstruct.tginfo)->alarmlevel((getchildval(tmp, "alarmlevel", it)) ? str_to<int>(tmp, 0) : 0);

                        ((tagstruct*) & tmpstruct.tginfo)->logged(((getchildval(tmp, "log", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->onmsged(((getchildval(tmp, "onmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->offmsged(((getchildval(tmp, "offmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->alarmcase((getchildval(tmp, "alarmcase", it)) ? str_to<int>(tmp, 0) : 0);
                        ((tagstruct*) & tmpstruct.tginfo)->alarmconstr(getchildval(tmp, "alarmconst", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->rwtype((getchildval(tmp, "rw", it)) ? str_to<int>(tmp, 0) : 0);
                        tmpstruct.changeset = MASK_RT_EXPORT1;
                        base.tags.push_back(tmpstruct);
                    }
                }
            }
        }

        void xml_loadtags_old(pugi::xml_node& val, base_data& base) {

            for (pugi::xml_node_iterator it = val.begin(); it != val.end(); ++it) {
                if (it->name() == NS_XML_TAG_IMPORT_OLD) {
                    std::string tmp = "";
                    tag_data tmpstruct;

                    if ((getattribute(tmp, "name", it)) && (tmp != "")) {
                        tmpstruct.name = tmp;
                        tmpstruct.group = (getattribute(tmp, "group", it)) ? tmp : "";
                        tmpstruct.comment = (getchildval(tmp, "comment", it)) ? tmp : "";
                        tmpstruct.bind = (getchildval(tmp, "bind", it)) ? tmp : "";
                        tmpstruct.comment = (getchildval(tmp, "comment", it)) ? tmp : "";
                        tmpstruct.ue = (getchildval(tmp, "eu", it)) ? tmp : "";
                        tmpstruct.almsg = (getchildval(tmp, "alarmmsgtext", it)) ? tmp : "";
                        tmpstruct.offmsg = (getchildval(tmp, "offmsgtext", it)) ? tmp : "";
                        tmpstruct.onmsg = (getchildval(tmp, "onmsgtext", it)) ? tmp : "";
                        ((tagstruct*) & tmpstruct.tginfo)->type(oldtypetonew((getchildval(tmp, "type", it)) ? str_to<int>(tmp, 0) : 0));
                        ((tagstruct*) & tmpstruct.tginfo)->minraw(getchildval(tmp, "minraw", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->maxraw(getchildval(tmp, "maxraw", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->mineu(getchildval(tmp, "mineu", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->maxeu(getchildval(tmp, "maxeu", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->logdb(str_to<double>(getchildval(tmp, "db", it) ? comma_to_point_copy(tmp) : "0"));
                        ((tagstruct*) & tmpstruct.tginfo)->devdb(str_to<double>(getchildval(tmp, "devdb", it) ? comma_to_point_copy(tmp) : "0"));
                        ((tagstruct*) & tmpstruct.tginfo)->alarmlevel(((getchildval(tmp, "alarmmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? altAccident :
                                ((getchildval(tmp, "alarmlocalmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? altWarning : 0);

                        ((tagstruct*) & tmpstruct.tginfo)->logged(((getchildval(tmp, "log", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->onmsged(((getchildval(tmp, "onmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->offmsged(((getchildval(tmp, "offmsg", it)) && (lower_copy(tmp) != "false") && (tmp != "0")) ? true : false);
                        ((tagstruct*) & tmpstruct.tginfo)->alarmcase((getchildval(tmp, "alarmcase", it)) ? str_to<int>(tmp, 0) : 0);
                        ((tagstruct*) & tmpstruct.tginfo)->alarmconstr(getchildval(tmp, "alarmconst", it) ? comma_to_point_copy(tmp) : "0");
                        ((tagstruct*) & tmpstruct.tginfo)->rwtype(0);
                        if (IN_REPORTSET(((tagstruct*) & tmpstruct.tginfo)->type())) {
                            ((tagstruct*) & tmpstruct.tginfo)->minraw(0);
                            ((tagstruct*) & tmpstruct.tginfo)->maxraw<num64>(100);
                        }
                        tmpstruct.changeset = MASK_RT_EXPORT1;
                        base.tags.push_back(tmpstruct);
                    }
                }
            }
        }

        void xml_loadSructure(pugi::xml_node& val, base_data& base) {
            pugi::xml_attribute verattr = val.attribute("ver");
            bool old = verattr.empty();
            pugi::xml_node tmp;
            tmp = val.child(NS_XML_GROUPS_IMPORT.c_str());
            if (!tmp.empty()) xml_loadgroups(tmp, base);
            tmp = val.child(NS_XML_AGROUPS_IMPORT.c_str());
            if (!tmp.empty()) xml_loadagroups(tmp, base);
            tmp = val.child(NS_XML_USERS_IMPORT.c_str());
            if (!tmp.empty()) xml_loadusers(tmp, base);
            if (old) {
                tmp = val.child(NS_XML_TAGS_IMPORT_OLD.c_str());
                if (!tmp.empty()) xml_loadtags_old(tmp, base);
            } else {
                tmp = val.child(NS_XML_TAGS_IMPORT.c_str());
                if (!tmp.empty()) xml_loadtags(tmp, base);
            }
        }

        bool xml_getimportdata(std::string filepath, base_data& base, int& loc, std::string group) {
            loc = NS_CODPAGE_UTF8;
            clearbase(base);
            pugi::xml_node tmp;
            pugi::xml_document doc;
            doc.load_file(filepath.c_str());
            tmp = doc.child(NS_XML_ROOT_IMPORT.c_str());
            if (!tmp.empty()) {
                xml_loadSructure(tmp, base);
                return true;
            };
            return false;
        }

        static std::string correct_csv_escapesec(const std::string& vl) {
            std::string rslt = vl;
            if (!rslt.length() > 1) {
                if (rslt[0] == '"' && (*rslt.rbegin()) == '"')
                    rslt = rslt.substr(1, rslt.length() - 1);
                if (!rslt.empty()) {
                    boost::algorithm::replace_all(rslt, "\";\"", ";");
                    boost::algorithm::replace_all(rslt, "\",\"", ",");
                    boost::algorithm::replace_all(rslt, "\"\n\"", "\n");
                    boost::algorithm::replace_all(rslt, "\"\"", "\"");
                }
            }
            return rslt;
        }
        
        static void csv_split_str(std::string vl, const std::string& spl, str_vect& tmprow) {
            boost::algorithm::replace_all(vl, "\",\"", ",");
            boost::algorithm::replace_all(vl, "\"\n\"", "\n");
            boost::algorithm::replace_all(vl, "\"\"", "\"");
            split_str(vl, spl, tmprow);
        }        

        bool csv_getimportdata(std::string filepath, base_data& base, int& loc, std::string group) {
            loc = NS_CODPAGE_LOC8;
            const int sz = filestream::filesize(filepath);
            bool old = false;
            if (sz > 0) {

                char* data = new char[sz];

                if (filestream::read(filepath, (void*) data) > 0) {
                    std::string data_str(data);
                    str_vect tmprow;
                    csv_split_str(data_str, "\n", tmprow);

                    for (str_vect::iterator it = tmprow.begin(); it != tmprow.end(); ++it) {
                        if (it == tmprow.begin()) old = (!boost::find_first((*it), "Type"));
                        if (it != tmprow.begin()) {

                            str_vect tmpitem;
                            csv_split_str(*it, ";", tmpitem);
                            if (tmpitem.size() > 0) {
                                if ((trim_copy(tmpitem.at(0)) != "") && ((it + 1) != tmprow.end())) {
                                    tag_data tmpstruct;
                                    tmpstruct.name = trim_copy(tmpitem.at(0));
                                    tmpstruct.group = (group != "") ? group : (tmpitem.size() > 1) ? trim_copy(tmpitem.at(1)) : "";
                                    tmpstruct.comment = correct_csv_escapesec((tmpitem.size() > 3) ? trim_copy(tmpitem.at(3)) : "");
                                    tmpstruct.bind = correct_csv_escapesec((tmpitem.size() > 2) ? trim_copy(tmpitem.at(2)) : "");
                                    tmpstruct.ue = correct_csv_escapesec((tmpitem.size() > 21) ? trim_copy(tmpitem.at(21)) : "");
                                    tmpstruct.almsg = correct_csv_escapesec((tmpitem.size() > 16) ? trim_copy(tmpitem.at(16)) : "");
                                    tmpstruct.offmsg = correct_csv_escapesec((tmpitem.size() > 14) ? trim_copy(tmpitem.at(14)) : "");
                                    tmpstruct.onmsg = correct_csv_escapesec((tmpitem.size() > 12) ? trim_copy(tmpitem.at(12)) : "");
                                    if (old) ((tagstruct*) & tmpstruct.tginfo)->type((tmpitem.size() > 5) ? oldtypetonew(str_to<int>(trim_copy(tmpitem.at(5)), 0)) : 0);
                                    else ((tagstruct*) & tmpstruct.tginfo)->type((tmpitem.size() > 5) ? str_to<int>(trim_copy(tmpitem.at(5)), 0) : 0);
                                    ((tagstruct*) & tmpstruct.tginfo)->minraw(trim_copy(tmpitem.at(7)));
                                    ((tagstruct*) & tmpstruct.tginfo)->maxraw(trim_copy(tmpitem.at(8)));
                                    ((tagstruct*) & tmpstruct.tginfo)->mineu(trim_copy(tmpitem.at(9)));
                                    ((tagstruct*) & tmpstruct.tginfo)->maxeu(trim_copy(tmpitem.at(10)));
                                    ((tagstruct*) & tmpstruct.tginfo)->logdb(str_to<double>(trim_copy(tmpitem.at(6))));
                                    if ((old) && (IN_REPORTSET(((tagstruct*) & tmpstruct.tginfo)->type()))) {
                                        ((tagstruct*) & tmpstruct.tginfo)->minraw(trim_copy(tmpitem.at(6)));
                                        if (tmpitem.size() > 21)
                                            ((tagstruct*) & tmpstruct.tginfo)->maxraw(trim_copy(trim_copy(tmpitem.at(21))));
                                    }
                                    ((tagstruct*) & tmpstruct.tginfo)->logged(((tmpitem.size() > 4) && (lower_copy(trim_copy(tmpitem.at(4))) == "true")) ? true : false);
                                    ((tagstruct*) & tmpstruct.tginfo)->onmsged(((tmpitem.size() > 11) && (lower_copy(trim_copy(tmpitem.at(11))) == "true")) ? true : false);
                                    ((tagstruct*) & tmpstruct.tginfo)->offmsged(((tmpitem.size() > 13) && (lower_copy(trim_copy(tmpitem.at(13))) == "true")) ? true : false);

                                    if (old)
                                        ((tagstruct*) & tmpstruct.tginfo)->alarmcase(((tmpitem.size() > 18) && (lower_copy(trim_copy(tmpitem.at(18))) == "<")) ? 0 : 1);
                                    else
                                        ((tagstruct*) & tmpstruct.tginfo)->alarmcase(((tmpitem.size() > 18)) ? str_to<int>(trim_copy(tmpitem.at(18)), 0) : 0);
                                    if (((tmpitem.size() > 19))) ((tagstruct*) & tmpstruct.tginfo)->alarmconstr(trim_copy(tmpitem.at(19)));
                                    if ((old) && ((tmpitem.size() > 21))) ((tagstruct*) & tmpstruct.tginfo)->devdb(str_to<double>(trim_copy(tmpitem.at(21))));
                                    /*if (old) ((tagstruct*) & tmpstruct.tginfo)->alarmlevel(((tmpitem.size() > 15) && (lower_copy(trim_copy(tmpitem.at(15))) != "true")) ? 0 :
                                            ((tmpitem.size() > 17) && (lower_copy(trim_copy(tmpitem.at(17))) == "600")) ? altAccident : altWarning);
                                    else*/
                                    if ((tmpitem.size() > 15) && !trim_copy(tmpitem.at(15)).empty())
                                        ((tagstruct*) & tmpstruct.tginfo)->value(correct_csv_escapesec(trim_copy(tmpitem.at(15))));
                                    ((tagstruct*) & tmpstruct.tginfo)->alarmlevel(str_to<int>(lower_copy(trim_copy(tmpitem.at(17))), 0));
                                    if (!old) ((tagstruct*) & tmpstruct.tginfo)->rwtype((tmpitem.size() > 21) ? str_to<int>(trim_copy(tmpitem.at(21)), 0) : 0);
                                    tmpstruct.changeset = MASK_RT_EXPORT1;
                                    base.tags.push_back(tmpstruct);
                                }
                            }
                        }
                    }
                }
                delete[] data;
                return true;
            }
            return false;
        }

        bool esd_getimportdata(std::string filepath, base_data& base, int& loc, std::string group, num64 mumcriteria) {
            loc = NS_CODPAGE_LOC8;
            const int sz = filestream::filesize(filepath);
            if (sz > 0) {
                char* data = new char[sz];
                // cout <<"sz="<<filepath << " "<< sz << endl;
                if (filestream::read(filepath, (void*) data) > 0) {
                    TDocFile* esdfl = (TDocFile*) data;
                    int recCount = (sz - 1229) / sizeof (TDocV);
                    for (int i = 0; i < recCount; i++) {
                        std::string name_ = std::string((char*) &esdfl->docV[i].Name);
                        std::string bind_ = binding_esd(esdfl->docV[i].MemType, esdfl->docV[i].addr, esdfl->docV[i].WI);
                        if ((name_ != "") && (bind_ != "") &&
                                (in_criteria(mumcriteria, esdfl->docV[i].addr, esdfl->docV[i].MemType))) {
                            boost::replace_all(name_, "%", "procent");
                            boost::replace_all(name_, ".", "dot");
                            tag_data tmpstruct;
                            tmpstruct.name = trim_copy(name_);
                            tmpstruct.group = group;
                            std::string tmpcomment = std::string((char*) &esdfl->docV[i].Comment);
                            boost::replace_all(tmpcomment, "\n", "");
                            boost::replace_all(tmpcomment, "\r", "");
                            char tmpchar = 0xA;
                            boost::replace_all(tmpcomment, std::string((char*) &tmpchar), "");
                            tmpchar = 0xD;
                            boost::replace_all(tmpcomment, std::string((char*) &tmpchar), "");
                            tmpstruct.comment = tmpcomment;
                            tmpstruct.onmsg = tmpcomment;
                            tmpstruct.offmsg = tmpcomment;
                            tmpstruct.almsg = tmpcomment;
                            tmpstruct.bind = bind_;
                            //((tagstruct*)&tmpstruct.tginfo)->type((esdfl->docV[i].MemType!=esd_type_v) ?  TYPE_DISCRET : 0);
                            ((tagstruct*) & tmpstruct.tginfo)->type(0);
                            ((tagstruct*) & tmpstruct.tginfo)->minraw<double>(0);
                            ((tagstruct*) & tmpstruct.tginfo)->maxraw<double>(esdfl->docV[i].MemType != esd_type_v ? 0 : 4095);
                            ((tagstruct*) & tmpstruct.tginfo)->mineu<double>(0);
                            ((tagstruct*) & tmpstruct.tginfo)->maxeu<double>(esdfl->docV[i].MemType != esd_type_v ? 1 : 100);
                            ((tagstruct*) & tmpstruct.tginfo)->logdb(0);
                            ((tagstruct*) & tmpstruct.tginfo)->logged(false);
                            ((tagstruct*) & tmpstruct.tginfo)->onmsged(false);
                            ((tagstruct*) & tmpstruct.tginfo)->offmsged(false);
                            ((tagstruct*) & tmpstruct.tginfo)->alarmcase(0);
                            ((tagstruct*) & tmpstruct.tginfo)->alarmconst<double>(0);
                            ((tagstruct*) & tmpstruct.tginfo)->devdb(0);
                            ((tagstruct*) & tmpstruct.tginfo)->alarmlevel(0);
                            ((tagstruct*) & tmpstruct.tginfo)->rwtype(0);
                            tmpstruct.changeset = MASK_RT_EXPORT1;
                            base.tags.push_back(tmpstruct);
                        }
                    }
                    return (base.tags.size() > 0);
                }
                delete[] data;
            }
            return false;
        }

        bool getimportdata(std::string filepath, base_data& base, int& loc, std::string group, num64 mumcriteria) {
            int type = gettipeimport(filepath);
            switch (type) {
                case TIPE_NS_IMPORT_XML: return xml_getimportdata(filepath, base, loc, group);
                case TIPE_NS_IMPORT_CSV: return csv_getimportdata(filepath, base, loc, group);
                case TIPE_NS_IMPORT_ESD: return esd_getimportdata(filepath, base, loc, group, mumcriteria);
            }
            return false;
        }

        void setattribute(pugi::xml_node node, const std::string name, const std::string val) {
            pugi::xml_attribute newattr = node.append_attribute(name.c_str());
            newattr.set_value(val.c_str());
        }

        bool setchildval(pugi::xml_node node, const std::string name, const std::string val) {
            pugi::xml_node newchild = node.append_child();
            newchild.set_name(name.c_str());
            xml_node val_text = newchild.append_child(pugi::node_pcdata);
            val_text.set_value(val.c_str());
            return true;
        }

        bool setchildval(pugi::xml_node node, const std::string name, bool val) {
            pugi::xml_node newchild = node.append_child();
            newchild.set_name(name.c_str());
            xml_node val_text = newchild.append_child(pugi::node_pcdata);
            val_text.set_value(val ? "true" : "false");
            return true;
        }

        bool xml_setexportdata(std::string filepath, base_data& base) {

            pugi::xml_document doc;
            pugi::xml_node rootnode = doc.append_child();
            rootnode.set_name(NS_XML_ROOT_IMPORT.c_str());
            pugi::xml_attribute newattr = rootnode.append_attribute("ver");
            newattr.set_value(2);

            if (base.groups.size() > 0) {
                pugi::xml_node groupsnode = rootnode.append_child();
                groupsnode.set_name(NS_XML_GROUPS_IMPORT.c_str());
                for (vect_group_data::iterator it = base.groups.begin(); it != base.groups.end(); ++it) {
                    pugi::xml_node groupnode = groupsnode.append_child();
                    groupnode.set_name(NS_XML_GROUP_IMPORT.c_str());
                    setattribute(groupnode, "name", it->name);
                    setchildval(groupnode, "app", to_str(((groupstruct*) & it->groupinfo)->appid()));
                    setchildval(groupnode, "chanaltype", to_str(((groupstruct*) & it->groupinfo)->chanaltype()));
                    setchildval(groupnode, "chanalnum", to_str(((groupstruct*) & it->groupinfo)->chanalnum()));
                    //setchildval(groupnode,"port",to_str(((groupstruct*)&it->groupinfo)->portnum()));
                    setchildval(groupnode, "device", to_str(((groupstruct*) & it->groupinfo)->protocol()));
                }
            }

            if (base.agroups.size() > 0) {
                pugi::xml_node agroupsnode = rootnode.append_child();
                agroupsnode.set_name(NS_XML_AGROUPS_IMPORT.c_str());
                for (vect_agroup_data::iterator it = base.agroups.begin(); it != base.agroups.end(); ++it) {
                    pugi::xml_node agroupnode = agroupsnode.append_child();
                    agroupnode.set_name(NS_XML_AGROUP_IMPORT.c_str());
                    setattribute(agroupnode, "name", it->name);
                }
            }

            if (base.tags.size() > 0) {
                pugi::xml_node tagsnode = rootnode.append_child();
                tagsnode.set_name(NS_XML_TAGS_IMPORT.c_str());
                for (vect_tag_data::iterator it = base.tags.begin(); it != base.tags.end(); ++it) {
                    pugi::xml_node tagnode = tagsnode.append_child();
                    tagnode.set_name(NS_XML_TAG_IMPORT.c_str());
                    setattribute(tagnode, "name", it->name);
                    setattribute(tagnode, "group", it->group);
                    setchildval(tagnode, "comment", it->comment);
                    setchildval(tagnode, "bind", it->bind);
                    setchildval(tagnode, "minraw", ((tagstruct*) & it->tginfo)->minraw_str());
                    setchildval(tagnode, "maxraw", ((tagstruct*) & it->tginfo)->maxraw_str());
                    setchildval(tagnode, "mineu", ((tagstruct*) & it->tginfo)->mineu_str());
                    setchildval(tagnode, "maxeu", ((tagstruct*) & it->tginfo)->maxeu_str());
                    setchildval(tagnode, "type", to_str(((tagstruct*) & it->tginfo)->type()));
                    setchildval(tagnode, "db", to_str<double>(((tagstruct*) & it->tginfo)->logdb()));
                    setchildval(tagnode, "dbraw", to_str(((tagstruct*) & it->tginfo)->devdb()));
                    setchildval(tagnode, "onmsg", ((tagstruct*) & it->tginfo)->onmsged());
                    setchildval(tagnode, "onmsgtext", it->onmsg);
                    setchildval(tagnode, "offmsg", ((tagstruct*) & it->tginfo)->offmsged());
                    setchildval(tagnode, "offmsgtext", it->offmsg);
                    setchildval(tagnode, "alarmlevel", to_str(((tagstruct*) & it->tginfo)->alarmlevel()));
                    setchildval(tagnode, "alarmmsgtext", it->almsg);
                    setchildval(tagnode, "log", ((tagstruct*) & it->tginfo)->logged());
                    setchildval(tagnode, "alarmconst", ((tagstruct*) & it->tginfo)->alarmconst_str());
                    setchildval(tagnode, "alarmcase", to_str(((tagstruct*) & it->tginfo)->alarmcase()));
                    setchildval(tagnode, "eu", it->ue);
                    setchildval(tagnode, "rw", to_str(((tagstruct*) & it->tginfo)->rwtype()));
                }
            }


            if (base.users.size() > 0) {
                pugi::xml_node usersnode = rootnode.append_child();
                usersnode.set_name(NS_XML_USERS_IMPORT.c_str());
                for (vect_user_data::iterator it = base.users.begin(); it != base.users.end(); ++it) {
                    pugi::xml_node usernode = usersnode.append_child();
                    usernode.set_name(NS_XML_USER_IMPORT.c_str());
                    setattribute(usernode, "name", it->name);
                    setattribute(usernode, "password", it->password);
                    setattribute(usernode, "level", to_str(it->accesslevel));
                }
            }

            doc.save_file(filepath.c_str());
            return true;
        }

        static std::string add_csv_escapesec(const std::string& vl) {
            std::string rslt = vl;
            if (!rslt.empty()) {
                boost::algorithm::replace_all(rslt, ";", "\";\"");
                boost::algorithm::replace_all(rslt, ",", "\",\"");
                boost::algorithm::replace_all(rslt, "\n", "\"\n\"");
                boost::algorithm::replace_all(rslt, "\"", "\"\"");
            }
            return rslt;
        }        

        bool csv_setexportdata(std::string filepath, base_data& base) {
            std::string outdata = "Name;Group;Item;Comment;Logged;Type;LogDB;MinRaw;MaxRaw;MinEu;MaxEu;OnMsged;OnMsg;offMsged;"
                    "OffMsg;Val;AlarmMsg;AlarmLevel;AlarmCase;AlarmConst;DeadBaund;EU;RW;\n";
            for (vect_tag_data::iterator it = base.tags.begin(); it != base.tags.end(); ++it) {
                std::string tmpoutdata = "";
                tmpoutdata += it->name + ";";
                tmpoutdata += it->group + ";";
                tmpoutdata += add_csv_escapesec(it->bind) + ";";
                tmpoutdata += add_csv_escapesec(it->comment) + ";";
                if (((tagstruct*) & it->tginfo)->logged())
                    tmpoutdata += "true;";
                else tmpoutdata += "false;";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->type()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->logdb()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->minraw_str()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->maxraw_str()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->mineu_str()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->maxeu_str()) + ";";
                if (((tagstruct*) & it->tginfo)->onmsged())
                    tmpoutdata += "true;";
                else tmpoutdata += "false;";
                tmpoutdata += add_csv_escapesec(it->onmsg) + ";";
                if (((tagstruct*) & it->tginfo)->offmsged())
                    tmpoutdata += "true;";
                else tmpoutdata += "false;";
                tmpoutdata += add_csv_escapesec(it->offmsg) + ";";
                tmpoutdata += add_csv_escapesec(((tagstruct*)& it->tginfo)->value_str()) + (";");

                tmpoutdata +=add_csv_escapesec(it->almsg) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->alarmlevel()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->alarmcase()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->alarmconst_str()) + ";";
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->devdb()) + ";";
                tmpoutdata += add_csv_escapesec(it->ue) + ";" ;
                tmpoutdata += to_str(((tagstruct*) & it->tginfo)->rwtype()) + ";\n";
                outdata += tmpoutdata;
            }
            filestream::write(filepath, (void*) outdata.c_str(), 0, outdata.size());
            return true;
        }

        bool setexportdata(std::string filepath, base_data& base) {
            int type = gettipeimport(filepath);
            switch (type) {
                case TIPE_NS_IMPORT_XML: return xml_setexportdata(filepath, base);
                case TIPE_NS_IMPORT_CSV: return csv_setexportdata(filepath, base);
            }
            return false;
        }


    }
}
