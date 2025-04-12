# slowme

A slow lorris in C

## Task

A lightweight and minimal reproduction of the classic Slowloris denial-of-service tool, written in C with minimal external dependencies. This project is designed for educational purposes, providing insight into how Slowloris attacks exhaust server connections by holding them open as long as possible.

The tool allows fine-grained control over the behavior of the attack through various command-line options:

### Features & Options:
-p, --port: Specify the target web server port (default: 80).

-s, --sockets: Set the number of sockets to use for the test.

-v, --verbose: Enable verbose output to monitor request flow and socket status.

-ua, --randuseragents: Randomize the User-Agent header for each request to evade basic filters.

-x, --useproxy: Connect using a SOCKS5 proxy (useful for anonymity or bypassing rate limits).

--https: Enable HTTPS support for targeting secure servers.

--sleeptime: Configure the sleep interval between sending partial headers (in seconds), allowing flexible timing for the attack.

### Architecture overview / flowchart




## Installation



## Usage





### The Core Team
* [Lorris BELUS](//github.com/Lbelus) - Developer

()=()
(^;^)
C × C
()_()
