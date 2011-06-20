/*
 * File:   form_import.cpp
 * Author: Serg
 *
 * Created on 5 Апрель 2010 г., 13:09
 */

#include "form_import.h"

namespace dvnci {
    namespace admin {

        void importtabledelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
            if ((index.isValid())  && (index.sibling(index.row(), 0).isValid())) {
                bool active = (index.sibling(index.row(), 0).data(Qt::CheckStateRole) == Qt::Checked);
                QStyleOptionViewItem option_ = option;
                option_.font.setBold(active);
                if (active)  option_.palette.setColor(QPalette::Text, immi_on_color);
                else option_.palette.setColor(QPalette::Text, immi_off_color);
                if (active)  option_.palette.setColor(QPalette::Background, immi_onback_color);
                else option_.palette.setColor(QPalette::Background, immi_offback_color);
                QItemDelegate::paint(painter, option_, index);
                return;}
            QItemDelegate::paint(painter, option, index);}

        form_import::form_import() {
            widget.setupUi(this);
            widget.tagtable->setItemDelegate(imtagmod.delegate);
            widget.grouptable->setItemDelegate(imgroupmod.delegate);
            widget.agrouptable->setItemDelegate(imagroupmod.delegate);
            widget.usertable->setItemDelegate(imusermod.delegate);
            connect(widget.tagtable,  SIGNAL(clicked (const QModelIndex& ) ), this, SLOT(tagtableChanged( const QModelIndex&)));
            connect(widget.grouptable,  SIGNAL(clicked (const QModelIndex& )), this, SLOT(grouptableChanged(const QModelIndex& )));
            connect(widget.agrouptable,  SIGNAL(clicked (const QModelIndex& )), this, SLOT(agrouptableChanged(const QModelIndex& )));
            connect(widget.usertable,  SIGNAL(clicked (const QModelIndex& )), this, SLOT(usertableChanged(const QModelIndex& )));
            connect(widget.btndeletetags,   SIGNAL(clicked()), this, SLOT(btndeletetagClick()));
            connect(widget.btndeletegroups,   SIGNAL(clicked()), this, SLOT(btndeletegroupClick()));
            connect(widget.btndeleteagroups,   SIGNAL(clicked()), this, SLOT(btndeleteagroupClick()));
            connect(widget.btndeleteusers,   SIGNAL(clicked()), this, SLOT(btndeleteuserClick()));
            connect(widget.btnprefixtag,   SIGNAL(clicked()), this, SLOT(btnprefixtagClick()));
            setWindowTitle(qtstr_translate(QString::fromStdString("importform")));
            widget.revwritecheckbox->setText(qtstr_translate(QString::fromStdString("importform.rewr")));
            widget.btndeletetags->setToolTip(qtstr_translate(QString::fromStdString("importform.clear")));
            widget.btndeletegroups->setToolTip(qtstr_translate(QString::fromStdString("importform.clear")));
            widget.btndeleteagroups->setToolTip(qtstr_translate(QString::fromStdString("importform.clear")));
            widget.btndeleteusers->setToolTip(qtstr_translate(QString::fromStdString("importform.clear")));
            widget.btnprefixtag->setToolTip(qtstr_translate(QString::fromStdString("importform.pref")));
            widget.labeltag->setText(qtstr_translate(QString::fromStdString("importform.tag")));
            widget.labelgroup->setText(qtstr_translate(QString::fromStdString("importform.group")));
            widget.labelagroup->setText(qtstr_translate(QString::fromStdString("importform.agroup")));
            widget.labeluser->setText(qtstr_translate(QString::fromStdString("importform.user")));}

        form_import::~form_import() {
            disconnect(widget.tagtable,  SIGNAL(clicked (const QModelIndex& )));
            disconnect(widget.grouptable,  SIGNAL(itemChanged(const QModelIndex& )));
            disconnect(widget.agrouptable,  SIGNAL(itemChanged(const QModelIndex& )));
            disconnect(widget.usertable,  SIGNAL(itemChanged(Qconst QModelIndex& )));
            disconnect(widget.btndeletetags,   SIGNAL(clicked()));
            disconnect(widget.btndeletegroups,   SIGNAL(clicked()));
            disconnect(widget.btndeleteagroups,   SIGNAL(clicked()));
            disconnect(widget.btndeleteusers,   SIGNAL(clicked()));
            disconnect(widget.btnprefixtag,   SIGNAL(clicked()));}

        void form_import::changelocal(base_data* base_, int inloc, int outloc) {
            for (vect_tag_data::iterator it = base_->tags.begin(); it != base_->tags.end(); ++it) {
                it->name = qt_gangelocale_str(it->name, inloc, outloc);
                it->comment = qt_gangelocale_str(it->comment, inloc, outloc);
                it->bind = qt_gangelocale_str(it->bind, inloc, outloc);
                it->group = qt_gangelocale_str(it->group, inloc, outloc);
                it->onmsg = qt_gangelocale_str(it->onmsg, inloc, outloc);
                it->offmsg = qt_gangelocale_str(it->offmsg, inloc, outloc);
                it->almsg = qt_gangelocale_str(it->almsg, inloc, outloc);
                it->ue = qt_gangelocale_str(it->ue, inloc, outloc);}
            for (vect_group_data::iterator it = base_->groups.begin(); it != base_->groups.end(); ++it) {
                it->name = qt_gangelocale_str(it->name, inloc, outloc);}
            for (vect_agroup_data::iterator it = base_->agroups.begin(); it != base_->agroups.end(); ++it) {
                it->name = qt_gangelocale_str(it->name, inloc, outloc);}
            for (vect_user_data::iterator it = base_->users.begin(); it != base_->users.end(); ++it) {
                it->name = qt_gangelocale_str(it->name, inloc, outloc);}}

        bool form_import::execs(base_data* base_, std::string name_, nodetype tp) {
            bool result_ = false;
            QString dCaption = "Import";
            QString dDirectory = "";
            QString dFilter = "*.xml *.csv *.esd";
            switch (tp) {
                case NT_ROOT_SERVERS_AVAIL:{
                    dFilter = "*.xml";
                    typeimport = importAll;
                    break;}
                case NT_ROOT_SERVERS_AVAIL_R:{
                    dFilter = "*.xml";
                    typeimport = importAll;
                    break;}
                case NT_ROOT_GROUPS:{
                    dFilter = "*.xml *.csv";
                    typeimport = importCustom;
                    break;}
                case NT_ROOT_AGROUPS:{
                    dFilter = "*.xml";
                    typeimport = importAGroup;
                    break;}
                case NT_ROOT_USERS:{
                    dFilter = "*.xml";
                    typeimport = importUser;
                    break;}
                case NT_GROUP:{
                    typeimport = importCustom;
                    break;}
                default: return false;}

            QString tmp_dir = QFileDialog::getOpenFileName(0, dCaption, dDirectory, dFilter);
            if (tmp_dir != "") {
                num64 numcriteria = 0;
                imtagmod.setPrefix("");
                if (gettipeimport(tmp_dir.toStdString()) == TIPE_NS_IMPORT_ESD) {
                    if (!esdfilter.execs(numcriteria)) {
                        return false;}}
                widget.tagtable->setModel(0);
                widget.grouptable->setModel(0);
                widget.agrouptable->setModel(0);
                widget.usertable->setModel(0);
                base_->options = 0;
                int local_ = 0;
                if (tp != NT_GROUP) name_ = "";
                if (getimportdata(tmp_dir.toStdString(), *base_, local_, name_, numcriteria)) {

                    if (local_ != 0) changelocal(base_, local_);
                    widget.taglayout->setVisible(base_->tags.size() > 0);
                    widget.grouplayout->setVisible(base_->groups.size() > 0);
                    widget.agrouplayout->setVisible(base_->agroups.size() > 0);
                    widget.userlayout->setVisible(base_->users.size() > 0);
                    widget.revwritecheckbox->setCheckState(base_->options > 0 ? Qt::Checked : Qt::Unchecked );

                    imtagmod.setBase(base_);
                    imgroupmod.setBase(base_);
                    imusermod.setBase(base_);
                    imagroupmod.setBase(base_);
                    widget.tagtable->setModel(&imtagmod);
                    widget.grouptable->setModel(&imgroupmod);
                    widget.usertable->setModel(&imusermod);
                    widget.agrouptable->setModel(&imagroupmod);
                    exec();
                    result_ = (QDialog::Accepted == result());
                    imtagmod.removenoactive();
                    imgroupmod.removenoactive();
                    imusermod.removenoactive();
                    imagroupmod.removenoactive();
                    if (imtagmod.prefix() != "") imtagmod.mergeprefix();
                    base_->options = widget.revwritecheckbox->checkState() == Qt::Checked ?  CRITERIA_REWRITE : CRITERIA_NO_REWRITE;
                    return result_;};};
            widget.tagtable->setModel(0);
            widget.grouptable->setModel(0);
            widget.agrouptable->setModel(0);
            widget.usertable->setModel(0);
            return false;}

        void form_import::btndeletetagClick() {
            imtagmod.removenoactive();
            widget.tagtable->setModel(0);
            widget.tagtable->setModel(&imtagmod);
            widget.tagtable->viewport()->update();};

        void form_import::btndeletegroupClick() {
            imgroupmod.removenoactive();
            widget.grouptable->setModel(0);
            widget.grouptable->setModel(&imgroupmod);
            widget.grouptable->viewport()->update();};

        void form_import::btndeleteagroupClick() {
            imagroupmod.removenoactive();
            widget.agrouptable->setModel(0);
            widget.agrouptable->setModel(&imagroupmod);
            widget.agrouptable->viewport()->update();};

        void form_import::btndeleteuserClick() {
            imusermod.removenoactive();
            widget.usertable->setModel(0);
            widget.usertable->setModel(&imusermod);
            widget.usertable->viewport()->update();};

        void form_import::btnprefixtagClick() {
            std::string tmp = imtagmod.prefix();
            if (getStringForm.execs(tmp, "importform.addpreftitle", "importform.addpref")) {
                imtagmod.setPrefix(tmp);
                widget.tagtable->setModel(0);
                widget.tagtable->setModel(&imtagmod);
                widget.tagtable->viewport()->update();}};

        QVariant importtagmodel::data(const QModelIndex &index, int role) const {
            QVariant tmp;
            if (index.isValid()) {

                if ((role != Qt::DisplayRole) && (role != Qt::EditRole) && (role != Qt::CheckStateRole)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return QVariant();

                if  (role == Qt::CheckStateRole) {
                    switch (index.column()) {
                        case 0:{
                            tmp = (base_->tags.at(id).changeset != 0) ?  Qt::Checked:  Qt::Unchecked;
                            break;}
                        case 17:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->logged() ? Qt::Checked:  Qt::Unchecked;
                            break;}
                        case 18:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->onmsged() ? Qt::Checked:  Qt::Unchecked;
                            break;}
                        case 19:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->offmsged() ? Qt::Checked:  Qt::Unchecked;
                            break;}
                        case 20:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->alarmlevel() == altAccident ? Qt::Checked:  Qt::Unchecked;
                            break;}
                        case 21:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->alarmlevel() == altWarning ? Qt::Checked:  Qt::Unchecked;
                            break;}
                        default: return QVariant();}
                    return tmp;}
                else {
                    switch (index.column()) {
                        case 1:{
                            std::string tmpstr = prefix_ + base_->tags.at(id).name;
                            tmp = qtstr_from_str_loc(tmpstr, loc);
                            break;}
                        case 2:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).comment, loc);
                            break;}
                        case 3:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).bind, loc);
                            break;}
                        case 4:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).group, loc);
                            break;}
                        case 5:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).almsg, loc);
                            break;}
                        case 6:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).onmsg, loc);
                            break;}
                        case 7:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).offmsg, loc);
                            break;}
                        case 8:{
                            tmp = qtstr_from_str_loc(base_->tags.at(id).ue, loc);
                            break;}
                        case 9:{
                            tmp = to_str<double>(((tagstruct*) & base_->tags.at(id).tginfo)->logdb()).c_str();
                            break;}
                        case 10:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->mineu_str().c_str();
                            break;}
                        case 11:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->maxeu_str().c_str();
                            break;}
                        case 12:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->minraw_str().c_str();
                            break;}
                        case 13:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->maxraw_str().c_str();
                            break;}
                        case 14:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->type();
                            break;}
                        case 15:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->alarmcase();
                            break;}
                        case 16:{
                            tmp = ((tagstruct*) & base_->tags.at(id).tginfo)->alarmconst_str().c_str();
                            break;}
                        case 22:{
                            tmp = to_str(((tagstruct*) & base_->tags.at(id).tginfo)->devdb()).c_str();
                            break;}}}}
            return tmp;}

        Qt::ItemFlags importtagmodel::flags(const QModelIndex &index) const {
            if (!index.isValid())  return 0;
            if ((index.column() == 0) || ((index.column() >= 17)  && (index.column() <= 22)))
                return (  Qt::ItemIsUserCheckable |   Qt::ItemIsEnabled );
            else return ( Qt::ItemIsEditable | Qt::ItemIsEnabled  );
            ;}

        QVariant importtagmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("s"));
                case 1: return QVariant(qtstr_translate("maintable.name"));
                case 2: return QVariant(qtstr_translate("maintable.comment"));
                case 3: return QVariant(qtstr_translate("maintable.bind"));
                case 4: return QVariant(qtstr_translate("maintable.group"));
                case 5: return QVariant(qtstr_translate("maintable.almsg"));
                case 6: return QVariant(qtstr_translate("maintable.onmsg"));
                case 7: return QVariant(qtstr_translate("maintable.onmsg"));
                case 8: return QVariant(qtstr_translate("maintable.ue"));
                case 9: return QVariant(qtstr_translate("maintable.logdb"));
                case 10: return QVariant(qtstr_translate("maintable.mineu"));
                case 11: return QVariant(qtstr_translate("maintable.maxeu"));
                case 12: return QVariant(qtstr_translate("maintable.minraw"));
                case 13: return QVariant(qtstr_translate("maintable.maxraw"));
                case 14: return QVariant(qtstr_translate("maintable.type"));
                case 15: return QVariant(qtstr_translate("maintable.alcase"));
                case 16: return QVariant(qtstr_translate("maintable.alconst"));
                case 17: return QVariant(qtstr_translate("maintable.logged"));
                case 18: return QVariant(qtstr_translate("maintable.onmsg"));
                case 19: return QVariant(qtstr_translate("maintable.offmsg"));
                case 20: return QVariant(qtstr_translate("maintable.almsg"));
                case 21: return QVariant(qtstr_translate("maintable.alconstmsg"));
                case 22: return QVariant(qtstr_translate("maintable.devdb"));}

            return  QVariant();}

        bool importtagmodel::setData(const QModelIndex &index, const QVariant &val, int role) {
            if (!index.isValid()) return false;

            if (index.isValid()) {


                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return false;

                switch (index.column()) {
                    case 0:{
                        base_->tags.at(id).changeset = val.toBool() ? MASK_RT_EXPORT1: 0;
                        break;}
                    case 1:{
                        std::string tmp = str_from_qtstr_loc(val.toString(), loc);
                        if (prefix() != "") boost::replace_first(tmp, prefix(), "");
                        base_->tags.at(id).name = tmp ;
                        break;}
                    case 2:{
                        base_->tags.at(id).comment = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 3:{
                        base_->tags.at(id).bind = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 4:{
                        base_->tags.at(id).group = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 5:{
                        base_->tags.at(id).almsg = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 6:{
                        base_->tags.at(id).onmsg = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 7:{
                        base_->tags.at(id).offmsg = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 8:{
                        base_->tags.at(id).ue = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 9:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->logdb(str_to<double>(val.toString().toStdString()));
                        break;}
                    case 10:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->mineu(val.toString().toStdString());
                        break;}
                    case 11:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->maxeu(val.toString().toStdString());
                        break;}
                    case 12:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->minraw(val.toString().toStdString());
                        break;}
                    case 13:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->alarmconstr(val.toString().toStdString());
                        break;}
                    case 14:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->type(str_to<int>(val.toString().toStdString(), 0));
                        ;
                        break;}
                    case 15:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->alarmcase(str_to<int>(val.toString().toStdString(), 0));
                        ;
                        break;}
                    case 16:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->alarmconstr(val.toString().toStdString());
                        break;}
                    case 17:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->logged((val == Qt::Checked) ? 1: 0);
                        break;}
                    case 18:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->onmsged((val == Qt::Checked) ? 1: 0);
                        break;}
                    case 19:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->offmsged((val == Qt::Checked) ? 1: 0);
                        break;}
                    case 22:{
                        ((tagstruct*) & base_->tags.at(id).tginfo)->devdb(str_to<double>(val.toString().toStdString()));
                        break;}}}
            return true;}

        QModelIndex importtagmodel::index(int row, int column,
                const QModelIndex &parent ) const {
            if (!hasIndex(row, column, parent) || (base_ == NULL))
                return QModelIndex();

            if (!parent.isValid()) {

                if (static_cast<int> (base_->tags.size()) > row) {
                    if (column == 0) return createIndex(row, column, row);
                    else
                        return createIndex(row, column, row);}}
            return QModelIndex();}

        bool tagnoactive(tag_data& val) {
            return (val.changeset == 0);}

        void importtagmodel::removenoactive() {
            if (base_ == NULL) return;
            std::remove_if(base_->tags.begin(), base_->tags.end(), tagnoactive);}

        void importtagmodel::mergeprefix() {
            for (vect_tag_data::iterator it = base_->tags.begin(); it != base_->tags.end(); ++it)
                it->name = prefix_ + it->name;}

        ////////////////////////////////////////

        QVariant importgroupmodel::data(const QModelIndex &index, int role) const {
            QVariant tmp;
            if (index.isValid()) {

                if ((role != Qt::DisplayRole) && (role != Qt::EditRole) && (role != Qt::CheckStateRole)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return QVariant();

                if  (role == Qt::CheckStateRole) {
                    switch (index.column()) {
                        case 0:{
                            tmp = (base_->groups.at(id).changeset != 0) ?  Qt::Checked:  Qt::Unchecked;
                            break;}

                        default: return QVariant();}
                    return tmp;}
                else {
                    switch (index.column()) {
                        case 1:{
                            tmp = qtstr_from_str_loc(base_->groups.at(id).name, loc);
                            break;}}}}
            return tmp;}

        Qt::ItemFlags importgroupmodel::flags(const QModelIndex &index) const {
            if (!index.isValid())  return 0;
            if ((index.column() == 0))
                return (  Qt::ItemIsUserCheckable |   Qt::ItemIsEnabled );
            else return ( Qt::ItemIsEditable | Qt::ItemIsEnabled  );
            ;}

        QVariant importgroupmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("s"));
                case 1: return QVariant(qtstr_translate("grouptable.name"));}

            return  QVariant();}

        bool importgroupmodel::setData(const QModelIndex &index, const QVariant &val, int role) {
            if (!index.isValid()) return false;

            if (index.isValid()) {


                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return false;

                switch (index.column()) {
                    case 0:{
                        base_->groups.at(id).changeset = val.toBool() ? MASK_GR_EXPORT1: 0;
                        break;}
                    case 1:{
                        base_->groups.at(id).name = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
}}
            return true;}

        QModelIndex importgroupmodel::index(int row, int column,
                const QModelIndex &parent ) const {
            if (!hasIndex(row, column, parent) || (base_ == NULL))
                return QModelIndex();

            if (!parent.isValid()) {

                if (static_cast<int> (base_->groups.size()) > row) {
                    if (column == 0) return createIndex(row, column, row);
                    else
                        return createIndex(row, column, row);}}
            return QModelIndex();}

        bool groupnoactive(group_data& val) {
            return (val.changeset == 0);}

        void importgroupmodel::removenoactive() {
            if (base_ == NULL) return;
            std::remove_if(base_->groups.begin(), base_->groups.end(), groupnoactive);}


        ////////////////////////////////////////

        QVariant importagroupmodel::data(const QModelIndex &index, int role) const {
            QVariant tmp;
            if (index.isValid()) {

                if ((role != Qt::DisplayRole) && (role != Qt::EditRole) && (role != Qt::CheckStateRole)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return QVariant();

                if  (role == Qt::CheckStateRole) {
                    switch (index.column()) {
                        case 0:{
                            tmp = (base_->agroups.at(id).changeset != 0) ?  Qt::Checked:  Qt::Unchecked;
                            break;}

                        default: return QVariant();}
                    return tmp;}
                else {
                    switch (index.column()) {
                        case 1:{
                            tmp = qtstr_from_str_loc(base_->agroups.at(id).name, loc);
                            break;}}}}
            return tmp;}

        Qt::ItemFlags importagroupmodel::flags(const QModelIndex &index) const {
            if (!index.isValid())  return 0;
            if ((index.column() == 0))
                return (  Qt::ItemIsUserCheckable |   Qt::ItemIsEnabled );
            else return ( Qt::ItemIsEditable | Qt::ItemIsEnabled  );
            ;}

        QVariant importagroupmodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("s"));
                case 1: return QVariant(qtstr_translate("agrouptable.name"));}

            return  QVariant();}

        bool importagroupmodel::setData(const QModelIndex &index, const QVariant &val, int role) {
            if (!index.isValid()) return false;

            if (index.isValid()) {


                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return false;

                switch (index.column()) {
                    case 0:{
                        base_->agroups.at(id).changeset = val.toBool() ? MASK_AGR_EXPORT1: 0;
                        break;}
                    case 1:{
                        base_->agroups.at(id).name = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
}}
            return true;}

        QModelIndex importagroupmodel::index(int row, int column,
                const QModelIndex &parent ) const {
            if (!hasIndex(row, column, parent) || (base_ == NULL))
                return QModelIndex();

            if (!parent.isValid()) {

                if (static_cast<int> (base_->agroups.size()) > row) {
                    if (column == 0) return createIndex(row, column, row);
                    else
                        return createIndex(row, column, row);}}
            return QModelIndex();}

        bool agroupnoactive(agroup_data& val) {
            return (val.changeset == 0);}

        void importagroupmodel::removenoactive() {
            if (base_ == NULL) return;
            std::remove_if(base_->agroups.begin(), base_->agroups.end(), agroupnoactive);}


        ////////////////////////////////////////

        QVariant importusermodel::data(const QModelIndex &index, int role) const {
            QVariant tmp;
            if (index.isValid()) {

                if ((role != Qt::DisplayRole) && (role != Qt::EditRole) && (role != Qt::CheckStateRole)) return QVariant();
                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return QVariant();

                if  (role == Qt::CheckStateRole) {
                    switch (index.column()) {
                        case 0:{
                            tmp = (base_->users.at(id).changeset != 0) ?  Qt::Checked:  Qt::Unchecked;
                            break;}

                        default: return QVariant();}
                    return tmp;}
                else {
                    switch (index.column()) {
                        case 1:{
                            tmp = qtstr_from_str_loc(base_->users.at(id).name, loc);
                            break;}
                        case 2:{
                            tmp = qtstr_from_str_loc(base_->users.at(id).password, loc);
                            break;}
                        case 3:{
                            tmp = base_->users.at(id).accesslevel;
                            break;}}}}
            return tmp;}

        Qt::ItemFlags importusermodel::flags(const QModelIndex &index) const {
            if (!index.isValid())  return 0;
            if ((index.column() == 0))
                return (  Qt::ItemIsUserCheckable |   Qt::ItemIsEnabled );
            else return ( Qt::ItemIsEditable | Qt::ItemIsEnabled  );}

        QVariant importusermodel::headerData(int section, Qt::Orientation orientation,
                int role) const {

            if (orientation != Qt::Horizontal || role != Qt::DisplayRole)
                return QAbstractItemModel::headerData(section, orientation, role);
            switch (section) {
                case 0: return QVariant(qtstr_translate("s"));
                case 1: return QVariant(qtstr_translate("usertable.name"));
                case 2: return QVariant(qtstr_translate("usertable.password"));
                case 3: return QVariant(qtstr_translate("usertable.level"));}

            return  QVariant();}

        bool importusermodel::setData(const QModelIndex &index, const QVariant &val, int role) {
            if (!index.isValid()) return false;

            if (index.isValid()) {


                indx id = static_cast<indx>(index.internalId());
                if (((id == npos) && (index.column() > 0)) || (!base_)) return false;

                switch (index.column()) {
                    case 0:{
                        base_->users.at(id).changeset = val.toBool() ? MASK_USER_EXPORT1: 0;
                        break;}
                    case 1:{
                        base_->users.at(id).name = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 2:{
                        base_->users.at(id).password = str_from_qtstr_loc(val.toString(), loc) ;
                        break;}
                    case 3:{
                        base_->users.at(id).accesslevel = str_to<int>(val.toString().toStdString(), 0);
                        break;}}}
            return true;}

        QModelIndex importusermodel::index(int row, int column,
                const QModelIndex &parent ) const {
            if (!hasIndex(row, column, parent) || (base_ == NULL))
                return QModelIndex();

            if (!parent.isValid()) {

                if (static_cast<int> (base_->users.size()) > row) {
                    if (column == 0) return createIndex(row, column, row);
                    else
                        return createIndex(row, column, row);}}
            return QModelIndex();}

        bool usernoactive(user_data& val) {
            return (val.changeset == 0);}

        void importusermodel::removenoactive() {
            if (!base_) return;
            std::remove_if(base_->users.begin(), base_->users.end(), usernoactive);}}}



