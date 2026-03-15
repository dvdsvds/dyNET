#pragma once

struct HttpRequest {
    char method[8];
    char path[256];
    char version[16];
    int method_len = 0;
    int path_len = 0;
    int version_len = 0;
};

void parse_request(const char* raw, HttpRequest& req);

struct HttpResponse {
    int status_code;
    char status_message[32];
    char body[4096];
    int body_len = 0;
    int content_len = 0;
};

void set_status_code(HttpResponse& res);
void build_response(HttpResponse& res, char* out, int& out_len);