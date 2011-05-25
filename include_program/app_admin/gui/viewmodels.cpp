/* 
 * File:   AbstractBaseModel.cpp
 * Author: Serg Alexeev sealeks@mail.ru
 * 
 * Created on 10 Декабрь 2009 г., 21:27
 */

#include "viewmodels.h"


namespace dvnci {
    namespace admin {


        /////////////////////////////////////////////////////////

        void tagsitemdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                tagsviewmodel* md = dynamic_cast<tagsviewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        num64 key = index.internalId();
                        if (mainintf->tag(key).refcnt() > 0) option_.font.setBold(true);
                        else option_.font.setBold(false);
                        if (mainintf->tag(key).error() != 0) {
                            option_.palette.setColor(QPalette::Text, immi_errortag_color);}
                        else {
                            if (mainintf->tag(key).valid() > 90)  option_.palette.setColor(QPalette::Text, immi_valid_color);
                            else option_.palette.setColor(QPalette::Text, option.palette.color(QPalette::Text));}
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        tagsviewmodel::tagsviewmodel( int loc_) : basetable(loc_) {
            iconmappair tmp[24]  = {iconmappair(TYPE_NODEF , QIcon(":icon/icon/ntGT.bmp")),
                iconmappair(TYPE_DOUBLE, QIcon(":icon/icon/ntReal.bmp")),
                iconmappair(TYPE_FLOAT, QIcon(":icon/icon/ntSingle.bmp")),
                iconmappair(TYPE_NUM64, QIcon(":icon/icon/ntLongWord.bmp")),
                iconmappair(TYPE_UNUM64, QIcon(":icon/icon/ntLongWord.bmp")),
                iconmappair(TYPE_NUM32, QIcon(":icon/icon/ntLongWord.bmp")),
                iconmappair(TYPE_UNUM32, QIcon(":icon/icon/ntLongWord.bmp")),
                iconmappair(TYPE_NUM16, QIcon(":icon/icon/ntWord.bmp")),
                iconmappair(TYPE_UNUM16, QIcon(":icon/icon/ntShortInt.bmp")),
                iconmappair(TYPE_NUM8, QIcon(":icon/icon/ntChar.bmp")),
                iconmappair(TYPE_UNUM8, QIcon(":icon/icon/ntByte.bmp")),
                iconmappair(TYPE_DISCRET, QIcon(":icon/icon/ntReal.bmp")),
                iconmappair(TYPE_TEXT, QIcon(":icon/icon/ntText.bmp")),
                iconmappair(TYPE_TM, QIcon(":icon/icon/ntDT.bmp")),
                iconmappair(REPORTTYPE_HOUR, QIcon(":icon/icon/ntHour.bmp")),
                iconmappair(REPORTTYPE_DAY, QIcon(":icon/icon/ntDay.bmp")),
                iconmappair(REPORTTYPE_MONTH, QIcon(":icon/icon/ntMonth.bmp")),
                iconmappair(REPORTTYPE_YEAR, QIcon(":icon/icon/ntYear.bmp")),
                iconmappair(REPORTTYPE_MIN, QIcon(":icon/icon/ntMin.bmp")),
                iconmappair(REPORTTYPE_DEC, QIcon(":icon/icon/ntDec.bmp")),
                iconmappair(REPORTTYPE_10MIN, QIcon(":icon/icon/ntMin10.bmp")),
                iconmappair(REPORTTYPE_30MIN, QIcon(":icon/icon/ntMin30.bmp")),
                iconmappair(REPORTTYPE_QVART, QIcon(":icon/icon/ntQvart.bmp")),
                iconmappair(EVENT_TYPE_WITHTIME, QIcon(":icon/icon/ntEvent.bmp"))};

            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 24, QIcon(":icon/icon/ntGT.bmp")));
            mbDelegate = new tagsitemdelegate();}

        QVariant tagsviewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {
                THD_EXCLUSIVE_LOCK(mainintf);

                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();

                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                QIcon tmm = iconmap->operator [](mainintf->tag(id).type());


                switch (index.column()) {
                    case 0: return iconmap->operator [](mainintf->tag(id).type());
                    case 1: return static_cast<int>(id);
                    case 2: return qtstr_from_str_loc(mainintf->tag(id).name());
                    case 3: return qtstr_from_str_loc(mainintf->tag(id).binding());
                    case 4: return mainintf->tag(id).value().c_str();
                    case 5: return mainintf->tag(id).value_log().c_str();
                    case 6: return mainintf->tag(id).time().c_str();
                    case 7: return mainintf->tag(id).valid();
                    case 8: return mainintf->tag(id).refcnt();
                    case 9: return mainintf->tag(id).error() ? QVariant(qtstr_translate(std::string(std::string("error.")+ to_str(mainintf->tag(id).error())).c_str())) : "";
                    case 10: return qtstr_from_str_loc(mainintf->tag(id).comment());}}

            return QVariant();}

        QVariant tagsviewmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("__"));
                case 1: return QVariant(qtstr_translate("maintable.key"));
                case 2: return QVariant(qtstr_translate("maintable.name"));
                case 3: return QVariant(qtstr_translate("maintable.binding"));
                case 4: return QVariant(qtstr_translate("maintable.val"));
                case 5: return QVariant(qtstr_translate("Lv"));
                case 6: return QVariant(qtstr_translate("maintable.tm"));
                //case 6: return QVariant(qtstr_translate("Lt"));
                case 7: return QVariant(qtstr_translate("maintable.vl"));
                case 8: return QVariant(qtstr_translate("maintable.rc"));
                case 9: return QVariant(qtstr_translate("maintable.error"));
                case 10: return QVariant(qtstr_translate("maintable.comment"));}

            return  QVariant();}


        ////////////////////////////////////////////////////////////////////////

        void groupsitemdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                groupsviewmodel* md = dynamic_cast<groupsviewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        num64 key = index.internalId();
                        if (mainintf->group(key).valid() > 90) option_.font.setBold(true);
                        else option_.font.setBold(false);
                        if (mainintf->group(key).error() != 0) {
                            option_.palette.setColor(QPalette::Text, immi_errortag_color);}
                        else {
                            if (mainintf->group(key).active())  option_.palette.setColor(QPalette::Text, immi_valid_color);
                            else option_.palette.setColor(QPalette::Text, option.palette.color(QPalette::Text));}
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        groupsviewmodel::groupsviewmodel( int loc_) : basetable(loc_) {
            iconmappair tmp[12]  = {iconmappair(NS_GROUP_SYSTEM, QIcon(":icon/icon/ntOSystem.bmp")),
                iconmappair(NS_GROUP_SYSTEMVAR, QIcon(":icon/icon/ntOSysVar.bmp")),
                iconmappair(NS_GROUP_SYSTEMCOUNT, QIcon(":icon/icon/ntOServCount.bmp")),
                iconmappair(NS_GROUP_SYSTEMREPORT, QIcon(":icon/icon/ntOReport.bmp")),
                iconmappair(NS_GROUP_SYSTEMREPORTCOUNT, QIcon(":icon/icon/ntOReportCnt.bmp")),
                iconmappair(NS_GROUP_NET, QIcon(":icon/icon/ntOnet.bmp")),
                iconmappair(NS_GROUP_OPC, QIcon(":icon/icon/ntOOPC.bmp")),
                iconmappair(NS_GROUP_DDE, QIcon(":icon/icon/ntODDE.bmp")),
                iconmappair(NS_GROUP_MODBUS, QIcon(":icon/icon/ntOModbus.bmp")),
                iconmappair(NS_GROUP_KOYO, QIcon(":icon/icon/ntODKoy.bmp")),
                iconmappair(NS_GROUP_LGKA, QIcon(":icon/icon/ntOLogika.bmp"))};

            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 11, QIcon(":icon/icon/ntOBase.bmp")));
            mbDelegate = new groupsitemdelegate();};

        QVariant groupsviewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {
                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                THD_EXCLUSIVE_LOCK(mainintf);

                switch (index.column()) {
                    case 0: return iconmap->operator [](mainintf->group(id).appid());
                    case 1: return static_cast<int>(id);
                    case 2: return qtstr_from_str_loc(mainintf->group(id).name());
                    case 3: return mainintf->group(id).active() ? "1": "0";
                    case 4: return mainintf->group(id).valid();
                    case 5: return mainintf->group(id).error() ? QVariant(qtstr_translate(std::string(std::string("error.")+ to_str(mainintf->group(id).error())).c_str())) : "";}}

            return QVariant();}

        QVariant groupsviewmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("__"));
                case 1: return QVariant(qtstr_translate("N"));
                case 2: return QVariant(qtstr_translate("grouptable.name"));
                case 3: return QVariant(qtstr_translate("grouptable.activ"));
                case 4: return QVariant(qtstr_translate("grouptable.valid"));
                case 5: return QVariant(qtstr_translate("grouptable.error"));}

            return  QVariant();}


        /////////////////////////////////////////////////////////////////

        QVariant accessrulesviewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {
                THD_EXCLUSIVE_LOCK(mainintf);
                if (role != Qt::DisplayRole) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();

                switch (index.column()) {
                    case 0: return qtstr_from_str_loc(mainintf->accessrule(id).name());
                    case 1: return qtstr_from_str_loc(mainintf->accessrule(id).cidr());
                    case 2: return qtstr_from_str_loc(mainintf->accessrule(id).application());
                    case 3: return (int) mainintf->accessrule(id).appid();
                    case 4: return (int) mainintf->accessrule(id).rule();
                    case 5: return (int) mainintf->accessrule(id).accesslevel();}}

            return QVariant();}

        QVariant accessrulesviewmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("accessrule.name"));
                case 1: return QVariant(qtstr_translate("accessrule.cidr"));
                case 2: return QVariant(qtstr_translate("accessrule.app"));
                case 3: return QVariant(qtstr_translate("accessrule.appid"));
                case 4: return QVariant(qtstr_translate("accessrule.rule"));
                case 5: return QVariant(qtstr_translate("regtable.acceslev"));}

            return  QVariant();}

        //////////////////////////////////////////////////////////









        /////////////////////////////////////////////////////////

        void debug_viewdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                debug_viewmodel* md = dynamic_cast<debug_viewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        num64 key = index.internalId();
                        switch (mainintf->debug(key).level()) {
                            case DEBUG_FATALERROR:{
                                option_.palette.setColor(QPalette::Text, immi_fatal_error_color1);
                                option_.font.setBold(true);
                                break;}
                            case DEBUG_ERROR:{
                                option_.palette.setColor(QPalette::Text, immi_error_color1);
                                option_.font.setBold(false);
                                break;}
                            case DEBUG_WARNING:{
                                option_.palette.setColor(QPalette::Text, immi_warning_color1);
                                option_.font.setBold(false);
                                break;}
                            default:{
                                option_.palette.setColor(QPalette::Text, immi_message_color1);
                                option_.font.setBold(false);
                                break;}}
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        debug_viewmodel::debug_viewmodel( int loc_ ) : livetableview(loc_) {
            mbDelegate = new debug_viewdelegate();
            iconmappair tmp[4]  = {iconmappair(DEBUG_MESSAGE, QIcon(":icon/icon/lognotice.png")),
                iconmappair(DEBUG_WARNING, QIcon(":icon/icon/logwarning.png")),
                iconmappair(DEBUG_ERROR, QIcon(":icon/icon/logerror.png")),
                iconmappair(DEBUG_FATALERROR, QIcon(":icon/icon/logerror.png"))};
            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 4));};

        QVariant debug_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {

                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();

                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                THD_EXCLUSIVE_LOCK(mainintf);

                switch (index.column()) {
                    case 0: return iconmap->operator [](mainintf->debug(id).level());
                    case 1: return mainintf->debug(id).time().c_str();
                    case 2: return qtstr_from_str_loc(mainintf->debug(id).message());
                    case 3: return QVariant(qtstr_translate(std::string("application." + to_str(mainintf->debug(id).appid())).c_str()));}}

            return QVariant();}

        QVariant debug_viewmodel::headerData(int section, Qt::Orientation orientation, int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("_"));
                case 1: return QVariant(qtstr_translate("logtable.tm"));
                case 2: return QVariant(qtstr_translate("logtable.msg"));
                case 3: return QVariant(qtstr_translate("logtable.app"));}

            return  QVariant();}


        /////////////////////////////////////////////////////////

        void journal_viewdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                journal_viewmodel* md = dynamic_cast<journal_viewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        num64 key = index.internalId();
                        switch (mainintf->journal(key).type()) {
                            case msNew:{
                                option_.palette.setColor(QPalette::Text, (mainintf->journal(key).level() >= altAccident) ? immi_accidnew_color : immi_alarmnew_color);
                                option_.font.setBold(false);
                                break;}
                            case msKvit:{
                                option_.palette.setColor(QPalette::Text, (mainintf->journal(key).level() >= altAccident) ? immi_accidkvit_color : immi_alarmkvit_color);
                                option_.font.setBold(false);
                                break;}
                            case msOut:{
                                option_.palette.setColor(QPalette::Text, (mainintf->journal(key).level() >= altAccident) ? immi_accidoff_color : immi_alarmoff_color);
                                option_.font.setBold(false);
                                break;}
                            case msOn:{
                                option_.palette.setColor(QPalette::Text, immi_eventon_color);
                                option_.font.setBold(false);
                                break;}
                            case msOff:{
                                option_.palette.setColor(QPalette::Text, immi_eventoff_color);
                                option_.font.setBold(false);
                                break;}
                            case msCmd:{
                                option_.palette.setColor(QPalette::Text, immi_command_color);
                                option_.font.setBold(true);
                                break;}
                            case msTimeEvent:{
                                option_.palette.setColor(QPalette::Text, immi_timeevent_color);
                                option_.font.setBold(true);
                                break;}}
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        journal_viewmodel::journal_viewmodel( int loc_ ) : livetableview(loc_) {
            mbDelegate = new journal_viewdelegate();
            iconmappair tmp[16]  = {iconmappair(((msNew << 4) | (altAccident)) , QIcon(":icon/icon/jravarnew.png")),
                iconmappair(((msNew << 4) | (altWarning)) , QIcon(":icon/icon/jralarmnew.png")),
                iconmappair(((msNew << 4) | (altNotice)) , QIcon(":icon/icon/jrnoticenew.png")),
                iconmappair(((msKvit << 4) | (altAccident)) , QIcon(":icon/icon/jravarkvit.png")),
                iconmappair(((msKvit << 4) | (altWarning)) , QIcon(":icon/icon/jralarmkvit.png")),
                iconmappair(((msKvit << 4) | (altNotice)) , QIcon(":icon/icon/jrnoticekvit.png")),
                iconmappair(((msOut << 4) | (altAccident)) , QIcon(":icon/icon/jravaroff.png")),
                iconmappair(((msOut << 4) | (altWarning)) , QIcon(":icon/icon/jralarmoff.png")),
                iconmappair(((msOut << 4) | (altNotice)) , QIcon(":icon/icon/jrnoticeoff.png")),
                iconmappair(((msCmd << 4) ) , QIcon(":icon/icon/jrcommand.png")),
                iconmappair(((msOn << 4) ) , QIcon(":icon/icon/jron.png")),
                iconmappair(((msOff << 4) ) , QIcon(":icon/icon/jroff.png")),
                iconmappair(((msTimeEvent << 4) ) , QIcon(":icon/icon/jrevent.png")),
                iconmappair(((msTimeEvent << 4) | (altAccident)) , QIcon(":icon/icon/jreventav.png")),
                iconmappair(((msTimeEvent << 4) | (altWarning)) , QIcon(":icon/icon/jrevental.png")),
                iconmappair(((msTimeEvent << 4) | (altNotice)) , QIcon(":icon/icon/jreventnot.png"))};
            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 16));};

        QVariant journal_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {


                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();

                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                THD_EXCLUSIVE_LOCK(mainintf);



                switch (index.column()) {
                    case 0: return iconmap->operator[]((mainintf->journal(id).type() << 4) | (mainintf->journal(id).level()));
                    case 1: return qtstr_from_str_utf8(mainintf->journal(id).time().c_str());
                    case 2: return qtstr_from_str_utf8(mainintf->journal(id).tag().c_str());
                    case 3: return qtstr_from_str_utf8(mainintf->journal(id).text().c_str());}}

            return QVariant();}

        QVariant journal_viewmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("_"));
                case 1: return QVariant(qtstr_translate("alarmtable.tm"));
                case 2: return QVariant(qtstr_translate("alarmtable.id"));
                case 3: return QVariant(qtstr_translate(""));}

            return  QVariant();}


        /////////////////////////////////////////////////////////////////

        void command_viewdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                command_viewmodel* md = dynamic_cast<command_viewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        option_.palette.setColor(QPalette::Text, immi_command_color);
                        option_.font.setBold(true);
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        QVariant command_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {

                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();

                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                THD_EXCLUSIVE_LOCK(mainintf);

                switch (index.column()) {
                    case 0: return _iconCommand;
                    case 1: return static_cast<int>(id);
                    case 2: return mainintf->command(id).tag().c_str();
                    case 3: return mainintf->command(id).valuebefore().c_str();
                    case 4: return mainintf->command(id).value().c_str();}}
            return QVariant();}

        QVariant command_viewmodel::headerData(int section, Qt::Orientation orientation, int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("commandtable.num"));
                case 1: return QVariant(qtstr_translate("commandtable.id"));
                case 2: return QVariant(qtstr_translate("commandtable.tag"));
                case 3: return QVariant(qtstr_translate("commandtable.val_bef"));
                case 4: return QVariant(qtstr_translate("commandtable.val"));}

            return  QVariant();}


        /////////////////////////////////////////////////////////////////

        void alarm_viewdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if (index.isValid()) {
                alarm_viewmodel* md = dynamic_cast<alarm_viewmodel*> (const_cast<QAbstractItemModel*> (index.model()));
                if (md) {
                    adminintf_ptr  mainintf = md->interf();
                    if (mainintf) {
                        QStyleOptionViewItem option_ = option;
                        num64 key = index.internalId();
                        if (mainintf->journal(key).level() >= altAccident) {
                            option_.palette.setColor(QPalette::Text, (mainintf->alarm(key).kvit()) ? immi_accidkvit_color : immi_accidnew_color);
                            option_.font.setBold(true);}
                        else {
                            option_.palette.setColor(QPalette::Text, (mainintf->alarm(key).kvit()) ? immi_alarmkvit_color : immi_alarmnew_color);
                            option_.font.setBold(true);}
                        QItemDelegate::paint(painter, option_, index);
                        return;}}}
            QItemDelegate::paint(painter, option, index);}

        alarm_viewmodel::alarm_viewmodel( int loc_) : livetableview(loc_) {
            mbDelegate = new alarm_viewdelegate();
            iconmappair tmp[9]  = {iconmappair( ((msNew << 4) | altAccident), QIcon(":icon/icon/jravarnew.png")),
                iconmappair( ((msNew << 4) | altWarning), QIcon(":icon/icon/jralarmnew.png")),
                iconmappair( ((msNew << 4) | altNotice), QIcon(":icon/icon/jrnoticenew.png")),
                iconmappair( ((msKvit << 4) | altAccident), QIcon(":icon/icon/jravarkvit.png")),
                iconmappair( ((msKvit << 4) | altWarning), QIcon(":icon/icon/jralarmkvit.png")),
                iconmappair( ((msKvit << 4) | altNotice), QIcon(":icon/icon/jrnoticekvit.png")),
                iconmappair( ((msTimeEvent << 4) | altAccident), QIcon(":icon/icon/jreventav.png")),
                iconmappair( ((msTimeEvent << 4) | altWarning), QIcon(":icon/icon/jreventnot.png")),
                iconmappair( ((msTimeEvent << 4) | altNotice), QIcon(":icon/icon/jreventnot.png"))};
            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 9));};

        QVariant alarm_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {


                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();
                THD_EXCLUSIVE_LOCK(mainintf);
                switch (index.column()) {
                    case 0: return (!mainintf->alarm(id).kvit()) ?
                                iconmap->operator[]((mainintf->alarm(id).type() << 4) | (mainintf->alarm(id).level())) :
                                iconmap->operator[]((msKvit << 4) | (mainintf->alarm(id).level())) ;
                    case 1: return qtstr_from_str_utf8(mainintf->alarm(id).time().c_str());
                    case 2: return qtstr_from_str_utf8(mainintf->alarm(id).tag().c_str());
                    case 3: return qtstr_from_str_utf8(mainintf->alarm(id).text().c_str());}}

            return QVariant();}

        QVariant alarm_viewmodel::headerData(int section, Qt::Orientation orientation, int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("_"));
                case 1: return QVariant(qtstr_translate("activealarmtable.tm"));
                case 2: return QVariant(qtstr_translate("activealarmtable.id"));
                case 3: return QVariant(qtstr_translate(""));}

            return  QVariant();}


        /////////////////////////////////////////////////////////////////

        regystry_viewmodel::regystry_viewmodel( int loc_ ) : livetableview(loc_) {
            iconmappair tmp[11]  = {iconmappair(NS_ADMIN_APPLICATION, QIcon(":icon/icon/appAdmin.png")),
                iconmappair(NS_ADMIN_SERVICE, QIcon(":icon/icon/appAdminService.png")),
                iconmappair(NS_PERSISTENCE_SERVICE, QIcon(":icon/icon/appArchService.png")),
                iconmappair(NS_SYSTEM_SERVICE, QIcon(":icon/icon/appSystemService.png")),
                iconmappair(NS_NET_SERVICE, QIcon(":icon/icon/appNetService.png")),
                iconmappair(NS_OPC_SERVICE, QIcon(":icon/icon/appOpcService.png")),
                iconmappair(NS_DDE_SERVICE, QIcon(":icon/icon/appDDEService.png")),
                iconmappair(NS_MODBUS_SERVICE, QIcon(":icon/icon/appModbusService.png")),
                iconmappair(NS_KOYO_SERVICE, QIcon(":icon/icon/appKoyoService.bmp")),
                iconmappair(NS_LGKA_SERVICE, QIcon(":icon/icon/appLgkService.png")),
                iconmappair(10000, QIcon(":icon/icon/AppTestService.png"))};
            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 11, QIcon(":icon/icon/AppNodef.png") ));
            mbDelegate = 0;};

        QVariant regystry_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {
                THD_EXCLUSIVE_LOCK(mainintf);
                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();

                switch (index.column()) {
                    case 0: return iconmap->operator [](mainintf->registry(id).appid());
                    case 1: return qtstr_translate(mainintf->registry(id).name().c_str());
                    case 2: return mainintf->registry(id).evset();
                    case 3: return mainintf->registry(id).queuehandle() ? to_str(mainintf->registry(id).queuehandle()).c_str(): "";}}

            return QVariant();}

        QVariant regystry_viewmodel::headerData(int section, Qt::Orientation orientation, int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("__"));
                case 1: return QVariant(qtstr_translate("regtable.name"));
                case 2: return QVariant(qtstr_translate("regtable.evst"));
                case 3: return QVariant(qtstr_translate("regtable.msghnd"));}

            return  QVariant();}


        /////////////////////////////////////////////////////////////////

        client_viewmodel::client_viewmodel( int loc_ ) : livetableview(loc_) {
            iconmappair tmp[12]  = {iconmappair(NS_ADMIN_APPLICATION, QIcon(":icon/icon/appAdmin.png")),
                iconmappair(NS_ADMIN_SERVICE, QIcon(":icon/icon/appAdminService.png")),
                iconmappair(NS_PERSISTENCE_SERVICE, QIcon(":icon/icon/appArchService.png")),
                iconmappair(NS_SYSTEM_SERVICE, QIcon(":icon/icon/appSystemService.png")),
                iconmappair(NS_NET_SERVICE, QIcon(":icon/icon/appNetService.png")),
                iconmappair(NS_OPC_SERVICE, QIcon(":icon/icon/appOpcService.png")),
                iconmappair(NS_DDE_SERVICE, QIcon(":icon/icon/appDDEService.png")),
                iconmappair(NS_MODBUS_SERVICE, QIcon(":icon/icon/appModbusService.png")),
                iconmappair(NS_KOYO_SERVICE, QIcon(":icon/icon/appKoyoService.bmp")),
                iconmappair(NS_LGKA_SERVICE, QIcon(":icon/icon/appLgkService.png")),
                iconmappair(10000, QIcon(":icon/icon/AppTestService.png"))};
            iconmap = iconmaptype_ptr( new iconmaptype(tmp, 11, QIcon(":icon/icon/AppNodef.png") ));
            mbDelegate = 0;};

        QVariant client_viewmodel::data(const QModelIndex &index, int role) const {
            if (index.isValid()) {
                THD_EXCLUSIVE_LOCK(mainintf);
                if ((role != Qt::DecorationRole) && (index.column() == 0)) return QVariant();
                if ((role != Qt::DisplayRole) && (index.column() > 0)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if ((id == npos) && (index.column() > 0)) return QVariant();

                switch (index.column()) {
                    case 0: return iconmap->operator [](mainintf->client(id).appid());
                    case 1: return qtstr_from_str_loc(mainintf->client(id).ip());
                    case 2: return qtstr_from_str_loc(mainintf->client(id).host());
                    case 3: return qtstr_from_str_loc(mainintf->client(id).user());
                    case 4: return QVariant(qtstr_translate(std::string("application." + to_str(mainintf->client(id).appid())).c_str()));}}

            return QVariant();}

        QVariant client_viewmodel::headerData(int section, Qt::Orientation orientation, int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("__"));
                case 1: return QVariant(qtstr_translate("clients.ip"));
                case 2: return QVariant(qtstr_translate("clients.host"));
                case 3: return QVariant(qtstr_translate("clients.user"));
                case 4: return QVariant(qtstr_translate("clients.service"));}

            return  QVariant();}}}






