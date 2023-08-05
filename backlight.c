#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_backlight() {
  FILE* file = fopen("/sys/class/backlight/intel_backlight/brightness", "r");
  if (file == NULL) {
    printf("get_backlight(): failed to open device\n");
    exit(1);
  }
  int value;
  fscanf(file, "%d", &value);
  return value;
}

int get_max_backlight() {
  FILE* file = fopen("/sys/class/backlight/intel_backlight/max_brightness", "r");
  if (file == NULL) {
    printf("get_max_backlight(): failed to open device\n");
    exit(1);
  }
  int value;
  fscanf(file, "%d", &value);
  return value;
}

int set_backlight(int value) {
  FILE* file = fopen("/sys/class/backlight/intel_backlight/brightness", "w");
  if (file == NULL) {
    printf("set_backlight(): failed to open device\n");
    exit(1);
  }
  fprintf(file, "%d", value);
  return 0;
}
  
int main(int argc, char* argv[]) {
  if (argc != 2) {
    int value = get_backlight();
    printf("%d\n", value);
    return 0;
  }

  if (strcmp(argv[1], "off") == 0) {
    set_backlight(0);
    return 0;
  }
  else if (strcmp(argv[1], "on" ) == 0) {
    int backlight = get_backlight();
    if (backlight != 0) return 0;
    int max_backlight = get_max_backlight();
    set_backlight(max_backlight / 2); // 50% brightness
    return 0;
  }
  else if (strcmp(argv[1], "toggle") == 0) {
    int curr_backlight = get_backlight();
    if (curr_backlight == 0) {
      int max_backlight = get_max_backlight();
      int value = max_backlight / 2;
      set_backlight(value);
      return 0;
    } else {
      set_backlight(0);
      return 0;
    }
  }

  char sign = argv[1][0];
  if (sign != '+' && sign != '-') {
    int value = atoi(argv[1]);
    set_backlight(value);
    return 0;
  } else {
    int change = atoi(&argv[1][1]); // string after sign --> int
    int value = get_backlight();
    if (sign == '+') value += change;
    if (sign == '-') value -= change;
    set_backlight(value);
    return 0;
  }
}
