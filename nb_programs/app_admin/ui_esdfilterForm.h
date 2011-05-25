/********************************************************************************
** Form generated from reading UI file 'esdfilterForm.ui'
**
** Created: Sat 26. Feb 20:55:08 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ESDFILTERFORM_H
#define UI_ESDFILTERFORM_H

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

class Ui_esdfilterForm
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

    void setupUi(QDialog *esdfilterForm)
    {
        if (esdfilterForm->objectName().isEmpty())
            esdfilterForm->setObjectName(QString::fromUtf8("esdfilterForm"));
        esdfilterForm->resize(285, 165);
        esdfilterForm->setModal(true);
        verticalLayout_2 = new QVBoxLayout(esdfilterForm);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(esdfilterForm);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        verticalLayout->addWidget(label);

        labeltype = new QLabel(esdfilterForm);
        labeltype->setObjectName(QString::fromUtf8("labeltype"));

        verticalLayout->addWidget(labeltype);

        comboBoxtype = new QComboBox(esdfilterForm);
        comboBoxtype->setObjectName(QString::fromUtf8("comboBoxtype"));

        verticalLayout->addWidget(comboBoxtype);

        labelrange = new QLabel(esdfilterForm);
        labelrange->setObjectName(QString::fromUtf8("labelrange"));

        verticalLayout->addWidget(labelrange);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        labelstart = new QLabel(esdfilterForm);
        labelstart->setObjectName(QString::fromUtf8("labelstart"));

        horizontalLayout->addWidget(labelstart);

        lineEditmin = new QLineEdit(esdfilterForm);
        lineEditmin->setObjectName(QString::fromUtf8("lineEditmin"));

        horizontalLayout->addWidget(lineEditmin);

        labelstop = new QLabel(esdfilterForm);
        labelstop->setObjectName(QString::fromUtf8("labelstop"));

        horizontalLayout->addWidget(labelstop);

        lineEditmax = new QLineEdit(esdfilterForm);
        lineEditmax->setObjectName(QString::fromUtf8("lineEditmax"));

        horizontalLayout->addWidget(lineEditmax);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(esdfilterForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(esdfilterForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), esdfilterForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), esdfilterForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(esdfilterForm);
    } // setupUi

    void retranslateUi(QDialog *esdfilterForm)
    {
        esdfilterForm->setWindowTitle(QApplication::translate("esdfilterForm", "esdfilterForm", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("esdfilterForm", "Filter", 0, QApplication::UnicodeUTF8));
        labeltype->setText(QApplication::translate("esdfilterForm", "typefilter", 0, QApplication::UnicodeUTF8));
        comboBoxtype->clear();
        comboBoxtype->insertItems(0, QStringList()
         << QApplication::translate("esdfilterForm", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "V", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "X", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "Y", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "C", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "S", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "GX", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "GY", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "T", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "SP", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("esdfilterForm", "B", 0, QApplication::UnicodeUTF8)
        );
        labelrange->setText(QApplication::translate("esdfilterForm", "rangel", 0, QApplication::UnicodeUTF8));
        labelstart->setText(QApplication::translate("esdfilterForm", "start", 0, QApplication::UnicodeUTF8));
        labelstop->setText(QApplication::translate("esdfilterForm", "stop", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class esdfilterForm: public Ui_esdfilterForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ESDFILTERFORM_H
