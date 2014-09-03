/* 
 * File:   ImmiPropertyManager.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 20 Ноябрь 2009 г., 12:54
 */

#ifndef _ADMININTF_ADMINPROPERTYMANAGER_H
#define	_ADMININTF_ADMINPROPERTYMANAGER_H


#include "kernel/constdef.h"

#include <admin/properties.h>
#include <admin/entitywraper.h>
#include <admin/lgk_entitywraper.h>
#include <admin/mdb_entitywraper.h>
#include <admin/koyo_entitywraper.h>
#include <admin/mms_entitywraper.h>
#include <admin/iec60870_entitywraper.h>
#include <admin/metawraper.h>
#include <admin/adminintf.h>




namespace dvnci {
    namespace admin {

        struct propertyinfo {

            std::string value;
            lcltype local;
            num64_set set;
            propidtype type;
            bool inChange;
            bool isDiff;
            std::string name;

            bool operator==(const propertyinfo & val) {
                return ((type == val.type) && (value == val.value));
            };

            bool operator!=(const propertyinfo & val) {
                return (!operator==(val));
            };

            const propertyinfo & operator=(const propertyinfo & val) {
                set = val.set;
                value = val.value;
                local = val.local;
                type = val.type;
                inChange = val.inChange;
                isDiff = val.isDiff;
                name = val.name;
                return (*this);
            };

            propertyinfo(const propertyinfo & val) {
                set = val.set;
                value = val.value;
                local = val.local;
                type = val.type;
                inChange = val.inChange;
                isDiff = val.isDiff;
                name = val.name;
            };

            propertyinfo() {
                value = "";
                local = 0;
                type = 0;
                inChange = false;
                isDiff = false;
                name = "";
            };
        };

        typedef std::pair<propidtype, propertyinfo> propertytable_pair;
        typedef std::map<propidtype, propertyinfo, std::less<propidtype>, std::allocator<propertytable_pair > > propertytable_map;




        // класс обрабатывающий ветви и листья дерева базы
        // через метод parsenodes(entity_map& pair)
        // делегирует обработку нода конкретному наследнику AbstractItemWraper

        class propertymanager : public abstractpropertymanager {

        public:

            typedef std::set <propidtype, std::less<propidtype>, std::allocator<propidtype> > property_set;

            typedef std::pair<propidtype, std::string > prop_str_pair;
            typedef std::map <propidtype, std::string, std::less<propidtype>, std::allocator<prop_str_pair > > prop_str_map;

            typedef std::vector<property_set> list_of_mapentity;

            typedef std::pair<nodeinfotype, abstractwraper_ptr> ninfotp_wrapers_pair;
            typedef std::map<nodeinfotype, abstractwraper_ptr, std::less<nodeinfotype>, std::allocator<ninfotp_wrapers_pair > > ninfotp_wrapers_map;

            typedef std::pair<indx, abstractwraper_ptr> indx_wrapers_pair;
            typedef std::map<indx, abstractwraper_ptr, std::less<indx>, std::allocator<indx_wrapers_pair > > indx_wrapers_map;

            propertymanager(lcltype loc = NS_CODPAGE_UTF8);

            virtual ~propertymanager() {
            };
            void intf(adminintf_ptr _interface_);
            // установка локали

            void locale(lcltype val) {
                locale_ = val;
            }

            lcltype locale() const {
                return locale_;
            }
            // регистрация обработчиков свойств айтемов
            void registwraper(nodeinfotype type, abstractwraper* wraper);
            void registwraper(nodetype type, abstractwraper* wraper);
            void registwraper(tagtype enttype, nodetype type, abstractwraper* wraper);
            void registwraper(appidtype parttype, tagtype enttype, nodetype type, abstractwraper* wraper);
            // регистрация обработчиков редакторов специфических свойств айтемов
            virtual void registpropertyeditor(propidtype prop, abstractpropertyeditor* edit);
            // карта с айтемами и значениями на обработку передается на обработке
            abstractwraper_ptr findwraper(nodeinfotype type);
            // карта с айтемами и значениями на обработку передается на обработке
            void parsenodes(entity_map& nodes, propertytable_map& map);

            //есть ли ключ в диапазоне списка словарей?
            bool findKeyinList(list_of_mapentity::iterator from, list_of_mapentity::iterator t, propidtype propid);
            // заполняет общий словарь значениеми из списка словарей по ключам properties
            void fillValueProperties();

            void excludegroupedit(propidtype id);

            void updateproperty(propidtype type, std::string val);

            void merge(entity_map& nodes, propertytable_map& map);


        private:

            lcltype locale_;
            adminintf_ptr _interface;

            propertytable_map table;
            ninfotp_wrapers_map wrapers; // реестр обработчиков айтемов
            indx_wrapers_map wrapersitems; // карта id - wraper

            property_set excl_groupeditset; // множество исключенных на групповое редактирование свойств
            property_set diff_prop; // множество свойств с различными значениями для разных итемов

            propertyeditor_map propeditors; // реестр редакторов свойств
            list_of_mapentity list_propertymap; // список карт свойств для всех айтемов

            prop_str_map properties; // карта общих свойств для всех айтемов
            prop_str_map update_prop; // карта свойств обновлены, но ожидают закрепления
            entity_map entity_inproccess; // карта ссылок обрабатываемых тегов



            void getTable();
            void removeexcl_groupedit(list_of_mapentity& val);
            std::string getPropertyVal(indx id, propidtype prop);
            void parsenodes();
            void merge_innode(propidtype prid, abstractwraper* wraper);
            //находит совпадения ключей в списке словарей
            //общие ключи сует в properties
            void removeunical(list_of_mapentity& val);
        };
    }
}

#endif	/* _IMMIPROPERTYMANAGER_H */

