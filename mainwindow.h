#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTableWidgetItem>
#include <iostream>
#include <string>
#include <stdio.h>
#include <QString>
#include <QStringList>
#include <QTableWidget>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();
 private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

 private:
  Ui::MainWindow* ui;
  int row;
  int col;
  QTableWidget* table = NULL;
};

#endif // MAINWINDOW_H
