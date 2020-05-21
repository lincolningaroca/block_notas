#ifndef FRMCAMBIARCLAVE_H
#define FRMCAMBIARCLAVE_H

#include <QDialog>
#include "database.h"
namespace Ui {
  class frmCambiarClave;
}

class frmCambiarClave : public QDialog
{
  Q_OBJECT

public:
  explicit frmCambiarClave(QString user, QWidget *parent = nullptr);

  ~frmCambiarClave();

private slots:
  void on_pushButton_clicked();
  void on_checkBox_clicked();

private:
  Ui::frmCambiarClave *ui;
  database *db;
  QString _user;
};

#endif // FRMCAMBIARCLAVE_H
