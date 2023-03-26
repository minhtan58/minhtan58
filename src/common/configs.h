#ifndef CONFIGS_H
#define CONFIGS_H
enum connect_type_t {
    DIRECT = 0,
    TCPIP = 1
};
typedef struct {
    connect_type_t _type;
    union {
        struct {
            char portName[6];
            int baudrate;
        } com;
        struct {
            char url[30];
        } ip;
    } data;
} config_t;

void configsSetPortName(const char *portName);
void configsSetBaudrate(int b);
void configsSetUrl(const char *url);
connect_type_t configsGetConnectType();
//extern config_t configs;
#endif // CONFIGS_H
