#include "maindatabase.h"
#include <QApplication>
#include"user.h"
#include"pvchat.h"
#include"group.h"
#include"chat.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    user u ;
    u.set_UserName("homa") ;
    u.set_Firstname("hooomaa") ;
    u.set_ID(1007) ;
    maindatabase::Modify_UserDetails( u ) ;
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
