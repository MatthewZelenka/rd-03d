#ifndef RD_03D_PARSER_H
#define RD_03D_PARSER_H

#include <stdlib.h>
#include <target_parser.h>

typedef struct rd_03d_parser_t rd_03d_parser_t;

typedef void (*rd_03d_parser_callback_t)(const target_t *target_array , void *user_data);

typedef void (*rd_03d_parser_error_callback_t)(const rd_03d_parser_t *target, int error);

// Heap
rd_03d_parser_t *rd_03d_parser_create(rd_03d_parser_callback_t callback, rd_03d_parser_error_callback_t error_callback, void *user_data);

void rd_03d_parser_destroy(rd_03d_parser_t *r0pt);

// No heap

size_t rd_03d_parser_size(void);

void rd_03d_parser_init(rd_03d_parser_t *r0pt, rd_03d_parser_callback_t callback, rd_03d_parser_error_callback_t error_callback, void *user_data);

void rd_03d_parser_deinit(rd_03d_parser_t *r0pt);

// common

void rd_03d_parser_reset(rd_03d_parser_t *r0pt);

void rd_03d_parser_feed(rd_03d_parser_t *r0pt, uint8_t byte);

#endif
