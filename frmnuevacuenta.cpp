#include "frmnuevacuenta.h"
#include "ui_frmnuevacuenta.h"
#include <QtCore>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QImage>
#include <QImageWriter>
//#include <db.h>

frmNuevaCuenta::frmNuevaCuenta(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmNuevaCuenta){
  ui->setupUi(this);
  ui->dni->setValidator(new QIntValidator(this));
  ui->telefono->setValidator(new QIntValidator(this));
  QRegExp exp("[a-zA-ZñÑ]{50}");

  QValidator *validator=new QRegExpValidator(exp,this);

  ui->apellidos->setValidator(validator);
  ui->nombres->setValidator(validator);

  QRegExp rxEmail("^(?:[\\w.-]+)@(?:\\w+\\.[a-z0-9]{2,3})(?:\\.[a-z]{2,3})?$");
  QRegExpValidator *validatorEmail=new QRegExpValidator(rxEmail,this);
  ui->email->setValidator(validatorEmail);
  ui->dni->setFocus();
  ui->tabWidget->setCurrentIndex(0);
  loadPicture();
  ui->plainTextEdit->setPlainText("*Recuerde:\n"
                                  "La pregunta secreta o frase junto con la respuesta, son datos "
                                  "que se le pedira, en caso que olvide su clave de acceso; esto "
                                  "para poder establecer una nueva clave!");
  ui->plainTextEdit->setStyleSheet("color: #C91903");
  ui->plainTextEdit->setReadOnly(true);
}

QByteArray frmNuevaCuenta::imageToByte(QImage image)
{
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  QImageWriter writer(&buffer,"PNG");
  writer.write(image);
  return buffer.data();
}

frmNuevaCuenta::~frmNuevaCuenta(){
  delete ui;
}

void frmNuevaCuenta::on_pushButton_5_clicked()
{
  db=new database();
  if (ui->dni->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar un número de DNI."));
      ui->tabWidget->setCurrentIndex(0);
      ui->dni->setFocus();
      return;
    }
  if (ui->dni->text().length()!=8) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar 8 dígitos."));
      ui->tabWidget->setCurrentIndex(0);
      ui->dni->selectAll();
      ui->dni->setFocus();
      return;
    }
  if (ui->apellidos->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar sus apellidos."));
      ui->tabWidget->setCurrentIndex(0);
      ui->apellidos->setFocus();
      return;
    }
  if (ui->nombres->text().isEmpty()) {
      QMessageBox::information(this,tr("SW_Note pad"),tr("Debe ingresar su nombre."));
      ui->tabWidget->setCurrentIndex(0);
      ui->nombres->setFocus();
      return;
    }
  if (ui->genero->currentIndex()==0) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Seleccione una opción valida."));
      ui->tabWidget->setCurrentIndex(0);
      ui->genero->setFocus();
      return;
    }
  if (ui->direccion->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una dirección."));
      ui->tabWidget->setCurrentIndex(0);
      ui->direccion->setFocus();
      return;
    }
  if (ui->usuario_3->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar un nombre de usuario."));
      ui->tabWidget->setCurrentIndex(1);
      ui->usuario_3->setFocus();
      return;
    }
  if (ui->password_3->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una clave."));
      ui->tabWidget->setCurrentIndex(1);
      ui->password_3->setFocus();
      return;
    }
  if (ui->Repassword_3->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar su clave de confirmación."));
      ui->tabWidget->setCurrentIndex(1);
      ui->Repassword_3->setFocus();
      return;
    }

  if(db->comprobarDni(ui->dni->text())){
      QMessageBox::information(this,
                               QApplication::applicationName(),
                               "El número: <b style='color:#CC3300'>"+ui->dni->text()+"</b>, ya esta registrado en la base de datos.\n\
                               Por favor pruebe con otro.");
                               ui->tabWidget->setCurrentIndex(0);
          ui->dni->selectAll();
      ui->dni->setFocus();
      return;
    }
  if(!ui->email->text().isEmpty()){
      if(db->comprobarEmail(ui->email->text())){
          QMessageBox::information(this,
                                   QApplication::applicationName(),
                                   "El correo: <b style='color:#CC3300'>"+ui->email->text()+
                                   "</b>, ya esta registrado en la base de datos.");
          ui->tabWidget->setCurrentIndex(0);
          ui->email->selectAll();
          ui->email->setFocus();
          return;
        }
    }
  if(db->comprobarUsuario(ui->usuario_3->text())){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Este nombre de usuario ya esta registrado en la base de datos.."));
      ui->tabWidget->setCurrentIndex(1);
      ui->usuario_3->selectAll();
      ui->usuario_3->setFocus();
      return;
    }
  if(ui->Repassword_3->text().compare(ui->password_3->text(),Qt::CaseSensitive)!=0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("El password de confirmación no coinside."));
      ui->tabWidget->setCurrentIndex(1);
      ui->Repassword_3->selectAll();
      ui->Repassword_3->setFocus();
      return;
    }
  if (ui->txtPregunta_3->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar una pregunta."));
      ui->tabWidget->setCurrentIndex(1);
      ui->txtPregunta_3->setFocus();
      return;
    }
  if (ui->txtRespuesta_3->text().isEmpty()) {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese una respuesta a esta pregunta."));
      ui->tabWidget->setCurrentIndex(1);
      ui->txtRespuesta_3->setFocus();
      return;
    }
  if(db->nuevaCuenta(ui->dni->text(),ui->apellidos->text(),ui->nombres->text(),
                     ui->genero->currentText(),ui->nacimeinto->date(),
                     ui->direccion->text(),ui->email->text(),ui->telefono->text(),
                     ui->usuario_3->text(),ui->Repassword_3->text(),ui->txtPregunta_3->text(),
                     ui->txtRespuesta_3->text(),imageToByte(ui->lblFoto_3->pixmap()->toImage()))){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Datos guardados."));
      accept();
    }
}

void frmNuevaCuenta::on_pushButton_6_clicked()
{
  reject();
}

void frmNuevaCuenta::on_toolButton_3_clicked()
{
  QString fileName=QFileDialog::getOpenFileName(this,
                                                tr("Seleccione una imagen."),
                                                QDir::rootPath(),
                                                tr("Imagenes (*.png *.jpg)"));
  if(fileName.isEmpty()){
      return;
    }
  QPixmap foto(fileName);
  ui->lblFoto_3->setPixmap(foto.scaled(ui->lblFoto_3->width(),
                                       ui->lblFoto_3->height(),
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));
}

void frmNuevaCuenta::loadPicture()
{
  QPixmap pix(":images/icontexto-user-web-20-wordpress.png");
  ui->lblFoto_3->setPixmap(pix.scaled(140,192,
                                      Qt::IgnoreAspectRatio,
                                      Qt::SmoothTransformation));
}

void frmNuevaCuenta::on_checkBox_clicked()
{
  if(ui->checkBox->isChecked()){
      ui->txtRespuesta_3->setEchoMode(QLineEdit::Normal);
    }else{
      ui->txtRespuesta_3->setEchoMode(QLineEdit::Password);
    }
}

void frmNuevaCuenta::on_checkBox_2_clicked()
{
  if(ui->checkBox_2->isChecked()){
      ui->password_3->setEchoMode(QLineEdit::Normal);
      ui->Repassword_3->setEchoMode(QLineEdit::Normal);
    }else{
      ui->password_3->setEchoMode(QLineEdit::Password);
      ui->Repassword_3->setEchoMode(QLineEdit::Password);
    }
}
