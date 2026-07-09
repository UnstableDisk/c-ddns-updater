CC = gcc

CFLAGS = -Wall -Wextra -std=c17 -Iinclude

SRC := ${wildcard src/*.c} $(wildcard providers/*.c)

TARGET = ddns

all:
	$(CC) $(CFLAGS) $(SRC) -lcurl -lcjson -o $(TARGET)

run:
	sudo systemctl daemon-reload
	sudo systemctl enable --now ddns-updater.timer

stop:
	sudo systemctl disable --now ddns-updater.timer

restart:
	sudo systemctl daemon-reload
	sudo systemctl restart ddns-updater.timer

status:
	systemctl list-timers | grep ddns

logs:
	journalctl -u ddns-updater.service -n 50

clean-systemd:
	sudo systemctl disable --now ddns-updater.timer
	sudo rm -f /etc/systemd/system/ddns-updater.service
	sudo rm -f /etc/systemd/system/ddns-updater.timer
	sudo systemctl daemon-reload

clean:
	rm -f $(TARGET)
