#ifndef FRMENCRIPTA_H
#define FRMENCRIPTA_H

#include <QDialog>

namespace Ui {
  class frmEncripta;
}

class frmEncripta : public QDialog
{
  Q_OBJECT

public:
  explicit frmEncripta(QWidget *parent = nullptr);
  ~frmEncripta();

private slots:
  void on_btnEncriptar_clicked();
  void on_btnDesencriptar_clicked();
  void on_btnBuscaArchivo_clicked();

private:
  Ui::frmEncripta *ui;
private:
  void limpiarControles();
};

#endif // FRMENCRIPTA_H
