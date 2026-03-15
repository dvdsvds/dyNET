#include "dynet/dysocket.hpp"
#include "dynet/dyhttp.hpp"
#include "dynet/dyutils.hpp"

int main() {
    int server_fd = dy_socket(2, 1, 0);
    if (server_fd < 0) return 1;

    dySocket addr;
    addr.family = 2;
    addr.port = dy_htons(8080);
    addr.addr = 0;
    for (int i = 0; i < 8; i++) addr.zero[i] = 0;

    if (dy_bind(server_fd, &addr, sizeof(dySocket)) < 0) {
        dy_close(server_fd);
        return 1;
    }

    if (dy_listen(server_fd, 10) < 0) {
        dy_close(server_fd);
        return 1;
    }

    while (1) {
        dySocket client_addr;
        unsigned int client_len = sizeof(dySocket);

        int client_fd = dy_accept(server_fd, &client_addr, &client_len);
        if (client_fd < 0) continue;

        char buf[4096] = {};
        int n = dy_read(client_fd, buf, sizeof(buf) - 1);
        if (n <= 0) {
            dy_close(client_fd);
            continue;
        }

        HttpRequest req;
        parse_request(buf, req);

        HttpResponse res;
        res.status_code = 200;
        res.body_len = 0;
        dy_strcat(res.body, res.body_len, "hello from dyNET");
        res.content_len = res.body_len;
        set_status_code(res);

        char out[8192];
        int out_len = 0;
        build_response(res, out, out_len);

        dy_write(client_fd, out, out_len);
        dy_close(client_fd);
    }

    dy_close(server_fd);
    return 0;
}