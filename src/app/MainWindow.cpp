#include <QtWidgets/QMenuBar>
#include <QtGui/QColor>
#include <QtWidgets/QHBoxLayout>

#include "MainWindow.h"

MainWindow::MainWindow()
{
    setWindowTitle(tr("endecrypt v1.0.0"));
    setFixedWidth(720);
    setFixedHeight(130);

    createMenus();
    createWidgets();
    createLayouts();
}

void MainWindow::createMenus()
{
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(tr("&Exit"), this, &QWidget::close);
}

void MainWindow::createWidgets()
{
    m_mainWidget = new QWidget();
    setCentralWidget(m_mainWidget);

    m_accountWidget = new AccountWidget();
}

void MainWindow::createLayouts()
{
    QHBoxLayout* mainLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(m_accountWidget);
    m_mainWidget->setLayout(mainLayout);
}

QPalette *MainWindow::darkPalette()
{
    QPalette *darkPalette = new QPalette();
    darkPalette->setColor(QPalette::Window, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::WindowText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette->setColor(QPalette::AlternateBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::ToolTipBase, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Text, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::Button, QColor(45, 45, 45));
    darkPalette->setColor(QPalette::ButtonText, QColor(208, 208, 208));
    darkPalette->setColor(QPalette::BrightText, Qt::red);
    darkPalette->setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette->setColor(QPalette::Link, Qt::gray);
    return darkPalette;
}