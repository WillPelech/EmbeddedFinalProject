import time
import board
import displayio
import terminalio
from adafruit_display_text import label
from adafruit_display_shapes.rect import Rect
from adafruit_display_shapes.line import Line
from adafruit_gizmo import tft_gizmo
import adafruit_lis3dh
import pulseio
import adafruit_irremote

# Initialize display
display = tft_gizmo.TFT_Gizmo()

# Initialize accelerometer
i2c = board.I2C()
lis3dh = adafruit_lis3dh.LIS3DH_I2C(i2c)

# Create display group
splash = displayio.Group()
display.show(splash)

# Colors
BLACK = 0x000000
WHITE = 0xFFFFFF
RED = 0xFF0000
GREEN = 0x00FF00
YELLOW = 0xFFFF00
BLUE = 0x0000FF

# Heart rate zones
ZONE_RESTING = (50, 60)
ZONE_MODERATE = (60, 70)
ZONE_ACTIVE = (70, 100)

def create_zone_box(x, y, width, height, color, text, bpm_range):
    """Create a zone display box with text"""
    box = Rect(x, y, width, height, fill=color)
    splash.append(box)
    
    # Add zone text
    text_area = label.Label(terminalio.FONT, text=text, color=BLACK)
    text_area.x = x + 5
    text_area.y = y + 10
    splash.append(text_area)
    
    # Add BPM range
    bpm_text = label.Label(terminalio.FONT, text=f"{bpm_range[0]}-{bpm_range[1]} BPM", color=BLACK)
    bpm_text.x = x + 5
    bpm_text.y = y + 30
    splash.append(bpm_text)
    
    return box

def create_heart_rate_display(x, y):
    """Create the current heart rate display"""
    # Background
    bg = Rect(x, y, 100, 60, fill=WHITE)
    splash.append(bg)
    
    # Title
    title = label.Label(terminalio.FONT, text="Heart Rate", color=BLACK)
    title.x = x + 5
    title.y = y + 10
    splash.append(title)
    
    # BPM value
    bpm = label.Label(terminalio.FONT, text="--", color=RED)
    bpm.x = x + 30
    bpm.y = y + 40
    splash.append(bpm)
    
    return bpm

def create_accelerometer_display(x, y):
    """Create the accelerometer data display"""
    # Background
    bg = Rect(x, y, 100, 100, fill=WHITE)
    splash.append(bg)
    
    # Title
    title = label.Label(terminalio.FONT, text="Accelerometer", color=BLACK)
    title.x = x + 5
    title.y = y + 10
    splash.append(title)
    
    # Axis labels
    x_label = label.Label(terminalio.FONT, text="X: --", color=BLACK)
    x_label.x = x + 5
    x_label.y = y + 30
    splash.append(x_label)
    
    y_label = label.Label(terminalio.FONT, text="Y: --", color=BLACK)
    y_label.x = x + 5
    y_label.y = y + 50
    splash.append(y_label)
    
    z_label = label.Label(terminalio.FONT, text="Z: --", color=BLACK)
    z_label.x = x + 5
    z_label.y = y + 70
    splash.append(z_label)
    
    return x_label, y_label, z_label

# Create the dashboard layout
# Heart rate zones
resting_zone = create_zone_box(10, 10, 100, 50, 0xFF9999, "Resting", ZONE_RESTING)
moderate_zone = create_zone_box(10, 70, 100, 50, 0xFFFF99, "Moderate", ZONE_MODERATE)
active_zone = create_zone_box(10, 130, 100, 50, 0x99FF99, "Active", ZONE_ACTIVE)

# Current heart rate
heart_rate_display = create_heart_rate_display(120, 10)

# Accelerometer data
x_label, y_label, z_label = create_accelerometer_display(120, 80)

# Main loop
while True:
    # Update accelerometer data
    x, y, z = lis3dh.acceleration
    x_label.text = f"X: {x:.2f}"
    y_label.text = f"Y: {y:.2f}"
    z_label.text = f"Z: {z:.2f}"
    
    # TODO: Add heart rate sensor reading logic here
    # For now, we'll use a placeholder value
    heart_rate = 75
    heart_rate_display.text = f"{heart_rate}"
    
    # Update display
    display.refresh()
    
    # Small delay to prevent screen flicker
    time.sleep(0.1) 