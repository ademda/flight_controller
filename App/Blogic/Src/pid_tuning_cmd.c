/*
 * pid_tuning_cmd.c
 *
 *  Created on: Apr 26, 2026
 *      Author: dalya
 *  Purpose: UART command handler for PID tuning implementation
 */

#include "pid_tuning_cmd.h"
#include "tuning.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ============================================================================
 * COMMAND BUFFER
 * ========================================================================== */

#define CMD_BUFFER_SIZE 64
static uint8_t cmd_buffer[CMD_BUFFER_SIZE];
static uint16_t cmd_buffer_idx = 0;
static UART_HandleTypeDef *g_uart_handle = NULL;

/* ============================================================================
 * INITIALIZATION
 * ========================================================================== */

void pid_tuning_cmd_init(UART_HandleTypeDef *uart_handle) {
    g_uart_handle = uart_handle;
    cmd_buffer_idx = 0;
    memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
    
    // Print welcome message
    if (g_uart_handle != NULL) {
        uint8_t msg[] = "\r\n===== PID TUNING SYSTEM INITIALIZED =====\r\n";
        HAL_UART_Transmit(g_uart_handle, msg, sizeof(msg)-1, 100);
        pid_tuning_cmd_print_help();
    }
}

/* ============================================================================
 * UART CHARACTER PROCESSING
 * ========================================================================== */

void pid_tuning_cmd_process_char(uint8_t data) {
    if (g_uart_handle == NULL) return;
    
    // Handle backspace
    if (data == '\b' || data == 0x7F) {
        if (cmd_buffer_idx > 0) {
            cmd_buffer_idx--;
            uint8_t bs[] = "\b \b";
            HAL_UART_Transmit(g_uart_handle, bs, sizeof(bs)-1, 10);
        }
        return;
    }
    
    // Echo character
    HAL_UART_Transmit(g_uart_handle, &data, 1, 10);
    
    // Handle Enter key
    if (data == '\r' || data == '\n') {
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)"\r\n", 2, 10);
        
        if (cmd_buffer_idx > 0) {
            cmd_buffer[cmd_buffer_idx] = '\0';
            // Command will be processed in update function
        }
        return;
    }
    
    // Add character to buffer if not full
    if (cmd_buffer_idx < (CMD_BUFFER_SIZE - 1)) {
        cmd_buffer[cmd_buffer_idx++] = data;
    }
}

/* ============================================================================
 * COMMAND PARSING AND EXECUTION
 * ========================================================================== */

static void parse_and_execute_command(char *cmd) {
    if (cmd == NULL || strlen(cmd) == 0) {
        return;
    }
    
    char cmd_copy[CMD_BUFFER_SIZE];
    strncpy(cmd_copy, (const char*)cmd, CMD_BUFFER_SIZE - 1);
    cmd_copy[CMD_BUFFER_SIZE - 1] = '\0';
    
    // Parse command
    char *token = strtok(cmd_copy, " ");
    if (token == NULL) return;
    
    char response[256];
    
    // Help command
    if (strcmp(token, "help") == 0 || strcmp(token, "h") == 0) {
        pid_tuning_cmd_print_help();
        return;
    }
    
    // Print gains command
    if (strcmp(token, "gains") == 0 || strcmp(token, "g") == 0) {
        pid_tuning_cmd_print_gains();
        return;
    }
    
    // Set PID command: set_pid <axis> <kp> <ki> <kd>
    if (strcmp(token, "set_pid") == 0 || strcmp(token, "spid") == 0) {
        char *axis_str = strtok(NULL, " ");
        char *kp_str = strtok(NULL, " ");
        char *ki_str = strtok(NULL, " ");
        char *kd_str = strtok(NULL, " ");
        
        if (axis_str == NULL || kp_str == NULL || ki_str == NULL || kd_str == NULL) {
            snprintf(response, sizeof(response), "ERROR: Usage: set_pid <roll|pitch|yaw> <kp> <ki> <kd>\r\n");
            HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
            return;
        }
        
        float kp = atof(kp_str);
        float ki = atof(ki_str);
        float kd = atof(kd_str);
        
        if (strcmp(axis_str, "roll") == 0) {
            pid_roll_kp = kp;
            pid_roll_ki = ki;
            pid_roll_kd = kd;
            snprintf(response, sizeof(response), 
                    "Roll PID updated: Kp=%.3f, Ki=%.3f, Kd=%.3f\r\n", kp, ki, kd);
        } else if (strcmp(axis_str, "pitch") == 0) {
            pid_pitch_kp = kp;
            pid_pitch_ki = ki;
            pid_pitch_kd = kd;
            snprintf(response, sizeof(response), 
                    "Pitch PID updated: Kp=%.3f, Ki=%.3f, Kd=%.3f\r\n", kp, ki, kd);
        } else if (strcmp(axis_str, "yaw") == 0) {
            pid_yaw_kp = kp;
            pid_yaw_ki = ki;
            pid_yaw_kd = kd;
            snprintf(response, sizeof(response), 
                    "Yaw PID updated: Kp=%.3f, Ki=%.3f, Kd=%.3f\r\n", kp, ki, kd);
        } else {
            snprintf(response, sizeof(response), "ERROR: Unknown axis. Use: roll, pitch, or yaw\r\n");
        }
        
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
        return;
    }
    
    // Get status command
    if (strcmp(token, "status") == 0 || strcmp(token, "s") == 0) {
        int active = tuning_get_active_axis();
        const char *axis_names[] = {"ROLL", "PITCH", "YAW"};
        
        if (active >= 0 && active < 3) {
            snprintf(response, sizeof(response), 
                    "TUNING MODE: %s\r\n", axis_names[active]);
        } else {
            snprintf(response, sizeof(response), "TUNING MODE: OFF (All axes disabled)\r\n");
        }
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
        
        // Print current measurements
        snprintf(response, sizeof(response), 
                "Roll: %.1f° | Pitch: %.1f° | Yaw: %.1f°\r\n",
                tuning_current_roll, tuning_current_pitch, tuning_current_yaw);
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
        
        snprintf(response, sizeof(response), 
                "Errors - Roll: %.1f° | Pitch: %.1f° | Yaw: %.1f°\r\n",
                tuning_roll_error, tuning_pitch_error, tuning_yaw_error);
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
        
        snprintf(response, sizeof(response), 
                "Outputs - Roll: %.3f | Pitch: %.3f | Yaw: %.3f\r\n",
                tuning_roll_output, tuning_pitch_output, tuning_yaw_output);
        HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
        return;
    }
    
    // Unknown command
    snprintf(response, sizeof(response), "Unknown command: %s\r\n", token);
    HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, strlen(response), 100);
    HAL_UART_Transmit(g_uart_handle, (uint8_t*)"Type 'help' for available commands\r\n", 37, 100);
}

void pid_tuning_cmd_update(void) {
    if (cmd_buffer_idx > 0) {
        cmd_buffer[cmd_buffer_idx] = '\0';
        parse_and_execute_command((char*)cmd_buffer);
        cmd_buffer_idx = 0;
        memset(cmd_buffer, 0, CMD_BUFFER_SIZE);
        
        // Print prompt
        if (g_uart_handle != NULL) {
            HAL_UART_Transmit(g_uart_handle, (uint8_t*)"> ", 2, 10);
        }
    }
}

/* ============================================================================
 * HELP AND STATUS PRINTING
 * ========================================================================== */

void pid_tuning_cmd_print_help(void) {
    if (g_uart_handle == NULL) return;
    
    const uint8_t help_msg[] = 
        "\r\n===== AVAILABLE COMMANDS =====\r\n"
        "help, h              - Show this help message\r\n"
        "gains, g             - Display current PID gains\r\n"
        "status, s            - Show current measurements and errors\r\n"
        "set_pid <axis> <kp> <ki> <kd> - Set PID gains\r\n"
        "                       axis: roll, pitch, or yaw\r\n"
        "                       Example: set_pid roll 1.5 0.08 0.15\r\n"
        "==============================\r\n"
        "NOTE: Edit tuning.h to enable/disable tuning mode for each axis!\r\n"
        "> ";
    
    HAL_UART_Transmit(g_uart_handle, (uint8_t*)help_msg, sizeof(help_msg)-1, 200);
}

void pid_tuning_cmd_print_gains(void) {
    if (g_uart_handle == NULL) return;
    
    char response[512];
    int len = snprintf(response, sizeof(response),
        "\r\n===== CURRENT PID GAINS =====\r\n"
        "Roll:   Kp=%.4f, Ki=%.4f, Kd=%.4f\r\n"
        "Pitch:  Kp=%.4f, Ki=%.4f, Kd=%.4f\r\n"
        "Yaw:    Kp=%.4f, Ki=%.4f, Kd=%.4f\r\n"
        "==============================\r\n> ",
        pid_roll_kp, pid_roll_ki, pid_roll_kd,
        pid_pitch_kp, pid_pitch_ki, pid_pitch_kd,
        pid_yaw_kp, pid_yaw_ki, pid_yaw_kd);
    
    HAL_UART_Transmit(g_uart_handle, (uint8_t*)response, len, 200);
}
