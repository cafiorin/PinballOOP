#include "Utils.h"

void myStrcpy(char *str1, const char *str2)
{
	int bufsize = sizeof(str1);
	int len = (int) strlen(str2);
	if (len < bufsize)
	{
		strcpy(str1, str2);
	}
	else
	{
		strncpy(str1, str2, bufsize);
		str1[bufsize - 1] = 0;
	}

}