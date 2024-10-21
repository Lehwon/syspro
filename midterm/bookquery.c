#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

struct bookDB {
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numofborrow;
	char borrow[5];
};

int main(int argc, char argv[]) {

	int fd;
	int select
	char c;

	struct bookDB book;

	if(argc < 2) {
		fprintf(stderr, "How to use: %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDONLY)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("--bookquery--\n");
	printf("0: list of all books, 1: list of available books ) ");
	if(scanf("%d", &select) == 1) {
		printf("%s\t %s\t %s\t %d\t %s\t %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
		if(select == 0) {
			lseek(fd, 0L, SEEK_SET);
			while((read(fd, (char *) &book, sizeof(book)) > 0))
			printf("%d\t %s\t %s\t %d\t %d\t %s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
		}
		else if(select == 1) {
			lseek(fd, 0L, SEEK_SET);
			while((read(fd, (char *) &book, sizeof(book)) > 0 && book.borrow == "True")
				printf("%d\t %s\t %s\t %d\t %d\t %s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
		}
		else printf("Input Error\n");
	} else printf("Input Error\n");

	close(fd);
	return 0;
}			
