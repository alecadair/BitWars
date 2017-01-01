#include "Socket.h"
#include "MySQL.h"
#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const unsigned int RCVBUFSIZE = 32; // Size of receive buffer

void HandleTCPClient(TCPSocket *sock);

int main(int argc, char *argv[]) {
  try {
    // Server Socket object on port 5678
    TCPServerSocket servSock(5678);
  
    // Wait for client connection
    for (;;) {
      HandleTCPClient(servSock.accept());
    }
  } catch (SocketException &e) {
    cerr << e.what() << endl;
    exit(1);
  }
  return 0;
}

// TCP client handling function
void HandleTCPClient(TCPSocket *sock) {
  char buffer[RCVBUFSIZE] = {0}; // Initialize buffer with null
  string command = "";

  // Receive the command until '$' is reached
  while (command.back() != '$') {
    sock->recv(buffer, RCVBUFSIZE);
    command += buffer;

    // Clear the buffer
    memset(buffer, 0, RCVBUFSIZE);
  }

  // Run command and send result to the client
  MySQL mySQL;
  int resultInt = mySQL.runCommand(command);
  char result[2];
  sprintf(result, "%d", resultInt);
  sock->send(result, 2);

  delete sock;
}
