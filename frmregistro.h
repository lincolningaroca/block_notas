#ifndef FRMREGISTRO_H
#define FRMREGISTRO_H

#include <QDialog>

namespace Ui {
  class frmRegistro;
}

class frmRegistro : public QDialog
{
  Q_OBJECT

public:
  explicit frmRegistro(QWidget *parent = nullptr);
  ~frmRegistro();

private slots:
  void on_pushButton_clicked();

private:
  Ui::frmRegistro *ui;
};

#endif // FRMREGISTRO_H
