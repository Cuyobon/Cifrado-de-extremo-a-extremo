#pragma once
#include "Prerequisites.h"
#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")

class
NetworkHelper {
public:
  NetworkHelper();
  ~NetworkHelper();

  // Modo Servidor
  /*
  * @brief Inicia un socket de servidor en el puerto indicado y lo deja en modo de escucha.
  * @param port Puerto TCP que se usar� para esperar conexiones entrantes.
  * @return true si el servidor se inici� correctamente.
  * @return false si ocurri� un error en el proceso de inicio.
  */
  bool
  StartServer(int port);

  /*
  * @brief Espera y acepta la conexi�n de un cliente entrante.
  * @return SOCKET correspondiente al cliente aceptado, o INVALID_SOCKET si hubo fallo.
  */
  SOCKET
  AcceptClient();

  // Modo Cliente
  /*
  * @brief Establece conexi�n con un servidor dado su IP y puerto.
  * @param ip Direcci�n IP del servidor.
  * @param port Puerto en el que escucha el servidor.
  * @return true si la conexi�n fue exitosa.
  * @return false si no se pudo conectar.
  */
  bool 
  ConnectToServer(const std::string& ip, int port);

  /*
  * @brief Env�a una cadena de texto a trav�s del socket.
  * @param socket Socket por el que se transmitir� la informaci�n.
  * @param data Texto que se desea enviar.
  * @return true si el env�o se realiz� sin errores.
  */
  bool
  SendData(SOCKET socket, const std::string& data);

  /*
  * @brief Env�a datos binarios (por ejemplo, claves AES o RSA) a trav�s del socket.
  * @param socket Socket por el que se transmitir� la informaci�n.
  * @param data Datos a enviar en formato binario.
  * @return true si el env�o se complet� correctamente.
  */
  bool
  SendData(SOCKET socket, const std::vector<unsigned char>& data);

  /*
  * @brief Recibe una cadena de texto desde el socket.
  * @param socket Socket desde el cual se recibir�n los datos.
  * @return Cadena recibida o una cadena vac�a si ocurre un error.
  */
  std::string
  ReceiveData(SOCKET socket);

  /*
  * @brief Recibe datos binarios desde el socket.
  * @param socket Socket desde el que se recibir�n los datos.
  * @param size N�mero de bytes a recibir (si es 0, se leer� hasta que no haya m�s datos disponibles).
  * @return Vector que contiene los bytes recibidos.
  */
  std::vector<unsigned char>
  ReceiveDataBinary(SOCKET socket, int size = 0);

  /*
  * @brief Cierra el socket sin comprobar si es v�lido.
  * @param socket Socket que se desea cerrar.
  */
  void
  close(SOCKET socket);

  /*
  * @brief Env�a la totalidad de los datos a trav�s del socket, garantizando que no se pierdan bytes.
  * @param s Socket utilizado para el env�o.
  * @param data Puntero al bloque de datos a enviar.
  * @param len Cantidad de bytes a enviar.
  * @return true si todos los bytes fueron enviados con �xito.
  * @return false si ocurri� un error durante el env�o.
  */
  bool
  SendAll(SOCKET s, const unsigned char* data, int len);

  /*
  * @brief Recibe exactamente la cantidad de bytes especificada.
  * @param s Socket desde el que se recibir�n los datos.
  * @param out Puntero al buffer donde se almacenar�n los datos recibidos.
  * @param len N�mero exacto de bytes que se espera recibir.
  * @return true si se recibieron todos los bytes correctamente.
  * @return false si hubo un error durante la recepci�n.
  */
  bool
  ReceiveExact(SOCKET s, unsigned char* out, int len);

public:
  SOCKET m_serverSocket = -1;
private:
  bool m_initialized;
};