import  SensorLib as s
import  time
ret =s.Init()
if ret == 0:
	print("Init Ok!")
else:
	print("Init ERR!")
humidity,temp,status= s.GetAM2301Data()

print("humidity:%f" % humidity)
print("temperature:%f" % temp)
print("status:%f" % status)

while True:
	humidity,temp,status= s.GetAM2301Data()
	s.LcdSendCmd(1);
	s.LcdSendCmd(0x80);
	data = "humidity:%.2f" % humidity
	s.LcdShow(data.encode("utf-8"));
	data = "温度：%.2f" % temp
	s.LcdSendCmd(0x90)
	s.LcdShow(data.encode("gbk"))
	time.sleep(2)
