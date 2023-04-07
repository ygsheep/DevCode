#pragma once

#include <QPushButton>
#include "ui_Button.h"

class Button : public QPushButton
{
	Q_OBJECT
public:
	Button(QWidget* parent, QString title);
	~Button();

	void setlength(int v);
	int getlength()const;
	// 鼠标移动
	//void mouseMoveEvent(QMouseEvent* e);

	/// 鼠标按下与跳起
	//void mousePressEvent(QMouseEvent* e);
	//void mouseReleaseEvent(QMouseEvent* e);

private:
	// 难度
	int length;
	Ui::ButtonClass ui;
};
