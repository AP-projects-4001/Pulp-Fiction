#include "channel.h"
#include<QFile>
#include<QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonValue>
channel::channel(user in_Owner , QString in_ChannelName)
{
    Owner = in_Owner ;
    ChannelName = in_ChannelName ;
}
void channel::set_ChannelName(QString in_ChannelName)
{
    ChannelName = in_ChannelName ;
}
void channel::set_Members( QVector<user> in_Members )
{
    Members = in_Members ;
}
QString channel::get_ChannelName()
{
    return ChannelName ;
}
QVector<user> channel::get_Members()
{
    return Members  ;
}
QString channel::ExtractFileName( int ChannelID )
{
    QString FileName = "Channe" + QString::number(ChannelID) + ".json" ;
    return FileName ;
}
void channel::Make_NewChannelFile( QString FileName  )
{
    QFile ChannelFile(FileName) ;
    if( !ChannelFile.open(QFile::WriteOnly ) )
    {
        qDebug() << "Error in making newFile " ;//
        return ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson( ChannelFile.readAll() , &JsonParseError) ;
    QJsonObject OwnerObj ;
    OwnerObj["ID"] = Owner.get_ID() ;
    OwnerObj["UserName"] = Owner.get_UserName() ;
    OwnerObj["PhoneNumber"] = Owner.get_PhoneNumber() ;
    QJsonObject RootObject = JsonDoc.object() ;
    RootObject["ID"] = ID ;
    RootObject["Owner"] = OwnerObj ;
    RootObject["Messages"] = "" ;
    RootObject["Members"] = "" ;
    RootObject["ChannelNameChannelName"] = ChannelName ;
    JsonDoc.setObject( RootObject ) ;
    ChannelFile.write( JsonDoc.toJson() ) ;
    ChannelFile.close() ;
}
void channel::add_Member(user &in_Member , QString FileName)
{
    Members.push_back(  in_Member ) ;
    QFile ChFile( FileName ) ;
    if( !ChFile.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject NewMember ;
    NewMember.insert("ID", in_Member.get_ID() ) ;
    NewMember.insert("UserName", in_Member.get_UserName()) ;
    NewMember.insert("PhoneNumber", in_Member.get_PhoneNumber()) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(ChFile.readAll(), &JsonParseError) ;
    ChFile.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray MembersArray = RootObject.value("Members").toArray() ;
    MembersArray.append( NewMember ) ;
    RootObject.insert("Members", MembersArray );
    JsonDoc.setObject(RootObject) ;
    ChFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    ChFile.write( JsonDoc.toJson() ) ;
    ChFile.close() ;
}
channel channel::read_channel( int in_ID )
{
    user tmpOwner ;
    channel Cobj( tmpOwner , "temp" ) ;
    QString FileName  = Cobj.ExtractFileName(in_ID) ;
    QFile CFile( FileName ) ;
    if ( !CFile.open(QIODevice::ReadOnly) )
    {
        qDebug() << "File open error";
        return Cobj ;
        //////////////////////
    }
    QJsonObject ReadObj , OwnerObj;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(CFile.readAll(), &JsonParseError) ;
    CFile.close() ;
    ReadObj  = JsonDoc.object() ;
    OwnerObj = ReadObj["Owner"].toObject() ;
    tmpOwner.set_ID( OwnerObj.value("ID").toInt() ) ;
    tmpOwner.set_UserName( OwnerObj.value("UserName").toString() ) ;
    tmpOwner.set_PhoneNumber( OwnerObj.value("PhoneNumber").toString() ) ;
    QJsonArray MessagesArr = ReadObj["Messages"].toArray() ;
    QVector<QString> tmpmess ;
    for( int i=0 ; i<MessagesArr.count() ; i++)
    {
        tmpmess.push_back(MessagesArr[i].toString()) ;
    }
    QJsonArray MembersArr = ReadObj["Members"].toArray() ;
    QVector<user> userstmpvector ;
    for( int i=0 ; i< MembersArr.count() ; i++ )
    {
        user tmpuser ;
        tmpuser.set_ID( MembersArr[i].toObject().value("ID").toInt()) ;
        tmpuser.set_UserName( MembersArr[i].toObject().value("UserName").toString() ) ;
        tmpuser.set_PhoneNumber( MembersArr[i].toObject().value("PhoneNumber").toString() ) ;
        userstmpvector.push_back( tmpuser ) ;
    }
    QJsonArray AdminsArr = ReadObj["Admins"].toArray() ;
    QVector<user> userstmpvector2 ;
    for( int i=0 ; i< AdminsArr.count() ; i++ )
    {
        user tmpuser ;
        tmpuser.set_ID( AdminsArr[i].toObject().value("ID").toInt()) ;
        tmpuser.set_UserName( AdminsArr[i].toObject().value("UserName").toString() ) ;
        tmpuser.set_PhoneNumber( AdminsArr[i].toObject().value("PhoneNumber").toString() ) ;
        userstmpvector2.push_back( tmpuser ) ;
    }
    Cobj.set_Admins( userstmpvector2 ) ;
    Cobj.set_Members( userstmpvector ) ;
    Cobj.set_Messages( tmpmess ) ;
    Cobj.set_ID( ReadObj.value("ID").toInt() ) ;
    Cobj.set_Owner( tmpOwner ) ;
    Cobj.set_ChannelName( ReadObj.value("ChannelName").toString() ) ;
    return Cobj ;
}
void channel::add_Admins(user &in_Admin , QString FileName)
{
    Admins.push_back(  in_Admin ) ;
    QFile ChFile( FileName ) ;
    if( !ChFile.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
       return ;
    }
    QJsonObject NewAdmin ;
    NewAdmin.insert("ID", in_Admin.get_ID() ) ;
    NewAdmin.insert("UserName", in_Admin.get_UserName()) ;
    NewAdmin.insert("PhoneNumber", in_Admin.get_PhoneNumber()) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(ChFile.readAll(), &JsonParseError) ;
    ChFile.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray AdminsArray = RootObject.value("Admins").toArray() ;
    AdminsArray.append( NewAdmin ) ;
    RootObject.insert("Admins", AdminsArray );
    JsonDoc.setObject(RootObject) ;
    ChFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    ChFile.write( JsonDoc.toJson() ) ;
    ChFile.close() ;

}
QVector<user> channel::get_Admins()
{
    return Admins ;
}
void channel::set_Admins( QVector<user> in_Admins)
{
    Admins = in_Admins ;
}
//void channel::
