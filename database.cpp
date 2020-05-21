#include "database.h"

database::database(){}
/*!
 * \brief database::logIn
 * \param usuario
 * \param clave
 * \return
 */
QImage database::byteToImage(QByteArray image)
{
  QBuffer buffer(&image);
  buffer.open(QIODevice::ReadOnly);
  QImageReader reader(&buffer,"PNG");
  return reader.read();
}

QByteArray database::imageToByte(QImage image)
{
  QBuffer buffer;
  buffer.open(QIODevice::WriteOnly);
  QImageWriter writer(&buffer,"PNG");
  writer.write(image);
  return buffer.data();
}
bool database::logIn(QString usuario, QString clave){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM usuarios WHERE usuario=? AND clave=?");
  query.addBindValue(usuario);
  QCryptographicHash hash(QCryptographicHash::Sha224);
  QByteArray text(clave.toUtf8());
  hash.addData(text);
  query.addBindValue(hash.result().toHex());
  if(query.exec()){
      query.next();
      if(query.value(0)==1){
          return true;
        }

    }
  return false;
}
/*!
  crea una nueva cuenta en la base de datos
 * \brief database::nuevaCuenta
 * \param dni
 * \param apellidos
 * \param nombres
 * \param genero
 * \param fecha
 * \param direccion
 * \param email
 * \param telefono
 * \param usuario
 * \param password
 * \param pregunta
 * \param respuesta
 * \param foto
 * \return
 */
bool database::nuevaCuenta(QString dni, QString apellidos, QString nombres, QString genero,
                           QDate fecha, QString direccion, QString email, QString telefono,
                           QString usuario, QString password, QString pregunta, QString respuesta,
                           QByteArray foto){
  conexion();
  QSqlQuery query;
  query.prepare("INSERT INTO usuarios(dni,apellidos,nombres,genero,nacimiento,direccion,email,\
                telefono,usuario,clave,pregunta,respuesta,foto) VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?)");
      query.addBindValue(dni);
  query.addBindValue(apellidos);
  query.addBindValue(nombres);
  query.addBindValue(genero);
  query.addBindValue(fecha);
  query.addBindValue(direccion);
  query.addBindValue(email);
  query.addBindValue(telefono);
  query.addBindValue(usuario);
  QCryptographicHash hash(QCryptographicHash::Sha224);
  QByteArray text(password.toUtf8());
  hash.addData(text);
  query.addBindValue(hash.result().toHex());
  query.addBindValue(pregunta);
  //respuesta encriptada
  QCryptographicHash hash1(QCryptographicHash::Sha224);
  QByteArray text1(respuesta.toUtf8());
  hash1.addData(text1);
  query.addBindValue(hash1.result().toHex());
  query.addBindValue(foto);
  return query.exec();
}
/**
 * @brief database::comprobarDni
 * @param dni
 * @return
 */
bool database::comprobarDni(QString dni){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM usuarios WHERE dni=?");
  query.addBindValue(dni);
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;
}


bool database::comprobarDni(QString dni, int idUsuario){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM contactos WHERE cdni=? and id_usuario=?");
  query.addBindValue(dni);
  query.addBindValue(idUsuario);
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;
}


bool database::comprobarEmail(QString email){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM usuarios WHERE email=?");
  query.addBindValue(email);
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;
}

bool database::comprobarEmail(QString email, int idUsuario){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM contactos WHERE cemail=? and id_usuario=?");
  query.addBindValue(email);
  query.addBindValue(idUsuario);
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;

}

bool database::comprobarUsuario(QString usuario){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM usuarios WHERE usuario=?");
  query.addBindValue(usuario);
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;
}

bool database::actualizaDatos(QString apellidos, QString nombres, QString genero,
                              QDate fecha, QString direccion, QString telefono,
                              QByteArray foto,QString dni,QString usuario){
  conexion();
  QSqlQuery query;
  query.prepare("UPDATE usuarios SET apellidos=?, nombres=?, genero=?, nacimiento=?,\
                 direccion=?, telefono=?, foto=? where dni=? AND usuario=?");
  query.addBindValue(apellidos);
  query.addBindValue(nombres);
  query.addBindValue(genero);
  query.addBindValue(fecha);
  query.addBindValue(direccion);
  query.addBindValue(telefono);
  query.addBindValue(foto);
  query.addBindValue(dni);
  query.addBindValue(usuario);

  if(!query.exec()){
      _errorMessage=query.lastError().text();
      return false;
    }
  return true;
}

QList<QVariant> database::datos(QString usuario){
  QList<QVariant> datosUsuario;

  conexion();
  QSqlQuery query;
  query.prepare("SELECT dni,apellidos,nombres,genero,nacimiento,direccion,email,telefono,\
                usuario,clave,foto FROM usuarios WHERE usuario=?");
                                                                query.addBindValue(usuario);
      if(query.exec()){
    while(query.next()){
        datosUsuario.append(query.value(0));
        datosUsuario.append(query.value(1));
        datosUsuario.append(query.value(2));
        datosUsuario.append(query.value(3));
        datosUsuario.append(query.value(4));
        datosUsuario.append(query.value(5));
        datosUsuario.append(query.value(6));
        datosUsuario.append(query.value(7));
        datosUsuario.append(query.value(8));
        datosUsuario.append(query.value(9));
        datosUsuario.append(query.value(10).toByteArray());
      }
  }

  return datosUsuario;
}

QString database::getDNI(QString usurio){
  QString dni;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT dni FROM usuarios WHERE usuario=?");
  query.addBindValue(usurio);
  if(query.exec()){
      while(query.next()){
          dni=query.value(0).toString();
        }
    }
  return dni;
}

int database::getIdUsuario(QString usuario){
  int idU=0;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT id_usuario FROM usuarios WHERE usuario=?");
  query.addBindValue(usuario);
  if(query.exec()){
      while(query.next()){
          idU=query.value(0).toInt();
        }
    }
  return idU;
}

bool database::guardarNota(int id, QString titulo, QDate fecha, QString contenido){
  conexion();
  QSqlQuery query;
  query.prepare("INSERT INTO notas (id_usuario,titulo,fecha,contenido) VALUES(?,?,?,?)");
  query.addBindValue(id);
  query.addBindValue(titulo);
  query.addBindValue(fecha);
  query.addBindValue(contenido);
  if(query.exec()){
      return true;
    }
  return false;
}

bool database::actualizaNota(QString titulo, QDate fecha, QString contenido, int idNota,int idUsuario){
  conexion();
  QSqlQuery query;
  query.prepare("UPDATE notas SET titulo=?, fecha=?, contenido=? WHERE id_nota=? AND id_usuario=?");
  query.addBindValue(titulo);
  query.addBindValue(fecha);
  query.addBindValue(contenido);
  query.addBindValue(idNota);
  query.addBindValue(idUsuario);
  return query.exec();
}

bool database::actualizaClave(QString clave,QString usuario){
  conexion();
  QSqlQuery query;
  query.prepare("UPDATE usuarios SET clave=? WHERE usuario=?");
  QCryptographicHash hash(QCryptographicHash::Sha224);
  QByteArray text(clave.toUtf8());
  hash.addData(text);
  query.addBindValue(hash.result().toHex());
  query.addBindValue(usuario);

  if(!query.exec()){
      _errorMessage=query.lastError().text();
      return false;
    }
  return true;
}

QList<QVariant> database::datos_Notas(QString titulo){
  QList<QVariant> Notas;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT id_nota,titulo,fecha,contenido FROM notas WHERE titulo=?");
  query.addBindValue(titulo);
  if(query.exec()){
      while(query.next()){
          Notas.append(query.value(0));
          Notas.append(query.value(1));
          Notas.append(query.value(2));
          Notas.append(query.value(3));
        }
    }
  return Notas;
}

bool database::registro(){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*) FROM registro");
  if(query.exec()){
      while(query.next()){
          if(query.value(0)==1){
              return true;
            }
        }
    }
  return false;
}

bool database::registrarDatos(QString id_registro, QDate fecha, QString nombres,\
                              QString empresa, QString email, bool reg){
  conexion();
  QSqlQuery query;
  query.prepare("INSERT INTO registro (id_registro,fecha,nombres,empresa,email,reg)VALUES(?,?,?,?,?,?)");
  QCryptographicHash hash(QCryptographicHash::Md5);
  QByteArray text(id_registro.toUtf8());
  hash.addData(text);
  //query.addBindValue(hash.result().toHex());
  query.addBindValue(hash.result().toHex());
  query.addBindValue(fecha);
  query.addBindValue(nombres);
  query.addBindValue(empresa);
  query.addBindValue(email);
  query.addBindValue(reg);
  if(query.exec()){
      return true;
    }
  return false;

}

QList<QVariant> database::datosRegistro(){
  QList<QVariant> Notas;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT id_registro,fecha,nombres,empresa,email FROM registro");
  if(query.exec()){
      while(query.next()){
          Notas.append(query.value(0));
          Notas.append(query.value(1));
          Notas.append(query.value(2));
          Notas.append(query.value(3));
          Notas.append(query.value(4));

        }
    }
  return Notas;
}

bool database::eliminarNota(int id){
  conexion();
  QSqlQuery query;
  query.prepare("DELETE FROM notas WHERE id_nota=?");
  query.addBindValue(id);
  if(!query.exec()){
      _errorMessage=query.lastError().text();
      return false;
    }
  return true;
}

bool database::nuevoContacto(contacto c){
  conexion();
  QSqlQuery query;
  query.prepare("INSERT INTO contactos(id_usuario,cdni,capellidos,cnombres,cnacimiento,cgenero,ces_civil,cdireccion,\
                cdepartamento,cprovincia,cdistrito,cnum_telefono,ctipo_num,cemail,ccat_contacto,ccomentario,cfoto)\
      VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)");
      query.addBindValue(c.getIdUsuario1());
  query.addBindValue(c.getDni());
  query.addBindValue(c.getApellidos());
  query.addBindValue(c.getNombres());
  query.addBindValue(c.getNacimiento());
  query.addBindValue(c.getGenero());
  query.addBindValue(c.getEstadoCivil());
  query.addBindValue(c.getDireccion());
  query.addBindValue(c.getDepartamento());
  query.addBindValue(c.getProvincia());
  query.addBindValue(c.getDistrito());
  query.addBindValue(c.getNum_telefono());
  query.addBindValue(c.getTipo_num());
  query.addBindValue(c.getEmail());
  query.addBindValue(c.getCat_contacto());
  query.addBindValue(c.getComentario());
  query.addBindValue(c.getFoto());
  return query.exec();
}

QStringList database::categorias(){
  QStringList listaCategorias;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT categoria FROM categorias");
  query.exec();
  while(query.next()){
      listaCategorias.append(query.value(0).toString());
    }
  return listaCategorias;
}

bool database::nuevaCategoria(QString categoria){
  conexion();
  QSqlQuery query;
  query.prepare("INSERT INTO categorias(categoria) VALUES(?)");
  query.addBindValue(categoria);
  return query.exec();


}

int database::getIdContacto(QString str, int idUsuario){
  conexion();
  int id=-1;
  QSqlQuery query;
  query.prepare("select id_contacto from contactos where capellidos=? and id_usuario=?");
  query.addBindValue(str);
  query.addBindValue(idUsuario);
  //query.addBindValue(nombres);
  if(!query.exec()){
      _errorMessage=query.lastError().text();
      return id;
    }
  query.next();
  id=query.value(0).toInt();
  return id;
}

QList<QVariant> database::datosContacto(int idContacto,int idUsuario){
  QList<QVariant>  datos;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT * FROM contactos WHERE id_contacto=? and id_usuario=?");
  query.addBindValue(idContacto);
  query.addBindValue(idUsuario);
  query.exec();
  while(query.next()){
      datos.append(query.value(0));
      datos.append(query.value(1));
      datos.append(query.value(2));
      datos.append(query.value(3));
      datos.append(query.value(4));
      datos.append(query.value(5));
      datos.append(query.value(6));
      datos.append(query.value(7));
      datos.append(query.value(8));
      datos.append(query.value(9));
      datos.append(query.value(10));
      datos.append(query.value(11));
      datos.append(query.value(12));
      datos.append(query.value(13));
      datos.append(query.value(14));
      datos.append(query.value(15));
      datos.append(query.value(16));
      datos.append(query.value(17));

    }
  return datos;

}

bool database::actualizaDatosContacto(contacto c, int idContacto, int idUsuario){
  conexion();
  QSqlQuery query;
  query.prepare("UPDATE contactos SET capellidos=?, cnombres=?, cnacimiento=?, cgenero=?,\
                ces_civil=?, cdireccion=?, cdepartamento=?, cprovincia=?, cdistrito=?,\
                cnum_telefono=?, ctipo_num=?, cemail=?, ccat_contacto=?, ccomentario=?, cfoto=?\
        WHERE id_contacto=? and id_usuario=?");
                                            query.addBindValue(c.getApellidos());
      query.addBindValue(c.getNombres());
  query.addBindValue(c.getNacimiento());
  query.addBindValue(c.getGenero());
  query.addBindValue(c.getEstadoCivil());
  query.addBindValue(c.getDireccion());
  query.addBindValue(c.getDepartamento());
  query.addBindValue(c.getProvincia());
  query.addBindValue(c.getDistrito());
  query.addBindValue(c.getNum_telefono());
  query.addBindValue(c.getTipo_num());
  query.addBindValue(c.getEmail());
  query.addBindValue(c.getCat_contacto());
  query.addBindValue(c.getComentario());
  query.addBindValue(c.getFoto());

  query.addBindValue(idContacto);
  query.addBindValue(idUsuario);
  return query.exec();

}

bool database::eliminarContacto(int idContacto, int idUsuario){
  conexion();
  QSqlQuery query;
  query.prepare("DELETE FROM contactos WHERE id_contacto=? AND id_usuario=?");
  query.addBindValue(idContacto);
  query.addBindValue(idUsuario);
  return query.exec();

}

QString database::pregunta(QString usuario){
  QString pregunta;
  conexion();
  QSqlQuery query;
  query.prepare("SELECT pregunta FROM usuarios WHERE usuario=?");
  query.addBindValue(usuario);
  query.exec();
  while(query.next()){
      pregunta=query.value(0).toString();
    }
  return pregunta;
}

bool database::ResetPassword(QString password,QString usuario){

  conexion();
  QSqlQuery query;
  query.prepare("UPDATE usuarios SET clave=? WHERE usuario=?");
  QCryptographicHash hash(QCryptographicHash::Sha224);
  QByteArray text(password.toUtf8());
  hash.addData(text);
  query.addBindValue(hash.result().toHex());
  query.addBindValue(usuario);
  return query.exec();

}

bool database::comprobarRespuesta(QString respuesta,QString usuario){
  conexion();
  QSqlQuery query;
  query.prepare("SELECT COUNT(*)  FROM usuarios WHERE respuesta=? AND usuario=?");
  QCryptographicHash hash(QCryptographicHash::Sha224);
  QByteArray text(respuesta.toUtf8());
  hash.addData(text);
  query.addBindValue(hash.result().toHex());
  query.addBindValue(usuario);
  query.exec();
  while(query.next()){
      if(query.value(0)==1){
          return true;
        }
    }
  return false;
}

bool database::cambiarPreguntaSecreta(QString pregunta, QString respuesta, QString usuario)
{
  conexion();
  QSqlQuery query;
  query.prepare("UPDATE usuarios SET pregunta=?, respuesta=? WHERE usuario=?");
  query.addBindValue(pregunta);
  QCryptographicHash hash1(QCryptographicHash::Sha224);
  QByteArray text1(respuesta.toUtf8());
  hash1.addData(text1);
  query.addBindValue(hash1.result().toHex());
  query.addBindValue(usuario);
  if(!query.exec()){
      _errorMessage=query.lastError().text();
      return false;
    }
  return true;
}

QString database::getError()
{
  return _errorMessage;
}
