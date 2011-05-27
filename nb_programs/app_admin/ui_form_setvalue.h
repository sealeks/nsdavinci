/********************************************************************************
** Form generated from reading UI file 'form_setvalue.ui'
**
** Created: Fri May 27 19:50:58 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_SETVALUE_H
#define UI_FORM_SETVALUE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QVBoxLayout>

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
            form_setvalue->setObjectName(QString::fromUtf8("form_setvalue"));
        form_setvalue->setWindowModality(Qt::WindowModal);
        form_setvalue->resize(298, 225);
        horizontalLayout_3 = new QHBoxLayout(form_setvalue);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelHeader = new QLabel(form_setvalue);
        labelHeader->setObjectName(QString::fromUtf8("labelHeader"));

        verticalLayout->addWidget(labelHeader);

        rbsetvalue = new QRadioButton(form_setvalue);
        rbsetvalue->setObjectName(QString::fromUtf8("rbsetvalue"));

        verticalLayout->addWidget(rbsetvalue);

        rbcommand = new QRadioButton(form_setvalue);
        rbcommand->setObjectName(QString::fromUtf8("rbcommand"));

        verticalLayout->addWidget(rbcommand);

        rbincvnt = new QRadioButton(form_setvalue);
        rbincvnt->setObjectName(QString::fromUtf8("rbincvnt"));

        verticalLayout->addWidget(rbincvnt);

        rbdeccnt = new QRadioButton(form_setvalue);
        rbdeccnt->setObjectName(QString::fromUtf8("rbdeccnt"));

        verticalLayout->addWidget(rbdeccnt);

        rbvalid = new QRadioButton(form_setvalue);
        rbvalid->setObjectName(QString::fromUtf8("rbvalid"));

        verticalLayout->addWidget(rbvalid);

        rbinvalid = new QRadioButton(form_setvalue);
        rbinvalid->setObjectName(QString::fromUtf8("rbinvalid"));

        verticalLayout->addWidget(rbinvalid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        valueedit = new QLineEdit(form_setvalue);
        valueedit->setObjectName(QString::fromUtf8("valueedit"));

        horizontalLayout->addWidget(valueedit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btncancel = new QPushButton(form_setvalue);
        btncancel->setObjectName(QString::fromUtf8("btncancel"));

        horizontalLayout_2->addWidget(btncancel);

        btnok = new QPushButton(form_setvalue);
        btnok->setObjectName(QString::fromUtf8("btnok"));

        horizontalLayout_2->addWidget(btnok);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(form_setvalue);

        QMetaObject::connectSlotsByName(form_setvalue);
    } // setupUi

    void retranslateUi(QDialog *form_setvalue)
    {
        form_setvalue->setWindowTitle(QApplication::translate("form_setvalue", "form_setvalue", 0, QApplication::UnicodeUTF8));
        labelHeader->setText(QApplication::translate("form_setvalue", "Header", 0, QApplication::UnicodeUTF8));
        rbsetvalue->setText(QApplication::translate("form_setvalue", "rbsetvalue", 0, QApplication::UnicodeUTF8));
        rbcommand->setText(QApplication::translate("form_setvalue", "rbcommand", 0, QApplication::UnicodeUTF8));
        rbincvnt->setText(QApplication::translate("form_setvalue", "rbincvnt", 0, QApplication::UnicodeUTF8));
        rbdeccnt->setText(QApplication::translate("form_setvalue", "rbdecvnt", 0, QApplication::UnicodeUTF8));
        rbvalid->setText(QApplication::translate("form_setvalue", "rbvalid", 0, QApplication::UnicodeUTF8));
        rbinvalid->setText(QApplication::translate("form_setvalue", "rbinvalid", 0, QApplication::UnicodeUTF8));
        btncancel->setText(QApplication::translate("form_setvalue", "Cancel", 0, QApplication::UnicodeUTF8));
        btnok->setText(QApplication::translate("form_setvalue", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_setvalue: public Ui_form_setvalue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_SETVALUE_H
