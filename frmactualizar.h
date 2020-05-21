#ifndef FRMACTUALIZAR_H
#define FRMACTUALIZAR_H

#include <QDialog>
#include "database.h"
#include "mainwindow.h"

namespace Ui {
class frmActualizar;
}

class frmActualizar : public QDialog
{
    Q_OBJECT

public:
    explicit frmActualizar(QWidget *parent = 0);
    ~frmActualizar();

private slots:
    void on_pushButton_12_clicked();
    void cargarDatos();
    void on_pushButton_clicked();


private:
    Ui::frmActualizar *ui;
    MainWindow *mainWW;
    //database *db;
};

#endif // FRMACTUALIZAR_H
