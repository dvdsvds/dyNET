#include "dynet/dysocket.hpp"
#include "dynet/dyhttp.hpp"
#include "dynet/dyutils.hpp"
#include "dynet/dyrouter.hpp"
#include "dynet/dythread.hpp"

void home_handler(HttpRequest&, HttpResponse& res) {
    res.status_code = 200;
    dy_strcat(res.body, res.body_len, "hello from dyNET\n");
    res.content_len = res.body_len;
    set_status_code(res);
}

struct ThreadArg {
    int client_fd;
    Router* router;
};

int thread_func(void* arg) {
    ThreadArg* targ = reinterpret_cast<ThreadArg*>(arg);
    int client_fd = targ->client_fd;
    Router* router = targ->router;

    char buf[4096] = {};
    int n = dy_read(client_fd, buf, sizeof(buf) - 1);
    dy_write(1, "read ok\n", 8);
    if (n <= 0) {
        dy_close(client_fd);
        return 0;
    }

    HttpRequest req;
    parse_request(buf, req);
    dy_write(1, "parse ok\n", 9);

    HttpResponse res;
    res.body_len = 0;
    res.content_len = 0;
    router_dispatch(*router, req, res);
    dy_write(1, "dispatch ok\n", 12);

    char out[8192];
    int out_len = 0;
    build_response(res, out, out_len);
    dy_write(client_fd, out, out_len);
    dy_close(client_fd);
    dy_free(targ, sizeof(ThreadArg));
    return 0;
}

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

    Route route;
    dy_strcpy(route.method, "GET");
    dy_strcpy(route.path, "/");
    route.handler = home_handler; 
    Router router = {};
    route_init(router, 8);
    router_add(router, route);

    while (1) {
        dySocket client_addr;
        unsigned int client_len = sizeof(dySocket);
        int client_fd = dy_accept(server_fd, &client_addr, &client_len);
        if (client_fd < 0) continue;

        ThreadArg* targ = reinterpret_cast<ThreadArg*>(dy_malloc(sizeof(ThreadArg)));
        targ->client_fd = client_fd;
        targ->router = &router;
        
        int tid = dy_thread_create(thread_func, targ);
        char tbuf[16];
        dy_itoa(tid, tbuf);
        dy_write(1, tbuf, 3);
        dy_write(1, "\n", 1);
    }

    dy_close(server_fd);
    return 0;
}