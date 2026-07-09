#ifndef NAMECOM_H
#define NAMECOM_H

#include "config.h"

typedef struct {
    int id;
    char answer[64];
    int found;
} DnsRecord;

int namecom_list_records(const Config *config, char *buffer, int buffer_size);

int namecom_find_a_record(const char *json, const Config *config, DnsRecord *record);

int namecom_update_a_record(const Config *config,
                            int record_id,
                            const char *new_ip,
                            char *buffer,
                            int buffer_size);
#endif
