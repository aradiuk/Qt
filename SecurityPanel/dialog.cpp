#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , savedCode_("")
    , input_("")
    , isAllowedToSave_(true)
{
    ui->setupUi(this);

    connect(ui->btn0, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn1, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn2, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn3, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn4, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn5, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn6, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn7, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn8, &QPushButton::clicked, this, &Dialog::numButtonClicked);
    connect(ui->btn9, &QPushButton::clicked, this, &Dialog::numButtonClicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::numButtonClicked()
{
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        input_ += button->text();
    }
    ui->lineEdit->setText(input_);
}

void Dialog::on_btnSave_clicked()
{
    if (input_.isEmpty()) {
        return;
    }
    if (isAllowedToSave_) {
        isAllowedToSave_ = false;
        savedCode_ = input_;
        QMessageBox::information(this, "Password saved", "Password has been saved.");
    } else if (!isAllowedToSave_) {
        QMessageBox::warning(this, "Verify first", "Please enter correct password before saving a new one.");
    }
    input_.clear();
    ui->lineEdit->setText(input_);
}

void Dialog::on_btnVerify_clicked()
{
    if (input_.isEmpty()) {
        return;
    }
    if (savedCode_.isEmpty()) {
        QMessageBox::information(this, "Password missing", "Password has not been set yet.");
    } else if (savedCode_ == input_) {
        isAllowedToSave_ = true;
        QMessageBox::information(this, "Accepted", "User verification passed.");
    } else {
        isAllowedToSave_ = false;
        QMessageBox::critical(this, "Rejected!", "User verification failed.");
    }
    input_.clear();
    ui->lineEdit->setText(input_);
}

