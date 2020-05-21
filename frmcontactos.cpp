#include "frmcontactos.h"
#include "ui_frmcontactos.h"
#include <QMessageBox>
#include <QIntValidator>
#include <QDebug>

frmContactos::frmContactos(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::frmContactos){
  ui->setupUi(this);
  db=new database();

  mwindows=qobject_cast<MainWindow *>(parent);


  nuevaCategoria=new frmNuevaCategoria(this);
  connect(nuevaCategoria,&frmNuevaCategoria::_addItem,
          this,&frmContactos::itemInsertado);
//  setWindowFlags(Qt::Dialog);

  windowsLoad();

  //dialogo para cargar foto
  dialogo=new QFileDialog(this);
  dialogo->setAcceptMode(QFileDialog::AcceptOpen);
  dialogo->setNameFilter(tr("Imagenes(*.png *.jpg *jpeg)"));
  dialogo->setVisible(QFileDialog::Detail);
  rx.setPattern("^[_a-z0-9-]+(\\.[_a-z0-9-]+)*@[a-z0-9-]+(\\.[a-z0-9-]+)*(\\.[a-z]{2,4})$");
  v.setRegExp(rx);

  //  cargarListaContactos();
  connect(ui->listWidget->selectionModel(),&QItemSelectionModel::currentChanged,
          this,&frmContactos::cargarDatosContacto);
  //  connect(ui->listView,&QAbstractItemView::clicked,this,&frmContactos::cargarDatosContacto);
  ui->listWidget->setFocus();
}

frmContactos::~frmContactos(){
  delete ui;
}

void frmContactos::itemInsertado(QString item){

  if(db->nuevaCategoria(item)){
      ui->comboBox_4->clear();
      llenarDatosCategoria();
      ui->comboBox_4->setCurrentText(item);
    }
}

void frmContactos::llenarDatosCategoria()
{

  QStringList listaCategorias;
  listaCategorias=db->categorias();
  ui->comboBox_4->addItems(listaCategorias);
  ui->comboBox_4->insertItem(0,"");
  ui->comboBox_4->insertItem(ui->comboBox_4->count(),"Nueva categoria..");
  ui->comboBox_4->setCurrentIndex(0);
  //segundo combo box de la pestaña actualizar

}

void frmContactos::validations()
{
  ui->txtDni->setValidator(new QIntValidator(this));
  QRegExp exp("[a-z A-Z ñ Ñ]{50}");
  QValidator *validator=new QRegExpValidator(exp,this);
  ui->txtApellidos->setValidator(validator);
  ui->txtNombres->setValidator(validator);
  QRegExp expInt("\\d{0,30}");
  QValidator *val=new QRegExpValidator(expInt,this);
  ui->txtTelefono->setValidator(val);
  ui->txtTelefono_2->setValidator(val);
}

void frmContactos::cargarListaContactos()
{

  db->conexion();
  QSqlQuery query;
  query.prepare("select id_contacto,capellidos, cnombres from contactos c join usuarios u\
                on c.id_usuario=u.id_usuario and usuario=?");
                                                          query.addBindValue(mwindows->getUsuario());
      if(!query.exec()){
    QMessageBox::critical(this,qApp->applicationName(),"Error\n"+
                          query.lastError().text()+ mwindows->getUsuario());
    return;
  }
  while(query.next()){
      //      res.insert(query.value(0).toInt(),query.value(1).toString());
      res.insert(query.value(0).toUInt(),
                 query.value(2).toString().append(" "+query.value(1).toString()));
    }
  //  QMap<int,QString>::iterator it;
  for(auto it=res.begin();it!=res.end();++it){
      item=new QListWidgetItem(QIcon(":/images/1401844315_Manager.png"),
                               it.value());
      ui->listWidget->addItem(item);
      qDebug()<<it.value()<<endl;
    }

}

void frmContactos::cargarDatosContacto()
{
  QList<QVariant>datosContacto;
  int id=res.key(ui->listWidget->currentIndex().data().toString());
  datosContacto=db->datosContacto(id,db->getIdUsuario(mwindows->getUsuario()));
  ui->a_dni->setText(datosContacto.value(2).toString());
  ui->a_apellidos->setText(datosContacto.value(3).toString());
  ui->a_nombres->setText(datosContacto.value(4).toString());
  ui->a_nacimiento->setDate(datosContacto.value(5).toDate());
  ui->cboGenero_2->setCurrentText(datosContacto.value(6).toString());
  ui->cboEstadoCivil_2->setCurrentText(datosContacto.value(7).toString());
  ui->txtDireccion_2->setText(datosContacto.value(8).toString());
  ui->txtDepartamento_2->setText(datosContacto.value(9).toString());
  ui->txtProvincia_2->setText(datosContacto.value(10).toString());
  ui->txtDistrito_2->setText(datosContacto.value(11).toString());
  ui->txtTelefono_2->setText(datosContacto.value(12).toString());
  ui->cboTipoNumero_2->setCurrentText(datosContacto.value(13).toString());
  ui->txtEmail_2->setText(datosContacto.value(14).toString());
  ui->comboBox_5->setCurrentText(datosContacto.value(15).toString());
  ui->textEdit_2->setText(datosContacto.value(16).toString());
  cargarFoto(datosContacto.value(17).toString());
  //QMessageBox::information(this,"hjh",datosContacto.value(17).toString());
  manageControls(true);
  //  ui->a_apellidos->setFocus();
  //QMessageBox::information(this,"jhjhhl",datosContacto.value(17).toString());
}

void frmContactos::windowsLoad()
{
  llenarDatosCategoria();
  cargarListaContactos();
  validations();
  ui->actionGuardar->setEnabled(false);
  ui->a_dni->setEnabled(false);
  ui->txtEmail_2->setEnabled(false);
  manageControls(false);
  QStringList listaCategorias;
  listaCategorias=db->categorias();
  ui->comboBox_5->addItems(listaCategorias);
  ui->comboBox_5->insertItem(0,"");
  ui->comboBox_5->setCurrentIndex(0);
  fotoPorDefecto();
  if(ui->listWidget->count()==0){
      ui->actionActualizarDatos->setEnabled(false);
      ui->actionEliminarContacto->setEnabled(false);
    }else{
      ui->actionActualizarDatos->setEnabled(true);
      ui->actionEliminarContacto->setEnabled(true);
    }
  ui->contactos->setCurrentIndex(0);
}

void frmContactos::manageControls(bool st)
{
  //ui->a_dni->setEnabled(st);
  ui->a_apellidos->setEnabled(st);
  ui->a_nombres->setEnabled(st);
  ui->a_nacimiento->setEnabled(st);
  ui->cboGenero_2->setEnabled(st);
  ui->cboEstadoCivil_2->setEnabled(st);
  ui->txtDireccion_2->setEnabled(st);
  ui->txtDepartamento_2->setEnabled(st);
  ui->txtProvincia_2->setEnabled(st);
  ui->txtDistrito_2->setEnabled(st);
  ui->txtTelefono_2->setEnabled(st);
  ui->cboTipoNumero_2->setEnabled(st);
  ui->pushButton_2->setEnabled(st);
  //ui->txtEmail_2->setEnabled(st);
  ui->comboBox_5->setEnabled(st);
  ui->textEdit_2->setEnabled(st);
}

void frmContactos::fotoPorDefecto()
{
  QPixmap pixmap(":/images/default.png");
  ui->lblFoto->setPixmap(pixmap.scaled(91,75,
                                       Qt::IgnoreAspectRatio,
                                       Qt::SmoothTransformation));
  ui->lblFoto_2->setPixmap(pixmap.scaled(91,75,
                                         Qt::IgnoreAspectRatio,
                                         Qt::SmoothTransformation));
}

void frmContactos::cargarFoto(QString foto)
{
  QString path=foto;
  QFile archivo(path);
  archivo.open(QIODevice::ReadOnly);
  if(archivo.exists()){
      QPixmap pixmap(path);
      ui->lblFoto_2->setPixmap(pixmap.scaled(ui->lblFoto_2->size()));
    }else{
      fotoPorDefecto();
    }

}

void frmContactos::limpiarControles(QString op)
{
  if(op=="guardar"){
      ui->txtDni->clear();
      ui->txtApellidos->clear();
      ui->txtNombres->clear();
      ui->Nacimiento->setDate(QDate::currentDate());
      ui->cboGenero->setCurrentIndex(0);
      ui->cboEstadoCivil->setCurrentIndex(0);
      ui->txtDireccion->clear();
      ui->txtDepartamento->clear();
      ui->txtProvincia->clear();
      ui->txtDistrito->clear();
      ui->txtTelefono->clear();
      ui->cboTipoNumero->setCurrentIndex(0);
      ui->txtEmail->clear();
      ui->comboBox_4->setCurrentIndex(0);
      ui->textEdit->clear();
      ui->listWidget->clear();
      //ui->lblFoto->setPixmap(nombreArchivo);
      fotoPorDefecto();
    }else{
      ui->a_dni->clear();
      ui->a_apellidos->clear();
      ui->a_nombres->clear();
      ui->a_nacimiento->setDate(QDate::currentDate());
      ui->cboGenero_2->setCurrentIndex(0);
      ui->cboEstadoCivil_2->setCurrentIndex(0);
      ui->txtDireccion_2->clear();
      ui->txtDepartamento_2->clear();
      ui->txtProvincia_2->clear();
      ui->txtDistrito_2->clear();
      ui->txtTelefono_2->clear();
      ui->cboTipoNumero_2->setCurrentIndex(0);
      ui->txtEmail_2->clear();
      ui->comboBox_5->setCurrentIndex(0);
      ui->textEdit_2->clear();
      ui->listWidget->clear();
      //ui->lblFoto->setPixmap(nombreArchivo);
      fotoPorDefecto();
    }
}

void frmContactos::on_comboBox_4_activated(const QString &arg1)
{
  if(arg1.compare("Nueva categoria..")==0){
      ui->comboBox_4->setCurrentIndex(0);
      nuevaCategoria->setFixedSize(400,80);
      //      nuevaCategoria=new frmNuevaCuenta(this);
      nuevaCategoria->exec();
    }
}

void frmContactos::on_actionGuardar_triggered()
{
  QString text=ui->txtEmail->text();
  int pos=0;
  //validacion, entrada de datos.
  if(ui->txtDni->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo.."));
      ui->txtDni->setFocus();
      return;
    }
  if(ui->txtDni->text().length()<8){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Un DNI se compone por 8 dígitos.."));
      ui->txtDni->selectAll();
      ui->txtDni->setFocus();
      return;
    }
  if(db->comprobarDni(ui->txtDni->text(),db->getIdUsuario(mwindows->getUsuario()))){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Este número ya está registrado en la base de datos.."));
      ui->txtDni->selectAll();
      ui->txtDni->setFocus();
      return;
    }
  if(ui->txtApellidos->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->txtApellidos->setFocus();
      return;
    }
  if(ui->txtNombres->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->txtNombres->setFocus();
      return;
    }
  if(ui->cboGenero->currentIndex()==0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Seleccione una opción válida."));
      ui->cboGenero->setFocus();
      return;
    }
  if(ui->cboEstadoCivil->currentIndex()==0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Seleccione una opción válida."));
      ui->cboEstadoCivil->setFocus();
      return;
    }
  if(ui->txtDireccion->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->txtDireccion->setFocus();
      return;
    }


  if(!ui->txtEmail->text().isEmpty())
    {
      if(db->comprobarEmail(ui->txtEmail->text(),db->getIdUsuario(mwindows->getUsuario()))){
          QMessageBox::information(this,QApplication::applicationName(),
                                   tr("Esta dirección de correo ya esta registrada en la base de datos...."));
          ui->txtEmail->selectAll();
          ui->txtEmail->setFocus();
          return;
        }
    }
  /*
        Validacion del patron de la direccion de correo electronico.

    */

  if(v.validate(text,pos)==QValidator::Invalid)
    {
      QMessageBox::warning(this,
                           QApplication::applicationName(),
                           tr("La dirección de correo que ingreso no es correcta..."));
      ui->txtEmail->selectAll();
      ui->txtEmail->setFocus();
      return;
    }

  con.setIdUsuario1(db->getIdUsuario(mwindows->getUsuario()));
  con.setDni(ui->txtDni->text());
  con.setApellidos(ui->txtApellidos->text());
  con.setNombres(ui->txtNombres->text());
  con.setNacimiento(ui->Nacimiento->date());
  con.setGenero(ui->cboGenero->currentText());
  con.setEstadoCivil(ui->cboEstadoCivil->currentText());
  con.setDireccion(ui->txtDireccion->text());
  con.setDepartamento(ui->txtDepartamento->text());
  con.setProvincia(ui->txtProvincia->text());
  con.setDistrito(ui->txtDistrito->text());
  con.setNum_telefono(ui->txtTelefono->text());
  con.setTipo_num(ui->cboTipoNumero->currentText());
  con.setEmail(ui->txtEmail->text());
  con.setCat_contacto(ui->comboBox_4->currentText());
  con.setComentario(ui->textEdit->document()->toPlainText());
  con.setFoto(nombreArchivo);

  if(db->nuevoContacto(con))
    {
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Datos guardados.."));
      limpiarControles();
      //      listModel=nullptr;
      ui->contactos->setCurrentIndex(0);
      ui->listWidget->setEnabled(true);
      cargarListaContactos();
      ui->actionGuardar->setEnabled(false);
      ui->actionActualizarDatos->setEnabled(true);
      ui->actionEliminarContacto->setEnabled(true);
      ui->listWidget->setFocus(Qt::OtherFocusReason);
      ui->listWidget->setCurrentRow(ui->listWidget->count()-1,
                                    QItemSelectionModel::Select);
      //      ui->txtDni->setFocus();
    }
  nombreArchivo.clear();
}


void frmContactos::on_actionActualizarDatos_triggered()
{
  if(ui->a_apellidos->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->a_apellidos->setFocus();
      return;
    }
  if(ui->a_nombres->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->a_nombres->setFocus();
      return;
    }
  if(ui->cboGenero_2->currentIndex()==0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Seleccione una opción válida."));
      ui->cboGenero_2->setFocus();
      return;
    }
  if(ui->cboEstadoCivil_2->currentIndex()==0){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Seleccione una opción válida."));
      ui->cboEstadoCivil_2->setFocus();
      return;
    }
  if(ui->txtDireccion_2->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío este campo...."));
      ui->txtDireccion_2->setFocus();
      return;
    }
  int id=res.key((ui->listWidget->currentIndex().data().toString()));

  //asignar valores a la clase contactos
  con.setApellidos(ui->a_apellidos->text());
  con.setNombres(ui->a_nombres->text());
  con.setNacimiento(ui->a_nacimiento->date());
  con.setGenero(ui->cboGenero_2->currentText());
  con.setEstadoCivil(ui->cboEstadoCivil_2->currentText());
  con.setDireccion(ui->txtDireccion_2->text());
  con.setDepartamento(ui->txtDepartamento_2->text());
  con.setProvincia(ui->txtProvincia_2->text());
  con.setDistrito(ui->txtDistrito_2->text());
  con.setNum_telefono(ui->txtTelefono_2->text());
  con.setTipo_num(ui->cboTipoNumero_2->currentText());
  con.setEmail(ui->txtEmail_2->text());
  con.setCat_contacto(ui->comboBox_5->currentText());
  con.setComentario(ui->textEdit_2->document()->toPlainText());
  con.setFoto(nombreArchivo);
  //ejecutar actualizacion
  if(db->actualizaDatosContacto(con,id,db->getIdUsuario(mwindows->getUsuario()))){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Datos actualizados.."));
      limpiarControles("actualiza");

    }
  cargarListaContactos();
  //  ui->listWidget->setFocus(Qt::OtherFocusReason);
  //  QModelIndex index=ui->listWidget->currentIndex();
  ui->listWidget->setCurrentRow(ui->listWidget->count()-1,
                                QItemSelectionModel::Select);
  nombreArchivo.clear();
}

void frmContactos::on_contactos_tabBarClicked(int index)
{
  if(index==1){
      ui->actionGuardar->setEnabled(true);
      ui->actionActualizarDatos->setEnabled(false);
      ui->actionEliminarContacto->setEnabled(false);
      ui->listWidget->setEnabled(false);
      ui->txtDni->setFocus();

    }else{
      if(ui->listWidget->model()->rowCount()==0){
          ui->actionActualizarDatos->setEnabled(false);
          ui->actionEliminarContacto->setEnabled(false);
        }else{
          ui->actionActualizarDatos->setEnabled(true);
          ui->actionEliminarContacto->setEnabled(true);
          ui->listWidget->setEnabled(true);
        }

      ui->actionGuardar->setEnabled(false);
      //ui->actionActualizarDatos->setEnabled(true);
      //ui->actionEliminarContacto->setEnabled(true);

    }
}

void frmContactos::on_pushButton_2_clicked()
{
  if(dialogo->exec()==QDialog::Rejected){
      return;
    }

  nombreArchivo=dialogo->selectedFiles().first();
  QPixmap pixmap(nombreArchivo);
  ui->lblFoto_2->setPixmap(
        pixmap.scaled(
          ui->lblFoto_2->width(),
          ui->lblFoto_2->height(),
          Qt::IgnoreAspectRatio,
          Qt::SmoothTransformation));
}

void frmContactos::on_pushButton_clicked()
{
  if(dialogo->exec()==QDialog::Rejected){
      return;
    }

  nombreArchivo=dialogo->selectedFiles().first();
  QPixmap pixmap(nombreArchivo);
  ui->lblFoto->setPixmap(
        pixmap.scaled(
          ui->lblFoto->width(),
          ui->lblFoto->height(),
          Qt::IgnoreAspectRatio,
          Qt::SmoothTransformation));
}

void frmContactos::on_actionEliminarContacto_triggered()
{
  //  if(ui->listWidget->currentRow()==-1){
  //      return;
  //    }
  int ret=QMessageBox::question(this,QApplication::applicationName(),
                                tr("Confirma que desea eliminar a: ")+\
                                "<b>"+ui->listWidget->currentIndex().data().toString()+
                                "</b>"+" de la base de datos..",\
                                QMessageBox::Yes | QMessageBox::No);
  if(ret==QMessageBox::No){
      return;
    }
  int idContacto=res.key(ui->listWidget->currentIndex().data().toString());
  if(db->eliminarContacto(idContacto,db->getIdUsuario(mwindows->getUsuario()))){
      //          QMessageBox::information(this,QApplication::applicationName(),
      //                                   tr("El contacto fue eliminado.."));
      //          ui->listWidget->clear();
      //          cargarListaContactos();
      //      if(ui->listWidget->count()==0){
      //          ui->actionActualizarDatos->setEnabled(false);
      //          ui->actionEliminarContacto->setEnabled(false);
      //          ui->listWidget->setEnabled(false);
      //          limpiarControles("actualiza");
      //          manageControls(false);
      //        }else{
      //          ui->actionActualizarDatos->setEnabled(true);
      //          ui->actionEliminarContacto->setEnabled(true);
      //          ui->listWidget->setEnabled(true);
      //              ui->listView->model().
      //        }
      ui->listWidget->clear();
      res.remove(idContacto);
      limpiarControles("otro");
      cargarListaContactos();
      //      res.clear();
      ui->listWidget->setCurrentRow(ui->listWidget->count()-1,QItemSelectionModel::Select);
    }
  //  ui->listWidget->clear();

}

void frmContactos::closeEvent(QCloseEvent *e)
{
  mwindows->contactos(true);
  e->accept();
}



