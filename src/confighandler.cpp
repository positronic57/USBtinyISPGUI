#include "confighandler.h"

#include <QFileInfo>
#include <QVector>
#include <QVariant>

int ConfigHandler::read_mcu_fuse_bits(const QString &mcu_model, const pugi::xml_node &fuse_node, struct Fuses &mcu_fuse)
{
    int status = 0;
    char bit_name[5] = "bit0";

    mcu_fuse.fuse_bits.clear();

    // Get fuse default value and names of the bits
    mcu_fuse.value = QString(fuse_node.attribute("defaultValue").value()).toInt(nullptr, 0);
    for(int bit = 0; bit < 8; bit++) {
        if (!fuse_node.child(bit_name)) {
            last_error.code = ERROR_CODES::ERROR_DEF_OF_FUSE_BIT_MISSING;
            last_error.message = QString(error_msg[static_cast<int>(last_error.code)])
                    .arg(fuse_node.name(), bit_name, mcu_model);
            status = -1;
            return status;
        }
        mcu_fuse.fuse_bits << QString(fuse_node.child_value(bit_name));
        bit_name[3] = bit_name[3] + 1;
    }

    return 0;
}

ConfigHandler::~ConfigHandler()
{
    if ((changes_are_made) && (QFileInfo(file_name).isWritable())) {
        config_xml.save_file(file_name.toStdString().c_str());
    }
}

int ConfigHandler::load_config(const QString &fn)
{
    last_error.clear();

    if ((changes_are_made) && (file_name != fn)) {
        config_xml.save_file(file_name.toStdString().c_str());
    }

    file_name = fn;
    changes_are_made = false;

    pugi::xml_parse_result load_result = config_xml.load_file(file_name.toStdString().c_str(), pugi::parse_default | pugi::parse_comments);

    if (load_result) {
        config_loaded = true;
        return 0;
    }

    config_loaded = false;
    last_error.code = ERROR_CODES::ERROR_LOAD_XML_FILE;
    last_error.message = QString(error_msg[static_cast<int>(last_error.code)])
                .arg(file_name, load_result.description());

    emit signalConfigHandlerError(last_error);

    return -1;
}

int ConfigHandler::load_config()
{
    return load_config(m_default_config_name);
}

int ConfigHandler::get_general_config(AvrdudeConfig &avrdude_config, BurnerConfig &burner_config)
{
    int status = -1;

    last_error.clear();

    if (!config_loaded) {
        return status;
    }

    status = 0;
    pugi::xpath_node config_node = config_xml.select_node("//config");
    if (config_node)
    {
        QStringList child_nodes = {
            "avrdudeExec",
            "avrdudeConf",
            "eraseBefore",
            "verifyAfter"
        };
        pugi::xml_node child_node;
        QVector<QVariant> config_values;
        for(int child = 0; child < child_nodes.count(); child++)
        {
            child_node = config_node.node().child(child_nodes.at(child).toStdString().c_str());
            if (child_node) {
                config_values.push_back(QVariant(child_node.text().as_string()));
            }
            else {
                last_error.code = ERROR_CODES::ERROR_CONFIG_ENTRY_NOT_FOUND;
                last_error.message = QString(error_msg[static_cast<int>(last_error.code)])
                        .arg(child_nodes.at(child));
                status = -1;
                break;
            }
        }

        if (status == 0) {
            avrdude_config.binary = config_values[0].toString();
            avrdude_config.config_file = config_values[1].toString();
            burner_config.errase_flash_before_burn = config_values[2].toBool();
            burner_config.verify_after_burn = config_values[3].toBool();
        }
    }
    else
    {
        last_error.code = ERROR_CODES::ERROR_CONFIG_SECTION_NOT_FOUND,
        last_error.message = error_msg[static_cast<int>(last_error.code)];
        status = -1;
    }

    if (status) {
        emit signalConfigHandlerError(last_error);
    }

    return status;
}

int ConfigHandler::write_general_config(const AvrdudeConfig &avrdude_config, const BurnerConfig &burner_config)
{
    int status = 0;

    last_error.clear();

    if (!config_loaded) {
        return status;
    }

    pugi::xpath_node config_node = config_xml.select_node("//config");

    if (config_node)
    {
        config_node.node().child("avrdudeExec").text().set(avrdude_config.binary.toStdString().c_str());
        config_node.node().child("avrdudeConf").text().set(avrdude_config.config_file.toStdString().c_str());
        config_node.node().child("eraseBefore").text().set(burner_config.errase_flash_before_burn ? "1" : "0");
        config_node.node().child("verifyAfter").text().set(burner_config.verify_after_burn ? "1" : "0");
        changes_are_made = true;
    }
    else
    {
        last_error.code = ERROR_CODES::ERROR_CONFIG_SECTION_NOT_FOUND;
        last_error.message = error_msg[static_cast<int>(last_error.code)];
        emit signalConfigHandlerError(last_error);
        status = -1;
    }

    return status;
}


int ConfigHandler::get_mcus_definitions(QVector<struct ConfigHandler::MCU> &devices)
{
    int status = -1;

    last_error.clear();

    if (!config_loaded) {
        return status;
    }

    pugi::xpath_node_set mcus = config_xml.select_nodes("//AVRDevice");

    if (mcus.empty()) {
        last_error.code = ERROR_CODES::ERROR_NO_AVR8_DEVICES_FOUND;
        last_error.message = error_msg[static_cast<int>(last_error.code)];
        return status;
    }

    status = 0;
    devices.clear();
    struct MCU mcu;

    pugi::xml_node fuse;
    for (pugi::xpath_node_set::const_iterator it = mcus.begin(); it != mcus.end(); ++it)
    {
        pugi::xpath_node mcu_node = *it;

        // Get device name
        mcu.model = QString(mcu_node.node().attribute("id").value());

        // Get the flag for on-chip EEPROM
        mcu.has_eeprom = mcu_node.node().child("EEPROM").text().as_bool();

        // Get the default value of HFUSE and the names of all bits from HFUSE childen
        fuse = mcu_node.node().child("HFUSE");
        status = read_mcu_fuse_bits(mcu.model, fuse, mcu.hfuses);
        if (status)
        {
            emit signalConfigHandlerError(last_error);
            return status;
        }

        // Get the default value of LFUSE and the names of all bits from LFUSE childen
        fuse = mcu_node.node().child("LFUSE");
        status = read_mcu_fuse_bits(mcu.model, fuse, mcu.lfuses);
        if (status)
        {
            emit signalConfigHandlerError(last_error);
            return status;
        }

        devices.push_back(mcu);
    }

    return status;
}

int ConfigHandler::get_burners(QList<Burner> &burners)
{
    int status = -1;

    last_error.clear();

    if (!config_loaded) {
        return status;
    }

    pugi::xpath_node_set burners_defs = config_xml.select_nodes("//burners/burner");

    if (burners_defs.empty()) {
        last_error.code = ERROR_CODES::ERROR_NO_BURNERS_FOUND;
        last_error.message = error_msg[static_cast<int>(last_error.code)];
        return status;
    }

    status = 0;
    burners.clear();
    struct Burner burner;

    for (pugi::xpath_node_set::const_iterator it = burners_defs.begin(); it != burners_defs.end(); ++it)
    {
        pugi::xpath_node burner_def = *it;

        // Get model name
        burner.device = QString(burner_def.node().attribute("model").value());

        // Get avrdude name for the device
        burner.avrdude_name = burner_def.node().attribute("avrdude_name").value();

        QString vendor_id(burner_def.node().attribute("usb_vendor_id").value());
        QString product_id(burner_def.node().attribute("usb_product_id").value());
        bool valid = false;
        burner.usb_vendor_id = static_cast<unsigned short>(vendor_id.toInt(&valid, 0));
        burner.usb_product_id = static_cast<unsigned short>(product_id.toInt(&valid, 0));

        burner.avrdude_name = burner_def.node().attribute("avrdude_name").value();

        burners.append(burner);
    }

    return status;
}

ConfigHandler::MCU::MCU(const QString &mcu_model, bool eeprom, const struct Fuses &mcu_hfuses, const struct Fuses &mcu_lfuses)
{
    model = mcu_model;
    has_eeprom = eeprom;
    hfuses = mcu_hfuses;
    lfuses = mcu_lfuses;
}

ConfigHandler::AvrdudeConfig::AvrdudeConfig(const QString &bin, const QString &conf)
{
    binary = bin;
    config_file = conf;
}

ConfigHandler::BurnerConfig::BurnerConfig(bool errase_flash, bool verify, const ConfigHandler::Burner &brn)
{
    errase_flash_before_burn = errase_flash;
    verify_after_burn = verify;
    burner = brn;
}

bool ConfigHandler::config_file_exists(const QString &config_file)
{
    return QFileInfo::exists(config_file);
}

bool ConfigHandler::is_config_file_readable(const QString &config_file)
{
    return QFileInfo(config_file).isReadable();
}

bool ConfigHandler::is_config_file_writable(const QString &config_file)
{
    return QFileInfo(config_file).isWritable();
}

ConfigHandler::error::error(ERROR_CODES c, const QString &m)
{
    code = c;
    message = m;
}

void ConfigHandler::error::clear()
{
    code = ERROR_CODES::NO_ERROR;
    message.clear();
}

ConfigHandler::Burner::Burner(const QString &dev, const QString &dude_name, unsigned short vendor_id, unsigned short product_id)
{
    device = dev;
    avrdude_name = dude_name;
    usb_vendor_id = vendor_id;
    usb_product_id = product_id;
}
