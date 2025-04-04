#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>

typedef struct number_content{
    int     num;
    struct  numbers *next_number;

}num_cont;

typedef struct list_of_numbers{

    num_cont     *list_of_numbers;
    num_cont     *initial;


}num_list;


num_list create_list(){

    num_list     num_list;
    num_list.list_of_numbers = NULL;
    num_list.initial = NULL;

    return num_list;
}



int main(){
    setlocale(LC_ALL, "");

    num_list num_list = create_list();

    int answer;
    num_cont *aux_ptr;


    while(true){

            num_cont *new_node = (num_cont *) malloc(sizeof(num_cont));

            printf("Digite um número: ");
            scanf("%d", &new_node->num);
            fflush(stdin);

            new_node->next_number = NULL;

            if(num_list.initial == NULL){
                num_list.initial = new_node;
                aux_ptr = new_node;

            }else{
                aux_ptr->next_number = (num_cont *) new_node;
                aux_ptr = new_node;
            }

            printf("Você deseja adicionar algum número? [1 - Sim] [0 - Não]");
            scanf("%d", &answer);

            if(answer == 0){
                break;
            }

    }

    num_list.list_of_numbers = num_list.initial;

    num_cont *current = (num_cont*) num_list.list_of_numbers;

            while (current != NULL) {
                printf("%d \n", current->num);
                current = current->next_number;
            }


    return 1;
}
