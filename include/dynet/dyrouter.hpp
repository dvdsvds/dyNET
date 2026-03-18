#pragma once
#include "dyhttp.hpp"
#include "dyutils.hpp"

struct Route {
    char method[8];
    char path[512];
    void (*handler)(HttpRequest&, HttpResponse&);
};

struct Router {
    Route* routes;
    int route_count;
    int capacity;
};

void route_init(Router& router, int capacity);
void router_add(Router& router, Route& route);
void router_dispatch(Router& router, HttpRequest& req, HttpResponse& res);
void router_free(Router& router);
