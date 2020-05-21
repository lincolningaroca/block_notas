#ifndef FRMDATOSREGISTRO_H
#define FRMDATOSREGISTRO_H

#include <QDialog>

namespace Ui {
  class frmDatosRegistro;
}

class frmDatosRegistro : public QDialog
{
  Q_OBJECT

public:
  explicit frmDatosRegistro(QWidget *parent = nullptr);
  ~frmDatosRegistro();

private slots:
  void on_pushButton_clicked();

private:
  Ui::frmDatosRegistro *ui;
};

#endif // FRMDATOSREGISTRO_H
