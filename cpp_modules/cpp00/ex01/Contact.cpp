#include "Contact.hpp"

void Contact::set(const std::string& fn,
                  const std::string& ln,
                  const std::string& nn,
                  const std::string& pn,
                  const std::string& ds)
{
    _firstName = fn;
    _lastName = ln;
    _nickname = nn;
    _phone = pn;
    _secret = ds;
}

const std::string& Contact::firstName() const   { return _firstName; }
const std::string& Contact::lastName()  const   { return _lastName; }
const std::string& Contact::nickname()  const   { return _nickname; }
const std::string& Contact::phone()     const   { return _phone; }
const std::string& Contact::secret()    const   { return _secret; }
