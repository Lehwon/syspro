#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]){
	char **ptr;
	char *s_ptr;
	extern char **environ;
	switch(argv[1][1]){
		case 'e':
		//if -e ==> print all value
		if(argc == 2) {
			for(ptr = environ; *ptr != 0; ptr++){
				printf("%s \n", *ptr); 
			}
		}
		//if -e "*" ==> print only * value
		else if(argc == 3){
			s_ptr = getenv(argv[2]);
			printf("%s \n", s_ptr);
		}
			break;
		case 'u':
			printf("My Realistic User ID : %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
			printf("My Valid User ID : %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
			break;
		case 'g':
			printf("My Realistic Group ID : %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
			printf("My Valid Group ID : %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
			break;
		case 'i':
			printf("My process number : [%d]\n", getpid());
			break;
		case 'p':
			printf("My parent's process number : [%d]\n", getppid());
			break;
			}
	exit(0);
}
