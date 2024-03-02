# Starting Scapy

Scapy可能需要使用到的依赖：[Download and Installation — Scapy 2.5.0 documentation](https://scapy.readthedocs.io/en/latest/installation.html#optional-dependencies)

不同平台下使用Scapy需要安装的软件：[Download and Installation — Scapy 2.5.0 documentation](https://scapy.readthedocs.io/en/latest/installation.html#platform-specific-instructions)

scapy的一些命令需要管理员权限，所以最好使用管理员权限打开scapy的命令行交互界面，ubuntu中可使用`sudo scapy -H`打开，windows中可以先用管理员权限打开cmd，再使用`scapy`打开


# Interactive tutorial
接下来将介绍一些python2.支持的scapy的一些特点
### First steps
一个IP数据包的创建、修改、删除操作：
```bash
>>> a = IP(ttl=10)
>>> a
<IP  ttl=10 |>
>>> a.src
'127.0.0.1'
>>> a.dst = "192.168.1.1"
>>> a
<IP  ttl=10 dst=192.168.1.1 |>
>>> a.src
'172.19.72.176'
>>> del(a.ttl)
>>> a
<IP  dst=192.168.1.1 |>
>>> a.ttl
64
>>>
```
- 两次src不一样的原因：Scapy根据目标IP地址来自动填充src。因为修改的dst所以src也相应的发生了改变
- Scapy中的ttl默认为为64

### Stacking layers
`/`用作不同层之间的组合操作符，较低的层可以重载高层的默认值(你也可以进行设置)，字符串可以作为原始层(raw layer)
```bash
>>> IP()
<IP  |>
>>> IP()/TCP()
<IP  frag=0 proto=tcp |<TCP  |>>
>>> Ether()/IP()/TCP()
<Ether  type=IPv4 |<IP  frag=0 proto=tcp |<TCP  |>>>
>>> IP()/TCP()/"GET / HTTP/1.0\r\n\r\n"
<IP  frag=0 proto=tcp |<TCP  |<Raw  load='GET / HTTP/1.0\r\n\r\n' |>>>
>>> Ether()/IP()/IP()/UDP()
<Ether  type=IPv4 |<IP  frag=0 proto=ipencap |<IP  frag=0 proto=udp |<UDP  |>>>>
>>> IP(proto=55)/TCP()
<IP  frag=0 proto=55 |<TCP  |>>
```
- `\r\n` 回车换行符

任何一个包都可以构造(built)或解析(dissected)。
```bash
>>> raw(IP())
b'E\x00\x00\x14\x00\x01\x00\x00@\x00|\xe7\x7f\x00\x00\x01\x7f\x00\x00\x01'
>>> IP(_)
<IP  version=4 ihl=5 tos=0x0 len=20 id=1 flags= frag=0 ttl=64 proto=hopopt chksum=0x7ce7 src=127.0.0.1 dst=127.0.0.1 |>
```
- raw()将数据包对象转换为原始字节序列(字符串)
- IP()可以将原始字节序列解析为IP数据包对象
- `_`表示最新的结果。如果最新的结果不是原始字节序列，就无法使用IP(_)进行解析

```bash
>>> a = Ether()/IP(dst="www.slashdot.org")/TCP()/"GET /index.html HTTP/1.0 \n\n"
>>> hexdump(a)
0000  EE FF FF FF FF FF 00 16 3E 04 65 D3 08 00 45 00  ........>.e...E.
0010  00 43 00 01 00 00 40 06 F9 9E AC 13 48 B0 68 12  .C....@.....H.h.
0020  24 40 00 14 00 50 00 00 00 00 00 00 00 00 50 02  $@...P........P.
0030  20 00 3C 9C 00 00 47 45 54 20 2F 69 6E 64 65 78   .<...GET /index
0040  2E 68 74 6D 6C 20 48 54 54 50 2F 31 2E 30 20 0A  .html HTTP/1.0 .
0050  0A                                               .
>>> b = raw(a)
>>> b
b'\xee\xff\xff\xff\xff\xff\x00\x16>\x04e\xd3\x08\x00E\x00\x00C\x00\x01\x00\x00@\x06\xf9\x9e\xac\x13H\xb0h\x12$@\x00\x14\x00P\x00\x00\x00\x00\x00\x00\x00\x00P\x02 \x00<\x9c\x00\x00GET /index.html HTTP/1.0 \n\n'
>>> c = Ether(b)
>>> c
<Ether  dst=ee:ff:ff:ff:ff:ff src=00:16:3e:04:65:d3 type=IPv4 |<IP  version=4 ihl=5 tos=0x0 len=67 id=1 flags= frag=0 ttl=64 proto=tcp chksum=0xf99e src=172.19.72.176 dst=104.18.36.64 |<TCP  sport=ftp_data dport=http seq=0 ack=0 dataofs=5 reserved=0 flags=S window=8192 chksum=0x3c9c urgptr=0 |<Raw  load='GET /index.html HTTP/1.0 \n\n' |>>>>
>>>
>>> c.hide_defaults()
>>> c
<Ether  dst=ee:ff:ff:ff:ff:ff src=00:16:3e:04:65:d3 type=IPv4 |<IP  ihl=5 len=67 frag=0 proto=tcp chksum=0xf99e src=172.19.72.176 dst=104.18.36.64 |<TCP  dataofs=5 chksum=0x3c9c |<Raw  load='GET /index.html HTTP/1.0 \n\n' |>>>>
>>>

```

- `hexdump(a)`：将数据包转换为十六进制表示并显示
- `c.hide_defaults()`：简化解析结果，删除与默认值相同的属性值(If this is too verbose, the method hide_defaults() will delete every field that has the same value as the default)



### Reading PCAP files

```bash
>>> a=rdpcap("/spare/captures/isakmp.cap")
>>> a
<isakmp.cap: UDP:721 TCP:0 ICMP:0 Other:0>
```



### Graphical dumps (PDF, PS)

[Usage — Scapy 2.5.0 documentation](https://scapy.readthedocs.io/en/latest/usage.html#graphical-dumps-pdf-ps)



### Generating sets of packets

```bash
>>> a = IP(dst="www.slashdot.org/30")
>>> a
<IP  dst=Net("www.slashdot.org/30") |>
>>> [p for p in a]
[<IP  dst=172.64.151.192 |>, <IP  dst=172.64.151.193 |>, 
<IP  dst=172.64.151.194 |>, <IP  dst=172.64.151.195 |>]

>>> b = IP(ttl = [1,2,(5,9)])
>>> b
<IP  ttl=[1, 2, (5, 9)] |>
>>> [p for p in b]
[<IP  ttl=1 |>, <IP  ttl=2 |>, <IP  ttl=5 |>, 
<IP  ttl=6 |>, <IP  ttl=7 |>, <IP  ttl=8 |>, <IP  ttl=9 |>]

>>> c = TCP(dport=[80, 443])
>>> [p for p in c]
[<TCP  dport=http |>, <TCP  dport=https |>]
>>> [p for p in a/c]
[<IP  frag=0 proto=tcp dst=172.64.151.192 |<TCP  dport=http |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.192 |<TCP  dport=https |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.193 |<TCP  dport=http |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.193 |<TCP  dport=https |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.194 |<TCP  dport=http |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.194 |<TCP  dport=https |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.195 |<TCP  dport=http |>>, 
<IP  frag=0 proto=tcp dst=172.64.151.195 |<TCP  dport=https |>>]
>>>
```

- 有的操作不能直接用于一组数据包（例如将数据包变成字符串），需要展开再进行使用（遍历）。如果直接对一组数据包进行`raw()`操作只有第一个数据包会转换为字符串

```bash
>>> p = PacketList(a)
>>> p
<PacketList: TCP:0 UDP:0 ICMP:0 Other:4>
>>> p = PacketList([p for p in a/c])
>>> p
<PacketList: TCP:8 UDP:0 ICMP:0 Other:0>
```

- 可以使用`PacketList`对象存储数据包集合，`PacketList`同时也提供了一些操作：

| Command         | Effect                                                     |
| --------------- | ---------------------------------------------------------- |
| summary()       | displays a list of summaries of each packet                |
| nsummary()      | same as previous, with the packet number                   |
| conversations() | displays a graph of conversations                          |
| show()          | displays the preferred representation (usually nsummary()) |
| filter()        | returns a packet list filtered with a lambda function      |
| hexdump()       | returns a hexdump of all packets                           |
| hexraw()        | returns a hexdump of the Raw layer of all packets          |
| padding()       | returns a hexdump of packets with padding                  |
| nzpadding()     | returns a hexdump of packets with non-zero padding         |
| plot()          | plots a lambda function applied to the packet list         |
| make_table()    | displays a table according to a lambda function            |



### Sending packets

```bash
>>> send(IP(dst="1.2.3.4")/ICMP())
.
Sent 1 packets.
>>> sendp(Ether()/IP(dst="1.2.3.4", ttl=(1, 4)), iface="eth1")
....
Sent 4 packets.
>>> sendp("I'm travelling on Ethernet", iface="eth1", loop=1, inter=0.2)
................^C
Sent 16 packets.
>>> send(IP(dst='127.0.0.1'), return_packets = True)
.
Sent 1 packets.
<PacketList: TCP:0 UDP:0 ICMP:0 Other:1>
```

- The `send()` function will send packets at layer 3. That is to say, it will handle routing and layer 2 for you.
-  The `sendp()`function will work at layer 2. It’s up to you to choose the right interface and the right link layer protocol. 
- send() and sendp() will also return sent packet list if `return_packets=True` is passed as parameter.
- `sendp()`中的`iface`可以通过`ifconfig`(linux)或`ipconfig`(windows)查看



### Fuzzing

```bash
>>> send(IP(dst="target")/fuzz(UDP()/NTP(version=4)),loop=1)
................^C
Sent 16 packets.
```

- `fuzz()`可以修改任何不是通过计算得到的值(检验和是通过计算得到的，无法修改)
- Note: If you use fuzz() in IP layer, src and dst parameter won’t be random so in order to do that use RandIP().



### Injecting bytes

```bash
>>> pkt = IP(len=RawVal(b"NotAnInteger"), src="127.0.0.1")
>>> bytes(pkt)
b'H\x00NotAnInt\x0f\xb3er\x00\x01\x00\x00@\x00\x00\x00\x7f\x00\x00\x01\x7f\x00\x00\x01\x00\x00'
>>>
```

[Usage — Scapy 2.5.0 documentation](https://scapy.readthedocs.io/en/latest/usage.html#injecting-bytes)



### Send and receive packets (sr)

```bash
>>> p = sr1(IP(dst="www.slashdot.org")/ICMP()/"XXXXXXXXXXX")
Begin emission:
...Finished to send 1 packets.
.*
Received 5 packets, got 1 answers, remaining 0 packets
>>> p
<IP version=4L ihl=5L tos=0x0 len=39 id=15489 flags= frag=0L ttl=42 proto=ICMP
 chksum=0x51dd src=66.35.250.151 dst=192.168.5.21 options='' |<ICMP type=echo-reply
 code=0 chksum=0xee45 id=0x0 seq=0x0 |<Raw load='XXXXXXXXXXX'
 |<Padding load='\x00\x00\x00\x00' |>>>>
>>> p.show()
---[ IP ]---
version   = 4L
ihl       = 5L
tos       = 0x0
len       = 39
id        = 15489
flags     =
frag      = 0L
ttl       = 42
proto     = ICMP
chksum    = 0x51dd
src       = 66.35.250.151
dst       = 192.168.5.21
options   = ''
---[ ICMP ]---
   type      = echo-reply
   code      = 0
   chksum    = 0xee45
   id        = 0x0
   seq       = 0x0
---[ Raw ]---
      load      = 'XXXXXXXXXXX'
---[ Padding ]---
         load      = '\x00\x00\x00\x00'
```

- `sr()`：发送数据包接收回答，`sr1()`，`sr()`的variant(变形)，只返回一个应答报文，两者都工作在网络层（三层，IP、ARP、etc）
- `srp()`：工作在链路层（二层，Ethernet、802.3、etc）
- 如果没有响应，则在超时到达之前会返回一个空值

```bash
>>> sr1(IP(dst="192.168.5.1")/UDP()/DNS(rd=1,qd=DNSQR(qname="www.slashdot.org")))
Begin emission:
Finished to send 1 packets.
..*
Received 3 packets, got 1 answers, remaining 0 packets
<IP version=4L ihl=5L tos=0x0 len=78 id=0 flags=DF frag=0L ttl=64 proto=UDP chksum=0xaf38
 src=192.168.5.1 dst=192.168.5.21 options='' |<UDP sport=53 dport=53 len=58 chksum=0xd55d
 |<DNS id=0 qr=1L opcode=QUERY aa=0L tc=0L rd=1L ra=1L z=0L rcode=ok qdcount=1 ancount=1
 nscount=0 arcount=0 qd=<DNSQR qname='www.slashdot.org.' qtype=A qclass=IN |>
 an=<DNSRR rrname='www.slashdot.org.' type=A rclass=IN ttl=3560L rdata='66.35.250.151' |>
 ns=0 ar=0 |<Padding load='\xc6\x94\xc7\xeb' |>>>>
```

- 向域名服务器`192.168.5.1`查询域名为`www.slashdot.org`的IP
- `rd = 1`表示使用递归搜索，`recursion desired`

**还有部分未完成**

### SYN Scans

### TCP traceroute

### Configuring super sockets

### Sniffing

