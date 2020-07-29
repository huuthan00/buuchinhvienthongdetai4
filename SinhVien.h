#pragma once
#include "DiemThi.h"
#include "MonHoc.h"
#include <string.h>

struct SinhVien {
	char masv[15];
	char ho[20];
	char ten[20];
	int phai;
	char password[20];
	PTR_DiemThi ptr_dsdiemthi;
};

struct NodeSinhVien
{
	SinhVien sv;
	struct NodeSinhVien* next;
};

typedef NodeSinhVien* PTR_SinhVien;

void Get_Phai_String(int phai, char phai_string[4]) {
	if (phai == 0) {
		strcpy_s(phai_string, 4, "Nu");
	}
	else {
		strcpy_s(phai_string, 4, "Nam");
	}
}

PTR_SinhVien New_NodeSinhVien(void) {
	PTR_SinhVien p;
	p = (PTR_SinhVien)malloc(sizeof(struct NodeSinhVien));
	return p;
}

ListMonHoc Lay_DSMonHoc_DaThi_Lop(PTR_SinhVien First_SinhVien, ListMonHoc dsmonhocs) {
	ListMonHoc dsmonhocdathi;
	for (PTR_SinhVien p_SinhVien = First_SinhVien; p_SinhVien != NULL; p_SinhVien = p_SinhVien->next) {
		for (PTR_DiemThi p_diemthi = p_SinhVien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
			if (Search_MonHoc_Theo_MaMH(dsmonhocdathi, p_diemthi->dt.MaMH) < 0) {
				int indexMonhoc = Search_MonHoc_Theo_MaMH(dsmonhocs, p_diemthi->dt.MaMH);
				Insert_ItemMonHoc_Order(dsmonhocdathi, dsmonhocs.data[indexMonhoc]);
			}
		}
	}
	return dsmonhocdathi;
}

ListMonHoc Lay_DSMonHoc_DaThi_SV(PTR_SinhVien p_SinhVien, ListMonHoc dsmonhocs) {
	ListMonHoc dsmonhocdathi;
	for (PTR_DiemThi p_diemthi = p_SinhVien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
		if (Search_MonHoc_Theo_MaMH(dsmonhocdathi, p_diemthi->dt.MaMH) < 0) {
			int indexMonhoc = Search_MonHoc_Theo_MaMH(dsmonhocs, p_diemthi->dt.MaMH);
			Insert_ItemMonHoc_Order(dsmonhocdathi, dsmonhocs.data[indexMonhoc]);
		}
	}
	return dsmonhocdathi;
}

int isValidMaSV(char masv[15]) {

	if (strlen(masv) <= 0) return 0;

	for (int i = 0; i < strlen(masv); i++)
	{
		if (!((masv[i] >= 'A' && masv[i] <= 'Z') || masv[i] >= '0' && masv[i] <= '9')) {
			return 0;
		}
	}
	return 1;
}

void In_DSSinhVien(PTR_SinhVien First) {
	PTR_SinhVien p;
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
		Get_Phai_String(p->sv.phai, phai_string);
		printf("%-6d%-15s%-20s%-20s%s\n", ++stt, p->sv.masv, p->sv.ho, p->sv.ten, phai_string);
		p = p->next;
	}
}

void Insert_First_SinhVien(PTR_SinhVien& First, SinhVien sv) {
	PTR_SinhVien p = New_NodeSinhVien();
	p->sv = sv;
	p->next = First;
	First = p;
	//In_DSSinhVien(First);
}

// Neu tim thay se tra ve sinh vien can tim.
// Khong tim thay se tra ve sinh vien voi masv = rong
PTR_SinhVien Search_SinhVien_MaSV(PTR_SinhVien First, char masv[15]) {
	PTR_SinhVien p;
	for (p = First; p != NULL; p = p->next) {
		if (strcmp(p->sv.masv, masv) == 0) break;
	}
	//Neu khong tim thay
	//SinhVien sv;
	//strcpy_s(sv.masv, "");
	//strcpy_s(sv.password, "");
	return p;
}

void Initialize_SinhVien(PTR_SinhVien& First) {
	First = NULL;
}

void uppercase(char* str) {
	for (int i = 0; i < strlen(str); i++)
	{
		str[i] = toupper(str[i]);
	}
}

SinhVien Tao_SinhVien(PTR_SinhVien First_SinhVien) {
	SinhVien sv;

	while (1) {
		printf("Ma sinh vien (Toi da 14 ky tu): ");
		gets_s(sv.masv);
		if (isValidMaSV(sv.masv)) {
			if (Search_SinhVien_MaSV(First_SinhVien, sv.masv) == NULL && strcmp(sv.masv,"GV") != 0) {
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

void In_DiemSinhVien_MonHoc(PTR_SinhVien First_SinhVien, char MaMH[15]) {
	int stt = 0;
	int dathi = FALSE;
	printf("\n%-6s%-15s%-20s%-20s%s\n", "STT", "MA SINH VIEN", "HO", "TEN", "DIEM");
	for (PTR_SinhVien p_SinhVien = First_SinhVien; p_SinhVien != NULL; p_SinhVien = p_SinhVien->next) {
		dathi = FALSE;
		for (PTR_DiemThi p_diemthi = p_SinhVien->sv.ptr_dsdiemthi; p_diemthi != NULL; p_diemthi = p_diemthi->next) {
			if (strcmp(p_diemthi->dt.MaMH, MaMH) == 0) {
				printf("%-6d%-15s%-20s%-20s%.2f\n", ++stt, p_SinhVien->sv.masv, p_SinhVien->sv.ho, p_SinhVien->sv.ten, p_diemthi->dt.Diem);
				dathi = TRUE;
			}
		}
		if (!dathi) {
			printf("%-6d%-15s%-20s%-20s%s\n", ++stt, p_SinhVien->sv.masv, p_SinhVien->sv.ho, p_SinhVien->sv.ten, "Chua thi");
		}
	}
}