/* main.cpp
 * This is the driver for the GUI.
 */

#include <QtGui>

#include <Qtilities>

#include "lnplauncher.cpp"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
  Qtilities::CoreGui::QtilitiesApplication app(argc, argv);

  Qtilities::CoreGui::QtilitiesApplication::applicationSessionPath();
  LOG_INITIALIZE();
  Log->setGlobalLogLevel(Logger::Debug);
  QString plain_example = QtilitiesCoreApplication::applicationDirPath() + "/lnp.log";
  Log->newFileEngine("lnp", plain_example);
  Log->toggleQtMsgEngine(true);
  Log->setIsQtMessageHandler(true);

  QString searchPath = QLatin1String(":/");
  QIcon::setThemeSearchPaths(QStringList() << searchPath);
  QIcon::setThemeName( "fallback" );
  MainWindow window;
  Qtilities::CoreGui::QtilitiesApplication::setMainWindow(&window);
  qDebug() << Qtilities::CoreGui::QtilitiesApplication::mainWindow();
  window.init();
  window.show();
  /*LNPLauncher launcher;
  launcher.show();*/

  return app.exec();
}
