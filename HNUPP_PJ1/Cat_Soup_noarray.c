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

//고양이 시작 죄표
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;
bool beforehomestate = false;

char CatItem[ITEM_NUM][50] = { "스크래쳐","캣타워" };
int CatItemPlace[ITEM_NUM] = { -1, -1 }; //놀거리. 배치 안되어 있을 때(-1)

typedef struct {
	char* name;
	int soup_n;
	int RLevel;
	int CP;
	int Feel;
} PLAYER;

void PrintStatusRoomMove(PLAYER player) {
	printf("%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", player.name);
	ST;
	printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", target);
	ST;
	printf("주사위를 굴립니다.또르륵...\n");
	ST;
	printf("%d이(가) 나왔습니다!\n", dice);
	ST;
}

void PrintStatusFeel(PLAYER *player){

	int dice = Random(6);

	printf("%d - %d : 주사위의 눈이 %d 이하이면 그냥 기분이 나빠집니다.\n", DICE, player->RLevel, DICE - player->RLevel);
	ST;
	printf("주사위를 굴립니다. 또르르..\n");
	ST;
	printf("%d이(가) 나왔습니다.\n", dice);
	ST;

	int decision_base = DICE - player->RLevel;
	if (dice > decision_base) {
		printf("기분이 나빠지지 않았습니다.\n");
	}
	else {
		printf("쫀떡이의 기분이 나빠집니다 : ");
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

	printf("==================== 현재 상태 ====================\n");
	printf("현재까지 만든 수프 : %d\n", player.soup_n);

	printf("CP : %d 포인트\n쫀떡이 기분(0~3): %d\n\t", player.CP, player.Feel);
	switch (player.Feel) {
	case 0:
		printf("기분이 매우 나쁩니다\n");
		break;
	case 1:
		printf("심심해합니다.\n");
		break;
	case 2:
		printf("식빵을 굽습니다.\n");
		break;
	case 3:
		printf("골골송을 부릅니다.\n");
		break;
	}

	printf("집사와의 관계(0~4) : %d\n", player.RLevel);
	switch (player.RLevel) {
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

int Random(int max) {
	return rand() % max + 1;
}

//mode 0->아무것도 하지 않기, 1->긁어주기
void Interfuc(PLAYER* player, int dice, int mode, int range) {
	if (mode == 0) {
		printf("아무것도 하지 않습니다.\n");
		ST;
		printf("4/6 확률로 친밀도가 떨어집니다.\n");
		ST;
		printf("주사위를 굴립니다.또르륵...\n");
	}
	else {
		printf("%s의 턱을 긁어주었습니다.\n", player->name);
		ST;
		printf("2/6의 확률로 친밀도가 높아집니다.\n");
		ST;
		printf("주사위를 굴립니다.또르륵...\n");
	}
	ST;

	printf("%d이(가) 나왔습니다!\n", dice);
	ST;

	if (dice < range) {
		if (mode == 0) {
			if (player->RLevel > 0) {
				printf("친밀도가 떨어집니다.\n");
				player->RLevel--;
			}
			else {
				printf("친밀도는 더이상 떨어지지 않습니다..\n");
			}
			ST;
		}
		else {
			printf("친밀도는 그대로입니다..\n");
			ST;
		}
	}
	else {
		if (mode == 0) {
			printf("다행히 친밀도가 떨어지지 않았습니다.\n");
		}
		else {
			if (player->RLevel < 4) {
				printf("친밀도가 높아집니다.\n");
				player->RLevel++;
			}
			else {
				printf("친밀도는 더이상 올라가지 않습니다.\n");
			}
		}
		ST;
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

	int dice = Random(6);

	switch (tmp) {
	case 0:
		//이상을 잘못봐서.. Interfuc 구조상 4가 아닌 5를 넣는게 맞음.
		Interfuc(player, dice, 0, 5);
		break;
	case 1:
		Interfuc(player, dice, 1, 5);
		break;
	}

	printf("현재 친밀도: %d\n", player->RLevel);
	ST;
}

void PrintIntro(PLAYER* player) {
	printf("****야옹이와 수프****\n");
	ST;
	printf("      /\\_/\\\n /\\  / o o \\\n//\\\\ \\~(*)~/\n`  \\/   ^ /\n   | \\|| ||\n   \\ '|| ||\n    \\)()-())\n\n");
	ST;

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
	Sleep(1000);

	system("cls");
}

void CatSoupMessage(PLAYER player) {

	int dice = Random(3);

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
	ST;
}

void CatMoveToHome() {
	if (cat > HME_POS) {
		beforecat = cat;
		cat--;
		ordernum = 0;
		//ordernum = 2;
	}
	//끝일 때
	else {
		beforecat = NULL;
		ordernum = 3;
	}
}

int CatMoveToSoup(PLAYER *player) {
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
		return 1;
	}
}

int MoveToNearItem(int itmx) {
	//고양이와 아이템이 같은 장소에 없을 때
	if (cat != CatItemPlace[itmx]) {
		//같지 않고 고양이x가 더 클 때
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

	//가장 가까운 아이템 탐색
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlace[i] != -1) { 
			int dis = abs(CatItemPlace[i] - cat);
			if (dis < nearItemDis) {
				nearItemDis = dis;
				nearItemNum = i;
			}
		}
	}
	
	//아이템으로 이동
	MoveToNearItem(nearItemNum);

	//아이템 이름 출력위해 리턴
	return nearItemNum;
}

int CatMoveToItem() {
	int minusOneCount = 0;
	
	//배치된 놀거리가 있는지 확인.
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlace[i] == -1) minusOneCount++;
	}
	
	//모든 놀거리(Item)이(가) 없는 상황
	if (minusOneCount == ITEM_NUM) {
		return -1;
	}
	//놀거리가 있는 경우
	else {
		return NearItemCK();
	}
}

int CatMove(PLAYER* player) {

	dice = Random(6);
	//호감도 설정. 구조체로 만들어 버려서 define을 사용할 수 없었음..
	target = 6 - player->RLevel;

	int itemIndex = NULL;

	switch (player->Feel) {
	case 0:
		CatMoveToHome();
		printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", player->name);
		break;
	case 1:
		itemIndex = CatMoveToItem();
		if ( itemIndex != -1) {
			printf("%s은(는) 심심해서 %s쪽으로 이동합니다.\n", player->name, CatItem[itemIndex]);
		}
		else {
			printf("놀거리가 없어서 기분이 매우 나빠집니다");
			if (player->Feel == 0) {
				printf("기분이 최저치라 더이상 나빠지지 않습니다!");
			}
			else {
				printf("%d ->", player->Feel);
				player->Feel--;
				printf("%d\n", player->Feel);
			}
		}
		break;
	case 2:
		printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n", player->name);
		break;
	case 3:
		CatMoveToSoup(&player);
		printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", player->name);
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

	//Cp 기본값 3
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

		Sleep(2500); //2.5초 대기
		system("cls");
	}

	free(player.name);

	return 0;
}