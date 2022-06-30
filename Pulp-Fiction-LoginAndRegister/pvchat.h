#ifndef PVCHAT_H
#define PVCHAT_H

#include "chat.h"
#include "user.h"
class pvchat : public chat
{
private:
    user Addressee ;
public:
    pvchat( user in_Owner , user in_Addressee);
    void Make_NewPVChatFile( QString FileName  ) ;
    QString ExtractFileName( int PVChatID ) ;
    user get_Addressee() ;
    void set_Addressee( user in_Addressee ) ;
    static pvchat read_PVChat( int in_ID ) ;
};

#endif // PVCHAT_H
