#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 4
#define ROOM_HEIGHT 4
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)

char room[ROOM_HEIGHT][ROOM_WIDTH];

int cat = 1;

typedef struct {
	char *name;
	int soup_n;
	int fLevel;
} PLAYER;

void PrintStatusRoomMove(int* arr, PLAYER player) {
	printf("%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", player.name);
	Sleep(500);
	printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", arr[1]);
	Sleep(500);
	printf("�ֻ����� �����ϴ�.�Ǹ���...\n");
	Sleep(500);
	printf("%d��(��) ���Խ��ϴ�!\n", arr[0]);
	Sleep(500);
}

void PrintStatus(PLAYER player, char *script) {
	printf("==================== ���� ���� ====================\n");
	printf("������� ���� ���� : %d\n", player.soup_n);
	printf("������� ����(0~4) : %d\n", player.fLevel);
	printf("  %s\n", script);
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

void Interaction(PLAYER *player) {
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

void PrintIntro(PLAYER *player) {
	printf("****�߿��̿� ����****\n");
	Sleep(500);
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	Sleep(500);

	char name[50];

	printf("�߿����� �̸��� �����ּ��� :");
	scanf_s("%49s", name, (unsigned)_countof(name));

	player->name = malloc(sizeof(name) + 1);
	if (player->name == NULL) {
		return;
	}

	//��� ��� ������..
	strcpy_s(player->name, sizeof(name), name);
	player->name[strlen(name)] = '\0';
	printf("�߿����� �̸��� %s�Դϴ�.\n", player->name);
	Sleep(2500);


	system("cls");
}

void CatSoupMSG(PLAYER player) {
	char *message_soup[] = {
		{"����"},
		{"�����"},
		{"����ݸ�"}
	};

	char* soup = message_soup[random(2)];

	printf("%s��(��) %s ������ ��������ϴ�!\n\n", player.name, soup);
	Sleep(500);
}

int CatMove(int* arr, PLAYER* player) {

	int dice = random(6);
	int target = 6 - player->fLevel;

	arr[0] = dice, arr[1] = target;

	if (dice >= target) {
		if (room[2][cat + 1] != '#') {
			room[2][cat] = '.';
			cat++;
			room[2][cat] = 'C';

			//�������� ��������..
			arr[2] = 1;
			if (room[1][cat] == 'B') {
				player->soup_n++;
				return 1;
			}
		}
		else {
			player->soup_n++;
			return 1;
		}
	}
	else {
		if (room[2][cat-1] != '#') {
			room[2][cat] = ' ';
			cat--;
			room[2][cat] = 'C';

			arr[2] = 2;
		}
		else {
			arr[2] = 3;
		}
	}
	return 0;
}

void PrintStatusCat(int* arr) {
	int ordernum = arr[2];

	switch (ordernum) {
		case 1:
			printf("���������� �����Դϴ�!\n\n");
			break;
		case 2:
			printf("�����߽��ϴ� �����մϴ�. \n\n");
			break;
		case 3:
			printf("���� ���� �ֽ��ϴ�... \n\n");
			break;
	}
	arr[3] = 0;
	Sleep(500);
}

void CreateMap() {
	for (int i = 0; i < ROOM_HEIGHT; i++) {
		for (int j = 0; j < ROOM_WIDTH; j++) {
			room[i][j] = ' ';
		}
	}

	for (int i = 0; i < ROOM_HEIGHT; i++) {
		room[i][0] = room[i][ROOM_WIDTH - 1] = '#';

		for (int j = 1;  j < ROOM_WIDTH -1; j++)
			room[i][j] = (i == 0 || i == ROOM_HEIGHT -1) ? '#' : ' ';
	}

	//�� ����, ����� ���
	room[1][HME_POS] = 'H';
	room[1][BWL_PO] = 'B';
	room[2][cat] = 'C';
}

void PrintRoom(){
	for (int i = 0; i < ROOM_HEIGHT; i++) {
		for (int j = 0; j < ROOM_WIDTH; j++) {
			printf("%c", room[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	Sleep(500);
}

int main() {
	srand((unsigned int)time(NULL));

	char *message[] = {
		{"�翡 ���� ������ �Ⱦ��մϴ�"},
		{"���� ���Ǳ� ����Դϴ�."},
		{"�׷����� ������ �����Դϴ�."},
		{"�Ǹ��� ����� �����ް� �ֽ��ϴ�."},
		{"���� �������Դϴ�."}
	};

	PLAYER player = { 0, 0 };

	int arr[3] = { 0 };

	PrintIntro(&player);

	CreateMap();

	while (1) {
		PrintStatus(player, message[player.fLevel]);

		int SoupPrint = CatMove(arr, &player);

		PrintStatusRoomMove(arr, player);

		PrintStatusCat(arr);

		if (SoupPrint == 1) {
			CatSoupMSG(player);
		}
		
		PrintRoom();

		Interaction(&player);
		
		Sleep(3000); //2.5�� ���
		system("cls");
	}

	free(player.name);

	return 0;
}