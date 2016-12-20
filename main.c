#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CURRENT_BRIGHTNESS_FILE "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_FILE "/sys/class/backlight/intel_backlight/max_brightness"
#define BUFFER_SIZE 10
#define NB_STEP 10

char buffer[BUFFER_SIZE];

int maxBrightness() {
    FILE* max_brightness_file = fopen(MAX_BRIGHTNESS_FILE, "r");
    if(max_brightness_file == NULL) {
        perror("Cannot open brightness file: ");
        return -1;
    }
    size_t nb_read_bytes = fread(buffer, 1, BUFFER_SIZE - 1, max_brightness_file);
    fclose(max_brightness_file);

    if(nb_read_bytes > 0) {
        return atoi(buffer);
    } else {
        perror("Cannot read max brightness file: ");
        return -1;
    }
}

void printUsage(char* exeName) {
    printf("Usage : %s {++ or --}\n", exeName);
}

int main(int argc, char* argv[]) {
    FILE* current_brightness_file;
    size_t nb_bytes;
    int current_brightness, new_brightness, step_brightness, max_brightness;
    bool increment, verbose = false;

    if(argc != 2 && argc != 3) {
        printUsage(argv[0]);
        exit(EXIT_SUCCESS);
    } else {
        if(strncmp(argv[1], "++", 3) == 0) {
            increment = true;
        }
        else if(strncmp(argv[1], "--", 3) == 0) {
            increment = false;
        }
        else {
            printUsage(argv[0]);
            exit(EXIT_SUCCESS);
        }

        if(argc == 3) {
            if(strncmp(argv[2], "-v", 3) == 0) {
                verbose = true;
            } else {
                printUsage(argv[0]);
                exit(EXIT_SUCCESS);
            }
        }

    }

	memset(buffer, '\0', BUFFER_SIZE);

    max_brightness = maxBrightness();
    if (max_brightness < 0) {
        exit(EXIT_FAILURE);
    }
    step_brightness = max_brightness / NB_STEP;

    current_brightness_file = fopen(CURRENT_BRIGHTNESS_FILE, "a+");
    if(current_brightness_file == NULL) {
        perror("Cannot open brightness file: ");
        exit(EXIT_FAILURE);
    }
	
	nb_bytes = fread(buffer, 1, BUFFER_SIZE - 1, current_brightness_file);

	if(nb_bytes > 0) {
        current_brightness = atoi(buffer);
	} else {
        perror("Cannot read brightness file: ");
        fclose(current_brightness_file);
        exit(EXIT_FAILURE);
    }

    if(increment) {
        new_brightness = current_brightness + step_brightness;
    } else {
        new_brightness = current_brightness - step_brightness;
    }

    if(new_brightness > max_brightness) {
        new_brightness = max_brightness;
    } else if (new_brightness < step_brightness) {
        new_brightness = step_brightness;
    }
    memset(buffer, '\0', BUFFER_SIZE);
    sprintf(buffer, "%d", new_brightness);

    nb_bytes = fwrite(buffer, strlen(buffer), 1, current_brightness_file);
    if(nb_bytes < 0) {
        perror("Cannot write brightness file: ");
        fclose(current_brightness_file);
        exit(EXIT_FAILURE);
    }

    if(verbose) {
        printf("Brightness: %d ==> %d\n", current_brightness, new_brightness);
    }

    fclose(current_brightness_file);
	exit(EXIT_SUCCESS);
}