# C DDNS Updater

A lightweight Dynamic DNS (DDNS) updater written in C for Linux.

The program automatically keeps a Name.com DNS A record synchronized with your current public IP address. It is intended to run on a home server with a dynamic public IP and only updates the DNS record when the IP address changes.

---

## Features

- Retrieve the current public IP address
- Load configuration from a file
- Authenticate with the Name.com REST API
- Retrieve DNS records
- Parse JSON responses using cJSON
- Compare the current DNS record with the current public IP
- Update the DNS record only when necessary
- Verify the update after it is completed
- Lightweight implementation using libcurl and cJSON

---

## Project Structure

```
c-ddns-updater/
├── configs/
│   ├── ddns.conf.example
│   └── ddns.conf          (not committed)
├── include/
├── providers/
├── src/
├── Makefile
├── README.md
└── .gitignore
```

---

## Dependencies

Ubuntu:

```bash
sudo apt update

sudo apt install \
    build-essential \
    libcurl4-openssl-dev \
    libcjson-dev
```

---

## Build

```bash
make
```

---

## Run Manually

```bash
./ddns
```

---

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

**(Never commit your real configuration file or API token.)**

---

## Automatic Execution with systemd

### Commands

```bash
make run
```

Install and enable automatic DDNS updates.

```bash
make stop
```

Stop and disable automatic updates.

```bash
make restart
```

Restart the timer after making changes.

```bash
make status
```

Display the timer status.

```bash
make logs
```

View the latest log messages.

```bash
make clean-systemd
```

Remove the installed systemd service and timer from the system.


---

## Current Workflow

```
Get public IP
        │
        ▼
Retrieve DNS records
        │
        ▼
Find matching A record
        │
        ▼
Compare public IP with DNS IP
        │
   ┌────┴────┐
   │         │
Same      Different
   │         │
 Exit    Update DNS
             │
             ▼
      Verify update
```

---

## Current Status

- [x] Configuration loader
- [x] HTTP client
- [x] HTTPS client
- [x] Basic Authentication
- [x] Public IP detection
- [x] Name.com API integration
- [x] DNS record retrieval
- [x] JSON parsing
- [x] DNS record comparison
- [x] DNS record update
- [x] Update verification
- [ ] Local IP cache optimization
- [ ] Retry mechanism
- [ ] Logging
- [ ] IPv6 (AAAA) support
- [ ] Multiple providers
- [ ] Multiple domains

---

## Security

The following files should **never** be committed:

```
configs/ddns.conf
server.key
ddns
```

The repository includes a `ddns.conf.example` file that demonstrates the required configuration format.

---

## Future Work

- Cloudflare provider
- DuckDNS provider
- No-IP provider
- IPv6 support
- Local cache to reduce unnecessary API requests
- Automatic retries
- Logging to file
- Multiple DNS providers
- Multiple host records
- Docker support

---

## License

MIT License
