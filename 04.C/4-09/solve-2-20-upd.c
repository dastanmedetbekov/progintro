#include <stdio.h>
// 2026-03-24
// 2-20. Pascal task on C
int prev_ch = 0;
int c;
int balance = 0;
int i = 0;

int in_word;

void pc(int ch) {
	putchar(ch);
}

int main() {
	while ((c = getchar()) != EOF)
	{
		if ((prev_ch == '\n' || prev_ch == ' ' || prev_ch == 0) && c != ' ' && c != '\n')
		{
    			pc('(');    // открываем только один раз — в начале слова
    			pc(c);
    			in_word = 1;
		}
		else if (in_word == 1 && c != ' ' && c != '\n')
		{
			pc(c);      // середина слова — просто символ
		}
		else if (prev_ch != ' ' && (c == ' ' || c == '\n'))
		{
			pc(')');    // закрываем в конце слова
	    		pc(c);
    			in_word = 0;
		}
	}
	if (prev_ch != ' ' && prev_ch != '\n') pc(')');
	printf("Balance: %d\n", balance);
	return 0;
}
