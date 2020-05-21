#ifndef FRMCAMBIARFRASE_H
#define FRMCAMBIARFRASE_H

#include <QDialog>
#include "database.h"
namespace Ui {
  class frmCambiarFrase;
}

class frmCambiarFrase : public QDialog
{
  Q_OBJECT

public:
  explicit frmCambiarFrase(QString user, QWidget *parent = nullptr);
  ~frmCambiarFrase();

private slots:
  void on_pushButton_clicked();
  void on_checkBox_clicked();

private:
  Ui::frmCambiarFrase *ui;
  database *db;
  QString _user;
};

#endif // FRMCAMBIARFRASE_H
