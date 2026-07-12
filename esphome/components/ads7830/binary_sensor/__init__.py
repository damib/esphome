import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, ads7830

CODEOWNERS = ["@damib"]

DEPENDENCIES = ["ads7830"]

from esphome.const import (
    CONF_INVERTED,
    CONF_THRESHOLD,
)

ads7830_ns = cg.esphome_ns.namespace("ads7830")
Ads7830Channel = ads7830_ns.class_("Ads7830Channel", cg.PollingComponent)
Ads7830BinarySensor = ads7830_ns.class_("BinarySensor", binary_sensor.BinarySensor, Ads7830Channel)

CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(Ads7830BinarySensor)
    .extend(ads7830.channel_schema())
    .extend({
        cv.Required(CONF_THRESHOLD): cv.float_,
        cv.Optional(CONF_INVERTED, default=False): cv.boolean,
    })
)

async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    cg.add(var.set_threshold(config[CONF_THRESHOLD]))
    cg.add(var.set_inverted(config[CONF_INVERTED]))
    await ads7830.config_channel(config, var)