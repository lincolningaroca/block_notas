#include "frmrecuperaclave.h"
#include "ui_frmrecuperaclave.h"

#include <QMessageBox>

frmRecuperaClave::frmRecuperaClave(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmRecuperaClave)
{
  ui->setupUi(this);
  ui->stackedWidget->setCurrentIndex(0);
}

frmRecuperaClave::~frmRecuperaClave()
{
  delete ui;
}

void frmRecuperaClave::on_txtUsuario_textChanged(const QString &arg1)
{
  if(arg1.isEmpty()){
      ui->pushButton->setEnabled(false);
    }else{
      ui->pushButton->setEnabled(true);
    }
}

void frmRecuperaClave::on_pushButton_clicked()
{
  db=new database();
  QString pregunta=db->pregunta(ui->txtUsuario->text());
  if(pregunta.isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Usuario incorrecto.."));
      ui->txtUsuario->selectAll();
      ui->txtUsuario->setFocus();
      return;
    }
  ui->txtPregunta->setText(pregunta);
  ui->txtRespuesta->setFocus();
  ui->stackedWidget->setCurrentIndex(1);
  ui->pushButton_3->setEnabled(true);

}
void frmRecuperaClave::on_pushButton_4_clicked()
{
  db=new database();
  if(!db->comprobarRespuesta(ui->txtRespuesta->text(),ui->txtUsuario->text())){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("La respuesta es incorrecta.."));
      ui->txtRespuesta->selectAll();
      ui->txtRespuesta->setFocus();
      return;
    }
  ui->stackedWidget->setCurrentIndex(2);
}

void frmRecuperaClave::on_pushButton_3_clicked()
{
  ui->txtUsuario->clear();
  ui->txtRespuesta->clear();
  ui->txtClave->clear();
  ui->txtReclave->clear();
  ui->stackedWidget->setCurrentIndex(0);
  ui->txtUsuario->setFocus();
  ui->pushButton_3->setEnabled(false);
}

void frmRecuperaClave::on_pushButton_2_clicked()
{
  db=new database();
  if(ui->txtClave->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una clave."));
      ui->txtClave->setFocus();
      return;
    }
  if(ui->txtReclave->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar su clave de confirmación."));
      ui->txtReclave->setFocus();
      return;
    }
  if(ui->txtReclave->text().compare(ui->txtClave->text(),Qt::CaseSensitive)!=0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("El password de confirmación no coinside."));
      ui->txtReclave->selectAll();
      ui->txtReclave->setFocus();
      return;
    }
  if(db->ResetPassword(ui->txtReclave->text(),ui->txtUsuario->text())){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Su password fue restaurado correctamente."));
      ui->txtUsuario->clear();
      ui->txtRespuesta->clear();
      ui->txtClave->clear();
      ui->txtReclave->clear();
      ui->stackedWidget->setCurrentIndex(0);
      accept();
    }
}

void frmRecuperaClave::on_checkBox_clicked()
{
  if(ui->checkBox->isChecked()){
      ui->txtRespuesta->setEchoMode(QLineEdit::Normal);
    }else{
      ui->txtRespuesta->setEchoMode(QLineEdit::Password);
    }
}

void frmRecuperaClave::on_checkBox_2_clicked()
{
  if(ui->checkBox_2->isChecked()){
      ui->txtClave->setEchoMode(QLineEdit::Normal);
      ui->txtReclave->setEchoMode(QLineEdit::Normal);
    }else{
      ui->txtClave->setEchoMode(QLineEdit::Password);
      ui->txtReclave->setEchoMode(QLineEdit::Password);
    }
}
