//	Backup Programm	//
// interrupt the realtime backup with strg+C
// use it only with text files like .txt or something like that...not for .odt files...or Microsoft open office
// compile: gcc backup.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
int main (int argc, char *argv[])
{	///
int fh;
char bufread[2048];
char filename[512];
char backupfile[512];
int i=0;

	if (argc == 1) {
	perror("\n\n-FATAL----------\n-Type in the filename you want to backup\n\n");
	exit(0); }

strcpy(filename,argv[1]);

// dauerschleife
int c=0;
while (1){
	c++;
	system("clear");

	if ( (fh=open(filename,O_RDONLY)) == -1) {
		perror("\n-FATAL------------\n-This file don´t exist\n\n-DEBUG-\n-Fail to Read the file\n\n");
		return EXIT_FAILURE;
	}

	if ( (read(fh,&bufread,sizeof(bufread))) == -1) {
		perror(NULL);
		return EXIT_FAILURE;
	}
	close(fh);

//	open or create the backup file
// 	check ob es den ordner schon gibt...oder erstelle ihn
	struct stat st = {0};
	if (stat("/root/.Backup", &st) == -1) {
	    mkdir("/root/.Backup", 0700);
	}
	snprintf(backupfile,sizeof(backupfile), "/root/.Backup/%s.backup",filename);


	if ( (fh=open(backupfile,O_RDWR|O_CREAT|O_TRUNC)) == -1) {
	perror("\n\n-FATAL--------------\n-Fehler beim öffnen der datei in funktion Backup open\n ");
	return EXIT_FAILURE;
	}

	if ( (write(fh,bufread,strlen(bufread))) == -1) {
	perror("\n\n-FATAL-----------\n-Fehler beim schreiben in die datei\n");
	return EXIT_FAILURE;
	}

	close(fh);
                printf("\n your file is %s \n",filename);
                printf("\n\n - - DEBUG - - %d backup\n\n",c);
//	check ob backup existiert
        if(fh=open(backupfile,O_RDONLY) == -1 ){
                perror("\n\n - - FATAL - - - - - \n - Backup nicht erstellt\n\n");
                return EXIT_FAILURE; }
		close(fh);

printf("\n\n\n-FINISH----------\n\n-backup file was createt\n-Name        = %s\n",backupfile);

	sleep(1);
}	//end while schleife

}	/// main end

