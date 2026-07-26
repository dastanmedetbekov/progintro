a) int arr[245][12] → int (*p)[12];

b) double arr[100][10][2] → double (*p)[10][2];

c) char arr[5][5] → char (*p)[5];

d) char *arr[5][5] → char *(*p)[5];

e) struct item *arr[20][3] → struct item *(*p)[3];

f) struct item *arr[20] → struct item **p;
