#pragma once

/**
 * known input ranges
 */

// retrigger, play/pause, and roll all use these
#define TRANSPORT_CV_LOW         128 // Negative voltage, 0V, or no connection
#define TRANSPORT_CV_HIGH        560 // +5V
#define TRANSPORT_BUTTON_PRESSED 768 // 770-787

// for use with reading daisy chain signals
#define LOGIC_HIGH  890
#define LOGIC_LOW   0
