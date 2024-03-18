#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include "QJoysticks.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    // 成员变量
private:
    Ui::Widget *ui;
    bool haveTrayIcon;
public:
    QJoysticks* m_joystick;

    // 成员函数
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void closeEvent(QCloseEvent *event) override;

    // 槽函数
private slots:
    void joystickAxisValue(int js_index, int axis_index, qreal value);
    void joystickButtonValue(int js_index, int button_index, bool pressed);
    void joystickPovValue(int js_index, int pov_index, int angle);
    void on_pushButtonStart_clicked();
    void on_pushButtonCheck_clicked();
};

extern Widget *globalMainWidget;

#endif // WIDGET_H
