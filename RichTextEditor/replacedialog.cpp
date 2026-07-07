#include "replacedialog.h"
#include "ui_replacedialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
    , isAll_(false)
    , text_("")
    , replaceText_("")
    , replace_(nullptr)
    , replaceAll_(nullptr)
{
    ui->setupUi(this);
    replace_ = new QPushButton("Replace", this);
    ui->buttonBox->addButton(replace_, QDialogButtonBox::ButtonRole::ActionRole);
    connect(replace_, &QPushButton::clicked, this, &ReplaceDialog::replace);
    replaceAll_ = new QPushButton("Replace All", this);
    ui->buttonBox->addButton(replaceAll_, QDialogButtonBox::ButtonRole::ActionRole);
    connect(replaceAll_, &QPushButton::clicked, this, &ReplaceDialog::replaceAll);
    save();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_buttonBox_rejected()
{
    reject();
}

void ReplaceDialog::replace()
{
    save();
    accept();
}

void ReplaceDialog::replaceAll()
{
    save();
    isAll_ = true;
    accept();
}

void ReplaceDialog::save()
{
    text_ = ui->lineEditFind->text();
    replaceText_ = ui->lineEditReplace->text();
    isAll_ = false;
}

