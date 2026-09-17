def ft_water_reminder():
    last_watered = int(input("Days since last watering: "))
    if last_watered >= 3:
        print ("Water the plants!")
    else:
        print ("Plants are fine")