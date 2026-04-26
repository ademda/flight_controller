# PID Tuning System - Implementation Summary

## Changes Made

This document summarizes all modifications made to implement the PID tuning system.

### 1. New Files Created

#### **tuning.h** (`App/Blogic/Inc/tuning.h`)
- Configuration header with defines for `ROLL_TUNING`, `PITCH_TUNING`, `YAW_TUNING` (set to 1 or 0)
- Global monitoring variables for real-time observation in CubeMonitor
- Global variables for adjustable PID gains (`pid_roll_kp`, `pid_roll_ki`, `pid_roll_kd`, etc.)
- Function declarations for tuning system initialization and monitoring

#### **tuning.c** (`App/Blogic/Src/tuning.c`)
- Implementation of monitoring variable management
- Default PID gain initialization (Roll Kp=1.0, Ki=0.05, Kd=0.1; Pitch same; Yaw Kp=2.0, Ki=0.1, Kd=0.05)
- Helper functions: `tuning_init()`, `tuning_update_monitor()`, `tuning_is_axis_enabled()`, `tuning_get_active_axis()`

#### **pid_tuning_cmd.h** (`App/Blogic/Inc/pid_tuning_cmd.h`)
- UART command handler interface
- Functions for initializing, processing, and executing PID tuning commands

#### **pid_tuning_cmd.c** (`App/Blogic/Src/pid_tuning_cmd.c`)
- Complete UART command parser with support for:
  - `help` / `h` - Display available commands
  - `gains` / `g` - Show current PID gains
  - `status` / `s` - Show current measurements and errors
  - `set_pid <axis> <kp> <ki> <kd>` - Update PID gains at runtime
- Character-by-character command buffer with backspace support
- Pretty-printed responses to UART

### 2. Modified Files

#### **ControlSystem.hpp** (`App/Control/Controller/Inc/ControlSystem.hpp`)
- Added `#include "tuning.h"`
- Added method: `void updatePIDGainsFromTuning();` to apply updated gains

#### **ControlSystem.cpp** (`App/Control/Controller/Src/ControlSystem.cpp`)
- Added `#include "tuning.h"`
- Modified `init()`:
  - Now calls `tuning_init()` to initialize tuning system
  - Calls `updatePIDGainsFromTuning()` to apply initial gains
- Modified `updateControl()`:
  - Now checks `tuning_get_active_axis()` to determine if tuning mode is enabled
  - Zeros out PID outputs for non-tuning axes (if ROLL_TUNING=1, pitch and yaw outputs are forced to 0)
  - Calls `tuning_update_monitor()` to populate monitoring variables
  - Updates setpoint monitoring variables
- Added new method: `updatePIDGainsFromTuning()` to apply current gains from tuning variables to PID controllers

#### **main.c** (`Core/Src/main.c`)
- Added includes: `#include "tuning.h"` and `#include "pid_tuning_cmd.h"`
- Added global variable: `uint8_t uart2_rx_char = 0;` for UART2 character reception
- Added in `main()`:
  - Call `pid_tuning_cmd_init(&huart2);` to initialize tuning command handler
  - Call `HAL_UART_Receive_IT(&huart2, &uart2_rx_char, 1);` to enable UART2 character reception
- Added in main loop:
  - Call `pid_tuning_cmd_update();` to process any pending commands

#### **stm32f4xx_it.c** (`Core/Src/stm32f4xx_it.c`)
- Added `#include "pid_tuning_cmd.h"`
- Modified `HAL_UART_RxCpltCallback()`:
  - Now handles UART2 reception (in addition to existing UART1 handling)
  - Calls `pid_tuning_cmd_process_char()` for each received character
  - Restarts UART2 interrupt-driven reception

### 3. Key Features

#### **Tuning Mode Configuration**
```c
#define ROLL_TUNING    1  // Set to 1 to tune roll, 0 otherwise
#define PITCH_TUNING   0
#define YAW_TUNING     0
```
Only ONE axis can be 1 at a time.

#### **Real-Time PID Adjustment**
Users can change PID gains via UART without recompiling:
```
set_pid roll 1.5 0.08 0.15
```

#### **CubeMonitor Variables**
All monitoring variables are exposed as globals for real-time observation:
- `tuning_current_roll`, `tuning_current_pitch`, `tuning_current_yaw`
- `tuning_roll_error`, `tuning_pitch_error`, `tuning_yaw_error`
- `tuning_roll_output`, `tuning_pitch_output`, `tuning_yaw_output`
- `pid_roll_kp`, `pid_roll_ki`, `pid_roll_kd` (and for pitch/yaw)

#### **Axis Isolation**
When tuning one axis (e.g., `ROLL_TUNING=1`):
- Only roll PID control is active
- Pitch and yaw outputs are zeroed out
- Drone only responds to roll stick input
- Other axes are completely disabled during tuning

#### **Terminal Interface (UART2 @ 115200 baud)**
Simple command-line interface with:
- Real-time PID gain adjustment
- Status monitoring
- Help documentation
- Graceful error handling

### 4. How It Works

**Tuning Workflow:**

1. **Enable Mode**: User edits `tuning.h` to set `ROLL_TUNING=1` and others to 0
2. **Compile & Flash**: Build and upload firmware
3. **Connect UART**: Open terminal on UART2 at 115200 baud
4. **Monitor**: Add tuning variables to CubeMonitor
5. **Adjust**: Use `set_pid` command to change Kp, Ki, Kd in real-time
6. **Observe**: Watch CubeMonitor plots to see response
7. **Repeat**: Adjust until response is optimal
8. **Switch Axis**: Change tuning.h for next axis and repeat

**Control Loop Integration:**

- `FlightController_Update()` calls `ControlSystem::updateControl()`
- `updateControl()` checks `tuning_get_active_axis()`
- If tuning mode is active, non-tuning axes are zeroed
- Monitoring variables are updated every loop iteration
- Main loop periodically calls `pid_tuning_cmd_update()` to process UART commands

### 5. Default PID Gains

```
Roll:   Kp=1.0,  Ki=0.05, Kd=0.1
Pitch:  Kp=1.0,  Ki=0.05, Kd=0.1
Yaw:    Kp=2.0,  Ki=0.1,  Kd=0.05
```

These are configurable in [tuning.c](App/Blogic/Src/tuning.c).

### 6. Building & Flashing

The new files integrate seamlessly with the existing STM32CubeIDE project:

```bash
# Build (in STM32CubeIDE or command line)
make clean
make

# Flash to STM32F401RE
# Use STM32CubeProgrammer or your preferred method
```

### 7. UART Configuration

**UART2** is used for tuning commands:
- Baud: 115200
- Data: 8 bits
- Stop: 1 bit
- Parity: None
- Flow: None

**UART1** remains unchanged and is used for RC receiver (iBUS).

### 8. File Structure

```
App/
├── Blogic/
│   ├── Inc/
│   │   ├── tuning.h              [NEW]
│   │   ├── pid_tuning_cmd.h       [NEW]
│   │   └── ...existing files...
│   └── Src/
│       ├── tuning.c              [NEW]
│       ├── pid_tuning_cmd.c       [NEW]
│       └── ...existing files...
├── Control/
│   └── Controller/
│       ├── Inc/
│       │   ├── ControlSystem.hpp  [MODIFIED]
│       │   └── ...
│       └── Src/
│           ├── ControlSystem.cpp  [MODIFIED]
│           └── ...
└── ...
Core/
├── Inc/
│   ├── main.h
│   └── ...
└── Src/
    ├── main.c                     [MODIFIED]
    ├── stm32f4xx_it.c            [MODIFIED]
    └── ...
```

### 9. Important Notes

1. **Single Axis Tuning**: Only one `#define` can be 1 at a time
2. **Dynamic Gain Update**: PID gains update immediately when set via terminal
3. **Axis Isolation**: When tuning, other axes are completely disabled (output = 0)
4. **CubeMonitor Integration**: All monitoring variables are accessible for real-time observation
5. **Safety**: Always conduct tuning in a safe environment with propellers safely secured

### 10. Next Steps

1. Read [PID_TUNING_GUIDE.md](PID_TUNING_GUIDE.md) for detailed tuning instructions
2. Edit `tuning.h` to enable tuning for desired axis
3. Build and flash firmware
4. Connect to UART2 terminal and start tuning
5. Use CubeMonitor to visualize drone response

---

For questions or issues, refer to the detailed guide in [PID_TUNING_GUIDE.md](PID_TUNING_GUIDE.md).
