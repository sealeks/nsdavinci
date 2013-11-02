/* 
 * File:   uiuitil.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 24 Ноябрь 2009 г., 16:46
 */

#ifndef _TABLEDELEGATE_H
#define	_TABLEDELEGATE_H



#include <kernel/constdef.h>
#include <kernel/utils.h>
#include <kernel/systemutil.h>

#include <admin/adminintf.h>

#include <QtWidgets/QItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QComboBox>
#include <QtGui>
#include <QString>

#include "RU_dict.h"

namespace dvnci {
    namespace admin {

        typedef std::pair<QString, int > delegate_propertyList_pair;
        typedef std::map<QString, int , std::less<QString>, std::allocator<delegate_propertyList_pair > > delegate_propertyList;


        QString qtstr_translate(QString key);
        QString qtstr_from_str_loc(std::string val, int loc = 0);
        std::string str_from_qtstr_loc(QString val, int loc = 0);
        QString qtstr_from_str_utf8(std::string val);
        std::string str_from_qtstr_utf8(QString val);
        std::string qt_gangelocale_str(std::string val, int inloc, int outloc = 0 );

        template <typename T>
        class iconmapper {
        public:

            typedef T                                                                                             indextype;
            typedef std::pair<indextype, QIcon>                                                                   type_icon_pair;
            typedef std::map<indextype, QIcon, std::less<indextype>, std::allocator<type_icon_pair > >            type_icon_map;
            typedef typename type_icon_map::const_iterator                                                        type_icon_constiterator;

            iconmapper(type_icon_pair* arr, std::size_t sz, QIcon def = QIcon()) {
                for (size_t i = 0; i < sz; i++) {
                    map_.insert(arr[i]);}
                deficon = def;}

            const QIcon & operator[](T id) const {
                type_icon_constiterator it = map_.find(id);
                return it != map_.end() ? (it->second) : deficon;}

        private:
            QIcon           deficon;
            type_icon_map   map_;} ;

        class uitabdelegate : public QItemDelegate {
            Q_OBJECT

        private:
            int typeeditor;
            delegate_propertyList lst;

        public:

            enum TypeEditor {
                TQSpinBox,
                TComboBox,
                TCheckBox,
                TRadioButton,
                TButton} ;

            uitabdelegate(TypeEditor type, QObject *parent = 0);
            ~uitabdelegate();
            void fillList(QString val, int vl);
            QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                    const QModelIndex &index) const;

            int _typeeditor() {
                return typeeditor;}

            int getval(QString val) {
                if (typeeditor == TComboBox) {
                    delegate_propertyList::const_iterator it = lst.find(val);
                    if (it != lst.end()) {
                        return it->second;}}
                return -1;}

            void setEditorData(QWidget *editor, const QModelIndex &index) const;
            void setModelData(QWidget *editor, QAbstractItemModel *model,
                    const QModelIndex &index) const;

            void updateEditorGeometry(QWidget *editor,
                    const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class string_translator {
        public:
            string_translator(std::string fn);
            QString Get(QString key_);
            virtual ~string_translator();

            QString qtstr_from_str_utf8(QString val) {
                std::string val1 = val.toStdString();
                return QString::fromUtf8(val1.c_str(), val1.size());}
        private:
            wstringtranslate_map* main_map;
            void Load(std::string fn);} ;
}}


#endif	/* _TABLEDELEGATE_H */

