import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, ads7830

from esphome.const import (
    CONF_DEVICE,
    CONF_CHANNEL
)


AUTO_LOAD = ["voltage_sampler"]

ads7830_ns = cg.esphome_ns.namespace("ads7830")
Ads7830Channel = ads7830_ns.class_("Ads7830Channel", cg.PollingComponent)
Ads7830Sensor = ads7830_ns.class_("Sensor", sensor.Sensor, Ads7830Channel)

CONFIG_SCHEMA = (
    sensor.sensor_schema(Ads7830Sensor)
    .extend(ads7830.ADS7830_CHANNEL_SCHEMA)
)

async def to_code(config):
    var = await sensor.new_sensor(config)
    adc_instance = await cg.get_variable(config[CONF_DEVICE])
    cg.add(var.set_adc_instance(adc_instance, config[CONF_CHANNEL]))
    await cg.register_component(var, config)
