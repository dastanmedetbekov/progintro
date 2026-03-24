#include <stdio.h>
// 2026-03-24
// 2-20. Pascal task on C
int prev_ch = 0;
int c;
int balance = 0;
int i = 0;

void pc(int ch) {
	putchar(ch);
}

int main() {
	while ((c = getchar()) != EOF) {
		if (c == '\n') i = 0;
    		if (prev_ch == 0 && c != '\n' && c != ' ') {
			pc('(');
			++balance;
			pc(c);
		}
		else if(prev_ch == ' ' && c != ' ') {
			pc('(');
			++balance;
			pc(c);
		}
		else if(prev_ch == '\n' && c != '\n' && c != ' ') {
			pc('(');
			++balance;
			pc(c);
		}
		else if(prev_ch == '\n' && c == '\n') {
			pc(c);
		}
		else if(prev_ch != ' ' && c == ' ' && prev_ch != '\n') {
			pc(')');
			--balance;
			pc(c);
		}
		else if(prev_ch != ' ' && c == '\n' && prev_ch != '\n') {
			pc(')');
			--balance;
			pc(c);
		}
		else if(prev_ch == '\n' && c != ' ' && i != 0) {
			pc(')');
			--balance;
			pc(c);
		}
		else {
			pc(c);
		}
		prev_ch = c;
		++i;
	}
	printf("Balance: %d, Loop worked: %d\n", balance, i);
	
	return 0;
}
