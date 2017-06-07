#include "Utils.h"

void myStrcpy(char *str1, const char *str2)
{
	int bufsize = sizeof(str1);
	int len = strlen(str2);
	if (len < bufsize)
	{
		strncpy(str1, str2, len);
	}
	else
	{
		strncpy(str1, str2, bufsize);
		str1[bufsize - 1] = 0;
	}

}