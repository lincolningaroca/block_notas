#include "frmregistro.h"
#include "ui_frmregistro.h"
#include "database.h"
#include <QCryptographicHash>
#include <QMessageBox>
#include "mainwindow.h"

frmRegistro::frmRegistro(QWidget *parent) :
  QDialog(parent),ui(new Ui::frmRegistro)
{
  ui->setupUi(this);
}

frmRegistro::~frmRegistro()
{
  delete ui;
}

void frmRegistro::on_pushButton_clicked()
{
  database *db=new database();
  if(ui->lineEdit->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese su nombre completo."));
      ui->lineEdit->setFocus();
      return;
    }
  if(ui->lineEdit_2->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese el nombre de su compañía y/o empresa."));
      ui->lineEdit_2->setFocus();
      return;
    }
  if(ui->lineEdit_3->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese su correo electrónico."));
      ui->lineEdit_3->setFocus();
      return;
    }

  if(db->registrarDatos(ui->lineEdit_2->text(),QDate::currentDate(),ui->lineEdit->text(),\
                        ui->lineEdit_2->text(),ui->lineEdit_3->text(),true)){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Sus datos fueron registrados correctamente.."));
      qobject_cast<MainWindow *>(parent())->registro();
      accept();
    }
}
