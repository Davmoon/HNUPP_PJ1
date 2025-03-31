#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 6
#define ROOM_HEIGHT 4
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)

//����� ���� ��ǥ
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;

typedef struct {
	char* name;
	int soup_n;
	int fLevel;
} PLAYER;

void PrintStatusRoomMove(PLAYER player) {
	printf("%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", player.name);
	Sleep(500);
	printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", target);
	Sleep(500);
	printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	Sleep(500);
	printf("%d��(��) ���Խ��ϴ�!\n", dice);
	Sleep(500);
}

void PrintStatus(PLAYER player) {

	printf("==================== ���� ���� ====================\n");
	printf("������� ���� ���� : %d\n", player.soup_n);
	printf("������� ����(0~4) : %d\n", player.fLevel);
	switch (player.fLevel) {
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

int random(int max) {
	return rand() % max + 1;
}

//mode 0->�ƹ��͵� ���� �ʱ�, 1->�ܾ��ֱ�
void Interfuc(PLAYER* player, int dice, int mode, int range) {
	if (mode == 0) {
		printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
		Sleep(500);
		printf("4/6 Ȯ���� ģ�е��� �������ϴ�.\n");
		Sleep(500);
		printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	}
	else {
		printf("%s�� ���� �ܾ��־����ϴ�.\n", player->name);
		Sleep(500);
		printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
		Sleep(500);
		printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	}
	Sleep(500);

	printf("%d��(��) ���Խ��ϴ�!\n", dice);
	Sleep(500);

	if (dice < range) {
		if (mode == 0) {
			if (player->fLevel > 0) {
				printf("ģ�е��� �������ϴ�.\n");
				player->fLevel--;
			}
			else {
				printf("ģ�е��� ���̻� �������� �ʽ��ϴ�..\n");
			}
			Sleep(500);
		}
		else {
			printf("ģ�е��� �״���Դϴ�..\n");
			Sleep(500);
		}
	}
	else {
		if (mode == 0) {
			printf("������ ģ�е��� �������� �ʾҽ��ϴ�.\n");
		}
		else {
			if (player->fLevel < 4) {
				printf("ģ�е��� �������ϴ�.\n");
				player->fLevel++;
			}
			else {
				printf("ģ�е��� ���̻� �ö��� �ʽ��ϴ�.\n");
			}
		}
		Sleep(500);
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

	int dice = random(6);

	switch (tmp) {
	case 0:
		//�̻��� �߸�����.. Interfuc ������ 4�� �ƴ� 5�� �ִ°� ����.
		Interfuc(player, dice, 0, 5);
		break;
	case 1:
		Interfuc(player, dice, 1, 5);
		break;
	}

	printf("���� ģ�е�: %d\n", player->fLevel);
	Sleep(500);
}

void PrintIntro(PLAYER* player) {
	printf("****�߿��̿� ����****\n");
	Sleep(500);
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	Sleep(500);

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
	Sleep(2500);

	system("cls");
}

void CatSoupMessage(PLAYER player) {

	int dice = random(3);

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
	Sleep(500);
}

int CatMove(PLAYER* player) {

	dice = random(6);
	//ȣ���� ����. ����ü�� ����� ������ define�� ����� �� ������..
	target = 6 - player->fLevel;

	// Ÿ�ٰ� ���ų� ���� ��
	if (dice >= target) {
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
			player->soup_n++;
			return 1;
		}
	}
	//Ÿ�ٺ��� ���� ��
	else {
		//���� �ƴ� ��
		if (cat > HME_POS) {
			beforecat = cat;
			cat--;
			ordernum = 2;
		}
		//���� ��
		else {
			beforecat = NULL;
			ordernum = 3;
		}
	}
	return 0;
}

void PrintStatusCat() {

	switch (ordernum) {
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
	Sleep(500);
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
	Sleep(500);
}

int main() {
	srand((unsigned int)time(NULL));

	PLAYER player = { NULL, 0, 0 };

	PrintIntro(&player);

	while (1) {
		PrintStatus(player);

		int SoupPrint = CatMove(&player);

		PrintStatusRoomMove(player);

		PrintStatusCat();

		if (SoupPrint == 1) {
			CatSoupMessage(player);
		}

		PrintMap();

		Interaction(&player);

		Sleep(2500); //2.5�� ���
		system("cls");
	}

	free(player.name);

	return 0;
}