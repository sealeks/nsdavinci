
#ifndef _ADMININTF_IEC60870WRAPER_H
#define	_ADMININTF_IEC60870WRAPER_H

#include <admin/entitywraper.h>

namespace dvnci {
    namespace admin {

        class iec60870Link : public abstractpropertyeditor {

        public:
            iec60870Link();
        };
        
        class iec60870COT : public abstractpropertyeditor {

        public:
            iec60870COT();
        };        

        class iec60870Selector : public abstractpropertyeditor {

        public:
            iec60870Selector();
        };
        
        class iec60870IOA : public abstractpropertyeditor {

        public:
            iec60870IOA();
        };   
        
        class iec60870Protocol : public abstractpropertyeditor {

        public:
            iec60870Protocol();
        };           

        class iec60870groupwraper : public linkgroupwraper {

        public:
            iec60870groupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            iec60870Link LinkPrEdit;
            iec60870COT COTPrEdit;
            iec60870Selector SelectorPrEdit;
            iec60870IOA IOAPrEdit;  
            iec60870Protocol ProtPrEdit;  
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp_and_prtcl(chnltype tp, num32 prtcl);
        };

    }
}

#endif