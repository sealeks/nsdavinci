/* 
 * File:   AbstractItemWraper.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 19 Ноябрь 2009 г., 3:46
 */


#ifndef _ADMININTF_ABSTRACTWRAPER_H
#define	_ADMININTF_ABSTRACTWRAPER_H

#include <kernel/utils.h>

#include <admin/adminintf.h>
#include <admin/properties.h>


#define ADD_PROPERTYS(x) addinpropertyset((propidtype*)& x, ( (sizeof x) / sizeof (propidtype)));
#define REMOVE_PROPERTYS(x) removefrompropertyset((propidtype*)& x, ( (sizeof x) / sizeof (propidtype)));

namespace dvnci {
    namespace admin {

        class abstractwraper;

        typedef  std::set<propidtype , std::less<propidtype>, std::allocator<propidtype > > propertysset;
        typedef boost::shared_ptr<abstractwraper> abstractwraper_ptr;

        // Wraper для итемов групп, тегов, прочих узлов свойства которых
        // отображают в таблице

        // класс для обработчиков свойств таблице
        // остальные наследуют от него

        class abstractpropertyeditor {
        public:

            abstractpropertyeditor(propidtype tp, std::string pref = "", lcltype loc =  NS_CODPAGE_UTF8) : type_(tp), locale_(loc), prefix_(pref) {};

            virtual ~abstractpropertyeditor() {};

            void locale(lcltype val) {
                locale_ = val;}

            virtual lcltype locale() const  {
                return locale_;}

            virtual propidtype type() const  {
                return type_;}

            void prefix(std::string val) {
                prefix_ = val;}

            std::string prefix() const  {
                return prefix_;}

            const num64_set& list() const {
                return list_of_property;}

            std::string name(std::string id_) {
                return "";};

            std::string value(std::string id_) {
                return "";}

            void addpropertylist(num8 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(unum8 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(num16 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(unum16 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(num32 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(unum32 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(num64 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

            void addpropertylist(unum64 enump) {
                list_of_property.insert(static_cast<num64> (enump));};

        protected:
            propidtype type_;
            lcltype locale_;
            std::string prefix_;
            num64_set list_of_property;

            void type(propidtype val) {
                type_ = val;}} ;




        typedef std::pair<propidtype, abstractpropertyeditor*> propertyeditor_pair;
        typedef std::map<propidtype, abstractpropertyeditor*, std::less<propidtype>, std::allocator<propertyeditor_pair > > propertyeditor_map;

        class boolpropertyeditor : public abstractpropertyeditor {
        public:
            boolpropertyeditor();} ;

        class noeditItempropertyeditor : public abstractpropertyeditor {
        public:
            noeditItempropertyeditor();} ;

        class alarmcasepropertyeditor : public abstractpropertyeditor {
        public:
            alarmcasepropertyeditor();} ;
            
        class alarmcaseboolpropertyeditor : public abstractpropertyeditor {
        public:
            alarmcaseboolpropertyeditor();} ;    

        class alarmlevelpropertyeditor : public abstractpropertyeditor {
        public:
            alarmlevelpropertyeditor();} ;
            
        class rwpropertyeditor : public abstractpropertyeditor {
        public:
            rwpropertyeditor();} ;


        class dbproviderpropertyeditor : public abstractpropertyeditor {
        public:
            dbproviderpropertyeditor();} ;

        class typetagpropertyeditor : public abstractpropertyeditor {
        public:
            typetagpropertyeditor();} ;

        class reporttypetagpropertyeditor : public abstractpropertyeditor {
        public:
            reporttypetagpropertyeditor();} ;

        class reportstatistictagpropertyeditor : public abstractpropertyeditor {
        public:
            reportstatistictagpropertyeditor();} ;

        class debuglevpropertyeditor : public abstractpropertyeditor {
        public:
            debuglevpropertyeditor();} ;


        class typegrouppropertyeditor : public abstractpropertyeditor {
        public:
            typegrouppropertyeditor();} ;

        class rs232boundratepropertyeditor : public abstractpropertyeditor {
        public:
            rs232boundratepropertyeditor();} ;

        class rs232databitpropertyeditor : public abstractpropertyeditor {
        public:
            rs232databitpropertyeditor();} ;

        class rs232stopbitpropertyeditor : public abstractpropertyeditor {
        public:
            rs232stopbitpropertyeditor();} ;

        class rs232paritypropertyeditor : public abstractpropertyeditor {
        public:
            rs232paritypropertyeditor();} ;

        class typeservicestartpropertyeditor : public abstractpropertyeditor {
        public:
            typeservicestartpropertyeditor();} ;

        class opcverpertyeditor : public abstractpropertyeditor {
        public:
            opcverpertyeditor();} ;

        class opccontypepertyeditor : public abstractpropertyeditor {
        public:
            opccontypepertyeditor();} ;

        class baselinkpropertyeditor : public abstractpropertyeditor {
        public:
            baselinkpropertyeditor();} ;


        class grouplocalpropertyeditor : public abstractpropertyeditor {
        public:
            grouplocalpropertyeditor();} ;

        class abstractpropertymanager {
        public:
            virtual void registpropertyeditor(propidtype prop, abstractpropertyeditor* edit) = 0;} ;

        class abstractwraper {
        public:

            abstractwraper(lcltype loc = NS_CODPAGE_UTF8) : locale_(loc) {};

            virtual ~abstractwraper() {};

            void  intf(adminintf* inf) {
                _interface = inf;}

            void locale(lcltype val) {
                locale_ = val;}

            lcltype locale() const  {
                return locale_;}

            virtual void setids(const entity_map& vl) {};

            virtual  void excludegroupedit(propertysset& excl) {};

            void  addproprtyeditors(abstractpropertymanager* mangr) {
                if (mangr) addproprtyeditors_internal(mangr);}

            void  getPropertySet(propertysset& val) {
                val = set_of_propertys;}

            virtual void setProperty(indx id, propidtype prop, std::string val) = 0;
            virtual std::string getProperty(indx id, propidtype prop) = 0;

            virtual void commit(indx id) {};


        protected:
            propertysset             set_of_propertys;
            adminintf*               _interface;
            lcltype                  locale_;
            boolpropertyeditor       boolPrEdit;
            noeditItempropertyeditor noEditPrEdit;

            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr) {};

            void removefrompropertyset(propidtype prop) {
                set_of_propertys.erase(prop);}

            void addinpropertyset(propidtype prop) {
                set_of_propertys.insert(prop);}

            void removefrompropertyset(propidtype* props, size_t cnt) {
                while ((cnt--) > 0) {
                    removefrompropertyset(*props);
                    props++;}}

            void addinpropertyset(propidtype* props, size_t cnt) {
                while ((cnt--) > 0) {
                    addinpropertyset(*props);
                    props++;}}} ;

        class nillwraper : public abstractwraper {
        public:

            nillwraper(lcltype loc = NS_CODPAGE_UTF8) : abstractwraper(loc) {};

            virtual void setProperty(indx id, propidtype prop, std::string val) {};

            virtual std::string getProperty(indx id, propidtype prop) {
                return "";}
        protected:} ;


        // Базовый класс обертка для тегов базы

        class basetagwraper : public abstractwraper {
        public:
            basetagwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void commit(indx id);

        protected:
            alarmcasepropertyeditor  acasePrEdit;
            alarmlevelpropertyeditor alevelPrEdit;
            typetagpropertyeditor    typePrEdit;
            rwpropertyeditor         rwPrEdit;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        class basereportcnttagwraper : public basetagwraper {
        public:
            basereportcnttagwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            reportstatistictagpropertyeditor statPrEdit;

            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;
            
        class basereporttagwraper : public basereportcnttagwraper {    
        public:
            basereporttagwraper(lcltype loc = NS_CODPAGE_UTF8);};


        class basenumerictagwraper : public basetagwraper {
        public:
            basenumerictagwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class basebooltagwraper : public basetagwraper {
        public:
            basebooltagwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            alarmcaseboolpropertyeditor  acaseboolPrEdit;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;
            
            

        class eventtagwraper : public basetagwraper {
        public:
            eventtagwraper(lcltype loc = NS_CODPAGE_UTF8);
           virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;
            
        //texttagwraper    
            
        class texttagwraper : public basetagwraper {
        public:
           texttagwraper(lcltype loc = NS_CODPAGE_UTF8);} ; 
            
        //timetagwraper
           
        class timetagwraper : public basetagwraper {
        public:
           timetagwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        // Базовый класс обертка для групп базы

        class basegroupwraper : public abstractwraper {
        public:
            basegroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void commit(indx id);
        protected:
            typegrouppropertyeditor        typePrEdit;
            rs232boundratepropertyeditor   rs232brPrEdit;
            rs232databitpropertyeditor     rs232dbPrEdit;
            rs232stopbitpropertyeditor     rs232sbPrEdit;
            rs232paritypropertyeditor      rs232prtPrEdit;
            grouplocalpropertyeditor       grlcPrEdit;
            std::string enum_;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        class defaultgroupwraper : public basegroupwraper {
        public:
            defaultgroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class netgroupwraper : public basegroupwraper {
        public:
            netgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        class opcgroupwraper : public basegroupwraper {
        public:
            opcgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            opcverpertyeditor      opcverPrEdit;
            opccontypepertyeditor  opcconPrEdit;

            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        class ddegroupwraper : public basegroupwraper {
        public:
            ddegroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        class systemgroupwraper : public basegroupwraper {
        public:
            systemgroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class sysvargroupwraper : public basegroupwraper {
        public:
            sysvargroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class systemcountgroupwraper : public basegroupwraper {
        public:
            systemcountgroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class systemcommandcasegroupwraper : public basegroupwraper {
        public:
            systemcommandcasegroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class systemreportgroupwraper : public basegroupwraper {
        public:
            systemreportgroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class systemreportcountgroupwraper : public basegroupwraper {
        public:
            systemreportcountgroupwraper(lcltype loc = NS_CODPAGE_UTF8);} ;

        class linkgroupwraper : public basegroupwraper {
        public:
            linkgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp(chnltype tp);};


        class agroupwraper : public abstractwraper {
        public:
            agroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype property_);
            virtual void commit(indx id);} ;

        class userwraper : public abstractwraper {
        public:
            userwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void commit(indx id);} ;
            
        class accessrulewraper : public abstractwraper {
        public:
            accessrulewraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void commit(indx id);} ;


        class configprjwraper : public abstractwraper {
        public:
            configprjwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void commit(indx id);

            virtual lcltype local() const {
                return NS_CODPAGE_UTF8;}

        protected:
            debuglevpropertyeditor   debuglevPred;
            dbproviderpropertyeditor dbprovPred;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        // обработка сервисов

        class baseserviceitemwraper : public abstractwraper {
        public:
            baseserviceitemwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void excludegroupedit(propertysset& excl);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype property_);

        protected:
            typeservicestartpropertyeditor starttypred;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;
}}

#endif
