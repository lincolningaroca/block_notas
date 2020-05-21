#include "frmdedicatoria.h"
#include "ui_frmdedicatoria.h"
#include <QFile>
#include <QTextStream>
frmDedicatoria::frmDedicatoria(QWidget *parent) :
    QDialog(parent), ui(new Ui::frmDedicatoria)
{
    ui->setupUi(this);
    QFile archivo(":dedicatoria.txt");
    if(!archivo.open(QIODevice::ReadOnly | QIODevice::Text)){
        return;
    }
    QTextStream in(&archivo);
    QString contenido=in.readAll();
    ui->txtDedicatoria->setText(contenido);
    ui->txtDedicatoria->setAlignment(Qt::AlignJustify);
    archivo.close();
}

frmDedicatoria::~frmDedicatoria()
{
    delete ui;


}
