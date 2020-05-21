#ifndef FRMRECUPERACLAVE_H
#define FRMRECUPERACLAVE_H

#include <QDialog>
#include "database.h"
namespace Ui {
  class frmRecuperaClave;
}

class frmRecuperaClave : public QDialog
{
  Q_OBJECT

public:
  explicit frmRecuperaClave(QWidget *parent = nullptr);
  ~frmRecuperaClave();

private slots:
  void on_txtUsuario_textChanged(const QString &arg1);
  void on_pushButton_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_2_clicked();
  void on_checkBox_clicked();
  void on_checkBox_2_clicked();
private:
  Ui::frmRecuperaClave *ui;
  database *db;
};

#endif // FRMRECUPERACLAVE_H
