#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <stdio.h>
#include <sstream>

using namespace std;
MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
  row = 0;
  col = 0;
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_pushButton_clicked() {
  QString to = ui->lineEdit->text();
  QTableWidgetItem* newItem = new QTableWidgetItem(to);
  ui->tableWidget->insertRow(row);
  ui->tableWidget->setItem(row, col, newItem);
  row += 1;
  ui->lineEdit->setText("");
}

void MainWindow::on_pushButton_2_clicked() {
  int contRow = ui->tableWidget->rowCount();
  bool ok;
  double mediana;
  if (contRow > 0) {
    // calcula mediana
    if (contRow % 2 != 1) {
      QTableWidgetItem* val =   ui->tableWidget->item(contRow / 2, 0);
      QTableWidgetItem* val1 = ui->tableWidget->item((contRow / 2) - 1, 0);
      mediana = (val->text().toDouble(&ok) + val1->text().toDouble(&ok)) / 2;
      ui->mediana->setText(QString::number(mediana, 'f', 2));
    } else {
      QTableWidgetItem* val =   ui->tableWidget->item(contRow / 2, 0);
      ui->mediana->setText(QString::number(val->text().toDouble(&ok)));
    }
    double sum = 0;
    for (int cont = 0; cont < contRow; cont++) {
      QTableWidgetItem* item =   ui->tableWidget->item(cont, 0);
      sum = sum + item->text().toDouble(&ok);
    }
    double promedio = (double) sum / contRow;
    ui->moda->setText(QString::number(promedio, 'f', 2));
    // calcula unicos valores
    double vector[2][contRow];
    double val;
    int cont2 = 0;
    bool sw;
    // setea con ceros
    for (int cont = 0; cont < contRow; cont++) {
      vector[0][cont] = 0;
      vector[1][cont] = 0;
    }

    for (int cont = 0; cont < contRow; cont++) {
      QTableWidgetItem* item =   ui->tableWidget->item(cont, 0);
      val = item->text().toDouble(&ok);
      if (cont2 == 0) {
        vector[0][cont2] = val;
        cont2 = cont2 + 1;
      } else {
        sw = true;
        for (int c = 0; c < cont2; c++) {
          if (val == vector[0][c]) {
            sw = false;
          }
        }
      }
      if (sw) {
        vector[0][cont2] = val;
        cont2 = cont2 + 1;
      }
    }

    //contamos cuantos existen en el vector numeros
    int sum1 = 0;
    double cad1, cad2;
    for (int c = 0; c < cont2; c++) {
      cad1 = vector[0][c];
      sum1 = 0;
      for (int c1 = 0; c1 < contRow; c1++) {
        QTableWidgetItem* item =   ui->tableWidget->item(c1, 0);
        cad2 = item->text().toDouble(&ok);
        if (cad1 == cad2) {
          sum1 += 1;
        }
      }
      vector[1][c] = double(sum1);
    }
    if (table == NULL) {
      table = new QTableWidget();
      table->adjustSize();
      table->setColumnCount(2);
      QStringList header;
      header << "Valor" << "cantidad";
      table->setHorizontalHeaderLabels(header);
      table->baseSize().setHeight(300);
      table->baseSize().setWidth(300);
      ui->formLayout->addWidget(table);
    }
    // remove row
    for (int cf = 0; cf < table->rowCount(); cf++) {
      table->removeRow(cf);
    }
    double x;
    stringstream ss;
    for (int cf = 0; cf < cont2; cf++) {
      x = vector[0][cf];
      ss.str("");
      ss << x;
      table->insertRow(cf);
      QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(ss.str()));
      table->setItem(cf, 0, item2);
      x = vector[1][cf];
      ss.str("");
      ss << x;
      QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(ss.str()));
      table->setItem(cf, 1, item3);
    }
  }
}
