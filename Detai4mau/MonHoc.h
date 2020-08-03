#pragma once
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLISTMONHOC 500
#define MAXTHUOCTINHMONHOC 3
#define FILELOP "lop.txt"
#define FILEMONHOC "monhoc.txt"
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


struct monhoc {
	char mamh[15];
	char tenmh[50];
};

typedef monhoc* PTR_monhoc;

struct listmonhoc {
	int n = 0;					// so nut cua danh sach
	PTR_monhoc data[MAXLISTMONHOC];	// danh sach mang 1 chieu con tro monhoc (PTR_monhoc)
};

void ClearInputBuffer(void) {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

int isValidmamh(char mamh[15]) {

	if (strlen(mamh) <= 0) return 0;

	for (int i = 0; i < strlen(mamh); i++)
	{
		if (!((mamh[i] >= 'A' && mamh[i] <= 'Z') || mamh[i] >= '0' && mamh[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}


int Empty_monhoc(listmonhoc ds) {
	return ds.n == 0;
}

int Full_monhoc(listmonhoc ds) {
	return ds.n == MAXLISTMONHOC;
}

//Tim kiem nhi phan **********************************
int Search_monhoc_theo_mamh(listmonhoc ds, char mamh[15]) {
	for (int i = 0; i < ds.n; i++) {
		if (strcmp(mamh, ds.data[i]->mamh) == 0) {
			return i;
		}
	}
	return -1;
}

int Delete_itemmonhoc(listmonhoc& dsmonhoc, int i) {
	int j;
	if (i < 0 || i >= dsmonhoc.n || Empty_monhoc(dsmonhoc))
		return 0;

	for (j = i + 1; j < dsmonhoc.n; j++) {
		dsmonhoc.data[j - 1] = dsmonhoc.data[j];
	}
	dsmonhoc.n--;
	return 1;
}

void In_dsmonhoc(listmonhoc& ds) {
	for (int i = 0; i < ds.n; i++)
	{
		printf("%-15s %s\n", ds.data[i]->mamh, ds.data[i]->tenmh);
	}
}

PTR_monhoc Tao_monhoc(listmonhoc dsmonhoc) {
	PTR_monhoc p = new monhoc;

	ClearInputBuffer();
	while (1) {
		printf("Ma mon hoc (Toi da 14 ky tu): ");
		gets_s(p->mamh);
		if (isValidmamh(p->mamh)) {
			if (Search_monhoc_theo_mamh(dsmonhoc, p->mamh) < 0) {
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
		gets_s(p->tenmh);
		if (strlen(p->tenmh) > 0) {
			break;
		}
		else {
			printf("Ten mon hoc khong duoc rong!\n\n");
		}
	}

	return p;
}

PTR_monhoc Tao_monhoc_token(char* token) {
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

	PTR_monhoc p = new monhoc;
	strncpy_s(p->mamh, list_thuoctinh[0], 15);
	strncpy_s(p->tenmh, list_thuoctinh[1], 50);

	return p;
}

int Insert_itemmonhoc(listmonhoc& ds, int i, PTR_monhoc p) {
	int j;
	if (i < 0 || i > ds.n || Full_monhoc(ds))
		return 0;

	for (j = ds.n - 1; j >= i; j--) {
		ds.data[j + 1] = ds.data[j];
	}

	ds.data[i] = p;
	ds.n++;
	return 1;
}

int Insert_itemmonhoc_order(listmonhoc& ds, PTR_monhoc p) {
	if (ds.n == 0) {
		return(Insert_itemmonhoc(ds, 0, p));
	}

	if (Search_monhoc_theo_mamh(ds, p->mamh) > 0) {
		printf("\nMa mon hoc bi trung, vui long nhap lai!\n");
		return 0;
	}

	int vitri = 0;

	while (vitri < ds.n && strcmp(ds.data[vitri]->mamh, p->mamh) < 0) {
		vitri++;
	}

	//printf("vitri %d\n", vitri);

	Insert_itemmonhoc(ds, vitri, p);
}

void Luu_dsmonhoc(listmonhoc dsmonhoc) {
	FILE* stream;
	errno_t err;
	int file_datontai = checkExistFile(FILEMONHOC);

	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILEMONHOC, "w");

	if (err == 0)
	{
		for (int i = 0; i < dsmonhoc.n; i++)
		{
			fprintf(stream, "%s|%s", dsmonhoc.data[i]->mamh, dsmonhoc.data[i]->tenmh);
			if (i < dsmonhoc.n - 1) {
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

int Update_itemmonhoc(listmonhoc& dsmonhoc, int i) {

	if (i < 0 || i >= dsmonhoc.n || Empty_monhoc(dsmonhoc))
		return 0;

	char mamhtemp[15];

	//while (1) {
	//	printf("Ma lop (Toi da 14 ky tu chi chua ky tu A->Z va 0->9): ");
	//	gets_s(mamhtemp);
	//	if (isValidMalop(mamhtemp)) {
	//		if (Search_monhoc_theo_mamh(dsmonhoc, mamhtemp) < 0) {
	//			strcpy_s(dsmonhoc.data[i]->mamh, 15, mamhtemp);
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
		gets_s(dsmonhoc.data[i]->tenmh);
		if (strlen(dsmonhoc.data[i]->tenmh) > 0) {
			break;
		}
		else {
			printf("Ten mon hoc khong duoc rong!\n\n");
		}
	}

	return 1;
}

void Them_monhoc(listmonhoc& dsmonhoc) {
	char tieptuc;
	do {
		PTR_monhoc p = Tao_monhoc(dsmonhoc);
		Insert_itemmonhoc_order(dsmonhoc, p);
		In_dsmonhoc(dsmonhoc);
		Luu_dsmonhoc(dsmonhoc);
		printf("Ban co muon tiep tuc them (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();
	} while (tieptuc == 'y' || tieptuc == 'Y');

}

void Delete_monhoc(listmonhoc& dsmonhoc) {
	printf("\nXoa mon hoc:\n");

	if (Empty_monhoc(dsmonhoc)) {
		printf("Danh sach rong, vui long them mon hoc!\n");
		return;
	}

	In_dsmonhoc(dsmonhoc);

	ClearInputBuffer();

	printf("Nhap ma so mon hoc can xoa: ");
	char malop[15];
	gets_s(malop);

	int vitricanxoa = Search_monhoc_theo_mamh(dsmonhoc, malop);

	if (vitricanxoa == -1) {
		printf("Khong tim thay ma so mon hoc can xoa!\n");
		return;
	}

	if (Delete_itemmonhoc(dsmonhoc, vitricanxoa)) {
		Luu_dsmonhoc(dsmonhoc);
		printf("\nXoa thanh cong!\n\n");
		In_dsmonhoc(dsmonhoc);
	}
	else {
		printf("\nXoa that bai!\n");
	}
}

void Update_monhoc(listmonhoc& dsmonhoc) {
	printf("\nChinh sua mon hoc:\n");

	if (Empty_monhoc(dsmonhoc)) {
		printf("Danh sach rong, vui long them mon hoc!\n");
		return;
	}

	In_dsmonhoc(dsmonhoc);

	ClearInputBuffer();

	printf("Nhap ma so mon hoc can sua: ");
	char malop[15];
	gets_s(malop);

	int vitricansua = Search_monhoc_theo_mamh(dsmonhoc, malop);
	if (vitricansua == -1) {
		printf("Khong tim thay ma so mon hoc can xoa!\n");
		return;
	}

	if (Update_itemmonhoc(dsmonhoc, vitricansua)) {
		Luu_dsmonhoc(dsmonhoc);
		printf("\nSua thanh cong!\n\n");
		In_dsmonhoc(dsmonhoc);
	}
	else {
		printf("\nSua that bai!\n");
	}
}

int Read_filemonhoc(listmonhoc& ds) {
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
				PTR_monhoc p = Tao_monhoc_token(buffer);
				int len = strlen(p->tenmh);
				if (p->tenmh[len - 1] == '\n') {
					p->tenmh[len - 1] = '\0';
				}
				Insert_itemmonhoc_order(ds, p);
			}

			//int len = strlen(ds.data[ds.n - 1]->ptr_dssinhvien->sv.password);
			//ds.data[ds.n - 1]->ptr_dssinhvien->sv.password[len - 1] = '\0';
		}
		//In_dsmonhoc(ds);
		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILELOP);
	}
	return 1;
}

