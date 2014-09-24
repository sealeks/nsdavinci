/* 
 * File:   AbstractItemWraper.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 19 Ноябрь 2009 г., 3:46
 */

#include <admin/entitywraper.h>
#include <admin/propertymanager.h>




namespace dvnci {
    namespace admin {


        using namespace std;

        // класс для обработчиков свойств в таблице
        // типа chek

        boolpropertyeditor::boolpropertyeditor() : abstractpropertyeditor(TYPE_PE_CHECKED) {
        }

        // класс для обработчиков свойств в таблице
        // типа нередактируемых

        noeditItempropertyeditor::noeditItempropertyeditor() : abstractpropertyeditor(TYPE_PE_NOTEDIT) {
        }

        // класс для обработчиков свойств в таблице
        // типа открывающийся список

        alarmcasepropertyeditor::alarmcasepropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "AlarmCase") {
            addpropertylist(PROPERTY_ALARMCASE_TAG_LESS);
            addpropertylist(PROPERTY_ALARMCASE_TAG_MORE);
            addpropertylist(PROPERTY_ALARMCASE_TAG_EQUAL);
        }

        alarmcaseboolpropertyeditor::alarmcaseboolpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "AlarmCaseBool") {
            addpropertylist(PROPERTY_ALARMCASE_TAG_LESS);
            addpropertylist(PROPERTY_ALARMCASE_TAG_MORE);
            addpropertylist(PROPERTY_ALARMCASE_TAG_EQUAL);
        }

        dbproviderpropertyeditor::dbproviderpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "DBProvider") {
            addpropertylist(PROPERTY_DB_PROVIDER_NONE);
            addpropertylist(PROPERTY_DB_PROVIDER_POSTGRESS);
            addpropertylist(PROPERTY_DB_PROVIDER_ORACLE);
            addpropertylist(PROPERTY_DB_PROVIDER_MYSQL);
        }

        alarmlevelpropertyeditor::alarmlevelpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "AlarmLevel") {
            addpropertylist(altNone);
            addpropertylist(altNotice);
            addpropertylist(altWarning);
            addpropertylist(altAccident);
        }

        rwpropertyeditor::rwpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RWtype") {
            addpropertylist(rwReadWrite);
            addpropertylist(rwReadOnly);
            addpropertylist(rwWriteOnly);
        }

        typetagpropertyeditor::typetagpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "TypeTag") {
            addpropertylist(TYPE_NODEF);
            addpropertylist(TYPE_DOUBLE);
            addpropertylist(TYPE_FLOAT);
            addpropertylist(TYPE_NUM64);
            addpropertylist(TYPE_UNUM64);
            addpropertylist(TYPE_NUM32);
            addpropertylist(TYPE_UNUM32);
            addpropertylist(TYPE_NUM16);
            addpropertylist(TYPE_UNUM16);
            addpropertylist(TYPE_NUM8);
            addpropertylist(TYPE_UNUM8);
            addpropertylist(TYPE_DISCRET);
            addpropertylist(TYPE_TEXT);
            addpropertylist(TYPE_TM);
            addpropertylist(EVENT_TYPE_WITHTIME);


            addpropertylist(REPORTTYPE_YEAR);
            addpropertylist(REPORTTYPE_MIN);
            addpropertylist(REPORTTYPE_HOUR);
            addpropertylist(REPORTTYPE_DEC);
            addpropertylist(REPORTTYPE_DAY);
            addpropertylist(REPORTTYPE_MONTH);
            addpropertylist(REPORTTYPE_10MIN);
            addpropertylist(REPORTTYPE_30MIN);
            addpropertylist(REPORTTYPE_QVART);
            addpropertylist(REPORTTYPE_CUSTOM);
        }

        reporttypetagpropertyeditor::reporttypetagpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "TypeTag") {
            addpropertylist(TYPE_NODEF);
            addpropertylist(REPORTTYPE_YEAR);
            addpropertylist(REPORTTYPE_MIN);
            addpropertylist(REPORTTYPE_HOUR);
            addpropertylist(REPORTTYPE_DEC);
            addpropertylist(REPORTTYPE_DAY);
            addpropertylist(REPORTTYPE_MONTH);
            addpropertylist(REPORTTYPE_10MIN);
            addpropertylist(REPORTTYPE_30MIN);
            addpropertylist(REPORTTYPE_QVART);
        }

        reportstatistictagpropertyeditor::reportstatistictagpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RepTagStatisic") {
            addpropertylist(REPORT_STATISTIC_NONE);
            addpropertylist(REPORT_STATISTIC_AVER);
            addpropertylist(REPORT_STATISTIC_INTEG);
            addpropertylist(REPORT_STATISTIC_SUM);
            addpropertylist(REPORT_STATISTIC_MIN);
            addpropertylist(REPORT_STATISTIC_MAX);
            addpropertylist(REPORT_STATISTIC_MOD);
        }

        debuglevpropertyeditor::debuglevpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "debuglevproperty") {
            addpropertylist(DEBUGLEVEL_HIGH);
            addpropertylist(DEBUGLEVEL_MIDLE);
            addpropertylist(DEBUGLEVEL_LOW);
            addpropertylist(DEBUGLEVEL_NONE);
        }

        typegrouppropertyeditor::typegrouppropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "TypeGroup") {
            addpropertylist(NS_GROUP_DEFAULT);
            addpropertylist(NS_GROUP_SYSTEM);
            addpropertylist(NS_GROUP_SYSTEMVAR);
            addpropertylist(NS_GROUP_SYSTEMCOUNT);
            addpropertylist(NS_GROUP_SYSTEMREPORT);
            addpropertylist(NS_GROUP_SYSTEMREPORTCOUNT);
            addpropertylist(NS_GROUP_NET);
            addpropertylist(NS_GROUP_OPC);
            addpropertylist(NS_GROUP_DDE);
            addpropertylist(NS_GROUP_MODBUS);
            addpropertylist(NS_GROUP_KOYO);
            addpropertylist(NS_GROUP_LGKA);
            addpropertylist(NS_GROUP_MMS);
            addpropertylist(NS_GROUP_IEC60870);
        }

        typeservicestartpropertyeditor::typeservicestartpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "Sevicestarttype") {
            addpropertylist(SERVICE_RUNSTATE_NODEF);
            addpropertylist(SERVICE_RUNSTATE_OFF);
            addpropertylist(SERVICE_RUNSTATE_DEMAND);
            addpropertylist(SERVICE_RUNSTATE_AUTO);
            addpropertylist(SERVICE_RUNSTATE_SYSTEM);
            addpropertylist(SERVICE_RUNSTATE_BOOT);
        }

        rs232boundratepropertyeditor::rs232boundratepropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RSBoundratetype") {
            addpropertylist(NT_RS_DOUNDRATE_110);
            addpropertylist(NT_RS_DOUNDRATE_300);
            addpropertylist(NT_RS_DOUNDRATE_600);
            addpropertylist(NT_RS_DOUNDRATE_1200);
            addpropertylist(NT_RS_DOUNDRATE_2400);
            addpropertylist(NT_RS_DOUNDRATE_4800);
            addpropertylist(NT_RS_DOUNDRATE_9600);
            addpropertylist(NT_RS_DOUNDRATE_14400);
            addpropertylist(NT_RS_DOUNDRATE_19200);
            addpropertylist(NT_RS_DOUNDRATE_38400);
            addpropertylist(NT_RS_DOUNDRATE_56000);
            addpropertylist(NT_RS_DOUNDRATE_57600);
            addpropertylist(NT_RS_DOUNDRATE_115200);
            addpropertylist(NT_RS_DOUNDRATE_128000);
            addpropertylist(NT_RS_DOUNDRATE_256000);
        }

        rs232databitpropertyeditor::rs232databitpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RSDatabittype") {
            addpropertylist(5);
            addpropertylist(6);
            addpropertylist(7);
            addpropertylist(8);
        }

        rs232stopbitpropertyeditor::rs232stopbitpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RSStopbittype") {
            addpropertylist(NT_RS_ONESTOPBIT);
            addpropertylist(NT_RS_ONE5STOPBITS);
            addpropertylist(NT_RS_TWOSTOPBITS);
        }

        rs232paritypropertyeditor::rs232paritypropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "RSParitytype") {
            addpropertylist(NT_RS_NOPARITY);
            addpropertylist(NT_RS_ODDPARITY);
            addpropertylist(NT_RS_EVENPARITY);
            addpropertylist(NT_RS_MARKPARITY);
            addpropertylist(NT_RS_SPACEPARITY);
        }

        opcverpertyeditor::opcverpertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "Opcvertype") {
            addpropertylist(0);
            addpropertylist(1);
            addpropertylist(2);
            addpropertylist(3);
        }

        opccontypepertyeditor::opccontypepertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "Opccontypetype") {
            addpropertylist(CONTYPE_SUBSCR);
            addpropertylist(CONTYPE_ASYNC);
            addpropertylist(CONTYPE_SYNC);
        }

        baselinkpropertyeditor::baselinkpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "BaseLinkbasetype") {
            addpropertylist(NT_CHTP_NODEF);
            addpropertylist(NT_CHTP_RS232_4XX);
            addpropertylist(NT_CHTP_TCP_IP);
            addpropertylist(NT_CHTP_UDP_IP);
        }

        grouplocalpropertyeditor::grouplocalpropertyeditor() : abstractpropertyeditor(TYPE_PE_LIST, "GrLocaltype") {
            addpropertylist(0);
            addpropertylist(NS_CODPAGE_LOC8);
            addpropertylist(NS_CODPAGE_UTF16);
            addpropertylist(NS_CODPAGE_UTF32);
        }

        // базовый класс для обработки листьев дерева
        // остальные наследуют от него


        // Базовый класс обертка для тегов базы

        basetagwraper::basetagwraper(lcltype loc) : abstractwraper(loc) {
            propidtype propadd[] = {PROPERTY_NAME_TAG, PROPERTY_COMMENT_TAG, PROPERTY_BIND_TAG, PROPERTY_MINCONT_TAG, PROPERTY_MAXCONT_TAG, /*PROPERTY_DETHBOUNDCONT_TAG*/
                PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_UETEXT_TAG, PROPERTY_OFFMSG_TAG, PROPERTY_OFFMSGTEXT_TAG, PROPERTY_ONMSG_TAG,
                PROPERTY_ONMSGTEXT_TAG, PROPERTY_ALARMLEVEL_TAG, PROPERTY_SERVERDB_TAG, PROPERTY_ALARMMSGTEXT_TAG, PROPERTY_ALARMVAL_TAG, PROPERTY_ALARMCASE_TAG,
                PROPERTY_ARCH_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_RW_TAG, PROPERTY_TAG_TYPE, PROPERTY_AL_TAG, PROPERTY_ALWACTIVE_TAG, PROPERTY_RANGABLE_TAG};
            ADD_PROPERTYS(propadd);
        }

        void basetagwraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_NAME_TAG);
        }

        void basetagwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_OFFMSG_TAG, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_ONMSG_TAG, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_ALWACTIVE_TAG, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_RANGABLE_TAG, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_ARCH_TAG, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_ALARMCASE_TAG, &acasePrEdit);
            mangr->registpropertyeditor(PROPERTY_ALARMLEVEL_TAG, &alevelPrEdit);
            mangr->registpropertyeditor(PROPERTY_TAG_TYPE, &typePrEdit);
            mangr->registpropertyeditor(PROPERTY_RW_TAG, &rwPrEdit);
        }

        void basetagwraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_NAME_TAG:
                {
                    _interface->tag(id).name(retremoved_namespace_delimit(val));
                    break;
                };
                case PROPERTY_COMMENT_TAG:
                {
                    _interface->tag(id).comment(val);
                    break;
                };
                case PROPERTY_BIND_TAG:
                {
                    _interface->tag(id).binding(val);
                    break;
                };
                case PROPERTY_MINCONT_TAG:
                {
                    _interface->tag(id).minraw(val);
                    break;
                };
                case PROPERTY_MAXCONT_TAG:
                {
                    _interface->tag(id).maxraw(val);
                    break;
                };
                case PROPERTY_UEMIN_TAG:
                {
                    _interface->tag(id).mineu(val);
                    break;
                };
                case PROPERTY_UEMAX_TAG:
                {
                    _interface->tag(id).maxeu(val);
                    break;
                };
                case PROPERTY_UETEXT_TAG:
                {
                    _interface->tag(id).eu(val);
                    break;
                };
                case PROPERTY_OFFMSG_TAG:
                {
                    int val_ = 0;
                    //bool old_offmsged = _interface->tag(id).offmsged();
                    if (str_to(val, val_)) _interface->tag(id).offmsged(val_);
                    /*if (old_offmsged!=_interface->tag(id).offmsged()){
                        if (old_offmsged) {
                            propidtype propdel[] = {PROPERTY_OFFMSGTEXT_TAG};
                            REMOVE_PROPERTYS(propdel);}
                        else{
                            propidtype propadd[] = {PROPERTY_OFFMSGTEXT_TAG};
                            ADD_PROPERTYS(propdel);}}*/
                    break;
                };
                case PROPERTY_OFFMSGTEXT_TAG:
                {
                    _interface->tag(id).offmsg(val);
                    break;
                };
                case PROPERTY_ONMSG_TAG:
                {
                    int val_ = 0;
                    //bool old_onmsged = _interface->tag(id).onmsged();
                    if (str_to(val, val_))_interface->tag(id).onmsged(val_);
                    /*if (old_onmsged!=_interface->tag(id).onmsged()){
                    if (old_onmsged) {
                            propidtype propdel[] = {PROPERTY_OFFMSGTEXT_TAG};
                            REMOVE_PROPERTYS(propdel);}
                        else{
                            propidtype propadd[] = {PROPERTY_OFFMSGTEXT_TAG};
                            ADD_PROPERTYS(propdel);}}*/
                    break;
                };
                case PROPERTY_ONMSGTEXT_TAG:
                {
                    _interface->tag(id).onmsg(val);
                    break;
                };
                case PROPERTY_SERVERDB_TAG:
                {
                    _interface->tag(id).devdb(val);
                    break;
                };
                case PROPERTY_ALARMLEVEL_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).alarmlevel(val_);
                    break;
                };
                case PROPERTY_ALARMMSGTEXT_TAG:
                {
                    _interface->tag(id).alarmmsg(val);
                    break;
                };
                case PROPERTY_ALARMVAL_TAG:
                {
                    _interface->tag(id).alarmconst(val);
                    break;
                };
                case PROPERTY_ALARMCASE_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).alarmcase(val_);
                    break;
                };
                case PROPERTY_ARCH_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).logged(val_);
                    break;
                };
                case PROPERTY_ARCHDB_TAG:
                {
                    _interface->tag(id).logdb(val);
                    break;
                };
                case PROPERTY_RW_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).rwtype(val_);
                    break;
                };
                case PROPERTY_AL_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).accesslevel(val_);
                    break;
                };
                case PROPERTY_ALWACTIVE_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).alwactive(val_);
                    break;
                };
                case PROPERTY_RANGABLE_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).rangable(val_);
                    break;
                };
                case PROPERTY_TAG_TYPE:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).type(val_);
                    break;
                };
            }
        }

        std::string basetagwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NAME_TAG: return retremoved_namespace_delimit(_interface->tag(id).name());
                case PROPERTY_COMMENT_TAG: return _interface->tag(id).comment();
                case PROPERTY_BIND_TAG: return _interface->tag(id).binding();
                case PROPERTY_MINCONT_TAG: return to_str(_interface->tag(id).minraw());
                case PROPERTY_MAXCONT_TAG: return to_str(_interface->tag(id).maxraw());
                case PROPERTY_UEMIN_TAG: return to_str(_interface->tag(id).mineu());
                case PROPERTY_UEMAX_TAG: return to_str(_interface->tag(id).maxeu());
                case PROPERTY_UETEXT_TAG: return _interface->tag(id).eu();
                case PROPERTY_OFFMSG_TAG: return to_str((int) _interface->tag(id).offmsged());
                case PROPERTY_OFFMSGTEXT_TAG: return _interface->tag(id).offmsg();
                case PROPERTY_ONMSG_TAG: return to_str((int) _interface->tag(id).onmsged());
                case PROPERTY_ONMSGTEXT_TAG: return _interface->tag(id).onmsg();
                case PROPERTY_SERVERDB_TAG: return to_str(_interface->tag(id).devdb());
                case PROPERTY_ALARMLEVEL_TAG: return to_str((int) _interface->tag(id).alarmlevel());
                case PROPERTY_ALARMMSGTEXT_TAG: return _interface->tag(id).alarmmsg();
                case PROPERTY_ALARMVAL_TAG: return to_str(_interface->tag(id).alarmconst());
                case PROPERTY_ALARMCASE_TAG: return to_str(_interface->tag(id).alarmcase());
                case PROPERTY_ARCH_TAG: return to_str(_interface->tag(id).logged());
                case PROPERTY_ARCHDB_TAG: return to_str(_interface->tag(id).logdb());
                case PROPERTY_RW_TAG: return to_str(_interface->tag(id).rwtype());
                case PROPERTY_AL_TAG: return to_str(_interface->tag(id).accesslevel());
                case PROPERTY_ALWACTIVE_TAG: return to_str(_interface->tag(id).alwactive());
                case PROPERTY_RANGABLE_TAG: return to_str(_interface->tag(id).rangable());
                case PROPERTY_TAG_TYPE: return to_str(_interface->tag(id).type());
            }
            return "";
        }

        void basetagwraper::commit(indx id) {
            _interface->merge_entities(NT_TAG, id);
        }

        //basereporttagwraper

        basereportcnttagwraper::basereportcnttagwraper(lcltype loc) : basetagwraper(loc) {
            propidtype propdel[] = {PROPERTY_MINCONT_TAG, PROPERTY_MAXCONT_TAG, PROPERTY_OFFMSG_TAG, PROPERTY_OFFMSGTEXT_TAG, PROPERTY_ONMSG_TAG,
                PROPERTY_ONMSGTEXT_TAG, PROPERTY_ALARMLEVEL_TAG, PROPERTY_ALARMMSGTEXT_TAG, PROPERTY_ALARMVAL_TAG, PROPERTY_ALARMCASE_TAG,
                PROPERTY_ARCH_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_SERVERDB_TAG, PROPERTY_RW_TAG, PROPERTY_AL_TAG, PROPERTY_RANGABLE_TAG,
                PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_ALWACTIVE_TAG};
            REMOVE_PROPERTYS(propdel);

            propidtype propadd[] = {PROPERTY_PREDCOUNT_TAG, PROPERTY_DELTCOUNT_TAG, PROPERTY_REPSTATISIC_TAG};
            ADD_PROPERTYS(propadd);
        }

        void basereportcnttagwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_REPSTATISIC_TAG, &statPrEdit);
        }

        void basereportcnttagwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_PREDCOUNT_TAG:
                {
                    reporthisttype val_;
                    if (str_to<reporthisttype > (val, val_)) {
                        _interface->tag(id).reporthistory(val_);
                    };
                    break;
                };
                case PROPERTY_DELTCOUNT_TAG:
                {
                    reporthistdelt val_;
                    if (str_to<reporthistdelt > (val, val_)) {
                        _interface->tag(id).reportsubdelt(val_);
                    };
                    break;
                };
                case PROPERTY_REPSTATISIC_TAG:
                {
                    repstattype val_;
                    if (str_to<repstattype > (val, val_)) {
                        _interface->tag(id).reportstatistic(val_);
                    };
                    break;
                };
                default: basetagwraper::setProperty(id, prop, val);
            }
        }

        std::string basereportcnttagwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_PREDCOUNT_TAG: return to_str(_interface->tag(id).reporthistory());
                case PROPERTY_DELTCOUNT_TAG: return to_str(_interface->tag(id).reportsubdelt());
                case PROPERTY_REPSTATISIC_TAG: return to_str(_interface->tag(id).reportstatistic());
                default: return basetagwraper::getProperty(id, prop);
            }
        }

        //basereporttagwraper

        basereporttagwraper::basereporttagwraper(lcltype loc) : basereportcnttagwraper(loc) {
            propidtype propdel[] = {PROPERTY_REPSTATISIC_TAG};
            REMOVE_PROPERTYS(propdel);
        }


        //basenumerictagwraper

        basenumerictagwraper::basenumerictagwraper(lcltype loc) : basetagwraper(loc) {
            /*propidtype propdel[] = { };
            REMOVE_PROPERTYS(propdel);*/
        }

        //basebooltagwraper

        basebooltagwraper::basebooltagwraper(lcltype loc) : basetagwraper(loc) {
            propidtype propdel[] = {PROPERTY_RANGABLE_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_MINCONT_TAG, PROPERTY_SERVERDB_TAG,
                PROPERTY_MAXCONT_TAG, PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_UETEXT_TAG, PROPERTY_ALARMVAL_TAG,
                PROPERTY_ALARMCASE_TAG};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_ALARMVALBOOL_TAG};
            ADD_PROPERTYS(propadd);
        }

        void basebooltagwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_ALARMVALBOOL_TAG, &boolPrEdit);
        }

        void basebooltagwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_ALARMVALBOOL_TAG:
                {
                    int val_ = 0;
                    if (str_to(val, val_))_interface->tag(id).alarmconst(val_ ? "1" : "0");
                    break;
                };
                default: basetagwraper::setProperty(id, prop, val);
            }
        }

        std::string basebooltagwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_ALARMVALBOOL_TAG: return to_str(_interface->tag(id).alarmconst());
                default: return basetagwraper::getProperty(id, prop);
            }
        }


        //baseeventtagwraper

        eventtagwraper::eventtagwraper(lcltype loc) : basetagwraper(loc) {
            propidtype propdel[] = {PROPERTY_MINCONT_TAG, PROPERTY_MAXCONT_TAG, /*PROPERTY_DETHBOUNDCONT_TAG*/
                PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_UETEXT_TAG, PROPERTY_OFFMSG_TAG, PROPERTY_OFFMSGTEXT_TAG, PROPERTY_ONMSG_TAG,
                PROPERTY_ONMSGTEXT_TAG, PROPERTY_SERVERDB_TAG, PROPERTY_ALARMMSGTEXT_TAG, PROPERTY_ALARMVAL_TAG, PROPERTY_ALARMCASE_TAG,
                PROPERTY_ARCH_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_RW_TAG, PROPERTY_COMMENT_TAG, PROPERTY_AL_TAG,
                PROPERTY_ALWACTIVE_TAG, PROPERTY_RANGABLE_TAG};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_EVENTTEXT_TAG};
            ADD_PROPERTYS(propadd);
        }

        std::string eventtagwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_EVENTTEXT_TAG: return _interface->tag(id).comment();
                default: return basetagwraper::getProperty(id, prop);
            }
            return "";
        }

        void eventtagwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_EVENTTEXT_TAG:
                {
                    _interface->tag(id).comment(val);
                    break;
                };
                default: basetagwraper::setProperty(id, prop, val);
            }
        }


        //texttagwraper

        texttagwraper::texttagwraper(lcltype loc) : basetagwraper(loc) {
            propidtype propdel[] = {PROPERTY_MINCONT_TAG, PROPERTY_MAXCONT_TAG,
                PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_UETEXT_TAG, PROPERTY_OFFMSG_TAG, PROPERTY_OFFMSGTEXT_TAG, PROPERTY_ONMSG_TAG,
                PROPERTY_ONMSGTEXT_TAG, PROPERTY_SERVERDB_TAG, PROPERTY_ALARMMSGTEXT_TAG, PROPERTY_ALARMVAL_TAG, PROPERTY_ALARMCASE_TAG,
                PROPERTY_ARCH_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_RW_TAG, PROPERTY_AL_TAG,
                PROPERTY_RANGABLE_TAG, PROPERTY_ALARMLEVEL_TAG};
            REMOVE_PROPERTYS(propdel);
        }


        //tinetagwraper

        timetagwraper::timetagwraper(lcltype loc) : basetagwraper(loc) {
            propidtype propdel[] = {PROPERTY_MINCONT_TAG, PROPERTY_MAXCONT_TAG,
                PROPERTY_UEMIN_TAG, PROPERTY_UEMAX_TAG, PROPERTY_UETEXT_TAG, PROPERTY_OFFMSG_TAG, PROPERTY_OFFMSGTEXT_TAG, PROPERTY_ONMSG_TAG,
                PROPERTY_ONMSGTEXT_TAG, PROPERTY_SERVERDB_TAG, PROPERTY_ALARMMSGTEXT_TAG, PROPERTY_ALARMVAL_TAG, PROPERTY_ALARMCASE_TAG,
                PROPERTY_ARCH_TAG, PROPERTY_ARCHDB_TAG, PROPERTY_RW_TAG, PROPERTY_AL_TAG,
                PROPERTY_RANGABLE_TAG, PROPERTY_ALARMLEVEL_TAG};
            REMOVE_PROPERTYS(propdel);
        }






        //basegroupwraper

        basegroupwraper::basegroupwraper(lcltype loc) : abstractwraper(loc) {
            enum_ = "BASEGROUP";
            propidtype propadd[] = {PROPERTY_NAME_GROUP, PROPERTY_ENUM_GROUP, PROPERTY_TYPE_GROUP, PROPERTY_CHANALTYPE_GROUP,
                PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            ADD_PROPERTYS(propadd);
        }

        void basegroupwraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_NAME_GROUP);
        }

        void basegroupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_TYPE_GROUP, &typePrEdit);
            mangr->registpropertyeditor(PROPERTY_GR_LOCALE, &grlcPrEdit);
        }

        void basegroupwraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_NAME_GROUP:
                {
                    _interface->group(id).name(val);
                    break;
                };
                case PROPERTY_CHANALPORT_GROUP:
                {
                    _interface->group(id).option(val);
                    break;
                };
                case PROPERTY_ENUM_GROUP:
                {
                    break;
                }
                case PROPERTY_TYPE_GROUP:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).appid(val_);
                    break;
                };
                case PROPERTY_CHANALTYPE_GROUP:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).chanaltype(val_);
                    break;
                };
                case PROPERTY_CHANALNUM_GROUP:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).chanalnum(val_);
                    break;
                };
                case PROPERTY_DEVNUM_GROUP:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).devnum(val_);
                    break;
                };
                case PROPERTY_GR_TO:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).timeout(val_);
                    break;
                };
                case PROPERTY_GR_DB:
                {
                    double val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).deadbound(val_);
                    break;
                };
                case PROPERTY_GR_GR:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).grouprate(val_);
                    break;
                };
                case PROPERTY_GR_SYNCT:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).utiloperation(val_ != 0);
                    break;
                };
                case PROPERTY_GR_BS:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).blocksize(val_);
                    break;
                };
                case PROPERTY_GR_ABS:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).archblocksize(val_);
                    break;
                };
                case PROPERTY_GR_TCNT:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).trycount(val_);
                    break;
                };
                case PROPERTY_GR_INDTO:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).indicateto(val_);
                    break;
                };
            }
        }

        string basegroupwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NAME_GROUP: return _interface->group(id).name();
                case PROPERTY_ENUM_GROUP: return enum_;
                case PROPERTY_TYPE_GROUP: return to_str(_interface->group(id).appid());
                case PROPERTY_CHANALTYPE_GROUP: return to_str(_interface->group(id).chanaltype());
                case PROPERTY_CHANALNUM_GROUP: return to_str(_interface->group(id).chanalnum());
                case PROPERTY_CHANALPORT_GROUP: return to_str(_interface->group(id).option());
                case PROPERTY_DEVNUM_GROUP: return to_str(_interface->group(id).devnum());
                case PROPERTY_GR_TO: return to_str(_interface->group(id).timeout());
                case PROPERTY_GR_DB: return to_str(_interface->group(id).deadbound());
                case PROPERTY_GR_GR: return to_str(_interface->group(id).grouprate());
                case PROPERTY_GR_SYNCT: return to_str(_interface->group(id).utiloperation() ? "1": "0");
                case PROPERTY_GR_BS: return to_str(_interface->group(id).blocksize());
                case PROPERTY_GR_ABS: return to_str(_interface->group(id).archblocksize());
                case PROPERTY_GR_TCNT: return to_str(_interface->group(id).trycount());
                case PROPERTY_GR_INDTO: return to_str(_interface->group(id).indicateto());
            }
            return "";
        }

        void basegroupwraper::commit(indx id) {
            _interface->merge_entities(NT_GROUP, id);
        }

        //systemgroupwraper

        defaultgroupwraper::defaultgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "DEFAULTGROUP";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        //systemgroupwraper

        systemgroupwraper::systemgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEM";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        // sysvargroupwraper

        sysvargroupwraper::sysvargroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEMVAR";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        // systemcountgroupwraper

        systemcountgroupwraper::systemcountgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEMCOUNT";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        // systemcountgroupwraper

        systemcommandcasegroupwraper::systemcommandcasegroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEMCOMMANDCASE";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        systemreportgroupwraper::systemreportgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEMREPORT";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        systemreportcountgroupwraper::systemreportcountgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "SYSTEMREPORTCOUNT";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
        }

        netgroupwraper::netgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "NETGROUP";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_CHANALHOST_GROUP, PROPERTY_CHANALUSER_GROUP, PROPERTY_CHANALPASSWORD_GROUP};
            ADD_PROPERTYS(propadd);
        }

        void netgroupwraper::setProperty(indx id, propidtype prop, string val) {

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
                default: basegroupwraper::setProperty(id, prop, val);
            }
        }

        std::string netgroupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_CHANALHOST_GROUP: return _interface->group(id).host();
                case PROPERTY_CHANALUSER_GROUP: return _interface->group(id).user();
                case PROPERTY_CHANALPASSWORD_GROUP: return _interface->group(id).password();
                default: return basegroupwraper::getProperty(id, prop);
            }
        }

        opcgroupwraper::opcgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "OPCGROUP";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_DEVNUM_GROUP,
                PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_CHANALPORT_GROUP, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_CHANALHOST_GROUP, /*PROPERTY_CHANALUSER_GROUP, PROPERTY_CHANALPASSWORD_GROUP,*/
                PROPERTY_OPCNAME_GROUP, PROPERTY_OPCGROUP_GROUP, PROPERTY_OPCVER_GROUP, PROPERTY_OPCCONTYPE_GROUP, PROPERTY_OPCUSEHDA_GROUP, PROPERTY_GR_LOCALE, PROPERTY_SERVER_NAME};
            ADD_PROPERTYS(propadd);
        }

        void opcgroupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_OPCUSEHDA_GROUP, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_OPCVER_GROUP, &opcverPrEdit);
            mangr->registpropertyeditor(PROPERTY_OPCCONTYPE_GROUP, &opcconPrEdit);
        }

        void opcgroupwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_SERVER_NAME:
                {
                    _interface->group(id).server(val);
                    break;
                };
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
                case PROPERTY_OPCNAME_GROUP:
                {
                    _interface->group(id).server(val);
                    break;
                };
                case PROPERTY_OPCGROUP_GROUP:
                {
                    _interface->group(id).group(val);
                    break;
                };
                case PROPERTY_OPCVER_GROUP:
                {
                    num16 val_ = 0;
                    if (str_to<num16>(val, val_))
                        _interface->group(id).ver(val_);
                    break;
                };
                case PROPERTY_OPCCONTYPE_GROUP:
                {
                    num16 val_ = 0;
                    if (str_to<num16>(val, val_))
                        _interface->group(id).synctype(val_);
                    break;
                };
                case PROPERTY_OPCUSEHDA_GROUP:
                {
                    _interface->group(id).supporttype(val != "0");
                    break;
                };
                case PROPERTY_GR_LOCALE:
                {
                    lcltype val_ = 0;
                    if (str_to<lcltype>(val, val_))
                        _interface->group(id).local(val_);
                    break;
                };
                default: basegroupwraper::setProperty(id, prop, val);
            }
        }

        std::string opcgroupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_SERVER_NAME: return _interface->group(id).server();
                case PROPERTY_CHANALHOST_GROUP: return _interface->group(id).host();
                case PROPERTY_CHANALUSER_GROUP: return _interface->group(id).user();
                case PROPERTY_CHANALPASSWORD_GROUP: return _interface->group(id).password();
                case PROPERTY_OPCNAME_GROUP: return _interface->group(id).server();
                case PROPERTY_OPCGROUP_GROUP: return _interface->group(id).group();
                case PROPERTY_OPCVER_GROUP: return to_str<num16>(_interface->group(id).ver());
                case PROPERTY_OPCCONTYPE_GROUP: return to_str<num16>(_interface->group(id).synctype());
                case PROPERTY_GR_LOCALE: return to_str<lcltype>(_interface->group(id).local());
                case PROPERTY_OPCUSEHDA_GROUP: return _interface->group(id).supporttype() ? "1": "0";
                default: return basegroupwraper::getProperty(id, prop);
            }
        }

        ddegroupwraper::ddegroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "DDEGROUP";
            propidtype propdel[] = {PROPERTY_CHANALTYPE_GROUP, PROPERTY_CHANALNUM_GROUP, PROPERTY_CHANALPORT_GROUP, PROPERTY_DEVNUM_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS, PROPERTY_GR_TCNT, PROPERTY_GR_INDTO};
            REMOVE_PROPERTYS(propdel);
            propidtype propadd[] = {PROPERTY_CHANALHOST_GROUP, PROPERTY_SERVER_NAME, PROPERTY_DDESERVER_TOPIC, PROPERTY_GR_LOCALE};
            ADD_PROPERTYS(propadd);
        }

        void ddegroupwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_CHANALHOST_GROUP:
                {
                    _interface->group(id).host(val);
                    break;
                };
                case PROPERTY_SERVER_NAME:
                {
                    _interface->group(id).server(val);
                    break;
                };
                case PROPERTY_DDESERVER_TOPIC:
                {
                    _interface->group(id).topic(val);
                    break;
                };
                case PROPERTY_GR_LOCALE:
                {
                    lcltype val_ = 0;
                    if (str_to(val, val_)) _interface->group(id).local(val_);
                    break;
                };
                default: basegroupwraper::setProperty(id, prop, val);
            }
        }

        std::string ddegroupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_CHANALHOST_GROUP: return _interface->group(id).host();
                case PROPERTY_SERVER_NAME: return _interface->group(id).server();
                case PROPERTY_DDESERVER_TOPIC: return _interface->group(id).topic();
                case PROPERTY_GR_LOCALE: return to_str<lcltype>(_interface->group(id).local());
                default: return basegroupwraper::getProperty(id, prop);
            }
        }

        linkgroupwraper::linkgroupwraper(lcltype loc) : basegroupwraper(loc) {
            enum_ = "LINKGROUP";
            propidtype propdel[] = {PROPERTY_CHANALPORT_GROUP, PROPERTY_GR_TO, PROPERTY_GR_DB,
                PROPERTY_GR_GR, PROPERTY_GR_SYNCT, PROPERTY_GR_BS, PROPERTY_GR_ABS};
            REMOVE_PROPERTYS(propdel);
        }

        void linkgroupwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_RS232_BOUNDRATE, &rs232brPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_DATABIT, &rs232dbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_STOPBIT, &rs232sbPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_PARITY, &rs232prtPrEdit);
            mangr->registpropertyeditor(PROPERTY_RS232_FLOWCTRL, &boolPrEdit);
        }

        void linkgroupwraper::setProperty(indx id, propidtype prop, std::string val) {

            switch (prop) {
                case PROPERTY_CHANALTYPE_GROUP:
                {
                    chnltype val_ = 0;
                    if (str_to<chnltype>(val, val_))
                        if ((val_ >= 0) && (val_ < 4))
                            _interface->group(id).chanaltype(val_);
                    break;
                }
                case PROPERTY_RSNUM_GROUP:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if ((val_ > 0) && (val_ <= 0xFFFF))
                            _interface->group(id).chanalnum(val_);
                    break;
                }
                case PROPERTY_DEVNUM_GROUP:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if ((val_ > 0) && (val_ <= 0xF9))
                            _interface->group(id).devnum(val_);
                    break;
                }

                case PROPERTY_RS232_BOUNDRATE:
                {
                    baudratetype val_ = NT_RS_DOUNDRATE_9600;
                    if (str_to<baudratetype>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->baudrate(val_);
                    break;
                }

                case PROPERTY_RS232_DATABIT:
                {
                    num32 val_ = 8;
                    if (str_to<baudratetype>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->databit(val_);
                    break;
                }

                case PROPERTY_RS232_STOPBIT:
                {
                    rsstopbittype val_ = 0;
                    if (str_to<rsstopbittype>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->stopbit(val_);
                    break;
                }

                case PROPERTY_RS232_PARITY:
                {
                    rsparitytype val_ = 0;
                    if (str_to<rsparitytype>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->parity(val_);
                    break;
                }

                case PROPERTY_RS232_FLOWCTRL:
                {
                    int val_ = 0;
                    if (str_to<int>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrol(val_ > 0);
                    break;
                }

                case PROPERTY_RS232_FLOWCTRLAF:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrolaftersleep(val_);
                    break;
                }

                case PROPERTY_RS232_FLOWCTRLBE:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrolbeforesleep(val_);
                    break;
                }

                case PROPERTY_RS232_RI:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->readinterval(val_);
                    break;
                }

                case PROPERTY_RS232_RTM:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->rtm(val_);
                    break;
                }

                case PROPERTY_RS232_RTC:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->rtc(val_);
                    break;
                }

                case PROPERTY_RS232_WTM:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->wtm(val_);
                    break;
                }

                case PROPERTY_RS232_WTC:
                {
                    num32 val_ = 0;
                    if (str_to<num32>(val, val_))
                        if (_interface->group(id).config())
                            static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->wtc(val_);
                    break;
                }

                case PROPERTY_CHANALHOST_ADDR_GROUP:
                {
                    _interface->group(id).host(val);
                    break;
                };
                default: basegroupwraper::setProperty(id, prop, val);
            }
        }

        std::string linkgroupwraper::getProperty(indx id, propidtype prop) {

            switch (prop) {
                case PROPERTY_CHANALTYPE_GROUP:
                {
                    chnltype val_ = ((_interface->group(id).chanaltype() >= 0) && ((_interface->group(id).chanaltype() < 4))) ? _interface->group(id).chanaltype() : 0;
                    return to_str<chnltype>(val_);
                    break;
                }
                case PROPERTY_RSNUM_GROUP:
                {
                    num32 val_ = ((_interface->group(id).chanaltype() >= 0) && ((_interface->group(id).chanaltype() <= 0xFFFF))) ? _interface->group(id).chanalnum() : 0;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_DEVNUM_GROUP:
                {
                    num32 val_ = ((_interface->group(id).devnum() >= 0) && ((_interface->group(id).devnum() <= 0xF9))) ? _interface->group(id).devnum() : 0;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_BOUNDRATE:
                {
                    baudratetype val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->baudrate() : NT_RS_DOUNDRATE_9600;
                    return to_str<baudratetype>(val_);
                    break;
                }
                case PROPERTY_RS232_DATABIT:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->databit() : 8;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_STOPBIT:
                {
                    rsstopbittype val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->stopbit() : 0;
                    return to_str<rsstopbittype>(val_);
                    break;
                }
                case PROPERTY_RS232_PARITY:
                {
                    rsparitytype val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->parity() : 0;
                    return to_str<rsparitytype>(val_);
                    break;
                }
                case PROPERTY_RS232_FLOWCTRL:
                {
                    bool val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrol() : false;
                    return val_ ? "1" : "0";
                    break;
                }
                case PROPERTY_RS232_FLOWCTRLAF:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrolaftersleep() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_FLOWCTRLBE:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->flowcontrolbeforesleep() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_RI:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->readinterval() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_RTM:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->rtm() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_RTC:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->rtc() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_WTM:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->wtm() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_RS232_WTC:
                {
                    num32 val_ = (_interface->group(id).config()) ? static_cast<prs232_property> (const_cast<void*> (_interface->group(id).config()))->wtc() : 50;
                    return to_str<num32>(val_);
                    break;
                }
                case PROPERTY_CHANALHOST_ADDR_GROUP:
                {
                    return _interface->group(id).host();
                    break;
                };
                default: return basegroupwraper::getProperty(id, prop);
            }
        }

        void linkgroupwraper::setchaneltp(chnltype tp) {
            switch (tp) {
                case NT_CHTP_NODEF:
                {
                    propidtype propdel[] = {PROPERTY_RSNUM_GROUP, PROPERTY_MODBUS_PROTOCOL, PROPERTY_DEVNUM_GROUP,
                        PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_DATABIT, PROPERTY_RS232_STOPBIT, PROPERTY_RS232_PARITY,
                        PROPERTY_RS232_FLOWCTRL, PROPERTY_RS232_FLOWCTRLAF, PROPERTY_RS232_FLOWCTRLBE,
                        PROPERTY_RS232_RI, PROPERTY_RS232_RTM, PROPERTY_RS232_RTC, PROPERTY_RS232_WTM,
                        PROPERTY_RS232_WTC};
                    REMOVE_PROPERTYS(propdel);
                    break;
                }
                case NT_CHTP_RS232_4XX:
                {
                    propidtype propadd[] = {PROPERTY_RSNUM_GROUP, PROPERTY_MODBUS_PROTOCOL, PROPERTY_DEVNUM_GROUP, PROPERTY_RS232_BOUNDRATE,
                        PROPERTY_RS232_DATABIT, PROPERTY_RS232_STOPBIT, PROPERTY_RS232_PARITY, PROPERTY_RS232_FLOWCTRL,
                        PROPERTY_RS232_FLOWCTRLAF, PROPERTY_RS232_FLOWCTRLBE,
                        PROPERTY_RS232_RI, PROPERTY_RS232_RTM, PROPERTY_RS232_RTC, PROPERTY_RS232_WTM,
                        PROPERTY_RS232_WTC};
                    ADD_PROPERTYS(propadd);
                    propidtype propdel[] = {PROPERTY_CHANALHOST_ADDR_GROUP};
                    REMOVE_PROPERTYS(propdel);
                    break;
                }
                case NT_CHTP_TCP_IP:
                {
                    propidtype propadd[] = {PROPERTY_MODBUS_PROTOCOL, PROPERTY_DEVNUM_GROUP, PROPERTY_CHANALHOST_ADDR_GROUP};
                    ADD_PROPERTYS(propadd);
                    propidtype propdel[] = {PROPERTY_RSNUM_GROUP, PROPERTY_RS232_BOUNDRATE, PROPERTY_RS232_DATABIT,
                        PROPERTY_RS232_STOPBIT, PROPERTY_RS232_PARITY, PROPERTY_RS232_FLOWCTRL, PROPERTY_RS232_FLOWCTRLAF, PROPERTY_RS232_FLOWCTRLBE,
                        PROPERTY_RS232_RI, PROPERTY_RS232_RTM, PROPERTY_RS232_RTC, PROPERTY_RS232_WTM,
                        PROPERTY_RS232_WTC};
                    REMOVE_PROPERTYS(propdel);
                    break;
                }
            }
        }

        void linkgroupwraper::setids(const entity_map& vl) {
            typedef std::set<chnltype, std::less<chnltype>, std::allocator<chnltype> > chnltype_settmp;
            chnltype_settmp tmp;
            chnltype val_ = 0;
            for (entity_map::const_iterator it = vl.begin(); it != vl.end(); ++it) {
                val_ = ((_interface->group(it->first).chanaltype() >= 0) && ((_interface->group(it->first).chanaltype() < 3))) ? _interface->group(it->first).chanaltype() : 0;
                tmp.insert(val_);
            }
            val_ = (tmp.size() != 1) ? 0 : (*tmp.begin());
            setchaneltp(val_);
        }

        agroupwraper::agroupwraper(lcltype loc) : abstractwraper(loc) {

            propidtype propadd[] = {PROPERTY_NAME_ALARMGROUP};
            addinpropertyset((propidtype*) & propadd, 1);
        }

        void agroupwraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_NAME_ALARMGROUP);
        }

        void agroupwraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_NAME_ALARMGROUP:
                {
                    _interface->agroup(id).name(val);
                    break;
                };
            }
        }

        string agroupwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NAME_ALARMGROUP: return _interface->agroup(id).name();
            }
            return "";
        }

        void agroupwraper::commit(indx id) {
            _interface->merge_entities(NT_AGROUP, id);
        }

        userwraper::userwraper(lcltype loc) : abstractwraper(loc) {

            propidtype propadd[] = {PROPERTY_NAME_USER, PROPERTY_NAME_USERPASSWORD, PROPERTY_NAME_USERLEVEL, PROPERTY_USERFILTER, PROPERTY_USERROLE};
            ADD_PROPERTYS(propadd);
        }

        void userwraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_NAME_USER);
        }

        void userwraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_NAME_USER:
                {
                    _interface->user(id).name(val);
                    break;
                };
                case PROPERTY_NAME_USERPASSWORD:
                {
                    _interface->user(id).password(val);
                    break;
                };
                case PROPERTY_USERFILTER:
                {
                    _interface->user(id).filter(val);
                    break;
                };
                case PROPERTY_USERROLE:
                {
                    rolesettype val_ = str_to_role(val);
                    dvnci::lower_and_trim(val);
                    if ((val_) || (val == "deny"))
                        _interface->user(id).role(val_);
                    break;
                };
                case PROPERTY_NAME_USERLEVEL:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->user(id).accesslevel(val_);
                    break;
                };
            }
        }

        std::string userwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_NAME_USER: return _interface->user(id).name();
                case PROPERTY_NAME_USERPASSWORD: return _interface->user(id).password();
                case PROPERTY_USERFILTER: return _interface->user(id).filter();
                case PROPERTY_USERROLE: return role_to_str(_interface->user(id).role());
                case PROPERTY_NAME_USERLEVEL: return to_str(_interface->user(id).accesslevel());
            }
            return "";
        }

        void userwraper::commit(indx id) {
            _interface->merge_entities(NT_USER, id);
        }

        accessrulewraper::accessrulewraper(lcltype loc) : abstractwraper(loc) {

            propidtype propadd[] = {PROPERTY_ACCESSRULENAME, PROPERTY_ACCESSRULEUSER, PROPERTY_ACCESSRULEFILTER, PROPERTY_ACCESSRULEROLE,
                PROPERTY_ACCESSRULELEV};
            ADD_PROPERTYS(propadd);
        }

        void accessrulewraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_ACCESSRULENAME);
        }

        void accessrulewraper::setProperty(indx id, propidtype prop, string val) {
            switch (prop) {
                case PROPERTY_ACCESSRULENAME:
                {
                    _interface->accessrule(id).name(val);
                    break;
                };
                case PROPERTY_ACCESSRULEUSER:
                {
                    _interface->accessrule(id).user(val);
                    break;
                };
                case PROPERTY_ACCESSRULEHOST:
                {
                    _interface->accessrule(id).host(val);
                    break;
                };
                case PROPERTY_ACCESSRULEFILTER:
                {
                    _interface->accessrule(id).filter(val);
                    break;
                };
                case PROPERTY_ACCESSRULEAPPID:
                {
                    appidtype val_ = 0;
                    if (str_to(val, val_)) _interface->accessrule(id).appid(val_);
                    break;
                };
                case PROPERTY_ACCESSRULERULE:
                {
                    accessruletype val_ = 0;
                    if (str_to(val, val_)) _interface->accessrule(id).accessrule(val_);
                    break;
                };
                case PROPERTY_ACCESSRULEROLE:
                {
                    rolesettype val_ = str_to_role(val);
                    dvnci::lower_and_trim(val);
                    if ((val_) || (val == "deny"))
                        _interface->accessrule(id).role(val_);
                    break;
                };
                case PROPERTY_ACCESSRULEPROT:
                {
                    protocoltype val_ = 0;
                    if (str_to(val, val_)) _interface->accessrule(id).protocol(val_);
                    break;
                };
                case PROPERTY_ACCESSRULELEV:
                {
                    acclevtype val_ = 0;
                    if (str_to(val, val_)) _interface->accessrule(id).accesslevel(val_);
                    break;
                };
            }
        }

        std::string accessrulewraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_ACCESSRULENAME: return _interface->accessrule(id).name();
                case PROPERTY_ACCESSRULEUSER: return _interface->accessrule(id).user();
                case PROPERTY_ACCESSRULEHOST: return _interface->accessrule(id).host();
                case PROPERTY_ACCESSRULEFILTER: return _interface->accessrule(id).filter();
                case PROPERTY_ACCESSRULEAPPID: return to_str(_interface->accessrule(id).appid());
                case PROPERTY_ACCESSRULERULE: return to_str(_interface->accessrule(id).accessrule());
                case PROPERTY_ACCESSRULEROLE: return role_to_str(_interface->accessrule(id).role());
                case PROPERTY_ACCESSRULEPROT: return to_str(_interface->accessrule(id).protocol());
                case PROPERTY_ACCESSRULELEV: return to_str(_interface->accessrule(id).accesslevel());
            }
            return "";
        }

        void accessrulewraper::commit(indx id) {
            _interface->merge_entities(NT_ACCESSRULE, id);
        }

        configprjwraper::configprjwraper(lcltype loc) : abstractwraper(loc) {

            propidtype propadd[] = {PROPERTY_CNFG_PATH, PROPERTY_CNFG_NAME, PROPERTY_CNFG_COMMENT, PROPERTY_CNFG_MAPSIZE,
                PROPERTY_CNFG_OSTYPE, PROPERTY_CNFG_DBMANAGER, PROPERTY_CNFG_DBCONSTR,
                PROPERTY_CNFG_ANALOGBUFF, PROPERTY_CNFG_HISTORYPERIOD, PROPERTY_CNFG_LOGLEVEL,
                PROPERTY_CNFG_ADMINPORT, PROPERTY_CNFG_REMOTEPORT, PROPERTY_CNFG_OPCREMOTEPORT};
            ADD_PROPERTYS(propadd);
        }

        void configprjwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_CNFG_DBMANAGER, &dbprovPred);
            mangr->registpropertyeditor(PROPERTY_CNFG_ANALOGBUFF, &boolPrEdit);
            mangr->registpropertyeditor(PROPERTY_CNFG_LOGLEVEL, &debuglevPred);
        }

        void configprjwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_CNFG_NAME:
                {
                    _interface->conf_property(NS_CNFG_NAME, val);
                    break;
                };
                case PROPERTY_CNFG_COMMENT:
                {
                    _interface->conf_property(NS_CNFG_COMMENT, val);
                    break;
                };
                    // case PROPERTY_CNFG_OSTYPE:{
                    //     _interface->conf_property(NS_CNFG_OSTYPE, val);
                    //    break;};
                    // case PROPERTY_CNFG_MAPSIZE:{
                    //   int val_ = 0;
                    //   if (str_to(val, val_)) _interface->conf_property(NS_CNFG_MAPSZ, val_);
                    //   break;};
                case PROPERTY_CNFG_DBMANAGER:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_DBMANAGER, val_);
                    break;
                };
                case PROPERTY_CNFG_DBCONSTR:
                {
                    _interface->conf_property(NS_CNFG_DBCONSTR, val);
                    break;
                };
                case PROPERTY_CNFG_ANALOGBUFF:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_ANALOGBUFF, val_);
                    break;
                };
                case PROPERTY_CNFG_HISTORYPERIOD:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_HISTORYPERIOD, val_);
                    break;
                };
                case PROPERTY_CNFG_LOGLEVEL:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_LOGLEVEL, val_);
                    break;
                };
                    // case PROPERTY_CNFG_ADMINNAME:{
                    //     _interface->conf_property(NS_CNFG_ADMINNAME, val);
                    //     break;};
                    //  case PROPERTY_CNFG_ADMINPASS:{
                    //     _interface->conf_property(NS_CNFG_ADMINPASS, val);
                    //      break;};
                case PROPERTY_CNFG_ADMINPORT:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_ADMINPORT, val_);
                    break;
                };
                case PROPERTY_CNFG_REMOTEPORT:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_REMOTEPORT, val_);
                    break;
                };
                case PROPERTY_CNFG_OPCREMOTEPORT:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->conf_property(NS_CNFG_OPCREMOTEPORT, val_);
                    break;
                };
            }
        }

        string configprjwraper::getProperty(indx id, propidtype prop) {
            switch (prop) {
                case PROPERTY_CNFG_PATH:
                {
                    return _interface->conf_property(NS_CNFG_PATH);
                };
                case PROPERTY_CNFG_NAME:
                {
                    return _interface->conf_property(NS_CNFG_NAME);
                };
                case PROPERTY_CNFG_COMMENT:
                {
                    return _interface->conf_property(NS_CNFG_COMMENT);
                };
                case PROPERTY_CNFG_OSTYPE:
                {
                    int tmp = 0;
                    if (dvnci::str_to<int>(_interface->conf_property(NS_CNFG_OSTYPE), tmp)) {
                        switch (tmp) {
                            case 1: return "WIN32";
                            case 2: return "WIN64";
                        }
                    }
                    return "";
                };
                case PROPERTY_CNFG_MAPSIZE:
                {
                    int tmp = 0;
                    if (dvnci::str_to<int>(_interface->conf_property(NS_CNFG_MAPSZ), tmp)) {
                        return to_str((tmp / 1024) / 1024) + " Mb";
                    }
                    return "";
                };
                case PROPERTY_CNFG_DBMANAGER:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_DBMANAGER));
                };
                case PROPERTY_CNFG_DBCONSTR:
                {
                    return _interface->conf_property(NS_CNFG_DBCONSTR);
                };

                case PROPERTY_CNFG_ANALOGBUFF:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_ANALOGBUFF));
                };
                case PROPERTY_CNFG_HISTORYPERIOD:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_HISTORYPERIOD));
                };
                case PROPERTY_CNFG_LOGLEVEL:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_LOGLEVEL));
                };
                    //    case PROPERTY_CNFG_ADMINNAME:{
                    //        return _interface->conf_property(NS_CNFG_ADMINNAME);};
                    //    case PROPERTY_CNFG_ADMINPASS:{
                    //        return _interface->conf_property(NS_CNFG_ADMINPASS);};
                case PROPERTY_CNFG_ADMINPORT:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_ADMINPORT));
                };
                case PROPERTY_CNFG_REMOTEPORT:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_REMOTEPORT));
                };
                case PROPERTY_CNFG_OPCREMOTEPORT:
                {
                    return to_str(_interface->conf_numproperty(NS_CNFG_OPCREMOTEPORT));
                };
            }
            return "";
        }

        void configprjwraper::commit(indx id) {
        }

        baseserviceitemwraper::baseserviceitemwraper(lcltype loc) : abstractwraper(loc) {
            propidtype propadd[] = {PROPERTY_NAME_SERVICE, PROPERTY_PATH_SERVICE, PROPERTY_STARTTYPE_SERVICE /*PROPERTY_TYPE_SERVICE, PROPERTY_STATUS_SERVICE*/};
            ADD_PROPERTYS(propadd);
        }

        void baseserviceitemwraper::excludegroupedit(propertysset& excl) {
            excl.insert(PROPERTY_NAME_SERVICE);
            excl.insert(PROPERTY_PATH_SERVICE);
        }

        void baseserviceitemwraper::addproprtyeditors_internal(abstractpropertymanager* mangr) {
            mangr->registpropertyeditor(PROPERTY_STARTTYPE_SERVICE, &starttypred);
            mangr->registpropertyeditor(PROPERTY_NAME_SERVICE, &noEditPrEdit);
            mangr->registpropertyeditor(PROPERTY_PATH_SERVICE, &noEditPrEdit);
        }

        void baseserviceitemwraper::setProperty(indx id, propidtype prop, string val) {

            switch (prop) {
                case PROPERTY_STARTTYPE_SERVICE:
                {
                    int val_ = 0;
                    if (str_to(val, val_)) _interface->service(id).starttype(val_);
                    break;
                };
            }
        }

        std::string baseserviceitemwraper::getProperty(indx id, propidtype prop) {
            DEBUG_STR_DVNCI(baseserviceitemwraper::getProperty);
            DEBUG_VAL2_DVNCI(id, prop);
            switch (prop) {
                case PROPERTY_NAME_SERVICE:
                {
                    return _interface->service(id).displayname();
                };
                case PROPERTY_PATH_SERVICE:
                {
                    return _interface->service(id).path();
                };
                case PROPERTY_STARTTYPE_SERVICE:
                {
                    return to_str(_interface->service(id).starttype());
                };
            }
            return "";
        }
    }
}

