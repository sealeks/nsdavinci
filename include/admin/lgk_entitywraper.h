
#ifndef _ADMININTF_LGKWRAPER_H
#define	_ADMININTF_LGKWRAPER_H

#include <admin/entitywraper.h>

namespace dvnci {
    namespace admin {

      class lgk_linkpropertyeditor : public abstractpropertyeditor {
        public:
            lgk_linkpropertyeditor();} ;

      class lgkprotocolpropertyeditor : public abstractpropertyeditor {
        public:
            lgkprotocolpropertyeditor();} ;

      class lgkgroupwraper : public linkgroupwraper {
        public:
            lgkgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);
            virtual void setids(const entity_map& vl);
        protected:
            lgk_linkpropertyeditor     LgkLPrEdit;
            lgkprotocolpropertyeditor  LgkProtPred;
            virtual void addproprtyeditors_internal(abstractpropertymanager* mangr);
            void setchaneltp_and_prtcl(chnltype tp, num32 prtcl);};

    }
    }

#endif