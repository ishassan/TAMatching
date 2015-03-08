#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QFileDialog>
#include <qmessagebox.h>
#include <bits/stdc++.h>
#include "Matching.h"
#include "Controller.h"
#include <QDesktopServices>

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

void MainWindow::on_btnbrowse_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Excel Sheet",".","Excel Files (*.xlsx)");
    ui->txtpath->setText(filename);
}

void MainWindow::on_btnok_clicked()
{
    QString excelfile = ui->txtpath->text();
    int numchoices = ui->txtNum->text().toInt();
    int taload = ui->taload->text().toInt();
    int tacourse = ui->tacourses->text().toInt();

    Controller controller(excelfile,numchoices,taload,tacourse);
    controller.run();
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Done","Done. Would you like to open the output file now?", QMessageBox::Yes|QMessageBox::No);
    if(reply == QMessageBox::Yes){
        QDesktopServices::openUrl(QUrl(controller.getOutputFile()));
    }
}

