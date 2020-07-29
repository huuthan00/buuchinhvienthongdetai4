#pragma once
#include "SinhVien.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXLISTLOP 500
#define MAXTHUOCTINHLOP 3
#define MAXTHUOCTINHSINHVIEN 5
#define MAXTHUOCTINHDIEM 2
#define MAXLENGTHNIENKHOA 10
#define DELIMITERLOPVOISINHVIEN "/"
#define DELIMITERSINHVIEN "]"
#define DELIMITERDIEM "}"
#define DELIMITERSINHVIENVSDIEM "["
#define DELIMITERTHUOCTINH "|"
#define FILELOP "Lop.txt"
#define FILEMONHOC "monhoc.txt"
#define FILEKETQUATHI "ketquathi.txt"
#define TRUE 1
#define FALSE 0

struct Lop {
	char MaLop[15];
	char NienKhoa[15];
	char TenLop[50];
	PTR_SinhVien ptr_dsSinhVien;
};

typedef Lop* PTR_Lop;

struct ListLop {
	int n = 0;					// so nut cua danh sach
	PTR_Lop data[MAXLISTLOP];	// danh sach mang 1 chieu con tro Lop (PTR_Lop)
};

struct NienKhoadata {
	int vitridau;
	int vitricuoi;
	char NienKhoa[15];
};

struct ListNienKhoa {
	int n = 0;
	NienKhoadata data[MAXLISTLOP];
};

int Empty_Lop(ListLop ds) {
	return ds.n == 0;
}

int Full_Lop(ListLop ds) {
	return ds.n == MAXLISTLOP;
}

int isValidMaLop(char MaLop[15]) {

	if (strlen(MaLop) <= 0) return 0;

	for (int i = 0; i < strlen(MaLop); i++)
	{
		if (!((MaLop[i] >= 'A' && MaLop[i] <= 'Z') || MaLop[i] >= '0' && MaLop[i] <= '9' || MaLop[i] == '-')) {
			return 0;
		}
	}
	return 1;
}

//Format DDDD-DDDD
int isValidNienKhoa(char NienKhoa[MAXLENGTHNIENKHOA]) {
	if (strlen(NienKhoa) != MAXLENGTHNIENKHOA - 1) return 0;

	for (int i = 0; i <= 3; i++)
	{
		if (!(NienKhoa[i] >= '0' && NienKhoa[i] <= '9')) {
			return 0;
		}
	}

	if (NienKhoa[4] != '-') return 0;

	for (int i = 5; i <= 8; i++)
	{
		if (!(NienKhoa[i] >= '0' && NienKhoa[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

int Search_Lop_theo_MaLop(ListLop& ds, char MaLop[15]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(MaLop, ds.data[i]->MaLop) == 0) {
			return i;
		}
	}
	return -1;
}

int Insert_Item_Lop(ListLop& ds, int i, PTR_Lop info) {
	int j;
	if (i < 0 || i > ds.n || Full_Lop(ds))
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = info;
	ds.n++;
	return 1;
}

int Delele_Item_Lop(ListLop& ds, int i) {
	int j;
	if (i < 0 || i >= ds.n || Empty_Lop(ds))
		return 0;
	for (j = i + 1; j < ds.n; j++) {
		ds.data[j - 1] = ds.data[j];
	}
	ds.n--;
	return 1;
}

int Update_Item_Lop(ListLop& dsLop, int i) {

	if (i < 0 || i >= dsLop.n || Empty_Lop(dsLop))
		return 0;
	//char MaLoptemp[15];

	//while (1) {
	//	printf("Ma Lop (Toi da 14 ky tu chi chua ky tu A->Z va 0->9): ");
	//	gets_s(MaLoptemp);
	//	if (isValidMaLop(MaLoptemp)) {
	//		if (Search_Lop_theo_MaLop(dsLop, MaLoptemp) < 0) {
	//			strcpy_s(dsLop.data[i]->MaLop, 15, MaLoptemp);
	//			break;
	//		}
	//		else {
	//			printf("Ma Lop da ton tai!\n\n");
	//		}
	//	}
	//	else {
	//		printf("Ma Lop khong hop le! Vui long nhap lai.\n\n");
	//	}
	//}

	while (1) {
		printf("Ten Lop (Toi da 49 ky tu): ");
		gets_s(dsLop.data[i]->TenLop);
		if (strlen(dsLop.data[i]->TenLop) > 0) {
			break;
		}
		else {
			printf("Ten Lop khong duoc rong! Vui long nhap lai.\n\n");
		}
	}

	while (1) {
		printf("Nien khoa (Toi da 10 ky tu, DDDD-DDDD): ");
		gets_s(dsLop.data[i]->NienKhoa);
		if (isValidNienKhoa(dsLop.data[i]->NienKhoa)) {
			break;
		}
		else {
			printf("Nien khoa khong dung dinh dang!\n\n");
		}
	}

	return 1;
}

PTR_SinhVien Search_SinhVien_DSLop_MaSV(ListLop ds, char masv[15], int& stt) {
	//SinhVien sv;
	for (int i = 0; i < ds.n; i++) {
		PTR_SinhVien p_SinhVien = Search_SinhVien_MaSV(ds.data[i]->ptr_dsSinhVien, masv);
		if (p_SinhVien != NULL) {
			stt = i;
			return p_SinhVien;
		}
		/*if (strlen(sv.masv) > 0) {
			stt = i;
			return sv;
		}*/
	}
	stt = -1;
	return NULL;
}

void In_DS_Lop(ListLop ds) {
	if (Empty_Lop(ds)) {
		printf("Danh sach rong!\n");
		return;
	}
	printf("%-6s%-14s %-14s %s\n", "STT", "Ma Lop", "Nien Khoa", "Ten Lop");
	printf("------------------------------------------------------\n");
	for (int i = 0; i < ds.n; i++) {
		printf("%-6d|%-14s|%-14s|%s\n", i + 1, ds.data[i]->MaLop, ds.data[i]->NienKhoa, ds.data[i]->TenLop);
	}
}

void In_DS_Lop_Theo_ViTri(ListLop ds, int dau, int cuoi) {
	if (Empty_Lop(ds)) {
		printf("Danh sach rong!\n");
		return;
	}
	if (dau < 0 || cuoi >= ds.n || dau > cuoi) {
		printf("vi tri dau va cuoi khong dung %d-%d", dau, cuoi);
		return;
	}
	printf("%-6s%-14s %-14s %s\n", "STT", "Ma Lop", "Nien Khoa", "Ten Lop");
	printf("------------------------------------------------------\n");
	for (int i = dau; i <= cuoi; i++) {
		printf("%-6d|%-14s|%-14s|%s\n", i + 1 - dau, ds.data[i]->MaLop, ds.data[i]->NienKhoa, ds.data[i]->TenLop);
	}
}

void Bubble_sort_Lop_NienKhoa(ListLop& dsLop) {
	if (Empty_Lop(dsLop)) {
		printf("Danh sach Lop rong!\n");
		return;
	}
	PTR_Lop temp;
	int flag = TRUE;
	for (int i = dsLop.n - 1; i > 0; i--) {
		flag = FALSE;
		for (int j = 0; j < i; j++) {
			if (strcmp(dsLop.data[j]->NienKhoa, dsLop.data[j + 1]->NienKhoa) > 0) {
				temp = dsLop.data[j];
				dsLop.data[j] = dsLop.data[j + 1];
				dsLop.data[j + 1] = temp;
				flag = TRUE;
			}
		}
		if (flag == FALSE) break;
	}
	In_DS_Lop(dsLop);
}

PTR_Lop Tao_Lop(ListLop dsLop) {
	PTR_Lop p = new Lop;

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	while (1) {
		printf("Ma Lop (Toi da 14 ky tu chi chua ky tu A->Z, 0->9 va -): ");
		gets_s(p->MaLop);
		if (isValidMaLop(p->MaLop)) {
			if (Search_Lop_theo_MaLop(dsLop, p->MaLop) < 0) {
				break;
			}
			else {
				printf("Ma Lop da ton tai!\n\n");
			}
		}
		else {
			printf("Ma Lop khong hop le! Vui long nhap lai.\n\n");
		}

	}

	while (1) {
		printf("Ten Lop (Toi da 49 ky tu): ");
		gets_s(p->TenLop);
		if (strlen(p->TenLop) > 0) {
			break;
		}
		else {
			printf("Ten Lop khong duoc rong! Vui long nhap lai.\n\n");
		}
	}

	while (1) {
		printf("Nien khoa (Toi da 10 ky tu, DDDD-DDDD): ");
		gets_s(p->NienKhoa);
		if (isValidNienKhoa(p->NienKhoa)) {
			break;
		}
		else {
			printf("Nien khoa khong dung dinh dang!\n\n");
		}
	}

	p->ptr_dsSinhVien = NULL;
	return p;
}

DiemThi Tao_diem_token(char* token) {
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHDIEM];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHDIEM) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	DiemThi dt;
	strncpy_s(dt.mamh, list_thuoctinh[0], 15);
	dt.diem = atof(list_thuoctinh[1]);

	return dt;
}

// Tao danh sach diem thi bang token
void Tao_dsDiemThi_token(PTR_DiemThi& First_DiemThi, char* token) {
	char* token_DiemThi, * nextToken_DiemThi;
	char* list_thuoctinh[MAXTHUOCTINHLOP];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_DiemThi = strtok_s(token, DELIMITERDIEM, &nextToken_DiemThi);

	while (token_DiemThi != NULL && token_DiemThi[0] != '\n' && token_DiemThi[1] != 0)
	{
		DiemThi dt = Tao_diem_token(token_DiemThi);
		Insert_First_DiemThi(First_DiemThi, dt);
		token_DiemThi = strtok_s(NULL, DELIMITERDIEM, &nextToken_DiemThi);
	}
}

PTR_Lop Tao_Lop_token(char* token) {
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHLOP];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHLOP) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	PTR_Lop p = new Lop;
	strncpy_s(p->MaLop, list_thuoctinh[0], 15);
	strncpy_s(p->NienKhoa, list_thuoctinh[1], 15);
	strncpy_s(p->TenLop, list_thuoctinh[2], 50);
	p->ptr_dsSinhVien = NULL;

	return p;
}

SinhVien Tao_SinhVien_token(char* token) {
	char* token_SinhVien, * nextToken_SinhVien;
	char* list_thuoctinh[MAXTHUOCTINHSINHVIEN];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_SinhVien = strtok_s(token, DELIMITERSINHVIENVSDIEM, &nextToken_SinhVien);

	char* token_thuoctinh, * nextToken_thuoctinh;
	//char* token_SinhVien_copy;
	//strcpy_s(token_SinhVien_copy, strlen(token_SinhVien), token_SinhVien);
	token_thuoctinh = strtok_s(token_SinhVien, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHSINHVIEN) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	SinhVien sv;
	strncpy_s(sv.masv, list_thuoctinh[0], 15);
	strncpy_s(sv.ho, list_thuoctinh[1], 20);
	strncpy_s(sv.ten, list_thuoctinh[2], 20);
	sv.phai = atoi(list_thuoctinh[3]);
	strncpy_s(sv.password, list_thuoctinh[4], 20);

	sv.ptr_dsDiemThi = NULL;

	if (nextToken_SinhVien != NULL && strlen(nextToken_SinhVien) >= 1) {
		Tao_dsDiemThi_token(sv.ptr_dsDiemThi, nextToken_SinhVien);
	}

	return sv;
}

void Tao_dsSinhVien_token(PTR_SinhVien& First, char* token) {
	char* token_SinhVien, * nextToken_SinhVien;
	char* list_thuoctinh[MAXTHUOCTINHLOP];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_SinhVien = strtok_s(token, DELIMITERSINHVIEN, &nextToken_SinhVien);

	while (token_SinhVien != NULL && token_SinhVien[0] != '\n' && token_SinhVien[1] != 0)
	{
		SinhVien sv = Tao_SinhVien_token(token_SinhVien);
		Insert_First_SinhVien(First, sv);
		token_SinhVien = strtok_s(NULL, DELIMITERSINHVIEN, &nextToken_SinhVien);
	}
}

// ---------------------------------- Nien Khoa ------------------------------------

int Insert_ItemNienKhoa(ListNienKhoa& ds, int i, NienKhoadata info) {
	int j;
	if (i < 0 || i > ds.n || ds.n >= MAXLISTLOP)
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = info;
	ds.n++;
	return 1;
}

//lay danh sach vi tri dau va cuoi cua moi nien khoa trong mang dsLop da sap xep
void Get_ListNienKhoa(ListLop& dsLop, ListNienKhoa& dsNienKhoa) {

	if (Empty_Lop(dsLop)) {
		printf("Danh sach Lop rong!\n");
		return;
	}

	Bubble_sort_Lop_NienKhoa(dsLop);
	char NienKhoa[50];

	NienKhoadata nkdata;
	//Phan tu dau tien
	strcpy_s(nkdata.NienKhoa, dsLop.data[0]->NienKhoa);
	nkdata.vitridau = 0;

	if (dsLop.n == 1) {
		nkdata.vitricuoi = 0;
		Insert_ItemNienKhoa(dsNienKhoa, dsNienKhoa.n, nkdata);
		return;
	}

	for (int i = 1; i < dsLop.n; i++) {
		if (strcmp(nkdata.NienKhoa, dsLop.data[i]->NienKhoa) != 0) {
			nkdata.vitricuoi = i - 1;
			Insert_ItemNienKhoa(dsNienKhoa, dsNienKhoa.n, nkdata);
			nkdata.vitridau = i;
			strcpy_s(nkdata.NienKhoa, dsLop.data[i]->NienKhoa);
		}
		// Truong hop i la phan tu cuoi cung
		if (i == dsLop.n - 1) {
			nkdata.vitricuoi = i;
			Insert_ItemNienKhoa(dsNienKhoa, dsNienKhoa.n, nkdata);
		}
	}


	//for (size_t i = 0; i < dsNienKhoa.n; i++)
	//{
	//	printf("%d %d %s", dsNienKhoa.data[i].vitridau, dsNienKhoa.data[i].vitricuoi, dsNienKhoa.data[i].NienKhoa);
	//}
}

// ---------------------------------- Ung Dung ------------------------------------

void Luu_dsLop(ListLop dsLop) {
	FILE* stream;
	errno_t err;

	// a: append (Mo file va them vao cuoi cua file neu ton tai).
	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILELOP, "w");

	if (err == 0)
	{
		for (int i = 0; i < dsLop.n; i++)
		{
			fprintf(stream, "%s|%s|%s/", dsLop.data[i]->MaLop, dsLop.data[i]->NienKhoa, dsLop.data[i]->TenLop);
			for (PTR_SinhVien p_SinhVien = dsLop.data[i]->ptr_dsSinhVien; p_SinhVien != NULL; p_SinhVien = p_SinhVien->next) {
				fprintf(stream, "%s|%s|%s|%d|%s[", p_SinhVien->sv.masv, p_SinhVien->sv.ho, p_SinhVien->sv.ten, p_SinhVien->sv.phai, p_SinhVien->sv.password);
				for (PTR_DiemThi p_DiemThi = p_SinhVien->sv.ptr_dsDiemThi; p_DiemThi != NULL; p_DiemThi = p_DiemThi->next) {
					fprintf(stream, "%s|%.2f}", p_DiemThi->dt.mamh, floorf(p_DiemThi->dt.diem * 100) / 100);
				}
				fprintf(stream, "%c", ']');
			}
			if (i < dsLop.n - 1) {
				fprintf(stream, "%c", '\n');
			}
		}

		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILEKETQUATHI);
	}
}

void Add_Lop(ListLop& dsLop) {
	printf("\nThem Lop:\n");
	PTR_Lop p = Tao_Lop(dsLop);

	if (Insert_Item_Lop(dsLop, dsLop.n, p)) {
		Luu_dsLop(dsLop);
		printf("\nThem than cong!\n");
	}
	else {
		printf("\nThem that bai!\n");
	}

	In_DS_Lop(dsLop);
}

void Delete_Lop(ListLop& dsLop) {
	printf("\nXoa Lop:\n");

	if (Empty_Lop(dsLop)) {
		printf("Danh sach rong, vui long them Lop!\n");
		return;
	}

	In_DS_Lop(dsLop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so Lop can xoa: ");
	char MaLop[15];
	gets_s(MaLop);

	int vitricanxoa = Search_Lop_theo_MaLop(dsLop, MaLop);

	if (vitricanxoa == -1) {
		printf("Khong tim thay ma so Lop can xoa!\n");
		return;
	}

	if (Delele_Item_Lop(dsLop, vitricanxoa)) {
		Luu_dsLop(dsLop);
		printf("\nXoa thanh cong!\n\n");
		In_DS_Lop(dsLop);
	}
	else {
		printf("\nXoa that bai!\n");
	}
}

void Update_Lop(ListLop& dsLop) {
	printf("\nChinh sua Lop:\n");

	if (Empty_Lop(dsLop)) {
		printf("Danh sach rong, vui long them Lop!\n");
		return;
	}

	In_DS_Lop(dsLop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so Lop can sua: ");
	char MaLop[15];
	gets_s(MaLop);

	int vitricansua = Search_Lop_theo_MaLop(dsLop, MaLop);
	if (vitricansua == -1) {
		printf("Khong tim thay ma so Lop can sua!\n");
		return;
	}

	if (Update_Item_Lop(dsLop, vitricansua)) {
		Luu_dsLop(dsLop);
		printf("\nSua thanh cong!\n\n");
		In_DS_Lop(dsLop);
	}
	else {
		printf("\nSua that bai!\n");
	}
}

int Read_fileLop(ListLop& ds) {
	FILE* stream;

	errno_t err;
	err = fopen_s(&stream, FILELOP, "r");
	if (err == 0)
	{
		//printf("Mo file %s thanh cong!\n", FILELOP);
		char buffer[10000];

		while (fgets(buffer, 10000, stream) != NULL) {
			//printf("t: %s", num);


			//TODO: cap phat bo nho
			char* token_Lop, * nextToken_Lop;

			// lay token dau tien (Lop)
			token_Lop = strtok_s(buffer, DELIMITERLOPVOISINHVIEN, &nextToken_Lop);

			if (token_Lop != NULL) {
				PTR_Lop p = Tao_Lop_token(token_Lop);
				Insert_Item_Lop(ds, ds.n, p);
			}

			if (nextToken_Lop != NULL && nextToken_Lop[0] != '\n' && nextToken_Lop[1] != 0) {
				Tao_dsSinhVien_token(ds.data[ds.n - 1]->ptr_dsSinhVien, nextToken_Lop);

				//int len = strlen(ds.data[ds.n - 1]->ptr_dsSinhVien->sv.password);
				//if (ds.data[ds.n - 1]->ptr_dsSinhVien->sv.password[len - 1] == '\n') {
				//	ds.data[ds.n - 1]->ptr_dsSinhVien->sv.password[len - 1] = '\0';
				//}
			}

		}
		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILELOP);
	}
	return 1;
}

void In_DS_Lop_NienKhoa(ListLop& dsLop) {
	ListNienKhoa dsNienKhoa;

	if (Empty_Lop(dsLop)) {
		printf("Danh sach Lop rong!\n");
		return;
	}

	Get_ListNienKhoa(dsLop, dsNienKhoa);
	int iNienKhoa;

	printf("\nDanh sach cac nien khoa:\n\n");
	for (int i = 0; i < dsNienKhoa.n; i++) {
		printf("%d: %s\n", i + 1, dsNienKhoa.data[i].NienKhoa);
	}
	printf("0: Tat ca\n");

	printf("Hay chon nien khoa can in (Nhap STT): ");

	do
		scanf_s("%d", &iNienKhoa);
	while (iNienKhoa < 0 || iNienKhoa > dsNienKhoa.n);

	if (iNienKhoa == 0) {
		for (int i = 0; i < dsNienKhoa.n; i++) {
			printf("\nNIEN KHOA %s:\n", dsNienKhoa.data[i].NienKhoa);
			In_DS_Lop_Theo_ViTri(dsLop, dsNienKhoa.data[i].vitridau, dsNienKhoa.data[i].vitricuoi);
		}
	}
	else {
		printf("\nNIEN KHOA %s:\n", dsNienKhoa.data[iNienKhoa - 1].NienKhoa);
		In_DS_Lop_Theo_ViTri(dsLop, dsNienKhoa.data[iNienKhoa - 1].vitridau, dsNienKhoa.data[iNienKhoa - 1].vitricuoi);
	}

}

void Nhap_SinhVien(ListLop& dsLop) {

	printf("\Nhap sinh vien cua Lop:\n");

	if (Empty_Lop(dsLop)) {
		printf("Danh sach rong, vui long them Lop!\n");
		return;
	}


	In_DS_Lop(dsLop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so Lop can them sinh vien: ");
	char MaLop[15];
	gets_s(MaLop);

	int vitricansua = Search_Lop_theo_MaLop(dsLop, MaLop);

	if (vitricansua == -1) {
		printf("Khong tim thay Lop can tim theo maso: %s!\n", MaLop);
		return;
	}

	char tieptuc;
	do {
		SinhVien sv = Tao_SinhVien(dsLop.data[vitricansua]->ptr_dsSinhVien);
		Insert_First_SinhVien(dsLop.data[vitricansua]->ptr_dsSinhVien, sv);
		Luu_dsLop(dsLop);
		In_DSSinhVien(dsLop.data[vitricansua]->ptr_dsSinhVien);
		printf("Ban co muon tiep tuc them (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();

		//Clear Input Buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	} while (tieptuc == 'y' || tieptuc == 'Y');

}

void In_bandiem_Lop(ListLop dsLop, ListMonHoc dsmonhoc) {
	printf("\nIn ban diem Lop:\n");

	if (Empty_Lop(dsLop)) {
		printf("Danh sach rong, vui long them Lop!\n");
		return;
	}

	In_DS_Lop(dsLop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so Lop can in: ");
	char MaLop[15];
	gets_s(MaLop);

	int vitricanin = Search_Lop_theo_MaLop(dsLop, MaLop);
	if (vitricanin == -1) {
		printf("Khong tim thay ma so Lop can xoa!\n");
		return;
	}

	//In_danhsachSinhVien(dsLop.data[vitricanin]->ptr_dsSinhVien);
	ListMonHoc dsmonhocdathi = Lay_dsmonhoc_dathi_Lop(dsLop.data[vitricanin]->ptr_dsSinhVien, dsmonhoc);
	

	if (Empty_MonHoc(dsmonhocdathi)) {
		printf("Lop chua thi mon nao!\n");
		return;
	}

	printf("Ban hay chon mon hoc can in ban diem (Chi hien thi nhung mon Lop da thi):\n\n");
	for (int i = 0; i < dsmonhocdathi.n; i++){
		printf("%d. %s - %s\n", i + 1, dsmonhocdathi.data[i]->mamh, dsmonhocdathi.data[i]->tenmh);
	}

	printf("0. Tat ca\n");

	system("cls");
	for (int i = 0; i < dsmonhocdathi.n; i++) {
		printf("\n\n%d. %s - %s\n", i + 1, dsmonhocdathi.data[i]->mamh, dsmonhocdathi.data[i]->tenmh);
		In_diemSinhVien_monhoc(dsLop.data[vitricanin]->ptr_dsSinhVien, dsmonhocdathi.data[i]->mamh);
	}

}
