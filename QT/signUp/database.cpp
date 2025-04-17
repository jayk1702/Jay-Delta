#include "database.h"


database::database() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("users.db");
    qDebug() << "Database path:" << QSqlDatabase::database().databaseName();



    if(db.open())
    {
        qDebug() << "Connection Successfull" << db.lastError().text();
    }

    QSqlQuery query;
    if(!query.exec("CREATE TABLE IF NOT EXISTS users (username TEXT PRIMARY KEY, password TEXT)"))
    {
        qDebug() << "Error:" << query.lastError().text();
    }
    else
    {
        qDebug() << "Table Created";
    }
    qDebug() << "Database path:" << QSqlDatabase::database().databaseName();
}


bool database::userExists(const QString &username)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = ?");
    query.addBindValue(username);
    query.exec();
    return query.next();
}

bool database::insertUser(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    return query.exec();
}

bool database::verifyCredentials(const QString &username, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(password);
    query.exec();
    return query.next();
}





