#include "misc.h"

#define CITY 20

// #define NB_LINES 3
// #define OPENFILE fopen("data/test.txt", "r")
// #define TRAVELS 4

#define NB_LINES 28
#define OPENFILE fopen("data/day9.txt", "r")
#define TRAVELS 9

// int min = 999;
// int max = 0;

struct Cities *init(char ida, char idb, char *city_a, char *city_b, u32 dist);
struct Cities *append(struct Cities *c, char ida, char idb, char *city_a,
                      char *city_b, u32 dist);
void free_list(struct Cities *c);
void print_list(struct Cities *c);
bool city_visited(char visited[TRAVELS][CITY], char const *city);
struct Cities_ids *append_ids(struct Cities_ids *cids, char id, char *city);
struct Cities_ids *init_ids(char id, char *city);
bool ids_exist(struct Cities_ids *cids, char *city);
void print_ids(struct Cities_ids *cids);
void free_ids(struct Cities_ids *cids);
void update_list(struct Cities *c, struct Cities_ids *cids);
void permute(struct Cities *c, char *a, int l, int r);
void swap(char *x, char *y);
u32 find_dist(struct Cities *c, char *visited);

struct Cities {
        char ida;
        char idb;
        char city_a[CITY];
        char city_b[CITY];
        u32 dist;

        struct Cities *next;
};

struct Cities_ids {
        char id;
        char city[CITY];

        struct Cities_ids *next;
};

int main() {
        FILE *f = OPENFILE;

        // ida and idb start
        char id = 'a';
        struct Cities *c = NULL;
        char visited[TRAVELS] = {0};
        u32 vis = 0;

        struct Cities_ids *cids = NULL;
        struct Cities_ids *tmp = cids;

        // need to check if ida or idb exists and if so, add the same char to
        // others lists
        for (int i = 0; i < NB_LINES; i++) {
                char *line = get_line(f);
                String s = line_split(line, " ");
                c = append(c, ' ', ' ', s.s[0], s.s[2], atoi(s.s[4]));

                if (!ids_exist(cids, s.s[0])) {
                        visited[vis++] = id;
                        cids = append_ids(cids, id++, s.s[0]);
                }

                if (!ids_exist(cids, s.s[2])) {
                        visited[vis++] = id;
                        cids = append_ids(cids, id++, s.s[2]);
                }

                free(line);
        }

        // created 2 linked lists to facilitate the create of ids for each city
        update_list(c, cids);

        u32 arr_len = strlen(visited);
        permute(c, visited, 0, arr_len - 1);

        free_ids(cids);
        free_list(c);

        fclose(f);
}

u32 find_dist(struct Cities *c, char *visited) {
        u32 res = 0;
        struct Cities *tmp = c;
        while (tmp) {
                for (u32 i = 0; i < TRAVELS; i++) {
                        if (visited[i] == tmp->ida &&
                            visited[i + 1] == tmp->idb) {
                                res += tmp->dist;
                        }
                        if (visited[i] == tmp->idb &&
                            visited[i + 1] == tmp->ida) {
                                res += tmp->dist;
                        }
                }

                tmp = tmp->next;
        }

        return res;
}

// finding min is for part 1 and max for part 2
void permute(struct Cities *c, char *a, int l, int r) {
        static u32 min = 999;
        static u32 max = 0;
        if (l == r) {
                printf("%s\n", a);
                u32 sum = find_dist(c, a);
                if (max < sum) {
                        max = sum;
                }
                if (min > sum) {
                        min = sum;
                }
                printf("min: %d\n", min);
                printf("max: %d\n", max);
        } else {
                for (int i = l; i <= r; i++) {
                        swap((a + l), (a + i));
                        permute(c, a, l + 1, r);
                        swap((a + l), (a + i));
                }
        }
}

void swap(char *x, char *y) {
        char tmp;
        tmp = *x;
        *x = *y;
        *y = tmp;
}

void free_ids(struct Cities_ids *cids) {
        struct Cities_ids *tmp = NULL;
        while (cids) {
                tmp = cids;
                cids = cids->next;
                free(tmp);
        }
}

void print_ids(struct Cities_ids *cids) {
        struct Cities_ids *tmp = cids;
        while (tmp) {
                printf("cids->id: %c | cids->city: %s\n", tmp->id, tmp->city);

                tmp = tmp->next;
        }
}

bool ids_exist(struct Cities_ids *cids, char *city) {
        struct Cities_ids *tmp = cids;
        while (tmp) {
                int cmp = strcmp(tmp->city, city);
                if (cmp == 0) {
                        return true;
                }
                tmp = tmp->next;
        }

        return false;
}

struct Cities_ids *init_ids(char id, char *city) {
        struct Cities_ids *new = malloc(sizeof(*new));
        if (!new) {
                return NULL;
        }

        new->id = id;
        strcpy(new->city, city);
        new->next = NULL;

        return new;
}

struct Cities_ids *append_ids(struct Cities_ids *cids, char id, char *city) {
        struct Cities_ids *new = init_ids(id, city);

        if (!cids) {
                return new;
        }

        struct Cities_ids *tmp = cids;
        while (tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = new;

        return cids;
}

struct Cities *init(char ida, char idb, char *city_a, char *city_b, u32 dist) {
        struct Cities *new = malloc(sizeof(*new));

        if (!new) {
                return NULL;
        }

        new->ida = ida;
        new->idb = idb;
        strcpy(new->city_a, city_a);
        strcpy(new->city_b, city_b);
        new->dist = dist;
        new->next = NULL;

        return new;
}

struct Cities *append(struct Cities *c, char ida, char idb, char *city_a,
                      char *city_b, u32 dist) {
        struct Cities *new = init(ida, idb, city_a, city_b, dist);

        if (!c) {
                return new;
        }

        struct Cities *tmp = c;
        while (tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = new;

        return c;
}

void update_list(struct Cities *c, struct Cities_ids *cids) {
        struct Cities *tmp_c = c;
        struct Cities_ids *tmp_cids = cids;
        while (tmp_c) {
                while (tmp_cids) {
                        int cmp_city_a = strcmp(tmp_c->city_a, tmp_cids->city);
                        int cmp_city_b = strcmp(tmp_c->city_b, tmp_cids->city);

                        if (cmp_city_a == 0) {
                                tmp_c->ida = tmp_cids->id;
                        }

                        if (cmp_city_b == 0) {
                                tmp_c->idb = tmp_cids->id;
                        }

                        tmp_cids = tmp_cids->next;
                }
                tmp_cids = cids;
                tmp_c = tmp_c->next;
        }
}

void print_list(struct Cities *c) {
        struct Cities *tmp = c;
        while (tmp) {
                printf("ida: %c | idb: %c | city_a: %-20s | city_b: %-20s | "
                       "dist: %d\n",
                       tmp->ida, tmp->idb, tmp->city_a, tmp->city_b, tmp->dist);

                tmp = tmp->next;
        }
}

void free_list(struct Cities *c) {
        struct Cities *tmp = NULL;
        while (c) {
                tmp = c;
                c = c->next;
                free(tmp);
        }
}
