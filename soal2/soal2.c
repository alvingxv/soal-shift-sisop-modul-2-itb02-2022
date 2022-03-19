#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <wait.h>
#include <string.h>
#include <dirent.h>

void copy(char *src, char *dest) {
	int status;
	pid_t child_id = fork();
	if (child_id == 0) {
		char *argv[] = {"cp", "-n", src, dest, NULL};
		execv("/usr/bin/cp", argv);
	} else {
		((wait(&status)) > 0);
	}
}

void delFile(char *file) {
	int status;
	pid_t child_id = fork();
	if (child_id == 0) {
		char *argv[] = {"rm", "-d", file, NULL};
		execv("/usr/bin/rm", argv);
	} else {
		((wait(&status)) > 0);
	}
}

void createFolder(char *dest) {
	int status;
	pid_t child_id = fork();
	if (child_id == 0) {
		char *argv[] = {"mkdir", "-p", dest, NULL};
		execv("/usr/bin/mkdir", argv);
	} else {
		((wait(&status)) > 0);
	}
}

void unzip() {
	int status;
	pid_t child_id = fork();
	if (child_id == 0) {
		char *argv[] = {"unzip", "-j", "drakor.zip", "*.png", "-d", "/home/rachmita/shift2/drakor", NULL};
		execv("/usr/bin/unzip", argv);
	} else {
		((wait(&status)) > 0);
	}
}

void fileRekursif(char *basePath) {
	char path[1000];
	struct dirent *dp;
	DIR *dir = opendir(basePath);

	if (!dir)
		return;

	while ((dp = readdir(dir)) != NULL) {
		if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0){
			char tempFol[100];
			char mkFol[100] = "/home/rachmita/shift2/drakor/";
			char drakor1[100] = "/home/rachmita/shift2/drakor/";
			char drakor2[1000] = "/home/rachmita/shift2/drakor/";
			char drakor3[1000] = "/home/rachmita/shift2/drakor/";
			char temp[1000], temp2[1000], temp3[1000], temp4[1000], getJudul[1000], getTahun[1000], getKate[1000], getFol[100], getJudul2[100], getTahun2[1000], getKate2[1000], getFol2[100], getJudul3[100], getTahun3[1000], getKate3[1000], getFol3[100];
			char *token, *token2, *token3;

			char listFile[100] = "/home/rachmita/shift2/drakor/";
			strcat(listFile, dp->d_name);

			//mendapatkan informasi 1 gambar 1 poster
			if (!(strstr(dp->d_name, "_"))) {
				strcpy(temp, dp->d_name); //school2021;2021;school.png
				token = strtok(temp, ";"); //school2021
				strcpy(getJudul, token);
				token = strtok(NULL, ";"); //2021
				strcpy(getTahun, token);
				token = strtok(NULL, ";"); //school.png
				strcpy(getKate, token);
				token = strtok(getKate, ".");//school
				strcpy(getFol, token);
				strcat(drakor1, getFol);
				strcat(drakor1, "/");
				strcat(drakor1, getJudul);
				strcat(drakor1, ".png");
			}
			
			//mendapatkan informasi 1 gambar 2 poster
			if (strstr(dp->d_name, "_")) {
				strcpy(temp3, dp->d_name); //start-up;2020;romance_thek2;2016;action.png
				token3 = strtok(temp3, ";"); //start-up
				strcpy(getJudul2, token3);
				token3 = strtok(NULL, ";"); //2020
				strcpy(getTahun2, token3);
				token3 = strtok(NULL, ";"); //romance_thek2;2016;action.png
				strcpy(getKate2, token3);
				token3 = strtok(getKate2, "_");//romance
				strcpy(getFol2, token3);
				strcat(drakor2, getFol2);
				strcat(drakor2, "/");
				strcat(drakor2, getJudul2);
				strcat(drakor2, ".png");
				
				strcpy(temp2, dp->d_name); //start-up;2020;romance_thek2;2016;action.png
				token2 = strtok(temp2, "_"); //start-up;2020;romance
				token2 = strtok(NULL, "_");	 //thek2;2016;action.png
				strcpy(temp4, token2);
				token2 = strtok(temp4, ";"); //thek2
				strcpy(getJudul3, token2);
				token2 = strtok(NULL, ";"); //2016
				strcpy(getTahun3, token2);
				token2 = strtok(NULL, ";"); //action.png
				strcpy(getKate3, token2);
				token2 = strtok(getKate3, ".");//action
				strcpy(getFol3, token2);
				strcat(drakor3, getFol3);
				strcat(drakor3, "/");
				strcat(drakor3, getJudul3);
				strcat(drakor3, ".png");
			}
            //membuat dir dengan kategori drama
			strcpy(tempFol, getFol);
			strcat(mkFol, tempFol);
			createFolder(mkFol);

			//copy gambar ke dir
			copy(listFile, drakor1);
			copy(listFile, drakor2);
			copy(listFile, drakor3);

			//membuat data.txt berisi nama dan tahun rilis
			FILE *data;
			char fname[100];
			strcpy(fname, mkFol);
			strcat(fname, "/data.txt");
			data = fopen(fname, "a+");
			if (!(strstr(dp->d_name, "_"))) {
				fprintf(data, "nama : %s\n", getJudul);
				fprintf(data, "tahun rilis : %s\n\n", getTahun);
			}

			fclose(data);

			delFile(listFile);

			strcpy(path, basePath);
			strcat(path, "/");
			strcat(path, dp->d_name);

			fileRekursif(path);
		}
	}

	closedir(dir);
}

int main() {
	
	createFolder("/home/rachmita/shift2/drakor/");
	unzip();

	fileRekursif("/home/rachmita/shift2/drakor/");
	delFile("/home/rachmita/shift2/drakor/data.txt");

	return 0;
}