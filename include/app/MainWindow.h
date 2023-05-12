#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <QtGui/QPalette>

#include "AccountWidget.h"

class MainWindow : public QMainWindow
{
public:
    MainWindow();
    static QPalette *darkPalette();

private:
    void createMenus();
    void createWidgets();
    void createLayouts();

    // Menus
    QMenu* m_fileMenu;

    // Widgets
    QWidget* m_mainWidget;
    AccountWidget* m_accountWidget;
};

#endif  // _MAINWINDOW_H_