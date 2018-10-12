#include "widget.h"
#include "ui_widget.h"
#include <QAndroidJniEnvironment>
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
    ui->listWidget->clear();
    QAndroidJniObject resString = QAndroidJniObject::callStaticObjectMethod("JniClass", "scanWifi","(Landroid/content/Context;)Ljava/lang/String;", QtAndroid::androidContext().object());
    QString qtString = resString.toString();
    QStringList splitQtString = qtString.split("///");
    splitQtString.removeLast();
    ui->listWidget->addItems(splitQtString);
}

void Widget::on_enableWifiButton_released()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("JniClass", "enableWifi", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    qDebug() << "===== IS WIFI ENABLED =====:" << res;
}

void Widget::on_disableWifiButton_released()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("JniClass", "disableWifi", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    qDebug() << "===== IS WIFI DISABLED =====:" << res;
}

void Widget::onCheckConnectionTimerTimeOut()
{
    bool res = QAndroidJniObject::callStaticMethod<jboolean>("JniClass", "isWifiEnabled", "(Landroid/content/Context;)Z", QtAndroid::androidContext().object());
    if (res) {
        ui->wifiStateValue->setStyleSheet("color: green");
        ui->wifiStateValue->setText("ON");
    }
    else {
        ui->wifiStateValue->setStyleSheet("color: red");
        ui->wifiStateValue->setText("OFF");
    }
}

void Widget::on_connectWifiButton_released()
{
    QString ssid = ui->listWidget->currentItem()->text();
    QAndroidJniObject ssidJni = QAndroidJniObject::fromString(ssid);
    QAndroidJniObject::callStaticMethod<void>("JniClass", "connectToSsid", "(Landroid/content/Context;Ljava/lang/String;)V", QtAndroid::androidContext().object(), ssidJni.object<jstring>());
}
