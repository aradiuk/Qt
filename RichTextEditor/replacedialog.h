#ifndef REPLACEDIALOG_H
#define REPLACEDIALOG_H

#include <QDialog>
#include <QPushButton>


namespace Ui {
class ReplaceDialog;
}

class ReplaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplaceDialog(QWidget *parent = nullptr);
    ~ReplaceDialog();

private slots:
    void on_buttonBox_rejected();
    void replace();
    void replaceAll();

private:
    void save();

private:
    Ui::ReplaceDialog *ui;

public:
    bool isAll_;
    QString text_;
    QString replaceText_;
    QPushButton* replace_;
    QPushButton* replaceAll_;
};

#endif // REPLACEDIALOG_H
