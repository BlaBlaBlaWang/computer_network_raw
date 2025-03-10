#ifndef GBN_RDT_SENDER_H
#define GBN_RDT_SENDER_H
#include "RdtSender.h"
using std::queue;

class GBNRdtSender :public RdtSender
{
private:
	int nextSequenceNumber;			// 下一个发送序号 
	bool waitingState;				// 是否处于等待Ack的状态
	static int windowSize;
	queue <Packet> packetWindow;	//已发送并等待Ack的数据包queue，根据窗口大小，一共维护4个实例的queue队列
	int base;						//记录发送窗口的当前序号

public:

	bool getWaitingState();
	bool send(const Message& message);						//发送应用层下来的Message，由NetworkServiceSimulator调用,如果发送方成功地将Message发送到网络层，返回true;如果因为发送方处于等待正确确认状态而拒绝发送Message，则返回false
	void receive(const Packet& ackPkt);						//接受确认Ack，将被NetworkServiceSimulator调用	
	void timeoutHandler(int seqNum);					//Timeout handler，将被NetworkServiceSimulator调用
	void printSlideWindow();

public:
	GBNRdtSender();
	virtual ~GBNRdtSender();
};

#endif