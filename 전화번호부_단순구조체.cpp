#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#define SIZE 20 // 전화번호부 용량
#define DELAY 1000
// 전화번호부 관리 프로그램 -> 전화번호부 화면 -> 1.검색 2.추가 3.삭제 4.종료 
/// (1)검색->이름으로 검색하기, 번호로 검색하기(앞번호 뒷번호), 주소로 검색하기. 이름만 100개 쭉 나옴. ///  
/// (2)추가->구조체 배열에 저장 또는 동적할당 후 구조체 배열에 저장. 
/// (3)삭제->삭제할 이름 선택 후 삭제.,
/// (4)종료 끄기.

typedef struct {
	char Name[12];
	char TelNumber[30];
	int age;
}PhoneInfo;

typedef struct {
	PhoneInfo tel[SIZE];
	int n; // 전화번호부에 저장된 번호 수
}PhoneBook;

void menu(); // // 전화번호부 메뉴
void ShowList(PhoneBook *k); // 전화번호부 목록출력
void search(PhoneBook *k); // 전화번호부 검색하기
int SearchByName(PhoneBook *k); // 이름으로 검색하기.
int SearchByAge(PhoneBook *k); // 나이로 검색하기.
int SearchByTelNumber(PhoneBook *k); // 전화번호로 검색하기
void insert(PhoneBook *k); // 전화번호부 삽입하기
void Delete(PhoneBook *k); // 전화번호부 삭제하기
void print(int a); // 입력후 삭제후 print
void TakeFront(PhoneBook *k, int n); // Delete시 배열 앞으로 당겨주는 함수.

int main() {
	PhoneBook pb;
	pb.n = 0; // 전화번호부 갯수 0으로 초기화.

	while (1) {
		menu();
		printf("\n현재 저장된 전화번호부 숫자 : %d\n", pb.n);

		switch (_getch()) {
		case '1': ShowList(&pb); break;
		case '2': search(&pb); break;
		case '3': insert(&pb); break;
		case '4': Delete(&pb); break;
		case '5': exit(0); break;
		default: printf("\n\n잘못된 번호가 입력됬습니다. 다시 입력하세요\n\n"); break;
		}
	}
}

void menu() { // 메뉴
	system("cls");
	printf("---------- 전화번호부 ----------\n");
	printf("1. 전화번호 출력하기 !! \n");
	printf("2. 전화번호 검색하기 !! \n");
	printf("3. 전화번호 추가하기 !! \n");
	printf("4. 전화번호 삭제하기 !! \n");
	printf("5. 전화번호부 종료 !! \n");
}

void ShowList(PhoneBook *k) { //전화번호 리스트 확인하기.
	int i = 0;
	system("cls");
	printf("    <    저     장     목     록    >\n");
	printf(" ─────────────────── \n");

	for (i = 0; i < k->n; i++) {
		printf(" 이름: %s   나이: %d    핸드폰번호: %s \n", k->tel[i].Name, k->tel[i].age, k->tel[i].TelNumber);
	}
	printf(" ─────────────────── \n");
	printf("\n\t%d초후에 메뉴로 돌아갑니다.\n", DELAY / 1000);
	Sleep(DELAY);
}

void search(PhoneBook *k) { // 전화번호 검색하기.
	int j = 0, i = 0;
	system("cls");
	while (1) {
		printf("    <    검     색     하     기    >\n");
		printf(" ─────────────────── \n");
		printf("\n 1. 이름으로 찾기 ");
		printf("\n 2. 나이로 찾기 ");
		printf("\n 3. 전화번호로 찾기 ");
		printf("\n 4. 메뉴로 돌아가기 \n");
		switch (_getch()) {
		case '1': {
			i = SearchByName(k);
		}break;
		case '2': {
			i = SearchByAge(k);
		}break;
		case '3': {
			i = SearchByTelNumber(k);
		}break;
		case '4': j = 1; break; // j는 메뉴로 돌아가기 위한 변수
		default: printf("\n잘못입력!!   1 ~ 4 중에서 하나만 누르세요 "); break;
		}
		if (i == k->n)system("cls");
		if (j == 1)break;
	}
}
int SearchByName(PhoneBook *k) {
	int i = 0;
	char name3[12];
	printf(" 이름을 입력하세요 : ");
	scanf(" %s", &name3);
	print(2); // 검색완료 print
	for (i = 0; i < k->n; i++) {
		if (strcmp(name3, k->tel[i].Name) == 0) {
			printf("이름 : %s\n", k->tel[i].Name);
			printf("나이 : %d\n", k->tel[i].age);
			printf("전화번호 : %s\n", k->tel[i].TelNumber);
			printf("\n");
			break;
		}
	}
	if (i == k->n) {
		printf(" 검색결과가 없습니다 !!\n");
		Sleep(DELAY);
	}
	return i;
}
int SearchByAge(PhoneBook *k) {
	int i, j = 0;
	int age3 = 0;
	printf(" 나이를 입력하세요 : ");
	scanf(" %d", &age3);
	print(2);
	for (i = 0; i < k->n; i++) {
		if (age3 == k->tel[i].age) {
			printf(" 이름 : %s\n", k->tel[i].Name);
			printf(" 나이 : %d\n", k->tel[i].age);
			printf(" 전화번호 : %s\n", k->tel[i].TelNumber);
			j = 1;
			printf("\n");
			break;
		}
	}
	if (j == 0) {
		printf(" 검색결과가 없습니다 !!\n");
	}
	return i;
}
int SearchByTelNumber(PhoneBook *k) {
	char TelNumber3[30];
	int i = 0;
	printf(" 전화번호를 입력하세요 : ");
	scanf(" %s", &TelNumber3);
	print(2);
	for (i = 0; i < k->n; i++) {
		if (strcmp(TelNumber3, k->tel[i].TelNumber) == 0) {
			printf("이름 : %s\n", k->tel[i].Name);
			printf("나이 : %d\n", k->tel[i].age);
			printf("전화번호 : %s\n", k->tel[i].TelNumber);
			printf("\n");
			break;
		}
	}
	if (i == k->n) {
		printf(" 검색결과가 없습니다 !!\n");
		Sleep(DELAY);
	}
	return i;
}
void insert(PhoneBook *k) { // 전화번호 추가하기.
	int i = 0;
	int age2 = 0;
	char name2[12];
	char telnumber2[30];
	system("cls");

	printf("    <    추     가     하     기    >\n");
	printf(" ─────────────────── \n");
	if (k->n == SIZE) {
		printf("전화번호부가 꽉찼습니다\n");
		printf(" ─────────────────── \n");
	}
	else {
		printf("\n현재 저장된 사람 %d / %d\n", k->n, SIZE);
		printf("이름(최대 5글자) : "); scanf(" %s", &name2);
		printf("나이 : "); scanf("%d", &age2);
		printf("핸드폰번호 : "); scanf(" %s", &telnumber2); // 개행문자 비워주기 위해서 %s앞에 공백 표시.

		k->tel[(k->n)].age = age2;
		strcpy(k->tel[(k->n)].Name, name2);
		strcpy(k->tel[(k->n)].TelNumber, telnumber2);
		(k->n)++; //현재 저장되어있는 전화번호부 사람수
		print(0);
	}
}

void Delete(PhoneBook *k) { // 전화번호 삭제하기.
	char delname[12], deltelname[30];
	int i = 0; // 검색 후 해당인덱스. -> 그 인덱스로 해당 구조체의 값을 삭제를 함.
	int m = 0; // 1번 or 2번
	system("cls");
	printf("    <    삭     제     하     기    >\n");
	printf(" ─────────────────── \n");
	if (k->n == 0) { // 전화번호부가 비었을 때.
		printf("  삭제할 전화번호부가 없습니다\n");
		printf(" ─────────────────── \n");
		printf("\n\t%d초후에 메뉴로 돌아갑니다.\n", DELAY / 1000);
		Sleep(DELAY);
	}
	else { // 전화번호부가 안비었을 때
		printf(" 1. 이름으로 찾기\n");
		printf(" 2. 전화번호로 찾기\n");
		switch (_getch()) {
		case '1': {
			i = SearchByName(k);
		}break;
		case '2': {
			i = SearchByTelNumber(k);
		}break;
		}
		printf("\n");
		if (i < (k->n)) {
			print(1); // 삭제완료 print
			TakeFront(k, i);
			(k->n)--; // 전체 전화번호부 숫자 감소.
		}
		Sleep(DELAY);
	}
}

void TakeFront(PhoneBook *k, int m) { // 삭제시 전화번호부 내용 앞으로 다 당겨줌.
	int i = 0;
	for (i = m; i < k->n; i++) {
		if (i == (k->n) - 1) {
			k->tel[i].age = 0;
			strcpy(k->tel[i].Name, "");
			strcpy(k->tel[i].TelNumber, "");
			break; // break를 쓰는 이유는 null배열을 참조해버리는걸 방지.
		}
		k->tel[i].age = k->tel[i + 1].age;
		strcpy(k->tel[i].Name, k->tel[i + 1].Name);
		strcpy(k->tel[i].TelNumber, k->tel[i + 1].TelNumber);
	}
}

void print(int a) { // 입력 후 삭제 후 print 
	int i = 0;
	if (a == 0) { // 입력완료 print
		printf("입력완료 !!!!\n"); printf("저장중");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf("저장완료 !!!!\n");
		printf("\n\t%d초후에 메뉴로 돌아갑니다.\n", DELAY / 1000);
		Sleep(DELAY);
	}

	else if (a == 1) { // 삭제완료 print     
		printf("입력완료 !!!!\n"); printf("삭제중");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf("삭제완료 !!!!\n");
		printf("\n\t%d초후에 메뉴로 돌아갑니다.\n", DELAY / 1000);
		Sleep(DELAY);
	}
	else {// 검색하기 print
		printf("입력완료 !!!!\n"); printf(" 검색중");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf(" 검색완료 !!!!\n");
		Sleep(DELAY);
	}
}