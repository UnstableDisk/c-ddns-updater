#include <stdio.h>
#include <string.h>

#include "ip.h"
#include "config.h"
#include "namecom.h"

int main(void)
{
    char ip[64] = {0};
    char records_json[16384] = {0};
    Config config;

    printf("===================================\n");
    printf("   C DDNS Updater v0.1.0\n");
    printf("===================================\n");

    if (load_config("configs/ddns.conf", &config) != 0) {
        printf("Failed to load config.\n");
        return 1;
    }

    if (get_public_ip(ip, sizeof(ip)) != 0) {
        printf("Failed to get public IP.\n");
        return 1;
    }

    printf("Public IP: %s\n", ip);

    if (namecom_list_records(&config, records_json, sizeof(records_json)) != 0) {
        printf("Failed to list Name.com DNS records.\n");
        return 1;
    }

    DnsRecord record;

    if (namecom_find_a_record(records_json, &config, &record) != 0) {
        printf("Failed to parse Name.com DNS records.\n");
        return 1;
    }

    if (!record.found) {
        printf("No matching A record found.\n");
        return 1;
    }

    printf("DNS record IP: %s\n", record.answer);
    printf("DNS record ID: %d\n", record.id);

    if (strcmp(ip, record.answer) == 0) {
        printf("No update needed.\n");
    } else {
        printf("Update needed: %s -> %s\n", record.answer, ip);
    }

    return 0;
}
