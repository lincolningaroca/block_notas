#include "frmdesencriptar.h"
#include "ui_frmdesencriptar.h"
#include <QMessageBox>

frmDesencriptar::frmDesencriptar(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmDesencriptar)
{
  ui->setupUi(this);
  mW=qobject_cast<MainWindow *>(parent);
}

frmDesencriptar::~frmDesencriptar()
{
  delete ui;
}

void frmDesencriptar::on_pushButton_clicked()
{
  if(mW->isEmptyText()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("El area de encriptacion esta vacía.."));
      ui->lineEdit->selectAll();
      ui->lineEdit->setFocus();
      return;
    }
  mW->decryptText(ui->lineEdit->text().toUInt());
  accept();

}
