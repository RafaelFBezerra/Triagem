#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>


typedef struct triagem //REGISTRO COM AS VARIAVEIS PARA ARMAZENAR OS DADOS DO PACIENTE
{
 int codigo;
 char nome[80],data[11],hora[6],sexo[10],queixa[30],hist[50],obs[50],drogas[4],alergias[4];
 char doencas[4],conduta[10],reavaliacao[4],horareav[6],dor[4],idade[3], pa[5],t[5],fr[5],pulso[6];
 }paciente;

typedef struct dadospaciente // DEFINIÇÃO DE LISTA SIMPLESMENTE ENCADEADA PARA ARMEZENAR OS DADOS DO PACIENTE
{
	paciente dados;
    struct dadospaciente *proximo;
}dadopac;

typedef struct listapaciente // NO DESCRITOR  
{
	dadopac *inicio;
    dadopac *fim;
}listapac;

void Inicializartriagem(listapac **Listapac) //INICIALIZACAO DA LISTA, ALOCANDO ESPAÇO NA MEMORIA
{
    *Listapac = (listapac *) malloc(sizeof(listapac));
    (*Listapac)->inicio = NULL;
    (*Listapac)->fim = NULL;
}

int EstaVaziapac(listapac *Listapac) //FUNÇAO PARA VERIFICAR SE A LISTA DO PACIENTE ESTA VAZIA 
{
    return Listapac->inicio == NULL;
}

void inserirpac(listapac *Listapac,char nome[], char sexo[], char queixa[], char hist[], char obs[], char drogas[], char alergias[],char doencas[], char conduta[], char reavaliacao[],  char horareav[], char dor[], char idade[], char pa[], char t[], char fr[], char pulso[],int codigo, char hora[],char data[])
//INSERÇÃO DOS DADOS DO PACIENTE NA LISTA 
{
	    dadopac *novopac;
        novopac = ( dadopac*)malloc(sizeof(dadopac));
        strcpy(novopac->dados.nome,nome);
        strcpy(novopac->dados.sexo,sexo);
        strcpy(novopac->dados.queixa,queixa);
        strcpy(novopac->dados.hist,hist);
        strcpy(novopac->dados.obs,obs);
        strcpy(novopac->dados.drogas,drogas);
        strcpy(novopac->dados.alergias,alergias);
        strcpy(novopac->dados.doencas,doencas);
        strcpy(novopac->dados.conduta,conduta);
        strcpy(novopac->dados.reavaliacao,reavaliacao);
        strcpy(novopac->dados.horareav,horareav);
        strcpy(novopac->dados.dor,dor);
        strcpy(novopac->dados.idade,idade);
        strcpy(novopac->dados.pa,pa);
        strcpy(novopac->dados.t,t);
        strcpy(novopac->dados.fr,fr);
        strcpy(novopac->dados.pulso,pulso);
		novopac->dados.codigo=codigo;
        strcpy(novopac->dados.hora,hora);
		strcpy(novopac->dados.data,data);
	    novopac->proximo = NULL;
   
		if (Listapac->inicio == NULL) //SE A LISTA ESTIVER VAZIA, SERÁ O PRIMEIRO ELEMENTO DA LISTA
	    { Listapac->inicio=novopac;
	      Listapac->fim=novopac;
		}
	    else
	      {Listapac->fim->proximo=novopac;// LISTA SIMPLESMENTE ENCADEADA, INSERÇÃO NO FINAL
	       Listapac->fim=novopac;
		  }
}
typedef struct listaprioridade //REGISTRO PARA ARMAZENAR OS DADOS NA LISTA PRIORITARIA DE TRIAGEM
{
	int prioridade, selecenf, codigopacleitolista, selecmed;
	char dataentlista[11], horaentlista[6];

}pr;

typedef struct Item
{   struct Item *anterior; //LISTA DUPLAMENTE ENCADEADA
	pr dado;
    struct Item *proximo;
}Itens;

typedef struct Listas
{   Itens *inicio; //NO DESCRITOR
    Itens *fim;
}Lista;


void Inicializar(Lista **lista) //ALOCAÇÃO NA MEMÓRIA
{
    *lista = (Lista *) malloc(sizeof(Lista));
    (*lista)->inicio = NULL;
    (*lista)->fim = NULL;
}

int EstaVazia(Lista *lista)//VERIFICA SE A LISTA DE TRIAGEM ESTA VAZIA
{
    return lista->inicio == NULL;
}


void Inserir(Lista *lista,listapac *Listapac,int prioridade, int codigopacleitolista,char dataentlista[], char horaentlista[],int selecenf,int selecmed)
//FUNCÃO QUE INSERE CONFORME A PRIORIDADE DE ATENDIMENTO (0-1-2-3)
{

	Itens *novo;
    novo = (Itens *)malloc(sizeof(Itens));//ALOCAÇÃO DE UM NOVO NO NA LISTA


    if (novo != NULL)
    {
		novo->dado.prioridade=prioridade;
	 	novo->dado.codigopacleitolista = Listapac->fim->dados.codigo;
		strcpy(novo->dado.horaentlista,Listapac->fim->dados.hora);
		strcpy(novo->dado.dataentlista,Listapac->fim->dados.data);
        novo->dado.selecenf = selecenf;
        novo->dado.selecmed = selecmed;

		novo->proximo = NULL;
        novo->anterior = NULL;

        if(EstaVazia(lista))//PARA LISTA VAZIA, INSERÇÃO SERA NO INICIO POR SE TRATAR DE SER O PRIMEIRO ELEMENTO
          {
            lista->inicio = novo;
            lista->fim = novo;
           	printf("Insere no inicio, insercao no inicio %d\n", novo->dado.prioridade);
		   }

        else
        {

            Itens *atual, *ant;

            for(atual = lista->inicio; atual != NULL && atual->dado.prioridade <= prioridade;ant = atual, atual = atual->proximo)//FOR PARA PERCORRER A LISTA
			// E INSERIR DE FORMA ORDENADA CONFORME A PRIORIDADE SELECIONADA PELO O USUARIO
			{

            }

            if(atual == NULL)
			{
                lista->fim = novo;
                novo->proximo = NULL;
                novo->anterior = ant;
                ant->proximo = novo;
            }
            else
			{
                if(atual == lista->inicio)
				{
                    lista->inicio = novo;
                    novo->proximo = atual;
                    atual->anterior = novo;
                }
                else
				{
                novo->proximo = atual;
                novo->anterior = ant;
                ant->proximo = novo;
                atual->anterior = novo;
            	}
            }

		}
   	}
}

void MostrarListaDireta(Lista *lista) // MOSTRA OS PACIENTES QUE ESTÃO NA LISTA DE TRIAGEM CONFORME SUA PRIORIDADE
{
    int i = 0;
    Itens *item;
    printf("\n\n Listando...\n\n");
    printf("---------------------------------\n");

    if (EstaVazia(lista))
    {
        printf ("A Lista esta vazia!\n");
    }
    else
    {
        item = lista->inicio;
              while(item != NULL)
        {
            i++;
				printf("CODIGO DA PRIORIDADE: %d\n", item->dado.prioridade);
				printf("CODIGO DO PACIENTE: %d\n", item->dado.codigopacleitolista);
				printf("DATA DE ENTRADA: %s\n", item->dado.dataentlista);
            	printf("HORA DE ENTRADA: %s\n", item->dado.horaentlista);
				printf("CODIGO DO ENFERMEIRO %d\n", item->dado.selecenf);
				printf("CODIGO DO MEDICO %d\n", item->dado.selecmed);
				
            item = item->proximo;
        }
    }

    printf("---------------------------------\n");
}

typedef struct cadmedicos // STRUCT PARA ARMAZENAR OS DADOS DOS MEDICOS CADASTRADOS, INSERIDOS EM UMA LISTA SIMPLESMENTE ENCADEADA
{char codigomed[100];
 char nomemed[100];
 }medicos;

typedef struct dadosmedicos
{
	medicos dados;
    struct dadosmedicos *proximo;
}dadomed;

typedef struct listasmedicos
{
	dadomed *inicio;
    dadomed *fim;
}listamed;

void Inicializarlistamed(listamed **Listamed)
{
    *Listamed = (listamed *) malloc(sizeof(Listamed));
    (*Listamed)->inicio = NULL;
    (*Listamed)->fim = NULL;
}

int EstaVaziamed(listamed *Listamed)
{
    return Listamed->inicio == NULL;
}
void cadastromedicos(listamed *Listamed, char codigomed[], char nomemed[])
{
    dadomed *novomed;
    novomed = ( dadomed*)malloc(sizeof(dadomed));


		strcpy(novomed->dados.codigomed,codigomed);
        strcpy(novomed->dados.nomemed,nomemed);

	    novomed->proximo = NULL;
   
		if (Listamed->inicio == NULL)
	    { Listamed->inicio=novomed;
	      Listamed->fim=novomed;
		}
	    else
	      {Listamed->fim->proximo=novomed;
	       Listamed->fim=novomed;
		  }

}

void mostrarcadastromedicos(listamed *Listamed) //MOSTRA A RELAÇÃO DE MEDICOS CADASTRADOS
{
	 int i=0;
	 dadomed *dadosmedicos;

	if (EstaVaziamed(Listamed))
    {
        printf ("NAO HA MEDICOS CADASTRADOS!!! CADASTRE O PRIMEIRO\n");
    }
    else
    {
			dadosmedicos = Listamed->inicio;
			while(dadosmedicos != NULL)
			{
				i++;
				printf("NOME DO MEDICO: %s\n", dadosmedicos->dados.nomemed);
				printf("REGISTRO DO MEDICO: %s\n", dadosmedicos->dados.codigomed);
				dadosmedicos = dadosmedicos->proximo;
			}
	}
}

typedef struct cadenfermeiros // STRUCT PARA ARMAZENAR OS DADOS DOS ENFERMEIROS CADASTRADOS, INSERIDOS EM UMA LISTA SIMPLESMENTE ENCADEADA
{char codigoenf[10];
 char nomeenf[100];

}enfermeiros;

typedef struct dadosenfermeiros
{
	enfermeiros dados;
    struct dadosenfermeiros *proximo;
}dadoenf;

typedef struct listasenfermeiros
{
	dadoenf *inicio;
    dadoenf *fim;
}listaenf;

void Inicializarlistaenf(listaenf **Listaenf)
{
    *Listaenf = (listaenf *) malloc(sizeof(Listaenf));
    (*Listaenf)->inicio = NULL;
    (*Listaenf)->fim = NULL;
}

int EstaVaziaenf(listaenf *Listaenf)
{
    return Listaenf->inicio == NULL;
}
void cadastroenfermeiros(listaenf *Listaenf, char codigoenf[], char nomeenf[])
{
    dadoenf *novoenf;
    novoenf = ( dadoenf*)malloc(sizeof(dadoenf));


		strcpy(novoenf->dados.codigoenf,codigoenf);
        strcpy(novoenf->dados.nomeenf,nomeenf);

	    novoenf->proximo = NULL;
   
		if (Listaenf->inicio == NULL)
	    { Listaenf->inicio=novoenf;
	      Listaenf->fim=novoenf;
		}
	    else
	      {Listaenf->fim->proximo=novoenf;
	       Listaenf->fim=novoenf;
		  }

}

void mostrarcadastroenfermeiros(listaenf *Listaenf) //MOSTRA A RELAÇÃO DE ENFERMEIROS CADASTRADOS
{
	 int i=0;
	 dadoenf *dadosenfermeiros;

	if (EstaVaziaenf(Listaenf))
    {
        printf ("NAO HA ENFERMEIROS CADASTRADOS!!! CADASTRE O PRIMEIRO\n");
    }
    else
    {
			dadosenfermeiros = Listaenf->inicio;

			while(dadosenfermeiros != NULL)
			{
				i++;
				printf("ENF:[%d]\nNOME DO ENFERMEIRO: %s\n", i, dadosenfermeiros->dados.nomeenf);
				printf("CODIGO DO ENFERMEIRO: %s\n", dadosenfermeiros->dados.codigoenf);
				dadosenfermeiros = dadosenfermeiros->proximo;
			}
	}
}
typedef struct leitos //DECLARAÇÃO DA LISTA DE LEITOS, LISTA SIMPLESMENTE ENCADEADA
{
	int contador,prioridadeleito,codigopacleito,codigoenfleito,codigomedleito;
	char dataent[11], horaent[6];
}leito;

typedef struct dadosleito
{
	leito dados;
    struct dadosleito *proximo;
}dadoleito;

typedef struct listaleitos
{
	dadoleito *inicio;
    dadoleito *fim;
}listaleito;

void Inicializarlistaleito(listaleito **Listaleito)
{
    *Listaleito = (listaleito *) malloc(sizeof(Listaleito));
    (*Listaleito)->inicio = NULL;
    (*Listaleito)->fim = NULL;
}

int EstaVazialeito(listaleito *Listaleito)
{
    return Listaleito->inicio == NULL;
}

void inserirleito(listaleito *Listaleito,listapac *Listapac,int prioridade, int codigopacleito, char horaent[],char dataent[],int selecenf,int selecmed)

{
    dadoleito *novoleito;
    novoleito = ( dadoleito*)malloc(sizeof(dadoleito));

	 	novoleito->dados.prioridadeleito = prioridade;
	 	novoleito->dados.codigoenfleito = selecenf;
	 	novoleito->dados.codigomedleito = selecmed;
	 	novoleito->dados.codigopacleito = Listapac->fim->dados.codigo;
		strcpy(novoleito->dados.horaent,Listapac->fim->dados.hora);
		strcpy(novoleito->dados.dataent,Listapac->fim->dados.data);
        


		novoleito->proximo = NULL;


		if (Listaleito->inicio == NULL)
	    {
			Listaleito->inicio=novoleito;
	        Listaleito->fim=novoleito;

		}
	    else
	      {
		   Listaleito->fim->proximo=novoleito;
	       Listaleito->fim=novoleito;

		  }

}
void mostrarlistaleito(listaleito *Listaleito) // MOSTRA OS PACIENTES INSERIDOS NO LEITO
{
	 int i=0;
	 dadoleito *dadosleito;
	 dadosleito =(dadoleito*)malloc(sizeof(dadoleito));
	 int *asd, *asdd;

	if (EstaVazialeito(Listaleito))
    {
        printf ("O LEITO ESTA VAZIO!!!\n");
    }
    else
    {
			dadosleito = Listaleito->inicio;

			while(dadosleito != NULL)
			{
				i++;
				printf("CODIGO DA PRIORIDADE: %d\n", dadosleito->dados.prioridadeleito);
				printf("CODIGO DO PACIENTE: %d\n", dadosleito->dados.codigopacleito);
				printf("DATA DE ENTRADA: %s\n", dadosleito->dados.dataent);
            	printf("HORA DE ENTRADA: %s\n", dadosleito->dados.horaent);
				printf("CODIGO DO ENFERMEIRO %d\n", dadosleito->dados.codigoenfleito);
				printf("CODIGO DO MEDICO %d\n",dadosleito->dados.codigomedleito);
				dadosleito = dadosleito->proximo;
			}
	}
}

int tamanholeito (listaleito *Listaleito) //RETORNA A QUANTIDADE DE LEITOS OCUPADOS
{
 dadoleito *z;
 int cont = 0;
 z = Listaleito->inicio;
 while (z != NULL)
   { cont ++;
     z = z->proximo;
   }
    return cont;
 }


void Menu() //VOID PRINTANDO AS OPÇÕES DISPONÍVEIS
{   system("cls");
    printf("                                |LISTA DE TRIAGEM| \n\n\n" );
  
	printf("MENU DE OPCOES \n\n" );
    printf("1 FICHA DE ATENDIMENTO  \n" );
	printf("2 LEITOS OCUPADOS E PACIENTES EM ESPERA \n" );
    printf("3 CADASTRO DE MEDICOS \n");
    printf("4 MOSTRAR MEDICOS CADASTRADOS \n" );
    printf("5 CADASTRO DE ENFERMEIROS \n" );
	printf("6 MOSTRAR ENFERMEIROS CADASTRADOS \n" );
	printf("7 RETIRAR DO LEITO E INSERIR NOVO PACIENTE \n" );
	printf("8 MOSTRAR LISTA PRIORITARIA DE TRIAGEM \n" );
	printf("9 MOSTRAR LISTA DE LEITOS \n" );
	printf("10 Sair \n" );
	printf("Opcao : " );
}


int tamanho (Lista *lista) //RETORNA A QUANTIDADE DE PACIENTES NA LISTA DE TRIAGEM
{
 Itens *p;
 int cont = 0;
 p = lista->inicio;
 while (p != NULL )
   {
   	  if(p->dado.prioridade != 0)
		   {
		   	cont ++;
		   }

	     p = p->proximo;
   }
    return cont;
 }

void retirarlista(Lista*lista) // FUNÇÃO QUE RETIRA O PACIENTE DA LISTA
{
    Itens *item;

    if(!EstaVazia(lista))
    {
        item = lista->inicio;
        lista->inicio = item->proximo;
        free(item);

        if (lista->inicio == NULL)
            lista->fim = NULL;
    }
}
void retiraleito(listaleito*Listaleito) //FUNÇÃO QUE RETIRA O PACIENTE DO LEITO
{
    dadoleito *dadosleito;

    if(!EstaVazialeito(Listaleito))
    {
        dadosleito = Listaleito->inicio;
        Listaleito->inicio= dadosleito->proximo;
        free(dadosleito);

        if (Listaleito->inicio == NULL)
            Listaleito->fim = NULL;
    }
}



int main()

{   int cod,tamlista,i,selecenf,verifleito,veriflista, selecmed;
    int z,opcao,tam,codigo, prioridade,contador=0;  
 	char nome[80],nomemed[80],codigomed[100], data[11],hora[6],sexo[9],queixa[30],hist[50],obs[50],drogas[3],alergias[3],doencas[3];
	char codigoenf[10], nomeenf[80], idade[3], pa[5],t[5],fr[5],pulso[6], conduta[10],reavaliacao[3],horareav[5],enfermeiro[80],dor[3];
	float valor;
   	int prioridadeleito, codigopacleito, codigopacleitolista;
	char dataent[11], horaent[6], dataentlista[11], horaentlista[6];


	Lista *lista = NULL;
	Inicializar(&lista);
    listamed *Listamed = NULL;
    Inicializarlistamed(&Listamed);
    listaenf *Listaenf = NULL;
    Inicializarlistaenf(&Listaenf);
    listaleito *Listaleito = NULL;
    Inicializarlistaleito(&Listaleito);
    listapac *Listapac = NULL;
    Inicializartriagem(&Listapac);

	tam = tamanholeito(Listaleito);
	tamlista = tamanho(lista);


   do{

    Menu();
    scanf("%i", &opcao);

        switch (opcao)
        {
            case 1: //INSERÇÃO DOS DADOS DO PACIENTE CONFORME SUA PRIORIADE, NA LISTA DE TRIAGEM E LEITOS, SEGUINDO AS CONDIÇÕES


                printf("SELECIONE A PRIORIDADE (0-VERMELHA - 1-AMARELA - 2-VERDE - 3-AZUL): ");//SELECIONA A PRIORIDADE
				scanf("%d",&prioridade);
					if(EstaVaziaenf(Listaenf)) //CASO NÃO TENHA MEDICOS E ENFERMEIROS CADASTRADOS, O USUÁRIO DEVE CADASTRAR ANTES DE INSERIR O PACIENTE 
					{
						printf("NAO HA ENFERMEIROS CADASTRADOS!!! CADASTRE PELO MENOS UM CONTINUAR!!!\n");
						system("pause");
						if (EstaVaziamed(Listamed))
							{
							printf("NAO HA MEDICOS CADASTRADOS!!! CADASTRE PELO MENOS UM CONTINUAR!!!\n");
							system("pause");
							}
					}
					else
					{
						
						if (prioridade==0) //INSERE DIRETAMENTE NO LEITO ENQUANTO HOUVER ESPAÇO (LEITO TAM 20)
						{

                            printf("NOME:  ");
                            scanf("\n%[^\n]s", &nome);
			                printf("SEXO:  ");
			                scanf("\n%[^\n]s", &sexo);
			                printf("QUEIXA:  ");
			                scanf("\n%[^\n]s", &queixa);
			                printf("BREVE HISTORIA:   ");
			                scanf("\n%[^\n]s", &hist);
			                printf("DROGAS:  ");
			                scanf("\n%[^\n]s", &drogas);
			                printf("OBSERVACAO:  ");
			                scanf("\n%[^\n]s", &obs);
			                printf("ALERGIAS:  ");
			                scanf("\n%[^\n]s", &alergias);
			                printf("DOENCAS:  ");
			                scanf("\n%[^\n]s", &doencas);
			                printf("CONDUTA:  ");
			                scanf("\n%[^\n]s", &conduta);
			                printf("REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &reavaliacao);
			                printf("HORA DA REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &horareav);
			                printf("DOR:  ");
			                scanf("\n%[^\n]s", &dor);
			                printf("IDADE:  ");
			                scanf("\n%[^\n]s", &idade);
			                printf("PRESSAO ARTERIAL:  ");
			                scanf("\n%[^\n]s", &pa);
			                printf("TEMPERATURA:  ");
			                scanf("\n%[^\n]s", &t);
			                printf("FREQUENCIA RESPIRATORIA:  ");
			                scanf("\n%[^\n]s", &fr);
			                printf("PULSO:  ");
			                scanf("\n%[^\n]s", &pulso);
							printf( "CODIGO DO PACIENTE: ");
			                scanf("\n%d", &codigo);
			                printf( "HORA: ");
			                scanf("\n%[^\n]s", &hora);
                            printf( "DATA: ");
			                scanf("\n%[^\n]s", &data);
							inserirpac(Listapac,nome, sexo, queixa, hist, obs, drogas, alergias, doencas, conduta, reavaliacao, horareav, dor, idade, pa, t, fr, pulso,codigo,hora,data);
							printf("ENFERMEIROS DISPONIVEIS: \n");
							mostrarcadastroenfermeiros(Listaenf);
							printf("MEDICOS DISPONIVEIS: \n");
							mostrarcadastromedicos(Listamed);
							printf("DIGITE O CODIGO DO ENFERMEIRO DESEJADO:\n");
							scanf("%d",&selecenf);
							system("pause");
							printf("DIGITE O CODIGO DO MEDICO DESEJADO:\n");
							scanf("%d",&selecmed);
							system("pause");
							
									tam=tamanholeito(Listaleito);

									if (tam<20)
									{
						            prioridade = 0;
									MostrarListaDireta(lista);
									printf("INSERCAO DIRETA NO LEITO\n");
					 				inserirleito(Listaleito,Listapac,prioridade,codigopacleito,horaent, dataent,selecenf,selecmed);
									mostrarlistaleito(Listaleito);
					                retirarlista(lista);
									printf("\n\n\n");
					                system("pause");

									}
									if (tam>=20)
									{
									printf("O LEITO ESTA CHEIO!!!!");
									printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
									prioridade = 0;
									Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
									MostrarListaDireta(lista);
					                printf("\n");
					                system("pause");
								    }
						}
						contador++;
						if(prioridade==1)// A CADA 5 INSERÇÕES (PRIORIDADES 1-2-3) INSERE O PACIENTE COM A PRIORIDADE MAIOR NO LEITO
						{
                            printf("NOME:  ");
                            scanf("\n%[^\n]s", &nome);
			                printf("SEXO:  ");
			                scanf("\n%[^\n]s", &sexo);
			                printf("QUEIXA:  ");
			                scanf("\n%[^\n]s", &queixa);
			                printf("BREVE HISTORIA:   ");
			                scanf("\n%[^\n]s", &hist);
			                printf("DROGAS:  ");
			                scanf("\n%[^\n]s", &drogas);
			                printf("OBSERVACAO:  ");
			                scanf("\n%[^\n]s", &obs);
			                printf("ALERGIAS:  ");
			                scanf("\n%[^\n]s", &alergias);
			                printf("DOENCAS:  ");
			                scanf("\n%[^\n]s", &doencas);
			                printf("CONDUTA:  ");
			                scanf("\n%[^\n]s", &conduta);
			                printf("REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &reavaliacao);
			                printf("HORA DA REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &horareav);
			                printf("DOR:  ");
			                scanf("\n%[^\n]s", &dor);
			                printf("IDADE:  ");
			                scanf("\n%[^\n]s", &idade);
			                printf("PRESSAO ARTERIAL:  ");
			                scanf("\n%[^\n]s", &pa);
			                printf("TEMPERATURA:  ");
			                scanf("\n%[^\n]s", &t);
			                printf("FREQUENCIA RESPIRATORIA:  ");
			                scanf("\n%[^\n]s", &fr);
			                printf("PULSO:  ");
			                scanf("\n%[^\n]s", &pulso);
							printf( "CODIGO DO PACIENTE: ");
			                scanf("\n%d", &codigo);
			                printf( "HORA: ");
			                scanf("\n%[^\n]s", &hora);
                            printf( "DATA: ");
			                scanf("\n%[^\n]s", &data);
							inserirpac(Listapac,nome, sexo, queixa, hist, obs, drogas, alergias, doencas, conduta, reavaliacao, horareav, dor, idade, pa, t, fr, pulso,codigo,hora,data);
							printf("ENFERMEIROS DISPONIVEIS: \n");
							mostrarcadastroenfermeiros(Listaenf);
							printf("MEDICOS DISPONIVEIS: \n");
							mostrarcadastromedicos(Listamed);
							printf("DIGITE O CODIGO DO ENFERMEIRO DESEJADO:\n");
							scanf("%d",&selecenf);
							system("pause");
							printf("DIGITE O CODIGO DO MEDICO DESEJADO:\n");
							scanf("%d",&selecmed);
							system("pause");
							tam = tamanholeito(Listaleito);
							tamlista = tamanho(lista);



							if(tamlista>0&&tam<20)
								{
									if(contador%5==0)
									{

										prioridade = 1;
										MostrarListaDireta(lista);
										printf("INSERCAO NO LEITO (A CADA 5 CADASTROS)\n");
										inserirleito(Listaleito,Listapac,prioridade,codigopacleito,horaent, dataent,selecenf,selecmed);
										mostrarlistaleito(Listaleito);
										retirarlista(lista);
										printf("\n");
						                system("pause");
									}
                                    system("pause");
								}


								if (tam>=20)
								{
									prioridade = 1;
									printf("O LEITO ESTA CHEIO!!!!\n");
									printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
									Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
									MostrarListaDireta(lista);
				                	printf("\n");
				                	system("pause");
								}
								prioridade = 1;
								printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
								Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
								MostrarListaDireta(lista);
				                printf("\n");
				                system("pause");

						}

						if(prioridade==2)
						{
                            printf("NOME:  ");
                            scanf("\n%[^\n]s", &nome);
			                printf("SEXO:  ");
			                scanf("\n%[^\n]s", &sexo);
			                printf("QUEIXA:  ");
			                scanf("\n%[^\n]s", &queixa);
			                printf("BREVE HISTORIA:   ");
			                scanf("\n%[^\n]s", &hist);
			                printf("DROGAS:  ");
			                scanf("\n%[^\n]s", &drogas);
			                printf("OBSERVACAO:  ");
			                scanf("\n%[^\n]s", &obs);
			                printf("ALERGIAS:  ");
			                scanf("\n%[^\n]s", &alergias);
			                printf("DOENCAS:  ");
			                scanf("\n%[^\n]s", &doencas);
			                printf("CONDUTA:  ");
			                scanf("\n%[^\n]s", &conduta);
			                printf("REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &reavaliacao);
			                printf("HORA DA REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &horareav);
			                printf("DOR:  ");
			                scanf("\n%[^\n]s", &dor);
			                printf("IDADE:  ");
			                scanf("\n%[^\n]s", &idade);
			                printf("PRESSAO ARTERIAL:  ");
			                scanf("\n%[^\n]s", &pa);
			                printf("TEMPERATURA:  ");
			                scanf("\n%[^\n]s", &t);
			                printf("FREQUENCIA RESPIRATORIA:  ");
			                scanf("\n%[^\n]s", &fr);
			                printf("PULSO:  ");
			                scanf("\n%[^\n]s", &pulso);
							printf( "CODIGO DO PACIENTE: ");
			                scanf("\n%d", &codigo);
			                printf( "HORA: ");
			                scanf("\n%[^\n]s", &hora);
                            printf( "DATA: ");
			                scanf("\n%[^\n]s", &data);
							inserirpac(Listapac,nome, sexo, queixa, hist, obs, drogas, alergias, doencas, conduta, reavaliacao, horareav, dor, idade, pa, t, fr, pulso,codigo,hora,data);
							printf("ENFERMEIROS DISPONIVEIS: \n");
							mostrarcadastroenfermeiros(Listaenf);
							printf("MEDICOS DISPONIVEIS: \n");
							mostrarcadastromedicos(Listamed);
							printf("DIGITE O CODIGO DO ENFERMEIRO DESEJADO:\n");
							scanf("%d",&selecenf);
							system("pause");
							printf("DIGITE O CODIGO DO MEDICO DESEJADO:\n");
							scanf("%d",&selecmed);
							system("pause");
								

								if(tamlista>0&&tam<20)
								{

									if(tamlista%5==0)
									{
										prioridade = 2;
										MostrarListaDireta(lista);
										printf("INSERCAO NO LEITO (A CADA 5 CADASTROS)\n");
										inserirleito(Listaleito,Listapac,prioridade,codigopacleito,horaent, dataent,selecenf,selecmed);
										mostrarlistaleito(Listaleito);
										retirarlista(lista);
										printf("\n");
						                system("pause");
									}

								system("pause");
								}

								if (tam>=20)
								{
									prioridade = 2;
									printf("O LEITO ESTA CHEIO!!!!");
									printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
									Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
									MostrarListaDireta(lista);
				                	printf("\n");
				                	system("pause");
								}
								prioridade = 2;
								printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
								Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
								MostrarListaDireta(lista);
				                printf("\n");
				                system("pause");
						}
						if(prioridade==3)
						{
                            printf("NOME:  ");
                            scanf("\n%[^\n]s", &nome);
			                printf("SEXO:  ");
			                scanf("\n%[^\n]s", &sexo);
			                printf("QUEIXA:  ");
			                scanf("\n%[^\n]s", &queixa);
			                printf("BREVE HISTORIA:   ");
			                scanf("\n%[^\n]s", &hist);
			                printf("DROGAS:  ");
			                scanf("\n%[^\n]s", &drogas);
			                printf("OBSERVACAO:  ");
			                scanf("\n%[^\n]s", &obs);
			                printf("ALERGIAS:  ");
			                scanf("\n%[^\n]s", &alergias);
			                printf("DOENCAS:  ");
			                scanf("\n%[^\n]s", &doencas);
			                printf("CONDUTA:  ");
			                scanf("\n%[^\n]s", &conduta);
			                printf("REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &reavaliacao);
			                printf("HORA DA REAVALIACAO:  ");
			                scanf("\n%[^\n]s", &horareav);
			                printf("DOR:  ");
			                scanf("\n%[^\n]s", &dor);
			                printf("IDADE:  ");
			                scanf("\n%[^\n]s", &idade);
			                printf("PRESSAO ARTERIAL:  ");
			                scanf("\n%[^\n]s", &pa);
			                printf("TEMPERATURA:  ");
			                scanf("\n%[^\n]s", &t);
			                printf("FREQUENCIA RESPIRATORIA:  ");
			                scanf("\n%[^\n]s", &fr);
			                printf("PULSO:  ");
			                scanf("\n%[^\n]s", &pulso);
							printf( "CODIGO DO PACIENTE: ");
			                scanf("\n%d", &codigo);
			                printf( "HORA: ");
			                scanf("\n%[^\n]s", &hora);
                            printf( "DATA: ");
			                scanf("\n%[^\n]s", &data);
							inserirpac(Listapac,nome, sexo, queixa, hist, obs, drogas, alergias, doencas, conduta, reavaliacao, horareav, dor, idade, pa, t, fr, pulso,codigo,hora,data);
							printf("ENFERMEIROS DISPONIVEIS: \n");
							mostrarcadastroenfermeiros(Listaenf);
							printf("MEDICOS DISPONIVEIS: \n");
							mostrarcadastromedicos(Listamed);
							printf("DIGITE O CODIGO DO ENFERMEIRO DESEJADO:\n");
							scanf("%d",&selecenf);
							system("pause");
							printf("DIGITE O CODIGO DO MEDICO DESEJADO:\n");
							scanf("%d",&selecmed);
							system("pause");
							tam = tamanholeito(Listaleito);
							tamlista = tamanho(lista);



							if(tamlista>0&&tam<20)
								{
									if(contador%5==0)
									{
										
										prioridade = 3;
										MostrarListaDireta(lista);
										printf("INSERCAO NO LEITO (A CADA 5 CADASTROS)\n");
										inserirleito(Listaleito,Listapac,prioridade,codigopacleito,horaent, dataent,selecenf,selecmed);
										mostrarlistaleito(Listaleito);
										retirarlista(lista);
										printf("\n");
						                system("pause");
									}
                                    system("pause");
								}


								if (tam>=20)
								{
									prioridade = 3;
									printf("O LEITO ESTA CHEIO!!!!");
									printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
									Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
									MostrarListaDireta(lista);
				                	printf("\n");
				                	system("pause");
								}
								prioridade = 3;
								printf("INSERCAO NA LISTA DE TRIAGEM!!!\n");
								Inserir(lista,Listapac, prioridade,codigopacleitolista,dataentlista, horaentlista, selecenf,selecmed);
								MostrarListaDireta(lista);
				                printf("\n");
				                system("pause");

						}
					}

				break;
            case 2: //RETORNA A QUANTIDADE DE PACIENTES NA LISTA E DOS LEITOS OCUPADOS

				tam = tamanholeito(Listaleito);
                printf( "LEITOS OCUPADOS = %d\n",tam);
                tamlista = tamanho(lista);
                printf( "QUANTIDADE DE PACIENTES NA LISTA = %d\n",tamlista);
				system("pause");
		        break;

            case 3://CADASTRAMENTO DE MEDICOS

				printf( "NOME DO MEDICO: ");
                scanf("\n%[^\n]s", &nomemed);
                printf( "CODIGO DO MEDICO: ");
                scanf("\n%[^\n]s", &codigomed);
                cadastromedicos(Listamed, codigomed, nomemed);
            	break;
            case 4://MOSTRAR A RELAÇÃO DE MEDICOS DISPONÍVEIS

            	mostrarcadastromedicos(Listamed);
				printf("\n");
                system("pause");
				break;

        	case 5://CADASTRAMENTO DE ENFERMEIROS
				printf( "NOME DO ENFERMEIRO: ");
                scanf("\n%[^\n]s", &nomeenf);
                printf( "CODIGO DO ENFERMEIRO: ");
                scanf("\n%[^\n]s", &codigoenf);
                cadastroenfermeiros(Listaenf, codigoenf, nomeenf);

                   break;

			case 6://MOSTRAR A RELAÇÃO DE ENFERMEIROS CADASTRADOS
            	mostrarcadastroenfermeiros(Listaenf);
				printf("\n");
                system("pause");
            		break;
			//tam = tamanholeito(Listaleito);
			//tamlista = tamanho(lista);

			case 7://CASE PARA RETIRAR O PACIENTE DO LEITO E INSERIR O PACIENTE DE MAIOR PRIORIDADE NO LEITO
				
			if (!EstaVazialeito(Listaleito))
		        {
				    printf("MOSTRANDO A LISTA DO LEITO!!!\n");
					mostrarlistaleito(Listaleito);
		            system("pause");
		            printf("RETIRA DO LEITO!!!\n");
					retiraleito(Listaleito);
		            mostrarlistaleito(Listaleito);
		            system("pause");
		            if(!EstaVazia(lista))
		            {
					printf("INSERE O PRIMEIRO PACIENTE DA LISTA DE TRIAGEM!!!\n");
		            inserirleito(Listaleito,Listapac,prioridade,codigopacleito,horaent, dataent,selecenf,selecmed);
		            mostrarlistaleito(Listaleito);
		            system("pause");
					MostrarListaDireta(lista);
					system("pause");
					retirarlista(lista);
					system("pause");
					printf("MOSTRANDO A LISTA ATUALIZADA!!!\n");
					MostrarListaDireta(lista);
					system("pause");
		            }
		            else
		            {
		            	printf("A LISTA ESTÁ VAZIA!!! FACA A INSERCAO DO PACIENTE CONFORME SUA PRIORIDADE!!!\n");
					}
				}
			else
				{
					printf("O LEITO ESTA VAZIO!!! FACA A INSERCAO DO PACIENTE CONFORME SUA PRIORIDADE!!!\n");
					system("pause");
				
				}
	
			case 8: //MOSTRAR OS PACIENTES DA LISTA
            		MostrarListaDireta(lista);
            		system("pause");
					break;
			case 9:
            		mostrarlistaleito(Listaleito);//MOSTRAR OS PACIENTES DO LEITO
            		system("pause");
					break;
	
			case 10:
            		exit;
            		break;

            default:

                printf( "Escolha invalida.\n\n");
                system("pause");
                break;
        }


    }
	while (opcao!=10);

    system("pause");
    return 0;
}
