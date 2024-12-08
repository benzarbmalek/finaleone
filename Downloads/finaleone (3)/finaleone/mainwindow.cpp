#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMainWindow>
#include <QMessageBox>
#include <QApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include "menu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->A->setPlaceholderText("Email");
    ui->B->setPlaceholderText("Mot de Passe");
    connect(ui->login, &QPushButton::clicked, this, &MainWindow::on_pushButton_login_clicked);
    connect(ui->cancel, &QPushButton::clicked, this, &MainWindow::on_pushButton_cancel_clicked);
    ui->label_3->setTextInteractionFlags(Qt::NoTextInteraction);
    ui->label_4->setTextInteractionFlags(Qt::NoTextInteraction);



}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_login_clicked() {
    QString username = ui->A->text().trimmed();
    QString password = ui->B->text().trimmed();

    QSqlQuery query;
    query.prepare("SELECT username FROM TABLE6 WHERE username = :username AND password = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec()) {
        if (query.next()) {
            QMessageBox::information(this, "Succès", "Connexion réussie.");
            this->close();

            Menu *menu = new Menu();
            menu->setAttribute(Qt::WA_DeleteOnClose);
            menu->show();

        } else {
            QMessageBox::warning(this, "Échec", "Nom d'utilisateur ou mot de passe incorrect.");
        }
    } else {
        qDebug() << "Erreur lors de l'exécution de la requête:" << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Une erreur s'est produite lors de l'authentification.");
    }
}




void MainWindow::on_pushButton_cancel_clicked(){

    this->close();
}
