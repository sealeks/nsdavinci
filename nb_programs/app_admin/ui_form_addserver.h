/********************************************************************************
** Form generated from reading UI file 'form_addserver.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_ADDSERVER_H
#define UI_FORM_ADDSERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

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
            form_addserver->setObjectName(QStringLiteral("form_addserver"));
        form_addserver->setWindowModality(Qt::ApplicationModal);
        form_addserver->resize(380, 260);
        form_addserver->setMinimumSize(QSize(380, 260));
        form_addserver->setMaximumSize(QSize(16777215, 260));
        form_addserver->setModal(true);
        verticalLayout_5 = new QVBoxLayout(form_addserver);
        verticalLayout_5->setSpacing(1);
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        labelheader = new QLabel(form_addserver);
        labelheader->setObjectName(QStringLiteral("labelheader"));
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
        checkboxlocal->setObjectName(QStringLiteral("checkboxlocal"));
        checkboxlocal->setEnabled(true);

        verticalLayout_4->addWidget(checkboxlocal);

        verticallayoutconstr = new QVBoxLayout();
        verticallayoutconstr->setObjectName(QStringLiteral("verticallayoutconstr"));
        labelconstr = new QLabel(form_addserver);
        labelconstr->setObjectName(QStringLiteral("labelconstr"));

        verticallayoutconstr->addWidget(labelconstr);

        lineeditconstr = new QLineEdit(form_addserver);
        lineeditconstr->setObjectName(QStringLiteral("lineeditconstr"));

        verticallayoutconstr->addWidget(lineeditconstr);


        verticalLayout_4->addLayout(verticallayoutconstr);

        verticalLayoutadmin = new QVBoxLayout();
        verticalLayoutadmin->setObjectName(QStringLiteral("verticalLayoutadmin"));
        labeladmin = new QLabel(form_addserver);
        labeladmin->setObjectName(QStringLiteral("labeladmin"));

        verticalLayoutadmin->addWidget(labeladmin);

        lineeditadmin = new QLineEdit(form_addserver);
        lineeditadmin->setObjectName(QStringLiteral("lineeditadmin"));

        verticalLayoutadmin->addWidget(lineeditadmin);


        verticalLayout_4->addLayout(verticalLayoutadmin);

        verticallayoutpassword = new QVBoxLayout();
        verticallayoutpassword->setObjectName(QStringLiteral("verticallayoutpassword"));
        labelpassword = new QLabel(form_addserver);
        labelpassword->setObjectName(QStringLiteral("labelpassword"));

        verticallayoutpassword->addWidget(labelpassword);

        lineditpassword = new QLineEdit(form_addserver);
        lineditpassword->setObjectName(QStringLiteral("lineditpassword"));

        verticallayoutpassword->addWidget(lineditpassword);


        verticalLayout_4->addLayout(verticallayoutpassword);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(10, -1, 10, -1);
        CancelButton = new QPushButton(form_addserver);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        horizontalLayout->addWidget(CancelButton);

        OKButton = new QPushButton(form_addserver);
        OKButton->setObjectName(QStringLiteral("OKButton"));

        horizontalLayout->addWidget(OKButton);


        verticalLayout_4->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(form_addserver);

        QMetaObject::connectSlotsByName(form_addserver);
    } // setupUi

    void retranslateUi(QDialog *form_addserver)
    {
        form_addserver->setWindowTitle(QApplication::translate("form_addserver", "form_addserver", 0));
        labelheader->setText(QApplication::translate("form_addserver", "TextLabel", 0));
        checkboxlocal->setText(QApplication::translate("form_addserver", ".local", 0));
        labelconstr->setText(QApplication::translate("form_addserver", "labelconstr", 0));
        labeladmin->setText(QApplication::translate("form_addserver", "labeladmin", 0));
        labelpassword->setText(QApplication::translate("form_addserver", "TextLabel", 0));
        CancelButton->setText(QApplication::translate("form_addserver", "Cancel", 0));
        OKButton->setText(QApplication::translate("form_addserver", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class form_addserver: public Ui_form_addserver {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_ADDSERVER_H
