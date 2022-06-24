#include "maindatabase.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "user.h"
#include "QJsonParseError"
maindatabase::maindatabase()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
    }
    Db.close();
}
void maindatabase::Add_user(user in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject Newuser ;
    Newuser.insert("ID", Creat_ID() ) ;
    Newuser.insert("UserName", in_user.get_UserName()) ;
    Newuser.insert("Password", in_user.get_Password() ) ;
    Newuser.insert("PhoneNumber", in_user.get_PhoneNumber()) ;
    Newuser.insert("EmailAddress", in_user.get_EmailAddress()) ;
    Newuser.insert("BirthDate", in_user.get_BirthDate()) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray UsersArray = RootObject.value("Users").toArray() ;
    UsersArray.append( Newuser ) ;
    RootObject.insert("Users", UsersArray );
    JsonDoc.setObject(RootObject) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
bool maindatabase::Check_username(QString in_username)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_username )
        {
            return false ;
        }
    }
    return true ;
}
bool maindatabase::Check_PhoneNumber(QString in_PhoneNumber)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["PhoneNumber"].toString() == in_PhoneNumber )
        {
            return false ;
        }
    }
    return true ;
}
bool maindatabase::Check_EmailAddress(QString in_EmailAddress)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["EmailAddress"].toString() == in_EmailAddress )
        {
            return false ;
        }
    }
    return true ;
}
bool maindatabase::Check_PVChat(user FirstUser , user SecondUser )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return false;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["PVChats"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( (TempObj["OwnerID"].toInt() == FirstUser.get_ID() && TempObj["AddresseeID"].toInt() == SecondUser.get_ID()) || (TempObj["AddresseeID"].toInt() == FirstUser.get_ID() && TempObj["OwnerID"].toInt() == SecondUser.get_ID()))
        {
            return false ;
        }
    }
    return true ;

}
bool maindatabase::Find_user( user &in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
      return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            in_user.set_UserName( TempObj["UserName"].toString() ) ;
            in_user.set_Password( TempObj["Password"].toString() ) ;
            in_user.set_ID( TempObj["ID"].toInt() ) ;
            in_user.set_EmailAddress( TempObj["EmailAddress"].toString() ) ;
            in_user.set_PhoneNumber( TempObj["PhoneNumber"].toString() ) ;
            in_user.set_BirthDate( TempObj["BirthDate"].toString() ) ;
            /*set PVchatsID
             GroupsID
             ChannelsID
             FriendsID */
            return true ;

        }
    }
    qDebug() << " not found current user" ;
    return false ;
}
int maindatabase::Creat_ID()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return 0;////
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    int TempID = JsonArray.size() + 1000 ;
    return TempID ;
}
int maindatabase::Creat_PVChatID()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return 0;////
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["PVChats"].toArray() ;
    int TempID = JsonArray.size()+1 ;
    return TempID ;
}
int maindatabase::Creat_GrouptID()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return 0;////
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Groups"].toArray() ;
    int TempID = JsonArray.size() + 1 ;
    return TempID ;
}
int maindatabase::Creat_ChannelID()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return 0;////
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Channels"].toArray() ;
    int TempID = JsonArray.size() + 1 ;
    return TempID ;
}
void maindatabase::Add_PVChat(pvchat in_PVChat )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject NewPVChat ;
    NewPVChat.insert( "ID" , Creat_PVChatID() ) ;
    NewPVChat.insert( "OwnerID" , in_PVChat.get_Owner().get_ID() ) ;
    NewPVChat.insert( "AddresseeID" , in_PVChat.get_Addressee().get_ID() ) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray PVChatArray = RootObject.value("PVChats").toArray() ;
    PVChatArray.append( NewPVChat ) ;
    RootObject.insert("PVChats", PVChatArray );
    JsonDoc.setObject(RootObject) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Add_Group(){}
void maindatabase::Add_Channel(){}
/*void maindatabase::Push_UserPVChatID()
{

}
void maindatabase::Push_UserGroupID()
{

}
void maindatabase::Push_UserChannelID()
{

}
void maindatabase::Delete_UserFriendID()
{

}
void maindatabase::Push_UserFriendID()
{

}*/
