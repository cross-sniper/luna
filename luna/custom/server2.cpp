// Assuming luna_State and lunaL_checktype are part of your luna C API bindings.
static int cbind(luna_State *L) {
    // Check if the argument is a table
    if (!luna_istable(L, 1)) {
        lunaL_error(L, "Argument must be a table");
        return 0;
    }

    // Iterate over the table and bind URLs to files
    luna_pushnil(L);  // Start iterating from the beginning
    while (luna_next(L, 1) != 0) {
        // Key is at index -2 and value is at index -1
        const char *url = lunaL_checkstring(L, -2);
        const char *file = lunaL_checkstring(L, -1);

        url_to_file_[url] = file;

        // Pop the value, leaving the key for the next iteration
        luna_pop(L, 1);
    }

    return 0;
}

static int crun(luna_State *L) {
    int port = lunaL_checknumber(L, 1);

    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    int reuse = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0) {
        perror("Error setting socket option");
        exit(EXIT_FAILURE);
    }

    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    if (::bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        perror("Error binding socket");
        exit(EXIT_FAILURE);
    }

    if (listen(server_socket, 5) < 0) {
        perror("Error listening on socket");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", port);

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        if (client_socket < 0) {
            perror("Error accepting connection");
            continue;
        }

        // Handle client request
        if (handle_client_request(client_socket) != 0) {
            // Error handling request, exit
            close(server_socket);
            close(client_socket);
            exit(EXIT_FAILURE);
        }

        close(client_socket);
    }

    return 0;
}

