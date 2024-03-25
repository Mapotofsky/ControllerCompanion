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
protected:
    void keyPressEvent(QKeyEvent *event) override {
        // 不调用基类的keyPressEvent，从而忽略所有按键事件
        // QWidget::keyPressEvent(event);
    }

    void keyReleaseEvent(QKeyEvent *event) override {
        // 不调用基类的keyReleaseEvent，从而忽略所有按键事件
        // QWidget::keyReleaseEvent(event);
    }

    // 槽函数
private slots:
    void joystickAxisValue(int js_index, int axis_index, qreal value);
    void joystickButtonValue(int js_index, int button_index, bool pressed);
    void joystickPovValue(int js_index, int pov_index, int angle);
    void on_pushButtonStart_clicked();
};

extern Widget *globalMainWidget;

#endif // WIDGET_H
