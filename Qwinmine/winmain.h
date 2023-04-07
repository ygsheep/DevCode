#ifndef WINMAIN_H
#define WINMAIN_H

#include <QWidget>
#include "PlayWin.h"

namespace Ui {
  class Winmain;
}

class Winmain : public QWidget
{
  Q_OBJECT

public:
  explicit Winmain(QWidget *parent = nullptr);
  ~Winmain();

private:
  Ui::Winmain *ui;
  PlayWin *win;
};

#endif // WINMAIN_H
