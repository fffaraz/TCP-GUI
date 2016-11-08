#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_btnConnect_clicked();
    void on_btnListen_clicked();
    void on_btnSend_clicked();
    void on_btnClear_clicked();
    void socket_aboutToClose();
    void socket_bytesWritten(qint64 bytes);
    void socket_connected();
    void socket_disconnected();
    void socket_error();
    void socket_readyRead();
    void socket_stateChanged();
    void server_newConnection();

private:
    Ui::MainWindow *ui;
    bool connected;
    QTcpServer server;
    QTcpSocket *socket;

private:
    void log(QString msg);
    void socket_events();
    void update(bool connected);
};

#endif // MAINWINDOW_H
