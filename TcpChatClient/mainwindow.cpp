#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , socket()
    , list()
    , model()
    , name("")
{
    ui->setupUi(this);
    connect(&socket, &QTcpSocket::connected, this, &MainWindow::connected);
    connect(&socket, &QTcpSocket::disconnected, this, &MainWindow::disconnected);
    connect(&socket, &QTcpSocket::readyRead, this, &MainWindow::readyRead);
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
    model.setStringList(list);
    ui->listView->setModel(&model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButtonConnect_clicked()
{
    if (socket.isOpen()) {
        socket.close();
    }
    if (name.isEmpty()) {
        name = QInputDialog::getText(this, "Get name", "What is your name?", QLineEdit::EchoMode::Normal);
    }
    quint16 port  = static_cast<quint16>(ui->lineEditPort->text().toInt());
    socket.connectToHost(ui->lineEditServer->text(), port);
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
    if (!socket.waitForConnected(3000)) {
        on_pushButtonDisconnect_clicked();
        QMessageBox::critical(this, "Error", socket.errorString());
        return;
    }
}

void MainWindow::on_pushButtonDisconnect_clicked()
{
    socket.close();
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
}

void MainWindow::on_pushButtonSend_clicked()
{
    if (!socket.isOpen()) {
        return;
    }
    QByteArray data;
    data.append(name.toUtf8());
    data.append(": ");
    data.append(ui->lineEditMessage->text().toUtf8());
    socket.write(data);
    ui->lineEditMessage->setText("");
}

void MainWindow::connected()
{
    ui->pushButtonConnect->setEnabled(false);
    ui->pushButtonDisconnect->setEnabled(true);
    ui->pushButtonSend->setEnabled(true);
}

void MainWindow::disconnected()
{
    ui->pushButtonConnect->setEnabled(true);
    ui->pushButtonDisconnect->setEnabled(false);
    ui->pushButtonSend->setEnabled(false);
}

void MainWindow::readyRead()
{
    QByteArray data = socket.readAll();
    list.append(QString(data));
    model.setStringList(list);
    ui->listView->scrollToBottom();
}

