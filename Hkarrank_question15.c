#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Package {
    char* id;
    int weight;
};

struct PostOffice {
    int min_weight;
    int max_weight;
    int packages_count;
    struct Package* packages;
};

struct Town {
    char* name;
    int offices_count;
    struct PostOffice* offices;
};

void print_all_packages(struct Town t) {
    printf("%s:\n", t.name);
    for (int i = 0; i < t.offices_count; i++) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t.offices[i].packages_count; j++) {
            printf("\t\t%s\n", t.offices[i].packages[j].id);
        }
    }
}

void send_all_acceptable_packages(struct Town* source, int source_office_index,
                                  struct Town* target, int target_office_index) {
    struct PostOffice* src = &source->offices[source_office_index];
    struct PostOffice* tgt = &target->offices[target_office_index];

    struct Package* accepted = malloc(src->packages_count * sizeof(struct Package));
    struct Package* rejected = malloc(src->packages_count * sizeof(struct Package));
    int acc_count = 0, rej_count = 0;

    for (int i = 0; i < src->packages_count; i++) {
        struct Package p = src->packages[i];
        if (p.weight >= tgt->min_weight && p.weight <= tgt->max_weight) {
            accepted[acc_count++] = p;
        } else {
            rejected[rej_count++] = p;
        }
    }

    // Update source office with rejected packages
    src->packages_count = rej_count;
    for (int i = 0; i < rej_count; i++) {
        src->packages[i] = rejected[i];
    }

    // Append accepted packages to target office
    tgt->packages = realloc(tgt->packages, (tgt->packages_count + acc_count) * sizeof(struct Package));
    for (int i = 0; i < acc_count; i++) {
        tgt->packages[tgt->packages_count++] = accepted[i];
    }

    free(accepted);
    free(rejected);
}

struct Town town_with_most_packages(struct Town* towns, int towns_count) {
    int max = -1;
    struct Town result = towns[0];

    for (int i = 0; i < towns_count; i++) {
        int total = 0;
        for (int j = 0; j < towns[i].offices_count; j++) {
            total += towns[i].offices[j].packages_count;
        }
        if (total > max) {
            max = total;
            result = towns[i];
        }
    }
    return result;
}

struct Town* find_town(struct Town* towns, int towns_count, char* name) {
    for (int i = 0; i < towns_count; i++) {
        if (strcmp(towns[i].name, name) == 0) {
            return &towns[i];
        }
    }
    return NULL;
}

int main() {
    int towns_count;
    scanf("%d", &towns_count);
    struct Town* towns = malloc(towns_count * sizeof(struct Town));

    for (int i = 0; i < towns_count; i++) {
        towns[i].name = malloc(100);
        scanf("%s", towns[i].name);
        scanf("%d", &towns[i].offices_count);
        towns[i].offices = malloc(towns[i].offices_count * sizeof(struct PostOffice));

        for (int j = 0; j < towns[i].offices_count; j++) {
            int packages_count;
            scanf("%d %d %d", &packages_count,
                  &towns[i].offices[j].min_weight,
                  &towns[i].offices[j].max_weight);

            towns[i].offices[j].packages_count = packages_count;
            towns[i].offices[j].packages = malloc(packages_count * sizeof(struct Package));

            for (int k = 0; k < packages_count; k++) {
                towns[i].offices[j].packages[k].id = malloc(100);
                scanf("%s", towns[i].offices[j].packages[k].id);
                scanf("%d", &towns[i].offices[j].packages[k].weight);
            }
        }
    }

    int queries;
    scanf("%d", &queries);
    for (int q = 0; q < queries; q++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            char town_name[100];
            scanf("%s", town_name);
            struct Town* t = find_town(towns, towns_count, town_name);
            print_all_packages(*t);
        } else if (type == 2) {
            char source_name[100], target_name[100];
            int src_index, tgt_index;
            scanf("%s %d %s %d", source_name, &src_index, target_name, &tgt_index);
            struct Town* src = find_town(towns, towns_count, source_name);
            struct Town* tgt = find_town(towns, towns_count, target_name);
            send_all_acceptable_packages(src, src_index, tgt, tgt_index);
        } else if (type == 3) {
            struct Town t = town_with_most_packages(towns, towns_count);
            printf("Town with the most number of packages is %s\n", t.name);
        }
    }

    // Memory cleanup omitted for brevity
    return 0;
}
