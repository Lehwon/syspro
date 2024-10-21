#include <stdio.h>

struct bookDB {
	int id;
	char bookname[10];
	char author[10];
	int year;
	int numofborrow;
	char borrow[5];
};

int main(int argc, char *argv[]) {
	struct bookDB book;
	int fd;

	if(argc < 2) {
		fprintf(stderr, "How to use: %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_WRONLY|O_CREATE|O_EXCL, 0640)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("%s\t %s\t %s\t %s\t %s\t %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
	while(scanf("%d %s %s %d %d %s", &book.id, book.bookname, book.author, &book.year, &book.numofborrow, book.borrow) == 6) {
		lseek(fd, (book.id - START_ID) * sizeof(book(, SEEK_SET);
		write(fd, (char *) &book, sizeof(book));
	}

	close(fd);
	exit(0);
}
