#include <stdio.h>
#include <stdlib.h>

int* total_number_of_books;
int** total_number_of_pages;

int main() {
    int total_number_of_shelves;
    scanf("%d", &total_number_of_shelves);

    int total_number_of_queries;
    scanf("%d", &total_number_of_queries);

    // Allocate memory for book count per shelf
    total_number_of_books = (int*)calloc(total_number_of_shelves, sizeof(int));

    // Allocate memory for pages per book per shelf
    total_number_of_pages = (int**)malloc(total_number_of_shelves * sizeof(int*));
    for (int i = 0; i < total_number_of_shelves; i++) {
        total_number_of_pages[i] = (int*)malloc(1100 * sizeof(int)); // max 1100 books per shelf
    }

    for (int q = 0; q < total_number_of_queries; q++) {
        int type;
        scanf("%d", &type);

        if (type == 1) {
            int x, y;
            scanf("%d %d", &x, &y);

            // 🟢 Type 1: Insert book with y pages at shelf x
            int book_index = total_number_of_books[x];
            total_number_of_pages[x][book_index] = y;
            total_number_of_books[x]++;
        }
        else if (type == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", total_number_of_pages[x][y]);
        }
        else if (type == 3) {
            int x;
            scanf("%d", &x);
            printf("%d\n", total_number_of_books[x]);
        }
    }

    // Free memory
    for (int i = 0; i < total_number_of_shelves; i++) {
        free(total_number_of_pages[i]);
    }
    free(total_number_of_pages);
    free(total_number_of_books);

    return 0;
}
