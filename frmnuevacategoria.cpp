#include "frmnuevacategoria.h"
#include "ui_frmnuevacategoria.h"

frmNuevaCategoria::frmNuevaCategoria(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmNuevaCategoria)
{
  ui->setupUi(this);
}

frmNuevaCategoria::~frmNuevaCategoria()
{
  delete ui;
}

void frmNuevaCategoria::on_pushButton_clicked()
{
  if(ui->lineEdit->text().isEmpty()){
      return;
    }
  emit _addItem(ui->lineEdit->text());
  ui->lineEdit->clear();
  accept();

}

void frmNuevaCategoria::on_lineEdit_textChanged(const QString &arg1)
{
  ui->lineEdit->setText(arg1.toUpper());
}
