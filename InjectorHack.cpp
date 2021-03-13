/*
Criador Por CoRingaModz
Telegram @CoRingaModzYT

*/



#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <thread>



int handle;
typedef char TEKASHI;
long int get_module_base(int pid, const char *module_name)
{
	FILE *fp;
	long addr = 0;
	char *pch;
	char filename[32];
	char line[1024];
	snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
	fp = fopen(filename, "r");
	if (fp != NULL)
	{
		while (fgets(line, sizeof(line), fp))
		{
			if (strstr(line, module_name))
			{
				pch = strtok(line, "-");
				addr = strtoul(pch, NULL, 16);
				break;
			}
		}
		fclose(fp);
	}
	return addr;
}
int INJECTOR_FLOAT(long int addr, float value)//Valores Alteravel Com Manual
{
	pwrite64(handle, &value, 4, addr);
	return 0;
}
int INJECTOR_DWORD(long int addr, int value)//Valores Sem Alteração Manual
{
	pwrite64(handle, &value, 4, addr);
	return 0;
}
int getPID(TEKASHI * PackageName)
{
	DIR *dir = NULL;
	struct dirent *ptr = NULL;
	FILE *fp = NULL;
	char filepath[256];
	char filetext[128];
	dir = opendir("/proc");
	if (NULL != dir)
	{
		while ((ptr = readdir(dir)) != NULL)
		{

			if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
				continue;
			if (ptr->d_type != DT_DIR)
				continue;
			sprintf(filepath, "/proc/%s/cmdline", ptr->d_name);
			fp = fopen(filepath, "r");
			if (NULL != fp)
			{
				fgets(filetext, sizeof(filetext), fp);
				if (strcmp(filetext, PackageName) == 0)
				{

					break;
				}
				fclose(fp);
			}
		}
	}
	if (readdir(dir) == NULL)
	{
		return 0;
	}
	closedir(dir);
	return atoi(ptr->d_name);
}

int rebootsystem() {
	return system("su -c 'reboot'");
}


int main(int argc, char **argv)
{
	int gs;
    void *jg;
	FILE *fp;
	char ch, wjm[51];
	if (!(fp = fopen("/storage/emulated/0/dump/", "r")))

	{
		rebootsystem();//Reniciar Celular si Roubarem Seu Code
	}
	int ipid = getPID("com.dts.freefireth");
	if (ipid == 0)
	{
	puts("Aplikasi tidak berjalan!");
	exit(1);
	}
	char TekashiCMods[64];
	sprintf(TekashiCMods, "/proc/%d/mem", ipid);
	handle = open(lj, O_RDWR);
	if (handle == -1)
	{
		puts("carregando Memoria Ops!\n");
		exit(1);
	}
	char mname[] = "libil2cpp.so";
	long int libbase = get_module_base(ipid, mname);
	INJECTOR_FLOAT(libbase + 0xaddress, 50);
	INJECTOR_DWORD(libbase + 0xE0CF0, 50);//Exemple // Boneco Branco
	INJECTOR_FLOAT(libbase + 0xaddress, 50);
	INJECTOR_FLOAT(libbase + 0xaddress, 50);
	close(handle);
	return 0;
}
