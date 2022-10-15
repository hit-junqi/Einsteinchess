#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QMainWindow>
#include <QFrame>
#include<QVector>
#include "Einsteinchess.h"
#include "Footwork.h"
#include<QPushButton>
#include<QLineEdit>
#include<QRadioButton>
#include<QLabel>
#include<QGraphicsView>
#include<QString>
#include<QGridLayout>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
class Chessboard: public QMainWindow
{
    Q_OBJECT
private slots:
    void getorder();
    void start_clicked();
    void restart_clicked();
    void mode1_clicked();
    void mode2_clicked();
    void about_clicked();
public:
    explicit Chessboard(QWidget *parent = 0);
    ~Chessboard();
    Einsteinchess einsteinchess[12];
    bool redTurn;
    bool start;
    bool end;
    int radius;
    int order;
    int ordercount;
    int modechoose;
    int selected;
    QPoint off;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QLineEdit*lineedit1;
    QLineEdit*lineedit2;
    QMenu *modeMenu;
    QAction *mode1,*mode2,*about;
    QVector<Footwork*> footworks;
    void begin();
    void redwin();
    void bluewin();
    void LuanXu(int*a,int min,int max);
    void paintEvent(QPaintEvent *);
    void drawPlate(QPainter& p);
    void drawHeadquarters(QPainter& p);
    void drawBeginPosition(QPainter& p);
    void drawBeginPosition(QPainter& p, int x, int y);
    void drawEinsteinchess(QPainter& p);
    void drawEinsteinchess(QPainter& p, int id);
    QPoint center(int row, int col);
    QPoint center(int id);
    QPoint topLeft(int row, int col);
    QPoint topLeft(int id);
    QRect cell(int row, int col);
    QRect cell(int id);
    bool getClickRowCol(QPoint pt, int& x, int& y);
    QString name(int id);
    bool red(int id);
    int getEinsteinchessId(int x, int y);
    void killEinsteinchess(int id);
    void reliveEinsteinchess(int id);
    void moveEinsteinchess(int moveid, int x, int y);
    bool dead(int id);
    void mouseReleaseEvent(QMouseEvent *);
    void click(QPoint pt);
    virtual void click(int id, int x, int y);
    void trySelectEinsteinchess(int id);
    void tryMoveEinsteinchess(int killid, int x, int y);
    void moveEinsteinchess(int moveid, int killid, int x, int y);
    void saveFootwork(int moveid, int killid, int x, int y, QVector<Footwork*>& footworks);
    bool ruleOfChess(int moveid, int x, int y);
    int win();
};
#endif // CHESSBOARD_H
