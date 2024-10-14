#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

char type(mode_t);
char *perm(mode_t);
void printStat(char*, char*, struct stat*, int);
void printFileNames(char *, int, struct stat*);

int main(int argc, char **argv) {

	DIR *dp;
	char *dir;
	struct stat st;
	struct dirent *d;
	char path[BUFSIZ + 1];
	int option = 0; //0: al, 1: -i, 2: -p, 3: -Q

	if(argv[1][0] == '-') {
		switch(argv[1][1]) {
			case 'i': option = 1; break;
			case 'p': option = 2; break;
			case 'Q': option = 3; break;
		}
	}
		

	if(argc == 1)
		dir = ".";
	else dir = argv[1];

	if((dp = opendir(dir)) == NULL)
		perror(dir);

	while((d = readdir(dp)) != NULL) {
		sprintf(path, "%s/%s", dir, d->d_name);
		if(lstat(path, &st) < 0)
			perror(path);
		else
			printStat(path, d->d_name, &st, option);

	}
	closedir(dp);
	exit(0);
}

void printStat(char *pathname, char *file, struct stat *st, int option) {
	
	printf("%5ld ", st->st_blocks);
	if(option == 1) printf("%10lu ", st->st_ino);
	printf("%c%s ", type(st->st_mode), perm(st->st_mode));
	printf("%3ld ", st->st_nlink);
	printf("%s %s ", getpwuid(st->st_uid)->pw_name, getgrgid(st->st_gid)->gr_name);
	printf("%9ld ", st->st_size);
	printf("%.12s ", ctime(&st->st_mtime)+4);
	printFileNames(file, option, st);
}

void printFileNames(char *file, int option, struct stat *st) {
	if(option == 2) { //-p
		printf("\"%s\"", file);
	} else {
		printf("%s", file);
	}
	if(type(st->st_mode) == 'd' && option == 3) { //-Q
		printf("/");
	}
	printf("\n");
}

char type(mode_t mode) {
	if(S_ISREG(mode))
		return('-');
	if(S_ISDIR(mode))
		return('d');
	if(S_ISCHR(mode))
		return('c');
	if(S_ISBLK(mode))
		return('b');
	if(S_ISLNK(mode))
		return('l');
	if(S_ISFIFO(mode))
		return('p');
	if(S_ISSOCK(mode))
		return('s');
}

char *perm(mode_t mode) {
	static char perms[10];
	strcpy(perms, "--------");

	for(int i = 0; i < 3; i++) {
		if(mode & (S_IRUSR >> i*3))
			perms[i*3] = 'r';
		if(mode & (S_IWUSR >> i*3))
			perms[i*3+1] = 'w';
		if(mode & (S_IXUSR >> i*3))
			perms[i*3+2] = 'x';
	}
	return(perms);
}
