#include "unity.h" 
#include "node.h" 
#include "hal.h" 
#include "hal_double.h" 
#include "frame.h" 
#include <string.h> 
#include <stdio.h> 
#define ADC_25   931u     
#define ADC_54   1291u    
#define ADC_55B  1304u    
#define ADC_70   1490u    
#define ADC_130  2234u    
/* 25,00 °C  */ 
/* 54,02 °C  */ 
/* 55,06 °C  : au bord de l'hystérésis (>= 55) */ 
/* 70,04 °C  */ 
/* 129,99 °C : hors plage */ 
void setUp(void) { hal_double_reset(); node_init(6000, 500); node_set_data_period_ms(0u); } 
void tearDown(void) {} 
/* alterne adc / adc+1 (0,08 °C) pour ne pas déclencher la détection de capteur figé (EF-05) */ 
static void feed(uint16_t adc, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc((uint16_t)(adc + (uint16_t)(i & 1))); 
hal_double_advance_ms(1000u); node_step(); } } 
/* même valeur brute répétée : sert aux tests de capteur figé */ 
static void feed_same(uint16_t adc, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc(adc); hal_double_advance_ms(1000u); node_step(); } } 
static void feed_seq(const uint16_t *v, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc(v[i]); hal_double_advance_ms(1000u); node_step(); } } 
static bool last_frame_has(const char *s) 
{ size_t n; const uint8_t *f = hal_double_last_frame(&n); return (f != NULL) && (strstr((const char *)f, s) != 
NULL); } 
static void queue_signed(const char *payload_without_crc) 
{ 
char c[128]; size_t n = strlen(payload_without_crc); 
snprintf(c, sizeof c, "%.*s,\"crc\":\"%04X\"}", (int)n - 1, payload_without_crc, crc16_ccitt_false((const 
uint8_t *)payload_without_crc, n)); 
hal_double_queue_command(c); 
} 
void test_EF04_alert_after_three_above(void) 
{ 
feed(ADC_25, 5); feed(ADC_70, 3); 
TEST_ASSERT_EQUAL(STATE_ALERT, node_state()); 
} 
int main(void) 
1~#include "unity.h" 
#include "node.h" 
#include "hal.h" 
#include "hal_double.h" 
#include "frame.h" 
#include <string.h> 
#include <stdio.h> 
#define ADC_25   931u     
#define ADC_54   1291u    
#define ADC_55B  1304u    
#define ADC_70   1490u    
#define ADC_130  2234u    
/* 25,00 °C  */ 
/* 54,02 °C  */ 
/* 55,06 °C  : au bord de l'hystérésis (>= 55) */ 
/* 70,04 °C  */ 
/* 129,99 °C : hors plage */ 
void setUp(void) { hal_double_reset(); node_init(6000, 500); node_set_data_period_ms(0u); } 
void tearDown(void) {} 
/* alterne adc / adc+1 (0,08 °C) pour ne pas déclencher la détection de capteur figé (EF-05) */ 
static void feed(uint16_t adc, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc((uint16_t)(adc + (uint16_t)(i & 1))); 
hal_double_advance_ms(1000u); node_step(); } } 
/* même valeur brute répétée : sert aux tests de capteur figé */ 
static void feed_same(uint16_t adc, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc(adc); hal_double_advance_ms(1000u); node_step(); } } 
static void feed_seq(const uint16_t *v, int n) 
{ for (int i = 0; i < n; i++) { hal_double_push_adc(v[i]); hal_double_advance_ms(1000u); node_step(); } } 
static bool last_frame_has(const char *s) 
{ size_t n; const uint8_t *f = hal_double_last_frame(&n); return (f != NULL) && (strstr((const char *)f, s) != 
NULL); } 
static void queue_signed(const char *payload_without_crc) 
{ 
char c[128]; size_t n = strlen(payload_without_crc); 
snprintf(c, sizeof c, "%.*s,\"crc\":\"%04X\"}", (int)n - 1, payload_without_crc, crc16_ccitt_false((const 
uint8_t *)payload_without_crc, n)); 
hal_double_queue_command(c); 
} 
void test_EF04_alert_after_three_above(void) 
{ 
feed(ADC_25, 5); feed(ADC_70, 3); 
TEST_ASSERT_EQUAL(STATE_ALERT, node_state()); 
} 
int main(void) 
{ 
    UNITY_BEGIN(); 
    RUN_TEST(test_EF04_alert_after_three_above); 
    return UNITY_END(); 
} 
