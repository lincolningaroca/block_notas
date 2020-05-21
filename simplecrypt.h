#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H
#include <QString>
#include <QVector>
#include <QFlags>
class SimpleCrypt
{
public:
  enum CompressionMode{
    CompressionAuto,
    CompressionAlways,
    CompressionNever
  };
  enum IntegrityProtectionMode{
    ProtectionNone,
    ProtectionCkecksum,
    ProtectionHash
  };
  enum Error{
    ErrorNoError,
    ErrorNoKeySet,
    ErrorUnKnownVersion,
    ErrorIntegrityFailed
  };
  SimpleCrypt();
  explicit SimpleCrypt(quint64 Key);
  void setKey(quint64 Key);
  bool hasKey()const{return !m_KeyParts.isEmpty();}
  void setCompressionMode(CompressionMode mode){m_compressionMode=mode;}
  CompressionMode compressionMode()const{return m_compressionMode;}
  void setIntegrityProtectionMode(IntegrityProtectionMode mode){m_protectionMode=mode;}
  IntegrityProtectionMode integrityProtectionMode()const{return m_protectionMode;}
  Error lastError()const{return m_lastError;}
  //encriptar
  QString encryptToString(const QString& plaintext);
  QString encryptToString(QByteArray plaintext);
  QByteArray encryptToByteArray(const QString& plaintext);
  QByteArray encryptToByteArray(QByteArray plaintext);
  //desemcriptar
  QString decryptToString(const QString& cyphertext);
  QByteArray decryptToByteArray(const QString& cyphertext);
  QString decryptToString(QByteArray cypher);
  QByteArray decryptToByteArray(QByteArray cypher);
  enum CryptoFlag{
    CryptoFlagNone=0,
    CryptoFlagCompression=0x01,
    CryptoFlagChecksum=0x02,
    CryptoFlagHash=0x04
  };
  Q_DECLARE_FLAGS(CryptoFlags,CryptoFlag)
private:
  void splitKey();
  quint64 m_Key;
  QVector<char> m_KeyParts;
  CompressionMode m_compressionMode;
  IntegrityProtectionMode m_protectionMode;
  Error m_lastError;
};
Q_DECLARE_OPERATORS_FOR_FLAGS(SimpleCrypt::CryptoFlags)
#endif // SIMPLECRYPT_H
