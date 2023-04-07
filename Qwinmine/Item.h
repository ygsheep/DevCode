#pragma once

#include <QLabel>

class Item : public QLabel
{
	Q_OBJECT

public:
	Item(QWidget* parent = nullptr);
	~Item();

	void background(QString Path);

	// 点击
	void mousePressEvent(QMouseEvent* e);
	void mouseReleaseEvent(QMouseEvent* e);
	void mouseDoubleClickEvent(QMouseEvent* e);

	void setisClick(bool click);
	void setisGhost(bool v);
	void setisLabel(bool label);
	void setNumber(int num);
	void setNumber();
	void setxy(int x, int y);
	/// \brief OpenItem
	/// \return void
	/// 点开
	void OpenItem();

	bool getisGhost() const;
	bool getisLabel() const;
	bool getisClick() const;
	int getghostNum()const;

private:
	int x;
	int y;
	bool left_click = false;
	bool right_click = false;
	bool isClick = false;
	bool isGhost = false;
	bool isLabel = false;
	int ghostNumber = 0;
	QPixmap *pix = new QPixmap();

signals:
	void startGame();
	void clickBlanked(int, int);
	void DoubleClicked(int, int);
	void labeled(int, int, bool);
	void gameovered();
	void gamestop();
};
