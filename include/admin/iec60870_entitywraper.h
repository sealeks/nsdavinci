
#ifndef _ADMININTF_IEC60870WRAPER_H
#define	_ADMININTF_IEC60870WRAPER_H

#include <admin/entitywraper.h>

namespace dvnci {
    namespace admin {

        class iec60870linkpropertyeditor : public abstractpropertyeditor {
        public:
            iec60870linkpropertyeditor();};

        class iec60870protocolpropertyeditor : public abstractpropertyeditor {
        public:
            iec60870protocolpropertyeditor();} ;


        class iec60870groupwraper : public linkgroupwraper {
        public:
            iec60870groupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            iec60870linkpropertyeditor ModBLPrEdit;
            iec60870protocolpropertyeditor  ModBPPrEdit;
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp_and_prtcl(chnltype tp, num32 prtcl);};

    }
    }

#endif