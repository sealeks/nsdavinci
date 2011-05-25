/********************************************************************************
** Form generated from reading UI file 'form_esdfilter.ui'
**
** Created: Wed May 25 17:21:05 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ESDFILTER_H
#define UI_FORM_ESDFILTER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_esdfilter
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *labeltype;
    QComboBox *comboBoxtype;
    QLabel *labelrange;
    QHBoxLayout *horizontalLayout;
    QLabel *labelstart;
    QLineEdit *lineEditmin;
    QLabel *labelstop;
    QLineEdit *lineEditmax;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *form_esdfilter)
    {
        if (form_esdfilter->objectName().isEmpty())
            form_esdfilter->setObjectName(QString::fromUtf8("form_esdfilter"));
        form_esdfilter->resize(285, 165);
        form_esdfilter->setModal(true);
        verticalLayout_2 = new QVBoxLayout(form_esdfilter);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(form_esdfilter);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        verticalLayout->addWidget(label);

        labeltype = new QLabel(form_esdfilter);
        labeltype->setObjectName(QString::fromUtf8("labeltype"));

        verticalLayout->addWidget(labeltype);

        comboBoxtype = new QComboBox(form_esdfilter);
        comboBoxtype->setObjectName(QString::fromUtf8("comboBoxtype"));

        verticalLayout->addWidget(comboBoxtype);

        labelrange = new QLabel(form_esdfilter);
        labelrange->setObjectName(QString::fromUtf8("labelrange"));

        verticalLayout->addWidget(labelrange);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelstart = new QLabel(form_esdfilter);
        labelstart->setObjectName(QString::fromUtf8("labelstart"));

        horizontalLayout->addWidget(labelstart);

        lineEditmin = new QLineEdit(form_esdfilter);
        lineEditmin->setObjectName(QString::fromUtf8("lineEditmin"));

        horizontalLayout->addWidget(lineEditmin);

        labelstop = new QLabel(form_esdfilter);
        labelstop->setObjectName(QString::fromUtf8("labelstop"));

        horizontalLayout->addWidget(labelstop);

        lineEditmax = new QLineEdit(form_esdfilter);
        lineEditmax->setObjectName(QString::fromUtf8("lineEditmax"));

        horizontalLayout->addWidget(lineEditmax);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(form_esdfilter);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(form_esdfilter);
        QObject::connect(buttonBox, SIGNAL(accepted()), form_esdfilter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), form_esdfilter, SLOT(reject()));

        QMetaObject::connectSlotsByName(form_esdfilter);
    } // setupUi

    void retranslateUi(QDialog *form_esdfilter)
    {
        form_esdfilter->setWindowTitle(QApplication::translate("form_esdfilter", "form_esdfilter", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("form_esdfilter", "Filter", 0, QApplication::UnicodeUTF8));
        labeltype->setText(QApplication::translate("form_esdfilter", "typefilter", 0, QApplication::UnicodeUTF8));
        comboBoxtype->clear();
        comboBoxtype->insertItems(0, QStringList()
         << QApplication::translate("form_esdfilter", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "V", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "S", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "GX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "GY", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "T", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "SP", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("form_esdfilter", "B", 0, QApplication::UnicodeUTF8)
        );
        labelrange->setText(QApplication::translate("form_esdfilter", "rangel", 0, QApplication::UnicodeUTF8));
        labelstart->setText(QApplication::translate("form_esdfilter", "start", 0, QApplication::UnicodeUTF8));
        labelstop->setText(QApplication::translate("form_esdfilter", "stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_esdfilter: public Ui_form_esdfilter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ESDFILTER_H
