#ifndef MAINDATABASE_H
#define MAINDATABASE_H
#include "user.h"
#include"pvchat.h"
class maindatabase
{
public:
    maindatabase();
    static int Creat_ID() ;
    static int Creat_PVChatID() ;
    static int Creat_GrouptID() ;
    static int Creat_ChannelID() ;
    static void Add_user(user in_user) ;
    static void Add_PVChat(pvchat in_PVChat) ;
    static void Add_Group() ;
    static void Add_Channel() ;
    static bool Check_username(QString in_username) ;//for sign in
    static bool Check_PhoneNumber(QString in_PhoneNumber) ;//for sign in
    static bool Check_EmailAddress(QString in_EmailAddress) ;//for sign in
    static bool Check_PVChat(user FirstUser , user SecondUser ) ;
    static bool Find_user( user &in_user ) ;//for login
    static void Push_UserPVChatID() ;
    static void Push_UserGroupID() ;
    static void Push_UserChannelID() ;
    static void Push_UserFriendID() ;
    static void Delete_UserFriendID() ;
    static bool userpasswordForforgot(user in_user, QString &pass);
};

#endif // MAINDATABASE_H
