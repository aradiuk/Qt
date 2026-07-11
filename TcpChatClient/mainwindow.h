#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractSocket>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_pushButtonConnect_clicked();
    void on_pushButtonDisconnect_clicked();
    void on_pushButtonSend_clicked();
    void connected();
    void disconnected();
    void readyRead();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    QStringList list;
    QStringListModel model;
    QString name;
};
#endif // MAINWINDOW_H
