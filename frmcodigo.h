#ifndef FRMCODIGO_H
#define FRMCODIGO_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
  class frmCodigo;
}

class frmCodigo : public QDialog
{
  Q_OBJECT

public:
  explicit frmCodigo(QWidget *parent = nullptr);
  ~frmCodigo();


private slots:
  void on_lineEdit_textChanged(const QString &arg1);
  void on_pushButton_clicked();

private:
  Ui::frmCodigo *ui;
  MainWindow *mWindows{nullptr};
};

#endif // FRMCODIGO_H
