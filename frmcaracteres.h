#ifndef FRMCARACTERES_H
#define FRMCARACTERES_H
#include <QDialog>
#include "mainwindow.h"
#include <QCloseEvent>
namespace Ui {
  class frmCaracteres;
}

class frmCaracteres : public QDialog
{
  Q_OBJECT

public:
  explicit frmCaracteres(QWidget *parent = 0);
  ~frmCaracteres();

private slots:
  void on_tableWidget_doubleClicked(const QModelIndex &index);
  void closeEvent(QCloseEvent *evt);

private:
  Ui::frmCaracteres *ui;
public:
  MainWindow *m_Window;
};

#endif // FRMCARACTERES_H
