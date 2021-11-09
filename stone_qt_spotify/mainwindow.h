#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "spotifywrapper.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AuthPushButton_clicked();
    void SetConnected();
    void SetUser(QString Str);

private:
    Ui::MainWindow *ui;
    SpotifyWrapper* spotify;

};
#endif // MAINWINDOW_H
