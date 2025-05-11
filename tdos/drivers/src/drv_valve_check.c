
#include "drv_valve_check.h"

static uint32_t timeout = 0;
static BOOL is_trigger_finished = FALSE;

static gpio_state_t current_state = STATE_IDLE;
static uint32_t active_counter = 0;
static uint32_t debounce_counter = 0;

// * 初始化测试阀门相关引脚
void driver_vcheck_gpio_init(void)
{
    gpio_init_type gpio_init_struct;
    // * 时钟总线初始化
    crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK, TRUE);

    gpio_default_para_init(&gpio_init_struct);

    gpio_bits_reset(GPIOB, GPIO_PINS_12 | GPIO_PINS_13);

    gpio_init_struct.gpio_pins = GPIO_PINS_12 | GPIO_PINS_13;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(GPIOB, &gpio_init_struct); // * 初始化

    driver_vcheck_ground_ready();
}

// * 接地引脚调整
void driver_vcheck_ground_ready(void)
{
    gpio_bits_set(GPIOB, GPIO_PINS_12); // 选取MOSI引脚复用为测试引脚
}

// * 测试一次
void driver_vcheck_start_once(BOOL *bTrigger)
{
    switch (current_state)
    {
    case STATE_IDLE:
        if (*bTrigger)
        {
            current_state = STATE_DEBOUNCE; // 进入防抖等待
            debounce_counter = 100;         // 防抖窗口50ms
        }
        break;

    case STATE_DEBOUNCE:
        if (debounce_counter > 0)
        {
            debounce_counter--;
        }
        else
        {
            gpio_bits_set(GPIOB, GPIO_PINS_13); // 确认触发，拉高GPIO
            active_counter = 1000;              // 1秒激活
            current_state = STATE_ACTIVE;
        }
        break;

    case STATE_ACTIVE:
        if (active_counter > 0)
        {
            active_counter--;
        }
        else
        {
            gpio_bits_reset(GPIOB, GPIO_PINS_13); // 1秒结束，拉低GPIO
            current_state = STATE_IDLE;
            *bTrigger = FALSE;
        }
        break;
    }
}