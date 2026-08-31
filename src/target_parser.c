#include "internal/target_parser_internal.h"

int build_signed_int16(uint8_t *in_byte, int position, int16_t *mod_byte);

int build_unsigned_int16(uint8_t *in_byte, int position, uint16_t *mod_byte);

target_parser_t *target_parser_create(
    target_parser_callback_t callback,
    target_parser_error_callback_t error_callback,
    void *user_data) 
{
    target_parser_t *tpt = malloc(sizeof(target_parser_t)); 
    if (tpt)
    {
        target_parser_init(tpt, callback, error_callback, user_data);
    }
    return tpt;
}

void target_parser_destroy(target_parser_t *tpt) 
{
    if (tpt)
    {
        target_parser_deinit(tpt);
        free(tpt);
        tpt = NULL;
    }
}

size_t target_parser_size(void) {
    return sizeof(target_parser_t);
}

void target_parser_init(target_parser_t *tpt,
    target_parser_callback_t callback,
    target_parser_error_callback_t error_callback,
    void *user_data) 
{
    tpt->callback = callback;
    tpt->error_callback = error_callback;
    tpt->user_data = user_data;
    target_parser_reset(tpt);
}

void target_parser_deinit(target_parser_t *tpt) {}

void target_parser_reset(target_parser_t *tpt)
{
    tpt->state = x_pos_low;
    tpt->current_target.x_pos = 0;
    tpt->current_target.y_pos = 0;
    tpt->current_target.speed = 0;
    tpt->current_target.pixel_distance_value = 0;
}

void target_parser_feed(target_parser_t *tpt, uint8_t byte) {
    if (!tpt) return;

    switch (tpt->state) {
        case x_pos_low:
            build_signed_int16(&byte, 0, &(tpt->current_target.x_pos));
            tpt->state = x_pos_high;
            break;
        case x_pos_high:
            build_signed_int16(&byte, 1, &(tpt->current_target.x_pos));
            tpt->state = y_pos_low;
            break;
        case y_pos_low:
            build_signed_int16(&byte, 0, &(tpt->current_target.y_pos));
            tpt->state = y_pos_high;
            break;
        case y_pos_high:
            build_signed_int16(&byte, 1, &(tpt->current_target.y_pos));
            tpt->state = speed_low;
            break;
        case speed_low:
            build_signed_int16(&byte, 0, &(tpt->current_target.speed));
            tpt->state = speed_high;
            break;
        case speed_high:
            build_signed_int16(&byte, 1, &(tpt->current_target.speed));
            tpt->state = pixel_distance_low;
            break;
        case pixel_distance_low:
            build_unsigned_int16(&byte, 0, &(tpt->current_target.pixel_distance_value));
            tpt->state = pixel_distance_high;
            break;
        case pixel_distance_high:
            build_unsigned_int16(&byte, 1, &(tpt->current_target.pixel_distance_value));
            tpt->state = x_pos_low;

            if (tpt->callback) {
                tpt->callback(&tpt->current_target, tpt->user_data);
            }
            break;
        default:
            if (tpt->error_callback) {
                tpt->error_callback(tpt, 0);
            }
            break;
    }
}

int build_signed_int16(uint8_t *in_byte, int position, int16_t *mod_byte) {
    uint16_t tmp = (uint16_t)*mod_byte;
    if (build_unsigned_int16(in_byte, position, &tmp)) 
    {
        switch (position) {
            case 0:
                *mod_byte = tmp;
                return 1;
            case 1:
                *mod_byte = (tmp & 0x8000) ? tmp ^ 0x8000 : -tmp;
                return 1;
        }
    }
    return 0;
}

int build_unsigned_int16(uint8_t *in_byte, int position, uint16_t *mod_byte) {
    switch (position) {
        case 0:
            *mod_byte = (*mod_byte & 0xFF00) | *in_byte;
            return 1;
        case 1:
            *mod_byte = ((uint16_t)*in_byte << 8) | (*mod_byte & 0xFF);
            return 1;
    }
    return 0;
}
