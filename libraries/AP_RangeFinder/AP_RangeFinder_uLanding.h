// -*- tab-width: 4; Mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
#pragma once

#include "RangeFinder.h"
#include "RangeFinder_Backend.h"

#define ULANDING_VERSION 1

#define ULAND_FILT_DEBUG 0

class AP_RangeFinder_uLanding : public AP_RangeFinder_Backend
{

public:
    // constructor
	AP_RangeFinder_uLanding(RangeFinder &ranger, uint8_t instance, RangeFinder::RangeFinder_State &_state,
                                   AP_SerialManager &serial_manager);

    // static detection function
    static bool detect(RangeFinder &ranger, uint8_t instance, AP_SerialManager &serial_manager);

    // update state
    void update(void);

    // pass raw uLanding data
    uint16_t get_raw_uLanding(void) { return _raw_uLanding; }

    // update uLanding filter parameters
    void set_ulanding_params(float sigma, float truncate);

private:
    // get a reading
    bool get_reading(uint16_t &reading_cm);

    AP_HAL::UARTDriver *uart = nullptr;
    uint32_t last_reading_ms = 0;
    uint8_t linebuf[10];
    uint8_t linebuf_len = 0;
    uint16_t _raw_uLanding;

    float _filter_sigma;
    float _filter_truncate;
#if ULAND_FILT_DEBUG
    int debug_print_count = 0;
#endif
};
