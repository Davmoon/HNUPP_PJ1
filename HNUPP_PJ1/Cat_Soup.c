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
	printf("%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", player.name);
	Sleep(500);
	printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", arr[1]);
	Sleep(500);
	printf("주사위를 굴립니다.또르륵...\n");
	Sleep(500);
	printf("%d이(가) 나왔습니다!\n", arr[0]);
	Sleep(500);
}

void PrintStatus(PLAYER player, char *script) {
	printf("==================== 현재 상태 ====================\n");
	printf("현재까지 만든 수프 : %d\n", player.soup_n);
	printf("집사와의 관계(0~4) : %d\n", player.fLevel);
	printf("  %s\n", script);
	printf("===================================================\n\n");
}

int random(int max) {
	return rand() % max + 1;
}

//mode 0->아무것도 하지 않기, 1->긁어주기
void Interfuc(PLAYER* player, int dice, int mode, int range) {
	if (mode == 0) {
		printf("아무것도 하지 않습니다.\n");
		Sleep(500);
		printf("4/6 확률로 친밀도가 떨어집니다.\n");
		Sleep(500);
		printf("주사위를 굴립니다.또르륵...\n");
	}
	else {
		printf("%s의 턱을 긁어주었습니다.\n", player->name);
		Sleep(500);
		printf("2/6의 확률로 친밀도가 높아집니다.\n");
		Sleep(500);
		printf("주사위를 굴립니다.또르륵...\n");
	}
	Sleep(500);

	printf("%d이(가) 나왔습니다!\n", dice);
	Sleep(500);

	if (dice < range) {
		if (mode == 0) {
			if (player->fLevel > 0) {
				printf("친밀도가 떨어집니다.\n");
				player->fLevel--;
			}
			else {
				printf("친밀도는 더이상 떨어지지 않습니다..\n");
			}
			Sleep(500);
		}
		else {
			printf("친밀도는 그대로입니다..\n");
			Sleep(500);
		}
	}
	else {
		if (mode == 0) {
			printf("다행히 친밀도가 떨어지지 않았습니다.\n");
		}
		else {
			if (player->fLevel < 4) {
				printf("친밀도가 높아집니다.\n");
				player->fLevel++;
			}
			else {
				printf("친밀도는 더이상 올라가지 않습니다.\n");
			}
		}
		Sleep(500);
	}
}

void Interaction(PLAYER *player) {
	//키보드 입력 함수 다시?
	int tmp;
	printf("어떤 상호작용을 하시겠습니까? 0. 아무것도 하지 않음    1. 긁어주기\n");

	do {
		printf(">> ");
		scanf_s("%d", &tmp);
	} while (tmp != 0 && tmp != 1);

	int dice = random(6);

	switch (tmp) {
		case 0:
			//이상을 잘못봐서.. Interfuc 구조상 4가 아닌 5를 넣는게 맞음.
			Interfuc(player, dice, 0, 5);
			break;
		case 1:
			Interfuc(player, dice, 1, 5);
			break;
	}

	printf("현재 친밀도: %d\n", player->fLevel);
	Sleep(500);
}

void PrintIntro(PLAYER *player) {
	printf("****야옹이와 수프****\n");
	Sleep(500);
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	Sleep(500);

	char name[50];

	printf("야옹이의 이름을 지어주세요 :");
	scanf_s("%49s", name, (unsigned)_countof(name));

	player->name = malloc(sizeof(name) + 1);
	if (player->name == NULL) {
		return;
	}

	//경고 잡고 싶은데..
	strcpy_s(player->name, sizeof(name), name);
	player->name[strlen(name)] = '\0';
	printf("야옹이의 이름은 %s입니다.\n", player->name);
	Sleep(2500);


	system("cls");
}

void CatSoupMSG(PLAYER player) {
	char *message_soup[] = {
		{"감자"},
		{"양송이"},
		{"브로콜리"}
	};

	char* soup = message_soup[random(2)];

	printf("%s이(가) %s 수프를 만들었습니다!\n\n", player.name, soup);
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

			//가독성이 안좋은데..
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
			printf("냄비쪽으로 움직입니다!\n\n");
			break;
		case 2:
			printf("실패했습니다 빠꾸합니다. \n\n");
			break;
		case 3:
			printf("아직 집에 있습니다... \n\n");
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

	//집 냄비, 고양이 출력
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
		{"곁에 오는 것조차 싫어합니다"},
		{"간식 자판기 취급입니다."},
		{"그럭저럭 쓸만한 집사입니다."},
		{"훌륭한 집사로 인정받고 있습니다."},
		{"집사 껌딱지입니다."}
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
		
		Sleep(3000); //2.5초 대기
		system("cls");
	}

	free(player.name);

	return 0;
}