
#include  "gobangheadfile.h"

extern "C" WINBASEAPI HWND WINAPI GetConsoleWindow ();
int main()
{
 system("title Gobang");
 SetConsoleOutputCP(437);
 SetWindowPos(GetConsoleWindow(),HWND_NOTOPMOST,133,0,1000,750,SWP_SHOWWINDOW/*|SWP_NOSIZE*/);

 cChessboard cb;
 point Frame;
 bool RunSwitch(true);
 while(RunSwitch)
 {
   int modeSwitch(0);
   CursorPositionGotoxy(30,1);
   cout<<"       Please  select a game mode  :        "<<endl; 
   CursorPositionGotoxy(0,5);
   cout<<"       1.Gamer and Gamer"<<endl;
   cout<<"       2.Gamer and Computer"<<endl;
   cout<<"       3.Exit Game "<<endl;
   cout<<"Your choice is :";
   cin>>modeSwitch;
   while(modeSwitch!=1 && modeSwitch!=2 && modeSwitch!=3)
   {
    cout<<"Input error!"<<endl;
	cout<<"Your choice is :";
    cin>>modeSwitch;
   }
   if(3==modeSwitch)
	   break;
   switch(modeSwitch)
   {
   case 1://玩家与玩家对战
	   {
	    system("cls");
		cReferee refereeGaG;
		cGamer Black(BLACK_CHESSMAN);
		cGamer White(WHITE_CHESSMAN);
		cb.DrawChessboard();
		  while(refereeGaG.WinJudge()!=BLACK_CHESSMAN && refereeGaG.WinJudge()!=WHITE_CHESSMAN)
		  {
			 Black.BasicDrawing(); 
			 Black. FallChessmanGamer(Frame,cb,refereeGaG);
			 if(refereeGaG.JudgeWhoSuccess(Frame,BLACK_CHESSMAN))
				 break;
			 White.BasicDrawing(); 
			 White.FallChessmanGamer(Frame,cb,refereeGaG);
			 if(refereeGaG.JudgeWhoSuccess(Frame,WHITE_CHESSMAN))
				 break;
		  }
		  system("cls");
		  CursorPositionGotoxy(37,10);
		  if(BLACK_CHESSMAN==refereeGaG.WinJudge())
			  cout<<"BLACK_GAMER WIN!!"<<endl;
		  if(WHITE_CHESSMAN==refereeGaG.WinJudge())
			  cout<<"WHITE_GAMER WIN!!"<<endl;
		  Sleep(2000);
	   }
	   break;
   case 2:
	   {
	     system("cls");
		 int Lived(0);
		 CursorPositionGotoxy(30,1);
         cout<<"        Please select who lived :        "<<endl; 
         CursorPositionGotoxy(0,5);
         cout<<"       1.You"<<endl;
         cout<<"       2.Computer"<<endl;
         cout<<"Your choice is :";
		 cin>>Lived;
		 while(Lived !=1 && Lived!=2)
		 {
		  cout<<"INPUT ERROR!"<<endl;
		  cout<<"Your choice is :";
		  cin>>Lived;
		 }
		 switch(Lived)
		 {
		 case 1:
			 {
			  system("cls");
	          cReferee refereeGaA;
		      cGamer Black(BLACK_CHESSMAN);
		      cGobangAI White(BLACK_CHESSMAN,refereeGaA);
		      cb.DrawChessboard();
              while(refereeGaA.WinJudge()!=BLACK_CHESSMAN && refereeGaA.WinJudge()!=WHITE_CHESSMAN)
			  {
			   Black.BasicDrawing(); 
			   Black.FallChessmanGamer(Frame,cb,refereeGaA);
			   if(refereeGaA.JudgeWhoSuccess(Frame,BLACK_CHESSMAN))
				 break;
			   White.BasicDraw();
			   White.InterfaceCall(Frame,refereeGaA);
			   White.OutPutDraw(Frame);
			   cb.FallChessman(Frame,WHITE_CHESSMAN);
			   if(refereeGaA.JudgeWhoSuccess(Frame,WHITE_CHESSMAN))
				 break;
			  }
			system("cls");
		    CursorPositionGotoxy(37,10);
		    if(BLACK_CHESSMAN==refereeGaA.WinJudge())
			  cout<<"HAPPY! YOU WIN!!"<<endl;
		    if(WHITE_CHESSMAN==refereeGaA.WinJudge())
			  cout<<"SAD!   AI  WIN!!"<<endl;
		    Sleep(2000);
			 }
			 break;
		 case 2:
			 {
			  system("cls");
	          cReferee refereeGaA;
		      cGamer White(WHITE_CHESSMAN);
		      cGobangAI Black(WHITE_CHESSMAN,refereeGaA);
		      cb.DrawChessboard();
              while(refereeGaA.WinJudge()!=BLACK_CHESSMAN && refereeGaA.WinJudge()!=WHITE_CHESSMAN)
			  {
			   Black.BasicDraw();
			   Black.InterfaceCall(Frame,refereeGaA);
			   Black.OutPutDraw(Frame);
			   cb.FallChessman(Frame,BLACK_CHESSMAN);
			   if(refereeGaA.JudgeWhoSuccess(Frame,BLACK_CHESSMAN))
				 break;
			   White.BasicDrawing(); 
			   White.FallChessmanGamer(Frame,cb,refereeGaA);
			   if(refereeGaA.JudgeWhoSuccess(Frame,WHITE_CHESSMAN))
				 break;			  
			  }
			system("cls");
		    CursorPositionGotoxy(37,10);
		    if(BLACK_CHESSMAN==refereeGaA.WinJudge())
			 cout<<"SAD!   AI  WIN!!"<<endl;
		    if(WHITE_CHESSMAN==refereeGaA.WinJudge())
			  cout<<"HAPPY! YOU WIN!!"<<endl;
		    Sleep(2000);
			 }
			 break;
		  default:
			  break;
		 }
	   }
	   break;
   }
 }
 
 return 0;
}