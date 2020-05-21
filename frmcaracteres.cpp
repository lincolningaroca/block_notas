#include "frmcaracteres.h"
#include "ui_frmcaracteres.h"
#include <QMessageBox>

frmCaracteres::frmCaracteres(QWidget *parent) :
  QDialog(parent),ui(new Ui::frmCaracteres)
{
  ui->setupUi(this);

  ui->tableWidget->setColumnWidth(0,80);
  ui->tableWidget->setColumnWidth(1,80);
  ui->tableWidget->setColumnWidth(2,90);
  m_Window=qobject_cast<MainWindow *>(parent);
  ui->tableWidget->setToolTip("<img src=\":images/important.png\"/>"
                              "<p style='color:#003333'>Haga doble click en una fila para insertar"
                              " el carácter correspondiente..</p>");
  ui->tableWidget->setToolTipDuration(5000);
}

frmCaracteres::~frmCaracteres()
{
  delete ui;
}

void frmCaracteres::on_tableWidget_doubleClicked(const QModelIndex &index){
  m_Window->setCaracter(ui->tableWidget->item(index.row(),2)->text());
}

void frmCaracteres::closeEvent(QCloseEvent *evt)
{
    m_Window->activatedPanelCaracteres(true);
    evt->accept();
}
