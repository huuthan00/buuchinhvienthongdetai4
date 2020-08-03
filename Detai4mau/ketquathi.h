#pragma once
#include "CauHoi.h"
#include "MonHoc.h"

#define FILEKETQUATHI "ketquathi.txt"
#define MAXTHUOCTINHKETQUATHI 4
#define MAXTHUOCTINHCAUTRALOI 9
#define DELIMITERKETQUATHI_DSCAUTRALOI "/"
#define DELIMITERCAUTRALOI "~"

struct ketquathi {
	char masv[15];
	char mamh[15];
	char malop[15];
	int sophuthi;
	listcautraloi dscautraloi;
};

struct nodeketquathi {
	ketquathi kqthi;
	struct nodeketquathi* next;
};

typedef nodeketquathi* PTR_ketquathi;

void Insert_first_ketquathi(PTR_ketquathi& First, ketquathi kqt) {
	PTR_ketquathi p = new nodeketquathi;
	p->kqthi = kqt;
	p->next = First;
	First = p;
}

PTR_ketquathi Search_ketquathi_masv_mamh(PTR_ketquathi First_ketquathi, char masv[15], char mamh[15]) {
	PTR_ketquathi p_ketquathi = NULL;
	for (p_ketquathi = First_ketquathi; p_ketquathi != NULL; p_ketquathi = p_ketquathi->next) {
		if (strcmp(p_ketquathi->kqthi.masv, masv) == 0 && strcmp(p_ketquathi->kqthi.mamh, mamh) == 0) {
			break;
		}
	}
	return p_ketquathi;
}

void In_danhsachketquathi_sinhvien_msmh(PTR_ketquathi First_ketquathi, PTR_nodecauhoi root_cauhoi, listmonhoc dsmonhoc, PTR_sinhvien p_sinhvien, char mamh[15]) {
	PTR_ketquathi p_ketquathi = Search_ketquathi_masv_mamh(First_ketquathi, p_sinhvien->sv.masv, mamh);

	if (p_ketquathi == NULL) {
		printf("Khong tim thay ket qua thi can tim!\n\n");
		return;
	}

	int vitrimonhoc = -1;

	vitrimonhoc = Search_monhoc_theo_mamh(dsmonhoc, p_ketquathi->kqthi.mamh);
	printf("Sinh vien: %s - %s %s\n", p_sinhvien->sv.masv, p_sinhvien->sv.ho, p_sinhvien->sv.ten);
	printf("Mon Hoc: %s - %s\n", dsmonhoc.data[vitrimonhoc]->mamh, dsmonhoc.data[vitrimonhoc]->tenmh);
	printf("Tong so cau hoi: %d \n", p_ketquathi->kqthi.dscautraloi.n);
	printf("So phut thi: %d \n", p_ketquathi->kqthi.sophuthi);
	printf("-----------------------------------------------------------------------------\n");
	for (int i = 0; i < p_ketquathi->kqthi.dscautraloi.n; i++)
	{
		printf("id = %d\n", p_ketquathi->kqthi.dscautraloi.data[i].ch.id);
		printf("Noi dung: %s\n", p_ketquathi->kqthi.dscautraloi.data[i].ch.noidung);
		printf("A. %s B. %s C. %s D. %s\n", p_ketquathi->kqthi.dscautraloi.data[i].ch.A, p_ketquathi->kqthi.dscautraloi.data[i].ch.B,
			p_ketquathi->kqthi.dscautraloi.data[i].ch.C, p_ketquathi->kqthi.dscautraloi.data[i].ch.D);
		printf("DA. %c\n", p_ketquathi->kqthi.dscautraloi.data[i].ch.dapan);
		printf("Cau tra loi: %c\n", p_ketquathi->kqthi.dscautraloi.data[i].cautraloi);
		printf("-----------------------------------------------------------------------------\n");
	}
	PTR_diemthi p_diemthi = Search_diemthi_mamh(p_sinhvien->sv.ptr_dsdiemthi, p_ketquathi->kqthi.mamh);
	printf("Diem: %f\n\n\n", p_diemthi->dt.diem);
}

void In_ketquathi(listlop dslop, PTR_ketquathi First_ketquathi, PTR_nodecauhoi root_cauhoi, listmonhoc dsmonhoc) {

	if (First_ketquathi == NULL) {
		printf("Chua co ket qua thi!\n");
		return;
	}
	char masv[15];
	for (int i = 0; i < dslop.n; i++)
	{
		In_danhsachsinhvien(dslop.data[i]->ptr_dssinhvien);
	}

	printf("\nHay nhap ma sinh vien can In: ");
	gets_s(masv);

	system("cls");

	int indexLop;
	PTR_sinhvien p_sinhvien = Search_sinhvien_dslop_masv(dslop, masv, indexLop);
	if (p_sinhvien != NULL) {
		listmonhoc dsmonhoc_dathi = Lay_dsmonhoc_dathi_sv(p_sinhvien, dsmonhoc);

		for (int i = 0; i < dsmonhoc_dathi.n; i++)
		{
			In_danhsachketquathi_sinhvien_msmh(First_ketquathi, root_cauhoi, dsmonhoc, p_sinhvien, dsmonhoc.data[i]->mamh);
		}
	}
	else {
		printf("Khong tim thay sinh vien");
	}
	
}

cautraloi Tao_cautraloi_token(char* token) {
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHCAUTRALOI];
	int vitri_thuoctinh = 0;

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token, DELIMITERTHUOCTINHCAUHOI, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHCAUTRALOI) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINHCAUHOI, &nextToken_thuoctinh);
	}
	cautraloi ctl;
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

	ctl.ch = ch;
	ctl.cautraloi = list_thuoctinh[8][0];

	return ctl;
}

int get_size_dscautraloi_token(char* token) {
	int tong = 1;
	for (int i = 0; i < strlen(token); i++)
	{
		if (token[i] == '~') {
			tong++;
		}
	}
	return tong;
}

listcautraloi Tao_dscautraloi_token(char* token) {
	listcautraloi dscautraloi;
	int size = get_size_dscautraloi_token(token);
	dscautraloi.data = ((PTR_cautraloi)malloc(sizeof(struct cautraloi)*size));

	char* token_cautraloi, * nextToken_cautraloi;
	token_cautraloi = strtok_s(token, DELIMITERCAUTRALOI, &nextToken_cautraloi);

	while (token_cautraloi != NULL) {
		cautraloi ctl = Tao_cautraloi_token(token_cautraloi);
		Insert_itemcautraloi(dscautraloi,dscautraloi.n, ctl);
		token_cautraloi = strtok_s(NULL, DELIMITERCAUTRALOI, &nextToken_cautraloi);
	}
	return dscautraloi;
}

ketquathi Tao_ketquathi_token(char* token) {
	char* token_ketquathi, * nextToken_ketquathi;
	char* token_thuoctinh, * nextToken_thuoctinh;
	char* list_thuoctinh[MAXTHUOCTINHKETQUATHI];
	int vitri_thuoctinh = 0;

	token_ketquathi = strtok_s(token, DELIMITERKETQUATHI_DSCAUTRALOI, &nextToken_ketquathi);

	// lay token dau tien (thuoctinh)
	token_thuoctinh = strtok_s(token_ketquathi, DELIMITERTHUOCTINH, &nextToken_thuoctinh);

	while (token_thuoctinh != NULL && vitri_thuoctinh < MAXTHUOCTINHCAUHOI) {
		list_thuoctinh[vitri_thuoctinh] = token_thuoctinh;
		vitri_thuoctinh++;
		token_thuoctinh = strtok_s(NULL, DELIMITERTHUOCTINH, &nextToken_thuoctinh);
	}

	ketquathi kqt;

	char* p;
	strncpy_s(kqt.malop, list_thuoctinh[0], 15);
	strncpy_s(kqt.masv, list_thuoctinh[1], 15);
	strncpy_s(kqt.mamh, list_thuoctinh[2], 15);
	kqt.sophuthi = strtol(list_thuoctinh[3], &p, 10);

	kqt.dscautraloi = Tao_dscautraloi_token(nextToken_ketquathi);;
	return kqt;
}

int Read_fileketquathi(PTR_ketquathi &First_ketquathi) {
	FILE* stream;

	errno_t err;
	err = fopen_s(&stream, FILEKETQUATHI, "r");
	if (err == 0)
	{
		//printf("Mo file %s thanh cong!\n", FILECAUHOI);
		char buffer[10000];

		while (fgets(buffer, 10000, stream) != NULL) {
			if (buffer != NULL) {
				ketquathi kqt = Tao_ketquathi_token(buffer);
				Insert_first_ketquathi(First_ketquathi, kqt);
			}
		}
		//In_Inorder_cauhoi(root);
		fclose(stream);
	}
	else
	{
		//printf("Chua co ket qua thi!\n", FILEKETQUATHI);
	}
	return 1;
}