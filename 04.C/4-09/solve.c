// 2026-03-22. It is boring to solve problems that you have to solve on Pascal. SO LETS DO IT. 2.19 but C
// I think <stdio.h> is enough to solve the problem.
#include <stdio.h>

// integers
int c;
int str_count = 0;
int i = 0;
int i_start = 0;
int i_last = 0;
int ch = 0; 
int prev_ch, in_word, current_word_len, first_char, last_char;
int total_words, even_len_words, odd_len_words, long_words, short_words, az_spec_words, max_word_len, min_word_len;
int current_space_series, max_space_series, bracket_balance, balance_broken, empty_brackets_count, az_words;

void zerofication() {
	in_word = 0;
	total_words = 0;
	even_len_words = 0;
	odd_len_words = 0;
	long_words = 0;
	short_words = 0;
	az_spec_words = 0;
	min_word_len = 0;
	max_word_len = 0;
	empty_brackets_count = 0;
	current_space_series = 0;
	max_space_series = 0;
	bracket_balance = 0;
	balance_broken = 0;
	prev_ch = 0;
	first_char = 0;
	last_char = 0;
}

void result_write() {
	printf("=========================\n");
	printf("Current stroke is: %d. Words counted: %d\n", str_count, total_words);
	printf("Odd words lenth: %d, Even : %d\n", odd_len_words, even_len_words);
	printf("Words > 7 chars are %d\nWords <= 2 chars are %d\n", long_words, short_words);
	printf("Words starting, ending with char between A-z are %d\n", az_spec_words);
	printf("Words starting with A and ending with z are %d\n", az_words);
	printf("The longest words has %d chars, The shortest has %d\n", max_word_len, min_word_len);
	printf("Max space series: %d\n", max_space_series);
	
}

void c_len_des () {
	if (current_word_len > 7) long_words++;
	if (current_word_len <= 2) short_words++;
}

void words_len_max_min() {
	if (current_word_len > max_word_len) max_word_len = current_word_len;
	if (min_word_len == 0 || current_word_len < min_word_len) min_word_len = current_word_len;
}

// count is this between A-z or not;
void a_btw_z() {
	if ((first_char >= 'A' && first_char <= 'Z') && (last_char >= 'a' && last_char <= 'z')) az_spec_words++;
}
:void a_z() {
	if (first_char == 'A' && last_char == 'z') az_words++;
}
int main() {
	while((c = getchar()) != EOF) 
	{
		if (c == '\n') {
			if (in_word == 1) {
				total_words++;
				last_char = prev_ch;

				if (current_word_len % 2 == 0) {
					even_len_words++;
				}
				else {
					odd_len_words++;
				}

				c_len_des();
				a_btw_z();
				a_z();
				words_len_max_min();
			}
			in_word = 0;
			str_count++;
			result_write();
			zerofication();
		}

		else if (c == ' ') {
			    current_space_series++;
			    if (current_space_series > max_space_series) max_space_series = current_space_series;
			if (in_word == 1) {
				total_words++;
				last_char = prev_ch;

				if (current_word_len % 2 == 0) {
					even_len_words++;
				}
				else {
					odd_len_words++;
				}

				c_len_des();
				a_btw_z();
				a_z();
				words_len_max_min();
			}
			in_word = 0;
		}

		else {
			if (in_word == 0) {
				first_char = c;
				current_word_len = 0;
				current_space_series = 0;
			}
			//else if(in_word == 1) {
			//}
			in_word = 1;
			current_word_len++;
		}
		// it is last operations
		prev_ch = c;
		i++;
	}
	return 0;
}

