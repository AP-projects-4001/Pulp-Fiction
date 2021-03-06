#include "pvchat.h"
#include <QFile>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
#include<QMessageBox>
pvchat::pvchat(user in_Owner , user in_Addressee)
{
    Owner.set_UserName    ( in_Owner.get_UserName() ) ;
    Owner.set_ID          ( in_Owner.get_ID() ) ;
    Owner.set_PhoneNumber ( in_Owner.get_PhoneNumber() ) ;
    Addressee.set_UserName( in_Addressee.get_UserName() ) ;
    Addressee.set_ID      ( in_Addressee.get_ID() ) ;
    Addressee.set_PhoneNumber( in_Addressee.get_PhoneNumber() ) ;
}

pvchat::pvchat(pvchat &copyPv , user howAmI)
{
    if(howAmI.get_ID() == copyPv.get_Owner().get_ID())
    {
        Owner.set_UserName    ( copyPv.get_Owner().get_UserName() ) ;
        Owner.set_ID          ( copyPv.get_Owner().get_ID() ) ;
        Owner.set_PhoneNumber ( copyPv.get_Owner().get_PhoneNumber() ) ;
        Addressee.set_UserName( copyPv.get_Addressee().get_UserName() ) ;
        Addressee.set_ID      ( copyPv.get_Addressee().get_ID() ) ;
        Addressee.set_PhoneNumber( copyPv.get_Addressee().get_PhoneNumber() ) ;

        setName      (copyPv.get_Addressee().get_UserName());
        set_Messages (copyPv.get_Messages());
        set_Addressee(copyPv.get_Addressee());
        set_ID       (copyPv.get_ID());
    }
    else
    {
        Owner.set_UserName    ( copyPv.get_Addressee().get_UserName() ) ;
        Owner.set_ID          ( copyPv.get_Addressee().get_ID() ) ;
        Owner.set_PhoneNumber ( copyPv.get_Addressee().get_PhoneNumber() ) ;
        Addressee.set_UserName( copyPv.get_Owner().get_UserName() ) ;
        Addressee.set_ID      ( copyPv.get_Owner().get_ID() ) ;
        Addressee.set_PhoneNumber( copyPv.get_Owner().get_PhoneNumber() ) ;

        setName      (copyPv.get_Owner().get_UserName());
        set_Messages (copyPv.get_Messages());
        set_Addressee(copyPv.get_Owner());
        set_ID       (copyPv.get_ID());
    }
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
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
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
pvchat pvchat::read_PVChat( int in_ID )
{
    user tmpOwner , tmpAddressee ;
    pvchat tmppvobj( tmpOwner , tmpAddressee )  ;
    QString FileName  = tmppvobj.ExtractFileName(in_ID) ;
    QFile CFile( FileName ) ;
    if ( !CFile.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
        return tmppvobj ;
    }
    QJsonObject ReadObj , OwnerObj , AddresseeObj;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(CFile.readAll(), &JsonParseError) ;
    CFile.close() ;
    ReadObj  = JsonDoc.object() ;
    OwnerObj = ReadObj["Owner"].toObject() ;
    AddresseeObj = ReadObj["Addressee"].toObject() ;

    tmpOwner.set_ID( OwnerObj.value("ID").toInt() ) ;
    tmpOwner.set_UserName( OwnerObj.value("UserName").toString() ) ;
    tmpOwner.set_PhoneNumber( OwnerObj.value("PhoneNumber").toString() ) ;

    tmpAddressee.set_ID( AddresseeObj.value("ID").toInt() ) ;
    tmpAddressee.set_UserName( AddresseeObj["UserName"].toString() ) ;
    tmpAddressee.set_PhoneNumber( AddresseeObj.value("PhoneNumber").toString() ) ;  

    QJsonArray MessagesArr = ReadObj["Messages"].toArray() ;
    QVector<QString> tmpmess ;
    for( int i=0 ; i<MessagesArr.count() ; i++)
    {
        tmpmess.push_back(MessagesArr[i].toString()) ;
    }
    tmppvobj.set_Messages( tmpmess ) ;
    tmppvobj.set_ID( ReadObj.value("ID").toInt() ) ;
    tmppvobj.set_Addressee( tmpAddressee ) ;
    tmppvobj.set_Owner( tmpOwner ) ;
    return tmppvobj ;

}
