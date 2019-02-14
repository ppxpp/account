#include "push.hpp"
#include "push_listener.hpp"
#include <grpcpp/grpcpp.h>
#include <android/log.h> 

#include "push.pb.h"
#include "push.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientAsyncReaderWriter;
using grpc::CompletionQueue;
using grpc::ClientWriter;
using grpc::Status;

#define  LOG_TAG    "push.cpp"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


namespace act {

	class PushImpl : public Push {
		enum class Type {
			READ = 1,
			WRITE = 2,
			CONNECT = 3
		};

	public:
		PushImpl(const std::string & host, const std::string & device, const std::shared_ptr<PushListener> & listener) {
			this->host = host;
			this->deivce = device;
			this->listener = listener;
		}

		void connect() {
			stub_ = push::PushChannel::NewStub(grpc::CreateChannel(host, grpc::InsecureChannelCredentials()));
			stream_ = stub_->AsyncConnect(&context_, &cq_, reinterpret_cast<void*>(Type::CONNECT));
			run();
		}

		void write() {
			push::Cmd cmd;
			cmd.set_type(1);
			cmd.set_device(deivce);
			LOGI(" ** Sending cmd");
			stream_->Write(cmd, reinterpret_cast<void*>(Type::WRITE));
		}

		void read() {
			LOGI(" ** read notify");
			stream_->Read(&notify_, reinterpret_cast<void*>(Type::READ));
		}

		void run() {
			while (true) {
				void* got_tag;
				bool ok = false;
				LOGI("before next");
				if (!cq_.Next(&got_tag, &ok)) {
					LOGI("quitting");
					break;
				}
				if (ok) {
					switch (static_cast<Type>(reinterpret_cast<long>(got_tag))) {
						case Type::READ:
							LOGI("Read a new message");
							this->listener->onNotify(notify_.msg());
							read();
							break;
						case Type::WRITE:
							LOGI("write msg to server done.");
							read();
							break;
						case Type::CONNECT:
							LOGI("Server connected.");
							write();
							break;
						default:
							LOGI("Unexpected tag");
					}
				}
				else 
				{
					LOGI("next not ok");
				}
			}
			LOGI("thread exit");
		}
	private:
		std::string host;
		std::string deivce; 
		std::shared_ptr<PushListener> listener;

		push::Notify notify_;
		std::unique_ptr<push::PushChannel::Stub> stub_;
		ClientContext context_;
		CompletionQueue cq_;
		std::unique_ptr<ClientAsyncReaderWriter<push::Cmd, push::Notify>> stream_;
		grpc::Status finish_status_ = grpc::Status::OK;
	};

	std::shared_ptr<act::Push> act::Push::create(const std::string & host, const std::string & device, const std::shared_ptr<PushListener> & listener)
	{
		return std::make_shared<PushImpl>(host, device, listener);
	}

}  // namespace act