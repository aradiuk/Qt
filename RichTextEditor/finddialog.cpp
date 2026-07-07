#include "finddialog.h"
#include "ui_finddialog.h"

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
    , text_("")
    , isCaseSensitive_(true)
    , isWholeWord_(false)
    , isBack_(false)
    , back_(nullptr)
{
    ui->setupUi(this);
    back_ = new QPushButton("Backwards", this);
    ui->buttonBox->addButton(back_, QDialogButtonBox::ButtonRole::ActionRole);
    connect(back_, &QPushButton::clicked, this, &FindDialog::goBack);
    save();
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_buttonBox_accepted()
{
    save();
    accept();
}

void FindDialog::on_buttonBox_rejected()
{
    reject();
}

void FindDialog::goBack()
{
    save();
    isBack_ = true;
    accept();
}

void FindDialog::save()
{
    text_ = ui->lineEdit->text();
    isCaseSensitive_ = ui->checkBoxCaseSensitive->isChecked();
    isWholeWord_ = ui->checkBoxWholeWord->isChecked();
    isBack_ = false;
}

