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

//����� ���� ��ǥ
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;
bool beforehomestate = false;

char CatItem[ITEM_NUM][50] = { "��ũ����","ĹŸ��" };
int CatItemPlace[ITEM_NUM] = { -1, -1 }; //��Ÿ�. ��ġ �ȵǾ� ���� ��(-1)

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
		if (player->Feel - 1 < 0) {
			printf("%d", player->Feel);
		}
		else {
			printf("%d", --player->Feel);
		}
	}
	printf("\n");
	ST;
}

void PrintStatus(PLAYER player) {

	printf("==================== ���� ���� ====================\n");
	printf("������� ���� ���� : %d\n", player.soup_n);

	printf("CP : %d ����Ʈ\n�˶��� ���(0~3): %d\n\t", player.CP, player.Feel);
	switch (player.Feel) {
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

	printf("������� ����(0~4) : %d\n", player.RLevel);
	switch (player.RLevel) {
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
	if (mode == 0) {
		printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
		ST;
		printf("4/6 Ȯ���� ģ�е��� �������ϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	}
	else {
		printf("%s�� ���� �ܾ��־����ϴ�.\n", player->name);
		ST;
		printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
		ST;
		printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	}
	ST;

	printf("%d��(��) ���Խ��ϴ�!\n", dice);
	ST;

	if (dice < range) {
		if (mode == 0) {
			if (player->RLevel > 0) {
				printf("ģ�е��� �������ϴ�.\n");
				player->RLevel--;
			}
			else {
				printf("ģ�е��� ���̻� �������� �ʽ��ϴ�..\n");
			}
			ST;
		}
		else {
			printf("ģ�е��� �״���Դϴ�..\n");
			ST;
		}
	}
	else {
		if (mode == 0) {
			printf("������ ģ�е��� �������� �ʾҽ��ϴ�.\n");
		}
		else {
			if (player->RLevel < 4) {
				printf("ģ�е��� �������ϴ�.\n");
				player->RLevel++;
			}
			else {
				printf("ģ�е��� ���̻� �ö��� �ʽ��ϴ�.\n");
			}
		}
		ST;
	}
}

void Interaction(PLAYER* player) {
	//Ű���� �Է� �Լ� �ٽ�?
	int tmp;
	printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�? 0. �ƹ��͵� ���� ����    1. �ܾ��ֱ�\n");

	do {
		printf(">> ");
		scanf_s("%d", &tmp);
	} while (tmp != 0 && tmp != 1);

	int dice = Random(6);

	switch (tmp) {
	case 0:
		//�̻��� �߸�����.. Interfuc ������ 4�� �ƴ� 5�� �ִ°� ����.
		Interfuc(player, dice, 0, 5);
		break;
	case 1:
		Interfuc(player, dice, 1, 5);
		break;
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

void CatMoveToHome() {
	if (cat > HME_POS) {
		beforecat = cat;
		cat--;
		ordernum = 0;
		//ordernum = 2;
	}
	//���� ��
	else {
		beforecat = NULL;
		ordernum = 3;
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

int MoveToNearItem(int itmx) {
	//����̿� �������� ���� ��ҿ� ���� ��
	if (cat != CatItemPlace[itmx]) {
		//���� �ʰ� �����x�� �� Ŭ ��
		if (cat > CatItemPlace) {
			beforecat = cat;
			cat--;
		}
		else {
			beforecat = cat;
			cat++;
		}
	}
}

int NearItemCK() {
	int nearItemNum = -1;
	int nearItemDis = INT_MAX;

	//���� ����� ������ Ž��
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlace[i] != -1) { 
			int dis = abs(CatItemPlace[i] - cat);
			if (dis < nearItemDis) {
				nearItemDis = dis;
				nearItemNum = i;
			}
		}
	}
	
	//���������� �̵�
	MoveToNearItem(nearItemNum);

	//������ �̸� ������� ����
	return nearItemNum;
}

int CatMoveToItem() {
	int minusOneCount = 0;
	
	//��ġ�� ��Ÿ��� �ִ��� Ȯ��.
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlace[i] == -1) minusOneCount++;
	}
	
	//��� ��Ÿ�(Item)��(��) ���� ��Ȳ
	if (minusOneCount == ITEM_NUM) {
		return -1;
	}
	//��Ÿ��� �ִ� ���
	else {
		return NearItemCK();
	}
}

int CatMove(PLAYER* player) {

	dice = Random(6);
	//ȣ���� ����. ����ü�� ����� ������ define�� ����� �� ������..
	target = 6 - player->RLevel;

	int itemIndex = NULL;

	switch (player->Feel) {
	case 0:
		CatMoveToHome();
		printf("����� �ſ� ���� %s��(��) ������ ���մϴ�.\n", player->name);
		break;
	case 1:
		itemIndex = CatMoveToItem();
		if ( itemIndex != -1) {
			printf("%s��(��) �ɽ��ؼ� %s������ �̵��մϴ�.\n", player->name, CatItem[itemIndex]);
		}
		else {
			printf("��Ÿ��� ��� ����� �ſ� �������ϴ�");
			if (player->Feel == 0) {
				printf("����� ����ġ�� ���̻� �������� �ʽ��ϴ�!");
			}
			else {
				printf("%d ->", player->Feel);
				player->Feel--;
				printf("%d\n", player->Feel);
			}
		}
		break;
	case 2:
		printf("%s��(��) ������� �Ļ��� ���� �ֽ��ϴ�.\n", player->name);
		break;
	case 3:
		CatMoveToSoup(&player);
		printf("%s��(��) ������ �θ��� ������ ���鷯 ���ϴ�.\n", player->name);
		break;
	}
	printf("\n");
	return 0;
}

void PrintStatusCat() {

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
	}
	ordernum = 0;
	ST;
}

void CatAction() {

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

int main() {
	srand((unsigned int)time(NULL));

	//Cp �⺻�� 3
	PLAYER player = { NULL, 0, 2, 0, 3};

	PrintIntro(&player);

	while (1) {
		PrintStatus(player);

		PrintStatusFeel(&player);

		int SoupPrint = CatMove(&player);

		//PrintStatusRoomMove(player);
		//PrintStatusCat();

		if (SoupPrint == 1) {
			CatSoupMessage(player);
		}

		CatAction();

		PrintMap();

		Interaction(&player);

		Sleep(2500); //2.5�� ���
		system("cls");
	}

	free(player.name);

	return 0;
}