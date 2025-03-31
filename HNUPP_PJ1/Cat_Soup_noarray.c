#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define ROOM_WIDTH 6
#define ROOM_HEIGHT 4
#define HME_POS 1
#define BWL_PO (ROOM_WIDTH - 2)

//고양이 시작 죄표
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;

typedef struct {
	char* name;
	int soup_n;
	int fLevel;
} PLAYER;

void PrintStatusRoomMove(PLAYER player) {
	printf("%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", player.name);
	Sleep(500);
	printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", target);
	Sleep(500);
	printf("주사위를 굴립니다.또르륵...\n");
	Sleep(500);
	printf("%d이(가) 나왔습니다!\n", dice);
	Sleep(500);
}

void PrintStatus(PLAYER player) {

	printf("==================== 현재 상태 ====================\n");
	printf("현재까지 만든 수프 : %d\n", player.soup_n);
	printf("집사와의 관계(0~4) : %d\n", player.fLevel);
	switch (player.fLevel) {
	case 0:
		printf("곁에 오는 것조차 싫어합니다\n");
		break;
	case 1:
		printf("간식 자판기 취급입니다.\n");
		break;
	case 2:
		printf("그럭저럭 쓸만한 집사입니다.\n");
		break;
	case 3:
		printf("훌륭한 집사로 인정받고 있습니다.\n");
		break;
	case 4:
		printf("집사 껌딱지입니다.\n");
		break;
	}
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

void Interaction(PLAYER* player) {
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

void PrintIntro(PLAYER* player) {
	printf("****야옹이와 수프****\n");
	Sleep(500);
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	Sleep(500);

	char name[50];

	printf("야옹이의 이름을 지어주세요 :");
	scanf_s("%49s", name, (unsigned)_countof(name));

	player->name = malloc(strlen(name) + 1);
	if (player->name == NULL) {
		return;
	}

	//경고 잡고 싶은데..
	strcpy_s(player->name, strlen(name) + 1, name);
	player->name[strlen(name)] = '\0';
	printf("야옹이의 이름은 %s입니다.\n", player->name);
	Sleep(2500);

	system("cls");
}

void CatSoupMessage(PLAYER player) {

	int dice = random(3);

	switch (dice) {
	case 1:
		printf("%s이(가) 감자 수프를 만들었습니다!\n\n", player.name);
		break;
	case 2:
		printf("%s이(가) 양송이 수프를 만들었습니다!\n\n", player.name);
		break;
	case 3:
		printf("%s이(가) 브로콜리 수프를 만들었습니다!\n\n", player.name);
		break;
	}
	Sleep(500);
}

int CatMove(PLAYER* player) {

	dice = random(6);
	//호감도 설정. 구조체로 만들어 버려서 define을 사용할 수 없었음..
	target = 6 - player->fLevel;

	// 타겟과 같거나 높을 때
	if (dice >= target) {
		//끝이 아닐 때
		if (cat < BWL_PO) {
			beforecat = cat;
			cat++;
			ordernum = 1;
			if (cat == BWL_PO) {
				player->soup_n++;
				return 1;
			}
		}
		//끝일 때
		else {
			beforecat = NULL;
			player->soup_n++;
			return 1;
		}
	}
	//타겟보다 작을 때
	else {
		//끝이 아닐 때
		if (cat > HME_POS) {
			beforecat = cat;
			cat--;
			ordernum = 2;
		}
		//끝일 때
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
		printf("냄비쪽으로 움직입니다!\n\n");
		break;
	case 2:
		printf("실패했습니다. 뒤로 돌아갑니다... \n\n");
		break;
	case 3:
		printf("아직 집에 있습니다... \n\n");
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

		Sleep(2500); //2.5초 대기
		system("cls");
	}

	free(player.name);

	return 0;
}