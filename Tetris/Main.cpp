#include<iostream>
#include<windows.h>
#include<ctime>
#include<conio.h>
using namespace std;
typedef  struct Coordinate
{
	int Pos_X;
	int Pos_Y;
} coor;
const int GameOperatorPoolSize_X = 30;
const int GameOperatorPoolSize_Y = 30;
const int GameShowPoolSize_X = 5;
const int GameShowPoolSize_Y = 5;
const WCHAR BLOCK_ICON = (WCHAR)30;
const int BLOCK_GROUP_SIZE = 4;
const int GroupLibrary_NUM = 7;
const  coor GroupLibrary[GroupLibrary_NUM][BLOCK_GROUP_SIZE] = {
	{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 2, 1 } }, //反L型
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 2, 1 } }, //L型
{ { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } }, //正方形
{ { 0, 0 },{ 1, 0 },{ 1, 1 },{ 2, 1 } },  //Z型
{ { 0, 0 },{ 0, 1 },{ 1, 1 },{ 1, 2 } }, //反Z型
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 } }, //直线型
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 1, 1 } }  //十字去下型
};
coor  rotateArithmetic(const coor & RotatePoint, const coor & Center, int direction)
{
	coor TempVar = RotatePoint;
	coor Rotated = { 0, 0 };
	TempVar.Pos_X -= Center.Pos_X;
	TempVar.Pos_Y -= Center.Pos_Y;
	if (0 == direction)//顺时针
	{
		Rotated.Pos_X = TempVar.Pos_Y + Center.Pos_X;
		Rotated.Pos_Y = (-TempVar.Pos_X + Center.Pos_Y);
	}
	if (1 == direction)//逆时针
	{
		Rotated.Pos_X = (-TempVar.Pos_Y + Center.Pos_X);
		Rotated.Pos_Y = TempVar.Pos_X + Center.Pos_Y;
	}
	return Rotated;
}
class CGamePool//游戏池类
{
public:
	friend class COperators;
	CGamePool(const int & iData_x, const int & iData_y);
	~CGamePool();
	bool PrintfOuterFrame(const int&  iFrameLength_X, const int&  iFrameLength_Y, const int & iFramePos_X, const int & iFramePos_Y);//打印外框架
	bool SetCursorPosition(const int & X, const int  & Y); //设置光标位置
	bool PrintfData(const int & X, const int Y);//打印数据
	bool EmptyData();//排空数据

private:
	WCHAR * *pData;
	HANDLE OutPutBuffer;
	int iData_X, iData_Y;
	int iDataPos_X, iDataPos_Y;
	int iOuterFrameTopLeft_X, iOuterFrameTopLeft_Y;
	int  iOuterFrameLength_X, iOuterFrameLength_Y;
};
/******************游戏池类函数实现  begin***************/
bool   CGamePool::EmptyData()//排空数据
{
	for (int i(0); i < iData_X; ++i)
	{
		for (int j(0); j < iData_Y; ++j)
		{
			pData[i][j] = ' ';
		}
	}
	return true;
}
CGamePool:: ~CGamePool()
{
	for (int i(0); i < iData_X; ++i)
		delete[] pData[i];
	delete[] pData;
	pData = NULL;
}
bool CGamePool::PrintfData(const int & X, const int Y)
{
	iDataPos_X = X; iDataPos_Y = Y;
	DWORD Wirttenlength = 0;
	for (int i(0); i < iData_X; ++i)
	{
		if (!SetCursorPosition(X, Y + i))
			return false;
		WriteConsoleW(OutPutBuffer, pData[i], iData_X, &Wirttenlength, NULL);
		cout << endl;
	}
	return true;
}
CGamePool::CGamePool(const int & iData_x, const int & iData_y)
{
	pData = new WCHAR*[iData_x];
	for (int i(0); i < iData_x; ++i)
		pData[i] = new WCHAR[iData_y];
	for (int i(0); i < iData_x; ++i)
		for (int j(0); j < iData_y; ++j)
			pData[i][j] = ' ';
	iData_X = iData_x;
	iData_Y = iData_y;
	OutPutBuffer = GetStdHandle(STD_OUTPUT_HANDLE);
	iOuterFrameTopLeft_X = 0; iOuterFrameTopLeft_Y = 0;
	iOuterFrameLength_X = 0; iOuterFrameLength_Y = 0;
}
bool CGamePool::SetCursorPosition(const int & X, const int  & Y)
{
	COORD pos;
	pos.X = X; pos.Y = Y;
	if (SetConsoleCursorPosition(OutPutBuffer, pos))
		return true;
	else
		return false;
}
bool CGamePool::PrintfOuterFrame(const int&  iFrameLength_X, const int&  iFrameLength_Y, const int & iFramePos_X, const int & iFramePos_Y)
{
	if (0 >= iFrameLength_X || 0 >= iFrameLength_Y)
		return false;
	iOuterFrameTopLeft_X = iFramePos_X;
	iOuterFrameTopLeft_Y = iFramePos_Y;
	iOuterFrameLength_X = iFrameLength_X;
	iOuterFrameLength_Y = iFrameLength_Y;
	char temp = ' ';
	for (int i(1); i <= iFrameLength_X; ++i)
	{
		if (!SetCursorPosition(iFramePos_X, iFramePos_Y + (i - 1)))
			return false;
		for (int j(1); j <= iFrameLength_Y; ++j)
		{
			if (1 == i)
			{
				if (1 == j)
					temp = char(201);
				else
				{
					if (iFrameLength_Y == j)
						temp = char(187);
					else
						temp = char(205);
				}
			}
			if (iFrameLength_X == i)
			{
				if (1 == j)
					temp = (char)200;
				else
				{
					if (iFrameLength_Y == j)
						temp = (char)188;
					else
						temp = (char)205;
				}
			}
			if ((i != 1 && i != iFrameLength_X) && (j == 1 || j == iFrameLength_Y))
				temp = (char)186;
			cout << temp;
			temp = ' ';
		}
		cout << endl;
	}
	return true;
}
/******************游戏池类函数实现  end***************/

class  CBlocks  //方块类
{
private:
	coor pos;
	WCHAR ICON;
public:
	friend class COperators;
	CBlocks();
	bool AlterPos(const coor& POS); //修改方块的坐标
	coor ReturnPos();  //返回方块的坐标
	bool AlterIcon(const WCHAR &);//修改方块图标
};
/******************方块类函数实现 begin***********************/
bool  CBlocks::AlterIcon(const WCHAR & icon)//修改方块图标
{
	ICON = icon;
	return true;
}
coor CBlocks::ReturnPos()
{
	return pos;
}
inline bool  CBlocks::AlterPos(const coor& POS)
{
	pos.Pos_X = POS.Pos_X;
	pos.Pos_Y = POS.Pos_Y;
	return true;
}
CBlocks::CBlocks()
{
	pos.Pos_X = 0;
	pos.Pos_Y = 0;
	ICON = BLOCK_ICON;
}
/************** 方块类函数实现 end*******/

class COperators   //操作员类
{
private:
	CBlocks  BlockGroup[2][BLOCK_GROUP_SIZE];   //0  被操作的方块组合  1 被展示的方块组合
	coor BlockGroupType[2][BLOCK_GROUP_SIZE];//0 被操作的方块组合类型  1  被展示的方块组合类型
public:
	COperators();
	bool TransferBlocks(const short & GamePoolBlockGroupTpye1, const short & GamePoolBlockGroupTpye2, const CGamePool & OperatorPool, const CGamePool & ShowPool);//将展示台的方块组合移动到操作台,并且展示台生成新的方块组合
	bool CollisionDetection(const CGamePool & OperatorPool, const bool & Left, const bool & Right, const bool & Down, const bool & up);//碰撞检测
	bool  LeftShiftCBlocks(const CGamePool & OperatorPool);//左移方块组合
	bool RightShiftCBlocks(const CGamePool & OperatorPool);//右移方块组合
	bool DownShiftCBlocks(const CGamePool & OperatorPool);//下移方块组合
	bool RotateCBlocks(const CGamePool & OperatorPool, int direction);//旋转方块组合
	bool  WriteGamePool(CGamePool & OperatorPool);//把方块组合的数据写入游戏池
	bool PrintfBlocksGroup(CGamePool & OperatorPool, const int & ShowOROperator);//打印方块组合
	int RemoveLine(CGamePool & OperatorPool);//消行
};
/***********操作员类函数实现 begin****/
bool COperators::RotateCBlocks(const CGamePool & OperatorPool, int direction)
{
	coor Center = { 0, 0 };
	coor TempVar[BLOCK_GROUP_SIZE];
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		Center.Pos_X += BlockGroup[0][i].pos.Pos_X;
		Center.Pos_Y += BlockGroup[0][i].pos.Pos_Y;
	}
	Center.Pos_X /= BLOCK_GROUP_SIZE; //精度
	Center.Pos_Y /= BLOCK_GROUP_SIZE;
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		TempVar[i] = BlockGroup[0][i].pos;
		BlockGroup[0][i].pos = rotateArithmetic(BlockGroup[0][i].pos, Center, direction);
	}
	if (false == CollisionDetection(OperatorPool, true, true, true, true))
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
			BlockGroup[0][i].pos = TempVar[i];
		return false;
	}
	return true;
}
int COperators::RemoveLine(CGamePool & OperatorPool)//消行
{
	int FullLineNum(0);
	int Score(0);
	int NotNullCount(0);
	int i(OperatorPool.iData_X - 1);
	for (; i >= 0; --i)
	{
		for (int j(0); j < OperatorPool.iData_Y; ++j)
		{
			if (OperatorPool.pData[i][j] != ' ')
				++NotNullCount;
		}
		if (OperatorPool.iData_Y == NotNullCount)
		{
			Score += 1 * (++FullLineNum);
			for (; NotNullCount>(-1); --NotNullCount)
				OperatorPool.pData[i][NotNullCount] = ' ';
		}
		else
		{
			if (FullLineNum > 0)
				break;
			NotNullCount = 0;
		}
	}
	if (0 == Score)
		return Score;
	for (int i1(i); i1> 0; --i1)
	{
		for (int j(0); j < OperatorPool.iData_Y; ++j)
		{
			if (OperatorPool.pData[i1][j] != ' ')
			{
				OperatorPool.pData[i1 + FullLineNum][j] = BLOCK_ICON;
				OperatorPool.pData[i1][j] = ' ';
			}
		}
	}
	return Score;
}
bool COperators::PrintfBlocksGroup(CGamePool & OperatorPool, const int & ShowOROperator)//打印方块组合
{
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		OperatorPool.SetCursorPosition(OperatorPool.iDataPos_X + BlockGroup[ShowOROperator][i].pos.Pos_X, OperatorPool.iDataPos_Y + BlockGroup[ShowOROperator][i].pos.Pos_Y);
		cout << char(BlockGroup[ShowOROperator][i].ICON);
	}
	return true;
}
bool  COperators::WriteGamePool(CGamePool & OperatorPool)//把方块组合的数据写入游戏池
{
	if (!OperatorPool.pData)
		return false;
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
		OperatorPool.pData[BlockGroup[0][i].pos.Pos_Y][BlockGroup[0][i].pos.Pos_X] = BlockGroup[0][i].ICON;
	return true;
}
bool RotateCBlocks(const CGamePool & OperatorPool)
{
	return true;
}
bool  COperators::LeftShiftCBlocks(const CGamePool & OperatorPool)//左移方块组合
{
	if (true == CollisionDetection(OperatorPool, true, false, false, false))
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
			BlockGroup[0][i].pos.Pos_X -= 1;
		return true;
	}
	else
		return false;
}
bool  COperators::RightShiftCBlocks(const CGamePool & OperatorPool)//右移方块组合
{
	if (true == CollisionDetection(OperatorPool, false, true, false, false))
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
			BlockGroup[0][i].pos.Pos_X += 1;
		return true;
	}
	else
		return false;
}
bool  COperators::DownShiftCBlocks(const CGamePool & OperatorPool)//下移方块组合
{
	if (true == CollisionDetection(OperatorPool, false, false, true, false))
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
			BlockGroup[0][i].pos.Pos_Y += 1;
		return true;
	}
	else
		return false;
}
bool COperators::CollisionDetection(const CGamePool & OperatorPool, const bool & Left, const bool & Right, const bool & Down, const bool & up)//碰撞检测
{
	if (Left == false && false == Right && false == Down && false == up)
		return false;
	if (true == Left)
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
		{
			if ((BlockGroup[0][i].pos.Pos_X - 1) < 0 || (OperatorPool.pData[BlockGroup[0][i].pos.Pos_Y][BlockGroup[0][i].pos.Pos_X - 1] != ' '))
				return false;
		}
	}
	if (true == Right)
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
		{
			if ((BlockGroup[0][i].pos.Pos_X + 1) >(OperatorPool.iData_Y - 1) || (OperatorPool.pData[BlockGroup[0][i].pos.Pos_Y][BlockGroup[0][i].pos.Pos_X + 1] != ' '))
				return false;
		}
	}
	if (true == up)
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
		{
			if ((BlockGroup[0][i].pos.Pos_Y - 1) < 0 || (OperatorPool.pData[BlockGroup[0][i].pos.Pos_Y - 1][BlockGroup[0][i].pos.Pos_X] != ' '))
				return false;
		}
	}
	if (true == Down)
	{
		for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
		{
			if ((BlockGroup[0][i].pos.Pos_Y + 1)  >(OperatorPool.iData_X - 1) || (OperatorPool.pData[BlockGroup[0][i].pos.Pos_Y + 1][BlockGroup[0][i].pos.Pos_X] != ' '))
			{
				return false;
			}
		}
	}
	return true;
}
bool COperators::TransferBlocks(const short &  GamePoolBlockGroupTpye1, const short &  GamePoolBlockGroupTpye2, const CGamePool & OperatorPool, const CGamePool & ShowPool)
{
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)    //把后者的方块组合类型给前者 
	{
		BlockGroupType[GamePoolBlockGroupTpye1][i].Pos_X = BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_X;
		BlockGroupType[GamePoolBlockGroupTpye1][i].Pos_Y = BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_Y;
		if (0 == i)
		{
			BlockGroup[GamePoolBlockGroupTpye1][i].pos.Pos_X = 2 + rand() % (OperatorPool.iData_X / 2);
			BlockGroup[GamePoolBlockGroupTpye1][i].pos.Pos_Y = 0;
		}
		else
		{
			BlockGroup[GamePoolBlockGroupTpye1][i].pos.Pos_X = BlockGroup[GamePoolBlockGroupTpye1][0].pos.Pos_X + BlockGroupType[GamePoolBlockGroupTpye1][i].Pos_X;
			BlockGroup[GamePoolBlockGroupTpye1][i].pos.Pos_Y = BlockGroup[GamePoolBlockGroupTpye1][0].pos.Pos_Y + BlockGroupType[GamePoolBlockGroupTpye1][i].Pos_Y;
		}
	}
	int GroupTpye = rand() % GroupLibrary_NUM;		//给后者随即生成一个新的方块组合类型
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_X = GroupLibrary[GroupTpye][i].Pos_X;
		BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_Y = GroupLibrary[GroupTpye][i].Pos_Y;
		if (0 == i)
		{
			BlockGroup[GamePoolBlockGroupTpye2][i].pos.Pos_X = (ShowPool.iData_X / 2) - 1;
			BlockGroup[GamePoolBlockGroupTpye2][i].pos.Pos_Y = (ShowPool.iData_Y / 2) - 1;
		}
		else
		{
			BlockGroup[GamePoolBlockGroupTpye2][i].pos.Pos_X = BlockGroup[GamePoolBlockGroupTpye2][0].pos.Pos_X + BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_X;
			BlockGroup[GamePoolBlockGroupTpye2][i].pos.Pos_Y = BlockGroup[GamePoolBlockGroupTpye2][0].pos.Pos_Y + BlockGroupType[GamePoolBlockGroupTpye2][i].Pos_Y;
		}
	}
	return true;
}
COperators::COperators()
{
	srand((unsigned  int)time(NULL));
	for (int i(0); i < 2; ++i)
	{
		for (int j(0); j < BLOCK_GROUP_SIZE; ++j)
		{
			BlockGroupType[i][j].Pos_X = 0;
			BlockGroupType[i][j].Pos_Y = 0;
		}
	}
	int GroupType = rand() % GroupLibrary_NUM;                                                       //
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)                                                                 //    初始化放入游戏展示池的方块组合类型
	{																																   //	                                		
		BlockGroupType[1][i].Pos_X = GroupLibrary[GroupType][i].Pos_X;                   //
		BlockGroupType[1][i].Pos_Y = GroupLibrary[GroupType][i].Pos_Y;                   // 
	}
}
/***********操作员类函数实现 end****/
class CGamer  //玩家类的实现
{
public:
	CGamer(const int & iOperatorSizeX, const int & iOperatorSizeY, const int & ShowPoolSizeX, const int & ShowPoolSizeY, const coor & OperatorPoolPos, const coor & ShowPoolPos);//
	bool Ready();//游戏准备
	bool PrintfDraw(const int & State);//打印画面
	bool RunGame();//游戏运行
	bool GamerOrder(const char & Order);//玩家指令
private:
	CGamePool OperatorPool, ShowPool;  //一个玩家会有两个游戏池，一个操作员为其服务,玩家不参与对游戏池的直接操作，	                                                              
	COperators Operators;                          //      只需对操作员发出指令,操作员参与对游戏池的直接操作
	coor  OperatorPoolPos, ShowPoolPos;
	int OperatorPoolSizeX, OperatorPoolSizeY, ShowPoolX, ShowPoolY;
	bool Dead;
	int GamerScore;
};
/***************玩家类函数实现begin*****************/
bool CGamer::PrintfDraw(const int & State)
{
	if (2 <= State)
	{
		OperatorPool.PrintfOuterFrame(OperatorPoolSizeX + 2, OperatorPoolSizeY + 2, OperatorPoolPos.Pos_X, OperatorPoolPos.Pos_Y);
		ShowPool.PrintfOuterFrame(ShowPoolX + 2, ShowPoolY + 2, ShowPoolPos.Pos_X, ShowPoolPos.Pos_Y);
	}
	if (1 <= State)
	{
		Operators.TransferBlocks(0, 1, OperatorPool, ShowPool);
		ShowPool.PrintfData(ShowPoolPos.Pos_X + 1, ShowPoolPos.Pos_Y + 1);
		Operators.PrintfBlocksGroup(ShowPool, 1);
	}
	if (0 <= State)
	{
		OperatorPool.PrintfData(OperatorPoolPos.Pos_X + 1, OperatorPoolPos.Pos_Y + 1);
		Operators.PrintfBlocksGroup(OperatorPool, 0);
	}
	return true;
}
bool CGamer::RunGame()
{
	Ready();
	char Order = ' ';
	clock_t LastTime = clock();
	clock_t Nowtime = 0;
	while (true)
	{
		if (_kbhit())
		{
			Order = _getch();
			if (true == GamerOrder(Order))
			{
				PrintfDraw(0);
			}
			else
			{
				Operators.WriteGamePool(OperatorPool);
				Operators.RemoveLine(OperatorPool);
				PrintfDraw(1);
			}
		}
		Nowtime = clock();
		Sleep(1);
		if (Nowtime - LastTime > 450)
		{
			if (true == GamerOrder('s'))
				PrintfDraw(0);
			else
			{
				Operators.WriteGamePool(OperatorPool);
				Operators.RemoveLine(OperatorPool);
				PrintfDraw(1);
			}
			LastTime = Nowtime;
		}
	}
}
bool CGamer::GamerOrder(const char & Order)//玩家指令
{
	switch (int(Order))
	{
	case 'w':case 'W':case '8':case 72: //上  
		Operators.RotateCBlocks(OperatorPool, 0);
		break;
	case 's':case 'S':case '2':case 80://下
		if (false == Operators.DownShiftCBlocks(OperatorPool))
			return false;
		break;
	case 'a':case 'A':case '4':case 75://左
		Operators.LeftShiftCBlocks(OperatorPool);
		break;
	case 'd':case 'D':case '6':case 77://右
		Operators.RightShiftCBlocks(OperatorPool);
		break;
	default:
		;
		break;
	}
	return true;
}
bool CGamer::Ready()//准备工作
{
	OperatorPool.PrintfOuterFrame(OperatorPoolSizeX + 2, OperatorPoolSizeY + 2, OperatorPoolPos.Pos_X, OperatorPoolPos.Pos_Y);
	ShowPool.PrintfOuterFrame(ShowPoolX + 2, ShowPoolY + 2, ShowPoolPos.Pos_X, ShowPoolPos.Pos_Y);
	OperatorPool.PrintfData(OperatorPoolPos.Pos_X + 1, OperatorPoolPos.Pos_Y + 1);
	ShowPool.PrintfData(ShowPoolPos.Pos_X + 1, ShowPoolPos.Pos_Y + 1);
	Operators.TransferBlocks(0, 1, OperatorPool, ShowPool);
	Operators.PrintfBlocksGroup(OperatorPool, 0);
	Operators.PrintfBlocksGroup(ShowPool, 1);
	return true;
}
CGamer::CGamer(const int & iOperatorSizeX, const int & iOperatorSizeY, const int & ShowPoolSizeX,
	const int & ShowPoolSizeY, const coor & OperatorPoolPos, const coor & ShowPoolPos) :OperatorPool(iOperatorSizeX, iOperatorSizeY), ShowPool(ShowPoolSizeX, ShowPoolSizeY)
{
	this->OperatorPoolPos.Pos_X = OperatorPoolPos.Pos_X;
	this->OperatorPoolPos.Pos_Y = OperatorPoolPos.Pos_Y;
	this->ShowPoolPos.Pos_X = ShowPoolPos.Pos_X;
	this->ShowPoolPos.Pos_Y = ShowPoolPos.Pos_Y;
	OperatorPoolSizeX = iOperatorSizeX;
	OperatorPoolSizeY = iOperatorSizeY;
	ShowPoolX = ShowPoolSizeX;
	ShowPoolY = ShowPoolSizeY;
	Dead = false;
	GamerScore = 0;
}
/***************玩家类函数实现end*******************/

int main()
{
	HANDLE g_hConsoleOutput;
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // 光标信息
	SetConsoleOutputCP(437);
	g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // 获取控制台输出句柄
	SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // 设置光标隐藏
	coor Opos = { 0, 0 }, Spos = { 23,0 };
	CGamer My(20, 20, 10, 10, Opos, Spos);
	My.Ready();
	My.RunGame();
	return 0;
}