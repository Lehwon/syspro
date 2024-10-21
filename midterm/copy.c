#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[]) {

	char c;
	FILE *fp1, *fp2;
	if (argc != 4) {
		fprintf(stderr, "How to use: %s 0 File1 File2\n", argv[0]);
		return 1;
	}

	fp1 = fopen(argv[2], "r");
	if(fp1 == NULL) {
		fprintf(stderr, "File %s Open Error\n", argv[2]);
		return 2;
	}

	fp2 = fopen(argv[3], "w");

	int cases = (int)argv[1];

	switch(cases) {
		case 0: //original data copy
			while((c = fgetc(fp1)) != EOF)
				fputc(c, fp2);
				break;

		case 1: //to lower
			while((c = fgetc(fp1)) != EOF)
				c = tolower(c);
				fputc(c, fp2);
				break;
		case 2://to upper
			while((c = fgetc(fp2)) != EOF)
				c = toupper(c);
				fputc(c, fp2);
				break;
	}

	fclose(fp1);
	fclose(fp2);

	return0;
}
