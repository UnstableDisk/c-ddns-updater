#include "config.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void trim_newline(char *s)
{
    s[strcspn(s, "\r\n")] = '\0';
}

int load_config(const char *path, Config *config)
{
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open config file");
        return -1;
    }

    memset(config, 0, sizeof(Config));
    config->ttl = 300;

    char line[512];

    while (fgets(line, sizeof(line), file)) {
        trim_newline(line);

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        char *equal = strchr(line, '=');
        if (!equal) {
            continue;
        }

        *equal = '\0';
        char *key = line;
        char *value = equal + 1;

        if (strcmp(key, "provider") == 0) {
            strncpy(config->provider, value, sizeof(config->provider) - 1);
        } else if (strcmp(key, "domain") == 0) {
            strncpy(config->domain, value, sizeof(config->domain) - 1);
        } else if (strcmp(key, "host") == 0) {
            strncpy(config->host, value, sizeof(config->host) - 1);
        } else if (strcmp(key, "username") == 0) {
            strncpy(config->username, value, sizeof(config->username) - 1);
        } else if (strcmp(key, "token") == 0) {
            strncpy(config->token, value, sizeof(config->token) - 1);
        } else if (strcmp(key, "ttl") == 0) {
            config->ttl = atoi(value);
        }
    }

    fclose(file);
    return 0;
}

