#ifndef HEAD_FIRST
#define HEAD_FIRST 

#define ARRAY_SIZE_X 29 //ʵ���������ö�λ����X���С
#define ARRAY_SIZE_Y 43 //ʵ���������ö�λ����Y���С
#define BLACK_CHESSMAN 1//��ɫ����
#define WHITE_CHESSMAN 2//��ɫ����
#define CHESSBOARD_X 15+1 //�����д�С
#define CHESSBOARD_Y 15+1 //�����д�С
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
void CursorPositionGotoxy(int,int); //���ƹ��
/*****************������*********************/
class cChessboard
{
private:
  unsigned char  ARRAY[ARRAY_SIZE_X][ARRAY_SIZE_Y];
public:
	cChessboard();
    void DrawChessboard(); //��������
	void FallChessman(const point&,const int&);  //��������
};
/******************����Ա��***************/
class cReferee
{ 
private:
  vector<point> BLACK_GAMER;//��ɫ������ӵ�ļ���
  vector<point> WHITE_GAMER;//��ɫ������ӵ�ļ���
  PositionCondition   ChessCondition[CHESSBOARD_X][CHESSBOARD_Y];//������ÿ���������Ƿ����ӣ�������˭���ӣ�
  int SuccessGamer;//���ջ�ʤ�����
public:
	friend class cGamer;
	friend class cGobangAI;
	cReferee();
    void  LogFallChessmanPoint(const point&,const int&);//(��¼���ӵ�)
    bool  JudgeWhoSuccess(const point&,const int&); //�ж�������´����Ƿ��ʤ
	bool inputRepeat(const point&);//�ж��Ƿ��������ӵĵط������Ƿ�Խ��
	int WinJudge();//����SuccessGameer
};
/**************�����***************/
class cGamer
{
private:
   int iGAMER_COLOR;
   int iChessmanNumber;
public:
  cGamer(const int&);
  void FallChessmanGamer(point&,cChessboard&,cReferee&);//�������
  void BasicDrawing();//��������
};
/********AI��һ��*****************/
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
  void AttackCountFallPoint(const point&,cReferee&,const int&);//�������ӵ���
  void AIattack(cReferee&);//���������
  void DefendCountFallPoint(const point&,cReferee&,const int&);//�������ӵ���
  void AIdefend(cReferee&);//���ص����
public:
  cGobangAI(const int&,cReferee&);
  bool InterfaceCall(point&, cReferee&);//�ӿں���	
  void BasicDraw();
  void OutPutDraw(const point&);
};
#endif
