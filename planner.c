#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
struct evento{
  char nome[48];
  int mes;
  int dia;
  int horas;
  int minutos;
};
char file_name[] = {"mainfile.dat"};
void criarEvento(){
  FILE *fp;
  struct evento new;
  fp = fopen(file_name, "ab");
  printf("\nDigite o nome que voce deseja inserir no seu evento: ");
  gets(new.nome);
  printf("Agora, digite o dia e o mes que voce deseja marcar seu evento\n");
  printf("Dia: ");
  scanf("%d", &new.dia);
  printf("Mes: ");
  scanf("%d", &new.mes);
  printf("Por fim, digite o horario de inicio dessa tarefa\n");
  printf("Horas: ");
  scanf("%d", &new.horas);
  printf("Minutos: "); 
  scanf("%d", &new.minutos); 
  fwrite(&new, sizeof(new), 1, fp);
  printf("Evento %s criado com sucesso para o dia %d/%d!!!\n", new.nome, new.dia, new.mes);
  fclose(fp);
  system("pause");
}
void alterarEvento(void){
  FILE *fp, *fp1;
  struct evento display, new;
  fp = fopen(file_name, "rb");
  fp1 = fopen("sub.dat", "wb");
  int d, m, count=0;
  char nome[48];
  printf("**********************************************\n\n");
  printf("Digite a data do evento que voce deseja alterar:\n");
  printf("Dia: ");
  while(1){
    fread(&display, sizeof(display), 1, fp);
    if(feof(fp)){
      break;
    }
    if(display.dia==d && display.mes==m && strcmp(nome, display.nome)==0){
      count=1;
      printf("\n\n%s\t", display.nome);
      printf("%d/%d\t", display.dia, display.mes);
      printf("%dh:%dmin\n\n", display.horas, display.minutos);
      printf("Digite o novo nome do evento: ");
      gets(display.nome);
      printf("Digite a nova data do evento:\n");
      printf("Dia: ");
      fflush(stdin);
      scanf("%d", &display.dia);
      printf("Mes: ");
      scanf("%d", &display.mes);
      printf("Por fim, digite o novo horario:\n");
      printf("Horas: ");
      scanf("%d", &display.horas);
      printf("Minutos: ");
      scanf("%d", &display.minutos);
      fwrite(&display, sizeof(display), 1, fp1);  
    }
    else{
      fwrite(&display, sizeof(display), 1, fp1);  
    }
  }
  fclose(fp);
  fclose(fp1);
  if(count==0){
    printf("\nNao ha evento disponivel\n\n");
  }
  else{
    fp = fopen(file_name, "wb");
    fp1 = fopen("sub.dat", "rb");
    while(1){
      fread(&display, sizeof(display), 1, fp1);
      if(feof(fp1)){
        break;
      }
      fwrite(&display, sizeof(display), 1, fp);
    }
  }
  fclose(fp);
  fclose(fp1);
  system("pause");
}

void mostrarData(void){
  FILE *fp;
  int d, m, count=0;
  struct evento display;
  fp = fopen(file_name, "rb");
  printf("**********************************************\n\n");
  printf("Digite a data que voce deseja visualizar seus eventos\n");
  printf("Dia: ");
  scanf("%d", &d);
  printf("Mes: "); 
  scanf("%d", &m);
  printf("**********************************************\n\n");
  printf("Nome do evento\tData\tHorario");
  while (1){
    fread(&display, sizeof(display), 1, fp);
    if(feof(fp)){
      break;
    }
    if (d==display.dia && m==display.mes){
      count++;
      printf("\n\n%s\t", display.nome);
      printf("%d/%d\t", display.dia, display.mes);
      printf("%dh:%dmin\n\n", display.horas, display.minutos);    
    }
  }
  if(count==0){
    printf("Nao ha eventos disponiveis nessa data\n\n");
  }
  fclose(fp);
  system("pause");
}

void mostrarTudo(void){
  FILE *fp;
  struct evento display;
  fp = fopen(file_name, "rb");
  printf("\t\tTodos os eventos\n\n");
  printf("**********************************************\n\n");
  printf("Nome do evento\tData\tHorario\n\n");
  while (1){
    fread(&display, sizeof(display), 1, fp);
    if(feof(fp)){
      break;
    }
    printf("%s\t", display.nome);
    printf("%d/%d\t", display.dia, display.mes);
    printf("%dh:%dmin\n\n", display.horas, display.minutos);
  }
  fclose(fp);
  system("pause");
}

void deletarTudo(){
  int n;
  FILE *fp, *fp1;
  struct evento display;
  char name[20];
  char yn[1];
  printf("**********************************************\n\n");
  printf("Deseja fazer um backup de seus eventos? (y/n): ");
  scanf("%s", &yn);
  if(strcmp(yn, "y")==0){
    printf("Digite o novo nome do arquivo.dat: ");
    fflush(stdin);
    gets(name);
    fp = fopen(name, "wb");
    fp1 = fopen(file_name, "rb");
    while(1){
      fread(&display, sizeof(display), 1, fp1);
      if(feof(fp)){
        break;
      }
      fwrite(&display, sizeof(display), 1, fp);
    }
    fclose(fp);
    fclose(fp1);
    remove(file_name);
    strcpy(file_name, name);
  }
  else{
    remove(file_name);
  }
  system("pause");
} 

void main(){
  int escolha;
  while (1){
    system("cls");
    printf("\nBem vindo ao Planner MINERVA!\n\n");
    printf("=======Escolha sua tarefa=======\n\n");
    printf("[1] Novo evento\n\n");
    printf("[2] Alterar evento ja existente\n\n");
    printf("[3] Exibir todos os eventos existentes\n\n");
    printf("[4] Consultar eventos pela data\n\n");
    printf("[5] Deletar todos os eventos\n\n");
    printf("[0] Sair do programa\n\n");
    printf("**********************************************\n\n");
    printf("Digite o numero correspondente: ");
    scanf("%d", &escolha);
    printf("\n\n");
    getchar();
    switch(escolha){
      case 1: criarEvento();
      break;
      
      case 2: alterarEvento();
      break;

      case 3: mostrarTudo();
      break;
      
      case 4: mostrarData();
      break;

      case 5: deletarTudo();
      break; 

      case 0: exit(0);
      break;
    }
  }
}