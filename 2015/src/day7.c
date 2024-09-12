#include "misc.h"
#include <time.h>

u16 part1(FILE *file);
void part2(FILE *file, u16 x);
struct Wire* init_wire(char const *id, u16 val);
struct Wire* append_wire(struct Wire *wire, char const *id, u16 val);
bool source_exists(struct Wire *wire, char const *id);
struct Wire* fetch_wires(FILE *file, struct Wire *wire);
void free_all_wires(struct Wire *wire);
void print_wires(struct Wire *wire);
u16 find_source(struct Wire *wire, FILE *f);
void update_wire(struct Wire *wire, u16 val);

#define NB_LINES 339

struct Wire {
        char id[3];
        u16 signal;

        struct Wire *next;
};

int main(void)
{
        FILE *file = fopen("data/day7.txt", "r");
        NL();
        printf("part1:\n");
        u16 x = part1(file);
        NL();
        rewind(file);

        printf("part2:\n");
        part2(file, x);
        fclose(file);
        return 0;
}

u16
part1(FILE *file)
{
        struct Wire *wire = NULL;
        wire = fetch_wires(file, wire);

        rewind(file);

        u16 x = find_source(wire, file);

        free_all_wires(wire);

        return x;
}

void
part2(FILE *file, u16 x)
{
        struct Wire *wire = NULL;
        wire = fetch_wires(file, wire);
        rewind(file);
        update_wire(wire, x);
        find_source(wire, file);
        free_all_wires(wire);
}

/*
 * updates 'b' wire for part 2
 */
void
update_wire(struct Wire *wire, u16 val)
{
        struct Wire *tmp = wire;
        while (tmp) {
                if (strcmp(tmp->id, "b") == 0) {
                        tmp->signal = val;
                }

                tmp = tmp->next;
        }
}

/*
 * Fake recursion.
 * the for loop 'is' the recursion
 * the first while loop checks the first wire
 * the second while loop checks the second wire
 */
u16
find_source(struct Wire *wire, FILE *f)
{
        struct Wire *tmp = wire;
        for (int i = 0; ; i++) {
                if (i == NB_LINES) {
                        i = 0;
                        rewind(f);
                }
                char *line = get_line(f);
                String s = line_split(line, " ");

                while (tmp) {

                        // The unique loop stop
                        // It only stops when wire 'a' signal is found
                        if (strcmp(tmp->id, "a") == 0) {
                                printf("wire: %s\n", tmp->id);
                                printf("val: %d\n", tmp->signal);
                                free(line);
                                return tmp->signal;
                        }

                        /*
                         *  1   AND x   ->  y
                         * [0] [1] [2] [3] [4]
                         */
                        if (isdigit(s.s[0][0]) && strcmp(s.s[2], tmp->id) == 0 && strcmp(s.s[1], "AND") == 0) {
                                if (!source_exists(wire, s.s[4])) {
                                        wire = append_wire(wire, s.s[4], atoi(s.s[0]) & tmp->signal);
                                }

                        /*
                         *  1   OR  x   ->  y
                         * [0] [1] [2] [3] [4]
                         */
                        } else if (isdigit(s.s[0][0]) && strcmp(s.s[2], tmp->id) == 0 && strcmp(s.s[1], "OR") == 0) {
                                if (!source_exists(wire, s.s[4])) {
                                        wire = append_wire(wire, s.s[4], atoi(s.s[0]) | tmp->signal);
                                }
                        }

                        /*
                         *  NOT x   ->  y
                         * [0] [1] [2] [3]
                         */
                        if (strcmp(s.s[0], "NOT") == 0 && strcmp(s.s[1], tmp->id) == 0) {
                                if (!source_exists(wire, s.s[3])) {
                                        wire = append_wire(wire, s.s[3], ~tmp->signal);
                                }
                        }

                        if (strcmp(s.s[0], tmp->id) == 0) {
                                /*
                                 *  x   LSHIFT 1   ->  y
                                 * [0] [1]    [2] [3] [4]
                                 */
                                if (strcmp(s.s[1], "LSHIFT") == 0) {
                                        if (!source_exists(wire, s.s[4])) {
                                                wire = append_wire(wire, s.s[4], tmp->signal << (atoi(s.s[2])));
                                        }

                                /*
                                 *  x   RSHIFT 1   ->  y
                                 * [0] [1]    [2] [3] [4]
                                 */
                                } else if (strcmp(s.s[1], "RSHIFT") == 0) {
                                        if (!source_exists(wire, s.s[4])) {
                                                wire = append_wire(wire, s.s[4], tmp->signal >> (atoi(s.s[2])));
                                        }
                                }

                                /*
                                 *  x   ->  y
                                 * [0] [1] [2]
                                 */
                                if (strcmp(s.s[1], "->") == 0) {
                                        if (!source_exists(wire, s.s[2])) {
                                                wire = append_wire(wire, s.s[2], tmp->signal);
                                        }
                                }

                                /*
                                 * Same strategy as the first while loop
                                 * we don't compare the first wire because it's already done in the 
                                 * first while loop
                                 */
                                struct Wire *tmp2 = wire;
                                while (tmp2) {
                                        if (strcmp(s.s[1], "AND") == 0) {
                                                if (strcmp(tmp2->id, s.s[2]) == 0)
                                                {
                                                        if (!source_exists(wire, s.s[4])) {
                                                                wire = append_wire(wire, s.s[4], (tmp->signal & tmp2->signal));
                                                        }
                                                }
                                        }
                                        if (strcmp(s.s[1], "OR") == 0) {
                                                if (strcmp(tmp2->id, s.s[2]) == 0)
                                                {
                                                        if (!source_exists(wire, s.s[4])) {
                                                                wire = append_wire(wire, s.s[4], (tmp->signal | tmp2->signal));
                                                        }
                                                }
                                        }

                                        tmp2 = tmp2->next;
                                }
                                tmp2 = wire;
                        }

                        tmp = tmp->next;
                }

                tmp = wire;

                free(line);

        }
}

// Initialise a new linked list. Only used inside append_wire()
struct Wire*
init_wire(char const *id, u16 val)
{
        struct Wire *new = malloc(sizeof(*new));
        if (!new) {
                return NULL;
        }

        strcpy(new->id, id);
        new->signal = val;
        new->next = NULL;

        return new;
}

// append a new wire by calling init_wire, check last node and merge new list
struct Wire *
append_wire(struct Wire *wire, char const *id, u16 val)
{
        struct Wire *new = init_wire(id, val);
        if (!wire) {
                return new;
        }

        struct Wire *tmp = wire;
        while (tmp->next) {
                tmp = tmp->next;
        }

        tmp->next = new;

        return wire;
}

// check if wire already exists to avoid redundancy
bool
source_exists(struct Wire *wire, char const *id)
{
        struct Wire *tmp = wire;
        while (tmp) {
                if (strcmp(tmp->id, id) == 0) {
                        return true;
                }

                tmp = tmp->next;
        }

        return false;
}

void
free_all_wires(struct Wire *wire)
{
        struct Wire *tmp = NULL;
        while (wire) {
                tmp = wire;
                wire = wire->next;
                free(tmp);
        }
}

void
print_wires(struct Wire *wire)
{
        printf("Sources:\n");
        struct Wire *tmp = wire;
        while (tmp) {
                printf("%s: %d\n", tmp->id, tmp->signal);
                tmp = tmp->next;
        }
}

// make a first iteration of the file to find all sources
struct Wire*
fetch_wires(FILE *file, struct Wire *wire)
{
        for (int i = 0; i < NB_LINES; i++) {
                char *line = get_line(file);
                String s = line_split(line, " ");

                if (strcmp(s.s[1], "->") == 0 && isdigit(s.s[0][0])) {
                        if (!source_exists(wire, s.s[2])) {
                                wire = append_wire(wire, s.s[2], atoi(s.s[0]));
                        }
                }

                free(line);
        }

        return wire;
}
