#include <malloc.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h> // Sleep

#include "Lop.h"
#include "random.h"
#include "ketquathi.h"

int laGiaoVien = 0;
int laSinhVien = 0;

void loadData(listlop& dslop, PTR_nodecauhoi& root_cauhoi, listmonhoc& dsmonhoc, PTR_ketquathi& First_ketquathi) {
	Read_filelop(dslop);
	Read_filecauhoi(root_cauhoi);
	Read_filemonhoc(dsmonhoc);
	Read_fileketquathi(First_ketquathi);
}

int menu_giaovien() {
	int chucnang;
	//system("cls");
	printf("\n\nCHUONG TRINH THI TRAC NGHIEM \n");
	printf("Cac chuc nang cua chuong trinh:\n");
	printf("	2: Them lop\n");
	printf("	3: Xoa lop\n");
	printf("	4: Sua lop\n");
	printf("	5: In danh sach lop theo nien khoa\n");
	printf("	6: Nhap sinh vien theo lop\n");
	printf("	7: Them mon hoc\n");
	printf("	8: Xoa mon hoc\n");
	printf("	9: Sua mon hoc\n");
	printf("	10: Nhap cau hoi thi\n");
	printf("	11: In chi tiet mon hoc da thi\n");
	printf("	12: In bang diem cua mot lop\n");
	printf("	0: Thoat\n");
	printf("Chuc nang ban chon: ");

	do
		scanf_s("%d", &chucnang);
	while (chucnang < 0 || chucnang > 12);

	return chucnang;
}

void check_cauhoi(int& socautraloidung, int& vitricauhoi, char cautraloi, char dapan) {
	if (dapan == cautraloi) {
		socautraloidung++;
		vitricauhoi++;
	}
	else {
		vitricauhoi++;
	}
}

void Luu_diem(PTR_sinhvien& p, char mamh[15], int socautraloidung, int tongcauhoithi) {
	diemthi dt;
	strcpy_s(dt.mamh, 15, mamh);
	dt.diem = (socautraloidung * 1.0 / tongcauhoithi) * 10.0;
	Insert_First_diemthi(p->sv.ptr_dsdiemthi, dt);
	printf("\n\ndiem= %f\n\n", dt.diem);
}

void Luu_ketquathi(PTR_ketquathi First_ketquathi) {
	FILE* stream;
	errno_t err;
	int file_datontai = checkExistFile(FILEKETQUATHI);

	// a: append (Mo file va them vao cuoi cua file neu ton tai).
	// Neu khong ton tai thi tao file moi.
	err = fopen_s(&stream, FILEKETQUATHI, "a");

	if (file_datontai) {
		fprintf(stream, "%c", '\n');
	}

	if (err == 0)
	{
		//printf("Mo file %s thanh cong!\n", FILEKETQUATHI);
		char buffer[10000];
		for (PTR_ketquathi p = First_ketquathi; p != NULL; p = p->next) {
			fprintf(stream, "%s|%s|%s|%d/", p->kqthi.malop, p->kqthi.masv, p->kqthi.mamh, p->kqthi.sophuthi);
			for (int i = 0; i < p->kqthi.dscautraloi.n; i++)
			{
				fprintf(stream, "%d|%s|%s|%s|%s|%s|%s|%c|%c", p->kqthi.dscautraloi.data[i].ch.id, p->kqthi.dscautraloi.data[i].ch.mamh,
					p->kqthi.dscautraloi.data[i].ch.noidung, p->kqthi.dscautraloi.data[i].ch.A,
					p->kqthi.dscautraloi.data[i].ch.B, p->kqthi.dscautraloi.data[i].ch.C,
					p->kqthi.dscautraloi.data[i].ch.D, p->kqthi.dscautraloi.data[i].ch.dapan,
					p->kqthi.dscautraloi.data[i].cautraloi);

				if (i < p->kqthi.dscautraloi.n - 1) {
					fprintf(stream, "%c", '~');
				}
			}

		}

		fclose(stream);
	}
	else
	{
		printf("Mo file %s that bai!\n", FILEKETQUATHI);
	}
}

void Luu_cautraloi(ketquathi& kqt, cauhoi ch, char cautl) {
	cautraloi ctl;
	ctl.cautraloi = cautl;
	ctl.ch = ch;
	Insert_itemcautraloi(kqt.dscautraloi, kqt.dscautraloi.n, ctl);
}

void Thi(listlop& dslop, char malop[15], PTR_sinhvien& p_sinhvien, char monthi[15], listcauhoi dscauhoithi, int tongthoigian, PTR_ketquathi& First_kqthi) {

	int socautraloidung = 0;
	int thoigianbatdau = (int)time(NULL);
	int vitricauhoi = 0;

	//Khoi tao ket qua thi
	ketquathi kqt;
	kqt.dscautraloi.data = (PTR_cautraloi)malloc(sizeof(struct cautraloi) * dscauhoithi.n);
	strcpy_s(kqt.malop, 15, malop);
	strcpy_s(kqt.mamh, 15, monthi);
	strcpy_s(kqt.masv, p_sinhvien->sv.masv);
	kqt.sophuthi = tongthoigian;

	while (1) {
		system("cls");
		printf("\nThoi gian con lai %ds\n", tongthoigian - ((int)time(NULL) - thoigianbatdau));

		if ((int)time(NULL) - thoigianbatdau >= tongthoigian) {
			printf("\nDa het thoi gian - Phan thi ket thuc!!\n\n");
			Insert_first_ketquathi(First_kqthi, kqt);
			Luu_diem(p_sinhvien, monthi, socautraloidung, dscauhoithi.n);
			Luu_ketquathi(First_kqthi);
			break;
		}

		printf("\n\n------------------------------THI TRAC NGHIEM-----------------------------------------\n\n");
		printf("Cau hoi %d/%d: %s\n", vitricauhoi + 1, dscauhoithi.n, dscauhoithi.data[vitricauhoi].noidung);
		printf("A. %s B. %s C. %s D.%s\n",
			dscauhoithi.data[vitricauhoi].A, dscauhoithi.data[vitricauhoi].B,
			dscauhoithi.data[vitricauhoi].C, dscauhoithi.data[vitricauhoi].D);
		printf("Moi ban chon cau tra loi: ");

		if (GetAsyncKeyState('A')) {
			Luu_cautraloi(kqt, dscauhoithi.data[vitricauhoi], 'A');
			check_cauhoi(socautraloidung, vitricauhoi, 'A', dscauhoithi.data[vitricauhoi].dapan);
		}

		//if (GetAsyncKeyState('B')) {
		//	check_cauhoi(socautraloidung, vitricauhoi, 'B', dscauhoithi.data[vitricauhoi].dapan);
		//	Luu_cautraloi(kqt, dscauhoithi.data[vitricauhoi], 'B');
		//}

		if (GetAsyncKeyState('C')) {
			Luu_cautraloi(kqt, dscauhoithi.data[vitricauhoi], 'C');
			check_cauhoi(socautraloidung, vitricauhoi, 'C', dscauhoithi.data[vitricauhoi].dapan);
		}

		if (GetAsyncKeyState('D')) {
			Luu_cautraloi(kqt, dscauhoithi.data[vitricauhoi], 'D');
			check_cauhoi(socautraloidung, vitricauhoi, 'D', dscauhoithi.data[vitricauhoi].dapan);
		}

		if ((int)time(NULL) - thoigianbatdau >= tongthoigian) {
			printf("\nDa het thoi gian - Phan thi ket thuc!!\n\n");
			Insert_first_ketquathi(First_kqthi, kqt);
			Luu_diem(p_sinhvien, monthi, socautraloidung, dscauhoithi.n);
			Luu_ketquathi(First_kqthi);
			break;
		}

		if (vitricauhoi >= dscauhoithi.n) {
			printf("\nPhan thi ket thuc!!\n\n");
			Insert_first_ketquathi(First_kqthi, kqt);
			Luu_diem(p_sinhvien, monthi, socautraloidung, dscauhoithi.n);
			Luu_dslop(dslop);
			Luu_ketquathi(First_kqthi);
			break;
		}

		Sleep(200);
	}
}

void Khoitao_baithi(listlop& dslop, char malop[15], listmonhoc dsmonhoc, PTR_nodecauhoi root_cauhoi, PTR_sinhvien& p_sinhvien, PTR_ketquathi& First_ketquathi) {
	system("cls");
	if (Empty_monhoc(dsmonhoc)) {
		printf("Danh sach mon hoc rong!");
		return;
	}
	if (root_cauhoi == NULL) {
		printf("Danh sach cau hoi thi rong!");
		return;
	}

	int stt_monhoc;
	int tongso_cauhoi = 0;
	char mamh[15];
	int socauhoi;
	int thoigianthi_phut;//tinh theo phut.
	listcauhoi dscauhoi;
	In_dsmonhoc(dsmonhoc);
	while (1) {
		printf("Hay chon mon thi (mamh): ");
		gets_s(mamh);
		stt_monhoc = Search_monhoc_theo_mamh(dsmonhoc, mamh);

		if (stt_monhoc >= 0) {
			if (Search_ketquathi_masv_mamh(First_ketquathi, p_sinhvien->sv.masv, mamh) == NULL) {
				tongso_cauhoi = Tong_cauhoi_cua_monhoc(root_cauhoi, mamh);

				dscauhoi.n = tongso_cauhoi;
				dscauhoi.data = (PTR_cauhoi)malloc(sizeof(struct cauhoi) * tongso_cauhoi);
				//printf("dscauhoi = %d\n", &dscauhoi.data);
				int index = 0;

				//printf("mangcauhoi: %d\n", &dscauhoi.data);
				Lay_dscauhoi_theo_mamh(root_cauhoi, mamh, &dscauhoi.data, index);
				//In_dscauhoi(dscauhoi);
				Tron_dscauhoi(dscauhoi);
				//In_dscauhoi(dscauhoi);
				printf("Tong so cau hoi cua mon %s la: %d\n", mamh, tongso_cauhoi);
				if (stt_monhoc >= 0 && tongso_cauhoi > 0) {
					break;
				}


				else if (tongso_cauhoi <= 0) {
					printf("Mon hoc hien tai khong co cau hoi nao!\n");
				}
			}
			else {
				printf("Ban da thi mon %s\n", mamh);
			}
		}
		else {
			printf("Khong tim thay mon hoc!\n\n");
		}
	}

	while (1) {
		printf("Nhap so cau hoi <= %d : ", tongso_cauhoi);
		scanf_s("%d", &socauhoi);

		if (socauhoi <= tongso_cauhoi && socauhoi > 0) break;

		if (socauhoi > tongso_cauhoi) {
			printf("So cau hoi khong hop le (Khong du so cau hoi) vui long nhap lai\n");
		}
		else {
			printf("So cau hoi phai la so lon hon 0, vui long nhap lai!\n");
		}

	}

	listcauhoi dscauhoithi;
	dscauhoithi.n = socauhoi;
	//printf("dsch: $d", &dscauhoi.data);
	dscauhoithi.data = dscauhoi.data;
	//printf("dscht: $d", &dscauhoithi.data);
	//printf("\n------------------------Truoc tron----------------------------------\n");
	//In_dscauhoi(dscauhoithi);
	Tron_dapandscauhoi(dscauhoithi);
	//printf("\n------------------------Sau tron----------------------------------\n");
	//In_dscauhoi(dscauhoithi);

	while (1)
	{
		printf("Nhap so phut: ");
		scanf_s("%d", &thoigianthi_phut);

		if (thoigianthi_phut > 0) break;

		printf("Thoi gian khong hop le, hay nhap so lon hon 0!\n");
	}
	//ClearInputBuffer();
	Thi(dslop, malop, p_sinhvien, mamh, dscauhoithi, thoigianthi_phut, First_ketquathi);
}

void Dang_nhap(listlop dslop, int& stt_lop_sinhvien_dangnhap, PTR_sinhvien& p_sinhvien) {
	char tieptuc;
	char taikhoan[15];
	char password[20];
	do {
		printf("Tai khoan: ");
		gets_s(taikhoan);
		printf("Mat khau: ");
		gets_s(password);

		uppercase(taikhoan);

		if (strcmp(taikhoan, "GV") == 0 && strcmp(password, "GV") == 0) {
			laGiaoVien = 1;
			break;
		}
		else {
			p_sinhvien = Search_sinhvien_dslop_masv(dslop, taikhoan, stt_lop_sinhvien_dangnhap);
			if (stt_lop_sinhvien_dangnhap >= 0 && strcmp(p_sinhvien->sv.password, password) == 0) { // Tim thay sinh vien
				laSinhVien = 1;
				break;
			}
		}
		printf("Thong tin dang nhap khong chinh xac!\n");
		printf("Ban co muon dang nhap lai (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();

		//ClearInputBuffer();
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	} while (tieptuc == 'y' || tieptuc == 'Y');
}

void Chon_menu_giaovien(listlop& dslop, listmonhoc& dsmonhoc, PTR_ketquathi& First_ketquathi, PTR_nodecauhoi& root_cauhoi) {
	int chucnang;
	do {
		chucnang = menu_giaovien();
		switch (chucnang)
		{
		case 1:
			system("cls");
			//printf("\nChuc nang chua hoan thien!\n");
			break;
		case 2:
			system("cls");
			Add_lop(dslop);
			break;
		case 3:
			system("cls");
			Delete_lop(dslop);
			break;
		case 4:
			system("cls");
			Update_lop(dslop);
			break;
		case 5:
			system("cls");
			In_danhsachlop_nienkhoa(dslop);
			break;
		case 6:
			system("cls");
			Nhap_sinhvien(dslop);
			break;
		case 7:
			system("cls");
			Them_monhoc(dsmonhoc);
			break;
		case 8:
			system("cls");
			Delete_monhoc(dsmonhoc);
			break;
		case 9:
			system("cls");
			Update_monhoc(dsmonhoc);
			break;
		case 10:
			system("cls");
			Nhap_cauhoi(root_cauhoi, dsmonhoc);
			break;
		case 11:
			system("cls");
			In_ketquathi(dslop, First_ketquathi, root_cauhoi, dsmonhoc);
			break;
		case 12:
			system("cls");
			In_bandiem_lop(dslop, dsmonhoc);
			break;
		default:
			break;
		}

		//Clear buffer reader
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);

	} while (chucnang != 0);
}

int main(int argc, char** argv) {
	listlop dslop;
	listmonhoc dsmonhoc;
	PTR_nodecauhoi root_cauhoi = NULL;
	PTR_ketquathi First_ketquathi = NULL;

	loadData(dslop, root_cauhoi, dsmonhoc, First_ketquathi);

	PTR_sinhvien p_sinhvien_dangnhap = NULL;

	int stt_lop_sinhvien_dangnhap = -1;//Luu index cua lop duoc dang nhap trong dslop

	char tieptuc;
	do {
		laSinhVien = FALSE;
		laGiaoVien = FALSE;

		Dang_nhap(dslop, stt_lop_sinhvien_dangnhap, p_sinhvien_dangnhap);

		char tieptuc_sinhvien;
		if (laSinhVien) {
			do {
				
				Khoitao_baithi(dslop, dslop.data[stt_lop_sinhvien_dangnhap]->malop, dsmonhoc, root_cauhoi, p_sinhvien_dangnhap, First_ketquathi);
				
				//Clear Input buffer
				int ch;
				while ((ch = getchar()) != '\n' && ch != EOF);

				printf("Ban co muon tiep tuc (y: Dong y, ky tu khac: Khong dong y): ");
				tieptuc_sinhvien = getchar();

				//Clear Input buffer
				while ((ch = getchar()) != '\n' && ch != EOF);
			} while (tieptuc_sinhvien == 'y' || tieptuc_sinhvien == 'Y');
		}
		else if (laGiaoVien) {
			Chon_menu_giaovien(dslop, dsmonhoc, First_ketquathi, root_cauhoi);
		}

		printf("Ban co muon tiep tuc chuong trinh (y: Dong y, ky tu khac: Khong dong y): ");
		tieptuc = getchar();

		//Clear buffer reader
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
	} while (tieptuc == 'y' || tieptuc == 'Y');

	return 0;
}
