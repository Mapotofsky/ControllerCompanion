#ifndef TRAYICON_H
#define TRAYICON_H

#include <QObject>
#include <QSystemTrayIcon>

// 前向声明出来QMenu类
class QMenu;

class TrayIcon : public QObject
{
    Q_OBJECT
    // 成员变量
private:
    static QScopedPointer<TrayIcon> self;  // 静态成员变量，用来持有TrayIcon类的唯一实例，实现单例
    QWidget* mainWidget;        // 维持所属的主窗体
    QMenu* menu;                // 维持右键托盘的菜单功能
    QSystemTrayIcon* trayIcon;  // 维持托盘对象

    // 成员函数
public:
    static TrayIcon* Instance();              // 声明单例
    explicit TrayIcon(QObject *parent = nullptr);    // explicit防止隐式类型转换
    void setToolTip(const QString& tip);      // 设置提示信息
    void setMainWidget(QWidget* mainWidget);  // 声明所属的主窗体
    void showMessage(const QString& title,
                     const QString& msg,
                     QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information,
                     int msec = 5000
                     );                       // 声明显示消息
    // 对外获取和设置是否可见
    bool getVisible() const;
    void setVisible(bool visible);

    // 槽函数
public Q_SLOTS:
    void closeAll();        // 退出菜单
    void showMainWidget();  // 显示主窗体的菜单
private slots:
    void iconIsActived(QSystemTrayIcon::ActivationReason reason);

    // 信号函数
signals:
    void trayIconExit();
};

#endif // TRAYICON_H
