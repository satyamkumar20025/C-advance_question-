#include <stdio.h>
#include <string.h>

int main() {
    char sentence[1000];

    // Read the full line including spaces
    fgets(sentence, sizeof(sentence), stdin);

    // Tokenize using space delimiter
    char *word = strtok(sentence, " ");
    while (word != NULL) {
        printf("%s\n", word);
        word = strtok(NULL, " ");
    }

    return 0;
}
