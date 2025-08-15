#pragma once
#include "Prerequisites.h"
#include "openssl/rsa.h"
#include "openssl/aes.h"

class
CryptoHelper {
public:
  CryptoHelper();
  ~CryptoHelper();

  // RSA
  /*
  * @brief Genera un nuevo par de llaves RSA de 2048 bits.
  */
  void
  GenerateRSAKeys();

  /*
  * @brief Devuelve la clave pública en formato PEM como un string.
  */
  std::string
  GetPublicKeyString() const;

  /*
  * @brief Carga la clave pública de un tercero a partir de una cadena en formato PEM.
  * @param pemkey Cadena que contiene la clave pública en formato PEM.
  */
  void
  LoadPeerPublicKey(const std::string& pemkey);

  // AES
  /*
  * @brief Genera una clave AES-256 (32 bytes aleatorios).
  */
  void
  GenerateAESKey();

  /*
  * @brief Cifra la clave AES usando la clave pública del tercero mediante RSA.
  * @return Clave AES cifrada como un vector de bytes.
  */
  std::vector<unsigned char>
  EncryptAESKeyWithPeer();

  /*
  * @brief Descifra la clave AES enviada por el cliente.
  * @param encryptedikey Vector con la clave AES cifrada recibida.
  */
  void
  DecryptAESKey(const std::vector<unsigned char>& encryptedikey);

  /*
  * @brief Cifra un mensaje usando AES-256.
  * @param plaintext Texto plano que se desea cifrar.
  * @param outIV Vector donde se almacenará el IV (vector de inicialización) usado en el cifrado.
  * @return Texto cifrado como vector de bytes.
  */
  std::vector<unsigned char>
  AESEncrypt(const std::string& plaintext, std::vector<unsigned char>& outIV);

  /*
  * @brief Descifra un mensaje cifrado con AES-256 en modo CBC.
  * @param ciphertext Vector de bytes con el texto cifrado.
  * @param iv Vector con el IV utilizado durante el cifrado.
  * @return Texto original en formato de cadena.
  */
  std::string
  AESDecrypt(const std::vector<unsigned char>& ciphertext,
             const std::vector<unsigned char>& iv);

private:
  RSA* rsaKeyPair;
  RSA* peerPublicKey;
  unsigned char aesKey[32];
};