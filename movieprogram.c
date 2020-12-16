#include <stdio.h>
#include <string.h>

#define SCOREFILE "moviescores.md"

int main(int argc, char *argv[])
{
    FILE *fPtr;

    if(argc < 3 || strcmp(argv[1],SCOREFILE) != 0)
    {
        printf("Syntax error or can't find file.");
        return 1;
    }
    else
    {
        fPtr = fopen(SCOREFILE, "r");
    }

    if (fPtr == NULL)
    {
        printf("Could not open file\n");
    }
    else
    {
        while(!feof(fPtr))
        {
            char name[256];
            int score1;
            int score2;

            if(fscanf(fPtr,"%[^:]: %d,%d\n",name,&score1,&score2) != 3)
            {
                break;
            }
        
            if(strcmp(argv[2],name) == 0)
            {
                printf("%s\nRotten Tomatoes Score: %d\nMetacritic Score: %d\n",name,score1,score2);
            }
        }
    }
    fclose(fPtr);
}
