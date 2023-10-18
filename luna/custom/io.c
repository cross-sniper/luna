#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//match_regex("sg", pattern);


static int luna_readfile(luna_State *L) {
    const char *filename = lunaL_checkstring(L, 1);
    FILE *file = fopen(filename, "r");
    if (file) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);
        char *contents = (char *)malloc(size + 1);
        if (contents) {
            fread(contents, 1, size, file);
            contents[size] = '\0';
            fclose(file);
            luna_pushstring(L, contents);
            free(contents);
            return 1;
        }
        fclose(file);
    }
    return 0;  // File not found or error occurred
}
static int luna_writefile(luna_State *L) {
    const char *filename = lunaL_checkstring(L, 1);
    const char *content = lunaL_checkstring(L, 2);
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs(content, file);
        fclose(file);
        return 1; // Success
    }
    return 0;  // Error occurred
}

static int p_input(luna_State *L) {
    const char *prompt = lunaL_optstring(L, 1, NULL);
    char buffer[1024];
    if (prompt) {
        printf("%s", prompt);
        fflush(stdout);
    }
    if (fgets(buffer, sizeof(buffer), stdin)) {
        // Find the newline character and replace it with a null terminator
        size_t len = strcspn(buffer, "\n");
        buffer[len] = '\0';

        luna_pushstring(L, buffer);
        return 1; // Success
    }
    return 0; // Error occurred
}



#include <curl/curl.h>

static int luna_curl_request(luna_State *L) {
    return 1;
}

