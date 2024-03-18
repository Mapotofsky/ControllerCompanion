#include <cmath>
#include <iostream>
#include "widget.h"
#include "./ui_widget.h"
#include "qmessagebox.h"
#include "trayicon.h"

Widget *globalMainWidget = nullptr;

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

    // 获取手柄实例
    m_joystick = QJoysticks::getInstance();
    m_joystick->setVirtualJoystickEnabled(false);  // 禁用虚拟手柄
    m_joystick->setVirtualJoystickRange(1);

    globalMainWidget = this;
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

void Widget::joystickAxisValue(int js_index, int axis_index, qreal value)
{
    if (m_joystick->joystickExists(js_index))
    {
        value = std::round(value * 10000) / 100;
        std::cout << "axis index: " << axis_index << ", ";
        std::cout << "value: " << value << std::endl;
        switch (axis_index)
        {
        // 左摇杆 -左+右 [-1, 1] * 100
        case 0:
            ui->label_axis0->setText(QString::number(value));
            break;
        // 左摇杆 -上+下 [-1, 1] * 100
        case 1:
            ui->label_axis1->setText(QString::number(value));
            break;
        // 右摇杆 -左+右 [-1, 1] * 100
        case 2:
            ui->label_axis2->setText(QString::number(value));
            break;
        // 右摇杆 -上+下 [-1, 1] * 100
        case 3:
            ui->label_axis3->setText(QString::number(value));
            break;
        // LT [0, 1] * 100
        case 4:
            ui->label_axis4->setText(QString::number(value));
            break;
        // RT [0, 1] * 100
        case 5:
            ui->label_axis5->setText(QString::number(value));
            break;
        default:
            break;
        }
    }
}

void Widget::joystickButtonValue(int js_index, int button_index, bool pressed)
{
    if (m_joystick->joystickExists(js_index))
    {
        std::cout << "button index: " << button_index << ", ";
        std::cout << "pressed: " << pressed << std::endl;
        switch (button_index)
        {
            // A
        case 0:
            ui->label_but0->setText(QString::number(pressed));
            break;
            // B
        case 1:
            ui->label_but1->setText(QString::number(pressed));
            break;
            // X
        case 2:
            ui->label_but2->setText(QString::number(pressed));
            break;
            // Y
        case 3:
            ui->label_but3->setText(QString::number(pressed));
            break;
            // LB
        case 4:
            ui->label_but4->setText(QString::number(pressed));
            break;
            // RB
        case 5:
            ui->label_but5->setText(QString::number(pressed));
            break;
        case 6:
            ui->label_but6->setText(QString::number(pressed));
            break;
        case 7:
            ui->label_but7->setText(QString::number(pressed));
            break;
            // LS
        case 8:
            ui->label_but8->setText(QString::number(pressed));
            break;
            // RS
        case 9:
            ui->label_but9->setText(QString::number(pressed));
            break;
        default:
            break;
        }
    }
}

void Widget::joystickPovValue(int js_index, int pov_index, int angle)
{
    if (m_joystick->joystickExists(js_index))
    {
        std::cout << "POV index: " << pov_index << ", ";
        std::cout << "angle: " << angle << std::endl;
        if (pov_index == 0)
        {
            ui->label_pov0->setText(QString::number(angle));
            switch (angle)
            {
            case 0:
                ui->label_povd0->setText("↑");
                break;
            case 45:
                ui->label_povd0->setText("↗");
                break;
            case 90:
                ui->label_povd0->setText("→");
                break;
            case 135:
                ui->label_povd0->setText("↘");
                break;
            case 180:
                ui->label_povd0->setText("↓");
                break;
            case 225:
                ui->label_povd0->setText("↙");
                break;
            case 270:
                ui->label_povd0->setText("←");
                break;
            case 315:
                ui->label_povd0->setText("↖");
                break;
            default:
                ui->label_povd0->setText("");
                break;
            }
        }
    }
}

void Widget::on_pushButtonStart_clicked()
{
    if(!haveTrayIcon)
    {
        //设置托盘所属的主窗体
        TrayIcon::Instance()->setMainWidget(this);
        //设置托盘可见
        TrayIcon::Instance()->setVisible(true);
        haveTrayIcon = true;
        //设置提示消息，看不见消息的是电脑开启了勿扰模式
        TrayIcon::Instance()->showMessage("自定义最小化托盘",
                                          "还没想好");
        TrayIcon::Instance()->setToolTip("Controller Companion Plus");
    }

    // 要先创建托盘实例后才能拿到手柄信息

    // 看看有几个
    ui->comboBox->clear();
    QStringList js_names = m_joystick->deviceNames();
    foreach (QString name, js_names)
    {
        ui->comboBox->addItem(name);
    }

    if (ui->comboBox->count())
    {
        // 看看有没有
        ui->label_exist->clear();
        ui->label_exist->setText((m_joystick->joystickExists(ui->comboBox->currentIndex()))?"True":"False");

        // 看看摇杆
        connect(m_joystick, SIGNAL(axisChanged(int,int,qreal)), this, SLOT(joystickAxisValue(int,int,qreal)));
        // 看看按钮
        connect(m_joystick, SIGNAL(buttonChanged(int,int,bool)), this, SLOT(joystickButtonValue(int,int,bool)));
        // 看看十字键
        connect(m_joystick, SIGNAL(povChanged(int,int,int)), this, SLOT(joystickPovValue(int,int,int)));
    }
}

