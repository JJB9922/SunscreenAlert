#include "fetch_uv_index.h"

//Weather api endpoint incl. api key in secrets

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGE("HTTP", "HTTP_EVENT_ERROR");
            break;
        default:
            break;
    }
    return ESP_OK;
}

void fetch_uv_index()
{
    esp_http_client_config_t config = {
        .url = WEATHER_API_ENDPOINT,
        .event_handler = http_event_handler,
    };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        int content_length = esp_http_client_get_content_length(client);
        char *buffer = (char *)malloc(content_length + 1);
        if (buffer) {
            int bytes_read = esp_http_client_read(client, buffer, content_length);
            printf("bytes read:%d", bytes_read);
            free(buffer);
        } else {
            ESP_LOGE("HTTP", "Failed to allocate memory for HTTP response");
        }
    } else {
        ESP_LOGE("HTTP", "HTTP request failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}
