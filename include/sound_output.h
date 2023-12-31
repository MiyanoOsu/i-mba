#ifndef SOUND_OUTPUT_H
#define SOUND_OUTPUT_H

#define SOUND_OUTPUT_FREQUENCY 44100
#define SOUND_SAMPLES_SIZE 2048

extern uint32_t Audio_Init();
extern void Audio_Write(int16_t* buffer, uint32_t buffer_size);
extern void Audio_Close();

#endif
