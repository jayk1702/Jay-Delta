/********************************************************************************
** Form generated from reading UI file 'signuppage.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUPPAGE_H
#define UI_SIGNUPPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signUpPage
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *createUserLabel;
    QLineEdit *userlineEdit;
    QLabel *createPassLabel;
    QLineEdit *createPasslineEdit;
    QLabel *confirmPassLabel;
    QLineEdit *confirmPasslineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *backtoLogInBtn;
    QPushButton *submitBtn;

    void setupUi(QDialog *signUpPage)
    {
        if (signUpPage->objectName().isEmpty())
            signUpPage->setObjectName("signUpPage");
        signUpPage->setWindowModality(Qt::WindowModality::WindowModal);
        signUpPage->resize(450, 300);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(signUpPage->sizePolicy().hasHeightForWidth());
        signUpPage->setSizePolicy(sizePolicy);
        signUpPage->setMinimumSize(QSize(450, 300));
        signUpPage->setMaximumSize(QSize(450, 300));
        signUpPage->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        signUpPage->setModal(false);
        layoutWidget = new QWidget(signUpPage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(40, 80, 356, 151));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 6);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        createUserLabel = new QLabel(layoutWidget);
        createUserLabel->setObjectName("createUserLabel");

        gridLayout->addWidget(createUserLabel, 0, 0, 1, 1);

        userlineEdit = new QLineEdit(layoutWidget);
        userlineEdit->setObjectName("userlineEdit");

        gridLayout->addWidget(userlineEdit, 0, 1, 1, 1);

        createPassLabel = new QLabel(layoutWidget);
        createPassLabel->setObjectName("createPassLabel");

        gridLayout->addWidget(createPassLabel, 1, 0, 1, 1);

        createPasslineEdit = new QLineEdit(layoutWidget);
        createPasslineEdit->setObjectName("createPasslineEdit");

        gridLayout->addWidget(createPasslineEdit, 1, 1, 1, 1);

        confirmPassLabel = new QLabel(layoutWidget);
        confirmPassLabel->setObjectName("confirmPassLabel");

        gridLayout->addWidget(confirmPassLabel, 2, 0, 1, 1);

        confirmPasslineEdit = new QLineEdit(layoutWidget);
        confirmPasslineEdit->setObjectName("confirmPasslineEdit");
        confirmPasslineEdit->setCursor(QCursor(Qt::CursorShape::IBeamCursor));
        confirmPasslineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        gridLayout->addWidget(confirmPasslineEdit, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        backtoLogInBtn = new QPushButton(layoutWidget);
        backtoLogInBtn->setObjectName("backtoLogInBtn");

        horizontalLayout->addWidget(backtoLogInBtn);

        submitBtn = new QPushButton(layoutWidget);
        submitBtn->setObjectName("submitBtn");
        submitBtn->setCursor(QCursor(Qt::CursorShape::ArrowCursor));

        horizontalLayout->addWidget(submitBtn);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(signUpPage);

        QMetaObject::connectSlotsByName(signUpPage);
    } // setupUi

    void retranslateUi(QDialog *signUpPage)
    {
        signUpPage->setWindowTitle(QCoreApplication::translate("signUpPage", "Sign Up ", nullptr));
        createUserLabel->setText(QCoreApplication::translate("signUpPage", "Enter Username", nullptr));
        createPassLabel->setText(QCoreApplication::translate("signUpPage", "Create Password", nullptr));
        confirmPassLabel->setText(QCoreApplication::translate("signUpPage", "Confirm Password", nullptr));
        backtoLogInBtn->setText(QCoreApplication::translate("signUpPage", "Back To Log In", nullptr));
        submitBtn->setText(QCoreApplication::translate("signUpPage", "Submit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signUpPage: public Ui_signUpPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUPPAGE_H
