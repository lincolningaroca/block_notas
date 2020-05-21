#include "frmlogin.h"
#include "ui_frmlogin.h"
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include "frmrecuperaclave.h"

frmLogin::frmLogin(QWidget *parent) :
  QDialog(parent),ui(new Ui::frmLogin){
  ui->setupUi(this);
  setWindowTitle(QApplication::applicationName().append(" <Iniciar sesión>"));
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  ui->Usuario->setFocus();
  ui->Password->setEchoMode(QLineEdit::Password);
  db=new database();
  //    mainW=qobject_cast<MainWindow *>(parent);
}

QString frmLogin::getUserName()
{
  return _userName;
}

frmLogin::~frmLogin(){
  delete ui;
}

void frmLogin::on_pushButton_2_clicked(){
  reject();
}

void frmLogin::on_pushButton_clicked(){

  if(ui->Usuario->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Por favor ingrese su nombre de usuario."));
      ui->Usuario->setFocus();
      return;
    }
  if(ui->Password->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Por favor ingrese una clave."));
      ui->Password->setFocus();
      return;
    }
  if(db->logIn(ui->Usuario->text(),ui->Password->text())){
      _userName=ui->Usuario->text();
      QDialog::accept();
    }else{
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Datos incorrectos."));
      ui->Usuario->selectAll();
      ui->Usuario->setFocus();
    }
}

void frmLogin::on_pushButton_3_clicked()
{
  frmRecuperaClave *r=new frmRecuperaClave(this);
  r->setFixedSize(400,162);
  r->exec();
}
