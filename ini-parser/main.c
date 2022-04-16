#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

struct data_struct
{
    char *sectionname;
    char *keyname;
};
struct data_struct *data;

void free_memory(char *p1, char *p2, char *p3, char *p4, char **pp1, char **pp2)
{
    free(p1);
    free(p2);
    free(p3);
    free(p4);
    free(pp1);
    free(pp2);
}

int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 2) // only ./main.exe without anything else or just filename
    {
        printf("Warning: Wrong entry\n");
        return 1;
    }

    // variables
    data = (struct data_struct *)malloc(sizeof(struct data_struct));
    char *value, *line, **lines, **extended_lines, *tokens, *section;
    int n = 100;
    int lenght = n;

    // section
    tokens = strtok(argv[2], ".");
    int len_sectionname = strlen(tokens);
    data->sectionname = (char *)malloc((len_sectionname + 1) * sizeof(char));
    if (data->sectionname == NULL)
    {
        printf("Warning: data->sectionname memory allocation failed.\n");
        return 1;
    }
    sscanf(tokens, "%[A-Z0-9a-z-]", data->sectionname);

    // key
    tokens = strtok(NULL, ".");
    int len_keyname = strlen(tokens);
    data->keyname = (char *)malloc((len_keyname + 1) * sizeof(char));
    if (data->keyname == NULL)
    {
        printf("Warning: data->keynname memory allocation failed.\n");
        return 1;
    }
    sscanf(tokens, "%[A-Z0-9a-z-]", data->keyname);

    // printf("   Length check:\n   section: %d\n   key: %d\n   TOTAL: %d\n", len_sectionname, len_keyname, len_sectionname + len_keyname + 1);

    // check for correctness of section and data indentifiers
    if (len_sectionname + len_keyname != strlen(data->sectionname) + strlen(data->keyname))
    {
        printf("Warning: Invalid identifiers in INI file");
        return 1;
    }

    // loading file
    lines = (char **)malloc(lenght * sizeof(char *)); // a hundered character pointers
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        printf("Warning: No such file or directory\n");
        return 1;
    }

    if (lines == NULL)
    {
        printf("Warning: Memory allocation failed (lines)\n");
        fclose(file);
        return 1;
    }

    // reading file
    char buffer[1000];
    int i = 0;
    char delim[] = " ";
    bool section_found = false;

    section = (char *)malloc((len_sectionname + 3) * sizeof(char));
    strcpy(section, "[");
    strcat(section, data->sectionname);
    strcat(section, "]");

    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        if (i == lenght)
        {
            // it means all 100 lines filled
            lenght += n;
            extended_lines = realloc(lines, lenght * (sizeof(char *)));
            if (extended_lines == NULL)
            {
                printf("Warning: Memory allocation failed (extended_lines)\n");
                fclose(file);
                return 1;
            }
            lines = extended_lines;
        }
        // trim newline char -> allocate memory -> copy to line
        if (buffer[strlen(buffer) - 1] == '\n')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }
        line = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if (line == NULL)
        {
            printf("Warning: Memory allocation failed (line)\n");
            fclose(file);
            return 1;
        }
        strcpy(line, buffer);
        lines[i] = line; // filling 100 lines
        i++;

        // printing all the lines
        // printf("%s\n", line);

        // search for header
        if (strcmp(line, section) == 0)
        {
            section_found = true;
        }

        // search for data
        if (section_found == true)
        {
            if (!strcmp(line, "\0")) // if there is an empty line - end of section
            {
                printf("Failed to find key \"%s\" in section %s\n", data->keyname, data->sectionname);
                fclose(file);
                free_memory(line, section, data->filename, data->sectionname, lines, extended_lines);
                return 1;
            }

            tokens = strtok(line, delim); // spitting by space -> first part [data]
            if (!strcmp(tokens, data->keyname))
            {
                tokens = strtok(NULL, delim); // second part "="
                tokens = strtok(NULL, delim); // third part: key
                printf("%s\n", tokens);
                fclose(file);
                free_memory(line, section, data->filename, data->sectionname, lines, extended_lines);
                return 0;
            }
        }
    }

    if (section_found == false)
    {
        printf("Failed to find section [%s]", data->sectionname);
    }

    // deallocating the memory & closing the file
    free(data);
    fclose(file);
    free_memory(line, section, data->filename, data->sectionname, lines, extended_lines);
    return 0;
}