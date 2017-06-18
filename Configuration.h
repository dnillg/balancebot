#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

// *** LOG *** //
#define LOG_TILT_PID_IO 1
#define LOG_DIST_PID_IO 1
#define LOG_ENCODER 0
#define LOG_EFF_FRQ 1

#define LOG_FLOAT_WIDTH 3
#define LOG_FLOAT_PREC 7
#define LOG_FLOAT_BUF_SIZE 10

// *** CONTROL *** //
#define NOMINAL_FRQ 100

// *** SCHEDULED JOB FREQUENCY *** //
#define SJF_EFFECTIVE_FRQ_LOG 100
#define SJF_EFFECTIVE_FRQ_LCD 500
#define SJF_STATUS_CHAR_LCD 100

// *** SERIAL *** //
#define SERIAL_BAUD 115200
#define HC_06_DEFAULT_BAUDRATE 38400
//1 - 1200bps
//2 - 2400bps
//3 - 4800bps
//4 - 9600bps
//5 - 19200bps
//6 - 38400bps
//7 - 57600bps
//8 - 115200bps
#define HC_06_BAUD_RATE_LEVEL 8

// *** LCD *** //
#define LCD_BACKLIGHT_INTENSITY 225

// *** LED-MATRIX *** //
#define LED_MATRIX_LIGHT_INTENSITY 15

// *** MOTORS *** //
#define MOTOR_MIN 50
#define MOTOR_LEFT_OFFSET 2
#define MOTOR_RIGHT_OFFSET 0

// *** TILT PID *** //
#define TILT_PID_P 1.25
#define TILT_PID_I 0.7
#define TILT_PID_D 0.05
#define TILT_PID_BALANCE_SETPOINT 0
#define TILT_PID_FORWARD_SETPOINT 50
#define TILT_PID_BACKWARD_SETPOINT -50

// *** DIST PID *** ///
#define DIST_PID_MAX_TILT_OFFSET 160
#define DIST_PID_P 0.08
#define DIST_PID_I 0
#define DIST_PID_D 0.01
#define DIST_PID_SETPOINT 0

// *** CONTROL *** //
#define DIRECTION_RESOLUTION 64
#define MAX_ROTATION_OFFSET 20

// *** I2C *** //
#define I2C_ADDR_BNO055 0x29
#define I2C_ADDR_DISP_16_2 0x3F

// *** PINS *** //
//HC-06
#define PIN_HC_06_RX 10
#define PIN_HC_06_TX 11
//Led-matrix
#define PIN_LEDMATRIX_DIN 14 // ORANGE
#define PIN_LEDMATRIX_CLK 16 // RED
#define PIN_LEDMATRIX_CS 15 // BROWN
//Encoder
#define PIN_ENCODER_RIGHT_A 2 //GREEN UPPER MOTOR
#define PIN_ENCODER_RIGHT_B 12 //BLUE UPPER MOTOR
#define PIN_ENCODER_LEFT_A 3 //GREEN, LOWER MOTOR
#define PIN_ENCODER_LEFT_B 13 //BLUE, LOWER MOTOR
//H-Bridge
#define PIN_HB_RIGHT_ENABLE 5 //PURPLE (ENB_A)
#define PIN_HB_LEFT_FORWARD 4 //RED (IN1)
#define PIN_HB_LEFT_BACKWARD 7 //ORANGE (IN2)
#define PIN_HB_LEFT_ENABLE 6 //GRAY (ENB_B)
#define PIN_HB_RIGHT_BACKWARD 8 //ORANGE (IN4)
#define PIN_HB_RIGHT_FORWARD 9 //RED (IN3)

#endif
