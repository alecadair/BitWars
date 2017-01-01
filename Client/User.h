#ifndef USER_H
#define USER_H

#include <QObject>
#include <string>

class User : public QObject {
   Q_OBJECT

public:
    User();

signals:
    void updateMessage(QString message, bool clear);

public slots:
    void login(std::string username, std::string password);
    void add(std::string username, std::string password, std::string fullName);
    void recordProgress();

private:
    const int RCVBUFSIZE = 32; // Size of receive buffer
    QString currentUser;
    int exists(std::string username);
    int sendCommandToServer(std::string command);
    void emitSQLOrSocketError(int result);
};

#endif // USER_H
