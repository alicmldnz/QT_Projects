/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionplay;
    QAction *actionstop;
    QAction *actionpause;
    QAction *actionOpen;
    QWidget *centralwidget;
    QStatusBar *statusbar;
    QToolBar *toolBar;
    QMenuBar *menubar;
    QMenu *menuOpen_File;
    QMenu *menuVideo;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(822, 800);
        actionplay = new QAction(MainWindow);
        actionplay->setObjectName("actionplay");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStart));
        actionplay->setIcon(icon);
        actionplay->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionstop = new QAction(MainWindow);
        actionstop->setObjectName("actionstop");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackStop));
        actionstop->setIcon(icon1);
        actionstop->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionpause = new QAction(MainWindow);
        actionpause->setObjectName("actionpause");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        actionpause->setIcon(icon2);
        actionpause->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::FolderNew));
        actionOpen->setIcon(icon3);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(822, 756));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 822, 22));
        menuOpen_File = new QMenu(menubar);
        menuOpen_File->setObjectName("menuOpen_File");
        menuVideo = new QMenu(menubar);
        menuVideo->setObjectName("menuVideo");
        MainWindow->setMenuBar(menubar);

        toolBar->addAction(actionOpen);
        toolBar->addAction(actionplay);
        toolBar->addAction(actionpause);
        toolBar->addAction(actionstop);
        menubar->addAction(menuOpen_File->menuAction());
        menubar->addAction(menuVideo->menuAction());
        menuOpen_File->addAction(actionOpen);
        menuVideo->addAction(actionplay);
        menuVideo->addAction(actionpause);
        menuVideo->addAction(actionstop);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionplay->setText(QCoreApplication::translate("MainWindow", "play", nullptr));
        actionstop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        actionpause->setText(QCoreApplication::translate("MainWindow", "pause", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
        menuOpen_File->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuVideo->setTitle(QCoreApplication::translate("MainWindow", "Video", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
