#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

enum class Operation {
    None,
    Add,
    Substract,
    Multiply,
    Divide
};

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog() override;

private slots:
    void on_btnEqual_clicked();
    void on_btnClear_clicked();

private:
    void numButtonClicked();
    void operationButtonClicked();
    void equal();
    void clickAfterEqual();

private:
    Ui::Dialog *ui;
    QString left_;
    QString right_;
    Operation operation_;
    bool wasEqualClicked_;
};
#endif // DIALOG_H
