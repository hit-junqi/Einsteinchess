#ifndef GAME_H
#define GAME_H
#include "Chessboard.h"
class Game : public Chessboard
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);
    ~Game();
    int depth;
    void click(int id, int x, int y);
    Footwork* getBestMove();
    void getPossibleMove(QVector<Footwork *> &footworks);
    void getAllPossibleMove(QVector<Footwork*>& footworks);
    void changerole();
    int getMinvalue(int depth, int currentMinvalue);
    int getMaxvalue(int depth, int currentMaxvalue);
    int value();
    void assumeGo(Footwork* footwork);
    void assumeBack(Footwork* footwork);
public slots:
    void computerMove();
};
#endif // GAME_H
