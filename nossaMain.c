#include "buffend.c"

void flush_in(){ 
   int ch;

   while( (ch = fgetc(stdin)) != EOF && ch != '\n' ){} 
}

int criar_tabelas(){

	char *nomeTabela=(char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
	char *nomeCampo=(char *)malloc(sizeof(char)*TAMANHO_NOME_CAMPO);
	int inserir, erro;

	char tipoCampo;
	int pk;

	table *tabela = (table *)malloc(sizeof(table)*1);
	int fimCampos = 0, numTabelas, tamanhoCampo, i;
	
	printf("Digite o numero de tabelas a serem inseridas!\n");
	scanf("%i",&numTabelas);

	for(i = 0; i < numTabelas; i++){
		printf("Digite o nome da tabela!\n");
		scanf("%s",nomeTabela);

		printf("\n%s\n", nomeTabela);

		tabela = iniciaTabela(nomeTabela);

		if(tabela == ERRO_NOME_TABELA_INVALIDO){
			printf("Erro: na função iniciaTabela(). Nome da tabela já existente.\n");
			return 0;
		}

		while(fimCampos == 0){
			printf("Digite o nome do campo!\n");
			scanf("%s",nomeCampo);

			flush_in();
			fflush(stdin);

			printf("Digite o Tipo do campo!(S-C-I-D)\n");
			scanf("%c",&tipoCampo);
			fflush(stdin);

			if(tipoCampo == 'I')
				tamanhoCampo = sizeof(int);
			if(tipoCampo == 'C')
				 tamanhoCampo = sizeof(char);
			if(tipoCampo =='D')
				tamanhoCampo = sizeof(double);
			if(tipoCampo == 'S'){
				printf("Digite o Tamanho do campo!\n");
				scanf("%d",&tamanhoCampo);
			}

			printf("O Campo eh Chave Primaria?(Sim 1 - 0 Nao)\n");
			scanf("%d",&pk);

			tabela = adicionaCampo(tabela, nomeCampo, tipoCampo, tamanhoCampo,pk);

			printf("Deseja inserir um novo campo? (Sim 1 - 0 Nao)\n");
			scanf("%d",&inserir);

			if(inserir == 0){
				fimCampos = 1;
				erro = finalizaTabela(tabela);

				if(erro != SUCCESS){
					printf("Erro %d: na função finalizaTabela().\n", erro);
					return 0;
				}
			}
		}
	}
	return 1;
}

int visualizar_tabela(){

	char *nomeTabela=(char *)malloc(sizeof(char)*TAMANHO_NOME_TABELA);
    struct fs_objects objeto;

	printf("Digite o nome da tabela!\n");
	scanf("%s",nomeTabela);
	objeto=leObjeto(nomeTabela);
	leSchema(objeto);
	printf("a tabela e:\n %s",objeto.nome);

	printf("\n|--------------------------------------------------------------------|\n\n");

	return 1;
}

int menu(){
	int opcao;
		
	printf("|--------------------------------------------------------------------|\n");
	printf("|                              Menu                                  |\n");
	printf("|--------------------------------------------------------------------|\n");
	printf(" Para criar tabelas digite 1 \n Para visualizar as tabelas criadas digite 2 \n Para sair digite 3\n");
	scanf("%d",&opcao);
	printf("|--------------------------------------------------------------------|\n");

	return opcao;
}

int main ()
{
	//~ tp_buffer *bp = (tp_buffer*)malloc(sizeof(tp_buffer)*PAGES);
	//~ bp = initbuffer();

	int opcao;

	while(opcao!=3)
	{
		if(opcao==1)
		{ //cria as tabelas
			printf("|--------------------------------------------------------------------|\n");
			printf("|                        Criar tabelas                               |\n");
			printf("|--------------------------------------------------------------------|\n\n");

			criar_tabelas();
		}
		if(opcao==2)
		{ //mostra as tabelas criadas
			printf("|--------------------------------------------------------------------|\n");
			printf("|                     Visualizar tabelas                             |\n");
			printf("|--------------------------------------------------------------------|\n\n");

			visualizar_tabela();
		}

		opcao = menu();
	}

	return 1;
}
