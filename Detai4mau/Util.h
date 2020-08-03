#pragma once
#include <stdio.h>
void ClearInputBuffer(void) {
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}