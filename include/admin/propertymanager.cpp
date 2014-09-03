/* 
 * File:   ImmiPropertyManager.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 20 Ноябрь 2009 г., 12:54
 */

#include <admin/propertymanager.h>

namespace dvnci {
    namespace admin {

        propertymanager::propertymanager(lcltype loc) : abstractpropertymanager(), locale_(loc) {

            registwraper(NT_TAG, new basetagwraper());

            registwraper(REPORTTYPE_YEAR, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_MIN, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_HOUR, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_DEC, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_DAY, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_MONTH, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_10MIN, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_30MIN, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_QVART, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_CUSTOM, NT_TAG, new basereporttagwraper());
            registwraper(REPORTTYPE_NONE, NT_TAG, new basereporttagwraper());

            registwraper(TYPE_NUM64, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_UNUM64, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_NUM32, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_UNUM32, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_NUM16, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_UNUM16, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_NUM8, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_UNUM8, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_FLOAT, NT_TAG, new basenumerictagwraper());
            registwraper(TYPE_DOUBLE, NT_TAG, new basenumerictagwraper());

            registwraper(TYPE_TEXT, NT_TAG, new texttagwraper());
            registwraper(TYPE_TIME, NT_TAG, new timetagwraper());
            registwraper(EVENT_TYPE_WITHTIME, NT_TAG, new eventtagwraper());

            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_YEAR, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_MIN, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_HOUR, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_DEC, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_DAY, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_MONTH, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_10MIN, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_30MIN, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_QVART, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_CUSTOM, NT_TAG, new basereportcnttagwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, REPORTTYPE_NONE, NT_TAG, new basereportcnttagwraper());


            registwraper(NT_SERVICE, new nillwraper());
            registwraper(SERVICE_STATUS_RUN, NT_SERVICE, new baseserviceitemwraper());
            registwraper(SERVICE_STATUS_STOPED, NT_SERVICE, new baseserviceitemwraper());
            registwraper(SERVICE_STATUS_PENDING, NT_SERVICE, new baseserviceitemwraper());


            registwraper(TYPE_DISCRET, NT_TAG, new basebooltagwraper());

            registwraper(NS_GROUP_SYSTEM, NT_GROUP, new systemgroupwraper());
            registwraper(NS_GROUP_SYSTEMVAR, NT_GROUP, new sysvargroupwraper());
            registwraper(NS_GROUP_SYSTEMCOUNT, NT_GROUP, new systemcountgroupwraper());
            registwraper(NS_GROUP_SYSTEMREPORT, NT_GROUP, new systemreportgroupwraper());
            registwraper(NS_GROUP_SYSTEMREPORTCOUNT, NT_GROUP, new systemreportcountgroupwraper());
            registwraper(NS_GROUP_NET, NT_GROUP, new netgroupwraper());
            registwraper(NS_GROUP_OPC, NT_GROUP, new opcgroupwraper());
            registwraper(NS_GROUP_DDE, NT_GROUP, new ddegroupwraper());
            registwraper(NS_GROUP_MODBUS, NT_GROUP, new modbusgroupwraper());
            registwraper(NS_GROUP_KOYO, NT_GROUP, new koyogroupwraper());
            registwraper(NS_GROUP_LGKA, NT_GROUP, new lgkgroupwraper());
            registwraper(NS_GROUP_MMS, NT_GROUP, new mmsgroupwraper());
            registwraper(NS_GROUP_IEC60870, NT_GROUP, new iec60870groupwraper());


            registwraper(NT_GROUP, new defaultgroupwraper());
            registwraper(NT_AGROUP, new agroupwraper());
            registwraper(NT_USER, new userwraper());
            registwraper(NT_ACCESSRULE, new accessrulewraper());
            registwraper(NT_ROOT_SERVERS_AVAIL, new configprjwraper());
            registwraper(NT_ROOT_SERVERS_AVAIL_R, new configprjwraper());
            registwraper(NT_MF_REPHEADER, new repheaderwraper());
            registwraper(NT_MF_REPARR, new reparrrwraper());
            registwraper(NT_MF_UNIT, new unitwraper());
            registwraper(NT_MF_TRENDHEADER, new trendheaderwraper());
            registwraper(NT_MF_TRENDARR, new trendarrwraper());
            registwraper(NT_MF_TREND, new trendwraper());
            registwraper(NT_MF_MESSHEADER, new messageheaderwraper());
            registwraper(NT_MF_MESSARR, new messagearrwraper());
            registwraper(NT_MF_MESSAGE, new messagewraper());
            registwraper(NT_MF_ROOT, new metawraper());
        }

        void propertymanager::intf(adminintf_ptr _interface_) {
            _interface = _interface_;
            for (ninfotp_wrapers_map::iterator it = wrapers.begin(); it != wrapers.end(); ++it) {
                it->second->intf(_interface.get());
            }
        }

        void propertymanager::registwraper(nodeinfotype type, abstractwraper* wraper) {
            wrapers.insert(ninfotp_wrapers_pair(type, abstractwraper_ptr(wraper)));
            wraper->excludegroupedit(excl_groupeditset);
            wraper->addproprtyeditors(this);
        }

        void propertymanager::registwraper(nodetype type, abstractwraper* wraper) {
            registwraper(nodeinfotype(type), wraper);
        }

        void propertymanager::registwraper(tagtype enttype, nodetype type, abstractwraper* wraper) {
            registwraper(nodeinfotype(type, enttype), wraper);
        }

        void propertymanager::registwraper(appidtype parttype, tagtype enttype, nodetype type, abstractwraper* wraper) {
            registwraper(nodeinfotype(type, enttype, parttype), wraper);
        }

        void propertymanager::registpropertyeditor(propidtype prop, abstractpropertyeditor* edit) {
            propeditors.insert(propertyeditor_pair(prop, edit));
        }

        abstractwraper_ptr propertymanager::findwraper(nodeinfotype type) {
            DEBUG_STR_VAL_DVNCI(findwraper, type.node())
            DEBUG_STR_VAL_DVNCI(findwraper, type.tgtype())
            DEBUG_STR_VAL_DVNCI(findwraper, type.pttype())
            ninfotp_wrapers_map::iterator it = wrapers.find(type);
            if (it != wrapers.end()) return it->second;
            num64 tmp = type;
            type = nodeinfotype(0xFFFFFFFF & tmp);
            it = wrapers.find(type);
            if (it != wrapers.end()) return it->second;
            type = nodeinfotype(0xFFFF & tmp);
            it = wrapers.find(type);
            if (it != wrapers.end()) return it->second;
            return abstractwraper_ptr();
        }

        void propertymanager::parsenodes(entity_map& nodes, propertytable_map& map) {
            entity_inproccess.clear();
            for (entity_map::iterator it = nodes.begin(); it != nodes.end(); ++it) {
                entity_inproccess.insert(*it);
            }
            propertymanager::parsenodes();
            map = table;
        }

        void propertymanager::excludegroupedit(propidtype id) {
            excl_groupeditset.insert(id);
        }

        void propertymanager::removeexcl_groupedit(list_of_mapentity& val) {
            for (property_set::iterator it = excl_groupeditset.begin(); it != excl_groupeditset.end(); ++it) {
                if (properties.find(*it) != properties.end()) properties.erase(*it);
            }
        }

        void propertymanager::parsenodes() {

            list_propertymap.clear();
            update_prop.clear();
            diff_prop.clear();
            wrapersitems.clear();
            for (entity_map::iterator it = entity_inproccess.begin(); it != entity_inproccess.end(); ++it) {
                // получить список свойств

                nodeinfotype type_node = it->second;
                indx id_node = it->first;
                // поск специфичного обработчика
                abstractwraper_ptr tmp_wrap = findwraper(type_node);

                if (tmp_wrap) {
                    // составляем карту айтемс - wraper
                    wrapersitems.insert(indx_wrapers_pair(id_node, abstractwraper_ptr(tmp_wrap)));
                    tmp_wrap->setids(entity_inproccess);
                }
            }

            // составляем множества свойств для каждого айтема
            // и пихаем их в лист
            for (indx_wrapers_map::iterator it = wrapersitems.begin(); it != wrapersitems.end(); ++it) {
                propertysset smp;
                it->second->getPropertySet(smp);
                list_propertymap.push_back(smp);
            }

            // исключаем из списка свойств уникальные, остается только пересекающееся множество
            // пихаем ризультат в карту properties
            removeunical(list_propertymap);

            // исключаем свойства нередактируемые в группе из карты properties
            if (list_propertymap.size() > 1) removeexcl_groupedit(list_propertymap);
            // заполняем список свойств значениями на отображение
            fillValueProperties();
            getTable();
        }

        void propertymanager::removeunical(list_of_mapentity& val) {
            properties.clear();
            if (val.empty()) return;
            property_set* firstelem = &val[0];
            if (firstelem) {
                for (property_set::iterator it = firstelem->begin(); it != firstelem->end(); ++it) {
                    list_of_mapentity::iterator it_list_start = val.begin();
                    it_list_start++;
                    list_of_mapentity::iterator it_list_end = val.end();
                    if (findKeyinList(it_list_start, it_list_end, *it))
                        properties.insert(prop_str_pair(*it, ""));
                }
            }
        }

        bool propertymanager::findKeyinList(list_of_mapentity::iterator from, list_of_mapentity::iterator t, propidtype prop) {
            list_of_mapentity::iterator it = from;
            while (it != t) {
                if ((*it).find(prop) == (*it).end()) return false;
                ++it;
            }
            return true;
        }

        std::string propertymanager::getPropertyVal(indx id, propidtype prop) {
            indx_wrapers_map::iterator it = wrapersitems.find(id);
            return (it != wrapersitems.end()) ? it->second->getProperty(id, prop) : "";
        }

        void propertymanager::fillValueProperties() {
            prop_str_map::iterator propiter = properties.begin();
            while (propiter != properties.end()) {
                propidtype tmppropid = propiter->first;
                entity_map::iterator it = entity_inproccess.begin();
                std::string propval_ = getPropertyVal(it->first, tmppropid);
                ++it;
                while (it != entity_inproccess.end()) {
                    if (getPropertyVal(it->first, tmppropid) != propval_) {
                        propval_ = "";
                        diff_prop.insert(tmppropid);
                    }
                    ++it;
                }
                properties[tmppropid] = propval_;
                propiter++;
            }
        }

        void propertymanager::getTable() {

            table.clear();
            for (prop_str_map::iterator it = properties.begin(); it != properties.end(); ++it) {
                propertyinfo tmp;
                tmp.type = it->first;
                tmp.value = it->second;
                tmp.isDiff = (diff_prop.find(it->first) != diff_prop.end());
                abstractpropertyeditor* predit = propeditors[it->first];
                tmp.type = (predit) ? predit->type() : 0;
                tmp.local = locale_;
                if (tmp.type == TYPE_PE_LIST) {
                    tmp.set = predit->list();
                    tmp.name = predit->prefix();
                }
                table.insert(propertytable_pair(it->first, tmp));
            }
        }

        void propertymanager::updateproperty(propidtype type, std::string val) {
            prop_str_map::iterator it = properties.find(type);
            if (it == properties.end()) return;
            if (it->second != val) update_prop.insert(prop_str_pair(type, val));
            else update_prop.erase(it->first);
        }

        void propertymanager::merge(entity_map& nodes, propertytable_map& map) {

            propertytable_map tmp;
            parsenodes(nodes, tmp);

            for (propertytable_map::iterator it = map.begin(); it != map.end(); ++it) {
                if (it->second.inChange) {
                    updateproperty(it->first, it->second.value);
                }
            }

            for (entity_map::iterator it = entity_inproccess.begin(); it != entity_inproccess.end(); ++it) {
                indx_wrapers_map::iterator it1 = wrapersitems.find(it->first);
                if (it1 != wrapersitems.end()) merge_innode(it->first, it1->second.get());
            }

            parsenodes();
            map = table;
        }

        void propertymanager::merge_innode(propidtype prid, abstractwraper* wraper) {

            for (prop_str_map::iterator it = update_prop.begin(); it != update_prop.end(); ++it) {
                abstractpropertyeditor* predit = propeditors[it->first];
                if (predit) {
                    switch (predit->type()) {
                        case TYPE_PE_CHECKED:
                        {
                            wraper->setProperty(prid, it->first, it->second);
                        }
                        case TYPE_PE_LIST:
                        {
                            wraper->setProperty(prid, it->first, it->second);
                        }
                    }
                } else
                    wraper->setProperty(prid, it->first, it->second);
            }
            wraper->commit(prid);
        }
    }
}
