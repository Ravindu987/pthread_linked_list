#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int thread_count;
int n;
int16_t m;
float m_member, m_insert, m_delete;

int16_t RandomIntegerGenerator();

struct list_node_s {
    int data;
    struct list_node_s* next;
};

int main(int argc, char* argv[]){
    long thread;
    pthread_t* thread_handles;
    clock_t start_time, end_time;
    double cpu_time_used;

    srand(time(NULL));

    n = strtol(argv[1], NULL, 10);
    m = strtol(argv[2], NULL, 10);
    m_member = strtod(argv[3], NULL);
    m_insert = strtod(argv[4], NULL);
    m_delete = strtod(argv[5], NULL);

    int num_member = m*m_member;
    int num_insert = m*m_insert;
    int num_delete = m*m_delete;

    struct list_node_s* head_p = malloc(sizeof(struct list_node_s));
    Populate(head_p, n);

    start_time = clock();

    for (int i=0; i<num_member; i++){
        Member(RandomIntegerGenerator(), head_p);
    }

    for (int i=0; i<num_insert; i++){
        Insert(RandomIntegerGenerator(), &head_p);
    }

    for (int i=0; i<num_delete; i++){
        Delete(RandomIntegerGenerator(), &head_p);
    }

    end_time = clock();

    cpu_time_used = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    printf(" Start to End Duration (CPU): %f s\n", cpu_time_used);

    return 0;
}

void Populate(struct list_node_s* head_p, int n) {
    int i = 0;
    
    while(i < n-1){
        int16_t value = RandomIntegerGenerator();
        if (Member(value, head_p)){
            continue;
        }
        Insert(value, &head_p);
        i++;
    }
}

void Display(struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;
    int i=0;
    while (curr_p != NULL){
        printf("Node %d: %d\n", i, curr_p->data);
        i++;
        curr_p = curr_p->next;
    }
}

int Member(int value, struct list_node_s* head_p) {
    struct list_node_s* curr_p = head_p;

    while (curr_p != NULL && curr_p->data < value){
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value){
        return 0;
    } else {
        return 1;
    }
}

int Insert(int value, struct list_node_s** head_pp) {
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;
    struct list_node_s* temp_p;

    while (curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p == NULL || curr_p->data > value){
        temp_p = malloc(sizeof(struct list_node_s));
        temp_p->data = value;
        temp_p->next = curr_p;
        if (pred_p == NULL){
            *head_pp = temp_p;
        } else {
            pred_p->next = temp_p;
        }
        return 1;
    } else {
        return 0;
    }
}

int Delete(int value, struct list_node_s** head_pp) {
    struct list_node_s* curr_p = *head_pp;
    struct list_node_s* pred_p = NULL;

    while (curr_p != NULL && curr_p->data < value){
        pred_p = curr_p;
        curr_p = curr_p->next;
    }

    if (curr_p != NULL && curr_p->data == value){
        if (pred_p == NULL){
            *head_pp = curr_p->next;
        } else {
            pred_p->next = curr_p->next;
        }
        free(curr_p);
        return 1;
    } else {
        return 0;
    }
}

int16_t RandomIntegerGenerator() {
    int16_t max_value = __INT16_MAX__;
    int16_t value = rand() % (max_value + 1);
    return value;
}