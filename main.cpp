#include <QApplication>
#include <QStyleFactory>
#include <mainwindow.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  a.setOrganizationName("SWMicrosystem's");
  a.setOrganizationDomain("swmicrosystems.890m.com");
  a.setApplicationName("SW_Note pad 2.0");
  a.setApplicationVersion("2.0");
  MainWindow w;
  w.setWindowState(Qt::WindowMaximized);
  w.show();
  return a.exec();
}
