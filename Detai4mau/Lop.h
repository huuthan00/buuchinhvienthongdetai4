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
#define FILELOP "lop.txt"
#define FILEMONHOC "monhoc.txt"
#define FILEKETQUATHI "ketquathi.txt"
#define TRUE 1
#define FALSE 0

struct lop {
	char malop[15];
	char nienkhoa[15];
	char tenlop[50];
	PTR_sinhvien ptr_dssinhvien;
};

typedef lop* PTR_lop;

struct listlop {
	int n = 0;					// so nut cua danh sach
	PTR_lop data[MAXLISTLOP];	// danh sach mang 1 chieu con tro lop (PTR_lop)
};

struct nienkhoadata {
	int vitridau;
	int vitricuoi;
	char nienkhoa[15];
};

struct listnienkhoa {
	int n = 0;
	nienkhoadata data[MAXLISTLOP];
};

int Empty_lop(listlop ds) {
	return ds.n == 0;
}

int Full_lop(listlop ds) {
	return ds.n == MAXLISTLOP;
}

int isValidMalop(char malop[15]) {

	if (strlen(malop) <= 0) return 0;

	for (int i = 0; i < strlen(malop); i++)
	{
		if (!((malop[i] >= 'A' && malop[i] <= 'Z') || malop[i] >= '0' && malop[i] <= '9' || malop[i] == '-')) {
			return 0;
		}
	}
	return 1;
}

//Format DDDD-DDDD
int isValidNienKhoa(char nienkhoa[MAXLENGTHNIENKHOA]) {
	if (strlen(nienkhoa) != MAXLENGTHNIENKHOA - 1) return 0;

	for (int i = 0; i <= 3; i++)
	{
		if (!(nienkhoa[i] >= '0' && nienkhoa[i] <= '9')) {
			return 0;
		}
	}

	if (nienkhoa[4] != '-') return 0;

	for (int i = 5; i <= 8; i++)
	{
		if (!(nienkhoa[i] >= '0' && nienkhoa[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

int Search_lop_theo_malop(listlop& ds, char malop[15]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(malop, ds.data[i]->malop) == 0) {
			return i;
		}
	}
	return -1;
}

int Insert_itemlop(listlop& ds, int i, PTR_lop info) {
	int j;
	if (i < 0 || i > ds.n || Full_lop(ds))
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = info;
	ds.n++;
	return 1;
}

int Delele_itemlop(listlop& ds, int i) {
	int j;
	if (i < 0 || i >= ds.n || Empty_lop(ds))
		return 0;
	for (j = i + 1; j < ds.n; j++) {
		ds.data[j - 1] = ds.data[j];
	}
	ds.n--;
	return 1;
}

int Update_itemlop(listlop& dslop, int i) {

	if (i < 0 || i >= dslop.n || Empty_lop(dslop))
		return 0;
	//char maloptemp[15];

	//while (1) {
	//	printf("Ma lop (Toi da 14 ky tu chi chua ky tu A->Z va 0->9): ");
	//	gets_s(maloptemp);
	//	if (isValidMalop(maloptemp)) {
	//		if (Search_lop_theo_malop(dslop, maloptemp) < 0) {
	//			strcpy_s(dslop.data[i]->malop, 15, maloptemp);
	//			break;
	//		}
	//		else {
	//			printf("Ma lop da ton tai!\n\n");
	//		}
	//	}
	//	else {
	//		printf("Ma lop khong hop le! Vui long nhap lai.\n\n");
	//	}
	//}

	while (1) {
		printf("Ten lop (Toi da 49 ky tu): ");
		gets_s(dslop.data[i]->tenlop);
		if (strlen(dslop.data[i]->tenlop) > 0) {
			break;
		}
		else {
			printf("Ten lop khong duoc rong! Vui long nhap lai.\n\n");
		}
	}

	while (1) {
		printf("Nien khoa (Toi da 10 ky tu, DDDD-DDDD): ");
		gets_s(dslop.data[i]->nienkhoa);
		if (isValidNienKhoa(dslop.data[i]->nienkhoa)) {
			break;
		}
		else {
			printf("Nien khoa khong dung dinh dang!\n\n");
		}
	}

	return 1;
}

PTR_sinhvien Search_sinhvien_dslop_masv(listlop ds, char masv[15], int& stt) {
	//sinhvien sv;
	for (int i = 0; i < ds.n; i++) {
		PTR_sinhvien p_sinhvien = Search_sinhvien_masv(ds.data[i]->ptr_dssinhvien, masv);
		if (p_sinhvien != NULL) {
			stt = i;
			return p_sinhvien;
		}
		/*if (strlen(sv.masv) > 0) {
			stt = i;
			return sv;
		}*/
	}
	stt = -1;
	return NULL;
}

void In_danhsachlop(listlop ds) {
	if (Empty_lop(ds)) {
		printf("Danh sach rong!\n");
		return;
	}
	printf("%-6s%-14s %-14s %s\n", "STT", "Ma Lop", "Nien Khoa", "Ten Lop");
	printf("------------------------------------------------------\n");
	for (int i = 0; i < ds.n; i++) {
		printf("%-6d|%-14s|%-14s|%s\n", i + 1, ds.data[i]->malop, ds.data[i]->nienkhoa, ds.data[i]->tenlop);
	}
}

void In_danhsachlop_theo_vitri(listlop ds, int dau, int cuoi) {
	if (Empty_lop(ds)) {
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
		printf("%-6d|%-14s|%-14s|%s\n", i + 1 - dau, ds.data[i]->malop, ds.data[i]->nienkhoa, ds.data[i]->tenlop);
	}
}

void Bubble_sort_lop_nienkhoa(listlop& dslop) {
	if (Empty_lop(dslop)) {
		printf("Danh sach lop rong!\n");
		return;
	}
	PTR_lop temp;
	int flag = TRUE;
	for (int i = dslop.n - 1; i > 0; i--) {
		flag = FALSE;
		for (int j = 0; j < i; j++) {
			if (strcmp(dslop.data[j]->nienkhoa, dslop.data[j + 1]->nienkhoa) > 0) {
				temp = dslop.data[j];
				dslop.data[j] = dslop.data[j + 1];
				dslop.data[j + 1] = temp;
				flag = TRUE;
			}
		}
		if (flag == FALSE) break;
	}
	In_danhsachlop(dslop);
}

PTR_lop Tao_lop(listlop dslop) {
	PTR_lop p = new lop;

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	while (1) {
		printf("Ma lop (Toi da 14 ky tu chi chua ky tu A->Z, 0->9 va -): ");
		gets_s(p->malop);
		if (isValidMalop(p->malop)) {
			if (Search_lop_theo_malop(dslop, p->malop) < 0) {
				break;
			}
			else {
				printf("Ma lop da ton tai!\n\n");
			}
		}
		else {
			printf("Ma lop khong hop le! Vui long nhap lai.\n\n");
		}

	}

	while (1) {
		printf("Ten lop (Toi da 49 ky tu): ");
		gets_s(p->tenlop);
		if (strlen(p->tenlop) > 0) {
			break;
		}
		else {
			printf("Ten lop khong duoc rong! Vui long nhap lai.\n\n");
		}
	}

	while (1) {
		printf("Nien khoa (Toi da 10 ky tu, DDDD-DDDD): ");
		gets_s(p->nienkhoa);
		if (isValidNienKhoa(p->nienkhoa)) {
			break;
		}
		else {
			printf("Nien khoa khong dung dinh dang!\n\n");
		}
	}

	p->ptr_dssinhvien = NULL;
	return p;
}

diemthi Tao_diem_token(char* token) {
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

	diemthi dt;
	strncpy_s(dt.mamh, list_thuoctinh[0], 15);
	dt.diem = atof(list_thuoctinh[1]);

	return dt;
}

// Tao danh sach diem thi bang token
void Tao_dsdiemthi_token(PTR_diemthi& First_diemthi, char* token) {
	char* token_diemthi, * nextToken_diemthi;
	char* list_thuoctinh[MAXTHUOCTINHLOP];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_diemthi = strtok_s(token, DELIMITERDIEM, &nextToken_diemthi);

	while (token_diemthi != NULL && token_diemthi[0] != '\n' && token_diemthi[1] != 0)
	{
		diemthi dt = Tao_diem_token(token_diemthi);
		Insert_First_diemthi(First_diemthi, dt);
		token_diemthi = strtok_s(NULL, DELIMITERDIEM, &nextToken_diemthi);
	}
}

PTR_lop Tao_lop_token(char* token) {
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

	PTR_lop p = new lop;
	strncpy_s(p->malop, list_thuoctinh[0], 15);
	strncpy_s(p->nienkhoa, list_thuoctinh[1], 15);
	strncpy_s(p->tenlop, list_thuoctinh[2], 50);
	p->ptr_dssinhvien = NULL;

	return p;
}

sinhvien Tao_sinhvien_token(char* token) {
	char* token_sinhvien, * nextToken_sinhvien;
	char* list_thuoctinh[MAXTHUOCTINHSINHVIEN];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_sinhvien = strtok_s(token, DELIMITERSINHVIENVSDIEM, &nextToken_sinhvien);

	char* token_thuoctinh, * nextToken_thuoctinh;
	//char* token_sinhvien_copy;
	//strcpy_s(token_sinhvien_copy, strlen(token_sinhvien), token_sinhvien);
	token_thuoctinh = strtok_s(token_sinhvien, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHSINHVIEN) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	sinhvien sv;
	strncpy_s(sv.masv, list_thuoctinh[0], 15);
	strncpy_s(sv.ho, list_thuoctinh[1], 20);
	strncpy_s(sv.ten, list_thuoctinh[2], 20);
	sv.phai = atoi(list_thuoctinh[3]);
	strncpy_s(sv.password, list_thuoctinh[4], 20);

	sv.ptr_dsdiemthi = NULL;

	if (nextToken_sinhvien != NULL && strlen(nextToken_sinhvien) >= 1) {
		Tao_dsdiemthi_token(sv.ptr_dsdiemthi, nextToken_sinhvien);
	}

	return sv;
}

void Tao_dssinhvien_token(PTR_sinhvien& First, char* token) {
	char* token_sinhvien, * nextToken_sinhvien;
	char* list_thuoctinh[MAXTHUOCTINHLOP];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_sinhvien = strtok_s(token, DELIMITERSINHVIEN, &nextToken_sinhvien);

	while (token_sinhvien != NULL && token_sinhvien[0] != '\n' && token_sinhvien[1] != 0)
	{
		sinhvien sv = Tao_sinhvien_token(token_sinhvien);
		Insert_first_sinhvien(First, sv);
		token_sinhvien = strtok_s(NULL, DELIMITERSINHVIEN, &nextToken_sinhvien);
	}
}

// ---------------------------------- Nien Khoa ------------------------------------

int Insert_itemnienkhoa(listnienkhoa& ds, int i, nienkhoadata info) {
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

//lay danh sach vi tri dau va cuoi cua moi nien khoa trong mang dslop da sap xep
void Get_listnienkhoa(listlop& dslop, listnienkhoa& dsnienkhoa) {

	if (Empty_lop(dslop)) {
		printf("Danh sach lop rong!\n");
		return;
	}

	Bubble_sort_lop_nienkhoa(dslop);
	char nienkhoa[50];

	nienkhoadata nkdata;
	//Phan tu dau tien
	strcpy_s(nkdata.nienkhoa, dslop.data[0]->nienkhoa);
	nkdata.vitridau = 0;

	if (dslop.n == 1) {
		nkdata.vitricuoi = 0;
		Insert_itemnienkhoa(dsnienkhoa, dsnienkhoa.n, nkdata);
		return;
	}

	for (int i = 1; i < dslop.n; i++) {
		if (strcmp(nkdata.nienkhoa, dslop.data[i]->nienkhoa) != 0) {
			nkdata.vitricuoi = i - 1;
			Insert_itemnienkhoa(dsnienkhoa, dsnienkhoa.n, nkdata);
			nkdata.vitridau = i;
			strcpy_s(nkdata.nienkhoa, dslop.data[i]->nienkhoa);
		}
		// Truong hop i la phan tu cuoi cung
		if (i == dslop.n - 1) {
			nkdata.vitricuoi = i;
			Insert_itemnienkhoa(dsnienkhoa, dsnienkhoa.n, nkdata);
		}
	}


	//for (size_t i = 0; i < dsnienkhoa.n; i++)
	//{
	//	printf("%d %d %s", dsnienkhoa.data[i].vitridau, dsnienkhoa.data[i].vitricuoi, dsnienkhoa.data[i].nienkhoa);
	//}
}

// ---------------------------------- Ung Dung ------------------------------------

void Luu_dslop(listlop dslop) {
	FILE* stream;
	errno_t err;

	// a: append (Mo file va them vao cuoi cua file neu ton tai).
	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILELOP, "w");

	if (err == 0)
	{
		for (int i = 0; i < dslop.n; i++)
		{
			fprintf(stream, "%s|%s|%s/", dslop.data[i]->malop, dslop.data[i]->nienkhoa, dslop.data[i]->tenlop);
			for (PTR_sinhvien p_sinhvien = dslop.data[i]->ptr_dssinhvien; p_sinhvien != NULL; p_sinhvien = p_sinhvien->next) {
				fprintf(stream, "%s|%s|%s|%d|%s[", p_sinhvien->sv.masv, p_sinhvien->sv.ho, p_sinhvien->sv.ten, p_sinhvien->sv.phai, p_sinhvien->sv.password);
				for (PTR_diemthi p_diemthi = p_sinhvien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
					fprintf(stream, "%s|%.2f}", p_diemthi->dt.mamh, floorf(p_diemthi->dt.diem * 100) / 100);
				}
				fprintf(stream, "%c", ']');
			}
			if (i < dslop.n - 1) {
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

void Add_lop(listlop& dslop) {
	printf("\nThem Lop:\n");
	PTR_lop p = Tao_lop(dslop);

	if (Insert_itemlop(dslop, dslop.n, p)) {
		Luu_dslop(dslop);
		printf("\nThem than cong!\n");
	}
	else {
		printf("\nThem that bai!\n");
	}

	In_danhsachlop(dslop);
}

void Delete_lop(listlop& dslop) {
	printf("\nXoa Lop:\n");

	if (Empty_lop(dslop)) {
		printf("Danh sach rong, vui long them lop!\n");
		return;
	}

	In_danhsachlop(dslop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so lop can xoa: ");
	char malop[15];
	gets_s(malop);

	int vitricanxoa = Search_lop_theo_malop(dslop, malop);

	if (vitricanxoa == -1) {
		printf("Khong tim thay ma so lop can xoa!\n");
		return;
	}

	if (Delele_itemlop(dslop, vitricanxoa)) {
		Luu_dslop(dslop);
		printf("\nXoa thanh cong!\n\n");
		In_danhsachlop(dslop);
	}
	else {
		printf("\nXoa that bai!\n");
	}
}

void Update_lop(listlop& dslop) {
	printf("\nChinh sua Lop:\n");

	if (Empty_lop(dslop)) {
		printf("Danh sach rong, vui long them lop!\n");
		return;
	}

	In_danhsachlop(dslop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so lop can sua: ");
	char malop[15];
	gets_s(malop);

	int vitricansua = Search_lop_theo_malop(dslop, malop);
	if (vitricansua == -1) {
		printf("Khong tim thay ma so lop can sua!\n");
		return;
	}

	if (Update_itemlop(dslop, vitricansua)) {
		Luu_dslop(dslop);
		printf("\nSua thanh cong!\n\n");
		In_danhsachlop(dslop);
	}
	else {
		printf("\nSua that bai!\n");
	}
}

int Read_filelop(listlop& ds) {
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
			char* token_lop, * nextToken_lop;

			// lay token dau tien (lop)
			token_lop = strtok_s(buffer, DELIMITERLOPVOISINHVIEN, &nextToken_lop);

			if (token_lop != NULL) {
				PTR_lop p = Tao_lop_token(token_lop);
				Insert_itemlop(ds, ds.n, p);
			}

			if (nextToken_lop != NULL && nextToken_lop[0] != '\n' && nextToken_lop[1] != 0) {
				Tao_dssinhvien_token(ds.data[ds.n - 1]->ptr_dssinhvien, nextToken_lop);

				//int len = strlen(ds.data[ds.n - 1]->ptr_dssinhvien->sv.password);
				//if (ds.data[ds.n - 1]->ptr_dssinhvien->sv.password[len - 1] == '\n') {
				//	ds.data[ds.n - 1]->ptr_dssinhvien->sv.password[len - 1] = '\0';
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

void In_danhsachlop_nienkhoa(listlop& dslop) {
	listnienkhoa dsnienkhoa;

	if (Empty_lop(dslop)) {
		printf("Danh sach lop rong!\n");
		return;
	}

	Get_listnienkhoa(dslop, dsnienkhoa);
	int inienkhoa;

	printf("\nDanh sach cac nien khoa:\n\n");
	for (int i = 0; i < dsnienkhoa.n; i++) {
		printf("%d: %s\n", i + 1, dsnienkhoa.data[i].nienkhoa);
	}
	printf("0: Tat ca\n");

	printf("Hay chon nien khoa can in (Nhap STT): ");

	do
		scanf_s("%d", &inienkhoa);
	while (inienkhoa < 0 || inienkhoa > dsnienkhoa.n);

	if (inienkhoa == 0) {
		for (int i = 0; i < dsnienkhoa.n; i++) {
			printf("\nNIEN KHOA %s:\n", dsnienkhoa.data[i].nienkhoa);
			In_danhsachlop_theo_vitri(dslop, dsnienkhoa.data[i].vitridau, dsnienkhoa.data[i].vitricuoi);
		}
	}
	else {
		printf("\nNIEN KHOA %s:\n", dsnienkhoa.data[inienkhoa - 1].nienkhoa);
		In_danhsachlop_theo_vitri(dslop, dsnienkhoa.data[inienkhoa - 1].vitridau, dsnienkhoa.data[inienkhoa - 1].vitricuoi);
	}

}

void Nhap_sinhvien(listlop& dslop) {

	printf("\Nhap sinh vien cua Lop:\n");

	if (Empty_lop(dslop)) {
		printf("Danh sach rong, vui long them lop!\n");
		return;
	}


	In_danhsachlop(dslop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so lop can them sinh vien: ");
	char malop[15];
	gets_s(malop);

	int vitricansua = Search_lop_theo_malop(dslop, malop);

	if (vitricansua == -1) {
		printf("Khong tim thay lop can tim theo maso: %s!\n", malop);
		return;
	}

	char tieptuc;
	do {
		sinhvien sv = Tao_sinhvien(dslop.data[vitricansua]->ptr_dssinhvien);
		Insert_first_sinhvien(dslop.data[vitricansua]->ptr_dssinhvien, sv);
		Luu_dslop(dslop);
		In_danhsachsinhvien(dslop.data[vitricansua]->ptr_dssinhvien);
		printf("Ban co muon tiep tuc them (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();

		//Clear Input Buffer
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	} while (tieptuc == 'y' || tieptuc == 'Y');

}

void In_bandiem_lop(listlop dslop, listmonhoc dsmonhoc) {
	printf("\nIn ban diem Lop:\n");

	if (Empty_lop(dslop)) {
		printf("Danh sach rong, vui long them lop!\n");
		return;
	}

	In_danhsachlop(dslop);

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	printf("Nhap ma so lop can in: ");
	char malop[15];
	gets_s(malop);

	int vitricanin = Search_lop_theo_malop(dslop, malop);
	if (vitricanin == -1) {
		printf("Khong tim thay ma so lop can xoa!\n");
		return;
	}

	//In_danhsachsinhvien(dslop.data[vitricanin]->ptr_dssinhvien);
	listmonhoc dsmonhocdathi = Lay_dsmonhoc_dathi_lop(dslop.data[vitricanin]->ptr_dssinhvien, dsmonhoc);
	

	if (Empty_monhoc(dsmonhocdathi)) {
		printf("Lop chua thi mon nao!\n");
		return;
	}

	printf("Ban hay chon mon hoc can in ban diem (Chi hien thi nhung mon lop da thi):\n\n");
	for (int i = 0; i < dsmonhocdathi.n; i++){
		printf("%d. %s - %s\n", i + 1, dsmonhocdathi.data[i]->mamh, dsmonhocdathi.data[i]->tenmh);
	}

	printf("0. Tat ca\n");

	system("cls");
	for (int i = 0; i < dsmonhocdathi.n; i++) {
		printf("\n\n%d. %s - %s\n", i + 1, dsmonhocdathi.data[i]->mamh, dsmonhocdathi.data[i]->tenmh);
		In_diemsinhvien_monhoc(dslop.data[vitricanin]->ptr_dssinhvien, dsmonhocdathi.data[i]->mamh);
	}

}
