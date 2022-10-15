#include "Chessboard.h"
#include <QPainter>
#include <QMouseEvent>
#include<QPushButton>
#include<QLineEdit>
#include<QTime>
#include<QRadioButton>
#include<QLabel>
#include<QGraphicsView>
#include<QString>
#include<QGridLayout>
#include<QMenuBar>
#include<QMenu>
#include<QMessageBox>
#include<QAction>
#include <QtGui>
Chessboard::Chessboard(QWidget *parent) : QMainWindow(parent)
{
    order=-1;
    this->radius= 20;
    ordercount=0;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    modechoose=0;
    start=0;
    end=0;
    button1 = new QPushButton(this);
    lineedit1=new QLineEdit(this);
    lineedit1->setEnabled(false);
    button2 = new QPushButton(this);
    button3 = new QPushButton(this);
    lineedit2=new QLineEdit(this);
    lineedit2->setEnabled(false);
    connect(button1,SIGNAL(clicked(bool)),this,SLOT(getorder()));
    connect(button2,SIGNAL(clicked(bool)),this,SLOT(start_clicked()));
    connect(button3,SIGNAL(clicked(bool)),this,SLOT(restart_clicked()));
    this->modeMenu = this->menuBar()->addMenu(tr("模式"));
    this->mode1 = this->modeMenu->addAction(tr("人人对战"));
    this->mode2 = this->modeMenu->addAction(tr("人机对战"));
    this->about = this->menuBar()->addAction(tr("关于"));
    connect(this->mode1,SIGNAL(triggered(bool)),this,SLOT(mode1_clicked()));
    connect(this->mode2,SIGNAL(triggered(bool)),this,SLOT(mode2_clicked()));
    connect(this->about,SIGNAL(triggered(bool)),this,SLOT(about_clicked()));
    setMinimumSize(radius*18+1, radius*20+1);
    begin();
}
Chessboard::~Chessboard(){};
void Chessboard::begin()
{
    int a[12];
    for(int j=0;j<12;j++)
       a[j]=j;
    LuanXu(a,0,6);
    LuanXu(a,6,12);
    for(int i=0; i<6; ++i)
    {
        int j=a[i];
        einsteinchess[i].id=i;
        einsteinchess[i].red=true;
        einsteinchess[i].begin(j);
    }
    for(int i=6; i<12; ++i)
    {
        int j=a[i];
        einsteinchess[i].id=i;
        einsteinchess[i].red=false;
        einsteinchess[i].begin(j);
    }
    selected = -1;
    redTurn = true;
    update();
}
void Chessboard::paintEvent(QPaintEvent *)
{
    int r = height()/20;
    radius = r;
    off = QPoint(r+1, r+1);
    button1->setGeometry(QRect(260,80,60,50));
    button1->setText("掷骰子");
    QBrush myBrush;
    QPalette palette;
    myBrush = QBrush(Qt::green,Qt::DiagCrossPattern);
    palette.setBrush( QPalette::Text,  myBrush);
    lineedit1->setFont(QFont("Timers" , 28 ,  QFont::Bold));
    lineedit1->setPalette(palette);
    button2->setGeometry(QRect(50,330,40,40));
    button2->setText("开始");
    button3->setGeometry(QRect(245,330,40,40));
    button3->setText("重玩");
    lineedit1->setGeometry(QRect(260,140,60,50));
    lineedit2->setGeometry(QRect(20,260,300,50));
    lineedit2->setText("注意：每次移动棋子前只有一次掷骰子的机会!");
    myBrush = QBrush(Qt::blue,Qt::DiagCrossPattern);
    palette.setBrush( QPalette::Text,  myBrush);
    lineedit2->setFont(QFont("Timers" , 8 ,  QFont::Bold));
    lineedit2->setPalette(palette);
    if(order==0||order==6)
        lineedit1->setText(" 1 ");
    if(order==1||order==7)
        lineedit1->setText(" 2 ");
    if(order==2||order==8)
        lineedit1->setText(" 3 ");
    if(order==3||order==9)
        lineedit1->setText(" 4 ");
    if(order==4||order==10)
        lineedit1->setText(" 5 ");
    if(order==5||order==11)
        lineedit1->setText(" 6 ");
    if(order==-1)
        lineedit1->setText(" ");
    QPainter p(this);
    p.save();
    drawPlate(p);
    drawEinsteinchess(p);                //画棋子
    p.restore();
}
void Chessboard::drawEinsteinchess(QPainter &p)
{
    for(int i=0; i<12; i++)
    {
        drawEinsteinchess(p, i);
    }
}
bool Chessboard::dead(int id)
{
    if(id == -1)return true;
    return einsteinchess[id].dead;
}
void Chessboard::LuanXu(int*a,int min,int max)//数组元素的乱序排列
{
    for(int i=min;i<max;i++)
    {
        int r = min+qrand()%6;
        int temp=a[i];
        a[i]=a[r];
        a[r]=temp;
    }
}
void Chessboard::drawEinsteinchess(QPainter &p, int id)            //画棋子
{
    if(dead(id)) return;
    QColor c;
    if(red(id)) c = Qt::red;
    else c = Qt::blue;
    p.setPen(QPen(QBrush(c), 1));
    if(id == selected) p.setBrush(Qt::gray);          //被选中为灰色
    else p.setBrush(Qt::white);
    p.drawEllipse(cell(id));
    p.setFont(QFont("song",radius*1));
    p.drawText(cell(id), name(id),QTextOption(Qt::AlignCenter));
}
QString Chessboard::name(int id)
{
    return einsteinchess[id].name();
}
bool Chessboard::red(int id)
{
    return einsteinchess[id].red;
}
void Chessboard::drawPlate(QPainter &p)
{
    for(int i=0; i<5; ++i)
        p.drawLine(center(i, 0), center(i, 4));
    for(int i=0; i<5; ++i)
        p.drawLine(center(0, i), center(4, i));
}
QPoint Chessboard::center(int x, int y)
{
    QPoint pt(radius*y*2+5, radius*x*2+40);
    return pt + off;
}
QPoint Chessboard::center(int id)
{
    return center(einsteinchess[id].x, einsteinchess[id].y);
}
QPoint Chessboard::topLeft(int x, int y)
{
    return center(x, y) - QPoint(radius, radius);
}
QPoint Chessboard::topLeft(int id)
{
    return center(id) - QPoint(radius, radius);
}
QRect Chessboard::cell(int x, int y)
{
    return QRect(topLeft(x, y), QSize(radius*2-1, radius*2-1));
}
QRect Chessboard::cell(int id)
{
    return QRect(topLeft(id), QSize(radius*2-1, radius*2-1));
}
bool Chessboard::getClickRowCol(QPoint pt, int &x, int &y)                      //点击的位置是对的
{
    for(x=0; x<5; ++x)
    {
        for(y=0; y<5; ++y)
        {
            QPoint distance = center(x, y) - pt;
            if(distance.x() * distance.x() + distance.y() * distance.y() < radius* radius)
                return true;
        }
    }
    return false;
}
int Chessboard::win(){                                                             //最后加
    int i,j,num1=0,num2=0;
    if(getEinsteinchessId(0,0)>5)
        return 2;
    if(getEinsteinchessId(4,4)>=0&&getEinsteinchessId(4,4)<6)
        return 1;
    for(i=0;i<5;i++)
        for(j=0;j<5;j++){
            if(getEinsteinchessId(i,j)>5)
                num2++;
            if(getEinsteinchessId(i,j)>=0&&getEinsteinchessId(i,j)<6)
                num1++;
        }
    if(num2==0)
        return 1;
    if(num1==0)
        return 2;
    return 0;
}
void Chessboard::redwin()
{
    if(win()==1)
    {
        QMessageBox::warning(NULL,"游戏结束","红方胜利!",
                             QMessageBox::Yes , QMessageBox::Yes);
        restart_clicked();
    }
}
void Chessboard::bluewin()
{
    if(win()==2)
    {
        QMessageBox::warning(NULL,"游戏结束","蓝方胜利!",
                             QMessageBox::Yes , QMessageBox::Yes);
        restart_clicked();
    }
}
void Chessboard::mode1_clicked()
{
     if(start==0)
        modechoose=1;
}
void Chessboard::mode2_clicked()
{
    if(start==0)
        modechoose=2;
}
void Chessboard::about_clicked()
{
    QMessageBox::warning(NULL,"游戏规则",
"每方回合轮流掷骰子，然后选择一枚与骰点同样数字的己棋朝下、右、或右下方（蓝色为朝上、左、左上方）移动一格至任何棋位，若无同点棋则改移最接近该数的己棋之一。当移到任何方棋子，将原位棋子移除棋盘不再使用。以先抵达敌方角落位，或消灭所有敌棋为胜!",
                         QMessageBox::Yes , QMessageBox::Yes);
}
void Chessboard::mouseReleaseEvent(QMouseEvent * clickPoint)
{
    click(clickPoint->pos());
}
void Chessboard::trySelectEinsteinchess(int id)                  //选择一个棋子
{
    if(id == -1)return;
    if(selected!=-1) return;
    if(redTurn)
    {
        if(this->einsteinchess[order].dead)
        {
            int min=10;
            for(int j=0;j<6;j++)
            {
                if(this->einsteinchess[j].dead)continue;
                if(qAbs(j-order)<min)
                     min=qAbs(j-order);
            }
            for(int k=0;k<6;k++)
            {
             if(qAbs(k-order)==min&&!this->einsteinchess[k].dead&&k==id)
                    selected=id;
            }
        }
        if(!this->einsteinchess[order].dead)
        {
            if(id==order)
                   selected=id;
        }
        update();
    }
    if(!redTurn)
    {
        if(this->einsteinchess[order+6].dead)
        {
            int min=10;
            for(int j=6;j<12;j++)
            {
                if(this->einsteinchess[j].dead)continue;
                if(qAbs(j-order-6)<min)
                    min=qAbs(j-order-6);
            }
            for(int k=6;k<12;k++)
            {
                if(qAbs(k-order-6)==min&&!this->einsteinchess[k].dead&&k==id)
                    selected=id;

            }
        }
        if(!this->einsteinchess[order+6].dead)
        {
            if(id==order+6)
                selected=id;
        }
    update();
    }
}
void Chessboard::tryMoveEinsteinchess(int killid, int x, int y)       //待定
{
    if(ruleOfChess(selected, x, y))             //说明可以移动
    {
        moveEinsteinchess(selected,killid, x, y);
        selected = -1;
        update();
    }
}
void Chessboard::start_clicked()
{
    if(modechoose == 0)
        QMessageBox::warning(NULL,"Warning","请在菜单栏中选择对弈模式，人人或人机!",
                             QMessageBox::Yes , QMessageBox::Yes);
    if(modechoose != 0&&end==0)
    {
        start=1;
        ordercount=0;
    }

}
void Chessboard::restart_clicked()
{
    modechoose=0;
    order=-1;
    start=0;
    end=0;
    ordercount=0;
    begin();
}
void Chessboard::getorder()
{
    if(modechoose!=0&&start!=0&&ordercount==0)
    {
        order=qrand()%6;
        ordercount=1;
        update();
    }
}
bool Chessboard::ruleOfChess(int moveid, int x, int y)
{
    if(einsteinchess[moveid].red)
    {
        if(einsteinchess[moveid].x==x-1&&einsteinchess[moveid].y==y&&x>=0&&x<5&&y>=0&&y<5) return true;
        if(einsteinchess[moveid].x==x&&einsteinchess[moveid].y==y-1&&x>=0&&x<5&&y>=0&&y<5) return true;
        if(einsteinchess[moveid].x==x-1&&einsteinchess[moveid].y==y-1&&x>=0&&x<5&&y>=0&&y<5) return true;
    }
    if(!einsteinchess[moveid].red)
    {
        if(einsteinchess[moveid].x==x+1&&einsteinchess[moveid].y==y&&x>=0&&x<5&&y>=0&&y<5) return true;
        if(einsteinchess[moveid].x==x&&einsteinchess[moveid].y==y+1&&x>=0&&x<5&&y>=0&&y<5) return true;
        if(einsteinchess[moveid].x==x+1&&einsteinchess[moveid].y==y+1&&x>=0&&x<5&&y>=0&&y<5) return true;
    }
    return false;
}
void Chessboard::reliveEinsteinchess(int id)
{
    if(id==-1) return;
    einsteinchess[id].dead = false;
}
void Chessboard::killEinsteinchess(int id)       //杀死某个棋子
{
    if(id==-1) return;
    einsteinchess[id].dead = true;
}
void Chessboard::moveEinsteinchess(int moveid, int x, int y)       //移动某个棋子到某个位置
{
    einsteinchess[moveid].x = x;
    einsteinchess[moveid].y = y;
    redTurn = !redTurn;
    ordercount=0;
}
void Chessboard::saveFootwork(int moveId, int killId, int x, int y, QVector<Footwork*>& footworks)
{
    Footwork* footwork = new Footwork;
    footwork->yFrom = einsteinchess[moveId].y;       //保留移动棋子位置
    footwork->yTo = y;
    footwork->xFrom = einsteinchess[moveId].x;
    footwork->xTo = x;
    footwork->moveId = moveId;
    footwork->killId = killId;
    footworks.append(footwork);                       //加入这个位置
}
void Chessboard::moveEinsteinchess(int moveid, int killid, int x, int y)
{
    saveFootwork(moveid, killid, x, y, footworks);
    killEinsteinchess(killid);
    moveEinsteinchess(moveid, x, y);
}
void Chessboard::click(int id, int x, int y)
{
    if(this->selected == -1)
    {
        trySelectEinsteinchess(id);                         //selected=id
    }
    else
    {
        tryMoveEinsteinchess(id, x, y);
    }
}
void Chessboard::click(QPoint pt)
{
    int x, y;
    bool a = getClickRowCol(pt, x, y);       //这个点的坐标在棋子范围内，顺便把坐标给到row和col
    if(!a) return;                               //没有点中棋子
    int id = getEinsteinchessId(x, y);
    click(id, x, y);
}
int Chessboard::getEinsteinchessId(int x, int y)              //得到棋子的序号
{
    for(int i=0; i<12; ++i)
    {
        if(einsteinchess[i].x == x && einsteinchess[i].y == y && !dead(i))
            return i;
    }
    return -1;
}

