/********************************************************************************
** Form generated from reading UI file 'form_addserver.ui'
**
** Created: Fri May 27 19:50:58 2011
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADDSERVER_H
#define UI_FORM_ADDSERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_form_addserver
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *labelheader;
    QCheckBox *checkboxlocal;
    QVBoxLayout *verticallayoutconstr;
    QLabel *labelconstr;
    QLineEdit *lineeditconstr;
    QVBoxLayout *verticalLayoutadmin;
    QLabel *labeladmin;
    QLineEdit *lineeditadmin;
    QVBoxLayout *verticallayoutpassword;
    QLabel *labelpassword;
    QLineEdit *lineditpassword;
    QHBoxLayout *horizontalLayout;
    QPushButton *CancelButton;
    QPushButton *OKButton;

    void setupUi(QDialog *form_addserver)
    {
        if (form_addserver->objectName().isEmpty())
            form_addserver->setObjectName(QString::fromUtf8("form_addserver"));
        form_addserver->setWindowModality(Qt::ApplicationModal);
        form_addserver->resize(380, 260);
        form_addserver->setMinimumSize(QSize(380, 260));
        form_addserver->setMaximumSize(QSize(16777215, 260));
        form_addserver->setModal(true);
        verticalLayout_5 = new QVBoxLayout(form_addserver);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labelheader = new QLabel(form_addserver);
        labelheader->setObjectName(QString::fromUtf8("labelheader"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(labelheader->sizePolicy().hasHeightForWidth());
        labelheader->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        labelheader->setFont(font);

        verticalLayout_4->addWidget(labelheader);

        checkboxlocal = new QCheckBox(form_addserver);
        checkboxlocal->setObjectName(QString::fromUtf8("checkboxlocal"));
        checkboxlocal->setEnabled(true);

        verticalLayout_4->addWidget(checkboxlocal);

        verticallayoutconstr = new QVBoxLayout();
        verticallayoutconstr->setObjectName(QString::fromUtf8("verticallayoutconstr"));
        labelconstr = new QLabel(form_addserver);
        labelconstr->setObjectName(QString::fromUtf8("labelconstr"));

        verticallayoutconstr->addWidget(labelconstr);

        lineeditconstr = new QLineEdit(form_addserver);
        lineeditconstr->setObjectName(QString::fromUtf8("lineeditconstr"));

        verticallayoutconstr->addWidget(lineeditconstr);


        verticalLayout_4->addLayout(verticallayoutconstr);

        verticalLayoutadmin = new QVBoxLayout();
        verticalLayoutadmin->setObjectName(QString::fromUtf8("verticalLayoutadmin"));
        labeladmin = new QLabel(form_addserver);
        labeladmin->setObjectName(QString::fromUtf8("labeladmin"));

        verticalLayoutadmin->addWidget(labeladmin);

        lineeditadmin = new QLineEdit(form_addserver);
        lineeditadmin->setObjectName(QString::fromUtf8("lineeditadmin"));

        verticalLayoutadmin->addWidget(lineeditadmin);


        verticalLayout_4->addLayout(verticalLayoutadmin);

        verticallayoutpassword = new QVBoxLayout();
        verticallayoutpassword->setObjectName(QString::fromUtf8("verticallayoutpassword"));
        labelpassword = new QLabel(form_addserver);
        labelpassword->setObjectName(QString::fromUtf8("labelpassword"));

        verticallayoutpassword->addWidget(labelpassword);

        lineditpassword = new QLineEdit(form_addserver);
        lineditpassword->setObjectName(QString::fromUtf8("lineditpassword"));

        verticallayoutpassword->addWidget(lineditpassword);


        verticalLayout_4->addLayout(verticallayoutpassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        CancelButton = new QPushButton(form_addserver);
        CancelButton->setObjectName(QString::fromUtf8("CancelButton"));

        horizontalLayout->addWidget(CancelButton);

        OKButton = new QPushButton(form_addserver);
        OKButton->setObjectName(QString::fromUtf8("OKButton"));

        horizontalLayout->addWidget(OKButton);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(form_addserver);

        QMetaObject::connectSlotsByName(form_addserver);
    } // setupUi

    void retranslateUi(QDialog *form_addserver)
    {
        form_addserver->setWindowTitle(QApplication::translate("form_addserver", "form_addserver", 0, QApplication::UnicodeUTF8));
        labelheader->setText(QApplication::translate("form_addserver", "TextLabel", 0, QApplication::UnicodeUTF8));
        checkboxlocal->setText(QApplication::translate("form_addserver", ".local", 0, QApplication::UnicodeUTF8));
        labelconstr->setText(QApplication::translate("form_addserver", "labelconstr", 0, QApplication::UnicodeUTF8));
        labeladmin->setText(QApplication::translate("form_addserver", "labeladmin", 0, QApplication::UnicodeUTF8));
        labelpassword->setText(QApplication::translate("form_addserver", "TextLabel", 0, QApplication::UnicodeUTF8));
        CancelButton->setText(QApplication::translate("form_addserver", "Cancel", 0, QApplication::UnicodeUTF8));
        OKButton->setText(QApplication::translate("form_addserver", "OK", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class form_addserver: public Ui_form_addserver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADDSERVER_H
