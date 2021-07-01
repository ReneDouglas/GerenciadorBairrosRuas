#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <stdbool.h>// biblioteca para a funcao do tipo BOOL



typedef struct{

        char nomeRua[50];
        char nomeBairro[30];
        int ID;

        }Estrutura;

struct tlista
{
       char Bairro[30];
       struct tlista *prox;
};

struct tlista *lista=NULL;

int menu();
bool VerificarRua(char nomeRua[],FILE *arqAfo);// Função que retorna um valor booleano, verdadeiro ou falso
void CadastrarRua(FILE *arqAfo);
void Erro(FILE *arqAfo);
void ListarRua(FILE *arqAfo);
void ListarBairro(FILE *arqAfo);
void BuscarRua(FILE *arqAfo);
void ExcluirRua(FILE *arqAfo);
void inserirLista(struct tlista **lista,char bairro[]);
void listar(struct tlista *list);
void cabecalho(const char nome[],int x, int y);
void FullScreen();
void apresentacao();
void creditos();


int main(int argc, char *argv[])
{
  FILE *arq;
  int opcao;

  //FullScreen();

  
  system("color 3F");


    if( (arq = fopen("arquivoAFG.dat", "r+b")) == NULL ){// abre o arquivo binário para leitura

        if( (arq = fopen("arquivoAFG.dat", "w+b")) == NULL ){// cria um arquivo binário para leitura e escrita.

            printf("ERRO NO ARQUIVO !!!");
            exit(1);

        }

    }


  do{

     opcao=menu();


     switch(opcao){


                case 1:
                     {
                       CadastrarRua(arq);
                       break;
                     }
                case 2:
                     {
                       ListarRua(arq);
                       break;
                     }
                case 3:
                     {
                       ListarBairro(arq);
                       break;
                     }      
                case 4:
                     {
                       BuscarRua(arq);
                       break;
                     }
                case 5:
                     {
                       ExcluirRua(arq);
                       break;
                     }
                case 9:
                     {
                       creditos();
                       break;   
                     }
                case 8:
                     {
                       apresentacao();
                       break;
                     }      
                case 6:
                     {
                       opcao=0;
                       gotoxy(25,14);
                       printf("\n\n\t\t\tAGUARDE, FINALIZANDO APLICACAO...");
                       sleep(1500);
                       exit(1);
                       break;

                     }
                default:
                        {
                             gotoxy(25,15);
                             printf("OPCAO INVALIDA!!\n");
                             sleep(1000);
                             main(argc,argv);
                        }
                }

     }while(opcao);



  fclose(arq);// fecha o arquivo

  getch();
  return 0;
}


void apresentacao()
{
     const char nome[20]="INSTRUCOES";
     int x,y;
     system("cls");
     cabecalho(nome,0,0);
     printf("\n\t\tCADASTRO/BUSCA DE RUAS EM AFOGADOS DA INGAZEIRA\n");
     printf("\t\t\tSECRETARIA MUNICIPAL DE SAUDE\n");
     printf("\nPara facilitar a busca e cadastro de ruas:");
     printf("\n");
     printf("\n1 - Nao digite caracteres especiais(Exemplos:  %c  %c  %c  %c  %c  %c)\n",33,39,44,47,46,96);
     printf("\n2 - Nao digite letras com acentos ou cedilha(Exemplos: %c , %c , %c , %c , %c)\n",130,133,135,141,151);
    
     getch();
}



void FullScreen()
{
  // FULL SCREEN 
  keybd_event ( VK_MENU, 0x36, 0, 0 );
  keybd_event ( VK_RETURN, 0x1C, 0, 0 );
  keybd_event ( VK_RETURN, 0x1C, KEYEVENTF_KEYUP, 0 );
  keybd_event ( VK_MENU, 0x38, KEYEVENTF_KEYUP, 0 );
  system("MODE con cols=150 lines=80");// aumenta a tela

}



int menu()
{
    char opcaoMenuAux;
    int opcaoMenu,x=0,y=0;
    const char nome[20]="MENU PRINCIPAL";

    system("cls");// limpar tela

    cabecalho(nome,x,y);
    printf("\n");
    printf("\n\t\t\t[1]  -  CADASTRAR RUA");
    printf("\n\t\t\t[2]  -  LISTAR RUAS POR BAIRRO");
    printf("\n\t\t\t[3]  -  LISTAR BAIRROS");
    printf("\n\t\t\t[4]  -  PESQUISAR RUA");
    printf("\n\t\t\t[5]  -  EXCLUIR RUA ");
    printf("\n\t\t\t[6]  -  SAIR\n");
    printf("\n\t\t\tSELECIONE SUA OPCAO: ");
    gotoxy(55,20);
    printf("[8]  -  INSTRUCOES");
    gotoxy(55,21);
    printf("[9]  -  SOBRE");
    gotoxy(45,12);
    //scanf("\t%d",&opcaoMenu);
    opcaoMenuAux=getch();
    opcaoMenu=atoi(&opcaoMenuAux);// transforma o valor para inteiro

    return opcaoMenu;
}



void CadastrarRua(FILE *arqAfo)
{
     Estrutura *ptrEst,estrutura;
     ptrEst=&estrutura;
     const char nome[20]="CADASTRO DE RUA";
     char Op[50];
     int x=0,y=0; 

     system("cls");
     cabecalho(nome,x,y);
     printf("\n\n\tNOME DA RUA: ");
     strupr(gets(Op));// strupr transforma todos os caracteres da string para maiusculo
     VerificarRua(Op,arqAfo);
     if((VerificarRua(Op,arqAfo)) == false)
     {
             Erro(arqAfo);
     }
     else
     {

          printf("\n\tNOME DO BAIRRO: ");
          strupr(gets(ptrEst->nomeBairro));




               if((ptrEst->nomeBairro[0]) == '\0')
               {
                      Erro(arqAfo);
               }

               else
               {
                    ptrEst->ID=0;
                    strupr(strcpy(ptrEst->nomeRua,Op));
                    fseek(arqAfo, 0, SEEK_END);// direciona o ponteiro para o final do arquivo
                    fwrite(ptrEst,sizeof(Estrutura),1,arqAfo);// salva a rua e o bairro no arquivo
                    printf("\n\n\tCADASTRO FINALIZADO COM SUCESSO!");
                    printf("\n\n\tAGUARDE...");
                    sleep(1000);
                    system("cls");
              }
     }


}

bool VerificarRua(char nomeRua[],FILE *arqAfo)
{
     Estrutura *ptrEst, estrutura;
     ptrEst=&estrutura;
     

     rewind(arqAfo);

     if((nomeRua[0]) == '\0')
     {
                     return false;
     }

     while(fread(ptrEst,sizeof(Estrutura),1,arqAfo)){
                                                     if(!stricmp(ptrEst->nomeRua,nomeRua)&&(ptrEst->ID!=1))
                                                     {
                                                                                          return false;
                                                     }
     }


}

void Erro(FILE *arqAfo)
{
     int Opcao,x=0,y=0;
     const char nome[20]="ERRO";

                         system("cls");
                         cabecalho(nome,x,y);
                         printf("\n\n\tCADASTRO NAO REALIZADO!\n");
                         printf("\n\t1 -- PREENCHA TODOS OS ESPACOS!");
                         printf("\n\t2 -- A RUA JA ESTA CADASTRADA!");
                         printf("\n\n\tPRESSIONE QUALQUER TECLA PARA EFETUAR UM NOVO CADASTRO\n\n");
                         gotoxy(50,20);
                         printf("ESC --> MENU PRINCIPAL\n");
                         Opcao=getch();
                         if(Opcao == 27)
                         {

                               menu();// Retorna para a função menu
                         }
                         else
                         {

                             CadastrarRua(arqAfo);// Retorna para a função CadastrarRua
                         }
}




void ListarRua(FILE *arqAfo)
{
     char OpBairro[30];
     Estrutura *ptrEst, estrutura;
     ptrEst=&estrutura;
     int x=0,y=0;
     const char nome[20]="BAIRROS E RUAS";

     rewind(arqAfo);// posiciona o ponteiro para o começo do arquivo
     system("cls");

     cabecalho(nome,x,y);
     printf("\n\n\tESCOLHA O BAIRRO: ");
     fflush(stdin);
     strupr(gets(OpBairro));
     printf("\n\n");
     cabecalho(OpBairro,7,7);
     printf("\n");
     while(fread(ptrEst,sizeof(Estrutura),1,arqAfo)){// Lê o arquivo até o final

         if(!strcmp(ptrEst->nomeBairro, OpBairro)&&(ptrEst->ID!=1)){
             printf("\n\t%s",ptrEst->nomeRua);
         }
     }

     getch();
}

void ListarBairro(FILE *arqAfo)
{
     
     Estrutura *ptrEst, estrutura;
     ptrEst=&estrutura;
     char OpBairro[30];
     const char nome[20]="BAIRROS CADASTRADOS";
     int x=0,y=0;
     
     rewind(arqAfo);// posiciona o ponteiro para o começo do arquivo
     system("cls");
     
     
     cabecalho(nome,x,y);
     printf("\n");
     while(fread(ptrEst,sizeof(Estrutura),1,arqAfo)){// Lê o arquivo até o final
            
            strcpy(OpBairro,ptrEst->nomeBairro);  
            inserirLista(&lista,OpBairro);
     }
     listar(lista);

     getch();     
}
     
     

void BuscarRua(FILE *arqAfo)
{
     char Op;
     char OpRua[50];
     Estrutura *ptrEst, estrutura;
     ptrEst=&estrutura;
     const char nome[20]="PESQUISAR RUA";
     const char nome2[20]="BAIRRO";
     int verdade=0,i=0,j=0;
     int x=0,y=0;

     rewind(arqAfo);
     system("cls");

     cabecalho(nome,x,y);
     printf("\n");
     printf("\n\tDIGITE O NOME DA RUA: ");
     fflush(stdin);
     strupr(gets(OpRua));
     printf("\n\n");
     cabecalho(nome2,7,7);
     printf("\n");
     while(fread(ptrEst,sizeof(Estrutura),1,arqAfo)){




                    if(!strcmp(ptrEst->nomeRua, OpRua)&&(ptrEst->ID!=1)){

                       printf("\n\n\t%s",ptrEst->nomeBairro);
                       verdade=1;
                       break;


                    }

   }
    if(verdade == 0)
    {
      printf("\n\n\tRUA NAO ENCONTRADA!");
    }


     getch();

}

void inserirLista(struct tlista **list, char bairro[])
{
     struct tlista *temp;
     
     if((*list) == NULL)
     {
                      *list=(struct tlista *)malloc(sizeof(struct tlista));
                      strcpy((*list)->Bairro,bairro);
                      (*list)->prox=NULL;
                      
                      
     }
     else
     {
         struct tlista *temp=(*list),*old;
         while((temp!=NULL)&&(strcmp(temp->Bairro,bairro)))
         {
                                                           old=temp;
                                                           temp=temp->prox;
         }
         if(temp == NULL)
         {
                 temp=(struct tlista *)malloc(sizeof(struct tlista));
                 temp->prox=NULL;
                 old->prox=temp;
                 strcpy(temp->Bairro,bairro);
         }
     }
}

void listar(struct tlista *list)
{
     struct tlista *temp;
     temp=lista;
     if(temp!=NULL)
     {
                   while(temp!=NULL)
                   {     
                                    
                                    printf("\n\t\t\t\t%s",temp->Bairro);
                                    temp=temp->prox;
                   }
     }
     else
     {
         printf("\n\n\tLISTA VAZIA !");
     }
     
}

void ExcluirRua(FILE *arqAfo)
{
     Estrutura *ptrEst, estrutura;
     ptrEst=&estrutura;
     const char nome[20]="EXCLUIR RUA";
     char OpRua[30];
     long posicao=-1;// variável para posicionar o ponteiro 1 byte antes da estrutura
     int verdade;
     int x=0,y=0;
     
     rewind(arqAfo);
     system("cls");

     cabecalho(nome,x,y);
     printf("\n");
     printf("\n\tDIGITE O NOME DA RUA A SER EXCLUIDA:\n\n\t");
     strupr(gets(OpRua));
     fflush(stdin);
     
     while(fread(ptrEst,sizeof(Estrutura),1,arqAfo))
     {
                                                    if(!strcmp(ptrEst->nomeRua,OpRua)&&(ptrEst->ID!=1))
                                                    {
                                                              ptrEst->ID=1; 
                                                              posicao=ftell(arqAfo)-sizeof(Estrutura);                                         
                                                              fseek(arqAfo, posicao, SEEK_SET);
                                                              fwrite(ptrEst,sizeof(Estrutura),1,arqAfo);
                                                              printf("\n\n\n\tRUA EXCLUIDA COM SUCESSO!");
                                                              printf("\n\n\tAGUARDE...");
                                                              sleep(1500);
                                                              verdade=0;
                                                              break;     
                                                    }
                                                    else
                                                    {
                                                        
                                                        verdade=1;
                                                       // break;
                                                    }
                                                                                                 
     }
     if(verdade == 1)
     {
                printf("\n\n\tA RUA NAO EXISTE NO ARQUIVO!!");
                getch();
     }
}

void cabecalho(const char nome[],int x,int y)
{
      
     int i;
     
     
     printf("%c",201);
     for(i=0;i<77;i++)
     {
                      printf("%c",205);
     }
     printf("%c",187);
     
     gotoxy(1,2+y);
     printf("%c",186);
     gotoxy(35,2+y);
     printf("%s",nome);
     gotoxy(79,2+y);
     printf("%c",186);
     printf("\n");
     printf("%c",200);
     
     for(i=0;i<77;i++)
     {
                      printf("%c",205);
     }
     printf("%c",188);
}

void creditos()
{
     const char nome[20]="SOBRE";
     int x,y;
     
     system("cls");
     cabecalho(nome,0,0);
     printf("\n\t\tSISTEMA DE CADASTRAMENTO DE RUAS E BAIRROS");
     printf("\n\n\t\tDESENVOLVIDO POR RENE DOUGLAS NOBRE DE MORAIS");
     printf("\n\n\t\t\t   COMPILADO EM 11/2011");
     
     getch();
     
}
