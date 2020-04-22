#include "../h/global.h"
int my_atoi(const char* const& str)
{
	if (strlen(str) == 0)
		return -1;
	int ans = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] < '0' || str[i]>'9')
			return -1;
		else
		{
			ans *= 10;
			ans += str[i] - '0';
		}
	}
	return ans;
}
double my_atof(const char* const& str)
{
	bool point = false;
	int i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '.')
		return -1;
	for (; i < strlen(str); i++)
	{
		if (str[i] <= '9' && str[i] >= '0')
			continue;
		if (str[i] == '.')
		{
			if (!point)
			{
				point = true;
				continue;
			}
			else
			{
				return -1;
			}
		}
		else
		{
			return -1;
		}
	}
	return atof(str);
}