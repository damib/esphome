import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor, ads7830

from esphome.const import (
    CONF_DEVICE,
    CONF_THRESHOLD,
    CONF_CHANNEL
)

AUTOLOAD = ['binary_sensor']

ads7830_ns = cg.esphome_ns.namespace("ads7830")
Ads7830Channel = ads7830_ns.class_("Ads7830Channel", cg.PollingComponent)
Ads7830BinarySensor = ads7830_ns.class_("BinarySensor", binary_sensor.BinarySensor, Ads7830Channel)

CONFIG_SCHEMA = (
    binary_sensor.binary_sensor_schema(Ads7830BinarySensor)
    .extend(ads7830.ADS7830_CHANNEL_SCHEMA)
    .extend({
        cv.Required(CONF_THRESHOLD): cv.int_
    })
)

async def to_code(config):
    var = await binary_sensor.new_binary_sensor(config)
    adc_instance = await cg.get_variable(config[CONF_DEVICE])
    cg.add(var.set_adc_instance(adc_instance, config[CONF_CHANNEL]))
    cg.add(var.set_threshold(config[CONF_THRESHOLD]))
    await cg.register_component(var, config)
