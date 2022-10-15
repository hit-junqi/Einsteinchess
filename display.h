#ifndef DISPLAY_H
#define DISPLAY_H
#include <QWidget>
#include "Chessboard.h"
class Display : public QWidget
{
    Q_OBJECT
public:
    explicit Display(QWidget *parent = 0);
    ~Display();
};
#endif // DISPLAY_H
