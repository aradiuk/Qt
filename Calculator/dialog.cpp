#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QSizePolicy>

// Ideally this should be implemented using some kind of a simple
// state-machine to not have these weird "wasEqualClicked_"-like workarounds,
// but my point was to do something with Qt Widgets and not to perfect the
// calculator algorithm.

static Operation getOperation(const QString& buttonText)
{
    if (buttonText == "+") {
        return Operation::Add;
    } else if (buttonText == "-") {
        return Operation::Substract;
    } else if (buttonText == "*") {
        return Operation::Multiply;
    } else if (buttonText == "/") {
        return Operation::Divide;
    }
    return Operation::None;
}

static QString getOperationText(const Operation operation)
{
    if (operation == Operation::Add) {
        return "+";
    } else if (operation == Operation::Substract) {
        return "-";
    } else if (operation == Operation::Multiply) {
        return "*";
    } else if (operation == Operation::Divide) {
        return "/";
    }
    return "+";
}

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
    , left_("")
    , right_("")
    , operation_(Operation::None)
    , wasEqualClicked_(false)
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

    connect(ui->btnAdd, &QPushButton::clicked, this, &Dialog::operationButtonClicked);
    connect(ui->btnDivide, &QPushButton::clicked, this, &Dialog::operationButtonClicked);
    connect(ui->btnMultiply, &QPushButton::clicked, this, &Dialog::operationButtonClicked);
    connect(ui->btnSubstract, &QPushButton::clicked, this, &Dialog::operationButtonClicked);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::numButtonClicked()
{
    static constexpr uint8_t maxSize = 10;
    clickAfterEqual();
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        const QString& input = button->text();
        const bool isOperationEmpty = (operation_ == Operation::None);
        QString& argument = (isOperationEmpty ? left_ : right_);
        if ((argument == "0") && (input == "0")) {
            return;
        }
        if (argument.size() > maxSize) {
            return;
        }
        argument += input;
        if (isOperationEmpty) {
            ui->lineEdit->setText(argument);
        } else {
            ui->lineEdit->setText(left_ + " " + getOperationText(operation_) + " " + argument);
        }
    }
}

void Dialog::operationButtonClicked()
{
    clickAfterEqual();
    if (left_.isEmpty()) {
        return;
    }
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    if (button) {
        const Operation operation = getOperation(button->text());
        if (right_.isEmpty()) {
            operation_ = operation;
            ui->lineEdit->setText(left_ + " " + button->text());
        } else {
            equal();
            operation_ = operation;
            ui->lineEdit->setText(ui->lineEdit->text() + " " + getOperationText(operation_));
        }
    }
}

void Dialog::equal()
{
    if (operation_ == Operation::None) {
        return;
    }
    double left = left_.toDouble();
    double right = right_.toDouble();
    double result = 0;
    switch (operation_) {
    case Operation::Add:
        result = left + right;
        break;
    case Operation::Substract:
        result = left - right;
        break;
    case Operation::Multiply:
        result = left * right;
        break;
    case Operation::Divide:
        if (right == 0) {
            QMessageBox::warning(this, "Divide by zero", "Can't divide by zero.");
            ui->lineEdit->setText("");
            left_.clear();
            right_.clear();
            operation_ = Operation::None;
            return;
        }
        result = left / right;
    }
    ui->lineEdit->setText(QString::number(result));
    left_ = QString::number(result);
    right_.clear();
    operation_ = Operation::None;
}

void Dialog::clickAfterEqual()
{
    if (wasEqualClicked_) {
        ui->lineEdit->setText("");
        wasEqualClicked_ = false;
        return;
    }
}

void Dialog::on_btnEqual_clicked()
{
    equal();
    wasEqualClicked_ = true;
}

void Dialog::on_btnClear_clicked()
{
    left_.clear();
    right_.clear();
    operation_ = Operation::None;
    ui->lineEdit->setText("");
}

