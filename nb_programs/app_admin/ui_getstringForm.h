/********************************************************************************
** Form generated from reading UI file 'getstringForm.ui'
**
** Created: Sat 26. Feb 21:25:05 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETSTRINGFORM_H
#define UI_GETSTRINGFORM_H

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

class Ui_getstringForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *getstringForm)
    {
        if (getstringForm->objectName().isEmpty())
            getstringForm->setObjectName(QString::fromUtf8("getstringForm"));
        getstringForm->resize(262, 100);
        getstringForm->setModal(true);
        verticalLayout_2 = new QVBoxLayout(getstringForm);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(getstringForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(10);
        label->setFont(font);

        verticalLayout->addWidget(label);

        lineEdit = new QLineEdit(getstringForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        buttonBox = new QDialogButtonBox(getstringForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(getstringForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), getstringForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), getstringForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(getstringForm);
    } // setupUi

    void retranslateUi(QDialog *getstringForm)
    {
        getstringForm->setWindowTitle(QApplication::translate("getstringForm", "getstringForm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("getstringForm", "TextInput", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class getstringForm: public Ui_getstringForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETSTRINGFORM_H
