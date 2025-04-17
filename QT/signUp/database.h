#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql/QSql>
#include <QtSql/QSqlDatabase>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

class database
{
public:

    database();
    // void createTable();

    bool userExists(const QString &username);
    bool insertUser(const QString &username, const QString &password);
    bool verifyCredentials(const QString &username, const QString &password);

private:
    QSqlDatabase db;
};


#endif // DATABASE_H
