#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        fprintf(stderr, "usage: %s [input file] [output file]\n", argv[0]);
        return 1;
    }
    FILE *fp_in = fopen(argv[1], "r");
    FILE *fp_out = fopen(argv[2], "w");
    clock_t before = clock();
    while(1)
    {
        int c = fgetc(fp_in);
        if (c == EOF)
            break;
        fputc(c, fp_out);
    }
    clock_t after = clock();
    fclose(fp_in);
    fclose(fp_out);
    clock_t duration = after - before;
    int s = duration / CLOCKS_PER_SEC;
    int ms = (duration % CLOCKS_PER_SEC) * 1000 / CLOCKS_PER_SEC;
    fprintf(stderr, "Copy took %ds%dms\n", s, ms);
    return 0;
}
