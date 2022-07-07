#include "user.h"
user::user()
{
    nameAccessibility = 0 ;
    phoneAccessibility = 0 ;
    photoAccessibility = 0 ;
    firstNameAccessibility = 0 ;
    lastNameAccessibility = 0 ;
    emailAccessibility = 0 ;
    BioAccessibility = 0 ;
}
void user::set_ID(int in_ID)
{
    ID = in_ID ;
}
void user::set_UserName(QString in_UserName)
{
    UserName = in_UserName ;
}
void user::set_Password(QString in_Pass)
{
    Password = in_Pass ;
}
void user::set_Firstname(QString in_firstname)
{
    Firstname = in_firstname;
}
void user::set_Lastname(QString in_lastname)
{
    Lastname = in_lastname;
}
void user::set_BirthDate(QString in_BirthDate)
{
    BirthDate = in_BirthDate ;
}
void user::set_PhoneNumber(QString in_PhoneNumber)
{
    PhoneNumber =in_PhoneNumber ;
}
void user::set_EmailAddress(QString in_EmailAddress)
{
    EmailAddress = in_EmailAddress ;
}

int user::get_ID()
{
    return ID ;
}
QString user::get_UserName()
{
    return UserName ;
}
QString user::get_Password()
{
    return Password ;
}

QString user::get_firstname()
{
    return Firstname;
}
QString user::get_lastname()
{
    return Lastname;
}
QString user::get_PhoneNumber()
{
    return PhoneNumber ;
}
QString user::get_EmailAddress()
{
    return EmailAddress ;
}
QString user::get_BirthDate()
{
    return BirthDate ;
}
void user::set_PVchatID( QVector<int> in_PVchatsID)
{
    PVchatsID = in_PVchatsID ;
}
void user::set_GroupsID( QVector<int> in_GroupsID)
{
    GroupsID = in_GroupsID ;
}
void user::set_ChannelsID( QVector<int> in_ChannelsID)
{
    ChannelsID = in_ChannelsID ;
}
void user::set_FriendsID( QVector<int> in_FriendsID)
{
    FriendsID = in_FriendsID ;
}
QVector<int>  user::get_PVchatsID()
{
    return PVchatsID ;
}
QVector<int>  user::get_GroupsID()
{
     return GroupsID ;
}
QVector<int> user::get_ChannelsID()
{
    return ChannelsID ;
}
QVector<int> user::get_FriendsID()
{
    return FriendsID ;
}
void user::add_PVchatID(int in_chID)
{
    ChannelsID.push_back( in_chID ) ;
}
void user::add_GroupID(int in_gID)
{
    GroupsID.push_back( in_gID ) ;
}
void user::add_ChannelID(int in_chID)
{

    ChannelsID.push_back( in_chID ) ;
}
void user::add_FriendID(int in_FID)
{
    FriendsID.push_back( in_FID ) ;
}

void user::delete_PVchatID(int in_chID)
{
    for(int i = 0 ; i<PVchatsID.size() ; i++ )
    {
        if( PVchatsID[i] == in_chID )
        {
            PVchatsID.removeAt(i) ;
        }
    }
}
void user::delete_GroupID(int in_gID)
{
    for(int i = 0 ; i<GroupsID.size() ; i++ )
    {
        if( GroupsID[i] == in_gID )
        {
            GroupsID.removeAt(i) ;
        }
    }
}
void user::delete_ChannelID(int in_chID)
{
    for(int i = 0 ; i<ChannelsID.size() ; i++ )
    {
        if( ChannelsID[i] == in_chID )
        {
            ChannelsID.removeAt(i) ;
        }
    }
}
void user::delete_FriendID(int in_FID)
{
    for(int i = 0 ; i<FriendsID.size() ; i++ )
    {
        if( FriendsID[i] == in_FID )
        {
            FriendsID.removeAt(i) ;
        }
    }
}
void user::set_Bio( QString in_Bio )
{
    Bio = in_Bio ;
}
QString user::get_Bio()
{
    return Bio ;
}
void user::setNameAccessibility( int in_Accessibility )
{
    nameAccessibility = in_Accessibility;
}
void user::setPhoneAccessibility( int in_Accessibility )
{
    phoneAccessibility = in_Accessibility ;
}
void user::setPhotoAccessibility( int in_Accessibility )
{
    photoAccessibility = in_Accessibility;
}
void user::setFirstNameAccessibility( int in_Accessibility )
{
    nameAccessibility = in_Accessibility;
}
void user::setLastNameAccessibility( int in_Accessibility )
{
    phoneAccessibility = in_Accessibility;
}
void user::setEmailAccessibility( int in_Accessibility )
{
    emailAccessibility = in_Accessibility;
}
void user::setBioAccessibility( int in_Accessibility )
{
    BioAccessibility = in_Accessibility;
}
int user::getNameAccessibility()
{
    return nameAccessibility ;
}
int user::getPhoneAccessibility()
{
    return phoneAccessibility;
}
int user::getPhotoAccessibility()
{
    return photoAccessibility;
}
int user::getFirstNameAccessibility()
{
    return nameAccessibility ;
}
int user::getLastNameAccessibility()
{
    return phoneAccessibility;
}
int user::getEmailAccessibility()
{
    return photoAccessibility;
}
int user::getBioAccessibility()
{
    return BioAccessibility;
}
