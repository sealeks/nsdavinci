/********************************************************************************
** Form generated from reading UI file 'form_setvalue.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_SETVALUE_H
#define UI_FORM_SETVALUE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_setvalue
{
public:
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *labelHeader;
    QRadioButton *rbsetvalue;
    QRadioButton *rbcommand;
    QRadioButton *rbincvnt;
    QRadioButton *rbdeccnt;
    QRadioButton *rbvalid;
    QRadioButton *rbinvalid;
    QHBoxLayout *horizontalLayout;
    QLineEdit *valueedit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btncancel;
    QPushButton *btnok;

    void setupUi(QDialog *form_setvalue)
    {
        if (form_setvalue->objectName().isEmpty())
            form_setvalue->setObjectName(QStringLiteral("form_setvalue"));
        form_setvalue->setWindowModality(Qt::WindowModal);
        form_setvalue->resize(298, 225);
        horizontalLayout_3 = new QHBoxLayout(form_setvalue);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        labelHeader = new QLabel(form_setvalue);
        labelHeader->setObjectName(QStringLiteral("labelHeader"));

        verticalLayout->addWidget(labelHeader);

        rbsetvalue = new QRadioButton(form_setvalue);
        rbsetvalue->setObjectName(QStringLiteral("rbsetvalue"));

        verticalLayout->addWidget(rbsetvalue);

        rbcommand = new QRadioButton(form_setvalue);
        rbcommand->setObjectName(QStringLiteral("rbcommand"));

        verticalLayout->addWidget(rbcommand);

        rbincvnt = new QRadioButton(form_setvalue);
        rbincvnt->setObjectName(QStringLiteral("rbincvnt"));

        verticalLayout->addWidget(rbincvnt);

        rbdeccnt = new QRadioButton(form_setvalue);
        rbdeccnt->setObjectName(QStringLiteral("rbdeccnt"));

        verticalLayout->addWidget(rbdeccnt);

        rbvalid = new QRadioButton(form_setvalue);
        rbvalid->setObjectName(QStringLiteral("rbvalid"));

        verticalLayout->addWidget(rbvalid);

        rbinvalid = new QRadioButton(form_setvalue);
        rbinvalid->setObjectName(QStringLiteral("rbinvalid"));

        verticalLayout->addWidget(rbinvalid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        valueedit = new QLineEdit(form_setvalue);
        valueedit->setObjectName(QStringLiteral("valueedit"));

        horizontalLayout->addWidget(valueedit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btncancel = new QPushButton(form_setvalue);
        btncancel->setObjectName(QStringLiteral("btncancel"));

        horizontalLayout_2->addWidget(btncancel);

        btnok = new QPushButton(form_setvalue);
        btnok->setObjectName(QStringLiteral("btnok"));

        horizontalLayout_2->addWidget(btnok);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(form_setvalue);

        QMetaObject::connectSlotsByName(form_setvalue);
    } // setupUi

    void retranslateUi(QDialog *form_setvalue)
    {
        form_setvalue->setWindowTitle(QApplication::translate("form_setvalue", "form_setvalue", 0));
        labelHeader->setText(QApplication::translate("form_setvalue", "Header", 0));
        rbsetvalue->setText(QApplication::translate("form_setvalue", "rbsetvalue", 0));
        rbcommand->setText(QApplication::translate("form_setvalue", "rbcommand", 0));
        rbincvnt->setText(QApplication::translate("form_setvalue", "rbincvnt", 0));
        rbdeccnt->setText(QApplication::translate("form_setvalue", "rbdecvnt", 0));
        rbvalid->setText(QApplication::translate("form_setvalue", "rbvalid", 0));
        rbinvalid->setText(QApplication::translate("form_setvalue", "rbinvalid", 0));
        btncancel->setText(QApplication::translate("form_setvalue", "Cancel", 0));
        btnok->setText(QApplication::translate("form_setvalue", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class form_setvalue: public Ui_form_setvalue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_SETVALUE_H
