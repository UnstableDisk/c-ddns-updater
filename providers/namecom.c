#include <string.h>
#include <cjson/cJSON.h>

#include "namecom.h"
#include "http.h"

#include <stdio.h>

int namecom_list_records(const Config *config, char *buffer, int buffer_size)
{
    char url[512];

    snprintf(url,
             sizeof(url),
             "https://api.name.com/core/v1/domains/%s/records",
             config->domain);

    return http_get_basic_auth(url,
                               config->username,
                               config->token,
                               buffer,
                               buffer_size);
}

int namecom_find_a_record(const char *json, const Config *config, DnsRecord *record)
{
    memset(record, 0, sizeof(DnsRecord));

    cJSON *root = cJSON_Parse(json);
    if (!root) {
        return -1;
    }

    cJSON *records = cJSON_GetObjectItem(root, "records");
    if (!cJSON_IsArray(records)) {
        cJSON_Delete(root);
        return -1;
    }

    cJSON *item = NULL;
    cJSON_ArrayForEach(item, records) {
        cJSON *type = cJSON_GetObjectItem(item, "type");
        cJSON *host = cJSON_GetObjectItem(item, "host");
        cJSON *answer = cJSON_GetObjectItem(item, "answer");
        cJSON *id = cJSON_GetObjectItem(item, "id");

        if (!cJSON_IsString(type) || !cJSON_IsString(answer) || !cJSON_IsNumber(id)) {
            continue;
        }

        const char *host_value = cJSON_IsString(host) ? host->valuestring : "";

        if (strcmp(type->valuestring, "A") == 0 &&
            ((strcmp(config->host, "@") == 0 && strcmp(host_value, "") == 0) ||
             strcmp(config->host, host_value) == 0)) {

            record->id = id->valueint;
            strncpy(record->answer, answer->valuestring, sizeof(record->answer) - 1);
            record->found = 1;

            cJSON_Delete(root);
            return 0;
        }
    }
    cJSON_Delete(root);
    return 0;
}

int namecom_update_a_record(const Config *config,
                            int record_id,
                            const char *new_ip,
                            char *buffer,
                            int buffer_size)
{
    char url[512];
    char json[512];

    snprintf(url,
             sizeof(url),
             "https://api.name.com/core/v1/domains/%s/records/%d",
             config->domain,
             record_id);

    snprintf(json,
             sizeof(json),
             "{\"host\":\"%s\",\"type\":\"A\",\"answer\":\"%s\",\"ttl\":%d}",
             strcmp(config->host, "@") == 0 ? "" : config->host,
             new_ip,
             config->ttl);

    return http_put_basic_auth(url,
                               config->username,
                               config->token,
                               json,
                               buffer,
                               buffer_size);
}
