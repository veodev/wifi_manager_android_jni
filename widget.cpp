#include "widget.h"
#include "ui_widget.h"
#include <QtAndroidExtras>
#include <QDebug>

const int CHECK_CONNECTION_INTERMAL_MS = 1000;

Widget::Widget(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(&_connectionCheckTimer, &QTimer::timeout, this, &Widget::onCheckConnectionTimerTimeOut);
    _connectionCheckTimer.start(CHECK_CONNECTION_INTERMAL_MS);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_scanWifiButton_released()
{
    QAndroidJniObject::callStaticMethod<void>("MyJavaClass", "scanWifi", "(Landroid/content/Context;)V", QtAndroid::androidContext().object());
}

void Widget::on_enableWifiButton_released()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("MyJavaClass", "enableWifi", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    qDebug() << "===== IS WIFI ENABLED =====:" << res;
}

void Widget::on_disableWifiButton_released()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("MyJavaClass", "disableWifi", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    qDebug() << "===== IS WIFI DISABLED =====:" << res;
}

void Widget::onCheckConnectionTimerTimeOut()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("MyJavaClass", "isWifiEnabled", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    if (res) {
        ui->wifiStateValue->setStyleSheet("color: green");
        ui->wifiStateValue->setText("ON");
    }
    else {
        ui->wifiStateValue->setStyleSheet("color: red");
        ui->wifiStateValue->setText("OFF");
    }
}
