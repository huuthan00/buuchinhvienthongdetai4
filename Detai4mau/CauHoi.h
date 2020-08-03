#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "random.h"
#include "MonHoc.h"

#define DELIMITERTHUOCTINHCAUHOI "|"
#define FILECAUHOI "cauhoi.txt"
#define MAXTHUOCTINHCAUHOI 8
#define DAPANA 0
#define DAPANB 1
#define DAPANC 2
#define DAPAND 3
#define MAXCAUHOI 4

struct cauhoi {
	int id;
	char mamh[15];
	char noidung[1000];
	char A[500];
	char B[500];
	char C[500];
	char D[500];
	char dapan;
};

typedef cauhoi* PTR_cauhoi;

struct listcauhoi {
	int n = 0;
	cauhoi* data;
};

struct nodecauhoi {
	cauhoi data;
	struct nodecauhoi* left;
	struct nodecauhoi* right;
};

typedef nodecauhoi* PTR_nodecauhoi;

struct cautraloi {
	cauhoi ch;
	char cautraloi;
};

typedef cautraloi* PTR_cautraloi;

struct listcautraloi {
	int n = 0;
	PTR_cautraloi data;
};

//int checkExistFile(const char* file) {
//	FILE* stream;
//
//	errno_t err;
//	err = fopen_s(&stream, file, "r");
//
//	if (err == 0) {
//		fclose(stream);
//		return 1;
//	}
//
//	return 0;
//}

//void Initialize(PTR_nodecauhoi& root) {
//	root = NULL;
//}

int Insert_itemcautraloi(listcautraloi& ds, int i, cautraloi ctl) {
	int j;
	if (i < 0 || i > ds.n)
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = ctl;
	ds.n++;
	return 1;
}

void Insert_nodecauhoi(PTR_nodecauhoi& p, cauhoi data) {
	// Nut hien tai se la nut la
	if (p == NULL) {
		p = new nodecauhoi;
		p->data = data;
		p->left = NULL;
		p->right = NULL;
	}
	else if (data.id < p->data.id) {
		Insert_nodecauhoi(p->left, data);
	}
	else if (data.id > p->data.id) {
		Insert_nodecauhoi(p->right, data);
	}
}

void In_Inorder_cauhoi(PTR_nodecauhoi p) {
	if (p != NULL) {
		In_Inorder_cauhoi(p->left);
		printf("\nID: %d MaMH: %s\n", p->data.id, p->data.mamh);
		printf("Noi dung: %s\n", p->data.noidung);
		printf("A. %s	B. %s	C. %s	D. %s\n", p->data.A, p->data.B, p->data.C, p->data.D);
		printf("Dap An: %c\n", p->data.dapan);
		In_Inorder_cauhoi(p->right);
	}
}

void Lay_dscauhoi_theo_mamh(PTR_nodecauhoi p, char mamh[15], cauhoi** dscauhoi, int& index) {
	//printf("dscauhoi = %d\n", &(*dscauhoi));

	if (p != NULL) {
		Lay_dscauhoi_theo_mamh(p->left, mamh, dscauhoi, index);
		if (strcmp(p->data.mamh, mamh) == 0) {
			(*dscauhoi)[index++] = p->data;
		}
		Lay_dscauhoi_theo_mamh(p->right, mamh, dscauhoi, index);
	}
}

int Tong_cauhoi_cua_monhoc(PTR_nodecauhoi p, char mamh[15]) {
	int tong = 0;
	if (p != NULL) {
		tong = tong + Tong_cauhoi_cua_monhoc(p->left, mamh);
		if (strcmp(p->data.mamh, mamh) == 0) {
			tong++;
		}
		tong = tong + Tong_cauhoi_cua_monhoc(p->right, mamh);
	}
	return tong;
}

cauhoi Tao_cauhoi_token(char* token) {
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHCAUHOI];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token, DELIMITERTHUOCTINHCAUHOI, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHCAUHOI) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINHCAUHOI, &nextToken_thuoctinh);
	}

	cauhoi ch;
	char* p;
	ch.id = strtol(list_thuoctinh[0], &p, 10);
	strncpy_s(ch.mamh, list_thuoctinh[1], 15);
	strncpy_s(ch.noidung, list_thuoctinh[2], 1000);
	strncpy_s(ch.A, list_thuoctinh[3], 500);
	strncpy_s(ch.B, list_thuoctinh[4], 500);
	strncpy_s(ch.C, list_thuoctinh[5], 500);
	strncpy_s(ch.D, list_thuoctinh[6], 500);

	ch.dapan = list_thuoctinh[7][0];

	return ch;
}

int Read_filecauhoi(PTR_nodecauhoi& root) {
	FILE* stream;

	errno_t err;
	err = fopen_s(&stream, FILECAUHOI, "r");
	if (err == 0)
	{
		//printf("Mo file %s thanh cong!\n", FILECAUHOI);
		char buffer[10000];

		while (fgets(buffer, 10000, stream) != NULL) {
			if (buffer != NULL) {
				cauhoi ch = Tao_cauhoi_token(buffer);
				Insert_nodecauhoi(root, ch);
			}
		}
		//In_Inorder_cauhoi(root);
		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILECAUHOI);
	}
	return 1;
}

void Luu_cauhoi(cauhoi ch) {
	FILE* stream;
	errno_t err;
	int file_datontai = checkExistFile(FILECAUHOI);

	// a: append (Mo file va them vao cuoi cua file neu ton tai).
	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILECAUHOI, "a");

	if (file_datontai) {
		fprintf(stream, "%c", '\n');
	}

	if (err == 0)
	{
		fprintf(stream, "%d|%s|%s|%s|%s|%s|%s|%c", ch.id, ch.mamh, ch.noidung, ch.A, ch.B, ch.C, ch.D, ch.dapan);
		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILEKETQUATHI);
	}
}

cauhoi Tao_cauhoi(listmonhoc dsmonhoc) {
	cauhoi choi;

	choi.id = Generate_id();

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	In_dsmonhoc(dsmonhoc);
	while (1) {
		printf("Ma mon hoc (Toi da 14 ky tu): ");
		gets_s(choi.mamh);
		if (Search_monhoc_theo_mamh(dsmonhoc, choi.mamh) >= 0) {
			break;
		}
		else {
			printf("Khong tim thay ma mon hoc!\n\n");
		}
	}

	while (1) {
		printf("Noi dung cau hoi (Toi da 49 ky tu): ");
		gets_s(choi.noidung);

		if (strlen(choi.noidung) > 0) {
			break;
		}
		else {
			printf("Noi dung khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Dap an A (Toi da 49 ky tu): ");
		gets_s(choi.A);

		if (strlen(choi.A) > 0) {
			break;
		}
		else {
			printf("Dap an khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Dap an B (Toi da 49 ky tu): ");
		gets_s(choi.B);

		if (strlen(choi.B) > 0) {
			if (strcmp(choi.B, choi.A) != 0) {
				break;
			}
			else {
				printf("Dap an bi trung!\n\n");
			}
		}
		else {
			printf("Dap an khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Dap an C (Toi da 49 ky tu): ");
		gets_s(choi.C);

		if (strlen(choi.C) > 0) {
			if (strcmp(choi.C, choi.A) != 0 && strcmp(choi.C, choi.B) != 0) {
				break;
			}
			else {
				printf("Dap an bi trung!\n\n");
			}
		}
		else {
			printf("Dap an khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Dap an D (Toi da 49 ky tu): ");
		gets_s(choi.D);

		if (strlen(choi.D) > 0) {
			if (strcmp(choi.D, choi.A) != 0 && strcmp(choi.D, choi.B) != 0 && strcmp(choi.D, choi.C) != 0) {
				break;
			}
			else {
				printf("Dap an bi trung!\n\n");
			}
		}
		else {
			printf("Dap an khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Dap An: (Ky tu A,B,C,D - Co phan biet hoa thuong): ");
		choi.dapan = getchar();
		//ClearInputBuffer();
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);

		if (choi.dapan == 'A' || choi.dapan == 'B' || choi.dapan == 'C' || choi.dapan == 'D') {
			break;
		}
		else {
			printf("Dap an khong hop le!\n\n");
		}
	}

	return choi;
}

//Fisher–Yates shuffle
void Tron_dscauhoi(listcauhoi& dscauhoi) {
	sMyRand((int)time(NULL));
	int j;
	for (int i = dscauhoi.n - 1; i > 1; i--) {
		j = getRand(0, i);
		if (i != j) {
			//Hoan doi
			cauhoi temp = dscauhoi.data[i];
			dscauhoi.data[i] = dscauhoi.data[j];
			dscauhoi.data[j] = temp;
		}
	}
}

void Tron_dsdapan(char* dsdapan[MAXCAUHOI], char& dapan) {
	int j;
	//Tron tu vi tri 0 - 2, vi vi tri 3 da chua dap an
	for (int i = MAXCAUHOI - 1; i > 1; i--) {
		j = getRand(0, i);
		//printf("i= %d, j= %d, da= %d", i, j, dapan - 'A');
		if (i != j) {
			//Neu vi tri hoan doi trung voi vi tri cua dap an thi ta thay doi dap an
			if (j == dapan - 'A') {
				dapan = 'A' + i;
			}
			else if (i == dapan - 'A') {
				dapan = 'A' + j;
			}

			//printf("DA. %s %c\n",dsdapan[i], dapan);
			//Hoan doi
			char* temp = (char*)malloc(500);
			strcpy_s(temp, 500, dsdapan[i]);
			strcpy_s(dsdapan[i], 500, dsdapan[j]);
			strcpy_s(dsdapan[j], 500, temp);
		}
	}
}

void Tron_dapandscauhoi(listcauhoi& dscauhoi) {
	sMyRand((int)time(NULL));
	for (int i = 0; i < dscauhoi.n; i++)
	{
		char* dsdapan[MAXCAUHOI];
		dsdapan[0] = (char*)malloc(500);
		dsdapan[1] = (char*)malloc(500);
		dsdapan[2] = (char*)malloc(500);
		dsdapan[3] = (char*)malloc(500);

		strcpy_s(dsdapan[0], 500, dscauhoi.data[i].A);
		strcpy_s(dsdapan[1], 500, dscauhoi.data[i].B);
		strcpy_s(dsdapan[2], 500, dscauhoi.data[i].C);
		strcpy_s(dsdapan[3], 500, dscauhoi.data[i].D);

		Tron_dsdapan(dsdapan, dscauhoi.data[i].dapan);

		strcpy_s(dscauhoi.data[i].A, 500, dsdapan[0]);
		strcpy_s(dscauhoi.data[i].B, 500, dsdapan[1]);
		strcpy_s(dscauhoi.data[i].C, 500, dsdapan[2]);
		strcpy_s(dscauhoi.data[i].D, 500, dsdapan[3]);
	}
}

PTR_nodecauhoi Search_cauhoi(PTR_nodecauhoi root, int id) {
	PTR_nodecauhoi p;
	p = root;

	while (p != NULL && p->data.id != id) {
		if (id < p->data.id) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}

	return p;
}

void Nhap_cauhoi(PTR_nodecauhoi& root, listmonhoc dsmonhoc) {
	if (Empty_monhoc(dsmonhoc)) {
		printf("Danh sach mon hoc rong!\n");
		return;
	}

	char tieptuc;
	do {
		cauhoi ch = Tao_cauhoi(dsmonhoc);
		Insert_nodecauhoi(root, ch);
		In_Inorder_cauhoi(root);
		Luu_cauhoi(ch);
		printf("Ban co muon tiep tuc them (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();
	} while (tieptuc == 'y' || tieptuc == 'Y');
}

void In_dscauhoi(listcauhoi ds) {
	if (ds.n == 0) {
		printf("Danh sach cau hoi rong!\n");
	}
	printf("\n");
	for (int i = 0; i < ds.n; i++)
	{
		printf("id = %s\n", ds.data[i].id);
		printf("Noi dung: %s\n", ds.data[i].noidung);
		printf("A. %s B. %s C. %s D. %s\n", ds.data[i].A, ds.data[i].B, ds.data[i].C, ds.data[i].D);
		printf("DA. %c\n\n", ds.data[i].dapan);
	}
}

int Insert_itemcauhoi(listcauhoi& ds, int i, cauhoi ch) {
	int j;
	if (i < 0 || i > ds.n)
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = ch;
	ds.n++;
	return 1;
}

//listcauhoi Get_listcauhoi_bang_listidcauhoi(PTR_nodecauhoi root_cauhoi, listcautraloi dsidcauhoi, listmonhoc dsmonhoc) {
//	listcauhoi dscauhoi;
//	dscauhoi.n = 0;
//	dscauhoi.data = (PTR_cauhoi)malloc(sizeof(struct cauhoi) * dsidcauhoi.n);
//
//	for (int i = 0; i < dsidcauhoi.n; i++)
//	{
//		PTR_nodecauhoi p_cauhoi = Search_cauhoi(root_cauhoi, dsidcauhoi.data[i].idcauhoi);
//		Insert_itemcauhoi(dscauhoi, dscauhoi.n, p_cauhoi->data);
//	}
//	return dscauhoi;
//}