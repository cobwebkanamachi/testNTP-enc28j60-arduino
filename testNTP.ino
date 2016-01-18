//https://github.com/Microduino/Microduino_Tutorials/blob/master/Microduino_ENC/ENCnetworktwelve/ENCnetworktwelve.ino<BR>
#include <EtherCard.h><BR>
<BR>
#define SECONDS_IN_DAY 86400<BR>
#define START_YEAR 1900<BR>
#define TIME_ZONE 9<BR>
//#define TIME_ZONE +1<BR>
static int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};<BR>
<BR>
// ethernet interface mac address, must be unique on the LAN<BR>
static byte mymac[] = { <BR>
  0x74,0x69,0x69,0x2D,0x30,0x31 };<BR>
<BR>
static byte ntpServer[] = {127,0,0,1}; //you should specify your NTP SRV in Decimal comma separated form<BR>
static byte srcPort = 0;<BR>
<BR>
<BR>
uint32_t timeStamp;<BR>
boolean requestSent;<BR>
<BR>
#define INTERVAL 10000<BR>
unsigned long lastTime = 0;<BR>
<BR>
byte Ethernet::buffer[700];<BR>
BufferFiller bfill;<BR>
<BR>
<BR>
void setup () {<BR>
<BR>
  Serial.begin(57600);<BR>
  Serial.println("NTP Demo");<BR>
<BR>
  if (ether.begin(sizeof Ethernet::buffer, mymac) == 0)<BR>
    Serial.println( "Failed to access Ethernet controller");<BR>
<BR>
  if (!ether.dhcpSetup())<BR>
    Serial.println("Failed to get configuration from DHCP");<BR>
  else<BR>
    Serial.println("DHCP configuration done");<BR>
 <BR>
  ether.printIp("IP Address:\t", ether.myip);<BR>
  ether.printIp("Netmask:\t", ether.netmask);<BR>
  ether.printIp("Gateway:\t", ether.gwip);<BR>
<BR>
  Serial.println();<BR>
  requestSent = false;<BR>
<BR>
}<BR>
<BR>
<BR>
void loop() {<BR>
<BR>
  ether.packetLoop(ether.packetReceive());<BR>
<BR> 
  if(requestSent && ether.ntpProcessAnswer(&timeStamp, srcPort)) {<BR>
    Serial.println("NTP answer received");<BR>
    Serial.println();<BR>
    Serial.print("Timestamp: ");<BR>
    Serial.println(timeStamp);<BR>
    Serial.println();<BR>
    printDate(timeStamp + 3600 * TIME_ZONE);<BR>
    requestSent = false;<BR>
  }<BR>
<BR>
  unsigned long time = millis();<BR>
  if(time - lastTime > INTERVAL) {<BR>
    lastTime = time;<BR>
    ether.ntpRequest(ntpServer, srcPort);<BR>
    Serial.println("NTP request sent");<BR>
    requestSent = true;<BR>
  }<BR>
}<BR>
<BR>
void printDate(uint32_t timeStamp) {<BR>
<BR>  
  unsigned int year = START_YEAR;<BR>
  while(1) {<BR>
    uint32_t seconds;<BR>
    if(isLeapYear(year)) seconds = SECONDS_IN_DAY * 366;<BR>
    else seconds = SECONDS_IN_DAY * 365;<BR>
    if(timeStamp >= seconds) {<BR>
      timeStamp -= seconds;<BR>
      year++;<BR>
    } else break;<BR>
  }<BR>
  <BR>
  unsigned int month = 0;<BR>
  while(1) {<BR>
    uint32_t seconds = SECONDS_IN_DAY * days_in_month[month];<BR>
    if(isLeapYear(year) && month == 1) seconds = SECONDS_IN_DAY * 29;<BR>
    if(timeStamp >= seconds) {<BR>
      timeStamp -= seconds;<BR>
      month++;<BR>
    } else break;<BR>
  }<BR>
  month++;<BR>
<BR>  
  unsigned int day = 1;<BR>
  while(1) {<BR>
    if(timeStamp >= SECONDS_IN_DAY) {<BR>
      timeStamp -= SECONDS_IN_DAY;<BR>
      day++;<BR>
    } else break;<BR>
  }<BR>
<BR>
  unsigned int hour = timeStamp / 3600;<BR>
  unsigned int minute = (timeStamp - (uint32_t)hour * 3600) / 60;<BR>
  unsigned int second = (timeStamp - (uint32_t)hour * 3600) - minute * 60;<BR>
<BR>  
  Serial.println("Current date and time:");<BR>
<BR>
  if(day < 10) Serial.print("0");<BR>
  Serial.print(day);<BR>
  Serial.print("/");<BR>
  <BR>
  if(month < 10) Serial.print("0");<BR>
  Serial.print(month);<BR>
  Serial.print("/");<BR>
  <BR>
  Serial.println(year);<BR>
  <BR>
  if(hour < 10) Serial.print("0");<BR>
  Serial.print(hour);<BR>
  Serial.print(":");<BR>
  <BR>
  if(minute < 10) Serial.print("0");<BR>
  Serial.print(minute);<BR>
  Serial.print(":");<BR>
  <BR>
  if(second < 10) Serial.print("0");<BR>
  Serial.println(second);<BR>
  <BR>
  Serial.println();<BR>
}<BR>
<BR>
boolean isLeapYear(unsigned int year) {<BR>
  <BR>
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));<BR>
}<BR>
