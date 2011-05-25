/* 
 * File:   lgk_entitywraper.cpp
 * Author: Serg
 * 
 * Created on 31 Октябрь 2010 г., 2:31
 */

#include <admin/koyo_entitywraper.h>

namespace dvnci {
    namespace admin {

const propidtype koyo_propmainadd[] =         { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RSNUM_GROUP, PROPERTY_CHANALHOST_ADDR_GROUP,
                                               PROPERTY_GR_TCNT, PROPERTY_GR_INDTO, PROPERTY_RS232_PARITY, PROPERTY_RS232_STOPBIT,
                                               PROPERTY_GR_TO,   PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_KOYO_PROTOCOL, PROPERTY_GR_SYNCT };

const propidtype koyo_propmainadd_rtu_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_PARITY,
                                                PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                                PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,
                                                PROPERTY_GR_BS,  PROPERTY_KOYO_PROTOCOL };

const propidtype koyo_propmainadd_tcp_add[] = { PROPERTY_CHANALHOST_ADDR_GROUP, PROPERTY_DEVNUM_GROUP,  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                               PROPERTY_GR_TO,PROPERTY_KOYO_PROTOCOL, PROPERTY_GR_BS };

const propidtype koyo_propmainadd_udp_add[] = { PROPERTY_CHANALHOST_ADDR_GROUP,  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                               PROPERTY_GR_TO, PROPERTY_KOYO_PROTOCOL, PROPERTY_GR_BS, PROPERTY_GR_SYNCT };

const propidtype koyo_propmainadd_dn_ascii_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_PARITY,PROPERTY_RS232_STOPBIT,
                                                  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                                  PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,
                                                  PROPERTY_GR_BS,  PROPERTY_KOYO_PROTOCOL, PROPERTY_GR_BS, PROPERTY_GR_SYNCT };

const propidtype koyo_propmainadd_dn_hex_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_PARITY,PROPERTY_RS232_STOPBIT,
                                                  PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                                  PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,
                                                  PROPERTY_GR_BS,  PROPERTY_KOYO_PROTOCOL, PROPERTY_GR_BS, PROPERTY_GR_SYNCT };



        koyolinkpropertyeditor::koyolinkpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "KoyoLinkbasetype") {
            addpropertylist(NT_CHTP_NODEF);
            addpropertylist(NT_CHTP_RS232_4XX);
            addpropertylist(NT_CHTP_TCP_IP);
            addpropertylist(NT_CHTP_UDP_IP);}


        koyoprotocolpropertyeditor::koyoprotocolpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "KoyoProtocolbasetype") {
            addpropertylist(NT_KOYO_MODBUS);
            addpropertylist(NT_KOYO_DIRECTNET_HEX);
            addpropertylist(NT_KOYO_DIRECTNET_ASCII);
            addpropertylist(NT_KOYO_DIRECTNET_ECOM);}


        koyogroupwraper::koyogroupwraper(lcltype loc) : linkgroupwraper(loc){
            enum_ = "KOYOGROUP";
            propidtype propdel[] = { PROPERTY_GR_GR, PROPERTY_CHANALNUM_GROUP,  PROPERTY_CHANALPORT_GROUP, 
                                     PROPERTY_RS232_DATABIT,  PROPERTY_RS232_STOPBIT, PROPERTY_CHANALTYPE_GROUP};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_KOYO_CHANALTYPE_GROUP, PROPERTY_KOYO_PROTOCOL};
            ADD_PROPERTYS(propadd);}

        void koyogroupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_KOYO_CHANALTYPE_GROUP, &KoyoLPrEdit);
            mangr->registpropertyeditor(PROPERTY_KOYO_PROTOCOL, &KoyoPPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_BOUNDRATE, &rs232brPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_DATABIT, &rs232dbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_STOPBIT, &rs232sbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_PARITY, &rs232prtPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_FLOWCTRL, &boolPrEdit);}

        void koyogroupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {

                case PROPERTY_KOYO_CHANALTYPE_GROUP: {
                    chnltype val_ = 0;
                    if (str_to<chnltype>(val, val_))
                           _interface->group().chanaltype(in_bounded<num32>(0,3,val_));
                    break;}

                case PROPERTY_KOYO_PROTOCOL:{
                    num32 val_ = 0;
                    switch (_interface->group(id).chanaltype()){
                        case NT_CHTP_RS232_4XX:{
                            if (str_to<num32>(val, val_)){
                                val_ = ((val_>=0) && ((val_<=2))) ? val_ : 0;
                                _interface->group().protocol(val_);}
                            break;}
                        case NT_CHTP_TCP_IP:{
                            _interface->group().protocol(NT_KOYO_MODBUS);
                            break;}
                        case NT_CHTP_UDP_IP:{
                            _interface->group().protocol(NT_CHTP_UDP_IP);
                            break;}}
                    break;}
                case PROPERTY_RS232_PARITY:{
                    rsparitytype val_=0;
                    if (str_to<rsparitytype>(val, val_)){
                        val_ = (val_>2) ? 0 : val_;
                        if (_interface->group(id).config())
                                static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity(val_);}
                    break;}
                 default: linkgroupwraper::setProperty(id, prop, val);}}


        std::string koyogroupwraper::getProperty(indx id, propidtype prop){

            switch (prop) {

                case PROPERTY_KOYO_CHANALTYPE_GROUP: {
                    chnltype val_ = ((_interface->group(id).chanaltype()>=0) && ((_interface->group(id).chanaltype()<=3))) ? _interface->group(id).chanaltype() : 0;
                    return to_str<chnltype>(val_);
                    break;}

                case PROPERTY_KOYO_PROTOCOL:{
                    switch (_interface->group(id).chanaltype()){
                        case NT_CHTP_RS232_4XX:{
                            num32 val_ = ((_interface->group(id).protocol()>=0) && ((_interface->group(id).protocol()<=2))) ? _interface->group(id).protocol() : 0;
                            return to_str<num32>(val_);
                            break;}
                        case NT_CHTP_TCP_IP:{
                            return  to_str(NT_KOYO_MODBUS);
                            break;}
                        case NT_CHTP_UDP_IP:{
                            return  to_str(NT_KOYO_DIRECTNET_ECOM);
                            break;}}
                    break;}

                case PROPERTY_RS232_PARITY:{
                    rsparitytype val_ = (_interface->group(id).config()) ?
                        ((static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity()> 2) ?
                            0 : static_cast<prs232_property> (const_cast<void*>(_interface->group(id).config()))->parity()) :
                        0;
                    return to_str<rsparitytype>(val_);
					break;}
                default: return linkgroupwraper::getProperty(id, prop);}
			return linkgroupwraper::getProperty(id, prop);}


        void koyogroupwraper::setchaneltp_and_prtcl(chnltype tp, num32 prtcl){
                 REMOVE_PROPERTYS(koyo_propmainadd)
                 switch (tp){
                     case NT_CHTP_RS232_4XX:{
                       switch(prtcl){
                       case NT_KOYO_MODBUS: {ADD_PROPERTYS(koyo_propmainadd_rtu_add); break;}
                       case NT_KOYO_DIRECTNET_HEX: {ADD_PROPERTYS(koyo_propmainadd_dn_hex_add); break;}
                       case NT_KOYO_DIRECTNET_ASCII: {ADD_PROPERTYS(koyo_propmainadd_dn_ascii_add); break;}}
                       break;}
                     case NT_CHTP_TCP_IP:{
                       ADD_PROPERTYS(koyo_propmainadd_tcp_add);
                       break;}
                     case NT_CHTP_UDP_IP:{
                       ADD_PROPERTYS(koyo_propmainadd_udp_add);
                       break;}}}

        void koyogroupwraper::setids(const entity_map& vl){
            typedef std::set<chnltype , std::less<chnltype>, std::allocator<chnltype> > chnltype_settmp;
            typedef std::set<num32 , std::less<num32>, std::allocator<num32> > prtcl_settmp;
            chnltype_settmp tmp;
            prtcl_settmp tmpprtcl;
            chnltype val_=0;
            num32 prtclval_=0;
            for (entity_map::const_iterator it = vl.begin(); it != vl.end(); ++it){
                val_ = ((_interface->group(it->first).chanaltype()>=0) && ((_interface->group(it->first).chanaltype()<=3))) ? _interface->group(it->first).chanaltype() : 0;
                prtclval_ = ((_interface->group(it->first).protocol()>=0) && ((_interface->group(it->first).protocol()<=3))) ? _interface->group(it->first).protocol() : 0;
                if (val_==NT_CHTP_TCP_IP) prtclval_=0;
                if (val_==NT_CHTP_UDP_IP) prtclval_=NT_KOYO_DIRECTNET_ECOM;
                tmpprtcl.insert(prtclval_);
                tmp.insert(val_);}
            val_=(tmp.size()!=1) ? 0 : (*tmp.begin());
            prtclval_=(tmpprtcl.size()!=1) ? 0 : (*tmpprtcl.begin());
            setchaneltp_and_prtcl(val_, prtclval_);}


    }}