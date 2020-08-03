#pragma once

struct diemthi
{
	char mamh[15];
	float diem;
};

struct nodediemthi
{
	diemthi dt;
	struct nodediemthi* next;
};

typedef nodediemthi* PTR_diemthi;

void Initialize_diemthi(PTR_diemthi& First)
{
	First = NULL;
}

void Insert_First_diemthi(PTR_diemthi& First, diemthi dt)
{
	PTR_diemthi p = new nodediemthi;
	p->dt = dt;
	p->next = First;
	First = p;
}

PTR_diemthi Search_diemthi_mamh(PTR_diemthi First, char mamh[15]) {
	PTR_diemthi p;
	for (p = First; p != NULL; p = p->next) {
		if (strcmp(p->dt.mamh, mamh) == 0) break;
	}
	return p;
}