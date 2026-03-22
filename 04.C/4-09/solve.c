// 2026-03-22. It is boring to solve problems that you have to solve on Pascal. SO LETS DO IT. 2.19 but C
// I think <stdio.h> is enough to solve the problem.
#include <stdio.h>

// integers
int c;
int ch = 0; 
int prev_ch, in_word, current_word_len, first_char, last_char;
int total_words, even_len_words, odd_len_words, long_words, short_words, az_spec_words, max_word_len, min_word_len;
int current_space_series, max_space_series, bracket_balance, balance_broken, empty_brackets_count;

int main() {
	while((c = getchar()) != EOF) 
	{
		if (c != ' ') {
			in_word = 1;
		}

		if (c == ' ' && prev_ch != ' ')
		{
			in_word = 0;
			ch++;
		}
		printf("result is %d\n", ch);
		prev_ch = c;
	}
	return 0;
}

