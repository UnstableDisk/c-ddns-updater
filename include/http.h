#ifndef HTTP_H
#define HTTP_H

int http_get(const char *url, char *buffer, int buffer_size);

int http_get_basic_auth(const char *url,
                        const char *username,
                        const char *password,
                        char *buffer,
                        int buffer_size);

int http_put_basic_auth(const char *url,
                        const char *username,
                        const char *password,
                        const char *json_body,
                        char *buffer,
                        int buffer_size);

#endif
