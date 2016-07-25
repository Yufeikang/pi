import  SensorLib as s

ret =s.Init()
if ret == 0:
	print("Init Ok!")
else:
	print("Init ERR!")
humidity,temp,status= s.GetAM2301Data()

print("humidity:%f" % humidity)
print("temperature:%f" % temp)
print("status:%f" % status)


