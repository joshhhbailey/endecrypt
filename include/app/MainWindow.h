#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <QtGui/QPalette>

#include "EndecryptWidget.h"

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
    EndecryptWidget* m_endecryptWidget;
};

#endif  // _MAINWINDOW_H_