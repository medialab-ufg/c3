#ifndef C3_UTILS_H
#define C3_UTILS_H 

#ifndef FALSE
#  define FALSE (0)
#endif
#ifndef TRUE
#  define TRUE (!FALSE)
#endif



double log_base(double n, double base);
uint32_t note2color(int16_t pinch, uint8_t ID);
uint16_t increase_vol(uint16_t amp, uint16_t vol, uint16_t v_max);
uint16_t decrease_vol(uint16_t amp, uint16_t vol);
void play_single_note(uint16_t pinch, uint16_t duration, uint16_t amplitude);
void play_single_note2(uint16_t pinch, uint16_t duration, uint16_t amplitude);
uint32_t Cor(float r, float g, float b);
uint32_t Color(uint8_t r, uint8_t g, uint8_t b);

#endif
