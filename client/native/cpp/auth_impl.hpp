#include "auth.hpp"
#include "auth_client.hpp"

namespace act {

class AuthImpl : public Auth  {
public:

	AuthImpl(const std::string & host);

    virtual AuthReply sign_up(const UserInfo & user) override;

    virtual AuthReply sign_in(const UserInfo & user) override;

    virtual AuthReply sign_out(const AuthInfo & auth) override;
	
	virtual int32_t update(const UserInfo & user) override;
private:
    AuthClient* mClient;
};

}  // namespace act
