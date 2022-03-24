#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <json-c/json.h>
#include <syslog.h>

const char *getweapons()
{
    DIR *d = opendir("/home/alvin/Sistem_Operasi/Modul2/rundisini/weapons");
    int i = 0;
    char *arrayWeapon[131];
    struct dirent *dir;
    dir = readdir(d);

    while (dir != NULL)
    {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        {
        }
        else
        {
            arrayWeapon[i] = (char *)malloc(strlen(dir->d_name) + 1);
            strcpy(arrayWeapon[i], dir->d_name);
            i++;
        }
        dir = readdir(d);
    }

    closedir(d);

    srand(time(0));
    int lower = 0, upper = (130 - 1);
    int random = rand() % (upper - lower + 1) + lower;

    return arrayWeapon[random];
}

const char *getcharacter()
{
    DIR *d = opendir("/home/alvin/Sistem_Operasi/Modul2/rundisini/characters");
    int i = 0;
    char *arrayCharacter[48];
    struct dirent *dir;
    dir = readdir(d);

    while (dir != NULL)
    {
        if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, ".."))
        {
        }
        else
        {
            arrayCharacter[i] = (char *)malloc(strlen(dir->d_name) + 1);
            strcpy(arrayCharacter[i], dir->d_name);
            i++;
        }
        dir = readdir(d);
    }

    closedir(d);

    srand(time(0));
    int lower = 0, upper = (48 - 1);
    int random = rand() % (upper - lower + 1) + lower;

    return arrayCharacter[random];
}

void createFolder(int f)
{
    int status = 0;
    if (fork() == 0)
    {
        char buffer[256];
        snprintf(buffer, sizeof buffer, "./gacha_gacha/total_gacha_%d", f + 90);
        char *argv[] = {"mkdir", buffer, NULL};
        execv("/bin/mkdir", argv);
    }
    while (wait(&status) > 0)
        ;
}

int main()
{
    pid_t pid, sid; // Variabel untuk menyimpan PID
    int status;
    pid = fork(); // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
     * (nilai variabel pid < 0) */
    if (pid < 0)
    {
        exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
     * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0)
    {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0)
    {
        exit(EXIT_FAILURE);
    }

    if ((chdir("/home/alvin/Sistem_Operasi/Modul2/rundisini")) < 0)
    {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    time_t currenttime = time(NULL);
    int limit = 1;
    while (1)
    {
        currenttime = time(NULL);
        if (currenttime >= 1648590284 && limit == 1)
        {
            limit++;
            pid_t child_pid1, child_pid2;

            child_pid1 = fork();

            if (child_pid1 && child_pid2 < 0)
            {
                exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
            }
            if (child_pid1 == 0)
            {
                pid_t childfrom1, childfrom1_2;
                (childfrom1 = fork()) && (childfrom1_2 = fork());
                if (childfrom1 == 0)
                {
                    char *argv[][6] = {
                        {"wget", "-q", "https://drive.google.com/u/0/uc?id=1xYYmsslb-9s8-4BDvosym7R4EmPi6BHp&export=download", "-O", "characters.zip", NULL},
                        {"wget", "-q", "https://drive.google.com/u/0/uc?id=1XSkAqqjkNmzZ0AdIZQt_eWGOZ0eJyNlT&export=download", "-O", "weapons.zip", NULL}};
                    printf("Sedang download database..");
                    for (int x = 0; x < 2; x++)
                    {
                        if (fork() == 0)
                            continue;
                        sleep(10);
                        execv("/bin/wget", argv[x]);
                    }
                }
                else if (childfrom1_2 == 0)
                {
                    char *argv[] = {"mkdir", "gacha_gacha", NULL};
                    execv("/bin/mkdir", argv);
                }
                else
                {
                    while ((wait(&status)) > 0)
                        ;
                    pid_t inichild3;
                    inichild3 = fork();
                    if (inichild3 == 0)
                    {
                        char *argv[][5] = {
                            {"unzip", "-q", "characters.zip", NULL},
                            {"unzip", "-q", "weapons.zip", NULL}};
                        printf("\nSedang unzip..\n");
                        for (int x = 0; x < 2; x++)
                        {
                            if (fork() == 0)
                                continue;
                            sleep(10);
                            execv("/bin/unzip", argv[x]);
                        }
                    }
                    else
                    {
                        while ((wait(&status)) > 0)
                            ;
                        char *argv[][6] = {
                            {"rm", "characters.zip", NULL},
                            {"rm", "weapons.zip", NULL}};
                        for (int x = 0; x < 2; x++)
                        {
                            if (fork() == 0)
                                continue;
                            execv("/bin/rm", argv[x]);
                        }
                    }
                }
            }
            else
            {
                while ((wait(&status)) > 0)
                    ;
                sleep(3);
                int i = 0, f= -90, primogems =79000;
                char *jam;
                char waktu[20];
                int persepuluh = 0;

                FILE *fp;
                char buffer[4096];
                struct json_object *parsed_json;
                struct json_object *rarity;
                struct json_object *name;

                FILE *fp2;
                char buffer2[4096];
                struct json_object *parsed_json2;
                struct json_object *rarity2;
                struct json_object *name2;
                while (primogems > 0)
                {
                    if (i % 2 == 0) // genap
                    {
                        if (i % 90 == 0)
                        {

                            f = f + 90;
                            createFolder(f);
                            if (i % 10 == 0)
                            {
                                time_t rawtime;
                                struct tm *timeinfo;
                                time(&rawtime);
                                timeinfo = localtime(&rawtime);
                                sprintf(waktu, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
                                jam = waktu;
                                persepuluh = persepuluh + 10;
                            }
                        }
                        else if (i % 10 == 0)
                        {
                            time_t rawtime;
                            struct tm *timeinfo;
                            time(&rawtime);
                            timeinfo = localtime(&rawtime);
                            sprintf(waktu, "%d:%d:%d", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
                            jam = waktu;
                            persepuluh = persepuluh + 10;
                        }
                        const char *weapon = getweapons();
                        char namafile[256];
                        snprintf(namafile, sizeof namafile, "./weapons/%s", weapon);
                        fp = fopen(namafile, "r");
                        fread(buffer, 4096, 1, fp);
                        fclose(fp);
                        parsed_json = json_tokener_parse(buffer);
                        json_object_object_get_ex(parsed_json, "name", &name);
                        json_object_object_get_ex(parsed_json, "rarity", &rarity);

                        FILE *d = NULL;
                        char filePath[500];
                        snprintf(filePath, sizeof filePath, "./gacha_gacha/total_gacha_%d/%s_gacha_%d.txt", f + 90, jam, persepuluh - 10);
                        d = fopen(filePath, "a");
                        fprintf(d, "%d_weapons_%d_%s_%d\n", i, json_object_get_int(rarity), json_object_get_string(name), primogems);
                        fclose(d);
                    }
                    else if (i % 2 == 1)
                    {
                        const char *character = getcharacter();
                        char namafile2[256];
                        snprintf(namafile2, sizeof namafile2, "./characters/%s", character);
                        fp2 = fopen(namafile2, "r");
                        fread(buffer2, 4096, 1, fp2);
                        fclose(fp2);
                        parsed_json2 = json_tokener_parse(buffer2);
                        json_object_object_get_ex(parsed_json2, "name", &name2);
                        json_object_object_get_ex(parsed_json2, "rarity", &rarity2);

                        FILE *d = NULL;
                        char filePath[500];
                        snprintf(filePath, sizeof filePath, "./gacha_gacha/total_gacha_%d/%s_gacha_%d.txt", f + 90, jam, persepuluh - 10);
                        d = fopen(filePath, "a");
                        fprintf(d, "%d_character_%d_%s_%d\n", i, json_object_get_int(rarity2), json_object_get_string(name2), primogems);
                        fclose(d);
                    }
                    i++;
                    primogems = primogems - 160;
                    sleep(1);
                }
            }
        }
        else if (currenttime >= 1648601084)
        {
            // kode setelah jam d-day
            pid_t childsetelahjam;
            childsetelahjam = fork();
            if (childsetelahjam == 0)
            {
                char *zipAkhir[] = {"zip", "-r", "-P", "satuduatiga", "not_safe_for_wibu.zip", "gacha_gacha", NULL};
                execv("/bin/zip", zipAkhir);
            }
            else
            {
                while ((wait(&status)) > 0)
                    ;
                char *hapus[] = {"rm", "-v", "!(*.zip)", NULL};
                execv("/bin/rm", hapus);
                exit(1);
            }

            sleep(30);
        }
    }
    return 0;
}