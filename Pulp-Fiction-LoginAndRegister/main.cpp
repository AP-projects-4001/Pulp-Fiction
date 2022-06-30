#include "pulp.h"
#include "maindatabase.h"
#include <QApplication>
#include "user.h"
#include "pvchat.h"
#include "loginsystem.h"
#include "homepage.h"
#include "newgroup.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginSystem ls;
    ls.show();
    return a.exec();
}
/*test main 1:
 *     user tmpuser ;
    if ( maindatabase::Check_username("hasan")== true )
    {
        tmpuser.set_UserName("hasan") ;
        tmpuser.set_ID( maindatabase::Creat_ID() ) ;
        tmpuser.set_Password( "12345678" ) ;
        tmpuser.set_PhoneNumber("111111111") ;
        maindatabase::Add_user( tmpuser ) ;
    }
    else
    {
        qDebug() << "bad username" ;
    }*/
/*test main 2:
 *         user tmpuser ;
        tmpuser.set_UserName("hasan") ;
        tmpuser.set_ID( maindatabase::Creat_ID() ) ;
        tmpuser.set_Password( "12345678" ) ;
        tmpuser.set_PhoneNumber("111111111") ;
        if(maindatabase::Find_user( tmpuser ) )
        {
            qDebug() << "found!" ;
        }*/
/*test main 3 :
 *     user owner  , second ;
    owner.set_UserName("zahra") ;
    owner.set_ID( maindatabase::Creat_ID() ) ;
    owner.set_PhoneNumber("093339234936") ;
    second.set_UserName("ali") ;
    second.set_ID( maindatabase::Creat_ID() ) ;
    second.set_PhoneNumber("09111111111") ;
    pvchat pvobj(owner) ;
    pvobj.Make_NewPVChatFile( pvobj.ExtractFileName(  maindatabase::Creat_PVChatID()) , second ) ;
    pvobj.add_Message("zahra:salam" , "PVChat1000.json" ) ;
    pvobj.add_Message("Ali:salam" , "PVChat1000.json" ) ;
    pvobj.add_Message("zahra:khobi" , "PVChat1000.json" ) ;
*/
/*test main 4 :
 *
    user owner  , second ;
        owner.set_UserName("zahra") ;
        owner.set_ID( maindatabase::Creat_ID() ) ;
        owner.set_PhoneNumber("093339234936") ;
        second.set_UserName("ali") ;
        second.set_ID( maindatabase::Creat_ID() ) ;
        second.set_PhoneNumber("09111111111") ;
        pvchat pvobj(owner , second ) ;
        maindatabase::Add_PVChat( pvobj ) ;*/
