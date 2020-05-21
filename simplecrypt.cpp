#include "simplecrypt.h"
#include <QByteArray>
#include <QtDebug>
#include <QtGlobal>
#include <QDateTime>
#include <QCryptographicHash>
#include <QDataStream>

SimpleCrypt::SimpleCrypt():m_Key(0),
  m_compressionMode(CompressionAuto),
  m_protectionMode(ProtectionCkecksum),
  m_lastError(ErrorNoError)
{
  qsrand(uint(QDateTime::currentMSecsSinceEpoch()&0xFFFF));
}
SimpleCrypt::SimpleCrypt(quint64 Key):m_Key(Key),
  m_compressionMode(CompressionAuto),
  m_protectionMode(ProtectionCkecksum),
  m_lastError(ErrorNoError)
{
  qsrand(uint(QDateTime::currentMSecsSinceEpoch()&0xFFFF));
  splitKey();
}

void SimpleCrypt::setKey(quint64 Key)
{
  m_Key=Key;
  splitKey();
}

QString SimpleCrypt::encryptToString(const QString &plaintext)
{
  QByteArray plaintextArray=plaintext.toUtf8();
  QByteArray cypher=encryptToByteArray(plaintextArray);
  QString cypherString=QString::fromLatin1(cypher.toBase64());
  return cypherString;
}

QString SimpleCrypt::encryptToString(QByteArray plaintext)
{
  QByteArray cypher=encryptToByteArray(plaintext);
  QString cypherString=QString::fromLatin1(cypher.toBase64());
  return cypherString;
}

QByteArray SimpleCrypt::encryptToByteArray(const QString &plaintext)
{
  QByteArray plaintextArray=plaintext.toUtf8();
  return encryptToByteArray(plaintextArray);
}

QByteArray SimpleCrypt::encryptToByteArray(QByteArray plaintext)
{
  if(m_KeyParts.isEmpty()){
      qWarning()<<"No Key set.";
      m_lastError=ErrorNoKeySet;
      return QByteArray();
    }
  QByteArray ba=plaintext;
  CryptoFlags flags=CryptoFlagNone;
  if(m_compressionMode==CompressionAlways){
      ba=qCompress(ba,9);
      flags|=CryptoFlagCompression;
    }else if(m_compressionMode==CompressionAuto){
      QByteArray compressed=qCompress(ba,9);
      if(compressed.count()<ba.count()){
          ba=compressed;
          flags|=CryptoFlagCompression;
        }
    }
  QByteArray integrityProtection;
  if(m_protectionMode==ProtectionCkecksum){
      flags|=CryptoFlagChecksum;
      QDataStream s(&integrityProtection, QIODevice::WriteOnly);
      s<<qChecksum(ba.constData(),ba.length());
    }else if(m_protectionMode==ProtectionHash){
      flags|=CryptoFlagHash;
      QCryptographicHash hash(QCryptographicHash::Sha1);
      hash.addData(ba);
      integrityProtection+=hash.result();
    }
  char randomChar=char(qrand() & 0xFF);
  ba=randomChar+integrityProtection+ba;

  int pos(0);
  char lastChar(0);

  int cnt=ba.count();
  while(pos<cnt){
      ba[pos]=ba.at(pos)^m_KeyParts.at(pos%8)^lastChar;
      lastChar=ba.at(pos);
      ++pos;
    }
  QByteArray resultArray;
  resultArray.append(char(0x03));
  resultArray.append(char(flags));
  resultArray.append(ba);

  m_lastError=ErrorNoError;
  return resultArray;
}

QString SimpleCrypt::decryptToString(const QString &cyphertext)
{
  QByteArray cyphertextArray=QByteArray::fromBase64(cyphertext.toLatin1());
  QByteArray plaintextArray=decryptToByteArray(cyphertextArray);
  QString plaintext=QString::fromUtf8(plaintextArray,plaintextArray.size());
  return plaintext;
}

QByteArray SimpleCrypt::decryptToByteArray(const QString &cyphertext)
{
  QByteArray cyphertextArray=QByteArray::fromBase64(cyphertext.toLatin1());
  QByteArray ba=decryptToByteArray(cyphertextArray);
  return ba;
}

QString SimpleCrypt::decryptToString(QByteArray cypher)
{
  QByteArray ba=decryptToByteArray(cypher);
  QString plaintext=QString::fromUtf8(ba,ba.size());
  return plaintext;
}

QByteArray SimpleCrypt::decryptToByteArray(QByteArray cypher)
{
  if(m_KeyParts.isEmpty()){
      qWarning()<<"No Key set.";
      m_lastError=ErrorNoKeySet;
      return QByteArray();
    }
  QByteArray ba=cypher;
  if(cypher.count()<3){
      return QByteArray();
    }
  char version=ba.at(0);

  if(version!=3){
      m_lastError=ErrorUnKnownVersion;
      qWarning()<<"Invalid version or not a cyphertext.";
      return QByteArray();
    }

  CryptoFlags flags=CryptoFlags(ba.at(1));

  ba=ba.mid(2);
  int pos(0);
  int cnt(ba.count());
  char lastChar=0;

  while(pos<cnt){
      char currentChar=ba[pos];
      ba[pos]=ba.at(pos)^lastChar^m_KeyParts.at(pos%8);
      lastChar=currentChar;
      ++pos;
    }

  ba=ba.mid(1);

  bool integrityOk(true);
  if(flags.testFlag(CryptoFlagChecksum)){
      if(ba.length()<2){
          m_lastError=ErrorIntegrityFailed;
          return QByteArray();
        }
      quint16 storedChecksum;
      {
        QDataStream s(&ba,QIODevice::ReadOnly);
        s>>storedChecksum;
      }
      ba=ba.mid(2);
      quint16 checKsum=qChecksum(ba.constData(),ba.length());
      integrityOk=(checKsum==storedChecksum);
    }else if(flags.testFlag(CryptoFlagHash)){
      if(ba.length()<20){
          m_lastError=ErrorIntegrityFailed;
          return QByteArray();
        }
      QByteArray storedHash=ba.left(20);
      ba=ba.mid(20);
      QCryptographicHash hash(QCryptographicHash::Sha1);
      hash.addData(ba);
      integrityOk=(hash.result()==storedHash);
    }
  if(!integrityOk){
      m_lastError=ErrorIntegrityFailed;
      return QByteArray();
    }
  if(flags.testFlag(CryptoFlagCompression)){
      ba=qUncompress(ba);
    }
  m_lastError=ErrorNoError;
  return ba;
}
void SimpleCrypt::splitKey()
{
  m_KeyParts.clear();
  m_KeyParts.resize(8);
  for(int i=0;i<8;i++){
      quint64 part=m_Key;
      for(int j=i;j>0;j--){
          part=part>>8;
        }
      part=part&0xff;
      m_KeyParts[i]=static_cast<char>(part);
    }
}
