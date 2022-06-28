#include "maindatabase.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "user.h"
#include "group.h"
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
    ///////////
    QJsonArray tmpArr ;
    for( int i=0 ; i<in_user.get_ChannelsID().count() ; i++)
    {
        tmpArr.push_back( in_user.get_ChannelsID().at(i) ) ;
    }
    Newuser.insert("ChannelsID" , tmpArr ) ;
    ///////////
    QJsonArray tmpArr2 ;
    for( int i=0 ; i<in_user.get_GroupsID().count() ; i++)
    {
        tmpArr2.push_back( in_user.get_GroupsID().at(i) ) ;
    }
    Newuser.insert("GroupsID" , tmpArr2 ) ;
    /////
    QJsonArray tmpArr3 ;
    for( int i=0 ; i<in_user.get_PVchatsID().count() ; i++)
    {
        tmpArr3.push_back( in_user.get_PVchatsID().at(i) ) ;
    }
    Newuser.insert("PVchatsID" , tmpArr3 ) ;
    QJsonArray tmpArr4 ;
    for( int i=0 ; i<in_user.get_FriendsID().count() ; i++)
    {
        tmpArr4.push_back( in_user.get_FriendsID().at(i) ) ;
    }
    Newuser.insert("FriendsID" , tmpArr4 ) ;
    /////////
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
            QVector<int> tmpv ;
            QJsonArray tmparr = TempObj["PVchatsID"].toArray() ;
            for( int i=0 ; i<tmparr.size() ; i++)
            {
                tmpv.push_back( tmparr.at(i).toInt() ) ;
            }
            in_user.set_PVchatID( tmpv ) ;
            QVector<int> tmpv2 ;
            QJsonArray tmparr2 = TempObj["GroupsID"].toArray() ;
            for( int i=0 ; i<tmparr2.size() ; i++)
            {
                tmpv2.push_back( tmparr2.at(i).toInt() ) ;
            }
            in_user.set_GroupsID( tmpv2 ) ;
            QVector<int> tmpv3 ;
            QJsonArray tmparr3 = TempObj["ChannelsID"].toArray() ;
            for( int i=0 ; i<tmparr3.size() ; i++)
            {
                tmpv3.push_back( tmparr3.at(i).toInt() ) ;
            }
            in_user.set_ChannelsID( tmpv3 ) ;
            QVector<int> tmpv4 ;
            QJsonArray tmparr4 = TempObj["FriendsID"].toArray() ;
            for( int i=0 ; i<tmparr4.size() ; i++)
            {
                tmpv4.push_back( tmparr4.at(i).toInt() ) ;
            }
            in_user.set_ChannelsID( tmpv4 ) ;
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
int maindatabase::Creat_GroupID()
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
void maindatabase::Add_Group(Group in_Group)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject NewGroup ;
    NewGroup.insert( "ID" , Creat_GroupID() ) ;
    NewGroup.insert( "GroupName" , in_Group.get_GroupName() ) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray GroupArray = RootObject.value("Groups").toArray() ;
    GroupArray.append( NewGroup ) ;
    RootObject.insert("Groups", GroupArray );
    JsonDoc.setObject(RootObject) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Add_Channel( channel in_Channel )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject NewChannel ;
    NewChannel.insert( "ID" , Creat_GroupID() ) ;
    NewChannel.insert( "ChannelName" , in_Channel.get_ChannelName() ) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray ChannelArray = RootObject.value("Channels").toArray() ;
    ChannelArray.append( NewChannel ) ;
    RootObject.insert("Groups", ChannelArray );
    JsonDoc.setObject(RootObject) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Push_UserPVChatID(int in_PVChatID , user in_user )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return  ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject jobj = JsonDoc.object() ;
    QJsonArray UsersArray = jobj["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject TempObj =  UsersArray.at(i).toObject();

        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            QJsonArray Array = Newuser["PVchatsID"].toArray() ;
            Array.append( QJsonValue(in_PVChatID) ) ;
            Newuser.insert( "PVchatsID" , Array );
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
            TempObj["PVchatsID"] = Array ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Push_UserGroupID(int in_GroupID , user in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return  ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject jobj = JsonDoc.object() ;
    QJsonArray UsersArray = jobj["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject TempObj =  UsersArray.at(i).toObject();

        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            QJsonArray Array = Newuser["GroupsID"].toArray() ;
            Array.append( QJsonValue(in_GroupID) ) ;
            Newuser.insert( "GroupsID" , Array );
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
            TempObj["GroupsID"] = Array ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Push_UserChannelID(int in_ChannelID , user in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return  ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject jobj = JsonDoc.object() ;
    QJsonArray UsersArray = jobj["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject TempObj =  UsersArray.at(i).toObject();

        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            QJsonArray Array = Newuser["ChannelsID"].toArray() ;
            Array.append( QJsonValue(in_ChannelID) ) ;
            Newuser.insert( "ChannelsID" , Array );
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
            TempObj["ChannelsID"] = Array ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}

void maindatabase::Push_UserFriendID(int in_FriendID , user in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return  ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject jobj = JsonDoc.object() ;
    QJsonArray UsersArray = jobj["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject TempObj =  UsersArray.at(i).toObject();

        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["Password"].toString() == in_user.get_Password())
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            QJsonArray Array = Newuser["FriendsID"].toArray() ;
            Array.append( QJsonValue(in_FriendID) ) ;
            Newuser.insert( "FriendsID" , Array );
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
            TempObj["FriendsID"] = Array ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
/*void maindatabase::Delete_UserFriendID()
{

}*/
