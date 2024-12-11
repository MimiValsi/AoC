#include "misc.h"
#include <stdio.h>
#include <string.h>

typedef struct Json json_t;

typedef struct Json {
        u32 index;
        char *str;
        json_t *next;
        json_t *prev;
} json_t;

void check_curly_brackets(const char *str, u32 len, json_t *obj);

json_t *init(u32 index, const char *str);
json_t *append(json_t *obj, u32 index, const char *str);
void ll_free(json_t *obj);
void ll_print(json_t *obj);

int main() {
        FILE *file = fopen("./data/day12_2.txt", "r");
        u32 len = get_file_length(file);
        // copy to array coz it's easier to control the loop flow
        char str[len];
        fgets(str, len, file);

        // create first object to null!
        // append() will make the rest
        json_t *obj = NULL;
        check_curly_brackets(str, len, obj);
        ll_print(obj);

        // start loop string.
        // check for first '{', this will begin a object

        // free object str before!
        // free(object->str);
        // free object.

        ll_free(obj);
        fclose(file);

        return 0;
}

void ll_print(json_t *obj) {
        json_t *tmp = obj;
        printf("object:\n");
        // printf("%d\n", tmp->index);
        while (tmp) {
                // printf("index: %d\nstr: %s\n", tmp->index, tmp->str);
                tmp = tmp->next;
        }
}

void ll_free(json_t *obj) {
        json_t *tmp = NULL;
        while (obj) {
                tmp = obj;
                obj = obj->next;
                free(tmp->str);
                free(tmp);
        }
}

// this may/will be recursive!
void check_curly_brackets(const char *str, u32 len, json_t *obj) {
        // copy str to this temporary variable so I can control the obj index!
        char tmp[1000] = {0};
        // this will be the tmp array index!
        u32 t = 1;
        tmp[0] = '{';
        for (u32 i = 1; i < len; i++) {
                // copy string
                tmp[t] = str[i];
                t++;

                if (str[i + 1] == '{') {
                        // update obj!
                        printf("tmp: %s\n", tmp);
                        printf("i: %d\n", i);
                        obj = append(obj, i, tmp);
                        // check_curly_brackets(&str[i], len, obj);
                        break;
                }
        }
}

void update(json_t *obj);

json_t *append(json_t *obj, u32 index, const char *str) {
        json_t *new = init(index, str);
        if (!obj) {
                return new;
        }

        json_t *tmp = obj;
        while (tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = new;

        return obj;
}

// initialise new ll object with index and str
// keep next and prev field to NULL
json_t *init(u32 index, const char *str) {
        json_t *obj = malloc(sizeof(json_t));
        if (!obj) {
                perror("couldn't allocate json_t\n");
                return NULL;
        }
        obj->index = index;
        obj->str = strdup(str);
        if (!obj->str) {
                perror("couldn't strdup string\n");
                return NULL;
        }
        obj->next = NULL;
        obj->prev = NULL;

        return obj;
}
