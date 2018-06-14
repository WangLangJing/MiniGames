#include "gobangheadfile.h"

void CursorPositionGotoxy(int x,int y)//���ƹ��
{
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD pos;
  pos.X=x;
  pos.Y=y;
  SetConsoleCursorPosition(hOut,pos);
}
/*******************************������*******************************************/
cChessboard::cChessboard()//���̵ĳ�ʼ��
{
 for(int i=0;i<ARRAY_SIZE_X;++i)
  {
     for(int j=0;j<ARRAY_SIZE_Y;++j)
	    ARRAY[i][j]=0;
  }   
  for(int i=0;i<ARRAY_SIZE_X;++i)
  {
      for(int j=0;j<ARRAY_SIZE_Y;++j)
	  {
		  if(i%2==0)
			  ARRAY[i][j]=205;  //����
		  if(j%3==0)
			  ARRAY[i][j]=186;  //����
		  if(i%2==0 && j%3==0)
			   ARRAY[i][j]=206; //ʮ��
		  if(i==0 && j%3==0)
			   ARRAY[i][j]=203; //ʮ������
		  if(j==0 && i%2==0)
			   ARRAY[i][j]=204; //ʮ������
		  if(i==(ARRAY_SIZE_X-1) && j%3==0)
			   ARRAY[i][j]=202;  //ʮ������
		  if(j==(ARRAY_SIZE_Y-1) && i%2==0)
			   ARRAY[i][j]=185; //ʮ������
		  if(i==0 && j==0)
               ARRAY[i][j]=201; //���¹�
		  if(i==0 && j==(ARRAY_SIZE_Y-1))
			   ARRAY[i][j]=187; //���¹�
		  if(i==(ARRAY_SIZE_X-1) && j==0)
			   ARRAY[i][j]=200; //���Ϲ�
		  if(i==(ARRAY_SIZE_X-1) && j==(ARRAY_SIZE_Y-1))
			   ARRAY[i][j]=188; //���Ϲ�
	  }
  }
}
void cChessboard::DrawChessboard() //���̵Ļ���
{
  for(int z=0;z<ARRAY_SIZE_X;++z)
  {
    if(z%2==0)
    { 
      CursorPositionGotoxy(16,z+3);
	  cout<<(z/2+1)<<flush;
	}
  }
  for(int x=0;x<ARRAY_SIZE_Y;++x)
  {
    if(x%3==0)
	{
	 CursorPositionGotoxy(20+x,1);
	  cout<<(x/3+1)<<flush;
	}
  }
  for(int i=0;i<ARRAY_SIZE_X;++i)
  { 
     CursorPositionGotoxy(20,i+3);
     for(int j=0;j<ARRAY_SIZE_Y;++j)
	 {
		 cout<<ARRAY[i][j];
	 }
	 cout<<flush;
  }  
}
void cChessboard::FallChessman(const point & XY,const int& WhoGamer)//����
{
  int i(0),j(0);
  unsigned char z;
  i=(XY.x-1)*3;
  j=(XY.y-1)*2;
  z=WhoGamer;
  CursorPositionGotoxy(i+20,j+3);
  cout<<z<<flush;
}
/**********************************����Ա��****************************************/
cReferee::cReferee()
{
    SuccessGamer=0;
	for(int i=0;i<CHESSBOARD_X;++i)
	{
	   for(int j=0;j<CHESSBOARD_Y;++j)
	   {
         ChessCondition[i][j].YESNO=false;
	     ChessCondition[i][j].WhoGamer=0;
	   }
	}
}
void cReferee::LogFallChessmanPoint(const point & XY,const int& WhoGamer)//��¼���ӵ�
{
 if(BLACK_CHESSMAN==WhoGamer)
  BLACK_GAMER.push_back(XY);
 if(WHITE_CHESSMAN==WhoGamer)
  WHITE_GAMER.push_back(XY);
  ChessCondition[XY.x][XY.y].YESNO=true;
  ChessCondition[XY.x][XY.y].WhoGamer=WhoGamer;
}
bool cReferee::JudgeWhoSuccess(const point& chessmanPos,const int& WhoGamer)//�ж�˭��˭Ӯ
{
  int iChessmanNumber(0);
  int x,y;
  if(iChessmanNumber<5)//�ں������ϼ��
  {
   iChessmanNumber=0;
   for(x=chessmanPos.x,y=chessmanPos.y;x<(chessmanPos.x+5);++x) 
   {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x>15)
		 break;
   }
   for(x=chessmanPos.x-1,y=chessmanPos.y;x>(chessmanPos.x-5);--x) 
   {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x<1)
		break;
   }
  }
  if(iChessmanNumber<5)//���������ϼ��
  {
   iChessmanNumber=0;
   for(x=chessmanPos.x,y=chessmanPos.y;y<(chessmanPos.y+5);++y) 
   {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || y>15)
		break;
   }
   for(x=chessmanPos.x,y=chessmanPos.y-1;y>(chessmanPos.y-5);--y) 
   {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || y<1)
		break;
   }
  }
   if(iChessmanNumber<5)//�����µ����ϼ����
  {
   iChessmanNumber=0;
  for(x=chessmanPos.x,y=chessmanPos.y;x<(chessmanPos.x+5);++x,--y) 
  {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x>15 || y<1)
		break;
  }
   for(x=chessmanPos.x-1,y=chessmanPos.y+1;x>(chessmanPos.x-5);--x,++y) 
   {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x<1 || y>15)
		break;
   }
  }
   if(iChessmanNumber<5)//�����ϵ����¼����
  {
   iChessmanNumber=0;
  for(x=chessmanPos.x,y=chessmanPos.y;x<(chessmanPos.x+5);++x,++y) 
  {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x>15 || y>15)
		break;
  }
  for(x=chessmanPos.x-1,y=chessmanPos.y-1;x>(chessmanPos.x-5);--x,--y) 
  {
    if(true==ChessCondition[x][y].YESNO && WhoGamer==ChessCondition[x][y].WhoGamer)
	  ++iChessmanNumber;
	if(WhoGamer!=ChessCondition[x][y].WhoGamer || x<1 || y<1)
		break;
  }
  }
  if(iChessmanNumber>=5)
   {
     SuccessGamer=WhoGamer;
     return true;
   }
   return false;
}
bool  cReferee::inputRepeat(const point& XY)
{
   if(XY.x>15 || XY.x<1 || XY.y>15 || XY.y<1)
	  return false;
   if(ChessCondition[XY.x][XY.y].YESNO==true)
	  return false;
   if(ChessCondition[XY.x][XY.y].YESNO==false)
	  return true;
}
int cReferee::WinJudge()
{
 if(WHITE_CHESSMAN==SuccessGamer)
	 return WHITE_CHESSMAN;
 if(BLACK_CHESSMAN==SuccessGamer)
	 return BLACK_CHESSMAN;
 return 0;
}
/*********************************������ʵ��***********************************/
cGamer::cGamer(const int & gamer_color)
{
  iGAMER_COLOR=gamer_color;
  iChessmanNumber=0;
}
void cGamer::BasicDrawing()//������ֵ�ָ��λ��
{
 if(BLACK_CHESSMAN==iGAMER_COLOR)
   {
      CursorPositionGotoxy(65,5);
      cout<<"Please input point(BlackGamer):"<<flush;
      CursorPositionGotoxy(97,5);
		for(int i=0;i<10;++i)
			cout<<' ';
   }
  if(WHITE_CHESSMAN==iGAMER_COLOR)
   {
      CursorPositionGotoxy(65,6);
      cout<<"Please input point(WhiteGamer):"<<flush;
	  CursorPositionGotoxy(97,6);
	  for(int i=0;i<10;++i)
			cout<<' ';
   }
}

void cGamer::FallChessmanGamer(point &XY, cChessboard& board,cReferee& referee)//�������
{
   if(BLACK_CHESSMAN==iGAMER_COLOR)
   {
      CursorPositionGotoxy(97,5);
      cin>>XY.x>>XY.y;
	  while(!referee.inputRepeat(XY))
	  {
	    CursorPositionGotoxy(20,37);
        cout<<"Sorroy! This point has chessman or Crossing the line.Please input again."<<flush;
        CursorPositionGotoxy(97,5);
		for(int i=0;i<10;++i)
			cout<<' ';
		cout<<flush;
		CursorPositionGotoxy(97,5);
		cin>>XY.x>>XY.y;
	  }
	  CursorPositionGotoxy(20,37);
	  for(int i=0;i<72;++i)
			cout<<' ';
	  cout<<flush;
	  board.FallChessman(XY,BLACK_CHESSMAN);
	  referee.BLACK_GAMER.push_back(XY);
	  referee.ChessCondition[XY.x][XY.y].YESNO=true;
	  referee.ChessCondition[XY.x][XY.y].WhoGamer=BLACK_CHESSMAN;
   }
  if(WHITE_CHESSMAN==iGAMER_COLOR)
   {
      CursorPositionGotoxy(97,6);
      cin>>XY.x>>XY.y;
	  while(!referee.inputRepeat(XY))
	  {
	    CursorPositionGotoxy(20,37);
        cout<<"Sorroy! This point has chessman or Crossing the line.Please input again."<<flush;
        CursorPositionGotoxy(97,6);
		for(int i=0;i<10;++i)
			cout<<' ';
		cout<<flush;
		CursorPositionGotoxy(97,6);
		cin>>XY.x>>XY.y;
	  }
	  CursorPositionGotoxy(20,37);
	  for(int i=0;i<72;++i)
			cout<<' ';
	  cout<<flush;
	  board.FallChessman(XY,WHITE_CHESSMAN);
	  referee.WHITE_GAMER.push_back(XY);
	  referee.ChessCondition[XY.x][XY.y].YESNO=true;
	  referee.ChessCondition[XY.x][XY.y].WhoGamer=WHITE_CHESSMAN;
   }
}
/*********************************������AIһ��*****************************************/
cGobangAI::cGobangAI(const int& WhoEnemy,cReferee& referee)//��ʼ����������
{
 EnemyColor=WhoEnemy;
 if(BLACK_CHESSMAN==WhoEnemy)
 {
	 EnemyData=& referee.BLACK_GAMER;
	 SelfData= & referee.WHITE_GAMER;
	 SelfColor=WHITE_CHESSMAN;
 }
 else
 {
	 EnemyData=& referee.WHITE_GAMER;
	 SelfData= & referee.BLACK_GAMER;
	 SelfColor=BLACK_CHESSMAN;
 }
  attackPoint.grade=0;
  defendPoint.grade=0;
 srand((unsigned)time(NULL));
}
void cGobangAI::AIattack(cReferee& referee)//���������
{

  if(BLACK_CHESSMAN==SelfColor &&  0==referee.BLACK_GAMER.size())//�����������ǵ�һ����
  {
   attackPoint.x=5+rand()%6;
   attackPoint.y=5+rand()%6;
  }
  if(0!=(*SelfData).size())
  {
	vector<point>::iterator EndData=(*SelfData).end();
    point temp;
	temp.x=(*(EndData-1)).x;
	temp.y=(*(EndData-1)).y;
	for(int i=1;i<=SEARCH_RANDGE;++i)
	{
      temp.x=(*(EndData-1)).x+i;
	  temp.y=(*(EndData-1)).y;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x-i;
	  temp.y=(*(EndData-1)).y;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x;
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x;
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x-i;
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x+i;
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x-i;
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	  temp.x=(*(EndData-1)).x+i;
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      AttackCountFallPoint(temp,referee,SelfColor);
	}
  }
}
void cGobangAI::AttackCountFallPoint(const point & XY,cReferee& referee,const int& WhoGamer)//���������
{
    int x(XY.x);
	int y(XY.y);
	pointAI TopScore;
	TopScore.grade=0;
    int i(0);
	//y��
    for(x=XY.x,y=XY.y-1,i=0;y>XY.y-(4+SEARCH_RANDGE);--y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || y<1)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);//���Ӳ������Լ�������Ϊ��һ�����ӵ��ּ�10��
	}
	for(x=XY.x,y=XY.y+1,i=0;y<XY.y+(4+SEARCH_RANDGE);++y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || y>15)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}

   //x��
	for(x=XY.x-1,y=XY.y,i=0;x> XY.x-(4+SEARCH_RANDGE);--x)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x<1)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}
	for(x=XY.x+1,y=XY.y,i=0;x<XY.x+(4+SEARCH_RANDGE);++x)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x>15)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}

	//����������
    for(x=XY.x+1,y=XY.y+1,i=0;x<XY.x+(4+SEARCH_RANDGE);++x,++y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x>15 || y>15)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}
	for(x=XY.x-1,y=XY.y-1,i=0;x>XY.x-(4+SEARCH_RANDGE);--x,--y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x<1 || y<1)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}

	//����������
	for(x=XY.x+1,y=XY.y-1,i=0;x<XY.x+(4+SEARCH_RANDGE);++x,--y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x>15 || y<1)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}
	for(x=XY.x-1,y=XY.y+1,i=0;x<XY.x-(4+SEARCH_RANDGE);--x,++y)
	{
      if(referee.ChessCondition[x][y].WhoGamer!=WhoGamer && referee.ChessCondition[x][y].WhoGamer!=0 || x<1 || y>15)
	     break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
	     TopScore.grade+=(ATTACKNUM*i);
	}
	if(TopScore.grade>=attackPoint.grade)
	{
	   attackPoint.x=XY.x;
	   attackPoint.y=XY.y;
	   attackPoint.grade=TopScore.grade;
	}
}
void cGobangAI::AIdefend(cReferee& referee)//���ص����
{
 
	vector<point>::iterator EndData=(*EnemyData).end();
    point temp;
	temp.x=(*(EndData-1)).x;
	temp.y=(*(EndData-1)).y;
	for(int i=1;i<=SEARCH_RANDGE;++i)
	{
      temp.x=(*(EndData-1)).x+i;//1
	  temp.y=(*(EndData-1)).y;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x-i;//2
	  temp.y=(*(EndData-1)).y;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x;//3
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x;//4
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x-i;//5
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x+i;//6
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x-i;//7
	  temp.y=(*(EndData-1)).y+i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	  temp.x=(*(EndData-1)).x+i;//8
	  temp.y=(*(EndData-1)).y-i;
	  if((true!=referee.ChessCondition[temp.x][temp.y].YESNO) && (temp.x>=1 && temp.x<=15 && temp.y>=1 && temp.y<=15))
	      DefendCountFallPoint(temp,referee,EnemyColor);
	}
  
}
void cGobangAI::DefendCountFallPoint(const point& XY,cReferee& referee,const int& WhoGamer)//�������ӵ���
{
    int x(XY.x);
	int y(XY.y);
	pointAI TopScore;
	TopScore.grade=0;
    int i(0);
	//X��
	for(x=XY.x+1,y=XY.y,i=0;x<XY.x+(4+SEARCH_RANDGE);++x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || x>15)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	for(x=XY.x-1,y=XY.y,i=0;x>XY.x-(4+SEARCH_RANDGE);--x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || x<1)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	//Y����
	for(x=XY.x,y=XY.y+1,i=0;y<XY.y+(4+SEARCH_RANDGE);++y)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || y>15)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	for(x=XY.x,y=XY.y-1,i=0;y>XY.y-(4+SEARCH_RANDGE);--y)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || y<1)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	//����������
	for(x=XY.x-1,y=XY.y-1,i=0;y>XY.y-(4+SEARCH_RANDGE);--y,--x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || y<1 || x<1)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	for(x=XY.x+1,y=XY.y+1,i=0;y<XY.y+(4+SEARCH_RANDGE);++y,++x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || y>15 || x>15)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	//����������
	for(x=XY.x+1,y=XY.y-1,i=0;y>XY.y-(4+SEARCH_RANDGE);--y,++x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || x>15 || y<1)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	for(x=XY.x-1,y=XY.y+1,i=0;y<XY.y+(4+SEARCH_RANDGE);++y,--x)
	{
	  if(true==referee.ChessCondition[x][y].YESNO && WhoGamer!=referee.ChessCondition[x][y].WhoGamer || y>15 || x<1)
		  break;
	  ++i;
	  if(true==referee.ChessCondition[x][y].YESNO && referee.ChessCondition[x][y].WhoGamer==WhoGamer)
		  	TopScore.grade+=(DEFENDNUM*i);
	}
	if(TopScore.grade==defendPoint.grade)
	{
	 int temp;
	 temp=rand()%2;
	 if(1==temp)
	 {
	  defendPoint.grade=TopScore.grade;
	  defendPoint.x=XY.x;
	  defendPoint.y=XY.y;
	 }
	}
	if(TopScore.grade>defendPoint.grade)
	{
	 defendPoint.grade=TopScore.grade;
	 defendPoint.x=XY.x;
	 defendPoint.y=XY.y;
	}
}
bool cGobangAI::InterfaceCall( point& XY, cReferee& referee)
{
 if(BLACK_CHESSMAN==SelfColor && 0==referee.BLACK_GAMER.size())
 {
   AIattack(referee);
   XY.x=attackPoint.x;
   XY.y=attackPoint.y;
   referee.ChessCondition[XY.x][XY.y].YESNO=true;
   referee.ChessCondition[XY.x][XY.y].WhoGamer=SelfColor;
    if(BLACK_CHESSMAN==SelfColor)
	   referee.BLACK_GAMER.push_back(XY);
    if(WHITE_CHESSMAN==SelfColor)
	  referee.WHITE_GAMER.push_back(XY);
   return true;
 }
 else
 {
   AIattack(referee);
   AIdefend(referee);
   if(attackPoint.grade>defendPoint.grade)
   {
    XY.x=attackPoint.x;
	XY.y=attackPoint.y;
	referee.ChessCondition[XY.x][XY.y].YESNO=true;
	referee.ChessCondition[XY.x][XY.y].WhoGamer=SelfColor;
   }
   if(attackPoint.grade<=defendPoint.grade)
   {
    XY.x=defendPoint.x;
	XY.y=defendPoint.y;
	referee.ChessCondition[XY.x][XY.y].YESNO=true;
    referee.ChessCondition[XY.x][XY.y].WhoGamer=SelfColor;
   }
   if(BLACK_CHESSMAN==SelfColor)
	   referee.BLACK_GAMER.push_back(XY);
    if(WHITE_CHESSMAN==SelfColor)
	  referee.WHITE_GAMER.push_back(XY);
   return true;
 }
}
void cGobangAI::BasicDraw()//������ֵ�ָ��λ��
{
 if(BLACK_CHESSMAN==SelfColor)
   {
      CursorPositionGotoxy(65,5);
      cout<<"Please input point(BlackGamer):"<<flush;
      CursorPositionGotoxy(97,5);
		for(int i=0;i<10;++i)
			cout<<' ';
   }
  if(WHITE_CHESSMAN==SelfColor)
   {
      CursorPositionGotoxy(65,6);
      cout<<"Please input point(WhiteGamer):"<<flush;
	  CursorPositionGotoxy(97,6);
	  for(int i=0;i<10;++i)
			cout<<' ';
   }
}
void cGobangAI::OutPutDraw(const point & XY)
{
  attackPoint.grade=0;
  defendPoint.grade=0;
 if(BLACK_CHESSMAN==SelfColor)
   {
      CursorPositionGotoxy(97,5);
	  cout<<XY.x<<"  "<<XY.y<<flush;
   }
  if(WHITE_CHESSMAN==SelfColor)
   {
	  CursorPositionGotoxy(97,6);
	  cout<<XY.x<<"  "<<XY.y<<flush;
   }
}
