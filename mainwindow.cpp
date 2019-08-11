#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QMessageBox>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>

#include "mainwindow.h"
#include "ui_mainwindow.h"

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


void MainWindow::on_actionNew_triggered()
{
    // Get folder from setting file

    // If folder doesn't exist, ask user to chose folder

    // If folder exists, create new journal file

}

void MainWindow::on_actionLoad_Journals_triggered()
{
    //Test
    // get the home path, to be used to save/load journals location
    QTextStream out(stdout);
    out << "Home Path: " << QDir::homePath() << endl;
    //QDesktopServices::openUrl();

    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    QString path = QFileDialog::getExistingDirectory();
    out << "selected: " << path << endl;
}
