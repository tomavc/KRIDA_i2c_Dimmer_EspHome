import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import i2c, light
from esphome.const import CONF_OUTPUT_ID

DEPENDENCIES = ['i2c']

CONF_CHANNEL = 'channel'

i2c_dimmer_ns = cg.esphome_ns.namespace('i2c_dimmer')
I2CDimmerOutput = i2c_dimmer_ns.class_(
    'I2CDimmerOutput', light.LightOutput, cg.Component, i2c.I2CDevice
)

CONFIG_SCHEMA = (
    light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend(
        {
            cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(I2CDimmerOutput),
            cv.Required(CONF_CHANNEL): cv.uint8_t,
        }
    )
    .extend(cv.COMPONENT_SCHEMA)
    .extend(i2c.i2c_device_schema(None))
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    await i2c.register_i2c_device(var, config)
    cg.add(var.set_channel(config[CONF_CHANNEL]))
