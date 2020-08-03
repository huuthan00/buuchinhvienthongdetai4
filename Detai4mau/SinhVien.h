#pragma once
#include "DiemThi.h"
#include "MonHoc.h"
#include <string.h>

struct sinhvien {
	char masv[15];
	char ho[20];
	char ten[20];
	int phai;
	char password[20];
	PTR_diemthi ptr_dsdiemthi;
};

struct nodesinhvien
{
	sinhvien sv;
	struct nodesinhvien* next;
};

typedef nodesinhvien* PTR_sinhvien;

void get_phai_string(int phai, char phai_string[4]) {
	if (phai == 0) {
		strcpy_s(phai_string, 4, "Nu");
	}
	else {
		strcpy_s(phai_string, 4, "Nam");
	}
}

PTR_sinhvien New_nodesinhvien(void) {
	PTR_sinhvien p;
	p = (PTR_sinhvien)malloc(sizeof(struct nodesinhvien));
	return p;
}

listmonhoc Lay_dsmonhoc_dathi_lop(PTR_sinhvien First_sinhvien, listmonhoc dsmonhocs) {
	listmonhoc dsmonhocdathi;
	for (PTR_sinhvien p_sinhvien = First_sinhvien; p_sinhvien != NULL; p_sinhvien = p_sinhvien->next) {
		for (PTR_diemthi p_diemthi = p_sinhvien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
			if (Search_monhoc_theo_mamh(dsmonhocdathi, p_diemthi->dt.mamh) < 0) {
				int indexMonhoc = Search_monhoc_theo_mamh(dsmonhocs, p_diemthi->dt.mamh);
				Insert_itemmonhoc_order(dsmonhocdathi, dsmonhocs.data[indexMonhoc]);
			}
		}
	}
	return dsmonhocdathi;
}

listmonhoc Lay_dsmonhoc_dathi_sv(PTR_sinhvien p_sinhvien, listmonhoc dsmonhocs) {
	listmonhoc dsmonhocdathi;
	for (PTR_diemthi p_diemthi = p_sinhvien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
		if (Search_monhoc_theo_mamh(dsmonhocdathi, p_diemthi->dt.mamh) < 0) {
			int indexMonhoc = Search_monhoc_theo_mamh(dsmonhocs, p_diemthi->dt.mamh);
			Insert_itemmonhoc_order(dsmonhocdathi, dsmonhocs.data[indexMonhoc]);
		}
	}
	return dsmonhocdathi;
}

int isValidMasv(char masv[15]) {

	if (strlen(masv) <= 0) return 0;

	for (int i = 0; i < strlen(masv); i++)
	{
		if (!((masv[i] >= 'A' && masv[i] <= 'Z') || masv[i] >= '0' && masv[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

void In_danhsachsinhvien(PTR_sinhvien First) {
	PTR_sinhvien p;
	int stt = 0;
	p = First;
	if (p == NULL) {
		printf("\Danh sach sinh vien rong!\n");
		return;
	}
	printf("\n%-6s%-15s%-20s%-20s%s\n", "STT", "MA SINH VIEN", "HO", "TEN", "PHAI");
	printf("--------------------------------------------------------------------------------\n");
	while (p != NULL) {
		char phai_string[4];
		get_phai_string(p->sv.phai, phai_string);
		printf("%-6d%-15s%-20s%-20s%s\n", ++stt, p->sv.masv, p->sv.ho, p->sv.ten, phai_string);
		p = p->next;
	}
}

void Insert_first_sinhvien(PTR_sinhvien& First, sinhvien sv) {
	PTR_sinhvien p = New_nodesinhvien();
	p->sv = sv;
	p->next = First;
	First = p;
	//In_danhsachsinhvien(First);
}

// Neu tim thay se tra ve sinh vien can tim.
// Khong tim thay se tra ve sinh vien voi masv = rong
PTR_sinhvien Search_sinhvien_masv(PTR_sinhvien First, char masv[15]) {
	PTR_sinhvien p;
	for (p = First; p != NULL; p = p->next) {
		if (strcmp(p->sv.masv, masv) == 0) break;
	}
	//Neu khong tim thay
	//sinhvien sv;
	//strcpy_s(sv.masv, "");
	//strcpy_s(sv.password, "");
	return p;
}

void Initialize_sinhvien(PTR_sinhvien& First) {
	First = NULL;
}

void uppercase(char* str) {
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}
}

sinhvien Tao_sinhvien(PTR_sinhvien First_sinhvien) {
	sinhvien sv;

	while (1) {
		printf("Ma sinh vien (Toi da 14 ky tu): ");
		gets_s(sv.masv);
		if (isValidMasv(sv.masv)) {
			if (Search_sinhvien_masv(First_sinhvien, sv.masv) == NULL && strcmp(sv.masv,"GV") != 0) {
				break;
			}
			else {
				printf("Ma sinh vien bi trung!\n\n");
			}
		}
		else {
			printf("ma sinh vien khong hop le!\n\n");
		}
	}

	while (1) {
		printf("Ho (Toi da 19 ky tu): ");
		gets_s(sv.ho);
		if (strlen(sv.ho) > 0) {
			break;
		}
		else {
			printf("Ho khong duoc rong!\n\n");
		}
	}

	while (1) {
		printf("Ten (Toi da 19 ky tu): ");
		gets_s(sv.ten);
		if (strlen(sv.ten) > 0) {
			break;
		}
		else {
			printf("Ten khong duoc rong!\n\n");
		}
	}

	while (1) {
		sv.phai = -1;

		printf("Phai (0: Nu, 1: Nam): ");
		scanf_s("%d", &sv.phai);

		if (sv.phai == 1 || sv.phai == 0) {
			break;
		}
		else if (sv.phai < 0) {
			printf("Phai khong hop le!\n\n");
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
		}
		else {
			printf("Phai khong hop le!\n\n");
		}
	}

	//ClearInputBuffer();
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);

	while (1) {
		printf("password (Toi da 19 ky tu): ");
		gets_s(sv.password);
		if (strlen(sv.password) > 0) {
			break;
		}
		else {
			printf("Password khong duoc rong!\n\n");
		}
	}

	sv.ptr_dsdiemthi = NULL;

	return sv;
}

void In_diemsinhvien_monhoc(PTR_sinhvien First_sinhvien, char mamh[15]) {
	int stt = 0;
	int dathi = FALSE;
	printf("\n%-6s%-15s%-20s%-20s%s\n", "STT", "MA SINH VIEN", "HO", "TEN", "DIEM");
	for (PTR_sinhvien p_sinhvien = First_sinhvien; p_sinhvien != NULL; p_sinhvien = p_sinhvien->next) {
		dathi = FALSE;
		for (PTR_diemthi p_diemthi = p_sinhvien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
			if (strcmp(p_diemthi->dt.mamh, mamh) == 0) {
				printf("%-6d%-15s%-20s%-20s%.2f\n", ++stt, p_sinhvien->sv.masv, p_sinhvien->sv.ho, p_sinhvien->sv.ten, p_diemthi->dt.diem);
				dathi = TRUE;
			}
		}
		if (!dathi) {
			printf("%-6d%-15s%-20s%-20s%s\n", ++stt, p_sinhvien->sv.masv, p_sinhvien->sv.ho, p_sinhvien->sv.ten, "Chua thi");
		}
	}
}