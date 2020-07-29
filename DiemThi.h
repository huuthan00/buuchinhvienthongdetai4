#pragma once

struct DiemThi
{
	char MaMH[15];
	float Diem;
};

struct NodeDiemThi
{
	DiemThi dt;
	struct NodeDiemThi* next;
};

typedef NodeDiemThi* PTR_DiemThi;

void Initialize_DiemThi(PTR_DiemThi& First)
{
	First = NULL;
}

void Insert_First_DiemThi(PTR_DiemThi& First, DiemThi dt)
{
	PTR_DiemThi p = new NodeDiemThi;
	p->dt = dt;
	p->next = First;
	First = p;
}

PTR_DiemThi Search_DiemThi_MaMH(PTR_DiemThi First, char MaMH[15]) {
	PTR_DiemThi p;
	for (p = First; p != NULL; p = p->next) {
		if (strcmp(p->dt.MaMH, MaMH) == 0) break;
	}
	return p;
}