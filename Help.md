# Root Login

$ screen /dev/tty.usbmodem<varies> 115200

#“logout” when done

#To quit the screen app, type CTRL-A, then CTRL-\ while in screen
#If you don't quit screen with this, you may not be able to get back in. You would have to restart the computer to get back in.




# SSH Login

ssh debian@beaglebone.local

#“logout” when done
#when executing commands as debian login which are administrative, start with "sudo" eg. "sudo apt-get update"




# To get internet working
#Assumes you are logged in as root on screen or debian on ssh
#Connect to RedRover
#System Preferences>>Sharing   select Internet Sharing over Wifi with BBB

$ dhclient

$ ping google.com

$ wget http://beagleboard.org

#If internet doesn't work, try "/sbin/route add default gw 192.168.7.1"




# To compile C++ code
BBB requires compiler and library support for the ISO C++ 2011 standard.
Whenever compiling, also list flag shown in error here -std=c++11 or -std=gnu++11
/usr/include/c++/4.9/bits/c++0x_warning.h:32:2: error: #error This file requires compiler and library support for the ISO C++ 2011 standard. This support is currently experimental, and must be enabled with the -std=c++11 or -std=gnu++11 compiler options.



# Resources
BlackLib Support: http://blacklib.yigityuce.com/index.html
Online BlackLib Manual: http://blacklib.yigityuce.com/v1_0/DOCUMENTS/EN/BlackLib-UserManual.pdf
BBB Chat Room: https://beagleboard.org/chat
BBB Forum: https://groups.google.com/forum/#!forum/beagleboard
Source code for the book Exploring BeagleBone: https://github.com/derekmolloy/exploringBB/




# If the steps above fail
#the remainder of this text file might help. It is somewhat repetitive, so scan through first.

Quick login (and verify system connections)
screen /dev/tty.usbmodem<varies> 115200
// login as root with password Nx8tV3r (default password is root)
ping google.com // verify network connection
if fails, type in dhclient
wget http://beagleboard.org // verify internet connection
date // verify it is correct
if incorrect
$ sudo ntpdate pool.ntp.org
31 Aug 19:05:55 ntpdate[8911]: the NTP socket is in use, exiting
$ sudo service ntp stop
[ ok ] Stopping NTP server: ntpd.
$ sudo ntpdate pool.ntp.org
31 Aug 19:07:11 ntpdate[10355]: adjust time server 46.29.176.115 offset -0.002893 sec
$ sudo service ntp start
date // verify it is correct
logout
Make sure to quit the screen app: type CTRL-A, then CTRL-\ while in screen
ssh debian@beaglebone.local
// never asked for login, but if it does login is debian, password Nx8tV3r
ping google.com // verify network connection
wget http://beagleboard.org // verify internet connection
date // verify it is correct

Quick Tips:
to remove a local git directory: sudo rm -r <directory name>

———————————————————————

I don’t have to do any of the instructions below now that the board is setup. Incase I need to again, do not re flash board. If I have to re-flash, extract new code off the board (push to git-hub).

Mission: BeagleBone Black Internet-over-USB on Mac

Initial setup

1. To flash board: Download latest software image and put image on SD card with Etcher software. Insert SD card into non-powered BBB. Hold down USER/BOOT button and then apply power with USB (USB is connected to my computer) and let go of button after a few seconds.
Online guides can be misguiding, just a warning.

2. Turn off board, leave SD card inserted, re-connect board to Mac. Install drivers and restart computer. In SystemPreferences>Network, the BBB is connected, with yellow tag. Turn on internet sharing with BBB under RedRover Wifi. In terminal, enter “screen /dev/tty.usbmodem<press "tab"> 115200” and am able to log in as root with password root. Enter in “dhclient”. ping to 8.8.8.8 or website results in “64 bytes from …” etc.. indicating success in this step.

Exit screen and enter “ssh root@beaglebone.local -l debian” OR "ssh debian@beaglebone.local" password is temppwd. If you get man-in-the-middle attack warning, enter “ssh-keygen -R beaglebone.local” to get rid of the warning. Then try to login in again. Will be prompted with question, so answer "yes".

ssh debian@beaglebone.local
sudo apt-get update // works
sudo apt-get install ntp // works
// downloaded great! Success!

The following is to get the time accurate, which is not necessary for this mission.
Go back to screen
screen /dev/tty.usbmodem<click "tab"> 115200
dhclient
/sbin/route add default gw 192.168.7.1
(ping works well)
“ntpdate -b -s -u pool.ntp.org” // failed…
“apt-get update” // may be unnecessary
“apt-get install ntp” // may be unnecessary
“apt-get install ntpdate”

$ sudo ntpdate pool.ntp.org
31 Aug 19:05:55 ntpdate[8911]: the NTP socket is in use, exiting
$ sudo service ntp stop
[ ok ] Stopping NTP server: ntpd.
$ sudo ntpdate pool.ntp.org
31 Aug 19:07:11 ntpdate[10355]: adjust time server 46.29.176.115 offset -0.002893 sec
$ sudo service ntp start

dpkg-reconfigure tzdata // for time zone

// or use this for timezone
“cd /etc”
“rm localtime”
“ln -s /usr/share/zoneinfo/America/New_York /etc/localtime” // Success! Time is accurate

To test internet connection (as root):
“wget http://beagleboard.org”

// if internet cuts off remove default IP
netstat -rn // see list
ip route delete

The reason I can’t get back into screen is that I never terminate screen, so it thinks screen is busy.
To quit the screen app, type CTRL-A, then CTRL-\ while in screen

Summary:
Use screen to access root, and ssh to access debian
use sudo in debian when access is not granted.
