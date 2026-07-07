import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, ads7830

CODEOWNERS = ["@damib"]

ads7830_ns = cg.esphome_ns.namespace("ads7830")
Ads7830Channel = ads7830_ns.class_("Ads7830Channel", cg.PollingComponent)
Ads7830Sensor = ads7830_ns.class_("Sensor", sensor.Sensor, Ads7830Channel)

CONFIG_SCHEMA = (
    sensor.sensor_schema(Ads7830Sensor)
    .extend(ads7830.channel_schema())
)

async def to_code(config):
    var = await sensor.new_sensor(config)
    await ads7830.config_channel(config, var)
