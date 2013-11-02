/* 
 * File:   uiwidgetitem.h
 * Author: Serg Alexeev sealeks@mail.ru
 *
 * Created on 26 Февраль 2010 г., 1:20
 */

#ifndef _NSWIDGETITEM_H
#define	_NSWIDGETITEM_H


#include <kernel/memfile.h>

#include <admin/adminintf.h>
#include <admin/factory.h>

#include "uiuitil.h"

#include <QtWidgets/QTreeWidgetItem>
#include <QIcon>
#include <QColor>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QtWidgets/QTreeWidget>


/*Класс итемса для представления дерева проекта,
 * содержит поля необходимые для хранения специфики,
 * отображаемой им сущности
 */

namespace dvnci {
    namespace admin {

        class uiwidgetitem;

        typedef int guiitemrang;

        const guiitemrang RANG_NODE_TYPE_0 = 0x0;
        const guiitemrang RANG_NODE_TYPE_1 = 0x1;
        const guiitemrang RANG_NODE_TYPE_2 = 0x2;
        const guiitemrang RANG_NODE_TYPE_3 = 0x3;
        const guiitemrang RANG_NODE_TYPE_4 = 0x4;

        typedef std::pair<indx, uiwidgetitem* > indx_widgit_pair;
        typedef std::map<indx, uiwidgetitem*, std::less<indx>, std::allocator<indx_widgit_pair > > indx_widgit_map;

        typedef std::pair<nodeinfotype, QIcon> icon_pair;
        typedef std::map<nodeinfotype , QIcon , std::less<nodeinfotype>, std::allocator<icon_pair > > icon_map;


        typedef std::pair<nodetype, guiitemrang> noderang_pair;
        typedef std::map<nodetype , guiitemrang , std::less<nodetype>, std::allocator<noderang_pair > > noderang_map;

        typedef std::pair<indx, QTreeWidget*> int_treewidget_pair;
        typedef std::map <indx , QTreeWidget* , std::less<indx>, std::allocator<int_treewidget_pair > > int_treewidget_map;

        typedef std::pair<indx, std::string> ind_filter_pair;
        typedef std::map <indx , std::string , std::less<indx>, std::allocator<ind_filter_pair > > ind_filter_map;

        typedef std::pair<nodetype, ind_filter_map> registry_filter_pair;
        typedef std::map <nodetype, ind_filter_map , std::less<nodetype>, std::allocator<registry_filter_pair > > registry_filter_map;

        typedef boost::shared_ptr<registry_filter_map> registry_filter_ptr;

        class uiwidgetitem : public QTreeWidgetItem {
        public:

            enum kindview {
                tvline, tvcascade} ;

            explicit uiwidgetitem(QTreeWidget  *view, nodetype ntp);
            explicit uiwidgetitem(uiwidgetitem *parent, indx itid, nodetype ntp, tagtype ttp = 0);
            explicit uiwidgetitem(QTreeWidget  *parent, uiwidgetitem *virtparent, indx itid, nodetype ntp, tagtype ttp = 0);
            explicit uiwidgetitem(uiwidgetitem *parent, indx itid, name_with_type nwt);
            explicit uiwidgetitem(QTreeWidget  *parent, uiwidgetitem *virtparent, indx itid, name_with_type nwt);
            virtual ~uiwidgetitem();

            static QIcon         icon(nodeinfotype nif);

            void                 loadchlids(const iteminfo_map& srcmap);
            void                 load_chlids(const iteminfo_map& srcmap);
            void                 loadfindedchilds(const iteminfo_map& srcmap);
            void                 updateitem(const iteminfo_pair& pairpack);
            void                 updateitemex(const iteminfo_pair& pairpack, bool all = true);
            void                 removeex(bool all = true);
            void                 additem_to_parent(nodetype type, indx id, indx_widgit_map& map);

            std::string          filter() const;
            void                 filter(std::string val);

            void                 nodetp(nodetype val) {
                if (nodeinfo_.typeex().node() != val) {
                    nodeinfo_.typeex(nodeinfotype(val, nodeinfo_.typeex().tgtype(), nodeinfo_.typeex().pttype()));
                    initicon();};}

            nodetype      nodetp() const {
                return nodeinfo_.typeex().node();}

            void                 tgtype(tagtype val) {
                if (nodeinfo_.typeex().tgtype() != val) {
                    nodeinfo_.typeex(nodeinfotype(nodeinfo_.typeex().node(), val, nodeinfo_.typeex().pttype()));
                    initicon();};}

            tagtype       tgtype() const {
                return nodeinfo_.typeex().tgtype();}

            void                 aptype(appidtype val) {
                if (nodeinfo_.typeex().pttype() != val) {
                    nodeinfo_.typeex(nodeinfotype(nodeinfo_.typeex().node(), nodeinfo_.typeex().tgtype(), val));
                    initicon();};}

            appidtype     aptype() const {
                return nodeinfo_.typeex().pttype();}

            void                 infotype(nodeinfotype val) {
                if (nodeinfo_.typeex() != val) {
                    nodeinfo_.typeex(val);
                    initicon();};}

            nodeinfotype  infotype() const {
                return nodeinfo_.typeex();}

            entity_pair   infonode() const {
                return entity_pair(key(), infotype());}

            registry_filter_map* registryfilter() const {
                return registryfilter_;};

            void                 registryfilter(registry_filter_map* val) {
                registryfilter_ = val;};

            indx          key() const {
                return key_;}

            void                 key(indx val) {
                key_ = val;}

            std::string          strciteria() const {
                return strciteria_;};
            void                 strciteria(std::string val );

            nodetype      filtertype() const {
                return filtertype_;}

            void                 filtertype(nodetype val) {
                if (filtertype_ != val) {
                    filtertype_ = val;
                    initicon();};}

            adminintf_ptr        intf() const {
                return intf_;}

            void                 intf(adminintf_ptr  val) {
                intf_ = val;}

            kindview             viewtype() const {
                return viewtype_;}
            void                 viewtype(kindview val);
            guiitemrang          rang(nodetype val, bool ignorekind = false) const;
            void                 rang(nodetype selfval);

            bool                 isloaded() const {
                return ((nodetp_canchild(nodetp())) && (!loadless()) && (viewtype_ != tvcascade))
                        ? isloaded_ : true;}

            void                 isloaded(bool val) {
                if (isloaded_ != val) {
                    isloaded_ = val;
                    initicon();};}

            bool                 loadless() const {
                return loadless_;};
            bool                 isfiltered() const ;

            bool                 ismeta() const {
                return nodetp_is_meta(nodetp());};
            uiwidgetitem*        intfroot() const ;
            uiwidgetitem*        virtualroot() const ;

            int_treewidget_map*  treewidgets() const {
                return treewidgets_;}

            QTreeWidget*         treewidget(nodetype val) const {
                return (treewidgets_->find(rang(val)) != treewidgets_->end()) ?
                        treewidgets_->find(val)->second : 0;}

            void                 treewidgets(int_treewidget_map* val) {
                treewidgets_ = val;}

            uiwidgetitem*        virtualparent() const {
                return virtualparent_;}


            uiwidgetitem *        operator[](indx id);
            void                 clear();
            void                 clear_child();


        private:

            indx               key_;
            name_with_type     nodeinfo_;
            std::string        strciteria_;
            nodetype           filtertype_;
            kindview           viewtype_;
            bool               isloaded_; // флаг загрузки
            bool               loadless_;  // только для поисклвого интерфеса, чтоб не загружались дети найденного


            adminintf_ptr             intf_;     // ссылка на интерфейс
            indx_widgit_map           child_set; // карта детей

            registry_filter_map*      registryfilter_;
            uiwidgetitem*             virtualparent_;
            int_treewidget_map*       treewidgets_;

            static icon_map           iconmap;
            static QIcon*             nillIcon;
            static QIcon*             filterIcon;
            static bool               iconinit;
            static noderang_map       rangmap;


            static void               regist();
            static QIcon              stickicon(const QIcon& val1, const QIcon& val2);
            static QIcon              notloadicon(const QIcon& val);

            void                      initicon();
            void                      regist_in_parent();
            void                      unregist_in_parent();
            void                      create_child(const iteminfo_pair& pairpack);
            QWidget*                  real_parent_for_this_child();
            void                      finditems(nodetype type, indx id, indx_widgit_map& map, uiwidgetitem* root = 0);
            void                      finditems_internal(nodetype type, indx id, indx_widgit_map& map);
            void                      clearallchild_where_rang_morethen0();
            void                      settext();
} ;}}


#endif	/* _NSWIDGETITEM_H */

