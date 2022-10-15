#include "Game.h"
#include <QTimer>
Game::Game(QWidget *parent) : Chessboard(parent)      //父类中包含构造函数begin
{
    depth = 3;
}
Game::~Game(){}
void Game::click(int id, int x, int y)
{
    if(redTurn&&order!=-1&&modechoose==2)
    {
        //update();
        Chessboard::click(id, x, y);
        Chessboard::redwin();
        if(!redTurn)
        {   order=-1;
            QTimer::singleShot(100, this, SLOT(computerMove()));
        }
    }
    if(redTurn&&order!=-1&&modechoose==1)
    {
        //update();
        Chessboard::click(id, x, y);
        Chessboard::redwin();
    }
    if(!redTurn&&order!=-1&&modechoose==1)
    {
        //order=-1;
        Chessboard::click(id, x, y);
        Chessboard::bluewin();
    }
}
void Game::computerMove()
{
    order=qrand()%6+6;
    Footwork* footwork = getBestMove();
    moveEinsteinchess(footwork->moveId, footwork->killId, footwork->xTo, footwork->yTo);        //应该移动指定棋子，这个自己写
    delete footwork;
    update();
    bluewin();
}
Footwork* Game::getBestMove()
{
    Footwork* a = NULL;
    QVector<Footwork*> footworks;               //走法集合?
    getPossibleMove(footworks);
    int maxInAllMinvalue = -300000;
    while(footworks.count())
    {
        Footwork* footwork = footworks.last();
        footworks.removeLast();
        assumeGo(footwork);               //这一步已经
        if(win()==2)
        {
            a=footwork;
            assumeBack(footwork);
            while(footworks.count())
            {
                footwork = footworks.last();
                footworks.removeLast();
                delete footwork;
            }
            return a;
        }
        int minvalue = getMinvalue(this->depth-1, maxInAllMinvalue);         //取最大的一步
        assumeBack(footwork);
        if(minvalue > maxInAllMinvalue)          //最小中取最大
        {
            if(a) delete a;
            a = footwork;
            maxInAllMinvalue = minvalue;
        }
        else
        {
            delete footwork;
        }
    }
    return a;
}
int Game::value()                                 //当前局势的得分
{
    int valueBlue = 0;
    int valueRed = 0;
    int number1=0;
    int number2=0;
    for(int i=0; i<6; ++i)
    {
        if(einsteinchess[i].dead) continue;
        number1++;
        valueRed += (einsteinchess[i].y+einsteinchess[i].x)*(einsteinchess[i].y+einsteinchess[i].x)/(8-einsteinchess[i].y-einsteinchess[i].x);
    }
    valueRed=valueRed *number1;
    for(int i=6; i<12; ++i)
    {
        if(einsteinchess[i].dead) continue;
        number2++;
        valueBlue += (8-einsteinchess[i].y-einsteinchess[i].x)*(8-einsteinchess[i].y-einsteinchess[i].x)/(einsteinchess[i].y+einsteinchess[i].x);
    }
    valueBlue=valueBlue *number2;
    return valueBlue - valueRed;
}
int Game::getMinvalue(int depth, int currentMinvalue)                   //得到最小分
{
    if(win()==2)  return 100000+depth;
    if(depth <= 0)return value();
    QVector<Footwork*> footworks;
    getAllPossibleMove(footworks);                                                        //得到所有的可能走法
    int minInAllMaxvalue = 100000;
    while(footworks.count())
    {
        Footwork* footwork = footworks.last();
        footworks.removeLast();
        assumeGo(footwork);
        if(win()==1)
        {
         //a=footwork;
            assumeBack(footwork);
            delete footwork;
            while(footworks.count())
            {
                footwork = footworks.last();
                footworks.removeLast();
                delete footwork;
            }
            return -100000-depth;
        }
        int maxvalue = getMaxvalue(depth-1, minInAllMaxvalue);           //取最小的
        assumeBack(footwork);          //做完后回到模拟前的那步棋
        delete footwork;
        if(maxvalue <= currentMinvalue)     //剪枝算法
        {
            while(footworks.count())
            {
                Footwork* footwork = footworks.last();
                footworks.removeLast();
                delete footwork;
            }
            return maxvalue;
        }
        if(maxvalue < minInAllMaxvalue)
        {
            minInAllMaxvalue = maxvalue;
        }
    }
    return minInAllMaxvalue;
}
int Game::getMaxvalue(int depth, int currentMaxvalue)
{
    if(win()==1)   return -100000-depth;
    if(depth <= 0)return value();       //直接返回总分
    QVector<Footwork*> footworks;
    getAllPossibleMove(footworks);
    int maxInAllMinvalue = -100000;
    while(footworks.count())
    {
        Footwork* footwork = footworks.last();
        footworks.removeLast();
        assumeGo(footwork);
        if(win()==2)
        {
         //a=footwork;
            assumeBack(footwork);
            delete footwork;
            while(footworks.count())
            {
                footwork = footworks.last();
                footworks.removeLast();
                delete footwork;
            }
            return 100000+depth;
        }
        int minvalue = getMinvalue(depth-1, maxInAllMinvalue);
        assumeBack(footwork);
        delete footwork;
        if(minvalue >= currentMaxvalue)
        {
            while(footworks.count())
            {
                Footwork* footwork = footworks.last();
                footworks.removeLast();
                delete footwork;
            }
            return minvalue;
        }
        if(minvalue > maxInAllMinvalue)
        {
            maxInAllMinvalue = minvalue;
        }
    }
    return maxInAllMinvalue;
}
void Game::assumeGo(Footwork *footwork)                     //杀死并且走棋
{
    if(footwork==NULL)return;
    killEinsteinchess(footwork->killId);
    moveEinsteinchess(footwork->moveId, footwork->xTo, footwork->yTo);
}
void Game::assumeBack(Footwork *footwork)                   //复活并且不走棋
{
    if(footwork==NULL)return;
    reliveEinsteinchess(footwork->killId);
    moveEinsteinchess(footwork->moveId, footwork->xFrom, footwork->yFrom);
}
void Game::getPossibleMove(QVector<Footwork *> &footworks)       //得到所有可能路径
{

    if(this->einsteinchess[order].dead){
        int min=100;
        for(int j=6;j<12;j++)
        {
            if(this->einsteinchess[j].dead)continue;
            if(qAbs(j-order)<min)
                 min=qAbs(j-order);
        }
        for(int k=6;k<12;k++)
        {
            if(qAbs(k-order)==min&&!this->einsteinchess[k].dead)
            {
                for(int x = 0; x<5; ++x)
                {
                    for(int y=0; y<5; ++y)
                    {
                        int killId = this->getEinsteinchessId(x, y);
                        if(ruleOfChess(k, x, y))
                            saveFootwork(k, killId, x, y, footworks);
                    }
                }
            }
        }
    }
    if(!this->einsteinchess[order].dead){
        for(int x = 0; x<5; ++x)
        {
            for(int y=0; y<5; ++y)
            {
                int killId = this->getEinsteinchessId(x, y);
                if(ruleOfChess(order, x, y))
                    saveFootwork(order, killId, x, y, footworks);
            }
        }
    }
}
void Game::getAllPossibleMove(QVector<Footwork *> &footworks)       //得到所有可能路径
{
    int minId, maxId;
    if(redTurn)
    {
        minId = 0, maxId = 6;
    }
    else
    {
        minId = 6, maxId = 12;
    }
    for(int i=minId;i<maxId; i++)
    {
        if(this->einsteinchess[i].dead) continue;
        for(int x = 0; x<5; ++x)
        {
            for(int y=0; y<5; ++y)
            {
                int killId = this->getEinsteinchessId(x, y);
                if(ruleOfChess(i, x, y))
                {
                    saveFootwork(i, killId, x, y, footworks);
                }
            }
        }
    }
}

