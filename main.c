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

}dic;

typedef struct Information_of_Students{
    char        RGM[9];
    dic   list_of_dicipline;


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
