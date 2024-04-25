#include "fetch_uv_index.h"

// Weather api endpoint incl. api key in secrets

esp_err_t http_event_handler(esp_http_client_event_t *evt) {
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGE("HTTP_CLIENT", "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGI("HTTP_CLIENT", "HTTP_EVENT_DISCONNECTED");
            break;
        default:
            ESP_LOGE("HTTP_CLIENT", "CERTIFIED BAD TIMES HAPPENED");
            break;
    }
    return ESP_OK;
}

void fetch_uv_index()
{   
    esp_http_client_config_t config = {
        .url = WEATHER_API_ENDPOINT,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .event_handler = http_event_handler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        printf("Connected!\n");
        // Next step - parse all this 
    }
    else
    {
        ESP_LOGE("HTTP_CLIENT", "HTTP GET request failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}