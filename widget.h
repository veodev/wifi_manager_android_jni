#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>

namespace Ui
{
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void on_scanWifiButton_released();
    void on_enableWifiButton_released();
    void on_disableWifiButton_released();
    void onCheckConnectionTimerTimeOut();

private:
    Ui::Widget* ui;
    QTimer _connectionCheckTimer;
};

#endif  // WIDGET_H
