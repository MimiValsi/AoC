#include "misc.h"
#include <stdio.h>
#include <string.h>

typedef struct Foo foo_t;

typedef struct Foo {
        u32 index;
        char *str;
        foo_t *next;
        foo_t *prev;
} foo_t;

void check_curly_brackets(const char *str, u32 len, foo_t **head);

foo_t *foo_init(u32 index, const char *str);
void foo_append_at_position(foo_t **head, u32 index, u32 position,
                            const char *str);
void foo_insert_at_beginning(foo_t **head, u32 index, const char *str);
void foo_append(foo_t **head, u32 index, const char *str);
void foo_free(foo_t *obj);
void foo_print(foo_t *obj);

int main() {
        FILE *file = fopen("./data/day12_2.txt", "r");
        u32 len = get_file_length(file);
        // copy to array coz it's easier to control the loop flow
        char str[len];
        fgets(str, len, file);
        printf("\nfull string: %s\n\n", str);

        // create first object to null!
        // foo_append() will make the rest
        foo_t *obj = NULL;
        // foo_append(&obj, 1, "red");
        // foo_append(&obj, 2, "blue");
        // foo_insert_at_beginning(&obj, 3, "green");

        check_curly_brackets(str, len, &obj);
        foo_print(obj);

        foo_free(obj);
        fclose(file);

        return 0;
}

void foo_print(foo_t *obj) {
        foo_t *tmp = obj;
        printf("\nobject:\n");
        while (tmp) {
                printf("index: %d\nstr: %s\n\n", tmp->index, tmp->str);
                tmp = tmp->next;
        }
}

void foo_free(foo_t *obj) {
        foo_t *tmp = NULL;
        while (obj) {
                tmp = obj;
                obj = obj->next;
                free(tmp->str);
                free(tmp);
        }
}

// this may/will be recursive!
void check_curly_brackets(const char *str, u32 len, foo_t **head) {
        // copy str to this temporary variable so I can control the obj index!
        char tmp[1000];
        memset(tmp, 0, 1000);
        // this will be the tmp array index!
        u32 t = 0;
        // tmp[0] = '{';

        // static var
        static u32 position = 1;
        for (u32 i = 0; i < len; i++) {
                // copy string
                tmp[t] = str[i];
                t++;

                if (str[i] == '}') {
                        foo_append(head, i, tmp);
                        // obj = check_curly_brackets(&str[i], len, obj);
                        foo_append_at_position(head, i, position, tmp);
                        position--;
                        printf("position--: %s\n", tmp);
                        break;
                }
                if (i != 0 && str[i + 1] == '{') {
                        // update obj!
                        printf("position++: %s\n", tmp);
                        // foo_append(head, i, tmp);
                        foo_append_at_position(head, i, position, tmp);
                        position++;
                        check_curly_brackets(&str[i + 1], len, head);
                        break;
                }
        }
}

void foo_append(foo_t **head, u32 index, const char *str) {
        foo_t *new = foo_init(index, str);
        if (!new) {
                perror("couldn't allocate foo_t\n");
                return;
        }

        if (!(*head)) {
                *head = new;
                return;
        }

        foo_t *tmp = *head;
        while (tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = new;
        new->prev = tmp;
}

void foo_append_at_position(foo_t **head, u32 index, u32 position,
                            const char *str) {

        if (position < 1) {
                perror("Position must be >= 1\n");
                return;
        }
        if (position == 1) {
                foo_insert_at_beginning(head, index, str);
                return;
        }

        foo_t *new = foo_init(index, str);
        foo_t *tmp = *head;
        for (u32 i = 1; !tmp && i < position - 1; i++) {
                tmp = tmp->next;
        }
        if (!tmp) {
                perror("Position went too far...\n");
                return;
        }

        new->next = tmp->next;
        new->prev = tmp;
        if (!tmp->next) {
                tmp->next->prev = new;
        }

        tmp->next = new;
}

void foo_insert_at_beginning(foo_t **head, u32 index, const char *str) {
        foo_t *new = foo_init(index, str);
        if (!(*head)) {
                *head = new;
                return;
        }
        new->next = *head;
        (*head)->prev = new;
        *head = new;
}

// initialise new ll object with index and str
// keep next and prev field to NULL
foo_t *foo_init(u32 index, const char *str) {
        foo_t *obj = malloc(sizeof(foo_t));
        if (!obj) {
                return NULL;
        }
        obj->index = index;

        if (obj->str) {
                strcat(obj->str, str);
        } else {
                obj->str = strdup(str);
                if (!obj->str) {
                        perror("couldn't strdup string\n");
                        return NULL;
                }
        }

        obj->next = NULL;
        obj->prev = NULL;

        return obj;
}
