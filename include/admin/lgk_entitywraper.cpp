/* 
 * File:   lgk_entitywraper.cpp
 * Author: Serg
 * 
 * Created on 31 Октябрь 2010 г., 2:31
 */

#include <admin/lgk_entitywraper.h>

namespace dvnci {
    namespace admin {

const propidtype propmainadd[] =         { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RSNUM_GROUP,PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                         PROPERTY_GR_TO,  PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_LGK_PROTOCOL };

const propidtype propmainadd_sp_add[] =  { PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE,PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                          PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,  PROPERTY_GR_SYNCT,
                                          PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_LGK_PROTOCOL };

const propidtype propmainadd_mek_add[] = { PROPERTY_RS232_BOUNDRATE,PROPERTY_GR_TCNT, PROPERTY_GR_INDTO,
                                           PROPERTY_RSNUM_GROUP, PROPERTY_GR_TO,  PROPERTY_GR_SYNCT, PROPERTY_LGK_PROTOCOL };

lgk_linkpropertyeditor::lgk_linkpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "LGKLinkbasetype") {
            addpropertylist(NT_CHTP_NODEF);
            addpropertylist(NT_CHTP_RS232_4XX);}


lgkprotocolpropertyeditor::lgkprotocolpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "LGKProtocolbasetype") {
            addpropertylist(0);
            addpropertylist(1);}

lgkgroupwraper::lgkgroupwraper(lcltype loc) : linkgroupwraper(loc){
            enum_ = "LGKGROUP";
            propidtype propdel[] = {PROPERTY_GR_GR, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALTYPE_GROUP};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_LGK_CHANALTYPE_GROUP};
            ADD_PROPERTYS(propadd);}

        void lgkgroupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_LGK_CHANALTYPE_GROUP, &LgkLPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_BOUNDRATE, &rs232brPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_DATABIT, &rs232dbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_STOPBIT, &rs232sbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_PARITY, &rs232prtPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_FLOWCTRL, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_LGK_PROTOCOL, &LgkProtPred);
            mangr->registpropertyeditor(PROPERTY_GR_SYNCT, &boolPrEdit);}

        void lgkgroupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {
                case PROPERTY_LGK_CHANALTYPE_GROUP: {
                    chnltype val_ = 0;
                    if (str_to<chnltype>(val, val_))
                           _interface->group().chanaltype(in_bounded<num32>(0,1,val_));
                    break;}
               /*case PROPERTY_GR_TO:{
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                           _interface->group().timeout(in_bounded<num32>(300,30000,val_));
                    break;}*/
                case PROPERTY_GR_BS:{
                    num32 val_ = 1;
                    if (str_to<num32>(val, val_))
                           _interface->group().blocksize(in_bounded<num32>(1, 30,val_));
                    break;}
                 case PROPERTY_GR_ABS:{
                    num32 val_ = 1;
                    if (str_to<num32>(val, val_))
                           _interface->group().archblocksize(in_bounded<num32>(1, 30,val_));
                    break;}

                case PROPERTY_LGK_PROTOCOL:{
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if ((val_>=0) && (val_<=1))
                           _interface->group().protocol(val_);
                    break;}

                case PROPERTY_DEVNUM_GROUP: {
                    if (val=="DIRECT") _interface->group().devnum(0xFF);
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_)){
                        if ((val_>=0) && (val_<=30))
                           _interface->group().devnum(val_);}
                    else
                           _interface->group().devnum(0xFF);
                    break;}
                 default: linkgroupwraper::setProperty(id, prop, val);}}


        std::string lgkgroupwraper::getProperty(indx id, propidtype prop){

            switch (prop) {
                case PROPERTY_LGK_CHANALTYPE_GROUP: {
                    chnltype val_ = (_interface->group(id).chanaltype()==NT_CHTP_RS232_4XX) ? NT_CHTP_RS232_4XX : NT_CHTP_NODEF;
                    return to_str<chnltype>(val_);
                    break;}
                /*case PROPERTY_GR_TO:{
                    num32 val_ = ((_interface->group(id).timeout()>=MINIMUM_IOTIMOUT) && ((_interface->group(id).timeout()<=MAXIMUM_IOTIMOUT))) ? _interface->group(id).timeout() : DEFAULT_IOTIMOUT;
                    return to_str<num32>(val_);
                    break;}*/
                case PROPERTY_GR_BS:{
                    num32 val_ = ((_interface->group(id).blocksize()>=1) && ((_interface->group(id).blocksize()<=30))) ? _interface->group(id).blocksize() : 10;
                    return to_str<num32>(val_);
                    break;}
                case PROPERTY_GR_ABS:{
                    num32 val_ = ((_interface->group(id).archblocksize()>=1) && ((_interface->group(id).archblocksize()<=30))) ? _interface->group(id).archblocksize() : 10;
                    return to_str<num32>(val_);
                    break;}
                case PROPERTY_LGK_PROTOCOL:{
                    num32 val_ = ((_interface->group(id).protocol()>=0) && ((_interface->group(id).protocol()<=1))) ? _interface->group(id).protocol() : 0;
                    return to_str<num32>(val_);
                    break;}
                case PROPERTY_DEVNUM_GROUP:{
                    num32 val_ = ((_interface->group(id).devnum()>=0) && ((_interface->group(id).devnum()<=30))) ? _interface->group(id).devnum() : 0xFF;
                    return (val_==0xFF) ? "DIRECT"  : to_str<num32>(val_);
                    break;}
                default: return linkgroupwraper::getProperty(id, prop);}}


        void lgkgroupwraper::setchaneltp_and_prtcl(chnltype tp, num32 prtcl){
                 REMOVE_PROPERTYS(propmainadd)
                    if (tp==NT_CHTP_RS232_4XX){
                       switch(prtcl){
                       case 0: {ADD_PROPERTYS(propmainadd_sp_add); break;}
                       case 1: {ADD_PROPERTYS(propmainadd_mek_add); break;}}}}

        void lgkgroupwraper::setids(const entity_map& vl){
            typedef std::set<chnltype , std::less<chnltype>, std::allocator<chnltype> > chnltype_settmp;
            typedef std::set<num32 , std::less<num32>, std::allocator<num32> > prtcl_settmp;
            chnltype_settmp tmp;
            prtcl_settmp tmpprtcl;
            chnltype val_=0;
            num32 prtclval_=0;
            for (entity_map::const_iterator it = vl.begin(); it != vl.end(); ++it){
                val_ = ((_interface->group(it->first).chanaltype()>=0) && ((_interface->group(it->first).chanaltype()<2))) ? _interface->group(it->first).chanaltype() : 0;
                prtclval_ = ((_interface->group(it->first).protocol()>=0) && ((_interface->group(it->first).protocol()<=1))) ? _interface->group(it->first).protocol() : 0;
                tmpprtcl.insert(prtclval_);
                tmp.insert(val_);}
            val_=(tmp.size()!=1) ? 0 : (*tmp.begin());
            prtclval_=(tmpprtcl.size()!=1) ? 0 : (*tmpprtcl.begin());
            setchaneltp_and_prtcl(val_, prtclval_);}


    }}