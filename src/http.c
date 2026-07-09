#include "http.h"

#include <curl/curl.h>
#include <stdio.h>
#include <string.h>

struct HttpBuffer {
    char *data;
    size_t capacity;
    size_t length;
};

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t total = size * nmemb;
    struct HttpBuffer *buf = (struct HttpBuffer *)userp;

    if (buf->length + total >= buf->capacity) {
        total = buf->capacity - buf->length - 1;
    }

    memcpy(buf->data + buf->length, contents, total);
    buf->length += total;
    buf->data[buf->length] = '\0';

    return size * nmemb;
}

int http_get(const char *url, char *buffer, int buffer_size)
{
    if (!url || !buffer || buffer_size <= 0) {
        return -1;
    }

    buffer[0] = '\0';

    CURL *curl = curl_easy_init();
    if (!curl) {
        return -1;
    }

    char error_buffer[CURL_ERROR_SIZE];
    error_buffer[0] = '\0';

    struct HttpBuffer response = {
        .data = buffer,
        .capacity = (size_t)buffer_size,
        .length = 0
    };

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "c-ddns-updater/0.1");

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        fprintf(stderr, "curl error: %s\n",
                error_buffer[0] ? error_buffer : curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);
    return 0;
}

int http_get_basic_auth(const char *url,
                        const char *username,
                        const char *password,
                        char *buffer,
                        int buffer_size)
{
    if (!url || !username || !password || !buffer || buffer_size <= 0) {
        return -1;
    }

    memset(buffer, '\0', buffer_size);

    CURL *curl = curl_easy_init();
    if (!curl) {
        return -1;
    }

    char error_buffer[CURL_ERROR_SIZE];
    error_buffer[0] = '\0';

    struct HttpBuffer response = {
        .data = buffer,
        .capacity = (size_t)buffer_size,
        .length = 0
    };

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_HTTPAUTH, CURLAUTH_BASIC);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "c-ddns-updater/0.1");

    CURLcode result = curl_easy_perform(curl);

    if (result != CURLE_OK) {
        fprintf(stderr, "curl error: %s\n",
                error_buffer[0] ? error_buffer : curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }

    curl_easy_cleanup(curl);
    return 0;
}
