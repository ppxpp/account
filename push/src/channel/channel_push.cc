#include "channel/channel_push.h"
/**
 * 通过gRPC通道往客户端推消息
 */
Status ChannelPush::PushToClient(ServerContext* context, const push::NotifyWrapper* notifyWrapper, push::Ret* ret)
{
	string device = notifyWrapper->device();
	// 查找是否有对应的通道
	map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>*>::iterator iter = AsyncStreamMap.find(device);
	if (iter != AsyncStreamMap.end())
	{
		// 往通道写数据
		ServerAsyncReaderWriter<push::Notify, push::Cmd>* stream = iter->second;
		stream->Write(notifyWrapper->notify(), (void*)1);
		ret->set_err(0);
		ret->set_msg("push success");
	}
	else
	{
		ret->set_err(1);
		ret->set_msg(string("can not find grpc Stream for ") + device);
	}
	return Status::OK;
}