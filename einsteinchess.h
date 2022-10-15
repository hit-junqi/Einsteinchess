#ifndef EINSTEINCHESS_H
#define EINSTEINCHESS_H
#include<QString>
class Einsteinchess
{
public:
    Einsteinchess();
    ~Einsteinchess();
    void begin(int id);
    int x;
    int y;
    bool dead;
    bool red;
    int id;
    QString name();
};
#endif // EINSTEINCHESS_H
