#ifndef FRMDEDICATORIA_H
#define FRMDEDICATORIA_H

#include <QDialog>

namespace Ui {
class frmDedicatoria;
}

class frmDedicatoria : public QDialog
{
    Q_OBJECT

public:
    explicit frmDedicatoria(QWidget *parent = 0);
    ~frmDedicatoria();

private:
    Ui::frmDedicatoria *ui;
};

#endif // FRMDEDICATORIA_H
