#pragma once

#include "bt_client.h"

typedef struct {
  char rmtbtaddr[13];
  role_t btmode;
} settings_t;

extern settings_t settings;

void loadSettings();
void saveSettings();