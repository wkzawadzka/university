#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// structs
struct student_person {
    char name[100];
    char surname[100];
    int index;
};

struct list_node {
    int index;
    struct list_node *next;
};
struct list_node *head = NULL;

struct BST_node {
    int index;
    struct BST_node *left;
    struct BST_node *right;
};
struct BST_node *head_BST = NULL;

struct BBST_node {
    int index;
    struct BBST_node *left;
    struct BBST_node *right;
};
struct BBST_node *head_BBST = NULL;

// global variables
int n;
char *FILENAME = "input_shuffled.csv";
struct student_person *students;
struct list_node *student;
struct BST_node *student_BST;
// struct BBST_node *student_BBST;

int *indexes;

/*------------------------------------ table -------------------------------------- */
void table_create(FILE *my_file, struct student_person records[], int len) {
    int i, fields;
    for (i = 0; i < len; i++) {
        fields = fscanf(my_file, "%[A-Za-z],%[A-Za-z],%d\n", &records[i].name, &records[i].surname, &records[i].index);
        indexes[i] = records[i].index;
        if (fields != 3)
            break;
    }
}

void shuffle_indexes(int *a, int len) {
    int i, random;
    for (i = len - 1; i > 0; i--) {
        random = rand() % (i + 1);
        int temp = a[i];
        a[i] = a[random];
        a[random] = temp;
    }
}
/*------------------------ dynamically ordered [linked] list ----------------------- */

void list_search(int index) {
    struct list_node *temp = head;
    while (temp != NULL) {
        if (temp->index == index) {
            return;
        }
        temp = temp->next;
    }
    printf("Student with index number %d is not found !!!\n", index);
}

void list_insert(int index) {
    student = (struct list_node *)malloc(sizeof(struct list_node));
    student->index = index;
    student->next = NULL;

    if (head == NULL || head->index >= student->index) // if there are no elements or first element is greater than the one to insert (so it need to go at the beginning)
    {
        student->next = head;
        head = student;
        return;
    } else // Locate the node before insertion
    {
        struct list_node *curr = head;
        while (curr->next != NULL && curr->next->index < student->index)
            curr = curr->next;

        student->next = curr->next;
        curr->next = student;
    }
}

void list_delete(int index) {
    struct list_node *temp1 = head;
    struct list_node *temp2 = head;
    while (temp1 != NULL) {
        if (temp1->index == index) {
            if (temp1 == temp2) {
                head = head->next;
                // free(temp1);
            } else {
                temp2->next = temp1->next;
                // free(temp1);
            }
            return;
        }
        temp2 = temp1;
        temp1 = temp1->next;
    }
    printf("Student with index number %d is not found\n", index);
}

void list_print() {
    struct list_node *temp = head;
    while (temp != NULL) {
        printf("%d\n", temp->index);
        temp = temp->next;
    }
}

void do_list_insertion(int choice, FILE *output) {
    float t;
    clock_t start, end;
    start = clock();
    int i;
    for (i = 0; i < n; i++) {
        list_insert(students[i].index); // insert data from table
    }
    end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;
    if (choice == 1) {
        printf("[1] INSERTION %f seconds\n", t / 50);
        fprintf(output, "list,%d,%f\n", n, t / 50);
    }
}

void do_list_search(int choice, FILE *output) {
    if (choice == 2) {
        int i, j;
        float t, temp_t;
        clock_t start, end;
        t = 0;
        for (j = 0; j < 10; j++) // 10 runs
        {
            shuffle_indexes(indexes, n);
            for (i = 0; i < n; i++) {
                int random_index = indexes[i];
                start = clock();
                list_search(random_index);
                end = clock();
                temp_t = (float)(end - start) / CLOCKS_PER_SEC;
                t = t + temp_t;
            }
        }
        printf("[2] SEARCH %f seconds\n", t / (10 * n));
        fprintf(output, "list,%d,%f\n", n, t / (10 * n));
    }
}

void do_list_delete(int choice, FILE *output) {
    if (choice == 3) {
        int i;
        float tt, t;
        clock_t start, end;
        t = 0;

        shuffle_indexes(indexes, n);
        for (i = 0; i < n; i++) {
            int random_index = indexes[i];
            start = clock();
            list_delete(random_index);
            end = clock();
            tt = (float)(end - start) / CLOCKS_PER_SEC;
            t = t + tt;
        }
        printf("[3] REMOVE %f seconds\n", t);
        fprintf(output, "list,%d,%f\n", n, t);
    }
}

/*--------------------------------- binary search tree ----------------------------- */
void *BST_create_new_node(int index) {
    student_BST = (struct BST_node *)malloc(sizeof(struct BST_node));
    student_BST->index = index;
    student_BST->left = student_BST->right = NULL;
}

struct BST_node *BST_insert(struct BST_node *root, int index) {

    if (root == NULL) {
        // first element
        BST_create_new_node(index);
        root = student_BST;
    } else {
        // recursively
        if (index <= root->index) // if smaller -> left subtree
        {
            root->left = BST_insert(root->left, index);
        } else // if greater -> right subtree
        {
            root->right = BST_insert(root->right, index);
        }
    }
    return root;
}

void BST_print_preorder(struct BST_node *root) {
    if (root == NULL)
        return;

    // print R0
    printf("%d ", root->index); // Print data
    // L
    BST_print_preorder(root->left); // Visit left subtree
    // R
    BST_print_preorder(root->right); // Visit right subtree
}

void BST_print_postorder(struct BST_node *root) {
    if (root == NULL)
        return;

    // L
    BST_print_preorder(root->left); // Visit left subtree
    // R
    BST_print_preorder(root->right); // Visit right subtree
    // print R0
    printf("%d ", root->index); // Print data
}

void BST_print_inorder(struct BST_node *root) {
    if (root == NULL)
        return;

    // L
    BST_print_preorder(root->left); // Visit left subtree
    // print R0
    printf("%d ", root->index); // Print data
    // R
    BST_print_preorder(root->right); // Visit right subtree
}

void BST_search(struct BST_node *root, int index) {
    // root case
    if (root == NULL || root->index == index) {
        // printf("Index: %d\n", root->index);
        return;
    }

    // if we are looking for a greater index than is in root
    if (root->index < index)
        return BST_search(root->right, index);

    // otherwise
    return BST_search(root->left, index);
}

void do_BST_insertion(int choice, FILE *output) {
    clock_t start, end;
    float t;
    int i;
    start = clock();
    for (i = 0; i < n; i++) {
        head_BST = BST_insert(head_BST, students[i].index); // insert data from table
    }
    end = clock();
    t = (float)(end - start) / CLOCKS_PER_SEC;
    if (choice == 1) {
        printf("[1] INSERTION %f seconds\n", t / n);
        fprintf(output, "BST,%d,%f\n", n, t / n);
    }
}

void do_BST_search(int choice, FILE *output) {
    if (choice == 2) {
        srand(time(NULL));
        clock_t start, end;
        float t, temp_t;
        int i, j;
        t = 0;
        for (j = 0; j < 10; j++) // 5 runs
        {
            shuffle_indexes(indexes, n);
            for (i = 0; i < n; i++) {
                int ran_id = indexes[i];
                start = clock();
                BST_search(head_BST, ran_id);
                end = clock();
                temp_t = (float)(end - start) / CLOCKS_PER_SEC;
                t = t + temp_t;
            }
        }
        printf("[2] SEARCH %f seconds\n", t / (10 * n));
        fprintf(output, "BST,%d,%f\n", n, t / (10 * n));
    }
}

struct BST_node *getMinimumindex(struct BST_node *curr) {
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

struct BST_node *BST_delete(struct BST_node *root, int index) {
    struct BST_node *parent = NULL;
    struct BST_node *curr = root;

    // search index in the BST and set its parent pointer
    while (curr && curr->index != index) {
        // update the parent to the curr node
        parent = curr;

        // if the given index is less than the curr node, go to the left subtree;
        // otherwise, go to the right subtree
        if (index < curr->index) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    // printf("    3Starting BST delete...\n");

    // return if the index is not found in the tree
    if (curr == NULL) {
        return root;
    }
    // Case 1: node to be deleted has no children, i.e., it is a leaf node
    if (curr->left == NULL && curr->right == NULL) {

        // if the node to be deleted is not a root node, then set its
        // parent left/right child to None
        if (curr != root) {
            if (parent->left == curr) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        // if the tree has only a root node, set it to None
        else {
            root = NULL;
        }

        // deallocate the memory
        // free(curr);
    }

    // Case 2 : node to be deleted has two children
    else if (curr->left && curr->right) {
        // find its inorder successor node
        struct BST_node *successor = getMinimumindex(curr->right);

        // store successor value
        int val = successor->index;

        // recursively delete the successor. Note that the successor
        // will have at most one child (right child)
        BST_delete(root, successor->index);

        // copy value of the successor to the current node
        curr->index = val;
    }

    // Case 3: node to be deleted has only one child
    else {
        // choose a child node
        struct BST_node *child = (curr->left != NULL) ? curr->left : curr->right;

        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (curr != root) {
            if (curr == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }

        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }

        // deallocate the memory
        // free(curr);
    }
    // printf("    4Starting BST delete...\n");

    return root;
}

void do_BST_delete(int choice, FILE *output)

{
    if (choice == 3) {
        int i;
        float t, temp_t;
        clock_t start, end;
        int count, ran_id;
        t = 0;
        shuffle_indexes(indexes, i);
        for (i = 0; i < n; i++) {
            ran_id = indexes[i];
            start = clock();
            head_BST = BST_delete(head_BST, ran_id);
            end = clock();
            temp_t = (float)(end - start) / CLOCKS_PER_SEC;
            t = t + temp_t;
        }
        printf("[3] REMOVE %f seconds\n", t);
        fprintf(output, "BST,%d,%f\n", n, t);
    }
}

/*--------------------------------- balanced binary search tree ----------------------------- */

void qcsort(int *list, int start, int end) {
    int left, right, temp;
    int mid = (start + end) / 2;
    int pivot = list[mid];

    left = start;
    right = end;
    while (left <= right) {

        // Increment the start pointer till it finds an element greater than  pivot
        while (list[left] < pivot) {
            left++;
        }

        // Decrement the end pointer till it finds an element less than pivot
        while (list[right] > pivot) {
            right--;
        }

        if (left <= right) {
            temp = list[left];
            list[left] = list[right];
            list[right] = temp;
            left++;
            right--;
        }
    }

    if (start < right) {
        qcsort(list, start, right);
    }
    if (left < end) {
        qcsort(list, left, end);
    }
}

struct BBST_node *BBST_create_new_node(int index) {
    struct BBST_node *student_BBST = (struct BBST_node *)malloc(sizeof(struct BBST_node));
    student_BBST->index = index;
    student_BBST->left = student_BBST->right = NULL;
    return student_BBST;
}

struct BBST_node *BBST_insert(struct BBST_node *root, int *a, int start, int end) {
    /* Base Case */
    if (start > end)
        return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end) / 2;
    root = BBST_create_new_node(a[mid]);
    ;

    root->left = BBST_insert(NULL, a, start, mid - 1);
    root->right = BBST_insert(NULL, a, mid + 1, end);

    return root;
}

void do_BBST_insertion(int choice, FILE *output) {
    float t = 0;
    clock_t start, end;
    start = clock();
    qcsort(indexes, 0, n - 1);
    head_BBST = BBST_insert(head_BBST, indexes, 0, n - 1);
    end = clock();

    if (choice == 1) {
        t = (float)(end - start) / CLOCKS_PER_SEC;
        printf("[1] INSERTION %f seconds\n", t);
        fprintf(output, "BBST,%d,%f\n", n, t);
    }
}

void BBST_search(struct BBST_node *root, int index) {
    // root case
    if (root == NULL || root->index == index) {
        // printf("Index: %d\n", root->index);
        return;
    }

    // if we are looking for a greater index than is in root
    if (root->index < index)
        return BBST_search(root->right, index);

    // otherwise
    return BBST_search(root->left, index);
}

void do_BBST_search(int choice, FILE *output) {
    if (choice == 2) {
        srand(time(NULL));
        clock_t start, end;
        float t, temp_t;
        int i, j;
        t = 0;
        for (j = 0; j < 10; j++) // 10 runs
        {
            shuffle_indexes(indexes, n);
            for (i = 0; i < n; i++) {
                int ran_id = indexes[i];
                // printf("Starting searching for %d...", ran_id);
                start = clock();
                BBST_search(head_BBST, ran_id);
                end = clock();
                // printf("Searching finished.\n");
                temp_t = (float)(end - start) / CLOCKS_PER_SEC;
                t = t + temp_t;
            }
        }
        printf("[2] SEARCH %f seconds\n", t / (10));
        fprintf(output, "BST,%d,%f\n", n, t / (10));
    }
}

struct BBST_node *getMinimumindexBBST(struct BBST_node *curr) {
    while (curr->left != NULL) {
        curr = curr->left;
    }
    return curr;
}

struct BBST_node *BBST_delete(struct BBST_node *root, int index) {
    struct BBST_node *parent = NULL;
    struct BBST_node *curr = root;

    // search index in the BBST and set its parent pointer
    while (curr && curr->index != index) {
        // update the parent to the curr node
        parent = curr;

        // if the given index is less than the curr node, go to the left subtree;
        // otherwise, go to the right subtree
        if (index < curr->index) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    // printf("    3Starting BBST delete...\n");

    // return if the index is not found in the tree
    if (curr == NULL) {
        return root;
    }
    // Case 1: node to be deleted has no children, i.e., it is a leaf node
    if (curr->left == NULL && curr->right == NULL) {

        // if the node to be deleted is not a root node, then set its
        // parent left/right child to None
        if (curr != root) {
            if (parent->left == curr) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        // if the tree has only a root node, set it to None
        else {
            root = NULL;
        }

        // deallocate the memory
        // free(curr);
    }

    // Case 2 : node to be deleted has two children
    else if (curr->left && curr->right) {
        // find its inorder successor node
        struct BBST_node *successor = getMinimumindexBBST(curr->right);

        // store successor value
        int val = successor->index;

        // recursively delete the successor. Note that the successor
        // will have at most one child (right child)
        BBST_delete(root, successor->index);

        // copy value of the successor to the current node
        curr->index = val;
    }

    // Case 3: node to be deleted has only one child
    else {
        // choose a child node
        struct BBST_node *child = (curr->left != NULL) ? curr->left : curr->right;

        // if the node to be deleted is not a root node, set its parent
        // to its child
        if (curr != root) {
            if (curr == parent->left) {
                parent->left = child;
            } else {
                parent->right = child;
            }
        }

        // if the node to be deleted is a root node, then set the root to the child
        else {
            root = child;
        }

        // deallocate the memory
        // free(curr);
    }
    // printf("    4Starting BBST delete...\n");

    return root;
}

void do_BBST_delete(int choice, FILE *output)

{
    if (choice == 3) {
        int i;
        float t, temp_t;
        clock_t start, end;
        int count, ran_id;
        t = 0;
        shuffle_indexes(indexes, i);
        for (i = 0; i < n; i++) {
            ran_id = indexes[i];
            start = clock();
            head_BBST = BBST_delete(head_BBST, ran_id);
            end = clock();
            temp_t = (float)(end - start) / CLOCKS_PER_SEC;
            t = t + temp_t;
        }
        printf("[3] REMOVE %f seconds\n", t);
        fprintf(output, "BBST,%d,%f\n", n, t);
    }
}

void BBST_print_preorder(struct BBST_node *root) {
    if (root == NULL)
        return;

    // print R0
    printf("%d ", root->index); // Print data
    // L
    BBST_print_preorder(root->left); // Visit left subtree
    // R
    BBST_print_preorder(root->right); // Visit right subtree
}

void BBST_print_postorder(struct BBST_node *root) {
    if (root == NULL)
        return;

    // L
    BBST_print_preorder(root->left); // Visit left subtree
    // R
    BBST_print_preorder(root->right); // Visit right subtree
    // print R0
    printf("%d ", root->index); // Print data
}

void BBST_print_inorder(struct BBST_node *root) {
    if (root == NULL)
        return;

    // L
    BBST_print_preorder(root->left); // Visit left subtree
    // print R0
    printf("%d ", root->index); // Print data
    // R
    BBST_print_preorder(root->right); // Visit right subtree
}

// other
char *filename_string(int choice) {
    if (choice == 1) {
        return "insertion.csv";
    }
    if (choice == 2) {
        return "search.csv";
    }
    if (choice == 3) {
        return "delete.csv";
    }
}

// main
int main() {
    srand(time(NULL));
    /*---------------------------------------------------------------------------------- */
    int choice, stepsize, repeats;
    int repeat;
    printf("\n[1] insertion\n[2] search\n[3] remove\n choice: ");
    scanf("%d", &choice);
    printf("\nenter starting size of database: "); // what size of subgroup of csv take to experiment
    scanf("%d", &n);
    printf("\nenter stepsize: ");
    scanf("%d", &stepsize);
    printf("\nenter number of measuring points: ");
    scanf("%d", &repeats);

    char *FILENAME_OUTPUT = filename_string(choice);
    FILE *output = fopen(FILENAME_OUTPUT, "a");

    if (!(choice == 1 || choice == 2 || choice == 3)) {
        printf("Wrong input.");
        return 1;
    }

    for (repeat = 0; repeat < repeats; repeat++) {
        indexes = (int *)malloc(n * sizeof(int));
        head = NULL;
        head_BST = NULL;
        printf("\n\n\n\n\n\nFor n equal to: %d\n", n);

        /*------------------------------------ table -------------------------------------- */
        students = malloc(n * sizeof *students);
        FILE *my_file = fopen(FILENAME, "r");
        if (my_file == NULL) {
            printf("Warning: File cannot be opened\n");
            return 1;
        }
        table_create(my_file, students, n);
        fclose(my_file);

        /*------------------------ dynamically ordered [linked] list ----------------------- */
        // printf("ORDERED LIST\n");
        // do_list_insertion(choice, output); // insert database
        // do_list_search(choice, output);    // searching random element with time measure (average of 5 runs)
        // do_list_delete(choice, output);    // deleting all in random manner
        // // list_print();              // optional printing
        // free(student);

        /*--------------------------------- binary search tree ----------------------------- */
        printf("\nBINARY SEARCH TREE\n");
        do_BST_insertion(choice, output); // insert database
        do_BST_search(choice, output);    // searching random element with time measure (average of 5 runs)
        do_BST_delete(choice, output);    // deleting all in random manner

        // optional printing {
        printf("\nPreorder:\n");
        BST_print_preorder(head_BST);
        printf("\nPostorder:\n");
        BST_print_postorder(head_BST);
        printf("\nInorder:\n");
        BST_print_inorder(head_BST);
        // }

        // free(student_BST);

        // /*------------------------------ BBST -------------------------------------------- */
        printf("\nBALANCED BINARY SEARCH TREE\n");
        do_BBST_insertion(choice, output);
        do_BBST_search(choice, output);
        do_BBST_delete(choice, output);

        // optional printing {
        printf("\nPreorder:\n");
        BBST_print_preorder(head_BBST);
        printf("\nPostorder:\n");
        BBST_print_postorder(head_BBST);
        printf("\nInorder:\n");
        BBST_print_inorder(head_BBST);
        // }

        // free(student_BBST);

        // // deallocating memory
        free(students);
        free(indexes);
        n = n + stepsize;
    }

    fclose(output);
    return 0;
}