/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    FILE* inptr = fopen("card.raw", "r");
    char outfilename[8];
    unsigned char buffer[512];
    int count = 0;
    int flag = 0;
    FILE* outptr = NULL;

    while(fread(buffer, 512, 1, inptr))
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            if(outptr != NULL)
            fclose(outptr);
            sprintf(outfilename,"%.3d.jpg", count++);
            outptr = fopen(outfilename, "w");
            flag = 1;
        }    
        if(flag == 1)
        fwrite(buffer, 512, 1, outptr);
    }
    fclose(inptr);
    return 0;
}
