#include "maindatabase.h"
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "user.h"
#include "groupclass.h"
#include "QJsonParseError"
#include<QMessageBox>
maindatabase::maindatabase()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
    }
    Db.close();
}
void maindatabase::Add_user(user in_user)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadWrite) )
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file");
       messageBox.setFixedSize(500,200);
       return ;
    }
    QJsonObject Newuser ;
    Newuser.insert("ID", Creat_ID() ) ;
    Newuser.insert("UserName", in_user.get_UserName()) ;
    Newuser.insert("Password", in_user.get_Password() ) ;
    Newuser.insert("PhoneNumber", in_user.get_PhoneNumber()) ;
    Newuser.insert("EmailAddress", in_user.get_EmailAddress()) ;
    Newuser.insert("BirthDate", in_user.get_BirthDate()) ;
    Newuser.insert( "Firstname" , in_user.get_firstname() ) ;
    Newuser.insert( "Lastname" , in_user.get_lastname() ) ;
    Newuser.insert( "Bio" , in_user.get_Bio() ) ;
    Newuser.insert("nameAccessibility" , in_user.getNameAccessibility() );
    Newuser.insert("phoneAccessibility" , in_user.getPhoneAccessibility() );
    Newuser.insert("photoAccessibility" , in_user.getPhotoAccessibility() );
    Newuser.insert("firstNameAccessibility" , in_user.getFirstNameAccessibility() );
    Newuser.insert("lastNameAccessibility" , in_user.getLastNameAccessibility() );
    Newuser.insert("emailAccessibility" , in_user.getEmailAccessibility() );
    Newuser.insert("BioAccessibility"  , in_user.getBioAccessibility() ) ;
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
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
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
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
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
            in_user.set_Firstname( TempObj["Firstname"].toString()) ;
            in_user.set_Lastname( TempObj["Lastname"].toString() ) ;
            in_user.set_Bio( TempObj["Bio"].toString() ) ;
            in_user.setBioAccessibility( TempObj["BioAccessibility"].toInt() ) ;
            in_user.setNameAccessibility( TempObj["nameAccessibility"].toInt() ) ;
            in_user.setPhoneAccessibility( TempObj["phoneAccessibility"].toInt() ) ;
            in_user.setPhotoAccessibility( TempObj["photoAccessibility"].toInt() ) ;
            in_user.setFirstNameAccessibility( TempObj["firstNameAccessibility"].toInt() ) ;
            in_user.setLastNameAccessibility( TempObj["lastNameAccessibility"].toInt() ) ;
            in_user.setEmailAccessibility( TempObj["emailAccessibility"].toInt() ) ;
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
            in_user.set_FriendsID( tmpv4 ) ;
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error","Not found current user!");
    messageBox.setFixedSize(500,200);
    return false ;
}
int maindatabase::Creat_ID()
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return 0;
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return 0;
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return ;
    }
    QJsonObject NewChannel ;
    NewChannel.insert( "ID" , Creat_ChannelID() ) ;
    NewChannel.insert( "ChannelName" , in_Channel.get_ChannelName() ) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray ChannelArray = RootObject.value("Channels").toArray() ;
    ChannelArray.append( NewChannel ) ;
    RootObject.insert("Channels", ChannelArray );
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
QVector<user> maindatabase::read_AllUsers()
{
    QVector<user> Usersvector ;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return  Usersvector;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray UsersArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        user tmpUser ;
        QJsonObject currUser ;
        currUser = UsersArray.at(i).toObject() ;
        tmpUser.set_UserName( currUser["UserName"].toString() ) ;
        tmpUser.set_Firstname( currUser["Firstname"].toString()) ;
        tmpUser.set_Lastname( currUser["Lastname"].toString() ) ;
        tmpUser.set_BirthDate( currUser["BirthDate"].toString() ) ;
        tmpUser.set_ID( currUser["ID"].toInt() ) ;
        tmpUser.set_Password( currUser["Password"].toString() ) ;
        tmpUser.set_EmailAddress( currUser["EmailAddress"].toString() ) ;
        tmpUser.set_PhoneNumber( currUser["PhoneNumber"].toString() ) ;
        tmpUser.set_Bio( currUser["Bio"].toString() ) ;
        ///
        tmpUser.setBioAccessibility( currUser["BioAccessibility"].toInt() ) ;
        tmpUser.setNameAccessibility( currUser["nameAccessibility"].toInt() ) ;
        tmpUser.setPhoneAccessibility( currUser["phoneAccessibility"].toInt() ) ;
        tmpUser.setPhotoAccessibility( currUser["photoAccessibility"].toInt() ) ;
        tmpUser.setFirstNameAccessibility( currUser["firstNameAccessibility"].toInt() ) ;
        tmpUser.setLastNameAccessibility( currUser["lastNameAccessibility"].toInt() ) ;
        tmpUser.setEmailAccessibility( currUser["emailAccessibility"].toInt() ) ;
        ///
        QVector<int> tmpv ;
        QJsonArray tmparr = currUser["PVchatsID"].toArray() ;
        for( int i=0 ; i<tmparr.size() ; i++)
        {
            tmpv.push_back( tmparr.at(i).toInt() ) ;
        }
        tmpUser.set_PVchatID( tmpv ) ;
        QVector<int> tmpv2 ;
        QJsonArray tmparr2 = currUser["GroupsID"].toArray() ;
        for( int i=0 ; i<tmparr2.size() ; i++)
        {
            tmpv2.push_back( tmparr2.at(i).toInt() ) ;
        }
        tmpUser.set_GroupsID( tmpv2 ) ;
        QVector<int> tmpv3 ;
        QJsonArray tmparr3 = currUser["ChannelsID"].toArray() ;
        for( int i=0 ; i<tmparr3.size() ; i++)
        {
            tmpv3.push_back( tmparr3.at(i).toInt() ) ;
        }
        tmpUser.set_ChannelsID( tmpv3 ) ;
        QVector<int> tmpv4 ;
        QJsonArray tmparr4 = currUser["FriendsID"].toArray() ;
        for( int i=0 ; i<tmparr4.size() ; i++)
        {
            tmpv4.push_back( tmparr4.at(i).toInt() ) ;
        }
        tmpUser.set_FriendsID( tmpv4 ) ;
        Usersvector.push_back( tmpUser ) ;


    }
    return Usersvector ;
}

user maindatabase::getUserdetails(int userid)
{
    user mainUser;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return  mainUser;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray UsersArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < UsersArray.size(); i++)
    {
        QJsonObject currUser ;
        currUser = UsersArray.at(i).toObject() ;
        if(currUser["ID"].toInt() == userid)
        {
            mainUser.set_UserName( currUser["UserName"].toString() ) ;
            mainUser.set_Firstname( currUser["Firstname"].toString()) ;
            mainUser.set_Lastname( currUser["Lastname"].toString() ) ;
            mainUser.set_BirthDate( currUser["BirthDate"].toString() ) ;
            mainUser.set_ID( currUser["ID"].toInt() ) ;
            mainUser.set_Password( currUser["Password"].toString() ) ;
            mainUser.set_EmailAddress( currUser["EmailAddress"].toString() ) ;
            mainUser.set_PhoneNumber( currUser["PhoneNumber"].toString() ) ;
            mainUser.set_Bio( currUser["Bio"].toString() ) ;
            ///
            mainUser.setBioAccessibility( currUser["BioAccessibility"].toInt() ) ;
            mainUser.setNameAccessibility( currUser["nameAccessibility"].toInt() ) ;
            mainUser.setPhoneAccessibility( currUser["phoneAccessibility"].toInt() ) ;
            mainUser.setPhotoAccessibility( currUser["photoAccessibility"].toInt() ) ;
            mainUser.setFirstNameAccessibility( currUser["firstNameAccessibility"].toInt() ) ;
            mainUser.setLastNameAccessibility( currUser["lastNameAccessibility"].toInt() ) ;
            mainUser.setEmailAccessibility( currUser["emailAccessibility"].toInt() ) ;
            ///
            QVector<int> tmpv ;
            QJsonArray tmparr = currUser["PVchatsID"].toArray() ;
            for( int i=0 ; i<tmparr.size() ; i++)
            {
                tmpv.push_back( tmparr.at(i).toInt() ) ;
            }
            mainUser.set_PVchatID( tmpv ) ;
            QVector<int> tmpv2 ;
            QJsonArray tmparr2 = currUser["GroupsID"].toArray() ;
            for( int i=0 ; i<tmparr2.size() ; i++)
            {
                tmpv2.push_back( tmparr2.at(i).toInt() ) ;
            }
            mainUser.set_GroupsID( tmpv2 ) ;
            QVector<int> tmpv3 ;
            QJsonArray tmparr3 = currUser["ChannelsID"].toArray() ;
            for( int i=0 ; i<tmparr3.size() ; i++)
            {
                tmpv3.push_back( tmparr3.at(i).toInt() ) ;
            }
            mainUser.set_ChannelsID( tmpv3 ) ;
            QVector<int> tmpv4 ;
            QJsonArray tmparr4 = currUser["FriendsID"].toArray() ;
            for( int i=0 ; i<tmparr4.size() ; i++)
            {
                tmpv4.push_back( tmparr4.at(i).toInt() ) ;
            }
            mainUser.set_FriendsID( tmpv4 ) ;

            break;
        }
    }
    return mainUser;
}
void maindatabase::Delete_UserFriendID(int in_FriendID , user &in_user)
{
    in_user.delete_FriendID(in_FriendID) ;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
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
            for( int i=0 ; i<Array.count() ; i++ )
            {
                if( in_FriendID == Array.at(i).toInt() )
                {
                    Array.removeAt(i) ;
                }
            }
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
void maindatabase::Delete_UserChannelID(int in_ChannelID , user &in_user )
{
    in_user.delete_FriendID(in_ChannelID) ;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
            for( int i=0 ; i<Array.count() ; i++ )
            {
                if( in_ChannelID == Array.at(i).toInt() )
                {
                    Array.removeAt(i) ;
                }
            }
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
void maindatabase::Delete_UserPVChatID(int in_PVChatID , user in_user )
{
    in_user.delete_PVchatID(in_PVChatID) ;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
            QJsonArray Array = Newuser["PVChatsID"].toArray() ;
            for( int i=0 ; i<Array.count() ; i++ )
            {
                if( in_PVChatID == Array.at(i).toInt() )
                {
                    Array.removeAt(i) ;
                }
            }
            Newuser.insert( "PVChatsID" , Array );
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
            TempObj["PVChatsID"] = Array ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
void maindatabase::Delete_UserGroupID(int in_GroupID , user in_user)
{
    in_user.delete_FriendID(in_GroupID) ;
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
            for( int i=0 ; i<Array.count() ; i++ )
            {
                if( in_GroupID == Array.at(i).toInt() )
                {
                    Array.removeAt(i) ;
                }
            }
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
void maindatabase::Modify_UserDetails( user in_user )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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

        if( in_user.get_ID() == TempObj["ID"].toInt() )
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            Newuser["BirthDate"] = in_user.get_BirthDate() ;
            Newuser["EmailAddress"] = in_user.get_EmailAddress() ;
            Newuser["Password"] = in_user.get_Password() ;
            Newuser["PhoneNumber"] = in_user.get_PhoneNumber() ;
            Newuser["Firstname"] = in_user.get_firstname() ;
            Newuser["Lastname"] = in_user.get_lastname() ;
            Newuser["UserName"] = in_user.get_UserName() ;
            Newuser["Bio"] = in_user.get_Bio() ;
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
bool maindatabase::userpasswordForforgot(user in_user, QString &pass)
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
      return false ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(Db.readAll(), &JsonParseError) ;
    Db.close() ;
    QJsonArray JsonArray = JsonDoc.object()["Users"].toArray() ;
    for (int i=0; i < JsonArray.size(); i++)
    {
        QJsonObject TempObj =  JsonArray.at(i).toObject();
        if( TempObj["UserName"].toString() == in_user.get_UserName() && TempObj["EmailAddress"].toString() == in_user.get_EmailAddress())
        {
            pass = TempObj["Password"].toString();
            return true ;

        }
    }
    QMessageBox messageBox;
    messageBox.critical(0,"Error"," Not found current user");
    messageBox.setFixedSize(500,200);
    return false ;

}
void maindatabase::Modify_UserAAccessibility( user in_user )
{
    QFile Db( "MainDatabase.json" ) ;
    if( !Db.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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

        if( in_user.get_ID() == TempObj["ID"].toInt() )
        {
            QJsonObject Newuser ;
            Newuser = UsersArray.at(i).toObject() ;
            Newuser["nameAccessibility"] = in_user.getNameAccessibility() ;
            Newuser["phoneAccessibility"] = in_user.getPhoneAccessibility() ;
            Newuser["photoAccessibility"] = in_user.getPhotoAccessibility() ;
            Newuser["firstNameAccessibility"] = in_user.getFirstNameAccessibility() ;
            Newuser["lastNameAccessibility"] = in_user.getLastNameAccessibility() ;
            Newuser["emailAccessibility"] = in_user.getEmailAccessibility() ;
            Newuser["BioAccessibility"] = in_user.getBioAccessibility() ;
            UsersArray.removeAt(i) ;
            UsersArray.insert(i , Newuser ) ;
        }
    }
    jobj.insert( "Users" , UsersArray ) ;
    JsonDoc.setObject(jobj) ;
    Db.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    Db.write( JsonDoc.toJson() ) ;
    Db.close() ;
}
