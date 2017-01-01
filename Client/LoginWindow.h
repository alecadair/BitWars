#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include "User.h"
#include <QMainWindow>
#include <string>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

signals:
    void loginUser(std::string username, std::string password);
    void addUser(std::string username, std::string password, std::string fullName);

public slots:
    void setMessage(QString message, bool clear);

private slots:
    void loginClicked();
    void registerClicked();

private:
    Ui::LoginWindow *ui;
    User user;
    bool validText(QString text);
};

#endif // LOGINWINDOW_H
