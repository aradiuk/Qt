#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

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
    void on_btnSave_clicked();

    void on_btnVerify_clicked();

private:
    void numButtonClicked();

private:
    Ui::Dialog *ui;
    QString savedCode_;
    QString input_;
    bool isAllowedToSave_;
};
#endif // DIALOG_H
