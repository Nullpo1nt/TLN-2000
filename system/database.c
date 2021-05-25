#include "database.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tln_structs.h"

struct _tln_db_s {};

// tln_waypoint vors[];
// tln_waypoint ndbs[];
// tln_waypoint intersections[];
// tln_waypoint userwaypoints[];
// tln_flightplan flightplans[];

tln_wp_t database_airports[] = {
    {AIRPORT, {42.4699444, -71.28900000}, "KBED", "BED", "Laurence G Hanscom Field Airport", "Bedford", "MA"},
    {AIRPORT, {42.3629444, -71.00638890}, "KBOS", "BOS", "Boston Logan Intl", "Boston", "MA"},
    {AIRPORT, {33.9424964, -118.4080486}, "KLAX", "LAX", "LAX Intl", "Los Angelos", "CA"},
    {AIRPORT, {28.4312000, -81.30810000}, "KMCO", "MCO", "Orlando Intl", "Orlando", "FL"},
    {AIRPORT, {42.9328056, -71.43575000}, "KMHT", "MHT", "Manchester Airport", "Manchester", "NH"},
    {AIRPORT, {41.9745219, -87.90659720}, "KORD", "ORD", "Chicago O'Hare International Airport", "Chicago", "IL"},
    {AIRPORT, {42.2671389, -71.87561110}, "KORH", "ORH", "Worcester Regional Airport", "Worchester", "MA"},
    {AIRPORT, {37.6213000, -122.3790000}, "KSFO", "SFO", "San Francisco International Airport", "San Francisco", "CA"},
    {AIRPORT, {21.3245000, -157.9251000}, "PHNL", "PHNL", "Honolulu", "Hawaaaa", "HI"},
};

typedef struct tln_db_tree {
    char value;
    tln_wp_t* waypoint;

    struct tln_db_tree* next;

    struct tln_db_tree* left;
    struct tln_db_tree* right;
} tln_db_tree_t;

void destroy_tree(tln_db_tree_t* tree) {
    if (tree != NULL) {
        destroy_tree(tree->next);
        destroy_tree(tree->left);
        destroy_tree(tree->right);

        free(tree);
    }
}

void insert(tln_db_tree_t** tree, tln_wp_t* waypoint, int i) {
    if (*tree == NULL) {
        *tree = (struct tln_db_tree*)malloc(sizeof(struct tln_db_tree));
        (*tree)->value = waypoint->usId[i];
        (*tree)->waypoint = NULL;
        (*tree)->left = NULL;
        (*tree)->right = NULL;
        (*tree)->next = NULL;

        if (i < strlen(waypoint->usId) - 1) {
            insert(&(*tree)->next, waypoint, ++i);
        } else {
            (*tree)->waypoint = waypoint;
        }
    } else if (waypoint->usId[i] < (*tree)->value) {
        insert(&(*tree)->left, waypoint, i);
    } else if (waypoint->usId[i] > (*tree)->value) {
        insert(&(*tree)->right, waypoint, i);
    } else {
        insert(&(*tree)->next, waypoint, ++i);
    }
}

tln_db_tree_t* find(tln_db_tree_t* t, char c) {
    if (t != NULL) {
        if (t->value == c) {
            return t;
        } else if (c < t->value) {
            return find(t->left, c);
        } else {
            return find(t->right, c);
        }
    } else {
        return NULL;
    }
}

int size(tln_db_tree_t* tree) {
    if (tree == NULL) {
        return 0;
    }

    return 1 + size(tree->left) + size(tree->right);
}

int fff(tln_db_tree_t* tree, char* buf, int i) {
    if (tree == NULL) {
        return i;
    }

    buf[i++] = tree->value;

    i = fff(tree->left, buf, i);

    i = fff(tree->right, buf, i);

    return i;
}

void next(tln_db_tree_t* tree, char* input, char* output) {
    tln_db_tree_t* t = tree;
    int il = strlen(input);
    for (int i = 0; i < il; i++) {
        t = find(t, input[i]);

        if (t == NULL) {
            break;
        }

        t = t->next;
    }

    if (t != NULL) {
        fff(t, output, 0);
    }
}

void test() {
    tln_db_tree_t* tree = NULL;

    for (int i = 0; i < 9; i++) {
        insert(&tree, &database_airports[i], 0);
    }

    int i = size(tree);

    char bah[3] = "OR";
    char asd[26] = "";

    next(tree, bah, asd);

    destroy_tree(tree);
}

tln_wp_t* database_getAirport(int x) {
    if (x > 4 || x < 0) {
        return NULL;
    }

    return &database_airports[x];
}

// void database_(char* partialId, char* buf) {
//     for (int i = 0; i < length(database_airports); i++) {
//         tln_wp_t* airport = &database_airports[i];

//         for (int x = 0; x < length(partialId); x++) {
//             if (airport->usId[x] == partialId[x]) {
//                 insert letter into buf
//             }
//         }
//     }
// }

// tln_wp_t* database_next(tln_wp_db_t* db, )

//     const greatcircle::LLPoint newportRI = {41.49008 * 0.017453293, -71.312796 * 0.017453293};
//     const greatcircle::LLPoint clevelandOH = {41.499498 * 0.017453293, -81.695391 * 0.017453293};
