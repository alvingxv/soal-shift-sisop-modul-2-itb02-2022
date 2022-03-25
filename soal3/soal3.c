#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

void listFilesRecursively(char *path);
int main()
{
  chdir("/home/kali/modul2/");

  int fork0 = fork();
  int status;

  if (fork0 == 0)
  {
    char *argv[] = {"mkdir","-p","darat",NULL};
    execv("/bin/mkdir", argv);
  }
  else
  {
    while ((wait(&status)) > 0);
    int fork2 = fork();
    if (fork2 == 0)
    {
      sleep(3);
      char *argv[] = {"mkdir", "-p", "air", NULL};
      execv("/bin/mkdir", argv);
    }
    else
    {
      while ((wait(&status)) > 0);
      int fork3 = fork();
      if (fork3 == 0)
      {
        char *argv[] = {"unzip", "animal.zip", NULL};
        execv("/bin/unzip", argv);
      }
      else
      {
        while ((wait(&status)) > 0);
        int fork4 = fork();
        if (fork4 == 0)
        {
          char *argv[] = {"find", "/home/kali/modul2/animal/", "-name", "*darat*", "-exec", "mv", "-t", "/home/kali/modul2/darat/", "{}", "+", NULL};
          execv("/bin/find", argv);
        }
        else
        {
          while ((wait(&status)) > 0);
          int fork5 = fork();
          if (fork5 == 0)
          {
            char *argv[] = {"find", "/home/kali/modul2/animal/", "-name", "*air*", "-exec", "mv", "-t", "/home/kali/modul2/air/", "{}", "+", NULL};
            execv("/bin/find", argv);
          }
          else
          {
            while ((wait(&status)) > 0);
            int fork6 = fork();
            if (fork6 == 0)
            {
              chdir("/home/kali/modul2/animal/");
              char *argv[] = {"find", "-type", "f", "-name", "*", "-delete", NULL};
              execv("/bin/find", argv);
            }
            else
            {
              while ((wait(&status)) > 0);
              int fork7 = fork();
              if (fork7 == 0)
              {
                chdir("/home/kali/modul2/animal/darat");
                char *argv[] = {"find", "-type", "f", "-name", "*bird*", "-delete", NULL};
                execv("/bin/find", argv);
              }
              else
              {
                chdir("/home/kali/modul2/air/");
                char path[100] = "/home/kali/modul2/air";
                listFilesRecursively(path);
              }
            }
          }
        }
      }
    }
  }
}

void listFilesRecursively(char *basePath)
{
  char path[100] = "/home/kali/modul2/air";
  struct stat fs;
  struct stat info;
  struct dirent *dp;
  int r, x;

  DIR *dir = opendir(basePath);
  FILE *fptr = fopen("list.txt", "w");

  if (!dir)
    return;

  while ((dp = readdir(dir)) != NULL)
  {
    if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
    {
      if (strcmp((dp->d_name), "list.txt") == 0)
        continue;
      else
        x = stat(path, &info);
      struct passwd *pw = getpwuid(info.st_uid);
      fprintf(fptr, "%s_", pw->pw_name);
      r = stat(path, &fs);
      if (fs.st_mode & S_IRUSR)
        fprintf(fptr, "r");
      if (fs.st_mode & S_IWUSR)
        fprintf(fptr, "w");

      fprintf(fptr, "_");
      fprintf(fptr, "%s\n", dp->d_name);
      strcpy(path, basePath);
      strcat(path, "/");
      strcat(path, dp->d_name);

      listFilesRecursively(path);
    }
  }

  closedir(dir);
}
