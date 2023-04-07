#pragma once

#include <QMainWindow>
#include "ui_PlayWin.h"
#include "Item.h"

class PlayWin : public QMainWindow
{
  Q_OBJECT


public:
  PlayWin(QWidget* parent = nullptr);
  ~PlayWin();

  void TopInfo();
  void BottomInfo();
  void DateInfo(int l, int r, int label);
  void ConnectInfo();

  // 初始化雷
  void GhostInfo();
  /// @brief 有范围的随机数
  /// @param min
  /// @param max
  /// @return 随机数
  int getRandom(int min, int max);
  ///
  /// \brief gameagain
  ///  重新开始游戏
  void gameagain();
  ///
  /// \brief for_space
  /// \param x
  /// \param y
  /// 翻开附近
  void for_space(int left_x, int left_y);
  ///
  /// \brief for_click
  /// \param x
  /// \param y
  /// 以 x,y 为中心
  void for_click(int left_x, int left_y);

  // 设置难度
  void setCard(int line, int row, int label);
  // 右键标记
  void setLabel(int x, int y, bool isacct);
  // 双击
  void DoubleClick(int x, int y);

  void rangeClick(int a, int b);
  // 游戏失败
  void gamefaill();
  // 游戏胜利
  void gamewin();

signals:
  void backed();
  void setCarded(int v);
  // 开启定时器
  void startTimered();
  void stopTimered();

private:
  // 行
  int line;
  // 列
  int row;
  // 可以标记的标签
  int labelNum;
  int temp = 0;
  int card;
  int ghost;
  float timerNum = 0.0;
  bool isGame = false;

  QTimer* timer;
  QList<QList<Item*>> date;
  QList<QList<int>> spaceList;
  QList<QHBoxLayout *> HBoxList;
  Ui::PlayWinClass ui;
};
