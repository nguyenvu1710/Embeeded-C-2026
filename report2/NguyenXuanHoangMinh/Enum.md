# Enum

## Definition

- enum short for Enumeration, similar to Struct it is a User-define data type but unlike struct it consist of a list/set of named intergers *constant*
- a constant is a value that is not suppossed to change during a program's operation, unlike a normal variable that can be update and edit when the code runs

## Purpose - why use enum?

- mostly for making codes easier to understand and manage
- In Embedded C, enum is commonly used to:
    + Represent device states, such as IDLE, RUNNING, and ERROR.
    + Define operating modes, such as MANUAL and AUTOMATIC.
    + Organize state machines and control logic LED_ON LED_OFF. 

## Syntax

- 
typedef enum  {
    CONSTANT1,CONSTANT2, CONSTANT3
}EnumName; //using typedef, you dont need to declare enum everytime

- this is an example of enum showing status with if-else 
        #include <stdio.h>

        typedef enum {
            SUCCESS = 1,
            FAILURE = 0,
            PENDING = 2
        } Device1;

        void connectStatus(Device1 status);  // Function prototype

        int main(void) {
            Device1 status = SUCCESS;

            connectStatus(status);

            return 0;
        }

        void connectStatus(Device1 status) {
            if (status == SUCCESS) {
                printf("Connection was successful\n");
            }
            else if (status == FAILURE) {
                printf("Could not connect\n");
            }
            else if (status == PENDING) {
                printf("Connecting...\n");
            }
            else {
                printf("Unknown status\n");
            }
        }

- this is eum with switch - case
        #include <stdio.h>

        typedef enum {
            STOPPED,
            RUNNING,
            ERROR
        } MotorState;

        int main(void) {
            MotorState motor = RUNNING;

            switch (motor) {
                case STOPPED:
                    printf("Motor stopped\n");
                    break;

                case RUNNING:
                    printf("Motor running\n");
                    break;

                case ERROR:
                    printf("Motor error\n");
                    break;

                default:
                    printf("Unknown state\n");
                    break;
            }

            return 0;
        }







-