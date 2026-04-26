# PID Tuning System - Configuration Reference

## Tuning Mode Defines

**Location:** `App/Blogic/Inc/tuning.h` (lines 24-28)

```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

### How to Enable Tuning

Set the desired axis to 1, others to 0:

#### Tune Roll Only
```c
#define ROLL_TUNING    1
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

#### Tune Pitch Only
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   1
#define YAW_TUNING     0
```

#### Tune Yaw Only
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     1
```

#### Normal Flight (No Tuning)
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

⚠️ **IMPORTANT**: Only ONE can be 1 at a time!

---

## Global Monitoring Variables

All of these are automatically updated every control loop iteration and can be observed in CubeMonitor.

### Current State Measurements
```c
float tuning_current_roll;      // Current roll angle (degrees)
float tuning_current_pitch;     // Current pitch angle (degrees)
float tuning_current_yaw;       // Current yaw angle (degrees)
```

### Setpoints
```c
float tuning_roll_setpoint;     // Desired roll angle (degrees)
float tuning_pitch_setpoint;    // Desired pitch angle (degrees)
float tuning_yaw_setpoint;      // Desired yaw angle (degrees)
```

### Errors (Setpoint - Current)
```c
float tuning_roll_error;        // Roll error (degrees)
float tuning_pitch_error;       // Pitch error (degrees)
float tuning_yaw_error;         // Yaw error (degrees)
```

### PID Control Outputs
```c
float tuning_roll_output;       // Roll PID output (-1.0 to 1.0)
float tuning_pitch_output;      // Pitch PID output (-1.0 to 1.0)
float tuning_yaw_output;        // Yaw PID output (-1.0 to 1.0)
```

### Adjustable PID Gains
```c
// Roll
float pid_roll_kp;              // Proportional gain
float pid_roll_ki;              // Integral gain
float pid_roll_kd;              // Derivative gain

// Pitch
float pid_pitch_kp;
float pid_pitch_ki;
float pid_pitch_kd;

// Yaw
float pid_yaw_kp;
float pid_yaw_ki;
float pid_yaw_kd;
```

---

## Default PID Gain Values

**Location:** `App/Blogic/Src/tuning.c` (lines 41-49)

```c
// Roll (default)
float pid_roll_kp = 1.0f;
float pid_roll_ki = 0.05f;
float pid_roll_kd = 0.1f;

// Pitch (default)
float pid_pitch_kp = 1.0f;
float pid_pitch_ki = 0.05f;
float pid_pitch_kd = 0.1f;

// Yaw (default)
float pid_yaw_kp = 2.0f;
float pid_yaw_ki = 0.1f;
float pid_yaw_kd = 0.05f;
```

To change defaults, edit these values and rebuild.

---

## UART Configuration

**Hardware:** UART2

**Default Settings:**
- Baud Rate: 115200
- Data Bits: 8
- Stop Bits: 1
- Parity: None
- Flow Control: None

These are configured via STM32CubeMX. To change them:
1. Open `.ioc` file in STM32CubeMX
2. Configure USART2 parameters
3. Generate code
4. Rebuild

---

## Terminal Commands Reference

### Help
```
help
h
```
Displays all available commands.

### View Gains
```
gains
g
```
Shows current PID gains for all axes.

### View Status
```
status
s
```
Shows:
- Active tuning axis
- Current angle measurements
- Current errors
- Current PID outputs

### Set PID Gains
```
set_pid <axis> <kp> <ki> <kd>
```

Parameters:
- `<axis>`: `roll`, `pitch`, or `yaw`
- `<kp>`: Proportional gain (float)
- `<ki>`: Integral gain (float)
- `<kd>`: Derivative gain (float)

Examples:
```
set_pid roll 1.5 0.08 0.15
set_pid pitch 1.2 0.06 0.12
set_pid yaw 2.5 0.12 0.08
```

---

## Behavior with Tuning Enabled/Disabled

### When Tuning is Disabled (All 0)
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0
```
- **Drone Response**: All three axes are active
- **Behavior**: Normal flight, responds to all control inputs
- **Use Case**: Normal autonomous/manual flight

### When Roll Tuning is Enabled
```c
#define ROLL_TUNING    1
#define PITCH_TUNING   0
#define YAW_TUNING     0
```
- **Drone Response**: 
  - Roll axis: ACTIVE (responds to roll input and PID control)
  - Pitch axis: DISABLED (output forced to 0)
  - Yaw axis: DISABLED (output forced to 0)
- **Behavior**: Drone only responds to roll stick, ignores pitch/yaw input
- **Use Case**: Isolate and tune roll axis

### When Pitch Tuning is Enabled
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   1
#define YAW_TUNING     0
```
- **Drone Response**:
  - Roll axis: DISABLED (output forced to 0)
  - Pitch axis: ACTIVE
  - Yaw axis: DISABLED (output forced to 0)
- **Behavior**: Only responds to pitch, ignores roll/yaw
- **Use Case**: Isolate and tune pitch axis

### When Yaw Tuning is Enabled
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     1
```
- **Drone Response**:
  - Roll axis: DISABLED (output forced to 0)
  - Pitch axis: DISABLED (output forced to 0)
  - Yaw axis: ACTIVE
- **Behavior**: Only responds to yaw, ignores roll/pitch
- **Use Case**: Isolate and tune yaw axis

---

## CubeMonitor Setup

### Step 1: Open CubeMonitor
In STM32CubeIDE: `Window → Show View → CubeMonitor`

### Step 2: Add Variables to Watch
1. Right-click in CubeMonitor window
2. Select "Add Variable"
3. Type the variable name (e.g., `tuning_current_roll`)
4. Select format (Float, Decimal, etc.)

### Step 3: Recommended Variables to Monitor

**For Roll Tuning:**
```
tuning_current_roll
tuning_roll_setpoint
tuning_roll_error
tuning_roll_output
```

**For Pitch Tuning:**
```
tuning_current_pitch
tuning_pitch_setpoint
tuning_pitch_error
tuning_pitch_output
```

**For Yaw Tuning:**
```
tuning_current_yaw
tuning_yaw_setpoint
tuning_yaw_error
tuning_yaw_output
```

**Always Monitor:**
```
pid_roll_kp      (or pid_pitch_kp / pid_yaw_kp for other axes)
pid_roll_ki
pid_roll_kd
```

### Step 4: Create Graphs
1. Use CubeMonitor's plotting feature
2. Plot error vs time (should decrease to zero)
3. Plot output vs time (should be smooth)
4. Plot angle vs time (should track setpoint)

---

## Control Loop Integration

The tuning system is integrated into the control loop as follows:

```
main()
  ├─ FlightController_Initialize()
  │  └─ control_system.init()
  │     └─ tuning_init()
  │
  ├─ pid_tuning_cmd_init(&huart2)
  │
  └─ Main Loop:
     ├─ FlightController_Update(dt)
     │  └─ control_system.updateControl()
     │     ├─ calculate roll_cmd, pitch_cmd, yaw_cmd via PID
     │     ├─ zero out non-tuning axes
     │     └─ tuning_update_monitor()
     │
     └─ pid_tuning_cmd_update()
        └─ process UART commands
           └─ update pid_roll_kp, pid_roll_ki, etc.
```

When PID gains are changed via UART:
1. Terminal command updates `pid_roll_kp`, `pid_roll_ki`, `pid_roll_kd` variables
2. Next `control_system.updateControl()` call uses new values
3. New gains take effect immediately

---

## Common Pitfalls

| Problem | Cause | Solution |
|---------|-------|----------|
| Firmware won't compile | Missing include file | Ensure all 4 new files are created |
| Terminal commands not recognized | Wrong UART selected | Check that UART2 is being used |
| PID gains not updating | Command syntax wrong | Use: `set_pid roll 1.5 0.08 0.15` |
| Only one axis enabled but others respond | Code not rebuilt | Rebuild and reflash after changing tuning.h |
| Can't connect to CubeMonitor | Variables not visible | Ensure firmware was built with debugging symbols |
| Drone responds to all axes during tuning | Tuning mode not enabled | Check tuning.h - set desired axis to 1 |

---

## Verification Checklist

After implementing, verify:

- [ ] All 4 new files created successfully
- [ ] ControlSystem.hpp and .cpp modified
- [ ] main.c includes new headers
- [ ] stm32f4xx_it.c modified for UART2
- [ ] Project compiles without errors
- [ ] Firmware flashes to MCU
- [ ] UART2 responds to terminal input (type `help`)
- [ ] `gains` command shows PID values
- [ ] `set_pid roll 1.2 0.05 0.1` works
- [ ] Variables visible in CubeMonitor
- [ ] Only one axis is 1 in tuning.h at a time

---

## Files Reference

### New Files
- `App/Blogic/Inc/tuning.h` - Configuration defines
- `App/Blogic/Src/tuning.c` - Monitoring implementation
- `App/Blogic/Inc/pid_tuning_cmd.h` - Command handler interface
- `App/Blogic/Src/pid_tuning_cmd.c` - Command parser implementation

### Modified Files
- `App/Control/Controller/Inc/ControlSystem.hpp`
- `App/Control/Controller/Src/ControlSystem.cpp`
- `Core/Src/main.c`
- `Core/Src/stm32f4xx_it.c`

### Documentation Files
- `QUICK_START.md` - 5-minute quick start
- `PID_TUNING_GUIDE.md` - Detailed tuning procedures
- `TUNING_IMPLEMENTATION_SUMMARY.md` - Technical implementation details
- `CONFIGURATION_REFERENCE.md` - This file

---

## Support

For issues or questions:
1. Check the relevant documentation file
2. Verify tuning.h configuration
3. Ensure UART2 is properly connected (115200 baud)
4. Check firmware compilation for errors
5. Verify all 4 new files were created

Good luck with PID tuning!
