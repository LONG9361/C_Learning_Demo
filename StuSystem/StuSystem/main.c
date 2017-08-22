#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//ѧ���ڵ�
typedef struct _STU
{
	char arrSTUNum[10];
	char arrSTUName[10];
	int iSTUScore;
	struct _STU* pNext;
} STUNODE;

//���������ͷ��β
STUNODE* g_pHead = NULL;
STUNODE* g_pEnd = NULL;

//���һ��ѧ����Ϣ
void AddStuMSG(char* arrSTUNum, char* arrSTUName, int iSTUScore);
void AddStuMSG_2(char* arrSTUNum, char* arrSTUName, int iSTUScore);
void AddStuMSG_3(STUNODE* pTemp, char* arrSTUNum, char* arrSTUName, int iSTUScore);

//ͨ��ѧ�Ų���ָ��ѧ����Ϣ
STUNODE* FindStuMSGBy_arrSTUNum(char* arrStuNum);

//�������
void FreeLinkData();

//��ʾ����ѧ����Ϣ
void ShowAllStuData();

//��ʾָ��ѧ����Ϣ
void ShowSpecificStuData(STUNODE* pTemp);

//��ʾָ��
void ShowOrder();

//����
void InsertData(STUNODE* pNewTemp, STUNODE* pTemp);

//�޸�ָ��ѧ����Ϣ
void ModifySpecificStuData(STUNODE* pTemp, char* arrStuNum, char* arrSTUName, int iSTUScore);

//ɾ��ָ��ѧ����Ϣ
void DeleteSpecificStuData(STUNODE* pTemp);

int main(void)
{
	int iOrder = -1;//��ʼ��

	char arrSTUNum[10] = { '\0' };
	char arrSTUName[10] = { '\0' };
	int iSTUScore = 0;
	int iFlag = 1;

	//��ʾָ��
	ShowOrder();

	while (iFlag)
	{
		printf("��ʾ������10�鿴ָ��\n");
		printf("������ָ�\n");
		scanf("%d", &iOrder);
		switch (iOrder)
		{
		case 0:
			iFlag = 0;
			break;
		case 1:
			//���һ��ѧ������Ϣ��β��ӣ�
			printf("����ѧ�ţ�");
			scanf("%s", arrSTUNum);
			printf("����������");
			scanf("%s", arrSTUName);
			printf("���������");
			scanf("%d", &iSTUScore);
			AddStuMSG(arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 2:
			//����ѧ����Ϣ(ѧ��)
			printf("������Ҫ������Ϣ��ѧ����ѧ�ţ�\n");
			scanf("%s", arrSTUNum);
			ShowSpecificStuData(FindStuMSGBy_arrSTUNum(arrSTUNum));
			break;
		case 3:
			//�޸�ָ��ѧ����Ϣ��ѧ�ţ�
			printf("������Ҫ�޸� ��Ϣ��ѧ����ѧ�ţ�\n");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp3 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			printf("����ѧ�ţ�");
			scanf("%s", arrSTUNum);
			printf("����������");
			scanf("%s", arrSTUName);
			printf("���������");
			scanf("%d", &iSTUScore);
			ModifySpecificStuData(pTemp3, arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 6:
			//ɾ��ָ��ѧ����Ϣ
			printf("������Ҫ�޸� ��Ϣ��ѧ����ѧ�ţ�\n");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp6 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			DeleteSpecificStuData(pTemp6);
			break;
		case 8:
			//��ʾ����ѧ����Ϣ
			ShowAllStuData();
			break;
		case 10:
			//�鿴ָ��
			ShowOrder();
			break;
		case 11:
			//���һ��ѧ������Ϣ(ͷ���)
			printf("����ѧ�ţ�");
			scanf("%s", arrSTUNum);
			printf("����������");
			scanf("%s", arrSTUName);
			printf("���������");
			scanf("%d", &iSTUScore);
			AddStuMSG_2(arrSTUNum, arrSTUName, iSTUScore);
			break;
		case 111:
			//���һ��ѧ������Ϣ��ָ��λ����ӣ�
			printf("������Ҫ����ѧ����Ϣ��λ����Ϣ������ѧ����ѧ�ţ���");
			scanf("%s", arrSTUNum);
			STUNODE* pTemp111 = FindStuMSGBy_arrSTUNum(arrSTUNum);
			printf("����ѧ�ţ�");
			scanf("%s", arrSTUNum);
			printf("����������");
			scanf("%s", arrSTUName);
			printf("���������");
			scanf("%d", &iSTUScore);
			AddStuMSG_3(pTemp111, arrSTUNum, arrSTUName, iSTUScore);
			break;
		default:
			printf("�����ָ��ԣ� \n");
		}
	}

	FreeLinkData();
	system("pause");
	return 0;
}

//���һ��ѧ������Ϣ(����β�����)
void AddStuMSG(char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	//��һ������������ĺϷ���
	if (arrSTUNum == NULL || arrSTUName == NULL || iSTUScore < 0)
	{
		printf("ѧ����Ϣ�������\n");
		return;
	}

	//�߼�
	//����һ���ڵ�
	STUNODE* pTemp = malloc(sizeof(STUNODE));
	//�ڵ��Ա����ʼֵ
	strcpy(pTemp->arrSTUNum, arrSTUNum);
	strcpy(pTemp->arrSTUName, arrSTUName);
	pTemp->iSTUScore = iSTUScore;
	pTemp->pNext = NULL;

	//����������
	if (g_pHead == NULL || g_pEnd == NULL)
	{
		g_pHead = pTemp;
		g_pEnd = pTemp;
	}
	else
	{
		g_pEnd->pNext = pTemp;//����
		g_pEnd = pTemp;//�����
	}
}

//���һ��ѧ����Ϣ������ͷ����ӣ�
void AddStuMSG_2(char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	if (arrSTUNum == NULL || arrSTUName == NULL || iSTUScore < 0)
	{
		printf("ѧ����Ϣ�������\n");
		return;
	}

	//�����ڵ�
	STUNODE* pTemp = malloc(sizeof(STUNODE));
	//��Ա��ֵ
	strcpy(pTemp->arrSTUNum, arrSTUNum);
	strcpy(pTemp->arrSTUName, arrSTUName);
	pTemp->iSTUScore = iSTUScore;
	pTemp->pNext = NULL;

	//��������
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

//���һ��ѧ����Ϣ��ָ��λ����ӣ�
void AddStuMSG_3(STUNODE* pTemp, char* arrSTUNum, char* arrSTUName, int iSTUScore)
{
	if (pTemp == NULL)
	{
		printf("����λ������\n");
	}

	//�����½ڵ㲢��ֵ
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

//ͨ��ѧ�Ų���ָ��ѧ����Ϣ(������ͷ��ʼ����)
STUNODE* FindStuMSGBy_arrSTUNum(char* arrSTUNum)
{
	//�������ĺϷ���
	if (arrSTUNum == NULL)
	{
		printf("ѧ���������:\n");
		return NULL;
	}

	//��������
	if (g_pHead == NULL)
	{
		printf("ѧ����Ϣ����Ϊ��\n");
		return NULL;
	}

	//��������
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

//�������
void FreeLinkData()
{
	STUNODE* pTemp = NULL;

	while (g_pHead != NULL)
	{
		//��¼�ڵ�
		pTemp = g_pHead;

		//ͷָ������ƶ�
		g_pHead = g_pHead->pNext;

		//ɾ����һ���ڵ�
		free(pTemp);
	}
}

//��ʾ����ѧ����Ϣ
void ShowAllStuData()
{
	STUNODE* pTemp = g_pHead;
	if (g_pHead != NULL)
	{
		while (pTemp != NULL)
		{
			printf("ѧ�ţ�%s��������%s��������%d\n", pTemp->arrSTUNum, pTemp->arrSTUName, pTemp->iSTUScore);
			//ָ��ָ����һ������
			pTemp = pTemp->pNext;
		}
	}
	else
	{
		printf("ѧ����ϢΪ��!\n");
	}
}

//��ʾָ��ѧ����Ϣ
void ShowSpecificStuData(STUNODE* pTemp)
{
	if (pTemp == NULL)
	{
		printf("�޴�ѧ����Ϣ��\n");
	}
	else
	{
		printf("ѧ�ţ�%s��������%s��������%d\n", pTemp->arrSTUNum, pTemp->arrSTUName, pTemp->iSTUScore);
	}
}

void ShowOrder()
{
	printf("****************ѧ����Ϣ����ϵͳ****************\n");
	printf("****************��ϵͳ����ָ������**************\n");
	printf("***       1������һ��ѧ����Ϣ������β��ӣ�   ***\n");
	printf("***       11������һ��ѧ����Ϣ������ͷ��ӣ�  ***\n");
	printf("***       111������һ��ѧ����Ϣ��ָ��λ�ã�   ***\n");
	printf("***       2������ָ��ѧ������Ϣ������/ѧ�ţ� ***\n");
	printf("***       3���޸�ָ��ѧ������Ϣ              ***\n");
	printf("***       4������ѧ������Ϣ���ļ���          ***\n");
	printf("***       5����ȡ�ļ��е�ѧ����Ϣ            ***\n");
	printf("***       6��ɾ��ָ��ѧ����Ϣ                ***\n");
	printf("***       7���ָ�ɾ����ѧ������Ϣ            ***\n");
	printf("***       8����ʾ����ѧ����Ϣ                ***\n");
	printf("***       0���˳�ϵͳ                        ***\n");
	printf("***********************************************\n");
}

//ָ��λ�ò���ڵ�
void InsertData(STUNODE* pNewTemp, STUNODE* pTemp)
{
	pNewTemp->pNext = pTemp->pNext;
	pTemp->pNext = pNewTemp;
}

void ModifySpecificStuData(STUNODE* pTemp, char* arrStuNum, char* arrSTUName, int iSTUScore)
{
	if (pTemp == NULL)
	{
		printf("�����ѧ��������\n");
	}
	else
	{
		//�滻ԭ��������
		strcpy(pTemp->arrSTUNum, arrStuNum);
		strcpy(pTemp->arrSTUName, arrSTUName);
		pTemp->iSTUScore = iSTUScore;
		//��ʾ����ɹ�
		printf("�޸�ѧ����Ϣ�ɹ���\n");
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