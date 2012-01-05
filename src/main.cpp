/* main.cpp
 * This is the driver for the GUI.
 */
#include <QtGui>
#include "lnplauncher.cpp"

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

  LNPLauncher launcher;
  launcher.show();

  return app.exec();
}
