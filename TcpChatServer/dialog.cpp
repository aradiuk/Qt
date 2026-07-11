#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , btnBack()
    , btnNext()
    , server()
{
    ui->setupUi(this);
    btnBack = new QPushButton("Back", this);
    btnNext = new QPushButton("Next", this);
    ui->buttonBox->addButton(btnBack, QDialogButtonBox::ActionRole);
    ui->buttonBox->addButton(btnNext, QDialogButtonBox::ActionRole);
    connect(btnBack, &QPushButton::clicked, this, &Dialog::back);
    connect(btnNext, &QPushButton::clicked, this, &Dialog::next);
    connect(&server, &Server::changed, this, &Dialog::changed);
    enableButtons();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButtonStart_clicked()
{
    quint16 port = static_cast<quint16>(ui->spinBoxPort->value());
    server.welcomeMessage = ui->lineEditWelcome->text() + "\r\n";
    if (!server.listen(QHostAddress::Any, port)) {
        QMessageBox::critical(this, "Error", server.errorString());
        return;
    }
    ui->lblChanged->setText("Listening...");
    enableButtons();
}

void Dialog::on_pushButtonStop_clicked()
{
    server.close();
    ui->lblChanged->setText("Server is offline");
    enableButtons();
}

void Dialog::next()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() + 1);
    enableButtons();
}

void Dialog::back()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->currentIndex() - 1);
    enableButtons();
}

void Dialog::changed()
{
    ui->lblChanged->setText(QString("There are %0 clients connected.").arg(server.count()));
}

void Dialog::enableButtons()
{
    ui->pushButtonStart->setEnabled(!server.isListening());
    ui->pushButtonStop->setEnabled(server.isListening());
    const int currentIdx = ui->stackedWidget->currentIndex();
    if (currentIdx == 0) {
        btnBack->setEnabled(false);
        btnNext->setEnabled(true);
    } else if (currentIdx == ui->stackedWidget->count() - 1) {
        btnNext->setEnabled(false);
        btnBack->setEnabled(true);
    } else {
        btnBack->setEnabled(true);
        btnNext->setEnabled(true);
    }
}

