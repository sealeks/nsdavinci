/********************************************************************************
** Form generated from reading UI file 'form_getstring.ui'
**
** Created: Mon 20. Jun 18:25:02 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_GETSTRING_H
#define UI_FORM_GETSTRING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_getstring
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *form_getstring)
    {
        if (form_getstring->objectName().isEmpty())
            form_getstring->setObjectName(QString::fromUtf8("form_getstring"));
        form_getstring->resize(262, 100);
        form_getstring->setModal(true);
        verticalLayout_2 = new QVBoxLayout(form_getstring);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(form_getstring);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(form_getstring);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(form_getstring);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(form_getstring);
        QObject::connect(buttonBox, SIGNAL(accepted()), form_getstring, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), form_getstring, SLOT(reject()));

        QMetaObject::connectSlotsByName(form_getstring);
    } // setupUi

    void retranslateUi(QDialog *form_getstring)
    {
        form_getstring->setWindowTitle(QApplication::translate("form_getstring", "form_getstring", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("form_getstring", "TextInput", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_getstring: public Ui_form_getstring {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_GETSTRING_H
