#include "esp_log.h"
#include "nvs_flash.h"
#include "settings.h"

#define LOG_SET "SETTINGS"

settings_t settings;
extern nvs_handle_t nvs_flsh_btw;

void saveSettings()
{
  // TODO -- Do a read first, if nothing differes quit, save a flash write
  esp_err_t err = nvs_set_blob(nvs_flsh_btw, "settings", (void *)&settings, sizeof(settings_t));
  if(err == ESP_OK) {
    ESP_LOGI(LOG_SET, "Blob store success");
  } else {
    ESP_LOGE(LOG_SET,"Unable to store blob - %s", esp_err_to_name(err));
 }
  err = nvs_commit(nvs_flsh_btw);
  if(err == ESP_OK) {
    ESP_LOGI(LOG_SET, "Settings written Successfully");
  } else {
    ESP_LOGE(LOG_SET,"Unable to write settings - %s", esp_err_to_name(err));
 }
}

void loadSettings()
{
  ESP_LOGI(LOG_SET,"Reading settings\n");
  size_t length = sizeof(settings_t);
  esp_err_t ret = nvs_get_blob(nvs_flsh_btw, "settings", (void*)&settings, &length);
  if(ret == ESP_OK && length == sizeof(settings_t)) {
    ESP_LOGI(LOG_SET, "Settings Read Successfully");
    return;
  } else {
    if(ret == ESP_OK) {
      ESP_LOGE(LOG_SET,"Incorrect Settings Length");
    } else {
      ESP_LOGE(LOG_SET,"Error (%s) reading\n", esp_err_to_name(ret));
    }
  }
  // Settings invalid, clear the memory
  memset(&settings, 0, sizeof(settings_t));
}