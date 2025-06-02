#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 8
#define ROOM_HEIGHT 4
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)
#define DICE 6
#define ITEM_NUM 2
#define ST Sleep(500)
#define MAX_MENU_ITEM (ITEM_NUM + 2)
#define MAX(a, b) ((a)>=(b)?(a):(b))

//����� ���� ��ǥ
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;
bool beforehomestate = false;

//����ü�� �ٲٸ� ���ڴµ�;;
char CatItemThing[ITEM_NUM][50] = {"��ũ����","ĹŸ��"};
int CatItemPriceThing[ITEM_NUM] = { 4, 6 };
int CatItemPlaceThing[ITEM_NUM] = { -1, -1 };

char CatItemPlay[ITEM_NUM][50] = { "�峭�� ��", "������ ������" };
int CatItemPricePlay[ITEM_NUM] = { 1, 2 };
int CatItemPlacePlay[ITEM_NUM] = { -1, -1 };

char CatItemFeelUpDialog[2][50] = { "����", "����" };

int CatItemFeelUpStatus[ITEM_NUM] = {1, 2};

typedef struct {
	char* name;
	int soup_n;
	int RLevel;
	int CP;
	int Feel;
} PLAYER;

void PrintStatusRoomMove(PLAYER player) {
	printf("%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", player.name);
	ST;
	printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", target);
	ST;
	printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	ST;
	printf("%d��(��) ���Խ��ϴ�!\n", dice);
	ST;
}

void PrintStatusFeel(PLAYER *player){

	int dice = Random(6);

	printf("%d - %d : �ֻ����� ���� %d �����̸� �׳� ����� �������ϴ�.\n", DICE, player->RLevel, DICE - player->RLevel);
	ST;
	printf("�ֻ����� �����ϴ�. �Ǹ���..\n");
	ST;
	printf("%d��(��) ���Խ��ϴ�.\n", dice);
	ST;

	int decision_base = DICE - player->RLevel;
	if (dice > decision_base) {
		printf("����� �������� �ʾҽ��ϴ�.\n");
	}
	else {
		printf("�˶����� ����� �������ϴ� : ");
		printf("%d -> ", player->Feel);
		if (player->Feel > 0) {
			player->Feel--;
			printf("%d", player->Feel);
		}
		else {
			printf("%d", player->Feel);
		}
	}
	printf("\n");
	ST;
}

void PrintStatus(PLAYER *player) {

	printf("==================== ���� ���� ====================\n");
	printf("������� ���� ���� : %d\n", player->soup_n);

	printf("CP : %d ����Ʈ\n�˶��� ���(0~3): %d\n\t", player->CP, player->Feel);
	switch (player->Feel) {
	case 0:
		printf("����� �ſ� ���޴ϴ�\n");
		break;
	case 1:
		printf("�ɽ����մϴ�.\n");
		break;
	case 2:
		printf("�Ļ��� �����ϴ�.\n");
		break;
	case 3:
		printf("������ �θ��ϴ�.\n");
		break;
	}

	printf("������� ģ�е�(0~4) : %d\n", player->RLevel);
	switch (player->RLevel) {
	case 0:
		printf("�翡 ���� ������ �Ⱦ��մϴ�\n");
		break;
	case 1:
		printf("���� ���Ǳ� ����Դϴ�.\n");
		break;
	case 2:
		printf("�׷����� ������ �����Դϴ�.\n");
		break;
	case 3:
		printf("�Ǹ��� ����� �����ް� �ֽ��ϴ�.\n");
		break;
	case 4:
		printf("���� �������Դϴ�.\n");
		break;
	}
	printf("===================================================\n\n");
}

int Random(int max) {
	return rand() % max + 1;
}

//mode 0->�ƹ��͵� ���� �ʱ�, 1->�ܾ��ֱ�
void Interfuc(PLAYER* player, int dice, int mode, int range) {
	int beforefeal = player->Feel;
	int beforeRLevel = player->RLevel;

	switch (mode) {
	case 0: //�ƹ��͵� ����

		if (player->Feel > 0) player->Feel--;

		printf("%s�� ����� ���������ϴ�: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("�ֻ��� ���� 5 �����̸� ģ�е��� 1 �����մϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
		ST;
		printf("%d��(��) ���Խ��ϴ�!\n", dice);
		ST;

		if (dice <= 5) {
			if (player->RLevel > 0) {
				player->RLevel--;
				printf("ģ�е��� �������ϴ�: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("ģ�е��� ���̻� �������� �ʽ��ϴ�: %d\n", player->RLevel);
			}
		}
		else {
			printf("������ ģ�е��� �״���Դϴ�: %d\n", player->RLevel);
		}
		break;

	case 1:// �ܱ�

		printf("%s�� ���� �ܾ��־����ϴ�.\n", player->name);
		ST;
		printf("%s�� ����� �״���Դϴ�: %d\n", player->name, player->Feel);
		ST;
		printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�... �Ǹ���...\n");
		ST;
		printf("%d��(��) ���Խ��ϴ�!\n", dice);
		ST;

		if (dice >= 5) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("ģ�е��� �������ϴ�: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("ģ�е��� �̹� �ִ��Դϴ�: %d\n", player->RLevel);
			}
		}
		else {
			printf("ģ�е��� �״���Դϴ�: %d\n", player->RLevel);
		}
		break;

	case 2: //��
		if (player->Feel < 3) player->Feel++;

		printf("�峭�� ��� %s�� ����־����ϴ�. ", player->name);
		printf("%s�� ����� ���� ���������ϴ�: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("�ֻ����� 4 �̻��̸� ģ�е��� 1 �����մϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�... �Ǹ���...\n");
		ST;
		printf("%d��(��) ���Խ��ϴ�!\n", dice);
		ST;

		if (dice >= 4) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("ģ�е��� �������ϴ�: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("ģ�е��� �̹� �ִ��Դϴ�: %d\n", player->RLevel);
			}
		}
		else {
			printf("ģ�е��� �״���Դϴ�: %d\n", player->RLevel);
		}
		break;

	case 3: //������

		if (player->Feel <= 1) player->Feel += 2;
		else if (player->Feel == 2) player->Feel = 3;

		printf("������ �����ͷ� %s�� �ų��� ����־����ϴ�. ", player->name);
		printf("%s�� ����� �� ���������ϴ�: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("�ֻ����� 2 �̻��̸� ģ�е��� 1 �����մϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�... �Ǹ���...\n");
		ST;
		printf("%d��(��) ���Խ��ϴ�!\n", dice);
		ST;
		if (dice >= 2) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("ģ�е��� �������ϴ�: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("ģ�е��� �̹� �ִ��Դϴ�: %d\n", player->RLevel);
			}
		}
		else {
			printf("ģ�е��� �״���Դϴ�: %d\n", player->RLevel);
		}
		break;
	}
	ST;
}


void Interaction(PLAYER* player) {
	//Ű���� �Է� �Լ� �ٽ�?
	int tmp;
	printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?\n0. �ƹ��͵� ���� ����\n1. �ܾ��ֱ�\n");

	int menuitmindex[MAX_MENU_ITEM] = { NULL };
	int menunum = 2;

	//��ġ�� ��Ÿ��� �ִ��� Ȯ��.
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlacePlay[i] != -1) { 
			printf("%d. %s\n", menunum, CatItemPlay[i]);
			menuitmindex[menunum] = i;
			menunum++;
		}
	}

	do {
		printf(">> ");
		scanf_s("%d", &tmp);
	} while (tmp < 0 || tmp >= menunum);

	int dice = Random(6);

	if (tmp == 0) {
		Interfuc(player, dice, 0, 5);
	}
	else if (tmp == 1) {
		Interfuc(player, dice, 1, 5);
	}
	else {
		int itemIndex = menuitmindex[tmp];

		if (itemIndex == 0) {
			Interfuc(player, dice, 2, 4);
		}
		else if (itemIndex == 1) {
			Interfuc(player, dice, 3, 2);
		}
		else {
			printf("������. �ٽ� �غ���\n");
		}
	}

	printf("���� ģ�е�: %d\n", player->RLevel);
	ST;
}

void PrintIntro(PLAYER* player) {
	printf("****�߿��̿� ����****\n");
	ST;
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	ST;

	char name[50];

	printf("�߿����� �̸��� �����ּ��� :");
	scanf_s("%49s", name, (unsigned)_countof(name));

	player->name = malloc(strlen(name) + 1);
	if (player->name == NULL) {
		return;
	}

	//��� ��� ������..
	strcpy_s(player->name, strlen(name) + 1, name);
	player->name[strlen(name)] = '\0';
	printf("�߿����� �̸��� %s�Դϴ�.\n", player->name);
	Sleep(1000);

	system("cls");
}

void CatSoupMessage(PLAYER player) {

	int dice = Random(3);

	switch (dice) {
	case 1:
		printf("%s��(��) ���� ������ ��������ϴ�!\n\n", player.name);
		break;
	case 2:
		printf("%s��(��) ����� ������ ��������ϴ�!\n\n", player.name);
		break;
	case 3:
		printf("%s��(��) ����ݸ� ������ ��������ϴ�!\n\n", player.name);
		break;
	}
	ST;
}

int CatMoveToHome(PLAYER *player) {
	if (cat > HME_POS) {
		beforecat = cat;
		cat--;
		//�ƹ��͵� ��� ����
		ordernum = 0;
		//ordernum = 2;
		return 0;
	}
	//���� ��
	else {
		beforecat = NULL;
		//�޽��ؼ� ������
		if (player->Feel < 3) {
			player->Feel++;
			ordernum = 4;
			return 1;
		}
		return 1;
	}
}

int CatMoveToSoup(PLAYER *player) {
	//���� �ƴ� ��
	if (cat < BWL_PO) {
		beforecat = cat;
		cat++;
		ordernum = 1;
		if (cat == BWL_PO) {
			player->soup_n++;
			return 1;
		}
	}
	//���� ��
	else {
		beforecat = NULL;
		return 1;
	}
}

int MoveToNearItem(PLAYER* player, int itm) {
	//����̿� �������� ���� ��ҿ� ���� ��
	if (cat != CatItemPlaceThing[itm]) {
		//���� �ʰ� �����x�� �� Ŭ ��
		if (cat > CatItemPlaceThing[itm]) {
			beforecat = cat;
			cat--;
		}
		else {
			beforecat = cat;
			cat++;
		}
	}
	else {
		switch (itm) {
		case 0:
			printf("%s��(��) %s�� �ܰ� ��ҽ��ϴ�.", player->name, CatItemThing[itm]);
			break;
		case 1:
			printf("%s��(��) %s�� �پ�ٴմϴ�.", player->name, CatItemThing[itm]);
			break;
		}
		printf(" ����� %s ���������ϴ� :", CatItemFeelUpDialog[itm]);
		printf("%d ->", player->Feel);
		player->Feel += CatItemFeelUpStatus[itm];
		printf("%d\n", player->Feel);	
	}
}

int NearItemCK(PLAYER* player) {
	int nearItemNum = -1;
	int nearItemDis = INT_MAX;

	//���� ����� ������ Ž��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlaceThing[i] != -1) {
			int dis = abs(CatItemPlaceThing[i] - cat);
			if (dis < nearItemDis) {
				nearItemDis = dis;
				nearItemNum = i;
			}
		}
	}
	
	//���������� �̵�
	MoveToNearItem(player, nearItemNum);

	//������ �̸� ������� ����
	return nearItemNum;
}

int CatMoveToItem(PLAYER* player) {
	int minusOneCount = 0;
	
	//��ġ�� ��Ÿ��� �ִ��� Ȯ��.
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlaceThing[i] == -1) minusOneCount++;
	}
	
	//��� ��Ÿ�(Item)��(��) ���� ��Ȳ
	if (minusOneCount == ITEM_NUM) {
		return -1;
	}
	//��Ÿ��� �ִ� ���
	else {
		return NearItemCK(player);
	}
}

int CatMove(PLAYER* player) {

	dice = Random(6);
	//ȣ���� ����. ����ü�� ����� ������ define�� ����� �� ������..
	target = 6 - player->RLevel;

	int itemIndex = 0;
	int homeheal = 0;

	switch (player->Feel) {
	case 0:
		homeheal = CatMoveToHome(player);
		if (homeheal == 0) {
			printf("����� �ſ� ���� %s��(��) ������ ���մϴ�.\n", player->name);
		}
		break;
	case 1:
		itemIndex = CatMoveToItem(player);
		if ( itemIndex != -1) {
			printf("%s��(��) �ɽ��ؼ� %s������ �̵��մϴ�.\n", player->name, CatItemThing[itemIndex]);
		}
		else {
			printf("��Ÿ��� ��� ����� �ſ� �������ϴ�");
			if (player->Feel == 0) {
				printf("����� ����ġ�� ���̻� �������� �ʽ��ϴ�!");
			}
			else {
				printf( "%d -> ", player->Feel);
				player->Feel--;
				printf("%d\n", player->Feel);
			}
		}
		break;
	case 2:
		printf("%s��(��) ������� �Ļ��� ���� �ֽ��ϴ�.\n", player->name);
		break;
	case 3:
		CatMoveToSoup(player);
		printf("%s��(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n", player->name);
		break;
	}
	printf("\n");
	return 0;
}

void PrintStatusCat(PLAYER * player) {

	switch (ordernum) {
	case 0:
		break;
	case 1:
		printf("���������� �����Դϴ�!\n\n");
		break;
	case 2:
		printf("�����߽��ϴ�. �ڷ� ���ư��ϴ�... \n\n");
		break;
	case 3:
		printf("���� ���� �ֽ��ϴ�... \n\n");
		break;
	case 4:
		printf("���� �����Ͽ� ȸ�����Դϴ�. ��� : %d -> %d\n\n", player->Feel -1, player->Feel);
		break;
	}
	ordernum = 0;
	ST;
}

void PrintMap() {

	for (int i = 0; i < ROOM_HEIGHT; i++) {
		for (int j = 0; j < ROOM_WIDTH; j++) {
			if (i == 0 || i == ROOM_HEIGHT - 1 || j == 0 || j == ROOM_WIDTH - 1) {
				printf("#");
			}
			else if (i == 1 && j == HME_POS) {
				printf("H");
			}
			else if (i == 1 && j == BWL_PO) {
				printf("B");
			}
			else if (i == 1) {
				int printed = 0;
				for (int k = 0; k < ITEM_NUM; k++) {
					if (CatItemPlaceThing[k] != -1 && CatItemPlaceThing[k] == j) {
						if (k == 0)
							printf("S");
						else if (k == 1)
							printf("T");
						printed = 1;
						break;
					}
				}
				if (!printed) printf(" ");
			}
			else if (i == 2 && beforecat != NULL && j == beforecat) {
				printf(".");
			}
			else if (i == 2 && j == cat) {
				printf("C");
			}
			else {
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
	ST;
}

void CreateCP(PLAYER* player) {
	player->CP += (MAX(0, player->Feel - 1) + player->RLevel);

	printf("\n�˶��� ���(0~3): %d\n", player->Feel);
	printf("������� ģ�е�(0~4): %d\n", player->RLevel);
	printf("�˶��� ��а� ģ�е��� ���� CP�� %d ����Ʈ ����Ǿ����ϴ�.\n", player->CP);
	printf("���� CP: %d ����Ʈ\n\n", player->CP);
}

void Shop(PLAYER * player) {
	printf("�������� ������ �� �� �ֽ��ϴ�.\n� ������ �����ұ��?\n");
	printf("0. �ƹ��͵� ���� �ʴ´�.\n");

	for (int i = 0; i < ITEM_NUM; i++) {
		printf("%d. %s : %d CP", i + 1, CatItemPlay[i], CatItemPricePlay[i]);
		if (CatItemPlacePlay[i] != -1) {
			printf(" (ǰ��)");
		}
		printf("\n");
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		printf("%d. %s : %d CP", ITEM_NUM + i + 1, CatItemThing[i], CatItemPriceThing[i]);
		if (CatItemPlaceThing[i] != -1) {
			printf(" (ǰ��)");
		}
		printf("\n");
	}

	int inputmp;

	do {
		printf(">> ");
		scanf_s("%d", &inputmp);

		if (inputmp == 0) {
			printf("������ ���� �ʾҽ��ϴ�.\n");
			break;
		}

		int ridx = inputmp - 1;

		if (ridx < ITEM_NUM) {
			if (CatItemPlacePlay[ridx] != -1) {
				printf("�̹� ������ �峭���Դϴ�.\n");
				break;
			}

			if (player->CP < CatItemPricePlay[ridx]) {
				printf("CP�� �����մϴ�.\n");
				break;
			}

			player->CP -= CatItemPricePlay[ridx];
			CatItemPlacePlay[ridx] = 0;
			printf("%s�� �����߽��ϴ�. ���� CP: %d ����Ʈ\n", CatItemPlay[ridx], player->CP);
		}
		else {
			int thingIdx = ridx - ITEM_NUM;

			if (CatItemPlaceThing[thingIdx] != -1) {
				printf("�̹� ������ �����Դϴ�.\n");
				break;
			}

			if (player->CP < CatItemPriceThing[thingIdx]) {
				printf("CP�� �����մϴ�.\n");
				break;
			}

			player->CP -= CatItemPriceThing[thingIdx];
			printf("%s�� �����߽��ϴ�. ���� CP: %d ����Ʈ\n", CatItemThing[thingIdx], player->CP);

			int x;
			do {
				x = Random(BWL_PO - HME_POS - 1) + HME_POS;
				int ck = 0;
				for (int i = 0; i < ITEM_NUM; i++) {
					if (CatItemPlaceThing[i] == x) {
						ck = 1;
						break;
					}
				}
				if (!ck) break;
			} while (1);

			CatItemPlaceThing[thingIdx] = x;
			printf("%s�� %d�� ��ġ\n", CatItemThing[thingIdx], x);
		}

		break;

	} while (1);
	
}

int main() {
	srand((unsigned int)time(NULL));

	//Cp �⺻�� 3
	PLAYER player = { NULL, 0, 2, 0, 3};

	PrintIntro(&player);

	while (1) {
		PrintStatus(&player);

		PrintStatusFeel(&player);

		int SoupPrint = CatMove(&player);

		//PrintStatusRoomMove(player);
		PrintStatusCat(&player);

		if (SoupPrint == 1) {
			CatSoupMessage(player);
		}

		PrintMap();

		Interaction(&player);

		CreateCP(&player);

		Shop(&player);

		Sleep(2500); //2.5�� ���
		system("cls");
	}

	free(player.name);

	return 0;
}