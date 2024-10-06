#include <stdio.h>
#include <string.h>
#include "copy.h"
#define REPEAT 5

char line[REPEAT][MAXLINE];

void sortLine(int len[]) {
	char temp[MAXLINE];
	int tempLen;

	for(int i = 0; i < REPEAT - 1; i++) {
		for(int j = 0; j < REPEAT - i - 1; j++) {
			if(len[j] < len[j+1]){
			strcpy(temp, line[j]);
			strcpy(line[j], line[j+1]);
			strcpy(line[j+1], temp);

			tempLen = len[j];
			len[j] = len[j+1];
			len[j+1] = tempLen;
			}
		}
	}
}


int main(void){
  int len[REPEAT];
  int i = 0;

  for(i = 0; i < REPEAT; i++) {
	  fgets(line[i], MAXLINE, stdin);
	  line[i][strcspn(line[i], "\n")] = '\0';
  }
  
  for(i = 0; i < REPEAT; i++)
	  len[i] = strlen(line[i]);

  sortLine(len);

  for(i = 0; i < REPEAT; i++)
    printf("%s \n", line[i]);

  return 0;
}
