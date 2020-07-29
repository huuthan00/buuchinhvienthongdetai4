#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLISTMONHOC 500
#define MAXTHUOCTINHMONHOC 3
#define FILELOP "lop.txt"
#define FILEMONHOC "MonHoc.txt"
#define FILEKETQUATHI "ketquathi.txt"
#define DELIMITERTHUOCTINH "|"

int checkExistFile(const char* file) {
	FILE* stream;

	errno_t err;
	err = fopen_s(&stream, file, "r");

	if (err == 0) {
		fclose(stream);
		return 1;
	}

	return 0;
}


struct MonHoc {
	char MaMH[15];
	char TenMH[50];
};

typedef MonHoc* PTR_MonHoc;

struct ListMonHoc {
	int n = 0;					// so nut cua danh sach
	PTR_MonHoc data[MAXLISTMONHOC];	// danh sach mang 1 chieu con tro MonHoc (PTR_MonHoc)
};

void ClearInputBuffer(void) {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int isValidMaMH(char MaMH[15]) {

	if (strlen(MaMH) <= 0) return 0;

	for (int i = 0; i < strlen(MaMH); i++)
	{
		if (!((MaMH[i] >= 'A' && MaMH[i] <= 'Z') || MaMH[i] >= '0' && MaMH[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}


int Empty_MonHoc(ListMonHoc ds) {
	return ds.n == 0;
}

int Full_MonHoc(ListMonHoc ds) {
	return ds.n == MAXLISTMONHOC;
}

//Tim kiem nhi phan **********************************
int Search_MonHoc_Theo_MaMH(ListMonHoc ds, char MaMH[15]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(MaMH, ds.data[i]->MaMH) == 0) {
			return i;
		}
	}
	return -1;
}

int Delete_itemMonHoc(ListMonHoc& dsMonHoc, int i) {
	int j;
	if (i < 0 || i >= dsMonHoc.n || Empty_MonHoc(dsMonHoc))
		return 0;

	for (j = i + 1; j < dsMonHoc.n; j++) {
		dsMonHoc.data[j - 1] = dsMonHoc.data[j];
	}
	dsMonHoc.n--;
	return 1;
}

void In_dsMonHoc(ListMonHoc& ds) {
	for (int i = 0; i < ds.n; i++)
	{
		printf("%-15s %s\n", ds.data[i]->MaMH, ds.data[i]->TenMH);
	}
}

PTR_MonHoc Tao_MonHoc(ListMonHoc dsMonHoc) {
	PTR_MonHoc p = new MonHoc;

	ClearInputBuffer();
	while (1) {
		printf("Ma mon hoc (Toi da 14 ky tu): ");
		gets_s(p->MaMH);
		if (isValidMaMH(p->MaMH)) {
			if (Search_MonHoc_Theo_MaMH(dsMonHoc, p->MaMH) < 0) {
				break;
			}
			else {
				printf("Ma mon hoc bi trung!\n\n");
			}
		}
		else {
			printf("Ma mon hoc khong hop le!\n\n");
		}
	}

	while (1) {
		printf("Ten mon hoc (Toi da 49 ky tu): ");
		gets_s(p->TenMH);
		if (strlen(p->TenMH) > 0) {
			break;
		}
		else {
			printf("Ten mon hoc khong duoc rong!\n\n");
		}
	}

	return p;
}

PTR_MonHoc Tao_MonHoc_token(char* token) {
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHMONHOC];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHMONHOC) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	PTR_MonHoc p = new MonHoc;
	strncpy_s(p->MaMH, list_thuoctinh[0], 15);
	strncpy_s(p->TenMH, list_thuoctinh[1], 50);

	return p;
}

int Insert_ItemMonHoc(ListMonHoc& ds, int i, PTR_MonHoc p) {
	int j;
	if (i < 0 || i > ds.n || Full_MonHoc(ds))
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = p;
	ds.n++;
	return 1;
}

int Insert_ItemMonHoc_Order(ListMonHoc& ds, PTR_MonHoc p) {
	if (ds.n == 0) {
		return(Insert_ItemMonHoc(ds, 0, p));
	}

	if (Search_MonHoc_Theo_MaMH(ds, p->MaMH) > 0) {
		printf("\nMa mon hoc bi trung, vui long nhap lai!\n");
		return 0;
	}

	int vitri = 0;

	while (vitri < ds.n && strcmp(ds.data[vitri]->MaMH, p->MaMH) < 0) {
		vitri++;
	}

	//printf("vitri %d\n", vitri);

	Insert_ItemMonHoc(ds, vitri, p);
}

void Luu_DSMonHoc(ListMonHoc dsMonHoc) {
	FILE* stream;
	errno_t err;
	int file_datontai = checkExistFile(FILEMONHOC);

	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILEMONHOC, "w");

	if (err == 0)
	{
		for (int i = 0; i < dsMonHoc.n; i++)
		{
			fprintf(stream, "%s|%s", dsMonHoc.data[i]->MaMH, dsMonHoc.data[i]->TenMH);
			if (i < dsMonHoc.n - 1) {
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

int Update_ItemMonHoc(ListMonHoc& dsMonHoc, int i) {

	if (i < 0 || i >= dsMonHoc.n || Empty_MonHoc(dsMonHoc))
		return 0;

	char MaMHtemp[15];

	//while (1) {
	//	printf("Ma lop (Toi da 14 ky tu chi chua ky tu A->Z va 0->9): ");
	//	gets_s(MaMHtemp);
	//	if (isValidMalop(MaMHtemp)) {
	//		if (Search_MonHoc_Theo_MaMH(dsMonHoc, MaMHtemp) < 0) {
	//			strcpy_s(dsMonHoc.data[i]->MaMH, 15, MaMHtemp);
	//			break;
	//		}
	//		else {
	//			printf("Ma mon hoc da ton tai!\n\n");
	//		}
	//	}
	//	else {
	//		printf("Ma mon hoc khong hop le! Vui long nhap lai.\n\n");
	//	}
	//}

	while (1) {
		printf("Ten mon hoc (Toi da 49 ky tu): ");
		gets_s(dsMonHoc.data[i]->TenMH);
		if (strlen(dsMonHoc.data[i]->TenMH) > 0) {
			break;
		}
		else {
			printf("Ten mon hoc khong duoc rong!\n\n");
		}
	}

	return 1;
}

void Them_MonHoc(ListMonHoc& dsMonHoc) {
	char tieptuc;
	do {
		PTR_MonHoc p = Tao_MonHoc(dsMonHoc);
		Insert_ItemMonHoc_Order(dsMonHoc, p);
		In_dsMonHoc(dsMonHoc);
		Luu_DSMonHoc(dsMonHoc);
		printf("Ban co muon tiep tuc them (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();
	} while (tieptuc == 'y' || tieptuc == 'Y');

}

void Delete_MonHoc(ListMonHoc& dsMonHoc) {
	printf("\nXoa mon hoc:\n");

	if (Empty_MonHoc(dsMonHoc)) {
		printf("Danh sach rong, vui long them mon hoc!\n");
		return;
	}

	In_dsMonHoc(dsMonHoc);

	ClearInputBuffer();

	printf("Nhap ma so mon hoc can xoa: ");
	char malop[15];
	gets_s(malop);

	int vitricanxoa = Search_MonHoc_Theo_MaMH(dsMonHoc, malop);

	if (vitricanxoa == -1) {
		printf("Khong tim thay ma so mon hoc can xoa!\n");
		return;
	}

	if (Delete_itemMonHoc(dsMonHoc, vitricanxoa)) {
		Luu_DSMonHoc(dsMonHoc);
		printf("\nXoa thanh cong!\n\n");
		In_dsMonHoc(dsMonHoc);
	}
	else {
		printf("\nXoa that bai!\n");
	}
}

void Update_MonHoc(ListMonHoc& dsMonHoc) {
	printf("\nChinh sua mon hoc:\n");

	if (Empty_MonHoc(dsMonHoc)) {
		printf("Danh sach rong, vui long them mon hoc!\n");
		return;
	}

	In_dsMonHoc(dsMonHoc);

	ClearInputBuffer();

	printf("Nhap ma so mon hoc can sua: ");
	char malop[15];
	gets_s(malop);

	int vitricansua = Search_MonHoc_Theo_MaMH(dsMonHoc, malop);
	if (vitricansua == -1) {
		printf("Khong tim thay ma so mon hoc can xoa!\n");
		return;
	}

	if (Update_ItemMonHoc(dsMonHoc, vitricansua)) {
		Luu_DSMonHoc(dsMonHoc);
		printf("\nSua thanh cong!\n\n");
		In_dsMonHoc(dsMonHoc);
	}
	else {
		printf("\nSua that bai!\n");
	}
}

int Read_FileMonHoc(ListMonHoc& ds) {
	FILE* stream;

	errno_t err;
	err = fopen_s(&stream, FILEMONHOC, "r");
	if (err == 0)
	{
		//printf("Mo file %s thanh cong!\n", FILEMONHOC);
		char buffer[10000];

		while (fgets(buffer, 10000, stream) != NULL) {
			// lay token dau tien (lop)
			if (buffer != NULL) {
				PTR_MonHoc p = Tao_MonHoc_token(buffer);
				int len = strlen(p->TenMH);
				if (p->TenMH[len - 1] == '\n') {
					p->TenMH[len - 1] = '\0';
				}
				Insert_ItemMonHoc_Order(ds, p);
			}

			//int len = strlen(ds.data[ds.n - 1]->ptr_dssinhvien->sv.password);
			//ds.data[ds.n - 1]->ptr_dssinhvien->sv.password[len - 1] = '\0';
		}
		//In_dsMonHoc(ds);
		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILELOP);
	}
	return 1;
}

