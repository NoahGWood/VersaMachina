#pragma once
#include "common/Base.h"
namespace VM
{
    using NodeId = uint32_t;
    using SlotId = uint32_t;
    using WireId = uint32_t;
    using ModuleId = uint32_t;

    enum class PortKind {
        Power,
        Ground,
        CAN,
        LIN,
        Lamp,
        IO,
        PWM,
        Sensor,
        RF,
        MILCAN,
        BUS_1553,
        J1708,
        J1939,
        Power28V,
        Power48V,
        GNSS,
        TimeSync,
        PPS,
        FireControl,
        TurretCtrl,
        LauncherCtrl,
        EWControl,
        EW_RFIn,
        EW_RFOut,
        Ethernet_Tac,
        CryptoKeyFill,
        IntercomAudio,
        HeadsetAudio,
        HardenedIO,
        EMPProtectedIO,
        Unknown
    };

    enum class PortDir{
        Input,
        Output,
        Bidirectional,
        TriState,
        Passive,
        PowerIn,
        PowerOut,
        OpenCollector,
        OpenEmitter,
        Unspecified,
        NC
    };

    enum class SignalType {
        Bool,
        Float,
        Int,
        Voltage,
        Current,
        FrameCAN,
        FrameLIN,
        FrameMILCAN,
        Frame1553,
        RFSignal,
        GNSS_Location,
        GNSS_Time,
        FireCommand,
        WeaponStatus,
        CryptoKeyLoad,
        CryptoKeyStatus,
        AudioFrame,
        PTTState,
        Unknown
    };

    struct PortSpec {
        std::string id;
        std::string name;
        PortKind kind;
        PortDir direction;
        std::unordered_map<std::string, std::string> tags;
    };

    struct SignalSpec {
        std::string id;
        SignalType type;
        std::string portId;
        bool isProvided;
    };

    struct BlockSpec {
        std::string id;
        std::string name;
        std::string version;
        std::vector<PortSpec> ports;
        std::vector<SignalSpec> signals;
        std::unordered_map<std::string, std::string> tags; // domain, safety, ...
    };

    struct BlockSpecRegistry {
        // Key: BlockSpec::id
        std::unordered_map<std::string, BlockSpec> blocks;        
    };

    struct Port {
        std::string id;
        std::string name;
        std::string kind;
        PortDir dir;
    };

    struct BlockPrefab{
        std::string id;
        std::string label;
        std::vector<Port> ports;
    };
} // namespace VM
