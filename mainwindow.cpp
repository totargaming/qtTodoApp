#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
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



