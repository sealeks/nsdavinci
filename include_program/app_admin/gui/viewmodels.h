/* 
 * File:   AbstractBaseModel.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 10 Декабрь 2009 г., 21:27
 */

#ifndef _ABSTRACTBASEMODEL_H
#define	_ABSTRACTBASEMODEL_H



#include <kernel/memfile.h>

#include <admin/adminintf.h>

#include "uiuitil.h"

#include <QtWidgets/QAbstractItemView>
#include <QSortFilterProxyModel>
#include <QtWidgets/QItemDelegate>
#include <QPainter>

namespace dvnci {
    namespace admin {

        class tagtabledelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class baseviewmodel : public QAbstractTableModel {
            ///// Q_OBJECT
        public:

            baseviewmodel( int loc_ = 0) : QAbstractTableModel() {
                loc = loc_;};

            virtual ~baseviewmodel() {};

            void interfs(adminintf_ptr intf) {
                mainintf = intf;}

            adminintf_ptr interf() {
                return mainintf;}

            void resetview() {
                beginResetModel();
                endResetModel();
            }

            Qt::ItemFlags flags(const QModelIndex &index) const {
                if (!index.isValid())  return 0;
                return ( Qt::ItemIsEnabled | Qt::ItemIsSelectable );}

            int rowCount(const QModelIndex &parent) const {
                return 0;}

            QItemDelegate* mbDelegate;
        protected:

            int loc;
            mutable adminintf_ptr mainintf;} ;

        class basetable : public baseviewmodel {

            Q_OBJECT
        public:
            basetable( int loc_ = 0) : baseviewmodel(loc_) {
                toprow_ = 0;
                visrow_ = 50;};

            virtual ~basetable() {};

            virtual void setindex(iteminfo_map& map_) {
                if ( map_.size() != count_) {
                    count_ = map_.size();
                beginResetModel();
                vect_.clear();
                endResetModel();
                }
                
                for (iteminfo_map::iterator it = map_.begin(); it != map_.end(); ++it) {
                    vect_.push_back(it->first);}}

            int rowCount(const QModelIndex &parent) const {
                return count_;}

            QModelIndex index(int row, int column,
                    const QModelIndex &parent = QModelIndex()) const {

                if (!hasIndex(row, column, parent))
                    return QModelIndex();

                if (!parent.isValid()) {
                    if (static_cast<size_t>(row) < count_) {
                        if (static_cast<int> (vect_.size()) > row) {
                            return createIndex(row, column, static_cast<int>(vect_[row]));}}}
                return QModelIndex();}

            virtual int  toprow() const {
                return toprow_;};

            virtual int  visrow() const {
                return visrow_;};

            virtual void toprow(int val) {
                toprow_ = val;};

            virtual void visrow(int val) {
                visrow_ = val;}

            virtual indx_set& getindex() {
                set_.clear();
                for (int i = toprow_; i < toprow_ + visrow_; i++) {
                    if (index(i, 0).internalId()!=npos)
                        set_.insert(index(i, 0).internalId());}
                return set_;}

        protected:
            int toprow_;
            int visrow_;
            indx_set set_;
            mutable indx_vect vect_;
            mutable indx cursor_;
            mutable indx count_;} ;


        ///////////////////////////////////////////////////////////////////////

        /////////////////////////////////////////////////////////

        const QRgb immi_valid_color = 0x1F831F;
        const QRgb immi_errortag_color = 0xCC0033;

        class tagsitemdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class tagsviewmodel : public basetable {
            Q_OBJECT
            typedef iconmapper<tagtype>      iconmaptype;
            typedef boost::shared_ptr<iconmaptype>  iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair     iconmappair;

        public:

            tagsviewmodel( int loc_ = 0);

            virtual ~tagsviewmodel() {
                delete mbDelegate;};
            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 12;};

        protected:
            iconmaptype_ptr    iconmap;} ;



        /////////////////////////////////////////////////////////

        class groupsitemdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class groupsviewmodel : public basetable {
            Q_OBJECT
            typedef iconmapper<appidtype>      iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;

        public:
            groupsviewmodel( int loc_ = 0) ;

            virtual ~groupsviewmodel() {};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 6;};

        protected:
            iconmaptype_ptr    iconmap;} ;



        /////////////////////////////////////////////////////////

        class accessrulesviewmodel : public basetable {

            Q_OBJECT
        public:
            accessrulesviewmodel( int loc_ = 0) : basetable(loc_) {
                mbDelegate = 0;};

            virtual ~accessrulesviewmodel() {};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 6;};} ;

        ///////////////////////////////////////////////////////////////////




        //////////////////////////////////////////////////////////////////

        //////////////////////////////////////////////////////////////////

        class livetableview : public baseviewmodel {

            Q_OBJECT
        public:
            livetableview( int loc_ = 0) : baseviewmodel(loc_) {};

            virtual ~livetableview() {};

            QModelIndex index(int row, int column,
                    const QModelIndex &parent ) const {

                if (!hasIndex(row, column, parent))
                    return QModelIndex();

                if (!parent.isValid()) {
                    if (static_cast<int> (rowCount(parent) > row)) {
                        return createIndex(row, column, row);}}
                return QModelIndex();}} ;



        const QRgb immi_fatal_error_color1 = 0xF02D0D;
        const QRgb immi_error_color1 = 0xF02D0D;
        const QRgb immi_warning_color1 = 0xEED237;
        const QRgb immi_message_color1 = 0x00B81E;

        /////////////////////////////////////////////////////////

        class debug_viewdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class debug_viewmodel :  public livetableview {
            Q_OBJECT
            typedef iconmapper<debuglvtype>    iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;
        public:
            debug_viewmodel( int loc_ = 0) ;

            virtual ~debug_viewmodel() {
                delete mbDelegate;};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 4;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->debug().count());}

        protected:
            iconmaptype_ptr    iconmap ;} ;


        /////////////////////////////////////////////////////////

        class journal_viewdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class journal_viewmodel :  public livetableview {
            Q_OBJECT
            typedef iconmapper<num32>          iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;

        public:
            journal_viewmodel( int loc_ = 0) ;

            virtual ~journal_viewmodel() {
                delete mbDelegate;};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 4;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->journal().count());}

        protected:
            iconmaptype_ptr    iconmap ;} ;


        /////////////////////////////////////////////////////////

        class command_viewdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class command_viewmodel :  public livetableview {

            Q_OBJECT
        public:
            command_viewmodel(int loc_ = 0) : livetableview(loc_) , _iconCommand(":icon/icon/jrcommand.png") {
                mbDelegate = new command_viewdelegate();};

            virtual ~command_viewmodel() {
                delete mbDelegate;};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 5;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->command().count());}
            QIcon  _iconCommand;} ;



        /////////////////////////////////////////////////////////

        const QRgb immi_accidnew_color = 0xFF3300;
        const QRgb immi_accidkvit_color = 0x9900FF;
        const QRgb immi_accidoff_color = 0x999999;
        const QRgb immi_alarmnew_color = 0xFF9900;
        const QRgb immi_alarmkvit_color = 0x9966FF;
        const QRgb immi_alarmoff_color = 0xCCCCCC;
        const QRgb immi_command_color = 0x009900;
        const QRgb immi_eventon_color = 0x003333;
        const QRgb immi_eventoff_color = 0x009999;
        const QRgb immi_timeevent_color = 0x009999;

        class alarm_viewdelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class alarm_viewmodel :  public livetableview {
            Q_OBJECT
            typedef iconmapper<num32>          iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;


        public:
            alarm_viewmodel( int loc_ = 0) ;

            virtual ~alarm_viewmodel() {
                delete mbDelegate;}

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 4;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->alarm().count());}

        protected:
            iconmaptype_ptr    iconmap;} ;



        /////////////////////////////////////////////////////////

        class regystry_viewmodel : public livetableview {
            Q_OBJECT
            typedef iconmapper<appidtype>     iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;

        public:

            regystry_viewmodel( int loc_ = 0) ;

            virtual ~regystry_viewmodel() {};

            QVariant data(const QModelIndex &index, int role) const;

            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 4;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->registry().count());}

        protected:
            iconmaptype_ptr    iconmap;} ;

        class client_viewmodel : public livetableview {
            typedef iconmapper<appidtype>     iconmaptype;
            typedef boost::shared_ptr<iconmaptype>    iconmaptype_ptr;
            typedef iconmaptype::type_icon_pair       iconmappair;
            Q_OBJECT
        public:

            client_viewmodel( int loc_ = 0);

            virtual ~client_viewmodel() {};

            QVariant data(const QModelIndex &index, int role) const;
            QVariant headerData(int section, Qt::Orientation orientation,
                    int role = Qt::DisplayRole) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 5;};

            int rowCount(const QModelIndex &parent) const {
                return static_cast<int> (mainintf->client().count());}
        protected:
            iconmaptype_ptr    iconmap;} ;}}

#endif	/* _ABSTRACTBASEMODEL_H */

