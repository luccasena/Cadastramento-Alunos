#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#define     TAM 60

void linhas(){
    printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}

void cabecalho(){

    linhas();
    printf("------ Lista de Alunos ------\n");
    linhas();
    printf("[1] - Realizar Cadastro;\n");
    printf("[2] - Mostrar Alunos;\n");
    printf("[3] - Procurar Aluno por RGM;\n");
    printf("[4] - Remover Aluno por RGM;\n");
    printf("[0] - Sair;\n");
    linhas();
    printf("Utilize os índices [x] para poder acessar as funcionalidade!\n");
    linhas();

}

void limpar_tela(){
    // Esta funcionalidade funciona corretamente no Windows
    system("cls");
}

typedef struct diciplines{
    char name_of_dicipline[255];
    struct diciplines *next_dicipline;

}diciplines;

typedef struct Information_of_Students{
    char                RGM[9];
    diciplines          *list_of_dicipline;


}students;

typedef struct College{
    students    College[TAM];
    int         position;

}Info;

Info create_list(){

    Info college;
    college.position = -1;

    return college;
}

int inserct_student(Info *Students){
    int answer;

    // Atualizando a posição do ultimo cadastro realizado:
    Students->position++;

    // Inserindo o RGM:
    printf("Digite o RGM do usuário: ");
    scanf("%s", Students->College[Students->position].RGM);
    fflush(stdin);

    // Como iremos criar uma lista encadeada para adicionar na lista de disciplinas
    // Precisamo definir um aonde essa lista irá começar (initial) e aonde irá terminar (final_list).

    diciplines *initial = NULL;
    diciplines *final_list = NULL;

    // Inserindo as diciplinas do usuário
    while(true){
        // Criando um novo local aonde será adicionado uma disciplina e alocando memória para suporta-lo.
        diciplines *new_node = (diciplines *) malloc(sizeof(diciplines));

        // Solicitando o nome da disciplina que o usuário deseja e armazenando na variável "new_node".
        printf("Digite o nome de uma disciplina: ");
        fgets(new_node->name_of_dicipline, 255, stdin);

        // Na teoria, se um elemento está sendo inserindo em uma lista encadeada então ele é o último,
        // logo ele estará apontando para NULL que indica o fim da lista.

        new_node->next_dicipline = NULL;

        // Se a variável initial é igual a NULL

        if(initial == NULL){
            initial = new_node;
            final_list = new_node;

        }else{
            final_list->next_dicipline = new_node;
            final_list = new_node;
        }

        printf("Você deseja adicionar mais uma disciplina?: ");
        scanf("%d", &answer);
        fflush(stdin);
        if (answer == 0){
            break;
        }
    }
    Students->College[Students->position].list_of_dicipline = initial;

    printf("Aluno: %s\nPosição: %d\n\n", Students->College[Students->position].RGM, Students->position);

    diciplines *current = Students->College[Students->position].list_of_dicipline;
    while (current != NULL) {
        printf("Disciplina: %s", current->name_of_dicipline);
        current = current->next_dicipline;
    }

    return 1;
}

int main(){
    setlocale(LC_ALL,"");

    Info Students = create_list();
    int choice;

    while(true){

        cabecalho();
        printf("Digite uma opção acima: ");
        if(scanf("%d", &choice) != 1){
            limpar_tela();
            linhas();
            printf("Erro tente novamente...\n");
            fflush(stdin);
        }else{
            limpar_tela();
            linhas();
            switch(choice){
                case 1:
                    printf("[1] - Realizar Cadastro;\n");

                    inserct_student(&Students);
                    limpar_tela();
                    linhas();
                    printf("Usuário inserido com sucesso!\n");


                    break;
                case 2:
                    printf("[2] - Mostrar Alunos;\n");

                    break;
                case 3:
                    printf("[3] - Procurar Aluno por RGM;\n");

                    break;
                case 4:
                    printf("[4] - Remover Aluno por RGM;\n");

                    break;
                case 0:

                    break;
                default:
                    printf("Opção fora do intervalo, tente novamente...\n");
                    break;

            }

        }

    }

    return 0;
}
