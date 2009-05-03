/********************************************************************************
** Form generated from reading ui file 'serverui.ui'
**
** Created: Thu 30. Apr 17:55:27 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SERVERUI_H
#define UI_SERVERUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerUI
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLabel *m_Label;

    void setupUi(QMainWindow *ServerUI)
    {
        if (ServerUI->objectName().isEmpty())
            ServerUI->setObjectName(QString::fromUtf8("ServerUI"));
        ServerUI->resize(93, 62);
        centralWidget = new QWidget(ServerUI);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setMargin(11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        m_Label = new QLabel(centralWidget);
        m_Label->setObjectName(QString::fromUtf8("m_Label"));

        verticalLayout->addWidget(m_Label);

        ServerUI->setCentralWidget(centralWidget);

        retranslateUi(ServerUI);

        QMetaObject::connectSlotsByName(ServerUI);
    } // setupUi

    void retranslateUi(QMainWindow *ServerUI)
    {
        ServerUI->setWindowTitle(QApplication::translate("ServerUI", "Server", 0, QApplication::UnicodeUTF8));
        m_Label->setText(QString());
        Q_UNUSED(ServerUI);
    } // retranslateUi

};

namespace Ui {
    class ServerUI: public Ui_ServerUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERUI_H
