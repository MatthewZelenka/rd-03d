#ifndef RD_03D_PARSER_INTERNAL_H
#define RD_03D_PARSER_INTERNAL_H

#include <rd_03d_parser.h>
// needed because target_parser_t is embedded by value not used as a pointer.
#include "target_parser_internal.h" // IWYU pragma: keep

typedef enum {
  start_0,
  start_1,
  start_2,
  start_3,
  payload_0,
  payload_1,
  payload_2,
  stop_0,
  stop_1,
} rd_03d_parser_state; 

struct rd_03d_parser_t {
    rd_03d_parser_callback_t callback;
    rd_03d_parser_error_callback_t error_callback;
    void *user_data;
    rd_03d_parser_state state;
    target_t current_rd_03d[3];
    target_parser_t tpt;
};

#endif
