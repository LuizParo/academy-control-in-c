/*
PROGRAMA DE SIMULAÇÃO DE CADASTRO DE ALUNOS EM UMA ACADEMIA

AUTORES:
        - CHRISTIAN JARDIM LOYOLA
        - GIOVANI FERNANDES
        - LUIZ GUILHERME PARO
        - PAULO DENADAI

OBJETIVO: Esse programa foi desenvolvido pelo grupo como requisito obrigatório do
          Projeto Integrado 2012 (Primeiro Semestre), para a empresa Academia
          Power Mad.
        
DESCRIÇÃO: Esse programa tem como objetivo simular o cadastro de alunos em uma 
           academia fazendo a manipulação de arquivo (cadastro, visualização, 
           ateração, exclusão, ordenação), seu BANCO DE DADOS é constituído de um
           arquivo binário e nele são jogados todas as informações.
           Cada cadastro é constituído de um código único, feito de forma auto-
           incremental (+1), sempre que um cadastro é excluído, seu código não 
           pode ser reaproveitado. A ordenação tem como objetivo fazer com que 
           todos os cadastros sejam exibidos de forma crescente, ja que a cada
           alteração o código em questão é jogado no final do arquivo.
           
LICENÇA: Esse codigo-fonte pode ser distribuído, desde que o nome dos autores 
         sejam mantidos e eventuais alterações sejam autorizadas pelos mesmos.
*/
//==============================================================================
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <ctype.h> // Para usar o comando toupper

int retorno=0; // variaveis globais;
FILE * arquivo; // Ponteiro para o arquivo principal;
FILE * arquivo_aux; // Ponteiro para o arquivo auxiliar;

//=== STRUCT CADASTRO ==========================================================
struct cadastro
{
   int codigo;
   char nome[50];
   char sexo;
   char datanasc[12];
   char end[100];
   char cidade[30];
   char estado[10];
   char cep[9];
   char rg[10];
   char cpf[12];
   char servico[100];
   float valor;
}c, c2, c3[100], c4[100];

//== ATENÇÃO ===================================================================
/* Todas as funções de validação tem rotinas de recuperação de tela, isso é feito
através dos parametros "int funcao", quando a função de validação é chamada pelo
case 1 (inserção) ela entra na comparação "if(funcao==1)", quando é pelo case 3
(alteração) ela entra na outra comparação "if(funcao==3)". Essa rotina foi criada 
para que sempre que o usuário digite o CPF/CEP/Sexo errado, ele exiba a mensagem
de erro, mas não apague da tela os dados que já foram digitados anteriormente,e 
também não fique acrescentando linhas de erro caso a inserção seja novamente 
feita errada. Ambas as funções (inserção/alteração) tem suas respectivas recuperação
de tela, para saber em qual delas entrar as funçoes tem variáveis chamadas
"controle_func", que entram no parametro "int funcao" comentado acima, caso seja
inserção ela tem o valor de 1 e entra na primeira comparação "if(funcao==1)", caso
seja alteração ela tem o valor de 3 e entra na segunda comparação "if(funcao==3)"; */

//=== FUNCAO VALIDA CPF ========================================================

/* Validação espelhada no site http://www.pb.utfpr.edu.br/omero/C/Exercicios/B/B8.Htm,
para maiores informações consulte a referência bibliográfica do trabalho. */
int valida_cpf(FILE *arquivo, int funcao)  
{    
   int icpf[11];  
   int i,somador=0,digito1,result1,result2,digito2,valor,valid=0;
   
   do
   {
      printf("CPF (Somente Numeros)............: ");
      gets(c.cpf);  
     
      //Efetua a conversao de array de char para um array de int.  
      for(i=0;i<11;i++)  
      icpf[i]=c.cpf[i]-48;
      
      //PRIMEIRO DIGITO.  
      for(i=0;i<9;i++)   
      somador+=icpf[i]*(10-i);     
      result1=somador%11;  
           
      if( (result1==0) || (result1==1) )  
      digito1=0;  
      
      else  
      digito1 = 11-result1;  
      
      //SEGUNDO DIGITO.  
      somador=0;  
      for(i=0;i<10;i++)  
      somador+=icpf[i]*(11-i);   
      valor=(somador/11)*11;  
      result2=somador-valor; 
         
      if( (result2==0) || (result2==1) )  
      digito2=0;
      
      else  
      digito2=11-result2;  
      
      //RESULTADOS DA VALIDACAO.    
      if((digito1==icpf[9]) && (digito2==icpf[10]))  
      valid++; 
       
      else  
      {
         /* As funcoes abaixo tem como objetivo recuperar a tela de
         cadastro/alteração caso o CPF seja inserido errado; */
         if(funcao==1) // Funcao insere_cad(); (case 1)
         {
            printf("\nCPF INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
          
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n   --->|| INSERIR NOVO CADASTRO ||<---");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG (Somente Numeros).............: %s\n", c.rg);
         }//if(funcao==1)
          
         if(funcao==3) // Funcao altera_cad(); (case 3)
         {
            printf("\nCPF INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
             
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n       -->|| EDITAR CADASTRO ||<--");
            printf("\n\nATENCAO! As alteracoes serao salvas somente se o usuario confirmar a acao!");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG...............................: %s", c.rg);
            printf("\nCPF..............................: %s", c.cpf);
            printf("\nAtividade........................: %s", c.servico);
            printf("\nMensalidade......................: R$ %4.2f", c.valor);
      
            printf("\n\nQual campo deseja alterar? ");
            printf("\n\n1-> Nome;");
            printf("\n2-> Sexo;");
            printf("\n3-> Data de Nascimento;");
            printf("\n4-> Endereco;");
            printf("\n5-> Cidade;");
            printf("\n6-> Estado;");
            printf("\n7-> CEP:");
            printf("\n8-> RG;");
            printf("\n9-> CPF;");
            printf("\n10-> Atividade;");
            printf("\n11-> Mensalidade;");
            printf("\n12-> Salvar alteracoes;");
            printf("\n0-> Voltar ao Menu Principal;");
            printf("\n\nEscolha uma das opcoes acima: \n\n\n");
         }//if(funcao==2)
      }
      somador=0;
      digito1=0;
      result1=0;
      result2=0;
      digito2=0;
      valor=0;
    }while(valid==0);
}

//=== FUNCAO VALIDA CEP ========================================================
int valida_cep(FILE * arquivo, int funcao)
{
   int cont=0;
   
   do
   {
      printf("CEP (Somente Numeros)............: ");
      gets(c.cep);
      cont=strlen(c.cep);
      
      if(cont!=8)
      {
         /* As funcoes abaixo tem como objetivo recuperar a tela de 
         cadastro/alteração caso o CEP seja inserido errado; */
         if(funcao==1) // Funcao insere_cad(); (case 1)
         {
            printf("\nCEP INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
            
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n   --->|| INSERIR NOVO CADASTRO ||<---");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s\n", c.estado);
         }
         
         if(funcao==3) // Funcao altera_cad(); (case 3)
         {
            printf("\nCEP INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
             
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n       -->|| EDITAR CADASTRO ||<--");
            printf("\n\nATENCAO! As alteracoes serao salvas somente se o usuario confirmar a acao!");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG...............................: %s", c.rg);
            printf("\nCPF..............................: %s", c.cpf);
            printf("\nAtividade........................: %s", c.servico);
            printf("\nMensalidade......................: R$ %4.2f", c.valor);
      
            printf("\n\nQual campo deseja alterar? ");
            printf("\n\n1-> Nome;");
            printf("\n2-> Sexo;");
            printf("\n3-> Data de Nascimento;");
            printf("\n4-> Endereco;");
            printf("\n5-> Cidade;");
            printf("\n6-> Estado;");
            printf("\n7-> CEP:");
            printf("\n8-> RG;");
            printf("\n9-> CPF;");
            printf("\n10-> Atividade;");
            printf("\n11-> Mensalidade;");
            printf("\n12-> Salvar alteracoes;");
            printf("\n0-> Voltar ao Menu Principal;");
            printf("\n\nEscolha uma das opcoes acima: \n\n\n");
         }
      }
   } while(cont!=8);
}

//=== FUNCAO VALIDA SEXO =======================================================
int valida_sexo(FILE * arquivo, int funcao)
{
   do
   {
      printf("Sexo (M/F).......................: ");
      c.sexo=getche();
      c.sexo=toupper(c.sexo); /*Função para passar os caracteres da variavel 
      "c.sexo" para maiuscula */
      
      if(((c.sexo!='m')&&(c.sexo!='M')) && ((c.sexo!='f')&&(c.sexo!='F')))
      {
         /* As funcoes abaixo tem como objetivo recuperar a tela de 
         cadastro/alteração caso o SEXO seja inserido errado; */
         if(funcao==1) // Funcao insere_cad(); (case 1)
         {
            printf("\n\nSEXO INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
            
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n   --->|| INSERIR NOVO CADASTRO ||<---");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s\n", c.nome);
         }
         
         if(funcao==3) // Funcao altera_cad(); (case 3)
         {
            printf("\n\nSEXO INVALIDO! Digite novamente.\n");
            getch();
            system("cls");
             
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n       -->|| EDITAR CADASTRO ||<--");
            printf("\n\nATENCAO! As alteracoes serao salvas somente se o usuario confirmar a acao!");
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG...............................: %s", c.rg);
            printf("\nCPF..............................: %s", c.cpf);
            printf("\nAtividade........................: %s", c.servico);
            printf("\nMensalidade......................: R$ %4.2f", c.valor);
      
            printf("\n\nQual campo deseja alterar? ");
            printf("\n\n1-> Nome;");
            printf("\n2-> Sexo;");
            printf("\n3-> Data de Nascimento;");
            printf("\n4-> Endereco;");
            printf("\n5-> Cidade;");
            printf("\n6-> Estado;");
            printf("\n7-> CEP:");
            printf("\n8-> RG;");
            printf("\n9-> CPF;");
            printf("\n10-> Atividade;");
            printf("\n11-> Mensalidade;");
            printf("\n12-> Salvar alteracoes;");
            printf("\n0-> Voltar ao Menu Principal;");
            printf("\n\nEscolha uma das opcoes acima: \n\n\n");
         }
      }
   } while(((c.sexo!='m')&&(c.sexo!='M')) && ((c.sexo!='f')&&(c.sexo!='F')));
}

//=== FUNCAO INSERIR CADASTRO ==================================================
void insere_cad()
{
   char op,resp;
   int controle_func=1, cod=1, i=0, vez=1;
   /*controle_func é uma variavel de controle para caso o cpf/cep/sexo seja inserido
   errado, a tela de cadastro seja recuperada; */
   
   do
   {
      arquivo=fopen("academia.txt","a+b");
      
      /* Rotina de leitura para que a variavel cod seja carregada e na inserção o 
      codigo sempre corresponda ao subsequente ao anterior gravado; */
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      while(retorno==1)
      {
         /* Vez garante que essa rotina seja lida somente 1 vez cada sempre que a 
         função de inserção é chamada; */
         if(vez==1)
         {
            cod=c.codigo; // Cod recebe o primeiro valor de c.cod registrado no arquivo;
            vez++; /* Vez passa a valer 2 e o laço não poderá mais ser lido até a próxima
            vez que a função insere_cad seja chamada*/
         }
      
         /* Caso o código subsequente seja maior que o primeiro lido acima, a variável
         cod recebe o código com maior valor gravado no arquivo; */
         if(c.codigo>cod)
         cod=c.codigo;

         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      }
      
      
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n   --->|| INSERIR NOVO CADASTRO ||<---");
         
      /* Garante que a variável cod receba +1, garantindo que ela seja sempre superior
      ao ultimo cod carregado na rotina acima, rotina lida somente 1 vez a cada chamada; */
      if(vez==2)
      {
         cod++;
         vez++;
      }
         
      printf("\n\nCodigo...........................: %d",cod);
      c.codigo = cod; //c.codigo recebe o valor de cod, que é acrescentado a cada inserção;
      printf("\nNome.............................: ");
      gets(c.nome);
      valida_sexo(arquivo, controle_func); //Chama a função valida_sexo;
      printf("\nData de Nascimento (DD/MM/AAAA)..: ");
      gets(c.datanasc);
      printf("Endereco.........................: ");
      gets(c.end);  
      printf("Cidade...........................: ");
      gets(c.cidade);
      printf("Estado...........................: ");
      gets(c.estado);
      valida_cep(arquivo, controle_func); //Chama a função valida_cep;
      printf("RG (Somente Numeros).............: ");
      gets(c.rg);
      valida_cpf(arquivo, controle_func); //Chama a função valida_cpf;
      printf("Atividade........................: ");
      gets(c.servico);
      printf("Mensalidade......................: R$ ");
      scanf("%f",&c.valor);
      fflush(stdin);
        
      /*Rotina criada somente para passar os caracteres da variavel "c.estado" 
      para maiuscula atraves do comando toupper; */
      for(i=0;i<10;i++)
      c.estado[i]=toupper(c.estado[i]);
      
      /*Confirma se o cadastro vai ser gravado ou não no arquivo, caso não seja,
      o codigo não incrementa +1; */
      printf("\nConfirmar Cadastro (S/N): ");
      resp=getche();
      
      if((resp!='n')&&(resp!='N'))
      {
         /* A variavel retorno vai receber o valor inteiro de 1 caso a gravação
         ocorra com sucesso; */
         retorno=fwrite (&c, sizeof(struct cadastro) ,1,arquivo);
         if(retorno==1) 
         {
            printf(" \n\n---|| Cadastro efetuado com sucesso!!! ||--- \n");
            cod++;
         }
         
         /* Caso haja alguma falha, ele retornara um valor diferente de
         1, identificando que houve alguma falha na gravação; */
         else 
         printf (" \n\n---|| Problemas: Cadastro nao efetuado!!! ||---" );
      } //if((resp!='n')&&(resp!='N'))
      
      //Caso o usuario escolha nao salvar, a mensagem abaixo aparece;
      else
      printf("\n\n---|| Cancelando cadastro!!! ||---\n");
      
      /* Pergunta feita ao usuario se ele deseja continuar, enquanto ele não 
      digitar n/N a rotina de inserção não acabará; */
      printf("\nDeseja continuar (S/N): ");
      op = getche();
      fclose(arquivo);
      system("cls");
   }while((op!='n') && (op!='N'));
   cod=1;
   system ("cls");  
}

//=== FUNCAO ALTERAR CADASTRO ==================================================
char altera_cad(char cpf[12])
{
   int op_alt=0, i=0, controle=0, controle_func=3;
   char op;
   /* Variável controle serve para verificar se o CPF digitado foi encontrado na
   struct, caso tenha sido, ele recebe 1, caso contrário ele continua 0, assim 
   caso o CPF não seja encontrado, uma mensagem aparece avisando o usuário; */
   
   /* controle_func é uma variavel de controle para caso o cpf/cep/sexo seja 
   inserido errado, a tela de cadastro seja recuperada; */
   
   /* Arquivo aberto somente como leitura para caso o arquivo nao exista, ele 
   nao crie outro vazio; */
   arquivo=fopen("academia.txt","r+b");
   if (arquivo==NULL)
   {
      printf("\nNao existe nenhum cadastro para este CPF.\n\n");
      getch();
      system("cls");
   }
   
   else
   {
      fclose(arquivo);
      /* Caso o arquivo exista, agora ele é aberto como leitura/gravação para 
      dar prosseguimento a função; */
      arquivo=fopen("academia.txt","a+b");
      
      // Retorno recebe 1 caso a leitura ocorra om sucesso;
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      /* Enquanto retorno for igual a 1 o loop continua, quando o arquivo chegar
      ao fim retorno receberá 0 e sairá do loop; */
      while(retorno==1)
      {
         // Comparação se o CPF digitado é igual a de algum CPF contido no arquivo;
         if(strcmp(c.cpf,cpf)==0)
         {
            do
            {
               system("cls");
               printf("\n         .:ACADEMIA POWER MAD:.        ");
               printf("\n\n       -->|| EDITAR CADASTRO ||<--");
               printf("\n\nATENCAO! As alteracoes serao salvas somente se o usuario confirmar a acao!");
               printf("\n\nCodigo...........................: %d", c.codigo);
               printf("\nNome.............................: %s", c.nome);
               printf("\nSexo (M/F).......................: %c", c.sexo);
               printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
               printf("\nEndereco.........................: %s", c.end);
               printf("\nCidade...........................: %s", c.cidade);
               printf("\nEstado...........................: %s", c.estado);
               printf("\nCEP..............................: %s", c.cep);
               printf("\nRG...............................: %s", c.rg);
               printf("\nCPF..............................: %s", c.cpf);
               printf("\nAtividade........................: %s", c.servico);
               printf("\nMensalidade......................: R$ %4.2f", c.valor);
               controle=1; //Controle recebe 1;
               
               /* Todas as alteraçõe são feitas na memória, os dados só serão 
               descarregados no arquivo caso o usuário digite a opção 12; */
               printf("\n\nQual campo deseja alterar? ");
               printf("\n\n1-> Nome;");
               printf("\n2-> Sexo;");
               printf("\n3-> Data de Nascimento;");
               printf("\n4-> Endereco;");
               printf("\n5-> Cidade;");
               printf("\n6-> Estado;");
               printf("\n7-> CEP:");
               printf("\n8-> RG;");
               printf("\n9-> CPF;");
               printf("\n10-> Atividade;");
               printf("\n11-> Mensalidade;");
               printf("\n12-> Salvar alteracoes;");
               printf("\n0-> Voltar ao Menu Principal;");
               printf("\n\nEscolha uma das opcoes acima: ");
               scanf("%d",&op_alt);
               fflush(stdin);

               if(op_alt==1)
               {
                  printf("\n\nNome.............................: ");
                  gets(c.nome);
                  system("cls");
               }
                     
               else if(op_alt==2) 
               {
                  system("\n\n");
                  valida_sexo(arquivo, controle_func); // Chama a função valida_sexo();
                  system("cls");
               }
               
               else if(op_alt==3) 
               {
                  printf("\n\nData de Nascimento (DD/MM/AAAA)..: ");
                  gets(c.datanasc);
                  system("cls");
               }
                     
               else if(op_alt==4) 
               {
                  printf("\n\nEndereco.........................: ");
                  gets(c.end);
                  system("cls");
               }
               
               else if(op_alt==5) 
               {
                  printf("\n\nCidade...........................: ");
                  gets(c.cidade);
                  system("cls");
               }
               
               else if(op_alt==6) 
               {
                  printf("\n\nEstado...........................: ");
                  gets(c.estado);
                  /*Rotina criada somente para passar os caracteres da variavel "c.estado" 
                  para maiuscula atraves do comando toupper; */
                  for(i=0;i<10;i++)
                  c.estado[i]=toupper(c.estado[i]);
                  system("cls");
               }
               
               else if(op_alt==7) 
               {
                  printf("\n\n");
                  valida_cep(arquivo, controle_func);
                  system("cls");
               }
          
               else if(op_alt==8)
               {
                  printf("\n\nRG (Somente Numeros).............: ");
                  gets(c.rg);
                  system("cls");
               }
               
               else if(op_alt==9) 
               {
                  printf("\n\n");
                  valida_cpf(arquivo, controle_func);
                  system("cls");
               }
               
               else if(op_alt==10) 
               {
                  printf("\n\nServico(s).......................: ");
                  gets(c.servico);
                  system("cls");
               }
                     
               else if(op_alt==11) 
               {
                  printf("\n\nValor do servico.................: R$ ");
                  scanf("%f",&c.valor);
                  fflush(stdin);
                  system("cls");
               }
               
               else if(op_alt==12) 
               {
                  printf("\nConfirmar Alteracao (S/N): ");
                  op = getche();
                  if((op!='N') && (op!='n'))
                  {
                     fclose(arquivo);
                     printf("\n");
                     
                     // Arquivo principal é copiado para um auxiliar;
                     system("copy academia.txt academia.dat"); 
                     // Arquivo principal é deletado;
                     system("del academia.txt"); 
                     
                     // Arquivo principal é reaberto para leitura/gravação;
                     arquivo=fopen("academia.txt", "a+b"); 
                     // Arquivo auxiliar é aberto somente para leitura;
                     arquivo_aux=fopen("academia.dat", "r+b"); 
                     
                     // Rotina de leitura do arquivo auxiliar;
                     fread(&c2, sizeof(struct cadastro), 1, arquivo_aux); 
                     // Enquanto o arquivo não chegar ao fim...;
                     while(!feof(arquivo_aux)) 
                     {
                        /* Todos os dados que forem diferentes do CPF digitado 
                        anteriormente são regravados no arquivo principal; */
                        if(strcmp(c2.cpf,cpf)!=0)
                        fwrite(&c2, sizeof(struct cadastro), 1, arquivo);
                        
                        // Verifica se o arquivo chegou ao fim;
                        fread(&c2, sizeof(struct cadastro), 1, arquivo_aux); 
                     }
                     /* O cadastro alterado recentemente é gravado no final do 
                     arquivo; */
                     fwrite(&c, sizeof(struct cadastro), 1, arquivo);
                  
                     fclose(arquivo_aux);
                     fclose(arquivo);
                     
                     printf("\n\nArquivo alterado com sucesso!");
                     system("del academia.dat"); // Arquivo auxiliar é deletado;
                     getch();
                     system("cls");
                  }
               } 
                  
               else if(op_alt==0) 
               {
                  fclose(arquivo);
                  system("cls");
                  break;
               }
               
               /* Caso a opção digitada seja diferente das especificadas no menu
               uma mensagem de aviso é dada ao usuário; */
               else
               {
                  system("cls");
                  printf("\n         .:ACADEMIA POWER MAD:.        ");
                  printf("\n\n********** ATENCAO **********");
                  printf("\n\nOpcao Invalida!\n\nEscolha novamente!!!");
                  getch();
                  system("cls");
               }
            }while(op_alt!=0);
         } //if(strcmp(c.cpf,cpf)==0)
         /* Verifica se o arquivo chegou ao fim, caso tenha saido, retorno 
         receberá 0, saido do loop;*/
         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      } //while(retorno==1)
      
      /* Caso o CPF digitado não tenha sido encontrado na struct, controle 
      continua 0 e a mensagem abaixo é exibida; */
      if(controle==0)
      {
         printf("\nNao existe nenhum cadastro para este CPF.\n\n");
         getch();
         fclose(arquivo);
         system("cls");
      } //if(controle==0)
      fclose(arquivo);
   }//else
}

//=== FUNCAO EXCLUIR CADASTRO ==================================================
char exclui_cad(char cpf[12])
{
   char op;
   int controle=0;
   
   /* Arquivo aberto somente como leitura para caso o arquivo nao exista, ele 
   nao crie outro vazio; */
   arquivo=fopen("academia.txt","r+b");
   if (arquivo==NULL)
   {
      printf("\nNao existe nenhum cadastro para este CPF.\n\n");
      getch();
      system("cls");
   }
   
   else
   {
      fclose(arquivo);
      /* Caso o arquivo exista, agora ele é aberto como leitura/gravação para 
      dar prosseguimento a função; */
      arquivo=fopen("academia.txt","a+b");
      
      // Retorno recebe 1 caso a leitura ocorra om sucesso;
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      /* Enquanto retorno for igual a 1 o loop continua, quando o arquivo chegar
      ao fim retorno receberá 0 e sairá do loop; */
      while(retorno==1)
      {
         if(strcmp(c.cpf,cpf)==0) // Compara se o CPF digitado existe na struct;
         {
            controle=1;
            system("cls");
            printf("\n         .:ACADEMIA POWER MAD:.        ");
            printf("\n\n      -->|| REMOVER CADASTRO ||<--");
            fclose(arquivo);
            
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG...............................: %s", c.rg);
            printf("\nCPF..............................: %s", c.cpf);
            printf("\nAtividade........................: %s", c.servico);
            printf("\nMensalidade......................: R$ %4.2f", c.valor);
            // Confirmação de exclusão do arquivo;
            printf("\n\nExcluir dados do CPF %s? (S/N): ",c.cpf); 
            op=getche();
            system("cls");
               
            if((op!='n') && (op!='N'))
            {
               // Arquivo principal é copiado para um auxiliar;
               system("copy academia.txt academia.dat"); 
               // Arquivo principal é deletado;
               system("del academia.txt"); 
               
               // Arquivo principal é reaberto para leitura/gravação;
               arquivo=fopen("academia.txt", "a+b");
               // Arquivo auxiliar é aberto somente para leitura;
               arquivo_aux=fopen("academia.dat", "r+b"); 
               
               // Posiciona o ponteiro do arquivo no inicio dele;
               fseek(arquivo, 0, SEEK_SET); 
               while(!feof(arquivo_aux)) // Enquanto o arquivo não chega ao fim;
               {
                  /* Todos os dados que forem diferentes do CPF digitado 
                  anteriormente são regravados no arquivo principal, isso 
                  garante que o CPF a ser removido não faça mais parte do 
                  arquivo principal; */
                  if(strcmp(c.cpf,cpf)!=0)
                  fwrite(&c, sizeof(struct cadastro), 1, arquivo);
                  
                  //Verifica se o arquivo chegou ao fim;
                  fread(&c, sizeof(struct cadastro), 1, arquivo_aux); 
               } //while(!feof(arquivo_aux))
      
               fclose(arquivo_aux);
      
               system("del academia.dat"); // Arquivo auxiliar é deletado;
               system("cls");
               printf("\n         .:ACADEMIA POWER MAD:.        ");
               printf("\n\n      -->|| REMOVER CADASTRO ||<--");
               printf("\n\nCadastro excluido com sucesso!");
      
               fclose(arquivo);
               fclose(arquivo_aux);
               getch();
               system("cls");
            } //if((op!='n') && (op!='N'))
            
            // Caso o usuário escolha não excluir o CPF, a mensagem abaixo é exibida;
            else 
            {
               fclose(arquivo);
               printf("\n         .:ACADEMIA POWER MAD:.        ");
               printf("\n\n      -->|| REMOVER CADASTRO ||<--");
               printf("\n\nExclusao nao realizada!");
               getch();
               system("cls");
            } //else
         } //if(strcmp(c.cpf,cpf)==0)
         
         /* Verifica se o arquivo chegou ao fim, caso tenha saido, retorno 
         receberá 0, saido do loop; */
         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      } //while(retorno==1)
      
      if(controle==0)
      {
         printf("\nNao existe nenhum cadastro para este CPF.\n\n");
         getch();
         fclose(arquivo);
         system("cls");
      } //if(controle==0)
   } //else
}

//=== FUNCAO PARA ORDENAR POR CODIGO (BUBBLE SORT)==============================
void ordenacao_cod_cad()
{
   int i=0, x=0, y=0;
   
   /* rotina que atribui -1 a todos os códigos da struct, porem é somente na 
   memória*/
   for(i=0;i<100;i++)
   c3[i].codigo=-1;
   
   /* Arquivo aberto somente como leitura para caso o arquivo nao exista, 
   ele nao crie outro vazio; */
   arquivo=fopen("academia.txt", "r+b");
   if(arquivo==NULL)
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n  --->|| RELATORIO DE CADASTRO ||<---");
      printf("\n\n---||Arquivo nao existe ou nao pode ser aberto||---");
      printf("\n\nPressione qualquer tecla para voltar ao menu principal");
      getch();
      system("cls");
   } //if(arquivo==NULL)
   
   else
   {
      // Posiciona ponteiro no inicio do arquivo;
      fseek(arquivo, 0, SEEK_SET);
      while(!feof(arquivo))
      {
         fread(&c3[x], sizeof(struct cadastro), 1, arquivo);
         x++; // Carrega os dados gravados e carrega no vetor struct x;
      } //while(!feof(arquivo))
      
      /* Ordenação que compara se o valor do código atual é maior que o código
      posterior, caso seja, ele inverte a posição de ambos */
      for(i=0;i<x;i++)
      for(y=0;y<x;y++)
      {
         // Comparação se o código atual é maior que o posterior;
         if(c3[y].codigo>c3[y+1].codigo)
         {
            c4[0]=c3[y]; // Joga o maior valor em um auxliar;
            c3[y]=c3[y+1]; // Joga o menor valor na posição anterior;
            c3[y+1]=c4[0]; // Joga o maior valor contido no auxiliar na posição posterior;
         }
      }
      fclose(arquivo);
      
      // Arquivo aberto somente como leitura;
      arquivo=fopen("academia.txt", "r+b");
      fseek(arquivo, 0, SEEK_SET);
      for(i=0;i<100;i++)
      {
         /* Todos os códigos que forem != de -1 são gravados no arquivo, porém 
         de forma ordenada; */
         if(c3[i].codigo!=-1)
         fwrite(&c3[i], sizeof(struct cadastro), 1, arquivo);
      }
      fclose(arquivo);
   }
}

//=== FUNCAO BUSCAR CADASTRO ===================================================
void busca_cad()
{
   int cont=0, sc=0; /* Cont é um controle para caso o CPF seja encontrado, uma
   mensagem de exibição aparece alertando o usuário; */
   char cpf_aux[12];
   
   // Arquivo aberto somente como leitura para caso o arquivo nao exista, ele nao crie outro vazio;
   arquivo=fopen("academia.txt","r+b");
   if (arquivo==NULL)
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| BUSCA DE CADASTRO ||<---");
      printf("\n\n---||Arquivo nao existe ou nao pode ser aberto||---");
      getch();
      system("cls");
   }
   
   else
   {
      fclose(arquivo);
      /* Caso o arquivo exista, agora ele é aberto como leitura/gravação para 
      dar prosseguimento a função; */
      arquivo=fopen("academia.txt","a+b");
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| BUSCA DE CADASTRO ||<---");
         
      printf("\n\nDigite o CPF (somente numeros): ");
      gets(cpf_aux);
      fflush(stdin);
      
      // Retorno recebe 1 caso a leitura ocorra com sucesso;
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      /* Enquanto retorno for igual a 1 o loop continua, quando o arquivo chegar
      ao fim retorno receberá 0 e sairá do loop; */
      while(retorno==1)
      {
         if(strcmp(c.cpf,cpf_aux)==0)
         {
            printf("\n\nCodigo...........................: %d", c.codigo);
            printf("\nNome.............................: %s", c.nome);
            printf("\nSexo (M/F).......................: %c", c.sexo);
            printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
            printf("\nEndereco.........................: %s", c.end);
            printf("\nCidade...........................: %s", c.cidade);
            printf("\nEstado...........................: %s", c.estado);
            printf("\nCEP..............................: %s", c.cep);
            printf("\nRG...............................: %s", c.rg);
            printf("\nCPF..............................: %s", c.cpf);
            printf("\nAtividade........................: %s", c.servico);
            printf("\nMensalidade......................: R$ %4.2f", c.valor);
            cont++; /* Como o CPF foi encontrado no arquivo, cont receberá 1 e
            não mais mostrará a mensagem de que o CPF não foi encontrado; */
            
            // Questionario do que deve ser feito com o resultado buscado;
            printf("\n\nO que deseja fazer?");
            printf("\n1-> Alterar cadastro;");
            printf("\n2-> Remover cadastro;");
            printf("\n0-> Voltar para o menu principal;");
            printf("\n\nEscolha uma das opcoes: ");
            scanf("%d",&sc);
            fflush(stdin);
            system("cls");
               
            switch(sc)
            {
               case 1: 
               fclose(arquivo);
               altera_cad(cpf_aux); // Chamada da função altera_cad;
               break;
                  
               case 2:
               fclose(arquivo);
               exclui_cad(cpf_aux); // Chamada da função exclui_cad;
               break;
                  
               default: system("cls");
               break;
            } //switch(sc)
         } //if(strcmp(c.cpf,cpf_aux)==0)
         /* Verifica se o arquivo chegou ao fim, caso tenha saido, retorno 
         receberá 0, saido do loop; */
         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      }//while(retorno==1)
      
      if(cont==0) /* Caso o CPF não seja similar a nenhum no arquivo, cont 
      continuará 0 e a mensagem abaixo é exibida; */
      {
         printf("\nNao existe nenhum cadastro para este CPF.\n\n");
         getch();
         fclose(arquivo);
         system("cls");
      } //if(cont==0)
      cont=0;
      fclose(arquivo);
   }
}

//=== FUNCAO PARA BACKUP DO SISTEMA ============================================
void backup_cad()
{
   /* Arquivo aberto somente como leitura para caso o arquivo nao exista, ele 
   nao crie outro vazio; */
   arquivo=fopen("academia.txt","r+b");
   if (arquivo==NULL)
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| BACKUP DO SISTEMA ||<---");
      printf("\n\n---||Arquivo nao existe ou nao pode ser aberto||---");
      getch();
      system("cls");
   } //if (arquivo==NULL)
   
   else
   {
      fclose(arquivo);
      // Todo o conteudo do arquivo princpal é copiado para o arquivo de backup;
      system("copy academia.txt academia.bkp");
      system("cls"); //Para eliminar mensagem de copia de arquivo;
      
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| BACKUP DO SISTEMA ||<---");
      printf("\n\nBackup realizado com sucesso!");
      getch();
      system("cls");
   } //else
}

//=== FUNCAO PARA  RETORNO DE BACKUP DO SISTEMA ================================
void restaura_cad()
{
   /* Arquivos abertos somente como leitura para caso os arquivos nao existam, 
   eles nao criem outro vazio; */
   arquivo_aux=fopen("academia.bkp","r+b");
   if (arquivo_aux==NULL)
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n  --->|| RESTAURACAO DO SISTEMA ||<---");
      printf("\n\n---||Arquivo necessario para restauracao do sistema nao encontrado||---");
      getch();
      system("cls");
   } //if (arquivo==NULL)
   
   else
   {
      fclose(arquivo_aux);
      /* Todo o conteudo do arquivo de backup é copiado para o principal, 
      restaurando o sistema a partir do backup; */
      system("copy academia.bkp academia.txt");
      system("cls"); //Para eliminar mensagem de copia de arquivo;
      
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| RESTAURACAO DO SISTEMA ||<---");
      printf("\n\nSistema restaurado com sucesso!");
      getch();
      system("cls");
   } //else
}

//=== FUNCAO EXIBIR TODOS OS CADASTROS =========================================
void relatorio_desordenado()
{
   arquivo=fopen("academia.txt", "r+b");
   if(arquivo==NULL)
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n  --->|| RELATORIO DE CADASTRO ||<---");
      printf("\n\n---||Arquivo nao existe ou nao pode ser aberto||---");
      printf("\n\nPressione qualquer tecla para voltar ao menu principal");
      getch();
      system("cls");
   } //if(arquivo==NULL)
   
   else
   {
      fclose(arquivo);
      /* Caso o arquivo exista, agora ele é aberto como leitura/gravação para 
      dar prosseguimento a função; */
      arquivo=fopen("academia.txt","a+b");
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| DADOS DOS CADASTRADOS ||<---");
      // Posiciona ponteiro no inicio do arquivo;
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      /* Enquanto retorno for igual a 1 o loop continua, quando o arquivo chegar
      ao fim retorno receberá 0 e sairá do loop; */
      while(retorno==1)
      {
         printf("\n\nCodigo...........................: %d", c.codigo);
         printf("\nNome.............................: %s", c.nome);
         printf("\nSexo (M/F).......................: %c", c.sexo);
         printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
         printf("\nEndereco.........................: %s", c.end);
         printf("\nCidade...........................: %s", c.cidade);
         printf("\nEstado...........................: %s", c.estado);
         printf("\nCEP..............................: %s", c.cep);
         printf("\nRG...............................: %s", c.rg);
         printf("\nCPF..............................: %s", c.cpf);
         printf("\nAtividade........................: %s", c.servico);
         printf("\nMensalidade......................: R$ %4.2f", c.valor);
         /* Verifica se o arquivo chegou ao fim, caso tenha saido, retorno 
         receberá 0, saido do loop; */
         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      } //while(retorno==1)
      fclose(arquivo);
      printf("\n\nPressione qualquer tecla para voltar ao menu principal");
      getch();
      system ("cls");
   }
}

//=== FUNCAO EXIBIR TODOS OS CADASTROS =========================================
void relatorio_cad()
{
   /* Sempre que um campo do arquivo é alterado, esse campo é regravado no arquivo como o ultimo da fila,
   se existem 5 cadastros no arquivo, e for necessario alterar o cadastro numero 2, a ordem na exibição ficaria
   fora de ordem (1,3,4,5,2), a função "ordenacao_cod_cad()" tem como objetivo ordenar para que a exibição seja
   feita na ordem correta (1,2,3,4,5); */
   ordenacao_cod_cad();
   
   // Tratamento de arquivo feito previamente na função "ordenacao_cod_cad()";
   if (arquivo==NULL)
   {}
   
   else
   {
      /* Caso o arquivo exista, agora ele é aberto como leitura/gravação para 
      dar prosseguimento a função; */
      arquivo=fopen("academia.txt","a+b");
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n    --->|| DADOS DOS CADASTRADOS ||<---");
      
      // Retorno recebe 1 caso a leitura ocorra om sucesso;
      retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      /* Enquanto retorno for igual a 1 o loop continua, quando o arquivo chegar
      ao fim retorno receberá 0 e sairá do loop; */
      while(retorno==1)
      {
         printf("\n\nCodigo...........................: %d", c.codigo);
         printf("\nNome.............................: %s", c.nome);
         printf("\nSexo (M/F).......................: %c", c.sexo);
         printf("\nData de Nascimento (DD/MM/AAAA)..: %s", c.datanasc);
         printf("\nEndereco.........................: %s", c.end);
         printf("\nCidade...........................: %s", c.cidade);
         printf("\nEstado...........................: %s", c.estado);
         printf("\nCEP..............................: %s", c.cep);
         printf("\nRG...............................: %s", c.rg);
         printf("\nCPF..............................: %s", c.cpf);
         printf("\nAtividade........................: %s", c.servico);
         printf("\nMensalidade......................: R$ %4.2f", c.valor);
         /* Verifica se o arquivo chegou ao fim, caso tenha saido, retorno 
         receberá 0, saido do loop; */
         retorno=fread(&c, sizeof(struct cadastro), 1, arquivo);
      } //while(retorno==1)
      fclose(arquivo);
      printf("\n\nPressione qualquer tecla para voltar ao menu principal");
      getch();
      system ("cls");
   }
}

//=== PROGRAMA =================================================================
int main()
{
   int cod_menu;
   char cpf_aux[12];
   
   do
   {
      printf("\n         .:ACADEMIA POWER MAD:.        ");
      printf("\n\n      --->|| MENU PRINCIPAL ||<---        \n");
      printf("\n\n1-> Inserir um novo cadastro;");
      printf("\n2-> Busca individual de cadastro;");
      printf("\n3-> Alterar cadastro do aluno;");
      printf("\n4-> Excluir cadastro do aluno;");
      printf("\n5-> Relatorio completo de cadastro (Sem Ordenacao);");
      printf("\n6-> Relatorio completo de cadastro (Com Ordenacao);");
      printf("\n7-> Backup do sistema;");
      printf("\n8-> Restaurar sistema;");
      printf("\n0-> Sair do programa;");
      printf("\n\nEscolha uma das opcoes acima: ");
      scanf("%d",&cod_menu);
      fflush(stdin);
      system("cls");
      
      switch(cod_menu)
      {
         case 1: insere_cad();
         system("cls");
         break;
                     
         case 2: busca_cad();
         break;
                     
         case 3: 
         printf("\n         .:ACADEMIA POWER MAD:.        ");
         printf("\n\n       -->|| EDITAR CADASTRO ||<--");
         printf("\n\nDigite o CPF: ");
         gets(cpf_aux);
         altera_cad(cpf_aux); // Chama função altera_cad com parametro de cpf_aux;
         break;
          
         case 4: 
         printf("\n         .:ACADEMIA POWER MAD:.        ");
         printf("\n\n      -->|| REMOVER CADASTRO ||<--");
         printf("\n\nDigite o CPF: ");
         gets(cpf_aux);
         exclui_cad(cpf_aux); // Chama função exclui_cad com parametro de cpf_aux;
         break;
         
         case 5: relatorio_desordenado();
         break;
         
         case 6: relatorio_cad();
         break;
         
         case 7: backup_cad();
         break;
         
         case 8: restaura_cad();
         break;
         
         case 0:
         return 0;
         exit(0);
         
         default:
         printf("\n         .:ACADEMIA POWER MAD:.        ");
         printf("\n\n********** ATENCAO **********");
         printf("\n\nOpcao Invalida!\n\nEscolha novamente!!!");
         getch();
         system("cls");
      } //switch(cod_menu)
   }while(cod_menu!=0);
}
