import serial
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# 设置串口参数
ser = serial.Serial('COM15', 9600, timeout=1)  # 串口名称和波特率

# 创建存储数据的列表
distances = []
speeds = []

# 设置绘图范围和缩放比例
plt.xlim(0, 100)  # 时间范围
plt.ylim(-100, 100)  # 速度距离范围

# 创建曲线对象
line1, = plt.plot([], [], 'b-', label='Distance')
line2, = plt.plot([], [], 'r-', label='Speed')

def update(frame):
    # 从串口读取数据，数据格式为"%d %d\n"
    data = ser.readline().decode("utf-8").strip()
    if data:
        distance, speed = map(int, data.split())

        # 添加数据到列表
        distances.append((distance-400) / 5)
        speeds.append(speed / 10)

        # 限制数据长度，保持在100个数据点内
        if len(distances) > 100:
            distances.pop(0)
            speeds.pop(0)

        # 更新曲线数据
        line1.set_data(range(len(distances)), distances)
        line2.set_data(range(len(speeds)), speeds)

        return line1, line2

ani = FuncAnimation(plt.gcf(), update, blit=True, interval=10)

plt.show()

# 关闭串口连接
ser.close()
