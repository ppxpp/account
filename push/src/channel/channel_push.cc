#include "channel/channel_push.h"
/**
 * ͨ��gRPCͨ�����ͻ�������Ϣ
 */
Status ChannelPush::PushToClient(ServerContext* context, const push::NotifyWrapper* notifyWrapper, push::Ret* ret)
{
	string device = notifyWrapper->device();
	// �����Ƿ��ж�Ӧ��ͨ��
	map<string, ServerAsyncReaderWriter<push::Notify, push::Cmd>*>::iterator iter = AsyncStreamMap.find(device);
	if (iter != AsyncStreamMap.end())
	{
		// ��ͨ��д����
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