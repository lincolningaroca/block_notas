#ifndef CONTACTO_H
#define CONTACTO_H
#include <QString>
#include <QDate>
class contacto
{
    //variables mienbro.
private:
    int     _id_usuario;
    QString _dni;
    QString _apellidos;
    QString _nombres;
    QDate   _nacimiento;
    QString _genero;
    QString _es_civil;
    QString _direccion;
    QString _departamento;
    QString _provincia;
    QString _distrito;
    QString _num_telefono;
    QString _tipo_num;
    QString _email;
    QString _cat_contacto;
    QString _comentario;
    QString _foto;


public:
    contacto();
public:
    //get and set***
    //************************//
    //*****id del usuario
    int getIdUsuario1(){return _id_usuario;}
    void setIdUsuario1( int idUsuario){_id_usuario=idUsuario;}
    //*****dni
    QString getDni()const{return _dni;}
    void setDni(const QString dni){_dni=dni;}
    //*****apellidos
    QString getApellidos()const{return _apellidos;}
    void setApellidos(const QString apellidos){_apellidos=apellidos;}
    //*****nombres
    QString getNombres()const{return _nombres;}
    void setNombres(const QString nombres){_nombres=nombres;}
    //*****fecha de nacimiento
    QDate getNacimiento(){return _nacimiento;}
    void setNacimiento(QDate nacimiento){_nacimiento=nacimiento;}
    //*****genero
    QString getGenero()const{return _genero;}
    void setGenero(const QString genero){_genero=genero;}
    //*****estado civil
    QString getEstadoCivil()const{return _es_civil;}
    void setEstadoCivil(const QString es_civil){_es_civil=es_civil;}
    //*****dirección
    QString getDireccion()const{return _direccion;}
    void setDireccion(const QString direccion){_direccion=direccion;}
    //*****departamento
    QString getDepartamento()const{return _departamento;}
    void setDepartamento(const QString departamento){_departamento=departamento;}
    //*****provincia
    QString getProvincia()const{return _provincia;}
    void setProvincia(const QString provincia){_provincia=provincia;}
    //*****distrito
    QString getDistrito()const{return _distrito;}
    void setDistrito(const QString distrito){_distrito=distrito;}
    //*****número telefónico
    QString getNum_telefono()const{return _num_telefono;}
    void setNum_telefono(const QString num_telefono){_num_telefono=num_telefono;}
    //*****tipo de número telefónico
    QString getTipo_num()const{return _tipo_num;}
    void setTipo_num(const QString tipo_num){_tipo_num=tipo_num;}
    //*****email
    QString getEmail()const{return _email;}
    void setEmail(const QString email){_email=email;}
    //*****categoría del contacto
    QString getCat_contacto()const{return _cat_contacto;}
    void setCat_contacto(const QString cat_contacto){_cat_contacto=cat_contacto;}
    //*****comentario
    QString getComentario()const{return _comentario;}
    void setComentario(const QString comentario){_comentario=comentario;}
    //*****foto
    QString getFoto(){return _foto;}
    void setFoto(QString foto){_foto=foto;}


};

#endif // CONTACTO_H
