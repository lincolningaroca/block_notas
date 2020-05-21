#ifndef FRMCONTACTOS_H
#define FRMCONTACTOS_H

#include <QMainWindow>
#include "database.h"
#include "contacto.h"
#include <QRegExp>
#include <QRegExpValidator>
#include <QFileDialog>
#include <mainwindow.h>
#include <QListWidgetItem>
#include "frmnuevacategoria.h"

namespace Ui {
  class frmContactos;
}
class frmNuevaCategoria;

class frmContactos : public QMainWindow
{
  Q_OBJECT

public:
  explicit frmContactos(QWidget *parent = nullptr);
  ~frmContactos();


private slots:
  void itemInsertado(QString item);
  void on_comboBox_4_activated(const QString &arg1);
  void on_actionGuardar_triggered();
  void on_actionActualizarDatos_triggered();
  void on_contactos_tabBarClicked(int index);
  void on_pushButton_2_clicked();
  void on_pushButton_clicked();
  void on_actionEliminarContacto_triggered();
  void closeEvent(QCloseEvent *e);

private:
  Ui::frmContactos *ui;
  frmNuevaCategoria *nuevaCategoria;
  database *db;
  contacto con;
  QRegExp rx;
  QRegExpValidator v;
  int idUsuario=0;
  QFileDialog *dialogo;
  QString nombreArchivo;
  MainWindow *mwindows;
  QListWidgetItem *item;
  QMap<int,QString> res;
//  QStringListModel *listModel{nullptr};

  void llenarDatosCategoria();
  void validations();
  void cargarListaContactos();
  void cargarDatosContacto();
  void windowsLoad();
  void manageControls(bool st=true);
  void fotoPorDefecto();
  void cargarFoto(QString foto);
  void limpiarControles(QString op="guardar");


};

#endif // FRMCONTACTOS_H
