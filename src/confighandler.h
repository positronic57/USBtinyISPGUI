#ifndef CONFIGHANDLER_H
#define CONFIGHANDLER_H

#include <QString>
#include <QStringList>
#include <QObject>

#include <bitset>

#include "pugixml.hpp"

class ConfigHandler: public QObject
{
    Q_OBJECT

public:
    enum class ERROR_CODES:int {
       NO_ERROR = 0,
       ERROR_LOAD_XML_FILE,
       ERROR_CONFIGURATION_NOT_LOADED,
       ERROR_CONFIG_SECTION_NOT_FOUND,
       ERROR_CONFIG_ENTRY_NOT_FOUND,
       ERROR_CONFIG_ENTRY_UPDATE_FAILED,
       ERROR_NO_AVR8_DEVICES_FOUND,
       ERROR_DEF_OF_FUSE_BIT_MISSING,
       ERROR_NO_BURNERS_FOUND
    };

    struct AvrdudeConfig {
        QString binary = "/usr/bin/avrdude";
        QString config_file = "/etc/avrdude.conf";
        AvrdudeConfig() = default;
        explicit AvrdudeConfig(const QString &bin, const QString &conf);
    };

    struct Burner {
        QString device = "USBtinyISP";
        QString avrdude_name = "usbtiny";
        unsigned short usb_vendor_id = 0x1781;
        unsigned short usb_product_id = 0x0C9F;
        Burner() = default;
        explicit Burner(const QString &dev, const QString &dude_name, unsigned short vendor_id, unsigned short product_id);
    };

    struct BurnerConfig {
        bool errase_flash_before_burn = true;
        bool verify_after_burn = false;
        Burner burner;
        BurnerConfig() = default;
        explicit BurnerConfig(bool errase_flash, bool verify, const ConfigHandler::Burner &brn);
    };

    struct Fuses {
        std::bitset<8> value = 0x00;    // Default value of FUSE byte
        QStringList fuse_bits;
        Fuses() = default;
    };

    struct MCU {
        QString model;
        bool has_eeprom = false;
        struct Fuses hfuses;
        struct Fuses lfuses;
        MCU() = default;
        explicit MCU(const QString &mcu_model, bool eeprom, const struct Fuses &mcu_hfuses, const struct Fuses &mcu_lfuses);
    };

    struct error {
        ERROR_CODES code = ERROR_CODES::NO_ERROR;
        QString message;
        error() = default;
        explicit error(ERROR_CODES c, const QString &m);
        void clear();
    };

private:
    pugi::xml_document config_xml;
    QString file_name;
    const QString m_default_config_name = "./config/USBtinyISPGUIConfigFile.xml";
    bool changes_are_made = false;
    bool config_loaded = false;

    const QStringList error_msg = {
        "No error",
        "Loading of XML %1 failed with error:\n%2",
        "Configuration not loaded",
        "Section/node \"config\" not found in XML file",
        "Config entry \"%1\" not found in XML file",
        "Update of config entry \"%1\" failed",
        "No AVR8 MCUs defined in configuration file",
        "%1 %2 for %3 missing in configuration file",
        "Programmer device(s) missing in configuration file"
    };

    int read_mcu_fuse_bits(const QString &mcu_model, const pugi::xml_node &fuse_node, struct Fuses &mcu_fuse);


public:
    ConfigHandler(QObject *parent = nullptr): QObject(parent) {};
    ~ConfigHandler();

    error last_error;
    int load_config(const QString &file_name);
    int load_config();
    int get_general_config(ConfigHandler::AvrdudeConfig &avrdude_config, ConfigHandler::BurnerConfig &burner_config);
    int write_general_config(const ConfigHandler::AvrdudeConfig &avrdude_config, const ConfigHandler::BurnerConfig &burner_config);
    int get_mcus_definitions(QVector<struct ConfigHandler::MCU> &devices);
    int get_burners(QList<struct ConfigHandler::Burner> &burners);

    static bool config_file_exists(const QString &config_file);
    static bool is_config_file_readable(const QString &config_file);
    static bool is_config_file_writable(const QString &config_file);

signals:
    void signalConfigHandlerError(ConfigHandler::error);
};

#endif // CONFIGHANDLER_H
