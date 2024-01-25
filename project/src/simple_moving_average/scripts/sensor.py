#!/usr/bin/env python

import rospy
import random
import math
from std_msgs.msg import Float64

def sensor():

    pub = rospy.Publisher('sensor_measurement', Float64, queue_size=100)
    rospy.init_node('sensor_driver_node', anonymous=True)
    rate = rospy.Rate(100)

    count = 0

    while not rospy.is_shutdown():

        g = random.gauss(0.0, 0.05)

        f = math.sin(count * math.pi / 180) + g

        count = count + 1

        rospy.loginfo(f)
        pub.publish(f)
        rate.sleep()

if __name__ == '__main__':
    try:
        sensor()
    except rospy.ROSInterruptException:
        pass