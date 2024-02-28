#include "../UIHeaders/mainwindow.h"




int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow* w = MainWindow::getWindowInstance();
  w->show();
  //delete w;
  return a.exec();
}
