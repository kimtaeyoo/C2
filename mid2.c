#include <stdio.h>

#define IN 1 // inside a word
#define OUT 0 // outside a word

// count line, word, and characters in input
int main(void)
{
        // nl: line count, wc: word count, nc: character count
        int c, nl, nw, nc, state;

        state = OUT;
        nl = nw = nc = 0;
        while((c = getchar()) != EOF){
                ++nc;
                if (c == '\n')
                        ++nl;
                if (c == ' ' || c == '\n' || c == '\t')
                        state = OUT;
                else if (state == OUT) {
                        state = IN;
                        ++nw;
                }
        }
        printf("%7d %7d %7d\n", nl, nw, nc);
}
