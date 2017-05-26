#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#define SERIAL_BAUD 115200

// *** LOG *** //
#define LOG_PID_IO 1
#define LOG_ENCODER 0
#define LOG_EFF_FRQ 0

#define LOG_FLOAT_WIDTH 3
#define LOG_FLOAT_PREC 7
#define LOG_FLOAT_BUF_SIZE 10

// *** CONTROL ***
#define NOMINAL_FRQ 100

// *** SCHEDULED JOB FREQUENCY ***
#define SJF_EFFECTIVE_FRQ_LOG 100
#define SJF_EFFECTIVE_FRQ_LCD 500
#define SJF_STATUS_CHAR_LCD 500

// *** LCD ***
#define LCD_BACKLIGHT_INTENSITY 225

// *** Motors ***
#define MOTOR_MIN 52
#define MOTOR_LEFT_OFFSET 0
#define MOTOR_RIGHT_OFFSET 0

// *** TILT PID *** //
#define TILT_PID_P 1.3
#define TILT_PID_I 0
#define TILT_PID_D 0.09
#define TILT_PID_SETPOINT 10

// *** I2C *** //
#define I2C_ADDR_BNO055 0x29
#define I2C_ADDR_DISP_16_2 0x3F

// *** PINS *** //
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
