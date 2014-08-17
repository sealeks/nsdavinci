
#ifndef _ADMININTF_MMSWRAPER_H
#define	_ADMININTF_MMSWRAPER_H

#include <admin/entitywraper.h>

namespace dvnci {
    namespace admin {

        class mmslinkpropertyeditor : public abstractpropertyeditor {
        public:
            mmslinkpropertyeditor();};

        class mmsprotocolpropertyeditor : public abstractpropertyeditor {
        public:
            mmsprotocolpropertyeditor();} ;


        class mmsgroupwraper : public basegroupwraper {
        public:
            mmsgroupwraper(lcltype loc = NS_CODPAGE_UTF8);
            virtual void setProperty(indx id, propidtype prop, std::string val);
            virtual std::string getProperty(indx id, propidtype prop);} ;
    }
    }

#endif