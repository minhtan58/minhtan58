#include <QtQml/qqmlprivate.h>
#include <QtCore/qdir.h>
#include <QtCore/qurl.h>

static const unsigned char qt_resource_tree[] = {
0,
0,0,0,0,2,0,0,0,1,0,0,0,1,0,0,0,
8,0,2,0,0,0,15,0,0,0,2,0,0,3,68,0,
0,0,0,0,1,0,0,0,0,0,0,0,108,0,0,0,
0,0,1,0,0,0,0,0,0,0,238,0,0,0,0,0,
1,0,0,0,0,0,0,0,20,0,0,0,0,0,1,0,
0,0,0,0,0,0,70,0,0,0,0,0,1,0,0,0,
0,0,0,1,112,0,2,0,0,0,13,0,0,0,17,0,
0,1,30,0,0,0,0,0,1,0,0,0,0,0,0,0,
42,0,0,0,0,0,1,0,0,0,0,0,0,0,184,0,
0,0,0,0,1,0,0,0,0,0,0,1,56,0,0,0,
0,0,1,0,0,0,0,0,0,0,164,0,0,0,0,0,
1,0,0,0,0,0,0,0,210,0,0,0,0,0,1,0,
0,0,0,0,0,1,8,0,0,0,0,0,1,0,0,0,
0,0,0,0,138,0,0,0,0,0,1,0,0,0,0,0,
0,1,82,0,0,0,0,0,1,0,0,0,0,0,0,2,
104,0,0,0,0,0,1,0,0,0,0,0,0,1,200,0,
0,0,0,0,1,0,0,0,0,0,0,1,166,0,0,0,
0,0,1,0,0,0,0,0,0,2,138,0,0,0,0,0,
1,0,0,0,0,0,0,2,16,0,0,0,0,0,1,0,
0,0,0,0,0,3,14,0,0,0,0,0,1,0,0,0,
0,0,0,2,50,0,0,0,0,0,1,0,0,0,0,0,
0,2,190,0,0,0,0,0,1,0,0,0,0,0,0,1,
138,0,0,0,0,0,1,0,0,0,0,0,0,2,228,0,
0,0,0,0,1,0,0,0,0,0,0,2,162,0,0,0,
0,0,1,0,0,0,0,0,0,2,78,0,0,0,0,0,
1,0,0,0,0,0,0,1,240,0,0,0,0,0,1,0,
0,0,0};
static const unsigned char qt_resource_names[] = {
0,
1,0,0,0,47,0,47,0,3,0,0,120,60,0,113,0,
109,0,108,0,8,5,230,90,92,0,108,0,111,0,103,0,
115,0,46,0,113,0,109,0,108,0,11,10,170,172,60,0,
100,0,105,0,103,0,105,0,116,0,97,0,108,0,46,0,
113,0,109,0,108,0,16,7,63,163,28,0,116,0,114,0,
97,0,110,0,115,0,109,0,105,0,115,0,115,0,105,0,
111,0,110,0,46,0,113,0,109,0,108,0,12,1,19,199,
188,0,111,0,118,0,101,0,114,0,118,0,105,0,101,0,
119,0,46,0,113,0,109,0,108,0,10,15,112,113,60,0,
115,0,101,0,114,0,105,0,97,0,108,0,46,0,113,0,
109,0,108,0,7,11,99,88,220,0,116,0,111,0,112,0,
46,0,113,0,109,0,108,0,10,10,179,57,124,0,115,0,
121,0,115,0,116,0,101,0,109,0,46,0,113,0,109,0,
108,0,11,11,133,71,92,0,118,0,105,0,114,0,116,0,
117,0,97,0,108,0,46,0,113,0,109,0,108,0,10,3,
87,97,60,0,97,0,110,0,97,0,108,0,111,0,103,0,
46,0,113,0,109,0,108,0,8,12,88,90,92,0,109,0,
101,0,110,0,117,0,46,0,113,0,109,0,108,0,10,10,
106,112,156,0,115,0,101,0,110,0,115,0,111,0,114,0,
46,0,113,0,109,0,108,0,10,11,85,125,92,0,98,0,
111,0,116,0,116,0,111,0,109,0,46,0,113,0,109,0,
108,0,12,15,189,51,188,0,99,0,101,0,108,0,108,0,
117,0,108,0,97,0,114,0,46,0,113,0,109,0,108,0,
10,7,110,9,51,0,67,0,111,0,109,0,112,0,111,0,
110,0,101,0,110,0,116,0,115,0,11,9,145,132,220,0,
77,0,121,0,84,0,97,0,98,0,108,0,101,0,46,0,
113,0,109,0,108,0,14,5,79,217,252,0,77,0,121,0,
76,0,111,0,103,0,84,0,97,0,98,0,108,0,101,0,
46,0,113,0,109,0,108,0,17,3,187,7,220,0,77,0,
121,0,83,0,101,0,110,0,115,0,111,0,114,0,84,0,
97,0,98,0,108,0,101,0,46,0,113,0,109,0,108,0,
13,14,167,156,252,0,67,0,111,0,108,0,111,0,114,0,
73,0,99,0,111,0,110,0,46,0,113,0,109,0,108,0,
14,6,94,180,124,0,77,0,121,0,84,0,101,0,120,0,
116,0,69,0,100,0,105,0,116,0,46,0,113,0,109,0,
108,0,11,8,22,148,220,0,77,0,121,0,76,0,97,0,
98,0,101,0,108,0,46,0,113,0,109,0,108,0,10,12,
253,205,124,0,77,0,121,0,84,0,101,0,120,0,116,0,
46,0,113,0,109,0,108,0,14,2,39,51,124,0,77,0,
121,0,67,0,111,0,109,0,98,0,111,0,66,0,111,0,
120,0,46,0,113,0,109,0,108,0,9,5,135,105,115,0,
71,0,108,0,111,0,98,0,97,0,108,0,46,0,106,0,
115,0,11,12,195,159,124,0,67,0,111,0,110,0,116,0,
101,0,110,0,116,0,46,0,113,0,109,0,108,0,16,9,
116,129,92,0,66,0,111,0,114,0,100,0,101,0,114,0,
101,0,100,0,84,0,101,0,120,0,116,0,46,0,113,0,
109,0,108,0,18,12,118,121,156,0,67,0,117,0,115,0,
116,0,111,0,109,0,77,0,101,0,110,0,117,0,73,0,
116,0,101,0,109,0,46,0,113,0,109,0,108,0,24,6,
222,66,92,0,77,0,121,0,86,0,105,0,114,0,116,0,
117,0,97,0,108,0,83,0,101,0,110,0,115,0,111,0,
114,0,84,0,97,0,98,0,108,0,101,0,46,0,113,0,
109,0,108,0,11,0,190,135,92,0,115,0,111,0,114,0,
116,0,105,0,110,0,103,0,46,0,113,0,109,0,108};
static const unsigned char qt_resource_empty_payout[] = { 0, 0, 0, 0, 0 };
QT_BEGIN_NAMESPACE
extern Q_CORE_EXPORT bool qRegisterResourceData(int, const unsigned char *, const unsigned char *, const unsigned char *);
QT_END_NAMESPACE
namespace QmlCacheGeneratedCode {
namespace _qml_sorting_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyVirtualSensorTable_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_cellular_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_bottom_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_CustomMenuItem_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_sensor_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_BorderedText_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_Content_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_Global_js { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyComboBox_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_menu_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyText_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_analog_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyLabel_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyTextEdit_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_virtual_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_system_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_ColorIcon_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MySensorTable_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyLogTable_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_top_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_serial_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_Components_MyTable_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_overview_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_transmission_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_digital_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}
namespace _qml_logs_qml { 
    extern const unsigned char qmlData[];
    const QQmlPrivate::CachedQmlUnit unit = {
        reinterpret_cast<const QV4::CompiledData::Unit*>(&qmlData), nullptr, nullptr
    };
}

}
namespace {
struct Registry {
    Registry();
    ~Registry();
    QHash<QString, const QQmlPrivate::CachedQmlUnit*> resourcePathToCachedUnit;
    static const QQmlPrivate::CachedQmlUnit *lookupCachedUnit(const QUrl &url);
};

Q_GLOBAL_STATIC(Registry, unitRegistry)


Registry::Registry() {
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/sorting.qml"), &QmlCacheGeneratedCode::_qml_sorting_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyVirtualSensorTable.qml"), &QmlCacheGeneratedCode::_qml_Components_MyVirtualSensorTable_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/cellular.qml"), &QmlCacheGeneratedCode::_qml_cellular_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/bottom.qml"), &QmlCacheGeneratedCode::_qml_bottom_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/CustomMenuItem.qml"), &QmlCacheGeneratedCode::_qml_Components_CustomMenuItem_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/sensor.qml"), &QmlCacheGeneratedCode::_qml_sensor_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/BorderedText.qml"), &QmlCacheGeneratedCode::_qml_Components_BorderedText_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/Content.qml"), &QmlCacheGeneratedCode::_qml_Components_Content_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/Global.js"), &QmlCacheGeneratedCode::_qml_Components_Global_js::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyComboBox.qml"), &QmlCacheGeneratedCode::_qml_Components_MyComboBox_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/menu.qml"), &QmlCacheGeneratedCode::_qml_menu_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyText.qml"), &QmlCacheGeneratedCode::_qml_Components_MyText_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/analog.qml"), &QmlCacheGeneratedCode::_qml_analog_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyLabel.qml"), &QmlCacheGeneratedCode::_qml_Components_MyLabel_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyTextEdit.qml"), &QmlCacheGeneratedCode::_qml_Components_MyTextEdit_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/virtual.qml"), &QmlCacheGeneratedCode::_qml_virtual_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/system.qml"), &QmlCacheGeneratedCode::_qml_system_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/ColorIcon.qml"), &QmlCacheGeneratedCode::_qml_Components_ColorIcon_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MySensorTable.qml"), &QmlCacheGeneratedCode::_qml_Components_MySensorTable_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyLogTable.qml"), &QmlCacheGeneratedCode::_qml_Components_MyLogTable_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/top.qml"), &QmlCacheGeneratedCode::_qml_top_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/serial.qml"), &QmlCacheGeneratedCode::_qml_serial_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/Components/MyTable.qml"), &QmlCacheGeneratedCode::_qml_Components_MyTable_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/overview.qml"), &QmlCacheGeneratedCode::_qml_overview_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/transmission.qml"), &QmlCacheGeneratedCode::_qml_transmission_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/digital.qml"), &QmlCacheGeneratedCode::_qml_digital_qml::unit);
        resourcePathToCachedUnit.insert(QStringLiteral("/qml/logs.qml"), &QmlCacheGeneratedCode::_qml_logs_qml::unit);
    QQmlPrivate::RegisterQmlUnitCacheHook registration;
    registration.version = 0;
    registration.lookupCachedQmlUnit = &lookupCachedUnit;
    QQmlPrivate::qmlregister(QQmlPrivate::QmlUnitCacheHookRegistration, &registration);
QT_PREPEND_NAMESPACE(qRegisterResourceData)(/*version*/0x01, qt_resource_tree, qt_resource_names, qt_resource_empty_payout);
}

Registry::~Registry() {
    QQmlPrivate::qmlunregister(QQmlPrivate::QmlUnitCacheHookRegistration, quintptr(&lookupCachedUnit));
}

const QQmlPrivate::CachedQmlUnit *Registry::lookupCachedUnit(const QUrl &url) {
    if (url.scheme() != QLatin1String("qrc"))
        return nullptr;
    QString resourcePath = QDir::cleanPath(url.path());
    if (resourcePath.isEmpty())
        return nullptr;
    if (!resourcePath.startsWith(QLatin1Char('/')))
        resourcePath.prepend(QLatin1Char('/'));
    return unitRegistry()->resourcePathToCachedUnit.value(resourcePath, nullptr);
}
}
int QT_MANGLE_NAMESPACE(qInitResources_resources)() {
    ::unitRegistry();
    Q_INIT_RESOURCE(res_resources_qmlcache);
    return 1;
}
Q_CONSTRUCTOR_FUNCTION(QT_MANGLE_NAMESPACE(qInitResources_resources))
int QT_MANGLE_NAMESPACE(qCleanupResources_resources)() {
    Q_CLEANUP_RESOURCE(res_resources_qmlcache);
    return 1;
}
