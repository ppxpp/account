#include <iostream>
#include <thread>
#include <grpcpp/grpcpp.h>
#include "push.grpc.pb.h"
#include "push.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientAsyncReaderWriter;
using grpc::CompletionQueue;
using grpc::ClientWriter;
using grpc::Status;

using namespace std;

void syncRpc() 
{
	std::cout << "Push Client" << std::endl;
	std::unique_ptr<push::PushChannel::Stub> stub_ = push::PushChannel::NewStub(grpc::CreateChannel("192.168.56.101:50051",
		grpc::InsecureChannelCredentials()));

	ClientContext context;
	std::shared_ptr<ClientReaderWriter<::push::Cmd, ::push::Notify> > stream(stub_->Connect(&context));

	push::Cmd cmd;
	cmd.set_device("abcdefgh");
	cmd.set_type(1);
	stream->Write(cmd);
	cout << "write cmd to server" << endl;
	stream->WritesDone();

	push::Notify notify;
	cout << "prepare to read" << endl;
	while (stream->Read(&notify))
	{
		cout << "read success: " << notify.msg() << endl;
	}
	cout << "read finish" << endl;
}

class AsyncClient {

	enum class Type {
		READ = 1,
		WRITE = 2,
		CONNECT = 3,
		WRITES_DONE = 4,
		FINISH = 5
	};

public:
	AsyncClient() {
		stub_ = push::PushChannel::NewStub(grpc::CreateChannel("192.168.56.101:50050",
			grpc::InsecureChannelCredentials()));
		stream_ = stub_->AsyncConnect(&context_, &cq_, reinterpret_cast<void*>(Type::CONNECT));
		grpc_thread_.reset(new std::thread(std::bind(&AsyncClient::run, this)));
	}

	void run() {
		while (true) {
			void* got_tag;
			bool ok = false;
			// Block until the next result is available in the completion queue "cq".
			// The return value of Next should always be checked. This return value
			// tells us whether there is any kind of event or the cq_ is shutting
			// down.
			if (!cq_.Next(&got_tag, &ok)) {
				std::cerr << "Client stream closed. Quitting" << std::endl;
				break;
			}

			// It's important to process all tags even if the ok is false. One might
			// want to deallocate memory that has be reinterpret_cast'ed to void*
			// when the tag got initialized. For our example, we cast an int to a
			// void*, so we don't have extra memory management to take care of.
			if (ok) {
				std::cout << std::endl
					<< "**** Processing completion queue tag " << got_tag
					<< std::endl;
				switch (static_cast<Type>(reinterpret_cast<long>(got_tag))) {
				case Type::READ:
					std::cout << "Read a new message: " << notify_.msg() << std::endl;
					read();
					break;
				case Type::WRITE:
					std::cout << "Sending message (async)." << std::endl;
					//AsyncHelloRequestNextMessage();
					//write();
					read();
					break;
				case Type::CONNECT:
					std::cout << "Server connected." << std::endl;
					break;
				case Type::WRITES_DONE:
					std::cout << "Server disconnecting." << std::endl;
					break;
				case Type::FINISH:
					std::cout << "Client finish; status = "
						<< (finish_status_.ok() ? "ok" : "cancelled")
						<< std::endl;
					context_.TryCancel();
					cq_.Shutdown();
					break;
				default:
					std::cerr << "Unexpected tag " << got_tag << std::endl;
					GPR_ASSERT(false);
				}
			}
		}
	}

	void write() {
		push::Cmd cmd;
		cmd.set_type(1);
		cmd.set_device("6e5ffdbe7d896dc677eadca6e4ef3dc156df4604");

		std::cout << " ** Sending cmd" << std::endl;
		stream_->Write(cmd, reinterpret_cast<void*>(Type::WRITE));
	}

	void read() {
		std::cout << " ** read notify" << std::endl;
		stream_->Read(&notify_, reinterpret_cast<void*>(Type::READ));
	}
private:
	push::Notify notify_;

	std::unique_ptr<push::PushChannel::Stub> stub_;
	ClientContext context_;
	CompletionQueue cq_;
	std::unique_ptr<ClientAsyncReaderWriter<push::Cmd, push::Notify>> stream_;

	// Thread that notifies the gRPC completion queue tags.
	std::unique_ptr<std::thread> grpc_thread_;

	// Finish status when the client is done with the stream.
	grpc::Status finish_status_ = grpc::Status::OK;
};

int main(int argc, char const *argv[])
{
	AsyncClient client;
	string text;
	while (true) {
		std::cout << "Enter text (type quit to end): ";
		std::cin >> text;

		if (text == "write") {
			client.write();
		} else if (text == "read") {
			//client.read();
		}
	}
	return 0;
}