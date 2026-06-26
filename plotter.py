import serial
import matplotlib.pyplot as plt
from matplotlib.ticker import MultipleLocator
import time 

PORT = 'COM4'
BAUD_RATE = 115200

MAX_POINTS = 50

frame_id = 0
frameIDOffset = 0

tnow = 0
tnowOffset = 0

ser = serial.Serial(PORT, BAUD_RATE, timeout=1)

# address -> data
radars = {}

plt.ion()
fig, ax = plt.subplots()

ax.set_ylim(150, 1600)
ax.yaxis.set_major_locator(MultipleLocator(100))
ax.xaxis.set_major_locator(MultipleLocator(5))
ax.set_xlabel("Sample")
ax.set_ylabel("Distance (mm)")
ax.set_title("XM125 Live Distance - Two Radars")

text_display = ax.text(
    0.02, 0.95, "",
    transform=ax.transAxes,
    fontsize=10,
    verticalalignment="top"
)

print("Listening to serial...")

def get_radar(addr):
    if addr not in radars:
        line, = ax.plot([], [], label=f"Radar {addr}")
        radars[addr] = {
            "frames": [],
            "distances": [],
            "line": line,
            "latest": None
        }
        ax.legend()

    return radars[addr]

log_file = open("serial.log", "a", buffering=1)  # line-buffered

while True:
    try:
        line_str = ser.readline().decode(errors="ignore").strip()
            

        if not line_str or not line_str[0].isdigit():
            continue

        parts = line_str.split(",")

        # CSV:
        # frame,address,loop_start,retCode,distances,raw_mm,filtered_mm,strength,...
        # trailing comma creates an empty last item, so accept 14 or 13
        if len(parts) < 14:
            continue

        frame_id = int(parts[0])+frameIDOffset
        
        addr = parts[1]
        
        retcode = int(parts[3])
        distances = int(parts[4])
        raw_mm = int(parts[5])
        filtered_mm = int(parts[6])
        p0_str = int(parts[7])
        
        tnow = int(parts[13])+tnowOffset

        if raw_mm <= 0 or not (150 <= raw_mm <= 1600):
            text_display.set_text(f"Radar {addr}: No Peak Detected")

        radar = get_radar(addr)

        radar["frames"].append(frame_id)
        radar["distances"].append(filtered_mm)
        radar["latest"] = filtered_mm

        if len(radar["frames"]) > MAX_POINTS:
            radar["frames"] = radar["frames"][-MAX_POINTS:]
            radar["distances"] = radar["distances"][-MAX_POINTS:]

        x = range(len(radar["distances"]))
        radar["line"].set_xdata(x)
        radar["line"].set_ydata(radar["distances"])

        display = ""
        for a, r in radars.items():
            if r["latest"] is not None:
                display += f"Radar {a}: {r['latest']} mm\n"

        text_display.set_text(display.strip())

        ax.relim()
        ax.autoscale_view()
        ax.set_ylim(150, 1600)

        plt.pause(0.01)
        if log_file.tell() == 0:
            log_file.write("frame id | address | retcode | numDistances | raw_mm | filtered_mm | p0 str | time now")
        log_file.write(f"{frame_id},{addr},{retcode},{distances},{raw_mm},{filtered_mm},{p0_str},{tnow},\n")

    except serial.SerialException:
        frameIDOffset=frame_id+1
        tnowOffset=tnow+1
        try:
            ser.close()
        except Exception:
            pass

        while True:
            try:
                ser = serial.Serial(PORT, BAUD_RATE, timeout=1)
                ser.reset_input_buffer()
                print("Reconnected!")
                break
            except serial.SerialException:
                time.sleep(1)
    except KeyboardInterrupt:
        print("Stopped")
        break