import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import light
from esphome.const import CONF_OUTPUT_ID
from esphome import pins

DEPENDENCIES = ['i2c']

CONF_I2C_ADDRESS = 'address'
CONF_CHANNEL = 'channel'

i2c_dimmer_ns = cg.esphome_ns.namespace('i2c_dimmer')
I2CDimmerOutput = i2c_dimmer_ns.class_('I2CDimmerOutput', light.LightOutput, cg.Component)

CONFIG_SCHEMA = light.BRIGHTNESS_ONLY_LIGHT_SCHEMA.extend({
    cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(I2CDimmerOutput),
    cv.Required(CONF_I2C_ADDRESS): cv.i2c_address,
    cv.Required(CONF_CHANNEL): cv.uint8_t,
}).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
    cg.add(var.set_i2c_address(config[CONF_I2C_ADDRESS]))
    cg.add(var.set_channel(config[CONF_CHANNEL]))