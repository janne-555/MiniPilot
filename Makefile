CC=gcc

CFLAGS=\
-I. \
-I./libraries/generated/include/mavlink/v2.0

SRC=\
main.c \
AP_Scheduler/AP_Scheduler.c \
AP_HAL/HAL_Linux.c \
AP_Vehicle/AP_Vehicle.c \
AP_Battery/AP_Battery.c \
AP_Baro/AP_Baro.c \
AP_GPS/AP_GPS.c \
AP_AHRS/AP_AHRS.c \
AP_IMU/AP_IMU.c \
AP_EKF/AP_EKF.c \
AP_Home/AP_Home.c \
AP_RC/AP_RC.c \
AP_Control/AP_Control.c \
AP_Compass/AP_Compass.c \
AP_FlightMode/AP_FlightMode.c \
AP_PID/AP_PID.c \
AP_Sim/AP_Sim.c \
AP_Mixer/AP_Mixer.c \
AP_Motors/AP_Motors.c \
AP_Param/AP_Param.c \
AP_Mode/AP_Mode.c \
AP_Nav/AP_Nav.c \
AP_Mission/AP_Mission.c \
AP_Logger/AP_Logger.c \
AP_Arming/AP_Arming.c \
AP_Input/AP_Keyboard.c \
AP_InertialNav/AP_InertialNav.c \
AP_PosControl/AP_PosControl.c \
AP_Debug/AP_Debug.c \
AP_Failsafe/AP_Failsafe.c \
GCS_MAVLink/GCS_Heartbeat.c \
GCS_MAVLink/GCS_Parser.c \
GCS_MAVLink/GCS_Statustext.c \
GCS_MAVLink/GCS_SysStatus.c \
GCS_MAVLink/GCS_Attitude.c \
GCS_MAVLink/GCS_GPS.c \
GCS_MAVLink/GCS_VFR_HUD.c \
GCS_MAVLink/GCS_Commands.c \
GCS_MAVLink/GCS_GlobalPosition.c \
GCS_MAVLink/GCS_EKFStatus.c \
GCS_MAVLink/GCS_Home.c \
GCS_MAVLink/GCS_Request.c \
GCS_MAVLink/GCS_AutopilotVersion.c \
GCS_MAVLink/GCS_ProtocolVersion.c \
GCS_MAVLink/GCS_MessageInterval.c \
GCS_MAVLink/GCS_Camera.c \
GCS_MAVLink/GCS_BatteryStatus.c \
GCS_MAVLink/GCS_LocalPosition.c \
GCS_MAVLink/GCS_Stream.c \
GCS_MAVLink/GCS_RC.c \
GCS_MAVLink/GCS_Servo.c \
GCS_MAVLink/GCS_Mission.c \
GCS_MAVLink/GCS_SystemTime.c \
GCS_MAVLink/GCS_ExtendedState.c \
GCS_MAVLink/GCS_Timesync.c \
GCS_MAVLink/GCS_Params.c
all:
	$(CC) $(SRC) $(CFLAGS) -o build/minipilot -lm

clean:
	rm -f build/minipilot
