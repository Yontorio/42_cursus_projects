#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
public:
    void set(const std::string& fn,
             const std::string& ln,
             const std::string& nn,
             const std::string& pn,
             const std::string& ds);

    const std::string& firstName() const;
    const std::string& lastName() const;
    const std::string& nickname() const;
    const std::string& phone() const;
    const std::string& secret() const;

private:
    std::string _firstName;
    std::string _lastName;
    std::string _nickname;
    std::string _phone;
    std::string _secret;
};

#endif
