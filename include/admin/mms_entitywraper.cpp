/* 
 * File:   lgk_entitywraper.cpp
 * Author: Serg
 * 
 * Created on 31 Октябрь 2010 г., 2:31
 */

#include <admin/mms_entitywraper.h>

namespace dvnci {
    namespace admin {

const propidtype mdb_propmainadd[] =         { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RSNUM_GROUP, PROPERTY_CHANALHOST_ADDR_GROUP,
                                               PROPERTY_GR_TCNT, PROPERTY_GR_INDTO, PROPERTY_RS232_PARITY,
                                               PROPERTY_GR_TO,   PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_MODBUS_PROTOCOL };

const propidtype mdb_propmainadd_rtu_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_PARITY,
                                                PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                                PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,
                                                PROPERTY_GR_BS,  PROPERTY_MODBUS_PROTOCOL };

const propidtype mdb_propmainadd_ascii_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_PARITY,
                                                  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                                  PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,
                                                  PROPERTY_GR_BS,  PROPERTY_MODBUS_PROTOCOL };

const propidtype mdb_propmainadd_tcp_add[] = { PROPERTY_CHANALHOST_ADDR_GROUP, PROPERTY_DEVNUM_GROUP,  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                               PROPERTY_GR_TO, PROPERTY_GR_BS };

        mmslinkpropertyeditor::mmslinkpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "MBLinkbasetype") {
            addpropertylist(NT_CHTP_NODEF);
            addpropertylist(NT_CHTP_RS232_4XX);
            addpropertylist(NT_CHTP_TCP_IP);}

        mmsprotocolpropertyeditor::mmsprotocolpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "MBProtocolbasetype") {
            addpropertylist(NT_MODBUS_RTU);
            addpropertylist(NT_MODBUS_ASCII);
        }

        mmsgroupwraper::mmsgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "MMSGROUP";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_CHANALHOST_GROUP, PROPERTY_MMSDOMAIN/*, PROPERTY_CHANALUSER_GROUP, 
            PROPERTY_CHANALPASSWORD_GROUP*/};
            ADD_PROPERTYS(propadd);
        }

const propidtype PROPERTY_MMSSELECTOR=0x047A;

        void mmsgroupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {
                case PROPERTY_CHANALHOST_GROUP:
                {
                    _interface->group(id).host(val);
                    break;
                };
                case PROPERTY_CHANALUSER_GROUP:
                {
                    _interface->group(id).user(val);
                    break;
                };
                case PROPERTY_CHANALPASSWORD_GROUP:
                {
                    _interface->group(id).password(val);
                    break;
                };
                case PROPERTY_MMSDOMAIN:
                {
                    _interface->group(id).topic(val);
                    break;
                };           
                default: basegroupwraper::setProperty(id, prop, val);
            }
        }

        std::string mmsgroupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_CHANALHOST_GROUP: return _interface->group(id).host();
                case PROPERTY_MMSDOMAIN: return _interface->group(id).topic();
                case PROPERTY_CHANALUSER_GROUP: return _interface->group(id).user();
                case PROPERTY_CHANALPASSWORD_GROUP: return _interface->group(id).password();
                default: return basegroupwraper::getProperty(id, prop);
            }
        }


    }}