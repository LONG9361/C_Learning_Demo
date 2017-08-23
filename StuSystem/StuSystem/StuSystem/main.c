#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//学生节点
typedef struct _STU
{
	char arrSTUNum[10];
	char arrSTUName[10];
	int iSTUScore;
	struct _STU* pNext;
} STUNODE;

//声明链表的头和尾
STUNODE* g_pHead = NULL;
STUNODE* g_pEnd = NULL;

//添加一个学生信息
void AddStuMSG(char* arrSTUNum, char* arrSTUName, int iSTUScore);
void AddStuMSG_2(char* arrSTUNum, char* arrSTUName, int iSTUScore);
void AddStuMSG_3(STUNODE* pTemp, char* arrSTUNum, char* arrSTUName, int iSTUScore);

//通过学号查找指定学生信息
STUNODE* FindStuMSGBy_arrSTUNum(char* arrStuNum);

//清空链表
void FreeLinkData();

//显示所有学生信息
void ShowAllStuData();

//显示指定学生信息
void ShowSpecificStuData(STUNODE* pTemp);

//显示指令
void ShowOrder();

//插入
void InsertData(STUNODE* pNewTemp, STUNODE* pTemp);

//修改指定学生信息
void ModifySpecificStuData(STUNODE* pTemp, char* arrStuNum, char* arrSTUName, int iSTUScore);

//删除指定学生信息
void DeleteSpecificStuData(STUNODE* pTemp);

//保存学生信息至文件
void SaveStuDataToFile();

//读取文件信息
void ReadStuDataFromSpecificFile();

int main(void)
{
	int iOrder = -1;//初始化

	char arrSTUNum[10] = { '\0' };
	char arrSTUName[10] = { '\0' };
	int iSTUScore = 0;
	int iFlag = 1;

	ReadStuDataFromSpecificFile("StuInfo.txt");

	//显示指令
	ShowOrder();

	while (iFlag)
	{
		printf("提示：输入10查看指令\n");
		printf("请输入指令：\n");
		scanf("%d", &iOrder);
		switch (iOrder)
		{
		case 0:
			iFlag = 0;
			break;
		case 1:
			//添加一个学生的信息（尾添加）
			printf("输入学号：");
			scanf("%s", arrSTUNum);
			printf("输入姓名：");
			scanf("%s", arrSTUName);
			printf("输入分数：");
			scanf("%d", &iSTUScore);
			AddStuMSG(arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 2:
			//查找学生信息(学号)
			printf("输入需要查找信息的学生的学号：\n");
			scanf("%s", arrSTUNum);
			ShowSpecificStuData(FindStuMSGBy_arrSTUNum(arrSTUNum));
			break;
		case 3:
			//修改指定学生信息（学号）
			printf("输入需要修改 信息的学生的学号：\n");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp3 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			printf("输入学号：");
			scanf("%s", arrSTUNum);
			printf("输入姓名：");
			scanf("%s", arrSTUName);
			printf("输入分数：");
			scanf("%d", &iSTUScore);
			ModifySpecificStuData(pTemp3, arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 4:
			//保存学生信息至文件
			SaveStuDataToFile();
			break;
		case 6:
			//删除指定学生信息
			printf("输入需要修改 信息的学生的学号：\n");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp6 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			DeleteSpecificStuData(pTemp6);
			break;
		case 8:
			//显示所有学生信息
			ShowAllStuData();
			break;
		case 10:
			//查看指令
			ShowOrder();
			break;
		case 11:
			//添加一个学生的信息(头添加)
			printf("输入学号：");
			scanf("%s", arrSTUNum);
			printf("输入姓名：");
			scanf("%s", arrSTUName);
			printf("输入分数：");
			scanf("%d", &iSTUScore);
			AddStuMSG_2(arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 111:
			//添加一个学生的信息（指定位置添加）
			printf("输入需要插入学生信息的位置信息（表中学生的学号）：");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp111 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			printf("输入学号：");
			scanf("%s", arrSTUNum);
			printf("输入姓名：");
			scanf("%s", arrSTUName);
			printf("输入分数：");
			scanf("%d", &iSTUScore);
			AddStuMSG_3(pTemp111, arrSTUNum, arrSTUName, iSTUScore);
			break;
		default:
			printf("输入的指令不对！ \n");
		}
	}
	SaveStuDataToFile("StuInfo.txt");
	FreeLinkData();
	system("pause");
	return 0;
}

//添加一个学生的信息(链表尾部添加)
void AddStuMSG(char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	//第一步，检验参数的合法性
	if (arrSTUNum == NULL || arrSTUName == NULL || iSTUScore < 0)
	{
		printf("学生信息输入错误！\n");
		return;
	}

	//逻辑
	//创建一个节点
	STUNODE* pTemp = malloc(sizeof(STUNODE));
	//节点成员赋初始值
	strcpy(pTemp->arrSTUNum, arrSTUNum);
	strcpy(pTemp->arrSTUName, arrSTUName);
	pTemp->iSTUScore = iSTUScore;
	pTemp->pNext = NULL;

	//接在链表上
	if (g_pHead == NULL || g_pEnd == NULL)
	{
		g_pHead = pTemp;
		g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pNext = pTemp;//链接
		g_pEnd = pTemp;//向后移
	}
}

//添加一个学生信息（链表头部添加）
void AddStuMSG_2(char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	if (arrSTUNum == NULL || arrSTUName == NULL || iSTUScore < 0)
	{
		printf("学生信息输入错误！\n");
		return;
	}

	//创建节点
	STUNODE* pTemp = malloc(sizeof(STUNODE));
	//成员赋值
	strcpy(pTemp->arrSTUNum, arrSTUNum);
	strcpy(pTemp->arrSTUName, arrSTUName);
	pTemp->iSTUScore = iSTUScore;
	pTemp->pNext = NULL;

	//链表链接
	if (g_pHead == NULL)
	{
		g_pEnd = pTemp;
	}
	else
	{
		pTemp->pNext = g_pHead;
	}
	g_pHead = pTemp;
}

//添加一个学生信息（指定位置添加）
void AddStuMSG_3(STUNODE* pTemp, char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	if (pTemp == NULL)
	{
		printf("插入位置有误！\n");
	}

	//创建新节点并赋值
	STUNODE* pNewTemp = malloc(sizeof(STUNODE));
	strcpy(pNewTemp->arrSTUNum, arrSTUNum);
	strcpy(pNewTemp->arrSTUName, arrSTUName);
	pNewTemp->iSTUScore = iSTUScore;
	pNewTemp->pNext = NULL;

	if (pTemp == g_pEnd)
	{
		g_pEnd->pNext = pNewTemp;
		g_pEnd = pNewTemp;
	}
	else
	{
		InsertData(pNewTemp, pTemp);
	}
}

//通过学号查找指定学生信息(从链表头开始查找)
STUNODE* FindStuMSGBy_arrSTUNum(char* arrSTUNum)
{
	//检查参数的合法性
	if (arrSTUNum == NULL)
	{
		printf("学号输入错误:\n");
		return NULL;
	}

	//链表引用
	if (g_pHead == NULL)
	{
		printf("学生信息数据为空\n");
		return NULL;
	}

	//遍历链表
	STUNODE* pTemp = g_pHead;
	while (pTemp != NULL)
	{
		if (strcmp(pTemp->arrSTUNum, arrSTUNum) == 0)
		{
			return pTemp;
		}
		pTemp = pTemp->pNext;
	}
	return NULL;

}

//清空链表
void FreeLinkData()
{
	STUNODE* pTemp = NULL;

	while (g_pHead != NULL)
	{
		//记录节点
		pTemp = g_pHead;

		//头指针向后移动
		g_pHead = g_pHead->pNext;

		//删除上一个节点
		free(pTemp);
	}
}

//显示所有学生信息
void ShowAllStuData()
{
	STUNODE* pTemp = g_pHead;
	if (g_pHead != NULL)
	{
		while (pTemp != NULL)
		{
			printf("学号：%s，姓名：%s，分数：%d\n", pTemp->arrSTUNum, pTemp->arrSTUName, pTemp->iSTUScore);
			//指针指向下一个数据
			pTemp = pTemp->pNext;
		}
	}
	else
	{
		printf("学生信息为空!\n");
	}
}

//显示指定学生信息
void ShowSpecificStuData(STUNODE* pTemp)
{
	if (pTemp == NULL)
	{
		printf("无此学生信息！\n");
	}
	else
	{
		printf("学号：%s，姓名：%s，分数：%d\n", pTemp->arrSTUNum, pTemp->arrSTUName, pTemp->iSTUScore);
	}
}

void ShowOrder()
{
	printf("****************学生信息管理系统****************\n");
	printf("****************本系统操作指令如下**************\n");
	printf("***       1、增加一个学生信息（链表尾添加）   ***\n");
	printf("***       11、增加一个学生信息（链表头添加）  ***\n");
	printf("***       111、增加一个学生信息（指定位置）   ***\n");
	printf("***       2、查找指定学生的信息（姓名/学号） ***\n");
	printf("***       3、修改指定学生的信息              ***\n");
	printf("***       4、保存学生的信息到文件中          ***\n");
	printf("***       5、读取文件中的学生信息            ***\n");
	printf("***       6、删除指定学生信息                ***\n");
	//printf("***       7、恢复删除的学生的信息            ***\n");
	printf("***       8、显示所有学生信息                ***\n");
	printf("***       0、退出系统                        ***\n");
	printf("***********************************************\n");
}

//指定位置插入节点
void InsertData(STUNODE* pNewTemp, STUNODE* pTemp)
{
	pNewTemp->pNext = pTemp->pNext;
	pTemp->pNext = pNewTemp;
}

void ModifySpecificStuData(STUNODE* pTemp, char* arrStuNum, char* arrSTUName, int iSTUScore)
{
	if (pTemp == NULL)
	{
		printf("输入的学生不存在\n");
	}
	else
	{
		//替换原来的数据
		strcpy(pTemp->arrSTUNum, arrStuNum);
		strcpy(pTemp->arrSTUName, arrSTUName);
		pTemp->iSTUScore = iSTUScore;
		//提示输入成功
		printf("修改学生信息成功：\n");
	}
}

void DeleteSpecificStuData(STUNODE* pTemp)
{
	if (g_pHead == g_pEnd)
	{
		free(g_pHead);
		g_pHead = NULL;
		g_pEnd = NULL;
		return;
	}
	else if (g_pHead->pNext == g_pEnd)
	{
		if (pTemp == g_pHead)
		{
			free(pTemp);
			pTemp = NULL;
			g_pHead = g_pEnd;
			return;
		}
		else
		{
			free(pTemp);
			pTemp = NULL;
			g_pEnd = g_pHead;
			g_pHead->pNext = NULL;
			return;
		}
	}
	else
	{
		STUNODE* pTempHead = g_pHead;

		if (pTemp == g_pHead)
		{
			g_pHead = g_pHead->pNext;
			free(pTemp);
			pTemp->pNext = NULL;
			return;
		}
		else
		{
			while (pTemp != NULL)
			{
				if (pTemp == pTempHead->pNext && pTemp == g_pEnd)
				{
					free(pTemp);
					pTemp->pNext = NULL;
					g_pEnd = pTempHead;
					g_pEnd->pNext = NULL;
					return;
				}
				else
				{
					pTempHead->pNext = pTemp->pNext;
					free(pTemp);
					pTemp->pNext = NULL;
					return;
				}
				pTempHead = pTempHead->pNext;
			}
		}

	}
}

//保存学生信息至文件
void SaveStuDataToFile(char* FileName)
{
	if (g_pHead == NULL)
	{
		printf("学生信息为空，无需保存！\n");
		return;
	}
	else
	{
		//打开文件
		FILE* fp = NULL;
		fp = fopen(FileName, "wb+");
		if (fp == NULL)
		{
			printf("文件打开失败!");
			return;
		}

		//操作文件指针进行数据保存
		else
		{
			char strBuf[30] = { '\0' };
			char strScore[10] = { '\0' };
			STUNODE* pTemp = g_pHead;
			while (pTemp)
			{
				//学生信息填入缓冲区
				strcpy(strBuf, pTemp->arrSTUNum);
				strcat(strBuf, ".");
				strcat(strBuf, pTemp->arrSTUName);
				strcat(strBuf, ".");
				_itoa(pTemp->iSTUScore, strScore, 10);//将整形变量转换为字符型
				strcat(strBuf, strScore);
				strcat(strBuf, "\r\n");
				//写入文件
				fwrite(strBuf, 1, strlen(strBuf), fp);
				pTemp = pTemp->pNext;
			}
			printf("保存成功！\n");
		}

		//关闭文件
		fclose(fp);
	}
}

//读取文件信息
void ReadStuDataFromSpecificFile(char* FileName)
{
	//打开文件
	FILE* fp = fopen(FileName, "rb+");
	if (fp == NULL)
	{
		printf("打开文件失败！\n");
		return;
	}
	//操作文件指针
	else
	{
		char strBuf[30] = { '\0' };
		char arrSTUNum[10] = { '\n' };
		char arrSTUName[10] = { '\n' };
		char arrSTUScore[10] = { '\n' };


		//读取文件内容
		while (fgets(strBuf, 30, fp) != NULL)
		{
			int i = 0;
			int iCount = 0;
			int j = 0;
			int k = 0;
			for (i = 0;strBuf[i] != '\r';i++)
			{
				if (iCount == 0)
				{
					if (strBuf[i] != '.')
					{
						arrSTUNum[i] = strBuf[i];
					}
					else
					{
						iCount++;
					}
				}
				else if (iCount == 1)
				{
					if (strBuf[i] != '.')
					{
						arrSTUName[j] = strBuf[i];
						j++;
					}
					else
					{
						iCount++;
					}
				}
				else if (iCount == 2)
				{
					if (strBuf[i] != '.')
					{
						arrSTUScore[k] = strBuf[i];
						k++;
					}
				}
			}
			//将学生信息添加至链表
			AddStuMSG(arrSTUNum, arrSTUName, atoi(arrSTUScore));
		}
	}
	//关闭文件
	fclose(fp);
}
