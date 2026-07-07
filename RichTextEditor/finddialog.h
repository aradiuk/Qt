#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void goBack();

private:
    void save();

private:
    Ui::FindDialog *ui;

// Just to not bother with setters and getters at least for now.
public:
    QString text_;
    bool isCaseSensitive_;
    bool isWholeWord_;
    bool isBack_;
    QPushButton* back_;
};

#endif // FINDDIALOG_H
