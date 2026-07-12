import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, ads7830

CODEOWNERS = ["@damib"]

DEPENDENCIES = ["i2c"]
AUTO_LOAD = ["ads7830"]

from esphome.const import (
    CONF_ID,
    CONF_REFERENCE_VOLTAGE,
)

ads7830_ns = cg.esphome_ns.namespace("ads7830")
ads7828_ns = cg.esphome_ns.namespace("ads7828")
AD7828Component = ads7828_ns.class_(
    "Ads7828", ads7830.AD7830Component
)


CONFIG_SCHEMA = (
    cv.Schema({
        cv.GenerateID(): cv.declare_id(AD7828Component),
        cv.Optional(CONF_REFERENCE_VOLTAGE, default=0.0): cv.float_
    })
    .extend(i2c.i2c_device_schema(0x48))
    .extend(cv.COMPONENT_SCHEMA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    cg.add(var.set_external_reference_voltage(config[CONF_REFERENCE_VOLTAGE]))
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)
