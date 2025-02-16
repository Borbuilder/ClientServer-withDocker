#include "../httplib/httplib.h"

#include <string>

bool try_connect(httplib::Client& client, const std::string& input);
void attempt_reconnect(int delay);