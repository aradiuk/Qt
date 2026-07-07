#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "finddialog.h"
#include "replacedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , path_("")
    , isChanged_(false)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    newFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    checkSave();
    newFile();
}


void MainWindow::on_actionOpen_triggered()
{
    checkSave();
    openFile();
}


void MainWindow::on_actionSave_triggered()
{
    saveFile(path_);
}


void MainWindow::on_actionSave_As_triggered()
{
    saveFileAs();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionFind_triggered()
{
    FindDialog* findDialog = new FindDialog();
    if (!findDialog->exec()) {
        return;
    }
    QTextDocument::FindFlags flags;
    if (findDialog->isCaseSensitive_) {
        flags |= QTextDocument::FindFlag::FindCaseSensitively;
    }
    if (findDialog->isWholeWord_) {
        flags |= QTextDocument::FindFlag::FindWholeWords;
    }
    if (findDialog->isBack_) {
        qDebug() << "In goBack";
        flags |= QTextDocument::FindFlag::FindBackward;
    }
    bool value = ui->textEdit->find(findDialog->text_, flags);
    if (!value) {
        QMessageBox::information(this, "Find", "Not able to find: " + findDialog->text_);
        return;
    }
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog* replaceDialog = new ReplaceDialog();
    if (!replaceDialog->exec()) {
        return;
    }
    QTextDocument::FindFlags flags;
    if (replaceDialog->isAll_) {
        QString text = ui->textEdit->toHtml();
        text = text.replace(replaceDialog->text_, replaceDialog->replaceText_);
        ui->textEdit->setHtml(text);
    } else {
        bool value = ui->textEdit->find(replaceDialog->text_, flags);
        if (!value) {
            QMessageBox::information(this, "Find", "Not able to find to replace: " + replaceDialog->text_);
            return;
        }
        QTextCursor cursor = ui->textEdit->textCursor();
        cursor.insertHtml(replaceDialog->replaceText_);
    }
    isChanged_ = true;
}

void MainWindow::on_actionSelect_All_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actionZoom_In_triggered()
{
    ui->textEdit->zoomIn();
}

void MainWindow::on_actionZoom_Out_triggered()
{
    ui->textEdit->zoomOut();
}

void MainWindow::on_actionBold_triggered()
{
    bool isBold = ui->textEdit->currentFont().bold();
    QFont font = ui->textEdit->currentFont();
    font.setBold(!isBold);
    ui->textEdit->setCurrentFont(font);
    isChanged_ = true;
}

void MainWindow::on_actionItalic_triggered()
{
    bool isItalic = ui->textEdit->currentFont().italic();
    ui->textEdit->setFontItalic(!isItalic);
    isChanged_ = true;
}

void MainWindow::on_actionUnderline_triggered()
{
    bool isUnderline = ui->textEdit->currentFont().underline();
    ui->textEdit->setFontUnderline(!isUnderline);
    isChanged_ = true;
}

void MainWindow::on_actionStrike_triggered()
{
    bool isStrike = ui->textEdit->currentFont().strikeOut();
    QFont font = ui->textEdit->currentFont();
    font.setStrikeOut(!isStrike);
    ui->textEdit->setCurrentFont(font);
    isChanged_ = true;
}

void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(ui->textEdit->currentCharFormat().foreground().color(), this);
    ui->textEdit->setTextColor(color);
    isChanged_ = true;
}

void MainWindow::on_actionFont_triggered()
{
    bool isOk = true;
    QFont font = QFontDialog::getFont(&isOk, ui->textEdit->currentFont(), this);
    if (isOk) {
        ui->textEdit->setCurrentFont(font);
    }
}

void MainWindow::on_actionHelp_triggered()
{

}

void MainWindow::on_actionAbout_triggered()
{
    QString about = QApplication::organizationName() + "\r\n" +
                    QApplication::organizationDomain() + "\r\n" +
                    QApplication::applicationName() + "\r\n" +
                    QApplication::applicationDisplayName() + "\r\n" +
                    QApplication::applicationVersion();
    QMessageBox::information(this, "About Us", about);
}

void MainWindow::on_textEdit_textChanged()
{
    isChanged_ = true;
}

void MainWindow::newFile()
{
    ui->textEdit->clear();
    ui->statusbar->showMessage("New File");
    path_ = "";
    isChanged_ = false;
}

void MainWindow::openFile()
{
    QString path = QFileDialog::getOpenFileName(this, "Open file");
    if (path.isEmpty()) {
        return;
    }
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error opening file", file.errorString());
        ui->statusbar->showMessage("Error opening file");
        return;
    }
    QTextStream stream(&file);
    ui->textEdit->setHtml(stream.readAll());
    file.close();
    path_ = path;
    ui->statusbar->showMessage(path_);
    isChanged_ = false;
}

void MainWindow::saveFile(const QString &path)
{
    if (path.isEmpty()) {
        saveFileAs();
        return;
    }

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error saving file", file.errorString());
        ui->statusbar->showMessage("Error saving file");
        saveFileAs();
        return;
    }
    QTextStream stream(&file);
    stream << ui->textEdit->toHtml();
    ui->textEdit->setHtml(stream.readAll());
    file.close();
    path_ = path;
    ui->statusbar->showMessage(path_);
    isChanged_ = false;
}

void MainWindow::saveFileAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Save file");
    if (path.isEmpty()) {
        return;
    }
    saveFile(path);
}

void MainWindow::checkSave()
{
    if (!isChanged_) {
        return;
    }
    QMessageBox::StandardButton value = QMessageBox::question(this, "Save file?", "You have unsaved changes. Would you like to save them?");
    if (value != QMessageBox::StandardButton::Yes) {
        return;
    }
    saveFile(path_);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->accept();
}
