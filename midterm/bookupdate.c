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

int main(int argc, char *argv[]) {

	int fd, id, state;
	char c;
	struct bookDB book;

	if(argc < 2) {
		fprintf(stderr, "How to use: %s file\n", argv[0]);
		exit(1);
	}

	if((fd = open(argv[1], O_RDWR)) == -1) {
		perror(argv[1]);
		exit(2);
	}

	printf("--bookupdate--\n");
	printf("0 bookID: borrow book, 1 bookID: return book ) ");
	if(scanf("%d %d", &state, &id) == 2) {
		if(state == 0) {
			lseek(fd, (long)(id-START_ID)*sizeof(book), SEEK_SET);
			if((read(fd, (char *) &book, sizeof(book)) > 0) && (book.id != 0) && (book.borrow == "False")) {
				&book.numofborrow += 1;
				book.borrow = "True";
				lseek(fd, (long)-sizeof(book), SEEK_CUR);
				write(fd, (char *) &book, sizeof(book);
				printf("You've got below book..\n");
				printf("%s\t %s\t %s\t %s\t %s\t %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
				printf("%d\t %s\t %s\t %d\t %d\t %s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
			}
			else {
				printf("You cannot borrow below book since it has been booked.\n");
				printf("%s\t %s\t %s\t %s\t %s\t %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
				printf("%d\t %s\t %s\t %d\t %d\t %s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
			}
		}
		else if(state = 1) {
			lseek(fd, (long)(id-START_ID)*sizeof(book), SEEK_SET);
			if((read(fd, (char *) &book, sizeof(book)) > 0) && (book.id != 0) && (book.borrow == "True")) {
				book.borrow = "False"
				lseek(fd, (long)-sizeof(book), SEEK_CUR);
				write(fd, (char *)&book, sizeof(book);
				printf("You'vd returned bellow book..");
				printf("%s\t %s\t %s\t %s\t %s\t %s\n", "id", "bookname", "author", "year", "numofborrow", "borrow");
				printf("%d\t %s\t %s\t %d\t %d\t %s\n", book.id, book.bookname, book.author, book.year, book.numofborrow, book.borrow);
			}
		}
	} else printf("Input Error\n");

	close(fd);
	exit(0);
}
