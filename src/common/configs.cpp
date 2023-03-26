#include <stdlib.h>
#include <string.h>
#include "configs.h"
config_t configs;

void configsSetPortName(const char *portName) {
    configs._type = DIRECT;
    memset(configs.data.com.portName, 0, sizeof(configs.data.com.portName));
    strncpy(configs.data.com.portName, portName, strlen(portName));
}
void configsSetBaudrate(int b) {
    configs._type = DIRECT;
    configs.data.com.baudrate = b;
}
void configsSetUrl(const char *url) {

}

connect_type_t configsGetConnectType() {
    return configs._type;
}
