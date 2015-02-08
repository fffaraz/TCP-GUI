#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connected = false;
    connect(&socket, SIGNAL(aboutToClose()), this, SLOT(socket_aboutToClose()));
    connect(&socket, SIGNAL(bytesWritten(qint64)), this, SLOT(socket_bytesWritten(qint64)));
    connect(&socket, SIGNAL(connected()), this, SLOT(socket_connected()));
    connect(&socket, SIGNAL(disconnected()), this, SLOT(socket_disconnected()));
    connect(&socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(socket_error()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(socket_readyRead()));
    connect(&socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(socket_stateChanged()));
    ui->btnConnect->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnConnect_clicked()
{
    if(!connected)
    {
        connected = true;
        ui->btnConnect->setText("Disconnect");
        ui->txtIP->setEnabled(false);
        ui->txtPort->setEnabled(false);
        ui->btnSend->setEnabled(true);
        socket.connectToHost(ui->txtIP->text(), ui->txtPort->text().toInt());
    }
    else
    {
        connected = false;
        ui->btnConnect->setText("Connect");
        ui->txtIP->setEnabled(true);
        ui->txtPort->setEnabled(true);
        ui->btnSend->setEnabled(false);
        socket.disconnectFromHost();
    }
}

void MainWindow::on_btnSend_clicked()
{
    socket.write(ui->txtSend->toPlainText().replace('\r', "").replace('\n', "\r\n").toUtf8());
}

void MainWindow::socket_aboutToClose()
{
    log("socket_aboutToClose");
}

void MainWindow::socket_bytesWritten(qint64 bytes)
{
    log("socket_bytesWritten : " + QString::number(bytes));
}

void MainWindow::socket_connected()
{
    log("socket_connected");
}

void MainWindow::socket_disconnected()
{
    log("socket_disconnected");
}

void MainWindow::socket_error()
{
    log("socket_error : " + socket.errorString());
}

void MainWindow::socket_readyRead()
{
    while(socket.bytesAvailable())
    {
        log(socket.readAll());
    }
}

void MainWindow::socket_stateChanged()
{
    //log("socket_stateChanged");
}

void MainWindow::log(QString msg)
{
    ui->txtReceive->appendPlainText(msg +"\n---");
}
