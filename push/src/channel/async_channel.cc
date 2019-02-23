#include <iostream>
#include "channel/async_channel.h"
#include "channel/channel_push.h"

using namespace std;

AsyncRpcChannel::AsyncRpcChannel(RedisCache* cache, ServerBuilder* builder)
{
	this->mCache = cache;
	builder->RegisterService(&service_);
	cq_ = builder->AddCompletionQueue();
	server_ = builder->BuildAndStart();
	HandleRpcs();
}

AsyncRpcChannel::~AsyncRpcChannel() {
	std::cout << "Shutting down server...." << std::endl;
	server_->Shutdown();
	// Always shutdown the completion queue after the server.
	cq_->Shutdown();
}

void AsyncRpcChannel::HandleRpcs() {
	// Spawn a new CallData instance to serve new clients.
	new CallData(mCache, &service_, cq_.get());
	void* tag;  // uniquely identifies a request.
	bool ok;
	while (true) {
		// Block waiting to read the next event from the completion queue. The
		// event is uniquely identified by its tag, which in this case is the
		// memory address of a CallData instance.
		// The return value of Next should always be checked. This return value
		// tells us whether there is any kind of event or cq_ is shutting down.
		bool ret = cq_->Next(&tag, &ok);
		cout << "cq->next return " << ret << ", ok = " << ok << ", tag = " << tag << endl;
		if (ok && tag != (void*)1)
		{
			if (tag == (void*)1)
			{
				// write event, ignore
			}
			else 
			{
				static_cast<CallData*>(tag)->Proceed();
			}
		}
	}
}

AsyncRpcChannel::CallData::CallData(RedisCache* cache, push::PushChannel::AsyncService* service, ServerCompletionQueue* cq):
	cache_(cache), service_(service), cq_(cq), status_(CREATE)
{
	stream_.reset(new ServerAsyncReaderWriter<push::Notify, push::Cmd>(&ctx_));
	Proceed();
}

void AsyncRpcChannel::CallData::Proceed()
{
	bool canceled = ctx_.IsCancelled();
	//cout << "CallData::Proceed, status_ = " << status_ << ", canceled = " << canceled << ", CallData = " << this << endl;
	if (canceled)
	{
		status_ = FINISH;
	}
	if (status_ == CREATE) {
		cout << "CallData::Proceed, status_ = CREATE" << endl;
		status_ = CONNECT;
		service_->RequestConnect(&ctx_, stream_.get(), cq_, cq_, this);
		ctx_.AsyncNotifyWhenDone(this);
	}
	else if (status_ == CONNECT) {
		cout << "CallData::Proceed, status_ = CONNECT" << endl;
		new CallData(cache_, service_, cq_);
		status_ = PROCESS;
		stream_->Read(&cmd_, this);
	}
	else if (status_ == PROCESS)
	{
		cout << "CallData::Proceed, status_ = PROCESS" << endl;
		int type = cmd_.type();
		if (type == 1)
		{
			string device = cmd_.device();
			cout << "read cmd type = " << type << ", deivce = " << device << endl;
			this->device = device;
			AsyncStreamMap.erase(device);
			AsyncStreamMap.insert(pair<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>*>(device, stream_.get()));
			// 判断Cache中是否有device对应的writeStream
			string value = cache_->getValue(device);
			if (value.empty())
			{
				cout << "not found " << device << " in cache" << endl;
				cache_->setValue(device, gRPCAddress);
			}
			else
			{
				cout << "found " << device << " in cache, value is " << value << endl;
			}
		}
		else
		{
			cout << "read cmd from client, unknow type = " << type << endl;
		}
		stream_->Read(&cmd_, this);
	}
	else 
	{
		if (!device.empty())
		{
			// 删除缓存
			cout << "remove cache for  " << device << endl;
			AsyncStreamMap.erase(device);
			cache_->deleteKey(device);
		}
		cout << "CallData::Proceed, status_ = FINISH, delete " << this << endl;
		delete this;
	}
}

