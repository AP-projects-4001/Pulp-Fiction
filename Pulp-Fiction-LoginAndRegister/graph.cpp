#include "graph.h"
Graph::Graph()
{
    QFile F( "Relations.json" ) ;
    if( !F.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
    }
    F.close();
}
void Graph::Update_RelationFile( QVector<user> in_users )
{
    QFile F( "Relations.json" ) ;
    F.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    QJsonObject JsonObj ;
    for(int i=0 ; i<in_users.size() ; i++ )
    {
        QJsonArray TempArr ;
        QVector<int> TempV = in_users[i].get_FriendsID()  ;
        for(int j=0 ; j<TempV.count() ; j++)
        {
            TempArr.push_back( TempV[j] ) ;
        }
        JsonObj.insert( QString::number(in_users[i].get_ID()) , TempArr ) ;
    }
    QJsonDocument JsonDoc  ;
    JsonDoc.setObject( JsonObj ) ;
    F.write( JsonDoc.toJson() ) ;
    F.close() ;
}
void Graph::Update_UserRelation( user in_user )
{
    QFile RF( "Relations.json" ) ;
    if( !RF.open(QIODevice::ReadOnly) )
    {
        qDebug() << "File open error";//temp// error dialog should be open here
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(RF.readAll(), &JsonParseError) ;
    RF.close();
    QJsonArray UFArr ;//= JsonDoc[QString::number(in_user.get_ID())].toArray() ;
    QVector<int> FVec = in_user.get_FriendsID() ;
    for(int i=0 ; i<FVec.count() ; i++ )
    {
        UFArr.append( FVec[i] ) ;
    }
    QJsonObject Jobj = JsonDoc.object() ;
    Jobj.insert( QString::number(in_user.get_ID()) , UFArr ) ;
    JsonDoc.setObject( Jobj ) ;
    RF.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    RF.write( JsonDoc.toJson() ) ;
    RF.close() ;

}
QVector<QVector<int>> Graph::Make_MatrixTable( int in_Dimension )
{
    QVector<QVector<int>> MatrixVec ;
    for(int i =0  ; i<in_Dimension ; i++ )
    {
        QVector<int> temp ;
        for(int j=0 ; j<in_Dimension ; j++ )
        {
            temp.push_back(0) ;
        }
        MatrixVec.push_back(temp) ;
    }
    return MatrixVec ;

}
QJsonArray Graph::Find_Correspondingvertices( int  HeadID )
{
    QFile F( "Relations.json" ) ;
    if( !F.open(QIODevice::ReadOnly) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(F.readAll(), &JsonParseError) ;
    F.close() ;
    QJsonArray FArr1 = JsonDoc[QString::number(HeadID)].toArray() ;
    QJsonArray FArr2 = FArr1 ;
    FArr2.push_front(HeadID) ;
    int c=0 ;
    while(c<2)
    {
    for(int i=0 ; i<FArr2.count() ; i++ )
    {
            QJsonArray tmp = JsonDoc[QString::number(FArr2.at(i).toInt())].toArray() ;
            for(int j=0 ; j<tmp.count() ; j++ )
            {
                bool b=true ;
                for(int t=0 ; t<FArr2.size() ; t++)
                {
                    if( FArr2[t] == tmp[j] )
                        b = false ;
                }
                if(b)
                {
                    FArr2.append(tmp[j]) ;
                }
            }
    }
    c++ ;
    }
    return FArr2 ;
}
QJsonArray Graph::Make_EdgesArray( int HeadID )
{
    QFile F( "Relations.json" ) ;
    if( !F.open(QIODevice::ReadWrite) )
    {
       qDebug() << "File open error";//temp// error dialog should be open here
    }
    QJsonParseError JsonParseError ;
    QJsonDocument JsonDoc = QJsonDocument::fromJson(F.readAll(), &JsonParseError) ;
    F.close() ;
    QJsonArray FArr1 = JsonDoc[QString::number(HeadID)].toArray() ;
    QJsonArray EdgesArray ;
    for(int i=0 ; i<FArr1.count() ; i++ )
    {
        QJsonArray tmp1 ;
        tmp1.append( HeadID ) ;
        tmp1.append( FArr1[i] ) ;
        if( Check_Uniqueness( EdgesArray , tmp1 ) )
            EdgesArray.append( tmp1 ) ;
        QJsonArray FArr2 = JsonDoc[QString::number(FArr1.at(i).toInt())].toArray() ;
        for(int j=0 ; j<FArr2.count() ; j++ )
        {
            QJsonArray tmp2 ;
            tmp2.append( FArr1[i] ) ;
            tmp2.append( FArr2[j] ) ;
            if( Check_Uniqueness( EdgesArray , tmp2 ) )
                EdgesArray.append( tmp2 ) ;
            QJsonArray FArr3 = JsonDoc[QString::number(FArr2.at(j).toInt())].toArray() ;
            for(int t=0 ; t<FArr3.count() ; t++ )
            {
                QJsonArray tmp3 ;
                tmp3.append( FArr2[j] ) ;
                tmp3.append( FArr3[t] ) ;
                if( Check_Uniqueness( EdgesArray , tmp3 ) )
                    EdgesArray.append( tmp3 ) ;
            }
        }
    }
    return EdgesArray ;

}
QJsonArray Graph::Virtualization( QJsonArray CurrArr , QJsonArray AuxiliaryArr )
{
    for( int i=0 ; i<AuxiliaryArr.count() ; i++ )
    {
        for( int j=0 ; j<CurrArr.count() ; j++ )
        {
                if( CurrArr[j][0] == AuxiliaryArr[i] )
                {
                    QJsonArray tmp ;
                    tmp.push_back(i) ;
                    tmp.push_back( CurrArr[j][1] ) ;
                    CurrArr.replace( j , tmp ) ;
                }
                if( CurrArr[j][1] == AuxiliaryArr[i] )
                {
                    QJsonArray tmp ;
                    tmp.push_back( CurrArr[j][0] ) ;
                    tmp.push_back(i) ;
                    CurrArr.replace( j , tmp ) ;
                }
                continue ;
        }
    }
    return CurrArr ;
}
bool Graph::Check_Uniqueness( QJsonArray Base , QJsonArray Examined )
{
    for( int i=0 ; i<Base.count() ; i++ )
    {
        if( Base[i][0] == Examined[0] && Base[i][1] == Examined[1] )
            return false ;
    }
    return true ;
}
QVector<QVector<int>> Graph::Creat_AdjacencyMatrix( int HeadID )
{
    QJsonArray Vertices = Find_Correspondingvertices( HeadID ) ;
    QVector<QVector<int>> AdjMatrix = Make_MatrixTable( Vertices.count() ) ;
    QJsonArray Edges = Virtualization( Make_EdgesArray(HeadID) , Vertices ) ;
    qDebug() << Edges.count() ;
    for(int i=0 ; i<Edges.count() ; i++)
    {
        int x = Edges[i][0].toInt() ;
        int y = Edges[i][1].toInt() ;
        AdjMatrix[x][y] = 1 ;
    }
    return AdjMatrix ;
}
QVector<QString> Graph::Creat_Guidlist( int HeadID )
{
    QJsonArray vertices =  Find_Correspondingvertices( HeadID )  ;
    QVector<QString> result ;
    for(int i=0 ; i< vertices.count() ; i++ )
    {
        user tmpu ;
        tmpu = maindatabase::getUserdetails( vertices.at(i).toInt() ) ;
        if( tmpu.get_UserName() == "" )
            tmpu.set_UserName("unknown username") ;
        QString tmpnode = tmpu.get_UserName() +" : " + QString::number(i) ;
        result.push_back( tmpnode ) ;
    }
    return result ;
}
QVector<QString> Graph::Convert_MatrixToString( QVector<QVector<int>> in_Matrix )
{
    QVector<QString> ans ;
    for( int i=0 ; i<in_Matrix.count()  ;i++)
    {
        QString tmpstr ;
        tmpstr += QString::number(in_Matrix[i][0]) ;
        for( int j=1 ; j<in_Matrix[i].count() ; j++ )
        {
            tmpstr += "," + QString::number(in_Matrix[i][j])  ;
        }
        ans.append( tmpstr ) ;
    }
    return ans ;
}

