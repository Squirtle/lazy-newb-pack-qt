/* main.cpp
 * This is the driver for the GUI.
 */
#include <QtGui>
#include "lnplauncher.cpp"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  QString searchPath = QLatin1String(":/");
  QIcon::setThemeSearchPaths(QStringList() << searchPath);
  QIcon::setThemeName( "fallback" );
  MainWindow window;
  window.show();
  /*LNPLauncher launcher;
  launcher.show();*/

  return app.exec();
}
