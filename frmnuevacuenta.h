#ifndef FRMNUEVACUENTA_H
#define FRMNUEVACUENTA_H

#include <QDialog>
#include "database.h"
namespace Ui {
  class frmNuevaCuenta;
}

class frmNuevaCuenta : public QDialog
{
  Q_OBJECT

public:
  explicit frmNuevaCuenta(QWidget *parent = nullptr);
  QByteArray imageToByte(QImage image);

  ~frmNuevaCuenta();

private slots:
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_toolButton_3_clicked();
  void on_checkBox_clicked();
  void on_checkBox_2_clicked();

private:
  void loadPicture();

private:
  Ui::frmNuevaCuenta *ui;
  database *db;
};

#endif // FRMNUEVACUENTA_H
