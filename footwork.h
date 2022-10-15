#ifndef FOOTWORK_H
#define FOOTWORK_H
#include <QObject>
class Footwork: public QObject
{
    Q_OBJECT
public:
    explicit Footwork(QObject *parent = 0);
    ~Footwork();
    int moveId;
    int killId;
    int xFrom;
    int yFrom;
    int xTo;
    int yTo;
};

#endif // FOOTWORK_H
