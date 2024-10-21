#include <stdio.h>
#include <stdlin.h>
#include <unistd.h>
#include <fcntl.h>

struct bookDB {
	int id;
	char bookname[10];
	char author[10];
	int yaer;
	int numofborrow;
	char borrow[5];
};

int main(int argc, char *argv[]) {

	int fd, id;
	int year;
	
	if(argc < 2) {
		fprintf(stderr, "How to use %s file\n", argv[0]);
		exit(1);
	}
	
	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("--bookquery--\n");
}
