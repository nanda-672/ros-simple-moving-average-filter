# Day-1 Bonus Assignment

## Sensor Node
```
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
```
Breakdown:
```
import rospy
import random
import math
from std_msgs.msg import Float64
```
mengimport library yang dibutuhkan dalam menjalankan program

```
    pub = rospy.Publisher('sensor_measurement', Float64, queue_size=100)
    rospy.init_node('sensor_driver_node', anonymous=True)
    rate = rospy.Rate(100)
```
melakukan tahap inisialisasi node dan tujuan publish nya.

```
    count = 0
```
inisiasi perhitungan yang nantinya digunakan untuk mengenerate random number

```
    while not rospy.is_shutdown():

        g = random.gauss(0.0, 0.05)

        f = math.sin(count * math.pi / 180) + g

        count = count + 1
```
selama node masih berjalan, mengenerate random number (g) menggunakan distribusi gauss dengan mean=0 dan sigma=0,05. serta melakukan kalkulasi pada elemen yang nantinya akan di publish (f). Dan juga menaikkan hitungan.
```
        rospy.loginfo(f)
        pub.publish(f)
        rate.sleep()
```
mencetak dan mempublish elemen. lalu mendiamkan program agar rate 100hz nya tepat.

```
if __name__ == '__main__':
    try:
        sensor()
    except rospy.ROSInterruptException:
        pass
```
exception digunakan agar kode tidak dieksekusi ketika sedang sleep.

## Filter Node
```
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <list>
#include <numeric>

void callback(const std_msgs::Float64::ConstPtr& f)
{
    double z;
    double sum;
    std::list<double> mylist;

    while(mylist.size() != 5)
    {
        mylist.push_back(f->data);
    }

    sum = std::accumulate(std::begin(mylist), std::end(mylist), 0.0);

    z = sum/5;

    if (mylist.size() == 5)
    {
        ROS_INFO("%f", z);
        mylist.pop_front();
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "filter_node");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("sensor_measurement", 100, callback);

    ros::spin();

    return 0;
}
```
Breakdown:
```
#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <list>
#include <numeric>
```
menginclude library yang akan digunakan dalam program nantinya.
```
void callback(const std_msgs::Float64::ConstPtr& f)
{
    double z;
    double sum;
    std::list<double> mylist;
```
membuat fungsi callback untuk memroses nilai yang diberikan oleh sensor node. inisialisasi variabel yang akan digunakan dalam fungsi.
```
    while(mylist.size() != 5)
    {
        mylist.push_back(f->data);
    }
```
mengisi list hingga didapat 5 anggota didalamnya. Karena input dari belakang, berarti elemen list terakhir adalah elemen terbaru.
```
    sum = std::accumulate(std::begin(mylist), std::end(mylist), 0.0);

    z = sum/5;
```
melakukan perhitungan average dari list yang ada.
```
    if (mylist.size() == 5)
    {
        ROS_INFO("%f", z);
        mylist.pop_front();
    }
```
ketika list sudah mencapai 5 anggota, maka node mulai mencetak nilai dari average (z). Lalu, menghilangkan anggota terdepan (terlama) dari list itu.
```
int main(int argc, char **argv)
{
    ros::init(argc, argv, "filter_node");

    ros::NodeHandle n;

    ros::Subscriber sub = n.subscribe("sensor_measurement", 100, callback);

    ros::spin();

    return 0;
}
```
menjalankan fungsi.

## Edit CMakeLists.txt
sebelum menjalankan catkin_make pada direktori workspace, editlah file CMakelists.txt anda dan tambah line ini di bawah,
```
add_executable(filter_node src/filter.cpp)

target_link_libraries(filter_node
  ${catkin_LIBRARIES}
)

catkin_install_python(PROGRAMS
  scripts/sensor.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
```
