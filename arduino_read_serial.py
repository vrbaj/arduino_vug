import serial
from time import sleep
from pathlib import Path
import csv
from datetime import datetime


def read_arduino(com_port, baudrate, path_to_file):
    ser = serial.Serial(com_port, baudrate, timeout=0.1)         # 1/timeout is the frequency at which the port is read
    while True:
        data = ser.readline().decode().strip()
        if data:
            print(data)
            if ";" in data:
                # valid measurement values received
                # expected temperature;humidity;pressure
                values = data.split(";")
                now = datetime.now()
                values.append(now.strftime("%Y-%m-%d %H:%M:%S"))
                with open(path_to_file, "w") as f:
                    writer = csv.writer(f, delimiter=";")
                    writer.writerow(values)
        sleep(1)


if __name__ == '__main__':
    path_to_save = Path("temperature.csv")
    if not path_to_save.exists():
        print("file with values does not exist")
        with open(path_to_save, "w") as f:
            writer = csv.writer(f, delimiter=";")
            writer.writerow(["temperature", "humidity", "pressure", "datetime"])
    read_arduino('COM6', 9600, path_to_save)
