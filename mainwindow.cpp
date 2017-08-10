#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crcoperate.h"
#include<string>
#include<QString>
#include<QMessageBox>

using std::string;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_OK_clicked()
{
    CRCoperate *crc = new CRCoperate(ui->lineEdit_SMAC->text(), ui->lineEdit_TMAC->text(),
                      ui->textEdit_DATA->toPlainText());
    bool match_s = crc->CHECKMAC(ui->lineEdit_SMAC->text());
    bool match_t = crc->CHECKMAC(ui->lineEdit_TMAC->text());
    bool match_d = crc->CHECKDATA(ui->textEdit_DATA->toPlainText());

    if(match_s && match_t && match_d)
        ui->lineEdit_FCS->setText(crc->GETFCS());
    else
    {
        QMessageBox::critical(NULL,"error","format error");
        ui->lineEdit_FCS->setText("format error");
    }
}

void MainWindow::on_pushButton_RETRY_clicked()
{
    ui->lineEdit_leadcode->setText("0xAAAAAAA");
    ui->lineEdit_delimiter->setText("0xAB");
    ui->lineEdit_SMAC->setText("");
    ui->lineEdit_TMAC->setText("");
    ui->lineEdit_FCS->setText("");
    ui->textEdit_DATA->setText("");
}
