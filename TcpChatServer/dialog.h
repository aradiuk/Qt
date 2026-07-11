#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>
#include "server.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonStop_clicked();
    void next();
    void back();
    void changed();

private:
    void enableButtons();

private:
    Ui::Dialog *ui;
    QPushButton* btnBack;
    QPushButton* btnNext;
    Server server;
};
#endif // DIALOG_H
