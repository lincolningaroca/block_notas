#include "frmencripta.h"
#include "ui_frmencripta.h"
#include <QMessageBox>
#include <QFileSystemModel>
#include <QCompleter>
#include <QFileDialog>
#include "DuCrypt.h"
#include <QInputDialog>

frmEncripta::frmEncripta(QWidget *parent) :
  QDialog(parent),  ui(new Ui::frmEncripta){
  ui->setupUi(this);
  auto model=new QFileSystemModel(this);
  model->setRootPath(QDir::rootPath());
  auto completer=new QCompleter(model,this);
  ui->txtArchivo->setCompleter(completer);
}

frmEncripta::~frmEncripta(){
  delete ui;
}

void frmEncripta::on_btnEncriptar_clicked(){
  auto sourceFileName=ui->txtArchivo->text();
  if(sourceFileName.isEmpty()){
      return;
    }
  if(ui->txtPassword->text().isEmpty()){
      QMessageBox::warning(this,
                           QApplication::applicationName().append(
                             " <Encriptar archivo>"),
                           tr("Digite una clave de encriptación..."));
      ui->txtPassword->setFocus();
      return;
    }

  auto destinationFileName=QFileDialog::getSaveFileName(this,
                                                        tr("Guardar archivo"),
                                                        QDir::rootPath(),
                                                        tr("Archivo de texto (*.txt)"));
  if(destinationFileName.isEmpty()){
      return;
    }
  bool ok;
  auto confirmPassword=QInputDialog::getText(this,
                                             QApplication::applicationName().append(
                                               " <Encriptar archivo>"),
                                             tr("Vuelva a ingresar su clave de encriptación.."),
                                             QLineEdit::Password,"",&ok);
  if(!ok){
      return;
    }
  if(ui->txtPassword->text().compare(confirmPassword)!=0){
      QMessageBox::warning(this,
                           QApplication::applicationName().append(
                             " <Encriptar archivo>"),
                           tr("La clave de confirmación no coincide..."));
      return;
    }

  DuCrypt dCrypt;
  dCrypt.setPassword(ui->txtPassword->text());
  if(dCrypt.encryptFile(sourceFileName,destinationFileName)){
      QMessageBox::information(this,
                               QApplication::applicationName().append(
                                 " <Encriptar archivo>"),
                               tr("El archivo fue encriptado con exito..."));
      limpiarControles();
    }else{
      QMessageBox::critical(this,
                            QApplication::applicationName().append(
                              " <Encriptar archivo>"),
                            tr("Error al encriptar archivo..."));
    }
}
//boton para desencriptar archivo
void frmEncripta::on_btnDesencriptar_clicked(){
  auto sourceFileName=ui->txtArchivo->text();
  if(sourceFileName.isEmpty()){
      return;
    }
  if(ui->txtPassword->text().isEmpty()){
      QMessageBox::warning(this,
                           QApplication::applicationName().append(
                             " <Encriptar archivo>"),
                           tr("Digite su clave de desencriptación..."));
      ui->txtPassword->setFocus();
      return;
    }

  auto destinationFileName=QFileDialog::getSaveFileName(this,
                                                        tr("Guardar archivo"),
                                                        QDir::rootPath(),
                                                        tr("Archivo de texto (*.txt)"));
  if(destinationFileName.isEmpty()){
      return;
    }

  DuCrypt dCrypt;
  dCrypt.setPassword(ui->txtPassword->text());
  if(dCrypt.decryptFile(sourceFileName,destinationFileName)){
      QMessageBox::information(this,
                               QApplication::applicationName().append(
                                 " <Encriptar archivo>"),
                               tr("El archivo fue desencriptado con exito..."));
      limpiarControles();
    }else{
      QMessageBox::critical(this,
                            QApplication::applicationName().append(
                              " <Encriptar archivo>"),
                            tr("Error al tratar de desencriptar archivo..."));
    }
}

void frmEncripta::limpiarControles(){
  ui->txtArchivo->clear();
  ui->txtPassword->clear();
  //ui->txtRePassword->clear();
  ui->txtPassword->setFocus();

}

void frmEncripta::on_btnBuscaArchivo_clicked(){
  auto fileName=QFileDialog::getOpenFileName(this,
                                             tr("Abrir archivo.."),
                                             QDir::rootPath(),
                                             tr("Archivos de texto (*.txt)"));
  if(fileName.isEmpty()){
      return;
    }
  ui->txtArchivo->setText(fileName);

}
