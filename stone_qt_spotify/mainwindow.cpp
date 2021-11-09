#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkReply>
#include <QGuiApplication>
#include <QObject>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    spotify = new SpotifyWrapper();
    QObject::connect(spotify, &SpotifyWrapper::authenticated, this, &MainWindow::SetConnected);
    QObject::connect(spotify, &SpotifyWrapper::sendUser, this, &MainWindow::SetUser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Set in the UI the User and show is connected
void MainWindow::SetConnected()
{
    ui->StatusLabel->setText("Conectado");
    ui->AuthPushButton->setEnabled(false);
    spotify->GetUser();
}

//Set in the UI the User and show is connected
void MainWindow::SetUser(QString Str)
{
    ui->UserLabel->setText(Str);
}


void MainWindow::on_AuthPushButton_clicked()
{
    spotify->grant();    
}

