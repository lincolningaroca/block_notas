#include "frmactualizar.h"
#include "ui_frmactualizar.h"
#include <QMessageBox>
//#include "database.h"
#include <QSqlTableModel>
#include "frmcambiarfrase.h"

frmActualizar::frmActualizar(QWidget *parent) :
  QDialog(parent), ui(new Ui::frmActualizar){
    ui->setupUi(this);

    mainWW=qobject_cast<MainWindow *>(parent);
    cargarDatos();
}

frmActualizar::~frmActualizar(){
    delete ui;
}
void frmActualizar::on_pushButton_12_clicked(){

    reject();
}

void frmActualizar::cargarDatos(){
    database *db=new database();
    db->conexion();
    QSqlTableModel *modelo=new QSqlTableModel(this,db->db);
    modelo->setTable("usuarios");
    modelo->setFilter(QString("dni='%1'").arg(db->getDNI(mainWW->getUsuario())));
    modelo->select();
    ui->tableView->setModel(modelo);
    ui->tableView->hideColumn(0);
    ui->tableView->hideColumn(1);
    ui->tableView->hideColumn(7);
    ui->tableView->hideColumn(9);
    ui->tableView->hideColumn(10);
}
void frmActualizar::on_pushButton_clicked(){
    accept();
}


