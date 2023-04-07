#include "winmain.h"
#include "ui_winmain.h"
#include "header.h"
#include "Button.h"

Winmain::Winmain(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::Winmain)
{
  ui->setupUi(this);
  setStyleSheet("background-color:#2c2f3b");
  this->setWindowTitle("扫雷");
  this->setWindowIcon(QIcon(":/image/image/icon.png"));
  setMaximumSize(400, 500);
  Button* b_1 = new  Button(this, "简单");
  Button* b_2 = new  Button(this, "普通");
  Button* b_3 = new  Button(this, "困难");
  ui->box->addWidget(b_1);
  ui->box->addWidget(b_2);
  ui->box->addWidget(b_3);
  win = new PlayWin();

  connect(win, &PlayWin::backed, this, [&]() {
          /*QMessageBox::information(this, "", "主窗口隐藏了");*/
          this->show();
          });
  connect(b_1, &QPushButton::clicked, [&]() {
          this->hide();
          win->show();
          });
}

Winmain::~Winmain()
{
  delete ui;
}
