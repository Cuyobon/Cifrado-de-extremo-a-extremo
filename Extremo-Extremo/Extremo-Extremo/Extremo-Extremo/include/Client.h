#pragma once
#include "NetworkHelper.h"
#include "CryptoHelper.h"
#include "Prerequisites.h"

class
Client {
public:
  Client() = default;
  Client(const std::string& ip, int port);
  ~Client();

  /*
* @brief Establece la conexi�n con el servidor.
* @return true Si la conexi�n se ha establecido correctamente.
* @return false Si la conexi�n no se ha establecido correctamente.
*/
  bool
  Connect();

  /*
  * @brief Intercambiar claves p�blicas con el servidor
  */
  void
  ExchangeKeys();

  /*
  * @brief Cifra la clave AES con la clave p�blica del servidor.
  */
  void
  SendAESKeyEncrypted();

  /*
  * @brief Recibe un mensaje cifrado del servidor, lo descifra y lo imprime.
  */
  void
  SendEncryptedMessage(const std::string& message);

  /*
  * @brief Cifra mensajes del loop para devolverlos.
  */
  void
  SendEncryptedMessageLoop();

  /*
  * @brief Recibe mensajes del servidor en un bucle.
  */
  void
  StartReceiveLoop();

  /*
  * @brief Inicia el bucle de chat.
  */
  void
  StartChatLoop();

private:
  std::string m_ip;
  int m_port;
  SOCKET m_serverSock;
  NetworkHelper m_net;
  CryptoHelper m_crypto;
};