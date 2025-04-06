#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#define     TAM 1

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
    printf("Utilize os �ndices [x] para poder acessar as funcionalidade!\n");
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
    int                 RGM;
    diciplines          *initial;


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

int isFull(Info *Students){
    return Students->position+1 == TAM;
}

int isEmpty(Info *Students){
    return Students->position == -1;

}

void insertSortRGM(Info *Students){

    int i, j;
    students atual;

    for(i = 1; i <= Students->position; i++){
        atual = Students->College[i];

        j = i - 1;
        while((j >= 0) && (atual.RGM < Students->College[j].RGM)){
           Students->College[j + 1] = Students->College[j];
           j--;

        }
        Students->College[j + 1] = atual;

    }
}

void inserct_student(Info *Students){

    int answer;

    // Atualizando a posi��o do ultimo cadastro realizado:
    Students->position++;
    int pos = Students->position;

    // Inserindo o RGM:
    // Tratamento do RGM;
    while(true){
        int RGM;
        printf("Digite o RGM do usu�rio: ");

        if(scanf("%d", &RGM) != 1){
            limpar_tela();
            printf("RGM Inv�lido! O formato padr�o � com n�meros...\n");
            linhas();
        }else if(RGM > 99999999 || RGM < 0){
            limpar_tela();
            printf("RGM Inv�lido! O valor inserido excedeu o limite de 9 digitos...\n");
            linhas();
        }else{
            Students->College[pos].RGM = RGM;
            break;
        }
        fflush(stdin);
    }
    fflush(stdin);
    // Como iremos criar uma lista encadeada para adicionar na lista de disciplinas
    // Precisamo definir um aonde essa lista ir� come�ar (initial.

    Students->College[pos].initial = NULL;

    // Definimos um ponteiro para auxiliar no encadeamento das disciplinas
    diciplines *aux_ptr;

    // Inserindo as diciplinas do usu�rio
    while(true){

        // Criando um novo local aonde ser� adicionado uma disciplina e alocando mem�ria para suporta-lo.
        diciplines *new_node = (diciplines *) malloc(sizeof(diciplines));

        // Solicitando o nome da disciplina que o usu�rio deseja e armazenando na vari�vel "new_node".
        printf("Digite o nome de uma disciplina: ");
        fgets(new_node->name_of_dicipline, 255, stdin);

        // Na teoria, se um elemento est� sendo inserindo em uma lista encadeada ent�o ele � o �ltimo,
        // logo ele estar� apontando para NULL que indica o fim da lista.

        new_node->next_dicipline = NULL;

        // Se a vari�vel initial � igual a NULL, ent�o o new_node � o primeiro n� da lista

        if(Students->College[pos].initial == NULL){
            Students->College[pos].initial= new_node;
            aux_ptr = new_node;

        }else {
            aux_ptr->next_dicipline = new_node;
            aux_ptr = new_node;
        }

        linhas();
        while(true){
            printf("Voc� deseja adicionar mais uma disciplina? [1 - Sim][0 - N�o]: ");
            if(scanf("%d", &answer) != 1){
                limpar_tela();
                printf("Op��o Inv�lida! Tente Novamente...\n");
                linhas();
                fflush(stdin);
            }else{
                if(answer == 0 || answer == 1){
                    break;
                }else{
                    limpar_tela();
                    printf("Op��o Inv�lida! Tente Novamente...\n");
                    linhas();
                }

            }
        }

        fflush(stdin);
        if (answer == 0){
            break;
        }
    }

    limpar_tela();
    linhas();
    insertSortRGM(&*Students);
    printf("Usu�rio inserido com sucesso!\n");

}

void remove_student(Info *Students){

    int RGM;

    printf("Digite o RGM do usu�rio que ser� removido: ");
    scanf("%d", &RGM);

    int size_of_list = Students->position+1;
    int pos;
    bool found = false;

    // Procura o RGM solicitado para remo��o e guarda sua posi��o:

    for(int i = 0; i < size_of_list; i++){
        if(RGM == Students->College[i].RGM){
            pos = i;
            found = true;
            break;
        }
    }

    if(!found){
        limpar_tela();
        linhas();
        printf("Usu�rio N�o foi encontrado!\n");

    }else{

        // Liberando os espa�os de mem�ria alocados para armazenar as disciplinas:

        diciplines *current = Students->College[pos].initial;
        while (current != NULL) {
            diciplines *temp = current->next_dicipline;
            free(current);
            current = temp;
        }
        Students->College[pos].initial = NULL;

        // Retirando da lista Sequencial o usu�rio solicitado:

        for(int i = pos; i < size_of_list; i++){
            Students->College[i] = Students->College[i + 1];
            }

        limpar_tela();
        linhas();
        printf("Usu�rio removido com sucesso!\n");
        Students->position--;
    }
}

void show_students(Info *Students){

    printf("Usu�rios Cadastrados em nosso Sistema:\n");
    linhas();
    int size_of_list = Students->position + 1;

    for(int i = 0; i < size_of_list; i++){

        printf("%d. RGM: %d \n", i+1,Students->College[i].RGM);

        diciplines *current = Students->College[i].initial;
        while(current != NULL){
            printf("  Disciplina: %s", current->name_of_dicipline);
            current = current->next_dicipline;
        }
        if(i < size_of_list-1){
            linhas();
        }
    }
    system("pause");
    limpar_tela();
}

void search_students(Info *Students){

    int RGM;

    printf("Digite o RGM do aluno que deseja encontrar: ");
    scanf("%d", &RGM);

    int size_of_list = Students->position +1;
    bool found = false;
    limpar_tela();

    for(int i = 0; i < size_of_list; i++){
        if (RGM == Students->College[i].RGM){
            found = true;
            printf("Aluno Encontrado:\n");
            linhas();
            printf("%d. RGM: %d\n", i+1, Students->College[i].RGM);

            diciplines *current = Students->College[i].initial;
            while(current != NULL){
                    printf("  Disciplina: %s", current->name_of_dicipline);
                    current = current->next_dicipline;
            }

            break;
        }
    }
     if(!found){
            limpar_tela();
            printf("Aluno com o RGM %d, n�o foi encontrado!\n",RGM);
        }

}

int main(){
    setlocale(LC_ALL,"");

    Info Students = create_list();
    int choice = -1;

    while(true){

        cabecalho();
        printf("Digite uma op��o acima: ");

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
                    linhas();

                    if(isFull(&Students)){
                        printf("Lista Cheia! N�o h� como acessar essa funcionalidade...\n");

                    }else{
                        inserct_student(&Students);
                    }

                    break;
                case 2:
                    printf("[2] - Mostrar Alunos;\n");
                    linhas();

                    if(isEmpty(&Students)){
                        printf("Lista Vazia! N�o h� como acessar essa funcionalidade...\n");

                    }else{
                        show_students(&Students);
                    }

                    break;
                case 3:
                    printf("[3] - Procurar Aluno por RGM;\n");
                    linhas();

                    if(isEmpty(&Students)){
                        printf("Lista Vazia! N�o h� como acessar essa funcionalidade...\n");

                    }else{
                        search_students(&Students);
                    }

                    break;
                case 4:
                    printf("[4] - Remover Aluno por RGM;\n");
                    linhas();

                    if(isEmpty(&Students)){
                        printf("Lista Vazia! N�o h� como acessar essa funcionalidade...\n");

                    }else{
                        remove_student(&Students);
                    }

                    break;
                case 0:
                    printf("[0] - Sair;\n");
                    linhas();

                    printf("Obrigado por Utilizar nosso programa!\n");

                    break;
                default:
                    printf("Op��o fora do intervalo, tente novamente...\n");
                    break;

            }

        }
        if(choice == 0){
            break;
        }

    }

    return 0;

}
