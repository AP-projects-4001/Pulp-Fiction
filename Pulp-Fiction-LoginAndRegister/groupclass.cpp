#include "groupclass.h"
#include<QFile>
#include<QDebug>
#include <QJsonDocument>
#include <QJsonParseError>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonValue>
#include<QMessageBox>
Group::Group(user in_Owner , QString in_GroupName)
{
    Owner = in_Owner ;
    GroupName = in_GroupName ;
}

Group::Group(Group &copyGroup)
{
    Owner     = copyGroup.get_Owner() ;
    GroupName = copyGroup.get_GroupName();
    setName     (copyGroup.get_GroupName());
    set_Members (copyGroup.get_Member());
    set_Messages(copyGroup.get_Messages());
    set_ID      (copyGroup.get_ID());
}
QString Group::get_GroupName()
{
    return GroupName ;
}
void Group::set_GroupName(QString in_GroupName)
{
    GroupName = in_GroupName ;
}
void  Group::set_Members( QVector<user> in_Members )
{
    Members = in_Members ;
}
void Group::add_Member(user &in_Member , QString FileName)
{
    Members.push_back(  in_Member ) ;
    QFile GFile( FileName ) ;
    if( !GFile.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
       return ;
    }
    QJsonObject NewMember ;
    NewMember.insert("ID", in_Member.get_ID() ) ;
    NewMember.insert("UserName", in_Member.get_UserName()) ;
    NewMember.insert("PhoneNumber", in_Member.get_PhoneNumber()) ;
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(GFile.readAll(), &JsonParseError) ;
    GFile.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray MembersArray = RootObject.value("Members").toArray() ;
    MembersArray.append( NewMember ) ;
    RootObject.insert("Members", MembersArray );
    JsonDoc.setObject(RootObject) ;
    GFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    GFile.write( JsonDoc.toJson() ) ;
    GFile.close() ;
}
QVector<user> Group::get_Member()
{
    return Members ;
}
QString Group::ExtractFileName( int GroupID )
{
    QString FileName = "Group" + QString::number(GroupID) + ".json" ;
    return FileName ;
}
void Group::Make_NewGroupFile( QString FileName  )
{
    QFile GroupFile(FileName) ;
    if( !GroupFile.open(QFile::WriteOnly ) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
        return ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson( GroupFile.readAll() , &JsonParseError) ;
    QJsonObject OwnerObj ;
    OwnerObj["ID"] = Owner.get_ID() ;
    OwnerObj["UserName"] = Owner.get_UserName() ;
    OwnerObj["PhoneNumber"] = Owner.get_PhoneNumber() ;
    QJsonObject RootObject = JsonDoc.object() ;
    RootObject["ID"] = ID ;
    RootObject["Owner"] = OwnerObj ;
    RootObject["Messages"] = "" ;
    RootObject["Members"] = "" ;
    RootObject["GroupName"] = GroupName ;
    JsonDoc.setObject( RootObject ) ;
    GroupFile.write( JsonDoc.toJson() ) ;
    GroupFile.close() ;
}
Group Group::read_Group( int in_ID )
{
    user tmpOwner ;
    Group Gobj( tmpOwner , "temp" ) ;
    QString FileName  = Gobj.ExtractFileName(in_ID) ;
    QFile CFile( FileName ) ;
    if ( !CFile.open(QIODevice::ReadOnly) )
    {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","There is a problem in opening file!");
        messageBox.setFixedSize(500,200);
        return Gobj ;
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
    Gobj.set_Members( userstmpvector ) ;
    Gobj.set_Messages( tmpmess ) ;
    Gobj.set_ID( ReadObj.value("ID").toInt() ) ;
    Gobj.set_Owner( tmpOwner ) ;
    Gobj.set_GroupName( ReadObj.value("GroupName").toString() ) ;
    return Gobj ;

}
void Group::delete_Member(user &in_Member , QString FileName)
{
    for(int i=0 ; i<Members.count() ; i++ )
    {
        if( Members[i].get_ID() == in_Member.get_ID() )
        {
            Members.removeAt(i) ;
            in_Member.delete_ChannelID( ID ) ;
        }

    }
    QFile GFile( FileName ) ;
    if( !GFile.open(QIODevice::ReadOnly) )
    {
       QMessageBox messageBox;
       messageBox.critical(0,"Error","There is a problem in opening file!");
       messageBox.setFixedSize(500,200);
       return ;
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(GFile.readAll(), &JsonParseError) ;
    GFile.close() ;
    QJsonObject RootObject = JsonDoc.object() ;
    QJsonArray MembersArray = RootObject.value("Members").toArray() ;
    for(int i=0 ; i<MembersArray.count() ; i++ )
    {
        if( MembersArray[i].toObject()["ID"] == in_Member.get_ID() )
        {
            MembersArray.removeAt(i) ;
        }
    }
    RootObject.insert("Members", MembersArray );
    JsonDoc.setObject(RootObject) ;
    GFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    GFile.write( JsonDoc.toJson() ) ;
    GFile.close() ;
}
