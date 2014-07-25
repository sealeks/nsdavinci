/* 
 * File:   lgk_entitywraper.cpp
 * Author: Serg
 * 
 * Created on 31 Октябрь 2010 г., 2:31
 */

#include <admin/iec60870_entitywraper.h>

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

        iec60870linkpropertyeditor::iec60870linkpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "MBLinkbasetype") {
            addpropertylist(NT_CHTP_NODEF);
            addpropertylist(NT_CHTP_RS232_4XX);
            addpropertylist(NT_CHTP_TCP_IP);}

        iec60870protocolpropertyeditor::iec60870protocolpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "MBProtocolbasetype") {
            addpropertylist(NT_MODBUS_RTU);
            addpropertylist(NT_MODBUS_ASCII);}



        iec60870groupwraper::iec60870groupwraper(lcltype loc) : linkgroupwraper(loc){
            enum_ = "IEC60870GROUP";
            propidtype propdel[] = { PROPERTY_GR_GR, PROPERTY_CHANALNUM_GROUP, PROPERTY_GR_SYNCT, PROPERTY_CHANALPORT_GROUP, 
                                     PROPERTY_RS232_DATABIT,  PROPERTY_RS232_STOPBIT, PROPERTY_CHANALTYPE_GROUP};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_MDB_CHANALTYPE_GROUP};
            ADD_PROPERTYS(propadd);}

        void iec60870groupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_MDB_CHANALTYPE_GROUP, &ModBLPrEdit);
            mangr->registpropertyeditor(PROPERTY_MODBUS_PROTOCOL, &ModBPPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_BOUNDRATE, &rs232brPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_DATABIT, &rs232dbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_STOPBIT, &rs232sbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_PARITY, &rs232prtPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_FLOWCTRL, &boolPrEdit);}

        void iec60870groupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {

                case PROPERTY_MDB_CHANALTYPE_GROUP: {
                    chnltype val_ = 0;
                    if (str_to<chnltype>(val, val_))
                           _interface->group().chanaltype(in_bounded<num32>(0,2,val_));
                    break;}

                case PROPERTY_MODBUS_PROTOCOL:{
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if ((val_>=0) && (val_<=1))
                           _interface->group().protocol(val_);
                    break;}
                case PROPERTY_RS232_PARITY:{
                    rsparitytype val_=0;
                    if (str_to<rsparitytype>(val, val_)){
                        val_ = (val_>2) ? 0 : val_;
                        if (_interface->group(id).config())
                                static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity(val_);}
                    break;}
                 default: linkgroupwraper::setProperty(id, prop, val);}}


        std::string iec60870groupwraper::getProperty(indx id, propidtype prop){

            switch (prop) {

                case PROPERTY_MDB_CHANALTYPE_GROUP: {
                    chnltype val_ = ((_interface->group(id).chanaltype()>=0) && ((_interface->group(id).chanaltype()<3))) ? _interface->group(id).chanaltype() : 0;
                    return to_str<chnltype>(val_);
                    break;}
                case PROPERTY_MODBUS_PROTOCOL:{
                    num32 val_ = ((_interface->group(id).protocol()>=0) && ((_interface->group(id).protocol()<=1))) ? _interface->group(id).protocol() : 0;
                    return to_str<num32>(val_);
                    break;}
                case PROPERTY_RS232_PARITY:{
                    rsparitytype val_ = (_interface->group(id).config()) ?
                        ((static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity()> 2) ?
                            0 : static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity()) :
                        0;
                    return to_str<rsparitytype>(val_);
                    break;}
                default: return linkgroupwraper::getProperty(id, prop);}}


        void iec60870groupwraper::setchaneltp_and_prtcl(chnltype tp, num32 prtcl){
                 REMOVE_PROPERTYS(mdb_propmainadd)
                    if (tp==NT_CHTP_RS232_4XX){
                       switch(prtcl){
                       case 0: {ADD_PROPERTYS(mdb_propmainadd_rtu_add); break;}
                       case 1: {ADD_PROPERTYS(mdb_propmainadd_ascii_add); break;}}}
                    else {
                       if (tp==NT_CHTP_TCP_IP){
                           ADD_PROPERTYS(mdb_propmainadd_tcp_add);}}}

        void iec60870groupwraper::setids(const entity_map& vl){
            typedef std::set<chnltype , std::less<chnltype>, std::allocator<chnltype> > chnltype_settmp;
            typedef std::set<num32 , std::less<num32>, std::allocator<num32> > prtcl_settmp;
            chnltype_settmp tmp;
            prtcl_settmp tmpprtcl;
            chnltype val_=0;
            num32 prtclval_=0;
            for (entity_map::const_iterator it = vl.begin(); it != vl.end(); ++it){
                val_ = ((_interface->group(it->first).chanaltype()>=0) && ((_interface->group(it->first).chanaltype()<3))) ? _interface->group(it->first).chanaltype() : 0;
                prtclval_ = ((_interface->group(it->first).protocol()>=0) && ((_interface->group(it->first).protocol()<=1))) ? _interface->group(it->first).protocol() : 0;
                tmpprtcl.insert(prtclval_);
                tmp.insert(val_);}
            val_=(tmp.size()!=1) ? 0 : (*tmp.begin());
            prtclval_=(tmpprtcl.size()!=1) ? 0 : (*tmpprtcl.begin());
            setchaneltp_and_prtcl(val_, prtclval_);}


    }}