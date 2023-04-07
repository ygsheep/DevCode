#include "Item.h"
#include <QMouseEvent>
#include <qmessagebox.h>
#include <qrandom.h>

Item::Item(QWidget* parent)
  : QLabel(parent)
{
  setStyleSheet(QString::fromUtf8(
                  "text-align:center;"
                  //"padding:10px"
                  ));
  //setFixedSize(pix.size());
  setScaledContents(true);
  setMargin(0);
  pix = new QPixmap();
  background(":/image/image/not_click.png");

}

Item::~Item()
{}

void Item::background(QString Path)
{
  pix->load(Path);
  setPixmap(*pix);
}

void Item::mousePressEvent(QMouseEvent* e)
{
  background(":/image/image/bg_click_0.png");
  if (e->button() == Qt::LeftButton)
    {
      left_click = true;
    }
  if (e->button() == Qt::RightButton)
    {
      right_click = true;
    }

  QLabel::mousePressEvent(e);
}

void Item::mouseReleaseEvent(QMouseEvent* e) {
  emit this->startGame();

  if (left_click && right_click) {
      emit clickBlanked(x, y);
      left_click = right_click = false;
      return;
    }
  if (e->button() == Qt::LeftButton) {
      left_click = false;
      if (isLabel) {
          background(":/image/image/isghost.png");
          return;
        }
      if (isGhost) {
          //QMessageBox::warning(this, "炸弹", "你输了");
          background(":/image/image/ghost_1.png");
          emit gameovered();
        }
      else if (ghostNumber >= 0 && ghostNumber <= 7)
        {
          QString Path = ":/image/image/bg_click_";
          Path += QString::number(ghostNumber) + ".png";
          background(Path);
        }
      emit clickBlanked(x, y);
      isClick = true;
    }
  else if (e->button() == Qt::RightButton)
    {
      isLabel = !isLabel;
      right_click = false;
      if (isClick) {
          isLabel = false;
          QString Path = ":/image/image/bg_click_";
          Path += QString::number(ghostNumber) + ".png";
          background(Path);
          return;
        }
      emit labeled(x, y, isLabel);
    }
}

void Item::mouseDoubleClickEvent(QMouseEvent* e)
{
  //判断是否左键双击
  if (e->buttons() == Qt::LeftButton)
    {
      emit DoubleClicked(x, y);
      return;
    }

  QLabel::mouseDoubleClickEvent(e);
}

void Item::setisClick(bool click)
{
  isClick = click;
  if (isLabel) {
      isClick = false;
      return;
    }
  if (isGhost) {
      background(":/image/image/ghost_1.png");
      emit gameovered();
      return;
    }
  if (isClick) {
      QString Path = ":/image/image/bg_click_";
      Path += QString::number(ghostNumber) + ".png";
      background(Path);
    }
  else {
      background(":/image/image/not_click.png");
    }
}

void Item::setisGhost(bool v)
{
  isGhost = v;
  if (isGhost) {
      ghostNumber = -1;
    }
  else {
      ghostNumber = 0;
    }
}

void Item::setisLabel(bool label)
{
  isLabel = label;
  if (isLabel)
    {
      background(":/image/image/isghost.png");
    }
  else {
      background(":/image/image/not_click.png");
    }
}

void Item::setNumber(int num)
{
  ghostNumber = num;
}

void Item::setNumber()
{
  ghostNumber++;
}

void Item::setxy(int a, int b)
{
  x = a;
  y = b;
}
void Item::OpenItem(){
  isLabel = false;
  isClick = true;
  if(isGhost){
      background(":/image/image/ghost_1.png");
    }
  else{
      QString Path = ":/image/image/bg_click_";
      Path += QString::number(ghostNumber) + ".png";
      background(Path);
    }

}

bool Item::getisGhost() const
{
  return isGhost;
}

bool Item::getisLabel() const
{
  return isLabel;
}

bool Item::getisClick() const
{
  return isClick;
}

int Item::getghostNum() const
{
  return ghostNumber;
}
