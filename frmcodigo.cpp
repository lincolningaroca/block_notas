#include "frmcodigo.h"
#include "ui_frmcodigo.h"
#include <QMessageBox>
#include "simplecrypt.h"


frmCodigo::frmCodigo(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmCodigo)
{
  ui->setupUi(this);
  mWindows=static_cast<MainWindow *>(parent);
  ui->pushButton->setEnabled(false);
  ui->lineEdit->setValidator(new QIntValidator(this));
}

frmCodigo::~frmCodigo()
{
  delete ui;
}
void frmCodigo::on_lineEdit_textChanged(const QString &arg1)
{
  if(arg1.length()==0){
      ui->pushButton->setEnabled(false);
    }else{
      ui->pushButton->setEnabled(true);
    }
}

void frmCodigo::on_pushButton_clicked()
{
  if(mWindows->isEmptyText()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("El area de encriptacion no puede estar vacía.."));
      ui->lineEdit->selectAll();
      return;
    }
  mWindows->encryptText(ui->lineEdit->text().toUInt());
  QDialog::accept();
}
