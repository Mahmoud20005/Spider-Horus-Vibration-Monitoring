import socket
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# Clear any previously opened figures to prevent memory issues
plt.close('all')

UDP_IP = "0.0.0.0"
UDP_PORT = 12345

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((UDP_IP, UDP_PORT))

# Enable non-blocking mode for real-time data reception
sock.setblocking(False)

y_data = []
limit = 100

fig, ax = plt.subplots(figsize=(10, 5))
line, = ax.plot([], [], lw=2, color='red')

# Configure graph limits and appearance
ax.set_ylim(0, 0.8)
ax.set_xlim(0, limit)
ax.set_title("Real-Time Micro-Vibration Analysis - Spider Horus")
ax.set_xlabel("Time (Samples)")
ax.set_ylabel("Vibration Intensity (G)")
ax.grid(True, linestyle='--', alpha=0.7)


def update(frame):
    latest_value = None

    # Read the most recent UDP packet and discard older buffered data
    while True:
        try:
            data, addr = sock.recvfrom(1024)
            latest_value = float(data.decode())
        except BlockingIOError:
            # No more data available
            break
        except Exception:
            # Ignore unexpected communication errors
            break

    # Update the live graph if new data is received
    if latest_value is not None:
        y_data.append(latest_value)

        # Keep only the latest samples
        if len(y_data) > limit:
            y_data.pop(0)

        # Update x-axis values and refresh the plot
        x_data = list(range(len(y_data)))
        line.set_data(x_data, y_data)

    return line,


# Create a real-time animation with a 10 ms refresh interval
ani = FuncAnimation(
    fig,
    update,
    interval=10,
    blit=False,
    cache_frame_data=False
)

# Display the live vibration monitoring window
plt.show()
