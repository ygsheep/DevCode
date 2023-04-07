#include <QApplication>
#include <PlayWin.h>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  PlayWin w;
  w.show();
  return a.exec();
}
