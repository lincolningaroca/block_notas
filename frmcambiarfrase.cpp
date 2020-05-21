#include "frmcambiarfrase.h"
#include "ui_frmcambiarfrase.h"
#include <QMessageBox>

frmCambiarFrase::frmCambiarFrase(QString user, QWidget *parent) :
  QDialog(parent), ui(new Ui::frmCambiarFrase), _user(user)
{
  ui->setupUi(this);
}

frmCambiarFrase::~frmCambiarFrase(){
  delete ui;
}
void frmCambiarFrase::on_pushButton_clicked(){
  db=new database();
  if(ui->lineEdit->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una frase aquí.."));
      ui->lineEdit->setFocus();
      return;
    }
  if(ui->lineEdit_2->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese una respuesta.."));
      ui->lineEdit_2->setFocus();
      return;
    }
  if(!db->cambiarPreguntaSecreta(ui->lineEdit->text(),
                                 ui->lineEdit_2->text(),_user)){
      QMessageBox::critical(this,qApp->applicationName(),
                            tr("Ocurrio un error al ajecutar esta acción.\n").append(
                              db->getError()));
      return;
    }
  QMessageBox::information(this,QApplication::applicationName(),
                           tr("los datos para la recuperación de su "
                              "password fué cambiado con exito.."));
  accept();
}

void frmCambiarFrase::on_checkBox_clicked()
{
  if(ui->checkBox->isChecked()){
      ui->lineEdit_2->setEchoMode(QLineEdit::Normal);
    }else{
      ui->lineEdit_2->setEchoMode(QLineEdit::Password);
    }
}
