# PID Tuning System Guide

## Overview

This flight controller now includes a comprehensive PID tuning system that allows you to tune the Roll, Pitch, and Yaw PID controllers one at a time via a serial terminal interface. CubeMonitor can be used to observe the drone's response in real-time during tuning.

## Features

- **Axis-Specific Tuning**: Tune only one axis (Roll, Pitch, or Yaw) at a time
- **Disabled Axes**: When tuning one axis, the other axes are zeroed out (drone only responds to tuned axis)
- **Runtime Adjustments**: Change PID gains without recompiling via UART terminal
- **CubeMonitor Integration**: Monitor real-time variables to observe tuning results
- **Terminal Commands**: Simple command interface for setting and viewing PID values

## Hardware Setup

The tuning system uses **UART2** (Serial Port 2) for terminal communication.

**Default UART2 Settings:**
- Baud Rate: 115200
- Data Bits: 8
- Stop Bits: 1
- Parity: None
- Flow Control: None

Connect a USB-to-UART adapter to UART2 and open a serial terminal (e.g., PuTTY, TeraTerm, minicom).

## Configuration

### Step 1: Enable Tuning Mode

Edit the file: `App/Blogic/Inc/tuning.h`

Find the tuning mode defines:
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

Set the axis you want to tune to `1`, and all others to `0`. **Only one can be 1 at a time!**

Example - to tune roll:
```c
#define ROLL_TUNING    1
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

Rebuild and flash the firmware.

### Step 2: Monitor Variables in CubeMonitor

Open CubeMonitor and add these variables to your watch list to observe the drone's response:

**Current Measurements:**
- `tuning_current_roll` - Current roll angle (degrees)
- `tuning_current_pitch` - Current pitch angle (degrees)
- `tuning_current_yaw` - Current yaw angle (degrees)

**Errors:**
- `tuning_roll_error` - Roll error (degrees)
- `tuning_pitch_error` - Pitch error (degrees)
- `tuning_yaw_error` - Yaw error (degrees)

**PID Outputs:**
- `tuning_roll_output` - Roll output (-1.0 to 1.0)
- `tuning_pitch_output` - Pitch output (-1.0 to 1.0)
- `tuning_yaw_output` - Yaw output (-1.0 to 1.0)

**Current PID Gains:**
- `pid_roll_kp`, `pid_roll_ki`, `pid_roll_kd`
- `pid_pitch_kp`, `pid_pitch_ki`, `pid_pitch_kd`
- `pid_yaw_kp`, `pid_yaw_ki`, `pid_yaw_kd`

## Terminal Commands

Once connected to UART2, type `help` or `h` to see all available commands.

### Available Commands

#### 1. Help
```
help   (or h)
```
Displays all available commands and their usage.

#### 2. View Current Gains
```
gains  (or g)
```
Displays all current PID gains for Roll, Pitch, and Yaw.

#### 3. View Status
```
status (or s)
```
Shows:
- Which axis is currently in tuning mode
- Current angle measurements for all three axes
- Current errors for all three axes
- Current PID outputs for all three axes

#### 4. Set PID Gains
```
set_pid <axis> <kp> <ki> <kd>
```

**Parameters:**
- `<axis>`: `roll`, `pitch`, or `yaw`
- `<kp>`: Proportional gain (floating point)
- `<ki>`: Integral gain (floating point)
- `<kd>`: Derivative gain (floating point)

**Example:**
```
set_pid roll 1.5 0.08 0.15
```

This sets the Roll PID to: Kp=1.5, Ki=0.08, Kd=0.15

## PID Tuning Workflow

### 1. Preparation
1. Enable tuning mode for one axis in `tuning.h`
2. Rebuild and flash the firmware
3. Connect to UART2 via serial terminal
4. Open CubeMonitor and add monitoring variables
5. Arm and lift the drone in a controlled manner (tether or open space)

### 2. Observe Baseline Response
1. In the terminal, type: `status` to see current measurements
2. In CubeMonitor, observe the current angles and errors
3. Tilt the drone manually and observe how it responds
4. Note the initial behavior

### 3. Tune Kp (Proportional Gain)
1. Increase Kp gradually: `set_pid roll 1.2 0.05 0.1`
2. Observe response in CubeMonitor
3. Repeat until the drone responds quickly but without oscillation
4. Too high Kp causes oscillations; too low causes slow response

### 4. Tune Kd (Derivative Gain)
1. If there's oscillation, increase Kd: `set_pid roll 1.2 0.05 0.15`
2. Kd dampens oscillations
3. Increase gradually to avoid slowing down response

### 5. Tune Ki (Integral Gain)
1. If there's steady-state error after tuning Kp and Kd, increase Ki slightly
2. Start low and increase gradually: `set_pid roll 1.2 0.08 0.15`
3. Too high Ki causes slow oscillations and wind-up

### 6. Repeat for Other Axes
1. Switch to the next axis in `tuning.h`
2. Rebuild and flash
3. Repeat steps 1-5 for Pitch and Yaw

## Example Tuning Values

These are starting points; actual values depend on your hardware:

**Roll (Default):**
- Kp: 1.0-1.5
- Ki: 0.05-0.1
- Kd: 0.1-0.2

**Pitch (Default):**
- Kp: 1.0-1.5
- Ki: 0.05-0.1
- Kd: 0.1-0.2

**Yaw (Default):**
- Kp: 2.0-3.0
- Ki: 0.1-0.15
- Kd: 0.05-0.1

## Important Notes

1. **One Axis at a Time**: Only one tuning mode can be enabled. Setting multiple to 1 will cause errors.

2. **Drone Behavior When Tuning is OFF**: If all defines are set to 0, the drone will respond to all three axes (normal flight mode).

3. **Drone Behavior When Tuning is ON**: If one axis is set to 1 (e.g., ROLL_TUNING=1), the drone will:
   - Only respond to roll stick input
   - Not respond to pitch or yaw (those outputs are zeroed)
   - This allows isolated testing of one axis

4. **CubeMonitor Real-Time Observation**: Use CubeMonitor's plotting features to create graphs of:
   - Error vs Time (should decrease and settle)
   - Output vs Time (should show smooth control without oscillation)
   - Angle vs Time (should track setpoint)

5. **Safety**: Always wear safety goggles and keep hands away from propellers. Conduct tuning in a safe, controlled environment.

## Troubleshooting

### Terminal Not Responding
- Check UART2 connection
- Verify baud rate is 115200
- Restart the MCU
- Try typing `help` or `h`

### PID Changes Not Taking Effect
- Verify the axis is enabled in `tuning.h`
- Check that you used the correct command: `set_pid <axis> <kp> <ki> <kd>`
- Use `gains` command to verify the values were updated

### Drone Not Responding to Tuned Axis
- Verify the tuning mode is enabled in `tuning.h`
- Check CubeMonitor to see if the PID output is non-zero
- Ensure the drone is armed and has throttle

### Oscillations During Tuning
- Reduce Kp value
- Increase Kd to dampen oscillations
- Reduce Ki to avoid integral wind-up

## Advanced: Modifying the System

The tuning system is modular and can be modified:

1. **Add new monitoring variables**: Edit `tuning.h` and `tuning.c`
2. **Add new commands**: Edit `pid_tuning_cmd.c`, specifically the `parse_and_execute_command()` function
3. **Change UART port**: Edit `main.c` to use a different UART
4. **Change baud rate**: Edit the UART configuration in STM32CubeMX and regenerate

## Files Overview

- **tuning.h**: Tuning mode configuration defines and monitoring variable declarations
- **tuning.c**: Implementation of monitoring variable updates
- **pid_tuning_cmd.h**: UART command handler interface
- **pid_tuning_cmd.c**: Implementation of terminal command parser and UART I/O
- **ControlSystem.hpp/cpp**: Modified to include tuning integration

## Next Steps

1. Flash the firmware with tuning enabled for Roll
2. Connect to UART2 at 115200 baud
3. Type `help` in the terminal
4. Follow the tuning workflow above
5. Monitor variables in CubeMonitor
6. Adjust PID values using `set_pid` commands
7. Repeat for Pitch and Yaw axes

Good luck with your PID tuning!
