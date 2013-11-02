/********************************************************************************
** Form generated from reading UI file 'form_getstring.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_GETSTRING_H
#define UI_FORM_GETSTRING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

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
            form_getstring->setObjectName(QStringLiteral("form_getstring"));
        form_getstring->resize(262, 100);
        form_getstring->setModal(true);
        verticalLayout_2 = new QVBoxLayout(form_getstring);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(form_getstring);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(form_getstring);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(form_getstring);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
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
        form_getstring->setWindowTitle(QApplication::translate("form_getstring", "form_getstring", 0));
        label->setText(QApplication::translate("form_getstring", "TextInput", 0));
    } // retranslateUi

};

namespace Ui {
    class form_getstring: public Ui_form_getstring {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_GETSTRING_H
