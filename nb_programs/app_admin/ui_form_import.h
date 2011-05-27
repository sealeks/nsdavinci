/********************************************************************************
** Form generated from reading UI file 'form_import.ui'
**
** Created: Fri May 27 19:50:57 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_IMPORT_H
#define UI_FORM_IMPORT_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_import
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QSplitter *splitter;
    QFrame *taglayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *taglayout_;
    QHBoxLayout *horizontalLayout;
    QToolButton *btndeletetags;
    QToolButton *btnprefixtag;
    QSpacerItem *horizontalSpacer;
    QLabel *labeltag;
    QTableView *tagtable;
    QFrame *grouplayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *grouplayout_;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *btndeletegroups;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelgroup;
    QTableView *grouptable;
    QFrame *agrouplayout;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *agrouplayout_;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *btndeleteagroups;
    QSpacerItem *horizontalSpacer_3;
    QLabel *labelagroup;
    QTableView *agrouptable;
    QFrame *userlayout;
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *userlayout_;
    QHBoxLayout *horizontalLayout_4;
    QToolButton *btndeleteusers;
    QSpacerItem *horizontalSpacer_4;
    QLabel *labeluser;
    QTableView *usertable;
    QCheckBox *revwritecheckbox;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *form_import)
    {
        if (form_import->objectName().isEmpty())
            form_import->setObjectName(QString::fromUtf8("form_import"));
        form_import->setWindowModality(Qt::ApplicationModal);
        form_import->resize(969, 627);
        form_import->setModal(true);
        verticalLayout_6 = new QVBoxLayout(form_import);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        splitter = new QSplitter(form_import);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        taglayout = new QFrame(splitter);
        taglayout->setObjectName(QString::fromUtf8("taglayout"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(taglayout->sizePolicy().hasHeightForWidth());
        taglayout->setSizePolicy(sizePolicy);
        taglayout->setFrameShape(QFrame::StyledPanel);
        taglayout->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(taglayout);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        taglayout_ = new QVBoxLayout();
        taglayout_->setObjectName(QString::fromUtf8("taglayout_"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        btndeletetags = new QToolButton(taglayout);
        btndeletetags->setObjectName(QString::fromUtf8("btndeletetags"));
        btndeletetags->setMaximumSize(QSize(20, 20));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/deleteuncheck.png"), QSize(), QIcon::Normal, QIcon::Off);
        btndeletetags->setIcon(icon);
        btndeletetags->setIconSize(QSize(20, 20));
        btndeletetags->setAutoRaise(true);

        horizontalLayout->addWidget(btndeletetags);

        btnprefixtag = new QToolButton(taglayout);
        btnprefixtag->setObjectName(QString::fromUtf8("btnprefixtag"));
        btnprefixtag->setMaximumSize(QSize(20, 20));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/addpr.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnprefixtag->setIcon(icon1);
        btnprefixtag->setIconSize(QSize(20, 20));
        btnprefixtag->setAutoRaise(true);

        horizontalLayout->addWidget(btnprefixtag);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        taglayout_->addLayout(horizontalLayout);

        labeltag = new QLabel(taglayout);
        labeltag->setObjectName(QString::fromUtf8("labeltag"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(labeltag->sizePolicy().hasHeightForWidth());
        labeltag->setSizePolicy(sizePolicy1);

        taglayout_->addWidget(labeltag);

        tagtable = new QTableView(taglayout);
        tagtable->setObjectName(QString::fromUtf8("tagtable"));
        sizePolicy.setHeightForWidth(tagtable->sizePolicy().hasHeightForWidth());
        tagtable->setSizePolicy(sizePolicy);
        tagtable->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        tagtable->setEditTriggers(QAbstractItemView::AllEditTriggers);
        tagtable->setTabKeyNavigation(true);
        tagtable->setProperty("showDropIndicator", QVariant(true));
        tagtable->setDragDropOverwriteMode(false);
        tagtable->setAlternatingRowColors(false);
        tagtable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        tagtable->setSelectionBehavior(QAbstractItemView::SelectItems);
        tagtable->setTextElideMode(Qt::ElideRight);
        tagtable->setSortingEnabled(false);
        tagtable->setCornerButtonEnabled(true);
        tagtable->horizontalHeader()->setCascadingSectionResizes(true);
        tagtable->horizontalHeader()->setHighlightSections(true);
        tagtable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tagtable->horizontalHeader()->setStretchLastSection(true);
        tagtable->verticalHeader()->setVisible(false);
        tagtable->verticalHeader()->setCascadingSectionResizes(false);
        tagtable->verticalHeader()->setDefaultSectionSize(20);
        tagtable->verticalHeader()->setHighlightSections(false);

        taglayout_->addWidget(tagtable);


        verticalLayout_2->addLayout(taglayout_);

        splitter->addWidget(taglayout);
        grouplayout = new QFrame(splitter);
        grouplayout->setObjectName(QString::fromUtf8("grouplayout"));
        sizePolicy.setHeightForWidth(grouplayout->sizePolicy().hasHeightForWidth());
        grouplayout->setSizePolicy(sizePolicy);
        grouplayout->setFrameShape(QFrame::StyledPanel);
        grouplayout->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(grouplayout);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        grouplayout_ = new QVBoxLayout();
        grouplayout_->setObjectName(QString::fromUtf8("grouplayout_"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btndeletegroups = new QToolButton(grouplayout);
        btndeletegroups->setObjectName(QString::fromUtf8("btndeletegroups"));
        btndeletegroups->setMaximumSize(QSize(20, 20));
        btndeletegroups->setIcon(icon);
        btndeletegroups->setIconSize(QSize(20, 20));
        btndeletegroups->setAutoRaise(true);

        horizontalLayout_2->addWidget(btndeletegroups);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        grouplayout_->addLayout(horizontalLayout_2);

        labelgroup = new QLabel(grouplayout);
        labelgroup->setObjectName(QString::fromUtf8("labelgroup"));
        sizePolicy1.setHeightForWidth(labelgroup->sizePolicy().hasHeightForWidth());
        labelgroup->setSizePolicy(sizePolicy1);

        grouplayout_->addWidget(labelgroup);

        grouptable = new QTableView(grouplayout);
        grouptable->setObjectName(QString::fromUtf8("grouptable"));
        sizePolicy.setHeightForWidth(grouptable->sizePolicy().hasHeightForWidth());
        grouptable->setSizePolicy(sizePolicy);
        grouptable->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        grouptable->setEditTriggers(QAbstractItemView::AllEditTriggers);
        grouptable->setTabKeyNavigation(false);
        grouptable->setProperty("showDropIndicator", QVariant(true));
        grouptable->setDragDropOverwriteMode(false);
        grouptable->setAlternatingRowColors(false);
        grouptable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        grouptable->setSelectionBehavior(QAbstractItemView::SelectItems);
        grouptable->setTextElideMode(Qt::ElideRight);
        grouptable->setSortingEnabled(false);
        grouptable->setCornerButtonEnabled(true);
        grouptable->horizontalHeader()->setCascadingSectionResizes(true);
        grouptable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        grouptable->horizontalHeader()->setStretchLastSection(true);
        grouptable->verticalHeader()->setVisible(false);
        grouptable->verticalHeader()->setCascadingSectionResizes(false);
        grouptable->verticalHeader()->setDefaultSectionSize(20);
        grouptable->verticalHeader()->setHighlightSections(false);

        grouplayout_->addWidget(grouptable);


        verticalLayout_3->addLayout(grouplayout_);

        splitter->addWidget(grouplayout);
        agrouplayout = new QFrame(splitter);
        agrouplayout->setObjectName(QString::fromUtf8("agrouplayout"));
        sizePolicy.setHeightForWidth(agrouplayout->sizePolicy().hasHeightForWidth());
        agrouplayout->setSizePolicy(sizePolicy);
        agrouplayout->setFrameShape(QFrame::StyledPanel);
        agrouplayout->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(agrouplayout);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        agrouplayout_ = new QVBoxLayout();
        agrouplayout_->setObjectName(QString::fromUtf8("agrouplayout_"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btndeleteagroups = new QToolButton(agrouplayout);
        btndeleteagroups->setObjectName(QString::fromUtf8("btndeleteagroups"));
        btndeleteagroups->setMaximumSize(QSize(20, 20));
        btndeleteagroups->setIcon(icon);
        btndeleteagroups->setIconSize(QSize(20, 20));
        btndeleteagroups->setAutoRaise(true);

        horizontalLayout_3->addWidget(btndeleteagroups);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        agrouplayout_->addLayout(horizontalLayout_3);

        labelagroup = new QLabel(agrouplayout);
        labelagroup->setObjectName(QString::fromUtf8("labelagroup"));
        sizePolicy1.setHeightForWidth(labelagroup->sizePolicy().hasHeightForWidth());
        labelagroup->setSizePolicy(sizePolicy1);

        agrouplayout_->addWidget(labelagroup);

        agrouptable = new QTableView(agrouplayout);
        agrouptable->setObjectName(QString::fromUtf8("agrouptable"));
        sizePolicy.setHeightForWidth(agrouptable->sizePolicy().hasHeightForWidth());
        agrouptable->setSizePolicy(sizePolicy);
        agrouptable->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        agrouptable->setEditTriggers(QAbstractItemView::AllEditTriggers);
        agrouptable->setTabKeyNavigation(false);
        agrouptable->setProperty("showDropIndicator", QVariant(true));
        agrouptable->setDragDropOverwriteMode(false);
        agrouptable->setAlternatingRowColors(false);
        agrouptable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        agrouptable->setSelectionBehavior(QAbstractItemView::SelectItems);
        agrouptable->setTextElideMode(Qt::ElideRight);
        agrouptable->setSortingEnabled(false);
        agrouptable->setCornerButtonEnabled(true);
        agrouptable->horizontalHeader()->setCascadingSectionResizes(true);
        agrouptable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        agrouptable->horizontalHeader()->setStretchLastSection(true);
        agrouptable->verticalHeader()->setVisible(false);
        agrouptable->verticalHeader()->setCascadingSectionResizes(false);
        agrouptable->verticalHeader()->setDefaultSectionSize(20);
        agrouptable->verticalHeader()->setHighlightSections(false);

        agrouplayout_->addWidget(agrouptable);


        verticalLayout_4->addLayout(agrouplayout_);

        splitter->addWidget(agrouplayout);
        userlayout = new QFrame(splitter);
        userlayout->setObjectName(QString::fromUtf8("userlayout"));
        sizePolicy.setHeightForWidth(userlayout->sizePolicy().hasHeightForWidth());
        userlayout->setSizePolicy(sizePolicy);
        userlayout->setFrameShape(QFrame::StyledPanel);
        userlayout->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(userlayout);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        userlayout_ = new QVBoxLayout();
        userlayout_->setObjectName(QString::fromUtf8("userlayout_"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        btndeleteusers = new QToolButton(userlayout);
        btndeleteusers->setObjectName(QString::fromUtf8("btndeleteusers"));
        btndeleteusers->setMaximumSize(QSize(20, 20));
        btndeleteusers->setIcon(icon);
        btndeleteusers->setIconSize(QSize(20, 20));
        btndeleteusers->setAutoRaise(true);

        horizontalLayout_4->addWidget(btndeleteusers);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);


        userlayout_->addLayout(horizontalLayout_4);

        labeluser = new QLabel(userlayout);
        labeluser->setObjectName(QString::fromUtf8("labeluser"));
        sizePolicy1.setHeightForWidth(labeluser->sizePolicy().hasHeightForWidth());
        labeluser->setSizePolicy(sizePolicy1);

        userlayout_->addWidget(labeluser);

        usertable = new QTableView(userlayout);
        usertable->setObjectName(QString::fromUtf8("usertable"));
        sizePolicy.setHeightForWidth(usertable->sizePolicy().hasHeightForWidth());
        usertable->setSizePolicy(sizePolicy);
        usertable->setLocale(QLocale(QLocale::Russian, QLocale::RussianFederation));
        usertable->setEditTriggers(QAbstractItemView::AllEditTriggers);
        usertable->setTabKeyNavigation(false);
        usertable->setProperty("showDropIndicator", QVariant(true));
        usertable->setDragDropOverwriteMode(false);
        usertable->setAlternatingRowColors(false);
        usertable->setSelectionMode(QAbstractItemView::ExtendedSelection);
        usertable->setSelectionBehavior(QAbstractItemView::SelectItems);
        usertable->setTextElideMode(Qt::ElideRight);
        usertable->setSortingEnabled(false);
        usertable->setCornerButtonEnabled(true);
        usertable->horizontalHeader()->setCascadingSectionResizes(true);
        usertable->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        usertable->horizontalHeader()->setStretchLastSection(true);
        usertable->verticalHeader()->setVisible(false);
        usertable->verticalHeader()->setCascadingSectionResizes(false);
        usertable->verticalHeader()->setDefaultSectionSize(20);
        usertable->verticalHeader()->setHighlightSections(false);

        userlayout_->addWidget(usertable);


        verticalLayout_5->addLayout(userlayout_);

        splitter->addWidget(userlayout);

        verticalLayout->addWidget(splitter);

        revwritecheckbox = new QCheckBox(form_import);
        revwritecheckbox->setObjectName(QString::fromUtf8("revwritecheckbox"));

        verticalLayout->addWidget(revwritecheckbox);

        buttonBox = new QDialogButtonBox(form_import);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_6->addLayout(verticalLayout);


        retranslateUi(form_import);
        QObject::connect(buttonBox, SIGNAL(accepted()), form_import, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), form_import, SLOT(reject()));

        QMetaObject::connectSlotsByName(form_import);
    } // setupUi

    void retranslateUi(QDialog *form_import)
    {
        form_import->setWindowTitle(QApplication::translate("form_import", "form_import", 0, QApplication::UnicodeUTF8));
        btndeletetags->setText(QApplication::translate("form_import", "...", 0, QApplication::UnicodeUTF8));
        btnprefixtag->setText(QApplication::translate("form_import", "...", 0, QApplication::UnicodeUTF8));
        labeltag->setText(QApplication::translate("form_import", "TextLabel", 0, QApplication::UnicodeUTF8));
        btndeletegroups->setText(QApplication::translate("form_import", "...", 0, QApplication::UnicodeUTF8));
        labelgroup->setText(QApplication::translate("form_import", "TextLabel", 0, QApplication::UnicodeUTF8));
        btndeleteagroups->setText(QApplication::translate("form_import", "...", 0, QApplication::UnicodeUTF8));
        labelagroup->setText(QApplication::translate("form_import", "TextLabel", 0, QApplication::UnicodeUTF8));
        btndeleteusers->setText(QApplication::translate("form_import", "...", 0, QApplication::UnicodeUTF8));
        labeluser->setText(QApplication::translate("form_import", "TextLabel", 0, QApplication::UnicodeUTF8));
        revwritecheckbox->setText(QApplication::translate("form_import", "rewrite", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_import: public Ui_form_import {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_IMPORT_H
