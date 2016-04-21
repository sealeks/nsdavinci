/* 
 * File:   form_import.h
 * Author: Serg
 *
 * Created on 5 Апрель 2010 г., 13:09
 */

#ifndef _IMPORTFORM_H
#define	_IMPORTFORM_H

#include <kernel/memfile.h>

#include <admin/adminstruct.h>
#include <admin/adminintf.h>
#include <admin/importutil.h>


#include <QtWidgets/QFileDialog>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QTableWidgetItem>

#include "form_esdfilter.h"
#include "ui_form_import.h"
#include "form_getstring.h"
#include "uiuitil.h"

namespace dvnci {
    namespace admin {


        const QRgb immi_off_color = 0xBBBFAC;
        const QRgb immi_on_color = 0x24006B;
        const QRgb immi_offback_color = 0xFAFAFA;
        const QRgb immi_onback_color = 0xCCFFBF;

        class importtabledelegate : public QItemDelegate {
        public:
            void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;} ;

        class importtagmodel : public QAbstractTableModel {

            Q_OBJECT
        public:

            importtagmodel( int loc_ = 0) : QAbstractTableModel() {
                loc = loc_;
                delegate = new importtabledelegate();
                prefix_ = "";};

            virtual ~importtagmodel() {
                delete delegate;};

            void setloc(int loc_) {
                loc = loc_;}

            void setBase(base_data* _base_) {
                base_ = _base_;}

            base_data* base() {
                return base_;}

            virtual QVariant headerData(int section, Qt::Orientation orientation,
                    int role) const;
            virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

            virtual int rowCount(const QModelIndex &parent) const {
                return (base_ != NULL) ? base_->tags.size() : 0;}
            QModelIndex index(int row, int column,
                    const QModelIndex &parent ) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 24;};
            virtual Qt::ItemFlags flags(const QModelIndex &index) const;
            virtual bool setData(const QModelIndex &id, const QVariant &val, int role);
            void removenoactive();
            void mergeprefix();

            void setPrefix(std::string val) {
                prefix_ = val;}

            std::string prefix() {
                return prefix_;}

            importtabledelegate* delegate;
        protected:
            int loc;
            mutable base_data* base_;
            std::string prefix_;} ;

        class importgroupmodel : public QAbstractTableModel {

            Q_OBJECT
        public:

            importgroupmodel( int loc_ = 0) : QAbstractTableModel() {
                loc = loc_;
                delegate = new importtabledelegate();};

            virtual ~importgroupmodel() {
                delete delegate;};

            void setloc(int loc_) {
                loc = loc_;}

            void setBase(base_data* _base_) {
                base_ = _base_;}

            base_data* base() {
                return base_;}

            virtual QVariant headerData(int section, Qt::Orientation orientation,
                    int role) const;
            virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

            virtual int rowCount(const QModelIndex &parent) const {
                return (base_ != NULL) ? base_->groups.size() : 0;}
            QModelIndex index(int row, int column,
                    const QModelIndex &parent ) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 2;};
            virtual Qt::ItemFlags flags(const QModelIndex &index) const;
            virtual bool setData(const QModelIndex &id, const QVariant &val, int role);
            void removenoactive();
            importtabledelegate* delegate;
        protected:
            int loc;
            mutable base_data* base_;} ;

        class importagroupmodel : public QAbstractTableModel {

            Q_OBJECT
        public:

            importagroupmodel( int loc_ = 0) : QAbstractTableModel() {
                loc = loc_;
                delegate = new importtabledelegate();};

            virtual ~importagroupmodel() {
                delete delegate;};

            void setloc(int loc_) {
                loc = loc_;}

            void setBase(base_data* _base_) {
                base_ = _base_;}

            base_data* base() {
                return base_;}

            virtual QVariant headerData(int section, Qt::Orientation orientation,
                    int role) const;
            virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

            virtual int rowCount(const QModelIndex &parent) const {
                return (base_ != NULL) ? base_->agroups.size() : 0;}
            QModelIndex index(int row, int column,
                    const QModelIndex &parent ) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 2;};
            virtual Qt::ItemFlags flags(const QModelIndex &index) const;
            virtual bool setData(const QModelIndex &id, const QVariant &val, int role);
            void removenoactive();
            importtabledelegate* delegate;
        protected:
            int loc;
            mutable base_data* base_;} ;

        class importusermodel : public QAbstractTableModel {

            Q_OBJECT
        public:

            importusermodel( int loc_ = 0) : QAbstractTableModel() {
                loc = loc_;
                delegate = new importtabledelegate();};

            virtual ~importusermodel() {
                delete delegate;};

            void setloc(int loc_) {
                loc = loc_;}

            void setBase(base_data* _base_) {
                base_ = _base_;}

            base_data* base() {
                return base_;}

            virtual QVariant headerData(int section, Qt::Orientation orientation,
                    int role) const;
            virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

            virtual int rowCount(const QModelIndex &parent) const {
                return (base_ != NULL) ? base_->users.size() : 0;}
            QModelIndex index(int row, int column,
                    const QModelIndex &parent ) const;

            int columnCount(const QModelIndex &parent  = QModelIndex() ) const {
                return 4;};
            virtual Qt::ItemFlags flags(const QModelIndex &index) const;
            virtual bool setData(const QModelIndex &id, const QVariant &val, int role);
            void removenoactive();
            importtabledelegate* delegate;
        protected:
            int loc;
            mutable base_data* base_;} ;

        class form_import : public QDialog {

            Q_OBJECT
        public:
            enum TypeImport {
                importTag = 1, importGroup = 2 , importAGroup = 4, importUser = 8,  importCustom = 3, importAll = 15} ;

            enum ImportSource {
                importXml = 1, importCVC = 2 , importPLC = 3} ;
            form_import();
            virtual ~form_import();
            bool execs(base_data* base_, std::string name_ = "", nodetype tp = 0x02);
            static void changelocal(base_data* base_, int inloc, int outloc = 0);
        private:
            Ui::form_import widget;
            importtagmodel imtagmod;
            importgroupmodel imgroupmod;
            importusermodel imusermod;
            importagroupmodel imagroupmod;
            base_data* base_;
            TypeImport typeimport;
            form_esdfilter esdfilter;
            form_getstring getStringForm;

        public slots:

            void tagtableChanged( const QModelIndex& ind) {
                if ((ind.isValid()) && (ind.column() == 0)) widget.tagtable->viewport()->update();};

            void grouptableChanged( const QModelIndex& ind) {
                if ((ind.isValid()) && (ind.column() == 0)) widget.grouptable->viewport()->update();};

            void agrouptableChanged( const QModelIndex& ind) {
                if ((ind.isValid()) && (ind.column() == 0)) widget.agrouptable->viewport()->update();};

            void usertableChanged( const QModelIndex& ind) {
                if ((ind.isValid()) && (ind.column() == 0)) widget.usertable->viewport()->update();};
            void btndeletetagClick();
            void btndeletegroupClick();
            void btndeleteagroupClick();
            void btndeleteuserClick();
            void btnprefixtagClick();} ;}}


#endif	/* _IMPORTFORM_H */
