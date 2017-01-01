#include "User.h"
#include "Socket.h"
#include <string>
#include <stdlib.h>

User::User() {
    currentUser = "";
}

void User::login(std::string username, std::string password) {
    int result = sendCommandToServer("LOGIN:" + username + "," + password);
    if (result == 0) {
        emit updateMessage("Unable to log in. Please check your username and password.", false);
    }
    else if (result == 1) {
        currentUser = QString::fromStdString(username);
        emit updateMessage("Successfully logged in as " + currentUser + ".", true);
    }
    else {
        emitSQLOrSocketError(result);
    }
}

void User::add(std::string username, std::string password, std::string fullName) {
    int result = exists(username);
    if (result == 0) {
        int result2 = sendCommandToServer("ADUSR:" + username + "," + password + "," + fullName);
        if (result2 == 0) {
            emit updateMessage("Sorry, we were unable to register the user.", false);
        }
        else if (result2 == 1) {
            QString user = QString::fromStdString(username);
            emit updateMessage("The user " + user + " was successfully registered.", true);
        }
        else {
            emitSQLOrSocketError(result2);
        }
    }
    else {
        if (result == 1) {
            emit updateMessage("Sorry, that username already exists.", false);
        }
        else {
            emitSQLOrSocketError(result);
        }
    }
}

void User::recordProgress() {
    // To be implemented
    // RPROG:
}

int User::exists(std::string username) {
    return sendCommandToServer("USREX:" + username);
}

// Returns 0/1 if result was false/true
// Returns 2 if there was an SQL error
// Returns 3 if there was a socket error
int User::sendCommandToServer(std::string command) {
    try {
        // Establish connection with the AWS server
        TCPSocket sock("ec2-52-37-93-85.us-west-2.compute.amazonaws.com", 5678);

        // Send the command to the server ('$' marks the end of the command)
        command += "$";
        const char* toSend = command.c_str();
        int toSendLength = strlen(toSend);
        sock.send(toSend, toSendLength);

        char buffer[RCVBUFSIZE + 1]; // Buffer for string + \0
        int bytesReceived = 0; // Bytes read on each recv()
        int totalBytesReceived = 0; // Total bytes read

        // Receive the result back from the server
        while (totalBytesReceived < 2) {
            // Receive up to the buffer size bytes from the sender
            if ((bytesReceived = (sock.recv(buffer, 2))) <= 0) {
                return 3;
            }
            totalBytesReceived += bytesReceived; // Keep tally of total bytes
            buffer[bytesReceived] = '\0'; // Terminate the string
        }
        return atoi(buffer);
    }
    catch (SocketException &e) {
        return 3;
    }
}

void User::emitSQLOrSocketError(int result) {
    if (result == 2) {
        emit updateMessage("There was an error with the socket. Please try again.", false);
    }
    else {
        emit updateMessage("There was an error with MySQL. Please try again.", false);
    }
}
