#ifndef FRMEDITADATOS_H
#define FRMEDITADATOS_H

#include <QDialog>
#include <database.h>
#include <QSqlError>
#include <QPixmap>
namespace Ui {
  class frmEditaDatos;
}

class frmEditaDatos : public QDialog
{
  Q_OBJECT

public:
  explicit frmEditaDatos(QWidget *parent = nullptr, QString user="");
  //    QImage byteToImage(QByteArray image);
  //    QByteArray imageToByte(QImage image);
  ~frmEditaDatos();

private slots:
  void on_pushButton_clicked();

  void on_pushButton_2_clicked();

  void on_toolButton_clicked();

private:
  Ui::frmEditaDatos *ui;
  database *db;
  QString _usuario;
  QImage _foto;
private:
  void cargarDatos();


};

#endif // FRMEDITADATOS_H
