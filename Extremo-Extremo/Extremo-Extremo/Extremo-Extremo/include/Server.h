#pragma once
#include "Prerequisites.h"
#include "NetworkHelper.h"
#include "CryptoHelper.h"

class
Server {
public:
  Server() = default;

  Server(int port);

  ~Server();

  /*
  * @brief Inicia el servidor y lo deja a la espera de conexiones entrantes.
  * @return true si el servidor se inici� correctamente.
  * @return false si ocurri� un error durante el arranque.
  */
  bool
  Start();

  /*
  * @brief Espera la conexi�n de un cliente.
  * Este m�todo bloquea la ejecuci�n hasta que un cliente se conecta.
  */
  void
  WaitForClient();

  /*
  * @brief Recibe un mensaje cifrado desde el cliente.
  */
  void
  ReceiveEncryptedMessage();

  /*
  * @brief Inicia el ciclo de recepci�n en un hilo independiente.
  */
  void
  StartReceiveLoop();

  /*
  * @brief Env�a mensajes cifrados al cliente en un bucle.
  */
  void
  SendEncryptedMessageLoop();

  /*
  * @brief Inicia el bucle de chat que permite enviar y recibir mensajes
  * entre el servidor y el cliente.
  */
  void
  StartChatLoop();

private:
  int m_port;
  SOCKET m_clientSock;
  NetworkHelper m_net;
  CryptoHelper m_crpto;
  std::thread m_rxThread;
  std::atomic<bool> m_running{ false };
};