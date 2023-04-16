#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // usarei o strcpy
#include <locale.h> // aceitar acentua��o

// 2 estruturas que ir�o ser usados durante todo o c�digo
typedef struct { // Estrutura contendo informa��es da disciplina
    char nomeDisciplina[25];
    struct Disciplina * prox;
} Disciplina;

typedef struct { // Estrutura contendo dados do aluno
    int rgm;
    Disciplina * inicioDisciplina;
    struct Dados * prox;
} Dados;


void menu() {
	
	printf("\n-=-=-=-=-=-=-= MENU DE ESCOLHA -=-=-=-=-=-=-=\n");
	printf("\n\tEscolha uma das op��es abaixo\n");
	printf("\t1 - CADASTRAR aluno\n"
		   "\t2 - PROCURAR aluno pelo RGM\n"
		   "\t3 - MOSTRAR todos os alunos\n"
		   "\t4 - REMOVER aluno pelo RGM\n"
		   "\t5 - SAIR\n");
}

// a partir de agora ir� ter fun��es de cadastro de aluno, de disciplina, remo��o, busca...

void cadastroAluno(Dados ** alunosGeral, int rgm, int i) {
	
	int indexDisciplina = 0;
	bool boolDisciplina = true;
	char nomeDisciplina[25], perguntaDisciplina;
    
	Dados * nvAluno = (Dados*) malloc(sizeof(Dados)); // aloca��o din�mica - DADOS
	
	// aplicando os valores para os determinados dados:
    nvAluno->inicioDisciplina = NULL;
    nvAluno->prox = NULL;
    nvAluno->rgm = rgm;
    
    do {
    	printf("Informe a %d disciplina: ", indexDisciplina + 1);
        scanf("%s", &nomeDisciplina);
        
        cadastroDisciplina(nvAluno, nomeDisciplina); // chamando a fun��o cadastroDisciplina pra incluir a disciplina digitada
        
        bool caracterCorreto = false;
        do {
        	printf("\nQuer adicionar mais disciplina?[s/n]: ");
	    	scanf(" %s", &perguntaDisciplina);
	    	
	    	if(perguntaDisciplina != 's' && perguntaDisciplina != 'n') {
	    		caracterCorreto  = false;
			} else {
				caracterCorreto =  true;
			}
		} while(!caracterCorreto);
	        
		if(perguntaDisciplina == 's') {
			boolDisciplina = true;
		} else {
			boolDisciplina =  false;
			indexDisciplina = 0;
		}
	
		indexDisciplina++;	
	} while(boolDisciplina); // do while vai repetir at� a resposta do usu�rio for != 's' ( false )
    
    if (*alunosGeral == NULL) {
        *alunosGeral = nvAluno;
    } else {
    	
        Dados* auxiliarAluno = *alunosGeral;
        while (auxiliarAluno->prox != NULL) {
            auxiliarAluno = auxiliarAluno->prox;
        }
        
        auxiliarAluno->prox = nvAluno;
    }
}


void cadastroDisciplina(Dados * aluno, char nomeDisciplina[25]) {
	
    Disciplina * nvDisciplina = (Disciplina*) malloc(sizeof(Disciplina)); // aloca��o din�mica - DISCIPLINA
    strcpy(nvDisciplina->nomeDisciplina, nomeDisciplina); // copiando o nome da disciplina
    
    if (aluno->inicioDisciplina == NULL) { // Se .iniciodisciplina (presente na struct) for NULL 
        aluno->inicioDisciplina = nvDisciplina;
    } else { // else vai rodar quando digitar a partir da segunda disciplina (question [s/n])
        Disciplina* auxiliarDiscipl = aluno->inicioDisciplina;
        
        while (auxiliarDiscipl->prox != NULL) { // enquanto o usu�rio quiser digitar mais disciplinas...
            auxiliarDiscipl = auxiliarDiscipl->prox;
        }
        
        auxiliarDiscipl->prox = nvDisciplina;
    }

}

Dados * procurarAlunoRGM(Dados * alunosGeral, int rgm) {
    Dados* aux = alunosGeral;
    while (aux != NULL) {
        if (aux->rgm == rgm) {
            return aux;
        }
    	aux = aux->prox;
	}
	return NULL;
}

void mostrarTodosAlunos(Dados * alunosGeral) {
    
    Dados * auxiliarAluno = alunosGeral;
	
	int i = 0, j = 0;
	printf("\n----- LISTA DOS ALUNOS CADASTRADOS -----\n");
    while (auxiliarAluno != NULL) { // o while vai rodar at� n�o tiver mais aluno
    	
    	printf("\n\t******* %d ALUNO *******\n", i + 1);
    	i++;
    	printf("RGM: %d\n",  auxiliarAluno->rgm);
    	
		if (auxiliarAluno->inicioDisciplina == NULL) {
            printf("\n[ERRO] Voc� n�o possui disciplina no nosso sistema!\n");
        } else {
        	
    		Disciplina* auxiliarDisciplina = auxiliarAluno->inicioDisciplina;
    		j = 0;
	        while (auxiliarDisciplina != NULL) {
	            printf("- Disciplina %d: %s\n", j + 1, auxiliarDisciplina->nomeDisciplina);
	            auxiliarDisciplina = auxiliarDisciplina->prox;
	            j++;
	        }
		}
		
		auxiliarAluno = auxiliarAluno->prox;
    }

}


void removerAlunoRGM(Dados ** alunosGeral, int rgm) {
	
	Dados * atual = *alunosGeral;
	Dados * anterior = NULL;

	while (atual != NULL && atual->rgm != rgm) { // o while vai at� achar o aluno com o RGM que o usu�rio digitou
	    anterior = atual;
	    atual = atual->prox;
	}
	
	if (atual != NULL) { // Se achou o aluno
	    if (anterior == NULL) { // primeira posi��o
	        *alunosGeral = atual->prox;
	    } else { // qualquer posi��o
	        anterior->prox = atual->prox;
	    }
	    
	    printf("\n\t\tSUCESSO!\n");
	    printf("---> REMOVEMOS O ALUNO DE RGM %d <---\n", rgm);
	} else { // se der NULL:
		printf("\nERRO!\n");
	    printf("N�o conseguimos encontrar o aluno de RGM %d. Tente novamente.\n", rgm);
	}
}

int main() {
	
	setlocale(LC_ALL, "Portuguese");
	
	Dados* alunosGeral = NULL; // aqui est� uma lista vazia
	
	// vari�veis
	int opcaoUsuario = 0;
	int i = 0, j = 0;
	int rgm, buscaRGM, removerRGM;
	
	// menu e switch-case
	while(opcaoUsuario != 5) {
		
		menu(); // menu com as op��es
		printf("\nInforme a op��o desejada: ");
		scanf("%d", &opcaoUsuario);
		
		switch(opcaoUsuario) { // switch-case nesse caso se torna mais organizado e clean.
			
			case 1:
				printf("\n------- CADASTRO %d ALUNO -------\n", i + 1);
				printf("Informe o RGM: ");
	    		scanf("%d", &rgm);
				i++;
				cadastroAluno(&alunosGeral, rgm, i);
				break;
				
			case 2:

				printf("\nInforme o RGM do aluno que deseja procurar: ");
				scanf("%d", &buscaRGM);
	
				Dados* alunoBuscado = procurarAlunoRGM(alunosGeral, buscaRGM);
				if (alunoBuscado != NULL) {
					
				    printf("\n\tO ALUNO FOI ACHADO!\n");
				    printf("SEGUE OS DADOS DO ALUNO:\n");
				    printf("*RGM: %d\n", alunoBuscado->rgm);
				    
				    if (alunoBuscado->inicioDisciplina == NULL) {
				        printf("Nenhuma disciplina cadastrada.\n");
				    } else {
				        Disciplina* auxDisciplina = alunoBuscado->inicioDisciplina;
				        while (auxDisciplina != NULL) {
				        	printf("- Disciplina %d: %s\n", j + 1, auxDisciplina->nomeDisciplina);
		            		j++;
				            auxDisciplina = auxDisciplina->prox;
				        }
				        printf("\n");
				    }
				    
				} else { // se a alunoBuscado retornar NULL quer dizer que o aluno n�o foi encontrado
					printf("Aluno N�O encontrado. Verifique se inseriu o RGM correto.\n");
				}
				
				break;
				
			case 3:
				mostrarTodosAlunos(alunosGeral);
				break;
				
			case 4:
				
				printf("\nInforme qual o RGM do aluno que deseja remover: ");
				scanf("%d", &removerRGM);
				
				removerAlunoRGM(&alunosGeral, removerRGM);
				break;
				
			case 5:
				printf("\nPROGRAMA ENCERRADO.\n");
				break;
				
			default:
				printf("\nOp��o inv�lida. Digite uma op��o v�lida!\n");
		}
		
	}
	
	return 0;
}
