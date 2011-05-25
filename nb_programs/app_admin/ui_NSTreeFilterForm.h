/********************************************************************************
** Form generated from reading UI file 'NSTreeFilterForm.ui'
**
** Created: Sat 26. Feb 21:25:05 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NSTREEFILTERFORM_H
#define UI_NSTREEFILTERFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_NSTreeFilterForm
{
public:
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QFrame *frameHeader;
    QVBoxLayout *verticalLayout_5;
    QLabel *HeadLineLable;
    QFrame *framebynodetype;
    QVBoxLayout *verticalLayout_9;
    QLabel *labelbynodetype;
    QComboBox *comboBoxbynodetype;
    QFrame *framebyName;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelbyName;
    QLineEdit *lineEditbyName;
    QFrame *framebyBind;
    QVBoxLayout *verticalLayout_3;
    QLabel *labelbyBind;
    QLineEdit *lineEditbyBind;
    QFrame *framebyComment;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelbyComment;
    QLineEdit *lineEditbyComment;
    QFrame *framebyGroup;
    QVBoxLayout *verticalLayout_11;
    QLabel *labelbyGroup;
    QListWidget *listWidgetbyGroup;
    QFrame *framebyGroupType;
    QVBoxLayout *verticalLayout_12;
    QLabel *labelbyGroupType;
    QListWidget *listWidgetbyGroupType;
    QFrame *framebyRtType;
    QVBoxLayout *verticalLayout_13;
    QLabel *labelbyRtType;
    QListWidget *listWidgetbyRtType;
    QFrame *frameButton;
    QHBoxLayout *horizontalLayout;
    QPushButton *BtnClear;
    QPushButton *BtnCancel;
    QPushButton *BntOk;

    void setupUi(QDialog *NSTreeFilterForm)
    {
        if (NSTreeFilterForm->objectName().isEmpty())
            NSTreeFilterForm->setObjectName(QString::fromUtf8("NSTreeFilterForm"));
        NSTreeFilterForm->setWindowModality(Qt::ApplicationModal);
        NSTreeFilterForm->resize(378, 1010);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NSTreeFilterForm->sizePolicy().hasHeightForWidth());
        NSTreeFilterForm->setSizePolicy(sizePolicy);
        NSTreeFilterForm->setMinimumSize(QSize(378, 0));
        NSTreeFilterForm->setAutoFillBackground(false);
        NSTreeFilterForm->setSizeGripEnabled(true);
        verticalLayout_6 = new QVBoxLayout(NSTreeFilterForm);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        frameHeader = new QFrame(NSTreeFilterForm);
        frameHeader->setObjectName(QString::fromUtf8("frameHeader"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frameHeader->sizePolicy().hasHeightForWidth());
        frameHeader->setSizePolicy(sizePolicy1);
        frameHeader->setMinimumSize(QSize(350, 30));
        frameHeader->setMaximumSize(QSize(10000, 30));
        frameHeader->setAutoFillBackground(false);
        frameHeader->setFrameShape(QFrame::StyledPanel);
        frameHeader->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frameHeader);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        HeadLineLable = new QLabel(frameHeader);
        HeadLineLable->setObjectName(QString::fromUtf8("HeadLineLable"));

        verticalLayout_5->addWidget(HeadLineLable);


        verticalLayout->addWidget(frameHeader);

        framebynodetype = new QFrame(NSTreeFilterForm);
        framebynodetype->setObjectName(QString::fromUtf8("framebynodetype"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(framebynodetype->sizePolicy().hasHeightForWidth());
        framebynodetype->setSizePolicy(sizePolicy2);
        framebynodetype->setMinimumSize(QSize(350, 58));
        framebynodetype->setMaximumSize(QSize(16777215, 58));
        framebynodetype->setAutoFillBackground(false);
        framebynodetype->setFrameShape(QFrame::StyledPanel);
        framebynodetype->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(framebynodetype);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        labelbynodetype = new QLabel(framebynodetype);
        labelbynodetype->setObjectName(QString::fromUtf8("labelbynodetype"));

        verticalLayout_9->addWidget(labelbynodetype);

        comboBoxbynodetype = new QComboBox(framebynodetype);
        comboBoxbynodetype->addItem(QString());
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icon/ntGT.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icon/ntEvent.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icon/ntOBase.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icon/cdtGroup.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icon/ntA.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon4, QString());
        comboBoxbynodetype->setObjectName(QString::fromUtf8("comboBoxbynodetype"));
        comboBoxbynodetype->setMinimumSize(QSize(0, 20));
        comboBoxbynodetype->setMaximumSize(QSize(16777215, 20));

        verticalLayout_9->addWidget(comboBoxbynodetype);


        verticalLayout->addWidget(framebynodetype);

        framebyName = new QFrame(NSTreeFilterForm);
        framebyName->setObjectName(QString::fromUtf8("framebyName"));
        sizePolicy2.setHeightForWidth(framebyName->sizePolicy().hasHeightForWidth());
        framebyName->setSizePolicy(sizePolicy2);
        framebyName->setMinimumSize(QSize(350, 58));
        framebyName->setMaximumSize(QSize(16777215, 58));
        framebyName->setAutoFillBackground(false);
        framebyName->setFrameShape(QFrame::StyledPanel);
        framebyName->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(framebyName);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelbyName = new QLabel(framebyName);
        labelbyName->setObjectName(QString::fromUtf8("labelbyName"));

        verticalLayout_2->addWidget(labelbyName);

        lineEditbyName = new QLineEdit(framebyName);
        lineEditbyName->setObjectName(QString::fromUtf8("lineEditbyName"));
        lineEditbyName->setMinimumSize(QSize(0, 20));
        lineEditbyName->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(lineEditbyName);


        verticalLayout->addWidget(framebyName);

        framebyBind = new QFrame(NSTreeFilterForm);
        framebyBind->setObjectName(QString::fromUtf8("framebyBind"));
        sizePolicy2.setHeightForWidth(framebyBind->sizePolicy().hasHeightForWidth());
        framebyBind->setSizePolicy(sizePolicy2);
        framebyBind->setMinimumSize(QSize(350, 58));
        framebyBind->setMaximumSize(QSize(16777215, 58));
        framebyBind->setAutoFillBackground(false);
        framebyBind->setFrameShape(QFrame::StyledPanel);
        framebyBind->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(framebyBind);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        labelbyBind = new QLabel(framebyBind);
        labelbyBind->setObjectName(QString::fromUtf8("labelbyBind"));

        verticalLayout_3->addWidget(labelbyBind);

        lineEditbyBind = new QLineEdit(framebyBind);
        lineEditbyBind->setObjectName(QString::fromUtf8("lineEditbyBind"));
        lineEditbyBind->setMinimumSize(QSize(0, 20));
        lineEditbyBind->setMaximumSize(QSize(16777215, 20));

        verticalLayout_3->addWidget(lineEditbyBind);


        verticalLayout->addWidget(framebyBind);

        framebyComment = new QFrame(NSTreeFilterForm);
        framebyComment->setObjectName(QString::fromUtf8("framebyComment"));
        sizePolicy2.setHeightForWidth(framebyComment->sizePolicy().hasHeightForWidth());
        framebyComment->setSizePolicy(sizePolicy2);
        framebyComment->setMinimumSize(QSize(350, 58));
        framebyComment->setMaximumSize(QSize(16777215, 58));
        framebyComment->setAutoFillBackground(false);
        framebyComment->setFrameShape(QFrame::StyledPanel);
        framebyComment->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(framebyComment);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelbyComment = new QLabel(framebyComment);
        labelbyComment->setObjectName(QString::fromUtf8("labelbyComment"));

        verticalLayout_4->addWidget(labelbyComment);

        lineEditbyComment = new QLineEdit(framebyComment);
        lineEditbyComment->setObjectName(QString::fromUtf8("lineEditbyComment"));
        lineEditbyComment->setMinimumSize(QSize(0, 20));
        lineEditbyComment->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(lineEditbyComment);


        verticalLayout->addWidget(framebyComment);

        framebyGroup = new QFrame(NSTreeFilterForm);
        framebyGroup->setObjectName(QString::fromUtf8("framebyGroup"));
        sizePolicy2.setHeightForWidth(framebyGroup->sizePolicy().hasHeightForWidth());
        framebyGroup->setSizePolicy(sizePolicy2);
        framebyGroup->setMinimumSize(QSize(350, 100));
        framebyGroup->setMaximumSize(QSize(16777215, 300));
        framebyGroup->setAutoFillBackground(false);
        framebyGroup->setFrameShape(QFrame::StyledPanel);
        framebyGroup->setFrameShadow(QFrame::Raised);
        verticalLayout_11 = new QVBoxLayout(framebyGroup);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        labelbyGroup = new QLabel(framebyGroup);
        labelbyGroup->setObjectName(QString::fromUtf8("labelbyGroup"));

        verticalLayout_11->addWidget(labelbyGroup);

        listWidgetbyGroup = new QListWidget(framebyGroup);
        listWidgetbyGroup->setObjectName(QString::fromUtf8("listWidgetbyGroup"));

        verticalLayout_11->addWidget(listWidgetbyGroup);


        verticalLayout->addWidget(framebyGroup);

        framebyGroupType = new QFrame(NSTreeFilterForm);
        framebyGroupType->setObjectName(QString::fromUtf8("framebyGroupType"));
        sizePolicy2.setHeightForWidth(framebyGroupType->sizePolicy().hasHeightForWidth());
        framebyGroupType->setSizePolicy(sizePolicy2);
        framebyGroupType->setMinimumSize(QSize(350, 100));
        framebyGroupType->setMaximumSize(QSize(16777215, 300));
        framebyGroupType->setAutoFillBackground(false);
        framebyGroupType->setFrameShape(QFrame::StyledPanel);
        framebyGroupType->setFrameShadow(QFrame::Raised);
        verticalLayout_12 = new QVBoxLayout(framebyGroupType);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        labelbyGroupType = new QLabel(framebyGroupType);
        labelbyGroupType->setObjectName(QString::fromUtf8("labelbyGroupType"));

        verticalLayout_12->addWidget(labelbyGroupType);

        listWidgetbyGroupType = new QListWidget(framebyGroupType);
        listWidgetbyGroupType->setObjectName(QString::fromUtf8("listWidgetbyGroupType"));

        verticalLayout_12->addWidget(listWidgetbyGroupType);


        verticalLayout->addWidget(framebyGroupType);

        framebyRtType = new QFrame(NSTreeFilterForm);
        framebyRtType->setObjectName(QString::fromUtf8("framebyRtType"));
        sizePolicy2.setHeightForWidth(framebyRtType->sizePolicy().hasHeightForWidth());
        framebyRtType->setSizePolicy(sizePolicy2);
        framebyRtType->setMinimumSize(QSize(350, 100));
        framebyRtType->setMaximumSize(QSize(16777215, 300));
        framebyRtType->setAutoFillBackground(false);
        framebyRtType->setFrameShape(QFrame::StyledPanel);
        framebyRtType->setFrameShadow(QFrame::Raised);
        verticalLayout_13 = new QVBoxLayout(framebyRtType);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        labelbyRtType = new QLabel(framebyRtType);
        labelbyRtType->setObjectName(QString::fromUtf8("labelbyRtType"));

        verticalLayout_13->addWidget(labelbyRtType);

        listWidgetbyRtType = new QListWidget(framebyRtType);
        listWidgetbyRtType->setObjectName(QString::fromUtf8("listWidgetbyRtType"));

        verticalLayout_13->addWidget(listWidgetbyRtType);


        verticalLayout->addWidget(framebyRtType);

        frameButton = new QFrame(NSTreeFilterForm);
        frameButton->setObjectName(QString::fromUtf8("frameButton"));
        sizePolicy2.setHeightForWidth(frameButton->sizePolicy().hasHeightForWidth());
        frameButton->setSizePolicy(sizePolicy2);
        frameButton->setMinimumSize(QSize(350, 50));
        frameButton->setMaximumSize(QSize(16777215, 50));
        frameButton->setAutoFillBackground(false);
        frameButton->setFrameShape(QFrame::StyledPanel);
        frameButton->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frameButton);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        BtnClear = new QPushButton(frameButton);
        BtnClear->setObjectName(QString::fromUtf8("BtnClear"));
        BtnClear->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(BtnClear);

        BtnCancel = new QPushButton(frameButton);
        BtnCancel->setObjectName(QString::fromUtf8("BtnCancel"));
        BtnCancel->setMaximumSize(QSize(80, 16777215));
        BtnCancel->setAutoExclusive(false);

        horizontalLayout->addWidget(BtnCancel);

        BntOk = new QPushButton(frameButton);
        BntOk->setObjectName(QString::fromUtf8("BntOk"));
        BntOk->setMaximumSize(QSize(80, 16777215));
        BntOk->setDefault(false);
        BntOk->setFlat(false);

        horizontalLayout->addWidget(BntOk);


        verticalLayout->addWidget(frameButton);


        verticalLayout_6->addLayout(verticalLayout);


        retranslateUi(NSTreeFilterForm);

        QMetaObject::connectSlotsByName(NSTreeFilterForm);
    } // setupUi

    void retranslateUi(QDialog *NSTreeFilterForm)
    {
        NSTreeFilterForm->setWindowTitle(QApplication::translate("NSTreeFilterForm", "NSTreeFilterForm", 0, QApplication::UnicodeUTF8));
        frameHeader->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        HeadLineLable->setText(QApplication::translate("NSTreeFilterForm", ".Finder", 0, QApplication::UnicodeUTF8));
        framebynodetype->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 252, 236);", 0, QApplication::UnicodeUTF8));
        labelbynodetype->setText(QApplication::translate("NSTreeFilterForm", "labelbynodetype", 0, QApplication::UnicodeUTF8));
        comboBoxbynodetype->setItemText(0, QString());
        comboBoxbynodetype->setItemText(1, QApplication::translate("NSTreeFilterForm", ".tag", 0, QApplication::UnicodeUTF8));
        comboBoxbynodetype->setItemText(2, QApplication::translate("NSTreeFilterForm", ".atag", 0, QApplication::UnicodeUTF8));
        comboBoxbynodetype->setItemText(3, QApplication::translate("NSTreeFilterForm", ".group", 0, QApplication::UnicodeUTF8));
        comboBoxbynodetype->setItemText(4, QApplication::translate("NSTreeFilterForm", ".agroup", 0, QApplication::UnicodeUTF8));
        comboBoxbynodetype->setItemText(5, QApplication::translate("NSTreeFilterForm", ".user", 0, QApplication::UnicodeUTF8));

        comboBoxbynodetype->setStyleSheet(QApplication::translate("NSTreeFilterForm", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
        framebyName->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        labelbyName->setText(QApplication::translate("NSTreeFilterForm", "labelbyName", 0, QApplication::UnicodeUTF8));
        lineEditbyName->setStyleSheet(QApplication::translate("NSTreeFilterForm", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(230, 230, 230);", 0, QApplication::UnicodeUTF8));
        framebyBind->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 252, 236);", 0, QApplication::UnicodeUTF8));
        labelbyBind->setText(QApplication::translate("NSTreeFilterForm", "labelbyBind", 0, QApplication::UnicodeUTF8));
        lineEditbyBind->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(255, 255, 255);\n"
"border-color: rgb(74, 255, 46);", 0, QApplication::UnicodeUTF8));
        framebyComment->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        labelbyComment->setText(QApplication::translate("NSTreeFilterForm", "labelbyComment", 0, QApplication::UnicodeUTF8));
        lineEditbyComment->setStyleSheet(QApplication::translate("NSTreeFilterForm", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
        framebyGroup->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        labelbyGroup->setText(QApplication::translate("NSTreeFilterForm", "labelbyGroup", 0, QApplication::UnicodeUTF8));
        framebyGroupType->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        labelbyGroupType->setText(QApplication::translate("NSTreeFilterForm", "labelbyGroupType", 0, QApplication::UnicodeUTF8));
        framebyRtType->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        labelbyRtType->setText(QApplication::translate("NSTreeFilterForm", "labelbyRtType", 0, QApplication::UnicodeUTF8));
        frameButton->setStyleSheet(QApplication::translate("NSTreeFilterForm", "background-color: rgb(236, 236, 236);", 0, QApplication::UnicodeUTF8));
        BtnClear->setText(QApplication::translate("NSTreeFilterForm", "Clear", 0, QApplication::UnicodeUTF8));
        BtnCancel->setText(QApplication::translate("NSTreeFilterForm", "Cancel", 0, QApplication::UnicodeUTF8));
        BntOk->setText(QApplication::translate("NSTreeFilterForm", "Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NSTreeFilterForm: public Ui_NSTreeFilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NSTREEFILTERFORM_H
