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
	{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 2, 1 } }, //��L��
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 2, 1 } }, //L��
{ { 0, 0 },{ 1, 0 },{ 0, 1 },{ 1, 1 } }, //������
{ { 0, 0 },{ 1, 0 },{ 1, 1 },{ 2, 1 } },  //Z��
{ { 0, 0 },{ 0, 1 },{ 1, 1 },{ 1, 2 } }, //��Z��
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 } }, //ֱ����
{ { 0, 0 },{ 1, 0 },{ 2, 0 },{ 1, 1 } }  //ʮ��ȥ����
};
coor  rotateArithmetic(const coor & RotatePoint, const coor & Center, int direction)
{
	coor TempVar = RotatePoint;
	coor Rotated = { 0, 0 };
	TempVar.Pos_X -= Center.Pos_X;
	TempVar.Pos_Y -= Center.Pos_Y;
	if (0 == direction)//˳ʱ��
	{
		Rotated.Pos_X = TempVar.Pos_Y + Center.Pos_X;
		Rotated.Pos_Y = (-TempVar.Pos_X + Center.Pos_Y);
	}
	if (1 == direction)//��ʱ��
	{
		Rotated.Pos_X = (-TempVar.Pos_Y + Center.Pos_X);
		Rotated.Pos_Y = TempVar.Pos_X + Center.Pos_Y;
	}
	return Rotated;
}
class CGamePool//��Ϸ����
{
public:
	friend class COperators;
	CGamePool(const int & iData_x, const int & iData_y);
	~CGamePool();
	bool PrintfOuterFrame(const int&  iFrameLength_X, const int&  iFrameLength_Y, const int & iFramePos_X, const int & iFramePos_Y);//��ӡ����
	bool SetCursorPosition(const int & X, const int  & Y); //���ù��λ��
	bool PrintfData(const int & X, const int Y);//��ӡ����
	bool EmptyData();//�ſ�����

private:
	WCHAR * *pData;
	HANDLE OutPutBuffer;
	int iData_X, iData_Y;
	int iDataPos_X, iDataPos_Y;
	int iOuterFrameTopLeft_X, iOuterFrameTopLeft_Y;
	int  iOuterFrameLength_X, iOuterFrameLength_Y;
};
/******************��Ϸ���ຯ��ʵ��  begin***************/
bool   CGamePool::EmptyData()//�ſ�����
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
/******************��Ϸ���ຯ��ʵ��  end***************/

class  CBlocks  //������
{
private:
	coor pos;
	WCHAR ICON;
public:
	friend class COperators;
	CBlocks();
	bool AlterPos(const coor& POS); //�޸ķ��������
	coor ReturnPos();  //���ط��������
	bool AlterIcon(const WCHAR &);//�޸ķ���ͼ��
};
/******************�����ຯ��ʵ�� begin***********************/
bool  CBlocks::AlterIcon(const WCHAR & icon)//�޸ķ���ͼ��
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
/************** �����ຯ��ʵ�� end*******/

class COperators   //����Ա��
{
private:
	CBlocks  BlockGroup[2][BLOCK_GROUP_SIZE];   //0  �������ķ������  1 ��չʾ�ķ������
	coor BlockGroupType[2][BLOCK_GROUP_SIZE];//0 �������ķ����������  1  ��չʾ�ķ����������
public:
	COperators();
	bool TransferBlocks(const short & GamePoolBlockGroupTpye1, const short & GamePoolBlockGroupTpye2, const CGamePool & OperatorPool, const CGamePool & ShowPool);//��չʾ̨�ķ�������ƶ�������̨,����չʾ̨�����µķ������
	bool CollisionDetection(const CGamePool & OperatorPool, const bool & Left, const bool & Right, const bool & Down, const bool & up);//��ײ���
	bool  LeftShiftCBlocks(const CGamePool & OperatorPool);//���Ʒ������
	bool RightShiftCBlocks(const CGamePool & OperatorPool);//���Ʒ������
	bool DownShiftCBlocks(const CGamePool & OperatorPool);//���Ʒ������
	bool RotateCBlocks(const CGamePool & OperatorPool, int direction);//��ת�������
	bool  WriteGamePool(CGamePool & OperatorPool);//�ѷ�����ϵ�����д����Ϸ��
	bool PrintfBlocksGroup(CGamePool & OperatorPool, const int & ShowOROperator);//��ӡ�������
	int RemoveLine(CGamePool & OperatorPool);//����
};
/***********����Ա�ຯ��ʵ�� begin****/
bool COperators::RotateCBlocks(const CGamePool & OperatorPool, int direction)
{
	coor Center = { 0, 0 };
	coor TempVar[BLOCK_GROUP_SIZE];
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		Center.Pos_X += BlockGroup[0][i].pos.Pos_X;
		Center.Pos_Y += BlockGroup[0][i].pos.Pos_Y;
	}
	Center.Pos_X /= BLOCK_GROUP_SIZE; //����
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
int COperators::RemoveLine(CGamePool & OperatorPool)//����
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
bool COperators::PrintfBlocksGroup(CGamePool & OperatorPool, const int & ShowOROperator)//��ӡ�������
{
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)
	{
		OperatorPool.SetCursorPosition(OperatorPool.iDataPos_X + BlockGroup[ShowOROperator][i].pos.Pos_X, OperatorPool.iDataPos_Y + BlockGroup[ShowOROperator][i].pos.Pos_Y);
		cout << char(BlockGroup[ShowOROperator][i].ICON);
	}
	return true;
}
bool  COperators::WriteGamePool(CGamePool & OperatorPool)//�ѷ�����ϵ�����д����Ϸ��
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
bool  COperators::LeftShiftCBlocks(const CGamePool & OperatorPool)//���Ʒ������
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
bool  COperators::RightShiftCBlocks(const CGamePool & OperatorPool)//���Ʒ������
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
bool  COperators::DownShiftCBlocks(const CGamePool & OperatorPool)//���Ʒ������
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
bool COperators::CollisionDetection(const CGamePool & OperatorPool, const bool & Left, const bool & Right, const bool & Down, const bool & up)//��ײ���
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
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)    //�Ѻ��ߵķ���������͸�ǰ�� 
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
	int GroupTpye = rand() % GroupLibrary_NUM;		//�������漴����һ���µķ����������
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
	for (int i(0); i < BLOCK_GROUP_SIZE; ++i)                                                                 //    ��ʼ��������Ϸչʾ�صķ����������
	{																																   //	                                		
		BlockGroupType[1][i].Pos_X = GroupLibrary[GroupType][i].Pos_X;                   //
		BlockGroupType[1][i].Pos_Y = GroupLibrary[GroupType][i].Pos_Y;                   // 
	}
}
/***********����Ա�ຯ��ʵ�� end****/
class CGamer  //������ʵ��
{
public:
	CGamer(const int & iOperatorSizeX, const int & iOperatorSizeY, const int & ShowPoolSizeX, const int & ShowPoolSizeY, const coor & OperatorPoolPos, const coor & ShowPoolPos);//
	bool Ready();//��Ϸ׼��
	bool PrintfDraw(const int & State);//��ӡ����
	bool RunGame();//��Ϸ����
	bool GamerOrder(const char & Order);//���ָ��
private:
	CGamePool OperatorPool, ShowPool;  //һ����һ���������Ϸ�أ�һ������ԱΪ�����,��Ҳ��������Ϸ�ص�ֱ�Ӳ�����	                                                              
	COperators Operators;                          //      ֻ��Բ���Ա����ָ��,����Ա�������Ϸ�ص�ֱ�Ӳ���
	coor  OperatorPoolPos, ShowPoolPos;
	int OperatorPoolSizeX, OperatorPoolSizeY, ShowPoolX, ShowPoolY;
	bool Dead;
	int GamerScore;
};
/***************����ຯ��ʵ��begin*****************/
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
bool CGamer::GamerOrder(const char & Order)//���ָ��
{
	switch (int(Order))
	{
	case 'w':case 'W':case '8':case 72: //��  
		Operators.RotateCBlocks(OperatorPool, 0);
		break;
	case 's':case 'S':case '2':case 80://��
		if (false == Operators.DownShiftCBlocks(OperatorPool))
			return false;
		break;
	case 'a':case 'A':case '4':case 75://��
		Operators.LeftShiftCBlocks(OperatorPool);
		break;
	case 'd':case 'D':case '6':case 77://��
		Operators.RightShiftCBlocks(OperatorPool);
		break;
	default:
		;
		break;
	}
	return true;
}
bool CGamer::Ready()//׼������
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
/***************����ຯ��ʵ��end*******************/

int main()
{
	HANDLE g_hConsoleOutput;
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ
	SetConsoleOutputCP(437);
	g_hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);  // ��ȡ����̨������
	SetConsoleCursorInfo(g_hConsoleOutput, &cursorInfo);  // ���ù������
	coor Opos = { 0, 0 }, Spos = { 23,0 };
	CGamer My(20, 20, 10, 10, Opos, Spos);
	My.Ready();
	My.RunGame();
	return 0;
}