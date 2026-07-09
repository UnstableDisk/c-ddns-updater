#ifndef CONFIG_H
#define CONFIG_H

typedef struct {
    char provider[64];
    char domain[256];
    char host[128];
    char username[128];
    char token[256];
    int ttl;
} Config;

int load_config(const char *path, Config *config);

#endif
