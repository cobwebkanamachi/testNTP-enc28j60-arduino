# testNTP-enc28j60-arduino
ethercardtest
this is a fork of this bellow.<BR>
https://github.com/Microduino/Microduino_Tutorials/blob/master/Microduino_ENC/ENCnetworktwelve/ENCnetworktwelve.ino<BR>
tested under Uno compatible breadboard arduino(328p).<BR>
if you run this, you would get like shown bellow(in TZ=JST).<BR>
<BR>
NTP Demo<BR>
DHCP configuration done<BR>
IP Address:IP of self<BR>
Netmask:MASK of self<BR>
Gateway:.IP of gw<BR>
<BR>
NTP request sent<BR>
NTP answer received<BR>
<BR>
Timestamp: 3662091416<BR>
<BR>
Current date and time:<BR>
18/01/2016<BR>
16:36:56<BR>
<BR>
Postscript:<BR>
If you like timestamp verify, use this.<BR>
http://www.timestampconvert.com/<BR>
I had got "Timestamp: 3662093991" from my disignated NTP SRV.<BR>
Displayed time is correct.<BR>
But apparently differs timeStamp value from normal one.<BR>
This is experiment, so i do not care<BR>
<BR>
Notice:<BR>
I do not care accuracy of this and wrote here.<BR>
Please testify every thing with yourself :-).<BR>
I can not take responsibility.<BR>
