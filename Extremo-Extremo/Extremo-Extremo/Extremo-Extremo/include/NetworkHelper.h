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
  * @param port Puerto TCP que se usará para esperar conexiones entrantes.
  * @return true si el servidor se inició correctamente.
  * @return false si ocurrió un error en el proceso de inicio.
  */
  bool
  StartServer(int port);

  /*
  * @brief Espera y acepta la conexión de un cliente entrante.
  * @return SOCKET correspondiente al cliente aceptado, o INVALID_SOCKET si hubo fallo.
  */
  SOCKET
  AcceptClient();

  // Modo Cliente
  /*
  * @brief Establece conexión con un servidor dado su IP y puerto.
  * @param ip Dirección IP del servidor.
  * @param port Puerto en el que escucha el servidor.
  * @return true si la conexión fue exitosa.
  * @return false si no se pudo conectar.
  */
  bool 
  ConnectToServer(const std::string& ip, int port);

  /*
  * @brief Envía una cadena de texto a través del socket.
  * @param socket Socket por el que se transmitirá la información.
  * @param data Texto que se desea enviar.
  * @return true si el envío se realizó sin errores.
  */
  bool
  SendData(SOCKET socket, const std::string& data);

  /*
  * @brief Envía datos binarios (por ejemplo, claves AES o RSA) a través del socket.
  * @param socket Socket por el que se transmitirá la información.
  * @param data Datos a enviar en formato binario.
  * @return true si el envío se completó correctamente.
  */
  bool
  SendData(SOCKET socket, const std::vector<unsigned char>& data);

  /*
  * @brief Recibe una cadena de texto desde el socket.
  * @param socket Socket desde el cual se recibirán los datos.
  * @return Cadena recibida o una cadena vacía si ocurre un error.
  */
  std::string
  ReceiveData(SOCKET socket);

  /*
  * @brief Recibe datos binarios desde el socket.
  * @param socket Socket desde el que se recibirán los datos.
  * @param size Número de bytes a recibir (si es 0, se leerá hasta que no haya más datos disponibles).
  * @return Vector que contiene los bytes recibidos.
  */
  std::vector<unsigned char>
  ReceiveDataBinary(SOCKET socket, int size = 0);

  /*
  * @brief Cierra el socket sin comprobar si es válido.
  * @param socket Socket que se desea cerrar.
  */
  void
  close(SOCKET socket);

  /*
  * @brief Envía la totalidad de los datos a través del socket, garantizando que no se pierdan bytes.
  * @param s Socket utilizado para el envío.
  * @param data Puntero al bloque de datos a enviar.
  * @param len Cantidad de bytes a enviar.
  * @return true si todos los bytes fueron enviados con éxito.
  * @return false si ocurrió un error durante el envío.
  */
  bool
  SendAll(SOCKET s, const unsigned char* data, int len);

  /*
  * @brief Recibe exactamente la cantidad de bytes especificada.
  * @param s Socket desde el que se recibirán los datos.
  * @param out Puntero al buffer donde se almacenarán los datos recibidos.
  * @param len Número exacto de bytes que se espera recibir.
  * @return true si se recibieron todos los bytes correctamente.
  * @return false si hubo un error durante la recepción.
  */
  bool
  ReceiveExact(SOCKET s, unsigned char* out, int len);

public:
  SOCKET m_serverSocket = -1;
private:
  bool m_initialized;
};