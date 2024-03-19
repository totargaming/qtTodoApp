#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QStandardPaths>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(this,"error",file.errorString());
    }
    QTextStream in(&file);
    while(!in.atEnd()) {
        QListWidgetItem* item = new QListWidgetItem(in.readLine(),ui->listWidget);
        ui->listWidget->addItem(item);
        item->setFlags(item->flags() | Qt::ItemIsEditable);

    }
    file.close();
    if (file.open(QIODevice::WriteOnly)) {
        file.close();}
}

MainWindow::~MainWindow()
{
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite)) {
        QMessageBox::information(this,"error",file.errorString());
    }
    QTextStream out(&file);
    for (int i = 0; i < ui->listWidget->count(); i++) {
        out <<ui->listWidget->item(i)->text() << "\n";
    }
    file.close();
    delete ui;
}

void MainWindow::on_btnAdd_clicked()
{
    QString txt = ui->txtTodo->text();
    if (txt.isEmpty()) {
        QMessageBox::warning(
            this,
            tr("Empty task!"),
            tr("Dont leave it blank! Write something!") );
    }
    QListWidgetItem* item = new QListWidgetItem(txt,ui->listWidget);
    ui->listWidget->addItem(item);
    item->setFlags(item->flags() | Qt::ItemIsEditable);
    ui->txtTodo->clear();
    ui->txtTodo->setFocus();
}


void MainWindow::on_btnRemove_clicked()
{
    QListWidgetItem *it = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete it;
}


void MainWindow::on_btnRemoveAll_clicked()
{
    ui->listWidget->clear();
}



