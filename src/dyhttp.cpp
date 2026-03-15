#include "dynet/dyhttp.hpp"
#include "dynet/dyutils.hpp"

void parse_request(const char* raw, HttpRequest& req) {
    int i = 0;
    while(raw[i] != ' ') {
        req.method[i] = raw[i];
        i++;
        req.method_len++;
    }
    i++;

    int j = 0;
    while(raw[i] != ' ') {
        req.path[j] = raw[i];
        i++;
        j++;
        req.path_len++;
    }
    i++;

    int h = 0;
    while(raw[i] != '\r') {
        req.version[h] = raw[i];
        i++;
        h++;
        req.version_len++;
    }
}


void set_status_code(HttpResponse& res) {
    switch(res.status_code) {
        case 100:
            dy_strcpy(res.status_message, "Continue");
            break;
        case 101:
            dy_strcpy(res.status_message, "Switching Protocols");
            break;
        case 200:
            dy_strcpy(res.status_message, "OK");
            break;
        case 201:
            dy_strcpy(res.status_message, "Created");
            break;
        case 202:
            dy_strcpy(res.status_message, "Accepted");
            break;
        case 204:
            dy_strcpy(res.status_message, "No Content");
            break;
        case 301:
            dy_strcpy(res.status_message, "Moved Permanently");
            break;
        case 302:
            dy_strcpy(res.status_message, "Found");
            break;
        case 304:
            dy_strcpy(res.status_message, "Not Modified");
            break;
        case 307:
            dy_strcpy(res.status_message, "Temporary Redirect");
            break;
        case 308:
            dy_strcpy(res.status_message, "Permanent Redirect");
            break;
        case 400:
            dy_strcpy(res.status_message, "Bad Request");
            break;
        case 401:
            dy_strcpy(res.status_message, "Unauthorized");
            break;
        case 403:
            dy_strcpy(res.status_message, "Forbidden");
            break;
        case 404:
            dy_strcpy(res.status_message, "Not Found");
            break;
        case 405:
            dy_strcpy(res.status_message, "Method Not Allowed");
            break;
        case 408:
            dy_strcpy(res.status_message, "Request Timeout");
            break;
        case 409:
            dy_strcpy(res.status_message, "Conflict");
            break;
        case 410:
            dy_strcpy(res.status_message, "Gone");
            break;
        case 429:
            dy_strcpy(res.status_message, "Too Many Requests");
            break;
        case 500:
            dy_strcpy(res.status_message, "Internal Server Error");
            break;
        case 501:
            dy_strcpy(res.status_message, "Not Implemented");
            break;
        case 502:
            dy_strcpy(res.status_message, "Bad Gateway");
            break;
        case 503:
            dy_strcpy(res.status_message, "Service Unavailable");
            break;
        case 504:
            dy_strcpy(res.status_message, "Gateway Timeout");
            break;
        default:
            dy_strcpy(res.status_message, "Invalid Error");
            break;
    }
}

void build_response(HttpResponse& res, char* out, int& out_len) {
    out_len = 0;
    dy_strcat(out, out_len, "HTTP/1.1 ");

    char code_buf[21];
    dy_itoa(res.status_code, code_buf);
    dy_strcat(out, out_len, code_buf);
    dy_strcat(out, out_len, " ");

    dy_strcat(out, out_len, res.status_message);
    dy_strcat(out, out_len, "\r\n");

    dy_strcat(out, out_len, "Content-Length: ");
    char len_buf[21];    
    dy_itoa(res.body_len, len_buf);
    dy_strcat(out, out_len, len_buf);

    dy_strcat(out, out_len, "\r\n\r\n");
    dy_strcat(out, out_len, res.body);
}