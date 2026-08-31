#ifndef TARGET_PARSER_INTERNAL_H

#define TARGET_PARSER_INTERNAL_H
#include <stdint.h>
#include <stdlib.h>
#include <target_parser.h>

typedef struct target_parser_t target_parser_t;

typedef void (*target_parser_callback_t)(const target_t *entity, void *user_data);

typedef void (*target_parser_error_callback_t)(const target_parser_t *entity, int error);

// Heap
target_parser_t *target_parser_create(target_parser_callback_t callback, target_parser_error_callback_t error_callback, void *user_data);

void target_parser_destroy(target_parser_t *tpt);

// No heap

size_t target_parser_size(void);

void target_parser_init(target_parser_t *tpt, target_parser_callback_t callback, target_parser_error_callback_t error_callback, void *user_data);

void target_parser_deinit(target_parser_t *tpt);

// common

void target_parser_reset(target_parser_t *tpt);

void target_parser_feed(target_parser_t *tpt, uint8_t byte);

typedef enum  {
  x_pos_high,
  x_pos_low,
  y_pos_high,
  y_pos_low,
  speed_high,
  speed_low,
  pixel_distance_high,
  pixel_distance_low,
} target_parser_state ; 

struct target_parser_t {
    target_parser_callback_t callback;
    target_parser_error_callback_t error_callback;
    void *user_data;
    target_t current_target;
    target_parser_state state;
};

#endif
