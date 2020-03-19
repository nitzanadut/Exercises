typedef struct Node {
    int value;
    struct Node *next;
    struct Node *last;
} Node;

typedef struct List {
    Node *head;
    Node *tail;
    int length;
    int sum;
} List;

List init();
void destroy(List *list);
void append(List *list, Node *node);
int delete(List *list, Node *node);
int get_length(List *list);
Node *get_head(List *list);
Node *get_tail(List *list);
Node *get_next(Node *node);
Node *get_last(Node *node);
int get_value(Node *node);
float get_avg(List *list);