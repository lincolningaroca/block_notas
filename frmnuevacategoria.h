#ifndef FRMNUEVACATEGORIA_H
#define FRMNUEVACATEGORIA_H

#include <QDialog>

namespace Ui {
  class frmNuevaCategoria;
}

class frmNuevaCategoria : public QDialog
{
  Q_OBJECT
signals:
  void _addItem(QString);
public:
  explicit frmNuevaCategoria(QWidget *parent = nullptr);
  ~frmNuevaCategoria();

private slots:
  void on_pushButton_clicked();
  void on_lineEdit_textChanged(const QString &arg1);

private:
  Ui::frmNuevaCategoria *ui;
};

#endif // FRMNUEVACATEGORIA_H
