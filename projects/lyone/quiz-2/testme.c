#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
	static char *set = "[({ ax})]";	//The set of characters from which a random character is drawn
	static int len = 9;
	int i = rand() % len; 
	return set[i];
}

char *inputString()
{
	static char *set = "erst";		//The set of characters from which a random string is generated
	int len = strlen(set);

	char *string = (char *)calloc(6, sizeof(char));
	int i, j;
	for(i = 0; i < 5; ++i)
	{
		j = rand() % len;
		string[i] = set[j];
	}
	return string;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
	printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
	  free(s);
      exit(200);
    }
	free(s);
  }
}


int main(int argc, char *argv[])
{
	srand(time(NULL));
    testme();
    return 0;
}
