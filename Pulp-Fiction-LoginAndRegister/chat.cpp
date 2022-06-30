#include "chat.h"
#include<QDebug>
#include<QFile>
#include<QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
chat::chat()
{

}
int chat::get_ID()
{
    return ID ;
}
user chat::get_Owner()
{
    return Owner ;
}
QVector<QString> chat::get_Messages()
{
    return Messages ;
}
void chat::set_Messages(QVector<QString> in_Messages )
{
    Messages = in_Messages ;
}
void chat::set_ID(int in_ID )
{
    ID = in_ID ;
}
void chat::set_Owner(user in_Owner )
{
    Owner = in_Owner ;
}
void chat::add_Message(QString in_Message , QString FileName)
{
    QFile CFile( FileName ) ;
    if( !CFile.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonParseError JsonParsError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson( CFile.readAll() , &JsonParsError ) ;
    CFile.close() ;
    QJsonObject ChatObj = JsonDoc.object() ;
    QJsonArray MessArray = ChatObj["Messages"].toArray() ;
    MessArray.append( QJsonValue(in_Message)) ;
    ChatObj.insert( "Messages" , MessArray ) ;
    JsonDoc.setObject(ChatObj) ;
    CFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate) ;
    CFile.write( JsonDoc.toJson() ) ;
    CFile.close() ;
}
