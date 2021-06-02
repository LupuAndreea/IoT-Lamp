#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QLabel>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


//Power on off
void MainWindow::on_pushButton_8_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();
    QLabel *label = new QLabel(tr("The lamp is on!"));
    label->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Standard
void MainWindow::on_pushButton_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//commands.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["1"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Study
void MainWindow::on_pushButton_2_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//commands.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["2"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Party
void MainWindow::on_pushButton_3_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//commands.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["3"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Clock
void MainWindow::on_pushButton_4_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//commands.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["4"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Alarm
void MainWindow::on_pushButton_5_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//commands.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["5"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Env
void MainWindow::on_pushButton_6_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//information.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["2"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}

//Gen
void MainWindow::on_pushButton_7_clicked()
{
    QWidget *wdg = new QWidget;
    wdg->show();

    QString val;
    QFile file;
    file.setFileName("//home//stefania//Desktop//Interfata-SmartLamp//information.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
    QJsonValue value = sett2.value(QString("input-buffers"));

    QJsonObject item = value.toObject();
    QJsonDocument Doc(item["1"].toObject());
    QByteArray ba = Doc.toJson();

    QLabel *label = new QLabel();
    QHBoxLayout *layout = new QHBoxLayout();
    label -> setText(QString(ba));
    layout->addWidget(label);
    wdg->setLayout(layout);
}
