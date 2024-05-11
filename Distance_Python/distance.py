import serial
import matplotlib.pyplot as plt

# 设置串口参数，根据你的PSoC配置进行更改
ser = serial.Serial('COM15', 9600, timeout=1)  # 串口名称和波特率

# 创建存储数据的文件
distance_file = open("distance.txt", "w")
speed_file = open("speed.txt", "w")

# 初始化数据列表
time = []
distances = []
speeds = []

try:
    while True:
        # 从串口读取数据，假设数据格式为"%d %d\n"
        data = ser.readline().decode("utf-8").strip()
        if data:
            distance, speed = map(int, data.split())

            # 将数据存储到文件
            distance_file.write(f"{distance}\n")
            speed_file.write(f"{speed}\n")

            # 添加数据到列表
            time.append(len(time))  # 使用时间作为x轴
            distances.append(distance)
            speeds.append(speed)

except KeyboardInterrupt:
    print("Interrupted")

finally:
    # 绘制图像
    plt.plot(time, distances, 'b-', label='Distance')
    plt.plot(time, speeds, 'r-', label='Speed')

    plt.xlabel('Time')
    plt.legend()

    # 保存图像
    plt.savefig('plot.png')

    # 关闭文件和串口连接
    distance_file.close()
    speed_file.close()
    ser.close()
