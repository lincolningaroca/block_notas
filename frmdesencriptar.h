#ifndef FRMDESENCRIPTAR_H
#define FRMDESENCRIPTAR_H
#include <mainwindow.h>
#include <QDialog>

namespace Ui {
  class frmDesencriptar;
}

class frmDesencriptar : public QDialog
{
  Q_OBJECT

public:
  explicit frmDesencriptar(QWidget *parent = nullptr);
  ~frmDesencriptar();

private slots:
  void on_pushButton_clicked();

private:
  Ui::frmDesencriptar *ui;
  MainWindow *mW;
};

#endif // FRMDESENCRIPTAR_H
