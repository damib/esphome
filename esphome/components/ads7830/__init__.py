import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c
from esphome.const import (
    CONF_ID,
    CONF_DEVICE,
    CONF_CHANNEL
)

DEPENDENCIES = ["i2c"]

ads7830_ns = cg.esphome_ns.namespace("ads7830")
AD7830Component = ads7830_ns.class_(
    "Ads7830", i2c.I2CDevice, cg.PollingComponent
)

CONFIG_SCHEMA = (
    cv.Schema(
        {
            cv.GenerateID(): cv.declare_id(AD7830Component),
        }
    )
    .extend(i2c.i2c_device_schema(0x48))
    .extend(cv.polling_component_schema("1s"))
)

ADS7830_CHANNEL_SCHEMA = cv.Schema(
    {
        cv.Required(CONF_DEVICE): cv.use_id(AD7830Component),
        cv.Required(CONF_CHANNEL): cv.int_range(0,7),
    }
).extend(cv.polling_component_schema("1s"))


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await i2c.register_i2c_device(var, config)
    await cg.register_component(var, config)
