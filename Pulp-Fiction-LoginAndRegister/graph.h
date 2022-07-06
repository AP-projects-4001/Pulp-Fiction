#ifndef GRAPH_H
#define GRAPH_H
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include "QJsonParseError"
#include "user.h"
#include "maindatabase.h"
class Graph
{
public:
    Graph();
    static void Update_RelationFile( QVector<user> in_users ) ;
    static void Update_UserRelation( user in_user ) ;
    static QVector<QVector<int>> Make_MatrixTable( int in_Dimension ) ;
    static QJsonArray Find_Correspondingvertices( int  HeadID ) ;
    static QJsonArray Make_EdgesArray( int HeadID ) ;
    static QJsonArray Virtualization( QJsonArray CurrArr , QJsonArray AuxiliaryArr ) ;
    static bool Check_Uniqueness( QJsonArray Base , QJsonArray Examined ) ;
    static QVector<QVector<int>> Creat_AdjacencyMatrix( int HeadID ) ;
    static QVector<QString> Creat_Guidlist( int HeadID )  ;


};

#endif // GRAPH_H

