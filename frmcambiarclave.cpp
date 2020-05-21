#include "frmcambiarclave.h"
#include "ui_frmcambiarclave.h"
#include <QMessageBox>

frmCambiarClave::frmCambiarClave(QString user, QWidget *parent) :
  QDialog(parent), ui(new Ui::frmCambiarClave), _user(user)
{
  ui->setupUi(this);
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
}

frmCambiarClave::~frmCambiarClave()
{
  delete ui;
}

void frmCambiarClave::on_pushButton_clicked()
{
  if(ui->clave->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una clave aquí."));
      ui->clave->setFocus();
      return;
    }
  if(ui->reClave->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar la clave de confirmación."));
      ui->reClave->setFocus();
      return;
    }
  if(ui->reClave->text().compare(ui->clave->text(),Qt::CaseSensitive)!=0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("La clave de confirmación que ingresó no coincide."));
      ui->reClave->selectAll();
      ui->reClave->setFocus();
      return;
    }
  db=new database();

  if(!db->actualizaClave(ui->reClave->text(),_user)){
      QMessageBox::critical(this,qApp->applicationName(),
                            tr("Ocurrio un error al ajecutar esta acción.\n").append(
                              db->getError()));
      return;
    }
  QMessageBox::information(this,QApplication::applicationName(),
                           tr("Su clave de acceso fue cambiada con exito."));
  QDialog::accept();
}

void frmCambiarClave::on_checkBox_clicked()
{
  if(ui->checkBox->isChecked()){
      ui->clave->setEchoMode(QLineEdit::Normal);
      ui->reClave->setEchoMode(QLineEdit::Normal);
    }else{
      ui->clave->setEchoMode(QLineEdit::Password);
      ui->reClave->setEchoMode(QLineEdit::Password);
    }
}
