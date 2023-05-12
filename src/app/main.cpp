#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>

#include "MainWindow.h"

int main(int argc, char **argv)
{
  // Create Qt application
  QApplication app(argc, argv);
  app.setStyle(QStyleFactory::create("fusion"));
  app.setPalette(*MainWindow::darkPalette());

  // Create application window
  MainWindow window;
  window.show();

  return app.exec();
}
