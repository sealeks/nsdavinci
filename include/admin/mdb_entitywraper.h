
#ifndef _ADMININTF_MODBUSWRAPER_H
#define	_ADMININTF_MODBUSWRAPER_H

#include <admin/entitywraper.h>

namespace dvnci {
    namespace admin {

        class modbuslinkpropertyeditor : public abstractpropertyeditor {

        public:
            modbuslinkpropertyeditor();
        };

        class modbusprotocolpropertyeditor : public abstractpropertyeditor {

        public:
            modbusprotocolpropertyeditor();
        };

        class modbusgroupwraper : public linkgroupwraper {

        public:
            modbusgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            modbuslinkpropertyeditor ModBLPrEdit;
            modbusprotocolpropertyeditor ModBPPrEdit;
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp_and_prtcl(chnltype tp, num32 prtcl);
        };

    }
}

#endif