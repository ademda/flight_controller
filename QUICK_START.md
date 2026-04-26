# PID Tuning System - Quick Start Guide

## 5-Minute Setup

### Step 1: Enable Tuning for One Axis 

Open: `App/Blogic/Inc/tuning.h`

Change this:
```c
#define ROLL_TUNING    0
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

To this (to tune Roll):
```c
#define ROLL_TUNING    1
#define PITCH_TUNING   0
#define YAW_TUNING     0
```

### Step 2: Build and Flash

```bash
# In STM32CubeIDE:
# Right-click project → Build Project
# Right-click project → Run As → Embedded C/C++ Application
```

### Step 3: Connect to Terminal

1. Connect USB-to-UART adapter to UART2
2. Open terminal (PuTTY, TeraTerm, minicom)
3. Settings: 115200 baud, 8 data bits, 1 stop bit, no parity
4. Type: `help`

### Step 4: View Current Gains

```
> gains
===== CURRENT PID GAINS =====
Roll:   Kp=1.0000, Ki=0.0500, Kd=0.1000
Pitch:  Kp=1.0000, Ki=0.0500, Kd=0.1000
Yaw:    Kp=2.0000, Ki=0.1000, Kd=0.0500
==============================
```

### Step 5: Adjust PID in Real-Time

Example - increase Roll Kp:
```
> set_pid roll 1.5 0.05 0.1
Roll PID updated: Kp=1.50, Ki=0.05, Kd=0.10
```

### Step 6: Monitor in CubeMonitor

Add these variables to watch list:
- `tuning_current_roll`
- `tuning_roll_error`
- `tuning_roll_output`

Observe the drone's response as you change PID values.

## Terminal Commands Cheat Sheet

| Command | Purpose | Example |
|---------|---------|---------|
| `help` or `h` | Show all commands | `> help` |
| `gains` or `g` | Display all PID gains | `> gains` |
| `status` or `s` | Show measurements, errors, outputs | `> status` |
| `set_pid` | Change a PID's gains | `> set_pid roll 1.5 0.08 0.15` |

## Tuning Parameters

### What They Do

- **Kp (Proportional)**: How hard to correct the error. Higher = faster response.
- **Ki (Integral)**: Fixes remaining steady-state error. Higher = removes offset.
- **Kd (Derivative)**: Dampens oscillations. Higher = smoother, less overshoot.

### Starting Values

```
Roll:   Kp ≈ 1.0-1.5,  Ki ≈ 0.05-0.1,  Kd ≈ 0.1-0.2
Pitch:  Kp ≈ 1.0-1.5,  Ki ≈ 0.05-0.1,  Kd ≈ 0.1-0.2
Yaw:    Kp ≈ 2.0-3.0,  Ki ≈ 0.1-0.15,  Kd ≈ 0.05-0.1
```

## Tuning Procedure

1. **Start with Kp only** (Ki=0, Kd=0 or very small)
   - Increase Kp until response is fast but stable
   
2. **Add Kd** to dampen oscillations
   - Increase gradually until smooth

3. **Add Ki** to remove steady-state error
   - Start small, increase slowly
## Workflow

```
1. Edit tuning.h → Set ROLL_TUNING=1
2. Build & Flash → Upload firmware
3. Connect terminal → UART2 @ 115200
4. Type "gains" → See current values
5. Type "status" → See live measurements
6. Type "set_pid roll 1.2 0.05 0.1" → Adjust values
7. Watch CubeMonitor → Observe response
8. Repeat steps 5-7 → Fine-tune
9. Switch to next axis → Repeat for Pitch, Yaw
```

## Advanced: Change Default Gains

Edit `App/Blogic/Src/tuning.c`:

```c
float pid_roll_kp = 1.0f;    // Change these defaults
float pid_roll_ki = 0.05f;
float pid_roll_kd = 0.1f;
```

Then rebuild and flash.

## Important Safety Notes

- ⚠️ Only ONE axis can be set to 1 in tuning.h at a time
- ⚠️ When tuning Roll, Pitch and Yaw are disabled (zero output)
- ⚠️ Conduct tuning in a safe area (tethered or outdoor)
- ⚠️ Secure propellers before connecting UART

## Files Modified/Created

New:
- `App/Blogic/Inc/tuning.h`
- `App/Blogic/Src/tuning.c`
- `App/Blogic/Inc/pid_tuning_cmd.h`
- `App/Blogic/Src/pid_tuning_cmd.c`

Modified:
- `App/Control/Controller/Inc/ControlSystem.hpp`
- `App/Control/Controller/Src/ControlSystem.cpp`
- `Core/Src/main.c`
- `Core/Src/stm32f4xx_it.c`

## Detailed Documentation

For more information, see:
- [PID_TUNING_GUIDE.md](PID_TUNING_GUIDE.md) - Complete guide with examples
- [TUNING_IMPLEMENTATION_SUMMARY.md](TUNING_IMPLEMENTATION_SUMMARY.md) - Technical details
