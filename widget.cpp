#include "widget.h"
#include "./ui_widget.h"
#include "qmessagebox.h"
#include "trayicon.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    this->setWindowFlags(windowFlags() | Qt::WindowMaximizeButtonHint);  // 禁用最大化按钮
    this->setFixedSize(this->width(), this->height());  // 固定窗口尺寸

    QIcon icon = QIcon(":/img/resources/controller.png");
    setWindowIcon(icon);
    setWindowTitle(tr("Controller Companion"));

    haveTrayIcon = false;
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    //弹出一个选择按钮，是否最小化程序到托盘运行
    QMessageBox::StandardButton button = QMessageBox::question(this,
                                                               "提示",
                                                               "是否最小化到系统托盘",
                                                               QMessageBox::Yes|QMessageBox::No,
                                                               QMessageBox::Yes);
    //不关闭程序，最小化程序到托盘运行
    if(button == QMessageBox::Yes)
    {
        if(!haveTrayIcon)
        {
            //设置托盘所属的主窗体
            TrayIcon::Instance()->setMainWidget(this);
            //设置托盘可见
            TrayIcon::Instance()->setVisible(true);
            haveTrayIcon = true;
        }
        //忽略关闭事件
        event->ignore();
        //隐藏主窗口
        this->hide();
        //设置提示消息，看不见消息的是电脑开启了勿扰模式
        TrayIcon::Instance()->showMessage("自定义最小化托盘",
                                          "已最小化");
        TrayIcon::Instance()->setToolTip("Controller Companion Plus");
    }
    //关闭程序
    else
    {
        event->accept();
    }
}
