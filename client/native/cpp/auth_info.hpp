// AUTOGENERATED FILE - DO NOT MODIFY!
// This file generated by Djinni from auth.djinni

#pragma once

#include <string>
#include <utility>

namespace act {

struct AuthInfo final {
    std::string token;

    AuthInfo(std::string token_)
    : token(std::move(token_))
    {}
};

}  // namespace act