/********************************************************************************
** Form generated from reading UI file 'setvalueform.ui'
**
** Created: Sat 26. Feb 21:25:05 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETVALUEFORM_H
#define UI_SETVALUEFORM_H

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

class Ui_setvalueform
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

    void setupUi(QDialog *setvalueform)
    {
        if (setvalueform->objectName().isEmpty())
            setvalueform->setObjectName(QString::fromUtf8("setvalueform"));
        setvalueform->setWindowModality(Qt::WindowModal);
        setvalueform->resize(298, 225);
        horizontalLayout_3 = new QHBoxLayout(setvalueform);
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelHeader = new QLabel(setvalueform);
        labelHeader->setObjectName(QString::fromUtf8("labelHeader"));

        verticalLayout->addWidget(labelHeader);

        rbsetvalue = new QRadioButton(setvalueform);
        rbsetvalue->setObjectName(QString::fromUtf8("rbsetvalue"));

        verticalLayout->addWidget(rbsetvalue);

        rbcommand = new QRadioButton(setvalueform);
        rbcommand->setObjectName(QString::fromUtf8("rbcommand"));

        verticalLayout->addWidget(rbcommand);

        rbincvnt = new QRadioButton(setvalueform);
        rbincvnt->setObjectName(QString::fromUtf8("rbincvnt"));

        verticalLayout->addWidget(rbincvnt);

        rbdeccnt = new QRadioButton(setvalueform);
        rbdeccnt->setObjectName(QString::fromUtf8("rbdeccnt"));

        verticalLayout->addWidget(rbdeccnt);

        rbvalid = new QRadioButton(setvalueform);
        rbvalid->setObjectName(QString::fromUtf8("rbvalid"));

        verticalLayout->addWidget(rbvalid);

        rbinvalid = new QRadioButton(setvalueform);
        rbinvalid->setObjectName(QString::fromUtf8("rbinvalid"));

        verticalLayout->addWidget(rbinvalid);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        valueedit = new QLineEdit(setvalueform);
        valueedit->setObjectName(QString::fromUtf8("valueedit"));

        horizontalLayout->addWidget(valueedit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btncancel = new QPushButton(setvalueform);
        btncancel->setObjectName(QString::fromUtf8("btncancel"));

        horizontalLayout_2->addWidget(btncancel);

        btnok = new QPushButton(setvalueform);
        btnok->setObjectName(QString::fromUtf8("btnok"));

        horizontalLayout_2->addWidget(btnok);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_3->addLayout(verticalLayout);


        retranslateUi(setvalueform);

        QMetaObject::connectSlotsByName(setvalueform);
    } // setupUi

    void retranslateUi(QDialog *setvalueform)
    {
        setvalueform->setWindowTitle(QApplication::translate("setvalueform", "setvalueform", 0, QApplication::UnicodeUTF8));
        labelHeader->setText(QApplication::translate("setvalueform", "Header", 0, QApplication::UnicodeUTF8));
        rbsetvalue->setText(QApplication::translate("setvalueform", "rbsetvalue", 0, QApplication::UnicodeUTF8));
        rbcommand->setText(QApplication::translate("setvalueform", "rbcommand", 0, QApplication::UnicodeUTF8));
        rbincvnt->setText(QApplication::translate("setvalueform", "rbincvnt", 0, QApplication::UnicodeUTF8));
        rbdeccnt->setText(QApplication::translate("setvalueform", "rbdecvnt", 0, QApplication::UnicodeUTF8));
        rbvalid->setText(QApplication::translate("setvalueform", "rbvalid", 0, QApplication::UnicodeUTF8));
        rbinvalid->setText(QApplication::translate("setvalueform", "rbinvalid", 0, QApplication::UnicodeUTF8));
        btncancel->setText(QApplication::translate("setvalueform", "Cancel", 0, QApplication::UnicodeUTF8));
        btnok->setText(QApplication::translate("setvalueform", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class setvalueform: public Ui_setvalueform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETVALUEFORM_H
