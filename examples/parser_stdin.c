#include <stdio.h>
#include <stdint.h>
#include "rd_03d_parser.h"

const int BUF_SIZE = 256;


// Helper: Convert 2 hex chars to 1 byte
// Returns 1 on success, 0 on invalid input
int hex_pair_to_byte(const char *hex_str, uint8_t *out_byte) {
    unsigned int temp;
    // "%2x" reads exactly 2 hex characters
    if (sscanf(hex_str, "%2x", &temp) == 1) {
        *out_byte = (uint8_t)temp;
        return 1;
    }
    return 0;
}

void rd_03d_target_callback(const target_t *p, void *user_data)
{
    (void)user_data;
    printf("x=%d y=%d speed=%d dist=%u\n",
           p->x_pos,
           p->y_pos,
           p->speed,
           p->pixel_distance_value);
}

void rd_03d_callback(const target_t *p, void *user_data)
{
    (void)user_data;
    for (int i = 0; i<3; i++) {
        printf("%d", i);
        rd_03d_target_callback(p+i, NULL);
    }
}

int main(void) {
    char line[BUF_SIZE];
    uint8_t byte;
    rd_03d_parser_t *r0pt = rd_03d_parser_create(rd_03d_callback, NULL, NULL);
    
    setvbuf(stdin, NULL, _IONBF, 0);
    
    printf("Enter hex bytes (e.g., AA 01 FF), or Ctrl+D to end:\n");

    // read line-by-line from stdin
    while (fgets(line, sizeof(line), stdin) != NULL) {
        char *ptr = line;
        char *endPtr = ptr + BUF_SIZE;
        // parse each hex pair in the line
        while (*ptr != '\0' && *ptr != '\n' && ptr < endPtr) {
            if (*ptr == ' ' || *ptr == '\t') {
                ptr++;
                continue;
            }

            if (hex_pair_to_byte(ptr, &byte)) {
                rd_03d_parser_feed(r0pt, byte);
                
                ptr += 2;
            } else {
                fprintf(stderr, "Invalid hex at: %s\n", ptr);
                ptr++;
            }
        }
        // Do not need to reset every read.
        // Resets so that every entered chunk is newly parsed.
        rd_03d_parser_reset(r0pt);
    }
    
    return 0;
}   

