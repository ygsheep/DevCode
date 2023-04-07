#include "Button.h"
#include "header.h"

Button::Button(QWidget* parent = nullptr, QString title = "")
	: QPushButton(parent)
{
	ui.setupUi(this);
	setText(title);
	setStyleSheet(QString::fromUtf8("QPushButton:hover{\n"
		"		color:#fff;\n"
		"	background-color:#fac03d;\n"
		"}\n"
		"QPushButton{\n"
		"	color:#0a0a0a ;\n"
		"	background-color:#fafafa;\n"
		"	border-radius:4px;\n"
		"	padding:10px  20px;\n"
		"	border:0;\n"
		"}"));
	setMouseTracking(true);
}

Button::~Button()
{}

void Button::setlength(int v) {
	length = v;
}

int Button::getlength() const
{
	return length;
}