_This project has been created as part of the 42 curriculum by ahoummad, mnasih

# ft_irc

## Description

The **ft_irc** project is an Internet Relay Chat (IRC) server built in C++98. Its primary goal is to provide a fully functional, standard-compliant centralized server capable of handling multiple asynchronous client connections via non-blocking I/O multiplexing. The server allows clients to connect, authenticate with a predefined password, communicate via channels, send private messages, and execute various standard IRC commands such as `JOIN`, `PART`, `NICK`, `MODE`, `KICK`, and `TOPIC`. It also implements an automated chat bot to enrich the user experience.

Through this project, concepts such as network programming, sockets, event-driven architecture, and the intricacies of the IRC protocol text-based messaging system are thoroughly explored and mastered.

## Instructions

### Prerequisites
- A standard C++ compiler (e.g., `c++`, `clang++`, or `g++`)
- `make` program

### Compilation

You can compile the project using the provided `Makefile`. To build the server executable, run the following command at the root of the repository:

```bash
make
```

This will compile the source files and generate an executable named `ircserv`.

Other available `make` commands:
- `make clean`: Removes the object files directory.
- `make fclean`: Removes the object files directory and the `ircserv` executable.
- `make re`: Recompiles the whole project from scratch.

### Execution

You can run the server by providing a port number and a connection password as arguments:

```bash
./ircserv <port> <password>
```

- `<port>`: The port on which the server will listen for incoming IRC client connections (e.g., `6667`).
- `<password>`: The server connection password that clients will need to provide via the `PASS` command in order to participate in the IRC network.

### Connecting with a Client
You can use standard IRC clients (like irssi, WeeChat, or LimeChat) to connect to the server. Example with `irssi`:
```bash
irssi -c 127.0.0.1 -p 6667 -w <password> -n <nickname>
```

## Resources

### References
- [RFC 1459: Internet Relay Chat Protocol](https://datatracker.ietf.org/doc/html/rfc1459) - The fundamental specification for the IRC protocol.
- **Beej's Guide to Network Programming** - A classic and highly recommended guide for learning socket programming.
- C++98 reference guides on [cppreference.com](https://en.cppreference.com/)

### AI Usage
During the development of this project, Artificial Intelligence was used exclusively for the generation and formatting of this `README.md` file. No AI tools or language models were used in designing, writing, or debugging the source code of the IRC server itself.
