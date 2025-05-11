
#include "drv_led.h"

/* 状态机枚举类型 */
typedef enum
{
    LED_IDLE,     // 空闲状态
    LED_DEBOUNCE, // 触发防抖检测
    LED_BLINK_ON, // 闪烁亮阶段
    LED_BLINK_OFF // 闪烁灭阶段
} LedBlinkState;

static LedBlinkState led_status = LED_IDLE; // 初始状态
static uint16_t led_timer = 0;              // 时间基准计数器
static uint8_t blink_count = 0;             // 闪烁次数计数器
static BOOL is_blinking = FALSE;            // 防止重入标志

#define DEBOUNCE_TIME 2   // 消抖时间20ms（2 * 10ms）
#define BLINK_INTERVAL 50 // 闪烁间隔500ms（50 * 10ms）
#define MAX_BLINKS 5      // 最大闪烁次数（可选限制）

/**
 * @brief 配置GPIO
 *
 */
void drv_led_init(void)
{
    gpio_init_type gpio_init_struct;

    // * 时钟总线初始化
    crm_periph_clock_enable(CRM_GPIOD_PERIPH_CLOCK, TRUE);
    gpio_default_para_init(&gpio_init_struct);
    // * 默认低电平
    gpio_bits_set(PORT_LED1, GPIO_PINS_14 | GPIO_PINS_15);
    gpio_init_struct.gpio_pins = GPIO_PINS_14 | GPIO_PINS_15;
    gpio_init_struct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_MODERATE;
    gpio_init_struct.gpio_mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL;
    gpio_init_struct.gpio_pull = GPIO_PULL_NONE;
    gpio_init(PORT_LED1, &gpio_init_struct); // * 初始化
}

/* GPIO控制函数（需根据硬件实现） */
void led_set_state(BOOL is_on)
{
    // 示例：控制GPIOD_PIN_15的LED
    if (is_on)
        gpio_bits_reset(GPIOD, GPIO_PINS_15);
    else
        gpio_bits_set(GPIOD, GPIO_PINS_15);
}

/* 触发LED闪烁（外部调用） */
void start_led_blink(void)
{
    if (!is_blinking)
    { // 防止重入
        led_status = LED_DEBOUNCE;
        led_timer = 0;
    }
}

/* LED闪烁任务（每10ms调用一次） */
void led_blink_task(void)
{
    switch (led_status)
    {
    case LED_IDLE:
        // 默认状态无操作
        break;

    case LED_DEBOUNCE:
        if (++led_timer >= DEBOUNCE_TIME)
        {
            led_status = LED_BLINK_ON;
            led_timer = 0;
            blink_count = 0;
            is_blinking = TRUE;
            led_set_state(TRUE); // 首次点亮LED
        }
        break;

    case LED_BLINK_ON:
        if (++led_timer >= BLINK_INTERVAL)
        {
            led_status = LED_BLINK_OFF;
            led_timer = 0;
            led_set_state(FALSE); // 熄灭LED
            if (++blink_count >= MAX_BLINKS)
            { // 可选次数限制
                led_status = LED_IDLE;
                is_blinking = FALSE;
            }
        }
        break;

    case LED_BLINK_OFF:
        if (++led_timer >= BLINK_INTERVAL)
        {
            led_status = LED_BLINK_ON;
            led_timer = 0;
            led_set_state(TRUE); // 重新点亮LED
        }
        break;

    default:
        led_status = LED_IDLE; // 容错处理
        is_blinking = FALSE;
        break;
    }
}
