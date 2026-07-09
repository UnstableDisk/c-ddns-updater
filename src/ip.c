#include "ip.h"
#include "http.h"

int get_public_ip(char *buffer, int buffer_size)
{
    return http_get("https://api.ipify.org", buffer, buffer_size);
}
