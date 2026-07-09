# C DDNS Updater

A lightweight Dynamic DNS (DDNS) updater written in C for Linux.

The program automatically keeps a DNS A record synchronized with your current public IP address. It is designed to run on a home server with a dynamic IP address and currently supports the Name.com DNS API.

## Features

- Retrieve the current public IP address
- Read configuration from a file
- Query DNS records using the Name.com API
- Compare the current DNS record with the public IP
- Update the DNS record only when necessary (coming soon)
- Verify updates after they are applied (coming soon)
- Lightweight C implementation using libcurl and cJSON

## Project Structure

```
c-ddns-updater/
├── configs/
├── include/
├── providers/
├── src/
├── Makefile
└── README.md
```

## Dependencies

Ubuntu:

```bash
sudo apt update

sudo apt install \
    build-essential \
    libcurl4-openssl-dev \
    libcjson-dev
```

## Build

```bash
make
```

## Run

```bash
./ddns
```

## Configuration

Create:

```
configs/ddns.conf
```

Example:

```ini
provider=namecom
domain=example.com
host=@
username=YOUR_USERNAME
token=YOUR_API_TOKEN
ttl=300
```

Never commit your real API token.

## Current Status

- [x] HTTP client
- [x] HTTPS support
- [x] Configuration loader
- [x] Public IP detection
- [x] Name.com authentication
- [x] DNS record retrieval
- [x] DNS record parsing
- [ ] DNS record update
- [ ] Automatic verification
- [ ] systemd service
- [ ] Logging

## Future Work

- Cloudflare support
- No-IP support
- IPv6 (AAAA) support
- Multiple domains
- Multiple hosts
- Automatic daemon mode
- Docker support

## License

MIT License
