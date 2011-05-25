/* 
 * File:   Itemwraper.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 2 Февраль 2010 г., 17:54
 */

#ifndef _ADMININTF_METAITEMWRAPER_H
#define	_ADMININTF_METAITEMWRAPER_H

#include <admin/entitywraper.h>


namespace dvnci {
    namespace admin {


        // типы атрибутов
        const int CMI_PROPERTY_TYPE_INT = 0x1;
        const int CMI_PROPERTY_TYPE_UINT = 0x2;
        const int CMI_PROPERTY_TYPE_STR = 0x0;
        const int CMI_PROPERTY_TYPE_BOOL = 0x3;
        const int CMI_PROPERTY_TYPE_DOUBLE = 0x4;




        // имена атрибутов

        // <ReportHeader>
        const std::string PROPERTY_NT_REPHEADER_NAME_STR = "name";
        const std::string PROPERTY_NT_REPHEADER_COLOR_STR = "color";
        const std::string PROPERTY_NT_REPHEADER_TEXTCOLOR_STR = "textcolor";
        const std::string PROPERTY_NT_REPHEADER_FONTSIZE_STR = "fontsize";

        // <ReportArr>
        const std::string PROPERTY_NT_REPARR_NAME_STR = "name";
        const std::string PROPERTY_NT_REPARR_DELT_STR = "delt";
        const std::string PROPERTY_NT_REPARR_GROUP_STR = "group";
        const std::string PROPERTY_NT_REPARR_WIDTH_STR = "width";
        const std::string PROPERTY_NT_REPARR_HEIGHT_STR = "height";
        const std::string PROPERTY_NT_REPARR_TYPE_STR = "type";
        const std::string PROPERTY_NT_REPARR_INITPER_STR = "initperiod";
        const std::string PROPERTY_NT_REPARR_SUBPER_STR = "subperiod";
        const std::string PROPERTY_NT_REPARR_AUTOPRINT_STR = "autoprint";
        const std::string PROPERTY_NT_REPARR_AUTOCLOSE_STR = "autoclose";
        const std::string PROPERTY_NT_REPARR_FOOTERSTR_STR = "foottext";

        // <unit>
        const std::string PROPERTY_NT_RUNIT_TG_STR = "tg";
        const std::string PROPERTY_NT_RUNIT_SUMTYPE_STR = "sumtype";
        const std::string PROPERTY_NT_RUNIT_ROUND_STR = "round";
        const std::string PROPERTY_NT_RUNIT_ROWCOLOR_STR = "rowcolor";
        const std::string PROPERTY_NT_RUNIT_TEXTCOLOR_STR = "textcolor";
        const std::string PROPERTY_NT_RUNIT_NEGCOLOR_STR = "negcolor";

        // <TrendHeader>
        const std::string PROPERTY_NT_TRENDHEADER_NAME_STR = "name";

        // <TrendArr>
        const std::string PROPERTY_NT_TRENDARR_NAME_STR = "name";

        // <trend>
        const std::string PROPERTY_NT_RTRENT_TG_STR = "tg";
        const std::string PROPERTY_NT_RTRENT_HEIGHT_STR = "height";
        const std::string PROPERTY_NT_RTRENT_FILL_STR = "fill";
        const std::string PROPERTY_NT_RTRENT_PENCOLOR_STR = "pencolor";
        const std::string PROPERTY_NT_RTRENT_FILLCOLOR_STR = "fillcolor";
        const std::string PROPERTY_NT_RTRENT_WIDTH_STR = "width";

        // <MessageHeader>
        const std::string PROPERTY_NT_MESSHEADER_NAME_STR = "name";

        // <MessageArr>
        const std::string PROPERTY_NT_MESSARR_NAME_STR = "name";

        // <message>
        const std::string PROPERTY_NT_RMESSAGE_TG_STR = "tg";

        //<meta>
        const std::string PROPERTY_NT_META_PROVIDER_STR = "DBProvider";
        const std::string PROPERTY_NT_META_CONSTR_STR = "constd::string";
        const std::string PROPERTY_NT_META_HOST_STR = "host";

        // Base class

        class basemetawraper : public abstractwraper {
        public:

            basemetawraper(lcltype loc = NS_CODPAGE_UTF8) : abstractwraper(loc) {};
            virtual void commit(indx id);

            virtual lcltype local() const {
                return NS_CODPAGE_UTF8;}
        protected:
            nodetype basetypeitem;
            virtual void setValue(propidtype type_, indx id, std::string attribname_, std::string val, std::string def_tp = "1", int min_ = -2000000, int max = 2000000 );
            virtual std::string value(propidtype type_, indx id, std::string attribname_,  std::string def_tp = "0");} ;


        // обработчик <ReportArr>

        class reparrrwraper : public basemetawraper {
        public:
            reparrrwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            reporttypetagpropertyeditor reptypePred;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        // обработчик <ReportHeader>

        class repheaderwraper : public basemetawraper {
        public:
            repheaderwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <unit>

        class unitwraper : public basemetawraper {
        public:
            unitwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            reportstatistictagpropertyeditor repstatPred;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        // обработчик <TrendArr>

        class trendarrwraper : public basemetawraper {
        public:
            trendarrwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <TrendHeader>

        class trendheaderwraper : public basemetawraper {
        public:
            trendheaderwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <trend>

        class trendwraper : public basemetawraper {
        public:
            trendwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        protected:
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;

        // обработчик <MessageArr>

        class messagearrwraper : public basemetawraper {
        public:
            messagearrwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <MessageHeader>

        class messageheaderwraper : public basemetawraper {
        public:
            messageheaderwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <message>

        class messagewraper : public basemetawraper {
        public:
            messagewraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;

        // обработчик <meta>

        class metawraper : public basemetawraper {
        public:
            metawraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
        private:
            dbproviderpropertyeditor dbprovPred;
        protected:
            reportstatistictagpropertyeditor repstatPred;
            virtual  void addproprtyeditors_internal(abstractpropertymanager* mangr);} ;
}}

#endif	/* _ITEMwraper_H */

