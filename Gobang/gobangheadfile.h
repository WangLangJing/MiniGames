#ifndef HEAD_FIRST
#define HEAD_FIRST 

#define ARRAY_SIZE_X 29 //实现棋盘所用二位数组X大大小
#define ARRAY_SIZE_Y 43 //实现棋盘所用二位数组Y大大小
#define BLACK_CHESSMAN 1//黑色棋子
#define WHITE_CHESSMAN 2//白色棋子
#define CHESSBOARD_X 15+1 //棋盘行大小
#define CHESSBOARD_Y 15+1 //棋盘列大小
#define ATTACKNUM 10
#define DEFENDNUM 15
#define SEARCH_RANDGE 1
#include<vector>
#include<windows.h>
#include<time.h>
#include<iostream>
using namespace std;

struct point
{
 int x,y;
};
struct PositionCondition
{
 bool YESNO;
 int WhoGamer;
};
void CursorPositionGotoxy(int,int); //控制光标
/*****************棋盘类*********************/
class cChessboard
{
private:
  unsigned char  ARRAY[ARRAY_SIZE_X][ARRAY_SIZE_Y];
public:
	cChessboard();
    void DrawChessboard(); //绘制棋盘
	void FallChessman(const point&,const int&);  //落下棋子
};
/******************裁判员类***************/
class cReferee
{ 
private:
  vector<point> BLACK_GAMER;//黑色玩家落子点的集合
  vector<point> WHITE_GAMER;//白色玩家落子点的集合
  PositionCondition   ChessCondition[CHESSBOARD_X][CHESSBOARD_Y];//棋盘上每点的情况（是否有子，若有是谁的子）
  int SuccessGamer;//最终获胜的玩家
public:
	friend class cGamer;
	friend class cGobangAI;
	cReferee();
    void  LogFallChessmanPoint(const point&,const int&);//(记录落子点)
    bool  JudgeWhoSuccess(const point&,const int&); //判断玩家落下此子是否获胜
	bool inputRepeat(const point&);//判断是否在有棋子的地方落子是否越界
	int WinJudge();//返回SuccessGameer
};
/**************玩家类***************/
class cGamer
{
private:
   int iGAMER_COLOR;
   int iChessmanNumber;
public:
  cGamer(const int&);
  void FallChessmanGamer(point&,cChessboard&,cReferee&);//玩家落子
  void BasicDrawing();//基本绘制
};
/********AI类一代*****************/
struct pointAI
{
 int x,y;
 int grade;
};
class cGobangAI
{
private:
  int  EnemyColor;
  int  SelfColor;
  pointAI attackPoint;
  pointAI defendPoint;
  vector<point>*  EnemyData; 
  vector<point>*  SelfData;
  void AttackCountFallPoint(const point&,cReferee&,const int&);//进攻落子点打分
  void AIattack(cReferee&);//进攻点分析
  void DefendCountFallPoint(const point&,cReferee&,const int&);//防守落子点打分
  void AIdefend(cReferee&);//防守点分析
public:
  cGobangAI(const int&,cReferee&);
  bool InterfaceCall(point&, cReferee&);//接口函数	
  void BasicDraw();
  void OutPutDraw(const point&);
};
#endif
