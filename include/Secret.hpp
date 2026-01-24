#include <string>

class Secret {
public:
  virtual std::string encrypt() const = 0;
  virtual ~Secret() = default;
};
