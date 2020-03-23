#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>
#define SIZE 20 // ��ȭ��ȣ�� �뷮
#define DELAY 1000
// ��ȭ��ȣ�� ���� ���α׷� -> ��ȭ��ȣ�� ȭ�� -> 1.�˻� 2.�߰� 3.���� 4.���� 
/// (1)�˻�->�̸����� �˻��ϱ�, ��ȣ�� �˻��ϱ�(�չ�ȣ �޹�ȣ), �ּҷ� �˻��ϱ�. �̸��� 100�� �� ����. ///  
/// (2)�߰�->����ü �迭�� ���� �Ǵ� �����Ҵ� �� ����ü �迭�� ����. 
/// (3)����->������ �̸� ���� �� ����.,
/// (4)���� ����.

typedef struct {
	char Name[12];
	char TelNumber[30];
	int age;
}PhoneInfo;

typedef struct {
	PhoneInfo tel[SIZE];
	int n; // ��ȭ��ȣ�ο� ����� ��ȣ ��
}PhoneBook;

void menu(); // // ��ȭ��ȣ�� �޴�
void ShowList(PhoneBook *k); // ��ȭ��ȣ�� ������
void search(PhoneBook *k); // ��ȭ��ȣ�� �˻��ϱ�
int SearchByName(PhoneBook *k); // �̸����� �˻��ϱ�.
int SearchByAge(PhoneBook *k); // ���̷� �˻��ϱ�.
int SearchByTelNumber(PhoneBook *k); // ��ȭ��ȣ�� �˻��ϱ�
void insert(PhoneBook *k); // ��ȭ��ȣ�� �����ϱ�
void Delete(PhoneBook *k); // ��ȭ��ȣ�� �����ϱ�
void print(int a); // �Է��� ������ print
void TakeFront(PhoneBook *k, int n); // Delete�� �迭 ������ ����ִ� �Լ�.

int main() {
	PhoneBook pb;
	pb.n = 0; // ��ȭ��ȣ�� ���� 0���� �ʱ�ȭ.

	while (1) {
		menu();
		printf("\n���� ����� ��ȭ��ȣ�� ���� : %d\n", pb.n);

		switch (_getch()) {
		case '1': ShowList(&pb); break;
		case '2': search(&pb); break;
		case '3': insert(&pb); break;
		case '4': Delete(&pb); break;
		case '5': exit(0); break;
		default: printf("\n\n�߸��� ��ȣ�� �Է���ϴ�. �ٽ� �Է��ϼ���\n\n"); break;
		}
	}
}

void menu() { // �޴�
	system("cls");
	printf("---------- ��ȭ��ȣ�� ----------\n");
	printf("1. ��ȭ��ȣ ����ϱ� !! \n");
	printf("2. ��ȭ��ȣ �˻��ϱ� !! \n");
	printf("3. ��ȭ��ȣ �߰��ϱ� !! \n");
	printf("4. ��ȭ��ȣ �����ϱ� !! \n");
	printf("5. ��ȭ��ȣ�� ���� !! \n");
}

void ShowList(PhoneBook *k) { //��ȭ��ȣ ����Ʈ Ȯ���ϱ�.
	int i = 0;
	system("cls");
	printf("    <    ��     ��     ��     ��    >\n");
	printf(" �������������������������������������� \n");

	for (i = 0; i < k->n; i++) {
		printf(" �̸�: %s   ����: %d    �ڵ�����ȣ: %s \n", k->tel[i].Name, k->tel[i].age, k->tel[i].TelNumber);
	}
	printf(" �������������������������������������� \n");
	printf("\n\t%d���Ŀ� �޴��� ���ư��ϴ�.\n", DELAY / 1000);
	Sleep(DELAY);
}

void search(PhoneBook *k) { // ��ȭ��ȣ �˻��ϱ�.
	int j = 0, i = 0;
	system("cls");
	while (1) {
		printf("    <    ��     ��     ��     ��    >\n");
		printf(" �������������������������������������� \n");
		printf("\n 1. �̸����� ã�� ");
		printf("\n 2. ���̷� ã�� ");
		printf("\n 3. ��ȭ��ȣ�� ã�� ");
		printf("\n 4. �޴��� ���ư��� \n");
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
		case '4': j = 1; break; // j�� �޴��� ���ư��� ���� ����
		default: printf("\n�߸��Է�!!   1 ~ 4 �߿��� �ϳ��� �������� "); break;
		}
		if (i == k->n)system("cls");
		if (j == 1)break;
	}
}
int SearchByName(PhoneBook *k) {
	int i = 0;
	char name3[12];
	printf(" �̸��� �Է��ϼ��� : ");
	scanf(" %s", &name3);
	print(2); // �˻��Ϸ� print
	for (i = 0; i < k->n; i++) {
		if (strcmp(name3, k->tel[i].Name) == 0) {
			printf("�̸� : %s\n", k->tel[i].Name);
			printf("���� : %d\n", k->tel[i].age);
			printf("��ȭ��ȣ : %s\n", k->tel[i].TelNumber);
			printf("\n");
			break;
		}
	}
	if (i == k->n) {
		printf(" �˻������ �����ϴ� !!\n");
		Sleep(DELAY);
	}
	return i;
}
int SearchByAge(PhoneBook *k) {
	int i, j = 0;
	int age3 = 0;
	printf(" ���̸� �Է��ϼ��� : ");
	scanf(" %d", &age3);
	print(2);
	for (i = 0; i < k->n; i++) {
		if (age3 == k->tel[i].age) {
			printf(" �̸� : %s\n", k->tel[i].Name);
			printf(" ���� : %d\n", k->tel[i].age);
			printf(" ��ȭ��ȣ : %s\n", k->tel[i].TelNumber);
			j = 1;
			printf("\n");
			break;
		}
	}
	if (j == 0) {
		printf(" �˻������ �����ϴ� !!\n");
	}
	return i;
}
int SearchByTelNumber(PhoneBook *k) {
	char TelNumber3[30];
	int i = 0;
	printf(" ��ȭ��ȣ�� �Է��ϼ��� : ");
	scanf(" %s", &TelNumber3);
	print(2);
	for (i = 0; i < k->n; i++) {
		if (strcmp(TelNumber3, k->tel[i].TelNumber) == 0) {
			printf("�̸� : %s\n", k->tel[i].Name);
			printf("���� : %d\n", k->tel[i].age);
			printf("��ȭ��ȣ : %s\n", k->tel[i].TelNumber);
			printf("\n");
			break;
		}
	}
	if (i == k->n) {
		printf(" �˻������ �����ϴ� !!\n");
		Sleep(DELAY);
	}
	return i;
}
void insert(PhoneBook *k) { // ��ȭ��ȣ �߰��ϱ�.
	int i = 0;
	int age2 = 0;
	char name2[12];
	char telnumber2[30];
	system("cls");

	printf("    <    ��     ��     ��     ��    >\n");
	printf(" �������������������������������������� \n");
	if (k->n == SIZE) {
		printf("��ȭ��ȣ�ΰ� ��á���ϴ�\n");
		printf(" �������������������������������������� \n");
	}
	else {
		printf("\n���� ����� ��� %d / %d\n", k->n, SIZE);
		printf("�̸�(�ִ� 5����) : "); scanf(" %s", &name2);
		printf("���� : "); scanf("%d", &age2);
		printf("�ڵ�����ȣ : "); scanf(" %s", &telnumber2); // ���๮�� ����ֱ� ���ؼ� %s�տ� ���� ǥ��.

		k->tel[(k->n)].age = age2;
		strcpy(k->tel[(k->n)].Name, name2);
		strcpy(k->tel[(k->n)].TelNumber, telnumber2);
		(k->n)++; //���� ����Ǿ��ִ� ��ȭ��ȣ�� �����
		print(0);
	}
}

void Delete(PhoneBook *k) { // ��ȭ��ȣ �����ϱ�.
	char delname[12], deltelname[30];
	int i = 0; // �˻� �� �ش��ε���. -> �� �ε����� �ش� ����ü�� ���� ������ ��.
	int m = 0; // 1�� or 2��
	system("cls");
	printf("    <    ��     ��     ��     ��    >\n");
	printf(" �������������������������������������� \n");
	if (k->n == 0) { // ��ȭ��ȣ�ΰ� ����� ��.
		printf("  ������ ��ȭ��ȣ�ΰ� �����ϴ�\n");
		printf(" �������������������������������������� \n");
		printf("\n\t%d���Ŀ� �޴��� ���ư��ϴ�.\n", DELAY / 1000);
		Sleep(DELAY);
	}
	else { // ��ȭ��ȣ�ΰ� �Ⱥ���� ��
		printf(" 1. �̸����� ã��\n");
		printf(" 2. ��ȭ��ȣ�� ã��\n");
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
			print(1); // �����Ϸ� print
			TakeFront(k, i);
			(k->n)--; // ��ü ��ȭ��ȣ�� ���� ����.
		}
		Sleep(DELAY);
	}
}

void TakeFront(PhoneBook *k, int m) { // ������ ��ȭ��ȣ�� ���� ������ �� �����.
	int i = 0;
	for (i = m; i < k->n; i++) {
		if (i == (k->n) - 1) {
			k->tel[i].age = 0;
			strcpy(k->tel[i].Name, "");
			strcpy(k->tel[i].TelNumber, "");
			break; // break�� ���� ������ null�迭�� �����ع����°� ����.
		}
		k->tel[i].age = k->tel[i + 1].age;
		strcpy(k->tel[i].Name, k->tel[i + 1].Name);
		strcpy(k->tel[i].TelNumber, k->tel[i + 1].TelNumber);
	}
}

void print(int a) { // �Է� �� ���� �� print 
	int i = 0;
	if (a == 0) { // �Է¿Ϸ� print
		printf("�Է¿Ϸ� !!!!\n"); printf("������");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf("����Ϸ� !!!!\n");
		printf("\n\t%d���Ŀ� �޴��� ���ư��ϴ�.\n", DELAY / 1000);
		Sleep(DELAY);
	}

	else if (a == 1) { // �����Ϸ� print     
		printf("�Է¿Ϸ� !!!!\n"); printf("������");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf("�����Ϸ� !!!!\n");
		printf("\n\t%d���Ŀ� �޴��� ���ư��ϴ�.\n", DELAY / 1000);
		Sleep(DELAY);
	}
	else {// �˻��ϱ� print
		printf("�Է¿Ϸ� !!!!\n"); printf(" �˻���");
		for (i = 0; i < 4; i++) {
			Sleep(DELAY / 3); printf(" . ");
		}
		printf(" �˻��Ϸ� !!!!\n");
		Sleep(DELAY);
	}
}