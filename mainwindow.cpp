#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "crcoperate.h"
#include<string>
#include<QString>

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
    ui->lineEdit_FCS->setText(crc->GETFCS());
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
