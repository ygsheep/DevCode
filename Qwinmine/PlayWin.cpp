#include "PlayWin.h"
#include "header.h"
#include "Button.h"
#include <qrandom.h>
#include <QTimer>

PlayWin::PlayWin(QWidget* parent)
  : QMainWindow(parent)
{
  ui.setupUi(this);

  //date = nullptr;
  //setStyleSheet("background-color:#2c2f3b");
  // 设置标题
  this->setWindowTitle("扫雷");
  // 设置图标
  this->setWindowIcon(QIcon(":/image/image/icon.png"));
  // 设置最小窗口大小
  //setMaximumSize(600, 800);
  //setMaximumSize(312, 450);
  timer = new QTimer(this);
  connect(this, &PlayWin::startTimered, this, [&]() {
      if (!isGame) {
          timer->start(1000);
          isGame = true;
          GhostInfo();
        }
    });
  connect(timer, &QTimer::timeout, this, [&]() {
      if (isGame) {
          timerNum += 1.0;
        }
      else {
          timerNum = 0.0;
        }
      ui.timer->setText(QString::number(timerNum));
    });
  // 初始化
  TopInfo(); // top
  DateInfo(9, 9, 10); // date
  BottomInfo(); // bottom
  ConnectInfo();
}

PlayWin::~PlayWin()
{
  date.clear();
}

void PlayWin::TopInfo()
{
  // 狗头 重新开始游戏
  QPixmap pix(":/image/image/once.png");
  ui.onceagnin->setIcon(pix);
  ui.onceagnin->setIconSize(QSize(64, 64));
  connect(ui.onceagnin, &QPushButton::clicked, this,&PlayWin::gameagain);
}

void PlayWin::BottomInfo()
{
  // 清空
  for(auto HL : HBoxList){
      ui.Vbox->removeItem(HL);
      HL->setParent(NULL);
    }
  HBoxList.clear();

  for (int _line = 0; _line < date.size(); _line++)
    {
      QHBoxLayout* HL = new QHBoxLayout(this);

      for (int _row = 0; _row < row; _row++)
        {
          Item* item = new Item();
          item->setxy(_line, _row);
          connect(item, &Item::startGame, this, [&]() {
              emit startTimered();
            });

          void (PlayWin:: * space)(int, int) = &PlayWin::for_space;
          void (PlayWin:: * doubleclick)(int, int) = &PlayWin::DoubleClick;
          void (PlayWin:: * label)(int, int, bool) = &PlayWin::setLabel;
          // 左键单击
          connect(item, &Item::clickBlanked, this, space);
          // 左键双击
          connect(item, &Item::DoubleClicked, this, doubleclick);
          // 右键标记
          connect(item, &Item::labeled, this, label);
          // 游戏失败
          connect(item, &Item::gameovered, this, &PlayWin::gamefaill);

          HL->setSpacing(0);
          HL->setContentsMargins(0, 0, 0, 0);
          HL->addWidget(item, 0, Qt::AlignHCenter | Qt::AlignVCenter);
          date[_line][_row] = item;
        }
      ui.Vbox->addLayout(HL);
      HBoxList.append(HL);
    }
  ui.Vbox->setSpacing(0);
  ui.Vbox->setContentsMargins(0, 0, 0, 0);

}

void PlayWin::DateInfo(int l = 9, int r = 9, int label = 10)
{
  // 行
  line = l;
  // 列
  row = r;

  temp = ghost = labelNum = label;
  // 初始化数组
  date.resize(line);

  for (int _line = 0; _line < date.size(); _line++)
    {
      date[_line].resize(row);
      //for (int _row = 0; _row < date[_line].size(); _row++)
      //{
      //	date[_line][_row]->setText(0);
      //}
    }
  ui.number->setText(QString::number(labelNum));
}

void PlayWin::ConnectInfo() {
  ui.menunew_Game->setTitle("新游戏");
  ui.actionone->setText("初级模式");
  connect(ui.actionone,&QAction::triggered,this,[&](){
      setCard(9,9,10);
    });
  ui.actiontwo->setText("中级模式");
  connect(ui.actiontwo,&QAction::triggered,this,[&](){
      setCard(16,9,40);
    });
  ui.actionthree->setText("困难模式");
  connect(ui.actionthree,&QAction::triggered,this,[&](){
      setCard(16,16,99);
    });

  ui.actionquit->setText("退出游戏");
  ui.actionquit->setShortcut(QCoreApplication::translate("", "ctrl+Q"));
  connect(ui.actionquit, &QAction::triggered, this, &QApplication::quit);
}

void PlayWin::GhostInfo()
{
  QList<QString> arr;
  int ghost_len = 0;
  ui.number->setText(QString::number(ghost));
  while (ghost_len != ghost)
    {
      int a = QRandomGenerator::global()->bounded(line);
      int b = QRandomGenerator::global()->bounded(row);
      QString ss = QString::number(a) + "," + QString::number(b);
      bool isAcct = false;
      for (auto it : arr)
        {
          if (it == ss) {
              isAcct = true;
              break;
            }
        }
      if (isAcct) {
          continue;
        }
      ghost_len++;
      arr << ss;
      // 计算炸弹  附近全部加一
      // 1  1  1
      // 1 炸弹 1
      // 1  1  1
      for (int left_x = a - 1; left_x < a + 2; left_x++)
        {
          for (int left_y = b - 1; left_y < b + 2; left_y++)
            {
              if (left_x >= 0 && left_x < line && left_y >= 0 && left_y < row) {
                  date[left_x][left_y]->setNumber();
                }
            }
        }
      date[a][b]->setisGhost(true);
    }
  //return;
}

int PlayWin::getRandom(int min, int max)
{
  //quint32 seed = quint32(QDateTime::currentDateTime().toSecsSinceEpoch());
  //QRandomGenerator generator(seed);
  srand((unsigned)time(NULL));
  int num = rand() % (max - min) + min;
  return num;
}

void PlayWin::gameagain()
{
  isGame = false;
  timerNum = 0.0;
  timer->stop();
  ui.timer->setText(QString::number(0.0));
  //date.clear();
  for (int x = 0; x < line; x++)
    {
      for (int y = 0; y < row; y++)
        {
          date[x][y]->setisGhost(false);
          date[x][y]->setisLabel(false);
          date[x][y]->setisClick(false);
        }
    }
  labelNum = temp;
  spaceList.clear();
  ui.onceagnin->setIcon(QIcon(":/image/image/once.png"));
}

void PlayWin::for_space(int left_x, int left_y)
{
  int space = 0;
  if (left_x >= 0 && left_x < line && left_y >= 0 && left_y < row) {
      for (int index = 0; index < spaceList.size(); index++)
        {
          if (spaceList[index][0] == left_x && spaceList[index][1] == left_y) {
              return;
            }
        }

      QList<int> temp;
      temp.push_back(left_x);
      temp.push_back(left_y);
      spaceList.push_back(temp);

      if (date[left_x][left_y]->getghostNum() == space) {
          date[left_x][left_y]->setisClick(true);
          //for_click(left_x, left_y);
          for (int a = left_x - 1; a < left_x + 2; a++) {
              for(int b = left_y -1 ; b < left_y +2;b++){
                  for_space(a,b);
                }
            }
        }
      else
        {
          date[left_x][left_y]->setisClick(true);
        }
    }
  this->gamewin();
}

void PlayWin::for_click(int x, int y)
{
  int left_x = x - 1;
  int left_y = y - 1;

  for (int index = 0; index < spaceList.size(); index++)
    {
      if (spaceList[index][0] == left_x && spaceList[index][1] == left_y) {
          return;
        }
    }
  QList<int> temp;
  temp.push_back(left_x);
  temp.push_back(left_y);
  spaceList.push_back(temp);
  for (int a = left_x; a <= left_x + 2; a++)
    {
      for (int b = left_y; b <= left_y + 2; b++)
        {
          if (a >= 0 && a < line && b >= 0 && b < row)
            {
              date[a][b]->setisClick(true);
              if(date[a][b]->getghostNum() == 0){
                  for_click(a,b);
                }
            }
        }
    }
}

void PlayWin::setCard(int line = 9, int row = 9, int label = 10)
{
  DateInfo(line,row,label);
  BottomInfo();
  gameagain();
}

void PlayWin::setLabel(int x, int y, bool isacct)
{
  isacct ? labelNum-- : labelNum++;
  if (labelNum < 0) {
      date[x][y]->setisLabel(false);
      labelNum++;
      return;
    }
  date[x][y]->setisLabel(isacct);
  ui.number->setText(QString::number(labelNum));
}

void PlayWin::DoubleClick(int x, int y)
{
  int left_x = x - 1;
  int left_y = y - 1;
  int ghost_sum = date[x][y]->getghostNum();
  for (int a = left_x; a <= left_x + 2; a++)
    {
      for (int b = left_y; b <= left_y + 2; b++)
        {
          if (a >= 0 && a < line && b >= 0 && b < row)
            {
              if (date[a][b]->getisLabel())
                {
                  ghost_sum--;
                }
            }
        }
    }
  if (ghost_sum != 0)
    {
      return;
    }
  for (int a = left_x; a <= left_x + 2; a++)
    {
      for (int b = left_y; b <= left_y + 2; b++)
        {
          if (a >= 0 && a < line && b >= 0 && b < row)
            {
              rangeClick(a,b);
              if (date[a][b]->getghostNum() == 0 && !date[a][b]->getisLabel() ) {
                  for_click(a, b);
                }
            }
        }
    }
  this->gamewin();
}

void PlayWin::rangeClick(int a, int b)
{
  //  for (int index = 0; index < spaceList.size(); index++)
  //    {
  //      if (spaceList[index][0] == a && spaceList[index][1] == b) {
  //          return;
  //        }
  //    }
  //  QList<int> temp;
  //  temp.push_back(a);
  //  temp.push_back(b);
  //  spaceList.push_back(temp);
  date[a][b]->setisClick(true);
}

void PlayWin::gamefaill()
{
  if (!isGame) return;
  for(int x = 0; x < line; x++){
      for(int y = 0; y < row ; y++){
          date[x][y]->OpenItem();
        }
    }
  isGame = false;
  timer->stop();
  ui.onceagnin->setIcon(QIcon(":/image/image/waring.png"));
//  QMessageBox::critical(this,"游戏失败","你输了");
}

void PlayWin::gamewin()
{
  int sum = 0;
  for (int a = 0; a < row; a++) {
      for(int b = 0 ; b < line; b++)
        sum += date[a][b]->getisClick() ? 1 : 0;
    }
  if(sum == (row * line - ghost) && isGame){
      timer->stop();
      QMessageBox msgBox;
      msgBox.setText("你赢了！");
      msgBox.exec();
    }
}
