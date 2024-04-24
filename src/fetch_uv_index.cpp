#include "fetch_uv_index.h"

//Weather api endpoint incl. api key in secrets

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI("HTTP", "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI("HTTP", "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            if (!esp_http_client_is_chunked_response(evt->client)) {
                printf("%.*s", evt->data_len, (char*)evt->data);
            }
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI("HTTP", "HTTP_EVENT_ON_FINISH");
            break;
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
        ESP_LOGI("HTTP", "Connected to API successfully");
    } else {
        ESP_LOGE("HTTP", "HTTP request failed: %s", esp_err_to_name(err));
    }
    
    esp_http_client_cleanup(client);
}
