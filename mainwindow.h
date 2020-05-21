#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <frmnuevacuenta.h>
#include <QLabel>
#include <QLineEdit>
#include <QDateEdit>
#include "database.h"
#include "simplecrypt.h"
#include <QPrinter>
//#include <QMenu>
#include <QCloseEvent>
#include <QSettings>
#include <QDesktopServices>
#include <QUrl>
#include "frmdedicatoria.h"
#include <QSize>
#include "aboutdialog.h"

namespace Ui {
    class MainWindow;
}
class FindDialog;
class FindReplaceDialog;
class frmContactos;
class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
  virtual void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
  bool getState();

private:


private slots:
    void on_actionQuitar_triggered();
    void on_actionAcerca_de_triggered();
    void on_actionCopiar_triggered();
    void on_actionPegar_triggered();
    void on_actionCortar_triggered();
    void on_actionSeleccionar_todo_triggered();
    void on_actionNuevo_triggered();
    void on_actionAbrir_triggered();
    bool on_actionGuardar_como_triggered();
    void on_actionTipo_de_fuente_triggered();
    void on_actionColor_de_fuente_triggered();
    void on_actionColor_de_fondo_triggered();
    void on_actionDeshacer_triggered();
    void on_actionRehacer_triggered();
    void on_actionImprimir_triggered();
    void on_actionIniciar_sesion_triggered();
    void on_actionCerrar_sesion_triggered();
    void on_actionCrear_una_cuenta_triggered();
    void on_actionAcerca_de_Qt_triggered();
    void on_actionEncontrar_triggered();
    void on_actionReemplazar_triggered();
    void on_actionEditar_datos_triggered();
    void on_actionHerramientas_mis_notas_triggered();
    void on_actionGuardar_nota_triggered();
    void on_actionMis_notas_triggered();
    void on_actionCambiar_contrase_a_triggered();
    void on_actionCalculadora_de_windows_triggered();
    void on_actionCifrar_texto_triggered();
    void on_actionDesencriptar_texto_triggered();
    void on_actionRegistro_triggered();
    void on_actionDatos_de_registro_triggered();
    void on_actionVista_previa_triggered();
    void print(QPrinter *printer);
//    void showContextMenu(const QPoint &pos);
    void on_listWidget_clicked(const QModelIndex &index);
    //slot eliminar nota.
    void oon_eliminar_nota();
    void on_actionContactos_triggered();
    void on_actionNueva_nota_triggered();
    void on_actionGuardarCambios_triggered();
    void on_actionCambiar_pregunta_secreta_triggered();
    void on_actionUrl_list_Directory_triggered();
    void on_actionTemas_de_ayuda_triggered();
    void on_actionWindows_triggered();
    void on_actionFusion_triggered();
    void on_actionWindows_XP_triggered();
    void on_actionEncriptar_un_archivo_triggered();
    bool on_actionGuardar_triggered();
    void documentWasModified();
    /*alineamiento del texto*************/
    void on_actionCentrado_triggered();
     void on_actionIzquierda_triggered();
     void on_actionDerecha_triggered();
     void on_actionJustificado_triggered();
     /*fin alineamiento******************/
     void printPreview(QPrinter *printer);
     void on_actionPanel_de_caracteres_triggered();
     void on_actionEstilo_por_defecto_triggered();
     void on_actionHerramientas_triggered(bool checked);
     void on_actionHerramientas_buscar_triggered(bool checked);
     void on_actionHerramientas_formato_triggered(bool checked);

     void on_actionExportar_como_pdf_triggered();

     void on_actioneliminarnota_triggered();



private:
    Ui::MainWindow *ui;
    frmNuevaCuenta *nuevo;
    QLabel *usuarioLabel;
    QLabel *tituloLabel;
    QLabel *fecha;
    QLabel *usuarioIcon;
    QLineEdit *titulo;
    QDateEdit *fechaN;
    database *db;
    SimpleCrypt *crypt;
    FindDialog *m_findDialog;
    FindReplaceDialog *m_findReplaceDialog;
    QAction *qaction;
    QMap<int,QString> data;
//    QMenu *menu;
    frmContactos *contacto;
    QString curFile;
    QString currentUser;
    QString styleWin="";
    QPalette paleta;
    QFont fuente;
    QColor colorFuente;
    bool opFormato=true;
    bool opBuscar=true;
    bool opBasicas=true;
    QPoint mWPos;
    QSize mWSize;
    QSettings settings,toolBarSetting,MWState;
    int id_nota=0;
    bool state=false;

    void createContextMenu();
    void windowsLoad();
    void writeSettings();
    void readSettings();
    void windowsload();
    void setCurrentFile(const QString &fileName);
    bool maybeSave();
    bool saveFile(const QString &fileName);
    void loadFile(const QString &fileName);
    bool isValidReg();
    void filePrintPdf();
    void isValidNote();

public:
    QString getUsuario();
    void activarMenu(bool op);
    void opcionMenu(bool op=true);
    void cargarNotas();
    bool isEmptyText();
    void encryptText(quint64 clave);
    void decryptText(quint64 clave);
    void registro();
    void modoNotas(bool op=true);
    void contactos(bool op);
    void setNotePadMode(bool op);
    bool getNotePadMode();
    void setCaracter(QString c);
    void activatedPanelCaracteres(bool op=false);
    bool notePadMode=false;
};

#endif // MAINWINDOW_H
