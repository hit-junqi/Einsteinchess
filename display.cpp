#include "Display.h"
#include <QHBoxLayout>
#include "Game.h"
Display::Display(QWidget *parent) : QWidget(parent)
{
    Game* game = new Game;
    QHBoxLayout* a = new QHBoxLayout(this);
    a->addWidget(game, 1);
}
Display::~Display(){}
