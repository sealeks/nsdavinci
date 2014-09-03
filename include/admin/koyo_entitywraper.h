
#ifndef _ADMININTF_KOYOWRAPER_H
#define	_ADMININTF_KOYOWRAPER_H


#include <admin/entitywraper.h>


namespace dvnci {
    namespace admin {

        class koyolinkpropertyeditor : public abstractpropertyeditor {

        public:
            koyolinkpropertyeditor();
        };

        class koyoprotocolpropertyeditor : public abstractpropertyeditor {

        public:
            koyoprotocolpropertyeditor();
        };

        class koyogroupwraper : public linkgroupwraper {

        public:
            koyogroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            koyolinkpropertyeditor KoyoLPrEdit;
            koyoprotocolpropertyeditor KoyoPPrEdit;
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp_and_prtcl(chnltype tp, num32 prtcl);
        };

    }
}

#endif