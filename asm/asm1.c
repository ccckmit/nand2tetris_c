#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *h2b[] = {
  "0000", "0001", "0010", "0011",
  "0100", "0101", "0110", "0111", 
  "1000", "1001", "1010", "1011",
  "1100", "1101", "1110", "1111"};

void hex2binary(char *hex, char *binary) {
  for (int i=0; hex[i] != '\0'; i++) {
    char h = hex[i] - '0';
    if (h > 10) h = hex[i] - 'A' + 10;
    sprintf(&binary[4*i], "%s", h2b[h]);
  }
}

void decimal2binary(int d, char *binary) {
  char hex[100];
  sprintf(hex, "%04x", d);
  hex2binary(hex, binary);  
}

char *codes[]={
"@2",
"D=A",
"@3",
"D=D+A",
"@0",
"M=D"
};

int codesLen = 6, dTableSize = 8;

char *dTable[]  = { "",    "M",   "D",   "MD",  "A",   "AM",  "AD",  "AMD"};
char *dBinary[] = { "000", "001", "010", "011", "100", "101", "110", "111"};

int find(char *item, char *array[], int len) {
    for (int i=0; i<len; i++) {
        if (strcmp(array[i], item)==0)
            return i;
    }
    return -1;
}

char *lookup(char *item, char *name[], char *value[], int len) {
   int i = find(item, name, len);
   if (i==-1) return NULL;
   return value[i];
}

void code2binary(char *code, char *binary) {
    if (code[0]=='@') {
      // A 指令： ＠number
      int number;
      sscanf(code, "@%d", &number);
//      printf("d=%d\n", d);
      decimal2binary(number, binary);  
    } else {
      // C 指令： d = exp
      // sprintf(binary, "error");
      char d[10], exp[100];
      sscanf(code, "%[^=]=%s", d, exp);
      printf("  d=%s exp=%s\n", d, exp);
      char *dcode = lookup(d, dTable, dBinary, dTableSize);
      printf("  dcode=%s", dcode);
    }
}

int main() {
  char hex[5];
  char binary[17];
/*  
  printf("%x\n", 10);
  printf("%x\n", 100);
  sprintf(hex, "%04x", 33);
  printf("%s\n", hex);
  hex2binary(hex, binary);
  printf("%s\n", binary);
  decimal2binary(33, binary);
  printf("binary(33)=%s\n", binary);
*/  
  for (int i=0;i<codesLen;i++) {
    printf("%s\n", codes[i]);
    code2binary(codes[i], binary);
    printf("=> %s\n", binary);
  }
}

/*
@2
D=A
@3
D=D+A
@0
M=D
*/

