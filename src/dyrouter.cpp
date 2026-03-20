#include "dynet/dyrouter.hpp"

void route_init(Router& router, int capacity) {
    router.routes = reinterpret_cast<Route*>(dy_malloc(sizeof(Route) * capacity));
    router.route_count = 0;
    router.capacity = capacity;
}

void router_add(Router& router, Route& route) {
    if(router.route_count == router.capacity) {
        router.routes = reinterpret_cast<Route*>(dy_realloc(
            router.routes,
            sizeof(Route) * router.capacity,
            sizeof(Route) * router.capacity * 2
        ));
        router.capacity *= 2;
    }
    router.routes[router.route_count] = route;
    router.route_count++;
}

void router_dispatch(Router& router, HttpRequest& req, HttpResponse& res) {
    for(int i = 0; i < router.route_count; i++) {
        if(dy_strcmp(router.routes[i].method, req.method) && dy_strcmp(router.routes[i].path, req.path)) {
            router.routes[i].handler(req, res);
            return;
        } 
    }
    res.status_code = 404;
    res.body_len = 0;
    dy_strcat(res.body, res.body_len, "Not Found");
    res.content_len = res.body_len;
    set_status_code(res);
}

void router_free(Router& router) {
    dy_free(router.routes, sizeof(Route) * router.capacity);
}
