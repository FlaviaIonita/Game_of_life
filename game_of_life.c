#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALIVE 'X'
#define DEAD '+'

struct c
{
    int l,c;
    struct c *next;
};
typedef struct c cell;

struct g
{
    int nr;
    cell* list_ch;
    struct g *next;
};
typedef struct g generation;

struct cc
{
    int l, c;
};
typedef struct cc cell_coord;

struct gr
{
    int** a;
    cell_coord* c_coord;
    int size;
};
typedef struct gr graph;

struct n
{
    char** table;
    cell* changes;
    struct n* left;
    struct n* right;
};
typedef struct n Node;

cell* create_cell(int l, int c)
{
    cell* newcell = (cell*)malloc(sizeof(cell));
    newcell->c = c;
    newcell->l = l;
    newcell->next = NULL;
    return newcell;
}

generation* create_generation(int nr)
{
    generation* gen = (generation*)malloc(sizeof(generation));
    gen->nr = nr;
    gen->list_ch = NULL;
    gen->next = NULL;
    return gen;
}

void push_list_sc(cell** head, int l, int c)
{
    cell* newcell = create_cell(l, c);
    if ( (*head) == NULL ||  l < (*head)->l || ( l == (*head)-> l && c < (*head)->c))
    {
        newcell->next = (*head);
        (*head) = newcell;
        return;
    }
    cell* aux = *head;
    while (aux->next && (aux->next->l < l || (aux->next->l == l && aux->next->c < c)))
        aux = aux->next;
    newcell->next = aux->next;
    aux->next = newcell;
}

void push_generation(generation** top, int nr, cell* list_ch)
{
    generation* newgen = create_generation(nr);
    newgen->list_ch = list_ch;
    newgen->next = (*top);
    (*top) = newgen;
}

void free_generations(generation *top)
{
    while(top)
    {
        cell* c = top->list_ch;
        while(c)
        {
            cell* aux1 = c;
            c = c->next;
            free(aux1);
        }
        generation * aux2 = top;
        top = top->next;
        free(aux2);
    }
}

void print_generation(FILE* output_file, generation* top)
{
    generation* gens[1000];
    int cnt = 0, i;
    while(top)
    {
        gens[cnt++] = top;
        top = top->next;
    }
    for( i = cnt-1; i >= 0; i-- )
    {
        fprintf(output_file, "%d", gens[i]->nr);
        cell *c = gens[i]->list_ch;
        while(c)
        {
            fprintf(output_file, " %d %d", c->l, c->c);
            c = c->next;
        }
        fprintf(output_file,"\n");
    }
}

char** create_table(int N, int M)
{
    int i;
    char** table = (char**) malloc(N * sizeof(char*));
    if (table == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    for (i = 0; i < N; i++)
    {
        table[i] = (char*) malloc(M * sizeof(char));
        if (table[i] == NULL)
        {
            printf("Memory allocation failed");
            return 0;
        }
    }
    return table;
}

int countAliveNeighbors(char **table, int N, int M, int i, int j)
{
    int cont = 0;
    if(i>0 && j>0 && table[i-1][j-1] == ALIVE)
        cont++;
    if(i>0 && table[i-1][j] == ALIVE)
        cont++;
    if(i>0 && j<M-1 && table[i-1][j+1] == ALIVE)
        cont++;
    if(j>0 && table[i][j-1] == ALIVE)
        cont++;
    if(j<M-1 && table[i][j+1] == ALIVE)
        cont++;
    if(i<N-1 && j>0 && table[i+1][j-1] == ALIVE)
        cont++;
    if(i<N-1 && table[i+1][j] == ALIVE)
        cont++;
    if(i<N-1 && j<M-1 && table[i+1][j+1] == ALIVE)
        cont++;
    return cont;
}

void print_table(FILE *output_file, char** table, int N, int M)
{
    int i, j;
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < M; j++)
            fprintf(output_file, "%c", table[i][j]);
        fprintf(output_file,"\n");
    }
}

void free_memory_table(char** table, int N)
{
    int i;
    for(i = 0; i < N; i++)
        if(table[i] != NULL)
            free(table[i]);
    if(table != NULL)
        free(table);
}

void game_of_life_task1(char** table, int N, int M)
{
    int i, j, cont;
    char** NewTable = create_table(N, M);
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
        {
            cont = countAliveNeighbors(table, N, M, i, j);
            if(table[i][j] == ALIVE)
            {
                if(cont < 2 || cont > 3)
                    NewTable[i][j] = DEAD;
                else
                    NewTable[i][j] = ALIVE;
            }
            else
            {
                if(cont == 3)
                    NewTable[i][j] = ALIVE;
                else
                    NewTable[i][j] = DEAD;
            }
        }
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            table[i][j] = NewTable[i][j];
    free_memory_table(NewTable, N);
}

void game_of_life_task2(char** table, int N, int M, generation** top, int gen_nr)
{
    int i, j, cont;
    char** NewTable = create_table(N, M);
    cell* changes = NULL;

    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
        {
            cont = countAliveNeighbors(table, N, M, i, j);
            if(table[i][j] == ALIVE)
            {
                if(cont < 2 || cont > 3)
                    NewTable[i][j] = DEAD;
                else
                    NewTable[i][j] = ALIVE;
            }
            else
            {
                if(cont == 3)
                    NewTable[i][j] = ALIVE;
                else
                    NewTable[i][j] = DEAD;
            }
            if(NewTable[i][j] != table[i][j])
                push_list_sc(&changes, i, j);
        }
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            table[i][j] = NewTable[i][j];
    push_generation(top, gen_nr, changes);
    free_memory_table(NewTable, N);
}

char** copy_table(char** t1, int N, int M)
{
    int i, j;
    char** t2 = create_table(N, M);
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            t2[i][j] = t1[i][j];
    return t2;
}


void rule_b(char** table, int N, int M, char** newTable, cell** changes)
{
    int i, j, cont;
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
        {
            cont = countAliveNeighbors(table, N, M, i, j);
            if(cont == 2)
                newTable[i][j] = ALIVE;
            else
                newTable[i][j] = table[i][j];

            if(newTable[i][j] != table[i][j])
                push_list_sc(changes, i, j);
        }
}

Node* game_of_life_task3(char** table, int N, int M, int c_gen, int max_gen)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->table = copy_table(table, N, M);
    node->left = node->right = NULL;
    node->changes = NULL;

    if(c_gen == max_gen)
        return node;

    char** tb = create_table(N, M);
    cell* changesB = NULL;
    rule_b(table, N, M, tb, &changesB);
    node->left = game_of_life_task3(tb, N, M, c_gen + 1, max_gen);
    node->left->changes = changesB;
    free_memory_table(tb, N);

    char** ts = create_table(N, M);
    cell* changesS = NULL;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < M; j++)
        {
            int cont = countAliveNeighbors(table, N, M, i, j);
            if(table[i][j] == ALIVE)
            {
                if(cont < 2 || cont > 3)
                    ts[i][j] = DEAD;
                else
                    ts[i][j] = ALIVE;
            }
            else
            {
                if(cont == 3)
                    ts[i][j] = ALIVE;
                else
                    ts[i][j] = DEAD;
            }

            if (ts[i][j] != table[i][j])
                push_list_sc(&changesS, i, j);
        }
    node->right = game_of_life_task3(ts, N, M, c_gen + 1, max_gen);
    node->right->changes = changesS;
    free_memory_table(ts, N);

    return node;
}

void preorder_write(FILE* output_file, Node* root, int N, int M)
{
    if (!root) return;
    print_table(output_file, root->table, N, M);
    fprintf(output_file, "\n");
    preorder_write(output_file, root->left, N, M);
    preorder_write(output_file, root->right, N, M);
}

void free_tree(Node* root, int N)
{
    if (!root) return;
    free_memory_table(root->table, N);
    cell* c = root->changes;
    while (c)
    {
        cell* aux = c;
        c = c->next;
        free(aux);
    }
    free_tree(root->left, N);
    free_tree(root->right, N);
    free(root);
}

int neighbors(cell_coord x, cell_coord y)
{
    return abs(x.l - y.l) <= 1 && abs(x.c - y.c) <= 1 && !(x.l == y.l && x.c == y.c);
}

graph build_graph(char** table, int N, int M)
{
    int i,j;
    graph g;
    g.size = 0;
    int capacity = N * M;
    g.c_coord = (cell_coord*)malloc(capacity * sizeof(cell_coord));
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (table[i][j] == ALIVE)
                g.c_coord[g.size++] = (cell_coord){i,j};
    g.c_coord = realloc(g.c_coord, g.size * sizeof(cell_coord));
    g.a = (int**)malloc(g.size * sizeof(int*));
    for (i = 0; i < g.size; i++)
    {
        g.a[i] = (int*)calloc(g.size, sizeof(int));
        for (j = 0; j < g.size; j++)
            if (i != j && neighbors(g.c_coord[i], g.c_coord[j]))
                g.a[i][j] = 1;
    }

    return g;
}

void free_graph(graph* g)
{
    for (int i = 0; i < g->size; i++)
        free(g->a[i]);
    free(g->a);
    free(g->c_coord);
}

void dfs(graph* g, int node, int depth, int* visited, cell_coord* curr, cell_coord* best, int* max_len)
{
    visited[node] = 1;
    curr[depth] = g->c_coord[node];
    if (depth > *max_len)
    {
        *max_len = depth;
        for (int i = 0; i <= depth; i++)
            best[i] = curr[i];
    }
    int remaining = g->size - depth - 1;
    if (depth + remaining <= *max_len)
    {
        visited[node] = 0;
        return;
    }
    for (int i = 0; i < g->size; i++)
    {
        if (!visited[i] && g->a[node][i])
        {
            dfs(g, i, depth + 1, visited, curr, best, max_len);
        }
    }
    visited[node] = 0;
}


void find_longest_path(FILE* output_file, graph* g)
{
    if (g->size == 0)
    {
        fprintf(output_file, "-1\n");
        return;
    }
    int* visited = calloc(g->size, sizeof(int));
    cell_coord* current = malloc(g->size * sizeof(cell_coord));
    cell_coord* best = malloc(g->size * sizeof(cell_coord));
    int max_len = -1;
    for (int i = 0; i < g->size; i++)
        dfs(g, i, 0, visited, current, best, &max_len);

    if (max_len == -1)
        fprintf(output_file, "-1\n");
    else
    {
        fprintf(output_file, "%d\n", max_len );
        for (int i = 0; i <= max_len; i++)
            fprintf(output_file, "(%d,%d) ", best[i].l, best[i].c);
        fprintf(output_file, "\n");
    }
    free(visited);
    free(current);
    free(best);
}

void preorder_longest_path(Node* root, int N, int M, FILE* output_file)
{
    if (!root) return;
    graph g = build_graph(root->table, N, M);
    find_longest_path(output_file, &g);
    free_graph(&g);

    preorder_longest_path(root->left, N, M, output_file);
    preorder_longest_path(root->right, N, M, output_file);
}

//bonus
void undo_generations(char** table, int N, int M, generation* top)
{
    generation* gens[1000];
    int cnt = 0, i;
    while(top)
    {
        gens[cnt++] = top;
        top = top->next;
    }
    for(i = 0; i < cnt; i++)
    {
        cell* c = gens[i]->list_ch;
        while(c)
        {
            int col = c->c, lin = c->l;
            if(table[lin][col] == ALIVE)
                table[lin][col] = DEAD;
            else table[lin][col] = ALIVE;
            c = c->next;
        }
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }
    FILE *input_file = fopen(argv[1], "r");
    FILE *output_file = fopen(argv[2], "w");
    if (input_file == NULL || output_file == NULL)
    {
        printf("Files couldn't open\n");
        if (input_file != NULL) fclose(input_file);
        if (output_file != NULL) fclose(output_file);
        return 0;
    }

    int T, N, M, K, i, j;
    fscanf(input_file, "%d", &T);
    fscanf(input_file, "%d", &N);
    fscanf(input_file, "%d", &M);
    fscanf(input_file, "%d", &K);
   
    if(T == 1 || T == 2 || T == 3 || T == 4)
    {
    char **table = create_table(N, M);
    for(i = 0; i < N; i++)
        for(j = 0; j < M; j++)
            fscanf(input_file, " %c", &table[i][j]);
    //task1
    if( T == 1 )
    {
        print_table(output_file, table, N, M);
        fprintf(output_file, "\n");
        while(K)
        {
            game_of_life_task1(table,N,M);
            print_table(output_file,table,N,M);
            fprintf(output_file,"\n");
            K--;
        }
    }
    //task2
    if( T == 2 )
    {
        generation *top = NULL;
        for( i = 1; i <= K; i++ )
            game_of_life_task2(table, N, M, &top, i);
        print_generation(output_file, top);
        free_generations(top);
    }
    //task3
    if (T == 3)
    {
        Node* root = game_of_life_task3(table, N, M, 0, K);
        preorder_write(output_file, root, N, M);
        free_tree(root, N);
    }
    //task4
    if (T == 4)
     {
         Node* root = game_of_life_task3(table, N, M, 0, K);
         preorder_longest_path(root, N, M, output_file);
         free_tree(root, N);
     }
     free_memory_table(table,N);
    }
    //task bonus
    if(T == 5)
    {
        generation *top = NULL;
        char line[1024];
        fgets(line, sizeof(line), input_file);

        for(i = K; i >= 1; i--)
        {
            if(!fgets(line, sizeof(line), input_file)) break;
            int gen;
            char* aux = strtok(line," ");
            if(!aux) continue;
            gen  = atoi(aux);
            cell* changes = NULL;
            while((aux = strtok(NULL," ")) != NULL)
            {
                int l, c;
                l = atoi(aux);
                aux = strtok(NULL," ");
                if(!aux) break;
                c = atoi(aux);
                push_list_sc(&changes, l, c);
            }
            push_generation(&top, gen, changes);
        }
        char** tb = create_table(N,M);
        for(i = 0; i < N; i++)
            for(j = 0; j < M; j++)
                fscanf(input_file, " %c", &tb[i][j]);
        undo_generations(tb, N, M, top);
        print_table(output_file, tb, N, M);
        free_generations(top);
        free_memory_table(tb, N);
        
    }
    fclose(input_file);
    fclose(output_file);
    
    return 0;
}
