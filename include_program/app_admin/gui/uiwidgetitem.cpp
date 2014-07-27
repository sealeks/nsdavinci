#include "uiwidgetitem.h"

namespace dvnci {
    namespace admin {


        using namespace std;

        nodetype getnormalizetag(nodetype val) {
            if (val == NT_ATAG) return NT_TAG;
            return val;}



        bool uiwidgetitem::iconinit = false;

        QIcon* uiwidgetitem::nillIcon = 0;

        QIcon* uiwidgetitem::filterIcon = 0;

        icon_map uiwidgetitem::iconmap;

        noderang_map uiwidgetitem::rangmap;

        void uiwidgetitem::regist() {

            if (iconinit) return;
            nillIcon = new QIcon(":icon/icon/PrjSome.bmp");
            filterIcon = new QIcon(":icon/icon/filter.bmp");
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT),  QIcon(":icon/icon/ntmainRoot.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_SERVERS_NOTAVAIL), QIcon(":icon/icon/ntLocalServNA.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_SERVERS_AVAIL), QIcon(":icon/icon/ntLocalServ.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_SERVERS_NOTAVAIL_R), QIcon(":icon/icon/ntRemoteServNC.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_SERVERS_AVAIL_R), QIcon(":icon/icon/ntRemoteServ.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTILGROUP), QIcon(":icon/icon/ntRootTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_MAINTABLE), QIcon(":icon/icon/ntBaseTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_GROUPTABLE), QIcon(":icon/icon/ntGroupTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_DEBUG), QIcon(":icon/icon/ntLogTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_REGISTRY), QIcon(":icon/icon/ntRegTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_VALCH), QIcon(":icon/icon/ntValChTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_COMMAND), QIcon(":icon/icon/ntCommandTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_ACCESSRULES), QIcon(":icon/icon/ntAccessRules.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_CLIENTS), QIcon(":icon/icon/ntClients.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_GROUPS), QIcon(":icon/icon/ntO.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_AGROUPS), QIcon(":icon/icon/ntT.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_SERVICES), QIcon(":icon/icon/ntService.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_USERS), QIcon(":icon/icon/ntUsers.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ROOT_ACCESSRULES), QIcon(":icon/icon/ntRules.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP), QIcon(":icon/icon/ntOBase.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_AGROUP), QIcon(":icon/icon/cdtGroup.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_USER), QIcon(":icon/icon/ntUser.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_ACCESSRULE), QIcon(":icon/icon/ntRule.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG), QIcon(":icon/icon/ntGT.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_SERVICE), QIcon(":icon/icon/ntServiceNo.bmp")));

            iconmap.insert(icon_pair(nodeinfotype(NT_SERVICE, SERVICE_STATUS_RUN), QIcon(":icon/icon/ntServiceOn.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_SERVICE, SERVICE_STATUS_STOPED), QIcon(":icon/icon/ntServiceOff.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_SERVICE, SERVICE_STATUS_PENDING), QIcon(":icon/icon/ntServicePend.bmp")));

            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_HOUR), QIcon(":icon/icon/ntHour.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_DAY), QIcon(":icon/icon/ntDay.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_MONTH), QIcon(":icon/icon/ntMonth.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_YEAR), QIcon(":icon/icon/ntYear.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_MIN), QIcon(":icon/icon/ntMin.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_DEC), QIcon(":icon/icon/ntDec.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_10MIN), QIcon(":icon/icon/ntMin10.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_30MIN), QIcon(":icon/icon/ntMin30.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, REPORTTYPE_QVART), QIcon(":icon/icon/ntQvart.bmp")));

            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, EVENT_TYPE_WITHTIME), QIcon(":icon/icon/ntEvent.bmp")));
            //iconmap.insert(icon_pair(nodeinfotype(NT_TAG, EVENT_TYPE_WITH_TIME_VAL), QIcon(":icon/icon/ntEventAnalog.bmp")));
            //iconmap.insert(icon_pair(nodeinfotype(NT_TAG, EVENT_TYPE_ALARM), QIcon(":icon/icon/ntEvent.bmp")));
            // iconmap.insert(icon_pair(nodeinfotype(NT_TAG,EVENT_TYPE_OSC), QIcon(":icon/icon/ntYear.bmp")));

            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_DISCRET), QIcon(":icon/icon/ntDiscret.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_NUM32), QIcon(":icon/icon/ntLongWord.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_DOUBLE), QIcon(":icon/icon/ntReal.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_UNUM32), QIcon(":icon/icon/ntLongWord.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_NUM8), QIcon(":icon/icon/ntSmallInt.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_UNUM16), QIcon(":icon/icon/ntWord.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_NUM16), QIcon(":icon/icon/ntShortInt.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_UNUM8), QIcon(":icon/icon/ntByte.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_FLOAT), QIcon(":icon/icon/ntSingle.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_NUM8), QIcon(":icon/icon/ntChar.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_TEXT), QIcon(":icon/icon/ntText.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_TAG, TYPE_TM), QIcon(":icon/icon/ntDT.bmp")));


            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_SYSTEM), QIcon(":icon/icon/ntOSystem.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_SYSTEMVAR), QIcon(":icon/icon/ntOSysVar.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_SYSTEMCOUNT), QIcon(":icon/icon/ntOServCount.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_SYSTEMREPORT), QIcon(":icon/icon/ntOReport.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_SYSTEMREPORTCOUNT), QIcon(":icon/icon/ntOReportCnt.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_NET), QIcon(":icon/icon/ntOnet.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_OPC), QIcon(":icon/icon/ntOOPC.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_DDE), QIcon(":icon/icon/ntODDE.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_MODBUS), QIcon(":icon/icon/ntOModbus.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_KOYO), QIcon(":icon/icon/ntODKoy.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_LGKA), QIcon(":icon/icon/ntOLogika.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_MMS), QIcon(":icon/icon/ntMMS.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_GROUP, NS_GROUP_IEC60870), QIcon(":icon/icon/ntIEC60870.bmp")));           


            iconmap.insert(icon_pair(nodeinfotype(NT_ATAG, 0), QIcon(":icon/icon/ntTT.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_ROOT, 0), QIcon(":icon/icon/cdtmeta.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_HOME, 0), QIcon(":icon/icon/cdtHomeList.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_REPLIST, 0), QIcon(":icon/icon/cdtReportList.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_TRENDLIST, 0), QIcon(":icon/icon/cdtTrendList.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_MESSLIST, 0), QIcon(":icon/icon/cdtMessageList.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_REPHEADER, 0), QIcon(":icon/icon/cdtReportHeader.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_TRENDHEADER, 0), QIcon(":icon/icon/cdtTrendHeader.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_MESSHEADER, 0), QIcon(":icon/icon/cdtMessageHeader.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_REPARR, 0), QIcon(":icon/icon/cdtReportArr.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_TRENDARR, 0), QIcon(":icon/icon/cdtTrendArr.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_MESSARR, 0), QIcon(":icon/icon/cdtMessageArr.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_UNIT, 0), QIcon(":icon/icon/cdtunit.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_TREND, 0), QIcon(":icon/icon/cdttrend.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_MF_MESSAGE, 0), QIcon(":icon/icon/cdtmsgtag.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_JOURNAL, 0), QIcon(":icon/icon/ntAlarmTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_ALARM, 0), QIcon(":icon/icon/ntActiveAlarmTable.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_FINDER, 0), QIcon(":icon/icon/ntFinder.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_ACCESSRULES, 0), QIcon(":icon/icon/ntAccessRules.bmp")));
            iconmap.insert(icon_pair(nodeinfotype(NT_UTIL_CLIENTS, 0), QIcon(":icon/icon/ntClients.bmp")));

            rangmap.insert(noderang_pair(NT_ROOT,                   RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_SERVERS_NOTAVAIL_R, RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_SERVERS_AVAIL_R,   RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_SERVERS_NOTAVAIL,  RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_SERVERS_AVAIL,     RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_GROUPS,            RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_AGROUPS,           RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_GROUPS,            RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_USERS,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_ACCESSRULES,       RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_FINDER,            RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTILGROUP,              RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_MAINTABLE,         RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_GROUPTABLE,        RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_DEBUG,               RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_REGISTRY,            RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_VALCH,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_COMMAND,           RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_JOURNAL,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_ALARM,       RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_JOURNAL,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_ACCESSRULES,       RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_UTIL_CLIENTS,                RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_JOURNAL,                  RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_COMMAND,                RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_REGISTRY,                    RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_LOG,                    RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_NODEF,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_ROOT,                RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_HOME,                RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_REPLIST,             RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_TRENDLIST,           RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_MESSLIST,            RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_ROOT_SERVICES,          RANG_NODE_TYPE_0));
            //?????????
            rangmap.insert(noderang_pair(NT_MF_REPHEADER,           RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_TRENDHEADER,         RANG_NODE_TYPE_0));
            rangmap.insert(noderang_pair(NT_MF_MESSHEADER,          RANG_NODE_TYPE_0));


            rangmap.insert(noderang_pair(NT_GROUP,                  RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_AGROUP,                 RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_MF_REPARR,              RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_MF_TRENDARR,            RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_MF_MESSARR,             RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_USER,                   RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_ACCESSRULE,             RANG_NODE_TYPE_1));
            rangmap.insert(noderang_pair(NT_SERVICE,                RANG_NODE_TYPE_1));

            rangmap.insert(noderang_pair(NT_TAG,                    RANG_NODE_TYPE_2));
            rangmap.insert(noderang_pair(NT_ATAG,                   RANG_NODE_TYPE_2));
            rangmap.insert(noderang_pair(NT_MF_UNIT,                RANG_NODE_TYPE_2));
            rangmap.insert(noderang_pair(NT_MF_TREND,               RANG_NODE_TYPE_2));
            rangmap.insert(noderang_pair(NT_MF_MESSAGE,             RANG_NODE_TYPE_2));
            iconinit = true;}

        QIcon uiwidgetitem::stickicon(const QIcon& val1, const QIcon& val2) {
            QSize qsz1(30, 30);
            QSize qsz2(15, 30);
            qsz1 = val1.actualSize(qsz1);
            qsz2 = val2.actualSize(qsz2);
            QPixmap pixm1 = val1.pixmap(qsz1);
            QPixmap pixm2 = val2.pixmap(qsz2);

            int _height = (qsz1.height() > qsz2.height()) ? qsz1.height() : qsz2.height();
            int _width = (qsz1.width() + qsz2.width());

            QPixmap newpxm(_width, _height);
            QPainter qptmp(&newpxm);

            qptmp.drawPixmap(0, 0, pixm1);
            qptmp.drawPixmap(qsz1.width(), 0, pixm2);
            qptmp.end();
            return QIcon(newpxm);}

        QIcon uiwidgetitem::notloadicon(const QIcon& val) {
            QSize qsz(30, 30);
            qsz = val.actualSize(qsz);
            QPixmap pixm = val.pixmap(qsz);
            int _height = qsz.height();
            int _width = qsz.width();
            QPixmap newpxm(_width, _height);
            QPainter qptmp(&newpxm);
            qptmp.drawPixmap(0, 0, pixm);
            qptmp.setPen(QColor::fromRgb(255, 0, 0, 255));
            qptmp.drawLine(0, 0, 8, 8);
            qptmp.drawLine(0, 8, 8, 0);
            qptmp.drawEllipse(2, 2, 4, 4);
            qptmp.end();
            return QIcon(newpxm);};

        uiwidgetitem::uiwidgetitem(QTreeWidget *view, nodetype ntp) :
        QTreeWidgetItem(view) , key_(0), nodeinfo_("", ntp), strciteria_(""),
        filtertype_(0), viewtype_(tvcascade), isloaded_(false), loadless_(false)  {
            regist();
            virtualparent_ = 0;
            treewidgets_ = 0;
            registryfilter_ = 0;
            initicon();}

        uiwidgetitem::uiwidgetitem(uiwidgetitem *parent, indx itid, nodetype ntp, tagtype ttp) :
        QTreeWidgetItem(parent) , key_(itid), nodeinfo_("", ntp, ttp), strciteria_(""),
        filtertype_(0), viewtype_(tvcascade), isloaded_(false), loadless_(false)  {
            regist();
            virtualparent_ = parent;
            regist_in_parent();
            isloaded(false);
            initicon();}

        uiwidgetitem::uiwidgetitem(QTreeWidget *parent, uiwidgetitem *virtparent, indx itid, nodetype ntp, tagtype ttp) :
        QTreeWidgetItem(parent), key_(itid), nodeinfo_("", ntp, ttp), strciteria_(""),
        filtertype_(0), viewtype_(tvcascade), isloaded_(false), loadless_(false) {
            regist();
            virtualparent_ = virtparent;
            regist_in_parent();
            isloaded(false);
            initicon();}

        uiwidgetitem::uiwidgetitem(uiwidgetitem *parent, indx itid, name_with_type nwt) :
        QTreeWidgetItem(parent) , key_(itid), nodeinfo_(nwt), strciteria_(""),
        filtertype_(0), viewtype_(tvcascade), isloaded_(false), loadless_(false)  {
            regist();
            virtualparent_ = parent;
            regist_in_parent();
            settext();
            isloaded(false);
            initicon();}

        uiwidgetitem::uiwidgetitem(QTreeWidget *parent, uiwidgetitem *virtparent, indx itid, name_with_type nwt) :
        QTreeWidgetItem(parent), key_(itid), nodeinfo_(nwt), strciteria_(""),
        filtertype_(0), viewtype_(tvcascade), isloaded_(false), loadless_(false) {
            regist();
            virtualparent_ = virtparent;
            regist_in_parent();
            settext();
            isloaded(false);
            initicon();}

        uiwidgetitem::~uiwidgetitem() {
            clear();}

        void   uiwidgetitem::settext() {
            if ((ismeta()) || (nodetp() == NT_USER) || (nodetp() == NT_ACCESSRULE))
                setText(0, QString::fromUtf8(nodeinfo_.name().c_str(), nodeinfo_.name().size()));
            else
                setText(0, qtstr_from_str_loc((nodetp() == NT_TAG) ? retremoved_namespace_delimit(nodeinfo_.name()) : nodeinfo_.name() , intf() ? intf()->locale() : NS_CODPAGE_UTF8));}

        void uiwidgetitem::regist_in_parent() {
            if (virtualparent_) {
                if (virtualparent_->child_set.find(key()) != virtualparent_->child_set.end())
                    virtualparent_->child_set[key()] = this;
                else
                    virtualparent_->child_set.insert(indx_widgit_pair(key(), this));
                intf_ = virtualparent_->intf_;
                treewidgets_ = virtualparent_->treewidgets();
                viewtype_ = virtualparent_->viewtype_;
                registryfilter_ = virtualparent_->registryfilter_;
                loadless_ = (virtualparent_->nodetp() == NT_UTIL_FINDER);}}

        void uiwidgetitem::unregist_in_parent() {
            if ((virtualparent_) && (!virtualparent_->child_set.empty())) {
                if (virtualparent_->child_set.find(key()) != virtualparent_->child_set.end())
                    virtualparent_->child_set.erase(key());}}

        void uiwidgetitem::create_child(const iteminfo_pair& pairpack) {
            QTreeWidget* parenttmp = dynamic_cast<QTreeWidget*> (real_parent_for_this_child());
            if (!(*this)[pairpack.first]) {
                (!parenttmp) ? new uiwidgetitem(this, pairpack.first, pairpack.second) :
                        new uiwidgetitem(parenttmp, this, pairpack.first, pairpack.second);}}

        QIcon uiwidgetitem::icon(nodeinfotype nif) {
            num64 tmp = nif;
            tmp = tmp & 0xFFFFFFFF;
            nif.setbasis(tmp);
            icon_map::iterator it = iconmap.find(nif);
            if (it != iconmap.end())
                return  (it->second) ;
            tmp = tmp & 0xFFFF;
            nif.setbasis(tmp);
            it = iconmap.find(nif);
            if (it != iconmap.end())
                return  (it->second);
            return *nillIcon;}

        void uiwidgetitem::initicon() {
            QIcon tmp = icon(infotype());
            if (isfiltered()) {
                tmp = stickicon(tmp, *filterIcon);};
            if (!isloaded()  && (!((nodetp() == NT_UTIL_FINDER) || (nodetp() == NT_UTIL_MAINTABLE) ||
                                   (nodetp() == NT_UTIL_GROUPTABLE)))) tmp = notloadicon(tmp);
            setIcon(0, tmp);}

        uiwidgetitem* uiwidgetitem::operator[](indx id) {
            indx_widgit_map::iterator it = child_set.find(id);
            return (it == child_set.end()) ? 0 : (uiwidgetitem*) it->second;}

        bool uiwidgetitem::isfiltered() const {
            return ((strciteria_.size() > 0) && ((nodetp() == NT_ROOT_GROUPS)  ||
                                                 (nodetp() == NT_GROUP) ||  (nodetp() == NT_ROOT_AGROUPS)  ||
                                                 (nodetp() == NT_AGROUP) || (nodetp() == NT_ROOT_USERS)
                                                 || (nodetp() == NT_UTIL_FINDER) || (nodetp() == NT_UTIL_MAINTABLE) ||
                                                 (nodetp() == NT_UTIL_GROUPTABLE)
                                                 ))  ? true : false;}

        void uiwidgetitem::loadchlids(const iteminfo_map& srcmap) {

            rang(nodetp());
            switch (nodetp()) {

                case NT_ROOT_NODEF:{
                    if (intf()->state() == adminintf::disconnected) {
                        nodetp(intf()->islocal() ? NT_ROOT_SERVERS_NOTAVAIL : NT_ROOT_SERVERS_NOTAVAIL_R);
                        setText(0, qtstr_translate(QString::fromStdString(intf()->named())));}
                    else {
                        nodetp(intf()->islocal() ? NT_ROOT_SERVERS_AVAIL : NT_ROOT_SERVERS_AVAIL_R);
                        setText(0, qtstr_translate(QString::fromStdString(intf()->named())));}
                    loadchlids(srcmap);
                    return;}


                case NT_ROOT_SERVERS_AVAIL:
                case NT_ROOT_SERVERS_AVAIL_R:{
                    setText(0, qtstr_translate(QString::fromStdString(intf()->named())));

                    uiwidgetitem* ch;
                    if (!(*this)[0]) {
                        ch = new uiwidgetitem(this, 0, NT_ROOT_GROUPS);
                        ch->setText(0, qtstr_translate("maintree.sourse"));}

                    if (!(*this)[1]) {
                        ch = new uiwidgetitem(this, 1, NT_ROOT_AGROUPS);
                        ch->setText(0, qtstr_translate("maintree.alarmsourse"));}

                    if (!(*this)[3]) {
                        ch = new uiwidgetitem(this, 3, NT_ROOT_ACCESSRULES);
                        ch->setText(0, qtstr_translate("maintree.rulesourse"));}

                    if (!(*this)[2]) {
                        ch = new uiwidgetitem(this, 2, NT_ROOT_USERS);
                        ch->setText(0, qtstr_translate("maintree.usersourse"));}

                    if (!(*this)[6]) {
                        ch = new uiwidgetitem(this, 6, NT_UTIL_FINDER );
                        ch->setText(0, qtstr_translate("maintree.finder"));}

                    if (!(*this)[4]) {
                        ch = new uiwidgetitem(this, 4, NT_MF_ROOT);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[7]) {
                        ch = new uiwidgetitem(this, 7, NT_ROOT_SERVICES);
                        ch->setText(0, qtstr_translate("maintree.services"));}

                    if (!(*this)[5]) {
                        ch = new uiwidgetitem(this, 5, NT_UTILGROUP);
                        ch->loadchlids(srcmap);}

                    isloaded(true);

                    break;}

                case NT_ROOT_SERVERS_NOTAVAIL:{
                    setText(0, qtstr_translate("maintree.local"));
                    isloaded(true);
                    break;}

                case NT_UTILGROUP:{
                    setText(0, qtstr_translate("maintree.debug"));

                    isloaded(true);

                    uiwidgetitem* ch;
                    if (!(*this)[0]) {
                        ch = new uiwidgetitem(this, 0, NT_UTIL_MAINTABLE);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[1]) {
                        ch = new uiwidgetitem(this, 1, NT_UTIL_GROUPTABLE);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[2]) {
                        ch = new uiwidgetitem(this, 2, NT_UTIL_REGISTRY);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[3]) {
                        ch = new uiwidgetitem(this, 3, NT_UTIL_ACCESSRULES);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[4]) {
                        ch = new uiwidgetitem(this, 4, NT_UTIL_CLIENTS);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[5]) {
                        ch = new uiwidgetitem(this, 5, NT_UTIL_DEBUG);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[6]) {
                        ch = new uiwidgetitem(this, 6, NT_UTIL_COMMAND);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[7]) {
                        ch = new uiwidgetitem(this, 7, NT_UTIL_JOURNAL);
                        ch->loadchlids(srcmap);}

                    if (!(*this)[8]) {
                        ch = new uiwidgetitem(this, 8, NT_UTIL_ALARM);
                        ch->loadchlids(srcmap);}

                    break;}


                case NT_UTIL_GROUPTABLE:{
                    setText(0, qtstr_translate("maintree.groups"));
                    isloaded(true);
                    break;}

                case NT_UTIL_MAINTABLE:{
                    setText(0, qtstr_translate("maintree.maintab"));
                    isloaded(true);
                    break;}

                case NT_UTIL_DEBUG:{
                    setText(0, qtstr_translate("maintree.log"));
                    isloaded(true);
                    break;}

                case NT_UTIL_ACCESSRULES:{
                    setText(0, qtstr_translate("maintree.accessrules"));
                    isloaded(true);
                    break;}

                case NT_UTIL_CLIENTS:{
                    setText(0, qtstr_translate("maintree.clients"));
                    isloaded(true);
                    break;}

                case NT_UTIL_REGISTRY:{
                    setText(0, qtstr_translate("maintree.regapp"));
                    isloaded(true);
                    break;}

                case NT_UTIL_COMMAND:{
                    setText(0, qtstr_translate("maintree.command"));
                    isloaded(true);
                    break;}

                case NT_UTIL_JOURNAL:{
                    setText(0, qtstr_translate("maintree.alarm"));
                    isloaded(true);
                    break;}

                case NT_UTIL_ALARM:{
                    setText(0, qtstr_translate("maintree.activealarm"));
                    isloaded(true);
                    break;}



                case NT_MF_ROOT:{
                    setText(0, qtstr_translate("metaclient.meta"));

                    isloaded(true);
                    uiwidgetitem* ch;

                    if (!(*this)[0]) {
                        ch = new uiwidgetitem(this, 0, NT_MF_HOME);
                        ch->setText(0, qtstr_translate("metaclient.homelist"));}

                    if (!(*this)[1]) {
                        ch = new uiwidgetitem(this, 1, NT_MF_REPLIST);
                        ch->setText(0, qtstr_translate("metaclient.reportlist"));}

                    if (!(*this)[2]) {
                        ch = new uiwidgetitem(this, 2, NT_MF_TRENDLIST);
                        ch->setText(0, qtstr_translate("metaclient.trendlist"));}

                    if (!(*this)[3]) {
                        ch = new uiwidgetitem(this, 3, NT_MF_MESSLIST);
                        ch->setText(0, qtstr_translate("metaclient.messagelist"));}
                    break;}

                default:{
                    if (nodetp_canchild(nodetp())) {
                        if ((nodetp_is_meta(nodetp())) ||
                                (nodetp() == NT_ROOT_GROUPS) ||
                                (nodetp() == NT_ROOT_AGROUPS) ||
                                (nodetp() == NT_ROOT_USERS) ||
                                (nodetp() == NT_ROOT_ACCESSRULES) ||
                                (nodetp() == NT_GROUP) ||
                                (nodetp() == NT_AGROUP) ||
                                (nodetp() == NT_ROOT_SERVICES) ||
                                (nodetp() == NT_UTIL_FINDER)) {

                            load_chlids(srcmap);
                            isloaded(true);}}}}}

        void uiwidgetitem::load_chlids(const iteminfo_map& srcmap) {

            rang(nodetp());
            indx_set needdelset;

            QTreeWidget* parenttmp = dynamic_cast<QTreeWidget*> (real_parent_for_this_child());

            if (parenttmp) {
                parenttmp->clear();}

            for (int i = 0; i < childCount(); i++) {
                if (srcmap.find(((uiwidgetitem*) child(i))->key()) == srcmap.end())
                    needdelset.insert(((uiwidgetitem*) child(i))->key());}

            for (iteminfo_map::const_iterator it = srcmap.begin(); it != srcmap.end(); ++it ) {
                create_child(*it);}

            for (indx_set::iterator it = needdelset.begin(); it != needdelset.end(); ++it) {
                if ((*this)[*it]) delete (*this)[*it];}}

        void uiwidgetitem::loadfindedchilds(const  iteminfo_map& srcmap) {

            rang(NT_UTIL_FINDER);
            clear_child();
            QTreeWidget* parenttmp = (tvcascade == viewtype_) ? treewidgets_->find(1)->second : 0;

            if (parenttmp) {
                parenttmp->clear();}

            for (iteminfo_map::const_iterator it = srcmap.begin(); it != srcmap.end(); ++it ) {
                create_child(*it);}}

        std::string uiwidgetitem::filter() const {
            if (!nodetp_canchild(nodetp())) return "";
            if (registryfilter()) {
                if (registryfilter()->find(nodetp()) != registryfilter()->end()) {
                    ind_filter_map* tmpmap = &registryfilter()->find(nodetp())->second;
                    if (tmpmap->find(key()) != tmpmap->end())
                        return (tmpmap->find(key())->second);}}
            return "";}

        void uiwidgetitem::filter(std::string val) {
            if (!isfiltered()) return;
            if (registryfilter()) {
                if (registryfilter()->find(nodetp()) == registryfilter()->end()) {
                    if (val == "") return;
                    ind_filter_map tmpmap;
                    tmpmap.insert(ind_filter_pair(key(), val));
                    registryfilter()->insert(registry_filter_pair(nodetp(), tmpmap));}
                else {
                    ind_filter_map tmpmap = registryfilter()->find(nodetp())->second;
                    if (tmpmap.find(key()) == tmpmap.end()) {
                        if (val == "") return;
                        tmpmap.insert(ind_filter_pair(key(), val));}
                    else {
                        if (val == "") return;
                        tmpmap[key()] = val;}}}}

        void uiwidgetitem::strciteria(string val) {
            if (strciteria_ != val) {
                strciteria_ = val;
                filter(val);
                initicon();};}

        void uiwidgetitem::viewtype(kindview val) {
            if (viewtype_ != val) {
                if (virtualroot()) {
                    isloaded_ = false;
                    virtualroot()->clearallchild_where_rang_morethen0();
                    for (indx_widgit_map::iterator it = child_set.begin(); it != child_set.end(); ++it) {
                        if (it->second) ((uiwidgetitem*) it->second)->viewtype(val);}
                    viewtype_ = val;}}}

        void uiwidgetitem::rang(nodetype vl) {
            nodetype chval = nodetp_child_by_parent(vl);
            guiitemrang val = 0;
            if (rang(chval, false) > rang(vl, false))
                val = rang(chval, false);
            else
                val = rang(vl, false);
            if (((vl == NT_UTIL_FINDER) || ((virtualparent())
                                            && (virtualparent()->nodetp() == NT_UTIL_FINDER)))
                    && (tvcascade == viewtype_)) val = 1;
            for (int_treewidget_map::iterator it = treewidgets_->begin(); it != treewidgets_->end(); ++it) {
                if (it->second)
                    ((QWidget*) it->second->parent())->setVisible(it->first <= val);}}

        uiwidgetitem* uiwidgetitem::virtualroot() const {
            uiwidgetitem* result = (uiwidgetitem*)this;
            while (result->virtualparent()) {
                result = result->virtualparent();}
            return result;}

        uiwidgetitem* uiwidgetitem::intfroot() const {
            if (!intf()) return 0;
            uiwidgetitem* result = (uiwidgetitem*)this;
            while ((result->virtualparent()->intf())) {
                result = result->virtualparent();}
            return result;}

        guiitemrang uiwidgetitem::rang(nodetype val, bool ignorekind) const {
            if ((viewtype_ == tvline) && (!ignorekind)) return 0;
            return (rangmap.find(val) != rangmap.end()) ? rangmap.find(val)->second : 0;}

        QWidget* uiwidgetitem::real_parent_for_this_child() {
            nodetype chtype_ = nodetp_child_by_parent(nodetp());
            nodetype selftype_ = nodetp();
            return ((rang(chtype_, false) == rang(selftype_, false)) || (!nodetp_canchild(selftype_))) ?
                    (QWidget*)this : treewidget(rang(chtype_, false));}

        void uiwidgetitem::updateitem(const iteminfo_pair& pairpack) {
			nodeinfo_=pairpack.second;
            infotype(pairpack.second.typeex());
            settext();}

        void uiwidgetitem::updateitemex(const iteminfo_pair& pairpack, bool all ) {
            if (!all) {
                updateitem(pairpack);
                return;}
            else {
                indx_widgit_map maptmp;
                finditems(nodetp(), key(), maptmp);
                if (maptmp.size() > 0) {
                    for (indx_widgit_map::iterator it = maptmp.begin(); it != maptmp.end(); ++it)
                        ((uiwidgetitem*) (it->second))->updateitem(pairpack);}}}

        void uiwidgetitem::finditems(nodetype type, indx id, indx_widgit_map& map, uiwidgetitem* root) {
            map.clear();
            if (root == 0)
                root = intfroot();
            if (root != 0)
                root->finditems_internal(type, id, map);}

        void uiwidgetitem::finditems_internal(nodetype type, indx id, indx_widgit_map& map) {

            for (indx_widgit_map::iterator it = child_set.begin(); it != child_set.end(); ++it) {
                if (((((uiwidgetitem*) (it->second))->nodetp()) == (type))
                        || ((type == NT_TAG) && (((uiwidgetitem*) (it->second))->nodetp() == NT_ATAG))) {
                    indx_widgit_map::iterator it1 = child_set.find(id);
                    if (it1 != child_set.end()) {
                        map.insert(indx_widgit_pair(map.size(), it1->second));}
                    return;}
                else ((uiwidgetitem*) (it->second))->finditems_internal(type, id,  map);}}

        void  uiwidgetitem::additem_to_parent(nodetype type, indx id, indx_widgit_map& map) {
            map.clear();
            finditems(type, id, map);
            if (map.size() > 0) {
                for (indx_widgit_map::iterator it = child_set.begin(); it != child_set.end(); ++it) {
                    ((uiwidgetitem*) (it->second))->isloaded(false);}}
            if (tvcascade == viewtype()) map.clear();}

        void uiwidgetitem::clearallchild_where_rang_morethen0() {
            for (indx_widgit_map::iterator it = child_set.begin(); it != child_set.end(); ++it) {
                if (it->second) {
                    if (rang(((uiwidgetitem*) it->second)->nodetp(), true) < 1)
                        ((uiwidgetitem*) it->second)->clearallchild_where_rang_morethen0();
                    else {
                        clear_child();
                        break;}}};}

        void uiwidgetitem::clear() {
            clear_child();
            unregist_in_parent();}

        void uiwidgetitem::clear_child() {
            indx_widgit_map::iterator it = child_set.begin();
            while (it != child_set.end()) {
                delete it->second;
                it = child_set.begin();}}

        void  uiwidgetitem::removeex(bool all) {
            if (all) {
                indx_widgit_map maptmp;
                finditems(nodetp(), key(), maptmp);
                if (maptmp.size() > 0) {
                    for (indx_widgit_map::iterator it = maptmp.begin(); it != maptmp.end(); ++it)
                        if (((uiwidgetitem*) (it->second)) != this)
                            delete ((uiwidgetitem*) (it->second));}}
            delete this;}
}}