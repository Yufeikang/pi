import SensorLib as s
import time

ret = s.Init()
if ret == 0:
    print("Init Ok!")
else:
    print("Init ERR!")
humidity, temp, status = s.GetAM2301Data()

print("humidity:%f" % humidity)
print("temperature:%f" % temp)
print("status:%f" % status)
s.GPIOSetMode(7, "OUTPUT".encode("ascii"))
s.GPIOSetPullUpDn(7, "PUD_OFF".encode("ascii"))
s.GPIODWrite(7, 0)
lcdOn = True
while True:
    humidity, temp, status = s.GetAM2301Data()
    if status == 1:
        s.LcdSendCmd(1)
        s.LcdSendCmd(0x80)
        data = "湿度:%.2f hr" % humidity
        s.LcdShow(data.encode("gbk"))
        data = "温度：%.2f C" % temp
        s.LcdSendCmd(0x90)
        s.LcdShow(data.encode("gbk"))
        s.LcdSendCmd(0x88)
        time_str = time.strftime("%A %H:%M")
        s.LcdShow(time_str.encode("gbk"))
    time.sleep(2)
    hour = time.localtime().tm_hour
    if 9 <= hour < 22:  # and lcdOn==False:
        s.GPIODWrite(7, 0)
        lcdOn = True
        print("lcd on")
    elif 0 <= hour < 9:  # and lcdOn==True:
        s.GPIODWrite(7, 1)
        lcdOn = False
        print("lcd off")
