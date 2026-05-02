#include <stdio.h>

#if !defined(TASK)
#error Please define which task you wanna run!
#error 40-41-42-43-44
#error only usable for TASK
#endif

#define PRINT(x) printf("CURRENT TASK IS %s \n", #x);

#if TASK==40

int main() {
    PRINT(40)
}

#elif TASK==41

int main() {
    PRINT(41)
    printf("%d\n", __LINE__);
}
#elif TASK==42

int main() {
    PRINT(42)
}
#elif TASK==43

int main() {
    PRINT(43)
}
#elif TASK==44

int main() {
    PRINT(44)
}

#else
#error I DONT KNOW! use -DTASK=40 or through 44
#endif
