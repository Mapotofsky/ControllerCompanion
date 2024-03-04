#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(), this->height());
    QIcon icon = QIcon(":/img/resources/controller.png");
    setWindowIcon(icon);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("a trayicon example");
    trayIcon->show();

    setWindowTitle(tr("Controller Companion"));
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}
