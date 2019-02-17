## 消息推送系统架构

![消息推送系统架构](http://ww1.sinaimg.cn/large/7ba68f52ly1g09ivq3s7pj20nw0djq49.jpg)

服务端对客户端暴露两个服务：
* 业务接口服务
* 消息推送服务

业务接口服务(`ActServer`)提供账号相关的API调用，包括注册、登录、退出接口。服务内部使用MySQL数据库存储用户的账号信息。

消息推送服务(`PushServer`)由**消息通道**以及**推送模块**两部分组成。消息通道分为自建通道(`gRPCChannle模块`)和系统推送通道。

gRPCChannle模块使用gRPC技术实现消息通道，对客户端提供通道创建接口，对PushServer提供消息下发接口（基于gRPC实现）。  
客户端进程启动时，会主动调用gRPCChannel模块的通道创建接口，并上报自己的设备号。gRCPChannel模块收到设备号后，会往Redis中登记通道信息，Key为客户端设备号deviceId，值为消息下发接口的gRPC服务地址，如192.168.56.101:50050。同时监控此通道的连接状态，当连接丢失时，从Redis中删除此通道信息。

PushServer为ActServer提供消息下发能力。  
为不阻塞ActServer的逻辑执行，ActServer与PushServer之间使用消息队列进行通讯。当ActServer需要给客户端推送消息时，会将客户端设备号以及待下发的消息打包成msg对象，并发布到队列中。PushServer会订阅此消息队列，从msg中解析出目标客户端的设备号。从Redis中检索此设备号是否有对应的gRPCChannel可用。如果有，则通过调用gPRCChannel提供的消息下发接口进行消息下发。如果下发失败或者当前无可用的gRPC通道可用，则会使用系统推送通道，借助终端厂商的消息推送能力进行消息下发。


## 系统时序
![系统时序图](http://ww1.sinaimg.cn/large/7ba68f52ly1g09iw46gcej216w1ckjt1.jpg)