/********************************************************************************
** Form generated from reading UI file 'form_filter.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_FILTER_H
#define UI_FORM_FILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_filter
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

    void setupUi(QDialog *form_filter)
    {
        if (form_filter->objectName().isEmpty())
            form_filter->setObjectName(QStringLiteral("form_filter"));
        form_filter->setWindowModality(Qt::ApplicationModal);
        form_filter->resize(378, 1010);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(form_filter->sizePolicy().hasHeightForWidth());
        form_filter->setSizePolicy(sizePolicy);
        form_filter->setMinimumSize(QSize(378, 0));
        form_filter->setAutoFillBackground(false);
        form_filter->setSizeGripEnabled(true);
        verticalLayout_6 = new QVBoxLayout(form_filter);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout_6->setSizeConstraint(QLayout::SetMinAndMaxSize);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
        frameHeader = new QFrame(form_filter);
        frameHeader->setObjectName(QStringLiteral("frameHeader"));
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
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setSizeConstraint(QLayout::SetDefaultConstraint);
        HeadLineLable = new QLabel(frameHeader);
        HeadLineLable->setObjectName(QStringLiteral("HeadLineLable"));

        verticalLayout_5->addWidget(HeadLineLable);


        verticalLayout->addWidget(frameHeader);

        framebynodetype = new QFrame(form_filter);
        framebynodetype->setObjectName(QStringLiteral("framebynodetype"));
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
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        labelbynodetype = new QLabel(framebynodetype);
        labelbynodetype->setObjectName(QStringLiteral("labelbynodetype"));

        verticalLayout_9->addWidget(labelbynodetype);

        comboBoxbynodetype = new QComboBox(framebynodetype);
        comboBoxbynodetype->addItem(QString());
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/icon/ntGT.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon, QString());
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/icon/ntEvent.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon1, QString());
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/icon/ntOBase.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/icon/cdtGroup.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/icon/ntA.bmp"), QSize(), QIcon::Normal, QIcon::Off);
        comboBoxbynodetype->addItem(icon4, QString());
        comboBoxbynodetype->setObjectName(QStringLiteral("comboBoxbynodetype"));
        comboBoxbynodetype->setMinimumSize(QSize(0, 20));
        comboBoxbynodetype->setMaximumSize(QSize(16777215, 20));

        verticalLayout_9->addWidget(comboBoxbynodetype);


        verticalLayout->addWidget(framebynodetype);

        framebyName = new QFrame(form_filter);
        framebyName->setObjectName(QStringLiteral("framebyName"));
        sizePolicy2.setHeightForWidth(framebyName->sizePolicy().hasHeightForWidth());
        framebyName->setSizePolicy(sizePolicy2);
        framebyName->setMinimumSize(QSize(350, 58));
        framebyName->setMaximumSize(QSize(16777215, 58));
        framebyName->setAutoFillBackground(false);
        framebyName->setFrameShape(QFrame::StyledPanel);
        framebyName->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(framebyName);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        labelbyName = new QLabel(framebyName);
        labelbyName->setObjectName(QStringLiteral("labelbyName"));

        verticalLayout_2->addWidget(labelbyName);

        lineEditbyName = new QLineEdit(framebyName);
        lineEditbyName->setObjectName(QStringLiteral("lineEditbyName"));
        lineEditbyName->setMinimumSize(QSize(0, 20));
        lineEditbyName->setMaximumSize(QSize(16777215, 20));

        verticalLayout_2->addWidget(lineEditbyName);


        verticalLayout->addWidget(framebyName);

        framebyBind = new QFrame(form_filter);
        framebyBind->setObjectName(QStringLiteral("framebyBind"));
        sizePolicy2.setHeightForWidth(framebyBind->sizePolicy().hasHeightForWidth());
        framebyBind->setSizePolicy(sizePolicy2);
        framebyBind->setMinimumSize(QSize(350, 58));
        framebyBind->setMaximumSize(QSize(16777215, 58));
        framebyBind->setAutoFillBackground(false);
        framebyBind->setFrameShape(QFrame::StyledPanel);
        framebyBind->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(framebyBind);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        labelbyBind = new QLabel(framebyBind);
        labelbyBind->setObjectName(QStringLiteral("labelbyBind"));

        verticalLayout_3->addWidget(labelbyBind);

        lineEditbyBind = new QLineEdit(framebyBind);
        lineEditbyBind->setObjectName(QStringLiteral("lineEditbyBind"));
        lineEditbyBind->setMinimumSize(QSize(0, 20));
        lineEditbyBind->setMaximumSize(QSize(16777215, 20));

        verticalLayout_3->addWidget(lineEditbyBind);


        verticalLayout->addWidget(framebyBind);

        framebyComment = new QFrame(form_filter);
        framebyComment->setObjectName(QStringLiteral("framebyComment"));
        sizePolicy2.setHeightForWidth(framebyComment->sizePolicy().hasHeightForWidth());
        framebyComment->setSizePolicy(sizePolicy2);
        framebyComment->setMinimumSize(QSize(350, 58));
        framebyComment->setMaximumSize(QSize(16777215, 58));
        framebyComment->setAutoFillBackground(false);
        framebyComment->setFrameShape(QFrame::StyledPanel);
        framebyComment->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(framebyComment);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelbyComment = new QLabel(framebyComment);
        labelbyComment->setObjectName(QStringLiteral("labelbyComment"));

        verticalLayout_4->addWidget(labelbyComment);

        lineEditbyComment = new QLineEdit(framebyComment);
        lineEditbyComment->setObjectName(QStringLiteral("lineEditbyComment"));
        lineEditbyComment->setMinimumSize(QSize(0, 20));
        lineEditbyComment->setMaximumSize(QSize(16777215, 20));

        verticalLayout_4->addWidget(lineEditbyComment);


        verticalLayout->addWidget(framebyComment);

        framebyGroup = new QFrame(form_filter);
        framebyGroup->setObjectName(QStringLiteral("framebyGroup"));
        sizePolicy2.setHeightForWidth(framebyGroup->sizePolicy().hasHeightForWidth());
        framebyGroup->setSizePolicy(sizePolicy2);
        framebyGroup->setMinimumSize(QSize(350, 100));
        framebyGroup->setMaximumSize(QSize(16777215, 300));
        framebyGroup->setAutoFillBackground(false);
        framebyGroup->setFrameShape(QFrame::StyledPanel);
        framebyGroup->setFrameShadow(QFrame::Raised);
        verticalLayout_11 = new QVBoxLayout(framebyGroup);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        labelbyGroup = new QLabel(framebyGroup);
        labelbyGroup->setObjectName(QStringLiteral("labelbyGroup"));

        verticalLayout_11->addWidget(labelbyGroup);

        listWidgetbyGroup = new QListWidget(framebyGroup);
        listWidgetbyGroup->setObjectName(QStringLiteral("listWidgetbyGroup"));

        verticalLayout_11->addWidget(listWidgetbyGroup);


        verticalLayout->addWidget(framebyGroup);

        framebyGroupType = new QFrame(form_filter);
        framebyGroupType->setObjectName(QStringLiteral("framebyGroupType"));
        sizePolicy2.setHeightForWidth(framebyGroupType->sizePolicy().hasHeightForWidth());
        framebyGroupType->setSizePolicy(sizePolicy2);
        framebyGroupType->setMinimumSize(QSize(350, 100));
        framebyGroupType->setMaximumSize(QSize(16777215, 300));
        framebyGroupType->setAutoFillBackground(false);
        framebyGroupType->setFrameShape(QFrame::StyledPanel);
        framebyGroupType->setFrameShadow(QFrame::Raised);
        verticalLayout_12 = new QVBoxLayout(framebyGroupType);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        labelbyGroupType = new QLabel(framebyGroupType);
        labelbyGroupType->setObjectName(QStringLiteral("labelbyGroupType"));

        verticalLayout_12->addWidget(labelbyGroupType);

        listWidgetbyGroupType = new QListWidget(framebyGroupType);
        listWidgetbyGroupType->setObjectName(QStringLiteral("listWidgetbyGroupType"));

        verticalLayout_12->addWidget(listWidgetbyGroupType);


        verticalLayout->addWidget(framebyGroupType);

        framebyRtType = new QFrame(form_filter);
        framebyRtType->setObjectName(QStringLiteral("framebyRtType"));
        sizePolicy2.setHeightForWidth(framebyRtType->sizePolicy().hasHeightForWidth());
        framebyRtType->setSizePolicy(sizePolicy2);
        framebyRtType->setMinimumSize(QSize(350, 100));
        framebyRtType->setMaximumSize(QSize(16777215, 300));
        framebyRtType->setAutoFillBackground(false);
        framebyRtType->setFrameShape(QFrame::StyledPanel);
        framebyRtType->setFrameShadow(QFrame::Raised);
        verticalLayout_13 = new QVBoxLayout(framebyRtType);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        labelbyRtType = new QLabel(framebyRtType);
        labelbyRtType->setObjectName(QStringLiteral("labelbyRtType"));

        verticalLayout_13->addWidget(labelbyRtType);

        listWidgetbyRtType = new QListWidget(framebyRtType);
        listWidgetbyRtType->setObjectName(QStringLiteral("listWidgetbyRtType"));

        verticalLayout_13->addWidget(listWidgetbyRtType);


        verticalLayout->addWidget(framebyRtType);

        frameButton = new QFrame(form_filter);
        frameButton->setObjectName(QStringLiteral("frameButton"));
        sizePolicy2.setHeightForWidth(frameButton->sizePolicy().hasHeightForWidth());
        frameButton->setSizePolicy(sizePolicy2);
        frameButton->setMinimumSize(QSize(350, 50));
        frameButton->setMaximumSize(QSize(16777215, 50));
        frameButton->setAutoFillBackground(false);
        frameButton->setFrameShape(QFrame::StyledPanel);
        frameButton->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frameButton);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        BtnClear = new QPushButton(frameButton);
        BtnClear->setObjectName(QStringLiteral("BtnClear"));
        BtnClear->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(BtnClear);

        BtnCancel = new QPushButton(frameButton);
        BtnCancel->setObjectName(QStringLiteral("BtnCancel"));
        BtnCancel->setMaximumSize(QSize(80, 16777215));
        BtnCancel->setAutoExclusive(false);

        horizontalLayout->addWidget(BtnCancel);

        BntOk = new QPushButton(frameButton);
        BntOk->setObjectName(QStringLiteral("BntOk"));
        BntOk->setMaximumSize(QSize(80, 16777215));
        BntOk->setDefault(false);
        BntOk->setFlat(false);

        horizontalLayout->addWidget(BntOk);


        verticalLayout->addWidget(frameButton);


        verticalLayout_6->addLayout(verticalLayout);


        retranslateUi(form_filter);

        QMetaObject::connectSlotsByName(form_filter);
    } // setupUi

    void retranslateUi(QDialog *form_filter)
    {
        form_filter->setWindowTitle(QApplication::translate("form_filter", "form_filter", 0));
        frameHeader->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        HeadLineLable->setText(QApplication::translate("form_filter", ".Finder", 0));
        framebynodetype->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 252, 236);", 0));
        labelbynodetype->setText(QApplication::translate("form_filter", "labelbynodetype", 0));
        comboBoxbynodetype->setItemText(0, QString());
        comboBoxbynodetype->setItemText(1, QApplication::translate("form_filter", ".tag", 0));
        comboBoxbynodetype->setItemText(2, QApplication::translate("form_filter", ".atag", 0));
        comboBoxbynodetype->setItemText(3, QApplication::translate("form_filter", ".group", 0));
        comboBoxbynodetype->setItemText(4, QApplication::translate("form_filter", ".agroup", 0));
        comboBoxbynodetype->setItemText(5, QApplication::translate("form_filter", ".user", 0));

        comboBoxbynodetype->setStyleSheet(QApplication::translate("form_filter", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(255, 255, 255);", 0));
        framebyName->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        labelbyName->setText(QApplication::translate("form_filter", "labelbyName", 0));
        lineEditbyName->setStyleSheet(QApplication::translate("form_filter", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(230, 230, 230);", 0));
        framebyBind->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 252, 236);", 0));
        labelbyBind->setText(QApplication::translate("form_filter", "labelbyBind", 0));
        lineEditbyBind->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(255, 255, 255);\n"
"border-color: rgb(74, 255, 46);", 0));
        framebyComment->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        labelbyComment->setText(QApplication::translate("form_filter", "labelbyComment", 0));
        lineEditbyComment->setStyleSheet(QApplication::translate("form_filter", "border-color: rgb(221, 221, 221);\n"
"background-color: rgb(255, 255, 255);", 0));
        framebyGroup->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        labelbyGroup->setText(QApplication::translate("form_filter", "labelbyGroup", 0));
        framebyGroupType->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        labelbyGroupType->setText(QApplication::translate("form_filter", "labelbyGroupType", 0));
        framebyRtType->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        labelbyRtType->setText(QApplication::translate("form_filter", "labelbyRtType", 0));
        frameButton->setStyleSheet(QApplication::translate("form_filter", "background-color: rgb(236, 236, 236);", 0));
        BtnClear->setText(QApplication::translate("form_filter", "Clear", 0));
        BtnCancel->setText(QApplication::translate("form_filter", "Cancel", 0));
        BntOk->setText(QApplication::translate("form_filter", "Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class form_filter: public Ui_form_filter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_FILTER_H
