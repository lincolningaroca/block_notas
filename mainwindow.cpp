#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QFont>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QPainter>
#include <QFontDialog>
#include <QColorDialog>
#include "frmlogin.h"
#include <finddialog.h>
#include <findreplacedialog.h>
#include <QSqlQueryModel>
#include "frmcambiarclave.h"
#include <QList>
#include <QProcess>
#include "frmcodigo.h"
#include "frmdesencriptar.h"
#include "frmregistro.h"
#include "frmdatosregistro.h"
#include "frmcontactos.h"
#include "frmeditadatos.h"
#include "frmcambiarfrase.h"
#include <QAction>
#include <QIcon>
#include <QStyleFactory>
#include <frmencripta.h>
#include "frmcaracteres.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  if(isValidReg()){
      ui->formatoToolBar->setVisible(true);
      ui->actionHerramientas_formato->setChecked(true);
      ui->actionHerramientas->setChecked(true);
      ui->mainToolBar->setVisible(true);
      ui->actionHerramientas_buscar->setChecked(true);
      ui->toolBar->setVisible(true);
    }else{
      readSettings();
    }
  setWindowTitle(QApplication::applicationName());
  windowsload();
  //comprobar registro de empresa.
  registro();
  //menu contextual
  createContextMenu();
  setCurrentFile("");
  connect(ui->textEdit->document(),&QTextDocument::contentsChanged,
          this,&MainWindow::documentWasModified);


  ui->actionCortar->setEnabled(false);
  ui->actionCopiar->setEnabled(false);
  connect(ui->textEdit, &QTextEdit::copyAvailable,
          ui->actionCortar,&QAction::setEnabled);
  connect(ui->textEdit,&QTextEdit::copyAvailable,
          ui->actionCopiar,&QAction::setEnabled);

  //comprobar si ahy elemtos en el listwidget

}

MainWindow::~MainWindow(){
  delete ui;
}

bool MainWindow::getState()
{
  state=ui->textEdit->document()->isEmpty();
  return state;
}

void MainWindow::on_actionQuitar_triggered(){
  close();
}

void MainWindow::on_actionAcerca_de_triggered()
{
//  QMessageBox::about(this,
//                     qApp->applicationName().append(
//                       "-Acerca del autor"),
//                     tr("<b>Autor: Lincoln Ingaroca de la Cruz<br>"
//                        "<br>Analista de sistemas-Programador<br>"
//                        "<br>lincolnf_2@hotmail.com.</b><br><br>") +
//                     +"<a href=\"http://www.swmicrosystems.890m.com\">"
//                      "SWMicrosystem's</a><br><br>");
  AboutDialog *about=new AboutDialog(this);
  about->exec();
}

void MainWindow::on_actionCopiar_triggered(){
  ui->textEdit->copy();
}

void MainWindow::on_actionPegar_triggered(){
  ui->textEdit->paste();
}

void MainWindow::on_actionCortar_triggered(){
  ui->textEdit->cut();
}

void MainWindow::on_actionSeleccionar_todo_triggered(){
  ui->textEdit->selectAll();
}

void MainWindow::on_actionNuevo_triggered(){
  if(maybeSave()){
      ui->textEdit->clear();
      setCurrentFile("");
    }
}
//boton abrir
void MainWindow::on_actionAbrir_triggered(){

  if(maybeSave()){
      QString fileName=QFileDialog::getOpenFileName(this,tr("Abrir archivo"),
                                                    QDir::rootPath(),
                                                    tr("Archivos de texto (*.txt);;Todos los archivos(*.*)"));
      if(!fileName.isEmpty()){
          loadFile(fileName);
        }
    }

}
//boton guardar
bool MainWindow::on_actionGuardar_como_triggered(){
  QFileDialog dialogo(this);
  dialogo.setNameFilter(tr("Archivos de texto (*.txt);; Todos los archivos (*.*)"));
  dialogo.setWindowModality(Qt::WindowModal);
  dialogo.setAcceptMode(QFileDialog::AcceptSave);
  QStringList files;
  if(dialogo.exec()){
      files=dialogo.selectedFiles();
    }else{
      return false;
    }
  return saveFile(files.at(0));
}

void MainWindow::on_actionTipo_de_fuente_triggered(){
  bool ok=true;
  fuente=QFontDialog::getFont(&ok,this);
  if(!ok){
      return;
    }
  ui->textEdit->setCurrentFont(fuente);
}

void MainWindow::on_actionColor_de_fuente_triggered(){
  colorFuente=QColorDialog::getColor(Qt::white,this);
  ui->textEdit->setTextColor(colorFuente);
}

void MainWindow::on_actionColor_de_fondo_triggered(){

  QColor color;
  QColorDialog dialogo(this);
  if (dialogo.exec()==QDialog::Rejected) {
      return;
    }
  color=dialogo.selectedColor();
  paleta.setColor(QPalette::Base,color);
  ui->textEdit->setPalette(paleta);
}

void MainWindow::on_actionDeshacer_triggered(){
  ui->textEdit->undo();
}

void MainWindow::on_actionRehacer_triggered(){
  ui->textEdit->redo();
}

/**
 *accion para impresion
 * @brief MainWindow::on_actionImprimir_triggered
 */
void MainWindow::on_actionImprimir_triggered(){
  QPrinter impresora;
  QTextDocument *documento=ui->textEdit->document();
  QPrintDialog dialogo(&impresora,this);
  if(dialogo.exec() == QDialog::Rejected){
      return;
    }
  documento->print(&impresora);
}

//llamada al formulario de inicio de sesión
void MainWindow::on_actionIniciar_sesion_triggered(){
  frmLogin *login=new frmLogin(this);
  if(login->exec()==QDialog::Rejected)
    return;
  currentUser=login->getUserName();
  activarMenu(true);
  opcionMenu(false);
  setNotePadMode(true);
  isValidNote();

}

//cerrar sesion
void MainWindow::on_actionCerrar_sesion_triggered(){
  activarMenu(false);
  opcionMenu();
  modoNotas(true);
  ui->textEdit->setReadOnly(false);
  ui->textEdit->clear();
  titulo->clear();
  fechaN->setDate(QDate::currentDate());
  ui->textEdit->setFocus();
  ui->dockWidget_2->setVisible(false);
  ui->actionMis_notas->setChecked(false);
  ui->actionGuardar_nota->setEnabled(true);
  ui->actionEditar_datos->setEnabled(false);
  ui->actionGuardarCambios->setEnabled(false);
  ui->actionNueva_nota->setEnabled(false);
  setNotePadMode(false);
}

void MainWindow::on_actionCrear_una_cuenta_triggered(){
  nuevo=new frmNuevaCuenta(this);
  nuevo->setFixedSize(731,438);
  nuevo->exec();
}

void MainWindow::activarMenu(bool op){
  if(op){
      ui->actionIniciar_sesion->setEnabled(false);
      ui->actionCerrar_sesion->setEnabled(true);
      ui->actionCrear_una_cuenta->setEnabled(false);
      ui->actionCambiar_contrase_a->setEnabled(true);
      ui->actionCambiar_pregunta_secreta->setEnabled(true);
      ui->menuNotas->setEnabled(true);
      ui->notasToolBar->setVisible(true);
      ui->actionHerramientas_mis_notas->setEnabled(true);
      ui->actionEditar_datos->setEnabled(true);
      ui->tituloToolBar->setVisible(true);
      ui->actionCifrar_texto->setEnabled(false);
      ui->actionDesencriptar_texto->setEnabled(false);
      ui->dockWidget_2->setVisible(true);
      ui->actionMis_notas->setChecked(true);
      //etiqueta que muestra el nombre e icono del usuario logeado.
      ui->textEdit->clear();
      usuarioLabel=new QLabel(this);
      usuarioLabel->setStyleSheet("color:#003300");
      usuarioLabel->setText(QString("Usuario conectado: <b>%1</b>").arg(currentUser));
      usuarioIcon=new QLabel(this);
      QPixmap pixmap(":images/icontexto-user-web-20-wordpress.png");
      usuarioIcon->setPixmap(pixmap.scaled(24,24,
                                           Qt::IgnoreAspectRatio,
                                           Qt::SmoothTransformation));
      //      currentUser=usuario;
      ui->statusBar->addPermanentWidget(usuarioIcon);
      ui->statusBar->addPermanentWidget(usuarioLabel,1);
      //cargar notas del usuario logeado
      cargarNotas();
    }else{
      ui->actionIniciar_sesion->setEnabled(true);
      ui->actionCerrar_sesion->setEnabled(false);
      ui->actionCrear_una_cuenta->setEnabled(true);
      ui->actionCambiar_contrase_a->setEnabled(false);
      ui->actionCambiar_pregunta_secreta->setEnabled(false);
      ui->actionEditar_datos->setEnabled(false);
      ui->menuNotas->setEnabled(false);
      ui->notasToolBar->setVisible(false);
      ui->actionHerramientas_mis_notas->setEnabled(false);
      ui->tituloToolBar->setVisible(false);
      ui->actionCifrar_texto->setEnabled(true);
      ui->actionDesencriptar_texto->setEnabled(true);
      ui->statusBar->removeWidget(usuarioIcon);
      ui->statusBar->removeWidget(usuarioLabel);
      usuarioLabel->clear();
      usuarioIcon->clear();
      ui->statusBar->showMessage(QString("Sesion cerrada"),5000);
    }
}

void MainWindow::opcionMenu(bool op){
  ui->actionAbrir->setEnabled(op);
  ui->actionGuardar_como->setEnabled(op);
  ui->actionGuardar->setEnabled(op);
  ui->actionNuevo->setEnabled(op);
}

void MainWindow::cargarNotas()
{
  db=new database();
  db->conexion();
  ui->listWidget->clear();
  QSqlQuery query;
  query.prepare("SELECT id_nota,titulo FROM notas n join usuarios u on\
                n.id_usuario=u.id_usuario AND usuario=?");

  query.addBindValue(getUsuario());
  if(!query.exec()){
    QMessageBox::critical(this,qApp->applicationName(),
                          tr("Error al ejecutar la sentencia.\n").append(
                            query.lastError().text()));
    return;
  }
  while(query.next()){
      data.insert(query.value(0).toInt(),
                  query.value(1).toString());
    }
  for(auto it=data.begin();it!=data.end();++it){
      QListWidgetItem *item=new QListWidgetItem(QIcon(":images/Planning.png"),
                                                it.value());
      ui->listWidget->addItem(item);
    }

  if(ui->listWidget->count()!=0){
      ui->listWidget->setEnabled(true);
    }
}

bool MainWindow::isEmptyText(){
  return ui->textEdit->document()->toPlainText().isEmpty();
}

void MainWindow::encryptText(quint64 clave){
  crypt=new SimpleCrypt();
  crypt->setKey(clave);
  ui->textEdit->setText(crypt->encryptToString(ui->textEdit->document()->toPlainText()));
}

void MainWindow::decryptText(quint64 clave){
  crypt=new SimpleCrypt();
  crypt->setKey(clave);
  ui->textEdit->setText(crypt->decryptToString(ui->textEdit->document()->toPlainText()));
}

void MainWindow::registro(){
  db=new database();
  if(db->registro()){
      ui->actionRegistro->setVisible(false);
      ui->actionDatos_de_registro->setVisible(true);
    }
}

void MainWindow::modoNotas(bool op){
  ui->menu_Editar->setEnabled(op);
  ui->menu_Fuente->setEnabled(op);
  ui->menu_Herramientas->setEnabled(op);
  ui->menu_ver->setEnabled(op);
  ui->mainToolBar->setEnabled(op);
  ui->actionAcerca_de->setEnabled(op);
  ui->toolBar->setEnabled(op);
}

void MainWindow::contactos(bool op){
  ui->actionContactos->setEnabled(op);
}

void MainWindow::setNotePadMode(bool op){
  notePadMode=op;
}

bool MainWindow::getNotePadMode(){
  return notePadMode;
}

void MainWindow::setCaracter(QString c)
{
  ui->textEdit->insertPlainText(c);

}

void MainWindow::activatedPanelCaracteres(bool op)
{
  ui->actionPanel_de_caracteres->setEnabled(op);
}

void MainWindow::on_actionAcerca_de_Qt_triggered(){
  QMessageBox::aboutQt(this,tr("Acerca de Qt"));
}

void MainWindow::on_actionEncontrar_triggered()
{
  m_findDialog->show();
}

void MainWindow::on_actionReemplazar_triggered(){
  m_findReplaceDialog->show();
}

void MainWindow::on_actionEditar_datos_triggered(){
  frmEditaDatos *edita=new frmEditaDatos(this,currentUser);
  //  edita->setFixedSize(531,299);
  edita->exec();
}

void MainWindow::on_actionHerramientas_mis_notas_triggered(){
  if(ui->actionHerramientas_mis_notas->isChecked()){
      ui->notasToolBar->setVisible(true);
    }else{
      ui->notasToolBar->setVisible(false);
    }
}
QString MainWindow::getUsuario()
{
  return currentUser;
}

void MainWindow::on_actionGuardar_nota_triggered()
{
  if(titulo->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Debe ingresar un titulo para esta nota."));
      titulo->setFocus();
      return;
    }
  if(ui->textEdit->document()->isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede guardar una nota en blanco."));
      ui->textEdit->setFocus();
      return;
    }
  db=new database();
  QString us=getUsuario();
  if(db->guardarNota(db->getIdUsuario(us),
                     titulo->text(),
                     fechaN->date(),
                     crypt->encryptToString(ui->textEdit->document()->toPlainText()))){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Nota guardada..."));
      titulo->clear();
      fechaN->setDate(QDate::currentDate());
      ui->textEdit->clear();
      ui->textEdit->setFocus();

      cargarNotas();
      ui->actioneliminarnota->setEnabled(true);
      qaction->setEnabled(true);
    }
}

void MainWindow::on_actionMis_notas_triggered(){
  if(ui->actionMis_notas->isChecked())
    ui->dockWidget_2->show();

  else
    ui->dockWidget_2->hide();
}

void MainWindow::on_actionCambiar_contrase_a_triggered(){
  frmCambiarClave *cambio=new frmCambiarClave(currentUser,this);
  cambio->exec();
}

void MainWindow::on_actionCalculadora_de_windows_triggered(){
  QProcess *myProcess=new QProcess(this);
  myProcess->start("calc.exe");
}

void MainWindow::on_actionCifrar_texto_triggered(){
  frmCodigo *codigo=new frmCodigo(this);
  codigo->setFixedSize(447,44);
  codigo->exec();
}

void MainWindow::on_actionDesencriptar_texto_triggered(){
  frmDesencriptar *des=new frmDesencriptar(this);
  des->setFixedSize(451,44);
  des->exec();
}

void MainWindow::on_actionRegistro_triggered(){
  frmRegistro *registro=new frmRegistro(this);
  registro->setFixedSize(400,145);
  registro->exec();
}

void MainWindow::on_actionDatos_de_registro_triggered(){
  frmDatosRegistro *datos=new frmDatosRegistro(this);
  datos->setFixedSize(516,295);
  datos->exec();
}

void MainWindow::on_actionVista_previa_triggered(){
  QPrinter printer(QPrinter::HighResolution);
  QPrintPreviewDialog preview(&printer,this);
  connect(&preview, SIGNAL(paintRequested(QPrinter*)),
          this,SLOT(printPreview(QPrinter*)));
  preview.exec();

}

void MainWindow::print(QPrinter *printer){
  QPainter qpainter(printer);
  qpainter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing|
                          QPainter::SmoothPixmapTransform,true);
  qpainter.drawText(printer->pageRect(),Qt::TextJustificationForced,
                    ui->textEdit->document()->toPlainText());
  // ui->textEdit->print(printer);

}

void MainWindow::createContextMenu(){
  ui->listWidget->setContextMenuPolicy(Qt::ActionsContextMenu);
  qaction=new QAction(QIcon(":images/6_-_Cross-128.png"),"Eliminar",this);
  ui->listWidget->addAction(qaction);
  connect(qaction,&QAction::triggered,this,&MainWindow::oon_eliminar_nota);
}

//guardar y cargar los estados de la aplicación
void MainWindow::writeSettings(){
  settings.beginGroup("Main window");
  settings.setValue("backgroundcolor",paleta);
  settings.setValue("tipoFuente",fuente);
  settings.setValue("ColorFuente",colorFuente);
  settings.setValue("styleWindows",styleWin);
  settings.endGroup();
  //estado de las tool bar

  toolBarSetting.beginGroup("Main windows_Tool bars");
  toolBarSetting.setValue("formatoToolBar",opFormato);
  toolBarSetting.setValue("buscarToolBar",opBuscar);
  toolBarSetting.setValue("mainToolBar",opBasicas);
  toolBarSetting.endGroup();
  //posicion y tamaño de la venta na principal
  /*posicion de la ventana principal*/
  MWState.beginGroup("Main window_pos_tam");
  MWState.setValue("MWPosition",mWPos);
  /*tamanaño de la ventana principal*/
  MWState.setValue("MWSize",mWSize);
  MWState.endGroup();
}

void MainWindow::readSettings(){
  settings.beginGroup("Main window");
  paleta= settings.value("backgroundcolor").value<QPalette>();
  ui->textEdit->setPalette(paleta);
  fuente=settings.value("tipoFuente").value<QFont>();
  ui->textEdit->setCurrentFont(fuente);
  colorFuente=settings.value("colorFuente").value<QColor>();
  ui->textEdit->setTextColor(colorFuente);
  styleWin=settings.value("styleWindows").toString();
  QApplication::setStyle(QStyleFactory::create(styleWin));
  settings.endGroup();
  //estado de las tool bar
  toolBarSetting.beginGroup("Main windows_Tool bars");
  opFormato=toolBarSetting.value("formatoToolBar").value<bool>();
  ui->actionHerramientas_formato->setChecked(opFormato);
  ui->formatoToolBar->setVisible(opFormato);
  //barra de herramientas buscar y reemplazar
  opBuscar=toolBarSetting.value("buscarToolBar").value<bool>();
  ui->actionHerramientas_buscar->setChecked(opBuscar);
  ui->toolBar->setVisible(opBuscar);
  //barra de herramientas principal
  opBasicas=toolBarSetting.value("mainToolBar").value<bool>();
  ui->actionHerramientas->setChecked(opBasicas);
  ui->mainToolBar->setVisible(opBasicas);
  toolBarSetting.endGroup();
  //posicion y tamaño de la venta na principal
  /*Posicion de la ventana principal*/
  MWState.beginGroup("Main window_pos_tam");
  mWPos=MWState.value("MWPosition").value<QPoint>();
  move(mWPos);
  /*Tamaño de la ventana principal*/
  mWSize=MWState.value("MWSize").value<QSize>();
  resize(mWSize);
  MWState.endGroup();

}

//al cargar la aplicaion
void MainWindow::windowsload(){
  ui->dockWidget_2->setVisible(false);
  ui->actionHerramientas_mis_notas->setChecked(true);
  ui->actionCerrar_sesion->setEnabled(false);
  ui->actionCambiar_contrase_a->setEnabled(false);
  ui->menuNotas->setEnabled(false);
  ui->notasToolBar->setVisible(false);
  ui->actionHerramientas_mis_notas->setEnabled(false);
  ui->tituloToolBar->setVisible(false);
  ui->actionEditar_datos->setEnabled(false);
  ui->actionGuardarCambios->setEnabled(false);
  ui->actionCambiar_pregunta_secreta->setEnabled(false);
  qreal margin=2.5;
  ui->textEdit->document()->setDocumentMargin(margin);
  //    ui->statusBar->addPermanentWidget(usuarioLabel);
  //formularios de buscar y reemplazar, instancia de objectos.
  m_findDialog=new FindDialog(this);
  m_findDialog->setModal(false);
  m_findDialog->setTextEdit(ui->textEdit);
  //formulario de reemplazar
  m_findReplaceDialog=new FindReplaceDialog(this);
  m_findReplaceDialog->setModal(false);
  m_findReplaceDialog->setTextEdit(ui->textEdit);
  //toolbar titulo
  tituloLabel=new QLabel("Titulo: ",this);
  ui->tituloToolBar->addWidget(tituloLabel);
  //lineedit
  titulo=new QLineEdit();
  titulo->setFixedWidth(256);
  titulo->setStyleSheet("background-color:#FFffCC");
  ui->tituloToolBar->addWidget(titulo);
  //date edit label
  fecha=new QLabel("\tFecha: ",this);
  //date edit control
  ui->tituloToolBar->addWidget(fecha);
  fechaN=new QDateEdit( QDate::currentDate(),this);
  fechaN->setCalendarPopup(true);
  ui->tituloToolBar->addWidget(fechaN);
  //objeto de encriptacion
  crypt=new SimpleCrypt(256);
}

bool MainWindow::maybeSave()
{
  if(ui->textEdit->document()->isModified()){
      QMessageBox::StandardButton ret;
      ret=QMessageBox::warning(this,
                               QApplication::applicationName(),
                               tr("El documento ha sido modificado.\n"
                                  "Desea guardar los cambios?"),
                               QMessageBox::Save|
                               QMessageBox::Discard|
                               QMessageBox::Cancel);
      if(ret==QMessageBox::Save)
        return on_actionGuardar_triggered();
      else if(ret==QMessageBox::Cancel)
        return false;
    }
  return true;
}

//void MainWindow::showContextMenu(const QPoint &pos){
//  (void)pos;
//  if(ui->listWidget->currentRow()==-1){
//      return;
//    }
//  //obtener id de la nota seleccionada
//  db=new database();
//  QList<QVariant> datos;
//  datos=db->datos_Notas(ui->listWidget->currentIndex().data().toString());
//  id_nota=datos.value(0).toInt();
//  //mostrar menu
//  const int x=cursor().pos().x();
//  const int y=cursor().pos().y();
//  menu->setGeometry(x,y,0,0);
//  menu->exec();
//}

void MainWindow::on_listWidget_clicked(const QModelIndex &index){
  db=new database();
  QList<QVariant> datos;
  datos=db->datos_Notas(index.data().toString());
  titulo->setText(datos.value(1).toString());
  fechaN->setDate(datos.value(2).toDate());
  ui->textEdit->setText(crypt->decryptToString(datos.value(3).toString()));
  ui->actionGuardarCambios->setEnabled(true);
  ui->actionNueva_nota->setEnabled(true);
  ui->actionGuardar_nota->setEnabled(false);
}

void MainWindow::oon_eliminar_nota(){
  db=new database();
  int ret=QMessageBox::question(this,
                                QApplication::applicationName(),
                                tr("Confirma que desea eliminar esta nota de la base de datos?"),
                                QMessageBox::Yes|
                                QMessageBox::No);
  if(ret==QMessageBox::No)
    return;
  id_nota=data.key(ui->listWidget->currentIndex().data().toString());
  if(!db->eliminarNota(id_nota)){
      QMessageBox::critical(this,qApp->applicationName(),
                            tr("Error al ejecutar esta acción\n").append(db->getError()));
      return;
    }
  data.remove(id_nota);
  cargarNotas();
  isValidNote();
  ui->textEdit->clear();
  titulo->clear();
}

void MainWindow::on_actionContactos_triggered(){
  contacto=new frmContactos(this);

//  contacto->setFixedSize(890,617);
  contacto->showNormal();
  contactos(false);
}

void MainWindow::closeEvent(QCloseEvent *e){
  mWPos=pos();
  mWSize=size();
  if(getNotePadMode()){
      QMessageBox::warning(this,
                           QApplication::applicationName().append(
                             " <Cerrar sesión..>"),
                           tr("<p style=\"color:#660000\">Antes de salir de la aplicación, debe cerrar sesión...<br>"
                              "Ir a menu: <b>Archivo->Usuarios->CerrarSesión.</b><br>"
                              "O puede presionar la combinación de teclas <b>Ctrl+Alt+P</b></p>"));
      e->ignore();
    }else{

      if(maybeSave()){

          writeSettings();
          e->accept();
        }else{

          e->ignore();
        }
    }
}

void MainWindow::on_actionNueva_nota_triggered(){
  ui->actionGuardar_nota->setEnabled(true);
  ui->actionGuardarCambios->setEnabled(false);
  ui->actionNueva_nota->setEnabled(false);
  titulo->clear();
  ui->textEdit->clear();
  fechaN->setDate(QDate().currentDate());
  titulo->setFocus();
}

void MainWindow::on_actionGuardarCambios_triggered(){
  int idNota=0;
  db=new database();
  QList<QVariant> datos;
  datos=db->datos_Notas(ui->listWidget->currentIndex().data().toString());
  idNota=datos.value(0).toInt();
  if(titulo->text().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Ingrese un título."));
      titulo->setFocus();
      return;
    }
  if(ui->textEdit->document()->toPlainText().isEmpty()){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("No puede dejar vacío el contenido."));
      ui->textEdit->setFocus();
      return;
    }
  if(db->actualizaNota(titulo->text(),fechaN->date(),
                       crypt->encryptToString(ui->textEdit->document()->toPlainText()),
                       idNota,db->getIdUsuario(getUsuario()))){
      QMessageBox::information(this,QApplication::applicationName(),
                               tr("Datos guardados.."));
      cargarNotas();
    }
}

void MainWindow::on_actionCambiar_pregunta_secreta_triggered(){
  frmCambiarFrase *cfrase=new frmCambiarFrase(currentUser,this);
  cfrase->exec();
}

void MainWindow::on_actionUrl_list_Directory_triggered(){
  QProcess *myProcess=new QProcess(this);
  myProcess->start("UrlListDirectory.exe");
}

void MainWindow::on_actionTemas_de_ayuda_triggered(){
  QDesktopServices::openUrl(QUrl::fromLocalFile(
                              QCoreApplication::applicationDirPath()+
                              "/help/swnotepad.chm"));
}

void MainWindow::on_actionWindows_triggered()
{
  QApplication::setStyle(QStyleFactory::create("windows"));
  styleWin="windows";
}

void MainWindow::on_actionFusion_triggered()
{
  QApplication::setStyle(QStyleFactory::create("Fusion"));
  styleWin="fusion";
}

void MainWindow::on_actionWindows_XP_triggered()
{
  QApplication::setStyle(QStyleFactory::create("windowsxp"));
  styleWin="windowsxp";
}

void MainWindow::on_actionEncriptar_un_archivo_triggered()
{
  frmEncripta *e=new frmEncripta(this);
  e->setFixedSize(400,102);
  e->exec();
}

//acciones cambiadas************************************************************************
bool MainWindow::on_actionGuardar_triggered()
{
  if(curFile.isEmpty()){
      return on_actionGuardar_como_triggered();
    }else{
      return saveFile(curFile);
    }
}

bool MainWindow::saveFile(const QString &fileName){
  QFile file(fileName);
  if(!file.open(QFile::WriteOnly|QFile::Text)){
      QMessageBox::warning(this,
                           QApplication::applicationName(),
                           tr("Error al guardar el archivo %1:\n%2.")
                           .arg(fileName)
                           .arg(file.errorString()));
      return false;
    }
  QTextStream out(&file);
  out<<ui->textEdit->toPlainText();
  setCurrentFile(fileName);
  return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
  curFile=fileName;
  ui->textEdit->document()->setModified(false);
  setWindowModified(false);
  QString shownName=curFile;
  if(curFile.isDetached()){
      shownName="Sin título";
    }
  setWindowFilePath(shownName);
}

void MainWindow::documentWasModified(){
  setWindowModified(ui->textEdit->document()->isModified());

}

void MainWindow::loadFile(const QString &fileName)
{
  QFile file(fileName);
  if(!file.open(QFile::ReadOnly|QFile::Text)){
      QMessageBox::warning(this,
                           QApplication::applicationName(),
                           tr("Error al cargar el archivo %1:\n%2.")
                           .arg(fileName)
                           .arg(file.errorString()));
      return;
    }
  QTextStream in(&file);
  ui->textEdit->setPlainText(in.readAll());
  setCurrentFile(fileName);
}

bool MainWindow::isValidReg()
{
  return toolBarSetting.allKeys().isEmpty();
}

void MainWindow::on_actionCentrado_triggered(){
  ui->textEdit->setAlignment(Qt::AlignHCenter);
}

void MainWindow::on_actionIzquierda_triggered()
{
  ui->textEdit->setAlignment(Qt::AlignLeft|Qt::AlignAbsolute);
}

void MainWindow::on_actionDerecha_triggered(){
  ui->textEdit->setAlignment(Qt::AlignRight|Qt::AlignAbsolute);
}

void MainWindow::on_actionJustificado_triggered(){
  ui->textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::printPreview(QPrinter *printer)
{
  ui->textEdit->print(printer);
}

void MainWindow::on_actionPanel_de_caracteres_triggered()
{
  frmCaracteres *c=new frmCaracteres(this);
  c->setWindowOpacity(0.98);
  c->show();
  activatedPanelCaracteres();
}

void MainWindow::on_actionEstilo_por_defecto_triggered()
{
  if(styleWin=="")
    return;
  else{
      QMessageBox::information(this,
                               QApplication::applicationName(),
                               tr("Para poder ver los cambios, necesita reiniciar el programa..<br>"
                                  "<b>\"Solo con el estilo: default.\"</b>"));
      QApplication::setStyle(QStyleFactory::create(""));
      styleWin="";
    }
}

void MainWindow::on_actionHerramientas_triggered(bool checked)
{
  ui->mainToolBar->setVisible(checked);
  opBasicas=checked;
}

void MainWindow::on_actionHerramientas_buscar_triggered(bool checked)
{
  ui->toolBar->setVisible(checked);
  opBuscar=checked;
}

void MainWindow::on_actionHerramientas_formato_triggered(bool checked)
{
  ui->formatoToolBar->setVisible(checked);
  opFormato=checked;
}

void MainWindow::filePrintPdf()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
//! [0]
    QFileDialog fileDialog(this, tr("Export PDF"));
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    fileDialog.setMimeTypeFilters(QStringList("application/pdf"));
    fileDialog.setDefaultSuffix("pdf");
    if (fileDialog.exec() != QDialog::Accepted)
        return;
    QString fileName = fileDialog.selectedFiles().first();
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    ui->textEdit->document()->print(&printer);
    statusBar()->showMessage(tr("Exported \"%1\"")
                             .arg(QDir::toNativeSeparators(fileName)));
//! [0]
#endif
}

void MainWindow::isValidNote()
{
  if(data.count()==0)
    {
      ui->actioneliminarnota->setEnabled(false);
      qaction->setEnabled(false);
      ui->actionGuardarCambios->setEnabled(false);
    }else{
      ui->actioneliminarnota->setEnabled(true);
      qaction->setEnabled(true);
      ui->actionGuardarCambios->setEnabled(true);
    }
}

void MainWindow::on_actionExportar_como_pdf_triggered()
{
  filePrintPdf();
}

void MainWindow::on_actioneliminarnota_triggered()
{
  oon_eliminar_nota();
}


