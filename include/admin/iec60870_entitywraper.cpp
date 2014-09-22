/* 
 * File:   lgk_entitywraper.cpp
 * Author: Serg
 * 
 * Created on 31 Октябрь 2010 г., 2:31
 */

#include <admin/iec60870_entitywraper.h>
#include <iec60870/iec60870_detail.h>

namespace dvnci {
    namespace admin {


        //const propidtype PROPERTY_IEC60870_PDULEN = 0x055A;
        //const propidtype PROPERTY_IEC60870_TSYNC = 0x055B;
        //const propidtype PROPERTY_IEC60870_SYNC = 0x055C;     
        //const propidtype PROPERTY_IEC60870_TR = 0x055D;        
        //const propidtype PROPERTY_IEC60870_TPOLL = 0x055E;     
        //const propidtype PROPERTY_IEC60870_TREACT = 0x055F;            
        //const propidtype PROPERTY_IEC60870_INIT = 0x0560;        
        //const propidtype PROPERTY_IEC60870_POLL = 0x0561;

        const propidtype iec_propmainadd[] = {PROPERTY_IEC60870_PROT};

        //PROPERTY_DEVNUM_GROUP
        //PROPERTY_GR_TCNT; 
        //PROPERTY_GR_INDTO;
        //PROPERTY_RSNUM_GROUP
        //, PROPERTY_RSNUM_GROUP,
        //PROPERTY_CHANALHOST_ADDR_GROUP
        // PROPERTY_RS232_BOUNDRATE

        const propidtype iec_propmain_101_add[] = {PROPERTY_DEVNUM_GROUP, PROPERTY_RSNUM_GROUP, PROPERTY_RS232_BOUNDRATE,
            PROPERTY_GR_TCNT,
            PROPERTY_IEC60870_LINKADR,
            PROPERTY_IEC60870_COT,
            PROPERTY_IEC60870_SECT,
            PROPERTY_IEC60870_IOA,
            PROPERTY_IEC60870_PDULEN,
            PROPERTY_IEC60870_TSYNC,
            PROPERTY_IEC60870_SYNC,
            PROPERTY_IEC60870_POLL};


        const propidtype iec_propmain_104_add[] = {PROPERTY_CHANALHOST_ADDR_GROUP,
            PROPERTY_IEC60870_T0,
            PROPERTY_IEC60870_T1,
            PROPERTY_IEC60870_T2,
            PROPERTY_IEC60870_T3,
            PROPERTY_IEC60870_K,
            PROPERTY_IEC60870_W,
            PROPERTY_IEC60870_PDULEN,
            PROPERTY_IEC60870_TSYNC,
            PROPERTY_IEC60870_SYNC,
            PROPERTY_IEC60870_POLL};

        iec60870Link::iec60870Link() : abstractpropertyeditor(TYPE_PE_LIST, "iec60870Link") {
            addpropertylist(static_cast<propidtype> (prot80670::lasz_none));
            addpropertylist(static_cast<propidtype> (prot80670::lasz_one));
            addpropertylist(static_cast<propidtype> (prot80670::lasz_double));
        }

        iec60870COT::iec60870COT() : abstractpropertyeditor(TYPE_PE_LIST, "iec60870COT") {
            addpropertylist(static_cast<propidtype> (prot80670::ctsz_one));
            addpropertylist(static_cast<propidtype> (prot80670::ctsz_double));
        }

        iec60870Selector::iec60870Selector() : abstractpropertyeditor(TYPE_PE_LIST, "iec60870Selector") {
            addpropertylist(static_cast<propidtype> (prot80670::select_one));
            addpropertylist(static_cast<propidtype> (prot80670::select_double));
        }

        iec60870IOA::iec60870IOA() : abstractpropertyeditor(TYPE_PE_LIST, "iec60870IOA") {
            addpropertylist(static_cast<propidtype> (prot80670::ioa_one));
            addpropertylist(static_cast<propidtype> (prot80670::ioa_double));
            addpropertylist(static_cast<propidtype> (prot80670::ioa_three));
        }

        iec60870Protocol::iec60870Protocol() : abstractpropertyeditor(TYPE_PE_LIST, "iec60870Protocol") {
            addpropertylist(static_cast<propidtype> (1));
            addpropertylist(static_cast<propidtype> (2));
            addpropertylist(static_cast<propidtype> (3));
            addpropertylist(static_cast<propidtype> (4));
        }

        iec60870groupwraper::iec60870groupwraper(lcltype loc) : linkgroupwraper(loc) {
            enum_ = "IEC60870GROUP";
            propidtype propdel[] = {PROPERTY_GR_GR, PROPERTY_CHANALNUM_GROUP, PROPERTY_GR_SYNCT, PROPERTY_CHANALPORT_GROUP,
                PROPERTY_RS232_DATABIT, PROPERTY_RS232_STOPBIT, PROPERTY_CHANALTYPE_GROUP, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_IEC60870_PROT};
            ADD_PROPERTYS(propadd);
        }

        void iec60870groupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_IEC60870_PROT, &ProtPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_LINKADR, &LinkPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_COT, &COTPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_SECT, &SelectorPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_IOA, &IOAPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_BOUNDRATE, &rs232brPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_SYNC, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_IEC60870_POLL, &boolPrEdit);
        }

        void iec60870groupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {

                case PROPERTY_IEC60870_PROT:
                {
                    prot80670::IEC_PROTOCOL prt = prot80670::protocol_from(str_to<protocoltype>(val));
                    switch (prt) {
                        case prot80670::IEC_104:
                        {
                            _interface->group(id).chanaltype(NT_CHTP_TCP_IP);
                            break;
                        }
                        default:
                        {
                            _interface->group(id).chanaltype(NT_CHTP_RS232_4XX);
                        }
                    }
                    _interface->group(id).protocol(static_cast<protocoltype> (prot80670::protocol_from(str_to<protocoltype>(val))));
                    break;
                }

                case PROPERTY_IEC60870_LINKADR:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        if (val_ < 3) {
                            opt.addr(static_cast<prot80670::ADDRESS_sizetype> (val_ < 3 ? val_ : 0));
                            _interface->group(id).option(opt.to_value());
                        }
                    }
                    break;
                }

                case PROPERTY_IEC60870_COT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        if (val_ < 3) {
                            opt.cot(static_cast<prot80670::COT_sizetype> (((val_) &&(val_ < 3)) ? val_ : 1));
                            _interface->group(id).option(opt.to_value());
                        }
                    }
                    break;
                }

                case PROPERTY_IEC60870_SECT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        if (val_ < 3) {
                            opt.sector(static_cast<prot80670::SECTOR_sizetype> (val_ < 3 ? (val_ ? val_ : 1) : 2));
                            _interface->group(id).option(opt.to_value());
                        }
                    }
                    break;
                }

                case PROPERTY_IEC60870_IOA:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        if (val_ < 4) {
                            opt.ioa(static_cast<prot80670::IOA_sizetype> (val_ < 4 ? (val_ ? val_ : 1) : 3));
                            _interface->group(id).option(opt.to_value());
                        }
                    }
                    break;
                }

                case PROPERTY_GR_TCNT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.trycount(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_T0:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.t0(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }


                case PROPERTY_IEC60870_T1:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.t1(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_T2:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.t2(val_);
                        _interface->group().option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_T3:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.t3(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_K:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.k(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_W:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.w(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_PDULEN:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.pdu_len(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }

                case PROPERTY_IEC60870_TSYNC:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    unum16 val_ = 0;
                    if (str_to<unum16>(val, val_)) {
                        opt.tymesync(val_);
                        _interface->group(id).option(opt.to_value());
                    }
                    break;
                }
                case PROPERTY_IEC60870_SYNC:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    opt.sync(val != "0");
                    _interface->group(id).option(opt.to_value());
                    break;
                }

                case PROPERTY_IEC60870_POLL:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    opt.poll(val != "0");
                    _interface->group(id).option(opt.to_value());
                    break;
                }

                case PROPERTY_RS232_PARITY:
                {
                    rsparitytype val_ = 0;
                    if (str_to<rsparitytype>(val, val_)) {
                        val_ = (val_ > 2) ? 0 : val_;

                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->parity(val_);
                    }
                    break;
                }
                default: linkgroupwraper::setProperty(id, prop, val);
            }
        }

        std::string iec60870groupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {

                case PROPERTY_IEC60870_PROT:
                {
                    protocoltype val_ = static_cast<protocoltype> (prot80670::protocol_from(_interface->group(id).protocol()));
                    prot80670::IEC_PROTOCOL prt = prot80670::protocol_from(_interface->group(id).protocol());
                    switch (prt) {
                        case prot80670::IEC_104:
                        {
                            if (_interface->group(id).chanaltype() == NT_CHTP_TCP_IP) {
                                return to_str<protocoltype>(val_);
                            }
                            break;
                        }
                        default:
                        {
                            if (_interface->group(id).chanaltype() == NT_CHTP_RS232_4XX) {
                                return to_str<protocoltype>(val_);
                            }
                        }
                    }
                    return to_str<protocoltype>(0);
                    break;
                }

                case PROPERTY_IEC60870_LINKADR:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.addr()));
                    break;
                }

                case PROPERTY_IEC60870_COT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.cot()));
                    break;
                }

                case PROPERTY_IEC60870_SECT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.sector()));
                    break;
                }

                case PROPERTY_IEC60870_IOA:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.ioa()));
                    break;
                }

                case PROPERTY_GR_TCNT:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.trycount()));
                    break;
                }

                case PROPERTY_IEC60870_T0:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.t0()));
                    break;
                }

                case PROPERTY_IEC60870_T1:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.t1()));
                    break;
                }

                case PROPERTY_IEC60870_T2:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.t2()));
                    break;
                }

                case PROPERTY_IEC60870_T3:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.t3()));
                    break;
                }

                case PROPERTY_IEC60870_K:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.k()));
                    break;
                }

                case PROPERTY_IEC60870_W:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.w()));
                    break;
                }

                case PROPERTY_IEC60870_PDULEN:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.pdu_len()));
                    break;
                }

                case PROPERTY_IEC60870_TSYNC:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.tymesync()));
                    break;
                }

                case PROPERTY_IEC60870_SYNC:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.sync() ? 1 : 0));
                    break;
                }

                case PROPERTY_IEC60870_POLL:
                {
                    prot80670::iec_option opt(_interface->group(id).option());
                    return to_str<unum16>(static_cast<unum16> (opt.poll() ? 1 : 0));
                    break;
                }

                case PROPERTY_RS232_PARITY:
                {
                    rsparitytype val_ = (_interface->group(id).config()) ?
                            ((static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->parity() > 2) ?
                            0 : static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->parity()) :
                            0;
                    return to_str<rsparitytype>(val_);

                    break;
                }
                default: return linkgroupwraper::getProperty(id, prop);
            }
        }

        void iec60870groupwraper::setchaneltp_and_prtcl(chnltype tp, num32 prtcl) {
            prot80670::IEC_PROTOCOL prt = prot80670::protocol_from(prtcl);
            REMOVE_PROPERTYS(iec_propmain_101_add);
            REMOVE_PROPERTYS(iec_propmain_104_add);
            switch (prt) {
                case prot80670::IEC_101:
                {
                    ADD_PROPERTYS(iec_propmain_101_add);
                    break;
                }
                case prot80670::IEC_104:
                {
                    ADD_PROPERTYS(iec_propmain_104_add);
                    break;
                }
                default:
                {

                }
            }
        }

        void iec60870groupwraper::setids(const entity_map& vl) {
            typedef std::set<chnltype, std::less<chnltype>, std::allocator<chnltype> > chnltype_settmp;
            typedef std::set<num32, std::less<num32>, std::allocator<num32> > prtcl_settmp;
            prtcl_settmp tmpprtcl;
            num32 prtclval_ = 0;
            for (entity_map::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                prtclval_ = static_cast<protocoltype> (prot80670::protocol_from(_interface->group(it->first).protocol()));
                tmpprtcl.insert(prtclval_);
            }
            setchaneltp_and_prtcl(0, prtclval_);
        }


    }
}