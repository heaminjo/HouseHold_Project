#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//지출 데이터
struct Expend {
	char name[30];
	int price;
	int category;
	Expend* next;
};

//스택
struct Stack {
	Expend* data;
	Expend* top;
	int count;
	int money;
};

//스택 생성
Stack* create_Stack() {
	Stack* stack = new Stack;
	memset(stack, NULL, sizeof(stack));

	stack->count = stack->money = 0;

	return stack;
}
//메인메뉴
void mainMenu() {
	printf("\n");
	printf("=====메인메뉴======\n");
	printf("1. 지출작성\n");
	printf("2. 통계\n");
	printf("9.종료\n");
	printf("\n");
	printf("번호 선택:");
}

//지출 내용 생성
Expend* push() {
	char name[30];
	int price;
	int category;
	Expend* ex = new Expend;
	ex->next = NULL;

	printf("\n");
	printf("=====지출 내용 입력=====\n");
	printf("1.식비 / 2.건강 / 3.문화생활\n");
	printf("선택:");
	scanf_s("%d", &category);

	printf("소비 내용:");
	scanf_s("%s", name,sizeof(name));

	printf("지출금액:");
	scanf_s("%d", &price);

	ex->category = category;
	strcpy(ex->name, name);
	ex->price = price;

	return ex;
}

//메인 스택 추가
void add(Stack* stack,Expend*ex) {
	if (stack == 0) {
		stack->top = ex;
	}
	else {
		ex->next = stack->top;
		stack->top = ex;
	}
	stack->data = ex;
	stack->money += ex->price;
	stack->count++;
}

//상세 지출 목록 출력
void detail_Print(Stack* stack,char category[]) {
	printf("\n");
	printf("[%s 목록]\n", category);
	Expend* top = stack->top;

	for (int i = 0; i < stack->count; i++) {
		printf("소비내용:%s\n", top->name);
		printf("금액:%d\n",top->price);
		printf("----------------\n");
		top = top->next;
	}
}

//카테고리별 목록 출력
void print(Stack* main, Stack* food, Stack* health, Stack* life) {
	int select;

	printf("=====통계=====\n");
	printf("☆총 지출 금액☆:%d원\n", main->money);
	printf("\n");
	printf("[식비]:%d원\n", food->money);
	printf("[건강]:%d원\n", health->money);
	printf("[문화]:%d원\n", life->money);

	printf("\n");
	printf("---상세보기---\n");
	printf("1.식비 / 2.건강 / 3.문화 / 9.보지않음\n");
	printf("번호 선택:");
	scanf_s("%d",&select);

	switch (select)
	{
	case 1: {
		char cate[10] = "식비";
		detail_Print(food,cate);
		break;
	}
	case 2: {
		char cate[10] = "건강";
		detail_Print(health,cate);
		break;
	}
	case 3: {
		char cate[10] = "문화";
		detail_Print(life,cate);
		break;
	}
	case 9:
		printf("메인으로 돌아갑니다.\n");
		break;
	}
}
int main(void) {
	int select;
	Stack* main = create_Stack();
	Stack* food = create_Stack();
	Stack* health = create_Stack();
	Stack* life = create_Stack();

	while (1) {
		mainMenu();
		scanf_s("%d", &select);
		switch (select)
		{
		case 1: {                //지출 목록 추가
			Expend* ex = NULL;
			ex = push();
			add(main, ex);

			if (ex->category == 1) {
				add(food, ex);
			}
			else if (ex->category == 2) {
				add(health, ex);
			}
			else if (ex->category == 3) {
				add(life, ex);
			}
			break;
		}
		case 2: {                  //지출 목록 출력
			print(main,food,health,life);
		}
		
		}
		system("pause");   // 잠시 멈추고
		system("cls");     //화면을 지우기

	}
	return 0;
}
