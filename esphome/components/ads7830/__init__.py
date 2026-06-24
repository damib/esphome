import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_CHANNEL,
    CONF_DEVICE,
    CONF_ID,
    CONF_REFERENCE_VOLTAGE,
)

CONF_DIFFERENTIAL_MODE = 'differential_mode'
CONF_USE_EXTERNAL_REFERENCE = 'use_external_reference'

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["voltage_sampler"]


ads7830_ns = cg.esphome_ns.namespace("ads7830")
AD7830Component = ads7830_ns.class_(
    "Ads7830", i2c.I2CDevice, cg.PollingComponent
)

CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(AD7830Component),
        cv.Optional(CONF_REFERENCE_VOLTAGE, default=0.0): cv.float_
    })
    .extend(i2c.i2c_device_schema(0x48))
    .extend(cv.polling_component_schema("1s"))
)

def channel_schema() -> cv.Schema:
    return cv.Schema({
        cv.Required(CONF_DEVICE): cv.use_id(AD7830Component),
        cv.Required(CONF_CHANNEL): cv.int_range(0,7),
        cv.Optional(CONF_DIFFERENTIAL_MODE, default=False): cv.boolean,
        cv.Optional(CONF_USE_EXTERNAL_REFERENCE, default=False): cv.boolean,
    }).extend(cv.polling_component_schema("1s"))

async def config_channel(config, var):
    adc_instance = await cg.get_variable(config[CONF_DEVICE])
    cg.add(var.set_differential_mode(config[CONF_DIFFERENTIAL_MODE]))
    cg.add(var.set_adc_instance(adc_instance, config[CONF_CHANNEL]))
    cg.add(var.set_use_internal_reference(not config[CONF_USE_EXTERNAL_REFERENCE]))
    await cg.register_component(var, config)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_external_reference_voltage(config[CONF_REFERENCE_VOLTAGE]))
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)
