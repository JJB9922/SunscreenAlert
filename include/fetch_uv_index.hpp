#ifndef FETCH_UV_INDEX_HPP
#define FETCH_UV_INDEX_HPP

#include "secrets.hpp"

#include "esp_system.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"

esp_err_t http_event_handler(esp_http_client_event_t *evt);
double process_response(char *buffer, size_t length);
double fetch_uv_index();

#endif