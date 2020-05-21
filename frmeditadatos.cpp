#include "frmeditadatos.h"
#include "ui_frmeditadatos.h"
#include <QMessageBox>
#include <QImageReader>
#include <QImageWriter>
#include <QFileDialog>

frmEditaDatos::frmEditaDatos(QWidget *parent, QString user) :
  QDialog(parent), ui(new Ui::frmEditaDatos),_usuario(user)
{
  ui->setupUi(this);
  cargarDatos();
  setWindowFlags(Qt::Dialog|Qt::MSWindowsFixedSizeDialogHint);
  QRegExp expInt("\\d{0,15}");
  QValidator *val=new QRegExpValidator(expInt,this);
  ui->telefono->setValidator(val);
}

//QImage frmEditaDatos::byteToImage(QByteArray image)
//{
//    QBuffer buffer(&image);
//    buffer.open(QIODevice::ReadOnly);
//    QImageReader reader(&buffer,"PNG");
//    return reader.read();
//}

//QByteArray frmEditaDatos::imageToByte(QImage image)
//{
//    QBuffer buffer;
//    buffer.open(QIODevice::WriteOnly);
//    QImageWriter writer(&buffer,"PNG");
//    writer.write(image);
//    return buffer.data();
//}

frmEditaDatos::~frmEditaDatos()
{
  delete ui;
}

void frmEditaDatos::cargarDatos(){
  db=new database();
  db->conexion();
  QSqlQuery query;
  query.prepare("SELECT * FROM usuarios WHERE usuario=?");
  query.addBindValue(_usuario);
  if(!query.exec()){
      QMessageBox::critical(this,qApp->applicationName(),
                            "Error al ejecutar la sentencia"+
                            query.lastError().text());
      return;
    }
  query.next();
  ui->dni->setText(query.value(1).toString());
  ui->apellidos->setText(query.value(2).toString());
  ui->nombres->setText(query.value(3).toString());
  ui->genero->setCurrentText(query.value(4).toString());
  ui->nacimeinto->setDate(query.value(5).toDate());
  ui->direccion->setText(query.value(6).toString());
  ui->email->setText(query.value(7).toString());
  ui->telefono->setText(query.value(8).toString());
  QPixmap pix;
  pix.loadFromData(query.value(13).toByteArray());

  ui->lblFoto->setPixmap(pix.scaled(176,225));

}

void frmEditaDatos::on_pushButton_clicked()
{
  //    db=new database();
  if(!db->actualizaDatos(ui->apellidos->text(),ui->nombres->text(),ui->genero->currentText(),
                         ui->nacimeinto->date(),ui->direccion->text(),ui->telefono->text(),
                         db->imageToByte(_foto),ui->dni->text(),_usuario)){
      QMessageBox::critical(this,qApp->applicationName(),
                            tr("Se producjo un error en la ejecució.\n").append(
                              db->getError()));
      return;
    }
  QMessageBox::information(this,QApplication::applicationName(),
                           tr("Sus datos fueron actualizados.."));
  accept();
}

void frmEditaDatos::on_pushButton_2_clicked()
{
  reject();
}

void frmEditaDatos::on_toolButton_clicked()
{
  QString fileName;
  fileName=QFileDialog::getOpenFileName(this,
                                        tr("Seleccione una imagen."),
                                        QDir::rootPath(),
                                        tr("Imagenes (*.png *.jpg)"));
  if(fileName.isEmpty()){
      return;
    }
  ui->lblFoto->setPixmap(QPixmap(fileName).scaled(ui->lblFoto->size()));
  _foto.load(fileName);
}
