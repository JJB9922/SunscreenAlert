#include "fetch_uv_index.h"
#include "cJSON.h"

#define MAX_RESPONSE_SIZE 4096

// Weather api endpoint incl. api key in secrets

char response_buffer[MAX_RESPONSE_SIZE];
size_t response_length = 0;

esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_DATA:
        if (response_length + evt->data_len < MAX_RESPONSE_SIZE)
        {
            memcpy(response_buffer + response_length, evt->data, evt->data_len);
            response_length += evt->data_len;
        }
        else
        {
            ESP_LOGE("HTTP_CLIENT", "Response too large, increase MAX_RESPONSE_SIZE");
        }
        break;
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

double process_response(char *buffer, size_t length) {
    buffer[length] = '\0';

    cJSON *root = cJSON_Parse(buffer);
    if (!root) {
        printf("Error: Failed to parse JSON\n");
        return 0.0;
    }

    cJSON *result = cJSON_GetObjectItem(root, "result");
    if (result) {
        cJSON *uv_max = cJSON_GetObjectItem(result, "uv_max");
        if (uv_max) {
            printf("Max UV: %.4f\n", uv_max->valuedouble);
            cJSON_Delete(root);
            return(uv_max->valuedouble);
        } else {
            printf("UV max not found in JSON response.\n");
        }
    } else {
        printf("Error: 'result' not found in JSON\n");
    }

    cJSON_Delete(root);
    return 0.0;
}

double fetch_uv_index()
{
    esp_http_client_config_t config = {
        .url = WEATHER_API_ENDPOINT,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .event_handler = http_event_handler,
    };

    esp_http_client_handle_t client = esp_http_client_init(&config);
    esp_http_client_set_header(client, "x-access-token", "openuv-3x66prlvinbd3p-io");
    esp_err_t err = esp_http_client_perform(client);

    double uv_index = 0;

    if (err == ESP_OK)
    {
        uv_index = process_response(response_buffer, response_length);
        esp_http_client_cleanup(client);
        return uv_index;
    }
    else
    {
        ESP_LOGE("HTTP_CLIENT", "HTTP GET request failed: %s", esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    return 0.0;
}