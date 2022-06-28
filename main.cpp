#include "maindatabase.h"
#include <QApplication>
#include"user.h"
#include"pvchat.h"
#include"group.h"
#include"chat.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user owner  , second ;
    QVector<int> fr{ 1 , 2 , 3 , 4} ;
             owner.set_UserName("samin") ;
             owner.set_ID( maindatabase::Creat_ID() ) ;
             owner.set_PhoneNumber("093339234936") ;
             owner.set_FriendsID( fr ) ;
             maindatabase::Add_user( owner ) ;
             second.set_UserName("ddddddddddddddddddddddddddd") ;
             second.set_ID( maindatabase::Creat_ID() ) ;
             second.set_PhoneNumber("09111111111") ;
             maindatabase::Add_user( second ) ;
             pvchat pvobj(owner , second ) ;
             QString tmpstr = pvobj.ExtractFileName( maindatabase::Creat_PVChatID() );
             pvobj.Make_NewPVChatFile( tmpstr ) ;
             pvobj.add_Message("zahra:salam" , tmpstr) ;
             pvobj.add_Message("Ali:salam" , tmpstr ) ;
             pvobj.add_Message("zahra:khobi" , tmpstr) ;
             maindatabase::Add_PVChat( pvobj ) ;
     maindatabase::Push_UserFriendID( 110, owner ) ;
    return a.exec();
}
/*  testmain:

user owner  , mem1 , mem2 , mem3 ;
        owner.set_UserName("zahra") ;
        owner.set_ID( maindatabase::Creat_ID() ) ;
        owner.set_PhoneNumber("093339234936") ;
        mem1.set_ID(1) ;
        mem1.set_PhoneNumber("123213321") ;
        mem1.set_UserName("ali") ;
        mem2.set_ID(2) ;
        mem2.set_PhoneNumber("88888") ;
        mem2.set_UserName("zahra") ;
        mem3.set_ID(3) ;
        mem3.set_PhoneNumber("776256") ;
        mem3.set_UserName("sima") ;
        Group gobj( owner , "iutgroup") ;
        int tmp = maindatabase::Creat_GroupID() ;
        QString name = gobj.ExtractFileName( tmp ) ;
        //gobj.Make_NewGroupFile( name ) ;
        gobj.add_Message("zahra:salam" ,name  ) ;
        gobj.add_Message("sima:salam" ,name  ) ;
        gobj.add_Message("mohammad:salam" ,name  ) ;
        gobj.add_Member( mem1 , name ) ;
        gobj.add_Member( mem2 , name ) ;
        gobj.add_Member( mem3 , name ) ;
        gobj = Group::read_Group(tmp ) ;*/
