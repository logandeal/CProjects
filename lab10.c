// Logan Deal ledvk2 CS1050 Lab 10

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define CLEARTEXT \
"It's Christmastime in Washington\a\nThe Democrats rehearsed \b\n"\
"Gettin' into gear for four more years\nThings not gettin' worse"\
"\"\\\?\n\n\t\t- Steve Earle"

void EncryptDecrypt(char *in, int displacement)
{
    char *cPtr = in;

    while(*cPtr != '\0')
    {
        if(*cPtr != ' ' && *cPtr != '\n' && *cPtr != '\t' && *cPtr != '\a' && *cPtr != '\b')
        {
            *cPtr = *cPtr + displacement;
        }
        cPtr++;
    }
    *cPtr = '\0';
    printf("%s",in);
}

void AdvEncrypt(char *in, char *passphrase)
{
    char *cPtr = in;
    int pIndex = 0;

    while(*cPtr != '\0')
    {
        if(*cPtr != ' ' && *cPtr != '\n' && *cPtr != '\t' && *cPtr != '\a' && *cPtr != '\b')
        {
            unsigned c = *cPtr + (passphrase[pIndex] % 10) + 1; 
            if(c > 127)
            {
                c = c - 127 + 33;
            }

            *cPtr = c;
            pIndex++;

            if(passphrase[pIndex] == '\0')
            {
                pIndex = 0;
            }
        }
        cPtr++;
    }
    *cPtr = '\0';
    printf("%s",in);
}

void AdvDecrypt(char *in, char *passphrase)
{
    char *cPtr = in;
    int pIndex = 0;

    while(*cPtr != '\0')
    {
        if(*cPtr != ' ' && *cPtr != '\n' && *cPtr != '\t' && *cPtr != '\a' && *cPtr != '\b')
        {
            unsigned c = *cPtr - (passphrase[pIndex] % 10) - 1; 
            if(c < 33)
            {
                c = c + 127 - 33;
            }

            *cPtr = c;
            pIndex++;

            if(passphrase[pIndex] == '\0')
            {
                pIndex = 0;
            }
        }
        cPtr++;
    }
    *cPtr = '\0';
    printf("%s",in);
}

int main(void)
{
    char s[256] = {CLEARTEXT};
    char passphrase[256];
    char passenter[256];
    char passlater[256];

    printf("**** Original ****\n");
    printf("%s",s);

    printf("\n\n**** Encrypted ****\n");
    EncryptDecrypt(s,4);

    printf("\n\n**** Unencrpyted ****\n");
    EncryptDecrypt(s,-4);
    printf("\n");

    printf("\n\n**** Adv Encrypted ****\n");
    printf("Enter passphrase: ");
    scanf("%s",passphrase);
    strcpy(passlater,passphrase);
    AdvEncrypt(s,passphrase);
    printf("\n");

    printf("\n\n**** Adv Unencrypted ****\n");
    printf("Enter passphrase to decrypt: ");
    for(int i=1;i<=5;i++)
    {
        scanf("%s",passenter);
        int same = strcmp(passenter,passlater);
        if(same == 0)
        {
            AdvDecrypt(s,passenter);
            break;
        }
        else
        {
            printf("Incorrect passphrase.\n");
            if(i==5)
            {
                break;
            }
            printf("Enter passphrase to decrypt: ");
        }
    }
    printf("\n");
}
