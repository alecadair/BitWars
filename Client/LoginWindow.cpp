#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "User.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow) {
    ui->setupUi(this);

    // Login
    QObject::connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::loginClicked);
    QObject::connect(this, &LoginWindow::loginUser, &user, &User::login);

    // Register
    QObject::connect(ui->registerButton, &QPushButton::clicked, this, &LoginWindow::registerClicked);
    QObject::connect(this, &LoginWindow::addUser, &user, &User::add);

    QObject::connect(&user, &User::updateMessage, this, &LoginWindow::setMessage);
}

LoginWindow::~LoginWindow() {
    delete ui;
}

void LoginWindow::setMessage(QString message, bool clear) {
    ui->messageLabel->setText(message);
    if (clear) {
        ui->lUsernameEdit->setText("");
        ui->lPasswordEdit->setText("");
        ui->rUsernameEdit->setText("");
        ui->rPasswordEdit->setText("");
        ui->rConfirmPasswordEdit->setText("");
        ui->rFullNameEdit->setText("");
    }
}

void LoginWindow::loginClicked() {
    QString username = ui->lUsernameEdit->text();
    QString password = ui->lPasswordEdit->text();
    if (username.isEmpty()|| password.isEmpty()) {
        ui->messageLabel->setText("Username and password are required to login.");
    }
    else if (!validText(username) || !validText(password)) {
        ui->messageLabel->setText("Fields cannot contain $'s or commas.");
    }
    else {
        emit loginUser(username.toStdString(), password.toStdString());
    }
}

void LoginWindow::registerClicked() {
    QString username = ui->rUsernameEdit->text();
    QString password = ui->rPasswordEdit->text();
    QString confirmPassword = ui->rConfirmPasswordEdit->text();
    QString fullName = ui->rFullNameEdit->text();
    if (username.isEmpty()|| password.isEmpty() || confirmPassword.isEmpty() || fullName.isEmpty()) {
        ui->messageLabel->setText("Username, password, and full name are required to register.");
    }
    else if (!validText(username) || !validText(password) || !validText(confirmPassword) || !validText(fullName)) {
        ui->messageLabel->setText("Fields cannot contain $'s' or commas.");
    }
    else if (password != confirmPassword) {
        ui->messageLabel->setText("The passwords provided do not match.");
    }
    else {
        emit addUser(username.toStdString(), password.toStdString(), fullName.toStdString());
    }
}

bool LoginWindow::validText(QString text) {
    if (text.contains("$") || text.contains(",")) {
        return false;
    }
    return true;
}
