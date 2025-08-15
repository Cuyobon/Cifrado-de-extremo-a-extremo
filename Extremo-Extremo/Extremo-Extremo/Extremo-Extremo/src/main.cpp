#include "Prerequisites.h"
#include "Server.h"
#include "Client.h"

static void
runServer(int port) {
  Server s(port);
  if (!s.Start()) {
    std::cerr << "[Main] No se pudo iniciar el server.\n";
    return;
  }
  s.WaitForClient(); // Intercambio de claves
  s.StartChatLoop(); // Envio y recepcion de datos
}

static void
runClient(const std::string& ip, int port) {
  Client c(ip, port);
  if (!c.Connect()) { std::cerr << "[Main] No se pudo conectar.\n"; return; }

  c.ExchangeKeys();
  c.SendAESKeyEncrypted();
  c.StartChatLoop();
}

int
main(int argc, char** argv) {
  std::string mode, ip;
  int port = 0;

  if (argc >= 2) {
    mode = argv[1];

    if (mode == "server") {
      port = (argc >= 3) ? std::stoi(argv[2]) : 12345;
    }
    else if (mode == "cliente") {
      if (argc < 4) {
        std::cerr << "Uso: Cliente E2EE <ip> <port>\n";
        return 1;
      }
      ip = argv[2];
      port = std::stoi(argv[3]);
    }
    else {
      std::cerr << "Modo desconocido. Usa: server | cliente\n";
      return 1;
    }
  }
  else {
    std::cout << "Modo (server/cliente): ";
    std::cin >> mode;

    if (mode == "server") {
      std::cout << "Puerto: ";
      std::cin >> port;
    }
    else if (mode == "cliente") {
      std::cout << "IP: ";
      std::cin >> ip;
      std::cout << "Puerto: ";
      std::cin >> port;
    }
    else {
      std::cerr << "Modo desconocido. Usa: servidor | cliente\n";
      return 1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }

  if (mode == "server") runServer(port);
  else runClient(ip, port);

  return 0;
}