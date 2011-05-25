#include "uiuitil.h"

namespace dvnci {
    namespace admin {
        using namespace std;

        string_translator* maintraslator__ = 0;
        bool maintraslatorinit__ = false;

        QString qtstr_translate(QString key) {
            try {
                if ((!maintraslator__) & !(maintraslatorinit__)) maintraslator__ = new string_translator("translator.properties");
                maintraslatorinit__ = true;}
            catch (...) {
                return key;
                maintraslatorinit__ = true;};
            if (!maintraslator__) return key;
            return maintraslator__->Get(key).trimmed();}

        QString qtstr_from_str_loc(string val, int loc) {
            switch (loc) {
                case NS_CODPAGE_LOC8:{
                    return QString::fromLocal8Bit(val.c_str(), val.size());
                    break;};
                case NS_CODPAGE_UTF8:{
                    return QString::fromUtf8(val.c_str(), val.size());
                    break;};}
            return QString::fromStdString(val);}

        QString qtstr_from_str_utf8(string val) {
            return QString::fromUtf8(val.c_str(), val.size());}

        string str_from_qtstr_loc(QString val, int loc) {
            string res;
            switch (loc) {
                case NS_CODPAGE_LOC8:{
                    res = val.toLocal8Bit().data();
                    return res;
                    break;};
                case NS_CODPAGE_UTF8:{
                    res = val.toUtf8().data();
                    return res;
                    break;};}
            return val.toStdString();}

        string str_from_qtstr_utf8(QString val) {
            string res;
            res = val.toUtf8().data();
            return res;}

        string qt_gangelocale_str(string val, int inloc, int outloc) {
            if (inloc == outloc) return val;
            QString tmp = qtstr_from_str_loc(val, inloc);
            return str_from_qtstr_loc(tmp, outloc);}

        uitabdelegate::uitabdelegate(TypeEditor type, QObject *parent)
        : QItemDelegate(parent) {
            typeeditor = type;}

        uitabdelegate::~uitabdelegate() {
            /*delete lst;*/
        }

        void uitabdelegate::fillList(QString val, int vl) {
            lst.insert(delegate_propertyList_pair(val, vl));}

        QWidget *uitabdelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
                const QModelIndex &) const {
            QWidget *editor;

            switch (typeeditor) {
                case TComboBox:{
                    QComboBox* cmbox = new QComboBox(parent);
                    delegate_propertyList::const_iterator it = lst.begin();
                    while (it != lst.end()) {
                        cmbox->addItem(it->first, it->second);
                        ++it;}
                    return static_cast<QWidget *> (cmbox);
                    break;}
                case TRadioButton:{
                    QRadioButton* cradio = new QRadioButton(parent);
                    return static_cast<QWidget *> (cradio);
                    break;}
                case TCheckBox:{
                    QCheckBox* chbox = new QCheckBox(parent);
                    return static_cast<QWidget *> (chbox);
                    break;}
                case TButton:{
                    editor = static_cast<QToolButton *> (new QToolButton(parent));
                    break;}

                default:
                    editor = static_cast<QSpinBox *> (new QSpinBox(parent));}
            return editor;}

        void uitabdelegate::setEditorData(QWidget *editor,
                const QModelIndex &index) const {
            QVariant data = index.model()->data(index, Qt::DisplayRole);

            switch (typeeditor) {

                case TComboBox:{
                    QComboBox *cmbox = static_cast<QComboBox *> (editor);
                    cmbox->setCurrentIndex(cmbox->findText(data.toString()));
                    break;}

                case TRadioButton:{
                    QRadioButton *cradio = static_cast<QRadioButton *> (editor);
                    cradio->setChecked(data.toBool());
                    break;
                    break;}

                case TCheckBox:{
                    QCheckBox *chbox = static_cast<QCheckBox *> (editor);
                    chbox->setChecked(data.toBool());
                    break;}

                case TButton:{
                    break;}
                default:{
                    QSpinBox *spinBox = static_cast<QSpinBox *> (editor);
                    spinBox->setValue(data.toInt());}}}

        void uitabdelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                const QModelIndex &index) const {
            QVariant data;

            switch (typeeditor) {
                case TComboBox:{
                    QComboBox *cmbox = static_cast<QComboBox *> (editor);
                    data = cmbox->currentText();
                    break;}

                case TRadioButton:{
                    QRadioButton *cradio = static_cast<QRadioButton *> (editor);
                    data = cradio->isChecked();
                    break;}

                case TCheckBox:{
                    QCheckBox *checkb = static_cast<QCheckBox *> (editor);
                    data = checkb->isChecked();
                    break;}
                case TButton:{
                    break;}
                default:{
                    QSpinBox *spinBox = static_cast<QSpinBox *> (editor);
                    spinBox->interpretText();
                    data = spinBox->value();}}


            model->setData(index, data, Qt::EditRole);}

        void uitabdelegate::updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &/* index */) const {
            editor->setGeometry(option.rect);}

        string_translator::string_translator(string fn) {
            main_map = new wstringtranslate_map;
            Load(fn);}

        void string_translator::Load(string fn) {
            load_dictionary(*main_map);}

        string_translator::~string_translator() {
            delete main_map;}

        QString string_translator::Get(QString key_) {
            wstringtranslate_map::iterator it = main_map->find(key_);
            if (it != main_map->end()) {
                return qtstr_from_str_utf8(it->second);}
            return key_;}

}}