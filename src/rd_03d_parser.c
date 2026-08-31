#include <string.h>
#include "internal/rd_03d_parser_internal.h"
#include "internal/target_parser_internal.h"

void rd_03d_parser_target_callback(const target_t *p, void *user_data)
{
    rd_03d_parser_t *r0pt = (rd_03d_parser_t*)user_data;
    switch (r0pt->state) {
        case payload_0:
            r0pt->current_rd_03d[0] = *p;
            r0pt->state = payload_1;
            break;
        case payload_1: 
            r0pt->current_rd_03d[1] = *p;
            r0pt->state = payload_2;
            break;
        case payload_2:
            r0pt->current_rd_03d[2] = *p;
            r0pt->state = stop_0;
            break;
        default:
            if (r0pt->error_callback) {
                r0pt->error_callback(r0pt, 0);
            }
            break;
    }
}

rd_03d_parser_t *rd_03d_parser_create(
    rd_03d_parser_callback_t callback,
    rd_03d_parser_error_callback_t error_callback,
    void *user_data) 
{
    rd_03d_parser_t *r0pt = malloc(sizeof(rd_03d_parser_t)); 
    if (r0pt)
    {
        rd_03d_parser_init(r0pt, callback, error_callback, user_data);
    }
    return r0pt;
}

void rd_03d_parser_destroy(rd_03d_parser_t *r0pt) 
{
    if (r0pt)
    {
        rd_03d_parser_deinit(r0pt);
        free(r0pt);
        r0pt = NULL;
    }
}

size_t rd_03d_parser_size(void) {
    return sizeof(rd_03d_parser_t);
}

void rd_03d_parser_init(rd_03d_parser_t *r0pt,
    rd_03d_parser_callback_t callback,
    rd_03d_parser_error_callback_t error_callback,
    void *user_data) 
{
    r0pt->callback = callback;
    r0pt->error_callback = error_callback;
    r0pt->user_data = user_data;
    target_parser_init(&r0pt->tpt, rd_03d_parser_target_callback, NULL, r0pt); 
    rd_03d_parser_reset(r0pt);
}

void rd_03d_parser_deinit(rd_03d_parser_t *r0pt) 
{
    target_parser_deinit(&r0pt->tpt);
}

void rd_03d_parser_reset(rd_03d_parser_t *r0pt)
{
    r0pt->state = start_0;
    memset(r0pt->current_rd_03d, 0, sizeof(r0pt->current_rd_03d));
    target_parser_reset(&r0pt->tpt);
}

void rd_03d_parser_feed(rd_03d_parser_t *r0pt, uint8_t byte) {
    if (!r0pt) return;

    switch (r0pt->state) {
        case start_0:
            if (byte == 0xAA) {
                r0pt->state = start_1;
            }
            break;
        case start_1:
            if (byte == 0xFF) {
                r0pt->state = start_2;
            }
            else {
                rd_03d_parser_reset(r0pt);
            }
            break;
        case start_2:
            if (byte == 0x03) {
                r0pt->state = start_3;
            }
            else {
                rd_03d_parser_reset(r0pt);
            }
            break;
        case start_3:
            if (byte == 0x00) {
                r0pt->state = payload_0;
            }
            else {
                rd_03d_parser_reset(r0pt);
            }
            break;
        case payload_0:
        case payload_1: 
        case payload_2:
            target_parser_feed(&r0pt->tpt, byte);
            break;
        case stop_0:
            if (byte == 0x55) {
                r0pt->state = stop_1;
            }
            else {
                rd_03d_parser_reset(r0pt);
            }
            break;
        case stop_1:
            if (byte == 0xCC) {
                r0pt->state = start_0;
                if (r0pt->callback) {
                    r0pt->callback(r0pt->current_rd_03d, r0pt->user_data);
                }
            }
            else
                rd_03d_parser_reset(r0pt);
            break;
        default:
            if (r0pt->error_callback) {
                r0pt->error_callback(r0pt, 0);
            }
            break;
    }
}
