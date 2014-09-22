/********************************************************************************
** Form generated from reading UI file 'form_admin.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADMIN_H
#define UI_FORM_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_form_admin
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_8;
    QSplitter *splitter_2;
    QSplitter *splitter;
    QFrame *treeframe0;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *btnkindview;
    QToolButton *btnaddserver;
    QToolButton *btnremoveserver;
    QToolButton *btnconnectserver;
    QToolButton *btndisconnectserver;
    QToolButton *btnmapproject;
    QToolButton *btnnewproject;
    QToolButton *btnunmapproject;
    QToolButton *btnsetfilter;
    QToolButton *btnresetfilter;
    QToolButton *btnadditem;
    QToolButton *btndeleteitem;
    QToolButton *btnimport;
    QToolButton *btnexport;
    QToolButton *btnchangegroup;
    QToolButton *btnchangeagroup;
    QToolButton *btnstartservice;
    QToolButton *btnstopservice;
    QToolButton *btnclone;
    QSpacerItem *horizontalSpacer_6;
    QTreeWidget *treeWidget;
    QFrame *treeframe1;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btnsetfilter1;
    QToolButton *btnresetfilter1;
    QToolButton *btnadditem1;
    QToolButton *btndeleteitem1;
    QToolButton *btnimport1;
    QToolButton *btnexport1;
    QToolButton *btnstartservice1;
    QToolButton *btnstopservice1;
    QToolButton *btnclone1;
    QSpacerItem *horizontalSpacer_4;
    QTreeWidget *treeWidget1;
    QFrame *treeframe2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btnsetfilter2;
    QToolButton *btnresetfilter2;
    QToolButton *btnadditem2;
    QToolButton *btndeleteitem2;
    QToolButton *btnimport2;
    QToolButton *btnexport2;
    QToolButton *btnchangegroup2;
    QToolButton *btnchangeagroup2;
    QSpacerItem *horizontalSpacer;
    QTreeWidget *treeWidget2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QFrame *nillframe;
    QFrame *propertyframe;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QToolButton *btnmerge;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *tableproperty;
    QFrame *viewframe;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btnsetfilterview;
    QToolButton *btninccnt;
    QToolButton *btndeccnt;
    QToolButton *btnsetallvalid;
    QToolButton *btnsetallinvalid;
    QToolButton *btnkvit;
    QToolButton *btngroupkvit;
    QToolButton *btnagroupkvit;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tableview;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_9;
    QListWidget *ErrorWidget;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *btnlogtype;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *btnclearlog;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *form_admin)
    {
        if (form_admin->objectName().isEmpty())
            form_admin->setObjectName(QStringLiteral("form_admin"));
        form_admin->resize(1098, 706);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(form_admin->sizePolicy().hasHeightForWidth());
        form_admin->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(form_admin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        verticalLayout_8 = new QVBoxLayout(centralwidget);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        verticalLayout_8->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_8->setContentsMargins(1, 1, 2, 2);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        sizePolicy1.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy1);
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        treeframe0 = new QFrame(splitter);
        treeframe0->setObjectName(QStringLiteral("treeframe0"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(treeframe0->sizePolicy().hasHeightForWidth());
        treeframe0->setSizePolicy(sizePolicy2);
        treeframe0->setMinimumSize(QSize(200, 0));
        treeframe0->setMaximumSize(QSize(300, 16777215));
        treeframe0->setAutoFillBackground(true);
        verticalLayout = new QVBoxLayout(treeframe0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        btnkindview = new QToolButton(treeframe0);
        btnkindview->setObjectName(QStringLiteral("btnkindview"));
        btnkindview->setMaximumSize(QSize(20, 20));
        btnkindview->setBaseSize(QSize(20, 20));
        btnkindview->setFocusPolicy(Qt::StrongFocus);
        btnkindview->setAcceptDrops(false);
        btnkindview->setAutoFillBackground(true);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/icon/linekind.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnkindview->setIcon(icon);
        btnkindview->setIconSize(QSize(20, 20));
        btnkindview->setCheckable(false);
        btnkindview->setAutoRepeat(false);
        btnkindview->setAutoExclusive(false);
        btnkindview->setPopupMode(QToolButton::DelayedPopup);
        btnkindview->setAutoRaise(true);
        btnkindview->setArrowType(Qt::NoArrow);

        horizontalLayout_6->addWidget(btnkindview);

        btnaddserver = new QToolButton(treeframe0);
        btnaddserver->setObjectName(QStringLiteral("btnaddserver"));
        btnaddserver->setMaximumSize(QSize(20, 20));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/icon/addserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnaddserver->setIcon(icon1);
        btnaddserver->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnaddserver);

        btnremoveserver = new QToolButton(treeframe0);
        btnremoveserver->setObjectName(QStringLiteral("btnremoveserver"));
        btnremoveserver->setMaximumSize(QSize(20, 20));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/icon/removeserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnremoveserver->setIcon(icon2);
        btnremoveserver->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnremoveserver);

        btnconnectserver = new QToolButton(treeframe0);
        btnconnectserver->setObjectName(QStringLiteral("btnconnectserver"));
        btnconnectserver->setMaximumSize(QSize(20, 20));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/icon/connectserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnconnectserver->setIcon(icon3);
        btnconnectserver->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnconnectserver);

        btndisconnectserver = new QToolButton(treeframe0);
        btndisconnectserver->setObjectName(QStringLiteral("btndisconnectserver"));
        btndisconnectserver->setMaximumSize(QSize(20, 20));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/icon/disconnectserver.png"), QSize(), QIcon::Normal, QIcon::Off);
        btndisconnectserver->setIcon(icon4);
        btndisconnectserver->setAutoRaise(true);

        horizontalLayout_6->addWidget(btndisconnectserver);

        btnmapproject = new QToolButton(treeframe0);
        btnmapproject->setObjectName(QStringLiteral("btnmapproject"));
        btnmapproject->setMaximumSize(QSize(20, 20));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/icon/maproject.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnmapproject->setIcon(icon5);
        btnmapproject->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnmapproject);

        btnnewproject = new QToolButton(treeframe0);
        btnnewproject->setObjectName(QStringLiteral("btnnewproject"));
        btnnewproject->setMaximumSize(QSize(20, 20));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/icon/newproject.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnnewproject->setIcon(icon6);
        btnnewproject->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnnewproject);

        btnunmapproject = new QToolButton(treeframe0);
        btnunmapproject->setObjectName(QStringLiteral("btnunmapproject"));
        btnunmapproject->setMaximumSize(QSize(20, 20));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/icon/unmaproject.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnunmapproject->setIcon(icon7);
        btnunmapproject->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnunmapproject);

        btnsetfilter = new QToolButton(treeframe0);
        btnsetfilter->setObjectName(QStringLiteral("btnsetfilter"));
        btnsetfilter->setMaximumSize(QSize(20, 20));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/icon/addfilter.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnsetfilter->setIcon(icon8);
        btnsetfilter->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnsetfilter);

        btnresetfilter = new QToolButton(treeframe0);
        btnresetfilter->setObjectName(QStringLiteral("btnresetfilter"));
        btnresetfilter->setMaximumSize(QSize(20, 20));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/icon/removefilter.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnresetfilter->setIcon(icon9);
        btnresetfilter->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnresetfilter);

        btnadditem = new QToolButton(treeframe0);
        btnadditem->setObjectName(QStringLiteral("btnadditem"));
        btnadditem->setMaximumSize(QSize(20, 20));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnadditem->setIcon(icon10);
        btnadditem->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnadditem);

        btndeleteitem = new QToolButton(treeframe0);
        btndeleteitem->setObjectName(QStringLiteral("btndeleteitem"));
        btndeleteitem->setMaximumSize(QSize(20, 20));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        btndeleteitem->setIcon(icon11);
        btndeleteitem->setAutoRaise(true);

        horizontalLayout_6->addWidget(btndeleteitem);

        btnimport = new QToolButton(treeframe0);
        btnimport->setObjectName(QStringLiteral("btnimport"));
        btnimport->setMaximumSize(QSize(20, 20));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icon/icon/import.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnimport->setIcon(icon12);
        btnimport->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnimport);

        btnexport = new QToolButton(treeframe0);
        btnexport->setObjectName(QStringLiteral("btnexport"));
        btnexport->setMaximumSize(QSize(20, 20));
        QIcon icon13;
        icon13.addFile(QStringLiteral(":/icon/icon/export.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnexport->setIcon(icon13);
        btnexport->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnexport);

        btnchangegroup = new QToolButton(treeframe0);
        btnchangegroup->setObjectName(QStringLiteral("btnchangegroup"));
        btnchangegroup->setMaximumSize(QSize(20, 20));
        QIcon icon14;
        icon14.addFile(QStringLiteral(":/icon/icon/changegroup.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnchangegroup->setIcon(icon14);
        btnchangegroup->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnchangegroup);

        btnchangeagroup = new QToolButton(treeframe0);
        btnchangeagroup->setObjectName(QStringLiteral("btnchangeagroup"));
        btnchangeagroup->setMaximumSize(QSize(20, 20));
        QIcon icon15;
        icon15.addFile(QStringLiteral(":/icon/icon/changeagroup.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnchangeagroup->setIcon(icon15);
        btnchangeagroup->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnchangeagroup);

        btnstartservice = new QToolButton(treeframe0);
        btnstartservice->setObjectName(QStringLiteral("btnstartservice"));
        btnstartservice->setMaximumSize(QSize(20, 20));
        QIcon icon16;
        icon16.addFile(QStringLiteral(":/icon/icon/startservice.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnstartservice->setIcon(icon16);
        btnstartservice->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnstartservice);

        btnstopservice = new QToolButton(treeframe0);
        btnstopservice->setObjectName(QStringLiteral("btnstopservice"));
        btnstopservice->setMaximumSize(QSize(20, 20));
        QIcon icon17;
        icon17.addFile(QStringLiteral(":/icon/icon/stopservice.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnstopservice->setIcon(icon17);
        btnstopservice->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnstopservice);

        btnclone = new QToolButton(treeframe0);
        btnclone->setObjectName(QStringLiteral("btnclone"));
        btnclone->setMaximumSize(QSize(20, 20));
        QIcon icon18;
        icon18.addFile(QStringLiteral(":/icon/icon/operation_clone.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnclone->setIcon(icon18);
        btnclone->setAutoRaise(true);

        horizontalLayout_6->addWidget(btnclone);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_6);

        treeWidget = new QTreeWidget(treeframe0);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setMinimumSize(QSize(200, 0));
        treeWidget->setBaseSize(QSize(240, 0));
        treeWidget->setMouseTracking(true);
        treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidget->setIconSize(QSize(24, 16));
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        splitter->addWidget(treeframe0);
        treeframe1 = new QFrame(splitter);
        treeframe1->setObjectName(QStringLiteral("treeframe1"));
        sizePolicy2.setHeightForWidth(treeframe1->sizePolicy().hasHeightForWidth());
        treeframe1->setSizePolicy(sizePolicy2);
        treeframe1->setMinimumSize(QSize(200, 0));
        verticalLayout_6 = new QVBoxLayout(treeframe1);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        btnsetfilter1 = new QToolButton(treeframe1);
        btnsetfilter1->setObjectName(QStringLiteral("btnsetfilter1"));
        btnsetfilter1->setMaximumSize(QSize(20, 20));
        btnsetfilter1->setBaseSize(QSize(18, 18));
        btnsetfilter1->setAcceptDrops(false);
        btnsetfilter1->setAutoFillBackground(true);
        btnsetfilter1->setIcon(icon8);
        btnsetfilter1->setIconSize(QSize(20, 20));
        btnsetfilter1->setShortcut(QStringLiteral(""));
        btnsetfilter1->setCheckable(false);
        btnsetfilter1->setAutoExclusive(false);
        btnsetfilter1->setPopupMode(QToolButton::InstantPopup);
        btnsetfilter1->setAutoRaise(true);
        btnsetfilter1->setArrowType(Qt::NoArrow);

        horizontalLayout_4->addWidget(btnsetfilter1);

        btnresetfilter1 = new QToolButton(treeframe1);
        btnresetfilter1->setObjectName(QStringLiteral("btnresetfilter1"));
        btnresetfilter1->setMaximumSize(QSize(20, 20));
        btnresetfilter1->setBaseSize(QSize(20, 20));
        btnresetfilter1->setAcceptDrops(false);
        btnresetfilter1->setAutoFillBackground(true);
        btnresetfilter1->setIcon(icon9);
        btnresetfilter1->setIconSize(QSize(20, 20));
        btnresetfilter1->setShortcut(QStringLiteral(""));
        btnresetfilter1->setCheckable(false);
        btnresetfilter1->setAutoExclusive(false);
        btnresetfilter1->setPopupMode(QToolButton::InstantPopup);
        btnresetfilter1->setAutoRaise(true);
        btnresetfilter1->setArrowType(Qt::NoArrow);

        horizontalLayout_4->addWidget(btnresetfilter1);

        btnadditem1 = new QToolButton(treeframe1);
        btnadditem1->setObjectName(QStringLiteral("btnadditem1"));
        btnadditem1->setMaximumSize(QSize(20, 20));
        btnadditem1->setBaseSize(QSize(20, 20));
        btnadditem1->setIcon(icon10);
        btnadditem1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnadditem1);

        btndeleteitem1 = new QToolButton(treeframe1);
        btndeleteitem1->setObjectName(QStringLiteral("btndeleteitem1"));
        btndeleteitem1->setMaximumSize(QSize(20, 20));
        btndeleteitem1->setBaseSize(QSize(20, 20));
        btndeleteitem1->setIcon(icon11);
        btndeleteitem1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btndeleteitem1);

        btnimport1 = new QToolButton(treeframe1);
        btnimport1->setObjectName(QStringLiteral("btnimport1"));
        btnimport1->setMaximumSize(QSize(20, 20));
        btnimport1->setIcon(icon12);
        btnimport1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnimport1);

        btnexport1 = new QToolButton(treeframe1);
        btnexport1->setObjectName(QStringLiteral("btnexport1"));
        btnexport1->setMaximumSize(QSize(20, 20));
        btnexport1->setIcon(icon13);
        btnexport1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnexport1);

        btnstartservice1 = new QToolButton(treeframe1);
        btnstartservice1->setObjectName(QStringLiteral("btnstartservice1"));
        btnstartservice1->setMaximumSize(QSize(20, 20));
        btnstartservice1->setIcon(icon16);
        btnstartservice1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnstartservice1);

        btnstopservice1 = new QToolButton(treeframe1);
        btnstopservice1->setObjectName(QStringLiteral("btnstopservice1"));
        btnstopservice1->setMaximumSize(QSize(20, 20));
        btnstopservice1->setIcon(icon17);
        btnstopservice1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnstopservice1);

        btnclone1 = new QToolButton(treeframe1);
        btnclone1->setObjectName(QStringLiteral("btnclone1"));
        btnclone1->setMaximumSize(QSize(20, 20));
        btnclone1->setIcon(icon18);
        btnclone1->setAutoRaise(true);

        horizontalLayout_4->addWidget(btnclone1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        verticalLayout_6->addLayout(horizontalLayout_4);

        treeWidget1 = new QTreeWidget(treeframe1);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem();
        __qtreewidgetitem1->setText(0, QStringLiteral("1"));
        treeWidget1->setHeaderItem(__qtreewidgetitem1);
        treeWidget1->setObjectName(QStringLiteral("treeWidget1"));
        sizePolicy1.setHeightForWidth(treeWidget1->sizePolicy().hasHeightForWidth());
        treeWidget1->setSizePolicy(sizePolicy1);
        treeWidget1->setMinimumSize(QSize(200, 0));
        treeWidget1->setMouseTracking(true);
        treeWidget1->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget1->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidget1->setIconSize(QSize(24, 16));
        treeWidget1->setRootIsDecorated(false);
        treeWidget1->header()->setVisible(false);

        verticalLayout_6->addWidget(treeWidget1);

        splitter->addWidget(treeframe1);
        treeframe2 = new QFrame(splitter);
        treeframe2->setObjectName(QStringLiteral("treeframe2"));
        sizePolicy2.setHeightForWidth(treeframe2->sizePolicy().hasHeightForWidth());
        treeframe2->setSizePolicy(sizePolicy2);
        treeframe2->setMinimumSize(QSize(200, 0));
        treeframe2->setProperty("flat", QVariant(true));
        verticalLayout_7 = new QVBoxLayout(treeframe2);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnsetfilter2 = new QToolButton(treeframe2);
        btnsetfilter2->setObjectName(QStringLiteral("btnsetfilter2"));
        btnsetfilter2->setMaximumSize(QSize(20, 20));
        btnsetfilter2->setBaseSize(QSize(18, 18));
        btnsetfilter2->setAcceptDrops(false);
        btnsetfilter2->setAutoFillBackground(true);
        btnsetfilter2->setIcon(icon8);
        btnsetfilter2->setIconSize(QSize(20, 20));
        btnsetfilter2->setShortcut(QStringLiteral(""));
        btnsetfilter2->setCheckable(false);
        btnsetfilter2->setPopupMode(QToolButton::InstantPopup);
        btnsetfilter2->setToolButtonStyle(Qt::ToolButtonIconOnly);
        btnsetfilter2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnsetfilter2);

        btnresetfilter2 = new QToolButton(treeframe2);
        btnresetfilter2->setObjectName(QStringLiteral("btnresetfilter2"));
        btnresetfilter2->setMaximumSize(QSize(20, 20));
        btnresetfilter2->setBaseSize(QSize(18, 18));
        btnresetfilter2->setAcceptDrops(false);
        btnresetfilter2->setAutoFillBackground(true);
        btnresetfilter2->setIcon(icon9);
        btnresetfilter2->setIconSize(QSize(20, 20));
        btnresetfilter2->setShortcut(QStringLiteral(""));
        btnresetfilter2->setCheckable(false);
        btnresetfilter2->setAutoExclusive(false);
        btnresetfilter2->setPopupMode(QToolButton::InstantPopup);
        btnresetfilter2->setAutoRaise(true);
        btnresetfilter2->setArrowType(Qt::NoArrow);

        horizontalLayout_3->addWidget(btnresetfilter2);

        btnadditem2 = new QToolButton(treeframe2);
        btnadditem2->setObjectName(QStringLiteral("btnadditem2"));
        btnadditem2->setMaximumSize(QSize(20, 20));
        btnadditem2->setBaseSize(QSize(20, 20));
        btnadditem2->setIcon(icon10);
        btnadditem2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnadditem2);

        btndeleteitem2 = new QToolButton(treeframe2);
        btndeleteitem2->setObjectName(QStringLiteral("btndeleteitem2"));
        btndeleteitem2->setMaximumSize(QSize(20, 20));
        btndeleteitem2->setBaseSize(QSize(20, 20));
        btndeleteitem2->setIcon(icon11);
        btndeleteitem2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btndeleteitem2);

        btnimport2 = new QToolButton(treeframe2);
        btnimport2->setObjectName(QStringLiteral("btnimport2"));
        btnimport2->setMaximumSize(QSize(20, 20));
        btnimport2->setIcon(icon12);
        btnimport2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnimport2);

        btnexport2 = new QToolButton(treeframe2);
        btnexport2->setObjectName(QStringLiteral("btnexport2"));
        btnexport2->setMaximumSize(QSize(20, 20));
        btnexport2->setIcon(icon13);
        btnexport2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnexport2);

        btnchangegroup2 = new QToolButton(treeframe2);
        btnchangegroup2->setObjectName(QStringLiteral("btnchangegroup2"));
        btnchangegroup2->setMaximumSize(QSize(20, 20));
        btnchangegroup2->setIcon(icon14);
        btnchangegroup2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnchangegroup2);

        btnchangeagroup2 = new QToolButton(treeframe2);
        btnchangeagroup2->setObjectName(QStringLiteral("btnchangeagroup2"));
        btnchangeagroup2->setMaximumSize(QSize(20, 20));
        btnchangeagroup2->setIcon(icon15);
        btnchangeagroup2->setAutoRaise(true);

        horizontalLayout_3->addWidget(btnchangeagroup2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_3);

        treeWidget2 = new QTreeWidget(treeframe2);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem();
        __qtreewidgetitem2->setText(0, QStringLiteral("1"));
        treeWidget2->setHeaderItem(__qtreewidgetitem2);
        treeWidget2->setObjectName(QStringLiteral("treeWidget2"));
        sizePolicy1.setHeightForWidth(treeWidget2->sizePolicy().hasHeightForWidth());
        treeWidget2->setSizePolicy(sizePolicy1);
        treeWidget2->setMinimumSize(QSize(200, 0));
        treeWidget2->setMouseTracking(true);
        treeWidget2->setContextMenuPolicy(Qt::CustomContextMenu);
        treeWidget2->setSelectionMode(QAbstractItemView::ExtendedSelection);
        treeWidget2->setIconSize(QSize(24, 16));
        treeWidget2->setRootIsDecorated(false);
        treeWidget2->header()->setVisible(false);

        verticalLayout_7->addWidget(treeWidget2);

        splitter->addWidget(treeframe2);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        nillframe = new QFrame(layoutWidget);
        nillframe->setObjectName(QStringLiteral("nillframe"));
        sizePolicy1.setHeightForWidth(nillframe->sizePolicy().hasHeightForWidth());
        nillframe->setSizePolicy(sizePolicy1);
        nillframe->setMinimumSize(QSize(340, 0));
        nillframe->setProperty("flat", QVariant(false));

        verticalLayout_4->addWidget(nillframe);

        propertyframe = new QFrame(layoutWidget);
        propertyframe->setObjectName(QStringLiteral("propertyframe"));
        sizePolicy1.setHeightForWidth(propertyframe->sizePolicy().hasHeightForWidth());
        propertyframe->setSizePolicy(sizePolicy1);
        propertyframe->setMinimumSize(QSize(340, 0));
        verticalLayout_2 = new QVBoxLayout(propertyframe);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(1, 1, 1, 1);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnmerge = new QToolButton(propertyframe);
        btnmerge->setObjectName(QStringLiteral("btnmerge"));
        btnmerge->setMaximumSize(QSize(30, 30));
        btnmerge->setBaseSize(QSize(22, 22));
        QIcon icon19;
        icon19.addFile(QStringLiteral(":/icon/icon/merge.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnmerge->setIcon(icon19);
        btnmerge->setIconSize(QSize(20, 20));
        btnmerge->setCheckable(false);
        btnmerge->setPopupMode(QToolButton::InstantPopup);
        btnmerge->setAutoRaise(true);

        horizontalLayout->addWidget(btnmerge);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        tableproperty = new QTableWidget(propertyframe);
        if (tableproperty->columnCount() < 2)
            tableproperty->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableproperty->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableproperty->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        if (tableproperty->rowCount() < 1)
            tableproperty->setRowCount(1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableproperty->setVerticalHeaderItem(0, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableproperty->setItem(0, 0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableproperty->setItem(0, 1, __qtablewidgetitem4);
        tableproperty->setObjectName(QStringLiteral("tableproperty"));
        sizePolicy1.setHeightForWidth(tableproperty->sizePolicy().hasHeightForWidth());
        tableproperty->setSizePolicy(sizePolicy1);
        tableproperty->setMinimumSize(QSize(340, 0));
        QPalette palette;
        QBrush brush(QColor(243, 243, 243, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush);
        QBrush brush1(QColor(236, 236, 236, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        QBrush brush2(QColor(230, 230, 230, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush);
        QBrush brush3(QColor(236, 233, 216, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush2);
        tableproperty->setPalette(palette);
        tableproperty->setAlternatingRowColors(true);
        tableproperty->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableproperty->horizontalHeader()->setVisible(false);
        tableproperty->horizontalHeader()->setCascadingSectionResizes(false);
        tableproperty->horizontalHeader()->setDefaultSectionSize(169);
        tableproperty->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableproperty->horizontalHeader()->setStretchLastSection(true);
        tableproperty->verticalHeader()->setVisible(false);
        tableproperty->verticalHeader()->setDefaultSectionSize(18);

        verticalLayout_2->addWidget(tableproperty);


        verticalLayout_4->addWidget(propertyframe);

        viewframe = new QFrame(layoutWidget);
        viewframe->setObjectName(QStringLiteral("viewframe"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(viewframe->sizePolicy().hasHeightForWidth());
        viewframe->setSizePolicy(sizePolicy3);
        viewframe->setMinimumSize(QSize(340, 0));
        verticalLayout_3 = new QVBoxLayout(viewframe);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnsetfilterview = new QToolButton(viewframe);
        btnsetfilterview->setObjectName(QStringLiteral("btnsetfilterview"));
        btnsetfilterview->setMaximumSize(QSize(20, 20));
        btnsetfilterview->setIcon(icon8);
        btnsetfilterview->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnsetfilterview);

        btninccnt = new QToolButton(viewframe);
        btninccnt->setObjectName(QStringLiteral("btninccnt"));
        btninccnt->setMaximumSize(QSize(20, 20));
        QIcon icon20;
        icon20.addFile(QStringLiteral(":/icon/icon/inccounter.png"), QSize(), QIcon::Normal, QIcon::Off);
        btninccnt->setIcon(icon20);
        btninccnt->setAutoRaise(true);

        horizontalLayout_2->addWidget(btninccnt);

        btndeccnt = new QToolButton(viewframe);
        btndeccnt->setObjectName(QStringLiteral("btndeccnt"));
        btndeccnt->setMaximumSize(QSize(20, 20));
        QIcon icon21;
        icon21.addFile(QStringLiteral(":/icon/icon/deccounter.png"), QSize(), QIcon::Normal, QIcon::Off);
        btndeccnt->setIcon(icon21);
        btndeccnt->setAutoRaise(true);

        horizontalLayout_2->addWidget(btndeccnt);

        btnsetallvalid = new QToolButton(viewframe);
        btnsetallvalid->setObjectName(QStringLiteral("btnsetallvalid"));
        btnsetallvalid->setMaximumSize(QSize(20, 20));
        QIcon icon22;
        icon22.addFile(QStringLiteral(":/icon/icon/setvalidall.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnsetallvalid->setIcon(icon22);
        btnsetallvalid->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnsetallvalid);

        btnsetallinvalid = new QToolButton(viewframe);
        btnsetallinvalid->setObjectName(QStringLiteral("btnsetallinvalid"));
        btnsetallinvalid->setMaximumSize(QSize(20, 20));
        QIcon icon23;
        icon23.addFile(QStringLiteral(":/icon/icon/setinvalidall.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnsetallinvalid->setIcon(icon23);
        btnsetallinvalid->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnsetallinvalid);

        btnkvit = new QToolButton(viewframe);
        btnkvit->setObjectName(QStringLiteral("btnkvit"));
        btnkvit->setMaximumSize(QSize(20, 20));
        QIcon icon24;
        icon24.addFile(QStringLiteral(":/icon/icon/kvit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnkvit->setIcon(icon24);
        btnkvit->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnkvit);

        btngroupkvit = new QToolButton(viewframe);
        btngroupkvit->setObjectName(QStringLiteral("btngroupkvit"));
        btngroupkvit->setMaximumSize(QSize(20, 20));
        QIcon icon25;
        icon25.addFile(QStringLiteral(":/icon/icon/group_kvit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btngroupkvit->setIcon(icon25);
        btngroupkvit->setAutoRaise(true);

        horizontalLayout_2->addWidget(btngroupkvit);

        btnagroupkvit = new QToolButton(viewframe);
        btnagroupkvit->setObjectName(QStringLiteral("btnagroupkvit"));
        btnagroupkvit->setMaximumSize(QSize(20, 20));
        QIcon icon26;
        icon26.addFile(QStringLiteral(":/icon/icon/agroup_kvit.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnagroupkvit->setIcon(icon26);
        btnagroupkvit->setAutoRaise(true);

        horizontalLayout_2->addWidget(btnagroupkvit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_2);

        tableview = new QTableView(viewframe);
        tableview->setObjectName(QStringLiteral("tableview"));
        tableview->setMinimumSize(QSize(340, 0));
        QPalette palette1;
        QBrush brush4(QColor(250, 250, 250, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush4);
        QBrush brush5(QColor(234, 234, 234, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush5);
        tableview->setPalette(palette1);
        QFont font;
        font.setPointSize(7);
        tableview->setFont(font);
        tableview->setEditTriggers(QAbstractItemView::SelectedClicked);
        tableview->setAlternatingRowColors(false);
        tableview->setSelectionMode(QAbstractItemView::SingleSelection);
        tableview->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableview->setSortingEnabled(false);
        tableview->setWordWrap(true);
        tableview->horizontalHeader()->setVisible(true);
        tableview->horizontalHeader()->setCascadingSectionResizes(false);
        tableview->horizontalHeader()->setDefaultSectionSize(50);
        tableview->horizontalHeader()->setMinimumSectionSize(18);
        tableview->horizontalHeader()->setProperty("showSortIndicator", QVariant(false));
        tableview->horizontalHeader()->setStretchLastSection(true);
        tableview->verticalHeader()->setVisible(false);
        tableview->verticalHeader()->setCascadingSectionResizes(false);
        tableview->verticalHeader()->setDefaultSectionSize(18);
        tableview->verticalHeader()->setHighlightSections(false);

        verticalLayout_3->addWidget(tableview);


        verticalLayout_4->addWidget(viewframe);

        splitter->addWidget(layoutWidget);
        splitter_2->addWidget(splitter);
        layoutWidget1 = new QWidget(splitter_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        verticalLayout_5 = new QVBoxLayout(layoutWidget1);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetMaximumSize);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        ErrorWidget = new QListWidget(layoutWidget1);
        ErrorWidget->setObjectName(QStringLiteral("ErrorWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(ErrorWidget->sizePolicy().hasHeightForWidth());
        ErrorWidget->setSizePolicy(sizePolicy4);
        ErrorWidget->setMaximumSize(QSize(16777215, 100));
        ErrorWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ErrorWidget->setSelectionMode(QAbstractItemView::NoSelection);
        ErrorWidget->setResizeMode(QListView::Adjust);
        ErrorWidget->setViewMode(QListView::ListMode);
        ErrorWidget->setUniformItemSizes(false);

        verticalLayout_9->addWidget(ErrorWidget);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setSizeConstraint(QLayout::SetMaximumSize);
        btnlogtype = new QToolButton(layoutWidget1);
        btnlogtype->setObjectName(QStringLiteral("btnlogtype"));
        btnlogtype->setMaximumSize(QSize(20, 20));
        QIcon icon27;
        icon27.addFile(QStringLiteral(":/icon/icon/logscreanall.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnlogtype->setIcon(icon27);
        btnlogtype->setIconSize(QSize(16, 16));
        btnlogtype->setAutoRaise(true);

        horizontalLayout_5->addWidget(btnlogtype);

        horizontalSpacer_5 = new QSpacerItem(20, 3, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        btnclearlog = new QToolButton(layoutWidget1);
        btnclearlog->setObjectName(QStringLiteral("btnclearlog"));
        btnclearlog->setMaximumSize(QSize(20, 20));
        QIcon icon28;
        icon28.addFile(QStringLiteral(":/icon/icon/logscreanclear.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnclearlog->setIcon(icon28);
        btnclearlog->setIconSize(QSize(16, 16));

        horizontalLayout_5->addWidget(btnclearlog);


        verticalLayout_9->addLayout(horizontalLayout_5);


        verticalLayout_5->addLayout(verticalLayout_9);

        splitter_2->addWidget(layoutWidget1);

        verticalLayout_8->addWidget(splitter_2);

        form_admin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(form_admin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1098, 21));
        form_admin->setMenuBar(menubar);
        statusbar = new QStatusBar(form_admin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        form_admin->setStatusBar(statusbar);
        toolBar = new QToolBar(form_admin);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        form_admin->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addSeparator();

        retranslateUi(form_admin);

        ErrorWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(form_admin);
    } // setupUi

    void retranslateUi(QMainWindow *form_admin)
    {
        form_admin->setWindowTitle(QApplication::translate("form_admin", "MainWindow", 0));
        treeframe0->setProperty("title", QVariant(QString()));
        btnkindview->setText(QApplication::translate("form_admin", "...", 0));
        btnaddserver->setText(QApplication::translate("form_admin", "...", 0));
        btnremoveserver->setText(QApplication::translate("form_admin", "...", 0));
        btnconnectserver->setText(QApplication::translate("form_admin", "...", 0));
        btndisconnectserver->setText(QApplication::translate("form_admin", "...", 0));
        btnmapproject->setText(QApplication::translate("form_admin", "...", 0));
        btnnewproject->setText(QApplication::translate("form_admin", "...", 0));
        btnunmapproject->setText(QApplication::translate("form_admin", "...", 0));
        btnsetfilter->setText(QApplication::translate("form_admin", "...", 0));
        btnresetfilter->setText(QApplication::translate("form_admin", "...", 0));
        btnadditem->setText(QApplication::translate("form_admin", "...", 0));
        btndeleteitem->setText(QApplication::translate("form_admin", "...", 0));
        btnimport->setText(QApplication::translate("form_admin", "...", 0));
        btnexport->setText(QApplication::translate("form_admin", "...", 0));
        btnchangegroup->setText(QApplication::translate("form_admin", "...", 0));
        btnchangeagroup->setText(QApplication::translate("form_admin", "...", 0));
        btnstartservice->setText(QApplication::translate("form_admin", "...", 0));
        btnstopservice->setText(QApplication::translate("form_admin", "...", 0));
        btnclone->setText(QApplication::translate("form_admin", "...", 0));
        treeframe1->setProperty("title", QVariant(QString()));
        btnsetfilter1->setText(QApplication::translate("form_admin", "...", 0));
        btnresetfilter1->setText(QApplication::translate("form_admin", "...", 0));
        btnadditem1->setText(QApplication::translate("form_admin", "...", 0));
        btndeleteitem1->setText(QApplication::translate("form_admin", "...", 0));
        btnimport1->setText(QApplication::translate("form_admin", "...", 0));
        btnexport1->setText(QApplication::translate("form_admin", "...", 0));
        btnstartservice1->setText(QApplication::translate("form_admin", "...", 0));
        btnstopservice1->setText(QApplication::translate("form_admin", "...", 0));
        btnclone1->setText(QApplication::translate("form_admin", "...", 0));
        treeframe2->setProperty("title", QVariant(QString()));
        btnsetfilter2->setText(QApplication::translate("form_admin", "...", 0));
        btnresetfilter2->setText(QApplication::translate("form_admin", "...", 0));
        btnadditem2->setText(QApplication::translate("form_admin", "...", 0));
        btndeleteitem2->setText(QApplication::translate("form_admin", "...", 0));
        btnimport2->setText(QApplication::translate("form_admin", "...", 0));
        btnexport2->setText(QApplication::translate("form_admin", "...", 0));
        btnchangegroup2->setText(QApplication::translate("form_admin", "...", 0));
        btnchangeagroup2->setText(QApplication::translate("form_admin", "...", 0));
        nillframe->setProperty("title", QVariant(QString()));
        propertyframe->setProperty("title", QVariant(QString()));
        btnmerge->setText(QApplication::translate("form_admin", "...", 0));
        QTableWidgetItem *___qtablewidgetitem = tableproperty->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("form_admin", "New Column", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tableproperty->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("form_admin", "New Column", 0));
        QTableWidgetItem *___qtablewidgetitem2 = tableproperty->verticalHeaderItem(0);
        ___qtablewidgetitem2->setText(QApplication::translate("form_admin", "New Row", 0));

        const bool __sortingEnabled = tableproperty->isSortingEnabled();
        tableproperty->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem3 = tableproperty->item(0, 0);
        ___qtablewidgetitem3->setText(QApplication::translate("form_admin", "bbb", 0));
        QTableWidgetItem *___qtablewidgetitem4 = tableproperty->item(0, 1);
        ___qtablewidgetitem4->setText(QApplication::translate("form_admin", "ccc", 0));
        tableproperty->setSortingEnabled(__sortingEnabled);

        viewframe->setProperty("title", QVariant(QString()));
        btnsetfilterview->setText(QApplication::translate("form_admin", "...", 0));
        btninccnt->setText(QApplication::translate("form_admin", "...", 0));
        btndeccnt->setText(QApplication::translate("form_admin", "...", 0));
        btnsetallvalid->setText(QApplication::translate("form_admin", "...", 0));
        btnsetallinvalid->setText(QApplication::translate("form_admin", "...", 0));
        btnkvit->setText(QApplication::translate("form_admin", "...", 0));
        btngroupkvit->setText(QApplication::translate("form_admin", "...", 0));
        btnagroupkvit->setText(QApplication::translate("form_admin", "...", 0));
#ifndef QT_NO_WHATSTHIS
        tableview->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
        btnlogtype->setText(QApplication::translate("form_admin", "...", 0));
        btnclearlog->setText(QApplication::translate("form_admin", "...", 0));
        toolBar->setWindowTitle(QApplication::translate("form_admin", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class form_admin: public Ui_form_admin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADMIN_H
