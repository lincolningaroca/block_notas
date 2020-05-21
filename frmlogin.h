#ifndef FRMLOGIN_H
#define FRMLOGIN_H

#include <QDialog>
#include "database.h"

namespace Ui {
  class frmLogin;
}

class frmLogin : public QDialog
{
  Q_OBJECT

public:
  explicit frmLogin(QWidget *parent = nullptr);
  QString getUserName();
  ~frmLogin();

private slots:
  void on_pushButton_2_clicked();
  void on_pushButton_clicked();
  void on_pushButton_3_clicked();

private:
  Ui::frmLogin *ui;
  database *db;
  QString _userName="";

};

#endif // FRMLOGIN_H
