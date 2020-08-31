#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/time.h>
#define compile_script "compile.sh"

struct File
{
	char filename[100];
	time_t mod_time;
}file,logs[10];

DIR *fd;
FILE *fd2;

char compile_file[100]="\0";
char open_compile[100]="\0";

void fill_log()
{
	for(int i=0;i<=10;i++)
		strcpy(logs[i].filename,"null\0");

}

void compile()
{
	system(compile_file);
}
void check_file()
{
	struct stat st;
	int exists = 0;
	struct timespec time;

	for(int i=0;i<10;i++)
	{
	
		if(strcmp(logs[i].filename,"null\0")!=0)
		{
			stat(logs[i].filename,&st);
			time = st.st_mtim;

			if(logs[i].mod_time < time.tv_sec)
			{
				printf("[+]compile!\n");
				logs[i].mod_time = time.tv_sec;
				compile();
			}
		}
	}
}
void open_directory()
{
	char directory[100]="\0";
	getcwd(directory,96);
	strcat(directory,"/\0");
	
	if((fd = opendir(directory))==NULL)
	{
		perror("opendir():");
		exit(EXIT_FAILURE);
	}
	
}

void open_file()
{
	if((fd2=fopen(open_compile,"r"))==NULL)
	{
		perror("fopen:");
		exit(EXIT_FAILURE);
	}
}

void check_directory(char *keyword)
{

	struct stat st;
	struct timespec time;
	struct dirent *directory;

	while((directory=readdir(fd))!=NULL)
	{
		
		if(strcmp(directory->d_name,keyword)==0)
		{
			printf("[+]file exists in directory\n");
	
			/*assume we are re-initiating*/
			stat(keyword,&st);
			time = st.st_mtim;

			for(int i=0;i<10;i++)
			{
				if(strcmp(logs[i].filename,"null")==0)
				{
					printf("[+]empty slot found\n");
					strcpy(logs[i].filename,keyword);
					logs[i].mod_time = time.tv_sec;
					break;
				}
			}
			break;
			
		}		
	}

	rewinddir(fd);
}


void read_compile_script()
{
	
	char buf[100]="\0";

	size_t counter;size_t pos;
	counter = pos = 0;
	char word[50]="\0"; char key[50]="\0";
	int source_file=0;
	while(fgets(buf,sizeof(buf),fd2))
	{
		
		for(size_t i=0;i<strlen(buf);i++)
		{
		
			if(buf[i]==' ')
			{
				while(pos<i)
				{
					word[counter]=buf[pos];pos++;counter++;
				}pos=i+1;
			
				if(word[counter-2]=='.' && word[counter-1]=='c')
				{
					printf("word = %s\n",word);
					check_directory(word);
					memset(word,0,50);
				}				
				counter=0;
			}
		}
	}
	rewind(fd2);
}


/*init function run at start, and if user does ./bot -u <compile_script>*/
void init()
{
	fill_log();
	open_file();
	open_directory();

	read_compile_script();

}

int main(int argc,char **argv)
{
	int arguments = 0;
	if(argc>1)
		arguments = 1;

	if(arguments==1)
	{
		if(strcmp(argv[1],"-k")==0)
		{
			system("pkill bot");
		}
		else
		{
			strcpy(compile_file,"./");
			strcat(compile_file,argv[1]);
			strcpy(open_compile,argv[1]);

			init();
			daemon(1,0);
			while(1)
			{
				check_file();
				sleep(3);
			}
		}
	}
		
	
	return 0;
}
