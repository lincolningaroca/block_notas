#ifndef DATABASE_H
#define DATABASE_H
#include <QtCore>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>
#include <QList>
#include <QSqlQueryModel>
#include "contacto.h"
#include <QImageReader>
#include <QImageWriter>
#include <QSqlError>
class database
{
public:
    database();
    QSqlDatabase db;
    //establecer conexión
    bool conexion(){
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(
                    QCoreApplication::applicationDirPath()+
                    "/sw_dabase/db2311046_sw_30061984.s3db");
        if(!db.open()){
            return false;
        }
        return true;
    }
    /*!
     * \brief logIn
     * \param usuario
     * \param clave
     * \return
     */
    QImage byteToImage(QByteArray image);
    QByteArray imageToByte(QImage image);
    bool logIn(QString usuario,QString clave);

    bool nuevaCuenta(QString dni,QString apellidos,QString nombres,
                     QString genero,QDate fecha,QString direccion,\
                     QString email,QString telefono,QString usuario,
                     QString password,QString pregunta,QString respuesta,
                     QByteArray foto);

    bool comprobarDni(QString dni);
    bool comprobarDni(QString dni,int idUsuario);
    bool comprobarEmail(QString email);
    bool comprobarEmail(QString email,int idUsuario);
    bool comprobarUsuario(QString usuario);
    bool actualizaDatos(QString apellidos, QString nombres, QString genero, QDate fecha, QString direccion,
                        QString telefono,QByteArray foto, QString dni,  QString usuario);
    QList<QVariant> datos(QString usuario);
    QString getDNI(QString usurio);
    int getIdUsuario(QString usuario);
    //notas
    bool guardarNota(int id,QString titulo,QDate fecha,QString contenido);
    bool actualizaNota(QString titulo, QDate fecha, QString contenido, int idNota, int idUsuario);
    bool actualizaClave(QString clave, QString usuario);
    QList<QVariant> datos_Notas(QString titulo);
    bool registro();
    bool registrarDatos(QString id_registro,QDate fecha,QString nombres,QString empresa,QString email,bool reg);
    QList<QVariant> datosRegistro();
    bool eliminarNota(int id);
    //funciones tabla contacto

    bool nuevoContacto(contacto c);
    bool actualizaContacto(contacto c);
    QStringList categorias();
    bool nuevaCategoria(QString categoria);
    int getIdContacto(QString str, int idUsuario);
    QList<QVariant>datosContacto(int idContacto, int idUsuario);
    bool actualizaDatosContacto(contacto c, int idContacto,int idUsuario);
    bool eliminarContacto(int idContacto, int idUsuario);
    //recuperar password
    QString pregunta(QString usuario);
    bool ResetPassword(QString password, QString usuario);
    bool comprobarRespuesta(QString respuesta, QString usuario);
    bool cambiarPreguntaSecreta(QString pregunta, QString respuesta,QString usuario);
    QString getError();

private:
    QString _errorMessage;

};

#endif // DATABASE_H
