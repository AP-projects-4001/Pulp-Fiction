#include "pvchat.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include<QJsonObject>
pvchat::pvchat(user in_Owner , user in_Addressee)
{
    Owner.set_UserName( in_Owner.get_UserName() ) ;
    Owner.set_ID( in_Owner.get_ID() ) ;
    Owner.set_PhoneNumber( in_Owner.get_PhoneNumber() ) ;
    Addressee.set_UserName( in_Addressee.get_UserName() ) ;
    Addressee.set_ID( in_Addressee.get_ID() ) ;
    Addressee.set_PhoneNumber( in_Addressee.get_PhoneNumber() ) ;
}
user pvchat::get_Addressee()
{
    return Addressee ;
}
void pvchat::set_Addressee( user in_Addressee )
{
    Addressee = in_Addressee ;
}
void pvchat::Make_NewPVChatFile( QString FileName )
{
    QFile PVChatFile(FileName) ;
    if( !PVChatFile.open(QFile::WriteOnly ) )
    {
        qDebug() << "Error in making newFile " ;//
        return ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson( PVChatFile.readAll() , &JsonParseError) ;
    QJsonObject OwnerObj  , AddresseeObj;
    OwnerObj["ID"] = Owner.get_ID() ;
    OwnerObj["UserName"] = Owner.get_UserName() ;
    OwnerObj["PhoneNumber"] = Owner.get_PhoneNumber() ;
    AddresseeObj["ID"] = Addressee.get_ID() ;
    AddresseeObj["UserName"] = Addressee.get_UserName() ;
    AddresseeObj["PhoneNumber"] = Addressee.get_PhoneNumber() ;
    QJsonObject RootObject = JsonDoc.object() ;
    RootObject["ID"] = ID ;
    RootObject["Addressee"] = AddresseeObj ;
    RootObject["Owner"] = OwnerObj ;
    RootObject["Messages"] = "" ;
    JsonDoc.setObject( RootObject ) ;
    PVChatFile.write( JsonDoc.toJson() ) ;
    PVChatFile.close() ;
}
QString pvchat::ExtractFileName( int PVChatID )
{
    QString FileName = "PVChat" + QString::number(PVChatID) + ".json" ;
    return FileName ;
}
