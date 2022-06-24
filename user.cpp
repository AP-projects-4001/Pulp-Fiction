#include "user.h"
user::user()
{

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
    if( in_Pass.size() < 8 )
    {
        //temp //error dialog
        return ;
    }
    Password =in_Pass ;
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
