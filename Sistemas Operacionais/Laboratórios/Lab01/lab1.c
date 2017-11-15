#include <unistd.h>
#include <fcntl.h>

#define CHMOD 0700
#define MAX 256

int main(void)
{
	char arquivo1[MAX];
	char arquivo2[MAX];
	char byte;
	int n;

	//Ler o nome do arquivo para copia
	write(STDOUT_FILENO, "Input file:", 11);
	int num_read1 = read(0, arquivo1, MAX);
	arquivo1[num_read1 - 1] = '\0';
	write(STDOUT_FILENO, "\n", 1);

	//Ler o nome do arquivo de saida
	write(STDOUT_FILENO, "Output file:", 12);
	int num_read2 = read(0, arquivo2, MAX);
	arquivo2[num_read2 - 1] = '\0';
	write(STDOUT_FILENO, "\n", 1);	

	int fileReader = open(arquivo1, O_RDONLY);
	if(fileReader < 0){
		write(STDOUT_FILENO,"Error 1: Não abriu o arquivo para leitura",8);
		_exit(1);
	}

	int creatFile = open(arquivo2, O_WRONLY|O_CREAT|O_TRUNC, CHMOD);
	if(creatFile < 0){
		write(STDOUT_FILENO,"Error 2: Não abriu ou criou o arquivo para escrita",8);
		_exit(2);
	}

	while((n = read(fileReader, &byte, 1)) > 0){
		write(creatFile, &byte, 1);
	}
	close(creatFile);
	close(fileReader);

	write(STDOUT_FILENO, "Copy Sucess\n", 12);

	return 0;
}