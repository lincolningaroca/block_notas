#include "frmdatosregistro.h"
#include "ui_frmdatosregistro.h"
#include "database.h"
#include <QList>
frmDatosRegistro::frmDatosRegistro(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmDatosRegistro)
{
  ui->setupUi(this);
  database *db=new database();
  QList<QVariant> datos;
  datos=db->datosRegistro();
  ui->fecha->setText(datos.value(1).toString());
  ui->nombres->setText(datos.value(2).toString());
  ui->empresa->setText(datos.value(3).toString());
  ui->email->setText(datos.value(4).toString());
  ui->label_3->setText(datos.value(0).toString().toUpper());
}

frmDatosRegistro::~frmDatosRegistro()
{
  delete ui;
}

void frmDatosRegistro::on_pushButton_clicked()
{
  accept();
}
