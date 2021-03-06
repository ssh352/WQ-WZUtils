/***************************************************************************
Copyright(C) 2018, Wizard Quant
Author: luoqingming
Description: simple gtest for the module MemClient and MemServer
Date: 2018-04-02
***************************************************************************/

#include <bits/stdc++.h>
#include "wzmem_inc/memengine.hpp"
#include "wzpiper.hpp"
#include "logger.h"
#include "gtest/gtest.h"

#ifndef PRT
#define PRT(...) printf(__VA_ARGS__)
//#define PRT(...)
#endif

#ifndef DataType
#define DataType Frame
#endif

#ifndef QueueSize
#define QueueSize 1024
#endif

#ifndef ReaderSize
#define ReaderSize 4
#endif

Logger * logger;

char logger_buf[1024];

class ServerClientTest : public ::testing::Test{
protected:
	
	WZPiper<MemEngine<DataType, QueueSize, ReaderSize> >  * memServer;
	WZPiper<MemEngine<DataType, QueueSize, ReaderSize> >  * memClient1;
	WZPiper<MemEngine<DataType, QueueSize, ReaderSize> >  * memClient2;

	virtual void SetUp(){
		// init all
		char file[] = "../doc/config.ini";
		logger -> ParseConfigInfo(file);

		memServer = new WZPiper<MemEngine<DataType, QueueSize, ReaderSize> > ();
		memServer -> init(file, WZ_PIPER_SERVER, WZ_PIPER_NBLOCK);

		memClient1 = new WZPiper<MemEngine<DataType, QueueSize, ReaderSize> > ();
		memClient1 -> init(file, WZ_PIPER_CLIENT, WZ_PIPER_NBLOCK);

		memClient2 = new WZPiper<MemEngine<DataType, QueueSize, ReaderSize> > ();
		memClient2 -> init(file, WZ_PIPER_CLIENT, WZ_PIPER_NBLOCK);
	}
	virtual void TearDown(){
		delete memServer;
	}
};

TEST_F(ServerClientTest, Simple){

	// test write
	Frame sendFrame;
	sendFrame.source = 1;
	sendFrame.msg_type = 2;
	sendFrame.error_id = WZ_ERROR_ID_SUCCESS;
	sendFrame.rtn_type = 3;
	sendFrame.length = 4;
	EXPECT_EQ(0 ,memServer -> Send(sendFrame));
	EXPECT_EQ(0,memClient1 -> Send(sendFrame));
	EXPECT_EQ(0,memClient2 -> Send(sendFrame));

	// test queue receive
	Frame recvFrame;
	EXPECT_EQ(sizeof(Frame),memClient1 -> Recv(recvFrame));
	EXPECT_EQ(1,recvFrame.source);
	EXPECT_EQ(2,recvFrame.msg_type );
	EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
	EXPECT_EQ(3,recvFrame.rtn_type);
	EXPECT_EQ(4,recvFrame.length);
	EXPECT_EQ(-1,memClient1 -> Recv(recvFrame));

}

TEST_F(ServerClientTest, WriteAndReadWorks){
	// test write
	Frame sendFrame;
	for (int i = 0; i<QueueSize ; i++ ) {
		sendFrame.source = i;
		sendFrame.msg_type = i;
		sendFrame.error_id = WZ_ERROR_ID_SUCCESS;
		sendFrame.rtn_type = i;
		sendFrame.length = i;
		EXPECT_EQ(0 ,memServer -> Send(sendFrame));
		if(i<(QueueSize/2)) 	EXPECT_EQ(0,memClient1 -> Send(sendFrame));
		else 	EXPECT_EQ(0,memClient2 -> Send(sendFrame));
	}

	// test queue full
	EXPECT_EQ(-1,memServer -> Send(sendFrame));
	EXPECT_EQ(-1,memClient1 -> Send(sendFrame));
	EXPECT_EQ(-1,memClient2 -> Send(sendFrame));
	
	// test Reader1
	Frame recvFrame;

	for (int i = 0; i<QueueSize ; i++ ) {
		EXPECT_EQ(sizeof(Frame),memClient1 -> Recv(recvFrame));
		EXPECT_EQ(i,recvFrame.source);
		EXPECT_EQ(i,recvFrame.msg_type );
		EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
		EXPECT_EQ(i,recvFrame.rtn_type);
		EXPECT_EQ(i,recvFrame.length);


		EXPECT_EQ(sizeof(Frame),memServer -> Recv(recvFrame));
		EXPECT_EQ(i,recvFrame.source);
		EXPECT_EQ(i,recvFrame.msg_type );
		EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
		EXPECT_EQ(i,recvFrame.rtn_type);
		EXPECT_EQ(i,recvFrame.length);
	}
	
	// test catch Writer
	EXPECT_EQ(-1,memClient1 -> Recv(recvFrame));
	EXPECT_EQ(QueueSize - 1,recvFrame.source);
	EXPECT_EQ(QueueSize - 1,recvFrame.msg_type );
	EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
	EXPECT_EQ(QueueSize - 1,recvFrame.rtn_type);
	EXPECT_EQ(QueueSize - 1,recvFrame.length);
	EXPECT_EQ(-1,memServer -> Send(sendFrame));

	// test Reader2
	for (int i = 0; i<QueueSize ; i++ ) {
		EXPECT_EQ(sizeof(Frame),memClient2 -> Recv(recvFrame));
		EXPECT_EQ(i,recvFrame.source);
		EXPECT_EQ(i,recvFrame.msg_type );
		EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
		EXPECT_EQ(i,recvFrame.rtn_type);
		EXPECT_EQ(i,recvFrame.length);
	}

	// test catch Writer
	LOG(INFO) << "before";
	EXPECT_EQ(-1,memClient2 -> Recv(recvFrame));
	LOG(INFO) << "end";
	EXPECT_EQ(QueueSize - 1,recvFrame.source);
	EXPECT_EQ(QueueSize - 1,recvFrame.msg_type );
	EXPECT_EQ(WZ_ERROR_ID_SUCCESS,recvFrame.error_id);
	EXPECT_EQ(QueueSize - 1,recvFrame.rtn_type);
	EXPECT_EQ(QueueSize - 1,recvFrame.length);

	// test write
	EXPECT_EQ(0,memServer -> Send(sendFrame));

}

TEST_F(ServerClientTest, AddReaderDown){
	char file[] = "../doc/config.ini";
	delete memClient1;
	WZPiper<MemEngine<DataType, QueueSize, ReaderSize> >  * memClient3;
	memClient3 = new WZPiper<MemEngine<DataType, QueueSize, ReaderSize> > ();
	memClient3 -> init(file, WZ_PIPER_CLIENT, WZ_PIPER_NBLOCK);
	WZPiper<MemEngine<DataType, QueueSize, ReaderSize> >  * memClient4;
	memClient4 = new WZPiper<MemEngine<DataType, QueueSize, ReaderSize> > ();
	memClient4 -> init(file, WZ_PIPER_CLIENT, WZ_PIPER_NBLOCK);
}

TEST_F(ServerClientTest, Signal){
	while(1){}
}

int main(int argc, char* argv[]){
  logger = new Logger(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}