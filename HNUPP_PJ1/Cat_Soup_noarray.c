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

//고양이 시작 죄표
int cat = 1, beforecat = NULL;
int dice = 0, target = 0, ordernum = 0;
bool beforehomestate = false;

//구조체로 바꾸면 좋겠는데;;
char CatItemThing[ITEM_NUM][50] = {"스크래쳐","캣타워"};
int CatItemPriceThing[ITEM_NUM] = { 4, 6 };
int CatItemPlaceThing[ITEM_NUM] = { -1, -1 };

char CatItemPlay[ITEM_NUM][50] = { "장난감 쥐", "레이저 포인터" };
int CatItemPricePlay[ITEM_NUM] = { 1, 2 };
int CatItemPlacePlay[ITEM_NUM] = { -1, -1 };

char CatItemFeelUpDialog[2][50] = { "조금", "제법" };

int CatItemFeelUpStatus[ITEM_NUM] = {1, 2};

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

	printf("==================== 현재 상태 ====================\n");
	printf("현재까지 만든 수프 : %d\n", player->soup_n);

	printf("CP : %d 포인트\n쫀떡이 기분(0~3): %d\n\t", player->CP, player->Feel);
	switch (player->Feel) {
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

	printf("집사와의 친밀도(0~4) : %d\n", player->RLevel);
	switch (player->RLevel) {
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
	int beforefeal = player->Feel;
	int beforeRLevel = player->RLevel;

	switch (mode) {
	case 0: //아무것도 안함

		if (player->Feel > 0) player->Feel--;

		printf("%s의 기분이 나빠졌습니다: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("주사위 눈이 5 이하이면 친밀도가 1 감소합니다.\n");
		ST;
		printf("주사위를 굴립니다. 또르륵...\n");
		ST;
		printf("%d이(가) 나왔습니다!\n", dice);
		ST;

		if (dice <= 5) {
			if (player->RLevel > 0) {
				player->RLevel--;
				printf("친밀도가 떨어집니다: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("친밀도는 더이상 떨어지지 않습니다: %d\n", player->RLevel);
			}
		}
		else {
			printf("다행히 친밀도는 그대로입니다: %d\n", player->RLevel);
		}
		break;

	case 1:// 긁기

		printf("%s의 턱을 긁어주었습니다.\n", player->name);
		ST;
		printf("%s의 기분은 그대로입니다: %d\n", player->name, player->Feel);
		ST;
		printf("2/6의 확률로 친밀도가 높아집니다.\n");
		ST;
		printf("주사위를 굴립니다... 또르륵...\n");
		ST;
		printf("%d이(가) 나왔습니다!\n", dice);
		ST;

		if (dice >= 5) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("친밀도가 높아집니다: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("친밀도는 이미 최대입니다: %d\n", player->RLevel);
			}
		}
		else {
			printf("친밀도는 그대로입니다: %d\n", player->RLevel);
		}
		break;

	case 2: //쥐
		if (player->Feel < 3) player->Feel++;

		printf("장난감 쥐로 %s와 놀아주었습니다. ", player->name);
		printf("%s의 기분이 조금 좋아졌습니다: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("주사위가 4 이상이면 친밀도가 1 증가합니다.\n");
		ST;
		printf("주사위를 굴립니다... 또르륵...\n");
		ST;
		printf("%d이(가) 나왔습니다!\n", dice);
		ST;

		if (dice >= 4) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("친밀도가 높아집니다: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("친밀도는 이미 최대입니다: %d\n", player->RLevel);
			}
		}
		else {
			printf("친밀도는 그대로입니다: %d\n", player->RLevel);
		}
		break;

	case 3: //레이저

		if (player->Feel <= 1) player->Feel += 2;
		else if (player->Feel == 2) player->Feel = 3;

		printf("레이저 포인터로 %s와 신나게 놀아주었습니다. ", player->name);
		printf("%s의 기분이 꽤 좋아졌습니다: %d -> %d\n", player->name, beforefeal, player->Feel);
		ST;
		printf("주사위가 2 이상이면 친밀도가 1 증가합니다.\n");
		ST;
		printf("주사위를 굴립니다... 또르륵...\n");
		ST;
		printf("%d이(가) 나왔습니다!\n", dice);
		ST;
		if (dice >= 2) {
			if (player->RLevel < 4) {
				player->RLevel++;
				printf("친밀도가 높아집니다: %d -> %d\n", beforeRLevel, player->RLevel);
			}
			else {
				printf("친밀도는 이미 최대입니다: %d\n", player->RLevel);
			}
		}
		else {
			printf("친밀도는 그대로입니다: %d\n", player->RLevel);
		}
		break;
	}
	ST;
}


void Interaction(PLAYER* player) {
	//키보드 입력 함수 다시?
	int tmp;
	printf("어떤 상호작용을 하시겠습니까?\n0. 아무것도 하지 않음\n1. 긁어주기\n");

	int menuitmindex[MAX_MENU_ITEM] = { NULL };
	int menunum = 2;

	//배치된 놀거리가 있는지 확인.
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
			printf("오류여. 다시 해봐랴\n");
		}
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

int CatMoveToHome(PLAYER *player) {
	if (cat > HME_POS) {
		beforecat = cat;
		cat--;
		//아무것도 출력 안함
		ordernum = 0;
		//ordernum = 2;
		return 0;
	}
	//끝일 때
	else {
		beforecat = NULL;
		//휴식해서 좋아짐
		if (player->Feel < 3) {
			player->Feel++;
			ordernum = 4;
			return 1;
		}
		return 1;
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

int MoveToNearItem(PLAYER* player, int itm) {
	//고양이와 아이템이 같은 장소에 없을 때
	if (cat != CatItemPlaceThing[itm]) {
		//같지 않고 고양이x가 더 클 때
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
			printf("%s은(는) %s를 긁고 놀았습니다.", player->name, CatItemThing[itm]);
			break;
		case 1:
			printf("%s은(는) %s를 뛰어다닙니다.", player->name, CatItemThing[itm]);
			break;
		}
		printf(" 기분이 %s 좋아졌습니다 :", CatItemFeelUpDialog[itm]);
		printf("%d ->", player->Feel);
		player->Feel += CatItemFeelUpStatus[itm];
		printf("%d\n", player->Feel);	
	}
}

int NearItemCK(PLAYER* player) {
	int nearItemNum = -1;
	int nearItemDis = INT_MAX;

	//가장 가까운 아이템 탐색
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlaceThing[i] != -1) {
			int dis = abs(CatItemPlaceThing[i] - cat);
			if (dis < nearItemDis) {
				nearItemDis = dis;
				nearItemNum = i;
			}
		}
	}
	
	//아이템으로 이동
	MoveToNearItem(player, nearItemNum);

	//아이템 이름 출력위해 리턴
	return nearItemNum;
}

int CatMoveToItem(PLAYER* player) {
	int minusOneCount = 0;
	
	//배치된 놀거리가 있는지 확인.
	for (int i = 0; i < ITEM_NUM; i++) {
		if (CatItemPlaceThing[i] == -1) minusOneCount++;
	}
	
	//모든 놀거리(Item)이(가) 없는 상황
	if (minusOneCount == ITEM_NUM) {
		return -1;
	}
	//놀거리가 있는 경우
	else {
		return NearItemCK(player);
	}
}

int CatMove(PLAYER* player) {

	dice = Random(6);
	//호감도 설정. 구조체로 만들어 버려서 define을 사용할 수 없었음..
	target = 6 - player->RLevel;

	int itemIndex = 0;
	int homeheal = 0;

	switch (player->Feel) {
	case 0:
		homeheal = CatMoveToHome(player);
		if (homeheal == 0) {
			printf("기분이 매우 나쁜 %s은(는) 집으로 향합니다.\n", player->name);
		}
		break;
	case 1:
		itemIndex = CatMoveToItem(player);
		if ( itemIndex != -1) {
			printf("%s은(는) 심심해서 %s쪽으로 이동합니다.\n", player->name, CatItemThing[itemIndex]);
		}
		else {
			printf("놀거리가 없어서 기분이 매우 나빠집니다");
			if (player->Feel == 0) {
				printf("기분이 최저치라 더이상 나빠지지 않습니다!");
			}
			else {
				printf( "%d -> ", player->Feel);
				player->Feel--;
				printf("%d\n", player->Feel);
			}
		}
		break;
	case 2:
		printf("%s은(는) 기분좋게 식빵을 굽고 있습니다.\n", player->name);
		break;
	case 3:
		CatMoveToSoup(player);
		printf("%s은(는) 골골송을 부르며 수프를 만들러 갑니다.\n", player->name);
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
		printf("냄비쪽으로 움직입니다!\n\n");
		break;
	case 2:
		printf("실패했습니다. 뒤로 돌아갑니다... \n\n");
		break;
	case 3:
		printf("아직 집에 있습니다... \n\n");
		break;
	case 4:
		printf("집에 도착하여 회복중입니다. 기분 : %d -> %d\n\n", player->Feel -1, player->Feel);
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

	printf("\n쫀떡의 기분(0~3): %d\n", player->Feel);
	printf("집사와의 친밀도(0~4): %d\n", player->RLevel);
	printf("쫀떡의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", player->CP);
	printf("보유 CP: %d 포인트\n\n", player->CP);
}

void Shop(PLAYER * player) {
	printf("상점에서 물건을 살 수 있습니다.\n어떤 물건을 구매할까요?\n");
	printf("0. 아무것도 사지 않는다.\n");

	for (int i = 0; i < ITEM_NUM; i++) {
		printf("%d. %s : %d CP", i + 1, CatItemPlay[i], CatItemPricePlay[i]);
		if (CatItemPlacePlay[i] != -1) {
			printf(" (품절)");
		}
		printf("\n");
	}

	for (int i = 0; i < ITEM_NUM; i++) {
		printf("%d. %s : %d CP", ITEM_NUM + i + 1, CatItemThing[i], CatItemPriceThing[i]);
		if (CatItemPlaceThing[i] != -1) {
			printf(" (품절)");
		}
		printf("\n");
	}

	int inputmp;

	do {
		printf(">> ");
		scanf_s("%d", &inputmp);

		if (inputmp == 0) {
			printf("물건을 사지 않았습니다.\n");
			break;
		}

		int ridx = inputmp - 1;

		if (ridx < ITEM_NUM) {
			if (CatItemPlacePlay[ridx] != -1) {
				printf("이미 구매한 장난감입니다.\n");
				break;
			}

			if (player->CP < CatItemPricePlay[ridx]) {
				printf("CP가 부족합니다.\n");
				break;
			}

			player->CP -= CatItemPricePlay[ridx];
			CatItemPlacePlay[ridx] = 0;
			printf("%s를 구매했습니다. 보유 CP: %d 포인트\n", CatItemPlay[ridx], player->CP);
		}
		else {
			int thingIdx = ridx - ITEM_NUM;

			if (CatItemPlaceThing[thingIdx] != -1) {
				printf("이미 구매한 가구입니다.\n");
				break;
			}

			if (player->CP < CatItemPriceThing[thingIdx]) {
				printf("CP가 부족합니다.\n");
				break;
			}

			player->CP -= CatItemPriceThing[thingIdx];
			printf("%s를 구매했습니다. 보유 CP: %d 포인트\n", CatItemThing[thingIdx], player->CP);

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
			printf("%s가 %d에 배치\n", CatItemThing[thingIdx], x);
		}

		break;

	} while (1);
	
}

int main() {
	srand((unsigned int)time(NULL));

	//Cp 기본값 3
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

		Sleep(2500); //2.5초 대기
		system("cls");
	}

	free(player.name);

	return 0;
}